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

	enum class DownBlockResult : int
	{
		Floating,
		Dropped,
	};

public:
	CCellBoard();
	virtual ~CCellBoard();

	void OnDraw(cocos2d::SpriteBatchNode* container);
	void UpdateDropBlock();
	void RotateDropBlock(bool bCW);
	void MoveBlockSide(int nDir);

	DownBlockResult MoveBlockDown();
	void CheckLineClear();

	int IsCollisionSideWall(CDropBlock* targetBlock);
	int IsCollisionFloor(CDropBlock* targetBlock);
	void DropBlock();

	bool IsDeadLine();

private:
	CDropBlock m_DropBlock;
	int arrCellFrameBoard[kCellMax] = { 0, };

};

