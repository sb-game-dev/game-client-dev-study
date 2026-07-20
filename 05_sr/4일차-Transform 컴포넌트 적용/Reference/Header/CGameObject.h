#pragma once
#include "CBase.h"
#include "CComponent.h"


BEGIN(Engine)
class CTransform;

class ENGINE_DLL CGameObject : public CBase
{
protected:
	explicit CGameObject(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CGameObject(const CGameObject& rhs);
	virtual ~CGameObject();

public:
	CComponent* Get_Component(COMPONENTID eID, const _tchar* pComponentTag);

public:
	virtual			HRESULT		Ready_GameObject();
	virtual			_int		Update_GameObject(const _float& fTimeDelta);
	virtual			void		LateUpdate_GameObject(const _float& fTimeDelta);
	virtual			void		Render_GameObject();

	virtual			void		SetTargetTransfrom(CTransform* pCom) 
	{
		m_pTargetTransfrom = pCom;
		if (m_pTargetTransfrom == nullptr)
		{
			MSG_BOX("TargetTransfrom Failed");
		}
	}

protected:
	map<const _tchar*, CComponent*>			m_mapComponent[ID_END];
	LPDIRECT3DDEVICE9						m_pGraphicDev;


private:
	CComponent* Find_Component(COMPONENTID eID, const _tchar* pComponentTag);

protected:
	virtual		void		Free();

protected:
	CTransform* m_pTargetTransfrom;
};

END