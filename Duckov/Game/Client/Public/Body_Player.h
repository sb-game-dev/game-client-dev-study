#pragma once
#include"Client_Defines.h"
#include "PartObject.h"
NS_BEGIN(Client)
class CBody_Player:public CPartObject
{
public:
	typedef struct tagBodyDesc : public CPartObject::PARTOBJECT_DESC
	{

	}BODY_DESC;
private:
	CBody_Player(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	virtual ~CBody_Player() = default;

public:
	const float4x4_t* Get_SocketMatrix(const char_t* pBoneName);

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	
	virtual void Priority_Update(f32_t fTimeDelta) override;
	virtual void Update(f32_t fTimeDelta) override;
	virtual void Late_Update(f32_t fTimeDelta) override;
	
	virtual HRESULT Render() override;
	virtual HRESULT	Render_Reflection(const matrix_t& matReflect) override;
	virtual HRESULT	Render_Shadow() override;
	virtual HRESULT	Render_Occluded() override;

private:
	float4_t						m_vGroundPlane = { 0.f, 1.f, 0.f, 0.f };

	shared_ptr<CModel>				m_pModelCom = { nullptr };
	shared_ptr<CVertexShader>		m_pVSCom = { nullptr };
	shared_ptr<CPixelShader>		m_pPSCom = { nullptr };
	shared_ptr<CPixelShader>		m_pPS_Shadow = { nullptr };
	shared_ptr<CPixelShader>		m_pPS_Occluded = { nullptr };
	ComPtr<ID3D11RasterizerState>	m_pRS_Reflect = { nullptr };


	shared_ptr<CConstantBuffer>		m_pCB = { nullptr };
	CB_PER_OBJECT					m_tCBData = {};

private:
	PLAYER_ANIM						m_eLowerMoveState = { PLAYER_ANIM::END };
	PLAYER_ANIM						m_eUpperMoveState = { PLAYER_ANIM::END };

private:
	HRESULT Ready_Components();
	HRESULT Ready_ConstantBuffer();
	HRESULT Update_ConstantBuffer(const matrix_t& matWorld);

	HRESULT Bind_Shader(shared_ptr<CVertexShader> pVS = nullptr, shared_ptr<CPixelShader> pPS = nullptr);
	HRESULT Bind_ShaderResources(const matrix_t& matWorld);
	
	HRESULT	Render_Mesh(const matrix_t& matWorld, ID3D11RasterizerState* pRS, shared_ptr<CPixelShader> pPS);


public:
	static shared_ptr<CBody_Player> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
	virtual shared_ptr<CPrototype> Clone(void* pArg) override;
};

NS_END