#pragma once
#include "Define.h"
class CStartEffect
{
public:
	CStartEffect();
	CStartEffect(const CStartEffect* rhs) = delete;
	CStartEffect& operator=(const CStartEffect* rhs) = delete;
	~CStartEffect();

public:
	void	Initialize();
	void	Update();
	void	Render(HDC hDC);


public:
	void	SetEffectRunning(bool bRunning) { m_bEffectRunning = bRunning; }
	bool	GetEffectRunning() { return m_bEffectRunning; }

public:
	static CStartEffect* GetInstance()
	{
		if (!m_pInstance)
			m_pInstance = new CStartEffect;
		return m_pInstance;
	}
	static void Destroy()
	{
		Safe_Delete(m_pInstance);
	}
private:
	static CStartEffect*	m_pInstance;

	float	m_fSpeed;

	float	m_fTop1;
	float	m_fTop2;
	float	m_fTop3;
	float	m_fTop4;
	float	m_fTop5;
	float	m_fTop6;
	float	m_fTop7;

	bool	m_bEffectRunning;
	float	m_fCnt;
};

