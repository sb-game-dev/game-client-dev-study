#pragma once
#include "CPlayer.h"
class CShop
{
public:
	CShop();
	~CShop();
public:
	void Initialize();
	void Update(CPlayer** ppPlayer);
	void Release();
};

enum Item
{
	Normal = 1,
	Magic,
	Rare,
	Legendary,
	Unique
};