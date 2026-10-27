#include "PixelShader.h"

CPixelShader::CPixelShader(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	: CShader { pDevice, pContext }
{
}

HRESULT CPixelShader::Initialize_Prototype(const tchar_t* pShaderFilePath, const char_t* pEntryPoint, const char_t* pTarget)
{
    uint32_t        iFlag = {};

#ifdef _DEBUG
    iFlag |= D3DCOMPILE_SKIP_OPTIMIZATION | D3DCOMPILE_DEBUG;
#else
    iFlag |= D3DCOMPILE_OPTIMIZATION_LEVEL1;
#endif    

    if (FAILED(D3DCompileFromFile(pShaderFilePath, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, pEntryPoint, pTarget, iFlag, 0, &m_pShaderByteCode, nullptr)))
        return E_FAIL;

    if (FAILED(m_pDevice->CreatePixelShader(m_pShaderByteCode->GetBufferPointer(), m_pShaderByteCode->GetBufferSize(), nullptr, &m_pPS)))
        return E_FAIL;

	return S_OK;
}

HRESULT CPixelShader::Initialize(void* pArg)
{
	return S_OK;
}

HRESULT CPixelShader::Begin()
{
    m_pContext->PSSetShader(m_pPS.Get(), nullptr, 0);

    return S_OK;
}

shared_ptr<CPixelShader> CPixelShader::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, const tchar_t* pShaderFilePath, const char_t* pEntryPoint, const char_t* pTarget)
{
    auto pInstance = shared_ptr<CPixelShader>(new CPixelShader(pDevice, pContext));

    if (FAILED(pInstance->Initialize_Prototype(pShaderFilePath, pEntryPoint, pTarget)))
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