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

	m_pTransform = CTransform::Create(m_pDevice, m_pContext);
	if (nullptr == m_pTransform)
		return E_FAIL;

	if (FAILED(m_pTransform->Initialize(pArg)))
		return E_FAIL;

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

	XMVECTOR viewPos= m_pTransform->Get_State(STATE::POSITION);

	viewPos = XMVector3TransformCoord(viewPos, matView);
	m_fViewZ = XMVectorGetZ(viewPos);
}
