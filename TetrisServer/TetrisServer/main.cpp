#include "stdafx.h"
#include "WorkThread.h"
#include "Structs.h"
#include "Constants.h"
#include "ClientSocket.h"
#include "ClientSocketPool.h"

unsigned int __stdcall EchoThreadMain(LPVOID CompletionPortIO);
void ErrorHandling(char *message);

int main(int argc, char* argv[])
{
	SetConsoleTitle(L"TetrisServer");

	ClientSocketPool& socketPoolref = boost::serialization::singleton<ClientSocketPool>::get_mutable_instance();
	
	WSADATA wsaData;
	HANDLE hComPort;
	SYSTEM_INFO sysInfo;

	SOCKET hServSock;
	SOCKADDR_IN servAdr;
	int i = 0;
	DWORD recvBytes, flags = 0;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		ErrorHandling("WSAStartup() error!");
			
	}

	hComPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	GetSystemInfo(&sysInfo);

	vector<WorkThread> vecWorkThread;
	vecWorkThread.resize(sysInfo.dwNumberOfProcessors);

	for (auto& workThread : vecWorkThread)
	{
		workThread.Proc(hComPort);
	}


	hServSock = WSASocket(PF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (hServSock == INVALID_SOCKET)
	{
		ErrorHandling("WSASocket() error!");
	}

	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAdr.sin_port = htons(atoi(argv[1]));

	if (::bind(hServSock, (SOCKADDR*)&servAdr, sizeof(servAdr)) == -1)
	{
		ErrorHandling("bind() error!");
	}

	if (listen(hServSock, 5) == -1)
	{
		ErrorHandling("listen() error!");
	}

	while (1)
	{
		SOCKET hClntSock;
		SOCKADDR_IN clntAdr;
		int addrLen = sizeof(clntAdr);

		hClntSock = accept(hServSock, (SOCKADDR*)&clntAdr, &addrLen);
		if (hClntSock == INVALID_SOCKET)
		{  
			int nErrorCode = WSAGetLastError();
			printf("Error %d", nErrorCode);
			ErrorHandling("accept() error!");
		}

		ClientSocket* pSocket = socketPoolref.CreateSocket();
		pSocket->hClntSock = hClntSock;
		memcpy(&(pSocket->clntAdr), &clntAdr, addrLen);
		memset(&(pSocket->recvOoverlapped), 0, sizeof(OVERLAPPED));

		CreateIoCompletionPort((HANDLE)pSocket->hClntSock, hComPort, pSocket->m_dwIOCPKey, 0);

		pSocket->recvWsaBuf.len = BUF_SIZE;
		pSocket->recvWsaBuf.buf = pSocket->recvbuffer;
		pSocket->recvOoverlapped.nRwMode = ClientSocket::READ_SOCKET;
		printf("New Connect\n");

		WSARecv(pSocket->hClntSock, &(pSocket->recvWsaBuf), 1, &recvBytes, &flags, (OVERLAPPED*)(&pSocket->recvOoverlapped), NULL);
	}

	return 0;
}

unsigned int __stdcall EchoThreadMain(LPVOID pComPort)
{
	HANDLE hComPort = (HANDLE)pComPort;
	SOCKET sock;
	DWORD bytesTrans;
	LPPER_HANDLE_DATA handleInfo;
	LPPER_IO_DATA ioInfo;
	DWORD flags = 0;

	while (1)
	{
		GetQueuedCompletionStatus(hComPort, &bytesTrans, (LPDWORD)&handleInfo, (LPOVERLAPPED*)&ioInfo, INFINITE);
		sock = handleInfo->hClntSock;

		if (ioInfo->rwMode == READ)
		{
			puts("message received!");
			if (bytesTrans == 0)
			{
				closesocket(sock);
				free(handleInfo);
				free(ioInfo);
				continue;
			}

			memset(&(ioInfo->overlapped), 0, sizeof(OVERLAPPED));
			ioInfo->wsaBuf.len = bytesTrans;
			ioInfo->rwMode = WRITE;
			WSASend(sock, &(ioInfo->wsaBuf), 1, NULL, 0, &(ioInfo->overlapped), NULL);

			ioInfo = (LPPER_IO_DATA)malloc(sizeof(PER_IO_DATA));
			memset(&(ioInfo->overlapped), 0, sizeof(OVERLAPPED));
			ioInfo->wsaBuf.len = BUF_SIZE;
			ioInfo->wsaBuf.buf = ioInfo->buffer;
			ioInfo->rwMode = READ;
			WSARecv(sock, &(ioInfo->wsaBuf), 1, NULL, &flags, &(ioInfo->overlapped), NULL);

		}
		else
		{
			puts("messager  send!");
			free(ioInfo);
		}

		return 0;
	}
}

void ErrorHandling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}