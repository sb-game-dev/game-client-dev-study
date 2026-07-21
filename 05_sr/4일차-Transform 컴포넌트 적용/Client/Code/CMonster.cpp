#include "pch.h"
#include "CMonster.h"
#include "CProtoMgr.h"

CMonster::CMonster(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
}

CMonster::~CMonster()
{
}

HRESULT	 CMonster::Ready_GameObject()
{
	if (FAILED(AddComponent()))
		return E_FAIL;
	//m_pTransformCom->m_vScale = { 2,1,1 };
	return S_OK;
}
_int CMonster::Update_GameObject(const _float& fTimeDelta)
{
	_int iExit = CGameObject::Update_GameObject(fTimeDelta);
	Follow(fTimeDelta);
	return iExit;
}
void CMonster::LateUpdate_GameObject(const _float& fTimeDelta)
{
	CGameObject::LateUpdate_GameObject(fTimeDelta);

}
void CMonster::Render_GameObject()
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_World());

	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	//m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	//m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

HRESULT CMonster::AddComponent()
{
	Engine::CComponent* pComponent;

	pComponent = m_pBufferCom = dynamic_cast<CTriCol*>(CProtoMgr::GetInstance()->Clone_Prototype(L"Proto_TriCol"));
	if (nullptr == pComponent)
	{
		MSG_BOX("BufferCom Failed");
		return E_FAIL;
	}
	m_mapComponent[ID_STATIC].insert({ L"Com_Buffer",pComponent });

	pComponent = m_pTransformCom = dynamic_cast<CTransform*>(CProtoMgr::GetInstance()->Clone_Prototype(L"Proto_Transform"));
	if (nullptr == pComponent)
	{
		MSG_BOX("TransformCom Failed");
		return E_FAIL;
	}
	m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform",pComponent });

	return S_OK;
}
void CMonster::Follow(const _float& fTimeDelta)
{
	_vec3 vTargetLook = { 0.f,1.f,0.f };
	_vec3 vMyLook = { 0.f,1.f,0.f }; 
	_vec3 vTargetPos = { 0.f,0.f,0.f };
	_vec3 vMyPos = { 0.f,0.f,0.f };
	_vec3 vDeltaPos = { 0.f,0.f,0.f };

	_vec3 vCross = { 0.f,0.f,0.f };
	FLOAT fAngle = 0.f;

	_matrix matRot;

	m_pTargetTransfrom->Get_Info(INFO_POS, &vTargetPos);
	m_pTransformCom->Get_Info(INFO_POS, &vMyPos);
	
	m_pTargetTransfrom->Get_Info(INFO_UP, &vTargetLook); 
	m_pTransformCom->Get_Info(INFO_UP, &vMyLook);

	vDeltaPos = vTargetPos - vMyPos;
	D3DXVec3Normalize(&vDeltaPos, &vDeltaPos);
	D3DXVec3Cross(&vCross, &vMyLook, &vDeltaPos);
	fAngle = acosf(D3DXVec3Dot(&vMyLook, &vDeltaPos));

	// acosf 값 범위에 따라 뒤집기
	//if (vMyPos.y > vTargetPos.y)
	//	fAngle = D3DX_PI * 2 - fAngle;
	D3DXMatrixRotationAxis(&matRot, &vCross, fAngle);
	m_pTransformCom->RotationAxis(&matRot);
	

	m_pTransformCom->Move_Pos(&vDeltaPos, 5.f, fTimeDelta);
}
CMonster* CMonster::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CMonster* pMonster = new CMonster(pGraphicDev);

	if (FAILED(pMonster->Ready_GameObject()))
	{
		Safe_Release(pMonster);
		MSG_BOX("Monster Create Failed");
		return nullptr;
	}
	return pMonster;
}

void CMonster::Free()
{
	CGameObject::Free();
}