#pragma once
class CMonster
{
	char m_szName[32];
	int m_iHp;
	int m_iPower;
	//int m_iLevel = 1;
	//int m_iGold = 0;
	//int m_iItem = 0;
public:
	void SetName(const char cTemp[]);
	char* GetName();
	void SetHp(int);
	int GetHp();
	void SetPower(int);
	int GetPower();
	//void SetLevel(int);
	//int GetLevel();
	//void SetGold(int);
	//int GetGold();
	//void SetItem(int);
	//int GetItem();
public:
	void CreateMonster(const char szName[], int iHp, int iPower);
	void PrintMonster();
	void EnemyAttack(int iPower);
	//void SelectJob(CPlayer** ppPlayer);
	//void SavePlayer(CPlayer** ppPlayer);
	//void LoadPlayer(CPlayer** ppPlayer);
};

