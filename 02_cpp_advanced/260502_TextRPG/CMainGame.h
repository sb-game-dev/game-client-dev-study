#pragma once
class CObj;
class CField;
class CStore;
class CInventory;
class CMainGame
{
private:
	enum MENUINDEX{FIELD=1,STORE,INVENTORY,GAMEOVER,END_MENU};
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
	CInventory* m_pInventory;
};

