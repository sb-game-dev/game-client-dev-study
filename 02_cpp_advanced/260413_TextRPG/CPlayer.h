#pragma once
#include "Define.h"

class CPlayer
{
public:
	enum JobIndex{WARRIOR = 1,MAGE,THIEF,LOADDATA};
public:
	CPlayer();
	~CPlayer();
public:
	void Initailize();
	void Render();
	void TakeDamage(int iNum) { m_tInfo.iHp -= iNum; }
	Info GetInfo() { return m_tInfo; }
	void Heal(int iNum) { m_tInfo.iHp = iNum; }
	void SaveData();
	void LoadData();
private:
	Info m_tInfo;
};

