#pragma once
#include "cocos2d.h"
#include "CellBoard.h"


using namespace cocos2d;

class CBlockBase
{
public:
	enum BlockType
	{
		kBlockTypeBar = 0,
		kBlockTypeMo,
		kBlockTypeSquare,
		kBlockTypeRSlide,
		kBlockTypeLSlide,
		kBlockTypeLCorner,
		kBlockTypeRCorner,
		kBlockTypeMax,
	};

	enum BlockState
	{
		kBlockStateA0 = 0,
		kBlockStateA90,
		kBlockStateA180,
		kBlockStateA270,
	};

	CBlockBase() = default;
	~CBlockBase() = default;
	virtual void Reset(cocos2d::Vec2&& pos, BlockType nBlockType);
	void DrawCell(ICellBoard* cellBoard);
	void UndrawCell(ICellBoard* cellBoard);
	BlockType GetBlockType();
	BlockState GetBlockState();

protected:
	BlockType m_nType;
	BlockState m_nState;
	cocos2d::Vec2 m_nPos;
};

class CDropBlock : public CBlockBase
{


public:
	CDropBlock() = default;
	~CDropBlock() = default;


public:
	virtual void Reset(cocos2d::Vec2&& posX, BlockType nBlockType) override;
	int IsCollisionToWall();

	bool IsCollisionToFloor();
	bool IsCollisionToCell(CCellBoard<20, 10>& cellBoard);
	bool IsCollision(CCellBoard<20, 10>& cellBoard);
	bool GetOverlap(CCellBoard<20, 10>& cellBoard, cocos2d::Vec2& vecOvelap);

	bool RotateCW();
	bool RotateCCW();
	cocos2d::Vec2&	GetPos();
	void SetPos(const cocos2d::Vec2& vecPos);

	bool DropByGravity() {};
	void SinkToFloor() {};
	void AttachBlock() {};


	bool __CollisionTest() {};

private:
};

const std::vector<Vec2>& GetBlockShapes(int nType, int nState);

/*
#ifndef BLOCK_SHAPE
#define BLOCK_SHAPE
//static Vec2 nShapeToBlock[7][4] = {
extern const std::vector<Vec2> nShapeToBlock[7][4] = {
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



const extern Vec2 BlockCore[7] = {
	Vec2::Vec2(1,2), //작대기
	Vec2::Vec2(1, 2), // ㅗ
	Vec2::Vec2(0,1), //네모
	Vec2::Vec2(1,2), //오른쪾 슬라이드
	Vec2::Vec2(1,2), // 왼쪽 슬라이드
	Vec2::Vec2(1,2), //ㄴ
	Vec2::Vec2(1,2) //역 ㄴ
};

inline const std::vector<Vec2>& GetBlockShapes(int nType, int nState)
{
	return nShapeToBlock[nType][nState];
}
#endif
*/
