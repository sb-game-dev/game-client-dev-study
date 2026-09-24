#include "Level_Logo.h"

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

}

HRESULT CLevel_Logo::Render()
{
    if (FAILED(__super::Render()))
        return E_FAIL;


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

