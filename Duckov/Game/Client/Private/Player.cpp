#include "Player.h"

const vector_t	g_vZ_Plus = XMVector4Normalize({ 0.f,0.f,+1.f,0.f });
const vector_t	g_vZ_Minus = XMVector4Normalize({ 0.f,0.f,-1.f,0.f });
const vector_t	g_vX_Plus = XMVector4Normalize({ +1.f,0.f,0.f,0.f });
const vector_t	g_vX_Minus = XMVector4Normalize({ -1.f,0.f,0.f,0.f });
const vector_t	g_vY_Plus = XMVector4Normalize({ 0.f,+1.f,0.f,0.f });
const vector_t	g_vY_Minus = XMVector4Normalize({ 0.f,-1.f,0.f,0.f });
const vector_t	g_vQuad1 = XMVector4Normalize({ +1.f,0.f,+1.f,0.f });
const vector_t	g_vQuad2 = XMVector4Normalize({ -1.f,0.f,+1.f,0.f });
const vector_t	g_vQuad3 = XMVector4Normalize({ -1.f,0.f,-1.f,0.f });
const vector_t	g_vQuad4 = XMVector4Normalize({ +1.f,0.f,-1.f,0.f });

CPlayer::CPlayer(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    :CGameObject(pDevice, pContext)
{
}

HRESULT CPlayer::Initialize_Prototype()
{
    if (FAILED(__super::Initialize_Prototype()))
        return E_FAIL;

    // 상수 버퍼 생성
    D3D11_BUFFER_DESC CBDesc{};
    CBDesc.ByteWidth = sizeof(CB_PER_OBJECT);
    CBDesc.Usage = D3D11_USAGE_DEFAULT;
    CBDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

    // 상수 버퍼를 초기화 할 때 SubResource는 nullptr로 설정. 나중에 UpdateSubresource 할 예정
    if (FAILED(m_pDevice->CreateBuffer(&CBDesc, nullptr, m_pCB.GetAddressOf())))
        return E_FAIL;

    // 레스터라이저 설정
    D3D11_RASTERIZER_DESC rsDesc{};
    rsDesc.FillMode = D3D11_FILL_SOLID;         //D3D11_FILL_WIREFRAME , D3D11_FILL_SOLID
    rsDesc.CullMode = D3D11_CULL_BACK;          // D3D11_CULL_BACK , D3D11_CULL_FRONT
    rsDesc.FrontCounterClockwise = false;       // 시계방향이 전면
    rsDesc.DepthClipEnable = true;

    m_pDevice->CreateRasterizerState(&rsDesc, m_pRS.GetAddressOf());

    rsDesc.FrontCounterClockwise = true;   // 반사되면 감기 순서가 뒤집히므로 앞면 기준도 뒤집음
    m_pDevice->CreateRasterizerState(&rsDesc, m_pRS_Reflect.GetAddressOf());
    return S_OK;
}

HRESULT CPlayer::Initialize(void* pArg)
{
    if (FAILED(__super::Initialize(pArg)))
        return E_FAIL;
    if (FAILED(Ready_Components()))
        return E_FAIL;
    return S_OK;
}

void CPlayer::Priority_Update(f32_t fDeltaTime)
{
    __super::Priority_Update(fDeltaTime);
}

void CPlayer::Update(f32_t fDeltaTime)
{
    __super::Update(fDeltaTime);

    KeyInput(fDeltaTime);
    AdjustPosY();
}
void CPlayer::Late_Update(f32_t fDeltaTime)
{
    __super::Late_Update(fDeltaTime);

    CGameInstance::Get().Add_RenderGroup(RENDERID::PLAYER, dynamic_pointer_cast<CGameObject>(shared_from_this()));
    CGameInstance::Get().Add_RenderGroup(RENDERID::OCCLUDEDPLAYER, dynamic_pointer_cast<CGameObject>(shared_from_this()));
    CGameInstance::Get().Add_RenderGroup(RENDERID::SHADOW, dynamic_pointer_cast<CGameObject>(shared_from_this()));
    CGameInstance::Get().Add_RenderGroup(RENDERID::REFLECT, dynamic_pointer_cast<CGameObject>(shared_from_this()));
}

HRESULT CPlayer::Render()
{
    return Render_Mesh(m_pTransformCom->Get_World(), m_pRS.Get());
}

HRESULT CPlayer::Render_Reflection(const XMMATRIX& matReflect)
{
    return Render_Mesh(m_pTransformCom->Get_World() * matReflect, m_pRS_Reflect.Get());
}

HRESULT CPlayer::Render_Shadow()
{
    XMVECTOR vPlane     = XMLoadFloat4(&m_vGroundPlane);
    XMVECTOR vToLight   = XMVectorSet(-0.5f, 0.5f, -0.5f, 0.f);   // SunLight Direction의 반대, w=0(평행광)

    XMMATRIX matShadow  = XMMatrixShadow(vPlane, vToLight);
    XMMATRIX matOffset  = XMMatrixTranslation(0.f, 0.01f, 0.f);  // 지형과 z-fighting 방지

    return Render_Mesh(m_pTransformCom->Get_World() * matShadow * matOffset, m_pRS.Get(), m_pPS_Shadow->Get_Shader().Get());
}

HRESULT CPlayer::Render_Occluded()
{
    return Render_Mesh(m_pTransformCom->Get_World(), m_pRS.Get(), m_pPS_Occluded->Get_Shader().Get());
}

HRESULT CPlayer::Ready_Components()
{
    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), TEXT("Prototype_Component_VIBuffer_Pyramid"),
        TEXT("Com_Buffer"), m_pBufferCom)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), TEXT("Prototype_Component_VS_VTXCOL"),
        TEXT("Com_VS"), m_pVS)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), TEXT("Prototype_Component_PS_VTXCOL"),
        TEXT("Com_PS"), m_pPS)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), TEXT("Prototype_Component_PS_VTXCOL_SHADOW"),
        TEXT("Com_PS_SHADOW"), m_pPS_Shadow)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), TEXT("Prototype_Component_PS_VTXCOL_OCCLUDEDPLAYER"),
        TEXT("Com_PS_OCCLUDEDPLAYER"), m_pPS_Occluded)))
        return E_FAIL;

    return S_OK;
}

HRESULT CPlayer::Render_Mesh(const XMMATRIX& matWorld, ID3D11RasterizerState* pRS)
{
    return Render_Mesh(matWorld, pRS, m_pPS->Get_Shader().Get());
}
HRESULT CPlayer::Render_Mesh(const XMMATRIX& matWorld, ID3D11RasterizerState* pRS, ID3D11PixelShader* pPS)
{
    // 변환 행렬 계산 -> 상수 버퍼(변환 행렬) 갱신
   //XMMATRIX matWorld = XMMatrixRotationX(m_fRotX) 
   //                    * XMMatrixRotationY(m_fRotY) 
   //                    * XMMatrixRotationZ(m_fRotZ)
   //                    * XMMatrixTranslation(m_vPosition.x, m_vPosition.y, m_vPosition.z);b


   // VS로 전달할 구조체 채우기
   // HLSL은 기본적으로 열 단위로 데이터를 읽기 때문에 전치를 해야 함
    CB_PER_OBJECT cbData;
    XMStoreFloat4x4(&cbData.WorldMatrix, XMMatrixTranspose(matWorld));


    // 변환 행렬의 정보를 가지고있는 m_pCB 버퍼로 복사(USAGE_DEFAULT로 생성해서 드라이버를 통해 복사)
    // 아래에서 VS의 b0 레지스터에 꽂을 예정
    m_pContext->UpdateSubresource(m_pCB.Get(), 0, nullptr, &cbData, 0, 0);
    m_pBufferCom->Bind_Resources();

    // InputLayoyt 꽂기(FVF의 역할)
    m_pContext->IASetInputLayout(m_pVS->Get_InputLayout().Get());

    // VS(버텍스 셰이더 단계) -> 월드변환, 뷰스페이스 변환, 투영 변환 행렬을 전달받아서 버텍스 버퍼에 계산함
    m_pContext->VSSetShader(m_pVS->Get_Shader().Get(), nullptr, 0);

    // VS의 상수버퍼슬롯(b0)에 상수버퍼(변환 행렬 버퍼) 꽂기
    m_pContext->VSSetConstantBuffers(0, //register(b0)과 연결됨
        1,
        m_pCB.GetAddressOf());

    // PS(픽셀 셰이더) -> 지금은 색 밖에 없음
    m_pContext->PSSetShader(pPS, nullptr, 0);

    // RS(레스터라이저 설정)
    m_pContext->RSSetState(pRS);

    // 그리기
    m_pContext->DrawIndexed(m_iIndexCnt, // IndexCnt: 인덱스 버퍼의 크기
        0,  // StartIndexLocation : 사용할 인덱스의 위치
        0); // BaseVERTEXLocation : 정점들을 가져오기 전에 이 호출에서 사용할 인덱스에 더해지는 정수값
    m_pBufferCom->Render();
    return S_OK;
}
void CPlayer::AdjustPosY()
{
    auto pHill = static_pointer_cast<CHill>(CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::GAMEPLAY), L"Layer_GameObject", TEXT("GameObject_Hill")));
    
    vector_t  vPos = m_pTransformCom->Get_State(STATE::POSITION);
    f32_t x = XMVectorGetX(vPos);
    f32_t z = XMVectorGetZ(vPos);
    vPos = XMVectorSetY(vPos, pHill->GetHeight(x, z) + 0.5f);
    m_pTransformCom->Set_State(STATE::POSITION, vPos);
    m_vGroundPlane = pHill->GetPlane(x, z);
    //const auto& vecIndex = pHill->GetIndex();
    //const auto& vecVtx = pHill->GetVertices();
    //
    //for (uint32_t i = 0; i + 2 < vecIndex.size(); i += 3)
    //{
    //    float3_t p0 = vecVtx[vecIndex[i]].vPosition;
    //    float3_t p1 = vecVtx[vecIndex[i + 1]].vPosition;
    //    float3_t p2 = vecVtx[vecIndex[i + 2]].vPosition;
    //
    //    vector_t vPlane = XMPlaneFromPoints(XMLoadFloat3(&p0), XMLoadFloat3(&p1), XMLoadFloat3(&p2));
    //
    //    vector_t vRayPos = vPos + vector_t{ 0,100.f,0,0.f };
    //    vector_t vRayDir = XMVectorSet(0.f, -1.f, 0.f, 0.f);   // 아래 방향
    //
    //    vector_t v0 = XMLoadFloat3(&p0);
    //    vector_t v1 = XMLoadFloat3(&p1);
    //    vector_t v2 = XMLoadFloat3(&p2);
    //
    //    f32_t fDist = 0.f;
    //    if (TriangleTests::Intersects(vRayPos, vRayDir, v0, v1, v2, fDist))
    //    {
    //        float4_t plane;
    //        XMStoreFloat4(&plane, vPlane); // x = a, y = b, z = c, w = d -> ax + by + cz + d = 0
    //
    //        f32_t fY = -(plane.x * XMVectorGetX(vPos) + plane.z * XMVectorGetZ(vPos) + plane.w) / plane.y;
    //
    //        vPos = XMVectorSetY(vPos, fY + 0.5f);
    //        m_pTransformCom->Set_State(STATE::POSITION, vPos);
    //
    //        vector_t vGround = XMPlaneNormalize(vPlane);
    //        if (XMVectorGetY(vGround) < 0.f)        // 법선이 아래를 보면 뒤집기
    //            vGround = XMVectorNegate(vGround);
    //        XMStoreFloat4(&m_vGroundPlane, vGround);
    //        return;
    //    }
    //}
}
void CPlayer::KeyInput(f32_t fDeltaTime)
{
    bool_t  bPushShift = false;
    if (GetAsyncKeyState(VK_LSHIFT))
    {
        m_pTransformCom->Set_Speed(16.f);
        bPushShift = true;
    }
    else
    {
        LookAtMouse(fDeltaTime);
        m_pTransformCom->Set_Speed(8.f);
    }

    vector_t vLook = m_pTransformCom->Get_State(STATE::LOOK);

    if (GetAsyncKeyState('W'))
    {
        if (GetAsyncKeyState('A'))
        {
            m_pTransformCom->Move_Position(g_vQuad2, fDeltaTime);
            if (!bPushShift)
                return;
            f32_t dot = XMVectorGetY(XMVector3Dot(vLook, g_vQuad2));
            if (XMConvertToDegrees(acosf(dot)) > 2.f)
            {
                if (XMVectorGetZ(vLook) > -XMVectorGetX(vLook))
                    m_pTransformCom->Turn(g_vY_Minus, fDeltaTime);
                else
                    m_pTransformCom->Turn(g_vY_Plus, fDeltaTime);
            }
        }
        else if (GetAsyncKeyState('D'))
        {
            m_pTransformCom->Move_Position(g_vQuad1, fDeltaTime);
            if (!bPushShift)
                return;
            f32_t dot = XMVectorGetY(XMVector3Dot(vLook, g_vQuad1));
            if (XMConvertToDegrees(acosf(dot)) > 2.f)
            {
                if (XMVectorGetZ(vLook) < XMVectorGetX(vLook))
                    m_pTransformCom->Turn(g_vY_Minus, fDeltaTime);
                else
                    m_pTransformCom->Turn(g_vY_Plus, fDeltaTime);
            }
        }
        else
        {
            m_pTransformCom->Move_Position(g_vZ_Plus, fDeltaTime);
            if (!bPushShift)
                return;
            f32_t dot = XMVectorGetY(XMVector3Dot(vLook, g_vZ_Plus));
            if (XMConvertToDegrees(acosf(dot)) > 2.f)
            {
                if (XMVectorGetX(vLook) < 0.f)
                    m_pTransformCom->Turn(g_vY_Plus, fDeltaTime);
                else 
                    m_pTransformCom->Turn(g_vY_Minus, fDeltaTime);
            }
        }
    }
    else if (GetAsyncKeyState('S'))
    {
        if (GetAsyncKeyState('A'))
        {
            m_pTransformCom->Move_Position(g_vQuad3, fDeltaTime);
            if (!bPushShift)
                return;
            f32_t dot = XMVectorGetY(XMVector3Dot(vLook, g_vQuad3));
            if (XMConvertToDegrees(acosf(dot)) > 2.f)
            {
                if (XMVectorGetZ(vLook) < XMVectorGetX(vLook))
                    m_pTransformCom->Turn(g_vY_Plus, fDeltaTime);
                else
                    m_pTransformCom->Turn(g_vY_Minus, fDeltaTime);
            }
        }
        else if (GetAsyncKeyState('D'))
        {
            m_pTransformCom->Move_Position(g_vQuad4, fDeltaTime);
            if (!bPushShift)
                return;
            f32_t dot = XMVectorGetY(XMVector3Dot(vLook, g_vQuad4));
            if (XMConvertToDegrees(acosf(dot)) > 2.f)
            {
                if (XMVectorGetZ(vLook) > -XMVectorGetX(vLook))
                    m_pTransformCom->Turn(g_vY_Plus, fDeltaTime);
                else
                    m_pTransformCom->Turn(g_vY_Minus, fDeltaTime);
            }
        }
        else
        {
            m_pTransformCom->Move_Position(g_vZ_Minus, fDeltaTime);
            if (!bPushShift)
                return;
            f32_t dot = XMVectorGetY(XMVector3Dot(vLook, g_vZ_Minus));
            if (XMConvertToDegrees(acosf(dot)) > 2.f)
            {
                if (XMVectorGetX(vLook) < 0.f)
                    m_pTransformCom->Turn(g_vY_Minus, fDeltaTime);
                else
                    m_pTransformCom->Turn(g_vY_Plus, fDeltaTime);
            }
        }
    }
    else if (GetAsyncKeyState('A'))
    {
        m_pTransformCom->Move_Position(g_vX_Minus, fDeltaTime);
        if (!bPushShift)
            return;
        f32_t dot = XMVectorGetY(XMVector3Dot(vLook, g_vX_Minus));
        if (XMConvertToDegrees(acosf(dot)) > 2.f)
        {
            if (XMVectorGetZ(vLook) < 0.f)
                m_pTransformCom->Turn(g_vY_Plus, fDeltaTime);
            else
                m_pTransformCom->Turn(g_vY_Minus, fDeltaTime);
        }
    }
    else if (GetAsyncKeyState('D'))
    {
        m_pTransformCom->Move_Position(g_vX_Plus, fDeltaTime);
        if (!bPushShift)
            return;
        f32_t dot = XMVectorGetY(XMVector3Dot(vLook, g_vX_Plus));
        if (XMConvertToDegrees(acosf(dot)) > 2.f)
        {
            if (XMVectorGetZ(vLook) < 0.f)
                m_pTransformCom->Turn(g_vY_Minus, fDeltaTime);
            else
                m_pTransformCom->Turn(g_vY_Plus, fDeltaTime);
        }
    }

    
}
void CPlayer::LookAtMouse(f32_t fDeltaTime)
{
    auto pMouse = CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::GAMEPLAY), L"Layer_GameObject", L"GameObject_ClientMouse");
    vector_t vTargetPos = pMouse->Get_Transform()->Get_State(STATE::POSITION);
    m_pTransformCom->LookAt(vTargetPos);
}
shared_ptr<CPlayer> CPlayer::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto pInstance = shared_ptr<CPlayer>(new CPlayer(pDevice, pContext));

    if (FAILED(pInstance->Initialize_Prototype()))
    {
        MSG_BOX("Create Failed : CPlayer");
        pInstance.reset();
    }
    return pInstance;
}

shared_ptr<CPrototype> CPlayer::Clone(void* pArg)
{
    auto pInstance = shared_ptr<CPlayer>(new CPlayer(*this));

    if (FAILED(pInstance->Initialize(pArg)))
    {
        MSG_BOX("Clone Failed : CPlayer");
        pInstance.reset();
    }
    return pInstance;
}
