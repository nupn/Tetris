#pragma once
#include "DropBlock.h"

class CBlockProductor
{
public:
	enum {
		kBlockResourcIdxDefault = 7,
		kBlockResourcIdxMax = 8,
		kRow = 20,
		kCol = 10
	};

	enum
	{
		kWindowsSize = CDropBlock::BlockType::kBlockTypeMax, // ���������
		kAllowCateSize = kWindowsSize * 2,//�����Ҷ� ����ϴ�ũ��
		kArraySize = kAllowCateSize * 2, //�ִ� ũ��
	};
public:
	CBlockProductor();
	~CBlockProductor();

	void SlideWindow();
	CBlockBase::BlockType GetBlock(int nIdx);

private:
	inline int __GetReserverSize();
	inline int __GetCircularIdx(int nDefer);
	bool __Reallocate(int nStartIdx, int nEndIdx);

	CBlockBase::BlockType m_blockQueue[kArraySize];
	int nQueueStart;
	int nQueueEnd;
};

static_assert(CBlockProductor::kArraySize >= CBlockProductor::kWindowsSize * 3, "ArraySize lager than 3 time of Windows Size ");
static_assert((CBlockProductor::kArraySize % CBlockProductor::kAllowCateSize) == 0, "ArraySize Divide by AllowCateSize without remainder");
static_assert(CBlockProductor::kArraySize > CBlockProductor::kAllowCateSize, "ArraySize Large then AllocateSzie");