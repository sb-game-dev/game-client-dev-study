#pragma once
#include "CObj.h"
class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void Initialize();
	void Update();
	void LateUpdate();
	void Render();
	void Release();
private:
	void CollisionCheck(list<CObj*> ObjList1, list<CObj*> ObjList2);
private:
	HDC m_hDC;
	list<CObj*> m_ObjList[OBJ_END];
};

