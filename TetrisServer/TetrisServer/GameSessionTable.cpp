#include "GameSessionTable.h"



CGameSessionTable::CGameSessionTable()
{
	m_vecSessionTable.reserve(kMaxSessionCnt);
}


CGameSessionTable::~CGameSessionTable()
{
}

CGameSession* CGameSessionTable::CreateSession()
{

	CGameSession* pSession = new CGameSession;
	m_vecSessionTable.emplace_back(pSession);

	return pSession;
}

void CGameSessionTable::DeleteSession(CGameSession* session)
{
	auto iter = std::find(std::begin(m_vecSessionTable), std::end(m_vecSessionTable), session);
	if (iter == std::end(m_vecSessionTable))
	{
		
	}
}

