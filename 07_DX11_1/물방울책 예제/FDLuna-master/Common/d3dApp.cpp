//***************************************************************************************
// d3dApp.cpp by Frank Luna (C) 2011 All Rights Reserved.
//***************************************************************************************

#include "d3dApp.h"
#include <WindowsX.h>
#include <sstream>

namespace
{
	// This is just used to forward Windows messages from a global window
	// procedure to our member function window procedure because we cannot
	// assign a member function to WNDCLASS::lpfnWndProc.
	D3DApp* gd3dApp = 0;
}

LRESULT CALLBACK
MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// Forward hwnd on because we can get messages (e.g., WM_CREATE)
	// before CreateWindow returns, and thus before mhMainWnd is valid.
	return gd3dApp->MsgProc(hwnd, msg, wParam, lParam);
}

D3DApp::D3DApp(HINSTANCE hInstance)
:	mhAppInst(hInstance),
	mMainWndCaption(L"D3D11 Application"),
	md3dDriverType(D3D_DRIVER_TYPE_HARDWARE),
	mClientWidth(800),
	mClientHeight(600),
	mEnable4xMsaa(false),
	mhMainWnd(0),
	mAppPaused(false),
	mMinimized(false),
	mMaximized(false),
	mResizing(false),
	m4xMsaaQuality(0),
 
	md3dDevice(0),
	md3dImmediateContext(0),
	mSwapChain(0),
	mDepthStencilBuffer(0),
	mRenderTargetView(0),
	mDepthStencilView(0)
{
	ZeroMemory(&mScreenViewport, sizeof(D3D11_VIEWPORT));

	// Get a pointer to the application object so we can forward 
	// Windows messages to the object's window procedure through
	// the global window procedure.
	gd3dApp = this;
}

D3DApp::~D3DApp()
{
	ReleaseCOM(mRenderTargetView);
	ReleaseCOM(mDepthStencilView);
	ReleaseCOM(mSwapChain);
	ReleaseCOM(mDepthStencilBuffer);

	// Restore all default settings.
	if( md3dImmediateContext )
		md3dImmediateContext->ClearState();

	ReleaseCOM(md3dImmediateContext);
	ReleaseCOM(md3dDevice);
}

HINSTANCE D3DApp::AppInst()const
{
	return mhAppInst;
}

HWND D3DApp::MainWnd()const
{
	return mhMainWnd;
}

float D3DApp::AspectRatio()const
{
	return static_cast<float>(mClientWidth) / mClientHeight;
}

int D3DApp::Run()
{
	MSG msg = {0};
 
	mTimer.Reset();

	while(msg.message != WM_QUIT)
	{
		// If there are Window messages then process them.
		if(PeekMessage( &msg, 0, 0, 0, PM_REMOVE ))
		{
            TranslateMessage( &msg );
            DispatchMessage( &msg );
		}
		// Otherwise, do animation/game stuff.
		else
        {	
			mTimer.Tick();

			if( !mAppPaused )
			{
				CalculateFrameStats();
				UpdateScene(mTimer.DeltaTime());	
				DrawScene();
			}
			else
			{
				Sleep(100);
			}
        }
    }

	return (int)msg.wParam;
}

bool D3DApp::Init()
{
	if(!InitMainWindow())
		return false;

	if(!InitDirect3D())
		return false;

	return true;
}
 
void D3DApp::OnResize()
{
	assert(md3dImmediateContext);
	assert(md3dDevice);
	assert(mSwapChain);

	// Release the old views, as they hold references to the buffers we
	// will be destroying.  Also release the old depth/stencil buffer.

	ReleaseCOM(mRenderTargetView);
	ReleaseCOM(mDepthStencilView);
	ReleaseCOM(mDepthStencilBuffer);


	// Resize the swap chain and recreate the render target view.

	HR(mSwapChain->ResizeBuffers(1, mClientWidth, mClientHeight, DXGI_FORMAT_R8G8B8A8_UNORM, 0));
	ID3D11Texture2D* backBuffer;

	// 렌더타겟의 후면버퍼 가져오기
	HR(mSwapChain->GetBuffer(0,											// 후면버퍼의 인덱스(더블 버퍼라면 0이고 삼중 버퍼 이상이면 신경써야함)
							 __uuidof(ID3D11Texture2D),					// 버퍼 인터페이스 형식을 지정하는 것. 일반적으로는 ID3D11Texture2D가 사용됨
							 reinterpret_cast<void**>(&backBuffer)));	// 후면버퍼를 가리키는 포인터를 돌려줌
	// 렌더타겟 뷰 생성
	HR(md3dDevice->CreateRenderTargetView(backBuffer,					// 렌더 대상으로 사용할 자원(방금 얻은 렌더타겟의 후면버퍼)
										  0,							// 렌더타겟 뷰 Desc 구조체를 가리키는 포인터. 형식을 완전히 지정해서 자원을 생성했다면 nullptr로 설정해도 됨.
										  &mRenderTargetView));			// 반환받을 렌더타겟 뷰
	ReleaseCOM(backBuffer);

	// Create the depth/stencil buffer and view.

	D3D11_TEXTURE2D_DESC depthStencilDesc;
	
	depthStencilDesc.Width     = mClientWidth;						// 텍스처의 너비
	depthStencilDesc.Height    = mClientHeight;						// 텍스처의 높이
	depthStencilDesc.MipLevels = 1;									// 밉맵 수준의 개수(깊이, 스텐실 버퍼를 위한 텍스처에서는 밉맵 수준이 하나만 있으면 됨)
	depthStencilDesc.ArraySize = 1;									// 텍스처 배열의 텍스처 개수 (깊이, 스텐실 버퍼를 위한 텍스처에서는 밉맵 수준이 하나만 있으면 됨)
	depthStencilDesc.Format    = DXGI_FORMAT_D24_UNORM_S8_UINT;		// 텍셀의 형식을 뜻하는 필드

	// 다중 표본 개수와 품질 수준을 서술하는 구조체 렌더타겟에서 설정한 것과 동일해야함
	// Use 4X MSAA? --must match swap chain MSAA values.
	if( mEnable4xMsaa )
	{
		depthStencilDesc.SampleDesc.Count   = 4;
		depthStencilDesc.SampleDesc.Quality = m4xMsaaQuality-1;
	}
	// No MSAA
	else
	{
		depthStencilDesc.SampleDesc.Count   = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
	}

	// 텍스처의 용도를 뜻하는 필드 
	// D3D11_USAGE_DEFAULT : 자원을 GPU가 읽고 써야한다면 이 용도를 설정 (CPU는 읽을 수 없음)
	// D3D11_USAGE_IMMUTEABLE : 자원을 일단 생성한 후에는 그 내용을 바꾸지 않는 경우에 이 용도를 지정.(GPU 읽기 전용)
	// D3D11_USAGE_DYNAMIC : CPU가 이 자원의 내용을 빈번하게 갱신해야 할 때 이 용도를 지정. (GPU 읽기 가능, CPU 읽기 쓰기 가능) 성능상의 피해가 생김
	// D3D11_USAGE_STAGING : GPU에서 CPU메모리로의 자료복사가능. 매우 느린 연산이므로 꼭 필요한 경우가 아니면 피해야한다.
	depthStencilDesc.Usage          = D3D11_USAGE_DEFAULT;

	// 자원을 파이프라인에 어떤 식으로 묶을 것인지를 지정하는 하나 이상의 플래그들을 OR로 결합하여 지정
	// D3D11_BIND_RENDER_TARGET : 텍스처를 렌더 타겟으로서 파이프라인에 묶는다.
	// D3D11_BIND_SHADER_RESOURCE : 텍스처를 셰이더 자원으로서 파이프라인에 묶는다.
	depthStencilDesc.BindFlags      = D3D11_BIND_DEPTH_STENCIL;

	// CPU가 자원에 접근하는 방식을 결정하는 플래그들을 지정한다.
	// 깊이, 스텐실 버퍼의 경우 GPU만 읽고 쓰기 때문에 0을 지정한다.
	depthStencilDesc.CPUAccessFlags = 0; 

	// 기타 플래그들로 깊이, 스텐시 버퍼의 경우 사용하지 않으므로 0지정
	depthStencilDesc.MiscFlags      = 0;

	HR(md3dDevice->CreateTexture2D(&depthStencilDesc, 0, &mDepthStencilBuffer));
	HR(md3dDevice->CreateDepthStencilView(mDepthStencilBuffer, 0, &mDepthStencilView));


	// Bind the render target view and depth/stencil view to the pipeline.

	md3dImmediateContext->OMSetRenderTargets(1,						// 렌더 대상의 개수 여기서는 하나
											 &mRenderTargetView,	// 렌더타겟 뷰들을 가리키는 포인터들을 담은 배열의 첫 원소를 가리키는 포인터
											 mDepthStencilView);	// 파이프라인에 묶을 깊이-스텐실 뷰를 가리키는 포인터
	

	// Set the viewport transform.

	mScreenViewport.TopLeftX = 0;
	mScreenViewport.TopLeftY = 0;
	mScreenViewport.Width    = static_cast<float>(mClientWidth);
	mScreenViewport.Height   = static_cast<float>(mClientHeight);
	mScreenViewport.MinDepth = 0.0f;
	mScreenViewport.MaxDepth = 1.0f;

	md3dImmediateContext->RSSetViewports(1, &mScreenViewport);
}
 
LRESULT D3DApp::MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch( msg )
	{
	// WM_ACTIVATE is sent when the window is activated or deactivated.  
	// We pause the game when the window is deactivated and unpause it 
	// when it becomes active.  
	case WM_ACTIVATE:
		if( LOWORD(wParam) == WA_INACTIVE )
		{
			mAppPaused = true;
			mTimer.Stop();
		}
		else
		{
			mAppPaused = false;
			mTimer.Start();
		}
		return 0;

	// WM_SIZE is sent when the user resizes the window.  
	case WM_SIZE:
		// Save the new client area dimensions.
		mClientWidth  = LOWORD(lParam);
		mClientHeight = HIWORD(lParam);
		if( md3dDevice )
		{
			if( wParam == SIZE_MINIMIZED )
			{
				mAppPaused = true;
				mMinimized = true;
				mMaximized = false;
			}
			else if( wParam == SIZE_MAXIMIZED )
			{
				mAppPaused = false;
				mMinimized = false;
				mMaximized = true;
				OnResize();
			}
			else if( wParam == SIZE_RESTORED )
			{
				
				// Restoring from minimized state?
				if( mMinimized )
				{
					mAppPaused = false;
					mMinimized = false;
					OnResize();
				}

				// Restoring from maximized state?
				else if( mMaximized )
				{
					mAppPaused = false;
					mMaximized = false;
					OnResize();
				}
				else if( mResizing )
				{
					// If user is dragging the resize bars, we do not resize 
					// the buffers here because as the user continuously 
					// drags the resize bars, a stream of WM_SIZE messages are
					// sent to the window, and it would be pointless (and slow)
					// to resize for each WM_SIZE message received from dragging
					// the resize bars.  So instead, we reset after the user is 
					// done resizing the window and releases the resize bars, which 
					// sends a WM_EXITSIZEMOVE message.
				}
				else // API call such as SetWindowPos or mSwapChain->SetFullscreenState.
				{
					OnResize();
				}
			}
		}
		return 0;

	// WM_EXITSIZEMOVE is sent when the user grabs the resize bars.
	case WM_ENTERSIZEMOVE:
		mAppPaused = true;
		mResizing  = true;
		mTimer.Stop();
		return 0;

	// WM_EXITSIZEMOVE is sent when the user releases the resize bars.
	// Here we reset everything based on the new window dimensions.
	case WM_EXITSIZEMOVE:
		mAppPaused = false;
		mResizing  = false;
		mTimer.Start();
		OnResize();
		return 0;
 
	// WM_DESTROY is sent when the window is being destroyed.
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	// The WM_MENUCHAR message is sent when a menu is active and the user presses 
	// a key that does not correspond to any mnemonic or accelerator key. 
	case WM_MENUCHAR:
        // Don't beep when we alt-enter.
        return MAKELRESULT(0, MNC_CLOSE);

	// Catch this message so to prevent the window from becoming too small.
	case WM_GETMINMAXINFO:
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = 200;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = 200; 
		return 0;

	case WM_LBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_RBUTTONDOWN:
		OnMouseDown(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;
	case WM_LBUTTONUP:
	case WM_MBUTTONUP:
	case WM_RBUTTONUP:
		OnMouseUp(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;
	case WM_MOUSEMOVE:
		OnMouseMove(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		return 0;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}


bool D3DApp::InitMainWindow()
{
	WNDCLASS wc;
	wc.style         = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc   = MainWndProc; 
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = mhAppInst;
	wc.hIcon         = LoadIcon(0, IDI_APPLICATION);
	wc.hCursor       = LoadCursor(0, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	wc.lpszMenuName  = 0;
	wc.lpszClassName = L"D3DWndClassName";

	if( !RegisterClass(&wc) )
	{
		MessageBox(0, L"RegisterClass Failed.", 0, 0);
		return false;
	}

	// Compute window rectangle dimensions based on requested client area dimensions.
	RECT R = { 0, 0, mClientWidth, mClientHeight };
    AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
	int width  = R.right - R.left;
	int height = R.bottom - R.top;

	mhMainWnd = CreateWindow(L"D3DWndClassName", mMainWndCaption.c_str(), 
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, 0, 0, mhAppInst, 0); 
	if( !mhMainWnd )
	{
		MessageBox(0, L"CreateWindow Failed.", 0, 0);
		return false;
	}

	ShowWindow(mhMainWnd, SW_SHOW);
	UpdateWindow(mhMainWnd);

	return true;
}

bool D3DApp::InitDirect3D()
{
	// Create the device and device context.

	UINT createDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)  
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL featureLevel;
	HRESULT hr = D3D11CreateDevice(
			0,						// 디스플레이 어댑터

			md3dDriverType,			// 드라이버 타입 : 
									// D3D_DRIVER_TYPE_HARDWARE(3차원 그래픽 가속이 적용되게하는 구동기)
									// D3D_DRIVER_TYPE_REFERENCE(표준 장치) 
									// D3D_DRIVER_TYPE_SOFTWARE(3차원 하드웨어를 흉내 내는 소프트웨어 구동기)

			0,						// 소프트웨어 구동기 지정하는 부분. 이 책에서는 D3D_DRIVER_TYPE_HARDWARE 를 사용하기 때문에 0 또는 nullptr로 지정
			createDeviceFlags,		// 추가적인 장치 생성 플래그
			0,						// pFeatureLevels 원소들의 순서가 곧 기능 수준을 점검하는 순서. 이 매개변수에 널 값을 지정하면 지원되는 최고 기능 수준이 선택됨
			0,						// 위 매개변수에 null을 저장했다면 이 매개변수는 0으로 지정하면 됨
			D3D11_SDK_VERSION,		// 항상 D3D11_SDK_VERSION로 지정
			&md3dDevice,			// 생성한 Deviec를 돌려준다
			&featureLevel,			// 지원되는 최고기능 수준을 돌려준다.
			&md3dImmediateContext	// 생성된 장치 문맥을 돌려준다.
	);

	if( FAILED(hr) )
	{
		MessageBox(0, L"D3D11CreateDevice Failed.", 0, 0);
		return false;
	}

	if( featureLevel != D3D_FEATURE_LEVEL_11_0 )
	{
		MessageBox(0, L"Direct3D Feature Level 11 unsupported.", 0, 0);
		return false;
	}

	// Check 4X MSAA quality support for our back buffer format.
	// All Direct3D 11 capable devices support 4X MSAA for all render 
	// target formats, so we only need to check quality support.

	HR(md3dDevice->CheckMultisampleQualityLevels(
		DXGI_FORMAT_R8G8B8A8_UNORM, 4, &m4xMsaaQuality));
	assert( m4xMsaaQuality > 0 );

	// Fill out a DXGI_SWAP_CHAIN_DESC to describe our swap chain.

	// <스왑체인구조체 생성 및 채우기>
	DXGI_SWAP_CHAIN_DESC sd;
	
	// 1. BufferDesc : 후면 버퍼의 속성들을 서술하는 구조체
	sd.BufferDesc.Width  = mClientWidth;									// 후면 버퍼 너비
	sd.BufferDesc.Height = mClientHeight;									// 후면 버퍼 높이
	sd.BufferDesc.RefreshRate.Numerator = 60;								// 디스플레이 모드 갱신율
	sd.BufferDesc.RefreshRate.Denominator = 1;								// 디스플레이 모드 갱신율
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;						// 후면 버퍼 픽셀 형식
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;	// 디스플레이 스캔라인 모드
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;					// 디스플레이 비례 모드

	// 2. SampleDesc : 다중 표본화를 위해 추출할 표본 개수와 품질 수준을 서술하는 구조체
	// Use 4X MSAA? 
	if( mEnable4xMsaa )
	{
		sd.SampleDesc.Count   = 4;
		sd.SampleDesc.Quality = m4xMsaaQuality-1;
	}
	// No MSAA
	else
	{
		sd.SampleDesc.Count   = 1;
		sd.SampleDesc.Quality = 0;
	}

	// 3. BufferUsage : 버퍼의 용도를 서술하는 구조체로, 지금 맥락에서는 후면 버퍼가 렌더타겟이므로 DXGI_USAGE_RENDER_TARGET_OUTPUT
	sd.BufferUsage  = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	// 4. BufferCount : 스왑체인에서 사용할 후면 버퍼의 개수. 후면버퍼 1개 -> 더블 버퍼링, 후면버퍼 2개 -> 삼중 버퍼링
	sd.BufferCount  = 1;

	// 5. OutputWindow : 렌더링 결과를 표시할 창의 핸들
	sd.OutputWindow = mhMainWnd;

	// 6. Windowed : 창모드를 원하면 ture, 전체 화면을 원하면 false
	sd.Windowed     = true;

	// 7. SwapEffect : 교환 효과를 서술하는 구조체. DXGI_SWAP_EFFECT_DISCARD를 지정하면 디스플레이 구동기가 가장 효율적인 제시 방법을 선택
	sd.SwapEffect   = DXGI_SWAP_EFFECT_DISCARD;

	//8. Flags : 
	sd.Flags        = 0;

	// To correctly create the swap chain, we must use the IDXGIFactory that was
	// used to create the device.  If we tried to use a different IDXGIFactory instance
	// (by calling CreateDXGIFactory), we get an error: "IDXGIFactory::CreateSwapChain: 
	// This function is being called with a device from a different IDXGIFactory."

	IDXGIDevice* dxgiDevice = 0;
	HR(md3dDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice));
	      
	IDXGIAdapter* dxgiAdapter = 0;
	HR(dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter));

	IDXGIFactory* dxgiFactory = 0;
	HR(dxgiAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&dxgiFactory));

	// 스왑체인 인터페이스 생성
	HR(dxgiFactory->CreateSwapChain(md3dDevice,		// ID3D11Device를 가리키는 포인터.
									&sd,			// 교환 사슬 서술 구조체를 가리키는 포인터.
									&mSwapChain));	// 생성된 교환 사슬 인터페이스를 돌려준다.
	
	ReleaseCOM(dxgiDevice);
	ReleaseCOM(dxgiAdapter);
	ReleaseCOM(dxgiFactory);

	// The remaining steps that need to be carried out for d3d creation
	// also need to be executed every time the window is resized.  So
	// just call the OnResize method here to avoid code duplication.
	
	OnResize();

	return true;
}

void D3DApp::CalculateFrameStats()
{
	// Code computes the average frames per second, and also the 
	// average time it takes to render one frame.  These stats 
	// are appended to the window caption bar.

	static int frameCnt = 0;
	static float timeElapsed = 0.0f;

	frameCnt++;

	// Compute averages over one second period.
	if( (mTimer.TotalTime() - timeElapsed) >= 1.0f )
	{
		float fps = (float)frameCnt; // fps = frameCnt / 1
		float mspf = 1000.0f / fps;

		std::wostringstream outs;   
		outs.precision(6);
		outs << mMainWndCaption << L"    "
			 << L"FPS: " << fps << L"    " 
			 << L"Frame Time: " << mspf << L" (ms)";
		SetWindowText(mhMainWnd, outs.str().c_str());
		
		// Reset for next average.
		frameCnt = 0;
		timeElapsed += 1.0f;
	}
}


