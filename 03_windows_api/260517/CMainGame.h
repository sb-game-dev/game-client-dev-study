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
	void LateUpdate();

private:
	void CollisionCheck(list<CObj*> , list<CObj*>);

private:
	HDC m_hDC;
	list<CObj*> m_ObjList[OBJ_END];
	int m_iFPS;
	DWORD m_dwTime;
	TCHAR m_szFPS[32];
};

