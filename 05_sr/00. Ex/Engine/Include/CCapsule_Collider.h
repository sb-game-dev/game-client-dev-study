#pragma once
#include "CCollider.h"

BEGIN(Engine)
class CGameObject;
class ENGINE_DLL CCapsule_Collider : public CCollider
{
private:
	explicit CCapsule_Collider();
	explicit CCapsule_Collider(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CCapsule_Collider(const CCollider& rhs);
	virtual ~CCapsule_Collider();

public:
	virtual _int Update_Component(const _float& fTimeDelta);
	virtual void LateUpdate_Component();

public:
	HRESULT			Ready_CCapsule_Collider();
	static			CCollider* Create(LPDIRECT3DDEVICE9 pGraphicDev);

	void			SetOffset(_vec3 vCenter) { m_vOffset = vCenter; }
	_vec3			GetOffset() { return m_vOffset; }

	void			SetRadius(float fRadius) { m_fRadius = fRadius; }
	float			GetRadius() { return m_fRadius; }

	void			SetHeight(float fHeight) { m_fHeight = fHeight; }
	float			GetHeight() { return m_fHeight; }

	void			SetAxis(CAPSULE_AXIS eCapsuleAxis) { m_eCapsuleAxis = eCapsuleAxis; }
	CAPSULE_AXIS	GetAxis() { return m_eCapsuleAxis; }

	virtual		CComponent* Clone(CGameObject* pOwner);

private:
	_vec3			m_vOffset;
	float			m_fRadius;
	float			m_fHeight;
	CAPSULE_AXIS	m_eCapsuleAxis;

private:
	virtual		void		Free();

};
END
