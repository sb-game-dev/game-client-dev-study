#pragma once
#include "Define.h"
class CMonster
{
public:
	CMonster();
	~CMonster();
public:
	void Initialize(int iLevel);
	void Update();
	void Release();
public:
	int GetHp(); 
	int GetPower(); 
private:
	stMonster* Monster;
public:
	void CreateMonster(int iLevel);
	void TakeDamage(int iEnemyDamage);
	void PrintInfo();
};

