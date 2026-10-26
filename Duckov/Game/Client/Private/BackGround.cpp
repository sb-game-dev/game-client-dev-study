#include "BackGround.h"

CBackGround::CBackGround(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	:CGameObject{pDevice,pContext}
{
}

HRESULT CBackGround::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
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

HRESULT CBackGround::Initialize(void* pArg)
{
    CBackGround::BACKGROUND_DESC        BackGroundDesc{};
	if (FAILED(__super::Initialize(&BackGroundDesc)))
		return E_FAIL;

    m_pTransformCom->Set_State(STATE::POSITION, vector_t{ 0.f,0.f,1.f,1.f });
    m_pTransformCom->Set_Scale( g_iWinSizeX, g_iWinSizeY, 1.f );

    if (FAILED(Ready_Components()))
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
    XMMATRIX matWorld = m_pTransformCom->Get_World();

    // 역전치 행렬은 이동 성분을 뺀 복사본으로 계산 (matWorld 자체는 이동 성분 유지)
    XMMATRIX matNoTrans = matWorld;
    matNoTrans.r[3] = XMVectorSet(0.f, 0.f, 0.f, 1.f);
    XMMATRIX matWorldInvTranspos = XMMatrixTranspose(XMMatrixInverse(nullptr, matNoTrans));

    CB_PER_OBJECT_LIT cbData;
    XMStoreFloat4x4(&cbData.mat_World, matWorld);
    XMStoreFloat4x4(&cbData.mat_WorldInvTranspose, matWorldInvTranspos);
    cbData.tMaterial = m_tMaterial;

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
    m_pContext->PSSetShader(m_pPS->Get_Shader().Get(), nullptr, 0);

    m_pContext->PSSetConstantBuffers(0, //register(b0)과 연결됨
        1,
        m_pCB.GetAddressOf());

    // 텍스처 바인드
    m_pTextureCom->Set_TexturePS(0, 0);

    // 샘플러 바인드
    m_pContext->PSSetSamplers(0, 1, m_pSampler.GetAddressOf());

    // RS(레스터라이저 설정)
    m_pContext->RSSetState(m_pRS.Get());
    
    m_pBufferCom->Render();

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

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::LOADING), Proto::VS_VTXTEX,
        TEXT("Com_VS"), m_pVS)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(ETOUI(LEVEL::LOADING), Proto::PS_VTXTEX_NOLIGHT,
        TEXT("Com_PS"), m_pPS)))
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