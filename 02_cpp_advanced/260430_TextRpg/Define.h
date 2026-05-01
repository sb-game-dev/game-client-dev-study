#pragma once
template<typename T>
void SafeDelete(T*& p)
{
	if (p)
	{
		delete p;
		p = nullptr;
	}
}
struct Info
{
	char szName[32];
	int iHp, iAttack, iMoney, iMaxHp;
};

enum ITEMTYPE{WEAPON,ARMOR,END_IT};
enum ITEMCLASS{NORMAL,MAGIC,RARE,END_IC};