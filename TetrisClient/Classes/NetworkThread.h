#pragma once
#include <thread>
#include "../proj.win32/Socket.h"
#include "../proj.win32/PacketHandler.h"
#include "Singletone.h"


//performFunctionInCocosThread example
//http://codelala.net/cocos2d-x-2-05-multi-threading-2-mutex/
class CNetworkThread : public NPL::Singletone<CNetworkThread>
{
public:

	CNetworkThread();
	virtual ~CNetworkThread();

	void Start(std::string strIp, int nPort, PacketHandler* pHandler);
	void Work();
	void Terminate();

	void SetPacketHandler(PacketHandler* pHandler);

	void SendPacket(ServerMessage::MessageType packetType, ::google::protobuf::Message* message);

private:
	std::string m_strIpAddress;
	int m_nPort;
	PacketHandler* m_pPackethandler;
	std::thread* m_pThread = nullptr;
	Socket m_pSocket;
};

