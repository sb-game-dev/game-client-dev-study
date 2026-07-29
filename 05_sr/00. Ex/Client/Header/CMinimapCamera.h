#pragma once
#include "CGameObject.h"

namespace Engine
{
	class CTransform;
}
class CMinimapCamera : public CGameObject
{
private:
	explicit CMinimapCamera(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual	~CMinimapCamera();

public:
	virtual	HRESULT		Ready_GameObject();
	virtual	_int		Update_GameObject(const _float& fTimeDelta);
	virtual	void		LateUpdate_GameObject(const _float& fTimeDelta);
	virtual	void		Render_GameObject();

private:
	Engine::CTransform* m_pTransformCom;

	HRESULT	Add_Component();

private:
	void	Direct_Follow(_vec3* vEye, _vec3* vAt, _vec3* vUp);
	void	Smooth_Follow(_vec3* vEye, _vec3* vAt, _vec3* vUp, float* fFov, const _float& fTimeDelta);
	void	MouseControl(_vec3* vEye, _vec3* vAt, _vec3* vUp, float* fFov, const _float& fTimeDelta);

	void	MouseFix();

private:
	_vec3   m_vEye;
	_vec3   m_vAt;
	_vec3   m_vUp;

	_vec3	m_vPreMousePos;
	_vec3	m_vCurMousePos;

	float	m_fFov;
	float	m_fRotX;
	float	m_fRotY;

public:
	static CMinimapCamera* Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual void		Free();
};
