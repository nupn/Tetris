#include "GameBoard.h"
#include "Constants.h"

using namespace cocos2d;

CGameBoard::CGameBoard()
	:m_nBlockMoveDownRange(1)
{
}


CGameBoard::~CGameBoard()
{
}


bool CGameBoard::init()
{
	m_pBatchCellContainer = CCellBatchSprite<kRow, kCol>::create2("Tetris/source.png");
	addChild(m_pBatchCellContainer);

	return Sprite::init();
}

void CGameBoard::ResetDropBlock(CDropBlock::BlockType nBlockType)
{
	m_DropBlock.Reset(cocos2d::Vec2(4, 19), nBlockType);
	m_nBlockMoveDownRange = 1;
}

void CGameBoard::RotateDropBlock(bool bCW)
{
	CDropBlock dropBlock(m_DropBlock);
	Vec2 blockPos = dropBlock.GetPos();
	if (bCW)
	{
		dropBlock.RotateCW();
	}
	else
	{
		dropBlock.RotateCCW();
	}

	Vec2 vecOverlap;
	if (!dropBlock.GetOverlap(m_cellBoard, vecOverlap))
	{
		return;
	}

	if (vecOverlap.x > 0 && vecOverlap.y > 0)
	{
		return;
	}

	Vec2 movePos = blockPos;
	movePos.x += vecOverlap.x;
	dropBlock.SetPos(movePos);
	if (!dropBlock.IsCollision(m_cellBoard))
	{
		m_DropBlock = dropBlock;
		return;
	}

	movePos = blockPos;
	movePos.y -= vecOverlap.y;
	dropBlock.SetPos(movePos);
	if (!dropBlock.IsCollision(m_cellBoard))
	{
		m_nBlockMoveDownRange = 1 - vecOverlap.y;
		m_DropBlock = dropBlock;
		return;
	}
}


void CGameBoard::UpdateDisplay()
{
	if (!m_pBatchCellContainer)
	{
		return;
	}

	//현재블럭
	if (m_bLineClearEffect)
	{
		m_pBatchCellContainer->DrawCellBoard(m_backCellBoard);
		m_pBatchCellContainer->DrawCellBoardEffect(m_effectCellBoard);

		CCDirector::sharedDirector()->getScheduler()->unschedule(CC_SCHEDULE_SELECTOR(CGameBoard::OnLineClearEffectEnd), this);
		CCDirector::sharedDirector()->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(CGameBoard::OnLineClearEffectEnd), this, 0.1f, false);
	}
	else
	{
		m_pBatchCellContainer->DrawCellBoard(m_cellBoard);
	}
	
	int nType = m_DropBlock.GetBlockType();
	int nState = m_DropBlock.GetBlockState();
	auto nPos = m_DropBlock.GetPos();
	for (auto blockInfo : GetBlockShapes(nType, nState))
	{
		int cellCol = nPos.x + blockInfo.x;
		int cellRow = nPos.y - blockInfo.y;
		m_pBatchCellContainer->UpdateCell(cellRow, cellCol, nType);
	}

	//쉐도우 블럭 그리기
	if (!m_bLineClearEffect)
	{
		CDropBlock dropBlock = __GetDropBlock();

		nType = dropBlock.GetBlockType();
		nState = dropBlock.GetBlockState();
		nPos = dropBlock.GetPos();
		for (auto blockInfo : GetBlockShapes(nType, nState))
		{
			int cellCol = nPos.x + blockInfo.x;
			int cellRow = nPos.y - blockInfo.y;
			m_pBatchCellContainer->UpdateCell(cellRow, cellCol, nType);
			m_pBatchCellContainer->UpdateCellEffect(cellRow, cellCol, kBlockEffectAlpha);
		}
	}

	if (m_bLineClearEffect || m_bLineClear)
	{
		m_bLineClearEffect = false;
		m_bNewBlickEffect = false;
		m_bLineClear = false;
	}
	else if (m_bNewBlickEffect)
	{
		nType = m_newBlockInfo.GetBlockType();
		nState = m_newBlockInfo.GetBlockState();
		nPos = m_newBlockInfo.GetPos();
		for (auto blockInfo : GetBlockShapes(nType, nState))
		{
			int cellCol = nPos.x + blockInfo.x;
			int cellRow = nPos.y - blockInfo.y;
			m_pBatchCellContainer->UpdateCell(cellRow, cellCol, nType);
			m_pBatchCellContainer->UpdateCellEffect(cellRow, cellCol, kBlockEffectTint);
		}

		m_bNewBlickEffect = false;
	}

	

		/*
	//현재 블럭 그리기
	m_DropBlock.DrawCell(&m_cellBoard);
	
	//일반블럭 그리기
	for (int row = 0; row < kRow; ++row)
	{
		for (int col = 0; col < kCol; ++col)
		{
			int nState = m_cellBoard.Get(row, col);
			m_pBatchCellContainer->UpdateCell(row, col, nState);
		}
	}

	//쉐도우 블럭 그리기
	
	CDropBlock dropBlock = __GetDropBlock();
	dropBlock.DrawCell(&m_cellBoard);


	dropBlock.UndrawCell(&m_cellBoard);
	m_DropBlock.UndrawCell(&m_cellBoard);
	*/
}

void CGameBoard::MoveBlockSide(int nDir)
{
	CDropBlock dropBlock(m_DropBlock);
	Vec2 blockPos = dropBlock.GetPos();
	blockPos.x += nDir;
	dropBlock.SetPos(blockPos);

	//벽뚤린 테트리스 해볼까?
	//사선으로 날리는 테트리스
	//여기도 바닥체크, 블럭체크 들어가야지?
	if (dropBlock.IsCollisionToWall() == 0 && dropBlock.IsCollisionToCell(m_cellBoard) == false)
	{
		blockPos.x += nDir;
		m_DropBlock = dropBlock;
	}

}

int CGameBoard::IsCollisionSideWall(CDropBlock* targetBlock)
{
	return 0;
}

int CGameBoard::IsCollisionFloor(CDropBlock* targetBlock)
{
	return 0;

}

void CGameBoard::DropBlock()
{
	//이미충돌주이라면 리턴
	m_DropBlock = __GetDropBlock();
	m_DropBlock.DrawCell(&m_cellBoard);


	m_bNewBlickEffect = true;
	m_newBlockInfo = m_DropBlock;

}

CDropBlock CGameBoard::__GetDropBlock()
{
	CDropBlock dropBlock(m_DropBlock);
	Vec2 blockPos = dropBlock.GetPos();

	int nHeight = blockPos.y;
	for (int i = 0; i < nHeight; ++i)
	{
		blockPos.y -= 1;
		dropBlock.SetPos(blockPos);
		if (dropBlock.IsCollisionToCell(m_cellBoard))
		{
			blockPos.y += 1;
			dropBlock.SetPos(blockPos);
			break;
		}
		if (dropBlock.IsCollisionToFloor())
		{
			blockPos.y += 1;
			dropBlock.SetPos(blockPos);
			break;
		}
	}

	return dropBlock;
}

CGameBoard::DownBlockResult CGameBoard::MoveBlockDown()
{
	CDropBlock dropBlock(m_DropBlock);
	Vec2 blockPos = dropBlock.GetPos();
	for (int i = 0; i < m_nBlockMoveDownRange; ++i)
	{
		blockPos.y -= 1;
		dropBlock.SetPos(blockPos);
		if ((dropBlock.IsCollisionToFloor()) || dropBlock.IsCollisionToCell(m_cellBoard))
		{
			blockPos.y += 1;
			dropBlock.SetPos(blockPos);

			m_DropBlock = dropBlock;

			m_DropBlock.DrawCell(&m_cellBoard);
			
			//m_bNewBlickEffect = true;
			//m_newBlockInfo = m_DropBlock;

			return CGameBoard::DownBlockResult::Dropped;
		}
	}

	m_DropBlock = dropBlock;
	return CGameBoard::DownBlockResult::Floating;
}

void CGameBoard::CheckLineClear()
{
	int posY = 23 * 20;
	int idx = 0, row = 0, col = 0;

	m_backCellBoard = m_cellBoard;
	m_effectCellBoard.Reset(0);

	int nLineClearCnt = 0;
	for (int row = 0; row < kRow; ++row)
	{
		bool bCheckCompleteLine = true;
		for (int col = 0; col < kCol; ++col)
		{
			if (m_cellBoard.Get(row, col) == kBlockResourcIdxDefault)
			{
				bCheckCompleteLine = false;
			}
		}

		if (bCheckCompleteLine)
		{
			for (int col = 0; col < kCol; ++col)
			{
				m_cellBoard.Set(row, col, kBlockResourcIdxDefault);
			}

			for (int col = 0; col < kCol; ++col)
			{
				m_effectCellBoard.Set(row, col, kBlockEffectTint);
			}

			++nLineClearCnt;
		}
		else
		{
			int nRowToMove = row - nLineClearCnt;
			if (nRowToMove >= 0 && nRowToMove != row)
			{
				for (int col = 0; col < kCol; ++col)
				{
					m_cellBoard.Set(nRowToMove, col, m_cellBoard.Get(row, col));
					m_cellBoard.Set(row, col, kBlockResourcIdxDefault);
				}
			}
		}
	}

	if (nLineClearCnt >= 3)
	{
		m_bLineClearEffect = true;
	}
	else
	{
		m_bLineClearEffect = false;
	}

	if (nLineClearCnt >= 0)
	{
		m_bLineClear = true;
	}
	else
	{
		m_bLineClear = false;
	}
}

bool CGameBoard::IsDeadLine()
{
	CDropBlock dropBlock(m_DropBlock);
	Vec2 blockPos = dropBlock.GetPos();
	blockPos.y -= 1;
	dropBlock.SetPos(blockPos);
	if ((dropBlock.IsCollisionToFloor()) || dropBlock.IsCollisionToCell(m_cellBoard))
	{
		return true;
	}

	return false;
}

void CGameBoard::OnLineClearEffectEnd(float dt)
{
	CCDirector::sharedDirector()->getScheduler()->unschedule(CC_SCHEDULE_SELECTOR(CGameBoard::OnLineClearEffectEnd), this);
	UpdateDisplay();
}