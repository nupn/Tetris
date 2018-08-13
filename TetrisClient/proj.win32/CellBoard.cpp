#include "CellBoard.h"

using namespace cocos2d;

cocos2d::Rect imgRect[CCellBoard::kBlockResourcIdxMax] = {
	cocos2d::Rect(0, 0, 23, 23),
	cocos2d::Rect(23, 0, 23, 23),
	cocos2d::Rect(0, 23, 23, 23),
	cocos2d::Rect(23, 23, 23, 23),
	cocos2d::Rect(0, 46, 23, 23),
	cocos2d::Rect(23, 46, 23, 23),
	cocos2d::Rect(0, 69, 23, 23),
	cocos2d::Rect(23, 69, 23, 23)
};

CCellBoard::CCellBoard()
{
	for (int i = 0; i < kCellMax; ++i)
	{
		arrCellFrameBoard[i] = kBlockResourcIdxDefault;
	}

}


CCellBoard::~CCellBoard()
{
}


void CCellBoard::UpdateDropBlock()
{
	int nIdx = rand() % static_cast<int>(CDropBlock::BlockType::kBlockTypeMax);
	m_DropBlock.Reset(cocos2d::Vec2(4, 19), static_cast<CDropBlock::BlockType>(nIdx));
}

void CCellBoard::RotateDropBlock(bool bCW)
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

	int nRep = dropBlock.IsCollisionToWall();
	//여기에 바닥체크, 블럭체크 들어가야지?
	if (nRep != 0)
	{
		blockPos.x -= nRep;
		dropBlock.SetPos(blockPos);
	}

	m_DropBlock = dropBlock;
}


void CCellBoard::OnDraw(cocos2d::SpriteBatchNode* container)
{
	m_DropBlock.DrawCell(arrCellFrameBoard);


	Sprite* pSprite;
	int posY = 23 * 20;
	int idx = 0, row = 0, col = 0;
	//for (int i = 0; i < kCellMax; ++i)

	for (int nCellState : arrCellFrameBoard)
	{
		col = idx % 10;
		row = floor(idx / 10);
		{
			pSprite = Sprite::createWithTexture(container->getTexture(), imgRect[nCellState]);
			pSprite->setPosition(Vec2(col * 23, posY + (row * 23)));
			container->addChild(pSprite);
		}
		++idx;
	}

	m_DropBlock.UndrawCell(arrCellFrameBoard);
}

void CCellBoard::MoveBlockSide(int nDir)
{
	CDropBlock dropBlock(m_DropBlock);
	Vec2 blockPos = dropBlock.GetPos();
	blockPos.x += nDir;
	dropBlock.SetPos(blockPos);

	//벽뚤린 테트리스 해볼까?
	//사선으로 날리는 테트리스
	//여기도 바닥체크, 블럭체크 들어가야지?
	if (dropBlock.IsCollisionToWall() == 0)
	{
		blockPos.x += nDir;
		m_DropBlock = dropBlock;
	}

}


/*
Rotate

CDropBlock dropBlock(m_DropBlock);
Vec2 blockPos = dropBlock.GetPos();
blockPos.x  += nDir;
dropBlock.SetPos(blockPos);

while ((IsCollisionSideWall(&dropBlock) > 0) != (nDir > 0))
{
blockPos.x += nDir;
}

*/
int CCellBoard::IsCollisionSideWall(CDropBlock* targetBlock)
{
	return 0;
}

int CCellBoard::IsCollisionFloor(CDropBlock* targetBlock)
{
	return 0;

}

void CCellBoard::DropBlock()
{
	//이미충돌주이라면 리턴

	CDropBlock dropBlock(m_DropBlock);
	Vec2 blockPos = dropBlock.GetPos();

	int nHeight = blockPos.y;
	for (int i = 0; i < nHeight; ++i)
	{
		blockPos.y -= 1;
		dropBlock.SetPos(blockPos);
		if (dropBlock.IsCollisionToFloor() != 0)
		{
			blockPos.y += 1;
			dropBlock.SetPos(blockPos);
			break;
		}
		else if (dropBlock.IsCollisionToCell(arrCellFrameBoard) != 0)
		{
			blockPos.y += 1;
			dropBlock.SetPos(blockPos);
			break;
		}
	}

	m_DropBlock = dropBlock;

	m_DropBlock.MarkCell(arrCellFrameBoard);
	UpdateDropBlock();
}

void CCellBoard::MoveBlockDown()
{
	CDropBlock dropBlock(m_DropBlock);
	Vec2 blockPos = dropBlock.GetPos();
	blockPos.y -= 1;
	dropBlock.SetPos(blockPos);
	if ((dropBlock.IsCollisionToFloor() != 0) || (dropBlock.IsCollisionToCell(arrCellFrameBoard) != 0))
	{
		blockPos.y += 1;
		dropBlock.SetPos(blockPos);

		m_DropBlock = dropBlock;

		m_DropBlock.MarkCell(arrCellFrameBoard);
		UpdateDropBlock();
	}
	else
	{
		m_DropBlock = dropBlock;
	}	
}

void CCellBoard::CheckLineClear()
{
	Sprite* pSprite;
	int posY = 23 * 20;
	int idx = 0, row = 0, col = 0;
	for (int i = 0; i < kCellMax; ++i)
	{
		col = i % 10;
		row = floor(i / 10);

	}

	for (int row = 0; row < 20; ++row)
	{
		bool bCheckCompleteLine = true;
		for (int col = 0; col < 10; ++col)
		{
			int idx = row * 10 + col;
			if (arrCellFrameBoard[idx] == kBlockResourcIdxDefault)
			{
				bCheckCompleteLine = false;
			}
		}

		if (bCheckCompleteLine)
		{
			for (int col = 0; col < 10; ++col)
			{
				int idx = row * 10 + col;
				if (arrCellFrameBoard[idx] == kBlockResourcIdxDefault)
				{
					bCheckCompleteLine = false;
				}
			}
		}
	}
}