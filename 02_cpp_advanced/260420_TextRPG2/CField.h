#pragma once
class CObj;
class CField
{
public:
	CField();
	~CField();
public:
	void SetPlayer(CObj* pPlayer) { m_pCopyPlayer = pPlayer; }
	void Update();
private:
	CObj* m_pCopyPlayer;
	CObj* m_pMonster;

	int Battle();
};

