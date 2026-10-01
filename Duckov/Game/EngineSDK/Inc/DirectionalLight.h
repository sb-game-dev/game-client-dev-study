#pragma once
#include "Engine_Defines.h"
#include "Light.h"

NS_BEGIN(Engine)

class ENGINE_DLL CDirectionalLight abstract : public CLight
{
protected:
	CDirectionalLight(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	~CDirectionalLight() = default;

public:
	virtual void	Priority_Update(f32_t fDeltaTime) PURE;
	virtual void	Update(f32_t fDeltaTime) PURE;
	virtual void	Late_Update(f32_t fDeltaTime) PURE;

protected:
	DirectionalLight				m_tDirectionalLight = {};
};

NS_END