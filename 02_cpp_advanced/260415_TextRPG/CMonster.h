#pragma once
#include "Define.h"
class CMonster
{
private:
	CMonster(const char szName[], int iHp, int iAttack);
	~CMonster();

public:
	void Initialize();
	void Update();
	void Release();
	void Render()const;
	void TakeDamage(int iNum) { m_tInfo.iHp -= iNum; }
	Info GetInfo() { return m_tInfo; }
public:
	static CMonster* Create(const char szName[], int iHp, int iAttack);
	void Destroy();
private:
	Info m_tInfo;
};

