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


	_matrix matView, matProj;

	_vec3   vEye{ 0.f, 0.f, -10.f };
	_vec3   vUp{ 0.f, 1.f, 0.f };
	_vec3	vPlayerPos;
	_vec3	vPlayerUp;
	_vec3	vPlayerLOOK;

	CTransform* pPlayerTransformCom = dynamic_cast<CTransform*>
		(CManagement::GetInstance()->Get_Component(ID_DYNAMIC, L"Environment_Layer", L"Player", L"Com_Transform"));

	pPlayerTransformCom->Get_Info(INFO_POS, &vPlayerPos);
	pPlayerTransformCom->Get_Info(INFO_UP, &vPlayerUp);
	pPlayerTransformCom->Get_Info(INFO_LOOK, &vPlayerLOOK);
	vEye = vPlayerPos + (vPlayerUp * -5) +(vPlayerLOOK * -5);
	vUp = -vPlayerLOOK;

	D3DXMatrixLookAtLH(&matView, &vEye, &vPlayerPos, &vUp);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &matView);

	D3DXMatrixPerspectiveFovLH(&matProj, D3DXToRadian(60.f), (_float)WINCX / WINCY, 0.1f, 1000.f);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &matProj);
}
void		CCamera::Render_GameObject()
{
}

HRESULT CCamera::Add_Component()
{
	return S_OK;
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