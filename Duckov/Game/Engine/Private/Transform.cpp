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

void CTransform::Move_Position(vector_t vDir, f32_t fDeltaTime)
{
	vector_t	vPosition = Get_State(STATE::POSITION);
	vPosition += vDir * m_fSpeedPerSec * fDeltaTime;

	Set_State(STATE::POSITION, vPosition);
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
}

void CTransform::Set_Scale(float3_t vScale)
{
	vector_t	vRight	= XMVector3Normalize(Get_State(STATE::RIGHT));
	vector_t	vUp		= XMVector3Normalize(Get_State(STATE::UP));
	vector_t	vLook	= XMVector3Normalize(Get_State(STATE::LOOK));

	Set_State(STATE::RIGHT, vRight* vScale.x);
	Set_State(STATE::UP,	vUp* vScale.y);
	Set_State(STATE::LOOK,	vLook* vScale.z);
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
