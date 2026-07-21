#pragma once
#include "CGameObject.h"


namespace Engine
{
	class CTransform;
}

BEGIN(Engine)
class CCamera :
    public CGameObject
{
private:
	explicit CCamera(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual	~CCamera();

public:
	virtual	HRESULT		Ready_GameObject();
	virtual	_int		Update_GameObject(const _float& fTimeDelta);
	virtual	void		LateUpdate_GameObject(const _float& fTimeDelta);
	virtual	void		Render_GameObject();

private:
	Engine::CTransform* m_pTransformCom;

	HRESULT	Add_Component();

public:
	static CCamera*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual void		Free();
};

END