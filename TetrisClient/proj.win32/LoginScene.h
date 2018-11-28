#pragma once
#include "cocos2d.h"
#include "../proj.win32/PacketHandler.h"

using namespace cocos2d;

class CLoginScene : public Scene, public PacketHandler
{
public:
	static cocos2d::Scene* createScene()
	{
		return CLoginScene::create();
	}


	CREATE_FUNC(CLoginScene);
	CLoginScene();
	virtual ~CLoginScene();
	virtual bool init();


	virtual void Handle(int nMessageType, protobuf::io::CodedInputStream* codedStream) override;
};

