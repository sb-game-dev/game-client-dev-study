#pragma once
#include "Client_Defines.h"
#include "DirectionalLight.h"
NS_BEGIN(Client)
class CSunLight : public CDirectionalLight
{
private:
	CSunLight(ComPtr<ID3D11Device>pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	~CSunLight() = default;

public:
	HRESULT		 Initialize();
	void		 Priority_Update(f32_t fDeltaTime) override;
	void		 Update(f32_t fDeltaTime) override;
	void		 Late_Update(f32_t fDeltaTime) override;

public:
	static shared_ptr<CSunLight> Create(ComPtr<ID3D11Device>pDevice, ComPtr<ID3D11DeviceContext> pContext);
};

NS_END	