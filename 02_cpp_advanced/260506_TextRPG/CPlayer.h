#pragma once
#include "CObj.h"
#include "CInventory.h"
class CPlayer :public CObj
{
private:
	enum JobIndex { WARRIOR = 1, MAGE, THIEF, END_JOBINDEX };
public :
	CPlayer();
	~CPlayer();
public :
	void SelectJob();
	void Render() override;

	void SetAttack(int iNum) { m_tInfo.iAttack = iNum; }
	void SetMaxHp(int iNum) { m_tInfo.iMaxHp = iNum; }
	void SetHp(int iNum) { m_tInfo.iHp = iNum; }


	void SetMoney(int iNum) { m_tInfo.iMoney = iNum; }
	void TakeDamage(int iNum) { m_tInfo.iHp -= iNum; }

	void InvRender() { m_Inventory.Render(); }
	void InvUpdate() { m_Inventory.Update(); }
	bool InvAddItem(CObj* pItem) {return m_Inventory.AddItem(pItem); }
	int InvDeleteItem(int iIndex) { return m_Inventory.DeleteItem(iIndex); }
	int GetWeaponSlot() { return m_Inventory.GetWeaponSlot(); }
	int GetArmorSlot() { return m_Inventory.GetArmorSlot(); }

private:
	CInventory m_Inventory;
};

