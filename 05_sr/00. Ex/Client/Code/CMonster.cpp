#include "pch.h"
#include "CMonster.h"
#include "CProtoMgr.h"
#include "CManagement.h"

CMonster::CMonster(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
{
}

CMonster::~CMonster()
{
}

HRESULT CMonster::Ready_GameObject()
{
	if (FAILED(Add_Component()))
		return E_FAIL;
	m_pTransformCom->m_vScale = { 5,5,5 };

	m_pTransformCom->m_vInfo[INFO_POS] = { 77,40,-100 };

	m_pColliderCom->SetCenter(m_pTransformCom->m_vInfo[INFO_POS]);
	m_pColliderCom->SetHalfSize(m_pTransformCom->m_vScale);
	return S_OK;
}

_int CMonster::Update_GameObject(const _float& fTimeDelta)
{

	_int iExit = CGameObject::Update_GameObject(fTimeDelta);

	return iExit;
}

void CMonster::LateUpdate_GameObject(const _float& fTimeDelta)
{
	CGameObject::LateUpdate_GameObject(fTimeDelta);

	_vec3	vPos;
	m_pTransformCom->Get_Info(INFO_POS, &vPos);
	m_pColliderCom->SetCenter(vPos);
}

void CMonster::Render_GameObject()
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_World());

	//cout << "MonsterRender" << endl;
	m_pTextureCom->Set_Texture(0);

	m_pBufferCom->Render_Buffer();

}

HRESULT CMonster::Add_Component()
{
	Engine::CComponent* pComponent = nullptr;

	// TriCol
	pComponent = m_pBufferCom = dynamic_cast<CCubeTex*>(CProtoMgr::GetInstance()->Clone_Prototype(L"Proto_CubeTex"));
	if (nullptr == pComponent)
		return E_FAIL;

	m_mapComponent[ID_STATIC].insert({ L"Com_Buffer", pComponent });

	/////////////////////////////////////////////////////////////////
	// Transform
	pComponent = m_pTransformCom = dynamic_cast<CTransform*>(CProtoMgr::GetInstance()->Clone_Prototype(L"Proto_Transform"));
	if (nullptr == pComponent)
		return E_FAIL;

	m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform", pComponent });


	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(CProtoMgr::GetInstance()->Clone_Prototype(L"Proto_MonsterTexture"));
	if (nullptr == pComponent)
		return E_FAIL;
	m_mapComponent[ID_STATIC].insert({ L"Com_Texture", pComponent });

	// Collider
	pComponent = m_pColliderCom = dynamic_cast<CCollider*>(CProtoMgr::GetInstance()->Clone_Prototype(L"Proto_Collider"));
	if (nullptr == pComponent)
		return E_FAIL;

	m_mapComponent[ID_DYNAMIC].insert({ L"Com_Collider", pComponent });


	return S_OK;
}

CMonster* CMonster::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CMonster* pMonster = new CMonster(pGraphicDev);

	if (FAILED(pMonster->Ready_GameObject()))
	{
		Safe_Release(pMonster);
		MSG_BOX("pMonster Create Failed");
		return nullptr;
	}

	return pMonster;
}

void CMonster::Free()
{
	CGameObject::Free();
}
