#include "QuarterView_Cam.h"
#include "GameObject.h"
#include "Player.h"
#include "Inven.h"

const f32_t g_fMaxFov = 60.f;
const f32_t g_fMinFov = 50.f;

CQuarterView_Cam::CQuarterView_Cam(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	:CCamera{pDevice, pContext}
{
}

CQuarterView_Cam::~CQuarterView_Cam()
{
}

HRESULT CQuarterView_Cam::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;
	return S_OK;
}

HRESULT CQuarterView_Cam::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;
	auto pPlayer = CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::GAMEPLAY), L"Layer_GameObject", TEXT("GameObject_Player"));
	vector_t vPlayerPos = pPlayer->Get_Transform()->Get_State(STATE::POSITION);

	XMStoreFloat4(&m_vAt, vPlayerPos);

	vector_t vOffset = XMLoadFloat4(&m_vOffset);
	m_pTransformCom->Set_State(STATE::POSITION, vPlayerPos + vOffset);
	
	m_pTransformCom->LookAt(vPlayerPos);
	Update_PipeLines();
	return S_OK;
}

void CQuarterView_Cam::Priority_Update(f32_t fTimeDelta)
{
}

void CQuarterView_Cam::Update(f32_t fDeltaTime)
{
	__super::Update(fDeltaTime);
	if (nullptr == m_pPlayer)
	{
		m_pPlayer = CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::GAMEPLAY), L"Layer_GameObject", TEXT("GameObject_Player"));
		if (nullptr == m_pPlayer)
			return;
	}
	vector_t vPlayerPos = m_pPlayer->Get_Transform()->Get_State(STATE::POSITION);

	auto pInven = static_pointer_cast<CInven>(CGameInstance::Get().Find_GameObject(
		ETOUI(LEVEL::GAMEPLAY), L"Layer_GameObject", L"GameObject_Inven"));

	bool_t bInvenOpen = (nullptr != pInven && pInven->Is_Open());
	
	// At 설정
	if (!bInvenOpen && CGameInstance::Get().Mouse_Pressing(DIM::RB) && !CGameInstance::Get().Key_Pressing(DIK_LSHIFT))
	{
		CGameInstance::Get().Get_MainCamera();
		auto pMouse = CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::GAMEPLAY), L"Layer_GameObject", GO::Client_Mouse);
		auto vWorldMousePos = pMouse->Get_Transform()->Get_State(STATE::POSITION);

		XMStoreFloat4(&m_vAt, (vWorldMousePos + vPlayerPos) / 2);

		vector_t vOffset = XMLoadFloat4(&m_vOffset);
		vector_t vAt = XMLoadFloat4(&m_vAt);
		m_pTransformCom->Set_State(STATE::POSITION, vAt + vOffset);
		m_pTransformCom->LookAt(vAt);

		// fov 변경
		//if (m_fFov > g_fMinFov)
		//	m_fFov -= fDeltaTime;
		//else
		m_fFovy = g_fMinFov;
	}
	else
	{
		vector_t vAt = XMLoadFloat4(&m_vAt);
		vector_t vDir = vPlayerPos - vAt;
		f32_t fDistance = XMVectorGetX(XMVector3Length(vDir));
		if (fDistance > 1.f)
		{
			vAt += XMVector3Normalize(vDir) * 50.f * fDeltaTime;
			XMStoreFloat4(&m_vAt, vAt);
		}
		else
		{
			XMStoreFloat4(&m_vAt, vPlayerPos);
		}
		// Eye 설정
		vector_t vOffset = XMLoadFloat4(&m_vOffset);
		m_pTransformCom->Set_State(STATE::POSITION, vAt + vOffset);
		m_pTransformCom->LookAt(vAt);
		// fov 복구
		if (m_fFovy < g_fMaxFov)
			m_fFovy += fDeltaTime * 50.f;
		else
			m_fFovy = g_fMaxFov;
	}

	if(!bInvenOpen)
		Shake(fDeltaTime);
	Update_PipeLines();
}

void CQuarterView_Cam::Late_Update(f32_t fDeltaTime)
{
	__super::Late_Update(fDeltaTime);
}

HRESULT CQuarterView_Cam::Render()
{
	return S_OK;
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
	if (FAILED(pInstance->Initialize_Prototype()))
		pInstance.reset();
	return pInstance;
}
shared_ptr<CPrototype> CQuarterView_Cam::Clone(void* pArg)
{
	auto pInstance = shared_ptr<CQuarterView_Cam>(new CQuarterView_Cam(*this));
	if (FAILED(pInstance->Initialize(pArg)))
		pInstance.reset();

	return pInstance;
}
