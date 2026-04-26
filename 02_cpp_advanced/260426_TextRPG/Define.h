#pragma once
struct Info
{
	char szName[32];
	int iHp, iAttack, iMoney;
};

enum ITEM_TYPE{WEAPON,ARMOR,END_ITEMTYPE};
enum ITEM_CLASS{NORMAL,MAGIC,RARE,END_ITEMCLASS};