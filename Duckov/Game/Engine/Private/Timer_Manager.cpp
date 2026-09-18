#include "Timer_Manager.h"
#include "Timer.h"
IMPLEMENT_SINGLETON(CTimerMgr)

CTimerMgr::CTimerMgr()
{
}

CTimerMgr::~CTimerMgr()
{
	Free();
}

f32_t CTimerMgr::Get_TimeDelta(const tchar_t* pTimerTag)
{
	CTimer* pTimer = Find_Timer(pTimerTag);
	if (nullptr == pTimer)
		return 0.f;

	return pTimer->Get_TimeDelta();
}

void CTimerMgr::Set_TimeDelta(const tchar_t* pTimerTag)
{
	CTimer* pTimer = Find_Timer(pTimerTag);
	if (nullptr == pTimer)
		return;

	pTimer->Update_Timer();
}

HRESULT CTimerMgr::Ready_Timer(const tchar_t* pTimerTag)
{
	CTimer* pTimer = Find_Timer(pTimerTag);

	if (nullptr != pTimer)
		return E_FAIL;

	pTimer = CTimer::Create();
	if (nullptr == pTimer)
		return E_FAIL;

	m_mapTimer.insert({ pTimerTag, pTimer });

	return S_OK;
}

shared_ptr<class CTimer> CTimerMgr::Find_Timer(const tchar_t* pTimerTag)
{
	auto		iter = find_if(m_mapTimer.begin(),
								m_mapTimer.end(),
								CTag_Finder(pTimerTag));

	if (iter == m_mapTimer.end())
		return nullptr;

	return iter->second;
}

void CTimerMgr::Free()
{

}
