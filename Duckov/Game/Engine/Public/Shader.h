#pragma once

#include "Component.h"

NS_BEGIN(Engine)

class ENGINE_DLL CShader abstract : public CComponent
{
protected:
	CShader(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	virtual ~CShader() = default;


public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;

protected:
	ComPtr<ID3DBlob>						m_pShaderByteCode = { nullptr };

public:
	virtual shared_ptr<CPrototype> Clone(void* pArg) = 0;
};

NS_END