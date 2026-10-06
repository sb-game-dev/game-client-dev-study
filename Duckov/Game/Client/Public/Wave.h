#pragma once
#include "Client_Defines.h"
#include "GameObject.h"
NS_BEGIN(Client)
class CWave : public CGameObject
{
private:
	CWave(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	~CWave() = default;

public:
	virtual HRESULT		Initialize_Prototype() override;
	virtual HRESULT		Initialize(void* pArg) override;
	virtual	void		Priority_Update(f32_t fDeltaTime) override;
	virtual	void		Update(f32_t fDeltaTime) override;
	virtual	void		Late_Update(f32_t fDeltaTime) override;
	virtual HRESULT		Render() override;

	vector<UINT>& GetIndex() { return m_tMeshData.Indices; }
	vector<VERTEX>& GetVertices() { return m_tMeshData.Vertices; }

private:
	MESHDATA m_tMeshData = {};
	MATERIAL m_tMaterial = {};

	ComPtr<ID3D11ShaderResourceView>	m_pSRV;
	ComPtr<ID3D11SamplerState>			m_pSampler;

private:
	f32_t m_fTime = { 0.f };
	f32_t GetWaveHeight(f32_t x, f32_t z, f32_t t)
	{
		return 0.5f * sinf(0.3f * x + 2.f * t) + 0.3f * cosf(0.2f * z + 1.5f * t);
	}
	float3_t GetWaveNormal(f32_t x, f32_t z, f32_t t)
	{
		f32_t fDhDx = 0.15f * cosf(0.3f * x + 2.f * t);
		f32_t fDhDz = -0.06f * sinf(0.2f * z + 1.5f * t);
		float3_t vNormal = { -fDhDx, 1.f, -fDhDz };
		XMStoreFloat3(&vNormal, XMVector3Normalize(XMLoadFloat3(&vNormal)));
		return vNormal;
	}

public:
	static shared_ptr<CWave> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
	virtual shared_ptr<CPrototype> Clone(void* pArg) override;
};

NS_END