#pragma once
#include "Client_Defines.h"
#include "GameObject.h"
#include "Hill.h"

NS_BEGIN(Client)
class CPlayer : public CGameObject
{
public:
	typedef struct tagPlayerDesc : public GAMEOBJECT_DESC
	{

	}PLAYER_DESC;
private:
	CPlayer(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	~CPlayer() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual	void	Priority_Update(f32_t fDeltaTime) override;
	virtual	void	Update(f32_t fDeltaTime) override;
	virtual	void	Late_Update(f32_t fDeltaTime) override;

	virtual HRESULT	Render() override;
	virtual HRESULT	Render_Reflection(const matrix_t& matReflect) override;
	virtual HRESULT	Render_Shadow() override;
	virtual HRESULT	Render_Occluded() override;

	virtual void	AdjustPosY();

private:
	float4_t						m_vGroundPlane = { 0.f, 1.f, 0.f, 0.f };	// ¹ß¹Ø Æò¸é (a,b,c,d)

	shared_ptr<CVIBuffer_Pyramid>	m_pBufferCom = { nullptr };
	shared_ptr<CVertexShader>		m_pVS = { nullptr };
	shared_ptr<CPixelShader>		m_pPS = { nullptr };
	shared_ptr<CPixelShader>		m_pPS_Shadow = { nullptr };
	shared_ptr<CPixelShader>		m_pPS_Occluded = { nullptr };

	shared_ptr<CConstantBuffer>		m_pCB = { nullptr };
	CB_PER_OBJECT					m_tCBData = {};

	ComPtr<ID3D11RasterizerState>	m_pRS_Reflect = { nullptr };

private:
	HRESULT			Ready_Components();
	HRESULT			Ready_ConstantBuffer();
	HRESULT			Update_ConstantBuffer(const matrix_t& matWorld);
	HRESULT			Render_Mesh(const matrix_t& matWorld, ID3D11RasterizerState* pRS, shared_ptr<CPixelShader> pPS);

	virtual			HRESULT Bind_Shader(shared_ptr<CVertexShader> pVS = nullptr, shared_ptr<CPixelShader> pPS = nullptr);
	virtual			HRESULT Bind_ShaderResources(const matrix_t& matWorld);

	void			KeyInput(f32_t fDeltaTime);
	void			LookAtMouse(f32_t fDeltaTime);

public:
	static shared_ptr<CPlayer> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
	virtual shared_ptr<CPrototype> Clone(void* pArg) override;
};

NS_END