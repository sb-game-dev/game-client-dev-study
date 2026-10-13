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
	virtual HRESULT	Render_Reflection(const XMMATRIX& matReflect) override;
	virtual HRESULT	Render_Shadow() override;

	virtual void	AdjustPosY();

private:
	ComPtr<ID3D11RasterizerState>	m_pRS_Reflect = { nullptr };
	ComPtr<ID3D11PixelShader>		m_pPS_Shadow = { nullptr };

	float4_t						m_vGroundPlane = { 0.f, 1.f, 0.f, 0.f };	// ¹ß¹Ø Æò¸é (a,b,c,d)

	vector_t	m_vZ_Plus	= XMVector4Normalize({ 0.f,0.f,+1.f,0.f });
	vector_t	m_vZ_Minus	= XMVector4Normalize({ 0.f,0.f,-1.f,0.f });
	vector_t	m_vX_Plus	= XMVector4Normalize({ +1.f,0.f,0.f,0.f });
	vector_t	m_vX_Minus	= XMVector4Normalize({ -1.f,0.f,0.f,0.f });
	vector_t	m_vY_Plus	= XMVector4Normalize({ 0.f,+1.f,0.f,0.f });
	vector_t	m_vY_Minus	= XMVector4Normalize({ 0.f,-1.f,0.f,0.f });
	vector_t	m_vQuad1	= XMVector4Normalize({ +1.f,0.f,+1.f,0.f });
	vector_t	m_vQuad2	= XMVector4Normalize({ -1.f,0.f,+1.f,0.f });
	vector_t	m_vQuad3	= XMVector4Normalize({ -1.f,0.f,-1.f,0.f });
	vector_t	m_vQuad4	= XMVector4Normalize({ +1.f,0.f,-1.f,0.f });

private:
	HRESULT			Render_Mesh(const XMMATRIX& matWorld, ID3D11RasterizerState* pRS) override;
	HRESULT			Render_Mesh(const XMMATRIX& matWorld, ID3D11RasterizerState* pRS, ID3D11PixelShader* pPS);

	void	KeyInput(f32_t fDeltaTime);
	void	LookAtMouse(f32_t fDeltaTime);


public:
	static shared_ptr<CPlayer> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
	virtual shared_ptr<CPrototype> Clone(void* pArg) override;
};

NS_END