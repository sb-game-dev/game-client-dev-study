#include "Free_Cam.h"

CFree_Cam::CFree_Cam(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	:CCamera{ pDevice, pContext }
{
}



HRESULT CFree_Cam::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;
	return S_OK;
}

HRESULT CFree_Cam::Initialize(void* pArg)
{
	auto    pDesc = static_cast<CAMERA_FREE_DESC*>(pArg);
	m_fMouseSensor = pDesc->fSensor;
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;
	return S_OK;
}

void CFree_Cam::Priority_Update(f32_t fTimeDelta)
{
}

void CFree_Cam::Update(f32_t fDeltaTime)
{
	__super::Update(fDeltaTime);
	
	KeyInput(fDeltaTime);
	if (m_bFix)
		Mouse_Fix();
}

void CFree_Cam::Late_Update(f32_t fDeltaTime)
{
	__super::Late_Update(fDeltaTime);
}

HRESULT CFree_Cam::Render()
{
	return __super::Render();
}

void CFree_Cam::KeyInput(const f32_t fDeltaTime)
{
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
	if (CGameInstance::Get().Key_Down(DIK_TAB))
	{
		m_bFix = !m_bFix;
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

void CFree_Cam::Mouse_Fix()
{
	float2_t	vpSize = CGameInstance::Get().Get_ViewportSize();
	POINT		ptMouse{ (long)vpSize.x >> 1, (long)vpSize .y>> 1 };

	ClientToScreen(g_hWnd, &ptMouse);
	SetCursorPos(ptMouse.x, ptMouse.y);
}

shared_ptr<CFree_Cam> CFree_Cam::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
	auto pInstance = shared_ptr<CFree_Cam>(new CFree_Cam(pDevice, pContext));
	if (FAILED(pInstance->Initialize_Prototype()))
		pInstance.reset();

	return pInstance;
}

shared_ptr<CPrototype> CFree_Cam::Clone(void* pArg)
{
	auto pInstance = shared_ptr<CFree_Cam>(new CFree_Cam(*this));
	if (FAILED(pInstance->Initialize(pArg)))
		pInstance.reset();

	return pInstance;
}
