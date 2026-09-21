#include "Timer_Manager.h"
#include "Timer.h"

IMPLEMENT_SINGLETON(CTimer_Manager)

CTimer_Manager::CTimer_Manager()
{
}

CTimer_Manager::~CTimer_Manager()
{

}

f32_t CTimer_Manager::Get_TimeDelta(const wstring_t& strTimerTag)
{
	auto pTimer = Find_Timer(strTimerTag);
	if (nullptr == pTimer)
		return 0.f;

	return pTimer->Get_TimeDelta();
}

void CTimer_Manager::Set_TimeDelta(const wstring_t& strTimerTag)
{
	auto pTimer = Find_Timer(strTimerTag);
	if (nullptr == pTimer)
		return;

	pTimer->Update_Timer();
}

HRESULT CTimer_Manager::Ready_Timer(const wstring_t& strTimerTag)
{
	auto pTimer = Find_Timer(strTimerTag);

	if (nullptr != pTimer)
		return E_FAIL;

	pTimer = CTimer::Create();
	if (nullptr == pTimer)
		return E_FAIL;

	m_Timers.insert({ strTimerTag, pTimer });

	return S_OK;
}

shared_ptr<CTimer> CTimer_Manager::Find_Timer(const wstring_t& strTimerTag)
{
	auto		iter = m_Timers.find(strTimerTag);

	if (iter == m_Timers.end())
		return nullptr;

	return iter->second;
}

void CTimer_Manager::Free()
{
	
}
