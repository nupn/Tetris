#pragma once
#include "Protocol.h"
#include "MemoryPool.h"
#include "User.h"
using namespace NPL;

class CGameSession : public PacketHandler
{
public:
	CGameSession();
	~CGameSession();
	void EnterUser(CUser* pUser);
	MEMPOOL_OPERATOR(CGameSession, 100);
};

MEMPOOL_STATIC(CGameSession, 100)
