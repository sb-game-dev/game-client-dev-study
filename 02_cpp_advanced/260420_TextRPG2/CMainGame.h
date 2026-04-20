#pragma once
class CObj;
class CField;
class CStore;

class CMainGame
{
public:
	CMainGame();
	~CMainGame();
public:
	void Initailze();
	void Update();
	void Release();
private:
	CObj* m_pPlayer;
	CField* m_pField;
	CStore* m_pStore;
};

