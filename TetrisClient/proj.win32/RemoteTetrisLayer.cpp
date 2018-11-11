#include "RemoteTetrisLayer.h"

using namespace cocos2d;

CRemoteTetrisLayer::CRemoteTetrisLayer()
{
}


CRemoteTetrisLayer::~CRemoteTetrisLayer()
{
}

//http://cocos2dx.tistory.com/entry/CCSpriteBatchNode-%EC%82%AC%EC%9A%A9%EB%B2%95-cocos2dx
bool CRemoteTetrisLayer::init()
{
	m_pGameBoard = CGameBoard::create("Tetris/remotesource.png", 12);
	addChild(dynamic_cast<Sprite*>(m_pGameBoard));

	m_pGameResultEffect = CGameStateFontEffect::create();
	m_pGameResultEffect->setAnchorPoint(Vec2::Vec2(0.5, 0.5));
	m_pGameResultEffect->setPosition(Vec2::Vec2(60, 120));
	addChild(m_pGameResultEffect);

	m_nGameState = kPlay;

	//CDropBlock::BlockType nType = m_BlockProductor.GetBlock(0);
	m_pGameBoard->ResetDropBlock(CDropBlock::BlockType::kBlockTypeRSlide);
	m_pGameBoard->SetShadowBlockVisible(false);

	return cocos2d::Layer::init();
}

void CRemoteTetrisLayer::UpdateCellTexture()
{
	m_pGameBoard->UpdateDisplay();
}

bool CRemoteTetrisLayer::IsDropBlockDeadLine()
{
	return m_pGameBoard->IsDeadLine();
}

void CRemoteTetrisLayer::OnEffectEnd(int nEndState)
{
	switch (m_nGameState)
	{
	case kPrepare:
		if (m_bChangeGameState)
		{
			m_pGameResultEffect->SetState(kReady);
			m_pGameResultEffect->PlayEffect(std::bind(&CRemoteTetrisLayer::OnEffectEnd, this, std::placeholders::_1));

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

bool CRemoteTetrisLayer::OnCreateBlock(CDropBlock::BlockType nBlockType)
{
	bool ret = m_pGameBoard->ResetDropBlock(nBlockType);
	m_pGameBoard->UpdateDisplay();

	return ret;
}

bool CRemoteTetrisLayer::OnBlinkBlock(CDropBlock& droppedBlock)
{
	if (m_pGameBoard == nullptr)
	{
		return false;
	}

	bool ret = m_pGameBoard->BlinkBlock(droppedBlock);
	if (ret)
	{
		m_pGameBoard->CheckLineClear();
		m_pGameBoard->UpdateDisplay();
	}

	return ret;
}
