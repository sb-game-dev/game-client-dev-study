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
	virtual float3_t	GetNormal(uint32_t i, uint32_t j);

	vector<UINT>&		GetIndex()		{ return m_tMeshData.Indices; }
	vector<VERTEX>&		GetVertices()	{ return m_tMeshData.Vertices; }

	void	LoadHeightMap(const tchar_t* pHightMapPath);

private:
	MESHDATA m_tMeshData = {}; 
	shared_ptr<CTexture>			m_pBlendCom = { nullptr };
	shared_ptr<CTexture>			m_pLayerCom = { nullptr };
	shared_ptr<CVertexShader>		m_pVS = { nullptr };
	shared_ptr<CPixelShader>		m_pPS = { nullptr };

	vector<f32_t>					m_vHeightmap;

	uint32_t    m_ivtxCntX = { 321 };
	uint32_t    m_ivtxCntZ = { 321 }; 
	f32_t       m_fDx = { 2.f };
	f32_t       m_fDz = { 2.f };
	f32_t       m_fHalfWidth = { 0.f };
	f32_t       m_fHalfDepth = { 0.f };

private:
	HRESULT			Ready_Components();

public:
	static shared_ptr<CHill> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
	virtual shared_ptr<CPrototype> Clone(void* pArg) override;
};

NS_END