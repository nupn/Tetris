#pragma once
#include "GameSession.h"
#include <vector>
#include "Singletone.h"
class  CGameSessionTable : public CGameSession, public NPL::Singletone<CGameSessionTable>
{
public:
	enum
	{
		kMaxSessionCnt = 60,
	};

public:
	CGameSessionTable();
	~CGameSessionTable();

	CGameSession* CreateSession();
	void DeleteSession(CGameSession* session);
	
private:
	std::vector<CGameSession*> m_vecSessionTable;


};

