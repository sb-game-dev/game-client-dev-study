#pragma once
#include "Client_Defines.h"
#include "SpotLight.h"
NS_BEGIN(Client)
class CPlayer_SpotLight : public CSpotLight
{
private:
	CPlayer_SpotLight(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext>pContext);
public:
	~CPlayer_SpotLight() = default;

public:
	HRESULT		 Initialize();
	virtual void Priority_Update(f32_t fDeltaTime) override;
	virtual void Update(f32_t fDeltaTime) override;
	virtual void Late_Update(f32_t fDeltaTime) override;

	void	SetPlayer(shared_ptr<class CGameObject> pPlayer) { m_pPlayer = pPlayer; }

private:
	shared_ptr<class CGameObject> m_pPlayer;

public:
	static shared_ptr<CPlayer_SpotLight> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext>pContext);

};

NS_END