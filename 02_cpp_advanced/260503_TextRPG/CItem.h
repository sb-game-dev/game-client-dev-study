#pragma once
#include "CObj.h"
class CItem:public CObj
{
public:
	CItem(const char* szName, int iHp, int iAttack, int iMoney);
	CItem(const CObj& rhs);
	~CItem();

public:


	// CObj을(를) 통해 상속됨
	void Render() override;

};

