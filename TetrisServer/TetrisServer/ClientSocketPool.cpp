
#include "stdafx.h"
#include "ClientSocketPool.h"


mutex ClientSocketPool::m_mutex;
int ClientSocketPool::m_uid = 0;

ClientSocketPool::ClientSocketPool()
{
}


ClientSocketPool::~ClientSocketPool()
{
}

ClientSocketPtr ClientSocketPool::CreateSocket()
{
	//serialobject ::interlockinterchange
	std::lock_guard<std::mutex> lock(m_mutex);
	ClientSocketPtr pSocket = make_shared<ClientSocket>(m_uid);
	++m_uid;


	__AddSocket(pSocket);

	return pSocket;
}

// mutax Ãß°¡ 
bool ClientSocketPool::__AddSocket(ClientSocketPtr pSocket)
{
	auto iter = std::find_if(begin(m_vecSockets), end(m_vecSockets), [pSocket](auto& item) -> bool
	{
		if (item->m_dwIOCPKey == pSocket->m_dwIOCPKey)
		{
			return true;
		}
		return false;
	});

	if (iter != m_vecSockets.end())
	{
		return false;
	}

	m_vecSockets.push_back(pSocket);
	return true;
}

bool ClientSocketPool::DelSocket(DWORD nCompletionKey)
{
	auto iter = std::remove_if(begin(m_vecSockets), end(m_vecSockets), [nCompletionKey](auto& item) -> bool
	{
		if (item->m_dwIOCPKey == nCompletionKey)
		{
			return true;
		}
	return false;
	});

	if (iter == m_vecSockets.end())
	{
		return false;
	}

	return true;
}

ClientSocketPtr ClientSocketPool::GetSocket(DWORD nCompletionKey) const
{
	auto iter = std::find_if(begin(m_vecSockets), end(m_vecSockets), [nCompletionKey](auto& item) -> bool
	{
		if (item->m_dwIOCPKey == nCompletionKey)
		{
			return true;
		}
	return false;
	});

	if (iter == m_vecSockets.end())
	{
		return nullptr;
	}

	return (*iter);
}