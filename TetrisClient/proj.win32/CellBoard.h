#pragma once
#include "cocos2d.h"
#include "DropBlock.h"

class CCellBoard
{
public:
	enum {
		kCellMax = 200,
		kBlockResourcIdxDefault = 7,
		kBlockResourcIdxMax = 8,
	};

public:
	CCellBoard();
	virtual ~CCellBoard();

	void OnDraw(cocos2d::SpriteBatchNode* container);
	void UpdateDropBlock();
	void RotateDropBlock(bool bCW);
	void MoveBlockSide(int nDir);
	void MoveBlockDown();
	int IsCollisionSideWall(CDropBlock* targetBlock);
	int IsCollisionFloor(CDropBlock* targetBlock);
	void DropBlock();

private:
	CDropBlock m_DropBlock;
	int arrCellFrameBoard[kCellMax] = { 0, };

};

