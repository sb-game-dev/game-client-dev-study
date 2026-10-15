#include "Transform.h"

CTransform::CTransform(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    : CComponent { pDevice, pContext }
{
}

void CTransform::Set_Scale(f32_t fScaleX, f32_t fScaleY, f32_t fScaleZ)
{
    Set_State(STATE::RIGHT, XMVector3Normalize(Get_State(STATE::RIGHT)) * fScaleX);
    Set_State(STATE::UP, XMVector3Normalize(Get_State(STATE::UP)) * fScaleY);
    Set_State(STATE::LOOK, XMVector3Normalize(Get_State(STATE::LOOK)) * fScaleZ);
}

void CTransform::Scaling(f32_t fScaleX, f32_t fScaleY, f32_t fScaleZ)
{
    Set_State(STATE::RIGHT, Get_State(STATE::RIGHT) * fScaleX);
    Set_State(STATE::UP, Get_State(STATE::UP) * fScaleY);
    Set_State(STATE::LOOK, Get_State(STATE::LOOK) * fScaleZ);
}

HRESULT CTransform::Initialize_Prototype()
{
    //vector_t        vTmp = {};

    //vTmp = XMVectorSetW(vTmp, 1.f);

    XMStoreFloat4x4(&m_WorldMatrix, XMMatrixIdentity());

    return S_OK;
}

HRESULT CTransform::Initialize(void* pArg)
{
    auto        pDesc = static_cast<CTransform::TRANSFORM_DESC*>(pArg);

    m_fSpeedPerSec = pDesc->fSpeedPerSec;
    m_fRotationPerSec = XMConvertToRadians(pDesc->fDegreeRotPerSec);        

    return S_OK;
}

void CTransform::Go_Straight(f32_t fTimeDelta)
{
    vector_t        vPosition = Get_State(STATE::POSITION);
    vector_t        vLook = Get_State(STATE::LOOK);

    vPosition += XMVector3Normalize(vLook) * m_fSpeedPerSec * fTimeDelta;

    Set_State(STATE::POSITION, vPosition);
}

void CTransform::Go_Backward(f32_t fTimeDelta)
{
    vector_t        vPosition = Get_State(STATE::POSITION);
    vector_t        vLook = Get_State(STATE::LOOK);

    vPosition -= XMVector3Normalize(vLook) * m_fSpeedPerSec * fTimeDelta;

    Set_State(STATE::POSITION, vPosition);
}

void CTransform::Go_Left(f32_t fTimeDelta)
{
    vector_t        vPosition = Get_State(STATE::POSITION);
    vector_t        vRight = Get_State(STATE::RIGHT);

    vPosition -= XMVector3Normalize(vRight) * m_fSpeedPerSec * fTimeDelta;

    Set_State(STATE::POSITION, vPosition);
}


void CTransform::Go_Right(f32_t fTimeDelta)
{
    vector_t        vPosition = Get_State(STATE::POSITION);
    vector_t        vRight = Get_State(STATE::RIGHT);

    vPosition += XMVector3Normalize(vRight) * m_fSpeedPerSec * fTimeDelta;

    Set_State(STATE::POSITION, vPosition);
}

void CTransform::Turn(fvector_t vAxis, f32_t fTimeDelta)
{
    vector_t        vRight = Get_State(STATE::RIGHT);
    vector_t        vUp = Get_State(STATE::UP);
    vector_t        vLook = Get_State(STATE::LOOK);

    matrix_t        RotationMatrix = XMMatrixRotationAxis(vAxis, m_fRotationPerSec * fTimeDelta);

    Set_State(STATE::RIGHT, XMVector3TransformNormal(vRight, RotationMatrix));
    Set_State(STATE::UP, XMVector3TransformNormal(vUp, RotationMatrix));
    Set_State(STATE::LOOK, XMVector3TransformNormal(vLook, RotationMatrix));
}

void CTransform::Rotation(fvector_t vAxis, f32_t fAngle)
{
    float3_t        vScaled = Get_Scaled();

    vector_t        vRight = XMVectorSet(1.f, 0.f, 0.f, 0.f) * vScaled.x;
    vector_t        vUp = XMVectorSet(0.f, 1.f, 0.f, 0.f) * vScaled.y;
    vector_t        vLook = XMVectorSet(0.f, 0.f, 1.f, 0.f) * vScaled.z;

    matrix_t        RotationMatrix = XMMatrixRotationAxis(vAxis, XMConvertToRadians(fAngle));

    Set_State(STATE::RIGHT, XMVector3TransformNormal(vRight, RotationMatrix));
    Set_State(STATE::UP, XMVector3TransformNormal(vUp, RotationMatrix));
    Set_State(STATE::LOOK, XMVector3TransformNormal(vLook, RotationMatrix));
}

void CTransform::Rotation(f32_t fRotationX, f32_t fRotationY, f32_t fRotationZ)
{
    float3_t        vScaled = Get_Scaled();

    vector_t        vRight = XMVectorSet(1.f, 0.f, 0.f, 0.f) * vScaled.x;
    vector_t        vUp = XMVectorSet(0.f, 1.f, 0.f, 0.f) * vScaled.y;
    vector_t        vLook = XMVectorSet(0.f, 0.f, 1.f, 0.f) * vScaled.z;

    vector_t        vQuaternion = XMQuaternionRotationRollPitchYaw(XMConvertToRadians(fRotationX), XMConvertToRadians(fRotationY), XMConvertToRadians(fRotationZ));

    matrix_t        RotationMatrix = XMMatrixRotationQuaternion(vQuaternion);

    Set_State(STATE::RIGHT, XMVector3TransformNormal(vRight, RotationMatrix));
    Set_State(STATE::UP, XMVector3TransformNormal(vUp, RotationMatrix));
    Set_State(STATE::LOOK, XMVector3TransformNormal(vLook, RotationMatrix));
}

void CTransform::LookAt(fvector_t vAt)
{
    float3_t        vScaled = Get_Scaled();

    vector_t        vLook = vAt - Get_State(STATE::POSITION);
    vector_t        vRight = XMVector3Cross(XMVectorSet(0.f, 1.f, 0.f, 0.f), vLook);
    vector_t        vUp = XMVector3Cross(vLook, vRight);

    Set_State(STATE::RIGHT, XMVector3Normalize(vRight) * vScaled.x);
    Set_State(STATE::UP, XMVector3Normalize(vUp) * vScaled.y);
    Set_State(STATE::LOOK, XMVector3Normalize(vLook) * vScaled.z);
}

void CTransform::MoveTo(fvector_t vGoal, f32_t fTimeDelta, f32_t fLimitDistance)
{
    vector_t        vPosition = Get_State(STATE::POSITION);

    vector_t        vMoveDir = vGoal - vPosition;

    f32_t           fDistance = XMVectorGetX(XMVector3Length(vMoveDir));
    
    if(fDistance >= fLimitDistance)
        vPosition += XMVector3Normalize(vMoveDir) *  m_fSpeedPerSec * fTimeDelta;
}


shared_ptr<CTransform> CTransform::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto pInstance = shared_ptr<CTransform>(new CTransform(pDevice, pContext));

    if (FAILED(pInstance->Initialize_Prototype()))
    {
        MSG_BOX("Failed to Created : CTransform");
        pInstance.reset();
    }

    return pInstance;
}


shared_ptr<CPrototype> CTransform::Clone(void* pArg)
{
    auto pInstance = shared_ptr<CTransform>(new CTransform(*this));

    if (FAILED(pInstance->Initialize(pArg)))
    {
        MSG_BOX("Failed to Cloned : CBackGround");
        pInstance.reset();
    }

    return pInstance;
}