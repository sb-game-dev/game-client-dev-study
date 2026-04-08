#pragma once
#include "pch.h"

struct Monster
{
	char szName[32];
	int iHp, iPower;
};

void PrintMonsterStat(Monster*);
Monster* CreateMonster(int iNum);