#include "pch.h"
#include "CBullet.h"

CBullet::CBullet(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
{
}

CBullet::~CBullet()
{
}
HRESULT CBullet::Ready_GameObject()
{
	return S_OK;
}
_int CBullet::Update_GameObject(const _float& fTimeDelta)
{
	_int iExit = CGameObject::Update_GameObject(fTimeDelta);

	return iExit;
}
void CBullet::LateUpdate_GameObject(const _float& fTimeDelta)
{
	CGameObject::LateUpdate_GameObject(fTimeDelta);
}
void CBullet::Render_GameObject()
{
	CGameObject::Render_GameObject();
}