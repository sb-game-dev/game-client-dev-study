#include "Level_Loading.h"

CLevel_Loading::CLevel_Loading(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    : CLevel { pDevice, pContext }
{
}

HRESULT CLevel_Loading::Initialize()
{
    if (FAILED(__super::Initialize()))
        return E_FAIL;

    return S_OK;
}

void CLevel_Loading::Update(f32_t fTimeDelta)
{
    __super::Update(fTimeDelta);

}

HRESULT CLevel_Loading::Render()
{
    if (FAILED(__super::Render()))
        return E_FAIL;
    

    return S_OK;
}

shared_ptr<CLevel_Loading> CLevel_Loading::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto pInstance = shared_ptr<CLevel_Loading>(new CLevel_Loading(pDevice, pContext));

    if (FAILED(pInstance->Initialize()))
    {
        MSG_BOX("Failed to Created : CLevel_Loading");
        pInstance.reset();
    }

    return pInstance;
}

