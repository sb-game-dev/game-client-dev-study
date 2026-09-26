#pragma once
#include "Client_Defines.h"
#include "GameObject.h"
NS_BEGIN(Client)
class CHill : public CGameObject
{
private:
	CHill(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	~CHill() = default;

public:
	virtual HRESULT	Initialize() override;
	virtual	void	Update(f32_t fDeltaTime) override;
	virtual	void	LateUpdate(f32_t fDeltaTime) override;
	virtual HRESULT	Render() override;

	virtual f32_t	GetHeight(f32_t x, f32_t z) { return 0.3f * (z * sinf(0.1f * x) + x * cosf(0.1f * z)); }
public:
	static shared_ptr<CHill> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
};

NS_END