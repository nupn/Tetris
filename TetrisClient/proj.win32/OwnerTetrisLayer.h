#pragma once
#include "cocos2d.h"
#include "../proj.win32/GameBoard.h"
#include "../proj.win32/BlockProductor.h"
#include "../proj.win32/GameStateFontEffect.h"
#include "../proj.win32/BasicTetrisLayer.h"
#include "NextBlockView.h"

class COwnerTetrisLayer  : public cocos2d::Layer
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


	enum
	{
		kGameResultLose = 0,
		kGameResultWin
	};

public:
	CREATE_FUNC(COwnerTetrisLayer);
	COwnerTetrisLayer();
	~COwnerTetrisLayer();

	virtual bool init() override;

	void UpdateDropBlock();
	void UpdateCellTexture();
	void RotateBlockLeft();
	void RotateBlockRight();
	void MoveBlockLeft();
	void MoveBlockRight();
	CGameBoard::DownBlockResult MoveBlockDown();
	
	void OnUpdate(float dt);

	void OnUpdateBlockDown(float dt);
	void DropBlock();
	bool IsDropBlockDeadLine();
	void ResetAllTimer();


	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	

	void OnEffectEnd(int nEndState);

private:
	void __UpdateDropBlock();

private:
	CGameBoard* m_pGameBoard = nullptr;
	CBlockProductor m_BlockProductor;
	CNextBlockView* m_nextBlockView;
	CNextBlockView* m_nextBlockView2;


	int m_nUpdateCnt = 0;
	int m_nUpdateCntTotal = 0;
	int m_nUpdatePerTime = 0;


	bool m_bMovingLeft = false;
	bool m_bMovingRight = false;
	bool m_bMovingDown = false;
	bool m_bMovingDownDeadLine = false;


	int m_nGameState = kPrepare;
	bool m_bChangeGameState = false;
	CGameStateFontEffect* m_pGameResultEffect = nullptr;
};

