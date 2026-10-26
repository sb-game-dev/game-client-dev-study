#include "Client_Mouse.h"
#include "QuarterView_Cam.h"
#include "Inven.h"
const f32_t g_SizeX = 24.f;
const f32_t g_SizeY = 15.f;
const f32_t g_RotZ[4] = { 0.f,90.f,180.f,270.f };

CClient_Mouse::CClient_Mouse(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    :CMouse{ pDevice,pContext }
{
}

HRESULT CClient_Mouse::Initialize_Prototype()
{
    if (FAILED(__super::Initialize_Prototype()))
        return E_FAIL;

    VTXNORM vertices[] =
    {
        { float3_t(-0.5f, -0.5f, 0.f), float3_t(0.f, 0.f, -1.f), float2_t(0.f, 1.f) },
        { float3_t(-0.5f, +0.5f, 0.f), float3_t(0.f, 0.f, -1.f), float2_t(0.f, 0.f) },
        { float3_t(+0.5f, +0.5f, 0.f), float3_t(0.f, 0.f, -1.f), float2_t(1.f, 0.f) },
        { float3_t(+0.5f, -0.5f, 0.f), float3_t(0.f, 0.f, -1.f), float2_t(1.f, 1.f) },
    };

    // 정점 버퍼 생성
    D3D11_BUFFER_DESC   VBDesc{};
    VBDesc.ByteWidth = sizeof(vertices);
    VBDesc.Usage = D3D11_USAGE_IMMUTABLE;
    VBDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA  VBData{};
    VBData.pSysMem = vertices;  
    if (FAILED(m_pDevice->CreateBuffer(&VBDesc, &VBData, &m_pVB)))
        return E_FAIL;
    // 인덱스 정보
    UINT indices[] = {
        0, 1, 2,
        0, 2, 3,
    };

    // 인덱스 버퍼 생성
    D3D11_BUFFER_DESC IBDesc{};
    IBDesc.ByteWidth = sizeof(indices);
    IBDesc.Usage = D3D11_USAGE_IMMUTABLE;
    IBDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

    D3D11_SUBRESOURCE_DATA IBData{};
    IBData.pSysMem = indices;
    m_iIndexCnt = size(indices);
    if (FAILED(m_pDevice->CreateBuffer(&IBDesc, &IBData, &m_pIB)))
        return E_FAIL;

    // 상수 버퍼 생성
    D3D11_BUFFER_DESC CBDesc{};
    CBDesc.ByteWidth = sizeof(CB_PER_OBJECT_LIT);
    CBDesc.Usage = D3D11_USAGE_DEFAULT;
    CBDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

    // 상수 버퍼를 초기화 할 때 SubResource는 nullptr로 설정. 나중에 UpdateSubresource 할 예정
    if (FAILED(m_pDevice->CreateBuffer(&CBDesc, nullptr, &m_pCB)))
        return E_FAIL;

    // 래스터라이저 설정
    D3D11_RASTERIZER_DESC rsDesc{};
    rsDesc.FillMode = D3D11_FILL_SOLID;         // D3D11_FILL_WIREFRAME , D3D11_FILL_SOLID
    rsDesc.CullMode = D3D11_CULL_BACK;          // D3D11_CULL_BACK , D3D11_CULL_FRONT
    rsDesc.FrontCounterClockwise = false;       // 시계방향이 전면
    rsDesc.DepthClipEnable = true;

    m_pDevice->CreateRasterizerState(&rsDesc, m_pRS.GetAddressOf());

    // 샘플러 생성
    D3D11_SAMPLER_DESC samplerDesc{};

    samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    samplerDesc.AddressU = samplerDesc.AddressV = samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
    samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

    if (FAILED(m_pDevice->CreateSamplerState(&samplerDesc, m_pSampler.GetAddressOf())))
        return E_FAIL;
    return S_OK;
}

HRESULT CClient_Mouse::Initialize(void* pArg)
{
    CClient_Mouse::CLIENT_MOUSE_DESC MouseDesc{};
    if (FAILED(__super::Initialize(&MouseDesc)))
        return E_FAIL;


    if (FAILED(Ready_Components()))
        return E_FAIL;
    if (FAILED(Ready_InstanceBuffers()))
        return E_FAIL;

    return S_OK;
}

void CClient_Mouse::Priority_Update(f32_t fTimeDelta)
{
    __super::Priority_Update(fTimeDelta);
}

void CClient_Mouse::Update(f32_t fTimeDelta)
{
    __super::Update(fTimeDelta);
    POINT		pt = CGameInstance::Get().Get_MousePos();

    m_vPosVP = { (f32_t)pt.x,(f32_t)pt.y,1.f };

    vector_t vRayOrigin = {};
    vector_t vRayDir = {};

    CGameInstance::Get().Get_MainCamera()->Compute_PickingRay(pt, vRayOrigin, vRayDir);

    auto pPlayer = CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::GAMEPLAY), L"Layer_GameObject", L"GameObject_Player");
    if (nullptr == pPlayer)
        return;

    float3_t    vPlayerPos = {};
    float3_t    vecOrigin = {};
    float3_t    vecRayDir = {};
    XMStoreFloat3(&vPlayerPos, pPlayer->Get_Transform()->Get_State(STATE::POSITION));
    XMStoreFloat3(&vecOrigin, vRayOrigin);
    XMStoreFloat3(&vecRayDir, vRayDir);

    // 직선의 방정식 => (x - x`)/a = (y - y`)/b = (z - z`)/c

    f32_t x = (vPlayerPos.y - vecOrigin.y) / vecRayDir.y * vecRayDir.x + vecOrigin.x;
    f32_t z = (vPlayerPos.y - vecOrigin.y) / vecRayDir.y * vecRayDir.z + vecOrigin.z;
    m_pTransformCom->Set_State(STATE::POSITION,{ x, vPlayerPos.y, z, 1.f });

    auto pInven = static_pointer_cast<CInven>(CGameInstance::Get().Find_GameObject(
        ETOUI(LEVEL::GAMEPLAY), L"Layer_GameObject", L"GameObject_Inven"));
    bool_t bInvenOpen = (nullptr != pInven && pInven->Is_Open());

    if (!bInvenOpen && CGameInstance::Get().Mouse_Pressing(DIM::LB) && m_fRange <= 50.f)
    {
        m_fRange += 10.f;
        static_pointer_cast<CQuarterView_Cam>(CGameInstance::Get().Get_MainCamera())->AddShakeTime(fTimeDelta * 2);
    }
    
    if (m_fRange > 26.f)
        m_fRange -= 100 * fTimeDelta;
    else
        m_fRange = 25.f;
}

void CClient_Mouse::Late_Update(f32_t fTimeDelta)
{
    __super::Late_Update(fTimeDelta);
    CGameInstance::Get().Add_RenderGroup(RENDERID::NONALPHA_UI, dynamic_pointer_cast<CGameObject>(shared_from_this()));
}

HRESULT CClient_Mouse::Render()
{
    if (FAILED(__super::Render()))
        return E_FAIL;
    auto pInven = static_pointer_cast<CInven>(CGameInstance::Get().Find_GameObject(
        ETOUI(LEVEL::GAMEPLAY), L"Layer_GameObject", L"GameObject_Inven"));
    D3D11_MAPPED_SUBRESOURCE tMapped{};

    if (FAILED(m_pContext->Map(m_pInstanceVB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &tMapped)))
        return E_FAIL;

    bool_t bInvenOpen = (nullptr != pInven && pInven->Is_Open());
    if (bInvenOpen)
    {
        m_eMouseState = MOUSESTATE::CURSOR;
        auto pDst = reinterpret_cast<float4x4_t*>(tMapped.pData);
        matrix_t matScale = XMMatrixScaling(g_SizeX, g_SizeY, 1.f);
        matrix_t matTrans = XMMatrixTranslation(+m_vPosVP.x - g_iWinSizeX * 0.5f + g_SizeX * 0.5f,
                                                -m_vPosVP.y + g_iWinSizeY * 0.5f - g_SizeY * 0.5f,
                                                m_vPosVP.z);
        XMStoreFloat4x4(pDst, matScale * matTrans);        
        m_pContext->Unmap(m_pInstanceVB.Get(), 0);
        return Render_Mesh(m_pInstanceVB.Get(), m_pPS, 1);
    }
    else
    {
        m_eMouseState = MOUSESTATE::ARROW;
        float3_t vOffsetPos[4] = { {0.f,m_fRange,0.f},{-m_fRange,0.f,0.f} ,{0.f,-m_fRange,0.f} ,{m_fRange,0.f,0.f} };
        auto pDst = reinterpret_cast<float4x4_t*>(tMapped.pData);
        for (uint32_t i = 0; i < 4; ++i)
        {
            matrix_t matScale = XMMatrixScaling(g_SizeX, g_SizeY, 1.f);
            matrix_t matRotZ = XMMatrixRotationZ(XMConvertToRadians(g_RotZ[i]));//+ (rand() % 10 - 5) * 5
            matrix_t matTrans = XMMatrixTranslation(+m_vPosVP.x - g_iWinSizeX * 0.5f + vOffsetPos[i].x,
                -m_vPosVP.y + g_iWinSizeY * 0.5f + vOffsetPos[i].y,
                m_vPosVP.z);
            XMStoreFloat4x4(&pDst[i], matScale * matRotZ * matTrans);
        }
        m_pContext->Unmap(m_pInstanceVB.Get(), 0);
        return Render_Mesh(m_pInstanceVB.Get(), m_pPS, 4);
    }
}

HRESULT CClient_Mouse::Ready_Components()
{
    //StaticLevel로 변경해야 할 듯
    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), Proto::Texture_Mouse,
        TEXT("Com_Texture"), m_pTextureCom)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), Proto::VS_VTXTEX_INSTANCE,
        TEXT("Com_VS"), m_pVS)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), Proto::PS_VTXTEX_NOLIGHT,
        TEXT("Com_PS"), m_pPS)))
        return E_FAIL;

    return S_OK;
}
HRESULT CClient_Mouse::Ready_InstanceBuffers()
{
    D3D11_BUFFER_DESC desc{};
    desc.ByteWidth = sizeof(float4x4_t) * 5;
    desc.Usage = D3D11_USAGE_DYNAMIC;
    desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

    if (FAILED(m_pDevice->CreateBuffer(&desc, nullptr, &m_pInstanceVB)))
        return E_FAIL;
    return S_OK;
}
HRESULT CClient_Mouse::Render_Mesh(ID3D11Buffer* pInstanceVB, shared_ptr<CPixelShader> pPS, uint32_t iInstanceCnt)
{
    CB_PER_OBJECT_LIT cbData;
    XMStoreFloat4x4(&cbData.mat_World, XMMatrixIdentity());
    XMStoreFloat4x4(&cbData.mat_WorldInvTranspose, XMMatrixIdentity());
    cbData.tMaterial = m_tMaterial;

    // 변환 행렬의 정보를 가지고있는 m_pCB 버퍼로 복사(USAGE_DEFAULT로 생성해서 드라이버를 통해 복사)
    // 아래에서 VS의 b0 레지스터에 꽂을 예정
    m_pContext->UpdateSubresource(m_pCB.Get(), 0, nullptr, &cbData, 0, 0);

    // 파이프라인에 꽂기
        //IA(입력 조립기 단계)
        // 정점 하나의 크기와 버퍼의 시작 위치 설정
    ID3D11Buffer* pVBs[] = { m_pVB.Get(),pInstanceVB };
    uint32_t iStride[] = { sizeof(VTXNORM),sizeof(float4x4_t) };
    uint32_t iOffset[] = { 0,0 };
    // 버텍스 버퍼 꽂기
    m_pContext->IASetVertexBuffers(0, 2, pVBs, iStride, iOffset);

    // 인덱스 버퍼 꽂기
    m_pContext->IASetIndexBuffer(m_pIB.Get(), DXGI_FORMAT_R32_UINT, 0);

    // 삼각형 그리기 설정
    m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // VS의 상수버퍼슬롯(b0)에 상수버퍼(변환 행렬 버퍼) 꽂기

    m_pContext->VSSetConstantBuffers(0, 1, m_pCB.GetAddressOf());


    m_pContext->PSSetConstantBuffers(0, //register(b0)과 연결됨
        1,
        m_pCB.GetAddressOf());

    if (FAILED(m_pVS->Begin()))
        return E_FAIL;
    if (FAILED(pPS->Begin()))
        return E_FAIL;

    if (FAILED(m_pTextureCom->Set_TexturePS(ETOUI(m_eMouseState), 0)))
        return E_FAIL;

    // 샘플러 바인드
    m_pContext->PSSetSamplers(0, 1, m_pSampler.GetAddressOf());

    // RS(레스터라이저 설정)
    m_pContext->RSSetState(m_pRS.Get());

    m_pContext->DrawIndexedInstanced(m_iIndexCnt,       // IndexCnt: 인덱스 버퍼의 크기
        iInstanceCnt,    // 인스턴스 개수(월드 행렬의 개수) 
        0, 0, 0);

    return S_OK;
}

shared_ptr<CClient_Mouse> CClient_Mouse::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto pInstance = shared_ptr<CClient_Mouse>(new CClient_Mouse(pDevice, pContext));

    if (FAILED(pInstance->Initialize_Prototype()))
    {
        MSG_BOX("Create Failed : CClient_Mouse");
        pInstance.reset();
    }
    return pInstance;
}

shared_ptr<CPrototype> CClient_Mouse::Clone(void* pArg)
{
    auto pInstance = shared_ptr<CClient_Mouse>(new CClient_Mouse(*this));
    if (FAILED(pInstance->Initialize(pArg)))
    {
        MSG_BOX("Clone Failed : CClient_Mouse");
        pInstance.reset();
    }
    return pInstance;
}