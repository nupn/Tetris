#pragma once
#include "cocos2d.h"
#include <functional>



using namespace cocos2d;

class CGameStateFontEffect : public Sprite
{
public:
	enum
	{
		kPrepareHost,
		kPrepare,
		kPause,

		kReady,

		kPlay,
		kDead,
		kWait,

		kResultWin,
		kResultLose,
		kResultNone,
	};

public:
	CREATE_FUNC(CGameStateFontEffect);
	CGameStateFontEffect();
	~CGameStateFontEffect();

	void SetState(int state);
	void PlayEffect();
	void PlayEffect(std::function<void(int)> func);
	void Clear();

	std::function<void(int)> m_callBack = nullptr;
	int	m_nState;
};

