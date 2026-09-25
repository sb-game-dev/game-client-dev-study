#include "Level_Loding.h"

CLevel_Loding::CLevel_Loding(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    :CLevel{ pDevice,pContext }
{
}

HRESULT CLevel_Loding::Initialize()
{
    if (FAILED(__super::Initialize()))
        return E_FAIL;
    return S_OK;
}

void CLevel_Loding::Update(f32_t fDeltaTime)
{
    __super::Update(fDeltaTime);
}

HRESULT CLevel_Loding::Render()
{
    if (FAILED(__super::Render()))
        return E_FAIL;
    return S_OK;
}


shared_ptr<CLevel_Loding> CLevel_Loding::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    return shared_ptr<CLevel_Loding>(new CLevel_Loding(pDevice, pContext));
}