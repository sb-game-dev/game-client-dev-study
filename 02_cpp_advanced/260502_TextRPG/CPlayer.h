#pragma once
#include "CObj.h"
class CPlayer:public CObj
{
private:
	enum JOBINDEX{WARRIOR=1,MAGE,THIEF,END_JOBINDX};
public:
	CPlayer();
	~CPlayer();

public:
	void SelectJob();
	void TackDamage(int iNum) { m_tInfo.iHp -= iNum; }
	void SetMaxHp(int iNum) { m_tInfo.iMaxHp = iNum; }
	void Heal(int iNum) { m_tInfo.iHp = iNum; }
	void SetMoney(int iNum) { m_tInfo.iMoney = iNum; }
	void SetAttack(int iNum) { m_tInfo.iAttack = iNum; }

public:
	void Render() override;

};

