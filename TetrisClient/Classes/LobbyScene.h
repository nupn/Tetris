#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

#include "../proj.win32/PacketHandler.h"
#include "..\proj.win32\ClassicTetrisLayer.h"
#include "../proj.win32/ChatLayer.h"


#include <string>

using namespace std;

class CLobbyScene : public cocos2d::Scene, public PacketHandler
{
public:
	CREATE_FUNC(CLobbyScene);
	virtual ~CLobbyScene();
	static cocos2d::Scene* createScene();
	virtual bool init();


	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	virtual void Handle(const ServerMessage::Chat& message) override;

private:
	CClassicTetrisLayer* m_pGameLayer = nullptr;
	CChatLayer* m_pChatLayer = nullptr;
};

#endif // __HELLOWORLD_SCENE_H__
