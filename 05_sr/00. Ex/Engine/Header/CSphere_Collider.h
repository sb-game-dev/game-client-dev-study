#pragma once
#include "CCollider.h"

BEGIN(Engine)
class CGameObject;
class ENGINE_DLL CSphere_Collider : public CCollider
{
private:
	explicit CSphere_Collider();
	explicit CSphere_Collider(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CSphere_Collider(const CCollider& rhs);
	virtual ~CSphere_Collider();

public:
	virtual _int Update_Component(const _float& fTimeDelta);
	virtual void LateUpdate_Component();

public:
	HRESULT		Ready_CSphere_Collider();
	static		CCollider* Create(LPDIRECT3DDEVICE9 pGraphicDev);

	void		SetOffset(_vec3 vCenter) { m_vOffset = vCenter; }
	_vec3		GetOffset() { return m_vOffset; }

	void		SetRadius(float fRadius) { m_fRadius = fRadius; }
	float		GetRadius() { return m_fRadius; }

	virtual		CComponent* Clone(CGameObject* pOwner);

private:
	_vec3		m_vOffset;
	float		m_fRadius;

private:
	virtual		void		Free();

};
END
