#include "Fog.h"

CFog::CFog(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    :CGameObject{pDevice,pContext}
{

}

HRESULT CFog::Initialize_Prototype()
{
    if (FAILED(__super::Initialize_Prototype()))
        return E_FAIL;
    return S_OK;
}

HRESULT CFog::Initialize(void* pArg)
{
    if (FAILED(__super::Initialize(pArg)))
        return E_FAIL;

    // 상수 버퍼 생성
    D3D11_BUFFER_DESC CBDesc{};
    CBDesc.ByteWidth = sizeof(CB_FOG);
    CBDesc.Usage = D3D11_USAGE_DEFAULT;
    CBDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

    // 상수 버퍼를 초기화 할 때 SubResource는 nullptr로 설정. 나중에 UpdateSubresource 할 예정
    if (FAILED(m_pDevice->CreateBuffer(&CBDesc, nullptr, m_pCBFog.GetAddressOf())))
        return E_FAIL;

    CB_FOG cbFog{};
    cbFog.FogColor = { 0.75, 0.75, 0.75, 1 };
    cbFog.FogStart = 1.f;
    cbFog.FogRange = 175.f;

    m_pContext->UpdateSubresource(m_pCBFog.Get(), 0, nullptr, &cbFog, 0, 0);

    m_pContext->PSSetConstantBuffers(5, 1, m_pCBFog.GetAddressOf());
    return S_OK;
}

void CFog::Priority_Update(const f32_t fDeltaTime)
{
    __super::Priority_Update(fDeltaTime);
}

void CFog::Update(const f32_t fDeltaTime)
{
    __super::Update(fDeltaTime);
}

void CFog::Late_Update(const f32_t fDeltaTime)
{
    __super::Late_Update(fDeltaTime);
}

shared_ptr<CFog> CFog::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto pInstance = shared_ptr<CFog>(new CFog(pDevice, pContext));

    if (FAILED(pInstance->Initialize_Prototype()))
    {
        MSG_BOX("Create Failed : CFog");
        pInstance.reset();
    }
    return pInstance;
}

shared_ptr<CPrototype> CFog::Clone(void* pArg)
{
    auto pInstance = shared_ptr<CFog>(new CFog(*this));

    if (FAILED(pInstance->Initialize(pArg)))
    {
        MSG_BOX("Clone Failed : CFog");
        pInstance.reset();
    }
    return pInstance;
}