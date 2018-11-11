#include "NextBlockView.h"



CNextBlockView::CNextBlockView()
{
}


CNextBlockView::~CNextBlockView()
{
}

bool CNextBlockView::init()
{
	m_pBatchContainer = CCellBatchSprite<kRow, kCol>::create2("Tetris/source.png", 23);
	addChild(m_pBatchContainer);

	return Sprite::init();
}

void CNextBlockView::SetBlock(CBlockBase::BlockType blockType)
{
	if (m_pBatchContainer == nullptr)
	{
		return;
	}

	if (blockType < 0 || blockType >= CBlockBase::BlockType::kBlockTypeMax)
	{
		return;
	}

	auto prevType = blockBase.GetBlockType();
	if (prevType >= 0 && prevType < CBlockBase::BlockType::kBlockTypeMax)
	{
		blockBase.UndrawCell(&m_cellBoard);
	}

	blockBase.Reset(Vec2(1,3), blockType);
	blockBase.DrawCell(&m_cellBoard);

	Sprite* pSprite;
	for (int row = 0; row < kRow; ++row)
	{
		for (int col = 0; col < kCol; ++col)
		{
			int nState = m_cellBoard.Get(row, col);
			m_pBatchContainer->UpdateCell(row, col, nState);
		}
	}
}