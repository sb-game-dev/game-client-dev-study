#pragma once
class CGradeCalc;
class CMainGame
{
private:
	enum Menu{ADD=1,RENDER,SEARCH,DELETE,END};
public:
	CMainGame();
	~CMainGame();

public:
	void Initialize();
	void Update();
	void Release();

private:
	CGradeCalc* m_pGradeCalc;
};

