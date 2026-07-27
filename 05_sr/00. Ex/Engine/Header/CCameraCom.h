#pragma once
#include "CComponent.h"


BEGIN(Engine)
class ENGINE_DLL CCameraCom :  public CComponent
{

private:
	explicit CCameraCom();
	explicit CCameraCom(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CCameraCom(const CCameraCom& rhs);
	virtual ~CCameraCom();

public:
	void		MouseControl(_vec3* vPlayerPos,_vec3* vPlayerLook, _vec3* vMousePos);

	virtual		_int Update_Component(const _float& fTimeDelta);
	virtual		void LateUpdate_Component();
public:
	HRESULT		Ready_CameraCom();
	static		CCameraCom* Create(LPDIRECT3DDEVICE9 pGraphicDev);

	virtual		CComponent* Clone();
private:
	virtual		void		Free();

private:
	_vec3		m_vEye;
	_vec3		m_vAt;
	_vec3		m_vUp;

	float		m_fFov;
};

END
