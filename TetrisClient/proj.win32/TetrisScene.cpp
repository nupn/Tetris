#include "TetrisScene.h"
#include "SimpleAudioEngine.h"
#include "TextFieldKR.h"
#include "NetworkThread.h"


CTetrisScene::~CTetrisScene()
{
}

Scene* CTetrisScene::createScene()
{
	return CTetrisScene::create();
}


static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool CTetrisScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}


	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(CTetrisScene::menuCloseCallback, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0)
	{
		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
		float y = origin.y + closeItem->getContentSize().height / 2;
		closeItem->setPosition(Vec2(x, y));
	}

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);


	stChatLayerSetting setting;
	setting.nWidth = 200;
	setting.nHeight = 300;
	setting.nFontSize = 24;

	m_pChatLayer = CChatLayer::create(setting);
	m_pChatLayer->setPosition(Vec2::Vec2(962, 70));
	addChild(m_pChatLayer);

	/*
	auto pTextField = TextFieldTTF::textFieldWithPlaceHolder("<click here for input>",
	"fonts/arial.ttf",
	36);
	pTextField->setPosition(500, 100);
	addChild(pTextField);
	//*/


	//auto pInputText = new InputText;
	//pInputText->setPosition(100, 100);
	//this->addChild(pInputText);
	//pInputText->_trackNode = pTextField;
	for (int i = 0; i < kRemoteSlotCount; ++i)
	{
		m_pRemoteLayer[i] = CRemoteTetrisLayer::create();
		m_pRemoteLayer[i]->setPosition(50 + (i % 3) * 140, 410 - floor(i/3) * 260);
		addChild(m_pRemoteLayer[i]);

	}

	


	COwnerTetrisLayer* pgameLayer = COwnerTetrisLayer::create();
	pgameLayer->setPosition(600, 150);
	pgameLayer->SetEventCallback(std::bind(&CTetrisScene::onGameEventCallback, this, std::placeholders::_1));
	pgameLayer->SetEventCallback2(std::bind(&CTetrisScene::onGameEventCallback2, this, std::placeholders::_1));
	addChild(pgameLayer);
	pgameLayer->UpdateCellTexture();

	m_pGameLayer = pgameLayer;


	return true;
}


void CTetrisScene::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void CTetrisScene::Handle(int nMessageType, protobuf::io::CodedInputStream* codedStream)
{
	if (!m_pChatLayer)
	{
		return;
	}

	Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]()->void
	{
		//m_pChatLayer->PushMessage(message.message());

	});
}

void CTetrisScene::onGameEventCallback(CDropBlock dropBlock)
{
	for (int i = 0; i < kRemoteSlotCount; ++i)
	{
		if (m_pRemoteLayer[i] != nullptr)
		{
			m_pRemoteLayer[i]->OnBlinkBlock(dropBlock);
		}
	}
}

void CTetrisScene::onGameEventCallback2(CDropBlock::BlockType nType)
{
	for (int i = 0; i < kRemoteSlotCount; ++i)
	{
		if (m_pRemoteLayer[i] != nullptr)
		{
			m_pRemoteLayer[i]->OnCreateBlock(nType);
		}
	}
}