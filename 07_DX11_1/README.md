# 7개월차 DX11 수업 정리

### 1일차 클래스 규칙

<details>
  <summary> 클래스 규칙</summary>

```cpp
class C클래스이름
{
private or protected:
  생성자
public:  // 스마트 포인터를 사용하기 위해 소멸자는 public으로 설정
  소멸자

public:
  함수
protected:
  변수
protected:
  함수
private:
  변수
private:
  함수

public:
  클래스 생성 관련 함수
  필요에 따라 소멸 관련 함수
};
```
</details>

### 2일차 MainApp
<details>
  <summary> MainApp 클래스</summary>

- namespace 습관화
- final -> 부모 클래스로 사용하지 않음(최하위 자식 클래스임을 나타냄)
- Create() 함수에서는 객체 생성과 동시에 Initialize()를 호출함. + 스마트 포인터종류중 하나인 unique_ptr을 사용(한 번만 생성해야 하는 객체에 사용)
- Create() 함수는 static으로 선언하여 객체가 없어소 함수호출을 하여 객체를 생성할 수 있도록 설정.

> MainApp.h
```cpp
namespace Client
{
	class CMainApp final
	{
	private:
		CMainApp();
	public:
		~CMainApp() = default;
	public:
		HRESULT Initialize();
		void Update();
		HRESULT Render();

	public:
		static unique_ptr<CMainApp> Create();
	};
}
```

> MainApp.cpp
```cpp
#include "MainApp.h"

CMainApp::CMainApp()
{
}

HRESULT CMainApp::Initialize()
{
    /* 엔진 프로젝트에 대한 준비. */
    return S_OK;
}

void CMainApp::Update()
{
}

HRESULT CMainApp::Render()
{
    return S_OK;
}

unique_ptr<CMainApp> CMainApp::Create()
{
    auto pInstance = unique_ptr<CMainApp>(new CMainApp());

    if (FAILED(pInstance->Initialize()))
    {
        pInstance.reset();        
    }

    return pInstance;
}
```
</details>


### 3일차 Engine프로젝트의 Defines 헤더파일 정리

<details>
  <summary> Engine_Defines.h </summary>

```cpp
#ifndef Engine_Define_h__
#define Engine_Define_h__

#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <functional>
#include <string>
#include <unordered_map>
#include <ctime>

#include "Engine_Enum.h"
#include "Engine_Macro.h"
#include "Engine_Struct.h"
#include "Engine_Typedef.h"
#include "Engine_Function.h"

// dinput 사용
#define DIRECTINPUT_VERSION	0x0800
#include <dinput.h>

// 경고 처리 무시
#pragma warning(disable : 4251)

// 메모리 누수
#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifndef DBG_NEW 

#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW 

#endif
#endif

using namespace std;
using namespace Engine;

#endif // Engine_Define_h__

```
</details>

<details>
  <summary> Engine_Enum.h </summary>

- enum class 사용
- 기존 enum과 동일하게 0부터 정수를 만들어줌
- 다만 기존의 enum 과는 다르게 정수값으로 묵시적 형변환이 안됨. -> 명시적 형변환 필요

```cpp
#ifndef Engine_Enum_h__
#define Engine_Enum_h__

namespace Engine
{
	enum class WINMODE { FULL, WIN, END };	
	enum class STATE { RIGHT, UP, LOOK, POSITION, END };
}
#endif // Engine_Enum_h__
```
</details>

<details>
  <summary> Engine_Function.h </summary>

- dx9때 사용하던 Find_Tag는 사용하지 않음
- map컨테이너의 Key를 더이상 w_char로 사용하지 않고 wstring을 사용하여 map컨테이너의 find함수를 하용하여 객체에 접근함

```cpp
#ifndef Engine_Function_h__
#define Engine_Function_h__

namespace Engine
{
	// 템플릿은 기능의 정해져있으나 자료형은 정해져있지 않은 것
	// 기능을 인스턴스화 하기 위하여 만들어두는 틀

	template<typename T>
	void Safe_Delete(T& Pointer)
	{
		if (nullptr != Pointer)
		{
			delete Pointer;
			Pointer = nullptr;
		}
	}

	template<typename T>
	void Safe_Delete_Array(T& Pointer)
	{
		if (nullptr != Pointer)
		{
			delete [] Pointer;
			Pointer = nullptr;
		}
	}
}

#endif // Engine_Function_h__

```
</details>


<details>
  <summary> Engine_Macro.h </summary>

- 싱글톤을 사용할 때 객체의 주소를 반환하지 않고 객체를 static으로 생성한 후 레퍼런스를 반환
- ENGINE_EXPORTS가 정의된 Engine프로젝트에서는 _declspec(dllexport)로 사용하고 정의되지않은 Client프로젝트 에서는 _declspec(dllimport)로 사용하기 위한 ENGIN_DLL 매크로 사용
  
```cpp
#ifndef Engine_Macro_h__
#define Engine_Macro_h__

#ifndef			MSG_BOX
#define			MSG_BOX(_message)			MessageBox(nullptr, TEXT(_message), L"System Message", MB_OK)
#endif

#define			NS_BEGIN(NAMESPACE)			namespace NAMESPACE {
#define			NS_END							    }

#define			NS_USING(NAMESPACE)			using namespace NAMESPACE;

#ifdef	ENGINE_EXPORTS
#define ENGINE_DLL		_declspec(dllexport)
#else
#define ENGINE_DLL		_declspec(dllimport)
#endif

/* 싱글톤 : 클래스를 할당(객체화) 하는 횟수를 n개로 제한한다 -> 1개로 제한한다.*/

#define NO_COPY(CLASSNAME)											    \
			private:												              \
			CLASSNAME(const CLASSNAME&) = delete;					\
			CLASSNAME& operator = (const CLASSNAME&) = delete;		

#define DECLARE_SINGLETON(CLASSNAME)						\
			NO_COPY(CLASSNAME)								        \
			public:											              \
				static CLASSNAME& Get(void)					    \
				{											                  \
					static CLASSNAME Instance = {};			  \
					return Instance;						          \
				}											
#endif // Engine_Macro_h__
```
</details>

<details>
  <summary> Engine_Struct.h </summary>

- Graphic_Device를 초기화하기 위한 매개변수를 구조체로 정의하여 매개변수의 길이를 줄인다

```cpp
#ifndef Engine_Struct_h__
#define Engine_Struct_h__

#include "Engine_Typedef.h"
namespace Engine
{
	typedef struct tagEngineDesc
	{
		HWND		hWnd;
		WINMODE		eWinMode;
		uint32_t	iWinSizeX, iWinSizeY;
	}ENGINE_DESC;
}
#endif // Engine_Struct_h__
```
</details>

<details>
  <summary> Engine_Typedef.h </summary>

> typedef를 사용하는 이유

- 한 줄만 고치면 전체 코드를 바꿀 수 있음(기존 타입에 별명을 붙이는 개념이기 때문)
- 타입의 크기를 이름에 명시(ex. f32_t)
- 긴 타입 이름을 축약할 수 있고 가독성이 좋아짐

```cpp
#ifndef Engine_Typedef_h__
#define Engine_Typedef_h__

namespace Engine
{
	typedef		bool					_bool;

	typedef		char					char_t;
	typedef		wchar_t					tchar_t;
	typedef		wstring					wstring_t;

	typedef		float					    f32_t;
	typedef		double					  f64_t;
	typedef		long double				f128_t;

	typedef    XMFLOAT2					float2_t;
	typedef    XMFLOAT3					float3_t;
	typedef    XMFLOAT4					float4_t;

	typedef    XMFLOAT4X4				float4x4_t;
}

#endif // Engine_Typedef_h__

```
</details>

<details>
  <summary> Client_Defines.h </summary>

```cpp
#pragma once

// 클라이언트에서 제작하는 클래스들이 이용할 공통적인 것들
#include <Windows.h>
#include <memory>  // 스마트 포인터를 사용하기 위함
#include "Engine_Defines.h"

// 아래의 using namespace 를 사용하기 위해 사용함
namespace Client
{

};

using namespace std;
using namespace Client;
using namespace Engine;

extern HWND	g_hWnd;
```
</details>

### 4일차 Engine의 클래스를 Client로 이동

<details>
  <summary> _declspec(dllexport) & _declspec(dllimport) </summary>

- 동적 라이브러리인 DLL에서의 클래스를 내보내기 위해서는 Engine프로젝트에서는 _declspec(dllexport) 가 필요함
- Client 프로젝트가 참조하는 Engine_SDK에서는 _declspec(dllimport)가 필요함
- Engine프로젝트의 헤더파일을 복사하여 Engine_SDK로 이동하여 사용하는데 복사하는 모든 헤더파일을 일일히 바꿔주지 못하므로 매크로를 사용
- 다만 Client프로젝트에 공개하지 않는 Engine프로젝트 내부에서만 사용하는 클래스는 키워드를 붙힐 필요가 없음
</details>



### 5일차 GameInstance

<details>
  <summary> GameInstance클래스 </summary>

- 엔진의 기능을 클라이언트에 보여주는 객체.
- 엔진에 정의되어있는 다양한 기능을 하는 객체를 모아서 보관한다.
- 엔진의 업데이트와 렌더를 담당한다.

> GameInstance.h

- 여러 메니저를 Initialize에서 모두 생성하여 사용 할 준비를 한다.
- 메니저를 통해 클라이언트에서 사용 할 함수를 만들어두고 생성한 메니저의 함수를 실행시켜주기만 함.
- 따라서 Engine에서 만드는 클래스는 싱글톤으로 만들지 않고 CGameInstance만을 싱글톤으로 만들어서 Client프로젝트에서 접근할 수 있도록 함.

```cpp
#pragma once
#include "Engine_Defines.h"
#include "Timer_Manager.h"
#include "Graphic_Device.h"

NS_BEGIN(Engine)
class ENGINE_DLL CGameInstance final
{
	DECLARE_SINGLETON(CGameInstance)

private:
	CGameInstance();

public:
	~CGameInstance();

public:/* 엔진의 초기화과정 : 여러 메니져를 미리 할당하여 사용 할 준비를 한다*/
	HRESULT			Initialize_Engine(const ENGINE_DESC& EngineDesc, _Out_ ComPtr<ID3D11Device>& pDevice, _Out_ ComPtr<ID3D11DeviceContext>& pContext);

public:
	HRESULT			Clear_BackBuffer_View(const float4_t* pClearColor);
	HRESULT			Clear_DepthStencil_View();
	HRESULT			Present();

public:
	f32_t			Get_TimeDelta(const wstring_t& strTimerTag);
	HRESULT			Add_Timer(const wstring_t& strTimerTag);
	void			Update_TimeDelta(const wstring_t& strTimerTag);

private:
	unique_ptr<CGraphic_Device>	m_pGraphic_Device = { nullptr };
	unique_ptr<CTimer_Manager>	m_pTimer_Manager = { nullptr };

};
NS_END

```

</details>

### 6일차 GraphicDevice

<details>
	<summary> Com_ptr </summary>

- Dx11의 컴객체 전용 스마트 포인터를 멤버로 들고있는 클래스 객체
- Com객체의 주소를 얻고 싶다면 .Get()을 사용해야 한다.
- Com객체의 이중 포인터를 얻고 싶다면 .GetAddressOf()를 사용해야 한다.
</details>

<details>
	<summary> GraphicDevice 초기화 단계 </summary>

1. Device(생성 및 할당), DeviceContext(기능 사용 + 파이프라인 연결) 객체 생성
2. SwapChain 생성
3. 백버퍼 뷰 생성
4. 깊이-스텐실 텍스처 생성 + 깊이-스텐실 뷰 생성
5. 백버퍼 뷰, 깊이-스텐실 뷰를 Device에 바인딩
6. 뷰포트 설정
</details>

<details>
	<summary> 텍스처와 뷰 </summary>

- 텍스처를 생성한 뒤 텍스처에서 뷰를 생성한 뒤 DeviecContext에 view를 바인딩 하여 사용할 수 있다.
- ID3D11Texture2D는 그냥 메모리 덩어리 일 뿐이고 view가 용도를 정함
- BindFlags는 만들 수 있는 view 종류의 허가이다. 텍스처 Format은 메모리 규격, view Format은 그 메모리의 해석이다.
- typed 포맷이면 해석이 하나라서 view desc를 nullptr로 생략할 수 있다. typeless면 view desc에 Format을 직접 지정해야 한다.

```cpp
ComPtr<ID3D11Texture2D> pDepthStencilTexture = { nullptr };

D3D11_TEXTURE2D_DESC	TextureDesc{};	

TextureDesc.Width = iWinCX;
TextureDesc.Height = iWinCY;
TextureDesc.MipLevels = 1;
TextureDesc.ArraySize = 1;
TextureDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

TextureDesc.SampleDesc.Quality = 0;
TextureDesc.SampleDesc.Count = 1;

TextureDesc.Usage = D3D11_USAGE_DEFAULT;
/* 추후에 어떤 용도로 바인딩 될 수 있는 View타입의 텍스쳐를 만들기위한 Texture2D입니까? */
TextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL
	/*| D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE*/;
TextureDesc.CPUAccessFlags = 0;
TextureDesc.MiscFlags = 0;

// 텍스처를 생성하기 위한 구조체를 채우고 그 구조체로 텍스처 생성
if (FAILED(m_pDevice->CreateTexture2D(&TextureDesc, nullptr, &pDepthStencilTexture)))
	return E_FAIL;
// 텍스처로부터 뷰를 생성하여 사용함
if (FAILED(m_pDevice->CreateDepthStencilView(pDepthStencilTexture.Get(), nullptr, &m_pDepthStencilView)))
	return E_FAIL;	
```
</details>

<details>
	<summary> RenderTarget추가 방법 </summary>

```cpp
// 미니맵 그리기 시작
// 미니맵RTV, DSV 미리 만들어 놓기
m_pDeviceContext->OMSetRenderTargets(1, m_pMinimapRTV.GetAddressOf(), m_pMinimapDSV.Get());

// 뷰포트 설정
D3D11_VIEWPORT vp{ 0.f, 0.f, 256.f, 256.f, 0.f, 1.f };
m_pDeviceContext->RSSetViewports(1, &vp);

m_pDeviceContext->ClearRenderTargetView(m_pMinimapRTV.Get(), clearColor);
m_pDeviceContext->ClearDepthStencilView(m_pMinimapDSV.Get(),
    D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);

// ... 미니맵용 카메라로 그리기 ...

// 원래대로 복구: 백버퍼 RTV + 메인 DSV + 메인 뷰포트
m_pDeviceContext->OMSetRenderTargets(1, m_pBackBufferRTV.GetAddressOf(), m_pDepthStencilView.Get());
m_pDeviceContext->RSSetViewports(1, &m_MainViewport);
m_pDeviceContext->PSSetShaderResources(0, 1, m_pMinimapSRV.GetAddressOf()); // 같은 텍스처를 SRV로(dx9에서의 SetTexture의 역할)
// ... 직교 투영으로 화면 구석에 사각형(RcTex 같은 버퍼) 그리기 ...
```
</details>























