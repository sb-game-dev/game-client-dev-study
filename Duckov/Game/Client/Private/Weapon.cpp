#include "Weapon.h"
#include "Inven.h"
#include "GameInstance.h"

CWeapon::CWeapon(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    : CPartObject{ pDevice, pContext }
{
}

HRESULT CWeapon::Initialize_Prototype()
{
    if (FAILED(__super::Initialize_Prototype()))
        return E_FAIL;

    /* 백그라운드 원형객체에 필요한 정보를 다 채워둔다. */



    return S_OK;
}

HRESULT CWeapon::Initialize(void* pArg)
{
    if (nullptr != pArg)
    {
        auto        pDesc = static_cast<CWeapon::WEAPON_DESC*>(pArg);
        m_pSocketMatrix = pDesc->pSocketMatrix;
    }

    /* 백그라운드 사본객체를 생성할때 원형이 읽어놓은 정보를 사본객체에게 채워준다. */
    if (FAILED(__super::Initialize(pArg)))
        return E_FAIL;

    if (FAILED(Ready_Components()))
        return E_FAIL;

    //m_pTransformCom->Set_Scale(10.f, 10.f, 10.f);
    m_pTransformCom->Rotation(-90.f, 0.f, 0.f);
    //m_pTransformCom->Set_State(STATE::POSITION, XMVectorSet(0.8f, 0.f, 0.f, 1.f));

    return S_OK;
}

void CWeapon::Priority_Update(f32_t fTimeDelta)
{
    __super::Priority_Update(fTimeDelta);
    auto pInven = m_pInven.lock();
    if (nullptr == pInven)
    {
        pInven = dynamic_pointer_cast<CInven>(CGameInstance::Get().Find_GameObject(
            ETOUI(LEVEL::GAMEPLAY), L"Layer_GameObject", L"GameObject_Inven"));
        if (nullptr == pInven)
            return;
        m_pInven = pInven;
    }
}

void CWeapon::Update(f32_t fTimeDelta)
{
    __super::Update(fTimeDelta);

    auto pInven = m_pInven.lock();
    if (nullptr == pInven || nullptr == pInven->Get_ActiveItem())
        return;
    Change_Model(pInven->Get_ActiveItem()->strItemName);
    matrix_t        SocketMatrix = XMLoadFloat4x4(m_pSocketMatrix);
    //for (uint32_t i = 0; i < 3; i++)
    //    SocketMatrix.r[i] = XMVector3Normalize(SocketMatrix.r[i]);

    matrix_t        ChildMatrix = XMLoadFloat4x4(m_pTransformCom->Get_WorldMatrixPtr()) * SocketMatrix;
    __super::Update_CombinedWorldMatrix(ChildMatrix);
}


void CWeapon::Late_Update(f32_t fTimeDelta)
{
    __super::Late_Update(fTimeDelta);

    auto pInven = m_pInven.lock();
    if (nullptr == pInven || nullptr == pInven->Get_ActiveItem())
        return;
    CGameInstance::Get().Add_RenderGroup(RENDERID::PLAYER, dynamic_pointer_cast<CGameObject>(shared_from_this()));

}

HRESULT CWeapon::Render()
{
    if (FAILED(Bind_Shader()))
        return E_FAIL;

    if (FAILED(Bind_ShaderResources(XMLoadFloat4x4(&m_CombinedWorldMatrix))))
        return E_FAIL;

    uint32_t        iNumMeshes = m_pModelCom->Get_NumMeshes();

    for (uint32_t i = 0; i < iNumMeshes; i++)
    {
        if (FAILED(m_pModelCom->Bind_Material(i, aiTextureType_DIFFUSE, 0, 0)))
            return E_FAIL;

        if (FAILED(m_pModelCom->Render(i)))
            return E_FAIL;
    }

    return S_OK;
}

HRESULT CWeapon::Change_Model(const wstring_t& strMeshPath)
{
    const wstring_t strMeshTag = Normalize_AssetPath(strMeshPath);

    if (false == CGameInstance::Get().Has_Prototype(m_iLevelIndex, strMeshTag))
        return E_FAIL;

    Remove_Component(TEXT("Com_Model"));
    if (FAILED(__super::Add_Component(m_iLevelIndex, strMeshTag, TEXT("Com_Model"), m_pModelCom)))
        return E_FAIL;

    return S_OK;
}

HRESULT CWeapon::Ready_Components()
{
    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), Proto::Model_Weapon_Axe,
        TEXT("Com_Model"), m_pModelCom)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), Proto::VS_MODEL,
        TEXT("Com_VS"), m_pVSCom)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), Proto::PS_MODEL,
        TEXT("Com_PS"), m_pPSCom)))
        return E_FAIL;

    return S_OK;
}

HRESULT CWeapon::Bind_Shader()
{
    if (FAILED(m_pVSCom->Begin()))
        return E_FAIL;

    if (FAILED(m_pPSCom->Begin()))
        return E_FAIL;

    return S_OK;
}

HRESULT CWeapon::Bind_ShaderResources(const matrix_t& matWorld)
{
    return __super::Bind_Vertex_ShaderResource(ETOUI(VSLOT::WORLD), matWorld);
}

shared_ptr<CWeapon> CWeapon::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto pInstance = shared_ptr<CWeapon>(new CWeapon(pDevice, pContext));

    if (FAILED(pInstance->Initialize_Prototype()))
    {
        MSG_BOX("Failed to Created : CWeapon");
        pInstance.reset();
    }

    return pInstance;
}


shared_ptr<CPrototype> CWeapon::Clone(void* pArg)
{
    shared_ptr<CWeapon> pInstance = shared_ptr<CWeapon>(new CWeapon(*this));

    if (FAILED(pInstance->Initialize(pArg)))
    {
        MSG_BOX("Failed to Cloned : CWeapon");
        pInstance.reset();
    }

    return pInstance;
}