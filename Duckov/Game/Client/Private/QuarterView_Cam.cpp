#include "QuarterView_Cam.h"

CQuarterView_Cam::CQuarterView_Cam(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	:CCamera{pDevice, pContext}
{
}

CQuarterView_Cam::~CQuarterView_Cam()
{
}

HRESULT CQuarterView_Cam::Initialize()
{
	if (FAILED(__super::Initialize()))
		return E_FAIL;
	m_vUp = { 0.f,0.f,1.f };
	return S_OK;
}

void CQuarterView_Cam::Update(f32_t fDeltaTime)
{
	__super::Update(fDeltaTime);
	if (nullptr == m_pPlayer)
		return;
	float3_t fPlayerPos = m_pPlayer->GetInfo(INFO::POS);

	XMVECTOR vPlayerPos = XMLoadFloat3(&fPlayerPos);
	XMVECTOR vCameraEye = vPlayerPos + XMVECTOR({ 0.f, 15.f, -5.f });
	
	m_vAt = fPlayerPos;
	XMStoreFloat3(&m_vEye,vCameraEye);
}

void CQuarterView_Cam::LateUpdate(f32_t fDeltaTime)
{
	__super::LateUpdate(fDeltaTime);
}

HRESULT CQuarterView_Cam::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;
	return E_NOTIMPL;
}


shared_ptr<CQuarterView_Cam> CQuarterView_Cam::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
	auto pInstance = shared_ptr<CQuarterView_Cam>(new CQuarterView_Cam(pDevice, pContext));
	if (FAILED(pInstance->Initialize()))
		pInstance.reset();
	return pInstance;
}