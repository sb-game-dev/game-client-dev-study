#include "VertexShader.h"

CVertexShader::CVertexShader(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	: CShader { pDevice, pContext }
{
}

HRESULT CVertexShader::Initialize_Prototype(const tchar_t* pShaderFilePath, const D3D11_INPUT_ELEMENT_DESC* pElements, uint32_t iNumElements)
{
	return S_OK;
}

HRESULT CVertexShader::Initialize(void* pArg)
{
	return S_OK;
}

shared_ptr<CVertexShader> CVertexShader::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, const tchar_t* pShaderFilePath, const D3D11_INPUT_ELEMENT_DESC* pElements, uint32_t iNumElements)
{
    auto pInstance = shared_ptr<CVertexShader>(new CVertexShader(pDevice, pContext));

    if (FAILED(pInstance->Initialize_Prototype(pShaderFilePath, pElements, iNumElements)))
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