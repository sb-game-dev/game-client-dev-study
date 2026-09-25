#include "GameInstance.h"

CGameInstance::CGameInstance()
{
}
CGameInstance::~CGameInstance()
{
}

HRESULT CGameInstance::Initialize_Engine(const ENGINE_DESC& EngineDesc, _Out_ ComPtr<ID3D11Device>& pDevice, _Out_ ComPtr<ID3D11DeviceContext>& pContext)
{
	m_pGraphic_Device = CGraphic_Device::Create(EngineDesc.hWnd, EngineDesc.eWinMode, EngineDesc.iWinSizeX, EngineDesc.iWinSizeY, pDevice, pContext);
	if (m_pGraphic_Device == nullptr)
		return E_FAIL;

	m_pTimer_Manager = CTimer_Manager::Create();
	if (m_pTimer_Manager == nullptr)
		return E_FAIL;

	m_pLevel_Manager = CLevel_Manager::Create();
	if (m_pLevel_Manager == nullptr)
		return E_FAIL;

	return S_OK;
}

HRESULT CGameInstance::Clear_BackBuffer_View(const float4_t* pClearColor)
{
	return m_pGraphic_Device->Clear_BackBuffer_View(pClearColor);
}
HRESULT CGameInstance::Clear_DepthStencil_View()
{
	return m_pGraphic_Device->Clear_DepthStencil_View();
}

HRESULT CGameInstance::Clear_Resources(int32_t iCurrentLevel)
{
	return S_OK;
}

void CGameInstance::Update_Engine(f32_t fDeltaTime)
{
	m_pLevel_Manager->Update(fDeltaTime);
}

void CGameInstance::LateUpdate_Engine(f32_t fDeltaTime)
{
	m_pLevel_Manager->LateUpdate(fDeltaTime);
}

HRESULT CGameInstance::Draw()
{
	return m_pLevel_Manager->Render();
}

HRESULT CGameInstance::Present()
{
	return m_pGraphic_Device->Present();
}
#pragma region LEVEL_MANAGER

HRESULT CGameInstance::Change_Level(int32_t iNewLevelIndex, shared_ptr<CLevel> pNewLevel)
{
	return m_pLevel_Manager->Change_Level(iNewLevelIndex, pNewLevel);
}

#pragma endregion

#pragma region TIMER_MANAGER

f32_t CGameInstance::Get_TimeDelta(const wstring_t& strTimerTag)
{
	return m_pTimer_Manager->Get_TimeDelta(strTimerTag);
}

HRESULT CGameInstance::Add_Timer(const wstring_t& strTimerTag)
{
	if (FAILED(m_pTimer_Manager->Add_Timer(strTimerTag)))
		return E_FAIL;
	return S_OK;
}
void CGameInstance::Update_TimeDelta(const wstring_t& strTimerTag)
{
	m_pTimer_Manager->Update_TimeDelta(strTimerTag);
}

#pragma endregion

void CGameInstance::Release_Engine()
{
	m_pLevel_Manager.reset();
	m_pTimer_Manager.reset();
	m_pGraphic_Device.reset();
}


