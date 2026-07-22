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
	void	KeyInput(const _float& fTimeDelta);

private:
	void	Direct_Follow(_vec3* vEye, _vec3* vAt, _vec3* vUp);
	void	Smooth_Follow(_vec3* vEye, _vec3* vAt, _vec3* vUp, float* fFov, const _float& fTimeDelta);

	_vec3   m_vEye;
	_vec3   m_vAt;
	_vec3   m_vUp;
	float	m_fFov;

public:
	static CCamera*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual void		Free();
};

END