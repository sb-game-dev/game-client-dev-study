#include "Light.h"

#include "ConstantBuffer.h"

CLight::CLight(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	: m_pDevice { pDevice }
	, m_pContext { pContext }
{
}

HRESULT CLight::Initialize(LIGHT eType, const LIGHT_DESC& LightDesc)
{
    m_eType = eType;

    m_LightDesc = LightDesc;

    m_pCB = CConstantBuffer::Create(m_pDevice, m_pContext, &m_LightDesc, sizeof m_LightDesc);
    if (nullptr == m_pCB)
        return E_FAIL;

    return S_OK;
}

HRESULT CLight::Bind_Pixel_ShaderResouce(uint32_t iSlot)
{
    return m_pCB->Bind_Pixel_ShaderResource(iSlot, &m_LightDesc);    
}

shared_ptr<CLight> CLight::Create(LIGHT eType, ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, const LIGHT_DESC& LightDesc)
{
    auto pInstance = shared_ptr<CLight>(new CLight(pDevice, pContext));

    if (FAILED(pInstance->Initialize(eType, LightDesc)))
    {
        MSG_BOX("Failed to Created : CLight");
        pInstance.reset();
    }

    return pInstance;
}
