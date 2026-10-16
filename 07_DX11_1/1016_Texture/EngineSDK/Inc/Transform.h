#pragma once

#include "Component.h"

/* 이 컴포넌트를 들고 있는객체의 월드공간에서의 상태를 표현한다. */
/* 상태표현 == 월드변환행렬 */


NS_BEGIN(Engine)

class ENGINE_DLL CTransform final : public CComponent
{
public:
	typedef struct tagTransformDesc
	{
		f32_t		fSpeedPerSec;
		f32_t		fDegreeRotPerSec;
	}TRANSFORM_DESC;
private:
	CTransform(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	virtual ~CTransform() = default;

public:
	vector_t Get_State(STATE eState) {
		return XMLoadFloat4x4(&m_WorldMatrix).r[ETOUI(eState)];
	} 

	float3_t Get_Scaled() {
		return float3_t(
			XMVectorGetX(XMVector3Length(Get_State(STATE::RIGHT))), 
			XMVectorGetX(XMVector3Length(Get_State(STATE::UP))),
			XMVectorGetX(XMVector3Length(Get_State(STATE::LOOK)))
		);
	}

	void Set_State(STATE eState, fvector_t vState) {
		XMStoreFloat4(reinterpret_cast<float4_t*>(&m_WorldMatrix.m[ETOUI(eState)][0]), vState);
	}

	/* 입력해준 스케일값으로 셋한다. */
	void Set_Scale(f32_t fScaleX, f32_t fScaleY, f32_t fScaleZ);

	/* 입력해준 스케일 값만큼 추가적으로 스케일한다. */
	void Scaling(f32_t fScaleX, f32_t fScaleY, f32_t fScaleZ);

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;

public:
	void Go_Straight(f32_t fTimeDelta);
	void Go_Backward(f32_t fTimeDelta);
	void Go_Left(f32_t fTimeDelta);
	void Go_Right(f32_t fTimeDelta);

	void Turn(fvector_t vAxis, f32_t fTimeDelta);
	void Rotation(fvector_t vAxis, f32_t fAngle);
	void Rotation(f32_t fRotationX = 0.f, f32_t fRotationY = 0.f, f32_t fRotationZ = 0.f);

	void LookAt(fvector_t vAt);
	void MoveTo(fvector_t vGoal, f32_t fTimeDelta, f32_t fLimitDistance = 0.1f);

private:
	float4x4_t				m_WorldMatrix = {};
	f32_t					m_fSpeedPerSec = {};
	f32_t					m_fRotationPerSec = {};

private:

public:
	static shared_ptr<CTransform> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
	virtual shared_ptr<CPrototype> Clone(void* pArg) override;

};

NS_END