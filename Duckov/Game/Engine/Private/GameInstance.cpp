#include "GameInstance.h"

CGameInstance::CGameInstance()
{
}

HRESULT CGameInstance::Initialize_Engine(const ENGINE_DESC& EngineDesc, _Out_ ComPtr<ID3D11Device>& pDevice, _Out_ ComPtr<ID3D11DeviceContext>& pContext)
{
	m_hWND = EngineDesc.hWnd;
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

	m_pRenderer = CRenderer::Create(pDevice, pContext, EngineDesc.iWinSizeX, EngineDesc.iWinSizeY);
	if (m_pRenderer == nullptr)
		return E_FAIL;

	m_pInput_Device = CInput_Device::Create(EngineDesc.hInstance, EngineDesc.hWnd);
	if (nullptr == m_pInput_Device)
		return E_FAIL;

	m_pPipeLine = CPipeLine::Create(pDevice, pContext);
	if (nullptr == m_pPipeLine)
		return E_FAIL;

	m_pSampler_Manager = CSampler_Manager::Create(pDevice, pContext);
	if (nullptr == m_pSampler_Manager)
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
	return S_OK;
}

void CGameInstance::Update_Engine(f32_t fDeltaTime)
{
	m_pInput_Device->Update();

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
float4x4_t CGameInstance::GetView()
{
	return m_pCamera_Manager->GetView();
}
shared_ptr<CCamera> CGameInstance::Get_MainCamera()
{
	return m_pCamera_Manager->Get_MainCamera();
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
void CGameInstance::SetBlurUse(bool_t bUseBlur)
{
	m_pRenderer->SetBlurUse(bUseBlur);
}
void CGameInstance::Set_Mirror(shared_ptr<CGameObject> pMirror)
{
	m_pRenderer->Set_Mirror(pMirror);
}

#pragma endregion

#pragma region INPUTDEVICE
int8_t CGameInstance::Get_DIKeyState(uint8_t byKeyID)
{
	return m_pInput_Device->Get_DIKeyState(byKeyID);
}
int8_t CGameInstance::Get_DIMouseState(DIM eMouse)
{
	return m_pInput_Device->Get_DIMouseState(eMouse);
}
int32_t CGameInstance::Get_DIMouseMove(DIMM eMouseState)
{
	return m_pInput_Device->Get_DIMouseMove(eMouseState);
}
bool_t CGameInstance::Key_Down(uint8_t byKey)
{
	return m_pInput_Device->Key_Down(byKey);
}
bool_t CGameInstance::Key_Up(uint8_t byKey)
{
	return m_pInput_Device->Key_Up(byKey);
}
bool_t CGameInstance::Key_Pressing(uint8_t byKey)
{
	return m_pInput_Device->Key_Pressing(byKey);
}
bool_t CGameInstance::Mouse_Down(DIM eMouse)
{
	return m_pInput_Device->Mouse_Down(eMouse);
}
bool_t CGameInstance::Mouse_Up(DIM eMouse)
{
	return m_pInput_Device->Mouse_Up(eMouse);
}
bool_t CGameInstance::Mouse_Pressing(DIM eMouse)
{
	return m_pInput_Device->Mouse_Pressing(eMouse);
}
POINT CGameInstance::Get_MousePos()
{
	return m_pInput_Device->Get_MousePos();
}

#pragma endregion


#pragma region PIPELINE
void CGameInstance::Set_Perspective_Transform(D3DTS eState, fmatrix_t TransformMatrix)
{
	m_pPipeLine->Set_Perspective_Transform(eState, TransformMatrix);
}

void CGameInstance::Set_Ortho_Transform(D3DTS eState, fmatrix_t TransformMatrix)
{
	m_pPipeLine->Set_Ortho_Transform(eState, TransformMatrix);
}

matrix_t CGameInstance::Get_Perspective_Transform(D3DTS eState) const
{
	return m_pPipeLine->Get_Perspective_Transform(eState);
}

matrix_t CGameInstance::Get_Ortho_Transform(D3DTS eState) const
{
	return m_pPipeLine->Get_Ortho_Transform(eState);
}

matrix_t CGameInstance::Get_Perspective_Transform_Inverse(D3DTS eState) const
{
	return m_pPipeLine->Get_Perspective_Transform_Inverse(eState);
}

matrix_t CGameInstance::Get_Ortho_Transform_Inverse(D3DTS eState) const
{
	return m_pPipeLine->Get_Ortho_Transform_Inverse(eState);
}

vector_t CGameInstance::Get_CamPosition() const
{
	return m_pPipeLine->Get_CamPosition();
}

HRESULT CGameInstance::Bind_PipeLine_Vertex_ShaderResource(uint32_t iSlot)
{
	return m_pPipeLine->Bind_Vertex_ShaderResource(iSlot);
}

HRESULT CGameInstance::Bind_PipeLine_Pixel_ShaderResource(uint32_t iSlot)
{
	return m_pPipeLine->Bind_Pixel_ShaderResource(iSlot);
}

#pragma endregion

#pragma region SAMPLER_MANAGER
HRESULT CGameInstance::Add_Sampler(const wstring_t& strSamplerTag, const D3D11_SAMPLER_DESC& SamplerDesc)
{
	return m_pSampler_Manager->Add_Sampler(strSamplerTag, SamplerDesc);
}

HRESULT CGameInstance::Bind_Sampler_Pixel_Shader(const wstring_t& strSamplerTag, uint32_t iSlot)
{
	return m_pSampler_Manager->Bind_Sampler_Pixel_Shader(strSamplerTag, iSlot);
}

#pragma endregion

void CGameInstance::Release_Engine()
{
	m_pSampler_Manager.reset();
	m_pPipeLine.reset();
	m_pInput_Device.reset();
	m_pLevel_Manager.reset();
	m_pRenderer.reset();
	m_pLight_Manager.reset();
	m_pCamera_Manager.reset();
	m_pObject_Manager.reset();
	m_pPrototype_Manager.reset();
	m_pTimer_Manager.reset();
	m_pGraphic_Device.reset();
}


