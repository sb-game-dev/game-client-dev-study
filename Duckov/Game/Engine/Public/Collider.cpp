#include "Collider.h"

CCollider::CCollider(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
}

HRESULT CCollider::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CCollider::Initialize(void* pArg)
{
	return E_NOTIMPL;
}

shared_ptr<CPrototype> CCollider::Clone(void* pArg)
{
	return shared_ptr<CPrototype>();
}
