#pragma once
#include "Shader.h"
NS_BEGIN(Engine)
class ENGINE_DLL CPixelShader : public CShader
{
private:
	CPixelShader(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	~CPixelShader() = default;
public:
	virtual HRESULT Initialize_Prototype(const tchar_t* pShaderFilePath, const char_t* pMainName);
	virtual HRESULT Initialize(void* pArg) override;

	virtual void	Bind_Shader() { m_pContext->PSSetShader(m_pPS.Get(), nullptr, 0); }
	ComPtr<ID3D11PixelShader>	Get_Shader() { return m_pPS; }
private:
	ComPtr<ID3D11PixelShader>				m_pPS = { nullptr };

public:
	static shared_ptr<CPixelShader> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext,
											const tchar_t* pShaderFilePath, const char_t* pMainName);
	virtual shared_ptr<CPrototype> Clone(void* pArg) override;

};

NS_END