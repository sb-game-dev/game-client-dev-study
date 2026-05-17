#pragma once
#include "CPlayer.h"
#include "CMonster.h"
#include "CBullet.h"
#include "Define.h"
class CMainGame
{
public :
	CMainGame();
	~CMainGame();

public:
	void Initialize();
	void Update();
	void Render();
	void Release();

private:
	HDC m_hDC;

	CObj* m_pPlayer;
	CObj* m_pMonster;
	list<CObj*> m_BulletList;
};

