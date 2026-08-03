#pragma once
#include "CComponent.h"

BEGIN(Engine)
class CGameObject;

class ENGINE_DLL CCollider :  public CComponent
{

protected:
	explicit CCollider();
	explicit CCollider(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CCollider(const CCollider& rhs);
	virtual ~CCollider();

public:
	virtual _int Update_Component(const _float& fTimeDelta);	//PURE로 설정
	virtual void LateUpdate_Component();						// PURE로 설정

public:
	HRESULT		Ready_CColliderCom();
	static		CCollider* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	//////////지울 부분///////////
	void		SetCenter(_vec3 vCenter)				{ m_vCenter = vCenter; }
	_vec3		GetCenter()								{ return m_vCenter; }

	void		SetHalfSize(_vec3 vHalfSize)			{ m_vHalfSize = vHalfSize; }
	_vec3		GetHalfSize()							{ return m_vHalfSize; }
	/////////////////////
	void			SetIsTrigger(bool bTrigger)				{ m_bIsTrigger = bTrigger; }
	bool			GetIsTrigger()							{ return m_bIsTrigger; }

	void			SetColliderType(COLLIDER_TYPE eType)	{ m_eColliderType = eType; }
	COLLIDER_TYPE	GetColliderType()						{ return m_eColliderType; }

	virtual		CComponent* Clone(CGameObject* pOwner) override;//PURE로 설정

protected:
	_vec3	m_vCenter;
	_vec3	m_vHalfSize;

	bool			m_bIsTrigger;
	COLLIDER_TYPE	m_eColliderType;

protected:
	virtual		void		Free();
};

END
