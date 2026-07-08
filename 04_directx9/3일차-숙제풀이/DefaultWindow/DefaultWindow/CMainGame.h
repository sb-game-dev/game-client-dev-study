#pragma once

#include "Define.h"
#include "CPlayer.h"

class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void		Initialize();
	void		Update();
	void		Render();	// 매 프레임마다 출력하는 코드를 모아놓는 함수
	void		Release();

private:
	HDC				m_hDC;
	CObj*			m_pPlayer;
	CObj*			m_pMonster;
};

// 내적을 이용하여 플레이어를 따라다니는 몬스터를 구현하라.