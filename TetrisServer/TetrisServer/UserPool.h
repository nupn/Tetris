#pragma once
#include "string"
#include "User.h"
#include "boost\serialization\singleton.hpp"

using namespace std;

class CUserPool : public boost::serialization::singleton<CUserPool>
{
public:
	friend class boost::serialization::singleton<CUserPool>;

	CUserPool();
	~CUserPool();

	bool CreateNewUser(string strUserName, CUser* pOutUser);
	void DeleteUser(string  strUserName, CUser* pOutUser);

	bool FindUser(string strUserName, CUser* pOutUser);
	void Lock();
	void UnLock();
};

