#pragma once
#include "cocos2d.h"
#include "DropBlock.h"
#include "CellBoard.h"
#include "CellBatchSprite.h"

class CGameBoard : public cocos2d::Sprite
{
public:
	enum {
		kRow = 20,
		kCol = 10
	};

	friend class CCellBoard<kRow, kCol>;
	enum class DownBlockResult : int
	{
		Floating,
		Dropped,
	};

public:
	CREATE_FUNC(CGameBoard);

	CGameBoard();
	virtual ~CGameBoard();

	virtual bool init() override;
	void UpdateDisplay();
	bool ResetDropBlock(CDropBlock::BlockType nBlockType);
	void RotateDropBlock(bool bCW);
	void MoveBlockSide(int nDir);

	DownBlockResult MoveBlockDown();
	void CheckLineClear();

	int IsCollisionSideWall(CDropBlock* targetBlock);
	int IsCollisionFloor(CDropBlock* targetBlock);
	void DropBlock();

	bool IsDeadLine();

	void OnLineClearEffectEnd(float dt);

private:
	CDropBlock __GetDropBlock();

private:
	int m_nBlockMoveDownRange;
	CDropBlock m_DropBlock;
	//int arrCellFrameBoard[kCellMax] = { 0, };
	
	CCellBoard<kRow, kCol> m_cellBoard;
	CCellBatchSprite<kRow, kCol>* m_pBatchCellContainer = nullptr;

	bool m_bLineClearEffect;
	bool m_bLineClear;
	CCellBoard<kRow, kCol> m_backCellBoard;
	CCellBoard<kRow, kCol> m_effectCellBoard;


	bool m_bNewBlickEffect = false;
	CDropBlock m_newBlockInfo;
};

