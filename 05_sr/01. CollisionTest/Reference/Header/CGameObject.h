#pragma once
#include "CBase.h"
#include "CComponent.h"
//#include "Engine_Enum.h"
//#include "CRenderer.h"

BEGIN(Engine)
class CCollider;

class ENGINE_DLL CGameObject : public CBase
{
protected:
	explicit CGameObject(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CGameObject(const CGameObject& rhs);
	virtual ~CGameObject();

public:
	CComponent* Get_Component(COMPONENTID eID, const _tchar* pComponentTag);
	void						SetObjID(OBJID eID) { m_eObjID = eID; }
	OBJID						GetObjID(OBJID eID) { return m_eObjID; }

public:
	virtual			HRESULT		Ready_GameObject();
	virtual			_int		Update_GameObject(const _float& fTimeDelta);
	virtual			void		LateUpdate_GameObject(const _float& fTimeDelta);
	virtual			void		Render_GameObject();

	//virtual			void		CollisionEvent(CGameObject* pGameObject);

protected:
	map<const _tchar*, CComponent*>			m_mapComponent[ID_END];
	LPDIRECT3DDEVICE9						m_pGraphicDev;
	OBJID									m_eObjID;

private:
	CComponent* Find_Component(COMPONENTID eID, const _tchar* pComponentTag);

protected:
	virtual		void		Free();
};

END