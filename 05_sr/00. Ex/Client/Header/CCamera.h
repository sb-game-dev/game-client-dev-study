#pragma once
#include "CGameObject.h"


namespace Engine
{
	class CTransform;
}

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

	CAMERATYPE			GetCameraType() { return m_eCameraType; }
	D3DVIEWPORT9		GetViewPort()	{ return m_tViewPort; }
	_matrix				GetVeiwMat() { return m_matView; }
	_matrix				GetProjMat() { return m_matProj; }

private:
	Engine::CTransform* m_pTransformCom;

	HRESULT	Add_Component();

private:
	void	Direct_Follow(_vec3* vEye, _vec3* vAt, _vec3* vUp);
	void	Smooth_Follow(_vec3* vEye, _vec3* vAt, _vec3* vUp, float* fFov, const _float& fTimeDelta);
	void	MouseControl(_vec3* vEye, _vec3* vAt, _vec3* vUp, float* fFov, const _float& fTimeDelta);
	void	ViewWolrdMap(_vec3* vEye, _vec3* vAt, _vec3* vUp);

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

	CAMERATYPE		m_eCameraType;
	D3DVIEWPORT9	m_tViewPort;
	_matrix			m_matView;
	_matrix			m_matProj;

public:
	static CCamera*		Create(LPDIRECT3DDEVICE9 pGraphicDev, CAMERATYPE eType);
	virtual void		Free();
};
