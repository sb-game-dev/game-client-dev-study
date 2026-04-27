#pragma once
#include "CObj.h"
class CItem:public CObj
{
public:
	CItem(const char* szName,int iHp,int iAttack, int iMoney );
	~CItem() {}

public:
	void Render() override;
};

