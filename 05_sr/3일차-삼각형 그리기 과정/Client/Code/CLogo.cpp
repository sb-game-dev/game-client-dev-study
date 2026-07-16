#include "pch.h"
#include "CLogo.h"
#include "CBackGround.h"

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
    CScene::Render_Scene();
}

HRESULT CLogo::Ready_Environment_Layer(const _tchar* pLayerTag)
{
    CLayer* pLayer = CLayer::Create();
    
    if (nullptr == pLayer)
        return E_FAIL;

    CGameObject* pGameObject = nullptr;

    // backGround
    pGameObject = CBackGround::Create(m_pGraphicDev);
    
    if (nullptr == pGameObject)
        return E_FAIL;

    if (FAILED(pLayer->Add_GameObject(L"BackGround", pGameObject)))
        return E_FAIL;

    // Player
    //pGameObject = CPlayer::Create(m_pGraphicDev);
    //
    //if (nullptr == pGameObject)
    //    return E_FAIL;
    //
    //if (FAILED(pLayer->Add_GameObject(L"Player", pGameObject)))
    //    return E_FAIL;
    //
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
