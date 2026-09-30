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
	virtual HRESULT	Initialize_Prototype() PURE; // 원형 객체의 Initialize
	virtual HRESULT	Initialize(void* pArg) PURE; // 복사본의 Initialize

protected:
	ComPtr<ID3D11Device>		m_pDevice = {nullptr};
	ComPtr<ID3D11DeviceContext> m_pContext = { nullptr };
public:
	virtual shared_ptr<CPrototype> Clone(void* pArg) PURE;
};

NS_END