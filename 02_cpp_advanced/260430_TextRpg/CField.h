#pragma once
class CObj;
class CField
{
public:
	CField();
	~CField();

public:
	void Update();
	void SetPlayer(CObj* pPlayer) { m_pPlayer = pPlayer; }

private:
	CObj* m_pPlayer;
	CObj* m_pMonster;
	int Battle();
};

