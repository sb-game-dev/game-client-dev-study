#include "GameInstance.h"

CGameInstance::CGameInstance()
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

	m_pPrototype_Manager = CPrototype_Manager::Create(EngineDesc.iNumLevels);
	if (m_pPrototype_Manager == nullptr)
		return E_FAIL;

	m_pObject_Manager = CObject_Manager::Create(EngineDesc.iNumLevels);
	if (m_pObject_Manager == nullptr)
		return E_FAIL;

	m_pCamera_Manager = CCamera_Manager::Create();
	if (m_pCamera_Manager == nullptr)
		return E_FAIL;

	m_pLight_Manager = CLight_Manager::Create();
	if (m_pLight_Manager == nullptr)
		return E_FAIL;

	m_pRenderer = CRenderer::Create(pDevice,pContext);
	if (m_pRenderer == nullptr)
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
	m_pPrototype_Manager->Clear(iCurrentLevel);
	m_pObject_Manager->Clear(iCurrentLevel);
	m_pRenderer->Clear_Mirror();
	return S_OK;
}

void CGameInstance::Update_Engine(f32_t fDeltaTime)
{
	m_pObject_Manager->Priority_Update(fDeltaTime);
	m_pCamera_Manager->Priority_Update(fDeltaTime);
	m_pLight_Manager->Priority_Update(fDeltaTime);

	m_pObject_Manager->Update(fDeltaTime);
	m_pCamera_Manager->Update(fDeltaTime);
	m_pLight_Manager->Update(fDeltaTime);

	m_pCamera_Manager->Late_Update(fDeltaTime);
	m_pObject_Manager->Late_Update(fDeltaTime);
	m_pLight_Manager->Late_Update(fDeltaTime);

	m_pLevel_Manager->Update(fDeltaTime);
}

HRESULT CGameInstance::Draw()
{	
	m_pRenderer->Render_GameObject();

	if (FAILED(m_pLevel_Manager->Render()))
		return E_FAIL;

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
	if (FAILED(m_pTimer_Manager->Add_Timer(strTimerTag)))
		return E_FAIL;
	return S_OK;
}
void CGameInstance::Update_TimeDelta(const wstring_t& strTimerTag)
{
	m_pTimer_Manager->Update_TimeDelta(strTimerTag);
}

#pragma endregion

#pragma region PROTOTYPE_MANAGER

HRESULT CGameInstance::Add_Prototype(uint32_t iLevelIndex, const wstring_t& strPrototypeTag, shared_ptr<CPrototype> pPrototype)
{
	if (FAILED(m_pPrototype_Manager->Add_Prototype(iLevelIndex, strPrototypeTag, pPrototype)))
		return E_FAIL;
	return S_OK;
}
shared_ptr<CPrototype> CGameInstance::Clone_Prototype(uint32_t iLevelIndex, const wstring_t& strPrototypeTag, void* pArg)
{
	return m_pPrototype_Manager->Clone_Prototype(iLevelIndex, strPrototypeTag, pArg);
}

#pragma endregion

#pragma region OBJECT_MANAGER

HRESULT CGameInstance::Add_GameObject(uint32_t iPrototypeLevelIndex, const wstring_t& strPrototypeTag, uint32_t iLayerLevelIndex, const wstring_t& strLayerTag, const wstring_t& strGameObjectTag, void* pArg)
{
	if (FAILED(m_pObject_Manager->Add_GameObject(iPrototypeLevelIndex, strPrototypeTag, iLayerLevelIndex, strLayerTag, strGameObjectTag, pArg)))
		return E_FAIL;
	return S_OK;
}

shared_ptr<CGameObject> CGameInstance::Find_GameObject(uint32_t iLayerLevelIndex, const wstring_t& strLayerTag, const wstring_t& strGameObjectTag)
{
	return m_pObject_Manager->Find_GameObject(iLayerLevelIndex,strLayerTag,strGameObjectTag);
}

#pragma endregion

#pragma region CAMERA_MANAGER
void CGameInstance::Add_Camera(const wstring_t& strCameraTag, shared_ptr<CCamera> pCamera)
{
	m_pCamera_Manager->Add_Camera(strCameraTag, pCamera);
}
void CGameInstance::Set_MainCamera(const wstring_t& strCameraTag)
{
	m_pCamera_Manager->Set_MainCamera(strCameraTag);
}
shared_ptr<CCamera> CGameInstance::Get_MainCamera(const wstring_t& strCameraTag)
{
	return m_pCamera_Manager->Get_MainCamera(strCameraTag);
}
#pragma endregion

#pragma region LIGHT_MANGER
void CGameInstance::AddLight(const wstring_t& strLightTag, shared_ptr<CLight> pLight)
{
	m_pLight_Manager->AddLight(strLightTag, pLight);
}
shared_ptr<CLight> CGameInstance::Find_Light(const wstring_t& strLightTag)
{
	return m_pLight_Manager->Find_Light(strLightTag);
}

#pragma endregion

#pragma region RENDERER
void CGameInstance::Add_RenderGroup(RENDERID eRenderID, shared_ptr<CGameObject> pGameObject)
{
	m_pRenderer->Add_RenderGroup(eRenderID, pGameObject);
}
void CGameInstance::Set_Mirror(shared_ptr<CGameObject> pMirror)
{
	m_pRenderer->Set_Mirror(pMirror);
}
void CGameInstance::Add_ReflectObject(shared_ptr<CGameObject> pObject)
{
	m_pRenderer->Add_ReflectObject(pObject);
}
#pragma endregion

void CGameInstance::Release_Engine()
{
	m_pRenderer.reset();
	m_pLight_Manager.reset();
	m_pLevel_Manager.reset();
	m_pCamera_Manager.reset();
	m_pObject_Manager.reset();
	m_pPrototype_Manager.reset();
	m_pTimer_Manager.reset();
	m_pGraphic_Device.reset();
}


