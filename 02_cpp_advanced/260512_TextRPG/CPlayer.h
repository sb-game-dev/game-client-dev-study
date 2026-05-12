#pragma once
#include "CObj.h"
#include "CInven.h"
class CPlayer:public CObj
{
private:
	enum JOBINDEX { WARRIOR = 1, MAGE, THIEF, JOBINDEX_END };
public :
	CPlayer();
	~CPlayer();

public :
	void SelectJob();

	void TakeDamage(int iNum) { m_tInfo.iHp -= iNum; }
	void ChangeMoney(int iNum) { m_tInfo.iMoney += iNum; }
	void SetMoney(int iNum) { m_tInfo.iMoney = iNum; }
	void SetMaxHp(int iNum) { m_tInfo.iMaxHp = iNum; }
	void SetHp(int iNum) { m_tInfo.iHp = iNum; }
	void SetAttack(int iNum) { m_tInfo.iAttack = iNum; }

	void PlayerStat(int iHp, int iAttack);

	void Equip(CObj* pItem);
	void Unequip(CObj* pItem);

	// CObj을(를) 통해 상속됨
	void Render() override;

public:
	CInven& GetInven() { return m_Inven; }

private:
	CInven m_Inven;
	CObj* m_pSlot[IT_END];
};

