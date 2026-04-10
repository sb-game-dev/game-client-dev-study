#pragma once
class CPlayer
{
private:
	char m_szName[32];
	int m_iHp;
	int m_iPower;
	int m_iLevel = 1;
	int m_iGold = 0;
	int m_iItem = 0;
public:
	void SetName(const char cTemp[]);
	char* GetName();
	void SetHp(int);
	int GetHp();
	void SetPower(int);
	int GetPower();
	void SetLevel(int);
	int GetLevel();
	void SetGold(int);
	int GetGold();
	void SetItem(int);
	int GetItem();
public:
	void PrintPlayer();
	void SelectJob(CPlayer** ppPlayer);
	void CreatePlayer(const char szName[], int iHp, int iPower);
	void SavePlayer();
	void LoadPlayer(CPlayer* ppPlayer);
	void EnemyAttack(int iPower);
};

enum Job
{
	Warrior = 1,
	Mage,
	Thief,
	LastJob,
	End
};

