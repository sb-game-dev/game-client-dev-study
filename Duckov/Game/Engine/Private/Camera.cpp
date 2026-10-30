#include "Camera.h"

CCamera::CCamera(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	:CGameObject{ pDevice ,pContext }
{
	
}

HRESULT CCamera::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;
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

	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	m_pTransformCom->Set_State(STATE::POSITION, XMLoadFloat4(&pDesc->vEye));
	m_pTransformCom->LookAt(XMLoadFloat4(&pDesc->vAt));

	Update_PipeLines();

	return S_OK;
}
void CCamera::Priority_Update(f32_t fDeltTime)
{
	__super::Priority_Update(fDeltTime);
}
void CCamera::Update(f32_t fDeltTime)
{
	__super::Update(fDeltTime);
}
void CCamera::Late_Update(f32_t fDeltTime)
{
	__super::Late_Update(fDeltTime);
	Update_Frustum();
}
HRESULT CCamera::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;
}
void CCamera::Update_Frustum()
{
	// 원근 투영행렬을 이용하여 절두체 생성 (뷰스페이스에 있는 절두체)
	// 직교투영행렬을 사용하여 그리는 UI들은 절두체 컬링을 사용하지 않아야한다.
	matrix_t matProj = CGameInstance::Get().Get_Perspective_Transform(D3DTS::PROJ);
	BoundingFrustum::CreateFromMatrix(m_tViewFrustum, matProj);
}

void CCamera::Compute_PickingRay(POINT pt, vector_t& vRayOriginW, vector_t& vRayDirW)
{
	uint32_t numVP = 1;
	D3D11_VIEWPORT  vp;
	m_pContext->RSGetViewports(&numVP, &vp);

	matrix_t matProj = CGameInstance::Get().Get_Perspective_Transform(D3DTS::PROJ);
	f32_t vx = (+2.f * pt.x / vp.Width - 1.f) / XMVectorGetX(matProj.r[0]);
	f32_t vy = (-2.f * pt.y / vp.Height + 1.f) / XMVectorGetY(matProj.r[1]);

	matrix_t matInvView = CGameInstance::Get().Get_Perspective_Transform_Inverse(D3DTS::VIEW);
	vRayOriginW = CGameInstance::Get().Get_CamPosition();
	vRayDirW = XMVector3Normalize(XMVector3TransformNormal({ vx, vy, 1.f, 0.f }, matInvView));
}

void CCamera::Update_PipeLines()
{
	CGameInstance::Get().Set_Perspective_Transform(D3DTS::VIEW,
		XMMatrixInverse(nullptr, XMLoadFloat4x4(m_pTransformCom->Get_WorldMatrixPtr())));

	float2_t		vViewportSize = CGameInstance::Get().Get_ViewportSize();

	CGameInstance::Get().Set_Perspective_Transform(D3DTS::PROJ,
		XMMatrixPerspectiveFovLH(XMConvertToRadians(m_fFovy), vViewportSize.x / vViewportSize.y, m_fNear, m_fFar));

}