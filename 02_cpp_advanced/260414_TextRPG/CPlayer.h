#pragma once
#include "Define.h"
class CPlayer
{
public:
	enum JOBINDEX { WARRIOR = 1, MAGE, THEIF, LOADDATA };
public:
	CPlayer();
	~CPlayer();
public:
	void Initialize();
	void Update();
	void Release();
	void Render();
	Info SetInfo() { return m_tInfo; }
	void TakeDamage(int iNum) { m_tInfo.iHp -= iNum; }
	void Heal(int iNum) { m_tInfo.iHp = iNum; }
public:
	Info m_tInfo;
};

