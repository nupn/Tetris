
#include "stdafx.h"
#include "Structs.h"
#include "WorkThread.h"
#include "Protocol.h"
#include "LobbySession.h"

WorkThread::WorkThread()
{
}


WorkThread::~WorkThread()
{
}


void WorkThread::Proc(HANDLE hComPort)
{
	m_pthread.reset(new thread(&WorkThread::Run, this, hComPort));

	//worker.join();
}

void WorkThread::Run(HANDLE hComPort)
{
	ClientSocketPool* pSocketPool = ClientSocketPool::GetInstnace();
	
	while (1)
	{
		DWORD bytesTrans;
		DWORD iocpKey;
		DWORD flags = 0;

		OVERLAPPEDEX* pOverlappedEx;
		int ret = GetQueuedCompletionStatus(hComPort, &bytesTrans, (LPDWORD)&iocpKey, (LPOVERLAPPED*)&pOverlappedEx, INFINITE);
		if (ret != 1)
		{
			printf("Invalid ret %d\n", ret);
			CloseSocket(iocpKey);
			continue;
		}

		if (bytesTrans == 0)
		{
			CloseSocket(iocpKey);
			continue;
		}

		ClientSocketPtr socket = pSocketPool->GetSocket(iocpKey);
		if (pOverlappedEx->nRwMode == ClientSocket::READ_SOCKET)
		{
			socket->OnReceiveComplete(bytesTrans);
			socket->ReadAndConsumeBuffer();
			socket->OnReceive();
		}
		else if (pOverlappedEx->nRwMode == ClientSocket::WRITE_SOCKET)
		{
			socket->OnSendComplete();
			socket->FlushPacket();
		}
	}
}

void WorkThread::CloseSocket(DWORD dwIOCPKey)
{
	ClientSocketPool* pSocketPool = ClientSocketPool::GetInstnace();
	ClientSocketPtr socket = pSocketPool->GetSocket(dwIOCPKey);
	if (socket != nullptr)
	{
		pSocketPool->DelSocket(dwIOCPKey);
	}

}