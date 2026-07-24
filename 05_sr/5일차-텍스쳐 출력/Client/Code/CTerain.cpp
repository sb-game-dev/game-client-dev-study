#include "pch.h"
#include "CTerain.h"
#include "CProtoMgr.h"

CTerain::CTerain(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
{
}

CTerain::~CTerain()
{
}

HRESULT CTerain::Ready_GameObject()
{
	if (FAILED(Add_Component()))
		return E_FAIL;


	m_pBufferCom->Ready_HeightMap(L"../Bin/Resource/Texture/Terrain/Height1.bmp");
	//m_pTransformCom->m_vScale = { 60.f, 60.f, 60.f };

	return S_OK;
}

_int CTerain::Update_GameObject(const _float& fTimeDelta)
{
	_int iExit = CGameObject::Update_GameObject(fTimeDelta);

	return iExit;
}

void CTerain::LateUpdate_GameObject(const _float& fTimeDelta)
{
	CGameObject::LateUpdate_GameObject(fTimeDelta);
}

void CTerain::Render_GameObject()
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_World());
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	m_pTextureCom->Set_Texture(0);
	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

HRESULT CTerain::Add_Component()
{
	Engine::CComponent* pComponent = nullptr;

	// 1
	pComponent = m_pBufferCom = dynamic_cast<CTerainTex*>(CProtoMgr::GetInstance()->Clone_Prototype(L"Proto_TerainTex"));
	if (nullptr == pComponent)
		return E_FAIL;

	//m_pBufferCom->ReadBmp("../Bin/Resource/Texture/Terrain/Height2.bmp");
	m_mapComponent[ID_STATIC].insert({ L"Com_Buffer", pComponent });

	pComponent = m_pTransformCom = dynamic_cast<CTransform*>(CProtoMgr::GetInstance()->Clone_Prototype(L"Proto_Transform"));
	if (nullptr == pComponent)
		return E_FAIL;

	m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform", pComponent });

	/////////////////////////////////////////////////////////////////

	// Texture
	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(CProtoMgr::GetInstance()->Clone_Prototype(L"Proto_TerainTexture"));
	if (nullptr == pComponent)
		return E_FAIL;

	m_mapComponent[ID_STATIC].insert({ L"Com_Texture", pComponent });
	///////////////////////////////////////////////////////////////////

	return S_OK;
}

CTerain* CTerain::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CTerain* pTerain = new CTerain(pGraphicDev);

	if (FAILED(pTerain->Ready_GameObject()))
	{
		Safe_Release(pTerain);
		MSG_BOX("pTerain Create Failed");
		return nullptr;
	}

	return pTerain;
}

void CTerain::Free()
{
	CGameObject::Free();
}
