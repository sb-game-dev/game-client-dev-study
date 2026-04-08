#pragma once
#include "Item.h"
struct Player
{
	char szName[32];
	int iHp=0, iPower=0, iGold = 0, iLevel = 1, iItemRarity = Normal;
};

void CreatPlayerObj(Player** pPlayer, const char pName[], int iHp, int iPower);
void PrintPlayerStat(Player*);
void SaveInfo(Player* pPlayer);
Player* SelectJob();