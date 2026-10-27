#include "Timer_Manager.h"
#include "Timer.h"


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


HRESULT CTimer_Manager::Add_Timer(const wstring_t& strTimerTag)
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

void CTimer_Manager::Update_TimeDelta(const wstring_t& strTimerTag)
{
	auto pTimer = Find_Timer(strTimerTag);
	if (nullptr == pTimer)
		return;

	pTimer->Update_Timer();
}

shared_ptr<CTimer> CTimer_Manager::Find_Timer(const wstring_t& strTimerTag)
{
	auto		iter = m_Timers.find(strTimerTag);

	if (iter == m_Timers.end())
		return nullptr;

	return iter->second;
}

unique_ptr<CTimer_Manager> CTimer_Manager::Create()
{
	return unique_ptr<CTimer_Manager>(new CTimer_Manager());
}
