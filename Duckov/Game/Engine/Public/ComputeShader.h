#pragma once
#include "Shader.h"
NS_BEGIN(Engine)
class ENGINE_DLL CComputeShader : public CShader
{
private:
	CComputeShader(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	~CComputeShader() = default;
public:
	virtual HRESULT Initialize_Prototype(const tchar_t* pShaderFilePath, const char_t* pMainName);
	virtual HRESULT Initialize(void* pArg) override;

	virtual void	Bind_Shader() { m_pContext->CSSetShader(m_pCS.Get(), nullptr, 0); }
	ComPtr<ID3D11ComputeShader>	Get_Shader() { return m_pCS; }
private:
	ComPtr<ID3D11ComputeShader>				m_pCS = { nullptr };

public:
	static shared_ptr<CComputeShader> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext,
											 const tchar_t* pShaderFilePath, const char_t* pMainName);
	virtual shared_ptr<CPrototype> Clone(void* pArg) override;

};

NS_END