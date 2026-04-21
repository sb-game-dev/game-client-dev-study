#pragma once
#define SAFEDELETE(p) if(p){delete p;p = nullptr;}
struct Info
{
	char szName[32];
	int iHp, iAttack, iGold;
};

enum ItemType { IT_WEAPON, IT_ARMOR, IT_END };
enum ItemClass { IC_NORMAL, IC_MAGIC, IC_RARE, IC_END };
