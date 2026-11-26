#include "Cube.h"
#include "Hill.h"
#include "Collider.h"
#include "Bullet.h"
#include "UI_HpBar.h"
#include "Weapon.h"

CCube::CCube(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	:CContainerObject(pDevice,pContext)
{
}

HRESULT CCube::Initialize_Prototype()
{
    if (FAILED(__super::Initialize_Prototype()))
        return E_FAIL;
	return S_OK;
}

HRESULT CCube::Initialize(void* pArg)
{
    if(FAILED(__super::Initialize(pArg)))
        return E_FAIL;

    if (FAILED(Ready_Components()))
        return E_FAIL;

    if (FAILED(Ready_ConstantBuffer()))
        return E_FAIL;

    if (FAILED(Ready_PartObjects()))
        return E_FAIL;

    auto pHill = dynamic_pointer_cast<CHill>(CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::ZEROZONE), L"Layer_GameObject", TEXT("GameObject_Hill")));
    if (nullptr == pHill)
        return E_FAIL;


    vector_t  vPos = m_pTransformCom->Get_State(STATE::POSITION);
    m_pTransformCom->Set_Scale(2.f,2.f,2.f);
    f32_t x = XMVectorGetX(vPos);
    f32_t z = XMVectorGetZ(vPos);
    vPos = XMVectorSetY(vPos, pHill->GetHeight(x, z) + 0.5f);
    m_pTransformCom->Set_State(STATE::POSITION, vPos);
    m_vGroundPlane = pHill->GetPlane(x, z);

    return S_OK;
}

void CCube::Priority_Update(f32_t fDeltaTime)
{
    __super::Priority_Update(fDeltaTime);
}

void CCube::Update(f32_t fDeltaTime)
{
    __super::Update(fDeltaTime);

    m_fHitTimeRemaining = max(0.f, m_fHitTimeRemaining - fDeltaTime);

}
void CCube::Late_Update(f32_t fDeltaTime)
{
    __super::Late_Update(fDeltaTime);

    if(Is_InFrustum())
        CGameInstance::Get().Add_RenderGroup(RENDERID::NONALPHA, dynamic_pointer_cast<CGameObject>(shared_from_this()));
    if (m_bEditorMode)
        return;
    // 그림자 : 월드 공간 박스 + 단위 행렬
    BoundingBox tShadowBox;
    m_pBufferCom->GetBoundinBox().Transform(tShadowBox, Get_ShadowWorld());   // 그림자를 감싸는 월드 박스

    if (Is_BoxInFrustum(tShadowBox, XMMatrixIdentity()))
        CGameInstance::Get().Add_RenderGroup(RENDERID::SHADOW, dynamic_pointer_cast<CGameObject>(shared_from_this()));
}

HRESULT CCube::Render()
{
    if (FAILED(CGameInstance::Get().Bind_RasterizerState(g_strRS_Cull_None)))
        return E_FAIL;
    if (FAILED(Render_Mesh(m_pTransformCom->Get_World(), m_pPS)))
        return E_FAIL;
    if (FAILED(CGameInstance::Get().Bind_RasterizerState(g_strRS_Default)))
        return E_FAIL;
    return S_OK;
}

HRESULT CCube::Render_Shadow()
{
    return Render_Mesh(Get_ShadowWorld(), m_pPS_Shadow);
}

void CCube::TriggerEnter(shared_ptr<class CCollider> pOtherCollider)
{
    //if (dynamic_pointer_cast<CBullet>(pOtherCollider->Get_Owner().lock()))
    //    Set_Dead();
    //if (dynamic_pointer_cast<CWeapon>(pOtherCollider->Get_Owner().lock()))
    //    Set_Dead();
}

void CCube::Take_Damage(const DAMAGE_DESC& Desc)
{
    m_fHP -= Desc.fDamage;
    m_fHitTimeRemaining = m_fHitDuration;
    m_pHpBar->Initialize_HitAnimation();
    switch (Desc.iDamageType)
    {
    case ETOUI(DAMAGE_TYPE::BULLET):

        break;
    case ETOUI(DAMAGE_TYPE::MELEE):

        break;
    default:

        break;
    }
    if (m_fHP <= 0.f)
    {
        // 죽었을 때 나는 소리 + 이펙트
        Set_Dead(); // 추후 시체로 모델 변경 + 파밍 가능하도록
        return;
    }
}

HRESULT CCube::Ready_Components()
{
    if (FAILED(__super::Add_Component(m_iLevelIndex, m_strTexturePath,
        TEXT("Com_Texture"), m_pTextureCom)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::STATIC), m_strMeshPath,
        TEXT("Com_Buffer"), m_pBufferCom)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::STATIC), Proto::VS_CUBE,
        TEXT("Com_VS"), m_pVS)))
        return E_FAIL;
    if (FAILED(__super::Add_Component(ETOUI(LEVEL::STATIC), Proto::Cube_Collider, TEXT("Com_Cube_Collider"), m_pCube_Collider)))
        return E_FAIL;

    m_pCube_Collider->Set_Extents(m_pTransformCom->Get_Scaled());


    if (FAILED(__super::Add_Component(ETOUI(LEVEL::STATIC), Proto::PS_CUBE,
        TEXT("Com_PS"), m_pPS)))
        return E_FAIL;


    if (FAILED(__super::Add_Component(ETOUI(LEVEL::STATIC), Proto::PS_CUBE_SHADOW,
        TEXT("Com_PS_SHADOW"), m_pPS_Shadow)))
        return E_FAIL;

    return S_OK;
}

HRESULT CCube::Ready_PartObjects()
{
    CUI_HpBar::UIHPBAR_DESC    UI_HpBarDesc{};
    UI_HpBarDesc.pParentTransformCom = m_pTransformCom;
    if (FAILED(__super::Add_PartObject(ETOUI(LEVEL::STATIC), Proto::Obj_UI_HpBar,
        TEXT("Part_HpBar"), &UI_HpBarDesc)))
        return E_FAIL;
    m_pHpBar = static_pointer_cast<CUI_HpBar>(Find_PartObect(TEXT("Part_HpBar")));
    return S_OK;
}

HRESULT CCube::Ready_ConstantBuffer()
{
    m_pCB = CConstantBuffer::Create(m_pDevice, m_pContext, &m_tCBData, sizeof(m_tCBData));
    if (nullptr == m_pCB)
        return E_FAIL;
    m_pCBHitRatio = CConstantBuffer::Create(m_pDevice, m_pContext, &m_vHitRatio, sizeof(m_vHitRatio));
    if (nullptr == m_pCBHitRatio)
        return E_FAIL;
    return S_OK;
}

HRESULT CCube::Update_ConstantBuffer(const matrix_t& matWorld)
{
    XMMATRIX matNoTrans = matWorld;
    matNoTrans.r[3] = XMVectorSet(0.f, 0.f, 0.f, 1.f);
    XMMATRIX matWorldInvTranspos = XMMatrixTranspose(XMMatrixInverse(nullptr, matNoTrans));

    XMStoreFloat4x4(&m_tCBData.mat_World, (matWorld));
    XMStoreFloat4x4(&m_tCBData.mat_WorldInvTranspose, (matWorldInvTranspos));

    m_vHitRatio.x = m_fHitTimeRemaining / m_fHitDuration;
    m_vHitRatio.y = m_fHitTimeRemaining / m_fHitDuration;
    m_vHitRatio.z = m_fHitTimeRemaining / m_fHitDuration;
    m_vHitRatio.w = m_fHitTimeRemaining / m_fHitDuration;

    return S_OK;
}

HRESULT CCube::Bind_Shader(shared_ptr<CVertexShader> pVS, shared_ptr<CPixelShader> pPS)
{
    if (FAILED(pVS->Begin()))
        return E_FAIL;

    if (FAILED(pPS->Begin()))
        return E_FAIL;
    return S_OK;
}

HRESULT CCube::Bind_ShaderResources(const matrix_t& matWorld)
{
    if (FAILED(Update_ConstantBuffer(matWorld)))
        return E_FAIL;

    if (FAILED(m_pCB->Bind_Vertex_ShaderResource(0, &m_tCBData)))
        return E_FAIL;

    if (FAILED(m_pTextureCom->Bind_Pixel_ShaderResource(0, 0)))
        return E_FAIL;
    return S_OK;
}

HRESULT CCube::Render_Mesh(const XMMATRIX& matWorld, shared_ptr<CPixelShader> pPS)
{
    if (FAILED(__super::Render()))
        return E_FAIL;

    if (FAILED(Bind_ShaderResources(matWorld)))
        return E_FAIL;

    if (FAILED(m_pCBHitRatio->Bind_Pixel_ShaderResource(7, &m_vHitRatio)))
        return E_FAIL;
    if (FAILED(Bind_Shader(m_pVS, pPS)))
        return E_FAIL;

    if (FAILED(m_pBufferCom->Bind_Resources()))
        return E_FAIL;

    if (FAILED(m_pBufferCom->Render()))
        return E_FAIL;

    ID3D11Buffer* pNull = nullptr;
    m_pContext->PSSetConstantBuffers(7, 1, &pNull);
    return S_OK;
}

matrix_t CCube::Get_ShadowWorld()
{
    vector_t    vPlane = XMLoadFloat4(&m_vGroundPlane);
    vector_t    vToLight = vector_t{ -0.5f,0.5f,-0.5f,0.f };

    matrix_t    matShadow = XMMatrixShadow(vPlane, vToLight);
    matShadow = matShadow * (1.f / XMVectorGetW(matShadow.r[3]));
    matrix_t    matOffset = XMMatrixTranslation(0.f, 0.01f, 0.f);

    return m_pTransformCom->Get_World() * matShadow * matOffset;
}

shared_ptr<CCube> CCube::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
	auto pInstance = shared_ptr<CCube>(new CCube(pDevice, pContext));

    if (FAILED(pInstance->Initialize_Prototype()))
    {
        MSG_BOX("Failed to Created : CCube");
        pInstance.reset();
    }

    return pInstance;
}

shared_ptr<CPrototype> CCube::Clone(void* pArg)
{
    auto pInstance = shared_ptr<CCube>(new CCube(*this));
    if (FAILED(pInstance->Initialize(pArg)))
    {
        MSG_BOX("Failed to Cloned : CCube");
        pInstance.reset();
    }

    return pInstance;
}
