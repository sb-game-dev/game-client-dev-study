#include "TargetDummy.h"
#include "Body_TargetDummy.h"
#include "Helmet_TargetDummy.h"
#include "Armor_TargetDummy.h"
#include "Armor.h"
#include "Hill.h"
#include "UI_HpBar.h"

CTargetDummy::CTargetDummy(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    :CContainerObject(pDevice, pContext)
{
}

HRESULT CTargetDummy::Initialize_Prototype()
{
    if (FAILED(__super::Initialize_Prototype()))
        return E_FAIL;
    return S_OK;
}

HRESULT CTargetDummy::Initialize(void* pArg)
{
    if (FAILED(__super::Initialize(pArg)))
        return E_FAIL;

    if (nullptr != pArg)
    {
        auto        pDesc = static_cast<CTargetDummy::TARGETDUMMY_DESC*>(pArg);

        m_pHelmetTag = pDesc->pHelmetTag;
        m_pArmorTag = pDesc->pArmorTag;
    }

    m_pTransformCom->Rotation(0.f, 90.f, 0.f);

    if (FAILED(Ready_PartObjects()))
        return E_FAIL;
    if (FAILED(Ready_Components()))
        return E_FAIL;

    XMStoreFloat4x4(&m_HelmetSocketmatrix, XMMatrixTranslation(0.f, 0.7f, 0.f));
    XMStoreFloat4x4(&m_ArmorSocketmatrix, XMMatrixTranslation(0.f, 0.35f, 0.f));

    auto pHill = dynamic_pointer_cast<CHill>(CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::ZEROZONE), L"Layer_GameObject", TEXT("GameObject_Hill")));
    if (nullptr == pHill)
        return S_OK;

    vector_t  vPos = m_pTransformCom->Get_State(STATE::POSITION);
    f32_t x = XMVectorGetX(vPos);
    f32_t z = XMVectorGetZ(vPos);
    vPos = XMVectorSetY(vPos, pHill->GetHeight(x, z) + 0.13f);
    m_pTransformCom->Set_State(STATE::POSITION, vPos);
    m_vGroundPlane = pHill->GetPlane(x, z);
    return S_OK;
}

void CTargetDummy::Priority_Update(f32_t fDeltaTime)
{
    __super::Priority_Update(fDeltaTime);
}

void CTargetDummy::Update(f32_t fDeltaTime)
{
    __super::Update(fDeltaTime);
}
void CTargetDummy::Late_Update(f32_t fDeltaTime)
{
    __super::Late_Update(fDeltaTime);
}

HRESULT CTargetDummy::Render()
{
    if (FAILED(__super::Render()))
        return E_FAIL;
    return S_OK;
}

void CTargetDummy::TriggerEnter(shared_ptr<class CCollider> pOtherCollider)
{

}

void CTargetDummy::Take_Damage(const DAMAGE_DESC& Desc)
{
    m_fHP -= Desc.fDamage;
    m_pBodyTargetDummy->Set_Hit();
    if(m_pArmorTargetDummy)     m_pArmorTargetDummy->Set_Hit();
    if(m_pHelmetTargetDummy)    m_pHelmetTargetDummy->Set_Hit();

    m_pHpBar->Initialize_HitAnimation();
}


HRESULT CTargetDummy::Ready_Components()
{
    if (FAILED(__super::Add_Component(ETOUI(LEVEL::STATIC), Proto::Cube_Collider, TEXT("Com_Cube_Collider"), m_pCube_Collider)))
        return E_FAIL;

    const BoundingBox& AABB = m_pBodyTargetDummy->Get_AABB();
    m_pCube_Collider->Set_OBBSize(AABB);
    m_pCube_Collider->Set_Offset({ 0.f, AABB.Center.y, 0.f });
    return S_OK;
}

HRESULT CTargetDummy::Ready_PartObjects()
{
    CBody_TargetDummy::BODYTARGETDUMMY_DESC BodyDesc{};
    BodyDesc.pParentTransformCom = m_pTransformCom;

    if (FAILED(__super::Add_PartObject(m_iLevelIndex, Proto::Obj_Body_TargetDummy,
        TEXT("Part_Body"), &BodyDesc)))
        return E_FAIL;
    m_pBodyTargetDummy = dynamic_pointer_cast<CBody_TargetDummy>(m_PartObjects[TEXT("Part_Body")]);

    if (nullptr != m_pHelmetTag)
    {
        CHelmet_TargetDummy::HELMETTARGETDUMMY_DESC        HelmetDesc{};
        HelmetDesc.pParentTransformCom = m_pTransformCom;
        HelmetDesc.pSocketMatrix = &m_HelmetSocketmatrix;
        HelmetDesc.pHelmetTag = m_pHelmetTag;
        if (FAILED(__super::Add_PartObject(ETOUI(m_iLevelIndex), Proto::Obj_Helmet_TargetDummy,
            TEXT("Part_Helmet"), &HelmetDesc)))
            return E_FAIL;
        m_pHelmetTargetDummy = dynamic_pointer_cast<CHelmet_TargetDummy>(m_PartObjects[TEXT("Part_Helmet")]);

    }
    if (nullptr != m_pArmorTag)
    {
        CArmor_TargetDummy::ARMORTARGETDUMMY_DESC        ArmorDesc{};
        ArmorDesc.pParentTransformCom = m_pTransformCom;
        ArmorDesc.pSocketMatrix = &m_ArmorSocketmatrix;
        ArmorDesc.pArmorTag = m_pArmorTag;
        if (FAILED(__super::Add_PartObject(ETOUI(m_iLevelIndex), Proto::Obj_Armor_TargetDummy,
            TEXT("Part_Armor"), &ArmorDesc)))
            return E_FAIL;
        m_pArmorTargetDummy = dynamic_pointer_cast<CArmor_TargetDummy>(m_PartObjects[TEXT("Part_Armor")]);
    }

    CUI_HpBar::UIHPBAR_DESC    UI_HpBarDesc{};
    UI_HpBarDesc.pParentTransformCom = m_pTransformCom;
    if (FAILED(__super::Add_PartObject(ETOUI(LEVEL::STATIC), Proto::Obj_UI_HpBar,
        TEXT("Part_HpBar"), &UI_HpBarDesc)))
        return E_FAIL;
    m_pHpBar = dynamic_pointer_cast<CUI_HpBar>(m_PartObjects[TEXT("Part_HpBar")]);

    return S_OK;
}

shared_ptr<CTargetDummy> CTargetDummy::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto pInstance = shared_ptr<CTargetDummy>(new CTargetDummy(pDevice, pContext));

    if (FAILED(pInstance->Initialize_Prototype()))
    {
        MSG_BOX("Create Failed : CTargetDummy");
        pInstance.reset();
    }
    return pInstance;
}

shared_ptr<CPrototype> CTargetDummy::Clone(void* pArg)
{
    auto pInstance = shared_ptr<CTargetDummy>(new CTargetDummy(*this));

    if (FAILED(pInstance->Initialize(pArg)))
    {
        MSG_BOX("Clone Failed : CTargetDummy");
        pInstance.reset();
    }
    return pInstance;
}
