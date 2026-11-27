#include "Bullet_Manager.h"
#include "Bullet.h"
CBullet_Manager::CBullet_Manager(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    : CGameObject{ pDevice,pContext }
{
}

HRESULT CBullet_Manager::Initialize_Prototype()
{
    if (FAILED(__super::Initialize_Prototype()))
        return E_FAIL;
    return S_OK;
}

HRESULT CBullet_Manager::Initialize(void* pArg)
{
    if (FAILED(__super::Initialize(pArg)))
        return E_FAIL;
    if (FAILED(Ready_Bullets()))
        return E_FAIL;
    return S_OK;
}

void CBullet_Manager::Priority_Update(f32_t fDeltaTime)
{
    __super::Priority_Update(fDeltaTime);
    for (auto& pBullet : m_Bullets)
    {
        if (nullptr != pBullet && pBullet->Is_Active() && !pBullet->Is_Dead())
            pBullet->Priority_Update(fDeltaTime);
    }
}

void CBullet_Manager::Update(f32_t fDeltaTime)
{
    __super::Update(fDeltaTime);
    for (auto& pBullet : m_Bullets)
    {
        if (nullptr != pBullet && pBullet->Is_Active() && !pBullet->Is_Dead())
            pBullet->Update(fDeltaTime);
    }
}

void CBullet_Manager::Late_Update(f32_t fDeltaTime)
{
    __super::Late_Update(fDeltaTime);

    for (auto& pBullet : m_Bullets)
    {
        if (nullptr != pBullet && pBullet->Is_Active() && !pBullet->Is_Dead())
            pBullet->Late_Update(fDeltaTime);
    }
}

HRESULT CBullet_Manager::Render()
{
    return S_OK;
}

void CBullet_Manager::Bullet_Active(const float3_t vPos, const float3_t& vDir, f32_t fSpeed)
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

void CBullet_Manager::Check_Collision(const vector<shared_ptr<CGameObject>>& vecObjects)
{
    for (auto& pBullet : m_Bullets)
    {
        if (nullptr == pBullet || !pBullet->Is_Active() || pBullet->Is_Dead())
            continue;
        vector_t vPrevPos = pBullet->Get_PrevPos();
        vector_t vDeltaPos = pBullet->Get_CurrPos() - vPrevPos;
        f32_t fLength = XMVectorGetX(XMVector3Length(vDeltaPos));
        if (fLength < 0.00001f)
            continue;

        vector_t vDir = vDeltaPos / fLength;

        shared_ptr<CGameObject> pHitObject = { nullptr };
        f32_t fMinDist = FLT_MAX;

        for (auto& pObj : vecObjects)
        {
            if (nullptr == pObj || !pObj->Is_Active() || pObj->Is_Dead())
                continue;
            shared_ptr<CCollider> pSrcCollider = { nullptr };
            pObj->Get_Component(pSrcCollider);
            if (FAILED(pObj->Get_Component(pSrcCollider)) || !pSrcCollider->Get_Active())
                continue;

            f32_t fDist = 0.f;
            if (auto pSrcCubeCollider = dynamic_pointer_cast<CCube_Collider>(pSrcCollider))
            {
                if (pSrcCubeCollider->Get_Info().Intersects(vPrevPos, vDir, fDist) && fDist <= fLength && fDist < fMinDist)
                {
                    fMinDist = fDist;
                    pHitObject = pObj;
                }
            }
        }
        if (nullptr != pHitObject)
            pBullet->On_Hit(pHitObject);
    }
}

HRESULT CBullet_Manager::Ready_Bullets()
{
    m_Bullets.reserve(m_iNumBullet);
    for (uint32_t i = 0; i < m_iNumBullet; ++i)
    {
        auto pBullet = dynamic_pointer_cast<CBullet>(CGameInstance::Get().Clone_Prototype(ETOUI(LEVEL::STATIC), Proto::Obj_Bullet));
        if (nullptr == pBullet)
            return E_FAIL;
        m_Bullets.push_back(pBullet);
    }
    return S_OK;
}

shared_ptr<CBullet_Manager> CBullet_Manager::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto pInstance = shared_ptr<CBullet_Manager>(new CBullet_Manager(pDevice, pContext));

    if (FAILED(pInstance->Initialize_Prototype()))
    {
        MSG_BOX("Failed to Created : CBullet_Manager");
        pInstance.reset();
    }

    return pInstance;
}


shared_ptr<CPrototype> CBullet_Manager::Clone(void* pArg)
{
    shared_ptr<CBullet_Manager> pInstance = shared_ptr<CBullet_Manager>(new CBullet_Manager(*this));

    if (FAILED(pInstance->Initialize(pArg)))
    {
        MSG_BOX("Failed to Cloned : CBullet_Manager");
        pInstance.reset();
    }

    return pInstance;
}