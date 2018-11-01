#include "LoginInputLayer.h"
#include "LobbyScene.h"
#include "TextFieldKR.h"


CLoginInputLayer::CLoginInputLayer()
{
}


CLoginInputLayer::~CLoginInputLayer()
{
}


bool CLoginInputLayer::init()
{
	const int nInputWidth = 200;
	const int nInputHeight = 38;

	const int nPosX = - nInputWidth / 2;


	const int RedDotImgSize = 12;

	auto pBackGround = Sprite::create("PosPoint.png");
	pBackGround->setAnchorPoint(Vec2::ZERO);
	pBackGround->setScaleX(nInputWidth / RedDotImgSize);
	pBackGround->setScaleY(nInputHeight / RedDotImgSize);
	pBackGround->setPosition(Vec2::Vec2(nPosX, 0));
	this->addChild(pBackGround);

	auto inputText = TextFieldKR::textFieldWithPlaceHolder("Input PlayerName", Size(nInputWidth, nInputHeight), TextHAlignment::LEFT, "fonts/malgun.ttf", 32);
	inputText->setTag(123);
	inputText->setAnchorPoint(Vec2::ZERO);
	inputText->setPosition(Vec2::Vec2(nPosX, 0));
	inputText->setMaxLineWidth(0);
	inputText->setInputMax(6);
	this->addChild(inputText);
	AddTrackNode(inputText);

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(InputText::onTouchBegan, static_cast<InputText*>(this));
	listener->onTouchEnded = CC_CALLBACK_2(InputText::onTouchEnded, static_cast<InputText*>(this));
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(CLoginInputLayer::onMenuSelectCallback, this));

	closeItem->setPosition(0, -30);
	closeItem->setAnchorPoint(Vec2::Vec2(0.5f, 0.5f));

	auto pMenu = Menu::create(closeItem, NULL);
	pMenu->setPosition(Vec2::ZERO);
	addChild(pMenu, 1);

	return Layer::init();
}

void CLoginInputLayer::onMenuSelectCallback(Ref* pSender)
{
	auto director = Director::getInstance();
	auto scene = CLobbyScene::createScene();
	if (director != nullptr && scene != nullptr)
	{
		director->replaceScene(scene);
	}
}
