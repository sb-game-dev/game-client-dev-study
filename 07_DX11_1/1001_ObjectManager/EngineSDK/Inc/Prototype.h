#pragma once

#include "Engine_Defines.h"

NS_BEGIN(Engine)

class ENGINE_DLL CPrototype abstract
{
protected:
	CPrototype(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	virtual ~CPrototype() = default;

public:
	virtual HRESULT Initialize_Prototype() = 0;
	virtual HRESULT Initialize(void* pArg) = 0;

protected:
	ComPtr<ID3D11Device>				m_pDevice = { nullptr };
	ComPtr<ID3D11DeviceContext>			m_pContext = { nullptr };\

public:
	virtual shared_ptr<CPrototype> Clone(void* pArg) = 0;

};

NS_END