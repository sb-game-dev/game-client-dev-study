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
enum MainGameMenu{FIELD =1,STORE,INVENTORY,GAME_EXIT,END_GAME_MENU};
enum JobIndex{WARRIOR = 1,MAGE,THIEF,END_JOBINDX};
enum MonsterLevel{LOW_LEVLE=1,MID_LEVEL,HIGH_LEVEL,END_MONSTERLEVEL};

enum ItemType{WEAPON,ARMOR,END_IT};
enum ItemClass{NORMAL,MAGIC,RARE,END_IC};

enum StoreMenu {BUY=1,SELL,STORE_EXIT,END_STORE_MENU};