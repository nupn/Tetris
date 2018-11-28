#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

#include "../proj.win32/PacketHandler.h"
#include "../proj.win32/ChatLayer.h"
#include "../proj.win32/RoomListLayer.h"


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
	void onPrevClick(cocos2d::Ref* pSender);
	void onNextClick(cocos2d::Ref* pSender);
	void menuCloseCallback(cocos2d::Ref* pSender);
	virtual void Handle(int nMessageType, protobuf::io::CodedInputStream* codedStream) override;

private:
	CRoomListLayer* m_pRoomListLayer = nullptr;
	CChatLayer* m_pChatLayer = nullptr;
};

#endif // __HELLOWORLD_SCENE_H__
