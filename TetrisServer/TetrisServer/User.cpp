#include "stdafx.h"
#include "User.h"
#include "ClientSocket.h"


CUser::CUser()
{
}


CUser::~CUser()
{
}

bool CUser::SetSocket(ClientSocket* pSocket)
{
	if (_pSocket == nullptr)
	{
		_pSocket = pSocket;
		return true;
	}

	return false;
}