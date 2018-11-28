#include "stdafx.h"
#include "LobbySession.h"

#include "ClientSocketPool.h"
#include "UserPool.h"

CLobbySession::CLobbySession()
{
	m_rooms.resize(kMaxRoomCnt);
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
		ServerMessage::MessageBase::ReqRoomList message;
		if (false == message.ParseFromCodedStream(codedStream))
			break;
		
		__OnReqRoomList(message, pSocket);
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


void CLobbySession::__OnReqRoomList(ServerMessage::MessageBase::ReqRoomList& onPacket, ClientSocket* pSocket)
{
	const int nStartIdx = onPacket.idx();
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
	sendMessage.set_roominfocount(nEncodeCnt);
	for (int i = nStartIdx; i < nEndIdx; ++i)
	{
		const auto& roomInfo = &m_rooms[i];
		auto pPakcetRoomData = sendMessage.add_rooms();
		if (pPakcetRoomData)
		{
			pPakcetRoomData->set_name(roomInfo->strRoomName);
		}
	}

	pSocket->SendPacket(ServerMessage::MessageType::kResLogin, &sendMessage);
}