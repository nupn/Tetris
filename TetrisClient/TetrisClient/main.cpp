#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <winsock2.h>
#include <Windows.h>
#include <thread>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <iostream>
#pragma comment(lib, "ws2_32.lib")

#define BUF_SIZE 100
using namespace std;

void ErrorHandling(char *message);

class TestCls
{
public:
	TestCls() {};
	~TestCls() {};

	char data[512];

	void OnData(const boost::system::error_code& err, std::size_t bytes_transferred)
	{

		printf("Message from server : [%d]%s\n", bytes_transferred, data);
	}

};

int main(int argc, char *argv[])
{
	WSADATA wsaData;
	SOCKET hSocket;
	SOCKADDR_IN servAdr;
	
	if (argc != 3)
	{
		printf("usage : %s ", argv[0]);
		exit(1);
	}

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		ErrorHandling("WSAStartup() error!");
	}

	hSocket = socket(PF_INET, SOCK_STREAM, 0);
	if (hSocket == INVALID_SOCKET)
	{
		ErrorHandling("socket() error!");
	}

	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = inet_addr(argv[1]);
	servAdr.sin_port = htons(atoi(argv[2]));

	if (connect(hSocket, (SOCKADDR*)&servAdr, sizeof(servAdr)) == SOCKET_ERROR)
	{
		ErrorHandling("connect() error!");

	}
	else
	{
		puts("connected.......");
	}

	std::thread thread1([&hSocket]()->void {
		while (1)
		{

			int strLen = 0;
			int readLen = 0;
			char message[BUF_SIZE];
			while ((readLen = recv(hSocket, &message[readLen], BUF_SIZE - 1, 0)) == 0)
			{
			}
			
			message[readLen] = '\n';
			message[readLen + 1] = 0;
			//cout << "From : " << message << endl;
			fputs("FromServer : ", stdout);
			fputs(message, stdout);
			fputs("\n", stdout);

			fputs("InputMessage : ", stdout);
		}
	});

	std::thread thread2([&hSocket]()->void {
		while (1)
		{
			int strLen = 0;
			int readLen = 0;
			char message[BUF_SIZE];

			//fputs("InputMessage q To quit) : ", stdout);
			//fgets(message, BUF_SIZE, stdin);
			//cout << "InputMessage : ";
			//cin >> message;
			fgets(message, BUF_SIZE, stdin);

			strLen = strlen(message);
			send(hSocket, message, strLen, 0);
		}
	});

	thread2.join();
	thread1.join();



	closesocket(hSocket);
	WSACleanup();
	return 0;
}

void ErrorHandling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
