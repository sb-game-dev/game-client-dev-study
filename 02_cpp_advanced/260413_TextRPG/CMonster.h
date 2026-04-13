#pragma once
#include "Define.h"

class CMonster
{
public:
	CMonster(const char TempName[], int iTempHp, int iTempAttack);
	~CMonster();

public:
	void Release();
	void TakeDamage(int iNum) {m_tInfo.iHp -= iNum;}
	void Render();
	Info GetInfo() { return m_tInfo; }
private:
	Info m_tInfo;
};

