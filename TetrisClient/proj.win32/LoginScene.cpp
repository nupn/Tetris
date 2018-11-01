#include "LoginScene.h"
#include "../proj.win32/LoginInputLayer.h"


CLoginScene::CLoginScene()
{
}


CLoginScene::~CLoginScene()
{
}


bool CLoginScene::init()
{
	auto wndSize = Director::getInstance()->getWinSize();

	const int nInputX = wndSize.width/2;
	const int nInputY = wndSize.height/2;

	auto inputLayer = CLoginInputLayer::create();
	inputLayer->setPosition(Vec2::Vec2(nInputX, nInputY));
	addChild(inputLayer);

	return Scene::init();
}