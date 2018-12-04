#include "LoginScene.h"
#include "../proj.win32/LoginInputLayer.h"
#include "NetworkThread.h"
#include "LobbyScene.h"

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

void CLoginScene::Handle(int nMessageType, protobuf::io::CodedInputStream* codedStream)
{
	if (codedStream == nullptr)
	{
		return;
	}

	switch (nMessageType)
	{
	case ServerMessage::MessageType::kResLogin:
	{
		ServerMessage::MessageBase::ResLogin message;
		if (false == message.ParseFromCodedStream(codedStream))
			break;

		if (message.res() > 0)
		{
			Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]()->void
			{
				auto director = Director::getInstance();
				CLobbyScene* scene = static_cast<CLobbyScene*>(CLobbyScene::createScene());

				CNetworkThread::GetInstance()->SetPacketHandler(scene);
				if (director != nullptr && scene != nullptr)
				{
					director->replaceScene(scene);
				}
			});
		}
	}
	break;
	}
}