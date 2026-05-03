#pragma once
class CObj;
class CField;
class CStore;
class CInventory;

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
	CStore* m_pStore;
	CInventory* m_pInventory;
};

