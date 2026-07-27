#include "pch.h"
#include "CLogo.h"
#include "CBackGround.h"
#include "CProtoMgr.h"
#include "CFontMgr.h"

#include "CPlayer.h"
#include "CMonster.h"
#include "CCamera.h"
#include <CTerrain.h>

CLogo::CLogo(LPDIRECT3DDEVICE9 pGraphicDev)
    : CScene(pGraphicDev)
{
}

CLogo::~CLogo()
{
}

HRESULT CLogo::Ready_Scene()
{
    if (FAILED(Ready_Prototype()))
        return E_FAIL;    
    
    if (FAILED(Ready_Environment_Layer(L"Environment_Layer")))
        return E_FAIL;
 


    return S_OK;
}

_int CLogo::Update_Scene(const _float& fTimeDelta)
{
    _int    iExit = CScene::Update_Scene(fTimeDelta);

    return iExit;
}

void CLogo::LateUpdate_Scene(const _float& fTimeDelta)
{
    CScene::LateUpdate_Scene(fTimeDelta);
}

void CLogo::Render_Scene()
{
    //_vec2       vPos = { 100.f, 100.f };
    //
    //CFontMgr::GetInstance()->Render_Font(L"Font_Jinji", L"Hello", &vPos, D3DXCOLOR(1.f, 0.f, 0.f, 1.f));

    CScene::Render_Scene();
}

HRESULT CLogo::Ready_Environment_Layer(const _tchar* pLayerTag)
{
    CLayer* pLayer = CLayer::Create();
    
    if (nullptr == pLayer)
        return E_FAIL;

    CGameObject* pGameObject = nullptr;

    // Camera
    pGameObject = CCamera::Create(m_pGraphicDev);
    
    if (nullptr == pGameObject)
        return E_FAIL;
    
    if (FAILED(pLayer->Add_GameObject(L"Camera", pGameObject)))
        return E_FAIL;

    // BackGround
    //pGameObject = CBackGround::Create(m_pGraphicDev);
    //
    //if (nullptr == pGameObject)
    //    return E_FAIL;
    //
    //if (FAILED(pLayer->Add_GameObject(L"BackGround", pGameObject)))
    //    return E_FAIL;

    // Terrain
    pGameObject = CTerrain::Create(m_pGraphicDev);

    if (nullptr == pGameObject)
        return E_FAIL;

    if (FAILED(pLayer->Add_GameObject(L"Terrain", pGameObject)))
        return E_FAIL;

    // Player
    pGameObject = CPlayer::Create(m_pGraphicDev);
    
    if (nullptr == pGameObject)
        return E_FAIL;
    
    if (FAILED(pLayer->Add_GameObject(L"Player", pGameObject)))
        return E_FAIL;
    
    
    //// Monster
    //pGameObject = CMonster::Create(m_pGraphicDev);
    //
    //if (nullptr == pGameObject)
    //    return E_FAIL;
    //
    //if (FAILED(pLayer->Add_GameObject(L"Monster", pGameObject)))
    //    return E_FAIL;


    m_mapLayer.insert({ pLayerTag, pLayer });

    return S_OK;
}

HRESULT CLogo::Ready_Prototype()
{
    if (FAILED(CProtoMgr::GetInstance()->Ready_Prototype(L"Proto_TriCol", Engine::CTriCol::Create(m_pGraphicDev))))
        return E_FAIL;

    if (FAILED(CProtoMgr::GetInstance()->Ready_Prototype(L"Proto_RcCol", Engine::CRcCol::Create(m_pGraphicDev))))
        return E_FAIL;

    if (FAILED(CProtoMgr::GetInstance()->Ready_Prototype(L"Proto_RcTex", Engine::CRcTex::Create(m_pGraphicDev))))
        return E_FAIL;

    if (FAILED(CProtoMgr::GetInstance()->Ready_Prototype(L"Proto_CubeTex", Engine::CCubeTex::Create(m_pGraphicDev))))
        return E_FAIL;

    if (FAILED(CProtoMgr::GetInstance()->Ready_Prototype(L"Proto_Pyramid", Engine::CPyramidCol::Create(m_pGraphicDev))))
        return E_FAIL;

    if (FAILED(CProtoMgr::GetInstance()->Ready_Prototype(L"Proto_TerrainTex", Engine::CTerrainTex::Create(m_pGraphicDev))))
        return E_FAIL;

    if (FAILED(CProtoMgr::GetInstance()->Ready_Prototype(L"Proto_Transform", Engine::CTransform::Create(m_pGraphicDev))))
        return E_FAIL;

    if (FAILED(CProtoMgr::GetInstance()->Ready_Prototype(L"Proto_Camera", Engine::CCameraCom::Create(m_pGraphicDev))))
        return E_FAIL;

    if (FAILED(CProtoMgr::GetInstance()->Ready_Prototype(L"Proto_PlayerTexture", Engine::CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Ma.jpg", 1))))
        return E_FAIL;

    if (FAILED(CProtoMgr::GetInstance()->Ready_Prototype(L"Proto_SkyTexture", Engine::CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/sky.jpg", 1))))
        return E_FAIL;

    if (FAILED(CProtoMgr::GetInstance()->Ready_Prototype(L"Proto_TerrainTexture", Engine::CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Terrain/Terrain0.png", 1))))
        return E_FAIL;

    if (FAILED(CProtoMgr::GetInstance()->Ready_Prototype(L"Proto_BulletTexture", Engine::CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Logo/sana.jpg", 1))))
        return E_FAIL;

    return S_OK;
}

CLogo* CLogo::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
    CLogo* pLogo = new CLogo(pGraphicDev);

    if (FAILED(pLogo->Ready_Scene()))
    {
        Safe_Release(pLogo);
        MSG_BOX("Logo Create Failed");
        return nullptr;
    }

    return pLogo;
}

void CLogo::Free()
{
    CScene::Free();
}
