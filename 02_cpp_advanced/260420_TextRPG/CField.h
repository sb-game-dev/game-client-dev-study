#pragma once
class CPlayer;
class CMonster;
class CField
{
private:
	CField();
	~CField();

public:
	void Update();
	static CField* Create();
	void Destroy();
	void SetPlayer(CPlayer* pPlayer) { m_pCopyPlayer = pPlayer; }

private:
	CPlayer* m_pCopyPlayer;
	CMonster* m_pMonster;

public:
	int Battle();
};

