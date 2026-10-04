#pragma once
#include "Client_Defines.h"
NS_BEGIN(Client)

class CBackGround : public CGameObject
{
private:
	CBackGround(ComPtr<ID3D11Device> pDevice,ComPtr<ID3D11DeviceContext> pContext);
public:
	virtual ~CBackGround() = default;

public:
	virtual		HRESULT		Initialize_Prototype() override;
	virtual		HRESULT		Initialize(void* pArg) override;
	virtual		void		Priority_Update(f32_t fTimeDelta)override;
	virtual		void		Update(f32_t fTimeDelta)override;
	virtual		void		Late_Update(f32_t fTimeDelta)override;
	virtual		HRESULT		Render() override;

private:
	ComPtr<ID3D11ShaderResourceView>	m_pSRV;			//텍스처
	ComPtr<ID3D11SamplerState>			m_pSampler;		//샘플러
	MATERIAL							m_tMaterial;	//머티리얼

public:
	static shared_ptr<CBackGround> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
	virtual shared_ptr<CPrototype> Clone(void* pArg) override;

};

NS_END