#include "NextBlockView.h"



CNextBlockView::CNextBlockView()
{
}


CNextBlockView::~CNextBlockView()
{
}

bool CNextBlockView::init()
{
	m_pBatchContainer = CCellBatchSprite<kRow, kCol>::create2("Tetris/source.png");
	addChild(m_pBatchContainer);

	return Sprite::init();
}

void CNextBlockView::SetBlock(CBlockBase::BlockType blockType)
{
	if (m_pBatchContainer == nullptr)
	{
		return;
	}

	blockBase.UndrawCell(&m_cellBoard);
	blockBase.Reset(Vec2(0,0), blockType);
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