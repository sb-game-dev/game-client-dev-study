#pragma once
#include "Define.h"
class CMonster
{
public:
	CMonster(const char* tempName,int tempHp,int tempAttack);
	~CMonster();

public:
	void Render();
	Info SetInfo() { return m_tInfo; }
	void TakeDamage(int iNum) { m_tInfo.iHp -= iNum; }
private:
	Info m_tInfo;
};

