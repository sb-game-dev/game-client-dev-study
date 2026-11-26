#include "Helmet.h"

#include "GameInstance.h"
#include "Inven.h"

CHelmet::CHelmet(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    : CPartObject{ pDevice, pContext }
{
}

HRESULT CHelmet::Initialize_Prototype()
{
    if (FAILED(__super::Initialize_Prototype()))
        return E_FAIL;

    /* 백그라운드 원형객체에 필요한 정보를 다 채워둔다. */



    return S_OK;
}

HRESULT CHelmet::Initialize(void* pArg)
{
    if (nullptr != pArg)
    {
        auto        pDesc = static_cast<CHelmet::HELMET_DESC*>(pArg);
        m_pSocketMatrix = pDesc->pSocketMatrix;
    }

    /* 백그라운드 사본객체를 생성할때 원형이 읽어놓은 정보를 사본객체에게 채워준다. */
    if (FAILED(__super::Initialize(pArg)))
        return E_FAIL;

    if (FAILED(Ready_Components()))
        return E_FAIL;

    //m_pTransformCom->Set_Scale(10.f, 10.f, 10.f);
    //m_pTransformCom->Rotation(-90.f, 0.f, 0.f);
    m_pTransformCom->Set_State(STATE::POSITION, XMVectorSet(0.f, 0.25f, 0.f, 1.f));

    return S_OK;
}

void CHelmet::Priority_Update(f32_t fDeltaTime)
{
    __super::Priority_Update(fDeltaTime);
    auto pInven = m_pInven.lock();
    if (nullptr == pInven)
    {
        pInven = dynamic_pointer_cast<CInven>(CGameInstance::Get().Find_GameObject(
            ETOUI(LEVEL::STATIC), L"Layer_Static", L"GameObject_Inven"));
        if (nullptr == pInven)
            return;
        m_pInven = pInven;
    }

}

void CHelmet::Update(f32_t fDeltaTime)
{
    __super::Update(fDeltaTime);

    auto pInven = m_pInven.lock();
    if (nullptr == pInven || nullptr == pInven->GetEquipSlot(EQUIP_SLOT::HEAD))
        return;
    Change_Model(pInven->GetEquipSlot(EQUIP_SLOT::HEAD)->strItemName);
    matrix_t        SocketMatrix = XMLoadFloat4x4(m_pSocketMatrix);
    //for (uint32_t i = 0; i < 3; i++)
    //    SocketMatrix.r[i] = XMVector3Normalize(SocketMatrix.r[i]);

    matrix_t        ChildMatrix = XMLoadFloat4x4(m_pTransformCom->Get_WorldMatrixPtr()) * SocketMatrix;
    __super::Update_CombinedWorldMatrix(ChildMatrix);
}


void CHelmet::Late_Update(f32_t fDeltaTime)
{
    __super::Late_Update(fDeltaTime);

    auto pInven = m_pInven.lock();
    if (nullptr == pInven || nullptr == pInven->GetEquipSlot(EQUIP_SLOT::HEAD))
        return;
    CGameInstance::Get().Add_RenderGroup(RENDERID::PLAYER, dynamic_pointer_cast<CGameObject>(shared_from_this()));

}

HRESULT CHelmet::Render()
{
    if (FAILED(Bind_Shader()))
        return E_FAIL;

    if (FAILED(Bind_ShaderResources(XMLoadFloat4x4(&m_CombinedWorldMatrix))))
        return E_FAIL;

    uint32_t        iNumMeshes = m_pModelCom->Get_NumMeshes();

    for (uint32_t i = 0; i < iNumMeshes; i++)
    {
        if (FAILED(m_pModelCom->Bind_Material(i, ModelFile::TEXTURE_TYPE::DIFFUSE, 0, 0)))
            return E_FAIL;

        if (FAILED(m_pModelCom->Render(i)))
            return E_FAIL;
    }

    return S_OK;
}

HRESULT CHelmet::Change_Model(const wstring_t& strMeshPath)
{
    const wstring_t strMeshTag = Normalize_AssetPath(strMeshPath);

    if (false == CGameInstance::Get().Has_Prototype(m_iLevelIndex, strMeshTag))
        return E_FAIL;

    Remove_Component(TEXT("Com_Model"));
    if (FAILED(__super::Add_Component(m_iLevelIndex, strMeshTag, TEXT("Com_Model"), m_pModelCom)))
        return E_FAIL;

    return S_OK;
}

HRESULT CHelmet::Ready_Components()
{
    if (FAILED(__super::Add_Component(ETOUI(LEVEL::STATIC), Proto::Model_Helmet_LV2,
        TEXT("Com_Model"), m_pModelCom)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::STATIC), Proto::VS_MODEL,
        TEXT("Com_VS"), m_pVSCom)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::STATIC), Proto::PS_MODEL,
        TEXT("Com_PS"), m_pPSCom)))
        return E_FAIL;

    return S_OK;
}

HRESULT CHelmet::Bind_Shader()
{
    if (FAILED(m_pVSCom->Begin()))
        return E_FAIL;

    if (FAILED(m_pPSCom->Begin()))
        return E_FAIL;

    return S_OK;
}

HRESULT CHelmet::Bind_ShaderResources(const matrix_t& matWorld)
{
    return __super::Bind_Vertex_ShaderResource(ETOUI(VSLOT::WORLD), matWorld);
}

shared_ptr<CHelmet> CHelmet::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto pInstance = shared_ptr<CHelmet>(new CHelmet(pDevice, pContext));

    if (FAILED(pInstance->Initialize_Prototype()))
    {
        MSG_BOX("Failed to Created : CHelmet");
        pInstance.reset();
    }

    return pInstance;
}


shared_ptr<CPrototype> CHelmet::Clone(void* pArg)
{
    shared_ptr<CHelmet> pInstance = shared_ptr<CHelmet>(new CHelmet(*this));

    if (FAILED(pInstance->Initialize(pArg)))
    {
        MSG_BOX("Failed to Cloned : CHelmet");
        pInstance.reset();
    }

    return pInstance;
}