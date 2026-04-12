#include "Define.h"
#include "pch.h"
void stPlayer::SetStat(const char tempName[], int tempHp, int tempPower,int tempGold,int tempLevel, int tempItem)
{
	strcpy_s(szName, sizeof(tempName), tempName);
	iHp = tempHp;
	iPower = tempPower;
	iGold = tempGold;
	iLevel = tempLevel;
	iItem = tempItem;
}

void stMonster::SetStat(const char tempName[], int tempHp, int tempPower)
{
	strcpy_s(szName, sizeof(tempName), tempName);
	iHp = tempHp;
	iPower = tempPower;
}

const int iItemColor[] = { 0,8,9,14,12,13 };
const char* szItemRarity[] = { "","Normal","Magic","Rare","Legendary","Unique" };

void setColor(unsigned short text)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text);
}