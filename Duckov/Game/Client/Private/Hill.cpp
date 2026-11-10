#include "Hill.h"
#include <fstream>

CHill::CHill(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    :CMapObject(pDevice, pContext)
{
}

HRESULT CHill::Initialize_Prototype()
{
    if (FAILED(__super::Initialize_Prototype()))
        return E_FAIL;

    D3D11_RASTERIZER_DESC rsDesc{};
    rsDesc.FillMode = D3D11_FILL_SOLID;         
    rsDesc.CullMode = D3D11_CULL_BACK;          
    rsDesc.FrontCounterClockwise = false;       
    rsDesc.DepthClipEnable = true;

    m_pDevice->CreateRasterizerState(&rsDesc, m_pRS.GetAddressOf());

    return S_OK;
}

HRESULT CHill::Initialize(void* pArg)
{
    if (FAILED(__super::Initialize(pArg)))
        return E_FAIL;

    auto pDesc = static_cast<HILL_DESC*>(pArg);
    m_strLayerPath = pDesc->strLayerPath;

    if (FAILED(Ready_Components()))
        return E_FAIL;
    if (FAILED(Ready_ConstantBuffer()))
        return E_FAIL;
    return S_OK;
}

void CHill::Priority_Update(f32_t fDeltaTime)
{
    __super::Priority_Update(fDeltaTime);
}

void CHill::Update(f32_t fDeltaTime)
{
    __super::Update(fDeltaTime);
}
void CHill::Late_Update(f32_t fDeltaTime)
{
    __super::Late_Update(fDeltaTime);
    CGameInstance::Get().Add_RenderGroup(RENDERID::NONALPHA, dynamic_pointer_cast<CGameObject>(shared_from_this()));
}

HRESULT CHill::Render()
{
    // 레스터라이즈 설정
    m_pContext->RSSetState(m_pRS.Get());
    
    if (FAILED(Bind_Shader(m_pVS, m_pPS)))
        return E_FAIL;

    if (FAILED(Bind_ShaderResources(m_pTransformCom->Get_World())))
        return E_FAIL;

    if (FAILED(m_pBufferCom->Bind_Resources()))
        return E_FAIL;

    if (FAILED(m_pBufferCom->Render()))
        return E_FAIL;

    return S_OK;
}

f32_t CHill::GetHeight(f32_t x, f32_t z)
{
    // 로컬로 변환하여 높이를 구한 뒤 다시 월드로 변환하여 y값을 구한다.
    matrix_t matWorld = m_pTransformCom->Get_World();
    matrix_t matInv = XMMatrixInverse(nullptr, matWorld);

    vector_t vLocal = XMVector3TransformCoord(XMVectorSet(x, 0.f, z, 1.f), matInv);
    
    f32_t fLocalY = m_pBufferCom->GetHeight(XMVectorGetX(vLocal), XMVectorGetZ(vLocal));

    vector_t vWorld = XMVector3TransformCoord(
        XMVectorSet(XMVectorGetX(vLocal), fLocalY, XMVectorGetZ(vLocal), 1.f), matWorld);
    return XMVectorGetY(vWorld);
}

float4_t CHill::GetPlane(f32_t x, f32_t z)
{
    return static_pointer_cast<CVIBuffer_Terrain>(__super::Find_Component(L"Com_Buffer"))->GetPlane(x, z);
}
HRESULT CHill::Update_ConstantBuffer(const matrix_t& matWorld)
{
    XMMATRIX matNoTrans = matWorld;
    matNoTrans.r[3] = XMVectorSet(0.f, 0.f, 0.f, 1.f);
    XMMATRIX matWorldInvTranspos = XMMatrixTranspose(XMMatrixInverse(nullptr, matNoTrans));

    XMStoreFloat4x4(&m_tCBData.mat_World, (matWorld));
    XMStoreFloat4x4(&m_tCBData.mat_WorldInvTranspose, (matWorldInvTranspos));

    return S_OK;
}
void CHill::Save_Extra(ofstream& Out) const
{
}

void CHill::Read_Extra(ifstream& In, HILL_DESC& Desc)
{
}

HRESULT CHill::Ready_Components()
{
    if (FAILED(__super::Add_Component(m_iLevelIndex, Normalize_AssetPath(m_strMeshPath),
        TEXT("Com_Buffer"), m_pBufferCom)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(m_iLevelIndex, Normalize_AssetPath(m_strTexturePath),
        TEXT("Com_Blend"), m_pBlendCom)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(m_iLevelIndex, Normalize_AssetPath(m_strLayerPath),
        TEXT("Com_Layer"), m_pLayerCom)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(m_iLevelIndex, Proto::VS_TERRAIN, TEXT("Com_VS"), m_pVS)))
        return E_FAIL;
    if (FAILED(__super::Add_Component(m_iLevelIndex, Proto::PS_TERRAIN, TEXT("Com_PS"), m_pPS)))
        return E_FAIL;

    return S_OK;
}

HRESULT CHill::Ready_ConstantBuffer()
{
    matrix_t matWorld = m_pTransformCom->Get_World();
    matrix_t matNoTrans = matWorld;
    matNoTrans.r[3] = XMVectorSet(0.f, 0.f, 0.f, 1.f);
    matrix_t matWorldInvTranspos = XMMatrixTranspose(XMMatrixInverse(nullptr, matNoTrans));

    XMStoreFloat4x4(&m_tCBData.mat_World, (matWorld));
    XMStoreFloat4x4(&m_tCBData.mat_WorldInvTranspose, (matWorldInvTranspos));

    m_pCB = CConstantBuffer::Create(m_pDevice, m_pContext, &m_tCBData, sizeof(m_tCBData));
    if (nullptr == m_pCB)
        return E_FAIL;
    return S_OK;
}

HRESULT CHill::Bind_Shader(shared_ptr<CVertexShader> pVS, shared_ptr<CPixelShader> pPS)
{
    if (FAILED(m_pVS->Begin()))
        return E_FAIL;

    if (FAILED(m_pPS->Begin()))
        return E_FAIL;
    return S_OK;
}

HRESULT CHill::Bind_ShaderResources(const matrix_t& matWorld)
{
    // 텍스처 바인드
    if (FAILED(m_pLayerCom->Set_TexturePS(0, 2)))   // Layer0 잔디     -> t2
        return E_FAIL;
    if (FAILED(m_pLayerCom->Set_TexturePS(1, 3)))   // Layer1 흙       -> t3
        return E_FAIL;
    if (FAILED(m_pLayerCom->Set_TexturePS(2, 4)))   // Layer2 아스팔트 -> t4
        return E_FAIL;
    if (FAILED(m_pBlendCom->Set_TexturePS(0, 5)))   // 혼합맵          -> t5
        return E_FAIL;

    // 상수버퍼 바인드
    if (FAILED(Update_ConstantBuffer(matWorld)))
        return E_FAIL;

    if (FAILED(m_pCB->Bind_Vertex_ShaderResource(0, &m_tCBData)))
        return E_FAIL;

    if (FAILED(m_pCB->Bind_Pixel_ShaderResource(0, &m_tCBData)))
        return E_FAIL;
    return S_OK;
}

shared_ptr<CHill> CHill::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto pInstance = shared_ptr<CHill>(new CHill(pDevice, pContext));

    if (FAILED(pInstance->Initialize_Prototype()))
        pInstance.reset();

    return pInstance;
}

shared_ptr<CPrototype> CHill::Clone(void* pArg)
{
    auto pInstance = shared_ptr<CHill>(new CHill(*this));
    if (FAILED(pInstance->Initialize(pArg)))
        pInstance.reset();

    return pInstance;
}
