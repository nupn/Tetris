#pragma once
#include <string>
class ClientSocket;
class CUser
{
public:
	CUser();
	~CUser();

	bool SetSocket(ClientSocket* pSocket);
	std::string GetName();
private:
	ClientSocket* _pSocket = nullptr;
	std::string _strUserName;
};

