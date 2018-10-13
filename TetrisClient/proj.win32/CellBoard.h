#pragma once
#include "cocos2d.h"
#include "Constants.h"

class ICellBoard
{
public:
	ICellBoard() = default;
	virtual ~ICellBoard() = default;

	virtual void Set(int row, int col, int nValue) = 0;
	virtual int Get(int row, int col) const = 0;
	virtual void Reset(int value) = 0;
};

template<int Row,int Col> class CCellBoard : public ICellBoard
{
public:
	enum {
		kCellMax = Row * Col
	};

public:
	CCellBoard()
	{
		for (int i = 0; i < kCellMax; ++i)
		{
			m_cellBoard[i] = kBlockResourcIdxDefault;
		}
	};

	virtual ~CCellBoard()
	{

	};
	
	virtual void Set(int row, int col, int nValue)
	{
		int npos = col + row * Col;
		if (npos >= 0 && npos < kCellMax)
		{
			m_cellBoard[npos] = nValue;
		}
	};

	virtual int Get(int row, int col) const
	{
		int npos = col + row * Col;
		if (npos >= 0 && npos < kCellMax)
		{
			return m_cellBoard[npos];
		}

		return -1;
	}

	virtual void Reset(int value)
	{
		for (int i = 0; i < kCellMax; ++i)
		{
			m_cellBoard[i] = value;
		}
	}


protected:
	int m_cellBoard[kCellMax] = { 0, };
};

