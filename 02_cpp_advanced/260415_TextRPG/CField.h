#pragma once
class CPlayer;
class CMonster;

class CField
{
private:
	CField();
	~CField();
public:
	void Initialize();
	void Update();
	void Release();
public:
	static CField* Create();
	void Destroy();
public:
	void SetPlayer(CPlayer* pPlayer) { m_copyPlayer = pPlayer; }

private:
	CPlayer* m_copyPlayer;
	CMonster* m_pMonster;
};

