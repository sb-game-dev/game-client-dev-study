#pragma once
#include "CObj.h"
#include "Define.h"
class CPlayer:public CObj
{
public:
	CPlayer();
	~CPlayer();

public:
	void Render()override;
	void SelectJob();

	void TakeDamage(int iNum) { m_tInfo.iHp -= iNum; }
	void SetHp(int iNum) { m_tInfo.iHp = iNum; }
	void AddMoney(int iNum) { m_tInfo.iMoney += iNum; }

	void itemAbility(int&& iHp, int&& iAttack);
	void Equip(CObj* pitem);
	void UnEquip(CObj* pitem);
private:
	CObj* m_pItemSlot[IT_END];

};

