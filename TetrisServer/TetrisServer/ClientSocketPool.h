#pragma once
#include "ClientSocket.h"
#include <mutex>
#include <boost/serialization/singleton.hpp>

class ClientSocketPool : public boost::serialization::singleton<ClientSocketPool>
{
public:
	friend class boost::serialization::singleton<ClientSocketPool>;

	ClientSocketPool();
	~ClientSocketPool();

	ClientSocket* CreateSocket();
	bool AddSocket(ClientSocket* pSocket);
	bool DelSocket(DWORD nCompletionKey);
	ClientSocket* GetSocket(DWORD nCompletionKey) const;

	template<typename T>
	void ForEach(T function) const {
		//복사 횟수 테스트 필요
		for (auto iter : m_vecSockets)
		{
			function(iter);
		}
	}

	static mutex      m_mutex;
	static int			m_uid;
private:
	vector<ClientSocket*> m_vecSockets;
};
