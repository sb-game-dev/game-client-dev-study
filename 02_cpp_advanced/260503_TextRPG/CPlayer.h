#pragma once
#include "CObj.h"
#include "CInventory.h"
class CPlayer:public CObj
{
public:
	CPlayer();
	~CPlayer();

public:
	void SeletJob();
	void SetMaxHp(int iNum) { m_tInfo.iMaxHp = iNum; }
	void SetHp(int iNum) { m_tInfo.iHp = iNum; }
	void SetMoney(int iNum) { m_tInfo.iMoney = iNum; }
	void SetAttack(int iNum) { m_tInfo.iAttack = iNum; }
	void TackDamage(int iNum) { m_tInfo.iHp -= iNum; }

	void Render() override;
	void RenderInventory() { m_pInventory.Render(); }

public:
	void Release();

public:
	bool AddItem(const CObj* pItem);
	void SellItem(int iIndex);
	void SetItem();

private:
	CInventory m_pInventory;
};

