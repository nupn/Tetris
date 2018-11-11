#pragma once
#include "cocos2d.h"
#include "../proj.win32/GameBoard.h"
#include "../proj.win32/BlockProductor.h"
#include "../proj.win32/GameStateFontEffect.h"
#include "../proj.win32/BasicTetrisLayer.h"
#include "NextBlockView.h"

class CRemoteTetrisLayer : public cocos2d::Layer
{
public:
	//���� �ѱ��
	//�������� ó�� �߷¹��������� �������ֱ�
	//������ �ֱ� �����̽� �� ���� ��� �������°�
	//ȸ���߿� ������ �������°� �����ϱ�
	enum
	{
		kPrepare,
		kReady,
		kPlay,
		kResult,
	};


	enum
	{
		kGameResultLose = 0,
		kGameResultWin
	};

public:
	CREATE_FUNC(CRemoteTetrisLayer);
	CRemoteTetrisLayer();
	~CRemoteTetrisLayer();

	virtual bool init() override;

	void UpdateCellTexture();
	bool IsDropBlockDeadLine();
	
	void OnEffectEnd(int nEndState);
	
//�Է�
	bool OnCreateBlock(CDropBlock::BlockType nBlockType);
	bool OnBlinkBlock(CDropBlock& droppedBlock);

private:
	CGameBoard* m_pGameBoard = nullptr;
	CGameStateFontEffect* m_pGameResultEffect = nullptr;

	int m_nGameState = kPrepare;
	bool m_bChangeGameState = false;
};

