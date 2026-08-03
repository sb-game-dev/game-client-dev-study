#pragma once

#include "CBase.h"
#include "Engine_Define.h"

BEGIN(Engine)
class CGameObject;
class ENGINE_DLL CComponent : public CBase
{
protected:
	explicit CComponent();
	explicit CComponent(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CComponent(const CComponent& rhs);
	virtual ~CComponent();

public:
	virtual _int Update_Component(const _float& fTimeDelta) { return 0; }
	virtual void LateUpdate_Component() { }

	virtual CGameObject* GetOwner() { return m_pOwner; }
	virtual void SetOwner(CGameObject* pGameObject) { m_pOwner = pGameObject; }

protected:
	LPDIRECT3DDEVICE9			m_pGraphicDev;
	_bool						m_bClone;
	CGameObject*				m_pOwner;

public:
	virtual CComponent* Clone(CGameObject* pOwner)	PURE;		// 프로토타입 디자인 패턴을 사용하는 예

protected:
	virtual void		Free();
};

END