#pragma once
#include "ClientSocketPool.h"

using namespace std;

class WorkThread
{
public:
	WorkThread();
	~WorkThread();
	
	void Proc(HANDLE hComPort);

	void Run(HANDLE hComPort);

private:
	shared_ptr<thread> m_pthread;
};

