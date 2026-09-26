#pragma once
#include "Client_Defines.h"
#include "GameObject.h"
NS_BEGIN(Client)
class CCube : public CGameObject
{
private:
	CCube(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	~CCube() = default;

public:
	virtual HRESULT	Initialize() override;
	virtual	void	Update(f32_t fDeltaTime) override;
	virtual	void	LateUpdate(f32_t fDeltaTime) override;
	virtual HRESULT	Render() override;

	virtual	void	SetPlayer() { m_bPlayer = true; }
private:
	_bool	m_bPlayer = false;

private:
	void	KeyInput(f32_t fDeltaTime);


public:
	static shared_ptr<CCube> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
};

NS_END