#include "VertexShader.h"

CVertexShader::CVertexShader(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	: CShader { pDevice, pContext }
{
}

HRESULT CVertexShader::Initialize_Prototype(const tchar_t* pShaderFilePath, const D3D11_INPUT_ELEMENT_DESC* pElements, uint32_t iNumElements, const char_t* pEntryPoint, const char_t* pTarget)
{
    uint32_t        iFlag = {};

#ifdef _DEBUG
    iFlag |= D3DCOMPILE_SKIP_OPTIMIZATION | D3DCOMPILE_DEBUG;
#else
    iFlag |= D3DCOMPILE_OPTIMIZATION_LEVEL1;
#endif    

    if (FAILED(D3DCompileFromFile(pShaderFilePath, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, pEntryPoint, pTarget, iFlag, 0, &m_pShaderByteCode, nullptr)))
        return E_FAIL;

    if (FAILED(m_pDevice->CreateVertexShader(m_pShaderByteCode->GetBufferPointer(), m_pShaderByteCode->GetBufferSize(), nullptr, &m_pVS)))
        return E_FAIL;

    if (FAILED(m_pDevice->CreateInputLayout(pElements, iNumElements, m_pShaderByteCode->GetBufferPointer(), m_pShaderByteCode->GetBufferSize(), &m_pInputLayout)))
        return E_FAIL;

	return S_OK;
}

HRESULT CVertexShader::Initialize(void* pArg)
{
	return S_OK;
}

HRESULT CVertexShader::Begin()
{
    m_pContext->VSSetShader(m_pVS.Get(), nullptr, 0);

    m_pContext->IASetInputLayout(m_pInputLayout.Get());

    return S_OK;
}

shared_ptr<CVertexShader> CVertexShader::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, const tchar_t* pShaderFilePath, const D3D11_INPUT_ELEMENT_DESC* pElements, uint32_t iNumElements, const char_t* pEntryPoint, const char_t* pTarget)
{
    auto pInstance = shared_ptr<CVertexShader>(new CVertexShader(pDevice, pContext));

    if (FAILED(pInstance->Initialize_Prototype(pShaderFilePath, pElements, iNumElements, pEntryPoint, pTarget)))
    {
        MSG_BOX("Failed to Created : CVertexShader");
        pInstance.reset();
    }

    return pInstance;
}


shared_ptr<CPrototype> CVertexShader::Clone(void* pArg)
{
    auto pInstance = shared_ptr<CVertexShader>(new CVertexShader(*this));

    if (FAILED(pInstance->Initialize(pArg)))
    {
        MSG_BOX("Failed to Cloned : CVertexShader");
        pInstance.reset();
    }

    return pInstance;
}