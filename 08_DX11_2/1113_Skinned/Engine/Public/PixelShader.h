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
	virtual HRESULT Initialize_Prototype(const tchar_t* pShaderFilePath, const char_t* pEntryPoint, const char_t* pTarget);
	virtual HRESULT Initialize(void* pArg) override;
	virtual HRESULT Begin() override;
private:
	ComPtr<ID3D11PixelShader>				m_pPS = {nullptr};	

public:
	static shared_ptr<CPixelShader> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, const tchar_t* pShaderFilePath, const char_t* pEntryPoint = "main", const char_t* pTarget = "ps_5_0");
	virtual shared_ptr<CPrototype> Clone(void* pArg) override;
};

NS_END