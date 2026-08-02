#include "pch.h"
#include "CSkyBox.h"
#include "CProtoMgr.h"
#include "CRenderer.h"
#include "CCameraMgr.h"

CSkyBox::CSkyBox(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
}

CSkyBox::~CSkyBox()
{
}

HRESULT CSkyBox::Ready_GameObject()
{
	if (FAILED(Add_Component()))
	{
		return E_FAIL;
	}
	float fScale = 200.f;
	m_pTransformCom->m_vScale = { fScale,fScale,fScale };
	CRenderer::GetInstance()->Add_RenderGroup(RENDER_PRIORITY, this);
	return S_OK;
}

_int CSkyBox::Update_GameObject(const _float& fTimeDelta)
{
	_int iExit = CGameObject::Update_GameObject(fTimeDelta);

	return iExit;
}

void CSkyBox::LateUpdate_GameObject(const _float& fTimeDelta)
{
	CGameObject::LateUpdate_GameObject(fTimeDelta);


	_matrix	matView;
	matView = CCameraMgr::GetInstance()->GetCameraView(PLAYER1);

	D3DXMatrixInverse(&matView, 0, &matView);
	m_pTransformCom->Set_Pos(matView._41, matView._42 + 3.f, matView._43);
}

void CSkyBox::Render_GameObject()
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_World());
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	m_pTextureCom->Set_Texture(0);
	m_pBufferCom->Render_Buffer();
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

HRESULT CSkyBox::Add_Component()
{
	Engine::CComponent* pComponent = nullptr;

	// CubeTex
	pComponent = m_pBufferCom = dynamic_cast<CCubeTex*>(CProtoMgr::GetInstance()->Clone_Prototype(L"Proto_CubeTex", this));
	if (nullptr == pComponent)
		return E_FAIL;
	m_mapComponent[ID_STATIC].insert({ L"Com_Buffer", pComponent });

	// Transform
	pComponent = m_pTransformCom = dynamic_cast<CTransform*>(CProtoMgr::GetInstance()->Clone_Prototype(L"Proto_Transform", this));
	if (nullptr == pComponent)
		return E_FAIL;
	m_mapComponent[ID_DYNAMIC].insert({ L"Com_Transform", pComponent });

	// Texture
	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(CProtoMgr::GetInstance()->Clone_Prototype(L"Proto_SkyBoxTexture", this));
	if (nullptr == pComponent)
		return E_FAIL;
	m_mapComponent[ID_STATIC].insert({ L"Com_Texture", pComponent });

	return S_OK;
}

CSkyBox* CSkyBox::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CSkyBox* pSkyBox = new CSkyBox(pGraphicDev);

	if (FAILED(pSkyBox->Ready_GameObject()))
	{
		Safe_Release(pSkyBox);
		return nullptr;
	}
	return pSkyBox;
}
void CSkyBox::Free() 
{
	CGameObject::Free();
}