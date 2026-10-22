#pragma once

#include "Shader.h"

NS_BEGIN(Engine)

class ENGINE_DLL CVertexShader final : public CShader
{
private:
	CVertexShader(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	virtual ~CVertexShader() = default;


public:
	virtual HRESULT Initialize_Prototype(const tchar_t* pShaderFilePath, const D3D11_INPUT_ELEMENT_DESC* pElements, uint32_t iNumElements);
	virtual HRESULT Initialize(void* pArg) override;

private:
	ComPtr<ID3D11VertexShader>				m_pVS = { nullptr };
	ComPtr<ID3D11InputLayout>				m_pInputLayout = { nullptr };

public:
	static shared_ptr<CVertexShader> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, const tchar_t* pShaderFilePath, const D3D11_INPUT_ELEMENT_DESC* pElements, uint32_t iNumElements);
	virtual shared_ptr<CPrototype> Clone(void* pArg) override;
};

NS_END