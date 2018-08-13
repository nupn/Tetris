#include "DropBlock.h"
#include "cocos2d.h"
#include <vector>

using namespace cocos2d;


static std::vector<Vec2> nShapeToBlock[7][4] = {
{
	//�۴��
	{ Vec2::Vec2(1,0), Vec2::Vec2(1,1), Vec2::Vec2(1,2), Vec2::Vec2(1,3) },
	{ Vec2::Vec2(0,2), Vec2::Vec2(1,2), Vec2::Vec2(2,2), Vec2::Vec2(3,2) },
	{ Vec2::Vec2(1,0), Vec2::Vec2(1,1), Vec2::Vec2(1,2), Vec2::Vec2(1,3) },
	{ Vec2::Vec2(0,2), Vec2::Vec2(1,2), Vec2::Vec2(2,2), Vec2::Vec2(3,2) }
},
{
//��
	{ Vec2::Vec2(1, 1), Vec2::Vec2(0, 2), Vec2::Vec2(1, 2), Vec2::Vec2(2, 2) },
	{ Vec2::Vec2(1,1), Vec2::Vec2(1,2), Vec2::Vec2(2,2), Vec2::Vec2(1,3) },
	{ Vec2::Vec2(0,2), Vec2::Vec2(1,2), Vec2::Vec2(2,2), Vec2::Vec2(1,3) },
	{ Vec2::Vec2(1,1), Vec2::Vec2(0,2), Vec2::Vec2(1,2), Vec2::Vec2(1,3) }
},
{
	//�׸�
	{ Vec2::Vec2(0,1), Vec2::Vec2(1,1), Vec2::Vec2(0,2), Vec2::Vec2(1,2) },
	{ Vec2::Vec2(0,1), Vec2::Vec2(1,1), Vec2::Vec2(0,2), Vec2::Vec2(1,2) },
	{ Vec2::Vec2(0,1), Vec2::Vec2(1,1), Vec2::Vec2(0,2), Vec2::Vec2(1,2) },
	{ Vec2::Vec2(0,1), Vec2::Vec2(1,1), Vec2::Vec2(0,2), Vec2::Vec2(1,2) }
},
{
	//������ �����̵�
	{ Vec2::Vec2(0,1), Vec2::Vec2(1,1), Vec2::Vec2(1,2), Vec2::Vec2(2,2) },
	{ Vec2::Vec2(2,1), Vec2::Vec2(1,2), Vec2::Vec2(2,2), Vec2::Vec2(1,3) },
	{ Vec2::Vec2(0,1), Vec2::Vec2(1,1), Vec2::Vec2(1,2), Vec2::Vec2(2,2) },
	{ Vec2::Vec2(2,1), Vec2::Vec2(1,2), Vec2::Vec2(2,2), Vec2::Vec2(1,3) }
},
{
	//���� �����̵�
	{ Vec2::Vec2(1,1), Vec2::Vec2(2,1), Vec2::Vec2(0,2), Vec2::Vec2(1,2) },
	{ Vec2::Vec2(1,1), Vec2::Vec2(1,2), Vec2::Vec2(2,2), Vec2::Vec2(2,3) },
	{ Vec2::Vec2(1,1), Vec2::Vec2(2,1), Vec2::Vec2(0,2), Vec2::Vec2(1,2) },
	{ Vec2::Vec2(1,1), Vec2::Vec2(1,2), Vec2::Vec2(2,2), Vec2::Vec2(2,3) }
},
{
	//��
	{ Vec2::Vec2(0,1), Vec2::Vec2(0,2), Vec2::Vec2(1,2), Vec2::Vec2(2,2) },
	{ Vec2::Vec2(1,1), Vec2::Vec2(2,1), Vec2::Vec2(1,2), Vec2::Vec2(1,3) },
	{ Vec2::Vec2(0,2), Vec2::Vec2(1,2), Vec2::Vec2(2,2), Vec2::Vec2(2,3) },
	{ Vec2::Vec2(1,1), Vec2::Vec2(1,2), Vec2::Vec2(1,3), Vec2::Vec2(0,3) }
},
{
	//����
	{ Vec2::Vec2(2,1), Vec2::Vec2(0,2), Vec2::Vec2(1,2), Vec2::Vec2(2,2) },
	{ Vec2::Vec2(1,1), Vec2::Vec2(1,2), Vec2::Vec2(1,3), Vec2::Vec2(2,3) },
	{ Vec2::Vec2(0,2), Vec2::Vec2(1,2), Vec2::Vec2(2,2), Vec2::Vec2(0,3) },
	{ Vec2::Vec2(0,1), Vec2::Vec2(1,1), Vec2::Vec2(1,2), Vec2::Vec2(1,3) }
}
};

/*
//�۴��
nShapeToBlock[0][0] = { Vec2::Vec2(1,0), Vec2::Vec2(1,1), Vec2::Vec2(1,2), Vec2::Vec2(1,3) };
nShapeToBlock[0][1] = { Vec2::Vec2(0,2), Vec2::Vec2(1,2), Vec2::Vec2(2,2), Vec2::Vec2(3,2) };
nShapeToBlock[0][3] = { Vec2::Vec2(1,0), Vec2::Vec2(1,1), Vec2::Vec2(1,2), Vec2::Vec2(1,3) };
nShapeToBlock[0][4] = { Vec2::Vec2(0,2), Vec2::Vec2(1,2), Vec2::Vec2(2,2), Vec2::Vec2(3,2) };

//��
nShapeToBlock[1][0] = { Vec2::Vec2(1,1), Vec2::Vec2(0,2), Vec2::Vec2(1,2), Vec2::Vec2(2,2) };
nShapeToBlock[1][1] = { Vec2::Vec2(1,1), Vec2::Vec2(1,2), Vec2::Vec2(2,2), Vec2::Vec2(1,3) };
nShapeToBlock[1][3] = { Vec2::Vec2(0,2), Vec2::Vec2(1,2), Vec2::Vec2(2,2), Vec2::Vec2(1,3) };
nShapeToBlock[1][4] = { Vec2::Vec2(1,1), Vec2::Vec2(0,2), Vec2::Vec2(1,2), Vec2::Vec2(1,3) };

//�׸�
nShapeToBlock[2][0] = { Vec2::Vec2(1,1), Vec2::Vec2(2,2), Vec2::Vec2(1,2), Vec2::Vec2(2,2) };
nShapeToBlock[2][1] = { Vec2::Vec2(1,1), Vec2::Vec2(2,2), Vec2::Vec2(1,2), Vec2::Vec2(2,2) };
nShapeToBlock[2][3] = { Vec2::Vec2(1,1), Vec2::Vec2(2,2), Vec2::Vec2(1,2), Vec2::Vec2(2,2) };
nShapeToBlock[2][4] = { Vec2::Vec2(1,1), Vec2::Vec2(2,2), Vec2::Vec2(1,2), Vec2::Vec2(2,2) };

//������ �����̵�
nShapeToBlock[3][0] = { Vec2::Vec2(0,1), Vec2::Vec2(1,1), Vec2::Vec2(1,2), Vec2::Vec2(2,2) };
nShapeToBlock[3][1] = { Vec2::Vec2(2,1), Vec2::Vec2(1,2), Vec2::Vec2(2,2), Vec2::Vec2(1,3) };
nShapeToBlock[3][3] = { Vec2::Vec2(0,1), Vec2::Vec2(1,1), Vec2::Vec2(1,2), Vec2::Vec2(2,2) };
nShapeToBlock[3][4] = { Vec2::Vec2(2,1), Vec2::Vec2(1,2), Vec2::Vec2(2,2), Vec2::Vec2(1,3) };

//���� �����̵�
nShapeToBlock[4][0] = { Vec2::Vec2(1,1), Vec2::Vec2(2,1), Vec2::Vec2(0,2), Vec2::Vec2(1,2) };
nShapeToBlock[4][1] = { Vec2::Vec2(1,1), Vec2::Vec2(1,2), Vec2::Vec2(2,2), Vec2::Vec2(2,3) };
nShapeToBlock[4][3] = { Vec2::Vec2(1,1), Vec2::Vec2(2,1), Vec2::Vec2(0,2), Vec2::Vec2(1,2) };
nShapeToBlock[4][4] = { Vec2::Vec2(1,1), Vec2::Vec2(1,2), Vec2::Vec2(2,2), Vec2::Vec2(2,3) };


//��
nShapeToBlock[5][0] = { Vec2::Vec2(0,1), Vec2::Vec2(0,2), Vec2::Vec2(1,2), Vec2::Vec2(2,2) };
nShapeToBlock[5][1] = { Vec2::Vec2(1,1), Vec2::Vec2(2,1), Vec2::Vec2(1,2), Vec2::Vec2(1,3) };
nShapeToBlock[5][3] = { Vec2::Vec2(0,2), Vec2::Vec2(1,2), Vec2::Vec2(2,2), Vec2::Vec2(2,3) };
nShapeToBlock[5][4] = { Vec2::Vec2(1,1), Vec2::Vec2(1,2), Vec2::Vec2(1,3), Vec2::Vec2(0,3) };

//��s
nShapeToBlock[6][0] = { Vec2::Vec2(2,1), Vec2::Vec2(0,2), Vec2::Vec2(1,2), Vec2::Vec2(2,2) };
nShapeToBlock[6][1] = { Vec2::Vec2(1,1), Vec2::Vec2(1,2), Vec2::Vec2(1,3), Vec2::Vec2(2,3) };
nShapeToBlock[6][3] = { Vec2::Vec2(0,2), Vec2::Vec2(1,2), Vec2::Vec2(2,2), Vec2::Vec2(0,3) };
nShapeToBlock[6][4] = { Vec2::Vec2(0,1), Vec2::Vec2(1,1), Vec2::Vec2(1,2), Vec2::Vec2(1,3) };
//*/

void CDropBlock::Reset(cocos2d::Vec2&& vecPos, BlockType nBlockType)
{
	m_nType = nBlockType;
	m_nState = BlockState::kBlockStateA0;
	m_nEditedYPos = 0;
	m_nPos = std::move(vecPos);

	++m_nblockIdx;
	m_nType = static_cast<BlockType>(m_nblockIdx);
	if (m_nblockIdx >= static_cast<int>(BlockType::kBlockTypeMax))
	{
		m_nblockIdx = 0;
		m_nType = BlockType::kBlockTypeBar;
	}
}
void CDropBlock::DrawCell(int* cellBoard)
{
	//�� üũ�� �����ҋ� �ʱ�ȭ�ҋ�������
	if (m_nType < BlockType::kBlockTypeBar || m_nType > BlockType::kBlockTypeMax)
	{
		return;
	}

	if (m_nState < BlockState::kBlockStateA0 || m_nState > BlockState::kBlockStateA270)
	{
		return;
	}

	for (auto blockInfo : nShapeToBlock[static_cast<int>(m_nType)][static_cast<int>(m_nState)])
	{
		int cellCol = m_nPos.x + blockInfo.x;
		int cellRow = m_nPos.y - blockInfo.y + m_nEditedYPos;

		int sellidx = cellCol + cellRow * 10;
		if (sellidx < 200)
		{
			cellBoard[sellidx] = static_cast<int>(m_nType);//Celltype�� �÷� �������� ��ġ���ѵ�
		}
	}
}

void CDropBlock::UndrawCell(int* cellBoard)
{
	if (m_nType < BlockType::kBlockTypeBar || m_nType > BlockType::kBlockTypeMax)
	{
		return;
	}

	if (m_nState < BlockState::kBlockStateA0 || m_nState > BlockState::kBlockStateA270)
	{
		return;
	}

	for (auto blockInfo : nShapeToBlock[static_cast<int>(m_nType)][static_cast<int>(m_nState)])
	{
		int cellCol = m_nPos.x + blockInfo.x;
		int cellRow = m_nPos.y - blockInfo.y + m_nEditedYPos;

		int sellidx = cellCol + cellRow * 10;
		if (sellidx < 200)
		{
			cellBoard[sellidx] = static_cast<int>(BlockType::kBlockTypeMax);//Celltype�� �÷� �������� ��ġ���ѵ�
		}
	}
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

int CDropBlock::IsCollisionToFloor()
{
	int nPos = 0;
	for (auto blockInfo : nShapeToBlock[static_cast<int>(m_nType)][static_cast<int>(m_nState)])
	{
		if ((m_nPos.y - blockInfo.y)  <  0)
		{
			if ((m_nPos.y - blockInfo.y) < nPos)
			{
				nPos = m_nPos.y - blockInfo.y;
			}
		}
	}

	return nPos;
}

int CDropBlock::IsCollisionToCell(int* cellBoard)
{
	int nPos = 0;
	for (auto blockInfo : nShapeToBlock[static_cast<int>(m_nType)][static_cast<int>(m_nState)])
	{
		int cellCol = m_nPos.x + blockInfo.x;
		int cellRow = m_nPos.y - blockInfo.y + m_nEditedYPos;

		int sellidx = cellCol + cellRow * 10;
		if (sellidx < 200)
		{
			if (cellBoard[sellidx] != BlockType::kBlockTypeMax)
			{
				if (nPos < cellRow)
				{
					nPos = cellRow;
				}
			}
		}
	}

	return nPos;
}

void CDropBlock::MarkCell(int* cellBoard)
{
	for (auto blockInfo : nShapeToBlock[static_cast<int>(m_nType)][static_cast<int>(m_nState)])
	{
		int cellCol = m_nPos.x + blockInfo.x;
		int cellRow = m_nPos.y - blockInfo.y + m_nEditedYPos;

		int sellidx = cellCol + cellRow * 10;
		if (sellidx < 200)
		{
			cellBoard[sellidx] = m_nType;
		}
	}
}