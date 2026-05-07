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

enum JOBINDEX { WARRIOR = 1, MAGE, THIEF, JOBINDX_END };
enum ITEMTYPE { WEAPON, ARMOR, IT_END };
enum ITEMCLASS { NORMAL, MAGIC, RARE, IC_END };
enum ITEMEQUIP { EQUIP, UNEQUIP, IE_END };