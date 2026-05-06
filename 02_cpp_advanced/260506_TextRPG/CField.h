#pragma once
class CObj;
class CField
{
private:
	enum MonsterLevel { LOW = 1, MID, HIGH, END_MONSTERLEVEL };
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

