#pragma once
#include "cocos2d.h"
#include "CellBoard.h"

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

