#pragma once
class CPlayer;
class CField;

class CMainGame
{
private:
	CMainGame();
	~CMainGame();
public:
	void Initialize();
	void Update();
	void Release();

public:
	static CMainGame* Create();
	void Destroy();
private:
	CPlayer* m_pPlayer;
	CField* m_pField;
};

