#include "stdafx.h"
#include "LobbySession.h"

#include "ClientSocketPool.h"


LobbySession::LobbySession()
{
}


LobbySession::~LobbySession()
{
}


void LobbySession::Handle(const ServerMessage::Login& message, ClientSocket* pSocket)
{

}

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
