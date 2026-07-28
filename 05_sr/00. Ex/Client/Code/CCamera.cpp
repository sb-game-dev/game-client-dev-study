#include "pch.h"
#include "CCamera.h"
#include "CProtoMgr.h"
#include "CManagement.h"
#include "CDInputMgr.h"

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
	m_pTransformCom->m_vInfo[INFO_POS] = { 0,5.f,-10.f };

	m_vEye = { 0.f, 5.f, -10.f };
	m_vAt = { 0.f, 0.f, 0.f };
	m_vUp = { 0.f, 1.f, 0.f };
	m_fFov = 60.f;

	m_vPreMousePos = { 0,0,0 };
	m_vCurMousePos = { 0,0,0 };

	m_fRotX = 0.f;
	m_fRotY = 0.f;

	_matrix matView, matProj;
	D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vAt, &m_vUp);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &matView);

	D3DXMatrixPerspectiveFovLH(&matProj, D3DXToRadian(m_fFov), (_float)WINCX / WINCY, 0.1f, 1000.f);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &matProj);

	return S_OK;
}
_int	CCamera::Update_GameObject(const _float& fTimeDelta)
{
	_int iExit = CGameObject::Update_GameObject(fTimeDelta);

	//Direct_Follow(&m_vEye,&m_vAt,&m_vUp);
	//Smooth_Follow(&m_vEye, &m_vAt, &m_vUp, &m_fFov, fTimeDelta);

	MouseControl(&m_vEye, &m_vAt, &m_vUp, &m_fFov, fTimeDelta);
	MouseFix();


	_matrix matView, matProj;
	D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vAt, &m_vUp);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &matView);

	return iExit;
}
void	CCamera::LateUpdate_GameObject(const _float& fTimeDelta)
{
	CGameObject::LateUpdate_GameObject(fTimeDelta);

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

	m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform", pComponent });

	return S_OK;
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

	*vEye	= vPlayerPos + (vPlayerUp * -5) + (vPlayerLOOK * -5);
	*vAt	= vPlayerPos;
	*vUp	= -vPlayerLOOK;
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

void CCamera::MouseControl(_vec3* vEye, _vec3* vAt, _vec3* vUp, float* fFov, const _float& fTimeDelta)
{
	// 0. 플레이어 위치 가져오기
	_vec3	vPlayerPos;
	CTransform* pPlayerTransformCom = dynamic_cast<CTransform*>
		(CManagement::GetInstance()->Get_Component(ID_DYNAMIC, L"GameLogic_Layer", L"Player", L"Com_Transform"));

	pPlayerTransformCom->Get_Info(INFO_POS, &vPlayerPos);

	// 1. 마우스 위치 가져오기
	//m_vCurMousePos = GetMouse();
	//
	//m_vCurMousePos.x -= WINCX * 0.5f;
	//m_vCurMousePos.y -= WINCY * 0.5f;

	_long x, y;
	x = CDInputMgr::GetInstance()->Get_DIMouseMove(DIMS_X);
	y = CDInputMgr::GetInstance()->Get_DIMouseMove(DIMS_Y);

	// 2. At 이동
	*vAt = { 0,0,1 };

	// 3. At 회전(공전)
	_matrix		matRot[ROT_END];

	//FLOAT		fRotX = D3DXToRadian(m_vCurMousePos.y / 3);
	//FLOAT		fRotY = D3DXToRadian(m_vCurMousePos.x / 4);

	m_fRotX += D3DXToRadian(y/5);
	m_fRotY += D3DXToRadian(x/5);


	if (m_fRotX >= D3DXToRadian(90))
		m_fRotX = D3DXToRadian(89);
	if (m_fRotX <= -D3DXToRadian(90))
		m_fRotX = -D3DXToRadian(89);

	D3DXMatrixRotationX(&matRot[ROT_X], m_fRotX);
	D3DXMatrixRotationY(&matRot[ROT_Y], m_fRotY);

	for (_uint i = 0; i < ROT_Z; ++i)
		D3DXVec3TransformNormal(vAt, vAt, &matRot[i]);

	// 4. Eye 이동
	*vEye = vPlayerPos - *vAt * 10;

	// 5. At 이동
	*vAt += *vEye;
	
	// 6. 플레이어에게 넘겨줄 방향 설정
	m_pTransformCom->m_vInfo[INFO_LOOK] = (*vAt) - (*vEye);

	cout << "CameraLook: " << m_pTransformCom->m_vInfo[INFO_LOOK].x << endl;
}

void CCamera::MouseFix()
{
	POINT		ptMouse{ WINCX >> 1, WINCY >> 1 };

	ClientToScreen(g_hWnd, &ptMouse);
	SetCursorPos(ptMouse.x, ptMouse.y);
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