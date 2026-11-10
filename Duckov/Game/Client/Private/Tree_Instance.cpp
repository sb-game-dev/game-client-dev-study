#include "Tree_Instance.h"
#include "Hill.h"

CTree_Instance::CTree_Instance(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    :CGameObject(pDevice, pContext)
{
}

HRESULT CTree_Instance::Initialize_Prototype()
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

HRESULT CTree_Instance::Initialize(void* pArg)
{
    if (FAILED(__super::Initialize(pArg)))
        return E_FAIL;

    if (FAILED(Ready_Components()))
        return E_FAIL;
    if (FAILED(Ready_InstanceBuffers()))
        return E_FAIL;


    return S_OK;
}

void CTree_Instance::Priority_Update(f32_t fDeltaTime)
{
    __super::Priority_Update(fDeltaTime);
}

void CTree_Instance::Update(f32_t fDeltaTime)
{
    __super::Update(fDeltaTime);
}
void CTree_Instance::Late_Update(f32_t fDeltaTime)
{
    __super::Late_Update(fDeltaTime);
    Cull_Instances();

    if (m_iVisibleCnt > 0)
        CGameInstance::Get().Add_RenderGroup(RENDERID::NONALPHA, dynamic_pointer_cast<CGameObject>(shared_from_this()));
    if (m_iVisibleShadowCnt > 0)
        CGameInstance::Get().Add_RenderGroup(RENDERID::SHADOW, dynamic_pointer_cast<CGameObject>(shared_from_this()));
}

HRESULT CTree_Instance::Render()
{
    return Render_Mesh(m_pInstanceVB.Get(), m_pPS, m_iVisibleCnt);
}

HRESULT CTree_Instance::Render_Shadow()
{
    return Render_Mesh(m_pInstanceVB_Shadow.Get(), m_pPS_Shadow, m_iVisibleShadowCnt);
}

HRESULT CTree_Instance::Ready_Components()
{
    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), Normalize_AssetPath(TEXT("Mesh/Tree/Pfb_Tree_01_1.fbx")),
        TEXT("Com_Model"), m_pModelCom)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), Proto::VS_MODEL_INSTANCE,
        TEXT("Com_VS"), m_pVS)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), Proto::PS_MODEL,
        TEXT("Com_PS"), m_pPS)))
        return E_FAIL;

    //if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), Proto::PS_VTXTEX_SHADOW,
    //    TEXT("Com_PS_SHADOW"), m_pPS_Shadow)))
    //    return E_FAIL;

    return S_OK;
}

HRESULT CTree_Instance::Ready_InstanceBuffers()
{
    m_WorldMats.resize(m_iNumInstance);
    m_ShadowMats.resize(m_iNumInstance);

    auto pHill = static_pointer_cast<CHill>(CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::GAMEPLAY), L"Layer_GameObject", TEXT("GameObject_Hill")));

    const vector_t  vToLight = vector_t{ -0.5f, 0.5f, -0.5f, 0.f };
    const matrix_t matOffset = XMMatrixTranslation(0.f, 0.01f, 0.0f);

    for (uint32_t i = 0; i < m_iNumInstance; ++i)
    {
        float x = f32_t(38.2f + (rand() % 10 - 5.f) * 10);
        float z = f32_t(-207.2f + (rand() % 10 - 5.f) * 10);

        vector_t vPos = vector_t{ x, 0.f, z, 1.f };
        vector_t vPlane = vector_t{ 0.f, 1.f, 0.f, 0.f };
        Compute_OnHill(vPos, vPlane);

        matrix_t matWorld = XMMatrixTranslationFromVector(vPos);    // XMMatrixTranslation에서 매개변수가 벡터로 바뀐 버전
        matrix_t matShadow = matWorld * XMMatrixShadow(vPlane, vToLight);

        matShadow = matShadow * (1.f / XMVectorGetW(matShadow.r[3]));
        matShadow = matShadow * matOffset;

        XMStoreFloat4x4(&m_WorldMats[i], matWorld);
        XMStoreFloat4x4(&m_ShadowMats[i], matShadow);

        //m_tLocalBox.Transform(m_ShadowBoxes[i], matShadow);   // 납작해진 그림자를 감싸는 월드 박스
    }

    D3D11_BUFFER_DESC desc{};
    desc.ByteWidth = sizeof(float4x4_t) * m_iNumInstance;
    desc.Usage = D3D11_USAGE_DYNAMIC;
    desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    if (FAILED(m_pDevice->CreateBuffer(&desc, nullptr, &m_pInstanceVB)))
        return E_FAIL;

    //if (FAILED(m_pDevice->CreateBuffer(&desc, nullptr, &m_pInstanceVB_Shadow)))
    //    return E_FAIL;

    return S_OK;
}

bool CTree_Instance::Compute_OnHill(vector_t& vPos, vector_t& vGroundPlane)
{
    auto pHill = static_pointer_cast<CHill>(CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::GAMEPLAY), L"Layer_GameObject", TEXT("GameObject_Hill")));

    f32_t x = XMVectorGetX(vPos);
    f32_t z = XMVectorGetZ(vPos);
    vPos = XMVectorSetY(vPos, pHill->GetHeight(x, z) + 0.5f);

    float4_t tempPlane = pHill->GetPlane(x, z);
    vGroundPlane = XMLoadFloat4(&tempPlane);

    return true;
}

void CTree_Instance::Cull_Instances()
{
    const matrix_t  matIdentity = XMMatrixIdentity();
    // 큐브 컬링
    D3D11_MAPPED_SUBRESOURCE tMapped{};
    
    if (FAILED(m_pContext->Map(m_pInstanceVB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &tMapped)))
        return;
    
    auto pDst = reinterpret_cast<float4x4_t*>(tMapped.pData);
    m_iVisibleCnt = 0;
    for (uint32_t i = 0; i < m_iNumInstance; ++i)
    {
        if (Is_BoxInFrustum(m_tLocalBox, XMLoadFloat4x4(&m_WorldMats[i])))
            pDst[m_iVisibleCnt++] = m_WorldMats[i];
    }
    m_pContext->Unmap(m_pInstanceVB.Get(), 0);

    //// 그림자 컬링
    //if (FAILED(m_pContext->Map(m_pInstanceVB_Shadow.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &tMapped)))
    //    return;
    //pDst = reinterpret_cast<float4x4_t*>(tMapped.pData);
    //m_iVisibleShadowCnt = 0;
    //
    //for (uint32_t i = 0; i < m_iNumInstance; ++i)
    //{
    //    // 그림자는 로컬스페이스가 없음. 따라서 절두체를 월드까지만 내려야 함.
    //    // 따라서 월드 -> 로컬로 이동하기 위한 월드^-1 를 만들때 사용할 월드 행렬 매개변수로 항등행렬을 보낸다.
    //    if (Is_BoxInFrustum(m_ShadowBoxes[i], matIdentity))
    //        pDst[m_iVisibleShadowCnt++] = m_ShadowMats[i];
    //}
    //m_pContext->Unmap(m_pInstanceVB_Shadow.Get(), 0);
}

HRESULT CTree_Instance::Render_Mesh(ID3D11Buffer* pInstanceVB, shared_ptr<CPixelShader> pPS, uint32_t iInstanceCnt)
{
    // RS(레스터라이저 설정)
    m_pContext->RSSetState(m_pRS.Get());

    if (FAILED(m_pVS->Begin()))
        return E_FAIL;

    if (FAILED(pPS->Begin()))
        return E_FAIL;
    uint32_t    iNumMeshes = m_pModelCom->Get_NumMeshes();
    for (uint32_t i = 0; i < iNumMeshes; ++i)
    {
        if (FAILED(m_pModelCom->Bind_Material(i, aiTextureType_DIFFUSE, 0, 0)))
            return E_FAIL;

        //if (FAILED(m_pModelCom->Bind_Material(i, aiTextureType_NORMALS, 0, 1)))
        //    return E_FAIL;

        if (FAILED(m_pModelCom->Render_Instanced(i,m_pInstanceVB.Get(), sizeof(float4x4_t), iInstanceCnt)))
            return E_FAIL;
    }

    return S_OK;
}

shared_ptr<CTree_Instance> CTree_Instance::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto pInstance = shared_ptr<CTree_Instance>(new CTree_Instance(pDevice, pContext));

    if (FAILED(pInstance->Initialize_Prototype()))
        pInstance.reset();

    return pInstance;
}

shared_ptr<CPrototype> CTree_Instance::Clone(void* pArg)
{
    auto pInstance = shared_ptr<CTree_Instance>(new CTree_Instance(*this));
    if (FAILED(pInstance->Initialize(pArg)))
        pInstance.reset();

    return pInstance;
}
