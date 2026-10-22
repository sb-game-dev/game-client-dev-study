#include "PixelShader.h"

CPixelShader::CPixelShader(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	: CShader { pDevice, pContext }
{
}

HRESULT CPixelShader::Initialize_Prototype(const tchar_t* pShaderFilePath)
{
	return S_OK;
}

HRESULT CPixelShader::Initialize(void* pArg)
{
	return S_OK;
}

shared_ptr<CPixelShader> CPixelShader::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, const tchar_t* pShaderFilePath)
{
    auto pInstance = shared_ptr<CPixelShader>(new CPixelShader(pDevice, pContext));

    if (FAILED(pInstance->Initialize_Prototype(pShaderFilePath)))
    {
        MSG_BOX("Failed to Created : CPixelShader");
        pInstance.reset();
    }

    return pInstance;
}


shared_ptr<CPrototype> CPixelShader::Clone(void* pArg)
{
    auto pInstance = shared_ptr<CPixelShader>(new CPixelShader(*this));

    if (FAILED(pInstance->Initialize(pArg)))
    {
        MSG_BOX("Failed to Cloned : CPixelShader");
        pInstance.reset();
    }

    return pInstance;
}