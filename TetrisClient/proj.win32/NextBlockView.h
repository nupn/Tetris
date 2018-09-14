#pragma once
#include "cocos2d.h"
#include "DropBlock.h"
#include "CellBoard.h"
#include "CellBatchSprite.h"

using namespace cocos2d;

class CNextBlockView : public Sprite
{
public:
	enum
	{
		kRow = 4,
		kCol = 4,
	};

public:
	CREATE_FUNC(CNextBlockView);
	CNextBlockView();
	virtual ~CNextBlockView();

	void SetBlock(CBlockBase::BlockType blockType);
	virtual bool init() override;

private:
	CBlockBase blockBase;
	CCellBatchSprite<kRow, kCol>* m_pBatchContainer = nullptr;
	CCellBoard<kRow, kCol> m_cellBoard;
};

