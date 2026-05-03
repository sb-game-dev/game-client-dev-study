#pragma once
class CObj;

class CField
{
public:
	CField();
	~CField();

public:
	void SetPlayer(CObj* pPlayer) { m_pPlayer = pPlayer; }
	void Update();

private:
	int Battle();
private:
	CObj* m_pPlayer;
	CObj* m_pMonster;
};

