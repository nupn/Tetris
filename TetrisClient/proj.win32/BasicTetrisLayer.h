#pragma once
#include "cocos2d.h"
#include "../proj.win32/GameBoard.h"
#include "../proj.win32/BlockProductor.h"
#include "../proj.win32/GameStateFontEffect.h"

class BasicTetrisLayer : public cocos2d::Layer
{
public:
	//일자 넘기기
	//블럭등장후 처음 중력받을때까지 딜레이주기
	//밑으로 넣기 스페이스 시 다음 블록 떨어지는것
	//회전중엔 밑으로 떨어지는건 연기하기
	enum
	{
		kPrepare,
		kReady,
		kPlay,
		kResult,
	};



public:
	BasicTetrisLayer();
	~BasicTetrisLayer();

private:

	CGameBoard* m_pGameBoard = nullptr;

};

