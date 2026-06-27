#pragma once

#include "Define.h"
#include "CObj.h"
class CTimer
{
public:
	CTimer();
	CTimer(const CTimer* rhs) = delete;
	CTimer& operator=(const CTimer* rhs) = delete;
	~CTimer();

public:
	void	Initialize();
	void	Update();
	void	Render(HDC hDC);

	int		GetSec() { return m_iSec; }

public:
	static CTimer* GetInstance()
	{
		if (!m_pInstance)
			m_pInstance = new CTimer;
		return m_pInstance;
	}
	static void Destroy()
	{
		Safe_Delete(m_pInstance);
	}
private:
	static CTimer*	m_pInstance;
	ULONGLONG		m_dwTimer;
	int				m_iSec;
};

