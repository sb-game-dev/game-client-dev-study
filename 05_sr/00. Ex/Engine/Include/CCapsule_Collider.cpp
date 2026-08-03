#include "CCapsule_Collider.h"
#include "CTransform.h"
#include "CGameObject.h"

CCapsule_Collider::CCapsule_Collider()
{
}

CCapsule_Collider::CCapsule_Collider(LPDIRECT3DDEVICE9 pGraphicDev)
	:CCollider(pGraphicDev)
{
}

CCapsule_Collider::CCapsule_Collider(const CCollider& rhs)
	:CCollider(rhs)
{
}

CCapsule_Collider::~CCapsule_Collider()
{
}

HRESULT CCapsule_Collider::Ready_CCapsule_Collider()
{
	return S_OK;
}

_int CCapsule_Collider::Update_Component(const _float& fTimeDelta)
{
	return 0;
}
void CCapsule_Collider::LateUpdate_Component()
{
	CTransform* pOwnerTransfrom = dynamic_cast<CTransform*> (m_pOwner->Get_Component(ID_DYNAMIC, L"Com_Transform"));

	_vec3 vOwnerPos;
	pOwnerTransfrom->Get_Info(INFO_POS, &vOwnerPos);
	m_vOffset = vOwnerPos;
}

CComponent* CCapsule_Collider::Clone(CGameObject* pOwner)
{
	CCapsule_Collider* pCapsule_Collider = new CCapsule_Collider(*this);

	if (FAILED(pCapsule_Collider->Ready_CColliderCom()))
	{
		Safe_Release(pCapsule_Collider);
		MSG_BOX("pSphere_Collider Create Failed");
		return nullptr;
	}
	pCapsule_Collider->SetOwner(pOwner);
	return pCapsule_Collider;
}

void CCapsule_Collider::Free()
{
	CCollider::Free();
}