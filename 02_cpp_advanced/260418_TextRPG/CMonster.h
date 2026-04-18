#pragma once
#include "CObj.h"
class CMonster:public CObj
{
private:
	CMonster(const char szName[], int iHp, int iAttack);
	~CMonster();
public:
	static CMonster* Create(const char szName[], int iHp, int iAttack);
	void Destroy();
};

