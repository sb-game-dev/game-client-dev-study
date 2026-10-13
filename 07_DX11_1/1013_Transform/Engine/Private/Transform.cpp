#include "Transform.h"

CTransform::CTransform(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    : CComponent { pDevice, pContext }
{
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

    /*XMVector3TransformCoord();
    XMVector3TransformNormal();
    XMVector4Transform();*/

    




}

void CTransform::Rotation(fvector_t vAxis, f32_t fAngle)
{
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