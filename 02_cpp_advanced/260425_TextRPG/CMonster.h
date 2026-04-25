#pragma once
#include "CObj.h"
class CMonster:public CObj
{
public:
	CMonster(const char* szName, int iHp, int iAttack);

	// CObj을(를) 통해 상속됨
	void Render() override;
};

