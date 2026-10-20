#include "Shader.h"

CShader::CShader(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	:CComponent{pDevice, pContext}
{
}

HRESULT CShader::Initialize_Prototype()
{
	return S_OK;
}

HRESULT CShader::Initialize(void* pArg)
{
	return S_OK;
}
