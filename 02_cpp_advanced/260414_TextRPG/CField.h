#pragma once
class CPlayer;
class CMonster;
class CField
{
public:
	CField();
	~CField();

public:
	void Initialize();
	void Update();
	void Release();
	void SetPlayer(CPlayer* pPlayer) { m_copyPlayer = pPlayer; }
	int Battle();
private:
	CPlayer* m_copyPlayer;
	CMonster* m_pMonster;
};

