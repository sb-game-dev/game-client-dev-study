#include "Free_Cam.h"

CFree_Cam::CFree_Cam(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	:CCamera{ pDevice, pContext }
{
}

CFree_Cam::~CFree_Cam()
{
}

HRESULT CFree_Cam::Initialize()
{
	if (FAILED(__super::Initialize()))
		return E_FAIL;
	m_vUp = { 0.f,0.f,1.f };
	return S_OK;
}

void CFree_Cam::Update(f32_t fDeltaTime)
{
	__super::Update(fDeltaTime);
	if (nullptr == m_pPlayer)
		return;
	float3_t fPlayerPos = m_pPlayer->GetInfo(INFO::POS);

	XMVECTOR vPlayerPos = XMLoadFloat3(&fPlayerPos);
	XMVECTOR vCameraEye = vPlayerPos + XMVECTOR({ 0.f, 5.f, -5.f });

	m_vAt = fPlayerPos;
	XMStoreFloat3(&m_vEye, vCameraEye);
}

void CFree_Cam::Late_Update(f32_t fDeltaTime)
{
	__super::Late_Update(fDeltaTime);
}

shared_ptr<CFree_Cam> CFree_Cam::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
	auto pInstance = shared_ptr<CFree_Cam>(new CFree_Cam(pDevice, pContext));
	if (FAILED(pInstance->Initialize()))
		pInstance.reset();
	return pInstance;
}