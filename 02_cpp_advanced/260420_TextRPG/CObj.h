#pragma once
class CObj
{
public:
	CObj();
	~CObj();

public:
	int GetHp() { return m_iHp; }
	int GetAttack() { return m_iAttack; }
	void Heal(int iNum) { m_iHp = iNum; }
	void TakeDamage(int iNum) { m_iHp -= iNum; }
	void Render();
protected:
	char m_szName[32];
	int m_iHp;
	int m_iAttack;
};

