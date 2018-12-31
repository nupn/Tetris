
#include "stdafx.h"
#include "ClientSocket.h"
#include "Protocol.h"

using namespace google;

ClientSocket::ClientSocket()
{
	memset(&(sendOverlapped), 0, sizeof(OVERLAPPEDEX));
	sendOverlapped.nRwMode = WRITE_SOCKET;

	memset(&(recvOoverlapped), 0, sizeof(OVERLAPPEDEX));
	recvOoverlapped.nRwMode = READ_SOCKET;
}

ClientSocket::ClientSocket(DWORD dwIOCPKey)
: m_dwIOCPKey(dwIOCPKey)
{
}


ClientSocket::~ClientSocket()
{
}

void ClientSocket::PutPacket(int packetType, ::protobuf::Message* message)
{
	if (message == nullptr)
	{
		return;
	}

	int nPacketSize = message->ByteSize() + MessageHeaderSize;
	if (nSendBuffUsed + nPacketSize > BUF_SIZE)
	{
		//User Reserve
		return;
	}

	protobuf::io::ArrayOutputStream  output_array_stream(sendbuffer + nSendBuffUsed, nPacketSize);
	protobuf::io::CodedOutputStream output_coded_stream(&output_array_stream);


	MessageHeader messageHeader;
	messageHeader.size = message->ByteSize();
	messageHeader.type = packetType;
	output_coded_stream.WriteRaw(&messageHeader, sizeof(MessageHeader));

	message->SerializeToCodedStream(&output_coded_stream);
	nSendBuffUsed += nPacketSize;
}


void ClientSocket::SendPacket(int packetType, ::google::protobuf::Message* message)
{
	PutPacket(packetType, message);
	__SendPacket();
}

void ClientSocket::FlushPacket()
{
	if (nSendBuffReserved > 0)
	{
		return;
	}

	if (nSendBuffUsed <= 0)
	{
		return;
	}

	__SendPacket();
}

void ClientSocket::__SendPacket()
{
	if (nSendBuffReserved > 0)
	{
		return;
	}

	nSendBuffReserved = 0;

	//필요할까?
	memset(&(sendOverlapped), 0, sizeof(OVERLAPPEDEX));
	sendOverlapped.nRwMode = WRITE_SOCKET;

	sendWsaBuf.len = nSendBuffUsed;
	sendWsaBuf.buf = sendbuffer;
	
	DWORD sendCompleteCnt;
	int retSend = ::WSASend(hClntSock, &(sendWsaBuf), 1, &(sendCompleteCnt), 0, (OVERLAPPED*)(&sendOverlapped), NULL);
	if (retSend == 0)
	{

		int nPrevSend = nSendBuffUsed;
		nSendBuffUsed -= sendCompleteCnt;
		::memmove(sendbuffer, sendbuffer + sendCompleteCnt, BUF_SIZE - nPrevSend);
	}

	//http://www.gpgstudy.com/forum/viewtopic.php?t=24044
	//WSA Send시 센드후 버퍼 유지할필요가 없다.?
	int nLastError = WSAGetLastError();
	if (nLastError == WSA_IO_PENDING)
	{
		nSendBuffReserved = nSendBuffUsed;
	}

	//버퍼 공간이 부족한경우
	//비동기 Send이지만 버퍼가 부족하기때문에 기다리다 BLOCK상태가이 되어서 오류가 발생?
	//https://www.joinc.co.kr/w/man/4100/WSASend
	//https://m.blog.naver.com/PostView.nhn?blogId=wildboys07&logNo=50180104146&proxyReferer=https%3A%2F%2Fwww.google.co.kr%2F
	if (nLastError == WSAEWOULDBLOCK)
	{

	}
}

void ClientSocket::OnSendComplete()
{
	if (nSendBuffReserved > 0)
	{
		int nPrevSend = nSendBuffReserved;
		::memmove(sendbuffer, sendbuffer + sendOverlapped.overlapped.InternalHigh, nSendBuffUsed - sendOverlapped.overlapped.InternalHigh);
		nSendBuffReserved -= sendOverlapped.overlapped.InternalHigh;
	}
}


//http://yongho1037.tistory.com/531
//http://www.gpgstudy.com/forum/viewtopic.php?t=7564
void ClientSocket::OnReceive()
{
	DWORD flags = 0;
	memset(&(recvOoverlapped), 0, sizeof(OVERLAPPEDEX));
	recvOoverlapped.nRwMode = READ_SOCKET;


	sendWsaBuf.len = BUF_SIZE;
	sendWsaBuf.buf = recvbuffer;

	::WSARecv(hClntSock, &(sendWsaBuf), 1, NULL, &flags, (OVERLAPPED*)(&recvOoverlapped), NULL);
}


void ClientSocket::OnReceiveComplete(int nReceiveBype)
{
	nRecvBufferUsed = nReceiveBype;
}

//http://egloos.zum.com/javawork/v/2726467
void ClientSocket::ReadAndConsumeBuffer()
{
	if (m_pPacketHandler == nullptr)
	{
		return;
	}

	protobuf::io::ArrayInputStream input_array_stream(recvWsaBuf.buf, nRecvBufferUsed);
	protobuf::io::CodedInputStream input_coded_stream(&input_array_stream);

	MessageHeader messageHeader;
	while (input_coded_stream.ReadRaw(&messageHeader, MessageHeaderSize))
	{
		const void* payload_ptr = NULL;
		int remainSize = 0;
		input_coded_stream.GetDirectBufferPointer(&payload_ptr, &remainSize);
		if (remainSize < (signed)messageHeader.size)
		{
			return;
		}

		protobuf::io::ArrayInputStream payload_array_stream(payload_ptr, messageHeader.size);
		protobuf::io::CodedInputStream payload_input_stream(&payload_array_stream);

		input_coded_stream.Skip(messageHeader.size);
		nRecvBufferUsed += MessageHeaderSize + messageHeader.size;


		m_pPacketHandler->Handle(messageHeader.type, &payload_input_stream, this);
		/*
		switch (messageHeader.type)
		{
		case ServerMessage::MessageType::kReqLogin:
			{
				ServerMessage::MessageBase::ReqLogin message;
				if (false == message.ParseFromCodedStream(&payload_input_stream))
					break;
				pPacketHandle->Handle(&message, this);
			}
			break;
			
			case ServerMessage::CHAT:
			{
				ServerMessage::Chat message;
				if (false == message.ParseFromCodedStream(&payload_input_stream))
					break;
				pPacketHandle->Handle(message, this);
			}
			break;
			case ServerMessage::MOVE:
			{
				ServerMessage::Move message;
				if (false == message.ParseFromCodedStream(&payload_input_stream))
					break;
				pPacketHandle->Handle(message, this);
			}
			break;
		}
			*/

	}
}

void ClientSocket::SetPacketHandler(PacketHandler* pPacketHandler)
{
	m_pPacketHandler = pPacketHandler;
}

void ClientSocket::SetUser(CUser* pUser)
{
	m_pUser = pUser;
}

CUser* ClientSocket::GetUser()
{
	return m_pUser;
}
