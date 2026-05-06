#pragma once
class CObj;
class CField;
class CStore;
class CMainGame
{
private:
	enum MainMenu { FIELD = 1, STORE, INVENTORY, END_MENU };
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
	CStore* m_pStore;
};

