#pragma once
#include "cocos2d.h"

using namespace cocos2d;

//논리와 디스플레이 나눌 필요가있나..
template<int Row, int Col> class CCellBatchSprite : public SpriteBatchNode 
{
	static const int DEFAULT_CAPACITY = 29;
public:
	enum
	{
		kStartYPos = 23 * Row,
	};

public:
	CCellBatchSprite() = default;
	virtual ~CCellBatchSprite() = default;


	static CCellBatchSprite<Row, Col>* CCellBatchSprite<Row, Col>::create2(const std::string& fileImage, ssize_t capacity = DEFAULT_CAPACITY)
	{
		CCellBatchSprite<Row, Col> *batchNode = new (std::nothrow) CCellBatchSprite<Row, Col>();
		if (batchNode && batchNode->initWithFile(fileImage, capacity))
		{
			batchNode->autorelease();
			batchNode->InitSprite();
			return batchNode;
		}

		delete batchNode;
		return nullptr;
	}


	void InitSprite()
	{
		Sprite* pSprite;
		for (int row = 0; row < Row; ++row)
		{
			for (int col = 0; col < Col; ++col)
			{
				pSprite = Sprite::createWithTexture(getTexture());
				pSprite->setTag(col + row * Col);
				pSprite->setPosition(Vec2(col * 23, kStartYPos + (row * 23)));
				addChild(pSprite);
			}
		}
	}

	inline void UpdateCell(int nRow, int nCol, int nState)
	{
		const static cocos2d::Rect imgRect[kBlockResourcIdxMax] = {
			cocos2d::Rect(0, 0, 23, 23),
			cocos2d::Rect(23, 0, 23, 23),
			cocos2d::Rect(0, 23, 23, 23),
			cocos2d::Rect(23, 23, 23, 23),
			cocos2d::Rect(0, 46, 23, 23),
			cocos2d::Rect(23, 46, 23, 23),
			cocos2d::Rect(0, 69, 23, 23),
			cocos2d::Rect(23, 69, 23, 23)
		};
		

		if (nState >= 0 && nState < kBlockResourcIdxMax)
		{
			Sprite* pSprite = (Sprite*)getChildByTag(nCol + nRow * Col);
			if (pSprite)
			{
				pSprite->setPosition(Vec2(nCol * 23, kStartYPos + (nRow * 23)));
				pSprite->setTextureRect(imgRect[nState]);
			}
		}
	}
};

