#include "Cube_Collider.h"
#include "GameObject.h"
CCube_Collider::CCube_Collider(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	:CCollider{ pDevice, pContext }
{
}

HRESULT CCube_Collider::Initialize_Prototype()
{
	m_eColliderType = COLLIDER_TYPE::CUBE;
	return S_OK;
}

HRESULT CCube_Collider::Initialize(void* pArg)
{
	return S_OK;
}

BoundingOrientedBox& CCube_Collider::Get_Info()
{
	BoundingOrientedBox BoundingBox = {};
	auto pOwner = m_pOwner.lock();
	if (nullptr != pOwner){
		matrix_t matWorld = pOwner->Get_ColliderMatrix();
		vector_t vScale, vRotQuat, vTrans;
		XMMatrixDecompose(&vScale, &vRotQuat, &vTrans, matWorld);
		vTrans += XMVectorSetW(XMLoadFloat3(&m_vOffset), 1.f);

		XMStoreFloat4(&m_BoundingBox.Orientation, vRotQuat);
		XMStoreFloat3(&m_BoundingBox.Center, vTrans);
	}
	return m_BoundingBox;
}

void CCube_Collider::Render_Collider(float4_t vColor)
{
	Get_Info();
	float3_t vCorners[8];

	m_BoundingBox.GetCorners(vCorners);

	
}

void CCube_Collider::Set_OBBSize(BoundingBox Box_AABB)
{
	BoundingOrientedBox::CreateFromBoundingBox(m_BoundingBox, Box_AABB);
}

shared_ptr<CCube_Collider> CCube_Collider::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
	auto pInstance = shared_ptr<CCube_Collider>(new CCube_Collider(pDevice, pContext));

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Clone Failed : CCube_Collider");
		pInstance.reset();
	}
	return pInstance;
}


shared_ptr<CPrototype> CCube_Collider::Clone(void* pArg)
{
	auto pInstance = shared_ptr<CPrototype>(new CCube_Collider(*this));

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Clone Failed : CCube_Collider");
		pInstance.reset();
	}
	return pInstance;
}


