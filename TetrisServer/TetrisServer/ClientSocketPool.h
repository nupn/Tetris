#pragma once
#include "ClientSocket.h"
#include "Singletone.h"

using namespace NPL;

class ClientSocketPool : public Singletone<ClientSocketPool>
{
public:
	ClientSocketPool();
	virtual ~ClientSocketPool();

	ClientSocketPtr CreateSocket();
	bool DelSocket(DWORD nCompletionKey);
	ClientSocketPtr GetSocket(DWORD nCompletionKey) const;

	template<typename T>
	void ForEach(T function) const {
		//복사 횟수 테스트 필요
		for (auto iter : m_vecSockets)
		{
			function(iter);
		}
	}

private:
	bool __AddSocket(ClientSocketPtr pSocket);

	static mutex      m_mutex;
	static int			m_uid;
private:
	vector<ClientSocketPtr> m_vecSockets;
};
