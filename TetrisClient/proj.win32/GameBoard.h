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
	static CGameBoard* create(const char* filename, const int nCellSize) 
	{
		CGameBoard *pRet = new(std::nothrow) CGameBoard(); 
		if (pRet && pRet->init(filename, nCellSize))
		{ 
			pRet->autorelease();
			return pRet;
		}
		else
		{
			delete pRet;
			pRet = nullptr;
			return nullptr;
		}
	}


	CGameBoard();
	virtual ~CGameBoard();

	bool init(const char* filename, const int nCellSize);
	void UpdateDisplay();
	bool ResetDropBlock(CDropBlock::BlockType nBlockType);
	void RotateDropBlock(bool bCW);
	void MoveBlockSide(int nDir);

	//DownBlockResult MoveBlockDown();
	void CheckLineClear();

	int IsCollisionSideWall(CDropBlock* targetBlock);
	int IsCollisionFloor(CDropBlock* targetBlock);

	bool DropBlock(int nDepth, CDropBlock& outRetBlock);
	bool IsDeadLine();

	void OnLineClearEffectEnd(float dt);

	bool BlinkBlock(CDropBlock targetBlock);
	void SetShadowBlockVisible(bool bBisible);

	CDropBlock::BlockType GetDropBlockType();

private:
	int _MoveBlockDown(int nDepth, CDropBlock& outRetBlock);
	//CDropBlock __GetDropBlock();

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
	bool m_bShowShadowBlock = true;
	CDropBlock m_newBlockInfo;
};

