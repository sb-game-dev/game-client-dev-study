#pragma once
#include "Define.h"
class CPlayer
{
public:
	CPlayer();
	~CPlayer();
public:
	void Initialize();
	void Update();
	void Release();
public:

	int GetHp();
	int GetGold();
	int GetItem();
	int GetLevel();
	int GetPower();

	void SetName(const char sTemp[]);
	void SetHp(int iTemp);
	void SetGold(int iTemp);
	void SetItem(int iTemp);
	void SetLevel(int iTemp);
	void SetPower(int iTemp);

private:
	stPlayer* Player;
public:
	void SelectJob();
	void TakeDamage(int iEnemyDamage);
	void PrintInfo();
	void SaveData();
	void LoadInfo();
};

enum Job
{
	Warrior = 1,
	Mage,
	Theif,
	LoadData,
	END
};

