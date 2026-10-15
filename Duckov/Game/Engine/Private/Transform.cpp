#include "Transform.h"

CTransform::CTransform(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	:CComponent{pDevice, pContext}
{
}

HRESULT CTransform::Initialize_Prototype()
{
	XMStoreFloat4x4(&m_WorldMatrix, XMMatrixIdentity());
	return S_OK;
}

HRESULT CTransform::Initialize(void* pArg)
{
	auto pDesc = static_cast<TRANSFORM_DESC*>(pArg);
	if (pDesc == nullptr)
		return S_OK;

	m_fSpeedPerSec = pDesc->fSpeedPerSec;
	m_fRotationPerSec = XMConvertToRadians(pDesc->fDegreeRotPerSec);

	vector_t	vPos = { pDesc->fPosX,pDesc->fPosY,pDesc->fPosZ,1.f };
	Set_State(STATE::POSITION, vPos);

	return S_OK;
}

void CTransform::Move_Position(fvector_t vDir, f32_t fDeltaTime)
{
	vector_t	vPosition = Get_State(STATE::POSITION);

	vPosition += vDir * m_fSpeedPerSec * fDeltaTime;

	Set_State(STATE::POSITION, vPosition);
}

void CTransform::Move_To(fvector_t vGoal, f32_t fDeltaTime, f32_t fLimitDistance)
{
	vector_t	vPos = Get_State(STATE::POSITION);
	vector_t	vDir = vGoal - vPos;

	f32_t	fMoveDistance = min(XMVectorGetX(XMVector3Length(vDir)), m_fSpeedPerSec * fDeltaTime);
	vPos += XMVector3Normalize(vDir) * fMoveDistance;

	//if (XMVectorGetX(XMVector3Length(vDir)) >= fLimitDistance)
	//	vPos += XMVector3Normalize(vDir) * m_fSpeedPerSec * fDeltaTime;

	Set_State(STATE::POSITION, vPos);
}

void CTransform::Go_Staight(f32_t fDeltaTime)
{
	vector_t	vPosition	= Get_State(STATE::POSITION);
	vector_t	vLook		= Get_State(STATE::LOOK);
	vPosition += XMVector3Normalize(vLook) * m_fSpeedPerSec * fDeltaTime;

	Set_State(STATE::POSITION, vPosition);
}

void CTransform::Go_Backward(f32_t fDeltaTime)
{
	vector_t	vPosition = Get_State(STATE::POSITION);
	vector_t	vLook = Get_State(STATE::LOOK);
	vPosition -= XMVector3Normalize(vLook) * m_fSpeedPerSec * fDeltaTime;

	Set_State(STATE::POSITION, vPosition);
}

void CTransform::Go_Left(f32_t fDeltaTime)
{
	vector_t	vPosition = Get_State(STATE::POSITION);
	vector_t	vRight = Get_State(STATE::RIGHT);
	vPosition -= XMVector3Normalize(vRight) * m_fSpeedPerSec * fDeltaTime;

	Set_State(STATE::POSITION, vPosition);
}

void CTransform::Go_Right(f32_t fDeltaTime)
{
	vector_t	vPosition = Get_State(STATE::POSITION);
	vector_t	vRight = Get_State(STATE::RIGHT);
	vPosition += XMVector3Normalize(vRight) * m_fSpeedPerSec * fDeltaTime;

	Set_State(STATE::POSITION, vPosition);
}

void CTransform::Turn(fvector_t vAxis, f32_t fDeltaTime)
{
	vector_t	vRight		= Get_State(STATE::RIGHT);
	vector_t	vUp			= Get_State(STATE::UP);
	vector_t	vLook		= Get_State(STATE::LOOK);

	matrix_t	RotationMatrix = XMMatrixRotationAxis(vAxis, m_fRotationPerSec * fDeltaTime);

	Set_State(STATE::RIGHT, XMVector3TransformNormal(vRight, RotationMatrix));
	Set_State(STATE::UP,	XMVector3TransformNormal(vUp, RotationMatrix));
	Set_State(STATE::LOOK,	XMVector3TransformNormal(vLook, RotationMatrix));
}

void CTransform::Rotation(fvector_t vAxis, f32_t fAngle)
{
	float3_t	vScaled = Get_Scaled();

	vector_t	vRight	= vector_t{1.f,0.f,0.f,0.f} * vScaled.x;
	vector_t	vUp		= vector_t{0.f,1.f,0.f,0.f} * vScaled.y;
	vector_t	vLook	= vector_t{0.f,0.f,1.f,0.f} * vScaled.z;

	matrix_t	RotationMatrix = XMMatrixRotationAxis(vAxis, fAngle);

	Set_State(STATE::RIGHT, XMVector3TransformNormal(vRight, RotationMatrix));
	Set_State(STATE::UP,	XMVector3TransformNormal(vUp, RotationMatrix));
	Set_State(STATE::LOOK,	XMVector3TransformNormal(vLook, RotationMatrix));
}

void CTransform::Rotation(f32_t fDegreeX, f32_t fDegreeY, f32_t fDegreeZ)
{
	float3_t	vScaled = Get_Scaled();

	vector_t	vRight = vector_t{ 1.f,0.f,0.f,0.f } *vScaled.x;
	vector_t	vUp = vector_t{ 0.f,1.f,0.f,0.f } *vScaled.y;
	vector_t	vLook = vector_t{ 0.f,0.f,1.f,0.f } *vScaled.z;

	vector_t	vQuaternion = XMQuaternionRotationRollPitchYaw(XMConvertToRadians(fDegreeX), XMConvertToRadians(fDegreeY), XMConvertToRadians(fDegreeZ));
	matrix_t	RotationMatrix = XMMatrixRotationQuaternion(vQuaternion);

	Set_State(STATE::RIGHT, XMVector3TransformNormal(vRight, RotationMatrix));
	Set_State(STATE::UP, XMVector3TransformNormal(vUp, RotationMatrix));
	Set_State(STATE::LOOK, XMVector3TransformNormal(vLook, RotationMatrix));
}

void CTransform::Set_Scale(f32_t ScaleX, f32_t ScaleY, f32_t ScaleZ)
{
	vector_t	vRight	= XMVector3Normalize(Get_State(STATE::RIGHT));
	vector_t	vUp		= XMVector3Normalize(Get_State(STATE::UP));
	vector_t	vLook	= XMVector3Normalize(Get_State(STATE::LOOK));

	Set_State(STATE::RIGHT, vRight * ScaleX);
	Set_State(STATE::UP,	vUp * ScaleY);
	Set_State(STATE::LOOK,	vLook * ScaleZ);
}

void CTransform::Scaling(f32_t ScaleX, f32_t ScaleY, f32_t ScaleZ)
{
	vector_t	vRight = Get_State(STATE::RIGHT);
	vector_t	vUp = Get_State(STATE::UP);
	vector_t	vLook = Get_State(STATE::LOOK);

	Set_State(STATE::RIGHT, vRight * ScaleX);
	Set_State(STATE::UP, vUp * ScaleY);
	Set_State(STATE::LOOK, vLook * ScaleZ);
}

void CTransform::LookAt(fvector_t vAt)
{
	float3_t	vScaled = Get_Scaled();

	vector_t	vLook	= vAt - Get_State(STATE::POSITION);
	vector_t	vRight	= XMVector3Cross(vector_t{ 0.f,1.f,0.f,0.f }, vLook);
	vector_t	vUp		= XMVector3Cross(vLook, vRight);

	Set_State(STATE::RIGHT, XMVector3Normalize(vRight) * vScaled.x);
	Set_State(STATE::UP,	XMVector3Normalize(vUp) * vScaled.y);
	Set_State(STATE::LOOK,	XMVector3Normalize(vLook) * vScaled.z);
}

shared_ptr<CTransform> CTransform::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
	auto pInstance = shared_ptr<CTransform>(new CTransform(pDevice, pContext));

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Clone Failed : CTransform");
		pInstance.reset();
	}
	return pInstance;
}

shared_ptr<CPrototype> CTransform::Clone(void* pArg)
{
	auto pInstance = shared_ptr<CPrototype>(new CTransform(*this));

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Clone Failed : CTransform");
		pInstance.reset();
	}
	return pInstance;
}
