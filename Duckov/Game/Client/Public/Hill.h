#pragma once
#include "Client_Defines.h"
#include "GameObject.h"



NS_BEGIN(Client)
class CHill : public CGameObject
{
public:
	typedef struct tagHillDesc : public GAMEOBJECT_DESC
	{

	}HILL_DESC;
private:
	CHill(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	~CHill() = default;

public:
	virtual HRESULT		Initialize_Prototype() override;
	virtual HRESULT		Initialize(void* pArg) override;
	virtual	void		Priority_Update(f32_t fDeltaTime) override;
	virtual	void		Update(f32_t fDeltaTime) override;
	virtual	void		Late_Update(f32_t fDeltaTime) override;
	virtual HRESULT		Render() override;

	virtual f32_t		GetHeight(f32_t x, f32_t z);
	virtual float4_t	GetPlane(f32_t x, f32_t z);

private:
	shared_ptr<CTexture>			m_pBlendCom = { nullptr };
	shared_ptr<CTexture>			m_pLayerCom = { nullptr };
	shared_ptr<CVIBuffer_Terrain>	m_pBufferCom = { nullptr };
	shared_ptr<CVertexShader>		m_pVS = { nullptr };
	shared_ptr<CPixelShader>		m_pPS = { nullptr };

	shared_ptr<CConstantBuffer>		m_pCB = { nullptr };
	CB_PER_OBJECT_LIT				m_tCBDesc = {};

private:
	HRESULT			Ready_Components();
	HRESULT			Ready_ConstantBuffer();

public:
	static shared_ptr<CHill> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
	virtual shared_ptr<CPrototype> Clone(void* pArg) override;
};

NS_END