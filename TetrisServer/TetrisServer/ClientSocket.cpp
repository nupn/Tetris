
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

void ClientSocket::PutPacket(ServerMessage::MessageType packetType, ::protobuf::Message* message)
{
	if (message == nullptr)
	{
		return;
	}

	int nPacketSize = message->ByteSize();
	if (nSendBuffUsed + message->ByteSize() > BUF_SIZE)
	{
		//User Reserve
		return;
	}

	protobuf::io::ArrayOutputStream  output_array_stream(sendbuffer + nSendBuffUsed, nPacketSize);
	protobuf::io::CodedOutputStream output_coded_stream(&output_array_stream);


	MessageHeader messageHeader;
	messageHeader.size = nPacketSize;
	messageHeader.type = packetType;
	output_coded_stream.WriteRaw(&messageHeader, sizeof(MessageHeader));

	message->SerializeToCodedStream(&output_coded_stream);
	nSendBuffUsed += message->ByteSize();
}


void ClientSocket::SendPacket(ServerMessage::MessageType packetType, ::google::protobuf::Message* message)
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

	//�ʿ��ұ�?
	memset(&(sendOverlapped), 0, sizeof(OVERLAPPEDEX));
	sendOverlapped.nRwMode = WRITE_SOCKET;

	sendWsaBuf.len = nSendBuffUsed;
	sendWsaBuf.buf = sendbuffer;
	
	DWORD sendCompleteCnt;
	int retSend = ::WSASend(hClntSock, &(sendWsaBuf), 1, &(sendCompleteCnt), 0, &(sendOverlapped), NULL);
	if (retSend == 0)
	{

		int nPrevSend = nSendBuffUsed;
		nSendBuffUsed -= sendCompleteCnt;
		::memmove(sendbuffer, sendbuffer + sendCompleteCnt, BUF_SIZE - nPrevSend);
	}

	//http://www.gpgstudy.com/forum/viewtopic.php?t=24044
	//WSA Send�� ������ ���� �������ʿ䰡 ����.?
	int nLastError = WSAGetLastError();
	if (nLastError == WSA_IO_PENDING)
	{
		nSendBuffReserved = nSendBuffUsed;
	}

	//���� ������ �����Ѱ��
	//�񵿱� Send������ ���۰� �����ϱ⶧���� ��ٸ��� BLOCK���°��� �Ǿ ������ �߻�?
	//https://www.joinc.co.kr/w/man/4100/WSASend
	//https://m.blog.naver.com/PostView.nhn?blogId=wildboys07&logNo=50180104146&proxyReferer=https%3A%2F%2Fwww.google.co.kr%2F
	if (nLastError == WSAEWOULDBLOCK)
	{

	}
}

void ClientSocket::OnSendComplete()
{
	int nPrevSend = nSendBuffUsed;
	::memmove(sendbuffer, sendbuffer + sendOverlapped.InternalHigh, nSendBuffUsed - sendOverlapped.InternalHigh);
	nSendBuffUsed -= sendOverlapped.InternalHigh;
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

	::WSARecv(hClntSock, &(sendWsaBuf), 1, NULL, &flags, &(recvOoverlapped), NULL);
}


void ClientSocket::OnReceiveComplete(int nReceiveBype)
{
	nRecvBufferUsed = nReceiveBype;
}

//http://egloos.zum.com/javawork/v/2726467
void ClientSocket::GetPacket(PacketHandler& pPacketHandle)
{
	protobuf::io::ArrayInputStream input_array_stream(sendWsaBuf.buf, nRecvBufferUsed);
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

		switch (messageHeader.type)
		{
			case ServerMessage::LOGIN:
			{
				ServerMessage::Login message;
				if (false == message.ParseFromCodedStream(&payload_input_stream))
					break;
				pPacketHandle.Handle(message);
			}
			break;
			case ServerMessage::CHAT:
			{
				ServerMessage::Chat message;
				if (false == message.ParseFromCodedStream(&payload_input_stream))
					break;
				pPacketHandle.Handle(message);
			}
			break;
			case ServerMessage::MOVE:
			{
				ServerMessage::Move message;
				if (false == message.ParseFromCodedStream(&payload_input_stream))
					break;
				pPacketHandle.Handle(message);
			}
			break;
		}

	}
}