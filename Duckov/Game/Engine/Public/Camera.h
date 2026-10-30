#pragma once
#include "GameObject.h"

NS_BEGIN(Engine)
class ENGINE_DLL CCamera abstract : public CGameObject
{
public:
	typedef struct tagCameraDesc : public CGameObject::GAMEOBJECT_DESC
	{
		float4_t		vEye, vAt;
		f32_t			fFovy, fNear, fFar;
	}CAMERA_DESC;

protected:
	CCamera(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	virtual ~CCamera() = default;

public:
	virtual HRESULT		Initialize_Prototype() override;
	virtual HRESULT		Initialize(void* pArg) override;
	virtual void		Priority_Update(f32_t fTimeDelta);
	virtual void		Update(f32_t fTimeDelta);
	virtual void		Late_Update(f32_t fTimeDelta);
	virtual HRESULT		Render();


	const	BoundingFrustum&	Get_ViewFrustum() { return m_tViewFrustum; }
	virtual void				Update_Frustum();

	virtual void				Compute_PickingRay(POINT pt, vector_t& vRayOriginW, vector_t& vRayDirW);

protected:
	BoundingFrustum		m_tViewFrustum = {};

	f32_t				m_fFovy = 60.f;
	f32_t				m_fNear = 0.1f;
	f32_t				m_fFar	= 1000.f;

protected:
	void				Update_PipeLines();
public:
	virtual shared_ptr<CPrototype> Clone(void* pArg) = 0;
};

NS_END