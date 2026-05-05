#pragma once
template<typename T>
void SafeDelete(T& p)
{
	if (p)
	{
		delete p;
		p = nullptr;
	}
}
struct Info
{
	int iHp, iMaxHp, iAttack, iMoney;
	char szName[32];
};

enum GameMenu { FIELD = 1, STORE, INVENTORY, END_GAMEMENU };
enum JobIndex { WARRIOR = 1, MAGE, THIEF, END_JOBINDEX };
enum MonsterLevel { LOW = 1, MID, HIGH, END_MONSTERLEVEL };

enum ItemType { WEAPON, ARMOR, END_IT };
enum ItemClass { NORMAL, MAGIC, RARE, END_IC };

enum StoreMenu{BUY=1,SELL,END_STOREMENU};