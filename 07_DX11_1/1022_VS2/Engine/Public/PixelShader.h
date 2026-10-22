#pragma once

#include "Shader.h"

NS_BEGIN(Engine)

class ENGINE_DLL CPixelShader final : public CShader
{
private:
	CPixelShader(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	virtual ~CPixelShader() = default;


public:
	virtual HRESULT Initialize_Prototype(const tchar_t* pShaderFilePath);
	virtual HRESULT Initialize(void* pArg) override;

private:
	ComPtr<ID3D11PixelShader>				m_pPS = {nullptr};	

public:
	static shared_ptr<CPixelShader> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, const tchar_t* pShaderFilePath);
	virtual shared_ptr<CPrototype> Clone(void* pArg) override;
};

NS_END