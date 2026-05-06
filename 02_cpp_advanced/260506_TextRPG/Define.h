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