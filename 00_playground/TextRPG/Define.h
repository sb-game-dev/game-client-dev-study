#pragma once
#include "pch.h"
#define SAFE_DELETE(p) {delete p;p = nullptr;}
#define SAFE_DELETE_ARRAY(p) {delete[] p;p = nullptr;}
#define SystemMessage(Message){cout<<Message<<endl;system("pause");}

//const int iItemColor[] = { 0,8,9,14,12,13 };
//const char* szItemRarity[] = { "","Normal","Magic","Rare","Legendary","Unique" };

struct stPlayer
{
	char szName[32];
	int iHp;
	int iPower;
	int iGold ;
	int iLevel;
	int iItem;
	void SetStat(const char tempName[], int tempHp, int tempPower, int tempGold, int tempLevel, int tempItem);
};

struct stMonster
{
	char szName[32];
	int iHp;
	int iPower;
	//int iGold = 0;
	//int iLevel = 1;
	//int iItem = 1;
	void SetStat(const char tempName[], int tempHp, int tempPower);
};
