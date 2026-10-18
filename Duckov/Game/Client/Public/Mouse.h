#pragma once
#include "Client_Defines.h"
#include "GameObject.h"
class CMouse : public CGameObject
{
private:
	CMouse(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	~CMouse() = default;

public:
	virtual HRESULT		Initialize_Prototype() override;
	virtual HRESULT		Initialize(void* pArg) override;

	virtual	void	Priority_Update(f32_t fDeltaTime) override;
	virtual	void	Update(f32_t fDeltaTime) override;
	virtual	void	Late_Update(f32_t fDeltaTime) override;

	virtual HRESULT	Render() override;
public:
	static shared_ptr<CMouse> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
	shared_ptr<CPrototype> Clone(void* pArg) override;
};

