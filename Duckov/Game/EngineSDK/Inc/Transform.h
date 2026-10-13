#pragma once
#include "Engine_Defines.h"
#include "Component.h"
NS_BEGIN(Engine)
class ENGINE_DLL CTransform : public CComponent
{
public:
	typedef struct tagTransformDesc
	{
		f32_t		fSpeedPerSec;
		f32_t		fDegreeRotPerSec; 
		f32_t		fPosX = {};
		f32_t		fPosY = {};
		f32_t		fPosZ = {};
	}TRANSFORM_DESC;
private:
	CTransform(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	virtual ~CTransform() = default;

public:
	HRESULT Initialize_Prototype() override;
	HRESULT Initialize(void* pArg) override;

public:
	vector_t Get_State(STATE eState) {
		return XMLoadFloat4x4(&m_WorldMatrix).r[ETOUI(eState)];
	}
	void Set_State(STATE eState, fvector_t vState)	{
		XMStoreFloat4(reinterpret_cast<float4_t*>(&m_WorldMatrix.m[ETOUI(eState)][0]), vState);
	}

	matrix_t		Get_World() { return XMLoadFloat4x4(&m_WorldMatrix); }

	void			Move_Position(vector_t vDir, f32_t fDeltaTime);

	void			Go_Staight(f32_t fDeltaTime);
	void			Go_Backward(f32_t fDeltaTime);
	void			Go_Left(f32_t fDeltaTime);
	void			Go_Right(f32_t fDeltaTime);

	void			Turn(fvector_t vAxis, f32_t fDeltaTime);
	void			Rotation(fvector_t vAxis, f32_t fAngle);

	void			Set_Speed(f32_t fSpeed) { m_fSpeedPerSec = fSpeed; }
	void			Set_RotationRadian(f32_t fRadian) { m_fRotationPerSec = fRadian; }

	void			Set_Scale(float3_t vScale);

private:
	float4x4_t		m_WorldMatrix = {};
	f32_t			m_fSpeedPerSec = {};
	f32_t			m_fRotationPerSec = {};
public:
	static shared_ptr<CTransform> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
	virtual shared_ptr<CPrototype> Clone(void* pArg) override;

};

NS_END