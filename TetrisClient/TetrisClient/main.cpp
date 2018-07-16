#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <winsock2.h>
#include <Windows.h>
#include <thread>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <iostream>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include "ServerMessage.pb.h"

#pragma comment(lib, "ws2_32.lib")

#define BUF_SIZE 512
using namespace std;
using namespace google;

struct MessageHeader
{
	google::protobuf::uint32 size;
	ServerMessage::MessageType type;
};
const int MessageHeaderSize = sizeof(MessageHeader);

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
	/**/
	std::thread thread1([&hSocket]()->void {
		while (1)
		{

			int strLen = 0;
			int readLen = 0;
			int nTotalLen = 0;
			char message[BUF_SIZE];
			while ((readLen = recv(hSocket, message, BUF_SIZE - 1, 0)) == 0)
			{
			}
			
			//cout << "From : " << message << endl;


			
			protobuf::io::ArrayInputStream input_array_stream(message, readLen);
			protobuf::io::CodedInputStream input_coded_stream(&input_array_stream);

			MessageHeader messageHeader;
			if (input_coded_stream.ReadRaw(&messageHeader, MessageHeaderSize))
			{
				const void* payload_ptr = NULL;
				int remainSize = 0;
				input_coded_stream.GetDirectBufferPointer(&payload_ptr, &remainSize);
				if (remainSize < (signed)messageHeader.size)
				{
					return;
				}

				protobuf::io::ArrayInputStream payload_array_stream(payload_ptr, messageHeader.size);
				protobuf::io::CodedInputStream payload_input_stream(&payload_array_stream);

				if (messageHeader.type == ServerMessage::CHAT)
				{

					ServerMessage::Chat recvMessage;
					if (false == recvMessage.ParseFromCodedStream(&payload_input_stream))
						break;

					printf("From : %s", recvMessage.message().c_str());
				}

			}
		}
	});

	std::thread thread2([&hSocket]()->void {
		char* messageBuf = new char[BUF_SIZE];
		char message[BUF_SIZE];

		while (1)
		{
			int strLen = 0;
			int readLen = 0;
			

			//fputs("InputMessage q To quit) : ", stdout);
			//fgets(message, BUF_SIZE, stdin);
			//cout << "InputMessage : ";
			//cin >> message;

			
			fgets(message, BUF_SIZE, stdin);
			strLen = strlen(message);
			
			ServerMessage::Chat sendMessage;
			sendMessage.set_dst_id(10);
			sendMessage.set_name("aas");
			sendMessage.set_message(message);



			MessageHeader messageHeader;
			messageHeader.size = sendMessage.ByteSize();
			messageHeader.type = ServerMessage::CHAT;

			int nLen = MessageHeaderSize + sendMessage.ByteSize();
			protobuf::io::ArrayOutputStream  output_array_stream(messageBuf, nLen);
			protobuf::io::CodedOutputStream output_coded_stream(&output_array_stream);
			output_coded_stream.WriteRaw(&messageHeader, MessageHeaderSize);

			sendMessage.SerializeToCodedStream(&output_coded_stream);
			

			/*
			WSABUF* pBuf = (WSABUF*)malloc(sizeof(WSABUF));
			memset(pBuf, 0, sizeof(WSABUF));
			pBuf->buf = messageBuf;
			pBuf->len = sendMessage.ByteSize();

			OVERLAPPED* lpo = (OVERLAPPED*)malloc(sizeof(OVERLAPPED));
			memset(pBuf, 0, sizeof(OVERLAPPED));

			int nRet = WSASend(hSocket, pBuf, 1, NULL, 0, lpo, NULL);
			DWORD dword = ::GetLastError();
			printf("%d %d\n", nRet, dword);
			*/
			
			
			//if (nLen != output_coded_stream.ByteCount())
			{
				printf("SendBytes : %d %d\n", nLen, output_coded_stream.ByteCount());
			}
			int nRet = send(hSocket, messageBuf, nLen, 0);
			//int nRet = send(hSocket, message, strLen, 0);
			if (nRet == ERROR_CURRENT_DIRECTORY)
			{
				printf("ERROR_CURRENT_DIRECTORY");
			}
			//DWORD dword = ::GetLastError();
			printf("%d\n", nRet);
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
