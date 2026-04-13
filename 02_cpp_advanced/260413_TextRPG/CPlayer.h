#pragma once
#include "Define.h"

class CPlayer
{
public:
	enum JobIndex{WARRIOR = 1,MAGE,THIEF};
public:
	CPlayer();
	~CPlayer();
public:
	void Initailize();
	void Render();
	void TakeDamage(int iNum) { m_tInfo.iHp -= iNum; }
	Info GetInfo() { return m_tInfo; }
	void Heal(int iNum) { m_tInfo.iHp = iNum; }
private:
	Info m_tInfo;
};

