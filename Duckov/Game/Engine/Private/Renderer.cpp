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
	if (FAILED(Ready_BlendState()))
		return E_FAIL;
	if (FAILED(Ready_BlendState_NoColor()))
		return E_FAIL;
	if (FAILED(Ready_Mirror_DSS()))
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

	Render_Mirror();

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

void CRenderer::Render_Mirror()
{
	if (nullptr == m_pMirror)        
		return;
	float blendrFactor[4] = { 0.f,0.f,0.f,0.f };

	// 스텐실버퍼에 거울 영역 채우기 (스텐실 1로 표시하기만 함. 거울이 그려지지는 않음)
	m_pContext->OMSetBlendState(m_pBS_NoColorWrite.Get(), blendrFactor, 0xffffffff);	// 색 없이 그리기
	m_pContext->OMSetDepthStencilState(m_pDSS_MarkMirror.Get(), 1);						// 쓰기만 하는 상태: 스텐실버퍼에 1값 쓰기
	
	m_pMirror->Render();																// 거울 영역 스텐실 버퍼에 1채우기

	// 블랜드 스테이트 초기화
	m_pContext->OMSetBlendState(nullptr, blendrFactor, 0xffffffff);

	XMMATRIX matReflect = XMMatrixReflect(m_pMirror->Get_MirrorPlane());
	m_pContext->OMSetDepthStencilState(m_pDSS_DrawReflection.Get(), 1);					// 읽기만 하는 상태: 스텐실버퍼가 1인지 검사만 함

	for (auto& pObj : m_ReflectObjects)
		pObj->Render_Reflection(matReflect);

	m_pContext->OMSetDepthStencilState(nullptr, 0);										// 기본 상태(스텐실 : off)
}

HRESULT CRenderer::Ready_BlendState()
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

HRESULT CRenderer::Ready_BlendState_NoColor()
{
	D3D11_BLEND_DESC noColorDesc{};
	noColorDesc.RenderTarget[0].RenderTargetWriteMask = 0;   // RGBA 아무 채널도 안 씀
	if (FAILED(m_pDevice->CreateBlendState(&noColorDesc, m_pBS_NoColorWrite.GetAddressOf())))
		return E_FAIL;
	return S_OK;
}
// 거울 렌더링에 쓰는 DSS 두 개 생성
// m_pDSS_MarkMirror     : 거울이 보이는 픽셀의 스텐실을 1로 표시 (쓰기)
// m_pDSS_DrawReflection : 스텐실이 1인 픽셀에만 반사 오브젝트 출력 (읽기 전용)
HRESULT CRenderer::Ready_Mirror_DSS()
{
	// ===== 1. 마킹용 =====
	D3D11_DEPTH_STENCIL_DESC markDesc{};

	// 깊이 테스트 수행 여부 -> 거울 앞을 가린 물체가 있으면 그 픽셀은 표시하지 않기 위해 켬
	// 깊이 버퍼에 대해 할 수 있는 일은 읽기(검사)와 쓰기(기록) 두 가지 이다
	
	// 검사 -> DepthEnable / DepthFunc -> 내 깊이를 버퍼에 적힌 값과 비교해서, 더 뒤에 있으면 탈락

	markDesc.DepthEnable = TRUE;
	// 깊이 테스트를 통과하면 깊이를 기록할지
	// ALL : 기록함. 일반 불투명 물체의 기본값
	// ZERO: 기록 안 함. 가려지면 탈락하지만, 다른 물체를 가리지 않음 
	//       -> 나는 남한테 가려질 수 있지만, 내가 남을 가리지 않겠다.
	
	// 거울 판의 깊이를 기록하면 버퍼에 'z=5에 뭔가 있다'가 남아서
	// 거울 뒤에 그려질 반사 오브젝트가 깊이 테스트에서 가려짐
	// -> 거울은 스텐실 표시만 하면 되므로 검사만 하고 자기 깊이는 남기지 않음
	markDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO; 

	// 깊이 비교 방법 (LESS : 더 가까운 픽셀이 테스트 통과)
	markDesc.DepthFunc = D3D11_COMPARISON_LESS;


	// 스텐실 테스트 수행 여부
	markDesc.StencilEnable = TRUE;
	// 비교 전에 Ref와 버퍼값에 AND할 마스크 (0xff = 8비트 전부 비교)
	// 마킹은 ALWAYS라 실제로는 쓰이지 않음
	markDesc.StencilReadMask = 0xff;

	// 앞면 삼각형에 적용할 규칙 (Func 1개 + 결과별 Op 3개)
	// Op 종류
	// KEEP             : 유지
	// REPLACE          : StencilRef로 교체
	// ZERO             : 0으로 교체
	// INCR_SAT/DECR_SAT: 1 증가/감소 (최대·최소에서 멈춤)
	// INCR/DECR        : 1 증가/감소 (넘치면 한 바퀴 돎
	
	// Ref와 버퍼값을 비교하는 방법 -> 무조건 통과시킴(마킹 단계에서는 버퍼값과 상관없이 통과해야 함)
	markDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// 스텐실 테스트 실패시 할 일 -> 기존값 유지
	// ALWAYS라 사실상 실패할 일 없음, 다만 거울속 세상에서 사용하기 때문에 미리 선언
	markDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	// 깊이 테스트 실패시 할 일 -> 기존 값 유지
	// ALWAYS라 사실상 실패할 일 없음, 다만 거울속 세상에서 사용하기 때문에 미리 선언
	markDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
	// 스텐실-깊이 테스트를 둘 다 통과 시 할 일 -> Ref 값으로 교체(Ref 값으로 1 설정함)
	markDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_REPLACE;

	// Op가 값을 쓸 때 실제로 바꿀 비트 (0xff = 8비트 전부 -> Op 결과가 그대로 기록됨)
	markDesc.StencilWriteMask = 0xff;
	

	// 뒷면 삼각형 규칙 -> 앞면과 동일
	// (거울은 CULL_BACK이라 뒷면이 래스터화되지 않지만 안전하게 맞춰 둠)
	markDesc.BackFace = markDesc.FrontFace;

	if (FAILED(m_pDevice->CreateDepthStencilState(&markDesc, m_pDSS_MarkMirror.GetAddressOf())))
		return E_FAIL;

	// ===== 2. 거울속 세상 출력용 (스텐실이 1인지 검사만 하고 값은 바꾸지 않음) =====
	D3D11_DEPTH_STENCIL_DESC reflectDesc = markDesc;
	// 깊이 테스트 끔 -> 복제본은 거울 뒤(더 먼 곳)에 있어서
	// 켜 두면 거울 뒤 지형 깊이에 가려짐. 끄면 깊이 쓰기도 같이 꺼짐
	reflectDesc.DepthEnable = FALSE;

	// Ref == 버퍼값 인 픽셀만 통과 -> 마킹된(1) 거울 영역에만 그려짐
	// Ref = OMSetDepthStencilState(m_pDSS_DrawReflection, 1)의 두 번째 인자 1
	reflectDesc.FrontFace.StencilFunc = D3D11_COMPARISON_EQUAL;

	// 거울 속 세상을 출력하기 위한 스텐실 테스트는 읽기용이므로 통과해도 값 유지
	// 사실 위에서 선언한 FailOp, DepthFailOp이 KEEP이라 버퍼를 절대 바꾸지 않음
	reflectDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;

	// 뒷면도 동일 (반사 오브젝트는 m_pRS_Reflect로 감기 방향을 뒤집어 그림)
	reflectDesc.BackFace = reflectDesc.FrontFace;
	if (FAILED(m_pDevice->CreateDepthStencilState(&reflectDesc, m_pDSS_DrawReflection.GetAddressOf())))
		return E_FAIL;

	return S_OK;
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
