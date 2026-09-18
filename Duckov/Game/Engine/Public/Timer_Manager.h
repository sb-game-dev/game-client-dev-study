#pragma once

#include "Engine_Define.h"

NS_BEGIN(Engine)
class CTimer;

class ENGINE_DLL CTimerMgr
{
	DECLARE_SINGLETON(CTimerMgr)

private:
	explicit CTimerMgr();
	virtual ~CTimerMgr();

public:
	f32_t							Get_TimeDelta(const tchar_t* pTimerTag);
	void							Set_TimeDelta(const tchar_t* pTimerTag);

public:
	HRESULT							Ready_Timer(const tchar_t* pTimerTag);

private:
	shared_ptr<class CTimer>			Find_Timer(const tchar_t* pTimerTag);

private:
	map<const wstring_t, shared_ptr<class CTimer>>		m_mapTimers;

private:
	virtual void		Free();
};

NS_END