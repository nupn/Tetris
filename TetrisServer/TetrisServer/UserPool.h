#pragma once
#include "string"
#include "User.h"
#include "Singletone.h"

using namespace NPL;
using namespace std;

class CUserPool : public Singletone<CUserPool>
{
public:
	CUserPool();
	virtual ~CUserPool();

	bool CreateNewUser(string strUserName, CUser* pOutUser);
	void DeleteUser(string  strUserName, CUser* pOutUser);

	bool FindUser(string strUserName, CUser* pOutUser);
	void Lock();
	void UnLock();
};

