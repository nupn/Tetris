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

	Vec2 vecOverlap;
	if (!dropBlock.GetOverlap(arrCellFrameBoard, vecOverlap))
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
	if (!dropBlock.IsCollision(arrCellFrameBoard))
	{
		m_DropBlock = dropBlock;
		return;
	}
	
	movePos = blockPos;
	movePos.y -= vecOverlap.y;
	dropBlock.SetPos(movePos);
	if (!dropBlock.IsCollision(arrCellFrameBoard))
	{
		m_DropBlock = dropBlock;
		return;
	}


	/*
	int nRep = dropBlock.IsCollisionToWall();
	//���⿡ �ٴ�üũ, ��üũ ������?
	if (nRep != 0)
	{
	blockPos.x -= nRep;
	dropBlock.SetPos(blockPos);
	}

	//IsCollisionToCell �� CellBoard �Լ��� ����
	if (dropBlock.IsCollisionToCell(arrCellFrameBoard))
	{
	return;
	}
	*/
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

	//���Ը� ��Ʈ���� �غ���?
	//�缱���� ������ ��Ʈ����
	//���⵵ �ٴ�üũ, ��üũ ������?
	if (dropBlock.IsCollisionToWall() == 0 && dropBlock.IsCollisionToCell(arrCellFrameBoard) == false)
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
	//�̹��浹���̶�� ����

	CDropBlock dropBlock(m_DropBlock);
	Vec2 blockPos = dropBlock.GetPos();

	int nHeight = blockPos.y;
	for (int i = 0; i < nHeight; ++i)
	{
		blockPos.y -= 1;
		dropBlock.SetPos(blockPos);
		if (dropBlock.IsCollisionToCell(arrCellFrameBoard))
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

	m_DropBlock = dropBlock;

	m_DropBlock.MarkCell(arrCellFrameBoard);
	CheckLineClear();
	UpdateDropBlock();
}

CCellBoard::DownBlockResult CCellBoard::MoveBlockDown()
{
	CDropBlock dropBlock(m_DropBlock);
	Vec2 blockPos = dropBlock.GetPos();
	blockPos.y -= 1;
	dropBlock.SetPos(blockPos);
	if ((dropBlock.IsCollisionToFloor()) || dropBlock.IsCollisionToCell(arrCellFrameBoard))
	{
		blockPos.y += 1;
		dropBlock.SetPos(blockPos);

		m_DropBlock = dropBlock;

		m_DropBlock.MarkCell(arrCellFrameBoard);
		UpdateDropBlock();

		return CCellBoard::DownBlockResult::Dropped;
	}

	m_DropBlock = dropBlock;
	return CCellBoard::DownBlockResult::Floating;
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

	int nLineClearCnt = 0;
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
				arrCellFrameBoard[idx] = kBlockResourcIdxDefault;
			}

			++nLineClearCnt;
		}
		else
		{
			int nRowToMove = row - nLineClearCnt;
			if (nRowToMove >= 0 && nRowToMove != row)
			{
				for (int col = 0; col < 10; ++col)
				{
					int idx = row * 10 + col;
					int idxTo = nRowToMove * 10 + col;
					arrCellFrameBoard[idxTo] = arrCellFrameBoard[idx];
					arrCellFrameBoard[idx] = kBlockResourcIdxDefault;
				}
			}
		}
	}
}

bool CCellBoard::IsDeadLine()
{
	CDropBlock dropBlock(m_DropBlock);
	Vec2 blockPos = dropBlock.GetPos();
	blockPos.y -= 1;
	dropBlock.SetPos(blockPos);
	if ((dropBlock.IsCollisionToFloor()) || dropBlock.IsCollisionToCell(arrCellFrameBoard))
	{
		return true;
	}

	return false;
}