#include "GameInstance.h"

CGameInstance::CGameInstance()
{
}
CGameInstance::~CGameInstance()
{
}

HRESULT CGameInstance::Initialize_Engine()
{
	m_pTimer_Manager = CTimer_Manager::Create();
	if(m_pTimer_Manager == nullptr)
		return E_FAIL;
	return S_OK;
}

f32_t CGameInstance::Get_TimeDelta(const wstring_t& strTimerTag)
{
	return m_pTimer_Manager->Get_TimeDelta(strTimerTag);
}

void CGameInstance::Update_TimeDelta(const wstring_t& strTimerTag)
{
	m_pTimer_Manager->Update_TimeDelta(strTimerTag);
}

HRESULT CGameInstance::Add_Timer(const wstring_t& strTimerTag)
{
	if (FAILED(m_pTimer_Manager->Add_Timer(strTimerTag)))
		return E_FAIL;
	return S_OK;
}