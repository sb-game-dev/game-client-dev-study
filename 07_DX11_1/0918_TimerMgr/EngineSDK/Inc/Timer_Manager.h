#pragma once

#include "Engine_Defines.h"

NS_BEGIN(Engine)

class ENGINE_DLL CTimer_Manager
{
	DECLARE_SINGLETON(CTimer_Manager)

private:
	explicit CTimer_Manager();
	virtual ~CTimer_Manager();

public:
	f32_t			Get_TimeDelta(const wstring_t& strTimerTag);
	void			Set_TimeDelta(const wstring_t& strTimerTag);

public:
	HRESULT			Ready_Timer(const wstring_t& strTimerTag);


private:	
	map<const wstring_t, shared_ptr<class CTimer>>		m_Timers;

private:
	shared_ptr<CTimer> Find_Timer(const wstring_t& strTimerTag);

private:
	virtual void		Free();
};

NS_END