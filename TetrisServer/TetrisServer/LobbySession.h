#pragma once
#include "Protocol.h"

class ClientSocket;

class LobbySession : public PacketHandler
{
public:
	LobbySession();
	~LobbySession();

	virtual void Handle(const ServerMessage::Login& message, ClientSocket* pSocket);
	virtual void Handle(const ServerMessage::Chat& message, ClientSocket* pSocket);
	virtual void Handle(const ServerMessage::Move& message, ClientSocket* pSocket);
};

