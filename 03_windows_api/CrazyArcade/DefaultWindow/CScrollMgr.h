#pragma once

#include "Define.h"

class CScrollMgr
{
private:
	CScrollMgr();
	CScrollMgr(const CScrollMgr& rhs) = delete;
	CScrollMgr& operator = (CScrollMgr& rCLineMgr) = delete;
	~CScrollMgr();

public:
	float	GetScrollX() { return m_fScrollX; }
	float	GetScrollY() { return m_fScrollY; }

	void	SetScrollX(float fX) { m_fScrollX += fX; }
	void	SetScrollY(float fY) { m_fScrollY += fY; }

public:
	static CScrollMgr* GetInstance()
	{
		if (!m_pInstance)
			m_pInstance = new CScrollMgr;
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
	static CScrollMgr* m_pInstance;

	float		m_fScrollX;
	float		m_fScrollY;
};

