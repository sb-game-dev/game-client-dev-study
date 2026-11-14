#pragma once
#include "Client_Defines.h"
#include "MapObject.h"



NS_BEGIN(Client)
class CHill : public CMapObject
{
public:
	typedef struct tagHillDesc : public MAPOBJECT_DESC
	{
		wstring_t strLayerPath = L"Duckov_Extract/Terrain/Terrain_GroundZero_Crop/Layer%d.png";
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

	virtual const vector<float3_t>& Get_Vertices() { return m_pBufferCom->Get_Vertices(); }
	virtual const vector<uint32_t>& Get_Indices() { return m_pBufferCom->Get_Indices(); }

public:
	const wstring_t& Get_LayerPath() const { return m_strLayerPath; }

private:
	wstring_t m_strLayerPath;

private:
	shared_ptr<CTexture>			m_pBlendCom = { nullptr };
	shared_ptr<CTexture>			m_pLayerCom = { nullptr };
	shared_ptr<CVIBuffer_Terrain>	m_pBufferCom = { nullptr };
	shared_ptr<CVertexShader>		m_pVS = { nullptr };
	shared_ptr<CPixelShader>		m_pPS = { nullptr };

	shared_ptr<CConstantBuffer>		m_pCB = { nullptr };
	CB_PER_OBJECT				m_tCBData = {};

	
private:
	HRESULT			Ready_Components();
	HRESULT			Ready_ConstantBuffer();
	HRESULT			Update_ConstantBuffer(const matrix_t& matWorld);

	virtual			HRESULT Bind_Shader(shared_ptr<CVertexShader> pVS = nullptr, shared_ptr<CPixelShader> pPS = nullptr);
	virtual			HRESULT Bind_ShaderResources(const matrix_t& matWorld = XMMatrixIdentity());

public:
	static shared_ptr<CHill> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
	virtual shared_ptr<CPrototype> Clone(void* pArg) override;
};

NS_END