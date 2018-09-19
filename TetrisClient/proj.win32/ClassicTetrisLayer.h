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

	void OnUpdateBlockDown(float dt);
	void DropBlock();
	bool IsDropBlockDeadLine();

private:
	void __UpdateDropBlock();

private:
	CGameBoard* m_pGameBoard = nullptr;
	CBlockProductor m_BlockProductor;
	CNextBlockView* m_nextBlockView;
	CNextBlockView* m_nextBlockView2;
};

