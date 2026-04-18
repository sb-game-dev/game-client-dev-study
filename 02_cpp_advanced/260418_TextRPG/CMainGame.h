#pragma once
class CPlayer;
class CField;
class CShop;
class CObj;
class CMainGame
{
private:
	CMainGame();
	~CMainGame();

public:
	void Initialize();
	void Update();
	void Release();

	static CMainGame* Create();
	void Destroy();

private:
	CPlayer* m_pPlayer;
	CField* m_pField;
	CShop* m_pShop;
};

