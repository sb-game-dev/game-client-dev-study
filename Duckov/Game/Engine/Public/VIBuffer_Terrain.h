#pragma once
#include "VIBuffer.h"
NS_BEGIN(Engine)
class ENGINE_DLL CVIBuffer_Terrain : public CVIBuffer
{
private:
	CVIBuffer_Terrain(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);

public:
	~CVIBuffer_Terrain() = default;
public:
	virtual HRESULT Initialize_Prototype(const tchar_t* pHeightMapPath);
	virtual HRESULT Initialize(void* pArg) override;

public:
	f32_t				GetHeight(f32_t x, f32_t z);
	float4_t			GetPlane(f32_t x, f32_t z);

private:
	vector<f32_t>		m_vHeightmap;

	uint32_t			m_ivtxCntX = { 321 };
	uint32_t			m_ivtxCntZ = { 321 };
	f32_t				m_fDx = { 2.f };
	f32_t				m_fDz = { 2.f };
	f32_t				m_fHalfWidth = { (m_ivtxCntX - 1) * 0.5f * m_fDx };
	f32_t				m_fHalfDepth = { (m_ivtxCntZ - 1) * 0.5f * m_fDz };

private:
	HRESULT				LoadHeightMap(const tchar_t* pHightMapPath);
	float3_t			GetNormal(uint32_t i, uint32_t j);

public:
	static shared_ptr<CVIBuffer_Terrain> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, const tchar_t* pHeightMapPath);
	virtual shared_ptr<CPrototype> Clone(void* pArg) override;

};

NS_END