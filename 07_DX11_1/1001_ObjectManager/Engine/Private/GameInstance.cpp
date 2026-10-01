#include "GameInstance.h"



CGameInstance::CGameInstance()
{
}

HRESULT CGameInstance::Initialize_Engine(const ENGINE_DESC& EngineDesc, _Out_ ComPtr<ID3D11Device>& pDevice, _Out_ ComPtr<ID3D11DeviceContext>& pContext)
{
	m_pGraphic_Device = CGraphic_Device::Create(EngineDesc.hWnd, EngineDesc.eWinMode, EngineDesc.iWinSizeX, EngineDesc.iWinSizeY, pDevice, pContext);
	if (nullptr == m_pGraphic_Device)
		return E_FAIL;

	m_pTimer_Manager = CTimer_Manager::Create();
	if (nullptr == m_pTimer_Manager)
		return E_FAIL;

	m_pLevel_Manager = CLevel_Manager::Create();
	if (nullptr == m_pLevel_Manager)
		return E_FAIL;

	m_pPrototype_Manager = CPrototype_Manager::Create(EngineDesc.iNumLevels);
	if (nullptr == m_pPrototype_Manager)
		return E_FAIL;

	m_pObject_Manager = CObject_Manager::Create(EngineDesc.iNumLevels);
	if (nullptr == m_pObject_Manager)
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

HRESULT CGameInstance::Clear_Resources(int32_t iClearLevelIndex)
{
	/* 매니져의 iClearLevelIndex용 자원들을 정리해준다. */
	m_pObject_Manager->Clear(iClearLevelIndex);
	m_pPrototype_Manager->Clear(iClearLevelIndex);

	

	return S_OK;
}

void CGameInstance::Update_Engine(f32_t fTimeDelta)
{
	m_pObject_Manager->Priority_Update(fTimeDelta);
	m_pObject_Manager->Update(fTimeDelta);
	m_pObject_Manager->Late_Update(fTimeDelta);

	m_pLevel_Manager->Update(fTimeDelta);
}

HRESULT CGameInstance::Draw()
{
	m_pLevel_Manager->Render();

	return S_OK;
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
	return m_pTimer_Manager->Add_Timer(strTimerTag);
}

void CGameInstance::Update_TimeDelta(const wstring_t& strTimerTag)
{
	m_pTimer_Manager->Update_TimeDelta(strTimerTag);
}
#pragma endregion

#pragma region PROTOTYPE_MANAGER
HRESULT CGameInstance::Add_Prototype(uint32_t iLevelIndex, const wstring_t& strPrototypeTag, shared_ptr<CPrototype> pPrototype)
{
	return m_pPrototype_Manager->Add_Prototype(iLevelIndex, strPrototypeTag, pPrototype);
}

shared_ptr<CPrototype> CGameInstance::Clone_Prototype(uint32_t iLevelIndex, const wstring_t& strPrototypeTag, void* pArg)
{
	return m_pPrototype_Manager->Clone_Prototype(iLevelIndex, strPrototypeTag, pArg);
}

#pragma endregion

#pragma region OBEJCT_MANAGER

HRESULT CGameInstance::Add_GameObject(uint32_t iPrototypeLevelIndex, const wstring_t& strPrototypeTag, uint32_t iLayerLevelIndex, 
	const wstring_t& strLayerTag, void* pArg)
{
	return m_pObject_Manager->Add_GameObject(iPrototypeLevelIndex, strPrototypeTag, iLayerLevelIndex, strLayerTag, pArg);
}

#pragma endregion

void CGameInstance::Release_Engine()
{
	m_pObject_Manager.reset();
	m_pPrototype_Manager.reset();
	m_pLevel_Manager.reset();
	m_pTimer_Manager.reset();
	m_pGraphic_Device.reset();

}
