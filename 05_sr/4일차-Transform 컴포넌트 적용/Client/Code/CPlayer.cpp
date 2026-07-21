#include "pch.h"
#include "CProtoMgr.h"
#include "CPlayer.h"

CPlayer::CPlayer(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
}

CPlayer::~CPlayer()
{
}

HRESULT	CPlayer::Ready_GameObject()
{
	if (FAILED(Add_Component()))
		return E_FAIL;
	return S_OK;
}

_int CPlayer::Update_GameObject(const _float& fTimeDelta)
{
	_int iResult = CGameObject::Update_GameObject(fTimeDelta);
	KeyInput(fTimeDelta);
	return iResult;
}
void CPlayer::LateUpdate_GameObject(const _float& fTimeDelta)
{
	CGameObject::LateUpdate_GameObject(fTimeDelta);
}
void CPlayer::Render_GameObject()
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_World());

	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	
	m_pBufferCom->Render_Buffer();
	
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}
HRESULT	CPlayer::Add_Component()
{
	Engine::CComponent* pComponent;

	pComponent = m_pBufferCom = dynamic_cast<CRcCol*>(CProtoMgr::GetInstance()->Clone_Prototype(L"Proto_RcCol"));
	if (nullptr == pComponent)
	{
		MSG_BOX("RcCom Failed");
		return E_FAIL;
	}
	m_mapComponent[ID_STATIC].insert({ L"Com_Buffer",pComponent });

	pComponent = m_pTransformCom = dynamic_cast<CTransform*>(CProtoMgr::GetInstance()->Clone_Prototype(L"Proto_Transform"));
	if (nullptr == pComponent)
	{
		MSG_BOX("TransCom Failed");
		return E_FAIL;
	}
	m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform",pComponent });
}
void CPlayer::KeyInput(const _float& fTimeDelta)
{
	_vec3 vLook;
	m_pTransformCom->Get_Info(INFO_UP, &vLook);

	if (GetAsyncKeyState(VK_UP))
		m_pTransformCom->Move_Pos(D3DXVec3Normalize(&vLook, &vLook), 10.f, fTimeDelta);
	if (GetAsyncKeyState(VK_DOWN))
		m_pTransformCom->Move_Pos(D3DXVec3Normalize(&vLook, &vLook), -10.f, fTimeDelta);

	if (GetAsyncKeyState('Q'))
		m_pTransformCom->RotX(180.f * fTimeDelta);
	if (GetAsyncKeyState('A'))
		m_pTransformCom->Rotation(ROT_X, -180.f * fTimeDelta);
	if (GetAsyncKeyState('W'))
		m_pTransformCom->Rotation(ROT_Y, 180.f * fTimeDelta);
	if (GetAsyncKeyState('S'))
		m_pTransformCom->Rotation(ROT_Y, -180.f * fTimeDelta);
	if (GetAsyncKeyState('E'))
		m_pTransformCom->Rotation(ROT_Z, 180.f * fTimeDelta);
	if (GetAsyncKeyState('D'))
		m_pTransformCom->Rotation(ROT_Z, -180.f * fTimeDelta);
}
CPlayer* CPlayer::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CPlayer* pObj = nullptr;
	pObj = new CPlayer(pGraphicDev);

	if (FAILED(pObj->Ready_GameObject()))
	{
		Safe_Release(pObj);
		MSG_BOX("Player Create Failed");
		return nullptr;
	}
	return pObj;
}
void CPlayer::Shoot()
{
}
void CPlayer::Free()
{
	Safe_Release(m_pBufferCom);

	Safe_Release(m_pTransformCom);

	CGameObject::Free();
}