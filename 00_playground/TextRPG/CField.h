#pragma once
#include "CMonster.h"
#include "CPlayer.h"
class CField
{
public:
	CField();
	~CField();
public:
	void Initialize(CPlayer* pPlayer);
	void Update(CPlayer** ppPlayer);
	void Release();
private:
	CMonster* Monster;
public:
	void Battle(CPlayer** ppPlayer);
};

