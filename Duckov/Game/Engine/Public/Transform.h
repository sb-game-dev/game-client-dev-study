#pragma once
#include "Engine_Defines.h"
#include "Component.h"
NS_BEGIN(Engine)
class ENGINE_DLL CTransform : public CComponent
{
public:
	typedef struct tagTransformDesc
	{
		f32_t		fSpeedPerSec = {};
		f32_t		fDegreeRotPerSec = {};
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

	float3_t	Get_Scaled() {
		return float3_t(
			XMVectorGetX(XMVector3Length(Get_State(STATE::RIGHT))),
			XMVectorGetX(XMVector3Length(Get_State(STATE::UP))),
			XMVectorGetX(XMVector3Length(Get_State(STATE::LOOK)))
		);
	}

	matrix_t		Get_World() { return XMLoadFloat4x4(&m_WorldMatrix); }

	void			Move_Position(fvector_t vDir, f32_t fDeltaTime);
	void			Move_To(fvector_t vGoal, f32_t fDeltaTime, f32_t fLimitDistance = 0.1f);

	void			Go_Staight(f32_t fDeltaTime);
	void			Go_Backward(f32_t fDeltaTime);
	void			Go_Left(f32_t fDeltaTime);
	void			Go_Right(f32_t fDeltaTime);

	void			Turn(fvector_t vAxis, f32_t fDeltaTime);
	void			Rotation(fvector_t vAxis, f32_t fAngle);
	void			Rotation(f32_t fRotationX = 0, f32_t fRotationY = 0, f32_t fRotationZ = 0);

	void			Set_Speed(f32_t fSpeed) { m_fSpeedPerSec = fSpeed; }
	void			Set_RotationDegree(f32_t fDegree) { m_fRotationPerSec = XMConvertToRadians(fDegree); }

	void			Set_Scale(f32_t ScaleX = 1, f32_t ScaleY = 1, f32_t ScaleZ = 1);
	void			Scaling(f32_t ScaleX = 1, f32_t ScaleY = 1, f32_t ScaleZ = 1);

	void			LookAt(fvector_t vAt);

private:
	float4x4_t		m_WorldMatrix = {};
	f32_t			m_fSpeedPerSec = {};
	f32_t			m_fRotationPerSec = {};

public:
	static shared_ptr<CTransform> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
	virtual shared_ptr<CPrototype> Clone(void* pArg) override;

};

NS_END