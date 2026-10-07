#include "Renderer.h"
#include "GameObject.h"
#include "GameInstance.h"
CRenderer::CRenderer(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	: m_pDevice{pDevice}
	, m_pContext{pContext}
{
}

HRESULT CRenderer::Initialize()
{
	// 블렌더 스테이트 생성
	D3D11_BLEND_DESC blendDesc{};
	blendDesc.AlphaToCoverageEnable = FALSE;      // 픽셀 알파를 MSAA 샘플 커버리지로 변환 (MSAA 사용 시에만 효과, 수업에서는 안 씀)
	blendDesc.IndependentBlendEnable = FALSE;     // FALSE: 모든 렌더타겟에 RenderTarget[0] 설정 공통 적용 
												  // TRUE: 렌더타겟별 개별 설정

	blendDesc.RenderTarget[0].BlendEnable = TRUE;                       // 블렌더 활성화
	// RGB 블렌드 설정 -> 렌더 타겟에 기록할 최종 RGB 계산
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;         // RGB Src블렌드 계수 : Src.a
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;    // RGB Dst블렌드 계수 : 1- Src.a
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;             // RGB 블렌드 연산

	// 알파 블렌드 설정 -> 렌더 타겟의 A 채널에 기록할 최종 알파값 계산
	// 최종A = Src.a * 1 + Dst.a * 0 = Src.a (기존 알파를 버리고 Src 알파로 덮어씀)
	// 백버퍼에서는 A가 화면에 표시되지 않아 영향 없음, 오프스크린 렌더타겟을 텍스처로 다시 쓸 때 그 텍스처의 알파가 됨
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;          // 알파 Src블렌드 계수 : Src 알파 * 1
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;        // 알파 Dst블렌드 계수 : Dst 알파 * 0
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;        // 알파 블랜드 연산
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL; // 렌더타겟에 기록할 채널 (RGBA 전부)

	if (FAILED(m_pDevice->CreateBlendState(&blendDesc, m_pBS.GetAddressOf())))
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
	CGameInstance::Get().Set_MainCamera(L"QuarterViewCam");
	Render_Priority();
	Render_NonAlpha();
	Render_Alpha();

	CGameInstance::Get().Set_MainCamera(L"COrthographic_Cam");
	Render_NonAlpha_UI();
	Render_Alpha_UI();

	Clear_RenderGroup();
 }

void CRenderer::Clear_RenderGroup()
{
	for (uint32_t i = 0; i < ETOUI(RENDERID::END); ++i)
		m_RenderGroup[i].clear();
}

void CRenderer::Render_Priority()
{
	for (auto& pObj : m_RenderGroup[ETOUI(RENDERID::PRIORITY)])
		pObj->Render();
}

void CRenderer::Render_NonAlpha()
{
	for (auto& pObj : m_RenderGroup[ETOUI(RENDERID::NONALPHA)])
		pObj->Render();
}

void CRenderer::Render_Alpha()
{
	// 알파블렌더 설정

	// 상수 블렌드 계수 -> 텍스처 알파와 상관없이 오브젝트를 일정 비율로 반투명하게 만들고 싶을 때 사용
	// 예시) 
	// blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_BLEND_FACTOR;         
	// blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_BLEND_FACTOR;       
	// bledFactor[4] = {0.3f, 0.3f,0.3f,0.3f};
	// 
	// => 최종 RGB -> Src.RGB * 0.3f + Dst.RGB * 0.7fs
	float blendFactor[4] = { 0.f, 0.f, 0.f, 0.f };
	
	// 블렌딩 ON
	m_pContext->OMSetBlendState(m_pBS.Get(),	// 블렌더 스테이트 객체의 포인터
								blendFactor,	// 부동소수점 값 네 개의 배열을 가리키는 포인터
								0xffffffff);	// SampleMask (0xffffffff -> 모든 샘플을 활성화)
	// 그리기
	for (auto& pObj : m_RenderGroup[ETOUI(RENDERID::ALPHA)])
		pObj->Render();

	// 복구
	m_pContext->OMSetBlendState(nullptr, blendFactor, 0xffffffff);
}

void CRenderer::Render_NonAlpha_UI()
{
	for (auto& pObj : m_RenderGroup[ETOUI(RENDERID::NONALPHA_UI)])
		pObj->Render();
}

void CRenderer::Render_Alpha_UI()
{
	for (auto& pObj : m_RenderGroup[ETOUI(RENDERID::ALPHA_UI)])
		pObj->Render();
}

unique_ptr<CRenderer> CRenderer::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
	auto pInstance = unique_ptr<CRenderer>(new CRenderer(pDevice, pContext));
	if (FAILED(pInstance->Initialize()))
		pInstance.reset();
	return pInstance;
}
