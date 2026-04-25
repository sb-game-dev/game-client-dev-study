#pragma once
#define SAFE_DELETE(p) if(p) {delete p;p = nullptr;}
struct Info
{
	char szName[32];
	int iHp;
	int iAttack;
	int iMoney;
};

enum ItemType {WEAPON,ARMOR,END_ITEMTYPE};
enum ItemClass{NORMAL,MAGIC,RARE,END_ITEMCLASS};
