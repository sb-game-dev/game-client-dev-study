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

	auto pPlayer = CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::GAMEPLAY), L"Layer_GameObject", TEXT("GameObject_Player"));
	if (nullptr != pPlayer)
	{
		vector_t vPlayerPos = pPlayer->Get_Transform()->Get_State(STATE::POSITION);
		XMStoreFloat3(&m_vAt, vPlayerPos);

		vector_t vCameraEye = vector_t{ m_vAt.x, m_vAt.y - 120.f, m_vAt.z - 10.f };
		XMStoreFloat3(&m_vEye, vCameraEye);
	}
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
		auto pMouse = CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::GAMEPLAY), L"Layer_GameObject", L"GameObject_ClientMouse");
		auto vWorldMousePos = pMouse->Get_Transform()->Get_State(STATE::POSITION);

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
			// fov 복구
		}
		else
		{
			XMStoreFloat3(&m_vAt, vPlayerPos);
		}

	}
	
	Shake(fDeltaTime);

	// Eye 설정
	vector_t vCameraEye = vector_t{ m_vAt.x, m_vAt.y + 20.f, m_vAt.z - 10.f };
	XMStoreFloat3(&m_vEye, vCameraEye);
}

void CQuarterView_Cam::Late_Update(f32_t fDeltaTime)
{
	__super::Late_Update(fDeltaTime);
}

void CQuarterView_Cam::Shake(f32_t fDeltaTime)
{
	if (m_fShakeTime <= 0.f)
	{
		m_fShakeTime = 0.f;
		m_vShakeOffset = {};
		return;
	}
	m_fShakeTime -= fDeltaTime;
	m_vShakeOffset.x = (rand() % 5 - 2) * fDeltaTime;
	m_vShakeOffset.z = (rand() % 5 - 2) * fDeltaTime;

	m_vAt.x += m_vShakeOffset.x;
	m_vAt.z += m_vShakeOffset.z;
}

shared_ptr<CQuarterView_Cam> CQuarterView_Cam::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
	auto pInstance = shared_ptr<CQuarterView_Cam>(new CQuarterView_Cam(pDevice, pContext));
	if (FAILED(pInstance->Initialize()))
		pInstance.reset();
	return pInstance;
}