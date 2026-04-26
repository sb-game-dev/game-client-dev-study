#pragma once
#include "CObj.h"
class CPlayer:public CObj
{
public:
	CPlayer() {};
	~CPlayer() {};
private:
	enum JOBINDEX{WARRIOR=1,MAGE,THIEF,END_JOBIDEX};
public:
	void Render() override;
	void TakeDamage(int iNum) override { m_tInfo.iHp -= iNum; }
	void Heal(int iNum) { m_tInfo.iHp = iNum; }
public:
	void SelectJob();
};

