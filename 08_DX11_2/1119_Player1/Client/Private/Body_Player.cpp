#include "Body_Player.h"

#include "GameInstance.h"

CBody_Player::CBody_Player(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    : CPartObject { pDevice, pContext }
{
}

HRESULT CBody_Player::Initialize_Prototype()
{
    if (FAILED(__super::Initialize_Prototype()))
        return E_FAIL;

    /* 백그라운드 원형객체에 필요한 정보를 다 채워둔다. */
    


    return S_OK;
}

HRESULT CBody_Player::Initialize(void* pArg)
{
    /* 백그라운드 사본객체를 생성할때 원형이 읽어놓은 정보를 사본객체에게 채워준다. */   
    if (FAILED(__super::Initialize(pArg)))
        return E_FAIL;

    if (FAILED(Ready_Components()))
        return E_FAIL;  

    m_pModelCom->Set_Animation(/*rand() % 20*/0, true);

    return S_OK;
}

void CBody_Player::Priority_Update(f32_t fTimeDelta)
{
    __super::Priority_Update(fTimeDelta);
}

void CBody_Player::Update(f32_t fTimeDelta)
{
    __super::Update(fTimeDelta);

    m_pModelCom->Play_Animation(fTimeDelta);
}

void CBody_Player::Late_Update(f32_t fTimeDelta)
{
    __super::Late_Update(fTimeDelta);

    CGameInstance::Get().Add_RenderGroup(RENDERGROUP::NONBLEND, dynamic_pointer_cast<CGameObject>(shared_from_this()));

}

HRESULT CBody_Player::Render()
{
    if (FAILED(Bind_Shader()))
        return E_FAIL;

    if (FAILED(Bind_ShaderResources()))
        return E_FAIL;

    uint32_t        iNumMeshes = m_pModelCom->Get_NumMeshes();

    for (uint32_t i = 0; i < iNumMeshes; i++)
    {
        if (FAILED(m_pModelCom->Bind_BoneMatrices(i, 2)))
            return E_FAIL;

        if (FAILED(m_pModelCom->Bind_Material(i, aiTextureType_DIFFUSE, 0, 0)))
            return E_FAIL;

        if (FAILED(m_pModelCom->Render(i)))
            return E_FAIL;
    }
   
    return S_OK;
}

HRESULT CBody_Player::Ready_Components()
{

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), TEXT("Prototype_Component_Model_Fiona"),
        TEXT("Com_Model"), m_pModelCom)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), TEXT("Prototype_Component_VS_AnimMesh"),
        TEXT("Com_VS"), m_pVSCom)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), TEXT("Prototype_Component_PS_Mesh"),
        TEXT("Com_PS"), m_pPSCom)))
        return E_FAIL;

    return S_OK;
}

HRESULT CBody_Player::Bind_Shader()
{
    if (FAILED(m_pVSCom->Begin()))
        return E_FAIL;

    if (FAILED(m_pPSCom->Begin()))
        return E_FAIL;

    return S_OK;
}

HRESULT CBody_Player::Bind_ShaderResources()
{
    if (FAILED(m_pTransformCom->Bind_Vertex_ShaderResource(ETOUI(VSLOT::WORLD))))
        return E_FAIL;

    return S_OK;
}

shared_ptr<CBody_Player> CBody_Player::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto pInstance = shared_ptr<CBody_Player>(new CBody_Player(pDevice, pContext));

    if (FAILED(pInstance->Initialize_Prototype()))
    {
        MSG_BOX("Failed to Created : CBody_Player");
        pInstance.reset();
    }

    return pInstance;
}


shared_ptr<CPrototype> CBody_Player::Clone(void* pArg)
{
    shared_ptr<CBody_Player> pInstance = shared_ptr<CBody_Player>(new CBody_Player(*this));

    if (FAILED(pInstance->Initialize(pArg)))
    {
        MSG_BOX("Failed to Cloned : CBody_Player");
        pInstance.reset();
    }

    return pInstance;
}