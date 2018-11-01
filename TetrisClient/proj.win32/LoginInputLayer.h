#pragma once
#include "cocos2d.h"
#include "../proj.win32/KeyboardNotificationLayer.h"

using namespace cocos2d;

class CLoginInputLayer : public Layer , public InputText
{
public:
	CREATE_FUNC(CLoginInputLayer);
	CLoginInputLayer();
	virtual ~CLoginInputLayer();


	virtual bool init() override;
	void onMenuSelectCallback(Ref* pSender);
};

