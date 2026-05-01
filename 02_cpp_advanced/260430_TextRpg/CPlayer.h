#pragma once
#include "CObj.h"
class CPlayer:public CObj
{
public:
	CPlayer() {}
	~CPlayer() {}
public:
	void SelectJob();
	void Render();
	Info GetInfo() { return m_tInfo; }
	void TakeDamage(int iNum) { m_tInfo.iHp -= iNum; }
	void Heal(int iNum) { m_tInfo.iHp = iNum; }
	void SetMoney(int iNum) { m_tInfo.iMoney = iNum; }
	void SetMaxHp(int iNum) { m_tInfo.iMaxHp = iNum; }
	void SetAttack(int iNum) { m_tInfo.iAttack = iNum; }
private:
	enum JOBINDEX{WARRIOR=1,MAGE,THIEF,END_JOBINDEX};
};

