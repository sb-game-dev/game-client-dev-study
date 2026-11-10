#include "StaticProp.h"

CStaticProp::CStaticProp (ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    :CMapObject(pDevice, pContext)
{
}

HRESULT CStaticProp::Initialize_Prototype()
{
    if (FAILED(__super::Initialize_Prototype()))
        return E_FAIL;

    // 래스터라이저 설정
    D3D11_RASTERIZER_DESC rsDesc{};
    rsDesc.FillMode = D3D11_FILL_SOLID;         // D3D11_FILL_WIREFRAME , D3D11_FILL_SOLID
    rsDesc.CullMode = D3D11_CULL_NONE;          // D3D11_CULL_BACK , D3D11_CULL_FRONT,D3D11_CULL_NONE
    rsDesc.FrontCounterClockwise = false;       // 시계방향이 전면
    rsDesc.DepthClipEnable = true;

    m_pDevice->CreateRasterizerState(&rsDesc, m_pRS.GetAddressOf());

    return S_OK;
}

HRESULT CStaticProp::Initialize(void* pArg)
{
    //auto pDesc = static_cast<STATICPROP_DESC*>(pArg);

    // 메시, 텍스처 Transform에 들어갈 변수(Pos, Rot, Scale) 값을 MapObject로 넘겨줌
    if (FAILED(__super::Initialize(pArg)))
        return E_FAIL;

    if (FAILED(Ready_Components()))
        return E_FAIL;

    if (FAILED(Ready_ConstantBuffer()))
        return E_FAIL;

    return S_OK;
}

void CStaticProp ::Priority_Update(f32_t fDeltaTime)
{
    __super::Priority_Update(fDeltaTime);
}

void CStaticProp ::Update(f32_t fDeltaTime)
{
    __super::Update(fDeltaTime);
}
void CStaticProp ::Late_Update(f32_t fDeltaTime)
{
    __super::Late_Update(fDeltaTime);

    
    CGameInstance::Get().Add_RenderGroup(RENDERID::NONALPHA, dynamic_pointer_cast<CGameObject>(shared_from_this()));


}

HRESULT CStaticProp ::Render()
{
    return Render_Mesh(m_pTransformCom->Get_World(), m_pRS.Get(), m_pPS);
}


HRESULT CStaticProp::Change_Mesh(const wstring_t& strMeshPath)
{
    const wstring_t strMeshTag = Normalize_AssetPath(strMeshPath);

    if (false == CGameInstance::Get().Has_Prototype(m_iLevelIndex, strMeshTag))
        return E_FAIL;                              // 등록 안 된 경로 → 기존 메시 유지                             

    shared_ptr<CModel> pNew;
    Remove_Component(TEXT("Com_Model"));
    if (FAILED(__super::Add_Component(m_iLevelIndex, strMeshTag, TEXT("Com_Model"), pNew)))
        return E_FAIL;

    m_pModelCom = pNew;
    m_strMeshPath = strMeshTag;
    return S_OK;
}

HRESULT CStaticProp ::Ready_Components()
{
    if (FAILED(Ready_Mesh()))
        return E_FAIL;

    if (FAILED(__super::Add_Component(m_iLevelIndex, Proto::VS_MODEL,
        TEXT("Com_VS"), m_pVS)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(m_iLevelIndex, Proto::PS_MODEL,
        TEXT("Com_PS"), m_pPS)))
        return E_FAIL;

    return S_OK;
}

HRESULT CStaticProp ::Ready_ConstantBuffer()
{
    m_pCB = CConstantBuffer::Create(m_pDevice, m_pContext, &m_tCBData, sizeof(m_tCBData));
    if (nullptr == m_pCB)
        return E_FAIL;

    return S_OK;
}

HRESULT CStaticProp::Ready_Mesh()
{
    if (FAILED(Change_Mesh(m_strMeshPath)))       return E_FAIL;
    return S_OK;
}

HRESULT CStaticProp::Update_ConstantBuffer(const matrix_t& matWorld)
{
    XMMATRIX matNoTrans = matWorld;
    matNoTrans.r[3] = XMVectorSet(0.f, 0.f, 0.f, 1.f);
    XMMATRIX matWorldInvTranspos = XMMatrixTranspose(XMMatrixInverse(nullptr, matNoTrans));

    XMStoreFloat4x4(&m_tCBData.mat_World, (matWorld));
    XMStoreFloat4x4(&m_tCBData.mat_WorldInvTranspose, (matWorldInvTranspos));

    return S_OK;
}

HRESULT CStaticProp::Bind_Shader(shared_ptr<CVertexShader> pVS, shared_ptr<CPixelShader> pPS)
{
    if (FAILED(pVS->Begin()))
        return E_FAIL;

    if (FAILED(pPS->Begin()))
        return E_FAIL;
    return S_OK;
}

HRESULT CStaticProp::Bind_ShaderResources(const matrix_t& matWorld)
{
    if (FAILED(Update_ConstantBuffer(matWorld)))
        return E_FAIL;

    if (FAILED(m_pCB->Bind_Vertex_ShaderResource(0, &m_tCBData)))
        return E_FAIL;

    if (FAILED(m_pCB->Bind_Pixel_ShaderResource(0, &m_tCBData)))
        return E_FAIL;

    return S_OK;
}

HRESULT CStaticProp::Render_Mesh(const XMMATRIX& matWorld, ID3D11RasterizerState* pRS, shared_ptr<CPixelShader> pPS)
{
    if (FAILED(__super::Render()))
        return E_FAIL;
    m_pContext->RSSetState(pRS);

    if (FAILED(Bind_ShaderResources(matWorld)))
        return E_FAIL;

    if (FAILED(Bind_Shader(m_pVS, pPS)))
        return E_FAIL;

    uint32_t iNumMeshes = m_pModelCom->Get_NumMeshes();
    for (uint32_t i = 0; i < iNumMeshes; ++i)
    {
        if (FAILED(m_pModelCom->Bind_Material(i, aiTextureType_DIFFUSE, 0, 0)))
            return E_FAIL;

        if (FAILED(m_pModelCom->Render(i)))
            return E_FAIL;
    }
    return S_OK;
}

shared_ptr<CStaticProp > CStaticProp::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto pInstance = shared_ptr<CStaticProp >(new CStaticProp (pDevice, pContext));

    if (FAILED(pInstance->Initialize_Prototype()))
        pInstance.reset();

    return pInstance;
}

shared_ptr<CPrototype> CStaticProp::Clone(void* pArg)
{
    auto pInstance = shared_ptr<CStaticProp >(new CStaticProp (*this));
    if (FAILED(pInstance->Initialize(pArg)))
        pInstance.reset();

    return pInstance;
}
