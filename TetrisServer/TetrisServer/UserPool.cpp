#include "UserPool.h"
#include <algorithm>


CUserPool::CUserPool()
{
}


CUserPool::~CUserPool()
{
}


CUser* CUserPool::CreateNewUser(string strUserName)
{
	//writeLock
	auto iter = std::find_if(begin(m_vecUserList), end(m_vecUserList), [&strUserName](const auto& pUser)->bool {
		if (strcmp(strUserName.c_str(), pUser->GetName().c_str()) == 0)
		{
			return true;
		}

		return false;
	});

	if (iter != end(m_vecUserList))
	{
		return nullptr;
	}

	CUser* pUser = new CUser();
	m_vecUserList.push_back(pUser);

	//unwirte lock

	return pUser;
}

void CUserPool::DeleteUser(string  strUserName, CUser* pOutUser)
{

}

bool CUserPool::FindUser(string strUserName, CUser* pOutUser)
{
	return true;
}
