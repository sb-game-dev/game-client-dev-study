#include "pch.h"
#include "CBullet.h"
#include "CProtoMgr.h"
#include "CRenderer.h"
CBullet::CBullet(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 vPos, _vec3 vDir)
	:CGameObject(pGraphicDev), m_vDir(vDir), m_vPos(vPos)
{
}

CBullet::~CBullet()
{
}

HRESULT CBullet::Ready_GameObject()
{
	if (FAILED(Add_Component()))
		return E_FAIL;
	m_fSpeed = 50.f;
	//m_pTransformCom->m_vInfo[INFO_LOOK] = m_vDir;
	m_pTransformCom->m_vScale = { 0.3,0.3,0.3 };
	m_pTransformCom->m_vInfo[INFO_POS] = m_vPos;
	m_pColliderCom->SetHalfSize(m_pTransformCom->m_vScale);
	CRenderer::GetInstance()->Add_RenderGroup(RENDER_NONALPHA, this);
	return S_OK;
}
_int CBullet::Update_GameObject(const _float& fTimeDelta)
{
	_int iExit = CGameObject::Update_GameObject(fTimeDelta);
	m_pTransformCom->Move_Pos(&m_vDir, m_fSpeed, fTimeDelta);
	return iExit;
}
void CBullet::LateUpdate_GameObject(const _float& fTimeDelta)
{
	CGameObject::LateUpdate_GameObject(fTimeDelta);
	_vec3 vPos;
	m_pTransformCom->Get_Info(INFO_POS, &vPos);
	m_pColliderCom->SetCenter(vPos);
}
void CBullet::Render_GameObject()
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_World());

	m_pTextureCom->Set_Texture(0);
	m_pBufferCom->Render_Buffer();

}

HRESULT CBullet::Add_Component()
{
	CComponent* pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CCubeTex*>(CProtoMgr::GetInstance()->Clone_Prototype(L"Proto_CubeTex"));
	if (nullptr == pComponent)
		return E_FAIL;
	m_mapComponent[ID_STATIC].insert({ L"Com_Buffer", pComponent });

	pComponent = m_pTransformCom = dynamic_cast<CTransform*>(CProtoMgr::GetInstance()->Clone_Prototype(L"Proto_Transform"));
	if (nullptr == pComponent)
		return E_FAIL;
	m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform", pComponent });

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(CProtoMgr::GetInstance()->Clone_Prototype(L"Proto_BulletTexture"));
	if (nullptr == pComponent)
		return E_FAIL;
	m_mapComponent[ID_DYNAMIC].insert({ L"Com_Texture", pComponent });

	pComponent = m_pColliderCom = dynamic_cast<CCollider*>(CProtoMgr::GetInstance()->Clone_Prototype(L"Proto_Collider"));
	if (nullptr == pComponent)
		return E_FAIL;

	m_mapComponent[ID_DYNAMIC].insert({ L"Com_Collider", pComponent });

	return S_OK;
}

CBullet* CBullet::Create(LPDIRECT3DDEVICE9 pGraphicDev, _vec3 vPos, _vec3 vDir)
{
	CBullet* pBullet = new CBullet(pGraphicDev, vPos, vDir);
	if (FAILED(pBullet->Ready_GameObject()))
	{
		Safe_Release(pBullet);
		MSG_BOX("pBullet Create Failed");
		return nullptr;
	}
	return pBullet;
}
void CBullet::Free()
{
	CGameObject::Free();
}