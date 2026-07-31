#include "pch.h"
#include "CStage.h"
#include "CBackGround.h"
#include "CProtoMgr.h"
#include "CFontMgr.h"

#include "CPlayer.h"
#include "CMonster.h"
#include "CTerrain.h"
#include "CCamera.h"
#include "CSkyBox.h"
#include "CCameraMgr.h"
#include "CCollisionMgr.h"
#include "CManagement.h"

CStage::CStage(LPDIRECT3DDEVICE9 pGraphicDev)
    : CScene(pGraphicDev)
{
}

CStage::~CStage()
{
}

HRESULT CStage::Ready_Scene()
{
     if (FAILED(Ready_Environment_Layer(L"Environment_Layer")))
        return E_FAIL;

    if (FAILED(Ready_GameLogic_Layer(L"GameLogic_Layer")))
        return E_FAIL;

    if (FAILED(Ready_UI_Layer(L"UI_Layer")))
        return E_FAIL;

    return S_OK;
}

_int CStage::Update_Scene(const _float& fTimeDelta)
{
    _int    iExit = CScene::Update_Scene(fTimeDelta);

    return iExit;
}

void CStage::LateUpdate_Scene(const _float& fTimeDelta)
{
    CScene::LateUpdate_Scene(fTimeDelta);

    CCollider* CPlayerCollider = dynamic_cast<CCollider*>
        (CManagement::GetInstance()->Get_Component(ID_DYNAMIC, L"GameLogic_Layer", L"Player", L"Com_Collider"));

    CCollider* CMonsterCollider = dynamic_cast<CCollider*>
        (CManagement::GetInstance()->Get_Component(ID_DYNAMIC, L"GameLogic_Layer", L"Monster", L"Com_Collider"));

    //CCollisionMgr::GetInstance()->CheckCollision(CMonsterCollider, CPlayerCollider);
}

void CStage::Render_Scene()
{
    //_vec2       vPos = { 100.f, 100.f };    
    //CFontMgr::GetInstance()->Render_Font(L"Font_Jinji", L"Hello", &vPos, D3DXCOLOR(1.f, 0.f, 0.f, 1.f));

    //sCScene::Render_Scene();
}

HRESULT CStage::Ready_Environment_Layer(const _tchar* pLayerTag)
{
    CLayer* pLayer = CLayer::Create();

    if (nullptr == pLayer)
        return E_FAIL;

    CGameObject* pGameObject = nullptr;

    //_vec3   vEye{ 0.f, 10.f, -10.f };
    //_vec3   vAt{ 0.f, 0.f, 1.f };
    //_vec3   vUp{ 0.f, 1.f, 0.f };

    // MainCamera
   
    pGameObject = CCamera::Create(m_pGraphicDev, PLAYER1);
    
    if (nullptr == pGameObject)
        return E_FAIL;
    
    if (FAILED(pLayer->Add_GameObject(L"Camera", pGameObject)))
        return E_FAIL;
    CCameraMgr::GetInstance()->AddCamera(pGameObject);

    // MapCamera

    pGameObject = CCamera::Create(m_pGraphicDev, MAP);
    
    if (nullptr == pGameObject)
        return E_FAIL;
    
    if (FAILED(pLayer->Add_GameObject(L"MapCamera", pGameObject)))
        return E_FAIL;
    CCameraMgr::GetInstance()->AddCamera(pGameObject);

       
    // Terrain
    pGameObject = CTerrain::Create(m_pGraphicDev);

    if (nullptr == pGameObject)
        return E_FAIL;

    if (FAILED(pLayer->Add_GameObject(L"Terrain", pGameObject)))
        return E_FAIL;

    // SkyBox
    pGameObject = CSkyBox::Create(m_pGraphicDev);

    if (nullptr == pGameObject)
        return E_FAIL;

    if (FAILED(pLayer->Add_GameObject(L"SkyBox", pGameObject)))
        return E_FAIL;
    m_mapLayer.insert({ pLayerTag, pLayer });

    return S_OK;
}

HRESULT CStage::Ready_GameLogic_Layer(const _tchar* pLayerTag)
{
    CLayer* pLayer = CLayer::Create();

    if (nullptr == pLayer)
        return E_FAIL;

    CGameObject* pGameObject = nullptr;

    // Player
    pGameObject = CPlayer::Create(m_pGraphicDev);

    if (nullptr == pGameObject)
        return E_FAIL;

    if (FAILED(pLayer->Add_GameObject(L"Player", pGameObject)))
        return E_FAIL;

    // Monster
    pGameObject = CMonster::Create(m_pGraphicDev);
    
    if (nullptr == pGameObject)
        return E_FAIL;
    
    if (FAILED(pLayer->Add_GameObject(L"Monster", pGameObject)))
        return E_FAIL;
    
    m_mapLayer.insert({ pLayerTag, pLayer });

    return S_OK;
}

HRESULT CStage::Ready_UI_Layer(const _tchar* pLayerTag)
{
    CLayer* pLayer = CLayer::Create();

    if (nullptr == pLayer)
        return E_FAIL;

    CGameObject* pGameObject = nullptr;



    m_mapLayer.insert({ pLayerTag, pLayer });

    return S_OK;
}

HRESULT CStage::Ready_Prototype()
{
    if (FAILED(CProtoMgr::GetInstance()->Ready_Prototype(L"Proto_TriCol", Engine::CTriCol::Create(m_pGraphicDev))))
        return E_FAIL;

    if (FAILED(CProtoMgr::GetInstance()->Ready_Prototype(L"Proto_RcCol", Engine::CRcCol::Create(m_pGraphicDev))))
        return E_FAIL;

    if (FAILED(CProtoMgr::GetInstance()->Ready_Prototype(L"Proto_RcTex", Engine::CRcTex::Create(m_pGraphicDev))))
        return E_FAIL;

    if (FAILED(CProtoMgr::GetInstance()->Ready_Prototype(L"Proto_Transform", Engine::CTransform::Create(m_pGraphicDev))))
        return E_FAIL;

    if (FAILED(CProtoMgr::GetInstance()->Ready_Prototype(L"Proto_PlayerTexture", Engine::CTexture::Create(m_pGraphicDev, TEX_NORMAL, L"../Bin/Resource/Texture/Player/Ma.jpg", 1))))
        return E_FAIL;


    return S_OK;
}

CStage* CStage::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
    CStage* pStage = new CStage(pGraphicDev);

    if (FAILED(pStage->Ready_Scene()))
    {
        Safe_Release(pStage);
        MSG_BOX("pStage Create Failed");
        return nullptr;
    }

    return pStage;
}

void CStage::Free()
{
    CScene::Free();
}
