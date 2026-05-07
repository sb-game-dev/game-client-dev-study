#pragma once
#include "CObj.h"
class CItem:public CObj
{
public:
	CItem(const char* szName, int iHp, int iAttack, int iMoney,ITEMTYPE IT );
	CItem(const CObj& rhs);
	~CItem();

public:
	void Render() override;

	ITEMTYPE GetType() { return eType; }
	ITEMEQUIP GetEquip() { return eEquip; }
	void SetItemEquip(ITEMEQUIP IE) { eEquip = IE; }

private:
	ITEMTYPE eType;
	ITEMEQUIP eEquip;
};

