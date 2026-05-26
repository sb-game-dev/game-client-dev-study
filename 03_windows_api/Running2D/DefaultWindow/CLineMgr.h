#pragma once
#include "CLine.h"
class CLineMgr
{
private:
	CLineMgr();
	CLineMgr(const CLineMgr& rhs) = delete;
	CLineMgr& operator = (CLineMgr& rCLineMgr) = delete;
	~CLineMgr();

public:
	bool	SetLine(float fPlayerX, float& fPlayerY,float fPrevX = 0, float fPrevY = 0);
	bool	SetRopeLine(float& fPlayerX, float fPlayerY);

	bool	CheckDownJumpLine(float fX, float pY, CLine* pLine);
	CLine*	FindCurrentLine(float fPlayerX, float fPlayerY);

public:
	void	Initialize();
	void	Render(HDC hDC);
	void	Release();

public:
	static CLineMgr* GetInstance()
	{
		if (!m_pInstance)
			m_pInstance = new CLineMgr;
		return m_pInstance;
	}

	static void DestroyInstance()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;
		}
	}
private:
	static CLineMgr*	m_pInstance;
	list<CLine*>		m_LineList;
	list<CLine*>		m_RopeList;
};

