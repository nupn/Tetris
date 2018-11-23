#pragma once
#include "singletone.h"
#include "Protocol.h"
#include "LoginSession.h"
#include "LobbySession.h"

using namespace NPL;

class CSessionPool : public Singletone<CSessionPool>
{
public:
	CSessionPool();
	virtual ~CSessionPool();

	PacketHandler* GetLoginSession();
	PacketHandler* GetLobbySession();


private:
	CLoginSession m_pLoginSession;
	CLobbySession m_pLobbySession;
};

