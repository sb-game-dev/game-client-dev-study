#pragma once
class CObj;
class CField;
class CShop;
class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	void Initialize();
	void Update();
	void Release();

private:
	CObj* m_pPlayer;
	CField* m_pField;
	CShop* m_pShop;
};

