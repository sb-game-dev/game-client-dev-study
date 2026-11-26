#include "TargetDummy.h"
#include "Body_TargetDummy.h"
#include "Helmet.h"
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
    if (FAILED(Ready_PartObjects()))
        return E_FAIL;
    if (FAILED(Ready_Components()))
        return E_FAIL;

    auto pHill = dynamic_pointer_cast<CHill>(CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::ZEROZONE), L"Layer_GameObject", TEXT("GameObject_Hill")));
    if (nullptr == pHill)
        return E_FAIL;

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
    m_fHitTimeRemaining = max(0.f, m_fHitTimeRemaining - fDeltaTime);
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
    m_fHitTimeRemaining = m_fHitDuration;
    m_pHpBar->Initialize_HitAnimation();
}


HRESULT CTargetDummy::Ready_Components()
{
    if (FAILED(__super::Add_Component(ETOUI(LEVEL::STATIC), Proto::Cube_Collider, TEXT("Com_Cube_Collider"), m_pCube_Collider)))
        return E_FAIL;

    m_pCube_Collider->Set_OBBSize(m_pBodyTargetDummy->Get_AABB());
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

    //CHelmet::HELMET_DESC        HelmetDesc{};
    //HelmetDesc.pParentTransformCom = m_pTransformCom;
    //HelmetDesc.pSocketMatrix = m_pBodyTargetDummy->Get_SocketMatrix("Head");
    //if (FAILED(__super::Add_PartObject(ETOUI(LEVEL::STATIC), Proto::Obj_Helmet,
    //    TEXT("Part_Helmet"), &HelmetDesc)))
    //    return E_FAIL;
    //
    //CArmor::ARMOR_DESC        ArmorDesc{};
    //ArmorDesc.pParentTransformCom = m_pTransformCom;
    //ArmorDesc.pSocketMatrix = m_pBodyTargetDummy->Get_SocketMatrix("Spine.001");
    //if (FAILED(__super::Add_PartObject(ETOUI(LEVEL::STATIC), Proto::Obj_Armor,
    //    TEXT("Part_Armor"), &ArmorDesc)))
    //    return E_FAIL;

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
