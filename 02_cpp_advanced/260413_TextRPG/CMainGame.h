#pragma once
#include "pch.h"
class CPlayer;
class CField;

class CMainGame
{
public:
	CMainGame();
	~CMainGame();
public:
	void Initialize();
	void Update();
	void Release();
private:
	CPlayer* m_pPlayer;
	CField* m_pField;
};

