#include "GameObject.h"


CGameObject::CGameObject(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	: m_pDevice{ pDevice }
	, m_pContext{ pContext }
{
	XMMATRIX matI= XMMatrixIdentity();
	XMStoreFloat4x4(&m_matWorld, matI);

	m_vInfo[static_cast<uint32_t>(INFO::RIGHT)] = { 1.f, 0.f, 0.f };
	m_vInfo[static_cast<uint32_t>(INFO::UP)]	= { 0.f, 1.f, 0.f };
	m_vInfo[static_cast<uint32_t>(INFO::LOOK)]	= { 0.f, 0.f, 1.f };
	m_vInfo[static_cast<uint32_t>(INFO::POS)]	= { 0.f, 0.f, 0.f };
}

HRESULT CGameObject::Initialize()
{
	return S_OK;
}
void CGameObject::Update(f32_t fDeltaTime)
{

}
void CGameObject::LateUpdate(f32_t fDeltaTime)
{
}
HRESULT	CGameObject::Render()
{
	return S_OK;
}

void CGameObject::MovePos(XMVECTOR vDir, f32_t fSpeed, f32_t fDeltaTime)
{
	XMVECTOR	vPos = XMLoadFloat3(&m_vInfo[static_cast<uint32_t>(INFO::POS)]);
	vPos += vDir * fSpeed * fDeltaTime;
	XMStoreFloat3(&m_vInfo[static_cast<uint32_t>(INFO::POS)], vPos);
}
XMMATRIX CGameObject::GetWorld()
{
	XMVECTOR vInfo[static_cast<uint32_t>(INFO::END)];
	for(uint32_t i =0;i< static_cast<uint32_t>(INFO::END);++i)
		vInfo[i] = XMLoadFloat3(&m_vInfo[i]);

	for (uint32_t i = 0; i < static_cast<uint32_t>(INFO::POS); ++i)
		vInfo[i] *= *(((f32_t*)&m_vScale) + i);

	XMMATRIX	matRot[static_cast<uint32_t>(ROTATION::END)];

	matRot[static_cast<uint32_t>(ROTATION::X)] = XMMatrixRotationX(m_fRotX);
	matRot[static_cast<uint32_t>(ROTATION::Y)] = XMMatrixRotationY(m_fRotY);
	matRot[static_cast<uint32_t>(ROTATION::Z)] = XMMatrixRotationZ(m_fRotZ);

	for (uint32_t i = 0; i < static_cast<uint32_t>(INFO::POS); ++i)
	{
		for (uint32_t j = 0; j < static_cast<uint32_t>(ROTATION::END); ++j)
			vInfo[i] = XMVector3TransformNormal(vInfo[i], matRot[j]);
	}

	vInfo[static_cast<uint32_t>(INFO::POS)] = XMVectorSetW(vInfo[static_cast<uint32_t>(INFO::POS)], 1.f);
	for (uint32_t i = 0; i < static_cast<uint32_t>(INFO::END); ++i)
		memcpy(&m_matWorld.m[i][0], &vInfo[i], sizeof(XMVECTOR));

	return XMLoadFloat4x4(&m_matWorld);
}
