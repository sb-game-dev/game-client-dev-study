#include "Level_GamePlay.h"
#include "Cube.h"
CLevel_GamePlay::CLevel_GamePlay(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    :CLevel{ pDevice,pContext }
{
}

HRESULT CLevel_GamePlay::Initialize()
{
    if (FAILED(__super::Initialize()))
        return E_FAIL;

    m_pCamera = CQuarterView_Cam::Create(m_pDevice, m_pContext);

    shared_ptr<CGameObject> pGameObject = {};
    pGameObject = CCube::Create(m_pDevice, m_pContext);
    pGameObject->SetPos({ 0.f,0.f,0.f });
    dynamic_pointer_cast<CCube>(pGameObject)->SetPlayer();
    m_mapObject.insert({ L"Player" ,pGameObject });

    m_pCamera->SetPlayer(pGameObject);

    pGameObject = CCube::Create(m_pDevice, m_pContext);
    pGameObject->SetPos({ 0.f,0.f,5.f });
    m_mapObject.insert({ L"Cube" ,pGameObject });


    return S_OK;
}

void CLevel_GamePlay::Update(f32_t fDeltaTime)
{
    __super::Update(fDeltaTime);
    m_pCamera->Update(fDeltaTime);
}


void CLevel_GamePlay::LateUpdate(f32_t fDeltaTime)
{
    __super::LateUpdate(fDeltaTime);
    m_pCamera->LateUpdate(fDeltaTime);
}

HRESULT CLevel_GamePlay::Render()
{
    if (FAILED(m_pCamera->Bind()))
        return E_FAIL;
    if (FAILED(__super::Render()))
        return E_FAIL;
    return S_OK;
}


shared_ptr<CLevel_GamePlay> CLevel_GamePlay::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto pInstance = shared_ptr<CLevel_GamePlay>(new CLevel_GamePlay(pDevice, pContext));
    if (FAILED(pInstance->Initialize()))
        pInstance.reset();

    return pInstance;
}