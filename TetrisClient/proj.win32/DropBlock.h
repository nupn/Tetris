#pragma once
#include "cocos2d.h"

class CDropBlock
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

public:
	CDropBlock() = default;
	~CDropBlock() = default;


public:
	void Reset(cocos2d::Vec2&& posX , BlockType nBlockType);
	void DrawCell(int* cellBoard);
	void UndrawCell(int* cellBoard);
	void MarkCell(int* cellBoard);

	int IsCollisionToWall();

	bool IsCollisionToFloor();
	bool IsCollisionToCell(int* cellBoard);
	bool IsCollision(int* cellBoard);

	bool RotateCW();
	bool RotateCCW();
	cocos2d::Vec2&	GetPos();
	void SetPos(const cocos2d::Vec2& vecPos);


	bool GetOverlap(int* cellBoard, cocos2d::Vec2& vecOvelap);
	

	bool DropByGravity() {};
	void SinkToFloor() {};
	void AttachBlock() {};


	bool __CollisionTest() {};

private:

	BlockType m_nType;
	BlockState m_nState;
	int m_nEditedYPos;
	cocos2d::Vec2 m_nPos;

	int m_nblockIdx = 0;

};

