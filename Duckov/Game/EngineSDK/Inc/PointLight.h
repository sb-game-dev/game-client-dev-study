#pragma once
#include "Engine_Defines.h"
#include "Light.h"
NS_BEGIN(Engine)

class ENGINE_DLL CPointLight abstract : public CLight
{
protected:
	CPointLight(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	~CPointLight() = default;

public:
	virtual void	Priority_Update(f32_t fDeltaTime) PURE;
	virtual void	Update(f32_t fDeltaTime) PURE;
	virtual void	Late_Update(f32_t fDeltaTime) PURE;

protected:
	PointLight				m_tPointLight = {};

};

NS_END