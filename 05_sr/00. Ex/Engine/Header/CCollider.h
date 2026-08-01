#pragma once
#include "CComponent.h"

BEGIN(Engine)
class CGameObject;

class ENGINE_DLL CCollider :  public CComponent
{

private:
	explicit CCollider();
	explicit CCollider(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CCollider(const CCollider& rhs);
	virtual ~CCollider();

public:
	virtual _int Update_Component(const _float& fTimeDelta);
	virtual void LateUpdate_Component();

public:
	HRESULT		Ready_CColliderCom();
	static		CCollider* Create(LPDIRECT3DDEVICE9 pGraphicDev);

	void		SetCenter(_vec3 vCenter)		{ m_vCenter = vCenter; }
	_vec3		GetCenter()						{ return m_vCenter; }

	void		SetHalfSize(_vec3 vHalfSize)	{ m_vHalfSize = vHalfSize; }
	_vec3		GetHalfSize()					{ return m_vHalfSize; }

private:
	_vec3	m_vCenter;
	_vec3	m_vHalfSize;

private:
	virtual		void		Free();

	// CComponent을(를) 통해 상속됨
	CComponent* Clone(CGameObject* pOwner) override;
};

END
