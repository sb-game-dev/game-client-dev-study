#pragma once
#include "Shader.h"
NS_BEGIN(Engine)
class ENGINE_DLL CVertexShader : public CShader
{
private:
	CVertexShader(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	~CVertexShader() = default;
public:
	virtual HRESULT				Initialize_Prototype(const tchar_t* pShaderFilePath, const D3D11_INPUT_ELEMENT_DESC* pElements, uint32_t iNumElements, const char_t* pEntryPoint, const char_t* pTarget);
	virtual HRESULT				Initialize(void* pArg) override;

	virtual void				Bind_Shader()		{ m_pContext->VSSetShader(m_pVS.Get(), nullptr, 0); }
	ComPtr<ID3D11VertexShader>	Get_Shader()		{ return m_pVS; }
	ComPtr<ID3D11InputLayout>	Get_InputLayout()	{ return m_pInputLayout; }

private:
	ComPtr<ID3D11VertexShader>				m_pVS = { nullptr };
	ComPtr<ID3D11InputLayout>				m_pInputLayout = { nullptr };

public:
	static shared_ptr<CVertexShader> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext,
											const tchar_t* pShaderFilePath, const D3D11_INPUT_ELEMENT_DESC* pElements, uint32_t iNumElements,
											const char_t* pEntryPoint = "main", const char_t* pTarget = "vs_5_0");
	virtual shared_ptr<CPrototype> Clone(void* pArg) override;

};

NS_END	