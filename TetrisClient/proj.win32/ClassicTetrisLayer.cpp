#include "ClassicTetrisLayer.h"

using namespace cocos2d;

CClassicTetrisLayer::CClassicTetrisLayer()
{
}


CClassicTetrisLayer::~CClassicTetrisLayer()
{
}

//http://cocos2dx.tistory.com/entry/CCSpriteBatchNode-%EC%82%AC%EC%9A%A9%EB%B2%95-cocos2dx
bool CClassicTetrisLayer::init()
{
	pBatchCellContainer = SpriteBatchNode::create("Tetris/source.png");
	addChild(pBatchCellContainer);
	m_CellBoard.UpdateDropBlock();

	return cocos2d::Layer::init();
}

void CClassicTetrisLayer::UpdateCellTexture()
{
	if (pBatchCellContainer == nullptr)
	{
		return;
	}

	pBatchCellContainer->removeAllChildren();
	m_CellBoard.OnDraw(pBatchCellContainer);
}

void CClassicTetrisLayer::UpdateDropBlock()
{
	m_CellBoard.UpdateDropBlock();
	UpdateCellTexture();
}

void CClassicTetrisLayer::RotateBlockLeft()
{
	m_CellBoard.RotateDropBlock(true);
	UpdateCellTexture();
}

void CClassicTetrisLayer::RotateBlockRight()
{
	m_CellBoard.RotateDropBlock(false);
	UpdateCellTexture();
}

void CClassicTetrisLayer::MoveBlockLeft()
{
	m_CellBoard.MoveBlockSide(-1);
	UpdateCellTexture();
}

void CClassicTetrisLayer::MoveBlockRight()
{
	m_CellBoard.MoveBlockSide(1);
	UpdateCellTexture();
}

void CClassicTetrisLayer::DropBlock()
{
	m_CellBoard.DropBlock();
	UpdateCellTexture();
}

void CClassicTetrisLayer::MoveBlockDown()
{
	m_CellBoard.MoveBlockDown();
	UpdateCellTexture();
}