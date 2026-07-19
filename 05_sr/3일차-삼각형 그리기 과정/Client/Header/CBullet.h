#pragma once
#include "CGameObject.h"
class CBullet :
    public CGameObject
{
private:
	CBullet(LPDIRECT3DDEVICE9 pGraphicDev);
	~CBullet();
public:
	virtual			HRESULT		Ready_GameObject();
	virtual			_int		Update_GameObject(const _float& fTimeDelta);
	virtual			void		LateUpdate_GameObject(const _float& fTimeDelta);
	virtual			void		Render_GameObject();

public:
	CBullet* Create(LPDIRECT3DDEVICE9 pGraphicDev);
};

