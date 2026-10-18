#include "QuarterView_Cam.h"
#include "GameObject.h"
#include "Player.h"

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

	vector_t vPlayerPos = m_pPlayer->Get_Transform()->Get_State(STATE::POSITION);
	// At 설정
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000 && !GetAsyncKeyState(VK_LSHIFT))
	{
		CGameInstance::Get().Get_MainCamera();
		float4_t vecWorldMousePos = static_pointer_cast<CPlayer>(m_pPlayer)->Get_WorldMousePos();
		vector_t vWorldMousePos = XMLoadFloat4(&vecWorldMousePos);

		XMStoreFloat3(&m_vAt, (vWorldMousePos + vPlayerPos) / 2);
		// fov 변경

	}
	else
	{
		vector_t vAt = XMLoadFloat3(&m_vAt);
		vector_t vDir = vPlayerPos - vAt;
		f32_t fDistance = XMVectorGetX(XMVector3Length(vDir));
		if (fDistance > 1.f)
		{
			vAt += XMVector3Normalize(vDir) * 50.f * fDeltaTime;
			XMStoreFloat3(&m_vAt, vAt);
		}
		else
		{
			XMStoreFloat3(&m_vAt, vPlayerPos);
		}
	}
	// Eye 설정
	vector_t vCameraEye = vector_t{ m_vAt.x, m_vAt.y + 10.f, m_vAt.z - 5.f };
	XMStoreFloat3(&m_vEye,vCameraEye);

	//m_vEye = { 0.f,15.f,0.f };
	//m_fTime += 5 * fDeltaTime;
	//m_vAt = { 5 * cosf(XM_2PI / 16 * m_fTime) ,0.f,5 * sinf(XM_2PI / 16 * m_fTime) };

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