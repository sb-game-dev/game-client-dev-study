#include "Scope.h"
#include "Inven.h"

CScope::CScope(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    :CGameObject{ pDevice,pContext }
{
}

HRESULT CScope::Initialize_Prototype()
{
    if (FAILED(__super::Initialize_Prototype()))
        return E_FAIL;

    // 래스터라이저 설정
    D3D11_RASTERIZER_DESC rsDesc{};
    rsDesc.FillMode = D3D11_FILL_SOLID;         // D3D11_FILL_WIREFRAME , D3D11_FILL_SOLID
    rsDesc.CullMode = D3D11_CULL_BACK;          // D3D11_CULL_BACK , D3D11_CULL_FRONT
    rsDesc.FrontCounterClockwise = false;       // 시계방향이 전면
    rsDesc.DepthClipEnable = true;

    m_pDevice->CreateRasterizerState(&rsDesc, m_pRS.GetAddressOf());

    return S_OK;
}

HRESULT CScope::Initialize(void* pArg)
{
    CScope::Scope_DESC        ScopeDesc{};
    if (FAILED(__super::Initialize(&ScopeDesc)))
        return E_FAIL;

    m_pTransformCom->Set_State(STATE::POSITION, vector_t{ 0.f,0.f,1.f,1.f });
    m_pTransformCom->Set_Scale(g_iWinSizeX, g_iWinSizeY, 1.f);

    if (FAILED(Ready_Components()))
        return E_FAIL;
    if (FAILED(Ready_ConstantBuffer()))
        return E_FAIL;

    return S_OK;
}

void CScope::Priority_Update(f32_t fTimeDelta)
{
    __super::Priority_Update(fTimeDelta);
}

void CScope::Update(f32_t fTimeDelta)
{
    __super::Update(fTimeDelta); 
}

void CScope::Late_Update(f32_t fTimeDelta)
{
    __super::Late_Update(fTimeDelta);
    auto pInven = static_pointer_cast<CInven>(CGameInstance::Get().Find_GameObject(
        ETOUI(LEVEL::GAMEPLAY), L"Layer_GameObject", L"GameObject_Inven"));
    bool_t bInvenOpen = (nullptr != pInven && pInven->Is_Open());

    if (!bInvenOpen && CGameInstance::Get().Mouse_Pressing(DIM::RB))
        CGameInstance::Get().Add_RenderGroup(RENDERID::ALPHA_UI, dynamic_pointer_cast<CGameObject>(shared_from_this()));
}
HRESULT CScope::Render()
{
    if (FAILED(__super::Render()))
        return E_FAIL;

    m_pContext->RSSetState(m_pRS.Get());

    if (FAILED(Bind_Shader(m_pVS, m_pPS)))
        return E_FAIL;

    if (FAILED(Bind_ShaderResources()))
        return E_FAIL;

    if (FAILED(m_pBufferCom->Bind_Resources()))
        return E_FAIL;
    
    if (FAILED(m_pBufferCom->Render()))
        return E_FAIL;

    return S_OK;
}
HRESULT CScope::Ready_Components()
{
    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), Proto::VIBuffer_Rect,
        TEXT("Com_Buffer"), m_pBufferCom)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), Proto::VS_VTXCOL,
        TEXT("Com_VS"), m_pVS)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), Proto::PS_VTXCOL_SCOPE,
        TEXT("Com_PS"), m_pPS)))
        return E_FAIL;
    return S_OK;
}
HRESULT CScope::Ready_ConstantBuffer()
{
    XMStoreFloat4x4(&m_tCBData.WorldMatrix, m_pTransformCom->Get_World());
    m_pCB = CConstantBuffer::Create(m_pDevice, m_pContext, &m_tCBData, sizeof(m_tCBData));
    if (nullptr == m_pCB)
        return E_FAIL;

    m_pCBMouse = CConstantBuffer::Create(m_pDevice, m_pContext, &m_tCBMouseData, sizeof(m_tCBMouseData));
    if (nullptr == m_pCBMouse)
        return E_FAIL;
    return S_OK;
}
HRESULT CScope::Update_ConstantBuffer()
{
    POINT		pt = CGameInstance::Get().Get_MousePos();

    m_tCBMouseData.vMousePos = { f32_t(pt.x) , f32_t(pt.y) };
    m_tCBMouseData.fRange = 200.f;
    return S_OK;
}
HRESULT CScope::Bind_Shader(shared_ptr<CVertexShader> pVS, shared_ptr<CPixelShader> pPS)
{
    if (FAILED(m_pVS->Begin()))
        return E_FAIL;
    if (FAILED(m_pPS->Begin()))
        return E_FAIL;
    return S_OK;
}
HRESULT CScope::Bind_ShaderResources(const matrix_t& matWorld)
{
    if (FAILED(Update_ConstantBuffer()))
        return E_FAIL;

    if (FAILED(m_pCB->Bind_Vertex_ShaderResource(0, &m_tCBData)))
        return E_FAIL;

    if (FAILED(m_pCBMouse->Bind_Pixel_ShaderResource(2, &m_tCBMouseData)))
        return E_FAIL;

    return S_OK;
}
shared_ptr<CScope> CScope::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto pInstance = shared_ptr<CScope>(new CScope(pDevice, pContext));

    if (FAILED(pInstance->Initialize_Prototype()))
    {
        MSG_BOX("Create Failed : CScope");
        pInstance.reset();
    }

    return pInstance;
}

shared_ptr<CPrototype> CScope::Clone(void* pArg)
{
    auto pInstance = shared_ptr<CScope>(new CScope(*this));
    if (FAILED(pInstance->Initialize(pArg)))
    {
        MSG_BOX("Clone Failed : CScope");
        pInstance.reset();
    }
    return pInstance;
}