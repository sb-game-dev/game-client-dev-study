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

	static CField* Create();
	void Destroy();

	void SetPlayer(CPlayer* pObj) { m_pCopyPlayer = pObj; }

private:
	CPlayer* m_pCopyPlayer;
	CMonster* m_pMonster;

	int Battle();
};

