#include "MapObject.h"

CMapObject::CMapObject(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    :CGameObject(pDevice, pContext)
{
}

HRESULT CMapObject::Initialize(void* pArg)
{
    if (nullptr == pArg)
        return E_FAIL;

    // 구조체 채우기
    auto pDesc = static_cast<MAPOBJECT_DESC*>(pArg);
    m_iLevelIndex = pDesc->iLevelIndex;
    m_vPosition = pDesc->vPosition;
    m_vRotation = pDesc->vRotation;
    m_vScale = pDesc->vScale;
    m_strMeshPath = pDesc->strMeshPath;
    m_strTexturePath = pDesc->strTexturePath;
    m_bEditorMode = pDesc->bEditorMode;

    // TransformCom 생성
    if (FAILED(__super::Initialize(pArg)))      
        return E_FAIL;

    // 구조체로 생성한 정보들 TransformCom에 적용
    Apply_Transform();
    return S_OK;
}

void CMapObject::Apply_Transform()
{
    m_pTransformCom->Rotation(m_vRotation.x, m_vRotation.y, m_vRotation.z);  
    m_pTransformCom->Set_Scale(m_vScale.x, m_vScale.y, m_vScale.z);          
    m_pTransformCom->Set_State(STATE::POSITION,
        XMVectorSet(m_vPosition.x, m_vPosition.y, m_vPosition.z, 1.f));
}