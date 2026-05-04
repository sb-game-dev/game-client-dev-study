#pragma once
#include "CObj.h"
class CPlayer:public CObj
{
public:
	CPlayer();
	~CPlayer();

public:
	void Render() override;

public:
	void SetHp(int iNum) { m_tInfo.iHp = iNum; }
	void SetMaxHp(int iNum) { m_tInfo.iMaxHp = iNum; }
	void SetMoney(int iNum) { m_tInfo.iMoney = iNum; }
	void SetAttack(int iNum) { m_tInfo.iAttack = iNum; }
	void TakeDamage(int iNum) { m_tInfo.iHp -= iNum; }

public:
	void SelectJob();
};

