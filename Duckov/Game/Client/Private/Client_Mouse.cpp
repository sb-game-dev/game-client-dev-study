#include "Client_Mouse.h"
#include "QuarterView_Cam.h"
#include "Inven.h"
#include "Player.h"
namespace {
    const f32_t g_SizeX = 27.f;
    const f32_t g_SizeY = 18.f;
    const f32_t g_CusorSizeX = 36.f;
    const f32_t g_CusorSizeY = 36.f;
    const f32_t g_RotZ[4] = { 0.f,90.f,180.f,270.f };
}
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

    // 상수 버퍼 생성 (부모의 m_tCBData 크기, 값은 Render_Mesh에서 갱신)
    m_pCB = CConstantBuffer::Create(m_pDevice, m_pContext, &m_tCBData, sizeof(m_tCBData));
    if (nullptr == m_pCB)
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

    auto pCamera = CGameInstance::Get().Get_MainCamera();
    if (nullptr == pCamera)
        return;
    pCamera->Compute_PickingRay(pt, vRayOrigin, vRayDir);

    auto pPlayer = m_pPlayer.lock();
    if (nullptr == pPlayer)
    {
        pPlayer = dynamic_pointer_cast<CPlayer>(CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::STATIC), L"Layer_Static", TEXT("GameObject_Player")));
        if (nullptr == pPlayer)
            return;
        m_pPlayer = pPlayer;
    }
    auto pInven = m_pInven.lock();
    if (nullptr == pInven)
    {
        pInven = dynamic_pointer_cast<CInven>(CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::STATIC), L"Layer_Static", TEXT("GameObject_Inven")));
        if (nullptr == pInven)
            return ;
        m_pInven = pInven;
    }

     if (pPlayer->Is_Firing() && pInven->Get_ActiveSlot() != EQUIP_SLOT::MELEE)
    {
        // 전부 창 안 좌표로 계산
        float2_t vViewport = CGameInstance::Get().Get_ViewportSize();
        f32_t fDirX = pt.x - vViewport.x * 0.5f;
        f32_t fDirY = pt.y - vViewport.y * 0.5f;
        f32_t fLen = sqrtf(fDirX * fDirX + fDirY * fDirY);

        if (fLen > 1.f)   // 중앙 근처에서는 방향이 없으니 건너뜀
        {
            const f32_t fRecoilSpeed = 80.f;   // 초당 밀려나는 픽셀
            m_vRecoilRemain.x += fDirX / fLen * fRecoilSpeed * fTimeDelta;
            m_vRecoilRemain.y += fDirY / fLen * fRecoilSpeed * fTimeDelta;

            // 정수 부분만 꺼내서 쓰고, 소수점은 남겨 둠
            long iMoveX = (long)m_vRecoilRemain.x;
            long iMoveY = (long)m_vRecoilRemain.y;
            m_vRecoilRemain.x -= iMoveX;
            m_vRecoilRemain.y -= iMoveY;
            if (0 != iMoveX || 0 != iMoveY)
            {
                POINT ptNew = { pt.x + iMoveX, pt.y + iMoveY };

                // SetCursorPos 직전에만 모니터 좌표로 변환
                ClientToScreen(g_hWnd, &ptNew);
                SetCursorPos(ptNew.x, ptNew.y);
            }
        }
    }
    else 
        m_vRecoilRemain = {};

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

    if (pPlayer->Is_Firing() && pInven->Get_ActiveSlot() != EQUIP_SLOT::MELEE)
        static_pointer_cast<CQuarterView_Cam>(CGameInstance::Get().Get_MainCamera())->AddShakeTime(fTimeDelta);
    
    if (m_fAimSpreadRange > 26.f)
        m_fAimSpreadRange -= 100 * fTimeDelta;
    else
        m_fAimSpreadRange = 25.f;
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
    D3D11_MAPPED_SUBRESOURCE tMapped{};

    if (FAILED(m_pContext->Map(m_pInstanceVB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &tMapped)))
        return E_FAIL;

    auto pInven = m_pInven.lock();
    if ((nullptr != pInven && pInven->Is_Open()) || ETOI(LEVEL::MAIN_MENU) >= CGameInstance::Get().Get_CurrentLevelIndex())
    {
        m_eMouseState = MOUSESTATE::CURSOR;
        auto pDst = reinterpret_cast<float4x4_t*>(tMapped.pData);
        matrix_t matScale = XMMatrixScaling(g_CusorSizeX, g_CusorSizeY, 1.f);
        matrix_t matTrans = XMMatrixTranslation(+m_vPosVP.x - g_iWinSizeX * 0.5f + g_CusorSizeX * 0.5f,
                                                -m_vPosVP.y + g_iWinSizeY * 0.5f - g_CusorSizeY * 0.5f,
                                                m_vPosVP.z);
        XMStoreFloat4x4(pDst, matScale * matTrans);        
        m_pContext->Unmap(m_pInstanceVB.Get(), 0);
        return Render_Mesh(m_pInstanceVB.Get(), m_pPS, 1);
    }
    else
    {
        m_eMouseState = MOUSESTATE::ARROW;
        float3_t vOffsetPos[4] = { {0.f,m_fAimSpreadRange,0.f},{-m_fAimSpreadRange,0.f,0.f} ,{0.f,-m_fAimSpreadRange,0.f} ,{m_fAimSpreadRange,0.f,0.f} };
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
    if (FAILED(__super::Add_Component(ETOUI(LEVEL::STATIC), Proto::Texture_Mouse,
        TEXT("Com_Texture"), m_pTextureCom)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::STATIC), Proto::VS_VTXTEX_INSTANCE_UI,
        TEXT("Com_VS"), m_pVS)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::STATIC), Proto::PS_VTXTEX_NOLIGHT,
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
    XMStoreFloat4x4(&m_tCBData.mat_World, XMMatrixIdentity());
    XMStoreFloat4x4(&m_tCBData.mat_WorldInvTranspose, XMMatrixIdentity());

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

    // VS, PS의 상수버퍼 슬롯(b0)에 변환 행렬 버퍼 꽂기
    if (FAILED(m_pCB->Bind_Vertex_ShaderResource(0, &m_tCBData)))
        return E_FAIL;
    if (FAILED(m_pCB->Bind_Pixel_ShaderResource(0, &m_tCBData)))
        return E_FAIL;

    if (FAILED(m_pVS->Begin()))
        return E_FAIL;
    if (FAILED(pPS->Begin()))
        return E_FAIL;

    if (FAILED(m_pTextureCom->Set_TexturePS(ETOUI(m_eMouseState), 0)))
        return E_FAIL;

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