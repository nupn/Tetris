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
	m_pGameBoard = CGameBoard::create();
	addChild(dynamic_cast<Sprite*>(m_pGameBoard));
	
	//m_pBlockProductor = CBlockProductor::create();
	//addChild(dynamic_cast<Sprite*>(m_pBlockProductor));

	__UpdateDropBlock();

	return cocos2d::Layer::init();
}

void CClassicTetrisLayer::UpdateCellTexture()
{
	m_pGameBoard->UpdateDisplay();
}

void CClassicTetrisLayer::UpdateDropBlock()
{
	__UpdateDropBlock();
	UpdateCellTexture();
}

void CClassicTetrisLayer::RotateBlockLeft()
{
	m_pGameBoard->RotateDropBlock(true);
	UpdateCellTexture();
}

void CClassicTetrisLayer::RotateBlockRight()
{
	m_pGameBoard->RotateDropBlock(false);
	UpdateCellTexture();
}

void CClassicTetrisLayer::MoveBlockLeft()
{
	m_pGameBoard->MoveBlockSide(-1);
	UpdateCellTexture();
}

void CClassicTetrisLayer::MoveBlockRight()
{
	m_pGameBoard->MoveBlockSide(1);
	UpdateCellTexture();
}

void CClassicTetrisLayer::DropBlock()
{
	m_pGameBoard->DropBlock();
	__UpdateDropBlock();
	m_pGameBoard->CheckLineClear();
	UpdateCellTexture();
}

CGameBoard::DownBlockResult CClassicTetrisLayer::MoveBlockDown()
{
	CGameBoard::DownBlockResult ret = m_pGameBoard->MoveBlockDown();
	if (ret == CGameBoard::DownBlockResult::Dropped)
	{
		m_pGameBoard->CheckLineClear();
		__UpdateDropBlock();
	}
	UpdateCellTexture();

	return ret;
}

bool CClassicTetrisLayer::IsDropBlockDeadLine()
{
	return m_pGameBoard->IsDeadLine();
}

void CClassicTetrisLayer::__UpdateDropBlock()
{
	static int nIdx = 0;
	nIdx++;
	if (nIdx >= CDropBlock::BlockType::kBlockTypeMax)
	{
		nIdx = 0;
	}
	CDropBlock::BlockType nType = static_cast<CDropBlock::BlockType>(nIdx);
	m_pGameBoard->ResetDropBlock(nType);
	return;
	//CDropBlock::BlockType nType = m_BlockProductor.GetBlock(0);
	//m_BlockProductor.SlideWindow();

}