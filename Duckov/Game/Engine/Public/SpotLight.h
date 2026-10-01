#pragma once
#include "Engine_Defines.h"
#include "Light.h"
NS_BEGIN(Engine)

class ENGINE_DLL CSpotLight abstract : public CLight
{
protected:
	CSpotLight(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	~CSpotLight() = default;

public:
	virtual void	Priority_Update(f32_t fDeltaTime) PURE;
	virtual void	Update(f32_t fDeltaTime) PURE;
	virtual void	Late_Update(f32_t fDeltaTime) PURE;

protected:
	SpotLight				m_tSpotLight = {};
};

NS_END