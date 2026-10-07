#pragma once
#include "Client_Defines.h"
#include "GameObject.h"
NS_BEGIN(Client)
class CFog : public CGameObject
{
private:
	CFog(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	~CFog() = default;

public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);
	virtual void	Priority_Update(const f32_t fDeltaTime);
	virtual void	Update(const f32_t fDeltaTime);
	virtual void	Late_Update(const f32_t fDeltaTime);

private:
	ComPtr<ID3D11Buffer>	m_pCBFog = { nullptr };

public:
	static shared_ptr<CFog> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
	shared_ptr<CPrototype> Clone(void* pArg) override;
};

NS_END