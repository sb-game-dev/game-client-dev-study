#include "Renderer.h"
#include "GameObject.h"
#include "GameInstance.h"
CRenderer::CRenderer(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	: m_pDevice{pDevice}
	, m_pContext{pContext}
{
}



HRESULT CRenderer::Initialize(uint32_t iWinSizeX, uint32_t iWinSizeY)
{

	if (FAILED(Ready_SceneTarget(iWinSizeX,iWinSizeY)))
		return E_FAIL;
	return S_OK;
}

void CRenderer::Add_RenderGroup(RENDERID eRenderID, shared_ptr<CGameObject> pGameObject)
{
	if (eRenderID >= RENDERID::END || nullptr == pGameObject)
		return;

	m_RenderGroup[ETOUI(eRenderID)].push_back(pGameObject);
}

void CRenderer::Render_GameObject()
{
	ComPtr<ID3D11RenderTargetView>	pOldRTV;
	ComPtr<ID3D11DepthStencilView>	pOldDSV;
	m_pContext->OMGetRenderTargets(1, pOldRTV.GetAddressOf(), pOldDSV.GetAddressOf());

	float clearColor[4] = { 0.016f, 0.016f, 0.129f, 1.f };
	m_pContext->OMSetRenderTargets(1, m_pSceneRTV.GetAddressOf(), pOldDSV.Get());
	m_pContext->ClearRenderTargetView(m_pSceneRTV.Get(), clearColor);


	Render_Priority();
	Render_NonAlpha();
	Render_OccludedPlayer();
	Render_Player();
	Render_Shadow();
	Render_Mirror();
	Render_Alpha();

	m_pContext->OMSetRenderTargets(1, pOldRTV.GetAddressOf(), pOldDSV.Get());

	m_pBlurFilter->BlurInPlace(m_pSceneSRV.Get(), m_pSceneUAV.Get(), 10);

	if(m_bDrawToBackBuffer)
		Render_FullScreen();
	Render_NonAlpha_UI();
	Render_Alpha_UI();

 }

void CRenderer::AddBlurField(f32_t fLeft, f32_t fTop, f32_t fWidth, f32_t fHeight)
{
	m_pBlurFilter->AddBlurField(fLeft, fTop, fWidth, fHeight);
}

HRESULT CRenderer::Ready_SceneTarget(uint32_t iWinSizeX, uint32_t iWinSizeY)
{
	D3D11_TEXTURE2D_DESC desc{};
	desc.Width = iWinSizeX;
	desc.Height = iWinSizeY;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;

	ComPtr<ID3D11Texture2D> pTex;
	m_pDevice->CreateTexture2D(&desc, nullptr, &pTex);
	m_pDevice->CreateRenderTargetView(pTex.Get(), nullptr, &m_pSceneRTV);
	m_pDevice->CreateShaderResourceView(pTex.Get(), nullptr, &m_pSceneSRV);
	m_pDevice->CreateUnorderedAccessView(pTex.Get(), nullptr, &m_pSceneUAV);

	D3D11_DEPTH_STENCIL_DESC noDepth{};

	noDepth.DepthEnable = FALSE;

	ComPtr<ID3DBlob> pVSBlob, pPSBlob, pErrBlob;

	uint32_t iFlags = 0;
#ifdef _DEBUG
	iFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif
	//VS 컴파일
	if (FAILED(D3DCompileFromFile(L"../Bin/Shader/Shader_Blur.hlsl", nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, 
		"VS_FullScreen", "vs_5_0", iFlags, 0, &pVSBlob, &pErrBlob)))                       
	{
		if (pErrBlob) OutputDebugStringA((char*)pErrBlob->GetBufferPointer());
		return E_FAIL;
	}
	// PS 컴파일
	if (FAILED(D3DCompileFromFile(L"../Bin/Shader/Shader_Blur.hlsl", nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"PS_FullScreen", "ps_5_0", iFlags, 0, &pPSBlob, &pErrBlob)))
	{
		if (pErrBlob) OutputDebugStringA((char*)pErrBlob->GetBufferPointer());
		return E_FAIL;
	}
	// 버텍스 셰이더 객체 생성
	if (FAILED(m_pDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &m_pVS_FullScreen)))
		return E_FAIL;

	// 픽셀 셰이더 객체 생성
	if (FAILED(m_pDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &m_pPS_FullScreen)))
		return E_FAIL;

	// 블러필터 객체 생성
	m_pBlurFilter = CBlurFilter::Create(m_pDevice, m_pContext, iWinSizeX, iWinSizeY);
	if (nullptr == m_pBlurFilter)
		return E_FAIL;

	return S_OK;
}

void CRenderer::Render_Priority()
{
	for (auto& pObj : m_RenderGroup[ETOUI(RENDERID::PRIORITY)])
	{
		if (nullptr != pObj)
			pObj->Render();
	}
	m_RenderGroup[ETOUI(RENDERID::PRIORITY)].clear();
}

void CRenderer::Render_NonAlpha()
{
	CGameInstance::Get().Bind_DepthStencilState(g_strDSS_SilhouetteMark, 10);

	for (auto& pObj : m_RenderGroup[ETOUI(RENDERID::NONALPHA)])
	{
		if (nullptr != pObj)
			pObj->Render();
	}
	m_RenderGroup[ETOUI(RENDERID::NONALPHA)].clear();

	CGameInstance::Get().Bind_DepthStencilState(g_strDSS_Default);
}

void CRenderer::Render_OccludedPlayer()
{
	CGameInstance::Get().Bind_BlendState(g_strBS_AlphaBlend);
	CGameInstance::Get().Bind_DepthStencilState(g_strDSS_MirrorReflect, 10);

	for (auto& pObj : m_RenderGroup[ETOUI(RENDERID::OCCLUDEDPLAYER)])
	{
		if (nullptr != pObj)
			pObj->Render_Occluded();
	}
	m_RenderGroup[ETOUI(RENDERID::OCCLUDEDPLAYER)].clear();


	CGameInstance::Get().Bind_BlendState(g_strBS_Default);
	CGameInstance::Get().Bind_DepthStencilState(g_strDSS_Default);
}

void CRenderer::Render_Player()
{
	for (auto& pObj : m_RenderGroup[ETOUI(RENDERID::PLAYER)])
	{
		if (nullptr != pObj)
			pObj->Render();
	}
	m_RenderGroup[ETOUI(RENDERID::PLAYER)].clear();
}

void CRenderer::Render_Mirror()
{
	auto pMirror = m_pMirror.lock();
	if (nullptr == pMirror)
	{
		m_RenderGroup[ETOUI(RENDERID::REFLECT)].clear();
		return;
	}
	float blendrFactor[4] = { 0.f,0.f,0.f,0.f };

	// 스텐실버퍼에 거울 영역 채우기 (스텐실 1로 표시하기만 함. 거울이 그려지지는 않음)
	CGameInstance::Get().Bind_BlendState(g_strBS_NoColor);
	CGameInstance::Get().Bind_DepthStencilState(g_strDSS_MirrorMark, 2);

	pMirror->Render();																// 거울 영역 스텐실 버퍼에 1채우기

	// 블랜드 스테이트 초기화
	m_pContext->OMSetBlendState(nullptr, blendrFactor, 0xffffffff);

	XMMATRIX matReflect = XMMatrixReflect(pMirror->Get_MirrorPlane());
	CGameInstance::Get().Bind_DepthStencilState(g_strDSS_MirrorReflect, 2);

	for (auto& pObj : m_RenderGroup[ETOUI(RENDERID::REFLECT)])
	{
		if (nullptr != pObj)
			pObj->Render_Reflection(matReflect);
	}
	m_RenderGroup[ETOUI(RENDERID::REFLECT)].clear();

	CGameInstance::Get().Bind_BlendState(g_strBS_Default);
	CGameInstance::Get().Bind_DepthStencilState(g_strDSS_Default);
}

void CRenderer::Render_Shadow()
{
	CGameInstance::Get().Bind_BlendState(g_strBS_AlphaBlend);
	CGameInstance::Get().Bind_DepthStencilState(g_strDSS_NoDoubleBlend, 10);

	for (auto& pObj : m_RenderGroup[ETOUI(RENDERID::SHADOW)])
	{
		if (nullptr != pObj)
			pObj->Render_Shadow();
	}
	m_RenderGroup[ETOUI(RENDERID::SHADOW)].clear();

	CGameInstance::Get().Bind_BlendState(g_strBS_Default);
	CGameInstance::Get().Bind_DepthStencilState(g_strDSS_Default);
}
void CRenderer::Render_Alpha()
{
	CGameInstance::Get().Bind_BlendState(g_strBS_AlphaBlend);
	CGameInstance::Get().Bind_DepthStencilState(g_strDSS_Alpha);
	for (auto& pObj : m_RenderGroup[ETOUI(RENDERID::ALPHA)])
	{
		pObj->Compute_ViewZ();
	}
	m_RenderGroup[ETOUI(RENDERID::ALPHA)].sort([](shared_ptr<CGameObject> pDst, shared_ptr<CGameObject> pSrc)->bool
		{
			return pDst->Get_ViewZ() > pSrc->Get_ViewZ();
		});
	// 그리기
	for (auto& pObj : m_RenderGroup[ETOUI(RENDERID::ALPHA)])
	{
		if (nullptr != pObj)
			pObj->Render();
	}
	m_RenderGroup[ETOUI(RENDERID::ALPHA)].clear();

	// 복구
	CGameInstance::Get().Bind_BlendState(g_strBS_Default);
	CGameInstance::Get().Bind_DepthStencilState(g_strDSS_Default);
}

void CRenderer::Render_FullScreen()
{
	CGameInstance::Get().Bind_DepthStencilState(g_strDSS_NonZ);
	m_pContext->IASetInputLayout(nullptr);
	m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_pContext->VSSetShader(m_pVS_FullScreen.Get(), nullptr, 0);
	m_pContext->PSSetShader(m_pPS_FullScreen.Get(), nullptr, 0);
	m_pContext->PSSetShaderResources(0, 1, m_pSceneSRV.GetAddressOf());
	m_pContext->Draw(3, 0);

	ID3D11ShaderResourceView* pNullSRV[1] = {nullptr};
	m_pContext->PSSetShaderResources(0, 1, pNullSRV);					// RTV와 같은 텍스처를 가리키기 때문에 SRV 해제																		
	m_pContext->OMSetDepthStencilState(nullptr, 0);						// UI를 그릴때는 깊이 쓰기를 켜야 하므로 초기화 해야 한다.
}

void CRenderer::Render_NonAlpha_UI()
{
	for (auto& pObj : m_RenderGroup[ETOUI(RENDERID::NONALPHA_UI)])
	{
		if (nullptr != pObj)
			pObj->Render();
	}
	m_RenderGroup[ETOUI(RENDERID::NONALPHA_UI)].clear();
}

void CRenderer::Render_Alpha_UI()
{
	CGameInstance::Get().Bind_BlendState(g_strBS_AlphaBlend);
	CGameInstance::Get().Bind_DepthStencilState(g_strDSS_Alpha);

	m_RenderGroup[ETOUI(RENDERID::ALPHA_UI)].sort([](shared_ptr<CGameObject> pDst, shared_ptr<CGameObject> pSrc)->bool
		{
			f32_t fDstZ = XMVectorGetZ(pDst->Get_Transform()->Get_State(STATE::POSITION));
			f32_t fSrcZ = XMVectorGetZ(pSrc->Get_Transform()->Get_State(STATE::POSITION));
			return fDstZ > fSrcZ;
		});
	// 그리기

	for (auto& pObj : m_RenderGroup[ETOUI(RENDERID::ALPHA_UI)])
	{
		if (nullptr != pObj)
			pObj->Render();
	}
	m_RenderGroup[ETOUI(RENDERID::ALPHA_UI)].clear();

	// 복구
	CGameInstance::Get().Bind_BlendState(g_strBS_Default);
	CGameInstance::Get().Bind_DepthStencilState(g_strDSS_Default);
}


unique_ptr<CRenderer> CRenderer::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, uint32_t iWinSizeX, uint32_t iWinsizeY)
{
	auto pInstance = unique_ptr<CRenderer>(new CRenderer(pDevice, pContext));
	if (FAILED(pInstance->Initialize(iWinSizeX, iWinsizeY)))
		pInstance.reset();
	return pInstance;
}
