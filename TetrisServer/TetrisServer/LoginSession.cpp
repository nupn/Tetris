#include "stdafx.h"
#include "LoginSession.h"

#include "ClientSocketPool.h"
#include "UserPool.h"
#include "SessionPool.h"

CLoginSession::CLoginSession()
{
}


CLoginSession::~CLoginSession()
{
}


void CLoginSession::Handle(int nMessageType, protobuf::io::CodedInputStream* codedStream, ClientSocket* pSocket)
{
	if (codedStream == nullptr)
	{
		return;
	}

	switch (nMessageType)
	{
	case ServerMessage::MessageType::kReqLogin:
	{
		ServerMessage::MessageBase::ReqLogin message;
		if (false == message.ParseFromCodedStream(codedStream))
			break;

		__OnReqLogin(message, pSocket);
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


void CLoginSession::__OnReqLogin(ServerMessage::MessageBase::ReqLogin& onPacket, ClientSocket* pSocket)
{
	const string& userName = onPacket.name();
	CUserPool* userPoolref = CUserPool::GetInstnace();
	CUser* pNewUser = nullptr;
	int ret = 0;
	if (userPoolref->CreateNewUser(userName, pNewUser) && pNewUser != nullptr)
	{
		if (pNewUser->SetSocket(pSocket))
		{
			ret = 1;
		}
	}

	auto pLobbySession = CSessionPool::GetInstnace()->GetLobbySession();
	if (pLobbySession)
	{
		pSocket->SetPacketHandler(pLobbySession);
	}
	else
	{

	}
	/*
	ServerMessage::MessageBase_ResLogin sendMessage;
	sendMessage.set_res(ret);
	pSocket->SendPacket(ServerMessage::MessageType::kResLogin, &sendMessage);
	*/
}