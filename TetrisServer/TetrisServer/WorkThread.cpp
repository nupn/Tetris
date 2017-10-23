#include "WorkThread.h"
#include "Structs.h"

WorkThread::WorkThread()
{
}


WorkThread::~WorkThread()
{
}


void WorkThread::Proc(HANDLE hComPort)
{
	m_pthread.reset(new thread(
		[] (HANDLE hCom) {
		SOCKET sock;
		DWORD bytesTrans;
		LPPER_HANDLE_DATA handleInfo;
		LPPER_IO_DATA ioInfo;
		DWORD flags = 0;

		while (1)
		{
			GetQueuedCompletionStatus(hCom, &bytesTrans, (LPDWORD)&handleInfo, (LPOVERLAPPED*)&ioInfo, INFINITE);
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
		}
	}, hComPort));

	//worker.join();
}