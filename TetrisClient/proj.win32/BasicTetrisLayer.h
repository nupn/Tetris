#pragma once
#include "cocos2d.h"
#include "../proj.win32/GameBoard.h"
#include "../proj.win32/BlockProductor.h"
#include "../proj.win32/GameStateFontEffect.h"

class BasicTetrisLayer : public cocos2d::Layer
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



public:
	BasicTetrisLayer();
	~BasicTetrisLayer();

private:

	CGameBoard* m_pGameBoard = nullptr;

};

