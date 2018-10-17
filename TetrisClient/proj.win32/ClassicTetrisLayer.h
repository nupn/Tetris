#pragma once
#include "cocos2d.h"
#include "../proj.win32/GameBoard.h"
#include "../proj.win32/BlockProductor.h"
#include "NextBlockView.h"

class CClassicTetrisLayer  : public cocos2d::Layer
{
public:
	CREATE_FUNC(CClassicTetrisLayer);
	CClassicTetrisLayer();
	~CClassicTetrisLayer();

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
};

