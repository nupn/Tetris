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
		kCol = 5,
		kRow = 2,
		kRoomCount = kRow * kCol,
	};

public:
	CREATE_FUNC(CRoomListLayer);
	CRoomListLayer();
	virtual ~CRoomListLayer();

	virtual bool init() override;
	void menuSelectCallback(Ref* pSender);

	void NextPage();
	void PrevPage();

private:
	void _clearSellInfo();
	void _initCell();
	void _setSetInfo(int idx, RoomInfo& info);

private:
	vector<RoomInfo> _vecRoomInfos;
	bool _bShowPrev = false;
	bool _bShowLast= false;

};

