#include "SessionPool.h"



CSessionPool::CSessionPool()
{
}


CSessionPool::~CSessionPool()
{
}


PacketHandler* CSessionPool::GetLoginSession()
{
	return &m_pLoginSession;
}


PacketHandler* CSessionPool::GetLobbySession()
{
	return &m_pLobbySession;
}


