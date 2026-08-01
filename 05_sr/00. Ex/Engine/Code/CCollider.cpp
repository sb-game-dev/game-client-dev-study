#include "CCollider.h"

CCollider::CCollider()
{
}

CCollider::CCollider(LPDIRECT3DDEVICE9 pGraphicDev)
	:CComponent(pGraphicDev)
{
}

CCollider::CCollider(const CCollider& rhs)
	:CComponent(rhs),m_vCenter(rhs.m_vCenter),m_vHalfSize(rhs.m_vHalfSize)
{
}

CCollider::~CCollider()
{
}

HRESULT CCollider::Ready_CColliderCom()
{
	m_vCenter = { 0, 0, 0 };
	m_vHalfSize = { 1, 1, 1 };

	return S_OK;
}

_int CCollider::Update_Component(const _float& fTimeDelta)
{
	
	return 0;
}

void CCollider::LateUpdate_Component()
{

}

CCollider* CCollider::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CCollider* pTransform = new CCollider(pGraphicDev);

	if (FAILED(pTransform->Ready_CColliderCom()))
	{
		Safe_Release(pTransform);
		MSG_BOX("Transform Create Failed");
		return nullptr;
	}

	return pTransform;
}


void CCollider::Free()
{
	CComponent::Free();
}

CComponent* CCollider::Clone(CGameObject* pOwner)
{
	CCollider* pCollider = new CCollider(*this);
	pCollider->SetOwner(pOwner);

	return pCollider;
}
