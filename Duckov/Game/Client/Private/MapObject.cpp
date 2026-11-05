#include "MapObject.h"

CMapObject::CMapObject(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    :CGameObject(pDevice, pContext)
{
}

HRESULT CMapObject::Initialize(void* pArg)
{
    if (nullptr == pArg)
        return E_FAIL;

    // 备炼眉 盲快扁
    auto pDesc = static_cast<MAPOBJECT_DESC*>(pArg);
    m_iLevelIndex = pDesc->iLevelIndex;
    m_vPosition = pDesc->vPosition;
    m_vScale = pDesc->vScale;
    m_strMeshPath = pDesc->strMeshPath;
    m_strTexturePath = pDesc->strTexturePath;
    m_bEditorMode = pDesc->bEditorMode;
    m_vQuaternion = pDesc->vQuaternion;

    // TransformCom 积己
    if (FAILED(__super::Initialize(pArg)))      
        return E_FAIL;
    Set_Transform(m_vPosition, m_vQuaternion, m_vScale);
    return S_OK;
}

void CMapObject::Set_RotationEuler(const float3_t& vDeg)
{
    m_vEulerHint = vDeg;
    XMStoreFloat4(&m_vQuaternion, XMQuaternionRotationRollPitchYaw(
        XMConvertToRadians(vDeg.x), XMConvertToRadians(vDeg.y), XMConvertToRadians(vDeg.z)));
    Apply_Transform();
}

void CMapObject::Set_Transform(const float3_t& vPos, const float4_t& vQuat, const float3_t& vScale)
{
    m_vPosition = vPos;
    m_vScale = vScale;
    XMStoreFloat4(&m_vQuaternion, XMQuaternionNormalize(XMLoadFloat4(&vQuat)));
    m_vEulerHint = Quat_To_EulerDeg(XMLoadFloat4(&m_vQuaternion));
    Apply_Transform();
}

void CMapObject::Apply_Transform()
{
    matrix_t World = XMMatrixScaling(m_vScale.x, m_vScale.y, m_vScale.z)
        * XMMatrixRotationQuaternion(XMLoadFloat4(&m_vQuaternion))
        * XMMatrixTranslation(m_vPosition.x, m_vPosition.y, m_vPosition.z);

    m_pTransformCom->Set_State(STATE::RIGHT, World.r[0]);
    m_pTransformCom->Set_State(STATE::UP, World.r[1]);
    m_pTransformCom->Set_State(STATE::LOOK, World.r[2]);
    m_pTransformCom->Set_State(STATE::POSITION, World.r[3]);
}