#pragma once
#include "CObj.h"
class CItem:public CObj
{
public:
	CItem() {};
	CItem(const char * szName , int iHp, int iAttack, int iMoney);
	CItem(const CObj& rhs);
	~CItem();

public:
	void Render() override;
	Info GetInfo() override { return m_tInfo; };
};

