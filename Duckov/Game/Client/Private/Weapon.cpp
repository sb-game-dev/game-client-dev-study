#include "Weapon.h"
#include "Inven.h"
#include "Player.h"
#include "GameInstance.h"
#include "Bullet.h"
#include "Cube.h"
#include "Body_Player.h"
#include "Client_Mouse.h"

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
    if (FAILED(Ready_Bullets()))
        return E_FAIL;

    //m_pTransformCom->Set_Scale(10.f, 10.f, 10.f);
    m_pTransformCom->Rotation(-90.f, 0.f, 0.f);
    //m_pTransformCom->Set_State(STATE::POSITION, XMVectorSet(0.8f, 0.f, 0.f, 1.f));
    
    m_tDamageDesc.fDamage = 50.f;
    m_tDamageDesc.pWeapon = static_pointer_cast<CGameObject>(shared_from_this());
    m_tDamageDesc.iDamageType = ETOUI(DAMAGE_TYPE::MELEE);
    m_tDamageDesc.pAttackObject = m_pParent;

    return S_OK;
}

void CWeapon::Priority_Update(f32_t fDeltaTime)
{
    __super::Priority_Update(fDeltaTime);
    auto pInven = m_pInven.lock();
    if (nullptr == pInven)
    {
        pInven = dynamic_pointer_cast<CInven>(CGameInstance::Get().Find_GameObject(
            ETOUI(LEVEL::STATIC), L"Layer_Static", GO::Inven));
        if (nullptr == pInven)
            return;
        m_pInven = pInven;
    }
    auto pClient_Mouse = m_pClient_Mouse.lock();
    if (nullptr == pClient_Mouse)
    {
        pClient_Mouse = dynamic_pointer_cast<CClient_Mouse>(CGameInstance::Get().Find_GameObject(
            ETOUI(LEVEL::STATIC), L"Layer_Static", GO::Client_Mouse));
        if (nullptr == pClient_Mouse)
            return;
        m_pClient_Mouse = pClient_Mouse;
    }
    for (auto& pBullet : m_Bullets)
    {
        if (nullptr != pBullet && pBullet->Is_Active() && !pBullet->Is_Dead())
            pBullet->Priority_Update(fDeltaTime);
    }
}

void CWeapon::Update(f32_t fDeltaTime)
{
    __super::Update(fDeltaTime);

    for (auto& pBullet : m_Bullets)
    {
        if (nullptr != pBullet && pBullet->Is_Active() && !pBullet->Is_Dead())
            pBullet->Update(fDeltaTime);
    }
    auto pInven = m_pInven.lock();
    auto pPlayer = static_pointer_cast<CPlayer>(m_pParent.lock());
    if (nullptr == pInven || nullptr == pInven->Get_ActiveItem())
        return;
    Change_Model(pInven->Get_ActiveItem()->strItemName);
    Play_FireAnim(fDeltaTime);
    
    matrix_t        SocketMatrix = XMLoadFloat4x4(m_pSocketMatrix);
    matrix_t        ChildMatrix;
    
    if (EQUIP_SLOT::MELEE == pInven->Get_ActiveSlot() || (nullptr != pPlayer && (pPlayer->Is_Swapping() || pPlayer->Is_Rolling())))
    {
        ChildMatrix = XMLoadFloat4x4(m_pTransformCom->Get_WorldMatrixPtr()) * SocketMatrix;
    }
    else
    {
        matrix_t SocketMatrixOnlyPos = XMMatrixTranslationFromVector(SocketMatrix.r[3]);
        matrix_t Recoil = XMMatrixTranslation(0.f, 0.f, -m_fRecoilOffset);
        ChildMatrix = Recoil * SocketMatrixOnlyPos;
    }
    __super::Update_CombinedWorldMatrix(ChildMatrix);

    if(EQUIP_SLOT::MELEE == pInven->Get_ActiveSlot())       Update_MeleeAttack();
    else                                                    Update_GunAttack(fDeltaTime);
}


void CWeapon::Late_Update(f32_t fDeltaTime)
{
    __super::Late_Update(fDeltaTime);

    for (auto& pBullet : m_Bullets)
    {
        if (nullptr != pBullet && pBullet->Is_Active() && !pBullet->Is_Dead())
            pBullet->Late_Update(fDeltaTime);
    }

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
        if (FAILED(m_pModelCom->Bind_Material(i, ModelFile::TEXTURE_TYPE::DIFFUSE, 0, 0)))
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
    if (EQUIP_SLOT::MELEE == m_pInven.lock()->Get_ActiveSlot())
        m_pCubeCollider->Set_OBBSize(m_pModelCom->GetBoundingBox());
    else
        m_pCubeCollider->Set_Active(false);


    return S_OK;
}

void CWeapon::Play_FireAnim(const f32_t fDeltaTime)
{
    auto pInven = m_pInven.lock();
    if (nullptr == pInven || EQUIP_SLOT::MELEE == pInven->Get_ActiveSlot())
    {
        m_pTransformCom->Set_State(STATE::POSITION, XMVectorSet(0.0f, 0.f, 0.f, 1.f));
        return;
    }
    auto pPlayer = static_pointer_cast<CPlayer>(m_pParent.lock());
    if (nullptr != pPlayer)
    {
        if(false == pPlayer->Is_Firing())
            m_fRecoilOffset = 0.f;
        else
        {
            m_fRecoilOffset += m_fRecoilSpeed * fDeltaTime;
            if (m_fRecoilOffset >= 0.1f)
            {
                m_fRecoilOffset = 0.1f; 
                m_fRecoilSpeed = -2.f;
            }
            else if (m_fRecoilOffset <= 0.f)
            { 
                m_fRecoilOffset = 0.f;  
                m_fRecoilSpeed = 2.f;
            }
        }
    }
}

void CWeapon::Update_MeleeAttack()
{
    auto pBody = static_pointer_cast<CPlayer>(m_pParent.lock())->Get_Body();
    if (PLAYER_ANIM::ATTACK_L2R != pBody->Get_UpperAnimState())
    {
        m_pCubeCollider->Set_Active(false);
        return;
    }
    f32_t fRatio = pBody->Get_CurrentTrackPosition(true) / pBody->Get_Duration(true);
    if (fRatio > 0.5f && fRatio < 0.8f)
    {
        m_pCubeCollider->Set_Active(true);
    }
    else
        m_pCubeCollider->Set_Active(false);
}

void CWeapon::TriggerEnter(shared_ptr<class CCollider> pOtherCollider)
{
    if (false == m_pCubeCollider->Get_Active())
        return;
    auto pOtherObject = pOtherCollider->Get_Owner().lock();

    for (auto pHit_Target : m_Hit_Targets)
    {
        if (pHit_Target.lock() == pOtherObject)
            return;
    }
    pOtherObject->Take_Damage(m_tDamageDesc);
    m_Hit_Targets.push_back(pOtherObject);
}

void CWeapon::Clear_Hit_Targets()
{
    m_Hit_Targets.clear();
}

HRESULT CWeapon::Ready_Components()
{
    if (FAILED(__super::Add_Component(ETOUI(LEVEL::STATIC), Proto::Model_Weapon_Axe,
        TEXT("Com_Model"), m_pModelCom)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::STATIC), Proto::VS_MODEL,
        TEXT("Com_VS"), m_pVSCom)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::STATIC), Proto::PS_MODEL,
        TEXT("Com_PS"), m_pPSCom)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::STATIC), Proto::Cube_Collider,
        TEXT("Com_Cube_Collider"), m_pCubeCollider)))
        return E_FAIL;
    m_pCubeCollider->Set_OBBSize(m_pModelCom->GetBoundingBox()); 
    m_pCubeCollider->Set_Active(false);
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

HRESULT CWeapon::Ready_Bullets()
{
    m_Bullets.reserve(m_iNumBullet);
    for (uint32_t i = 0; i < m_iNumBullet; ++i)
    {
        auto pBullet = dynamic_pointer_cast<CBullet>(CGameInstance::Get().Clone_Prototype(ETOUI(LEVEL::STATIC), Proto::Obj_Bullet));
        if(nullptr == pBullet)
            return E_FAIL;
        m_Bullets.push_back(pBullet);
    }
    return S_OK;
}

void CWeapon::Update_GunAttack(const f32_t& fDeltaTime)
{
    auto pPlayer = static_pointer_cast<CPlayer>(m_pParent.lock());
    if (nullptr == pPlayer)
        return;

    if (m_fFireTimer > 0.f)
        m_fFireTimer -= fDeltaTime;
    else if (pPlayer->Is_Firing())
    {
        float3_t vPos = { m_CombinedWorldMatrix._41,m_CombinedWorldMatrix._42,m_CombinedWorldMatrix._43 };
        float3_t vDir = { m_CombinedWorldMatrix._31,m_CombinedWorldMatrix._32,m_CombinedWorldMatrix._33 };
        f32_t fSpeed = { 100.f };
        // 총알 확산
        XMStoreFloat3(&vDir,
            XMVector3TransformNormal(XMLoadFloat3(&vDir), XMMatrixRotationY(XMConvertToRadians(0))));//CGameInstance::Get().Random(-5, 5)
        Fire(vPos,vDir,fSpeed);   //총알 발사
        m_fFireTimer += m_fFireinterval;

        auto pClient_Mouse = m_pClient_Mouse.lock();
        pClient_Mouse->Add_AimSpreadRange(10);
    }
}

void CWeapon::Fire(const float3_t vPos, const float3_t& vDir, f32_t fSpeed)
{
    for (auto& pBullet : m_Bullets)
    {
        if (!pBullet->Is_Active())
        {
            pBullet->Bullet_Active(vPos, vDir, fSpeed);
            return;
        }
    }
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