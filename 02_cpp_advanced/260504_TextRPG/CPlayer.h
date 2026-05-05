#pragma once
#include "CObj.h"
#include "CInventory.h"
class CPlayer:public CObj
{
public:
	CPlayer();
	~CPlayer();

public:
	void Render() override;

public:
	void SetHp(int iNum) { m_tInfo.iHp = iNum; }
	void SetMaxHp(int iNum) { m_tInfo.iMaxHp = iNum; }
	void SetMoney(int iNum) { m_tInfo.iMoney = iNum; }
	void SetAttack(int iNum) { m_tInfo.iAttack = iNum; }
	void TakeDamage(int iNum) { m_tInfo.iHp -= iNum; }

public:
	void InvRender() { m_Inventorty.Render(); }
	void InvUpdate() { m_Inventorty.Update(); }
	bool InvAddItem(CObj* pItem) { return m_Inventorty.AddItem(pItem); }
	int InvDeleteItem(int iIndex) { return m_Inventorty.DeleteItem(iIndex); }

public:
	void SelectJob();
private:
	CInventory m_Inventorty;
};

