#pragma once
#include "Define.h"
#include "CPlayer.h"
#include "CBullet.h"
#include "CMonster.h"
class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void Initialize();
	void Update();
	void Render();
	void Release();

private:
	HDC				m_hDC;
	CObj*			m_pPlayer;
	CObj*			m_pMonster;

	list<CObj*>		m_BulletList;
};

