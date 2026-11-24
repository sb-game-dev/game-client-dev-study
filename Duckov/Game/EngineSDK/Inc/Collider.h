#pragma once
#include "Engine_Defines.h"
#include "Component.h"
NS_BEGIN(Engine)
class ENGINE_DLL CCollider : public CComponent
{
protected:
	CCollider(ComPtr<ID3D11Device>pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	~CCollider() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;


public:
	virtual void			SetIsTrigger(bool bTrigger)		{ m_bIsTrigger = bTrigger; }
	virtual bool			GetIsTrigger()					{ return m_bIsTrigger; }

	virtual void			Set_Offset(float3_t vOffset)	{ m_vOffset = vOffset; }
	virtual float3_t		Get_Offset()					{ return m_vOffset; }
	
	virtual void			Set_Active(bool _b)				{ m_bActive = _b; }
	virtual bool			Get_Active()					{ return m_bActive; }

	virtual COLLIDER_TYPE	GetColliderType()				{ return m_eColliderType; }

	virtual void			Render_Collider(float4_t vColor) PURE;
protected:
	bool				m_bIsTrigger = { true };
	COLLIDER_TYPE		m_eColliderType = {COLLIDER_TYPE::END};
	float3_t			m_vOffset = { 0,0,0 };
	bool				m_bActive = true;

public:
	virtual shared_ptr<CPrototype> Clone(void* pArg) PURE;
};

NS_END