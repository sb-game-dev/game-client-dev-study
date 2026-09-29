#pragma once
#include "Client_Defines.h"
#include "GameObject.h"
NS_BEGIN(Client)
class CHill : public CGameObject
{
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

	virtual f32_t		GetHeight(f32_t x, f32_t z) { return 0.3f * (z * sinf(0.1f * x) + x * cosf(0.1f * z)); }
	virtual float3_t	GetNormal(f32_t x, f32_t z);

	vector<UINT>&		GetIndex()		{ return m_tMeshData.Indices; }
	vector<VERTEX>&		GetVertices()	{ return m_tMeshData.Vertices; }

private:
	MESHDATA m_tMeshData = {};
	MATERIAL m_tMaterial = {};
public:
	static shared_ptr<CHill> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
	virtual shared_ptr<CPrototype> Clone(void* pArg) override;
};

NS_END