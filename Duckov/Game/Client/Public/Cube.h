#pragma once
#include "Client_Defines.h"
#include "ContainerObject.h"

NS_BEGIN(Client)
class CCube : public CContainerObject
{
public:
	typedef struct tagCubeDesc : public CONTAINEROBJECT_DESC
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

public:
	virtual void	TriggerEnter(shared_ptr<class CCollider> pOtherCollider)override;
	virtual void	Take_Damage(const DAMAGE_DESC& Desc)override;
private:
	float4_t						m_vGroundPlane = { 0.f, 1.f, 0.f, 0.f };	// ¹ß¹Ø Æò¸é (a,b,c,d)

	shared_ptr<CTexture>			m_pTextureCom = { nullptr };
	shared_ptr<CVIBuffer_Cube>		m_pBufferCom = { nullptr };
	shared_ptr<CCube_Collider>		m_pCube_Collider = { nullptr };
	shared_ptr<CVertexShader>		m_pVS = { nullptr };
	shared_ptr<CPixelShader>		m_pPS = { nullptr };
	shared_ptr<CPixelShader>		m_pPS_Shadow = { nullptr };

	shared_ptr<class CUI_HpBar>		m_pHpBar = { nullptr };

private:
	HRESULT			Ready_Components();
	HRESULT			Ready_PartObjects();
	HRESULT			Ready_ConstantBuffer();
	HRESULT			Update_ConstantBuffer(const matrix_t& matWorld);

	virtual			HRESULT Bind_Shader(shared_ptr<CVertexShader> pVS = nullptr, shared_ptr<CPixelShader> pPS = nullptr);
	virtual			HRESULT Bind_ShaderResources(const matrix_t& matWorld);

	HRESULT			Render_Mesh(const XMMATRIX& matWorld, shared_ptr<CPixelShader> pPS);
	matrix_t		Get_ShadowWorld();
public:
	static shared_ptr<CCube> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
	virtual shared_ptr<CPrototype> Clone(void* pArg) override;
};

NS_END