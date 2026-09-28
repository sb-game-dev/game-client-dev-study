#include "Level_Loading.h"
#include "Loader.h"
#include "Level_Logo.h"
#include "Level_GamePlay.h"

CLevel_Loading::CLevel_Loading(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    :CLevel{ pDevice,pContext }
{
}


HRESULT CLevel_Loading::Initialize(LEVEL eNextLevel)
{
    if (FAILED(__super::Initialize()))
        return E_FAIL;
    m_eNextLevelID = eNextLevel;

    /* 다음 레벨을 위한 자원 준비하는 과정*/
    m_pLoader = CLoader::Create(m_pDevice, m_pContext, eNextLevel);
    if (nullptr == m_pLoader)
        return E_FAIL;
    /* 로딩레벨에 필요한 객체들을 생성하는 과정. */
    if (FAILED(Ready_Layer_BackGround()))
        return E_FAIL;

    if (FAILED(Ready_Layer_UI()))
        return E_FAIL;

    return S_OK;
}

void CLevel_Loading::Update(f32_t fDeltaTime)
{
    __super::Update(fDeltaTime);
    if (true == m_pLoader->isFinished() &&
        GetAsyncKeyState(VK_SPACE) & 0x8000)
    {
        shared_ptr<CLevel> pNewLevel = { nullptr };
        switch (m_eNextLevelID)
        {
        case Client::LEVEL::LOGO:
            pNewLevel = CLevel_Logo::Create(m_pDevice,m_pContext);
            break;
        case Client::LEVEL::GAMEPLAY:
            pNewLevel = CLevel_GamePlay::Create(m_pDevice, m_pContext);
            break;
        }

        if (FAILED(CGameInstance::Get().Change_Level(ETOI(m_eNextLevelID), pNewLevel)))
            return;
        return;
    }

}

void CLevel_Loading::LateUpdate(f32_t fDeltaTime)
{
    __super::LateUpdate(fDeltaTime);
}

HRESULT CLevel_Loading::Render()
{
    if (FAILED(__super::Render()))
        return E_FAIL;
#ifdef _DEBUG
    m_pLoader->Draw_Debug();
#endif
    return S_OK;
}


HRESULT CLevel_Loading::Ready_Layer_BackGround()
{
    return S_OK;
}

HRESULT CLevel_Loading::Ready_Layer_UI()
{
    return S_OK;
}

shared_ptr<CLevel_Loading> CLevel_Loading::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, LEVEL eNextLevel)
{
    auto pInstance = shared_ptr<CLevel_Loading>(new CLevel_Loading(pDevice, pContext));

    if (FAILED(pInstance->Initialize(eNextLevel)))
    {
        MSG_BOX("Failed to Created : CLevel_Loading");
        pInstance.reset();
    }

    return pInstance;
}