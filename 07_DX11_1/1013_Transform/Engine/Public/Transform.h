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

	void Set_State(STATE eState, fvector_t vState) {
		XMStoreFloat4(reinterpret_cast<float4_t*>(&m_WorldMatrix.m[ETOUI(eState)][0]), vState);
	}

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