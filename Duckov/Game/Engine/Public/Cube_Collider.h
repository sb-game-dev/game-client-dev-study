#pragma once
#include "Engine_Defines.h"
#include "Collider.h"
NS_BEGIN(Engine)
class ENGINE_DLL CCube_Collider : public CCollider
{
private:
	CCube_Collider(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	~CCube_Collider() = default;

public:
	HRESULT Initialize_Prototype() override;
	HRESULT Initialize(void* pArg) override;

public:
	BoundingOrientedBox&	Get_Info();
	void					Render_Collider(float4_t vColor)override;

	void					Set_Center(float3_t vPos) { m_BoundingBox.Center = vPos; }

	void					Set_Orientation(float4_t q) { m_BoundingBox.Orientation = q; }

	void					Set_Extents(float3_t vExtents) { m_BoundingBox.Extents = vExtents; }
	float3_t				Get_Extents() { return m_BoundingBox.Extents; }

	void					Set_OBBSize(BoundingBox Box_AABB);
private:
	BoundingOrientedBox		m_BoundingBox = {};


public:
	static shared_ptr<CCube_Collider> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
	virtual shared_ptr<CPrototype> Clone(void* pArg) override;
};

NS_END