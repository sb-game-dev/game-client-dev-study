#include "MapTool_Cam.h"

CMapTool_Cam::CMapTool_Cam(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	:CCamera{ pDevice, pContext }
{
}



HRESULT CMapTool_Cam::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;
	return S_OK;
}

HRESULT CMapTool_Cam::Initialize(void* pArg)
{
	auto    pDesc = static_cast<tagMapToolCamDesc*>(pArg);
	m_fMouseSensor = pDesc->fSensor;

	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;
	return S_OK;
}

void CMapTool_Cam::Priority_Update(f32_t fTimeDelta)
{
}

void CMapTool_Cam::Update(f32_t fDeltaTime)
{
	__super::Update(fDeltaTime);
	if (!CGameInstance::Get().Get_DIMouseState(DIM::RB))
		return;
	if (m_bSceneClicked)
	{
		KeyInput(fDeltaTime);
	}
}

void CMapTool_Cam::Late_Update(f32_t fDeltaTime)
{
	__super::Late_Update(fDeltaTime);
}

HRESULT CMapTool_Cam::Render()
{
	return __super::Render();
}

void CMapTool_Cam::KeyInput(const f32_t fDeltaTime)
{
	if (!CGameInstance::Get().Get_DIMouseState(DIM::RB))
		return;
	if (CGameInstance::Get().Get_DIKeyState(DIK_W))
	{
		m_pTransformCom->Go_Straight(fDeltaTime);
	}
	if (CGameInstance::Get().Get_DIKeyState(DIK_S))
	{
		m_pTransformCom->Go_Backward(fDeltaTime);
	}
	if (CGameInstance::Get().Get_DIKeyState(DIK_A))
	{
		m_pTransformCom->Go_Left(fDeltaTime);
	}
	if (CGameInstance::Get().Get_DIKeyState(DIK_D))
	{
		m_pTransformCom->Go_Right(fDeltaTime);
	}


	int32_t     iMouseMove = {};
	if (iMouseMove = CGameInstance::Get().Get_DIMouseMove(DIMM::Y))
	{
		m_pTransformCom->Turn(m_pTransformCom->Get_State(STATE::RIGHT), m_fMouseSensor * iMouseMove * fDeltaTime);
	}
	if (iMouseMove = CGameInstance::Get().Get_DIMouseMove(DIMM::X))
	{
		m_pTransformCom->Turn(XMVectorSet(0.f, 1.f, 0.f, 0.f), m_fMouseSensor * iMouseMove * fDeltaTime);
	}
	Update_PipeLines();
}

shared_ptr<CMapTool_Cam> CMapTool_Cam::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
	auto pInstance = shared_ptr<CMapTool_Cam>(new CMapTool_Cam(pDevice, pContext));
	if (FAILED(pInstance->Initialize_Prototype()))
		pInstance.reset();

	return pInstance;
}

shared_ptr<CPrototype> CMapTool_Cam::Clone(void* pArg)
{
	auto pInstance = shared_ptr<CMapTool_Cam>(new CMapTool_Cam(*this));
	if (FAILED(pInstance->Initialize(pArg)))
		pInstance.reset();

	return pInstance;
}
