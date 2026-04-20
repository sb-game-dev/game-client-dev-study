#pragma once
#include "CObj.h"
class CPlayer:public CObj
{
public:
	CPlayer();
	~CPlayer();
private:
	enum JOBINDEX{WARRIOR = 1,MAGE,THIEF,JOBIDEX_END};
public:
	void SelectJob();
	void Heal(int iNum) { m_tInfo.iHp = iNum; }
};

