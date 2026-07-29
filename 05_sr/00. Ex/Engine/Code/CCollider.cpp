#include "CCollider.h"

CCollider::CCollider()
{
}

CCollider::CCollider(LPDIRECT3DDEVICE9 pGraphicDev)
{
}

CCollider::CCollider(const CCollider& rhs)
{
}

CCollider::~CCollider()
{
}

HRESULT CCollider::Ready_CColliderCom()
{
	//D3DXMatrixIdentity(&m_matWorld);
	//
	//for (_uint i = 0; i < INFO_END; ++i)
	//	memcpy(&m_vInfo[i], &m_matWorld.m[i][0], sizeof(_vec3));
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

CComponent* CCollider::Clone()
{
	return new CCollider(*this);
}

void CCollider::Free()
{
	CComponent::Free();
}
