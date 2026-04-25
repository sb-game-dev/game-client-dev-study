#pragma once
#include "CObj.h"
class CPlayer :public CObj
{
public:
	CPlayer();
	~CPlayer();
	enum JOBINDEX{WARRIOR=1,MAGE,THIEF,END_JOB};
public:
	void Initialize();
	void SetHp(int iNum) { m_tInfo.iHp = iNum; };
	void SetMoney(int iNum) { m_tInfo.iMoney = iNum; }
	void SetAttack(int iNum) { m_tInfo.iAttack = iNum; }
	void Render() override;
};

