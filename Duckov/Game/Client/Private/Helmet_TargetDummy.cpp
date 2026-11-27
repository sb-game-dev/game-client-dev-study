#include "Helmet_TargetDummy.h"

CHelmet_TargetDummy::CHelmet_TargetDummy(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    : CPartObject{ pDevice, pContext }
{
}

HRESULT CHelmet_TargetDummy::Initialize_Prototype()
{
    if (FAILED(__super::Initialize_Prototype()))
        return E_FAIL;

    /* 백그라운드 원형객체에 필요한 정보를 다 채워둔다. */



    return S_OK;
}

HRESULT CHelmet_TargetDummy::Initialize(void* pArg)
{
    if (nullptr != pArg)
    {
        auto        pDesc = static_cast<CHelmet_TargetDummy::HELMETTARGETDUMMY_DESC*>(pArg);

        m_pSocketMatrix = pDesc->pSocketMatrix;
        m_pHelmetTag = pDesc->pHelmetTag;
    }

    /* 백그라운드 사본객체를 생성할때 원형이 읽어놓은 정보를 사본객체에게 채워준다. */
    if (FAILED(__super::Initialize(pArg)))
        return E_FAIL;

    if (FAILED(Ready_Components()))
        return E_FAIL;

    if (FAILED(Ready_ConstantBuffer()))
        return E_FAIL;

    //m_pTransformCom->Set_Scale(10.f, 10.f, 10.f);
    //m_pTransformCom->Rotation(-90.f, 0.f, 0.f);
    m_pTransformCom->Set_State(STATE::POSITION, XMVectorSet(0.f, 0.25f, 0.f, 1.f));

    return S_OK;
}

void CHelmet_TargetDummy::Priority_Update(f32_t fDeltaTime)
{
    __super::Priority_Update(fDeltaTime);
}

void CHelmet_TargetDummy::Update(f32_t fDeltaTime)
{
    __super::Update(fDeltaTime);

    m_fHitTimeRemaining = max(0.f, m_fHitTimeRemaining - fDeltaTime);
    matrix_t        SocketMatrix = XMLoadFloat4x4(m_pSocketMatrix);
    matrix_t        ChildMatrix = XMLoadFloat4x4(m_pTransformCom->Get_WorldMatrixPtr()) * SocketMatrix;
    __super::Update_CombinedWorldMatrix(ChildMatrix);
}


void CHelmet_TargetDummy::Late_Update(f32_t fDeltaTime)
{
    __super::Late_Update(fDeltaTime);

    CGameInstance::Get().Add_RenderGroup(RENDERID::NONALPHA, dynamic_pointer_cast<CGameObject>(shared_from_this()));
}

HRESULT CHelmet_TargetDummy::Render()
{
    if (FAILED(Bind_Shader()))
        return E_FAIL;

    if (FAILED(Bind_ShaderResources(XMLoadFloat4x4(&m_CombinedWorldMatrix))))
        return E_FAIL;

    if (FAILED(m_pCBHitRatio->Bind_Pixel_ShaderResource(7, &m_vHitRatio)))
        return E_FAIL;

    uint32_t    iNumMeshes = m_pModelCom->Get_NumMeshes();
    for (uint32_t i = 0; i < iNumMeshes; ++i)
    {
        if (FAILED(m_pModelCom->Bind_BoneMatrix(i, 2)))
            return E_FAIL;
        if (FAILED(m_pModelCom->Bind_Material(i, ModelFile::TEXTURE_TYPE::DIFFUSE, 0, 0)))
            return E_FAIL;

        //if (FAILED(m_pModelCom->Bind_Material(i, aiTextureType_NORMALS, 0, 1)))
        //    return E_FAIL;

        if (FAILED(m_pModelCom->Render(i)))
            return E_FAIL;
    }
    ID3D11Buffer* pNull = nullptr;
    m_pContext->PSSetConstantBuffers(7, 1, &pNull);

    return S_OK;
}

HRESULT CHelmet_TargetDummy::Ready_ConstantBuffer()
{
    m_pCBHitRatio = CConstantBuffer::Create(m_pDevice, m_pContext, &m_vHitRatio, sizeof(m_vHitRatio));
    if (nullptr == m_pCBHitRatio)
        return E_FAIL;
    return S_OK;
}
HRESULT CHelmet_TargetDummy::Update_ConstantBuffer()
{
    m_vHitRatio.x = m_fHitTimeRemaining / m_fHitDuration;
    m_vHitRatio.y = m_fHitTimeRemaining / m_fHitDuration;
    m_vHitRatio.z = m_fHitTimeRemaining / m_fHitDuration;
    m_vHitRatio.w = m_fHitTimeRemaining / m_fHitDuration;
    return S_OK;
}

HRESULT CHelmet_TargetDummy::Ready_Components()
{
    if (FAILED(__super::Add_Component(ETOUI(LEVEL::STATIC), m_pHelmetTag,
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

HRESULT CHelmet_TargetDummy::Bind_Shader()
{
    if (FAILED(m_pVSCom->Begin()))
        return E_FAIL;

    if (FAILED(m_pPSCom->Begin()))
        return E_FAIL;

    return S_OK;
}

HRESULT CHelmet_TargetDummy::Bind_ShaderResources(const matrix_t& matWorld)
{
    Update_ConstantBuffer();
    return __super::Bind_Vertex_ShaderResource(ETOUI(VSLOT::WORLD), matWorld);
}

shared_ptr<CHelmet_TargetDummy> CHelmet_TargetDummy::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto pInstance = shared_ptr<CHelmet_TargetDummy>(new CHelmet_TargetDummy(pDevice, pContext));

    if (FAILED(pInstance->Initialize_Prototype()))
    {
        MSG_BOX("Failed to Created : CHelmet_TargetDummy");
        pInstance.reset();
    }

    return pInstance;
}


shared_ptr<CPrototype> CHelmet_TargetDummy::Clone(void* pArg)
{
    shared_ptr<CHelmet_TargetDummy> pInstance = shared_ptr<CHelmet_TargetDummy>(new CHelmet_TargetDummy(*this));

    if (FAILED(pInstance->Initialize(pArg)))
    {
        MSG_BOX("Failed to Cloned : CHelmet_TargetDummy");
        pInstance.reset();
    }

    return pInstance;
}