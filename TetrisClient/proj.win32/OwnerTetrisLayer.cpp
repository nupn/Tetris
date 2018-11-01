#include "OwnerTetrisLayer.h"

using namespace cocos2d;

COwnerTetrisLayer::COwnerTetrisLayer()
{
}


COwnerTetrisLayer::~COwnerTetrisLayer()
{
	CCDirector::sharedDirector()->getScheduler()->unschedule(CC_SCHEDULE_SELECTOR(COwnerTetrisLayer::OnUpdate), this);
}

//http://cocos2dx.tistory.com/entry/CCSpriteBatchNode-%EC%82%AC%EC%9A%A9%EB%B2%95-cocos2dx
bool COwnerTetrisLayer::init()
{
	m_pGameBoard = CGameBoard::create();
	addChild(dynamic_cast<Sprite*>(m_pGameBoard));
	
	m_nextBlockView = CNextBlockView::create();
	m_nextBlockView->setPosition(Vec2(240, 460 - (23 *4)));
	addChild(m_nextBlockView);

	m_nextBlockView2 = CNextBlockView::create();
	m_nextBlockView2->setPosition(Vec2(240, 460 - (23 * 4)- (23 * 4) - 23));
	addChild(m_nextBlockView2);



	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(COwnerTetrisLayer::onKeyPressed, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(COwnerTetrisLayer::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);



	__UpdateDropBlock();


	CCDirector::sharedDirector()->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(COwnerTetrisLayer::OnUpdate), this, 0, false);

	m_pGameResultEffect = CGameStateFontEffect::create();
	m_pGameResultEffect->setAnchorPoint(Vec2::Vec2(0.5, 0.5));
	m_pGameResultEffect->setPosition(Vec2::Vec2(115, 230));
	addChild(m_pGameResultEffect);
	//m_pGameResultEffect->SetState(kGameStateReady);

	m_nGameState = kPlay;
	/*
	if (m_nGameState == kPrepare && m_bChangeGameState == false)
	{
		if (m_pGameResultEffect != nullptr)
		{
			m_pGameResultEffect->SetState(CGameStateFontEffect::kPrepareHost);
			m_pGameResultEffect->PlayEffect(std::bind(&COwnerTetrisLayer::OnEffectEnd, this, std::placeholders::_1));
			m_bChangeGameState = true;
		}
	}
	*/

	return cocos2d::Layer::init();
}

void COwnerTetrisLayer::UpdateCellTexture()
{
	m_pGameBoard->UpdateDisplay();
}

void COwnerTetrisLayer::UpdateDropBlock()
{
	__UpdateDropBlock();
	UpdateCellTexture();
}

void COwnerTetrisLayer::RotateBlockLeft()
{
	m_pGameBoard->RotateDropBlock(true);
	UpdateCellTexture();
}

void COwnerTetrisLayer::RotateBlockRight()
{
	m_pGameBoard->RotateDropBlock(false);
	UpdateCellTexture();
}

void COwnerTetrisLayer::MoveBlockLeft()
{
	m_pGameBoard->MoveBlockSide(-1);
	UpdateCellTexture();
}

void COwnerTetrisLayer::MoveBlockRight()
{
	m_pGameBoard->MoveBlockSide(1);
	UpdateCellTexture();
}

void COwnerTetrisLayer::DropBlock()
{
	m_pGameBoard->DropBlock();
	__UpdateDropBlock();
	m_pGameBoard->CheckLineClear();
	UpdateCellTexture();
}

CGameBoard::DownBlockResult COwnerTetrisLayer::MoveBlockDown()
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

bool COwnerTetrisLayer::IsDropBlockDeadLine()
{
	return m_pGameBoard->IsDeadLine();
}

void COwnerTetrisLayer::__UpdateDropBlock()
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
	if (!m_pGameBoard->ResetDropBlock(nType))
	{
		m_pGameResultEffect->SetState(CGameStateFontEffect::kDead);
		m_pGameResultEffect->PlayEffect(std::bind(&COwnerTetrisLayer::OnEffectEnd, this, std::placeholders::_1));

		m_nGameState = kReady;
		return;
	}

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

	CCDirector::getInstance()->getScheduler()->unschedule(CC_SCHEDULE_SELECTOR(COwnerTetrisLayer::OnUpdateBlockDown), this);
	CCDirector::getInstance()->getScheduler()->schedule(CC_SCHEDULE_SELECTOR(COwnerTetrisLayer::OnUpdateBlockDown), this, 2, false);
}

void COwnerTetrisLayer::OnUpdateBlockDown(float dt)
{
	if (m_nGameState != kPlay)
	{
		return;
	}

	CGameBoard::DownBlockResult ret = m_pGameBoard->MoveBlockDown();
	if (ret == CGameBoard::DownBlockResult::Dropped)
	{
		m_pGameBoard->CheckLineClear();
		__UpdateDropBlock();
	}
	//변화가 없다면 굳이? 전체를
	UpdateCellTexture();
}



void COwnerTetrisLayer::OnUpdate(float dt)
{
	if (m_nGameState != kPlay)
	{
		return;
	}
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


void COwnerTetrisLayer::ResetAllTimer()
{
	m_nUpdateCnt = 0;
	m_nUpdateCntTotal = 0;
	m_nUpdatePerTime = 20;
	m_bMovingDownDeadLine = false;
}


void COwnerTetrisLayer::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
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

void COwnerTetrisLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (m_nGameState == kPlay)
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
}


void COwnerTetrisLayer::OnEffectEnd(int nEndState)
{
	switch (m_nGameState)
	{
	case kPrepare:
		if (m_bChangeGameState)
		{
			m_pGameResultEffect->SetState(kReady);
			m_pGameResultEffect->PlayEffect(std::bind(&COwnerTetrisLayer::OnEffectEnd, this, std::placeholders::_1));

			m_nGameState = kReady;
		}
		break;
	case kReady:
		{
		//원래는 이떄 서버로 요청보내기해야함!!!
			m_pGameResultEffect->Clear();
			m_nGameState = kPlay;
		}
		break;
	default:
		break;
	}
}

void OnEffectEnd(int nEffectType)
{

}