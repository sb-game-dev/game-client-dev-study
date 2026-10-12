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
- 사용 방법 -> `WINMODE::FULL`

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
- map컨테이너의 Key를 더이상 w_char로 사용하지 않고 wstring을 사용하여 map컨테이너의 find함수를 사용하여 객체에 접근함
- 스마트 포인터를 사용하여 ReferenceCnt를 관리하기 때문에Safe_Release()를 사용하지 않음.

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


### 7일차 LevelManager

<details>
	<summary> Level </summary>

- Scene을 앞으로 Level이라고 부름
- Client에서 Level들을 생성해야 하므로 ENGINE_DLL매크로를 사용
- 오직 Level은 하나의 종류만 존재해야 함.

```cpp
#pragma once
#include "Engine_Defines.h"
#include "GameObject.h"
NS_BEGIN(Engine)
class ENGINE_DLL CLevel abstract //객체화 되지 않는다(x) 자식객체를 생성해야만 객체화 된다.(O)
{
protected:
	CLevel(ComPtr<ID3D11Device>pDevice, ComPtr<ID3D11DeviceContext> pContext);

public:
	virtual ~CLevel() = default;
public:
	virtual HRESULT Initialize();
	virtual void	Update(f32_t fDeltaTime);
	virtual HRESULT	Render();

protected:
	ComPtr<ID3D11Device>		m_pDevice = { nullptr };
	ComPtr<ID3D11DeviceContext> m_pContext = { nullptr };
};
NS_END
```
</details>

<details> 
	<summary> LevelManager </summary>

- 현재 존재하는 Level객체를 저장하고 enum값도 저장함.
- Level을 변경해주는 역할도 수행함.

> CLevel_Manager

```cpp
#pragma once
#include "Level.h"
NS_BEGIN(Engine)
class CLevel_Manager
{
private:
	CLevel_Manager();
public:
	~CLevel_Manager() = default;

public:
	HRESULT			Change_Level(int32_t iNewLevelIndex, shared_ptr<CLevel> pNewLevel);
	void			Update(f32_t fTimeDelta);
	HRESULT			Render();
private:
	int32_t						m_iCurrentLevelIndex = { -1 };
	shared_ptr<CLevel>			m_pCurrentLevel = { nullptr };
public:
	static unique_ptr<CLevel_Manager>	Create();
};
NS_END
```

> CLevel_Manager.cpp

```cpp
#include "Level_Manager.h"
#include "GameInstance.h"

CLevel_Manager::CLevel_Manager()
{
}
// 새로운 Level의 enum값과 객체를 전달받는다
// 기존Level이 있는 경우에는 Level의 자원을 정리(삭제)한다. -> Prototypes(원본 객체), GameObject(사본 객체) 삭제
HRESULT CLevel_Manager::Change_Level(int32_t iNewLevelIndex, shared_ptr<CLevel> pNewLevel)
{
	if (nullptr != m_pCurrentLevel)
	{
		m_pCurrentLevel.reset();
		/* 지금 삭제한 레벨의 자원을 정리한다. */
		CGameInstance::Get().Clear_Resources(m_iCurrentLevelIndex);
	}
	m_iCurrentLevelIndex = iNewLevelIndex;
	m_pCurrentLevel = pNewLevel;

	return S_OK;
}

void CLevel_Manager::Update(f32_t fTimeDelta)
{
	if (nullptr != m_pCurrentLevel)
		m_pCurrentLevel->Update(fTimeDelta);
}

HRESULT CLevel_Manager::Render()
{
	if (nullptr != m_pCurrentLevel)
		m_pCurrentLevel->Render();
	return S_OK;
}
unique_ptr<CLevel_Manager>	CLevel_Manager::Create()
{
	return unique_ptr<CLevel_Manager>(new CLevel_Manager());
}
```

</details>

<details>
	<summary> Client에서의 Level </summary>

> Level_Loading

- Level에 필요한 자원들(객체들)의 원본을 생성해주는 Level
- 생성하고자 하는 Level을 만들기 전에 무조건 먼저 거쳐야하는 Level
- 따라서 다음 Level의 enum값을 Create()함수의 매개변수로 받고 멤버로 저장한다.
- 멀티 쓰레드를 사용하여 객체들의 원본을 생성하는 Loader 클래스를 멤버로 갖는다.
- Loader클래스에서 원본 객체를 생성하는 작업이 끝나면 생성하고자하는 Level을 생성한다.

> Level_Logo

- Logo씬

> Level_GamePlay

- GamePlay씬

</details>



### 8일차 PrototypeManager

<details>
	<summary> 1. Prototype </summary>

> Prototype이란?

- 원형을 생성한 뒤 실제 사용은 복제본으로 사용을 하는 디자인 패턴의 종류
- Initialize에서 멤버변수 초기화등을 하는데 이때 파싱을 하게됨.
- 파일 읽기를 객체가 생성될 때마다 진행하면 비용이 크기 때문에 원본객체 하나를 생성할 때만 진행하면 객체를 복사할 때는 하지 않아도 되어서 효율적임.
- 객체 생성시 초기화 : Initialize_Prototype() / 객체 복제시 초기화 : Initialize()

> Prototype을 적용하는 방법

- Prototype(Engine) <- GameObject(Engine) <- Player(Client)
- Engine에 있는 Prototype,GameObject는 Clone만 있고 Client에 있는 Player는 Create와 Clone(override)이 모두 있다.
- 원형 Player를 생성할 때는 Create() 함수 호출 후 Initialize_Prototype()을 호출 한 뒤 Prototype_Manager에서 원형을 저장하게 됨(Prototype형으로 저장)
- 사본객체 Player를 복제할 때는 Clone() 함수 호출 후 Initialize()를 호출 한 뒤 Object_Manager에서 복제본을 저장하게 됨(Prototype형으로 저장)
- 오브젝트와 컴포넌트에 적용

</details>

<details>
	<summary> 2. Prototype_Manager </summary>

> Prototype_Manager란?

- 원형 객체들을 레벨별로 모아서 관리한다. (m_pPrototypes, AddPrototype())
	- 레벨별로 모아서 관리하기 때문에 Client에서 레벨을 몇 개 만들었는지 알아야하고 Create시 매개변수로 받아서 멤버로 저장하게 됨
	- 또한 레벨별로 map컨테이너를 만들기 위해 map컨테이너타입의 동적배열을 멤버로 가지고있고 Initialize에서 배열의 크기를 정해줌
- 원형 객체를 복제하여 사본 객체를 생성해준다. (Clone_Prototype())

> Prototype_Manager.h

```cpp
#pragma once
#include "Engine_Defines.h"
NS_BEGIN(Engine)

class CPrototype;
class CPrototype_Manager final
{
private:
	CPrototype_Manager();
public:
	~CPrototype_Manager() = default;

public:
	HRESULT Initialize(uint32_t iNumLevels);	// Manager 생성시 멤버변수(m_iNumLevels)초기화, 동적배열의 크기 설정
	HRESULT Add_Prototype(uint32_t iLevelIndex, const wstring_t& strPrototypeTag, shared_ptr<CPrototype> pPrototype);	// 동적배열에 원본객체 추가
	shared_ptr<CPrototype> Clone_Prototype(uint32_t iLevelIndex, const wstring_t& strPrototypeTag, void* pArg);			// 동적배열의 원본을 복사한 후 반환
	void Clear(uint32_t iClearLevelIndex);		// 매개변수로 받은 Level의 동적배열을 비워줌

private:
	uint32_t	m_iNumLevels = {};

private:
	typedef map<const wstring_t, shared_ptr<CPrototype>>	PROTOTYPES;
	// 동적 배열을 스마트 포인터로 선언
	shared_ptr<PROTOTYPES[]> m_pPrototypes = { nullptr };
private:
	shared_ptr<CPrototype> Find_Prototype(uint32_t iLevelIndex, const wstring_t& strPrototypeTag);
public:
	static unique_ptr<CPrototype_Manager> Create(uint32_t iNumLevels);	//Manager 생성시 Client쪽에서 Level이 몇 개 있는지 입력받음
};

NS_END

```

> Prototype_Manager.cpp

```cpp
#include "Prototype_Manager.h"
#include "Prototype.h"

CPrototype_Manager::CPrototype_Manager()
{
}

HRESULT CPrototype_Manager::Initialize(uint32_t iNumLevels)
{
	m_iNumLevels = iNumLevels;
	m_pPrototypes = make_shared<PROTOTYPES[]>(iNumLevels);	// 동적배열을 스마트 포인터로 생성해줌 c++17 버전부터 가능
	return S_OK;
}

HRESULT CPrototype_Manager::Add_Prototype(uint32_t iLevelIndex, const wstring_t& strPrototypeTag, shared_ptr<CPrototype> pPrototype)
{
	// 추가하고자하는 원형객체가 이미 있는지 확인
	if (iLevelIndex >= m_iNumLevels ||
		nullptr != Find_Prototype(iLevelIndex, strPrototypeTag))
		return E_FAIL;

	// 없는 경우 추가
	m_pPrototypes[iLevelIndex].emplace(strPrototypeTag, pPrototype);
	return S_OK;
}

shared_ptr<CPrototype> CPrototype_Manager::Clone_Prototype(uint32_t iLevelIndex, const wstring_t& strPrototypeTag, void* pArg)
{
	// 복제하고자하는 원형객체를 찾음
	auto        pPrototype = Find_Prototype(iLevelIndex, strPrototypeTag);
	if (nullptr == pPrototype)
		return nullptr;

	//원형 객체가 있는 경우 원형객체의 Clone을 호출하여 복제본을 생성
	auto        pCloneObject = pPrototype->Clone(pArg);
	if (nullptr == pCloneObject)
		return nullptr;

	// 복제본이 잘 생성되었다면 반환
	return pCloneObject;
}

void CPrototype_Manager::Clear(uint32_t iClearLevelIndex)
{
	if (iClearLevelIndex >= m_iNumLevels)
		return;
	// 객체들을 스마트포인터로 관리하기 때문에 메모리 해제를 스마트포인터에게 맡김(반복문으로 순회하며 .reset()을 하지 않아도 됨)
	m_pPrototypes[iClearLevelIndex].clear();
}

shared_ptr<CPrototype> CPrototype_Manager::Find_Prototype(uint32_t iLevelIndex, const wstring_t& strPrototypeTag)
{
	// 맵  특정 key값에 해당하는 원소가 있는지 확인
	auto Pair = m_pPrototypes[iLevelIndex].find(strPrototypeTag);

	if (Pair == m_pPrototypes[iLevelIndex].end())
		return nullptr;

	return Pair->second;
}

unique_ptr<CPrototype_Manager> CPrototype_Manager::Create(uint32_t iNumLevels)
{
	auto pInstance = unique_ptr<CPrototype_Manager> (new CPrototype_Manager());

	if (FAILED(pInstance->Initialize(iNumLevels)))
	{
		MSG_BOX("Failed to Created : CObject_Manager");
		pInstance.reset();
	}

	return pInstance;
}

```

</details>


### 9일차 Object_Manager & Layer

<details>
	<summary> 1. Object_Manager </summary>

> Object_Manager
- 사본객체들을 저장하는 레이어를 레벨별로 저장하고 관리함 (m_pLayers, Add_GameObject())
	- 레벨별로 레이어를 저장하기 때문에 Create시 Client에서 만든 Level의 개수를 전달받음.
 	- 또한 레벨별로 map컨테이너를 만들기 위해 map컨테이너타입의 동적배열을 멤버로 가지고있고 Initialize에서 배열의 크기를 정해줌.
- 저장된 레이어들의 Priority_Update(),Update(),Late_Update()를 호출함.

> Object_Manager.h

```cpp
#pragma once
#include "Engine_Defines.h"

NS_BEGIN(Engine)
class CGameObject;
class CObject_Manager
{
private:
	CObject_Manager();
public:
	~CObject_Manager() = default;
public:
	HRESULT	Initialize(uint32_t iNumLevels);
	HRESULT	Add_GameObject(uint32_t iPrototypeLevelIndex, const wstring_t& strPrototypeTag, 
						   uint32_t iLayerLevelIndex,	  const wstring_t& strLayerTag, const wstring_t& strGameObjectTag, void* pArg = nullptr);
	void		Priority_Update(f32_t fDeltaTime);
	void		Update(f32_t fDeltaTime);
	void		Late_Update(f32_t fDeltaTime);
	HRESULT		Render();
	void		Clear(uint32_t iClearLevelIndex);
	shared_ptr<CGameObject>			Find_GameObject(uint32_t iLayerLevelIndex, const wstring_t& strLayerTag, const wstring_t& strGameObjectTag);
private:
	uint32_t	m_iNumLevels = {};
	typedef map<const wstring_t, shared_ptr<class CLayer>> LAYERS;
	shared_ptr<LAYERS[]> m_pLayers = {};
private:
	shared_ptr<class CLayer> Find_Layer(uint32_t iLayerLevelIndex, const wstring_t& strLayerTag);
public:
	static unique_ptr<CObject_Manager> Create(uint32_t iNumLevels);
};
NS_END
```

> Object_Manager.cpp

```cpp
#include "Object_Manager.h"
#include "Layer.h"
#include "GameInstance.h"
CObject_Manager::CObject_Manager()
{
}
HRESULT CObject_Manager::Initialize(uint32_t iNumLevels)
{
	m_iNumLevels = iNumLevels;
	m_pLayers = make_shared<LAYERS[]>(iNumLevels);
	return S_OK;
}

HRESULT CObject_Manager::Add_GameObject(uint32_t iPrototypeLevelIndex, const wstring_t& strPrototypeTag, 
										uint32_t iLayerLevelIndex, const wstring_t& strLayerTag, const wstring_t& strGameObjectTag, 
										void* pArg)
{
	// Prototype_Manager에 접근하여 Loader에서 생성한 원본을 가져다 복제본을 생성함
	auto pCopyGameObject = dynamic_pointer_cast<CGameObject>(CGameInstance::Get().Clone_Prototype(iPrototypeLevelIndex, strPrototypeTag, pArg));
	if (nullptr == pCopyGameObject)
		return E_FAIL;

	// 생성한 복제본을 넣을 레이어를 검색
	auto pLayer = Find_Layer(iLayerLevelIndex, strLayerTag);

	// 만약 레이어가 없다면 
	if (nullptr == pLayer)
	{
		// 레이어를 생성한다
		pLayer = CLayer::Create();
		// 생성한 레이어에 복제본을 추가
		pLayer->Add_GameObject(strGameObjectTag, pCopyGameObject);
		// 생성한 레이어를 Layers에 등록
		m_pLayers[iLayerLevelIndex].emplace(strLayerTag, pLayer);
	}
	// 레이어가 있다면 생성한 복제본을 레이어에 추가
	else
		pLayer->Add_GameObject(strGameObjectTag, pCopyGameObject);

	return S_OK;
}
void CObject_Manager::Priority_Update(f32_t fDeltaTime)
{
	for (uint32_t i = 0; i < m_iNumLevels; ++i)
	{
		for (auto& Pair : m_pLayers[i])
		{
			if (nullptr != Pair.second)
				Pair.second->Priority_Update(fDeltaTime);
		}
	}
}
void CObject_Manager::Update(f32_t fDeltaTime)
{
	for (uint32_t i = 0; i < m_iNumLevels; ++i)
	{
		for (auto& Pair : m_pLayers[i])
		{
			if (nullptr != Pair.second)
				Pair.second->Update(fDeltaTime);
		}
	}
}
void CObject_Manager::Late_Update(f32_t fDeltaTime)
{
	for (uint32_t i = 0; i < m_iNumLevels; ++i)
	{
		for (auto& Pair : m_pLayers[i])
		{
			if (nullptr != Pair.second)
				Pair.second->Late_Update(fDeltaTime);
		}
	}
}
HRESULT	CObject_Manager::Render()
{
	for (uint32_t i = 0; i < m_iNumLevels; ++i)
	{
		for (auto& Pair : m_pLayers[i])
		{
			if (nullptr != Pair.second)
				if (FAILED(Pair.second->Render())) return E_FAIL;
		}
	}
	return S_OK;
}

void CObject_Manager::Clear(uint32_t iClearLevelIndex)
{
	if (iClearLevelIndex >= m_iNumLevels)
		return;
	m_pLayers[iClearLevelIndex].clear();
}

shared_ptr<CGameObject> CObject_Manager::Find_GameObject(uint32_t iLayerLevelIndex, const wstring_t& strLayerTag, const wstring_t& strGameObjectTag)
{
	auto pLayer = Find_Layer(iLayerLevelIndex, strLayerTag);
	if (nullptr == pLayer)
		return nullptr;

	auto pGameObject = pLayer->Find_GameObject(strGameObjectTag);
	if (nullptr == pGameObject)
		return nullptr;

	return pGameObject;
}

shared_ptr<CLayer> CObject_Manager::Find_Layer(uint32_t iLayerLevelIndex, const wstring_t& strLayerTag)
{
	auto iter = m_pLayers[iLayerLevelIndex].find(strLayerTag);
	if (iter == m_pLayers[iLayerLevelIndex].end())
		return nullptr;
	return iter->second;
}

unique_ptr<CObject_Manager> CObject_Manager::Create(uint32_t iNumLevels)
{
	auto pInstance = unique_ptr<CObject_Manager>(new CObject_Manager());
	if (FAILED(pInstance->Initialize(iNumLevels)))
	{
		MSG_BOX("Create Failed : CObject_Manager");
		pInstance.reset();
	}
	return pInstance;
}
```

</details>

<details>
	<summary> 2. Layer </summary>

> Layer란?

- 비슷한 기능을 하는 사본 객체를 모아놓는 그룹 
- 맵 컨테이너로 사본객체를 저장 (m_GameObjects, Add_GameObject())
- 사본객체의 Priority_Update(), Update(), Late_Update()를 호출

> Layer.h

```cpp
#pragma once
#include "Engine_Defines.h"
NS_BEGIN(Engine)
class CGameObject;
class CLayer
{
private:
	CLayer();
public:
	~CLayer() = default;

public:
	HRESULT		Add_GameObject(const wstring_t& strGameObjectTag ,shared_ptr<class CGameObject> pGameObject);
	void		Priority_Update(f32_t fTimeDelta);
	void		Update(f32_t fTimeDelat);
	void		Late_Update(f32_t fTimeDelta);
	HRESULT		Render();

	shared_ptr<CGameObject>	Find_GameObject(const wstring_t& strGameObjectTag);

private:
	map<const wstring_t, shared_ptr<CGameObject>>		m_GameObjects;

public:
	static shared_ptr<CLayer>	Create();
};

NS_END
```

> Layer.cpp

```cpp
#include "Layer.h"
#include "GameObject.h"
CLayer::CLayer()
{

}

HRESULT CLayer::Add_GameObject(const wstring_t& strGameObjectTag, shared_ptr<class CGameObject> pGameObject)
{
    m_GameObjects.emplace(strGameObjectTag, pGameObject);

    return S_OK;
}

void CLayer::Priority_Update(f32_t fTimeDelta)
{
    for (auto& Pair : m_GameObjects)
    {
        if (nullptr != Pair.second)
            Pair.second->Priority_Update(fTimeDelta);
    }
}
void CLayer::Update(f32_t fTimeDelta)
{
    for (auto& Pair : m_GameObjects)
    {
        if (nullptr != Pair.second)
            Pair.second->Update(fTimeDelta);
    }
}
void CLayer::Late_Update(f32_t fTimeDelta)
{
    for (auto& Pair : m_GameObjects)
    {
        if (nullptr != Pair.second)
            Pair.second->Late_Update(fTimeDelta);
    }
}
HRESULT	CLayer::Render()
{
    for (auto& Pair : m_GameObjects)
    {
        if (nullptr != Pair.second)
            if (FAILED(Pair.second->Render()))return E_FAIL;
    }
    return S_OK;
}
shared_ptr<CGameObject> CLayer::Find_GameObject(const wstring_t& strGameObjectTag)
{
    auto iter = m_GameObjects.find(strGameObjectTag);
    if (iter == m_GameObjects.end())
        return nullptr;
    return iter->second;
}
shared_ptr<CLayer>	CLayer::Create()
{
    return shared_ptr<CLayer>(new CLayer());
}

```

</details>

<details>
	<summary> 3. 원형 객체와 사본객체 생성 </summary>

> 원형 객체 생성

- 원형객체는 Level_Loading의 Loader에서 NextLevel에 맞는 원형 객체들을 생성 `CGameInstance::Get().Add_Prototype()`
- 원형 객체는 Add_Prototype() 함수를 호출하면 Prototype_Manager의 map컨테이너에 등록됨
- Add_Prototype()의 매개변수
	- `uint32_t iLevelIndex`
 	- `const wstring_t& strPrototypeTag`
  	- `void* pArg`

> 사본 객체 생성

- 사본 객체는 각 Level에서 원형 객체를 복제함	`CGameInstance::Get().Add_GameObject`
- 사본 객체는 Layer에 저장되고 Layer는 Object_Manager에 등록됨
- 원형 객체가 없다면 사본 객체는 생성되지 않음
- Add_GameObject()의 매개변수
	- `uint32_t iPrototypeLevelIndex`
	- `const wstring_t& strPrototypeTag`
 	- `uint32_t iLayerLevelIndex`
  	- `const wstring_t& strLayerTag`
  	- `const wstring_t& strGameObjectTag`
  	- `void* pArg = nullptr`

</details>
































