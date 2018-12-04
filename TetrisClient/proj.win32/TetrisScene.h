#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

#include "../proj.win32/PacketHandler.h"
#include "..\proj.win32\OwnerTetrisLayer.h"
#include "..\proj.win32\RemoteTetrisLayer.h"
#include "../proj.win32/ChatLayer.h"


#include <string>

using namespace std;

class CTetrisScene : public cocos2d::Scene, public PacketHandler
{
public:
	enum
	{
		kRemoteSlotCount = 5
	};

public:
	CREATE_FUNC(CTetrisScene);
	virtual ~CTetrisScene();
	static cocos2d::Scene* createScene();
	virtual bool init();


	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	void onGameEventCallback(CDropBlock nEventIdx);
	void onGameEventCallback2(CDropBlock::BlockType nIdx);

	virtual void Handle(int nMessageType, protobuf::io::CodedInputStream* codedStream) override;

private:
	CRemoteTetrisLayer* m_pRemoteLayer[kRemoteSlotCount] = { nullptr ,};
	COwnerTetrisLayer* m_pGameLayer = nullptr;
	CChatLayer* m_pChatLayer = nullptr;
};

#endif // __HELLOWORLD_SCENE_H__
