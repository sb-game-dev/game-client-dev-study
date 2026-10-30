#include "Terrain.h"

#include "GameInstance.h"

CTerrain::CTerrain(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    : CGameObject { pDevice, pContext }
{
}

HRESULT CTerrain::Initialize_Prototype()
{
    if (FAILED(__super::Initialize_Prototype()))
        return E_FAIL;

    /* 백그라운드 원형객체에 필요한 정보를 다 채워둔다. */


    return S_OK;
}

HRESULT CTerrain::Initialize(void* pArg)
{
    /* 백그라운드 사본객체를 생성할때 원형이 읽어놓은 정보를 사본객체에게 채워준다. */   
    if (FAILED(__super::Initialize(pArg)))
        return E_FAIL;

    if (FAILED(Ready_Components()))
        return E_FAIL;

    return S_OK;
}

void CTerrain::Priority_Update(f32_t fTimeDelta)
{
    __super::Priority_Update(fTimeDelta);
}

void CTerrain::Update(f32_t fTimeDelta)
{
    __super::Update(fTimeDelta);
}

void CTerrain::Late_Update(f32_t fTimeDelta)
{
    __super::Late_Update(fTimeDelta);


    /* 백그라운드가 화면에 그려져야하는 상황이라면 렌더러추가해준다. */
    CGameInstance::Get().Add_RenderGroup(RENDERGROUP::NONBLEND, dynamic_pointer_cast<CGameObject>(shared_from_this()));

}

HRESULT CTerrain::Render()
{
    if (FAILED(Bind_Shader()))
        return E_FAIL;

    if (FAILED(Bind_ShaderResources()))
        return E_FAIL;

    if (FAILED(m_pVIBufferCom->Bind_Resources()))
        return E_FAIL;

    if (FAILED(m_pVIBufferCom->Render()))
        return E_FAIL;

    return S_OK;
}

HRESULT CTerrain::Ready_Components()
{
    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), TEXT("Prototype_Component_Texture_Terrain"),
        TEXT("Com_Texture"), m_pTextureCom)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), TEXT("Prototype_Component_VIBuffer_Terrain"),
        TEXT("Com_VIBuffer"), m_pVIBufferCom)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), TEXT("Prototype_Component_VS_PosNorTex"),
        TEXT("Com_VS"), m_pVSCom)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), TEXT("Prototype_Component_PS_PosNorTex"),
        TEXT("Com_PS"), m_pPSCom)))
        return E_FAIL;

    return S_OK;
}

HRESULT CTerrain::Bind_Shader()
{
    if (FAILED(m_pVSCom->Begin()))
        return E_FAIL;

    if (FAILED(m_pPSCom->Begin()))
        return E_FAIL;

    return S_OK;
}

HRESULT CTerrain::Bind_ShaderResources()
{
    if (FAILED(m_pTextureCom->Bind_Pixel_ShaderResources(0)))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Bind_Sampler_Pixel_Shader(g_strSampler_Point, 0)))
        return E_FAIL;

    if (FAILED(m_pTransformCom->Bind_Vertex_ShaderResource(0)))
        return E_FAIL;

    return S_OK;
}

shared_ptr<CTerrain> CTerrain::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto pInstance = shared_ptr<CTerrain>(new CTerrain(pDevice, pContext));

    if (FAILED(pInstance->Initialize_Prototype()))
    {
        MSG_BOX("Failed to Created : CTerrain");
        pInstance.reset();
    }

    return pInstance;
}


shared_ptr<CPrototype> CTerrain::Clone(void* pArg)
{
    shared_ptr<CTerrain> pInstance = shared_ptr<CTerrain>(new CTerrain(*this));

    if (FAILED(pInstance->Initialize(pArg)))
    {
        MSG_BOX("Failed to Cloned : CTerrain");
        pInstance.reset();
    }

    return pInstance;
}