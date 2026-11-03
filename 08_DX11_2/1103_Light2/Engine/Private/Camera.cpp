#include "Camera.h"

#include "GameInstance.h"

CCamera::CCamera(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	: CGameObject { pDevice, pContext }
{
}

HRESULT CCamera::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CCamera::Initialize(void* pArg)
{
	if (nullptr == pArg)
		return E_FAIL;

	auto	pDesc = static_cast<CAMERA_DESC*>(pArg);
	m_fFovy = pDesc->fFovy;
	m_fNear = pDesc->fNear;
	m_fFar = pDesc->fFar;

	if (FAILED(__super::Initialize(pDesc)))
		return E_FAIL;

	m_pTransformCom->Set_State(STATE::POSITION, XMLoadFloat4(&pDesc->vEye));
	m_pTransformCom->LookAt(XMLoadFloat4(&pDesc->vAt));
	
	Update_PipeLines();
	
	return S_OK;
}

void CCamera::Priority_Update(f32_t fTimeDelta)
{
}

void CCamera::Update(f32_t fTimeDelta)
{
}

void CCamera::Late_Update(f32_t fTimeDelta)
{
}

HRESULT CCamera::Render()
{
	return S_OK;
}

void CCamera::Update_PipeLines()
{
	CGameInstance::Get().Set_Perspective_Transform(D3DTS::VIEW,
		XMMatrixInverse(nullptr, XMLoadFloat4x4(m_pTransformCom->Get_WorldMatrixPtr())));

	float2_t		vViewportSize = CGameInstance::Get().Get_ViewportSize();

	CGameInstance::Get().Set_Perspective_Transform(D3DTS::PROJ,
		XMMatrixPerspectiveFovLH(XMConvertToRadians(m_fFovy), vViewportSize.x / vViewportSize.y, m_fNear, m_fFar));

}
