#pragma once
#include "Client_Defines.h"
#include "GameObject.h"
NS_BEGIN(Engine)
class CTexture;
NS_END

NS_BEGIN(Client)
class CCube_Instance : public CGameObject
{
public:
	typedef struct tagCubeInstanceDesc : public GAMEOBJECT_DESC
	{

	}CUBE_DESC;
private:
	CCube_Instance(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	~CCube_Instance() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual	void	Priority_Update(f32_t fDeltaTime) override;
	virtual	void	Update(f32_t fDeltaTime) override;
	virtual	void	Late_Update(f32_t fDeltaTime) override;
	virtual HRESULT	Render() override;
	virtual HRESULT	Render_Shadow() override;

private:
	static constexpr uint32_t		m_iNumInstance = 16;
	ComPtr<ID3D11Buffer>			m_pInstanceVB = { nullptr };
	ComPtr<ID3D11Buffer>			m_pInstanceVB_Shadow = { nullptr };

	shared_ptr<CTexture>			m_pTextureCom = { nullptr };
	shared_ptr<CVertexShader>		m_pVS = { nullptr };
	shared_ptr<CPixelShader>		m_pPS = { nullptr };
	shared_ptr<CPixelShader>		m_pPS_Shadow = { nullptr };

	float4x4_t						m_WorldMats[m_iNumInstance] = {};      
	float4x4_t						m_ShadowMats[m_iNumInstance] = {};
	BoundingBox						m_ShadowBoxes[m_iNumInstance] = {};    
	uint32_t						m_iVisibleCnt = {};
	uint32_t						m_iVisibleShadowCnt = {};

private:
	HRESULT			Ready_Components();
	HRESULT			Ready_InstanceBuffers();
	bool			Compute_OnHill(vector_t& vPos, vector_t& vGroundPlane);
	void            Cull_Instances();
	HRESULT         Render_Mesh(ID3D11Buffer* pInstanceVB, shared_ptr<CPixelShader> pPS, uint32_t iInstanceCnt);

public:
	static shared_ptr<CCube_Instance> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
	virtual shared_ptr<CPrototype> Clone(void* pArg) override;
};

NS_END