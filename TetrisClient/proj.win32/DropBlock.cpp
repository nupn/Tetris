#include "DropBlock.h"
#include "cocos2d.h"
#include <vector>

using namespace cocos2d;


//static Vec2 nShapeToBlock[7][4] = {
static std::vector<Vec2> nShapeToBlock[7][4] = {
{
	//작대기
	{ Vec2::Vec2(1,0), Vec2::Vec2(1,1), Vec2::Vec2(1,2), Vec2::Vec2(1,3) },
	{ Vec2::Vec2(0,2), Vec2::Vec2(1,2), Vec2::Vec2(2,2), Vec2::Vec2(3,2) },
	{ Vec2::Vec2(1,0), Vec2::Vec2(1,1), Vec2::Vec2(1,2), Vec2::Vec2(1,3) },
	{ Vec2::Vec2(0,2), Vec2::Vec2(1,2), Vec2::Vec2(2,2), Vec2::Vec2(3,2) }
},
{
//ㅗ
	{ Vec2::Vec2(1, 1), Vec2::Vec2(0, 2), Vec2::Vec2(1, 2), Vec2::Vec2(2, 2) },
	{ Vec2::Vec2(1,1), Vec2::Vec2(1,2), Vec2::Vec2(2,2), Vec2::Vec2(1,3) },
	{ Vec2::Vec2(0,2), Vec2::Vec2(1,2), Vec2::Vec2(2,2), Vec2::Vec2(1,3) },
	{ Vec2::Vec2(1,1), Vec2::Vec2(0,2), Vec2::Vec2(1,2), Vec2::Vec2(1,3) }
},
{
	//네모
	{ Vec2::Vec2(0,1), Vec2::Vec2(1,1), Vec2::Vec2(0,2), Vec2::Vec2(1,2) },
	{ Vec2::Vec2(0,1), Vec2::Vec2(1,1), Vec2::Vec2(0,2), Vec2::Vec2(1,2) },
	{ Vec2::Vec2(0,1), Vec2::Vec2(1,1), Vec2::Vec2(0,2), Vec2::Vec2(1,2) },
	{ Vec2::Vec2(0,1), Vec2::Vec2(1,1), Vec2::Vec2(0,2), Vec2::Vec2(1,2) }
},
{
	//오른쪽 슬라이드
	{ Vec2::Vec2(0,1), Vec2::Vec2(1,1), Vec2::Vec2(1,2), Vec2::Vec2(2,2) },
	{ Vec2::Vec2(2,1), Vec2::Vec2(2,2), Vec2::Vec2(1,2), Vec2::Vec2(1,3) },
	{ Vec2::Vec2(0,1), Vec2::Vec2(1,1), Vec2::Vec2(1,2), Vec2::Vec2(2,2) },
	{ Vec2::Vec2(2,1), Vec2::Vec2(2,2), Vec2::Vec2(1,2), Vec2::Vec2(1,3) }
},
{
	//왼쪽 슬라이드
	{ Vec2::Vec2(0,2), Vec2::Vec2(1,2), Vec2::Vec2(1,1), Vec2::Vec2(2,1) },
	{ Vec2::Vec2(0,1), Vec2::Vec2(0,2), Vec2::Vec2(1,2), Vec2::Vec2(1,3) },
	{ Vec2::Vec2(0,2), Vec2::Vec2(1,2), Vec2::Vec2(1,1), Vec2::Vec2(2,1) },
	{ Vec2::Vec2(0,1), Vec2::Vec2(0,2), Vec2::Vec2(1,2), Vec2::Vec2(1,3) }
},
{
	//ㄴ
	{ Vec2::Vec2(0,1), Vec2::Vec2(0,2), Vec2::Vec2(1,2), Vec2::Vec2(2,2) },
	{ Vec2::Vec2(2,1), Vec2::Vec2(1,1), Vec2::Vec2(1,2), Vec2::Vec2(1,3) },
	{ Vec2::Vec2(0,2), Vec2::Vec2(1,2), Vec2::Vec2(2,2), Vec2::Vec2(2,3) },
	{ Vec2::Vec2(1,1), Vec2::Vec2(1,2), Vec2::Vec2(1,3), Vec2::Vec2(0,3) }
},
{
	//역ㄴ
	{ Vec2::Vec2(0,2), Vec2::Vec2(1,2), Vec2::Vec2(2,2), Vec2::Vec2(2,1) },
	{ Vec2::Vec2(1,1), Vec2::Vec2(1,2), Vec2::Vec2(1,3), Vec2::Vec2(2,3) },
	{ Vec2::Vec2(0,3), Vec2::Vec2(0,2), Vec2::Vec2(1,2), Vec2::Vec2(2,2) },
	{ Vec2::Vec2(0,1), Vec2::Vec2(1,1), Vec2::Vec2(1,2), Vec2::Vec2(1,3) }
}
};



static Vec2 BlockCore[7] = {
	Vec2::Vec2(1,2), //작대기
	Vec2::Vec2(1, 2), // ㅗ
	Vec2::Vec2(0,1), //네모
	Vec2::Vec2(1,2), //오른쪾 슬라이드
	Vec2::Vec2(1,2), // 왼쪽 슬라이드
	Vec2::Vec2(1,2), //ㄴ
	Vec2::Vec2(1,2) //역 ㄴ
};


/*
//작대기
nShapeToBlock[0][0] = { Vec2::Vec2(1,0), Vec2::Vec2(1,1), Vec2::Vec2(1,2), Vec2::Vec2(1,3) };
nShapeToBlock[0][1] = { Vec2::Vec2(0,2), Vec2::Vec2(1,2), Vec2::Vec2(2,2), Vec2::Vec2(3,2) };
nShapeToBlock[0][3] = { Vec2::Vec2(1,0), Vec2::Vec2(1,1), Vec2::Vec2(1,2), Vec2::Vec2(1,3) };
nShapeToBlock[0][4] = { Vec2::Vec2(0,2), Vec2::Vec2(1,2), Vec2::Vec2(2,2), Vec2::Vec2(3,2) };

//ㅗ
nShapeToBlock[1][0] = { Vec2::Vec2(1,1), Vec2::Vec2(0,2), Vec2::Vec2(1,2), Vec2::Vec2(2,2) };
nShapeToBlock[1][1] = { Vec2::Vec2(1,1), Vec2::Vec2(1,2), Vec2::Vec2(2,2), Vec2::Vec2(1,3) };
nShapeToBlock[1][3] = { Vec2::Vec2(0,2), Vec2::Vec2(1,2), Vec2::Vec2(2,2), Vec2::Vec2(1,3) };
nShapeToBlock[1][4] = { Vec2::Vec2(1,1), Vec2::Vec2(0,2), Vec2::Vec2(1,2), Vec2::Vec2(1,3) };

//네모
nShapeToBlock[2][0] = { Vec2::Vec2(1,1), Vec2::Vec2(2,2), Vec2::Vec2(1,2), Vec2::Vec2(2,2) };
nShapeToBlock[2][1] = { Vec2::Vec2(1,1), Vec2::Vec2(2,2), Vec2::Vec2(1,2), Vec2::Vec2(2,2) };
nShapeToBlock[2][3] = { Vec2::Vec2(1,1), Vec2::Vec2(2,2), Vec2::Vec2(1,2), Vec2::Vec2(2,2) };
nShapeToBlock[2][4] = { Vec2::Vec2(1,1), Vec2::Vec2(2,2), Vec2::Vec2(1,2), Vec2::Vec2(2,2) };

//오른쪽 슬라이드
nShapeToBlock[3][0] = { Vec2::Vec2(0,1), Vec2::Vec2(1,1), Vec2::Vec2(1,2), Vec2::Vec2(2,2) };
nShapeToBlock[3][1] = { Vec2::Vec2(2,1), Vec2::Vec2(1,2), Vec2::Vec2(2,2), Vec2::Vec2(1,3) };
nShapeToBlock[3][3] = { Vec2::Vec2(0,1), Vec2::Vec2(1,1), Vec2::Vec2(1,2), Vec2::Vec2(2,2) };
nShapeToBlock[3][4] = { Vec2::Vec2(2,1), Vec2::Vec2(1,2), Vec2::Vec2(2,2), Vec2::Vec2(1,3) };

//왼쪽 슬라이드
nShapeToBlock[4][0] = { Vec2::Vec2(1,1), Vec2::Vec2(2,1), Vec2::Vec2(0,2), Vec2::Vec2(1,2) };
nShapeToBlock[4][1] = { Vec2::Vec2(1,1), Vec2::Vec2(1,2), Vec2::Vec2(2,2), Vec2::Vec2(2,3) };
nShapeToBlock[4][3] = { Vec2::Vec2(1,1), Vec2::Vec2(2,1), Vec2::Vec2(0,2), Vec2::Vec2(1,2) };
nShapeToBlock[4][4] = { Vec2::Vec2(1,1), Vec2::Vec2(1,2), Vec2::Vec2(2,2), Vec2::Vec2(2,3) };


//ㄴ
nShapeToBlock[5][0] = { Vec2::Vec2(0,1), Vec2::Vec2(0,2), Vec2::Vec2(1,2), Vec2::Vec2(2,2) };
nShapeToBlock[5][1] = { Vec2::Vec2(1,1), Vec2::Vec2(2,1), Vec2::Vec2(1,2), Vec2::Vec2(1,3) };
nShapeToBlock[5][3] = { Vec2::Vec2(0,2), Vec2::Vec2(1,2), Vec2::Vec2(2,2), Vec2::Vec2(2,3) };
nShapeToBlock[5][4] = { Vec2::Vec2(1,1), Vec2::Vec2(1,2), Vec2::Vec2(1,3), Vec2::Vec2(0,3) };

//역s
nShapeToBlock[6][0] = { Vec2::Vec2(2,1), Vec2::Vec2(0,2), Vec2::Vec2(1,2), Vec2::Vec2(2,2) };
nShapeToBlock[6][1] = { Vec2::Vec2(1,1), Vec2::Vec2(1,2), Vec2::Vec2(1,3), Vec2::Vec2(2,3) };
nShapeToBlock[6][3] = { Vec2::Vec2(0,2), Vec2::Vec2(1,2), Vec2::Vec2(2,2), Vec2::Vec2(0,3) };
nShapeToBlock[6][4] = { Vec2::Vec2(0,1), Vec2::Vec2(1,1), Vec2::Vec2(1,2), Vec2::Vec2(1,3) };
//*/

void CBlockBase::Reset(cocos2d::Vec2&& pos, BlockType nBlockType)
{
	if (nBlockType < 0 || nBlockType >= BlockType::kBlockTypeMax)
	{
		return;
	}

	m_nType = nBlockType;
	m_nState = BlockState::kBlockStateA0;
	m_nPos = std::move(pos);
}

void CBlockBase::DrawCell(ICellBoard* cellBoard)
{
	for (auto blockInfo : nShapeToBlock[static_cast<int>(m_nType)][static_cast<int>(m_nState)])
	{
		int cellCol = m_nPos.x + blockInfo.x;
		int cellRow = m_nPos.y - blockInfo.y;

		cellBoard->Set(cellRow, cellCol, m_nType);//Celltype과 컬러 프레임을 일치시켜둠
	}
}

void CBlockBase::UndrawCell(ICellBoard* cellBoard)
{
	{
		for (auto blockInfo : nShapeToBlock[static_cast<int>(m_nType)][static_cast<int>(m_nState)])
		{
			int cellCol = m_nPos.x + blockInfo.x;
			int cellRow = m_nPos.y - blockInfo.y;

			cellBoard->Set(cellRow, cellCol, BlockType::kBlockTypeMax);//Celltype과 컬러 프레임을 일치시켜둠
		}
	}
}

void CDropBlock::Reset(cocos2d::Vec2&& vecPos, BlockType nBlockType)
{
	CBlockBase::Reset(std::move(vecPos), nBlockType);
	m_nEditedYPos = 0;
}


bool CDropBlock::RotateCW()
{
	int nAngle = static_cast<int>(m_nState) + 1;
	if (nAngle > static_cast<int>(BlockState::kBlockStateA270))
	{
		m_nState = BlockState::kBlockStateA0;
	}
	else
	{
		m_nState = static_cast<BlockState>(nAngle);
	}

	return true;
};

bool CDropBlock::RotateCCW()
{
	int nAngle = static_cast<int>(m_nState) - 1;
	if (nAngle < static_cast<int>(BlockState::kBlockStateA0))
	{
		m_nState = BlockState::kBlockStateA270;
	}
	else
	{
		m_nState = static_cast<BlockState>(nAngle);
	}

	return true;
};

cocos2d::Vec2&	CDropBlock::GetPos()
{
	return m_nPos;
}

void CDropBlock::SetPos(const cocos2d::Vec2& vecPos)
{
	m_nPos = vecPos;
}

int CDropBlock::IsCollisionToWall()
{
	int nPos = 0;
	for (auto blockInfo : nShapeToBlock[static_cast<int>(m_nType)][static_cast<int>(m_nState)])
	{
		if ((m_nPos.x + blockInfo.x) > 9)
		{
			if ((m_nPos.x + blockInfo.x) - 9 > nPos)
			{
				nPos = (m_nPos.x + blockInfo.x) - 9;
			}
		}

		if ((m_nPos.x + blockInfo.x) < 0)
		{
			if ((m_nPos.x + blockInfo.x) < nPos)
			{
				nPos = m_nPos.x + blockInfo.x;
			}
		}
	}

	return nPos;
}

bool CDropBlock::IsCollisionToFloor()
{
	for (auto blockInfo : nShapeToBlock[static_cast<int>(m_nType)][static_cast<int>(m_nState)])
	{
		if ((m_nPos.y - blockInfo.y)  <  0)
		{
			return true;
		}
	}

	return false;
}

bool CDropBlock::IsCollisionToCell(CCellBoard<20, 10>& cellBoard)
{
	for (auto blockInfo : nShapeToBlock[static_cast<int>(m_nType)][static_cast<int>(m_nState)])
	{
		int cellCol = m_nPos.x + blockInfo.x;
		int cellRow = m_nPos.y - blockInfo.y + m_nEditedYPos;

		if (cellBoard.Get(cellRow, cellCol) != BlockType::kBlockTypeMax)
		{
			return true;
		}
	}

	return false;
}


bool CDropBlock::GetOverlap(CCellBoard<20, 10>& cellBoard, Vec2& vecOvelap)
{
	Vec2 coreBlock = BlockCore[m_nType];
	Vec2 lastCheck;
	int cellCol = 0;
	int cellRow = 0;
	int sellidx = 0;
	
	int nWidthDistance = 0;
	int nHeightDistance = 0;

	for (auto blockInfo : nShapeToBlock[static_cast<int>(m_nType)][static_cast<int>(m_nState)])
	{
		cellCol = m_nPos.x + blockInfo.x;
		cellRow = m_nPos.y - blockInfo.y + m_nEditedYPos;

		bool isCollison = false;
		if (cellBoard.Get(cellRow, cellCol) != BlockType::kBlockTypeMax)
		{
			isCollison = true;
		}

		if (cellRow < 0)
		{
			isCollison = true;
		}

		if (cellCol < 0 || cellCol > 9)
		{
			isCollison = true;
		}

		if (isCollison)
		{
			if (lastCheck.x != 0 && lastCheck.y != 0)
			{
				int distance = abs(lastCheck.x - blockInfo.x) + abs(lastCheck.y - blockInfo.y);
				if (distance > 1)
				{
					return false;
				}
			}

			nWidthDistance = coreBlock.x - blockInfo.x;
			nHeightDistance = coreBlock.y - blockInfo.y;

			if (abs(nWidthDistance) > abs(vecOvelap.x))
			{
				vecOvelap.x = nWidthDistance;
			}

			if (abs(nHeightDistance) > abs(vecOvelap.y))
			{
				vecOvelap.y = nHeightDistance;
			}

			lastCheck = blockInfo;
		}
	}

	return true;
}

bool CDropBlock::IsCollision(CCellBoard<20, 10>& cellBoard)
{
	int cellCol = 0;
	int cellRow = 0;
	int sellidx = 0;

	for (auto blockInfo : nShapeToBlock[static_cast<int>(m_nType)][static_cast<int>(m_nState)])
	{
		cellCol = m_nPos.x + blockInfo.x;
		cellRow = m_nPos.y - blockInfo.y + m_nEditedYPos;

		if (cellBoard.Get(cellRow, cellCol) != BlockType::kBlockTypeMax)
		{
			return true;
		}

		if (cellRow < 0)
		{
			return true;
		}

		if (cellCol < 0 || cellCol > 9)
		{
			return true;
		}
	}

	return false;
}

//
//bool CDropBlock::IsCollisionToCell(int* cellBoard)
//{
//int nPos = 0;
//for (auto blockInfo : nShapeToBlock[static_cast<int>(m_nType)][static_cast<int>(m_nState)])
//{
//int cellCol = m_nPos.x + blockInfo.x;
//int cellRow = m_nPos.y - blockInfo.y + m_nEditedYPos;
//
//int sellidx = cellCol + cellRow * 10;
//if (sellidx < 200)
//{
//if (cellBoard[sellidx] != BlockType::kBlockTypeMax)
//{
//if (nPos < cellRow)
//{
//nPos = cellRow;
//}
//}
//}
//}
//
//return false;
//}



//bool CDropBlock::IsCollisionToFloor()
//{
//	int nPos = 0;
//	for (auto blockInfo : nShapeToBlock[static_cast<int>(m_nType)][static_cast<int>(m_nState)])
//	{
//		if ((m_nPos.y - blockInfo.y)  <  0)
//		{
//			if ((m_nPos.y - blockInfo.y) < nPos)
//			{
//				nPos = m_nPos.y - blockInfo.y;
//			}
//		}
//	}
//
//	return nPos;
//}