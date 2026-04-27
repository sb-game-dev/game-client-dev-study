#pragma once
#include "CObj.h"
class CPlayer :public CObj
{
private :
	enum JOBINDEX {WARRIOR = 1,MAGE,THIEF,END_JOBINDEX};
public:
	void Render() override;
	void TakeDamage(int iNum) { m_tInfo.iHp -= iNum; }
	void Heal(int iNum) { m_tInfo.iHp = iNum; }
	void SelectJob();
};
