#include "Level_Logo.h"

#include "Level_Loading.h"
#include "GameInstance.h"

CLevel_Logo::CLevel_Logo(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    : CLevel{ pDevice, pContext }
{
}

HRESULT CLevel_Logo::Initialize()
{
    if (FAILED(__super::Initialize()))
        return E_FAIL;

    return S_OK;
}

void CLevel_Logo::Update(f32_t fTimeDelta)
{
    __super::Update(fTimeDelta);

    if (GetKeyState(VK_RETURN) & 0x8000)
    {
        if (FAILED(CGameInstance::Get().Change_Level(ETOI(LEVEL::LOADING),
            CLevel_Loading::Create(m_pDevice, m_pContext, LEVEL::GAMEPLAY))))
            return;

        return; 
    }

}

HRESULT CLevel_Logo::Render()
{
    if (FAILED(__super::Render()))
        return E_FAIL;

#ifdef _DEBUG
    SetWindowText(g_hWnd, TEXT("로고 레벨입니다."));
#endif


    return S_OK;
}

shared_ptr<CLevel_Logo> CLevel_Logo::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto pInstance = shared_ptr<CLevel_Logo>(new CLevel_Logo(pDevice, pContext));

    if (FAILED(pInstance->Initialize()))
    {
        MSG_BOX("Failed to Created : CLevel_Logo");
        pInstance.reset();
    }

    return pInstance;
}

