#include "RoomListLayer.h"
#include "NetworkThread.h"
#include "TetrisScene.h"


CRoomListLayer::CRoomListLayer()
{
}


CRoomListLayer::~CRoomListLayer()
{
}


bool CRoomListLayer::init()
{
	_vecRoomInfos.clear();
	_vecRoomInfos.resize(kMaxCapacity);
	
	/*
	for (int i = 0; i < 24; ++i)
	{
		char roomName[256];
		sprintf(roomName, "RoomName %d", i);
		_vecRoomInfos[i].strRoomName = roomName;
	}
	*/
	_nPage = 0;
	_initCell();
	_clearSellInfo();
	_updateCell();

	return Layer::init();
}


void CRoomListLayer::NextPage()
{
	if ((_nPage + 1) * kRoomCount >= kMaxCapacity)
	{
		return;
	}

	const int nMaxData = _vecRoomInfos.size();
	if ((_nPage+1) * kRoomCount >= nMaxData)
	{
		return;
	}

	++_nPage;
	_updateCell();
}


void CRoomListLayer::PrevPage()
{
	if (_nPage < 1)
	{
		return;
	}

	--_nPage;
	_updateCell();
}


void CRoomListLayer::_initCell()
{
	removeAllChildrenWithCleanup(true);


	const int nHeightGap = 130;
	const int nWidthGap = 360;
	auto contentsize = Size::Size(348, 97);
	auto startPos = Vec2::Vec2(0, 130);

	Vector<MenuItem*> menulist;
	for (int i = 0; i < kRoomCount; ++i)
	{
		auto cellPos = Vec2::Vec2(startPos.x + nWidthGap * floor(i / kRow), startPos.y - nHeightGap * (i % kRow));

		auto spriteFront = Sprite::create();
		spriteFront->setTag(1);
		spriteFront->setContentSize(contentsize);

		auto background = Sprite::create("RoomList.png");
		background->setAnchorPoint(Vec2::ZERO);
		background->setTag(1);
		spriteFront->addChild(background);

		auto label = Label::create("", "fonts/malgun.ttf", 32);
		label->setColor(Color3B::BLACK);
		label->setAnchorPoint(Vec2::ZERO);
		label->setPosition(Vec2::Vec2(30, 30));
		label->setTag(2);
		spriteFront->addChild(label);

		auto spriteBack = Sprite::create();
		spriteBack->setTag(2);
		spriteBack->setContentSize(contentsize);

		background = Sprite::create("RoomList2.png");
		background->setAnchorPoint(Vec2::ZERO);
		background->setTag(1);
		spriteBack->addChild(background);

		label = Label::create("", "fonts/malgun.ttf", 29);
		label->setColor(Color3B::BLACK);
		label->setAnchorPoint(Vec2::ZERO);
		label->setPosition(Vec2::Vec2(30, 30));
		label->setTag(2);
		spriteBack->addChild(label);

		auto meunItem = MenuItemSprite::create(spriteFront, spriteBack, CC_CALLBACK_1(CRoomListLayer::_roomSelectCallback, this));
		meunItem->setPosition(cellPos);
		meunItem->setAnchorPoint(Vec2::ZERO);
		meunItem->setTag(i);
		menulist.pushBack(meunItem);
	}


	auto menu = Menu::createWithArray(menulist);
	menu->setPosition(Vec2::ZERO);
	menu->setAnchorPoint(Vec2::ZERO);
	menu->setTag(1);
	addChild(menu);
}

void CRoomListLayer::_clearSellInfo()
{
	auto menu = getChildByTag(1);
	if (menu == nullptr)
	{
		return;
	}

	for (int i = 0; i < kRoomCount; ++i)
	{
		auto menuItem = menu->getChildByTag(i);
		if (menuItem != nullptr)
		{
			menuItem->setVisible(false);
		}
	}
}

void CRoomListLayer::_setSetInfo(int idx, RoomInfo& info)
{
	auto menu = getChildByTag(1);
	if (menu == nullptr)
	{
		return;
	}

	auto menuItem = menu->getChildByTag(idx);
	if (menuItem == nullptr)
	{
		return;
	}
	menuItem->setVisible(true);

	auto frontSprite = menuItem->getChildByTag(1);
	if (frontSprite != nullptr)
	{
		auto label = (Label*)frontSprite->getChildByTag(2);
		if (label != nullptr)
		{
			label->setString(info.strRoomName);
		}
	}

	auto backsprite = menuItem->getChildByTag(2);
	if (backsprite != nullptr)
	{
		auto label = (Label*)backsprite->getChildByTag(2);
		if (label != nullptr)
		{
			label->setString(info.strRoomName);
		}
	}
}

void CRoomListLayer::_updateCell()
{
	_clearSellInfo();

	int nMinBound = _nPage * kRoomCount;
	const int nMaxData = _vecRoomInfos.size();

	for (int i = 0; i < kRoomCount; ++i)
	{
		const int dataIdx = nMinBound + i;
		if (dataIdx >= 0 && dataIdx < nMaxData)
		{
			_setSetInfo(i, _vecRoomInfos[dataIdx]);
		}
	}
}


void CRoomListLayer::_roomSelectCallback(Ref* pSender)
{
	auto menuItem = static_cast<MenuItemSprite*>(pSender);
	if (menuItem != nullptr)
	{
		int nTag = menuItem->getTag();
		int nDataIdx = _nPage * kRoomCount + nTag;
		if (nDataIdx >= 0 && nDataIdx <= _vecRoomInfos.size())
		{
			auto& roomInfo = _vecRoomInfos[nDataIdx];
			if (roomInfo.nRoomId > 0)
			{
				ServerMessage::MessageBase::ReqEnterRoom msgEnterRoom;
				msgEnterRoom.set_nroomid(roomInfo.nRoomId);
				CNetworkThread::GetInstance()->SendPacket(ServerMessage::MessageType::kReqEnterRoom, &msgEnterRoom);
			}

			/*auto director = Director::getInstance();
			auto scene = CTetrisScene::createScene();
			if (director != nullptr && scene != nullptr)
			{
				director->replaceScene(scene);
			}*/
		}
	}
}

void CRoomListLayer::OnRecevieRoomList(ServerMessage::MessageBase::ResRoomList &receivePacket)
{

	const auto currentIdx = receivePacket.currentidx();
	const int nCount = receivePacket.rooms_size();

	_nPage = floor(currentIdx / kRoomCount);

	for (int i = 0; i < kRoomCount; ++i)
	{
		int nIdx = currentIdx + i;
		if (i < nCount && nIdx < kMaxCapacity)
		{

			const ServerMessage::MessageBase::ResRoomList::RoomInfo roomInfo = receivePacket.rooms(i);
			_vecRoomInfos[nIdx].strRoomName = roomInfo.name();
		}
	}

	Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]()->void
	{
		_updateCell();
	});
}