#include "stdafx.h"
#include "LobbySession.h"

#include "ClientSocketPool.h"
#include "GameSessionTable.h"
#include "UserPool.h"

CLobbySession::CLobbySession()
{
	m_rooms.resize(kMaxRoomCnt);

	for (int i = 0; i < 10; ++i)
	{
		char roomName[512];
		sprintf(roomName, "RoomName %d", i);
		m_rooms[i].strRoomName = roomName;
	}
}


CLobbySession::~CLobbySession()
{
}


void CLobbySession::Handle(int nMessageType, protobuf::io::CodedInputStream* codedStream, ClientSocket* pSocket)
{
	if (codedStream == nullptr)
	{
		return;
	}

	switch (nMessageType)
	{
	case ServerMessage::MessageType::kReqRoomList:
	{
		__OnReqRoomList(codedStream, pSocket);
	}
	break;

	case ServerMessage::MessageType::kReqCreateRoom:
	{
		__OnReqCreateRoom(codedStream, pSocket);
	}
	break;


	case ServerMessage::MessageType::kReqEnterRoom:
	{
		__OnReqEnterRoom(codedStream, pSocket);
	}
	break;

	}
}

/*
void LobbySession::Handle(const ServerMessage::Chat& message, ClientSocket* pSocket)
{

	ClientSocketPool& socketPoolref = boost::serialization::singleton<ClientSocketPool>::get_mutable_instance();

	const string& msg = message.message();
	printf("OnMessage : %s", msg.c_str());
	socketPoolref.ForEach([msg](ClientSocket* pSocket)->void {
		ServerMessage::Chat sendMessage;
		sendMessage.set_name("aaa1");
		sendMessage.set_dst_id(1);
		sendMessage.set_message(msg);

		pSocket->SendPacket(ServerMessage::CHAT, &sendMessage);
	});
}

void LobbySession::Handle(const ServerMessage::Move& message, ClientSocket* pSocket)
{

}
*/


void CLobbySession::__OnReqRoomList(protobuf::io::CodedInputStream* codedStream, ClientSocket* pSocket)
{
	ServerMessage::MessageBase::ReqRoomList message;
	if (!message.ParseFromCodedStream(codedStream))
	{
		return;
	}



	const int nStartIdx = message.idx();
	int nEndIdx = nStartIdx + kShowRoomCnt;
	int nEncodeCnt = nEndIdx - nStartIdx;
	if (nEncodeCnt <= 0)
	{
		return;
	}

	if (nEndIdx >= kMaxRoomCnt)
	{
		nEndIdx = kMaxRoomCnt - 1;
	}

	ServerMessage::MessageBase_ResRoomList sendMessage;
	sendMessage.set_currentidx(nStartIdx);
	//sendMessage.set_roominfocount(nEncodeCnt);
	for (int i = nStartIdx; i < nEndIdx; ++i)
	{
		const auto& roomInfo = &m_rooms[i];
		auto pPakcetRoomData = sendMessage.add_rooms();
		if (pPakcetRoomData)
		{
			pPakcetRoomData->set_nroomid(roomInfo->nRoomId);
			pPakcetRoomData->set_name(roomInfo->strRoomName);
		}
	}

	pSocket->SendPacket(ServerMessage::MessageType::kResRoomList, &sendMessage);
}
void CLobbySession::__OnReqCreateRoom(protobuf::io::CodedInputStream* codedStream, ClientSocket* pSocket)
{
	ServerMessage::MessageBase::ReqCreateRoom message;
	if (!message.ParseFromCodedStream(codedStream))
	{
		return;
	}

	string strRoomName = message.strroomname();
	int nSlotIdx = message.nroomslotidx();
	int nRoomSize = m_rooms.size();
	if (nSlotIdx < 0 || nSlotIdx >= nRoomSize)
	{
		return;
	}

	auto& roomInfo = m_rooms[nSlotIdx];
	if (roomInfo.nRoomId != -1)
	{
		return;
	}

	roomInfo.nRoomId = __GetRoomId();
	roomInfo.strRoomName = strRoomName;

	auto sessionTable = CGameSessionTable::GetInstance();
	if (!sessionTable)
	{
		return;
	}


	auto pUser = pSocket->GetUser();
	if (pUser)
	{
		auto pSession = sessionTable->CreateSession();
		pSocket->SetPacketHandler(pSession);
		pSession->EnterUser(pUser);
	}
}

void CLobbySession::__OnReqEnterRoom(protobuf::io::CodedInputStream* codedStream, ClientSocket* pSocket)
{
	ServerMessage::MessageBase::ReqEnterRoom message;
	if (!message.ParseFromCodedStream(codedStream))
	{
		return;
	}

	auto sessionTable = CGameSessionTable::GetInstance();
	if (!sessionTable)
	{
		return;
	}

	auto pUser = pSocket->GetUser();
	if (pUser)
	{
		sessionTable->EnterUser(pUser);
	}

}

unsigned int CLobbySession::__GetRoomId()
{
	return m_nRoomId++;
}