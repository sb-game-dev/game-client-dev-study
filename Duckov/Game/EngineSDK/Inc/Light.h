#pragma once
#include "Engine_Defines.h"
NS_BEGIN(Engine)
class ENGINE_DLL CLight abstract
{
protected:
	CLight(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	~CLight() = default;

public:
	virtual void	Priority_Update(f32_t fDeltaTime) PURE;
	virtual void	Update(f32_t fDeltaTime) PURE;
	virtual void	Late_Update(f32_t fDeltaTime) PURE;

protected:
	ComPtr<ID3D11Device>		m_pDevice = { nullptr };
	ComPtr<ID3D11DeviceContext> m_pContext = { nullptr };

	ComPtr<ID3D11Buffer>		m_pLightCB = { nullptr };
};

NS_END