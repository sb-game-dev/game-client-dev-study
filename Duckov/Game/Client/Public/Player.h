#pragma once
#include "Client_Defines.h"
#include "GameObject.h"
NS_BEGIN(Client)
class CPlayer : public CGameObject
{
private:
	CPlayer(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	~CPlayer() = default;

public:
	virtual HRESULT	Initialize() override;
	virtual	void	Update(f32_t fDeltaTime) override;
	virtual	void	LateUpdate(f32_t fDeltaTime) override;
	virtual HRESULT	Render() override;

private:
	void	KeyInput(f32_t fDeltaTime);
	void	LookAtMouse(f32_t fDeltaTime);

public:
	static shared_ptr<CPlayer> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
};

NS_END