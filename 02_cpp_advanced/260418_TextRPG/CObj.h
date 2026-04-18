#pragma once
class CObj
{
protected:
	CObj();
	~CObj();
public:
	void Initialize();
	void Update();
	void Release();

	static CObj* Create();
	void Destroy();
	void TakeDamage(int iNum) { m_iHp -= iNum; }
	void Render();
	
	int GetHp() { return m_iHp; }
	int GetAttack() { return m_iAttack; }
	void SetHp(int iNum) { m_iHp = iNum; }


protected:
	char m_szName[32];
	int m_iHp;
	int m_iAttack;

};

