#pragma once
#include "CObj.h"
class CMonster:public CObj
{
public:
	CMonster();
	CMonster(const char* szName, int iHp, int iAttack);
	~CMonster();
};

