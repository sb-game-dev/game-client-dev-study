#pragma once
#include "Engine_Define.h"

NS_BEGIN(Engine)
class CTimer
{
private:
	CTimer();
public:
	~CTimer();

public:
	f32_t				Get_TimeDelta() const { return m_fTimeDelta; }

public:
	HRESULT				Ready_Timer();
	void				Update_Timer();

private:
	LARGE_INTEGER		m_FrameTime;
	LARGE_INTEGER		m_FixTime;
	LARGE_INTEGER		m_LastTime;

	LARGE_INTEGER		m_CpuTick;

	f32_t				m_fTimeDelta;

public:
	static shared_ptr<class Timer> Create();
private:
	virtual void	Free();
};

NS_END
