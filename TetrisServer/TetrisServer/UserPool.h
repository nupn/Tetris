#pragma once
#include "string"
#include "User.h"
#include "Singletone.h"
#include <vector>

using namespace NPL;
using namespace std;

class CUserPool : public Singletone<CUserPool>
{
public:
	CUserPool();
	virtual ~CUserPool();

	CUser* CreateNewUser(string strUserName);
	void DeleteUser(string  strUserName, CUser* pOutUser);

	bool FindUser(string strUserName, CUser* pOutUser);
private:
	std::vector<CUser*> m_vecUserList;
};

