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

public:
	void CollisonCheck(list<CObj*> &ObjList_1, list<CObj*> &ObjList_2);

private:
	HDC m_hDC;
	list<CObj*> m_ObjList[OBJ_END];
};

