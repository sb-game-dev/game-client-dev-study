#include "..\public\Graphic_Device.h"

CGraphic_Device::CGraphic_Device()
	: m_pDevice{ nullptr }
	, m_pDeviceContext{ nullptr }
{	
	
}

CGraphic_Device::~CGraphic_Device()
{
	//#if defined(DEBUG) || defined(_DEBUG)
	//	ID3D11Debug* d3dDebug;
	//	HRESULT hr = m_pDevice->QueryInterface(__uuidof(ID3D11Debug), reinterpret_cast<void**>(&d3dDebug));
	//	if (SUCCEEDED(hr))
	//	{
	//		OutputDebugStringW(L"----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- \r ");
	//		OutputDebugStringW(L"                                                                    D3D11 Live Object ref Count Checker \r ");
	//		OutputDebugStringW(L"----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- \r ");
	//
	//		hr = d3dDebug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
	//
	//		OutputDebugStringW(L"----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- \r ");
	//		OutputDebugStringW(L"                                                                    D3D11 Live Object ref Count Checker END \r ");
	//		OutputDebugStringW(L"----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- \r ");
	//	}
	//	if (d3dDebug != nullptr)            d3dDebug->Release();
	//#endif
}

HRESULT CGraphic_Device::Initialize(HWND hWnd, WINMODE isWindowed, uint32_t iWinSizeX, uint32_t iWinSizeY, _Out_ ComPtr<ID3D11Device>& pDevice, _Out_ ComPtr<ID3D11DeviceContext>& pContext)
{
	uint32_t		iFlag = 0;

#ifdef _DEBUG
	iFlag = D3D11_CREATE_DEVICE_DEBUG;
#endif
	D3D_FEATURE_LEVEL			FeatureLV;

	/* dx9 : 장치 초기화를 하기위한 설정을 쭈욱 하고나서 최종적으로 장치객체를 생성한다. */
	/* dx11 : 우선적으로 장치 객체를 생성하고 장치객체를 통해서 기타 초기화작업 및 설정을 해나간다. */

	/* 그래픽 장치를 초기화한다. */



	if (FAILED(D3D11CreateDevice(nullptr,									// 디스플레이 어댑터
								 D3D_DRIVER_TYPE_HARDWARE,					// 드라이버 타입 : 
																			// D3D_DRIVER_TYPE_HARDWARE(3차원 그래픽 가속이 적용되게하는 구동기)
																			// D3D_DRIVER_TYPE_REFERENCE(표준 장치) 
																			// D3D_DRIVER_TYPE_SOFTWARE(3차원 하드웨어를 흉내 내는 소프트웨어 구동기)
								 0,											// 소프트웨어 구동기 지정하는 부분. 이 책에서는 D3D_DRIVER_TYPE_HARDWARE 를 사용하기 때문에 0 또는 nullptr로 지정
								 iFlag, 									// 추가적인 장치 생성 플래그
								 nullptr,									// pFeatureLevels 원소들의 순서가 곧 기능 수준을 점검하는 순서. 이 매개변수에 널 값을 지정하면 지원되는 최고 기능 수준이 선택됨
								 0, 										// 위 매개변수에 null을 저장했다면 이 매개변수는 0으로 지정하면 됨
								 D3D11_SDK_VERSION,							// 항상 D3D11_SDK_VERSION로 지정
								 m_pDevice.GetAddressOf(),					// 생성한 Deviec를 돌려준다
								 &FeatureLV,								// 지원되는 최고기능 수준을 돌려준다.
								 m_pDeviceContext.GetAddressOf()			// 생성된 장치 문맥을 돌려준다.
	)))
		return E_FAIL;

	/* SwapChain : 더블버퍼링. 전면과 후면버퍼를 번갈아가며 화면에 보여준다.(Present) */


	/* 스왑체인객체를 생성하였고 생성한 스왑체인 객체가 백버퍼를 내장한다. 백버퍼를 생성하기 위한 ID3D11Texture2D 만든거야. */
	/* 스왑체인 객체를 만들면서 백버퍼에 해당하는 ID3D11Texture2D객체를 만들어 스왑체인 객체가 내장한다. */
	if (FAILED(Ready_SwapChain(hWnd, isWindowed, iWinSizeX, iWinSizeY)))
		return E_FAIL;

	/* 스왑체인이 들고 있는 텍스쳐 2D를 가져와서 이를 바탕으로 백버퍼 렌더타겟 뷰를 만든다.*/
	if (FAILED(Ready_BackBufferRenderTargetView()))
		return E_FAIL;

	if (FAILED(Ready_DepthStencilView(iWinSizeX, iWinSizeY)))
		return E_FAIL;

	/* 장치에 바인드해놓을 렌더 타겟들과 뎁스스텐실뷰를 세팅한다. */
	/* 장치는 동시에 최대 4->8개의 렌더타겟을 들고 있을 수 있다. */
	ID3D11RenderTargetView*		pRTVs[] = {
		m_pBackBufferRTV.Get(),
	};

	
	/* 렌더타겟의 픽셀 수와 깊이스텐실버퍼의 픽셀수가 서로 다르다면 절대 렌더링이 불가능해진다. */
	m_pDeviceContext->OMSetRenderTargets(1,								// 렌더 대상의 개수 여기서는 하나
										 pRTVs,							// 렌더타겟 뷰들을 가리키는 포인터들을 담은 배열의 첫 원소를 가리키는 포인터
										 m_pDepthStencilView.Get());	// 파이프라인에 묶을 깊이-스텐실 뷰를 가리키는 포인터				
	
	// 뷰포트 구조체 설정
	D3D11_VIEWPORT			ViewPortDesc;
	ZeroMemory(&ViewPortDesc, sizeof(D3D11_VIEWPORT));
	ViewPortDesc.TopLeftX = 0;									// 왼쪽위 x좌표
	ViewPortDesc.TopLeftY = 0;									// 왼쪽위 y좌표
	ViewPortDesc.Width = static_cast<f32_t>(iWinSizeX);			// 너비
	ViewPortDesc.Height = static_cast<f32_t>(iWinSizeY);		// 높이
	ViewPortDesc.MinDepth = 0.f;								// 최소 깊이 버퍼값
	ViewPortDesc.MaxDepth = 1.f;								// 최대 깊이 버퍼값 (특수 효과를 원하는 것이 아닌한 0 ~ 1로 설정)

	// 뷰포트 초기화
	m_pDeviceContext->RSSetViewports(1, &ViewPortDesc);		

	// Device와 Context 내보내기
	pDevice = m_pDevice;
	pContext= m_pDeviceContext;	

	return S_OK;
}

HRESULT CGraphic_Device::Clear_BackBuffer_View(const float4_t* pClearColor)
{
	if (nullptr == m_pDeviceContext)
		return E_FAIL;

	/* DX9기준 : Clear함수는 백버퍼, 깊이스텐실버퍼를 한꺼번에 지운다.  */
	// m_pGraphic_Device->Clear(어떤 영역만큼 지울까, 어떤 것들을 지울까? , 뭘로 지울가. );	

	/* 백버퍼를 초기화한다.  */
	m_pDeviceContext->ClearRenderTargetView(m_pBackBufferRTV.Get(), reinterpret_cast<const f32_t*>(pClearColor));

 	return S_OK;
}

HRESULT CGraphic_Device::Clear_DepthStencil_View()
{
	if (nullptr == m_pDeviceContext)
		return E_FAIL;

	m_pDeviceContext->ClearDepthStencilView(m_pDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);

	return S_OK;
}

HRESULT CGraphic_Device::Present()
{
	if (nullptr == m_pSwapChain)
		return E_FAIL;
	
	/* 전면 버퍼와 후면 버퍼를 교체하여 후면 버퍼를 전면으로 보여주는 역할을 한다. */
	/* 후면 버퍼를 직접 화면에 보여줄게. */	
	return m_pSwapChain->Present(0, 0);	
}


HRESULT CGraphic_Device::Ready_SwapChain(HWND hWnd, WINMODE isWindowed, uint32_t iWinCX, uint32_t iWinCY)
{
	ComPtr<IDXGIDevice>			pDevice = nullptr;
	m_pDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&pDevice);

	ComPtr<IDXGIAdapter>			pAdapter = nullptr;
	pDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&pAdapter);

	ComPtr<IDXGIFactory>			pFactory = nullptr;
	pAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&pFactory);

	// 스왑체인 구조체 생성
	/* 스왑체인을 생성한다. = 텍스쳐를 생성하는 행위 + 스왑하는 형태  */
	DXGI_SWAP_CHAIN_DESC		SwapChain;
	ZeroMemory(&SwapChain, sizeof(DXGI_SWAP_CHAIN_DESC));
			

	// BufferDesc : 후면 버퍼의 속성들을 서술하는 구조체
	/* 백버퍼 == 텍스쳐 */
	/*텍스처(백버퍼 == ID3D11Texture2D)를 생성하는 행위*/
	SwapChain.BufferDesc.Width = iWinCX;	/* 가로 픽셀 수 */
	SwapChain.BufferDesc.Height = iWinCY;	/* 세로 픽셀 수 */

	/* float4(1.f, 1.f, 1.f, 1.f) */
	/* float4(1.f, 0.f, 0.f, 1.f) */
	
	// 후면 버퍼 픽셀 형식
	SwapChain.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; /*D3DFMT_A8R8G8B8*/ /* 만든 픽셀하나의 데이터 정보 : 32BIT픽셀생성하되 부호가 없는 정규화된 수를 저장할께 */
	SwapChain.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;	// 디스플레이 스캔라인 모드
	SwapChain.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;					// 디스플레이 비례 모드

	// BufferUsage : 버퍼의 용도를 서술하는 구조체로, 지금 맥락에서는 후면 버퍼가 렌더타겟이므로 DXGI_USAGE_RENDER_TARGET_OUTPUT
	/* 스케치북에 사과를 그릴꺼야. */
	/* RENDER_TARGET : 그림을 당하는 대상. 스케치북 */
	SwapChain.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	SwapChain.BufferCount = 1;

	/*스왑하는 형태 : 모니터 주사율에 따라 조절해도 됨. */
	SwapChain.BufferDesc.RefreshRate.Numerator = 60;
	SwapChain.BufferDesc.RefreshRate.Denominator = 1;

	// SampleDesc : 다중 표본화를 위해 추출할 표본 개수와 품질 수준을 서술하는 구조체 4X MSAA를 사용하지 않는 형태 
	/* 멀티샘플링 : 안티얼라이징 (계단현상방지) */
	/* 나중에 후처리 렌더링 : 멀티샘플링 지원(x) */
	SwapChain.SampleDesc.Quality = 0;

	// BufferCount : 스왑체인에서 사용할 후면 버퍼의 개수. 후면버퍼 1개 -> 더블 버퍼링, 후면버퍼 2개 -> 삼중 버퍼링
	SwapChain.SampleDesc.Count = 1;	

	// OutputWindow : 렌더링 결과를 표시할 창의 핸들
	SwapChain.OutputWindow = hWnd;	

	// Windowed : 창모드를 원하면 ture, 전체 화면을 원하면 false
	SwapChain.Windowed = static_cast<BOOL>(isWindowed);

	// SwapEffect : 교환 효과를 서술하는 구조체. DXGI_SWAP_EFFECT_DISCARD를 지정하면 디스플레이 구동기가 가장 효율적인 제시 방법을 선택
	SwapChain.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	// 스왑체인 인터페이스 생성
	/* 백버퍼라는 텍스처(ID3D11Texture2D)를 생성했다. */	
	if (FAILED(pFactory->CreateSwapChain(m_pDevice.Get(), &SwapChain, &m_pSwapChain)))
		return E_FAIL;

	return S_OK;
}


HRESULT CGraphic_Device::Ready_BackBufferRenderTargetView()
{
	if (nullptr == m_pDevice)
		return E_FAIL;

	/* 내가 앞으로 사용 하기위한 용도의 텍스쳐를 생성하기위한 베이스 데이터를 가지고 있는 객체이다. */
	/* 내가 앞으로 사용 하기위한 용도의 텍스쳐 : ID3D11RenderTargetView, ID3D11ShaderResoureView, ID3D11DepthStencilView */
	ComPtr<ID3D11Texture2D>		pBackBufferTexture = nullptr;

	// 렌더타겟의 후면버퍼 가져오기
	/* 스왑체인이 들고있던 텍스처를 가져와봐. */
	if (FAILED(m_pSwapChain->GetBuffer(0,									// 후면버퍼의 인덱스(더블 버퍼라면 0이고 삼중 버퍼 이상이면 신경써야함)
									   __uuidof(ID3D11Texture2D),			// 버퍼 인터페이스 형식을 지정하는 것. 일반적으로는 ID3D11Texture2D가 사용됨
									   (void**)&pBackBufferTexture)))		// 후면버퍼를 가리키는 포인터를 돌려줌
		return E_FAIL;

	// 렌더타겟 뷰 생성
	/* 실제 렌더타겟용도로 사용할 수 있는 텍스쳐 타입(ID3D11RenderTargetView)의 객체를 생성한다. */
	if (FAILED(m_pDevice->CreateRenderTargetView(pBackBufferTexture.Get(),// 렌더 대상으로 사용할 자원(방금 얻은 렌더타겟의 후면버퍼)
												 nullptr, 				  // 렌더타겟 뷰 Desc 구조체를 가리키는 포인터. 형식을 완전히 지정해서 자원을 생성했다면 nullptr로 설정해도 됨.
												 &m_pBackBufferRTV)))	  // 반환받을 렌더타겟 뷰
		return E_FAIL;	

	return S_OK;
}

HRESULT CGraphic_Device::Ready_DepthStencilView(uint32_t iWinCX, uint32_t iWinCY)
{
	if (nullptr == m_pDevice)
		return E_FAIL;

	ComPtr<ID3D11Texture2D> pDepthStencilTexture = { nullptr };
	
	D3D11_TEXTURE2D_DESC	TextureDesc{};	

	/* 깊이 버퍼의 픽셀은 백버퍼의 픽셀과 갯수가 동일해야만 깊이 테스트가 가능해진다. */
	/* 픽셀의 수가 다르면 아에 렌더링을 못함. */
	TextureDesc.Width = iWinCX;									// 텍스처의 너비
	TextureDesc.Height = iWinCY;								// 텍스처의 높이
	TextureDesc.MipLevels = 1;									// 밉맵 수준의 개수(깊이, 스텐실 버퍼를 위한 텍스처에서는 밉맵 수준이 하나만 있으면 됨)
	TextureDesc.ArraySize = 1;									// 텍스처 배열의 텍스처 개수 (깊이, 스텐실 버퍼를 위한 텍스처에서는 밉맵 수준이 하나만 있으면 됨)
	TextureDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;			// 텍셀의 형식을 뜻하는 필드

	TextureDesc.SampleDesc.Quality = 0;							// 다중 표본 개수와 품질 수준을 서술하는 구조체 렌더타겟에서 설정한 것과 동일해야함
	TextureDesc.SampleDesc.Count = 1;

	/* 동적? 정적?  */
	// 텍스처의 용도를 뜻하는 필드 
	// D3D11_USAGE_DEFAULT : 자원을 GPU가 읽고 써야한다면 이 용도를 설정 (CPU는 읽을 수 없음)
	// D3D11_USAGE_IMMUTEABLE : 자원을 일단 생성한 후에는 그 내용을 바꾸지 않는 경우에 이 용도를 지정.(GPU 읽기 전용)
	// D3D11_USAGE_DYNAMIC : CPU가 이 자원의 내용을 빈번하게 갱신해야 할 때 이 용도를 지정. (GPU 읽기 가능, CPU 읽기 쓰기 가능) 성능상의 피해가 생김
	// D3D11_USAGE_STAGING : GPU에서 CPU메모리로의 자료복사가능. 매우 느린 연산이므로 꼭 필요한 경우가 아니면 피해야한다.
	TextureDesc.Usage = D3D11_USAGE_DEFAULT /* 정적 */;


	/* 추후에 어떤 용도로 바인딩 될 수 있는 View타입의 텍스쳐를 만들기위한 Texture2D입니까? */
	// 자원을 파이프라인에 어떤 식으로 묶을 것인지를 지정하는 하나 이상의 플래그들을 OR로 결합하여 지정
	// D3D11_BIND_RENDER_TARGET : 텍스처를 렌더 타겟으로서 파이프라인에 묶는다.
	// D3D11_BIND_SHADER_RESOURCE : 텍스처를 셰이더 자원으로서 파이프라인에 묶는다.
	TextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL
		/*| D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE*/;


	// CPU가 자원에 접근하는 방식을 결정하는 플래그들을 지정한다.
	// 깊이, 스텐실 버퍼의 경우 GPU만 읽고 쓰기 때문에 0을 지정한다.
	TextureDesc.CPUAccessFlags = 0;

	// 기타 플래그들로 깊이, 스텐시 버퍼의 경우 사용하지 않으므로 0지정
	TextureDesc.MiscFlags = 0;

	// 버퍼 생성
	if (FAILED(m_pDevice->CreateTexture2D(&TextureDesc, nullptr, &pDepthStencilTexture)))
		return E_FAIL;

	/* RenderTargetView */
	/* ShaderResourceView */
	/* DepthStencilView */	

	// 뷰 생성
	if (FAILED(m_pDevice->CreateDepthStencilView(pDepthStencilTexture.Get(), nullptr, &m_pDepthStencilView)))
		return E_FAIL;		

	return S_OK;
}

unique_ptr<CGraphic_Device> CGraphic_Device::Create(HWND hWnd, WINMODE isWindowed, uint32_t iWinSizeX, uint32_t iWinSizeY, _Out_ ComPtr<ID3D11Device>& pDevice, _Out_ ComPtr<ID3D11DeviceContext>& pContext)
{
	auto			pInstance = unique_ptr<CGraphic_Device>(new CGraphic_Device);

	if (FAILED(pInstance->Initialize(hWnd, isWindowed, iWinSizeX, iWinSizeY, pDevice, pContext)))
	{
		MSG_BOX("Failed to Created : CGraphic_Device");
		pInstance.reset();
	}

	return pInstance;
}


