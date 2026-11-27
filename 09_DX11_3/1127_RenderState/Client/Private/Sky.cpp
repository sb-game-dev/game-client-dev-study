#include "Sky.h"

#include "GameInstance.h"

CSky::CSky(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    : CGameObject { pDevice, pContext }
{
}

HRESULT CSky::Initialize_Prototype()
{
    if (FAILED(__super::Initialize_Prototype()))
        return E_FAIL;

    /* 백그라운드 원형객체에 필요한 정보를 다 채워둔다. */


    return S_OK;
}

HRESULT CSky::Initialize(void* pArg)
{
    /* 백그라운드 사본객체를 생성할때 원형이 읽어놓은 정보를 사본객체에게 채워준다. */   
    if (FAILED(__super::Initialize(pArg)))
        return E_FAIL;

    if (FAILED(Ready_Components()))
        return E_FAIL;

    return S_OK;
}

void CSky::Priority_Update(f32_t fTimeDelta)
{
    __super::Priority_Update(fTimeDelta);
}

void CSky::Update(f32_t fTimeDelta)
{
    __super::Update(fTimeDelta);

    m_pTransformCom->Set_State(STATE::POSITION, CGameInstance::Get().Get_CamPosition());    
    
}

void CSky::Late_Update(f32_t fTimeDelta)
{
    __super::Late_Update(fTimeDelta);


    /* 백그라운드가 화면에 그려져야하는 상황이라면 렌더러추가해준다. */
    CGameInstance::Get().Add_RenderGroup(RENDERGROUP::PRIORITY, dynamic_pointer_cast<CGameObject>(shared_from_this()));

}

HRESULT CSky::Render()
{

    if (FAILED(Begin_Draw()))
        return E_FAIL;

    if (FAILED(m_pVIBufferCom->Render()))
        return E_FAIL;

    if (FAILED(End_Draw()))
        return E_FAIL;

    return S_OK;
}

HRESULT CSky::Ready_Components()
{
    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), TEXT("Prototype_Component_Texture_Sky"),
        TEXT("Com_Texture"), m_pTextureCom)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), TEXT("Prototype_Component_VIBuffer_Cube"),
        TEXT("Com_VIBuffer"), m_pVIBufferCom)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), TEXT("Prototype_Component_VS_Cube_Sky"),
        TEXT("Com_VS"), m_pVSCom)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), TEXT("Prototype_Component_PS_Cube"),
        TEXT("Com_PS"), m_pPSCom)))
        return E_FAIL;

    return S_OK;
}

HRESULT CSky::Begin_Draw()
{
    if (FAILED(Bind_Shader()))
        return E_FAIL;

    if (FAILED(Bind_ShaderResources()))
        return E_FAIL;

    if (FAILED(m_pVIBufferCom->Bind_Resources()))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Bind_RasterizerState(g_strRS_NonCull)))
        return E_FAIL;
    if (FAILED(CGameInstance::Get().Bind_DepthStencilState(g_strDSS_NonZ)))
        return E_FAIL;

    return S_OK;
}

HRESULT CSky::End_Draw()
{
    if (FAILED(CGameInstance::Get().Bind_RasterizerState(g_strRS_Default)))
        return E_FAIL;
    if (FAILED(CGameInstance::Get().Bind_DepthStencilState(g_strDSS_Default)))
        return E_FAIL;

    return S_OK;
}

HRESULT CSky::Bind_Shader()
{
    if (FAILED(m_pVSCom->Begin()))
        return E_FAIL;

    if (FAILED(m_pPSCom->Begin()))
        return E_FAIL;

    return S_OK;
}

HRESULT CSky::Bind_ShaderResources()
{
    if (FAILED(m_pTextureCom->Bind_Pixel_ShaderResources(0)))
        return E_FAIL;



    if (FAILED(m_pTransformCom->Bind_Vertex_ShaderResource(ETOUI(VSLOT::WORLD))))
        return E_FAIL;

    return S_OK;
}

shared_ptr<CSky> CSky::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto pInstance = shared_ptr<CSky>(new CSky(pDevice, pContext));

    if (FAILED(pInstance->Initialize_Prototype()))
    {
        MSG_BOX("Failed to Created : CSky");
        pInstance.reset();
    }

    return pInstance;
}


shared_ptr<CPrototype> CSky::Clone(void* pArg)
{
    shared_ptr<CSky> pInstance = shared_ptr<CSky>(new CSky(*this));

    if (FAILED(pInstance->Initialize(pArg)))
    {
        MSG_BOX("Failed to Cloned : CSky");
        pInstance.reset();
    }

    return pInstance;
}