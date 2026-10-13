#pragma once
#include "Client_Defines.h"
#include "GameObject.h"
NS_BEGIN(Client)
class CCube : public CGameObject
{
public:
	typedef struct tagCubeDesc : public GAMEOBJECT_DESC
	{
		
	}CUBE_DESC;
private:
	CCube(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	~CCube() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual	void	Priority_Update(f32_t fDeltaTime) override;
	virtual	void	Update(f32_t fDeltaTime) override;
	virtual	void	Late_Update(f32_t fDeltaTime) override;
	virtual HRESULT	Render() override;
	virtual HRESULT	Render_Shadow() override;

private:
	ComPtr<ID3D11PixelShader>		m_pPS_Shadow = { nullptr };
	float4_t						m_vGroundPlane = { 0.f, 1.f, 0.f, 0.f };	// ¹ß¹Ø Æò¸é (a,b,c,d)

private:
	HRESULT			Render_Mesh(const XMMATRIX& matWorld, ID3D11RasterizerState* pRS, ID3D11PixelShader* pPS);

public:
	static shared_ptr<CCube> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
	virtual shared_ptr<CPrototype> Clone(void* pArg) override;
};

NS_END