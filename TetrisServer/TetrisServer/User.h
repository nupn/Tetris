#pragma once
class ClientSocket;
class CUser
{
public:
	CUser();
	~CUser();

	bool SetSocket(ClientSocket* pSocket);

	ClientSocket* pSocket;
};

