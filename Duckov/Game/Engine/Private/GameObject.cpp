#include "GameObject.h"
#include "GameInstance.h"



CGameObject::CGameObject(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	: CPrototype{pDevice, pContext}
{
}

HRESULT CGameObject::Initialize_Prototype()
{
	return S_OK;
}
HRESULT CGameObject::Initialize(void* pArg)
{
	auto pDesc = static_cast<GAMEOBJECT_DESC*>(pArg);

	m_pTransformCom = CTransform::Create(m_pDevice, m_pContext);
	if (nullptr == m_pTransformCom)
		return E_FAIL;

	if (FAILED(m_pTransformCom->Initialize(pArg)))
		return E_FAIL;

	m_Components.emplace(g_strTransformComTag, m_pTransformCom);
	return S_OK;
}
void CGameObject::Priority_Update(f32_t fDeltaTime)
{
}
void CGameObject::Update(f32_t fDeltaTime)
{
}
void CGameObject::Late_Update(f32_t fDeltaTime)
{
}
HRESULT	CGameObject::Render()
{
	return S_OK;
}

void CGameObject::Compute_ViewZ()
{
	float4x4_t f44View = CGameInstance::Get().GetView();
	matrix_t matView = XMLoadFloat4x4(&f44View);

	XMVECTOR viewPos= m_pTransformCom->Get_State(STATE::POSITION);

	viewPos = XMVector3TransformCoord(viewPos, matView);
	m_fViewZ = XMVectorGetZ(viewPos);
}

bool_t CGameObject::Is_InFrustum()
{
	if (false == m_bUseCulling)
		return true;
	return Is_BoxInFrustum(m_tLocalBox, m_pTransformCom->Get_World());
}

bool_t CGameObject::Is_BoxInFrustum(const BoundingBox& tLocalBox, const matrix_t& matWorld)
{
	auto pCam = CGameInstance::Get().Get_MainCamera();
	matrix_t matInvView = XMLoadFloat4x4(&pCam->Get_InvView());
	matrix_t matInvWorld = XMMatrixInverse(nullptr, matWorld);
	matrix_t matToLocal = XMMatrixMultiply(matInvView, matInvWorld);   

	vector_t vScale, vRotQuat, vTrans;
	XMMatrixDecompose(&vScale, &vRotQuat, &vTrans, matToLocal);

	BoundingFrustum tLocalFrustum;
	pCam->Get_ViewFrustum().Transform(tLocalFrustum, XMVectorGetX(vScale), vRotQuat, vTrans);

	return tLocalBox.Intersects(tLocalFrustum);
}

shared_ptr<CComponent> CGameObject::Find_Component(const wstring_t& strComponentTag)
{
	auto iter = m_Components.find(strComponentTag);
	if (iter == m_Components.end())
		return nullptr;

	return iter->second;
}
