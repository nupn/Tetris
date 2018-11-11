#pragma once
#include "cocos2d.h"
#include <vector>

using namespace cocos2d;
using namespace std;

struct RoomInfo
{
	string strRoomName = "None";

};

class CRoomListLayer : public Layer
{
public:
	enum
	{
		kCol = 3,
		kRow = 2,
		kRoomCount = kRow * kCol,
		kMaxCapacity = 36,
	};

public:
	CREATE_FUNC(CRoomListLayer);
	CRoomListLayer();
	virtual ~CRoomListLayer();

	virtual bool init() override;
	void _roomSelectCallback(Ref* pSender);

	void NextPage();
	void PrevPage();

private:
	void _clearSellInfo();
	void _initCell();
	void _updateCell();
	void _setSetInfo(int idx, RoomInfo& info);

private:
	vector<RoomInfo> _vecRoomInfos;
	int _nPage = 0;
};

