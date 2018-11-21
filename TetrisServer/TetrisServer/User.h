#include "ClientSocket.h"

#pragma once
class CUser
{
public:
	CUser();
	~CUser();

	bool SetSocket(ClientSocket* pSocket);

	ClientSocket* pSocket;
};

