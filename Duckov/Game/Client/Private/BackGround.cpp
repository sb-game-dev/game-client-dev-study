#include "BackGround.h"

CBackGround::CBackGround(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	:CGameObject{pDevice,pContext}
{
}

HRESULT CBackGround::Initialize_Prototype()
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

HRESULT CBackGround::Initialize(void* pArg)
{
    CBackGround::BACKGROUND_DESC        BackGroundDesc{};
	if (FAILED(__super::Initialize(&BackGroundDesc)))
		return E_FAIL;

    m_pTransformCom->Set_State(STATE::POSITION, vector_t{ 0.f,0.f,1.f,1.f });
    m_pTransformCom->Set_Scale( g_iWinSizeX, g_iWinSizeY, 1.f );

    if (FAILED(Ready_Components()))
        return E_FAIL;
    if (FAILED(Ready_ConstantBuffer()))
        return E_FAIL;

    return S_OK;
}

void CBackGround::Priority_Update(f32_t fTimeDelta)
{
	__super::Priority_Update(fTimeDelta);
}

void CBackGround::Update(f32_t fTimeDelta)
{
	__super::Update(fTimeDelta);
}

void CBackGround::Late_Update(f32_t fTimeDelta)
{
	__super::Late_Update(fTimeDelta);
    CGameInstance::Get().Add_RenderGroup(RENDERID::NONALPHA_UI, dynamic_pointer_cast<CGameObject>(shared_from_this()));
}
HRESULT CBackGround::Render()
{
	if (FAILED(__super::Render()))
		return E_FAIL;

    // RS(레스터라이저 설정)
    m_pContext->RSSetState(m_pRS.Get());

    if (FAILED(Bind_Shader()))
        return S_OK;
    
    if (FAILED(Bind_ShaderResources()))
        return S_OK;

    if (FAILED(m_pBufferCom->Bind_Resources()))
        return E_FAIL;

    if (FAILED(m_pBufferCom->Render()))
        return E_FAIL;

    return S_OK;
}
HRESULT CBackGround::Ready_Components()
{
    if (FAILED(__super::Add_Component(ETOUI(LEVEL::LOADING), Proto::Texture_BackGround, 
        TEXT("Com_Texture"), m_pTextureCom)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::LOADING), Proto::VIBuffer_Rect, 
        TEXT("Com_Buffer"), m_pBufferCom)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::LOADING), Proto::VS_VTXTEX_UI,
        TEXT("Com_VS"), m_pVS)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::LOADING), Proto::PS_VTXTEX_NOLIGHT,
        TEXT("Com_PS"), m_pPS)))
        return E_FAIL;
    return S_OK;
}
HRESULT CBackGround::Ready_ConstantBuffer()
{
    XMMATRIX matWorld = m_pTransformCom->Get_World();

    // 역전치 행렬은 이동 성분을 뺀 복사본으로 계산 (matWorld 자체는 이동 성분 유지)
    XMMATRIX matNoTrans = matWorld;
    matNoTrans.r[3] = XMVectorSet(0.f, 0.f, 0.f, 1.f);
    XMMATRIX matWorldInvTranspos = XMMatrixTranspose(XMMatrixInverse(nullptr, matNoTrans));

    XMStoreFloat4x4(&m_tCBData.mat_World, matWorld);
    XMStoreFloat4x4(&m_tCBData.mat_WorldInvTranspose, matWorldInvTranspos);
    m_tCBData.tMaterial = m_tMaterial;

    m_pCB = CConstantBuffer::Create(m_pDevice, m_pContext, &m_tCBData, sizeof(m_tCBData));
    if (nullptr == m_pCB)
        return E_FAIL;
    return S_OK;
}
HRESULT CBackGround::Bind_Shader(shared_ptr<CVertexShader> pVS, shared_ptr<CPixelShader> pPS)
{
    if (FAILED(m_pVS->Begin()))
        return E_FAIL;

    if (FAILED(m_pPS->Begin()))
        return E_FAIL;
    return S_OK;
}
HRESULT CBackGround::Bind_ShaderResources()
{
    if (FAILED(m_pCB->Bind_Vertex_ShaderResource(0, &m_tCBData)))
        return E_FAIL;

    if (FAILED(m_pCB->Bind_Pixel_ShaderResource(0, &m_tCBData)))
        return E_FAIL;

    if (FAILED(m_pTextureCom->Bind_Pixel_ShaderResource(0, 0)))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Bind_Sampler_Pixel_Shader(g_strSampler_Linear, 0)))
        return E_FAIL;
    return S_OK;
}
shared_ptr<CBackGround> CBackGround::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
	auto pInstance = shared_ptr<CBackGround>(new CBackGround(pDevice, pContext));

	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Create Failed : CBackGround");
		pInstance.reset();
	}

	return pInstance;
}

shared_ptr<CPrototype> CBackGround::Clone(void* pArg)
{
	auto pInstance = shared_ptr<CBackGround>(new CBackGround(*this));
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Clone Failed : CBackGround");
		pInstance.reset();
	}
	return pInstance;
}