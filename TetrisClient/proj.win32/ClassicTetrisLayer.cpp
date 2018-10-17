#include "ClassicTetrisLayer.h"

using namespace cocos2d;

CClassicTetrisLayer::CClassicTetrisLayer()
{
}


CClassicTetrisLayer::~CClassicTetrisLayer()
{
	CCDirector::sharedDirector()->getScheduler()->unschedule(CC_SCHEDULE_SELECTOR(CClassicTetrisLayer::OnUpdate), this);
}

//http://cocos2dx.tistory.com/entry/CCSpriteBatchNode-%EC%82%AC%EC%9A%A9%EB%B2%95-cocos2dx
bool CClassicTetrisLayer::init()
{
	m_pGameBoard = CGameBoard::create();
	addChild(dynamic_cast<Sprite*>(m_pGameBoard));
	
	m_nextBlockView = CNextBlockView::create();
	m_nextBlockView->setPosition(Vec2(300, 700));
	addChild(m_nextBlockView);

	m_nextBlockView2 = CNextBlockView::create();
	m_nextBlockView2->setPosition(Vec2(300, 600));
	addChild(m_nextBlockView2);



	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(CClassicTetrisLayer::onKeyPressed, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(CClassicTetrisLayer::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);



	__UpdateDropBlock();


	CCDirector::sharedDirector()->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(CClassicTetrisLayer::OnUpdate), this, 0, false);
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
	/*
	static int nIdx = 0;
	nIdx++;
	if (nIdx >= CDropBlock::BlockType::kBlockTypeMax)
	{
		nIdx = 0;
	}
	CDropBlock::BlockType nType = static_cast<CDropBlock::BlockType>(nIdx);
	m_pGameBoard->ResetDropBlock(nType);
	return;
	*/
	CDropBlock::BlockType nType = m_BlockProductor.GetBlock(0);
	m_BlockProductor.SlideWindow();
	m_pGameBoard->ResetDropBlock(nType);

	nType = m_BlockProductor.GetBlock(0);
	if (m_nextBlockView)
	{
		m_nextBlockView->SetBlock(nType);
	}
	nType = m_BlockProductor.GetBlock(1);
	if (m_nextBlockView2)
	{
		m_nextBlockView2->SetBlock(nType);
	}


	nType = m_BlockProductor.GetBlock(3);

	CCDirector::sharedDirector()->getScheduler()->unschedule(CC_SCHEDULE_SELECTOR(CClassicTetrisLayer::OnUpdateBlockDown), this);
	CCDirector::sharedDirector()->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(CClassicTetrisLayer::OnUpdateBlockDown), this, 2, false);
}

void CClassicTetrisLayer::OnUpdateBlockDown(float dt)
{
	CGameBoard::DownBlockResult ret = m_pGameBoard->MoveBlockDown();
	if (ret == CGameBoard::DownBlockResult::Dropped)
	{
		m_pGameBoard->CheckLineClear();
		__UpdateDropBlock();
	}
	//변화가 없다면 굳이? 전체를
	UpdateCellTexture();
}



void CClassicTetrisLayer::OnUpdate(float dt)
{
	//m_nUpdatePerTime = (nMovePerFrameMax - nMovePerFrameMin) - floor((nMovePerFrameMax - nMovePerFrameMin) * floor((m_nUpdateCntTotal * m_nUpdateCntTotal) / nMaxSpeed));


	const int nMoveMinFrame = 10;
	const int nMovePerFrame = 3;

	if (m_bMovingRight)
	{
		m_nUpdateCnt++;
		++m_nUpdateCntTotal;
		if (m_nUpdateCntTotal > nMoveMinFrame)
		{
			if (m_nUpdateCnt > nMovePerFrame)
			{
				MoveBlockRight();
				m_nUpdateCnt -= nMovePerFrame;
			}
		}
	}
	else if (m_bMovingLeft)
	{
		m_nUpdateCnt++;
		++m_nUpdateCntTotal;
		if (m_nUpdateCntTotal > nMoveMinFrame)
		{
			if (m_nUpdateCnt > nMovePerFrame)
			{

				MoveBlockLeft();
				m_nUpdateCnt -= nMovePerFrame;
			}
		}
	}
	else if (m_bMovingDown)
	{
		m_nUpdateCnt++;
		++m_nUpdateCntTotal;
		if (m_nUpdateCntTotal > nMoveMinFrame)
		{
			if (m_nUpdateCnt > nMovePerFrame)
			{
				if (IsDropBlockDeadLine() && !m_bMovingDownDeadLine)
				{
					m_bMovingDownDeadLine = true;
					m_nUpdateCntTotal = 0;
					return;
				}

				CGameBoard::DownBlockResult ret = MoveBlockDown();
				m_nUpdateCnt -= nMovePerFrame;
				if (ret == CGameBoard::DownBlockResult::Dropped)
				{
					ResetAllTimer();
				}
			}
		}
	}
}


void CClassicTetrisLayer::ResetAllTimer()
{
	m_nUpdateCnt = 0;
	m_nUpdateCntTotal = 0;
	m_nUpdatePerTime = 20;
	m_bMovingDownDeadLine = false;
}


void CClassicTetrisLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		m_bMovingLeft = false;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		m_bMovingRight = false;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	{
		m_bMovingDown = false;
	}
}

void CClassicTetrisLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ALT)
	{
		//346
	}

	if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
	{
		RotateBlockLeft();
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
	{
		if (m_bMovingDown == false)
		{
			MoveBlockDown();
			m_nUpdateCnt = 0;
			m_nUpdateCntTotal = 0;
			m_nUpdatePerTime = 20;
			m_bMovingDown = true;
			m_bMovingDownDeadLine = false;
		}
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
	{
		if (m_bMovingLeft == false)
		{
			MoveBlockLeft();
			m_nUpdateCnt = 0;
			m_nUpdateCntTotal = 0;
			m_nUpdatePerTime = 20;
			m_bMovingLeft = true;
		}
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
	{
		if (m_bMovingRight == false)
		{
			MoveBlockRight();
			m_nUpdateCnt = 0;
			m_nUpdateCntTotal = 0;
			m_nUpdatePerTime = 20;
			m_bMovingRight = true;
		}
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
	{
		DropBlock();
	}
}
