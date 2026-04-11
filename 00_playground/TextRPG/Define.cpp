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