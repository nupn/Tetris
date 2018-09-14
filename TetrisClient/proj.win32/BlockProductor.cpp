#include "BlockProductor.h"
#include <algorithm>
#include <random>

using namespace cocos2d;

CBlockProductor::CBlockProductor()
{

	nQueueStart = 0;
	nQueueEnd = kAllowCateSize;
	__Reallocate(nQueueStart, nQueueEnd);
}


CBlockProductor::~CBlockProductor()
{
}

int CBlockProductor::__GetCircularIdx(int nDefer)
{
	return nDefer % kArraySize;
}

int CBlockProductor::__GetReserverSize()
{
	if (nQueueEnd > nQueueStart)
	{
		return nQueueEnd - nQueueStart;
	}
	else
	{
		return CBlockProductor::kArraySize + nQueueEnd - nQueueStart;
	}

}

CDropBlock::BlockType CBlockProductor::GetBlock(int nIdx)
{
	return m_blockQueue[__GetCircularIdx(nQueueStart + nIdx)];
}

void CBlockProductor::SlideWindow()
{
	++nQueueStart;
	if (nQueueStart >= kArraySize)
	{
		nQueueStart = 0;
	}

	int reservSize = __GetReserverSize();
	while (reservSize < CBlockProductor::kWindowsSize * 2)
	{
		int ExpendedIdx = __GetCircularIdx(nQueueEnd + kAllowCateSize - 1);
		if (reservSize + kAllowCateSize > kArraySize)
		{
			break;
		}

		if (!__Reallocate(nQueueEnd, ExpendedIdx))
		{
			break;
		}
		nQueueEnd = ExpendedIdx;

		reservSize = __GetReserverSize();
	}
}


bool CBlockProductor::__Reallocate(int nStartIdx, int nEndIdx)
{
	if (nStartIdx >= kArraySize || nEndIdx >= kArraySize)
	{
		//ERROR
		return false;
	}

	CDropBlock::BlockType nBuffer[kAllowCateSize];
	for (int i = 0; i < kAllowCateSize; ++i)
	{
		nBuffer[i] = static_cast<CDropBlock::BlockType>(i % CDropBlock::BlockType::kBlockTypeMax);
	}

	std::random_shuffle(std::begin(nBuffer), std::begin(nBuffer) + (kAllowCateSize-1));

	if (nEndIdx > nStartIdx)
	{
		int j = 0;
		for (int i = nStartIdx; i < nEndIdx; ++i)
		{
			if (j < kAllowCateSize)
			{
				m_blockQueue[i] = nBuffer[j];
				++j;
			}
		}
	}
	else
	{
		int j = 0;
		for (int i = nStartIdx; i < kArraySize; ++i)
		{
			if (j < kAllowCateSize)
			{
				m_blockQueue[i] = nBuffer[j];
				++j;
			}
		}

		for (int i = 0; i < nEndIdx; ++i)
		{
			if (j < kAllowCateSize)
			{
				m_blockQueue[i] = nBuffer[j];
				++j;
			}
		}
	}
	return true;
}
