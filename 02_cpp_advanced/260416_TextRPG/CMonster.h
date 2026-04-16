#pragma once
#include "Define.h"
class CMonster
{

private:
	CMonster(const char szName[],int iHp, int iAttack);
	~CMonster();

public:
	void Initialize();
	void Release();

public:
	static CMonster* Create(const char szName[], int iHp, int iAttack);
	void Destroy();
	void Render() const;
	Info GetInfo() const {return m_tInfo;}
	void TakeDamage(int iNum) { m_tInfo.iHp -= iNum; }

private:
	Info m_tInfo;
};

