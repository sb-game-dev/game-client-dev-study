#pragma once
template<typename T>
void Safe_Delete(T& p)
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

enum ITEMTYPE { WEAPON, ARMOR, IT_END };
enum ITEMCLASS { NORMAL, MAGIC, RARE, IC_END };
enum ITEMSTATE { UNEQUP, EQUIP, IS_END };