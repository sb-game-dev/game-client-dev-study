#pragma once
#include "CObj.h"
class CItem:public CObj
{
public:
	CItem();
	CItem(const char* szName, int iHp, int iAttack,int iMoney);
	~CItem();
public:
	virtual void Render();
};

