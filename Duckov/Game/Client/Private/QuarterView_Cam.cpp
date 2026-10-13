#include "QuarterView_Cam.h"
#include "GameObject.h"
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

	// At 설정
	vector_t vPlayerPos = m_pPlayer->Get_Transform()->Get_State(STATE::POSITION);
	XMStoreFloat3(&m_vAt, vPlayerPos);

	// Eye 설정
	vector_t vCameraEye = vPlayerPos + vector_t({ 0.f, 5.f, -5.f });
	XMStoreFloat3(&m_vEye,vCameraEye);
}

void CQuarterView_Cam::Late_Update(f32_t fDeltaTime)
{
	__super::Late_Update(fDeltaTime);
}

shared_ptr<CQuarterView_Cam> CQuarterView_Cam::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
	auto pInstance = shared_ptr<CQuarterView_Cam>(new CQuarterView_Cam(pDevice, pContext));
	if (FAILED(pInstance->Initialize()))
		pInstance.reset();
	return pInstance;
}