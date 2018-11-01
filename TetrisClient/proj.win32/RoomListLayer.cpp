#include "RoomListLayer.h"



CRoomListLayer::CRoomListLayer()
{
}


CRoomListLayer::~CRoomListLayer()
{
}


bool CRoomListLayer::init()
{
	_vecRoomInfos.clear();
	_vecRoomInfos.resize(24);
	for (int i = 0; i < 24; ++i)
	{
		char roomName[256];
		sprintf(roomName, "RoomName %d", i);
		_vecRoomInfos[i].strRoomName = roomName;
	}

	_initCell();
	_clearSellInfo();
	for (int i = 2; i < 7; ++i)
	{
		_setSetInfo(i, _vecRoomInfos[i]);
	}

	return Layer::init();
}

void CRoomListLayer::menuSelectCallback(Ref* pSender)
{
}

void CRoomListLayer::NextPage()
{

}


void CRoomListLayer::PrevPage()
{

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

		auto meunItem = MenuItemSprite::create(spriteFront, spriteBack, CC_CALLBACK_1(CRoomListLayer::menuSelectCallback, this));
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