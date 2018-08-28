#pragma once
#include "cocos2d.h"
#include "CellBoard.h"

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
	CCellBoard::DownBlockResult MoveBlockDown();
	
	void DropBlock();
	bool IsDropBlockDeadLine();
public:
	cocos2d::SpriteBatchNode* pBatchCellContainer = nullptr;
	CCellBoard m_CellBoard;

private:


};

