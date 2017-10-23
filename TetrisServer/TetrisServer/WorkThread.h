#pragma once
#include <thread>
#include <winsock2.h>
using namespace std;

class WorkThread
{
public:
	WorkThread();
	~WorkThread();
	
	void Proc(HANDLE hComPort);

private:
	shared_ptr<thread> m_pthread;
};

