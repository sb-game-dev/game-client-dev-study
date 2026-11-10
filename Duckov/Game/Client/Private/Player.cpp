#include "Player.h"
#include "Inven.h"

namespace {
    vector_t	g_vY_Plus = XMVector4Normalize({ 0.f,+1.f,0.f,0.f });
    vector_t	g_vY_Minus = XMVector4Normalize({ 0.f,-1.f,0.f,0.f });
}

CPlayer::CPlayer(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    :CMapObject(pDevice, pContext)
{
}

HRESULT CPlayer::Initialize_Prototype()
{
    if (FAILED(__super::Initialize_Prototype()))
        return E_FAIL;

    // 레스터라이저 설정
    D3D11_RASTERIZER_DESC rsDesc{};
    rsDesc.FillMode = D3D11_FILL_SOLID;         //D3D11_FILL_WIREFRAME , D3D11_FILL_SOLID
    rsDesc.CullMode = D3D11_CULL_BACK;          // D3D11_CULL_BACK , D3D11_CULL_FRONT
    rsDesc.FrontCounterClockwise = false;       // 시계방향이 전면
    rsDesc.DepthClipEnable = true;

    m_pDevice->CreateRasterizerState(&rsDesc, m_pRS.GetAddressOf());

    rsDesc.FrontCounterClockwise = true;        // 반사되면 감기 순서가 뒤집히므로 앞면 기준도 뒤집음
    m_pDevice->CreateRasterizerState(&rsDesc, m_pRS_Reflect.GetAddressOf());
    return S_OK;
}

HRESULT CPlayer::Initialize(void* pArg)
{
    if (FAILED(__super::Initialize(pArg)))
        return E_FAIL;
    if (FAILED(Ready_Components()))
        return E_FAIL;
    if (FAILED(Ready_ConstantBuffer()))
        return E_FAIL;
    return S_OK;
}

void CPlayer::Priority_Update(f32_t fDeltaTime)
{
    __super::Priority_Update(fDeltaTime);
    if (m_bEditorMode)
        return;

    m_bAiming = false;
    m_bFiring = false;

    auto pInven = m_pInven.lock();
    if (nullptr == pInven)
    {
        pInven = dynamic_pointer_cast<CInven>(CGameInstance::Get().Find_GameObject(
            ETOUI(LEVEL::GAMEPLAY), L"Layer_GameObject", L"GameObject_Inven"));
        if (nullptr == pInven)
            return;
        m_pInven = pInven;
    }
    bool_t bInvenOpen = (nullptr != pInven && pInven->Is_Open());

    if (!bInvenOpen)
    {
        KeyInput(fDeltaTime);
        AdjustPosY();
    }
}

void CPlayer::Update(f32_t fDeltaTime)
{
    __super::Update(fDeltaTime);
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
    return Render_Mesh(m_pTransformCom->Get_World(), m_pRS.Get(), m_pPS);
}

HRESULT CPlayer::Render_Reflection(const matrix_t& matReflect)
{
    if (m_bEditorMode)
        return S_OK;
    return Render_Mesh(m_pTransformCom->Get_World() * matReflect, m_pRS_Reflect.Get(), m_pPS);
}

HRESULT CPlayer::Render_Shadow()
{
    if (m_bEditorMode)
        return S_OK;
    XMVECTOR vPlane     = XMLoadFloat4(&m_vGroundPlane);
    XMVECTOR vToLight   = XMVectorSet(-0.5f, 0.5f, -0.5f, 0.f);  // SunLight Direction의 반대, w=0(평행광)

    matrix_t matShadow  = XMMatrixShadow(vPlane, vToLight);
    matrix_t matOffset  = XMMatrixTranslation(0.f, 0.01f, 0.f);  // 지형과 z-fighting 방지

    return Render_Mesh(m_pTransformCom->Get_World() * matShadow * matOffset, m_pRS.Get(), m_pPS_Shadow);
}

HRESULT CPlayer::Render_Occluded()
{
    if (m_bEditorMode)
        return S_OK;
    return Render_Mesh(m_pTransformCom->Get_World(), m_pRS.Get(), m_pPS_Occluded);
}

HRESULT CPlayer::Ready_Components()
{
    if(FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), Normalize_AssetPath(TEXT("Characters/0_CharacterModel_Boss_Wu/0_CharacterModel_Boss_Wu.fbx")),
        TEXT("Com_Model"),m_pModel)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), Proto::VS_MODEL,
        TEXT("Com_VS"), m_pVS)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), Proto::PS_MODEL,
        TEXT("Com_PS"), m_pPS)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), Proto::PS_VTXCOL_SHADOW,
        TEXT("Com_PS_SHADOW"), m_pPS_Shadow)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), Proto::PS_VTXCOL_OCCLUDED,
        TEXT("Com_PS_OCCLUDED"), m_pPS_Occluded)))
        return E_FAIL;

    return S_OK;
}

HRESULT CPlayer::Ready_ConstantBuffer()
{
    m_pCB = CConstantBuffer::Create(m_pDevice, m_pContext, &m_tCBData, sizeof m_tCBData);
    if (nullptr == m_pCB)
        return E_FAIL;

    return S_OK;
}

HRESULT CPlayer::Update_ConstantBuffer(const matrix_t& matWorld)
{
    XMMATRIX matNoTrans = matWorld;
    matNoTrans.r[3] = XMVectorSet(0.f, 0.f, 0.f, 1.f);
    XMMATRIX matWorldInvTranspos = XMMatrixTranspose(XMMatrixInverse(nullptr, matNoTrans));

    XMStoreFloat4x4(&m_tCBData.mat_World, (matWorld));
    XMStoreFloat4x4(&m_tCBData.mat_WorldInvTranspose, (matWorldInvTranspos));

    return S_OK;
}


HRESULT CPlayer::Render_Mesh(const matrix_t& matWorld, ID3D11RasterizerState* pRS, shared_ptr<CPixelShader> pPS)
{
    if (FAILED(__super::Render()))
        return E_FAIL;

    // RS(레스터라이저 설정)
    m_pContext->RSSetState(pRS);

    if (FAILED(Bind_Shader(m_pVS, pPS)))
        return E_FAIL;

    if (FAILED(Bind_ShaderResources(matWorld)))
        return E_FAIL;
    uint32_t    iNumMeshes = m_pModel->Get_NumMeshes();
    for (uint32_t i = 0; i < iNumMeshes; ++i)
    {
        if (FAILED(m_pModel->Bind_Material(i, aiTextureType_DIFFUSE, 0, 0)))
            return E_FAIL;

        //if (FAILED(m_pModelCom->Bind_Material(i, aiTextureType_NORMALS, 0, 1)))
        //    return E_FAIL;

        if (FAILED(m_pModel->Render(i)))
            return E_FAIL;
    }
    return S_OK;
}

HRESULT CPlayer::Bind_Shader(shared_ptr<CVertexShader> pVS, shared_ptr<CPixelShader> pPS)
{
    if (FAILED(pVS->Begin()))
        return E_FAIL;

    if (FAILED(pPS->Begin()))
        return E_FAIL;
    return S_OK;
}

HRESULT CPlayer::Bind_ShaderResources(const matrix_t& matWorld)
{
    if (FAILED(Update_ConstantBuffer(matWorld)))
        return E_FAIL;
    if (FAILED(m_pCB->Bind_Vertex_ShaderResource(0, &m_tCBData)))
        return E_FAIL;
    return S_OK;
}

void CPlayer::AdjustPosY()
{
    if (m_bEditorMode)
        return;
    auto pHill = static_pointer_cast<CHill>(CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::GAMEPLAY), L"Layer_GameObject", TEXT("GameObject_Hill")));
    
    vector_t  vPos = m_pTransformCom->Get_State(STATE::POSITION);
    f32_t x = XMVectorGetX(vPos);
    f32_t z = XMVectorGetZ(vPos);
    vPos = XMVectorSetY(vPos, pHill->GetHeight(x, z) + 0.1f);
    m_pTransformCom->Set_State(STATE::POSITION, vPos);
    m_vGroundPlane = pHill->GetPlane(x, z);
}
void CPlayer::KeyInput(f32_t fDeltaTime)
{
    bool_t  bPushShift = false;
    if (CGameInstance::Get().Key_Pressing(DIK_LSHIFT))
    {
        m_pTransformCom->Set_Speed(16.f);
        bPushShift = true;
    }
    else
    {
        m_bAiming = CGameInstance::Get().Mouse_Pressing(DIM::RB);
        m_bFiring = CGameInstance::Get().Mouse_Pressing(DIM::LB);
        LookAtMouse(fDeltaTime);
        m_pTransformCom->Set_Speed(8.f);
    }

    auto pInven = m_pInven.lock();
    if (pInven)
    {
        if (CGameInstance::Get().Key_Down(DIK_1)) 
            pInven->Set_ActiveSlot(EQUIP_SLOT::GUN_1);
        if (CGameInstance::Get().Key_Down(DIK_2)) 
            pInven->Set_ActiveSlot(EQUIP_SLOT::GUN_2);
        if (CGameInstance::Get().Key_Down(DIK_V))
            pInven->Set_ActiveSlot(EQUIP_SLOT::MELEE);
    }
    
    vector_t vLook = m_pTransformCom->Get_State(STATE::LOOK);

    f32_t fInputX = 0.f, fInputZ = 0.f;
    if (CGameInstance::Get().Key_Pressing(DIK_W)) fInputZ += 1.f;
    if (CGameInstance::Get().Key_Pressing(DIK_S)) fInputZ -= 1.f;
    if (CGameInstance::Get().Key_Pressing(DIK_A)) fInputX -= 1.f;
    if (CGameInstance::Get().Key_Pressing(DIK_D)) fInputX += 1.f;
    if (0.f == fInputX && 0.f == fInputZ)
        return;

    matrix_t matCamWorld = CGameInstance::Get().Get_Perspective_Transform_Inverse(D3DTS::VIEW);
    vector_t vCamRight = XMVector3Normalize(XMVectorSetY(matCamWorld.r[0], 0.f));
    vector_t vCamLook = XMVector3Normalize(XMVectorSetY(matCamWorld.r[2], 0.f));

    vector_t vMoveDir = XMVector3Normalize(vCamRight * fInputX + vCamLook * fInputZ);
    m_pTransformCom->Move_Position(vMoveDir, fDeltaTime);

    if (!bPushShift)
        return;

    vLook = XMVector3Normalize(XMVectorSetY(vLook, 0.f));
    f32_t fDot = XMVectorGetX(XMVector3Dot(vLook, vMoveDir));
    if (fDot < cosf(XMConvertToRadians(2.f)))
    {
        f32_t fCrossY = XMVectorGetY(XMVector3Cross(vLook, vMoveDir));
        m_pTransformCom->Turn(fCrossY > 0.f ? g_vY_Plus : g_vY_Minus, fDeltaTime);
    }
}
void CPlayer::LookAtMouse(f32_t fDeltaTime)
{
    auto pMouse = CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::GAMEPLAY), L"Layer_GameObject", GO::Client_Mouse);
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
