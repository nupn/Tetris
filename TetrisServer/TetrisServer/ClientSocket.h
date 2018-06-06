#pragma once
#include "NPCMemoryPool/NPCMemoryPool.h"
#include "Structs.h"
#include "PacketBase.h"
#include <functional>

using namespace NPCL;


struct OVERLAPPEDEX : public OVERLAPPED
{
	int nRwMode;
};

class ClientSocket
{
public:
	enum
	{
		WRITE_SOCKET = 0,
		READ_SOCKET
	};

public:
	ClientSocket();
	ClientSocket(DWORD dwIOCPKey);

	~ClientSocket();
	
	void PutPacket(ServerMessage::MessageType packetType, ::google::protobuf::Message* message);
	void SendPacket(ServerMessage::MessageType packetType, ::google::protobuf::Message* message);
	void FlushPacket();
	void OnSendComplete();
	

	void OnReceive();
	void OnReceiveComplete(int nReceiveBype);
	void GetPacket(PacketHandler& pPacketHandle);

private:
void __SendPacket();

public:

	SOCKET hClntSock;
	SOCKADDR_IN clntAdr;

	OVERLAPPEDEX sendOverlapped;
	OVERLAPPEDEX recvOoverlapped;


	WSABUF	sendWsaBuf;
	WSABUF	recvWsaBuf;

	char sendbuffer[BUF_SIZE];
	int nSendBuffUsed = 0;
	int nSendBuffReserved = 0;


	char recvbuffer[BUF_SIZE];
	int nRecvBufferUsed = 0;


	DWORD m_dwIOCPKey;

	MEMPOOL_OPERATOR(ClientSocket, 100);

};



MEMPOOL_STATIC(ClientSocket, 100)