#include "pch.h"
#include "CCamera.h"
#include "CProtoMgr.h"
#include "CManagement.h"

CCamera::CCamera(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
}

CCamera::~CCamera()
{
}
HRESULT		CCamera::Ready_GameObject()
{
	if (FAILED(Add_Component()))
		return E_FAIL;
	m_pTransformCom->m_vInfo[INFO_POS] = { 0,5,-5 };

	m_vEye = { 0.f, 0.f, -10.f };
	m_vAt = { 0.f, 0.f, 0.f };
	m_vUp = { 0.f, 1.f, 0.f };
	m_fFov = 60.f;
	return S_OK;
}
_int	CCamera::Update_GameObject(const _float& fTimeDelta)
{
	_int iExit = CGameObject::Update_GameObject(fTimeDelta);
	return iExit;
}
void	CCamera::LateUpdate_GameObject(const _float& fTimeDelta)
{
	CGameObject::LateUpdate_GameObject(fTimeDelta);

	KeyInput(fTimeDelta);

	//Direct_Follow(&m_vEye,&m_vAt,&m_vUp);
	Smooth_Follow(&m_vEye, &m_vAt, &m_vUp, &m_fFov, fTimeDelta);

	_matrix matView, matProj;
	D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vAt, &m_vUp);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &matView);

	D3DXMatrixPerspectiveFovLH(&matProj, D3DXToRadian(m_fFov), (_float)WINCX / WINCY, 0.1f, 1000.f);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &matProj);
}
void CCamera::Render_GameObject()
{
}

HRESULT CCamera::Add_Component()
{
	Engine::CComponent* pComponent = nullptr;
	// Transform
	pComponent = m_pTransformCom = dynamic_cast<CTransform*>(CProtoMgr::GetInstance()->Clone_Prototype(L"Proto_Transform"));
	if (nullptr == pComponent)
		return E_FAIL;

	m_mapComponent[ID_STATIC].insert({ L"Com_Transform", pComponent });

	return S_OK;
}

void CCamera::KeyInput(const _float& fTimeDelta)
{
	if (GetAsyncKeyState('Q'))
		m_fFov += 15.f * fTimeDelta;
	if (GetAsyncKeyState('A'))
		m_fFov -= 15.f * fTimeDelta;
}

void CCamera::Direct_Follow(_vec3* vEye,_vec3* vAt,_vec3* vUp)
{
	_vec3	vPlayerPos;
	_vec3	vPlayerUp;
	_vec3	vPlayerLOOK;

	CTransform* pPlayerTransformCom = dynamic_cast<CTransform*>
		(CManagement::GetInstance()->Get_Component(ID_DYNAMIC, L"Environment_Layer", L"Player", L"Com_Transform"));

	pPlayerTransformCom->Get_Info(INFO_POS, &vPlayerPos);
	pPlayerTransformCom->Get_Info(INFO_UP, &vPlayerUp);
	pPlayerTransformCom->Get_Info(INFO_LOOK, &vPlayerLOOK);

	*vEye = vPlayerPos + (vPlayerUp * -5) + (vPlayerLOOK * -5);
	*vAt = vPlayerPos;
	*vUp = -vPlayerLOOK;
}

void CCamera::Smooth_Follow(_vec3* vEye, _vec3* vAt, _vec3* vUp, float* fFov, const _float& fTimeDelta)
{
	_vec3	vPlayerPos;
	_vec3	vPlayerUp;
	_vec3	vPlayerLOOK;
	_vec3	vDeltaPos;
	_vec3	vMyPos;

	CTransform* pPlayerTransformCom = dynamic_cast<CTransform*>
		(CManagement::GetInstance()->Get_Component(ID_DYNAMIC, L"Environment_Layer", L"Player", L"Com_Transform"));

	pPlayerTransformCom->Get_Info(INFO_POS, &vPlayerPos);
	pPlayerTransformCom->Get_Info(INFO_UP, &vPlayerUp);
	pPlayerTransformCom->Get_Info(INFO_LOOK, &vPlayerLOOK);
	m_pTransformCom->Get_Info(INFO_POS, &vMyPos);

	_vec3	vTargetPos = vPlayerPos + (vPlayerUp * -5) + (vPlayerLOOK * -5);

	vDeltaPos = vTargetPos - vMyPos;
	float	fDeltaPos = D3DXVec3Length(&vDeltaPos);
	
	if (fDeltaPos > 1.f)
	{
		float	fChaseSpeed = 5.f + fDeltaPos;
		m_pTransformCom->Chase_Target(&vTargetPos, fChaseSpeed, fTimeDelta);
		//*fFov = 60.f + fDeltaPos*10;
	}
	m_pTransformCom->Get_Info(INFO_POS, vEye);
	*vAt = vPlayerPos;
	*vUp = -vPlayerLOOK;
}

CCamera* CCamera::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CCamera* pCamera = new CCamera(pGraphicDev);

	if (FAILED(pCamera->Ready_GameObject()))
	{
		MSG_BOX("Camera Create Failed");
		Safe_Release(pCamera);
		return nullptr;
	}
	return pCamera;
}

void CCamera::Free()
{
	CGameObject::Free();
}