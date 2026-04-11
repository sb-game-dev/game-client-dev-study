#pragma once
#include "CPlayer.h"
#include "CField.h"
#include "CShop.h"
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
	CPlayer* Player;
	CField* Field;
	CShop* Shop;
};

