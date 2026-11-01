# MapTool 작업 설명서

> 이 문서만 보고 **지금의 맵툴(Hierarchy + Scene + Inspector, StaticProp 생성/삭제/편집)을 처음부터 똑같이 다시 만들 수 있도록** 작업 순서대로 정리한 설명서입니다.
> 각 단계는 **목표 → 수정 파일 → 코드 → 확인 방법 → 주의** 순서로 적었습니다.
> 마지막에 **사용한 ImGui 함수/위젯 정리**(부록 A)가 있습니다.

---

## 목차

- [0. 전체 그림](#0-전체-그림)
- [1단계. 프로젝트 만들기 + 빈 창 띄우기](#1단계-프로젝트-만들기--빈-창-띄우기)
- [2단계. ImGui 붙이기 + 메뉴바](#2단계-imgui-붙이기--메뉴바)
- [3단계. 창 3개 — Hierarchy / Scene / Inspector](#3단계-창-3개--hierarchy--scene--inspector)
- [4단계. Scene 창에 게임 화면 넣기 (RTT)](#4단계-scene-창에-게임-화면-넣기-rtt)
- [5단계. 맵툴 카메라 + SkyBox](#5단계-맵툴-카메라--skybox)
- [6단계. 배치 객체 만들기 — CStaticProp + Hierarchy 생성 메뉴](#6단계-배치-객체-만들기--cstaticprop--hierarchy-생성-메뉴)
- [7단계. Hierarchy 목록 + 선택](#7단계-hierarchy-목록--선택)
- [8단계. 삭제](#8단계-삭제)
- [9단계. Inspector — 이름 + Transform](#9단계-inspector--이름--transform)
- [10단계. Inspector — Static Prop (Mesh / Texture 교체)](#10단계-inspector--static-prop-mesh--texture-교체)
- [11. 현재 상태와 남은 작업](#11-현재-상태와-남은-작업)
- [부록 A. 사용한 ImGui 함수/위젯 정리](#부록-a-사용한-imgui-함수위젯-정리)
- [부록 B. 커밋 기록](#부록-b-커밋-기록)
- [부록 C. 자주 겪는 문제](#부록-c-자주-겪는-문제)

---

## 0. 전체 그림

### 폴더 구조

```
Duckov/Game/
├─ Engine/        엔진 DLL (빌드하면 EngineSDK/Inc, EngineSDK/Lib, 각 Bin으로 복사)
├─ EngineSDK/     Inc(헤더), Lib(Engine.lib)
├─ Client/        게임. 맵툴이 Client의 cpp를 같이 컴파일해서 씀 (StaticProp, MapObject, SkyBox ...)
└─ MapTool/
   ├─ Default/    Default.cpp(WinMain), Default.vcxproj, imgui.ini
   ├─ ImGui/      imgui 소스 (imgui.cpp, imgui_draw.cpp, imgui_widgets.cpp, imgui_tables.cpp,
   │              imgui_demo.cpp, imgui_impl_win32.cpp, imgui_impl_dx11.cpp + 헤더)
   ├─ Public/     MapTool_Defines.h, ToolMainApp.h, Level_MapTool.h, MapTool_Cam.h,
   │              EditorUI.h, EditorUI_Defines.h, EditorUI_Utils.h,
   │              Panel.h, Panel_Hierarchy.h, Panel_Scene.h, Panel_Inspector.h
   ├─ Private/    ToolMainApp.cpp, Level_MapTool.cpp, MapTool_Cam.cpp,
   │              EditorUI.cpp, Panel_Hierarchy.cpp, Panel_Scene.cpp, Panel_Inspector.cpp
   └─ Bin/        Engine.dll, Shader/ (Client/Bin/Shader에서 빌드 후 복사)
```

### 클래스 역할

| 클래스 | 위치 | 역할 |
|---|---|---|
| `wWinMain` / `WndProc` | MapTool/Default/Default.cpp | 창 생성, 메시지 루프(60fps), ImGui에 메시지 먼저 전달 |
| `CToolMainApp` | MapTool | 엔진 초기화, ImGui 초기화/프레임 시작/렌더, `CEditorUI` 소유, 레벨 시작 |
| `CEditorUI` | MapTool | 에디터 화면 전체: 메뉴바, 레이아웃 계산, 공용 상태(`EDITOR_CONTEXT`) 보관, 패널 3개 소유 |
| `CPanel_Hierarchy` / `CPanel_Scene` / `CPanel_Inspector` | MapTool | 각 창 하나씩 (`CPanel` 상속, Context를 참조로 공유) |
| `CLevel_MapTool` | MapTool | 툴 레벨: SkyBox, 맵툴 카메라, StaticProp 원형 등록 |
| `CMapTool_Cam` | MapTool (namespace Client) | 우클릭+WASD+마우스 자유 카메라 |
| `CMapObject` | Client | 배치 가능한 모든 객체의 부모. DESC로 위치/회전/크기/메시/텍스처를 받음 |
| `CStaticProp` | Client | 그리기만 하는 구조물. 메시/텍스처를 **경로 문자열**로 받아 교체 가능 |
| `CAsset_Manager` | Engine | "경로로 원형 찾기 → 없으면 로드해서 등록" 캐시 |
| `CRenderer` | Engine | 씬을 텍스처(RTT)에 그림 → 툴은 그 SRV를 ImGui::Image로 표시 |

### 한 프레임의 흐름

```
wWinMain 루프 (1/60초마다)
 └ CToolMainApp::Update
     ├ Begin_ImGui()          ImGui_ImplDX11_NewFrame → ImGui_ImplWin32_NewFrame → ImGui::NewFrame
     ├ CEditorUI::Update()    메뉴바 → 레이아웃 계산 → 패널 Render (Hierarchy → Scene → Inspector)   (여기서 생성/삭제/편집)
     ├ Sync_SceneView()       Scene 창 포커스 여부를 카메라에 전달
     └ Update_Engine()        Priority_Update(Remove_Dead 먼저) → Update → Late_Update(RenderGroup 등록)
 └ CToolMainApp::Render
     ├ Clear 백버퍼/깊이
     ├ Draw()                 Renderer가 씬을 SceneRTV(텍스처)에 그림. 백버퍼에는 안 그림
     ├ Render_ImGui()         ImGui::Render → ImGui_ImplDX11_RenderDrawData (Scene 창에 SceneSRV가 보임)
     └ Present
```

### 설계 원칙 (계획서 MapTool_Plan.md 요약)

- **프로토타입 Clone + DESC**: "어떤 클래스인가" = 프로토타입 태그, "어떤 값으로 만들까" = DESC
- 구조물은 클래스 하나(`CStaticProp`) + **메시 경로 문자열**(`"builtin/cube"` → 나중에 `"model/xxx.fbx"`)
- 로직 있는 객체는 `CMapObject`를 상속 (나중 단계)
- **ImGui 코드는 MapTool에만.** Engine/Client 클래스에는 넣지 않는다 (타입별 UI는 툴에서 `dynamic_pointer_cast`로 분기)
- 회전은 행렬이 아니라 **각도(도)로 보관** (행렬에서 다시 뽑으면 값이 튐)
- Engine 헤더 수정 → **Engine 먼저 빌드** → MapTool / Client 빌드

---

## 1단계. 프로젝트 만들기 + 빈 창 띄우기

**목표**: 솔루션에 MapTool 실행 프로젝트를 추가하고, 엔진을 초기화해서 빈 창이 60fps로 돌아가게 한다.

### 1-1. 프로젝트 추가

- `Game.sln`에 Windows 데스크톱 애플리케이션 프로젝트 추가 → 폴더 `MapTool/Default/`, 프로젝트 파일 `Default.vcxproj`, 출력 이름 `MapTool.exe`
- 출력 폴더(작업 디렉터리)를 `MapTool/Bin/`으로. (셰이더 경로 `../Bin/Shader/...`, 리소스 경로 `../../../Resource/...`가 이 기준)

### 1-2. 프로젝트 속성 (Debug/Release 둘 다)

| 항목 | 값 |
|---|---|
| C/C++ → 추가 포함 디렉터리 | `../Public;../ImGui;../../Client/Public;../../EngineSDK/Inc/;../../ThirdParty;` |
| C/C++ → 전처리기 정의 | `_DEBUG(또는 NDEBUG);_MAPTOOL;_WINDOWS;` |
| C/C++ → 언어 표준 | `stdcpp20` |
| 링커 → 추가 라이브러리 디렉터리 | `../../EngineSDK/Lib/` |
| 링커 → 추가 종속성 | `Engine.lib;d3dcompiler.lib;` |
| 빌드 이벤트 → 빌드 후 이벤트 | `xcopy "$(SolutionDir)Client\Bin\Shader" "$(SolutionDir)MapTool\Bin\Shader\" /E /Y /I` |

- `MapTool/Bin/`에 `Engine.dll`이 있어야 실행됨 (Engine 빌드 후 복사되도록 Engine 쪽 빌드 후 이벤트에 MapTool/Bin 추가)
- 프로젝트 종속성: MapTool → Engine (Engine이 먼저 빌드되게)

- 빌드 후 xcopy로 `Client/Bin/Shader`가 `MapTool/Bin/Shader`로 복사된다. 엔진 Renderer가 시작할 때 `../Bin/Shader/Shader_FullScreen.hlsl`을 컴파일하므로 **1단계부터 필요**하다

### 1-3. Client 코드 가져오기
- 맵툴은 Client 클래스를 **소스째로 같이 컴파일**한다 (vcxproj에 `..\..\Client\Private\XXX.cpp`를 추가)
- 단계마다 필요한 파일만 추가하면 된다

| 단계 | 추가하는 Client cpp |
|---|---|
| 5단계 | `SkyBox.cpp` |
| 6단계 | `MapObject.cpp`, `StaticProp.cpp` |

- 실제 프로젝트에는 `Free_Cam.cpp`, `BackGround.cpp`, `Cube.cpp` 등 Client 파일이 더 들어 있지만 맵툴 기능에는 필요 없다
- `_MAPTOOL` 정의로 툴에서만 다르게 동작해야 하는 코드를 분기할 수 있음 (최종 목표는 분기 없이 DESC로 해결)

### 1-4. MapTool_Defines.h

```cpp
#pragma once
#include "Client_Defines.h"
namespace MapTool
{
    static constexpr uint32_t g_iToolWinSizeX = 1600;
    static constexpr uint32_t g_iToolWinSizeY = 900;
};

using namespace std;
using namespace Client;
using namespace Engine;
using namespace MapTool;
```

### 1-5. 레벨 enum에 MAPTOOL 추가 (Client_Defines.h)

```cpp
enum class LEVEL { STATIC, LOADING, LOGO, GAMEPLAY, MAPTOOL, END };
```

**확인**: 빈 창이 뜨고 빌드 에러가 없다.

### 1-6. Default.cpp (WinMain / 창 / 메시지)

```cpp
#include "framework.h"
#include "Default.h"
#include "ToolMainApp.h"

#define MAX_LOADSTRING 100
// 전역 변수:
HINSTANCE hInst;            // 현재 인스턴스입니다.
HWND      g_hWnd;
WCHAR szTitle[MAX_LOADSTRING];           // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];     // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
#ifdef _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DEFAULT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance(hInstance, nCmdShow))
        return FALSE;

    MSG msg{};

    unique_ptr<CToolMainApp> pToolMainApp = CToolMainApp::Create();
    if (nullptr == pToolMainApp)
        return FALSE;
    if (FAILED(CGameInstance::Get().Add_Timer(TEXT("Timer_Default"))))
        return FALSE;
    if (FAILED(CGameInstance::Get().Add_Timer(TEXT("Timer_60"))))
        return FALSE;

    f32_t fTimeDeltaAcc = {};
    bool_t bDone = false;
    while (!bDone)
    {
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (WM_QUIT == msg.message)
                bDone = true;
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
        }
        if (bDone)
            break;

        CGameInstance::Get().Update_TimeDelta(TEXT("Timer_Default"));
        fTimeDeltaAcc += CGameInstance::Get().Get_TimeDelta(TEXT("Timer_Default"));
        if (fTimeDeltaAcc >= 1.f / 60.f)                       // 60fps 고정
        {
            CGameInstance::Get().Update_TimeDelta(TEXT("Timer_60"));
            pToolMainApp->Update(CGameInstance::Get().Get_TimeDelta(TEXT("Timer_60")));
            pToolMainApp->Render();
            fTimeDeltaAcc = 0.f;
        }
    }

    pToolMainApp.reset();
    return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex{};

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DEFAULT));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = 0;                      // 윈도우 기본 메뉴 제거 (2단계에서 ImGui 메뉴바를 씀)
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance;  // 인스턴스 핸들을 전역 변수에 저장합니다.

    // 클라이언트 영역이 정확히 1600x900이 되도록 DPI를 고려해서 창 크기 계산
    RECT rc{ 0, 0, g_iToolWinSizeX, g_iToolWinSizeY };
    AdjustWindowRectExForDpi(&rc, WS_OVERLAPPEDWINDOW, FALSE, 0, GetDpiForSystem());

    const int iWinW = rc.right - rc.left;
    const int iWinH = rc.bottom - rc.top;

    // 작업 영역(작업 표시줄 제외) 가운데에 배치
    RECT rcWork{};
    SystemParametersInfoW(SPI_GETWORKAREA, 0, &rcWork, 0);
    const int iPosX = rcWork.left + ((rcWork.right - rcWork.left) - iWinW) / 2;
    const int iPosY = rcWork.top + ((rcWork.bottom - rcWork.top) - iWinH) / 2;

    HWND hWnd = CreateWindowW(szWindowClass, L"MapTool", WS_OVERLAPPEDWINDOW,
        iPosX, iPosY, iWinW, iWinH, nullptr, nullptr, hInstance, nullptr);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    g_hWnd = hWnd;
    return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_KEYDOWN:
        if (VK_ESCAPE == wParam)
            DestroyWindow(hWnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
```

- `g_hWnd`, `hInst`는 `Client_Defines.h`에서 `extern`으로 선언된 전역 → 여기서 정의
- 엔진은 `CToolMainApp::Create()` 안에서 초기화되므로, 타이머(`Add_Timer`)는 그 **뒤**에 추가

### 1-7. CToolMainApp (엔진 초기화 + 프레임)

**ToolMainApp.h**

```cpp
#pragma once
#include "MapTool_Defines.h"

NS_BEGIN(MapTool)
class CToolMainApp final
{
private:
	CToolMainApp() = default;
public:
	~CToolMainApp();

public:
	HRESULT		Initialize();
	void		Update(f32_t fDeltaTime);
	HRESULT		Render();

private:
	ComPtr<ID3D11Device>				m_pDevice = { nullptr };
	ComPtr<ID3D11DeviceContext>			m_pContext = { nullptr };

public:
	static		unique_ptr<CToolMainApp>		Create();
};

NS_END
```

**ToolMainApp.cpp**

```cpp
#include "MapTool_Defines.h"
#include "ToolMainApp.h"
#include "Level_MapTool.h"

CToolMainApp::~CToolMainApp()
{
    CGameInstance::Get().Release_Engine();
}

HRESULT CToolMainApp::Initialize()
{
    ENGINE_DESC EngineDesc{};
    EngineDesc.hWnd = g_hWnd;
    EngineDesc.iWinSizeX = g_iToolWinSizeX;
    EngineDesc.iWinSizeY = g_iToolWinSizeY;
    EngineDesc.eWinMode = WINMODE::WIN;
    EngineDesc.iNumLevels = ETOUI(LEVEL::END);
    EngineDesc.hInstance = hInst;

    if (FAILED(CGameInstance::Get().Initialize_Engine(EngineDesc, m_pDevice, m_pContext)))
        return E_FAIL;

    // 툴 레벨 시작
    if (FAILED(CGameInstance::Get().Change_Level(static_cast<int>(LEVEL::MAPTOOL),
        CLevel_MapTool::Create(m_pDevice, m_pContext))))
        return E_FAIL;

    return S_OK;
}

void CToolMainApp::Update(f32_t fDeltaTime)
{
    CGameInstance::Get().Update_Engine(fDeltaTime);
}

HRESULT CToolMainApp::Render()
{
    // Clear
    float4_t    vClearColor = float4_t{ 0.f, 0.f, 0.f, 1.f };
    CGameInstance::Get().Clear_BackBuffer_View(&vClearColor);
    CGameInstance::Get().Clear_DepthStencil_View();

    CGameInstance::Get().Bind_PipeLine_Vertex_ShaderResource(1);
    CGameInstance::Get().Bind_PipeLine_Pixel_ShaderResource(1);
    CGameInstance::Get().Bind_PipeLine_Geometry_ShaderResource(1);

    CGameInstance::Get().Draw();

    CGameInstance::Get().Present();
    return S_OK;
}

unique_ptr<CToolMainApp> CToolMainApp::Create()
{
    auto    pInstance = unique_ptr<CToolMainApp>(new CToolMainApp());

    if (FAILED(pInstance->Initialize()))
    {
        MSG_BOX("Failed to Created : CToolMainApp");
        pInstance.reset();
    }
    return pInstance;
}
```

### 1-8. CLevel_MapTool (빈 레벨)

**Level_MapTool.h**

```cpp
#pragma once
#include "MapTool_Defines.h"
#include "Level.h"

NS_BEGIN(MapTool)
class CLevel_MapTool final : public CLevel
{
private:
	CLevel_MapTool(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	~CLevel_MapTool() = default;

public:
	virtual		HRESULT		Initialize() override;
	virtual		void		Update(f32_t fDeltaTime) override;
	virtual		HRESULT		Render() override;

public:
	static shared_ptr<CLevel_MapTool> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
};
NS_END
```

**Level_MapTool.cpp**

```cpp
#include "Level_MapTool.h"

CLevel_MapTool::CLevel_MapTool(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    :CLevel{ pDevice,pContext }
{
}

HRESULT CLevel_MapTool::Initialize()
{
    if (FAILED(__super::Initialize()))
        return E_FAIL;

    SetWindowText(g_hWnd, L"MapTool_Level");

    return S_OK;
}

void CLevel_MapTool::Update(f32_t fDeltaTime)
{
    __super::Update(fDeltaTime);
}

HRESULT CLevel_MapTool::Render()
{
    if (FAILED(__super::Render()))
        return E_FAIL;
    return S_OK;
}

shared_ptr<CLevel_MapTool> CLevel_MapTool::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto pInstance = shared_ptr<CLevel_MapTool>(new CLevel_MapTool(pDevice, pContext));
    if (FAILED(pInstance->Initialize()))
        pInstance.reset();

    return pInstance;
}
```

- vcxproj: `MapTool_Defines.h`, `ToolMainApp.h/.cpp`, `Level_MapTool.h/.cpp`, `Default.cpp` 등록

**실행 결과**
- 작업 영역 가운데에 1600x900 창이 뜨고, 제목 표시줄이 `MapTool_Level`로 바뀐다
- 창 전체가 **밝은 회색**(0.75)이다 — 엔진 Renderer가 씬을 씬 텍스처에 그린 뒤 백버퍼로 복사하기 때문 (4단계에서 자세히)
- ESC를 누르면 꺼진다

**주의**
- 실행 시 Engine.dll이 없다고 나오면 `MapTool/Bin/Engine.dll` 복사 확인
- 시작하자마자 꺼지면 `MapTool/Bin/Shader/`에 셰이더가 복사됐는지 확인 (Renderer 초기화 실패)

---

## 2단계. ImGui 붙이기 + 메뉴바

**목표**: 툴 창 위에 ImGui가 그려지고 마우스/키보드 입력이 ImGui로 들어간다. 에디터 UI 클래스(`CEditorUI`)를 만들고 메뉴바부터 띄운다.

### 2-0. ImGui가 동작하는 방식 (먼저 알아 둘 것)

ImGui는 **즉시 모드(Immediate Mode) GUI**다. 일반적인 UI 라이브러리처럼 "버튼 객체를 만들어 두고 이벤트를 연결하는" 방식이 아니다.

| | 일반 UI (유지 모드) | ImGui (즉시 모드) |
|---|---|---|
| 위젯 만들기 | 시작할 때 버튼 객체를 한 번 만들어 보관 | **매 프레임** `ImGui::Button("저장")`을 다시 호출 |
| 클릭 처리 | 클릭 이벤트 콜백을 등록 | 호출한 그 자리에서 **반환값**(`true` = 이번 프레임에 눌림)으로 처리 |
| 상태(값) | 위젯이 값을 들고 있음 | **우리 변수**를 넘기고, ImGui는 그걸 읽고/바꿀 뿐 |

```cpp
// 매 프레임 실행되는 코드
if (ImGui::Button("저장"))        // 1) 버튼을 그리고  2) 이번 프레임에 눌렸으면 true
    Save();
ImGui::DragFloat("속도", &m_fSpeed);   // m_fSpeed는 우리 멤버. ImGui는 매 프레임 그 값을 보여 주고, 드래그하면 바꿔 줌
```

알아 둘 규칙
1. **한 프레임의 흐름**: `NewFrame()` → (위젯 함수들 호출) → `Render()`. 위젯 함수는 화면에 바로 그리지 않고 **그리기 명령만 쌓는다.** 실제로 GPU에 그리는 건 `Render()` 뒤의 `ImGui_ImplDX11_RenderDrawData()`
2. **Begin/End 짝**: 창, 메뉴, 팝업, 콤보는 `BeginXXX()` ~ `EndXXX()` 사이에 내용을 넣는다. 짝을 맞추는 규칙이 두 가지라 헷갈리기 쉽다
   - `Begin()`(창)은 반환값과 **상관없이 항상** `End()`
   - `BeginMenu / BeginMainMenuBar / BeginPopup* / BeginCombo`는 **`true`일 때만** `EndXXX()`
3. **라벨 = ID**: `Button("저장")`의 `"저장"`은 화면 글자이면서 ImGui가 위젯을 구분하는 ID다. 같은 창 안에서 라벨이 같으면 서로 헷갈린다 → 글자는 같게 보이고 ID만 다르게 하려면 `"저장##1"`, `"저장##2"`처럼 `##` 뒤에 구분자를 붙인다 (`##` 뒤는 화면에 안 보임)
4. **"바로 앞 위젯" 함수**: `IsItemHovered()`, `GetItemRectMin()`, `BeginPopupContextItem()`처럼 이름에 `Item`이 들어간 함수는 **바로 앞에 그린 위젯 하나**를 기준으로 답한다. `IsWindowFocused()`처럼 `Window`가 들어간 함수는 **지금 Begin~End 중인 창**을 기준으로 답한다
5. **문자열은 UTF-8 `const char*`**: 엔진의 `wstring`은 그대로 못 넘기고 변환해야 한다 (7단계 `To_UTF8`)

### 2-1. ImGui 소스 추가

- `MapTool/ImGui/`에 아래 파일을 넣고 vcxproj에 추가
  - `imgui.cpp, imgui_draw.cpp, imgui_widgets.cpp, imgui_tables.cpp, imgui_demo.cpp`
  - `imgui_impl_win32.cpp/.h, imgui_impl_dx11.cpp/.h`
  - `imgui.h, imconfig.h, imgui_internal.h, imstb_rectpack.h, imstb_textedit.h, imstb_truetype.h`
- ImGui cpp 파일들은 **미리 컴파일된 헤더 사용 안 함**으로 설정 (pch를 쓰는 경우)

- 각 ImGui cpp의 속성 → C/C++ → 명령줄 → 추가 옵션에 `/utf-8` (Debug/Release 둘 다)

### 2-2. Default.cpp — ImGui에 메시지 전달

맨 위 include와 선언 추가

```cpp
#include "imgui.h"              // ImGui::GetIO()를 사용하기 위해
#include "imgui_impl_win32.h"
#include "framework.h"
#include "Default.h"
#include "ToolMainApp.h"

// ... 전역 변수, 함수 선언 ...

// imgui_impl_win32.h에서 #if 0으로 막혀 있으므로 직접 선언
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
```

`wWinMain`의 `UNREFERENCED_PARAMETER` 다음, `LoadStringW` 전에 추가

```cpp
    // DPI 인식 설정 (창을 만들기 전에)
    ImGui_ImplWin32_EnableDpiAwareness();
```

`WndProc` — **ImGui가 먼저** 메시지를 받는다

```cpp
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // ImGui가 먼저 메시지를 받음. true면 ImGui가 처리한 것
    if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
        return true;

    switch (message)
    {
    case WM_KEYDOWN:
        // ImGui 입력창에서 ESC를 눌러도 툴이 꺼지지 않게
        if (VK_ESCAPE == wParam && (nullptr == ImGui::GetCurrentContext() || !ImGui::GetIO().WantCaptureKeyboard))
            DestroyWindow(hWnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
```

**처음 나오는 ImGui 함수 / 값**

| 함수 / 값 | 하는 일 | 자세히 |
|---|---|---|
| `ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam)` | 윈도우 메시지를 ImGui에 전달 | 마우스 이동(`WM_MOUSEMOVE`), 버튼(`WM_LBUTTONDOWN/UP`, `WM_RBUTTONDOWN/UP`), 휠, 키보드, 글자 입력(`WM_CHAR`), 포커스 메시지를 받아서 ImGui 입력 상태(`ImGuiIO`)에 쌓는다. ImGui가 메시지를 직접 처리했으면(예: 커서 모양 바꾸기) `0`이 아닌 값을 돌려준다. **헤더에서 `#if 0`으로 막혀 있어서** cpp에 `extern`으로 직접 선언해야 한다 |
| `ImGui_ImplWin32_EnableDpiAwareness()` | 프로그램을 DPI 인식 모드로 설정 | 윈도우 배율이 125%, 150%일 때 OS가 창을 비트맵으로 늘려서 **흐릿하게** 보이게 하는 것을 막는다. 창을 만들기 **전에** 불러야 효과가 있다 |
| `ImGui::GetCurrentContext()` | 지금 ImGui 컨텍스트(포인터)를 돌려줌 | `CreateContext()` 전이나 `DestroyContext()` 뒤에는 `nullptr`. WndProc은 ImGui 초기화 **전에도**(창 생성 중) 메시지를 받기 때문에, `GetIO()`를 부르기 전에 컨텍스트가 있는지 먼저 확인한다 |
| `ImGui::GetIO()` | ImGui 전체의 입출력 정보(`ImGuiIO&`)를 돌려줌 | 설정(`ConfigFlags`, 폰트), 입력(`DisplaySize`, `DeltaTime`, 마우스 위치/버튼, 키), 출력(`WantCaptureKeyboard` 등)이 들어 있는 **게시판**. 창과는 관계없다 |
| `io.WantCaptureKeyboard` | ImGui가 키보드를 쓰는 중인가 | 입력칸에 글자를 치는 중이거나 키보드 내비게이션 중이면 `true`. 이때는 키 입력을 게임/툴이 쓰지 말라는 신호 → ESC로 툴이 꺼지지 않게 하는 데 사용 |

### 2-3. CEditorUI — 메뉴바

에디터 화면 전체를 맡는 클래스. 이번 단계에서는 메뉴바만 그린다. (3단계에서 창 3개를 붙인다)

**EditorUI.h**

```cpp
#pragma once
#include "MapTool_Defines.h"

NS_BEGIN(MapTool)
// 에디터 화면 전체
class CEditorUI final
{
private:
	CEditorUI() = default;
public:
	~CEditorUI() = default;

public:
	HRESULT		Initialize();
	void		Update(const f32_t& fDeltaTime);

private:
	f32_t		m_fMenuBarHeight = {};
	bool_t		m_bShowDemo = { false };

private:
	void		Render_MenuBar();

public:
	static unique_ptr<CEditorUI> Create();
};

NS_END
```

**EditorUI.cpp**

```cpp
#include "imgui.h"
#include "EditorUI.h"

HRESULT CEditorUI::Initialize()
{
	return S_OK;
}

void CEditorUI::Update(const f32_t& fDeltaTime)
{
    Render_MenuBar();

    if (m_bShowDemo)
        ImGui::ShowDemoWindow(&m_bShowDemo);
}

void CEditorUI::Render_MenuBar()
{
    // 화면 맨 위에 꽉 차게 붙는 메뉴 바.
    // 일반 창(Begin) 안이 아니라 바깥에서 호출한다.
    // 일반 창(Begin)과는 다르게 false를 반환하면 EndMainMenuBar를 호출하지 않고 빠져나간다.
    if (!ImGui::BeginMainMenuBar())
        return;

    m_fMenuBarHeight = ImGui::GetWindowHeight();      // 3단계 레이아웃에서 사용

    // 펼쳐지는 메뉴
    // true일 때만 EndMenu를 호출.
    if (ImGui::BeginMenu("File"))
    {
        // MenuItem(라벨, 단축키표시, 선택됨, 활성화);
        // 단축키는 오른쪽에 보이는 글자일 뿐이고 실제 동작은 따로 만들어야 함.
        ImGui::MenuItem("New Scene", nullptr, false, false);        // 저장/불러오기 전까지 비활성
        ImGui::MenuItem("Open Scene", "Ctrl + O", false, false);
        ImGui::MenuItem("Save", "Ctrl + S", false, false);
        ImGui::MenuItem("Save As", nullptr, false, false);
        ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("View"))
    {
        ImGui::MenuItem("ImGui Demo", nullptr, &m_bShowDemo);       // bool* 를 넘기면 체크 토글
        ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
}

unique_ptr<CEditorUI> CEditorUI::Create()
{
    auto pInstance = unique_ptr<CEditorUI>(new CEditorUI());
    if (FAILED(pInstance->Initialize()))
    {
        MSG_BOX("Failed to Created : CEditorUI");
        pInstance.reset();
    }
    return pInstance;
}
```

**처음 나오는 ImGui 함수**

| 함수 | 하는 일 | 자세히 |
|---|---|---|
| `ImGui::BeginMainMenuBar()` | 화면(프로그램 창) 맨 위에 꽉 차는 메뉴바를 시작 | 일반 창(`Begin`) **바깥**에서 부른다. 메뉴바를 그릴 수 있으면 `true` → **`true`일 때만** `EndMainMenuBar()` |
| `ImGui::EndMainMenuBar()` | 메뉴바 끝 | `BeginMainMenuBar()`가 `true`였을 때만 호출 |
| `ImGui::GetWindowHeight()` | **지금 그리고 있는 창**의 높이 | 메뉴바도 ImGui 내부에서는 창 하나라서, `BeginMainMenuBar()` 안에서 부르면 메뉴바 높이가 나온다 (기본 폰트 기준 약 19). 3단계에서 세 창을 그 아래부터 놓는 데 사용 |
| `ImGui::BeginMenu("File")` | 메뉴바의 펼침 메뉴 하나 | 메뉴가 **펼쳐져 있는 동안** `true` → 그 안에 `MenuItem`을 넣고, **`true`일 때만** `EndMenu()` |
| `ImGui::EndMenu()` | 펼침 메뉴 끝 | `BeginMenu()`가 `true`였을 때만 호출 |
| `ImGui::MenuItem(라벨, 단축키글자, 선택됨, 활성화)` | 메뉴 항목 하나 | **클릭한 프레임에 `true`.** 두 번째 인자는 오른쪽에 회색으로 보이는 **글자일 뿐** 실제 단축키 동작은 따로 만들어야 한다. 네 번째 인자가 `false`면 회색 비활성(클릭 불가) |
| `ImGui::MenuItem(라벨, nullptr, &bool변수)` | 체크 표시가 붙는 토글 항목 | `bool*`를 넘기면 클릭할 때마다 ImGui가 그 변수를 `true/false`로 뒤집고, 켜져 있으면 체크 표시를 그린다 |
| `ImGui::ShowDemoWindow(&bool변수)` | ImGui 데모(예제) 창 | 모든 위젯 예제가 들어 있는 참고용 창. 코드는 `imgui_demo.cpp`. `bool*`를 넘기면 창에 X 버튼이 생기고 누르면 ImGui가 변수를 `false`로 바꾼다 |

### 2-4. CToolMainApp — ImGui 초기화 / 프레임 / 종료

**ToolMainApp.h** (전체)

```cpp
#pragma once
#include "MapTool_Defines.h"

NS_BEGIN(MapTool)
class CEditorUI;
class CToolMainApp final
{
private:
	CToolMainApp() = default;
public:
	~CToolMainApp();

public:
	HRESULT		Initialize();
	void		Update(f32_t fDeltaTime);
	HRESULT		Render();

private:
	ComPtr<ID3D11Device>				m_pDevice = { nullptr };
	ComPtr<ID3D11DeviceContext>			m_pContext = { nullptr };

	unique_ptr<CEditorUI>				m_pEditorUI = { nullptr };
	bool_t								m_bReadyImGui = { false };

private:
	HRESULT								Ready_ImGui();
	HRESULT								Begin_ImGui();
	HRESULT								Render_ImGui();
	HRESULT								Shutdown_ImGui();

public:
	static		unique_ptr<CToolMainApp>		Create();
};

NS_END
```

**ToolMainApp.cpp** — include

```cpp
#include "imgui.h"
#include "MapTool_Defines.h"
#include "ToolMainApp.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include "Level_MapTool.h"
#include "EditorUI.h"
```

**소멸자** — 툴 → ImGui → 엔진 순서로 정리

```cpp
CToolMainApp::~CToolMainApp()
{
    m_pEditorUI.reset();        // 툴 먼저
    Shutdown_ImGui();           // ImGui 정리
    CGameInstance::Get().Release_Engine();   // 엔진은 마지막
}
```

**Initialize** — 엔진 → ImGui → CEditorUI → 레벨 순서

```cpp
HRESULT CToolMainApp::Initialize()
{
    ENGINE_DESC EngineDesc{};
    EngineDesc.hWnd = g_hWnd;
    EngineDesc.iWinSizeX = g_iToolWinSizeX;
    EngineDesc.iWinSizeY = g_iToolWinSizeY;
    EngineDesc.eWinMode = WINMODE::WIN;
    EngineDesc.iNumLevels = ETOUI(LEVEL::END);
    EngineDesc.hInstance = hInst;

    if (FAILED(CGameInstance::Get().Initialize_Engine(EngineDesc, m_pDevice, m_pContext)))
        return E_FAIL;

    if (FAILED(Ready_ImGui()))                  // 추가
        return E_FAIL;

    m_pEditorUI = CEditorUI::Create();          // 추가
    if (nullptr == m_pEditorUI)
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Change_Level(static_cast<int>(LEVEL::MAPTOOL),
        CLevel_MapTool::Create(m_pDevice, m_pContext))))
        return E_FAIL;

    return S_OK;
}
```

**Ready_ImGui** — 컨텍스트 → IO 설정 → 스타일 → 백엔드 (폰트는 따로 넣지 않으면 ImGui 기본 폰트 사용)

```cpp
HRESULT CToolMainApp::Ready_ImGui()
{
    // 1. 컨텍스트 생성
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // ImGui와 애플리케이션이 정보를 주고받는 구조체
    // 설정, 입력, 출력, 폰트가 있음
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;   // 키보드로 위젯 이동
    //io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;       // docking 브랜치 기능

    // 2. 스타일
    ImGui::StyleColorsDark();

    // 3. 플랫폼/렌더러 백엔드
    if (!ImGui_ImplWin32_Init(g_hWnd))
        return E_FAIL;
    if (!ImGui_ImplDX11_Init(m_pDevice.Get(), m_pContext.Get()))
        return E_FAIL;

    m_bReadyImGui = true;
    return S_OK;
}

HRESULT CToolMainApp::Begin_ImGui()
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    return S_OK;
}

HRESULT CToolMainApp::Render_ImGui()
{
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    return S_OK;
}

HRESULT CToolMainApp::Shutdown_ImGui()
{
    if (!m_bReadyImGui)
        return E_FAIL;
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    return S_OK;
}
```

**처음 나오는 ImGui 함수 — 초기화 / 프레임 / 종료**

| 함수 | 하는 일 | 자세히 |
|---|---|---|
| `IMGUI_CHECKVERSION()` | 헤더와 컴파일된 ImGui의 버전 검사 (매크로) | `imgui.h`와 `imgui.cpp`의 버전이나 구조체 크기가 다르면 assert. 서로 다른 버전 파일을 섞었을 때 바로 알 수 있다 |
| `ImGui::CreateContext()` | ImGui 컨텍스트(전체 상태) 생성 | 창 목록, 입력 상태, 폰트, 스타일 등 ImGui의 모든 상태가 여기 들어간다. **다른 ImGui 함수보다 먼저** 불러야 한다 |
| `io.ConfigFlags \|= ImGuiConfigFlags_NavEnableKeyboard` | 키보드 내비게이션 켜기 | Tab / 방향키로 위젯 사이를 이동하고 Enter / Space로 누를 수 있다 |
| `ImGui::StyleColorsDark()` | 색 테마를 다크로 | `StyleColorsLight()`, `StyleColorsClassic()`도 있다. 세부 색과 여백은 `ImGui::GetStyle()`로 직접 바꿀 수 있다 |
| `ImGui_ImplWin32_Init(hWnd)` | Win32 백엔드 초기화 | 이 HWND를 기준으로 화면 크기, 마우스 위치, 커서 모양, 시간을 처리한다 |
| `ImGui_ImplDX11_Init(Device, Context)` | DX11 백엔드 초기화 | Device/Context를 보관만 하고, 실제 GPU 리소스(폰트 텍스처, 셰이더, 버퍼, 상태)는 **첫 `ImGui_ImplDX11_NewFrame()` 때** 만든다. Device는 리소스 생성용, Context는 매 프레임 그리기 명령용 |
| `ImGui_ImplDX11_NewFrame()` | DX11 백엔드 프레임 시작 | 아직 GPU 리소스가 없으면 여기서 만든다 |
| `ImGui_ImplWin32_NewFrame()` | Win32 백엔드 프레임 시작 | `GetClientRect`로 창 크기를 재서 `io.DisplaySize`에 넣고, 지난 프레임부터 흐른 시간(`io.DeltaTime`), 마우스 위치 등을 갱신한다 |
| `ImGui::NewFrame()` | ImGui 프레임 시작 | 이 다음부터 `Begin`, `Button` 같은 위젯 함수를 부를 수 있다. **백엔드 두 개의 NewFrame 다음**에 불러야 한다 (입력과 화면 크기가 먼저 갱신돼야 하므로) |
| `ImGui::Render()` | 이번 프레임의 위젯 호출을 마무리 | 쌓인 그리기 명령을 **정점/인덱스/명령 목록(`ImDrawData`)**으로 정리한다. 아직 화면에 그리지는 않는다 |
| `ImGui::GetDrawData()` | `Render()`가 만든 `ImDrawData*`를 돌려줌 | |
| `ImGui_ImplDX11_RenderDrawData(ImDrawData*)` | DX11로 실제 그리기 | 정점/인덱스를 GPU 버퍼에 올리고, 창마다 잘라 그리기(Scissor) + 텍스처를 묶어 `DrawIndexed`. 그리기 전에 파이프라인 상태를 백업하고 끝나면 복구한다 |
| `ImGui_ImplDX11_Shutdown()` / `ImGui_ImplWin32_Shutdown()` | 백엔드 정리 | 초기화의 **반대 순서**로 정리 |
| `ImGui::DestroyContext()` | 컨텍스트 삭제 | 이후 `GetCurrentContext()`는 `nullptr` |

**Update / Render** — 프레임 순서가 중요

```cpp
void CToolMainApp::Update(f32_t fDeltaTime)
{
    if (FAILED(Begin_ImGui()))
        return;
    m_pEditorUI->Update(fDeltaTime);   // ImGui 화면 (생성/삭제/편집이 여기서 일어남)
    CGameInstance::Get().Update_Engine(fDeltaTime);
}

HRESULT CToolMainApp::Render()
{
    float4_t vClearColor = float4_t{ 0.f, 0.f, 0.f, 1.f };
    CGameInstance::Get().Clear_BackBuffer_View(&vClearColor);
    CGameInstance::Get().Clear_DepthStencil_View();

    CGameInstance::Get().Bind_PipeLine_Vertex_ShaderResource(1);
    CGameInstance::Get().Bind_PipeLine_Pixel_ShaderResource(1);
    CGameInstance::Get().Bind_PipeLine_Geometry_ShaderResource(1);

    CGameInstance::Get().Draw();      // 씬

    if (FAILED(Render_ImGui()))       // ImGui → 백버퍼 (씬보다 나중!)
        return E_FAIL;

    CGameInstance::Get().Present();
    return S_OK;
}
```

- vcxproj: `EditorUI.h/.cpp` 등록

**실행 결과**
- 회색 화면 맨 위에 `File | View` 메뉴바가 생긴다 (File 항목은 아직 회색 비활성)
- `View → ImGui Demo`를 누르면 데모 창이 뜨고, 드래그/클릭/입력이 된다 (모든 위젯 예제가 들어 있음)
- 데모 창의 입력칸에 글자를 넣는 중에 ESC를 눌러도 툴이 꺼지지 않는다. 입력칸 밖에서 누르면 꺼진다

**주의**
- ImGui 창에 입력이 안 들어가면 WndProc 맨 앞의 `ImGui_ImplWin32_WndProcHandler` 호출 확인
- `Begin_ImGui`(NewFrame)는 ImGui 함수를 부르기 **전**, `Render_ImGui`는 씬 `Draw()` **뒤**, `Present` **전**

---

## 3단계. 창 3개 — Hierarchy / Scene / Inspector

**목표**: 2단계 메뉴바 아래에 `Hierarchy | Scene | Inspector` 세 창이 화면을 꽉 채우고 움직이지 않는다. (도킹 없이 직접 좌표 계산)
창 하나가 클래스 하나가 되도록 구조를 잡고 시작한다.

### 3-1. 구조

```
CEditorUI  (메뉴바 + 레이아웃 계산 + EDITOR_CONTEXT 보관 + 패널 3개 소유)
 ├─ CPanel_Hierarchy   객체 목록, 선택, 생성/삭제          (6~8단계)
 ├─ CPanel_Scene       씬 텍스처 표시, 포커스/hover 기록    (4단계)
 └─ CPanel_Inspector   선택 객체의 값 편집                 (9·10단계)
       ▲ 모두 CPanel 상속, EDITOR_CONTEXT& 를 참조로 받음
```

| 파일 | 내용 |
|---|---|
| `Public/EditorUI_Defines.h` | `PANEL_RECT`, `EDITOR_CONTEXT`(패널끼리 공유하는 상태) — 단계마다 멤버 추가 |
| `Public/EditorUI_Utils.h` | 패널들이 같이 쓰는 ImGui 도우미 — 단계마다 함수 추가 |
| `Public/Panel.h` | `CPanel` (abstract) |
| `Public/Panel_XXX.h`, `Private/Panel_XXX.cpp` | 창 하나씩 |
| `Public/EditorUI.h`, `Private/EditorUI.cpp` | `CEditorUI` |

**규칙**
- 패널끼리는 서로를 직접 부르지 않는다. 주고받을 값(선택, Scene 포커스 등)은 전부 `EDITOR_CONTEXT`를 거친다
- 창의 위치/크기는 `CEditorUI`가 계산해서 `Render(const PANEL_RECT&)`로 넘긴다

### 3-2. EditorUI_Defines.h

```cpp
#pragma once
#include "MapTool_Defines.h"

NS_BEGIN(MapTool)

// 창 하나의 위치와 크기 (CEditorUI::Calc_Layout에서 계산)
struct PANEL_RECT
{
	f32_t fX, fY, fW, fH;
};

// 패널끼리 같이 쓰는 상태
// CEditorUI가 소유하고, 각 패널은 참조로 받는다.
struct EDITOR_CONTEXT
{
	// 4단계: Scene 창 상태
	// 7단계: 선택 상태
};

NS_END
```

### 3-3. EditorUI_Utils.h

```cpp
#pragma once
#include "imgui.h"
#include "EditorUI_Defines.h"

// 패널들이 같이 쓰는 ImGui 도우미
NS_BEGIN(MapTool)

inline constexpr ImGuiWindowFlags g_FixedPanelFlags =
	ImGuiWindowFlags_NoMove                 // 제목 표시줄을 드래그해도 안 움직임
	| ImGuiWindowFlags_NoResize             // 모서리를 끌어도 크기 안 바뀜
	| ImGuiWindowFlags_NoCollapse           // 제목 표시줄의 접기 버튼 제거
	| ImGuiWindowFlags_NoSavedSettings;     // 창 정보를 imgui.ini에 저장하지 않음

inline void Set_NextPanelRect(const PANEL_RECT& tRect)
{
	ImGui::SetNextWindowPos(ImVec2(tRect.fX, tRect.fY), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(tRect.fW, tRect.fH), ImGuiCond_Always);
}

// 7단계: To_UTF8, To_Wide
// 10단계: Render_AssetCombo

NS_END
```

- 헤더에 함수 본문을 두므로 `inline` 필수 (여러 cpp에서 include해도 중복 정의 에러가 안 나게)

**처음 나오는 ImGui 함수 / 값**

| 함수 / 값 | 하는 일 | 자세히 |
|---|---|---|
| `ImGui::SetNextWindowPos(위치, 조건)` | **다음에 `Begin`할 창**의 위치 지정 | 화면(프로그램 창 안쪽) 왼쪽 위가 `(0, 0)`인 픽셀 좌표. 반드시 그 창의 `Begin` **전에** 부른다 |
| `ImGui::SetNextWindowSize(크기, 조건)` | 다음 창의 크기 지정 | 위와 같다 |
| `ImGuiCond_Always` | "매 프레임 이 값으로 강제" | `ImGuiCond_FirstUseEver`(처음 한 번만, 이후엔 사용자가 옮긴 대로)와 비교된다. 우리는 레이아웃을 직접 계산하므로 Always |
| `ImGuiWindowFlags_NoMove` | 제목 표시줄을 드래그해도 창이 안 움직임 | |
| `ImGuiWindowFlags_NoResize` | 모서리를 끌어도 크기가 안 바뀜 | |
| `ImGuiWindowFlags_NoCollapse` | 제목 표시줄의 접기(▼) 버튼 제거 | 접히면 `Begin()`이 `false`가 되는데 그 경우를 아예 막는다 |
| `ImGuiWindowFlags_NoSavedSettings` | 창 위치/크기를 `imgui.ini`에 저장하지 않음 | 어차피 매 프레임 강제로 정하므로 저장하면 ini와 값이 엇갈린다 |
| `ImVec2(x, y)` | ImGui의 2D 벡터 타입 | 위치와 크기에 쓴다. 엔진의 `float2_t`와는 다른 타입이라 필요하면 `.x`, `.y`로 옮겨 담는다 |

### 3-4. Panel.h — 패널 부모

```cpp
#pragma once
#include "EditorUI_Defines.h"

NS_BEGIN(MapTool)
// 에디터 창 하나 (Hierarchy, Scene, Inspector)
// 위치/크기는 CEditorUI가 계산해서 Render에 넘겨준다.
class CPanel abstract
{
protected:
	explicit CPanel(EDITOR_CONTEXT& Context) : m_Context{ Context } {}
public:
	virtual ~CPanel() = default;

public:
	virtual void	Render(const PANEL_RECT& tRect) = 0;

protected:
	EDITOR_CONTEXT&		m_Context;		// CEditorUI가 소유한 공용 상태
};
NS_END
```

### 3-5. 패널 3개 (빈 창)

헤더는 세 개 모두 같은 모양 (이름만 다름). 예: `Panel_Hierarchy.h`

```cpp
#pragma once
#include "Panel.h"

NS_BEGIN(MapTool)
// 객체 이름 목록 + 선택 + 우클릭 생성/삭제
// 값 편집은 하지 않는다 (Inspector 담당)
class CPanel_Hierarchy final : public CPanel
{
private:
	explicit CPanel_Hierarchy(EDITOR_CONTEXT& Context) : CPanel{ Context } {}
public:
	virtual ~CPanel_Hierarchy() = default;

public:
	virtual void	Render(const PANEL_RECT& tRect) override;

public:
	static unique_ptr<CPanel_Hierarchy> Create(EDITOR_CONTEXT& Context);
};
NS_END
```

- `Panel_Scene.h` → `CPanel_Scene` (주석: 엔진이 그린 씬 텍스처(RTT)를 비율에 맞춰 표시)
- `Panel_Inspector.h` → `CPanel_Inspector` (주석: 선택한 객체의 이름, Transform, 타입별 섹션)

cpp도 지금은 빈 창만 연다. 예: `Panel_Hierarchy.cpp`

```cpp
#include "EditorUI_Utils.h"
#include "Panel_Hierarchy.h"

void CPanel_Hierarchy::Render(const PANEL_RECT& tRect)
{
    Set_NextPanelRect(tRect);
    if (ImGui::Begin("Hierarchy", nullptr, g_FixedPanelFlags))   // nullptr: X 버튼 없음
    {
        // 6단계부터 채움
    }
    ImGui::End();            // Begin의 반환값과 상관없이 항상 호출!
}

unique_ptr<CPanel_Hierarchy> CPanel_Hierarchy::Create(EDITOR_CONTEXT& Context)
{
    // 생성자가 private이라 make_unique 대신 new
    return unique_ptr<CPanel_Hierarchy>(new CPanel_Hierarchy(Context));
}
```

- `Panel_Scene.cpp` → 창 이름 `"Scene"` (본문은 4단계)
- `Panel_Inspector.cpp` → 창 이름 `"Inspector"` (본문은 9단계)

**처음 나오는 ImGui 함수**

| 함수 | 하는 일 | 자세히 |
|---|---|---|
| `ImGui::Begin(이름, p_open, 플래그)` | 창 하나 시작 | `이름`은 제목 표시줄 글자이자 **창의 ID**(같은 이름으로 두 번 Begin하면 같은 창에 이어서 그려진다). `p_open`에 `nullptr`을 주면 닫기(X) 버튼이 없다. 반환값은 "내용을 그릴 필요가 있나"(접혔거나 화면 밖이면 `false`) → `false`면 안쪽 위젯을 건너뛰어도 된다 |
| `ImGui::End()` | 창 끝 | **`Begin()`의 반환값과 상관없이 항상** 호출. 그래서 `if (Begin(...)) { ... }` 다음, `if` 바깥에 둔다 |

### 3-6. EditorUI.h (2단계 헤더에 레이아웃·패널 추가)

```cpp
#pragma once
#include "EditorUI_Defines.h"

NS_BEGIN(MapTool)
class CPanel_Hierarchy;
class CPanel_Scene;
class CPanel_Inspector;

// 에디터 화면 전체
// 메뉴바, 레이아웃 계산, 공용 상태(EDITOR_CONTEXT) 보관, 패널 3개 소유
class CEditorUI final
{
private:
	CEditorUI() = default;
public:
	~CEditorUI();

public:
	HRESULT		Initialize();
	void		Update(const f32_t& fDeltaTime);

private:
	f32_t		m_fMenuBarHeight = {};
	f32_t		m_fSidePamelWidth = { 280.f };   // 좌우 창 폭
	bool_t		m_bShowDemo = { false };

	PANEL_RECT	m_tHierarchy = {};
	PANEL_RECT	m_tScene = {};
	PANEL_RECT	m_tInspector = {};

	EDITOR_CONTEXT					m_Context;		// 패널들이 참조로 공유

	unique_ptr<CPanel_Hierarchy>	m_pHierarchy;
	unique_ptr<CPanel_Scene>		m_pScene;
	unique_ptr<CPanel_Inspector>	m_pInspector;

private:
	void		Calc_Layout();
	void		Render_MenuBar();

public:
	static unique_ptr<CEditorUI> Create();
};

NS_END
```

### 3-7. EditorUI.cpp

```cpp
#include "EditorUI_Utils.h"
#include "EditorUI.h"
#include "Panel_Hierarchy.h"
#include "Panel_Scene.h"
#include "Panel_Inspector.h"

// unique_ptr<CPanel_*>를 지우려면 완전한 타입이 필요해서 cpp에서 정의
CEditorUI::~CEditorUI() = default;

HRESULT CEditorUI::Initialize()
{
    m_pHierarchy = CPanel_Hierarchy::Create(m_Context);
    m_pScene     = CPanel_Scene::Create(m_Context);
    m_pInspector = CPanel_Inspector::Create(m_Context);

    if (nullptr == m_pHierarchy || nullptr == m_pScene || nullptr == m_pInspector)
        return E_FAIL;

	return S_OK;
}

void CEditorUI::Update(const f32_t& fDeltaTime)
{
    Render_MenuBar();     // 메뉴바 높이를 먼저 알아야
    Calc_Layout();        // 그 아래 영역을 나눌 수 있음

    m_pHierarchy->Render(m_tHierarchy);
    m_pScene->Render(m_tScene);
    m_pInspector->Render(m_tInspector);

    if (m_bShowDemo)
        ImGui::ShowDemoWindow(&m_bShowDemo);
}

void CEditorUI::Calc_Layout()
{
    // 현재 창 영역 크기
    const ImVec2 vDisplay = ImGui::GetIO().DisplaySize;

    // 메뉴바 바로 아래부터의 시작 좌표
    const f32_t fTop    = m_fMenuBarHeight;
    const f32_t fHeight = vDisplay.y - fTop;

    // 창이 좁아져도 씬이 최소 200은 남게 좌우 폭 보정
    f32_t fSide = m_fSidePamelWidth;
    const f32_t fMinScene = 200.f;
    if (vDisplay.x - fSide * 2.f < fMinScene)
        fSide = max(0.f, (vDisplay.x - fMinScene) * 0.5f);

    // 세 창의 Rect 정보
    m_tHierarchy    = { 0.f, fTop, fSide, fHeight };
    m_tScene        = { fSide, fTop, vDisplay.x - fSide * 2.f, fHeight };
    m_tInspector    = { vDisplay.x - fSide, fTop, fSide, fHeight };
}

void CEditorUI::Render_MenuBar()
{
    // 화면 맨 위에 꽉 차게 붙는 메뉴 바.
    // 일반 창(Begin) 안이 아니라 바깥에서 호출한다.
    // 일반 창(Begin)과는 다르게 false를 반환하면 EndMainMenuBar를 호출하지 않고 빠져나간다.
    if (!ImGui::BeginMainMenuBar())
        return;

    m_fMenuBarHeight = ImGui::GetWindowHeight();

    // 펼쳐지는 메뉴
    // true일 때만 EndMenu를 호출.
    if (ImGui::BeginMenu("File"))
    {
        // MenuItem(라벨, 단축키표시, 선택됨, 활성화);
        // 단축키는 오른쪽에 보이는 글자일 뿐이고 실제 동작은 따로 만들어야 함.
        ImGui::MenuItem("New Scene", nullptr, false, false);        // 저장/불러오기 전까지 비활성
        ImGui::MenuItem("Open Scene", "Ctrl + O", false, false);
        ImGui::MenuItem("Save", "Ctrl + S", false, false);
        ImGui::MenuItem("Save As", nullptr, false, false);
        ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("View"))
    {
        ImGui::MenuItem("ImGui Demo", nullptr, &m_bShowDemo);       // bool* 를 넘기면 체크 토글
        ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
}

unique_ptr<CEditorUI> CEditorUI::Create()
{
    auto pInstance = unique_ptr<CEditorUI>(new CEditorUI());
    if (FAILED(pInstance->Initialize()))
    {
        MSG_BOX("Failed to Created : CEditorUI");
        pInstance.reset();
    }
    return pInstance;
}
```

**처음 나오는 ImGui 값**

| 값 | 하는 일 | 자세히 |
|---|---|---|
| `ImGui::GetIO().DisplaySize` | 프로그램 창 안쪽 영역 크기 | `ImGui_ImplWin32_NewFrame()`이 매 프레임 `GetClientRect(hWnd)`로 재서 넣어 둔 값을 읽는다. 처음엔 `(1600, 900)`, 창 크기를 바꾸면 다음 프레임에 바로 바뀐다. **ImGui 창(Hierarchy 등)의 크기가 아니라** 프로그램 창 전체 크기다 |

### 3-8. 프로젝트 등록
- `Default.vcxproj`에 헤더 7개(`EditorUI.h, EditorUI_Defines.h, EditorUI_Utils.h, Panel.h, Panel_Hierarchy.h, Panel_Inspector.h, Panel_Scene.h`), cpp 4개(`EditorUI.cpp, Panel_Hierarchy.cpp, Panel_Inspector.cpp, Panel_Scene.cpp`) 추가
- `Default.vcxproj.filters` (솔루션 탐색기 폴더)

```
01. EditorUI
 ├─ EditorUI.h / EditorUI.cpp
 ├─ 00. Common       EditorUI_Defines.h, EditorUI_Utils.h
 └─ 01. Panel        Panel.h, Panel_Hierarchy.h/.cpp, Panel_Inspector.h/.cpp, Panel_Scene.h/.cpp
```
- 파일은 **UTF-8 (BOM) + CRLF**로 저장 (BOM이 없으면 MSVC가 CP949로 읽어서 한글 주석이 깨지거나 다음 줄을 먹을 수 있음)

**실행 결과**
- 메뉴바 아래에 Hierarchy | Scene | Inspector 세 창이 화면을 꽉 채운다 (좌우 창 폭 280)
- 창 크기를 바꿔도 세 창이 화면을 꽉 채우고, 드래그/리사이즈가 안 된다
- 세 창 모두 아직 비어 있다 (Scene은 4단계, Hierarchy는 6단계, Inspector는 9단계에서 채움)
- `View → ImGui Demo`는 그대로 동작

**주의**
- `Begin`은 false여도 `End`를 반드시 호출. 반대로 `BeginMainMenuBar / BeginMenu / BeginPopup / BeginCombo`는 **true일 때만** End 호출
- `ImGuiCond_Always`로 매 프레임 위치/크기를 강제하므로 `NoSavedSettings`를 같이 써야 ini와 싸우지 않음
- `CEditorUI` 소멸자를 헤더에서 `= default`로 하면 `CPanel_*`가 전방 선언뿐이라 `unique_ptr` 삭제에서 컴파일 에러 → cpp에서 정의
- 패널은 `m_Context`를 참조로 들고 있으므로 `CEditorUI`는 복사/이동하면 안 됨 (`unique_ptr`로만 다루므로 문제 없음)

---

## 4단계. Scene 창에 게임 화면 넣기 (RTT)

**목표**: 엔진이 그린 3D 화면을 텍스처로 받아 Scene 창 안에 **비율을 유지하며** 표시한다.

### 4-1. 개념 — 렌더 타깃을 바꿔서 그린다 (RTT, Render To Texture)

**그림은 "지금 묶여 있는 렌더 타깃"에 그려진다**
- 파이프라인 마지막 단계인 출력 병합기(OM, Output Merger)가 픽셀 셰이더가 낸 색을 **현재 바인딩된 렌더 타깃**에 기록한다
- 어디에 그릴지는 `OMSetRenderTargets(RTV 개수, RTV 배열, DSV)` 한 줄로 정한다
- 평소에는 `CGraphic_Device` 초기화 때 **백버퍼 RTV + 깊이 버퍼 DSV**를 묶어 두기 때문에 모든 Draw가 백버퍼로 가고, `Present`로 화면에 나온다

```cpp
// CGraphic_Device 초기화 (이미 있는 코드)
ID3D11RenderTargetView* pRTVs[] = { m_pBackBufferRTV.Get() };
m_pDeviceContext->OMSetRenderTargets(1, pRTVs, m_pDepthStencilView.Get());
m_pDeviceContext->RSSetViewports(1, &ViewPortDesc);      // 창 크기 뷰포트
```

**RTT = 백버퍼 대신 내가 만든 텍스처를 묶고 그리기**
- 직접 만든 텍스처의 RTV를 묶고 그리면 결과가 화면이 아니라 **텍스처에 남는다**
- 그 텍스처를 다시 **읽기용(SRV)** 으로 쓰면 셰이더나 ImGui에서 이미지처럼 쓸 수 있다

**텍스처 하나에 "뷰"를 두 개 만든다**

| 뷰 | 용도 | 여기서 쓰는 곳 |
|---|---|---|
| RTV (Render Target View) | 그리기 대상 (쓰기) | 씬 오브젝트를 그릴 때 |
| SRV (Shader Resource View) | 셰이더에서 읽기 | 백버퍼로 복사(Client), `ImGui::Image`(MapTool) |

- 뷰를 만들려면 텍스처 생성 때 `BindFlags`에 해당 용도가 들어 있어야 한다 (없으면 `CreateXXXView` 실패)
- **같은 텍스처를 RTV로 묶은 채 SRV로 읽을 수 없다.** 그래서 항상 "RTV로 그리기 → RTV 풀기(원래 타깃으로 복구) → SRV로 읽기 → 다 읽으면 SRV 풀기" 순서를 지킨다 (어기면 DX11이 한쪽을 강제로 풀고 디버그 출력에 경고를 남긴다)

**전체 흐름**

```
[평소]   오브젝트 Draw ──▶ 백버퍼 RTV ──────────────────────────────────────────▶ Present

[RTT]    오브젝트 Draw ──▶ SceneRTV (텍스처)
                              │
                              ├─ Client  : Render_FullScreen — SceneSRV를 읽어 백버퍼에 그대로 복사 ──▶ Present
                              └─ MapTool : 복사 안 함. ImGui::Image(SceneSRV)로 Scene 창 안에만 그림 ──▶ Present
```

Client와 MapTool이 **같은 Renderer 코드**를 쓰고, 마지막 복사만 `m_bDrawToBackBuffer`로 켜고 끈다.

### 4-2. Renderer.h — 멤버 추가

```cpp
#pragma once
#include "Engine_Defines.h"

// --- class CRenderer 안 ---
public:
	void	Set_DrawToBackBuffer(bool_t bDraw)			{ m_bDrawToBackBuffer = bDraw; }
	ID3D11ShaderResourceView* Get_SceneSRV()const		{ return m_pSceneSRV.Get(); }
private:
	// 씬 텍스처 (텍스처 하나에 뷰 2개)
	ComPtr<ID3D11RenderTargetView>		m_pSceneRTV;      // 그리기
	ComPtr<ID3D11ShaderResourceView>	m_pSceneSRV;      // 읽기

	// 씬 텍스처 → 백버퍼 복사용
	ComPtr<ID3D11VertexShader>			m_pVS_FullScreen;
	ComPtr<ID3D11PixelShader>			m_pPS_FullScreen;
	ComPtr<ID3D11DepthStencilState>		m_pDSS_NoDepth;   // 복사할 때는 깊이 테스트 끔

	bool_t								m_bDrawToBackBuffer = { true };   // Client는 true, 툴은 false
private:
	void	Render_FullScreen();
	HRESULT	Ready_SceneTarget(uint32_t iWinSizeX, uint32_t iWinsizeY);
```

### 4-3. Ready_SceneTarget — 씬 텍스처 만들기

`CRenderer::Initialize`에서 다른 상태 객체들과 함께 한 번 호출한다.

```cpp
// Renderer.cpp
#include "Renderer.h"
#include "GameObject.h"
#include "GameInstance.h"

HRESULT CRenderer::Ready_SceneTarget(uint32_t iWinSizeX, uint32_t iWinSizeY)
{
	// 1. 텍스처 생성
	D3D11_TEXTURE2D_DESC desc{};
	desc.Width = iWinSizeX;                         // 창(=백버퍼, 깊이 버퍼)과 같은 크기
	desc.Height = iWinSizeY;
	desc.MipLevels = 1;                             // 화면용이라 밉맵 불필요
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;       // 백버퍼와 같은 색 형식
	desc.SampleDesc.Count = 1;                      // MSAA 없음 (깊이 버퍼와 같아야 함)
	desc.Usage = D3D11_USAGE_DEFAULT;               // GPU가 읽고 쓰기
	desc.BindFlags = D3D11_BIND_RENDER_TARGET       // RTV를 만들려면
	               | D3D11_BIND_SHADER_RESOURCE;    // SRV를 만들려면

	ComPtr<ID3D11Texture2D> pTex;
	m_pDevice->CreateTexture2D(&desc, nullptr, &pTex);

	// 2. 같은 텍스처에 뷰 2개
	m_pDevice->CreateRenderTargetView(pTex.Get(), nullptr, &m_pSceneRTV);
	m_pDevice->CreateShaderResourceView(pTex.Get(), nullptr, &m_pSceneSRV);
	// pTex는 여기서 사라져도 됨 — 뷰들이 텍스처 참조를 들고 있음

	// 3. 백버퍼로 복사할 때 쓸 "깊이 끔" 상태
	D3D11_DEPTH_STENCIL_DESC noDepth{};
	noDepth.DepthEnable = FALSE;
	if (FAILED(m_pDevice->CreateDepthStencilState(&noDepth, m_pDSS_NoDepth.GetAddressOf())))
		return E_FAIL;

	// 4. 복사용 셰이더 (Shader_FullScreen.hlsl의 VS_FullScreen / PS_FullScreen)
	ComPtr<ID3DBlob> pVSBlob, pPSBlob, pErrBlob;
	uint32_t iFlags = 0;
#ifdef _DEBUG
	iFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif
	if (FAILED(D3DCompileFromFile(L"../Bin/Shader/Shader_FullScreen.hlsl", nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"VS_FullScreen", "vs_5_0", iFlags, 0, &pVSBlob, &pErrBlob)))
	{
		if (pErrBlob) OutputDebugStringA((char*)pErrBlob->GetBufferPointer());
		return E_FAIL;
	}
	if (FAILED(D3DCompileFromFile(L"../Bin/Shader/Shader_FullScreen.hlsl", nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"PS_FullScreen", "ps_5_0", iFlags, 0, &pPSBlob, &pErrBlob)))
	{
		if (pErrBlob) OutputDebugStringA((char*)pErrBlob->GetBufferPointer());
		return E_FAIL;
	}
	if (FAILED(m_pDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &m_pVS_FullScreen)))
		return E_FAIL;
	if (FAILED(m_pDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &m_pPS_FullScreen)))
		return E_FAIL;

	return S_OK;
}
```

- **크기를 창과 같게 하는 이유**: 깊이 버퍼는 새로 만들지 않고 기존 것을 같이 쓰는데, 렌더 타깃과 깊이 버퍼의 크기·샘플 수가 다르면 그려지지 않는다. 뷰포트도 그대로 쓸 수 있다
- 셰이더 경로 `../Bin/Shader/`는 실행 폴더 기준 → MapTool도 `MapTool/Bin/Shader/`에 `Shader_FullScreen.hlsl`이 있어야 함 (1-2의 xcopy)

### 4-4. Render_GameObject — 타깃 바꾸기 → 그리기 → 되돌리기

`CGameInstance::Draw()`가 매 프레임 `m_pRenderer->Render_GameObject()`를 부른다.

```cpp
void CRenderer::Render_GameObject()
{
	// 1. 지금 묶여 있는 타깃(백버퍼 RTV + 깊이 DSV)을 백업
	ComPtr<ID3D11RenderTargetView>	pOldRTV;
	ComPtr<ID3D11DepthStencilView>	pOldDSV;
	m_pContext->OMGetRenderTargets(1, pOldRTV.GetAddressOf(), pOldDSV.GetAddressOf());

	// 2. 렌더 타깃만 씬 텍스처로 교체 (깊이 버퍼는 기존 것 그대로)
	float clearColor[4] = { 0.75f, 0.75f, 0.75f, 1.f };
	m_pContext->OMSetRenderTargets(1, m_pSceneRTV.GetAddressOf(), pOldDSV.Get());

	// 3. 씬 텍스처 지우기 (백버퍼 Clear와 별개 — 텍스처는 따로 지워야 지난 프레임이 안 남음)
	m_pContext->ClearRenderTargetView(m_pSceneRTV.Get(), clearColor);

	// 4. 오브젝트 그리기 — 각 객체의 Render는 바뀐 게 없다. 타깃만 바뀌었을 뿐
	Render_Priority();
	Render_NonAlpha();
	Render_OccludedPlayer();
	Render_Player();
	Render_Shadow();
	Render_AlphaPre();
	Render_Mirror();
	Render_Alpha();

	// 5. 원래 타깃(백버퍼)으로 복구 → 이제 씬 텍스처는 RTV에서 풀려서 SRV로 읽을 수 있음
	m_pContext->OMSetRenderTargets(1, pOldRTV.GetAddressOf(), pOldDSV.Get());

	// 6. Client: 씬 텍스처를 백버퍼에 복사 / MapTool: 건너뜀 (ImGui::Image가 대신 보여줌)
	if (m_bDrawToBackBuffer)
		Render_FullScreen();

	// 7. UI는 씬 텍스처가 아니라 백버퍼에 바로 그림
	Render_NonAlpha_UI();
	Render_Alpha_UI();
}
```

- **백업을 하는 이유**: Renderer가 백버퍼 RTV를 직접 들고 있지 않아도, 원래 타깃이 무엇이었든 그대로 되돌릴 수 있다
- `OMGetRenderTargets`는 받은 뷰의 참조 카운트를 올려 준다 → `ComPtr`로 받으면 함수가 끝날 때 자동으로 `Release`
- 깊이 버퍼는 `CToolMainApp::Render`(Client는 `CMainApp::Render`) 맨 앞의 `Clear_DepthStencil_View()`에서 이미 지워졌으므로 여기서는 색만 지운다
- 씬 텍스처는 창과 같은 크기라 **뷰포트를 바꿀 필요가 없다** (크기가 다른 텍스처에 그릴 때는 `RSSetViewports`도 같이 바꾸고 복구해야 함)
- 7번 UI 그룹은 백버퍼에 그려지므로 MapTool에서는 Scene 창 안이 아니라 ImGui 창 뒤에 깔린다 → 맵툴 레벨에서는 UI 객체를 만들지 않는다

### 4-5. Render_FullScreen — 씬 텍스처를 백버퍼에 복사 (Client)

정점 버퍼 없이 **화면을 덮는 삼각형 하나**를 그리고, 픽셀마다 씬 텍스처의 같은 위치 텍셀을 그대로 출력한다.

```cpp
void CRenderer::Render_FullScreen()
{
	m_pContext->OMSetDepthStencilState(m_pDSS_NoDepth.Get(), 0);   // 깊이 테스트 끔 (씬 위에 덮어써야 함)
	m_pContext->IASetInputLayout(nullptr);                          // 정점 버퍼/입력 레이아웃 없음
	m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_pContext->VSSetShader(m_pVS_FullScreen.Get(), nullptr, 0);
	m_pContext->PSSetShader(m_pPS_FullScreen.Get(), nullptr, 0);
	m_pContext->PSSetShaderResources(0, 1, m_pSceneSRV.GetAddressOf());   // t0 = 씬 텍스처
	m_pContext->Draw(3, 0);                                               // 정점 3개 = 삼각형 1개

	ID3D11ShaderResourceView* pNullSRV[1] = { nullptr };
	m_pContext->PSSetShaderResources(0, 1, pNullSRV);   // SRV 풀기 — 다음 프레임에 RTV로 다시 묶어야 하므로
	m_pContext->OMSetDepthStencilState(nullptr, 0);     // 기본 깊이 상태로 (UI는 깊이를 다시 써야 함)
}
```

**Shader_FullScreen.hlsl** (`Client/Bin/Shader/`에 새로 만듦)

```hlsl
Texture2D g_Input : register(t0);     // PSSetShaderResources(0, ...)로 묶은 씬 텍스처

struct VS_OUT
{
    float4 vPosition : SV_POSITION;
};

// SV_VertexID : 입력 조립기(IA)가 만들어 주는 "몇 번째 정점인지" 값
// Draw(3, 0) → 이 함수가 세 번 호출되고 iVertexID로 0, 1, 2가 들어감
VS_OUT VS_FullScreen(uint iVertexID : SV_VertexID)
{
    VS_OUT Out;
    float2 g_vUVs[3] = { float2(0, 0), float2(2, 0), float2(0, 2) };
    float2 vUV = g_vUVs[iVertexID];

    // UV(0~2) → NDC : x는 -1 ~ 3, y는 뒤집어서 1 ~ -3
    // → (-1,1) (3,1) (-1,-3) : 화면(-1~1)보다 큰 삼각형. 밖은 클리핑되고 화면 사각형만 남음
    Out.vPosition = float4(vUV * float2(2.f, -2.f) + float2(-1.f, 1.f), 0.f, 1.f);
    return Out;
}

float4 PS_FullScreen(VS_OUT In) : SV_TARGET
{
    // PS의 SV_POSITION은 픽셀 좌표 (0.5, 0.5), (1.5, 0.5) ...
    // 텍스처와 화면 크기가 같으므로 정수로 바꾸면 그대로 텍셀 인덱스 (샘플러 불필요)
    return g_Input[uint2(In.vPosition.xy)];
}
```

- 사각형(삼각형 2개) 대신 큰 삼각형 1개를 쓰면 정점 버퍼도 필요 없고, 대각선 경계에서 픽셀이 두 번 처리되지도 않는다

### 4-6. GameInstance 연결 + 툴에서 끄기

**GameInstance**에 전달 함수 추가

```cpp
void	Set_DrawToBackBuffer(bool_t bDraw);          // → m_pRenderer->Set_DrawToBackBuffer
ID3D11ShaderResourceView* Get_SceneSRV()const;      // → m_pRenderer->Get_SceneSRV
float2_t Get_ViewportSize() { return m_vViewportSize; }   // Initialize_Engine 끝에서 Compute_ViewportSize()
```

**MapTool**: `CToolMainApp::Initialize`의 `Change_Level` 다음, `return S_OK;` 전에 추가

```cpp
    CGameInstance::Get().Set_DrawToBackBuffer(false);   // 씬을 백버퍼에 복사하지 않음 → Scene 창에서만 보이게
```

MapTool 한 프레임에서 렌더 타깃이 바뀌는 순서

```
CToolMainApp::Render
 ├ Clear_BackBuffer_View / Clear_DepthStencil_View     백버퍼(검정) + 깊이 지우기
 ├ Draw() → Render_GameObject
 │    ├ OMSetRenderTargets(SceneRTV)                    ── 씬 텍스처에 그리기 시작
 │    ├ Clear(0.75 회색) → 오브젝트 그리기
 │    ├ OMSetRenderTargets(백버퍼)                       ── 복구
 │    └ Render_FullScreen 건너뜀 (m_bDrawToBackBuffer = false)
 ├ Render_ImGui()                                       백버퍼에 ImGui 창들을 그림
 │    └ Scene 창의 ImGui::Image가 SceneSRV를 읽어서 창 안에 표시
 └ Present
```

- ImGui는 그리기 명령을 `ImGui::Image` 호출 시점이 아니라 `ImGui_ImplDX11_RenderDrawData`에서 실행한다 → 그 시점에는 씬 텍스처가 이미 이번 프레임 그림으로 채워져 있다
- 1~3단계에서 화면 전체가 회색이었던 것이 바로 `Render_FullScreen`이 씬 텍스처(회색으로 지워진)를 백버퍼에 복사한 결과

### 4-7. EditorUI_Defines.h — EDITOR_CONTEXT에 Scene 상태 추가

```cpp
struct EDITOR_CONTEXT
{
	// ---------- Scene 창 ----------
	float2_t	vImageMin = {};					// 화면 기준 씬 이미지 좌상단 (피킹용)
	float2_t	vImageSize = {};				// 씬 이미지 크기 (피킹에서 NDC로 바꿀 때 나누는 값)
	bool_t		bSceneHovered = {};				// 씬 이미지 위에 마우스가 있는지 → 카메라 조작 허용 (5단계)
	bool_t		bSceneFocused = {};				// Scene 창이 포커스인지 → 카메라 조작 허용 (5단계)

	// 7단계: 선택 상태
};
```

### 4-8. CPanel_Scene

**Panel_Scene.h**

```cpp
#pragma once
#include "Panel.h"

NS_BEGIN(MapTool)
// 엔진이 그린 씬 텍스처(RTT)를 비율에 맞춰 표시
// 포커스/hover/이미지 영역을 Context에 기록한다 (카메라, 피킹용)
class CPanel_Scene final : public CPanel
{
private:
	explicit CPanel_Scene(EDITOR_CONTEXT& Context) : CPanel{ Context } {}
public:
	virtual ~CPanel_Scene() = default;

public:
	virtual void	Render(const PANEL_RECT& tRect) override;

public:
	static unique_ptr<CPanel_Scene> Create(EDITOR_CONTEXT& Context);
};
NS_END
```

**Panel_Scene.cpp**

```cpp
#include "EditorUI_Utils.h"
#include "Panel_Scene.h"

void CPanel_Scene::Render(const PANEL_RECT& tRect)
{
    // 창의 크기와 위치 지정
    Set_NextPanelRect(tRect);

    // 창 옵션
    constexpr ImGuiWindowFlags eSceneFlags = g_FixedPanelFlags
        | ImGuiWindowFlags_NoScrollbar
        | ImGuiWindowFlags_NoScrollWithMouse;

    // 창 안쪽 여백(기본 8,8)을 0으로 → 이미지가 창에 딱 붙음
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
    ImGui::Begin("Scene", nullptr, eSceneFlags);
    ImGui::PopStyleVar();         // Begin 직후 복구 (Begin 시점에 적용되므로)

    // 현재 커서부터 창 오른쪽 아래까지 위젯을 놓을 수 있는 공간
    const ImVec2 vAvail = ImGui::GetContentRegionAvail();

    // 씬 텍스처 비율 유지
    float2_t vpSize = CGameInstance::Get().Get_ViewportSize();
    const f32_t fAspect = static_cast<f32_t>(vpSize.x) / vpSize.y;

    ImVec2 vSize = vAvail;
    if (vAvail.x / fAspect <= vAvail.y)   vSize.y = vAvail.x / fAspect;   // 가로에 맞춤
    else                                  vSize.x = vAvail.y * fAspect;   // 세로에 맞춤

    // 세로 가운데 정렬 (커서 위치 = 다음 위젯이 놓일 위치)
    const ImVec2 vCursor = ImVec2(0, (vAvail.y - vSize.y) * 0.5f);
    ImGui::SetCursorPos(vCursor);

    // SRV 포인터를 ImTextureID로 넘기면 DX11 백엔드가 PS 0번 슬롯에 바인딩해서 그림
    // 실제로 그리는 것이 아닌 그리기 명령만 기록한다. Image도 하나의 아이템으로 등록된다.
    ID3D11ShaderResourceView* pSRV = CGameInstance::Get().Get_SceneSRV();
    ImGui::Image((ImTextureID)pSRV, vSize);

    // 바로 앞 아이템(Image)에 대한 정보 — 사이에 다른 위젯을 넣지 말 것
    m_Context.vImageMin     = float2_t(ImGui::GetItemRectMin().x, ImGui::GetItemRectMin().y);  // 화면 기준 좌상단 (피킹용)
    m_Context.vImageSize    = float2_t(vSize.x, vSize.y);
    m_Context.bSceneHovered = ImGui::IsItemHovered();
    m_Context.bSceneFocused = ImGui::IsWindowFocused();   // 마지막으로 클릭된 창이면 true → 카메라 조작 허용
                                                          // (Begin~End 사이에서 불러야 이 창 값이 나옴)
    ImGui::End();
}
```

**처음 나오는 ImGui 함수 / 값**

| 함수 / 값 | 하는 일 | 자세히 |
|---|---|---|
| `ImGuiWindowFlags_NoScrollbar` / `NoScrollWithMouse` | 스크롤바 숨김 / 휠로 스크롤 안 함 | 이미지가 창에 딱 맞으므로 스크롤이 생기지 않게 한다 |
| `ImGui::PushStyleVar(항목, 값)` | 스타일 값 하나를 **잠깐** 바꿈 | 스택 구조라서 `PopStyleVar()`로 되돌린다. Push한 개수만큼 Pop해야 하고, 안 하면 `End` 때 assert |
| `ImGuiStyleVar_WindowPadding` | 창 테두리와 내용 사이의 안쪽 여백 (기본 8, 8) | `(0, 0)`으로 바꾸면 이미지가 창 테두리에 딱 붙는다. 창 여백은 **`Begin` 시점에 적용**되므로 Begin 전에 Push, Begin 직후 Pop |
| `ImGui::PopStyleVar()` | 마지막으로 Push한 스타일을 되돌림 | 인자로 개수를 줄 수 있다 (`PopStyleVar(2)`) |
| `ImGui::GetContentRegionAvail()` | **현재 커서부터** 창 내용 영역 오른쪽 아래까지 남은 크기 | 제목 표시줄, 여백, 스크롤바를 뺀 실제로 위젯을 놓을 수 있는 공간. Scene 창 기준 약 `(1040, 862)` |
| `ImGui::SetCursorPos(위치)` | 다음 위젯을 놓을 위치를 지정 | **창 기준 좌표**(창 왼쪽 위 = `(0, 0)`, 제목 표시줄 포함). ImGui는 위젯을 놓을 때마다 커서를 다음 줄로 옮기는데, 그 커서를 직접 옮기는 것. 원래 커서 시작점(`GetCursorPos()`)은 제목 표시줄 아래이므로, 내용 영역 정확히 가운데에 두려면 그 시작점만큼 더해야 한다 (지금 코드는 y만 계산해서 제목 표시줄 높이의 절반쯤 위로 치우침) |
| `ImGui::Image(텍스처ID, 크기)` | 텍스처를 사각형으로 그림 | DX11 백엔드에서는 `ID3D11ShaderResourceView*`를 `ImTextureID`로 바꿔 넘긴다. 실제로 그릴 때 백엔드가 그 SRV를 픽셀 셰이더 t0에 묶는다. 뒤에 UV 인자(`uv0`, `uv1`)를 주면 텍스처의 일부만 그리거나 뒤집을 수 있다 |
| `ImTextureID` | ImGui가 텍스처를 가리키는 값 | ImGui 본체는 그 정체를 모르고, 백엔드가 해석한다 (DX11 = SRV 포인터) |
| `ImGui::GetItemRectMin()` | **바로 앞 위젯**의 왼쪽 위 좌표 | **화면 기준 좌표**(프로그램 창 안쪽 왼쪽 위 = `(0, 0)`). `SetCursorPos`의 창 기준 좌표와 다르니 주의. `GetItemRectMax()`, `GetItemRectSize()`도 있다 |
| `ImGui::IsItemHovered()` | 마우스가 **바로 앞 위젯** 위에 있나 | 위젯 사각형 안에 마우스가 있고, 팝업이나 다른 창에 가려지지 않았으면 `true`. 매 프레임 마우스 위치로 다시 판단 |
| `ImGui::IsWindowFocused()` | **지금 그리는 창**이 포커스(마지막으로 클릭해서 활성화된 창)인가 | ImGui는 포커스 창을 딱 하나 기억하고(`g.NavWindow`), 지금 `Begin`~`End` 중인 창과 같은지 비교한다. 다른 창을 **클릭**해야 바뀌고 마우스를 옮기기만 해서는 안 바뀐다. `Begin`~`End` **안에서** 불러야 한다 |

- `IsWindowFocused` vs `IsItemHovered`: 앞의 것은 "Scene 창을 마지막으로 클릭했나"(클릭으로 바뀜), 뒤의 것은 "마우스가 지금 씬 이미지 위에 있나"(움직임으로 바뀜). 5단계 카메라가 둘 다 사용한다

**실행 결과**
- 1~3단계에서 화면 전체에 깔려 있던 회색이 사라지고, **Scene 창 안에만** 회색(0.75) 씬 이미지가 보인다
- 창 크기를 바꿔도 씬 이미지가 찌그러지지 않는다 (가로에 맞추고 위아래는 ImGui 창 배경)

**주의**
- 툴에서 `Set_DrawToBackBuffer(false)`를 안 하면 씬이 백버퍼 전체에도 그려져 ImGui 창 뒤에 겹쳐 보인다
- `ImGui::Render`는 반드시 씬 `Draw()` **뒤**에 (그래야 SceneSRV에 이번 프레임 그림이 들어 있음)
- 현재 가로 방향 가운데 정렬은 안 되어 있음 (`vCursor.x = (vAvail.x - vSize.x) * 0.5f` 추가하면 됨 — 남은 작업)

---

## 5단계. 맵툴 카메라 + SkyBox

**목표**: Scene 창에 SkyBox가 보이고, Scene 창을 클릭한 상태에서 **우클릭을 누르고** WASD로 이동, 마우스로 회전한다. (유니티 씬 뷰 방식)

### 5-1. Engine — 카메라를 게임오브젝트로

- `CCamera : CGameObject` (abstract). Transform 컴포넌트가 카메라의 월드 행렬
- DESC

```cpp
// Camera.h
#pragma once
#include "GameObject.h"

// --- class ENGINE_DLL CCamera abstract : public CGameObject 안 ---
typedef struct tagCameraDesc : public CGameObject::GAMEOBJECT_DESC
{
	float4_t		vEye, vAt;
	f32_t			fFovy, fNear, fFar;
}CAMERA_DESC;
```

- `Initialize`: Fovy/Near/Far 저장 → `__super::Initialize`(Transform 생성, 속도/회전속도) → 위치=vEye, `LookAt(vAt)` → `Update_PipeLines()`
- `Update_PipeLines()`: **View = 월드행렬의 역행렬**, **Proj = PerspectiveFovLH(fovy, 뷰포트 가로/세로, near, far)** 를 파이프라인에 설정

```cpp
// Camera.cpp
#include "Camera.h"

void CCamera::Update_PipeLines()
{
	CGameInstance::Get().Set_Perspective_Transform(D3DTS::VIEW,
		XMMatrixInverse(nullptr, XMLoadFloat4x4(m_pTransformCom->Get_WorldMatrixPtr())));

	float2_t vViewportSize = CGameInstance::Get().Get_ViewportSize();
	CGameInstance::Get().Set_Perspective_Transform(D3DTS::PROJ,
		XMMatrixPerspectiveFovLH(XMConvertToRadians(m_fFovy), vViewportSize.x / vViewportSize.y, m_fNear, m_fFar));
}
```

- `Late_Update`에서 `Update_Frustum()` (절두체 컬링용)
- `CCamera::Render`는 그릴 게 없으니 `return S_OK;`로 끝나게 (부모 Render 결과만 반환)

**Camera_Manager** — 카메라를 슬롯에 등록하고 메인 카메라를 고른다 (`weak_ptr` 보관)

```cpp
enum class CAMERA { ORTHOGRAPHIC, QUARTERVIEW, FREE, END };   // Engine_Enum.h

// Camera_Manager.h
#pragma once
#include "Engine_Defines.h"

// Camera_Manager.cpp
#include "Camera_Manager.h"
#include "Camera.h"

// --- class CCamera_Manager 안 ---

void				Add_Camera(CAMERA eCameraID, shared_ptr<CCamera> pCamera);
void				Set_MainCamera(CAMERA eCameraID);
shared_ptr<CCamera> Get_MainCamera() { return m_pMainCamera.lock(); }
```

### 5-2. CMapTool_Cam

**MapTool_Cam.h**

```cpp
#pragma once
#include "Camera.h"
#include "Client_Defines.h"

NS_BEGIN(Client)
class CMapTool_Cam : public CCamera
{
public:
    typedef struct tagMapToolCamDesc : public CCamera::CAMERA_DESC
    {
        f32_t			fSensor = {};      // 마우스 감도
    }CAMERA_MAPTOOL_CAM_DESC;
private:
    CMapTool_Cam(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
    virtual ~CMapTool_Cam() = default;
public:
    virtual HRESULT Initialize_Prototype() override;
    virtual HRESULT Initialize(void* pArg) override;
    virtual void Priority_Update(f32_t fTimeDelta);
    virtual void Update(f32_t fTimeDelta);
    virtual void Late_Update(f32_t fTimeDelta);
    virtual HRESULT Render();

    virtual void Set_SceneClicked(bool_t bClicked) { m_bSceneClicked = bClicked; }
    virtual void Set_SceneHovered(bool_t bHovered) { m_bSceneHovered = bHovered; }
private:
    bool_t      m_bSceneClicked = { false };    // Scene 창이 포커스인가
    bool_t      m_bSceneHovered = { false };    // 마우스가 씬 이미지 위에 있는가
    f32_t	    m_fMouseSensor = {};
private:
    void        KeyInput(const f32_t fDeltaTime);
public:
    static shared_ptr<CMapTool_Cam> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
    shared_ptr<CPrototype> Clone(void* pArg) override;
};
NS_END
```

**MapTool_Cam.cpp 핵심**

```cpp
#include "MapTool_Cam.h"

CMapTool_Cam::CMapTool_Cam(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	:CCamera{ pDevice, pContext }
{
}

HRESULT CMapTool_Cam::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;
	return S_OK;
}

HRESULT CMapTool_Cam::Initialize(void* pArg)
{
	auto pDesc = static_cast<tagMapToolCamDesc*>(pArg);
	m_fMouseSensor = pDesc->fSensor;
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;
	return S_OK;
}

void CMapTool_Cam::Update(f32_t fDeltaTime)
{
	__super::Update(fDeltaTime);
	if (!CGameInstance::Get().Get_DIMouseState(DIM::RB))   // 우클릭 중에만
		return;
	if (m_bSceneClicked && m_bSceneHovered)                 // Scene 창이 포커스 + 마우스가 씬 이미지 위일 때만
		KeyInput(fDeltaTime);
}

void CMapTool_Cam::KeyInput(const f32_t fDeltaTime)
{
	if (CGameInstance::Get().Get_DIKeyState(DIK_W)) m_pTransformCom->Go_Straight(fDeltaTime);
	if (CGameInstance::Get().Get_DIKeyState(DIK_S)) m_pTransformCom->Go_Backward(fDeltaTime);
	if (CGameInstance::Get().Get_DIKeyState(DIK_A)) m_pTransformCom->Go_Left(fDeltaTime);
	if (CGameInstance::Get().Get_DIKeyState(DIK_D)) m_pTransformCom->Go_Right(fDeltaTime);

	int32_t iMouseMove = {};
	if (iMouseMove = CGameInstance::Get().Get_DIMouseMove(DIMM::Y))     // 위아래: 자기 Right 축 기준
		m_pTransformCom->Turn(m_pTransformCom->Get_State(STATE::RIGHT), m_fMouseSensor * iMouseMove * fDeltaTime);
	if (iMouseMove = CGameInstance::Get().Get_DIMouseMove(DIMM::X))     // 좌우: 월드 Y축 기준
		m_pTransformCom->Turn(XMVectorSet(0.f, 1.f, 0.f, 0.f), m_fMouseSensor * iMouseMove * fDeltaTime);

	Update_PipeLines();      // 움직였으면 View/Proj 갱신
}
```

- `Create`는 `Initialize_Prototype`, `Clone`은 복사 생성 후 `Initialize(pArg)` (프로토타입 패턴 그대로)
- `Proto::Obj_MapToolCam`, `GO::MapToolCam` 태그를 `Client_Tags.h`에 추가

### 5-3. Level_MapTool — SkyBox와 카메라 배치

**Level_MapTool.h** — private에 선언 추가

```cpp
private:
	HRESULT Ready_Layer_BackGround(const tchar_t* pLayerTag);
	HRESULT Ready_Layer_GameObject(const tchar_t* pLayerTag);
```

**Level_MapTool.cpp** — include와 Initialize에 추가

```cpp
#include "Level_MapTool.h"
#include "MapTool_Cam.h"
#include "SkyBox.h"

HRESULT CLevel_MapTool::Initialize()
{
    if (FAILED(__super::Initialize()))
        return E_FAIL;

    SetWindowText(g_hWnd, L"MapTool_Level");

    if (FAILED(Ready_Layer_BackGround(TEXT("Layer_BackGround")))) return E_FAIL;
    if (FAILED(Ready_Layer_GameObject(TEXT("Layer_GameObject")))) return E_FAIL;
    return S_OK;
}
```

**Ready_Layer_BackGround** — SkyBox + 공용 VS

```cpp
HRESULT CLevel_MapTool::Ready_Layer_BackGround(const tchar_t* pLayerTag)
{
    // ---------- 원형 ----------
    // SkyBox 텍스처
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::MAPTOOL), Proto::Texture_SkyBox,
        CTexture::Create(m_pDevice, m_pContext, TEXT("../../../Resource/Ex/proc_preview.png"), 1))))
        return E_FAIL;

    // SkyBox 객체
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::MAPTOOL), Proto::Obj_SkyBox,
        CSkyBox::Create(m_pDevice, m_pContext))))
        return E_FAIL;

    // 정점 셰이더 (SkyBox와 6단계 StaticProp이 같이 씀)
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::MAPTOOL), Proto::VS_VTXTEX,
        CVertexShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Shader_VtxTex.hlsl", VTXNORM::Elements, VTXNORM::iNumElements, "VS_MAIN"))))
        return E_FAIL;

    // SkyBox 픽셀 셰이더
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::MAPTOOL), Proto::PS_VTXTEX_SKYBOX,
        CPixelShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Shader_VtxTex.hlsl", "PS_MAIN_SKY"))))
        return E_FAIL;

    // SkyBox 정점/인덱스 버퍼
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::MAPTOOL), Proto::VIBuffer_SkyBox,
        CVIBuffer_SkyBox::Create(m_pDevice, m_pContext))))
        return E_FAIL;

    // ---------- 사본 ----------
    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::MAPTOOL), Proto::Obj_SkyBox,
        ETOUI(LEVEL::MAPTOOL), Layer::BackGround, GO::SkyBox)))
        return E_FAIL;

    return S_OK;
}
```

- 레이어 태그는 인자로 받은 `pLayerTag` 대신 `Client_Tags.h`의 `Layer::BackGround`를 쓴다 (값은 같은 `"Layer_BackGround"`)

**Ready_Layer_GameObject** — 카메라

```cpp
HRESULT CLevel_MapTool::Ready_Layer_GameObject(const tchar_t* pLayerTag)
{
    // 카메라 원형
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::MAPTOOL), Proto::Obj_MapToolCam,
        CMapTool_Cam::Create(m_pDevice, m_pContext))))
        return E_FAIL;

    // 카메라 사본
    CMapTool_Cam::CAMERA_MAPTOOL_CAM_DESC         CameraDesc{};
    CameraDesc.fDegreeRotPerSec = 180.f;            // 회전 속도 (도/초)
    CameraDesc.fSpeedPerSec = 20.f;                 // 이동 속도
    CameraDesc.vEye = float4_t(0.f, 0.f, -5.f, 1.f);  // 카메라 위치
    CameraDesc.vAt = float4_t(0.f, 0.f, 0.f, 1.f);    // 바라보는 점 (원점)
    CameraDesc.fFovy = 60.f;
    CameraDesc.fNear = 0.1f;
    CameraDesc.fFar = 1000.f;
    CameraDesc.fSensor = 0.05f;                     // 마우스 감도

    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::MAPTOOL), Proto::Obj_MapToolCam,
        ETOUI(LEVEL::MAPTOOL), pLayerTag, GO::MapToolCam, &CameraDesc)))
        return E_FAIL;

    // 카메라 매니저에 등록 + 메인 카메라로 지정
    auto pMapToolCam = dynamic_pointer_cast<CMapTool_Cam>(CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::MAPTOOL), pLayerTag, GO::MapToolCam));
    CGameInstance::Get().Add_Camera(CAMERA::FREE, pMapToolCam);
    CGameInstance::Get().Set_MainCamera(CAMERA::FREE);

    return S_OK;
}
```

- vcxproj: `MapTool_Cam.h/.cpp`, `..\..\Client\Private\SkyBox.cpp` 등록

### 5-4. 툴 → 카메라 연결 (Scene 창 포커스 + 마우스가 씬 위일 때만 조작)

카메라는 ImGui를 모르므로, 툴이 매 프레임 **두 가지**를 알려 준다.

| 값 | 어디서 오나 (4-8 `CPanel_Scene::Render`) | 없으면 생기는 문제 |
|---|---|---|
| 포커스 (`bSceneFocused`) | `ImGui::IsWindowFocused()` — Scene 창이 마지막으로 클릭된 창인가 | Hierarchy에서 이름을 고치다 우클릭 + WASD를 눌러도 카메라가 움직임 |
| 호버 (`bSceneHovered`) | `ImGui::IsItemHovered()` — 마우스가 씬 이미지 위에 있는가 | Scene을 클릭해 둔 채 마우스를 Inspector 위로 옮겨 우클릭해도 카메라가 움직임 |

**EditorUI.h** — public에 조회 함수 추가

```cpp
	bool_t		GetSceneCliked() { return m_Context.bSceneFocused; }
	bool_t		GetSceneHovered() { return m_Context.bSceneHovered; }
```

**ToolMainApp.h** — private에 선언 추가

```cpp
	void								Sync_SceneView();
```

**ToolMainApp.cpp** — include, Update, 함수 본문 추가

```cpp
#include "MapTool_Cam.h"

void CToolMainApp::Update(f32_t fDeltaTime)
{
    if (FAILED(Begin_ImGui()))
        return;
    m_pEditorUI->Update(fDeltaTime);
    Sync_SceneView();                  // 추가: Scene 창 포커스/호버 → 카메라
    CGameInstance::Get().Update_Engine(fDeltaTime);
}

void CToolMainApp::Sync_SceneView()
{
    auto pCamera = dynamic_pointer_cast<CMapTool_Cam>(CGameInstance::Get().Get_MainCamera());
    if (nullptr == pCamera)
        return;
    pCamera->Set_SceneClicked(m_pEditorUI->GetSceneCliked());    // = Scene 창 IsWindowFocused
    pCamera->Set_SceneHovered(m_pEditorUI->GetSceneHovered());   // = 씬 이미지 IsItemHovered
}
```

- `Sync_SceneView`는 `CEditorUI::Update`(이번 프레임 포커스/호버 갱신) **다음**, `Update_Engine`(카메라 Update) **전**에 불러야 같은 프레임 값이 전달된다

**카메라가 움직이는 조건** (`CMapTool_Cam::Update`)

```
우클릭 누름  AND  Scene 창이 포커스  AND  마우스가 씬 이미지 위
  (DIM::RB)       (m_bSceneClicked)       (m_bSceneHovered)
```

**실행 결과**
- Scene 창에 SkyBox 텍스처(`proc_preview.png`)가 보인다
- Scene 창을 한 번 클릭 → 마우스를 씬 이미지 위에 두고 우클릭 누른 채 WASD로 이동, 마우스로 회전
- Hierarchy/Inspector를 클릭해 포커스를 옮기면 우클릭 + WASD를 해도 안 움직인다
- Scene 창이 포커스여도 마우스가 Hierarchy/Inspector 위나 씬 이미지 위아래의 빈 띠(비율 맞춤으로 생긴 여백) 위에 있으면 안 움직인다

**주의 / 남은 것**
- 마우스 이동량은 이미 "이번 프레임 이동 픽셀"이라 `fDeltaTime`을 곱하면 프레임에 따라 감도가 달라짐 → 곱하기 제거 + `fSensor` 재조정 (남은 작업)
- 피치(위아래) 제한 없음 → 90도 넘으면 뒤집힘 (남은 작업)
- 호버는 **매 프레임** 검사하므로, 우클릭으로 회전하다가 커서가 씬 이미지 밖으로 나가면 그 순간 멈춘다 (DirectInput 마우스 이동량은 커서가 화면 끝에 닿아도 계속 들어오지만, ImGui 커서 위치는 이미지 밖으로 나감). "우클릭을 **시작한 순간** 씬 위였으면 놓을 때까지 계속 조작"으로 바꾸면 해결 (남은 작업)

### 5-5. (참고) 카메라 매니저가 없는 엔진이라면

이 프로젝트는 엔진에 `CCamera_Manager`가 있어서 5-3, 5-4처럼 **등록(`Add_Camera`) → 메인 지정(`Set_MainCamera`) → 꺼내 쓰기(`Get_MainCamera`)**로 처리한다.
카메라 매니저가 없는 엔진에서는 `CToolMainApp`이 카메라를 **직접 들고 있으면** 된다. 실행 결과는 5-4와 같다.

| | 카메라 매니저 있음 (5-3, 5-4) | 카메라 매니저 없음 (이 절) |
|---|---|---|
| 레벨 | 카메라 생성 + `Add_Camera` + `Set_MainCamera` | 카메라 생성만 |
| ToolMainApp | 매 프레임 `Get_MainCamera()`로 꺼냄 | 레벨이 만든 카메라를 **한 번 찾아서** `weak_ptr`로 보관 |
| ToolMainApp이 알아야 하는 것 | 없음 | 카메라가 있는 레벨/레이어/태그 |

**Level_MapTool.cpp** — `Ready_Layer_GameObject`에서 매니저 관련 3줄을 뺀다

```cpp
    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::MAPTOOL), Proto::Obj_MapToolCam,
        ETOUI(LEVEL::MAPTOOL), pLayerTag, GO::MapToolCam, &CameraDesc)))
        return E_FAIL;

    // 카메라 매니저가 없으므로 아래는 쓰지 않는다
    // auto pMapToolCam = dynamic_pointer_cast<CMapTool_Cam>(CGameInstance::Get().Find_GameObject(...));
    // CGameInstance::Get().Add_Camera(CAMERA::FREE, pMapToolCam);
    // CGameInstance::Get().Set_MainCamera(CAMERA::FREE);

    return S_OK;
```

**ToolMainApp.h** — 전방 선언과 멤버 추가

```cpp
#pragma once
#include "MapTool_Defines.h"

NS_BEGIN(Client)
class CMapTool_Cam;                     // MapTool_Cam은 Client 네임스페이스
NS_END

NS_BEGIN(MapTool)
class CEditorUI;
class CToolMainApp final
{
    // ... 기존 멤버 ...
private:
	weak_ptr<CMapTool_Cam>				m_pCamera;      // 주인은 레벨의 레이어 → weak_ptr로 가리키기만
    // ...
};
NS_END
```

**ToolMainApp.cpp** — 레벨을 만든 뒤 카메라를 찾아 두고, 매 프레임 그걸 쓴다

```cpp
HRESULT CToolMainApp::Initialize()
{
    // ... 엔진, ImGui, CEditorUI ...

    if (FAILED(CGameInstance::Get().Change_Level(static_cast<int>(LEVEL::MAPTOOL),
        CLevel_MapTool::Create(m_pDevice, m_pContext))))
        return E_FAIL;

    // 레벨이 카메라를 만들었으므로 이제 찾을 수 있다
    m_pCamera = dynamic_pointer_cast<CMapTool_Cam>(CGameInstance::Get().Find_GameObject(
        ETOUI(LEVEL::MAPTOOL), TEXT("Layer_GameObject"), GO::MapToolCam));
    if (m_pCamera.expired())
        return E_FAIL;

    CGameInstance::Get().Set_DrawToBackBuffer(false);
    return S_OK;
}

void CToolMainApp::Sync_SceneView()
{
    auto pCamera = m_pCamera.lock();    // 레벨이 바뀌어 카메라가 사라졌으면 nullptr
    if (nullptr == pCamera)
        return;
    pCamera->Set_SceneClicked(m_pEditorUI->GetSceneCliked());
    pCamera->Set_SceneHovered(m_pEditorUI->GetSceneHovered());
}
```

**주의**
- **`shared_ptr`로 들고 있으면 안 된다.** 카메라의 주인은 레벨의 레이어다. ToolMainApp이 붙잡고 있으면 레벨을 정리해도 카메라가 메모리에서 사라지지 않는다 (`EDITOR_CONTEXT::pSelected`가 `weak_ptr`인 것과 같은 이유)
- **찾는 시점은 `Change_Level` 다음.** 그 전에는 카메라가 아직 없다. 레이어 태그(`"Layer_GameObject"`)와 GO 태그(`GO::MapToolCam`)가 레벨에서 쓴 값과 같아야 한다
- View/Proj 행렬은 카메라가 스스로 `Update_PipeLines()`로 파이프라인에 넣으므로, 매니저가 없어도 화면은 똑같이 나온다
- 엔진의 절두체 컬링(`CGameObject::Is_BoxInFrustum`)은 `Get_MainCamera()`를 쓴다. 매니저가 없는 엔진이라면 컬링에 쓸 카메라도 다른 방법(예: 파이프라인의 View/Proj로 절두체 계산)으로 넘겨줘야 한다. 맵툴의 SkyBox와 StaticProp은 컬링을 끄고 있어서 지금은 영향이 없다

---

## 6단계. 배치 객체 만들기 — CStaticProp + Hierarchy 생성 메뉴

**목표**: Hierarchy 빈 곳을 우클릭해서 `Add Static_Prop`을 누르면 Scene에 텍스처 입힌 큐브가 나타난다.
이를 위해 배치 가능한 객체의 부모(`CMapObject`), 경로로 리소스를 찾는 캐시(`CAsset_Manager`), 구조물 클래스(`CStaticProp`)를 만든다.

### 6-1. CMapObject + MAPOBJECT_DESC

배치 가능한 객체가 "레벨 번호 + Transform + 메시/텍스처 경로"를 DESC로 받는다. 툴/게임 어느 레벨이든 같은 코드로 동작.

**MapObject.h (Client/Public)**

```cpp
#pragma once
#include "Client_Defines.h"
#include "GameObject.h"
#include <fstream>

NS_BEGIN(Client)
class CMapObject abstract : public CGameObject
{
public:
    typedef struct tagMapObjectDesc : public GAMEOBJECT_DESC
    {
        uint32_t  iLevelIndex = {};                // 컴포넌트를 찾을 레벨 (툴: MAPTOOL, Client: GAMEPLAY)
        float3_t  vPosition = {};
        float3_t  vRotation = {};                  // degree
        float3_t  vScale = { 1.f, 1.f, 1.f };
        wstring_t strMeshPath;                     // "builtin/cube", 나중 "model/xxx.fbx"
        wstring_t strTexturePath;                  // Resource 기준 상대 경로
        bool_t    bEditorMode = { false };         // true면 로직 건너뛰고 렌더만
    }MAPOBJECT_DESC;

protected:
    CMapObject(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
    virtual ~CMapObject() = default;
public:
    virtual HRESULT Initialize(void* pArg) override;

    const float3_t& Get_Position() const { return m_vPosition; }
    const float3_t& Get_Rotation() const { return m_vRotation; }
    const float3_t& Get_Scale()    const { return m_vScale; }
    void Set_Position(const float3_t& v) { m_vPosition = v; Apply_Transform(); }
    void Set_Rotation(const float3_t& v) { m_vRotation = v; Apply_Transform(); }
    void Set_Scale(const float3_t& v)    { m_vScale = v;    Apply_Transform(); }

    virtual void Save_Extra(ofstream& Out) const {}                        // 저장 단계용 (클래스별 추가 값)
    virtual void Load_Extra(ifstream& In, MAPOBJECT_DESC& Desc) {}

    const wstring_t& Get_MeshPath() const    { return m_strMeshPath; }
    const wstring_t& Get_TexturePath() const { return m_strTexturePath; }
protected:
    void Apply_Transform();
protected:
    uint32_t  m_iLevelIndex = {};
    float3_t  m_vPosition = {};
    float3_t  m_vRotation = {};
    float3_t  m_vScale = { 1.f, 1.f, 1.f };
    wstring_t m_strMeshPath;
    wstring_t m_strTexturePath;
    bool_t    m_bEditorMode = { false };
};
NS_END
```

**MapObject.cpp**

```cpp
#include "MapObject.h"

CMapObject::CMapObject(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    :CGameObject(pDevice, pContext)
{
}

HRESULT CMapObject::Initialize(void* pArg)
{
    if (nullptr == pArg)
        return E_FAIL;

    // 1. DESC 값을 멤버로 보관 (Inspector 편집, 저장용 — 행렬에서 다시 뽑지 않기)
    auto pDesc = static_cast<MAPOBJECT_DESC*>(pArg);
    m_iLevelIndex    = pDesc->iLevelIndex;
    m_vPosition      = pDesc->vPosition;
    m_vRotation      = pDesc->vRotation;
    m_vScale         = pDesc->vScale;
    m_strMeshPath    = pDesc->strMeshPath;
    m_strTexturePath = pDesc->strTexturePath;
    m_bEditorMode    = pDesc->bEditorMode;

    // 2. TransformCom 생성 (CGameObject::Initialize)
    if (FAILED(__super::Initialize(pArg)))
        return E_FAIL;

    // 3. 값 → Transform
    Apply_Transform();
    return S_OK;
}

void CMapObject::Apply_Transform()
{
    // 순서: 회전(크기 유지) → 크기 → 위치
    m_pTransformCom->Rotation(m_vRotation.x, m_vRotation.y, m_vRotation.z);
    m_pTransformCom->Set_Scale(m_vScale.x, m_vScale.y, m_vScale.z);
    m_pTransformCom->Set_State(STATE::POSITION,
        XMVectorSet(m_vPosition.x, m_vPosition.y, m_vPosition.z, 1.f));
}
```

### 6-2. Engine — CTransform::Rotation(도 x, y, z)

현재 크기를 유지한 채 기본 축을 오일러 회전시킨다.

```cpp
// Transform.cpp
#include "Transform.h"
#include "ConstantBuffer.h"

void CTransform::Rotation(f32_t fDegreeX, f32_t fDegreeY, f32_t fDegreeZ)
{
	float3_t	vScaled = Get_Scaled();

	vector_t	vRight = vector_t{ 1.f,0.f,0.f,0.f } * vScaled.x;
	vector_t	vUp    = vector_t{ 0.f,1.f,0.f,0.f } * vScaled.y;
	vector_t	vLook  = vector_t{ 0.f,0.f,1.f,0.f } * vScaled.z;

	vector_t	vQuaternion = XMQuaternionRotationRollPitchYaw(
		XMConvertToRadians(fDegreeX), XMConvertToRadians(fDegreeY), XMConvertToRadians(fDegreeZ));
	matrix_t	RotationMatrix = XMMatrixRotationQuaternion(vQuaternion);

	Set_State(STATE::RIGHT, XMVector3TransformNormal(vRight, RotationMatrix));
	Set_State(STATE::UP,    XMVector3TransformNormal(vUp,    RotationMatrix));
	Set_State(STATE::LOOK,  XMVector3TransformNormal(vLook,  RotationMatrix));
}
```

- `Set_Scale(x, y, z)`는 각 축을 정규화한 뒤 크기를 곱한다 → 회전 후 호출해도 회전이 유지됨

**확인**: DESC에 위치/회전/크기를 넣어 만든 객체가 그 값대로 놓인다.

### 6-3. CAsset_Manager — 경로로 찾고, 없으면 로드

"경로로 원형을 찾고, 없으면 로드해서 등록" — 같은 메시/텍스처는 **한 번만** 로드된다.
`Proto::Texture_XXX`처럼 태그를 미리 만들지 않고 **정규화된 경로 자체가 프로토타입 태그**가 된다.

**Engine_Function.h — 경로 정규화 + 상수**

```cpp
// Engine_Function.h는 따로 include하지 않는다.
// Engine_Defines.h가 <algorithm>, <cwctype>, <string> 다음에 이 파일을 include하므로
// replace / transform / towlower를 그대로 쓸 수 있다.
#ifndef Engine_Function_h__
#define Engine_Function_h__

namespace Engine
{
// ... 기존 Safe_Delete 등 ...

constexpr const tchar_t* g_strResourceRoot  = TEXT("../../../Resource/");
constexpr const tchar_t* g_strBuiltinPrefix = TEXT("builtin/");

inline wstring_t Normalize_AssetPath(wstring_t strPath)
{
	// 역슬래시 → 슬래시
	replace(strPath.begin(), strPath.end(), L'\\', L'/');
	// 대문자 → 소문자
	transform(strPath.begin(), strPath.end(), strPath.begin(), ::towlower);
	// 앞의 리소스 루트 제거 → Resource 기준 상대 경로
	const wstring_t strRoot = L"../../../resource/";
	if (0 == strPath.rfind(strRoot, 0))
		strPath.erase(0, strRoot.size());
	return strPath;
}
}

#endif // Engine_Function_h__
```
- 예: `L"Ex\\WoodCrate01.dds"` → `L"ex/woodcrate01.dds"`
- `Engine_Defines.h`에 `<algorithm>`(replace, transform), `<cwctype>`(towlower)이 이 파일보다 먼저 include되어 있어야 함 (없으면 추가). `wstring_t`, `tchar_t`는 바로 앞의 `Engine_Typedef.h`

**Prototype_Manager — Has_Prototype 추가 (`Find_Prototype`이 private이라)**

```cpp
// Prototype_Manager.h — public에 선언
	bool_t	Has_Prototype(uint32_t iLevelIndex, const wstring_t& strPrototypeTag);

// Prototype_Manager.cpp
#include "Prototype_Manager.h"
#include "Prototype.h"

bool_t CPrototype_Manager::Has_Prototype(uint32_t iLevelIndex, const wstring_t& strPrototypeTag)
{
	if (iLevelIndex >= m_iNumLevels)
		return false;
	return nullptr != Find_Prototype(iLevelIndex, strPrototypeTag);
}
```
+ `GameInstance::Has_Prototype` 전달 함수

**Asset_Manager.h / .cpp (Engine)**

**Asset_Manager.h**

```cpp
#pragma once
#include "Engine_Defines.h"

NS_BEGIN(Engine)
class CPrototype;
class CAsset_Manager final
{
private:
	CAsset_Manager(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	~CAsset_Manager() = default;
public:
	HRESULT	Get_Or_Load_Texture(uint32_t iLevelIndex, const wstring_t& strPath, _Out_ wstring_t& strTag);
	HRESULT	Get_or_Load_Mesh(uint32_t iLevelIndex, const wstring_t& strPath, _Out_ wstring_t& strTag);
private:
	shared_ptr<CPrototype> Create_BuiltinMesh(const wstring_t& strTag);
private:
	ComPtr<ID3D11Device>		m_pDevice;
	ComPtr<ID3D11DeviceContext>	m_pContext;
	unordered_set<wstring_t>    m_FailedTags;   // 실패한 경로는 다시 시도하지 않도록 기록
public:
	static unique_ptr<CAsset_Manager> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
};
NS_END
```

**Asset_Manager.cpp**

```cpp
#include "Asset_Manager.h"
#include "GameInstance.h"       // Has_Prototype, Add_Prototype, CTexture, CVIBuffer_Cube/Rect

CAsset_Manager::CAsset_Manager(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	:m_pDevice{pDevice}
	,m_pContext{pContext}
{
}

HRESULT CAsset_Manager::Get_Or_Load_Texture(uint32_t iLevelIndex, const wstring_t& strPath, _Out_ wstring_t& strTag)
{
    strTag = Normalize_AssetPath(strPath);                       // 1. 태그 = 정규화 경로

    if (CGameInstance::Get().Has_Prototype(iLevelIndex, strTag)) // 2. 이미 있으면 끝
        return S_OK;
    if (m_FailedTags.count(strTag))                              // 3. 실패했던 경로면 바로 실패
        return E_FAIL;

    wstring_t strLoadPath = wstring_t(g_strResourceRoot) + strTag;   // 4. 로드
    auto pTexture = CTexture::Create(m_pDevice, m_pContext, strLoadPath.c_str(), 1);
    if (nullptr == pTexture)
    {
        m_FailedTags.insert(strTag);
        return E_FAIL;
    }
    return CGameInstance::Get().Add_Prototype(iLevelIndex, strTag, pTexture);   // 5. 등록
}

HRESULT CAsset_Manager::Get_or_Load_Mesh(uint32_t iLevelIndex, const wstring_t& strPath, _Out_ wstring_t& strTag)
{
    strTag = Normalize_AssetPath(strPath);
    if (CGameInstance::Get().Has_Prototype(iLevelIndex, strTag))
        return S_OK;
    if (m_FailedTags.count(strTag))
        return E_FAIL;

    shared_ptr<CPrototype> pMesh;
    if (0 == strTag.rfind(g_strBuiltinPrefix, 0))       // "builtin/"으로 시작
        pMesh = Create_BuiltinMesh(strTag);
    // else: fbx 모델 로드 (계획서 10단계)

    if (nullptr == pMesh)
    {
        m_FailedTags.insert(strTag);
        return E_FAIL;
    }
    return CGameInstance::Get().Add_Prototype(iLevelIndex, strTag, pMesh);
}

shared_ptr<CPrototype> CAsset_Manager::Create_BuiltinMesh(const wstring_t& strTag)
{
    if (strTag == L"builtin/cube") return CVIBuffer_Cube::Create(m_pDevice, m_pContext);
    if (strTag == L"builtin/rect") return CVIBuffer_Rect::Create(m_pDevice, m_pContext);
    return nullptr;   // pyramid는 VTXCOL이라 텍스처 셰이더와 안 맞아서 제외
}
```

**GameInstance가 소유**

```cpp
// GameInstance.h
#include "Asset_Manager.h"
#pragma region ASSET_MANAGER
	HRESULT	Get_Or_Load_Texture(uint32_t iLevelIndex, const wstring_t& strPath, _Out_ wstring_t& strTag);
	HRESULT	Get_or_Load_Mesh(uint32_t iLevelIndex, const wstring_t& strPath, _Out_ wstring_t& strTag);
#pragma endregion
	unique_ptr<CAsset_Manager>		m_pAsset_Manager = { nullptr };

// GameInstance.cpp — Initialize_Engine (Sampler_Manager 다음)
m_pAsset_Manager = CAsset_Manager::Create(pDevice, pContext);
if (nullptr == m_pAsset_Manager)
    return E_FAIL;

// Release_Engine — 맨 앞에서 먼저 해제
m_pAsset_Manager.reset();
```

- `Engine.vcxproj`에 `Asset_Manager.h/.cpp` 추가 → **Engine 빌드** (EngineSDK/Inc로 헤더 복사됨)

**주의**
- `Add_Prototype`은 같은 태그가 있으면 `E_FAIL` → 반드시 "확인 → 생성 → 등록" 순서
- 없는 경로를 매 프레임 요청해도 `m_FailedTags` 덕에 파일을 계속 열지 않음

### 6-4. Engine — CGameObject::Remove_Component

`Add_Component`는 같은 태그가 있으면 실패하므로, 교체하려면 먼저 지워야 한다.

```cpp
virtual void Remove_Component(const wstring_t& strComponentTag) { m_Components.erase(strComponentTag); }
```

### 6-5. CStaticProp

클래스 하나로 모든 구조물을 표현한다. 메시/텍스처를 경로로 받고, **생성 후에도 교체**할 수 있다 (교체 UI는 10단계).

**태그 (Client_Tags.h)**

```cpp
inline constexpr const wchar_t* Obj_StaticProp = L"Prototype_GameObject_StaticProp";   // Proto
inline constexpr const wchar_t* StaticProp     = L"GameObject_StaticProp";             // GO
```

**StaticProp.h**

```cpp
#pragma once
#include "Client_Defines.h"
#include "MapObject.h"

NS_BEGIN(Client)
class CStaticProp : public CMapObject
{
public:
    typedef struct tagStaticPropDesc : public MAPOBJECT_DESC { } STATICPROP_DESC;
private:
    CStaticProp(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
    ~CStaticProp() = default;
public:
    virtual HRESULT Initialize_Prototype() override;
    virtual HRESULT Initialize(void* pArg) override;
    virtual	void	Priority_Update(f32_t fDeltaTime) override;
    virtual	void	Update(f32_t fDeltaTime) override;
    virtual	void	Late_Update(f32_t fDeltaTime) override;
    virtual HRESULT	Render() override;

    HRESULT Change_Texture(const wstring_t& strTexturePath);
    HRESULT Change_Mesh(const wstring_t& strMeshPath);
private:
    shared_ptr<CTexture>            m_pTextureCom;
    shared_ptr<CVIBuffer>           m_pBufferCom;
    shared_ptr<CVertexShader>       m_pVS;
    shared_ptr<CPixelShader>        m_pPS;
    shared_ptr<CConstantBuffer>     m_pCB;
    CB_PER_OBJECT_LIT               m_tCBData = {};
private:
    HRESULT Ready_Components();
    HRESULT Ready_ConstantBuffer();
    HRESULT Ready_Mesh();
    HRESULT Update_ConstantBuffer(const matrix_t& matWorld);
    HRESULT Bind_Shader(shared_ptr<CVertexShader> pVS, shared_ptr<CPixelShader> pPS);
    HRESULT Bind_ShaderResources(const matrix_t& matWorld);
    HRESULT Render_Mesh(const XMMATRIX& matWorld, ID3D11RasterizerState* pRS, shared_ptr<CPixelShader> pPS);
public:
    static shared_ptr<CStaticProp> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
    virtual shared_ptr<CPrototype> Clone(void* pArg) override;
};
NS_END
```

**StaticProp.cpp**

**include + 생성자**

```cpp
#include "StaticProp.h"

CStaticProp::CStaticProp(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    :CMapObject(pDevice, pContext)
{
}
```

**Initialize_Prototype** — 래스터라이저(컬링 없음) + 머티리얼 (원형에서 한 번, 사본은 복사됨)

```cpp
HRESULT CStaticProp::Initialize_Prototype()
{
    if (FAILED(__super::Initialize_Prototype()))
        return E_FAIL;

    D3D11_RASTERIZER_DESC rsDesc{};
    rsDesc.FillMode = D3D11_FILL_SOLID;
    rsDesc.CullMode = D3D11_CULL_NONE;          // 처음엔 컬링 끄기 (rect 뒷면도 보이게)
    rsDesc.FrontCounterClockwise = false;       // 시계 방향이 앞면
    rsDesc.DepthClipEnable = true;
    m_pDevice->CreateRasterizerState(&rsDesc, m_pRS.GetAddressOf());

    m_tMaterial.Ambient  = float4_t(1.f, 1.f, 1.f, 1.f);
    m_tMaterial.Diffuse  = float4_t(1.f, 1.f, 1.f, 1.f);
    m_tMaterial.Specular = float4_t(0.2f, 0.2f, 0.2f, 16.f);   // w = 반사 강도

    return S_OK;
}
```

**Initialize** — 부모(DESC/Transform) → 컴포넌트 → 상수버퍼

```cpp
HRESULT CStaticProp::Initialize(void* pArg)
{
    if (FAILED(__super::Initialize(pArg)))   return E_FAIL;   // CMapObject
    if (FAILED(Ready_Components()))          return E_FAIL;
    if (FAILED(Ready_ConstantBuffer()))      return E_FAIL;
    return S_OK;
}

HRESULT CStaticProp::Ready_Components()
{
    if (FAILED(Ready_Mesh()))
        return E_FAIL;
    if (FAILED(__super::Add_Component(m_iLevelIndex, Proto::VS_VTXTEX, TEXT("Com_VS"), m_pVS)))
        return E_FAIL;
    if (FAILED(__super::Add_Component(m_iLevelIndex, Proto::PS_VTXTEX_NOLIGHT, TEXT("Com_PS"), m_pPS)))
        return E_FAIL;
    return S_OK;
}

// 생성과 교체가 같은 코드를 쓴다
HRESULT CStaticProp::Ready_Mesh()
{
    if (FAILED(Change_Mesh(m_strMeshPath)))       return E_FAIL;
    if (FAILED(Change_Texture(m_strTexturePath))) return E_FAIL;
    return S_OK;
}

HRESULT CStaticProp::Ready_ConstantBuffer()
{
    m_pCB = CConstantBuffer::Create(m_pDevice, m_pContext, &m_tCBData, sizeof(m_tCBData));
    return nullptr == m_pCB ? E_FAIL : S_OK;
}
```

**Change_Texture / Change_Mesh** — 새 리소스를 **먼저 Get_Or_Load**, 성공하면 기존 컴포넌트 제거 → 추가

```cpp
HRESULT CStaticProp::Change_Texture(const wstring_t& strTexturePath)
{
    wstring_t strTexTag;
    if (FAILED(CGameInstance::Get().Get_Or_Load_Texture(m_iLevelIndex, strTexturePath, strTexTag)))
        return E_FAIL;                              // 실패 시 기존 텍스처 유지

    shared_ptr<CTexture> pNew;
    Remove_Component(TEXT("Com_Texture"));
    if (FAILED(__super::Add_Component(m_iLevelIndex, strTexTag, TEXT("Com_Texture"), pNew)))
        return E_FAIL;

    m_pTextureCom = pNew;
    m_strTexturePath = strTexTag;                   // 저장하는 경로는 정규화된 태그
    return S_OK;
}

HRESULT CStaticProp::Change_Mesh(const wstring_t& strMeshPath)
{
    wstring_t strMeshTag;
    if (FAILED(CGameInstance::Get().Get_or_Load_Mesh(m_iLevelIndex, strMeshPath, strMeshTag)))
        return E_FAIL;

    if (0 != strMeshTag.rfind(g_strBuiltinPrefix, 0))
        return E_FAIL;                              // 모델은 계획서 10단계에서

    shared_ptr<CVIBuffer> pNew;
    Remove_Component(TEXT("Com_Buffer"));
    if (FAILED(__super::Add_Component(m_iLevelIndex, strMeshTag, TEXT("Com_Buffer"), pNew)))
        return E_FAIL;

    m_pBufferCom = pNew;
    m_strMeshPath = strMeshTag;
    return S_OK;
}
```

**Late_Update / Render** — 그리기 순서: 상수버퍼 → 셰이더 → 텍스처 → 버퍼 (`CCube::Render_Mesh` 참고)

```cpp
void CStaticProp::Priority_Update(f32_t fDeltaTime)
{
    __super::Priority_Update(fDeltaTime);
}

void CStaticProp::Update(f32_t fDeltaTime)
{
    __super::Update(fDeltaTime);
}

void CStaticProp::Late_Update(f32_t fDeltaTime)
{
    __super::Late_Update(fDeltaTime);
    CGameInstance::Get().Add_RenderGroup(RENDERID::NONALPHA, dynamic_pointer_cast<CGameObject>(shared_from_this()));
}

HRESULT CStaticProp::Render()
{
    return Render_Mesh(m_pTransformCom->Get_World(), m_pRS.Get(), m_pPS);
}

HRESULT CStaticProp::Update_ConstantBuffer(const matrix_t& matWorld)
{
    XMMATRIX matNoTrans = matWorld;
    matNoTrans.r[3] = XMVectorSet(0.f, 0.f, 0.f, 1.f);                   // 이동 제거
    XMMATRIX matWorldInvTranspos = XMMatrixTranspose(XMMatrixInverse(nullptr, matNoTrans));   // 노멀용

    XMStoreFloat4x4(&m_tCBData.mat_World, matWorld);
    XMStoreFloat4x4(&m_tCBData.mat_WorldInvTranspose, matWorldInvTranspos);
    m_tCBData.tMaterial = m_tMaterial;
    return S_OK;
}

HRESULT CStaticProp::Bind_ShaderResources(const matrix_t& matWorld)
{
    if (FAILED(Update_ConstantBuffer(matWorld)))                                  return E_FAIL;
    if (FAILED(m_pCB->Bind_Vertex_ShaderResource(0, &m_tCBData)))                 return E_FAIL;  // b0
    if (FAILED(m_pCB->Bind_Pixel_ShaderResource(0, &m_tCBData)))                  return E_FAIL;
    if (FAILED(CGameInstance::Get().Bind_Sampler_Pixel_Shader(g_strSampler_Linear, 0))) return E_FAIL;  // s0
    if (FAILED(m_pTextureCom->Bind_Pixel_ShaderResource(0, 0)))                   return E_FAIL;  // t0
    return S_OK;
}

HRESULT CStaticProp::Bind_Shader(shared_ptr<CVertexShader> pVS, shared_ptr<CPixelShader> pPS)
{
    if (FAILED(pVS->Begin())) return E_FAIL;
    if (FAILED(pPS->Begin())) return E_FAIL;
    return S_OK;
}

HRESULT CStaticProp::Render_Mesh(const XMMATRIX& matWorld, ID3D11RasterizerState* pRS, shared_ptr<CPixelShader> pPS)
{
    if (FAILED(__super::Render()))              return E_FAIL;
    m_pContext->RSSetState(pRS);
    if (FAILED(Bind_ShaderResources(matWorld))) return E_FAIL;
    if (FAILED(Bind_Shader(m_pVS, pPS)))        return E_FAIL;
    if (FAILED(m_pBufferCom->Bind_Resources())) return E_FAIL;
    if (FAILED(m_pBufferCom->Render()))         return E_FAIL;
    return S_OK;
}
```

**Create / Clone** — 표준 프로토타입 패턴

```cpp
shared_ptr<CStaticProp> CStaticProp::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto pInstance = shared_ptr<CStaticProp>(new CStaticProp(pDevice, pContext));
    if (FAILED(pInstance->Initialize_Prototype()))
        pInstance.reset();
    return pInstance;
}
shared_ptr<CPrototype> CStaticProp::Clone(void* pArg)
{
    auto pInstance = shared_ptr<CStaticProp>(new CStaticProp(*this));
    if (FAILED(pInstance->Initialize(pArg)))
        pInstance.reset();
    return pInstance;
}
```

- `Client.vcxproj`와 MapTool `Default.vcxproj` 둘 다에 `MapObject.cpp`, `StaticProp.cpp` 추가
- 셰이더: `Shader_VtxTex.hlsl` (정점 형식 VTXNORM) — `VS_MAIN` + `PS_MAIN_NOLIGHT`

### 6-6. Engine — 같은 태그로 두 번 Add하면 실패하게

Hierarchy가 `Prop_00`, `Prop_01` ... 태그를 직접 만들기 때문에, 같은 태그가 조용히 무시되면 "만들었는데 안 생기는" 문제가 생긴다.

```cpp
// Layer.cpp
#include "Layer.h"
#include "GameObject.h"
#include "GameInstance.h"

// 중복 태그면 실패
HRESULT CLayer::Add_GameObject(const wstring_t& strGameObjectTag, shared_ptr<class CGameObject> pGameObject)
{
    if (false == m_GameObjects.emplace(strGameObjectTag, pGameObject).second)
        return E_FAIL;
    return S_OK;
}
```

- `CObject_Manager::Add_GameObject`: `pLayer->Add_GameObject` 실패(중복 태그) 시 `E_FAIL`을 그대로 반환하도록 수정 (새 레이어를 만들 때 / 기존 레이어에 넣을 때 둘 다)

### 6-7. Level_MapTool — StaticProp 원형 등록

**Level_MapTool.h** — private에 선언 추가

```cpp
	HRESULT Ready_Layer_Map(const tchar_t* pLayerTag);
```

**Level_MapTool.cpp** — include와 Initialize (최종)

```cpp
#include "Level_MapTool.h"
#include "MapTool_Cam.h"
#include "SkyBox.h"
#include "StaticProp.h"

HRESULT CLevel_MapTool::Initialize()
{
    if (FAILED(__super::Initialize()))
        return E_FAIL;

    SetWindowText(g_hWnd, L"MapTool_Level");

    if (FAILED(Ready_Layer_BackGround(TEXT("Layer_BackGround")))) return E_FAIL;
    if (FAILED(Ready_Layer_GameObject(TEXT("Layer_GameObject")))) return E_FAIL;
    if (FAILED(Ready_Layer_Map(TEXT("Layer_Map"))))               return E_FAIL;
    return S_OK;
}
```

**Ready_Layer_Map**

```cpp
HRESULT CLevel_MapTool::Ready_Layer_Map(const tchar_t* pLayerTag)
{
    // 픽셀 셰이더 (VS_VTXTEX는 Ready_Layer_BackGround에서 이미 등록됨)
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::MAPTOOL), Proto::PS_VTXTEX_NOLIGHT,
        CPixelShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Shader_VtxTex.hlsl", "PS_MAIN_NOLIGHT"))))
        return E_FAIL;

    // Obj_StaticProp 객체 원형
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::MAPTOOL), Proto::Obj_StaticProp,
        CStaticProp::Create(m_pDevice, m_pContext))))
        return E_FAIL;

    return S_OK;
}
```

- **메시/텍스처 원형은 여기서 등록하지 않는다** — `CAsset_Manager`가 필요할 때 로드 (6-3)
- 사본은 만들지 않는다. 사본은 Hierarchy가 `Layer_Map`에 만든다 (6-9). 그래서 인자 `pLayerTag`(`"Layer_Map"`)는 이 함수에서 쓰지 않는다

### 6-8. EditorUI_Defines.h — 메시/텍스처 목록 추가

`EDITOR_CONTEXT` 아래에 추가. 생성 기본값(이번 단계)과 Inspector 콤보(10단계)가 같이 쓴다.

```cpp
// { 표시 이름, 경로 } 목록 (Inspector 콤보, Hierarchy 생성 기본값)
struct ASSET_ITEM
{
	const char*		pName;		// 콤보 표시용
	const wchar_t*	pPath;		// DESC에 넣을 경로 (텍스처는 Resource 기준 상대 경로)
};

inline constexpr ASSET_ITEM g_Meshes[] = {
	{ "Cube", L"builtin/cube" },
	{ "Rect", L"builtin/rect" },
};

inline constexpr ASSET_ITEM g_Textures[] = {
	{ "WoodCrate01", L"Ex/WoodCrate01.dds" },
	{ "WoodCrate02", L"Ex/WoodCrate02.dds" },
};
```

- `inline constexpr` 배열: 헤더에 두어도 여러 cpp에서 중복 정의 에러가 안 남 (C++17)

### 6-9. CPanel_Hierarchy — 빈 곳 우클릭으로 생성

**Panel_Hierarchy.h** — private에 추가

```cpp
private:
	// 빈 곳 우클릭 메뉴에 보일 배치 가능한 목록
	struct PLACEABLE
	{
		const char*		pName;				// 메뉴에 보일 이름
		const wchar_t*	pPrototypeTag;		// Add_GameObject에 넘길 프로토타입 태그
	};

	static constexpr PLACEABLE s_Placeables[] = {
		{ "Add Static_Prop", Proto::Obj_StaticProp },
	};

private:
	uint32_t	m_iNextID = {};						// "Prop_N"의 N

private:
	void		Create_Object(const wchar_t* pPrototypeTag);
```

**Panel_Hierarchy.cpp** — include 추가 + Create_Object (기본값으로 생성 + 고유 태그)

```cpp
#include "EditorUI_Utils.h"
#include "Panel_Hierarchy.h"
#include "StaticProp.h"

void CPanel_Hierarchy::Create_Object(const wchar_t* pPrototypeTag)
{
    CStaticProp::STATICPROP_DESC Desc{};
    Desc.iLevelIndex    = ETOUI(LEVEL::MAPTOOL);
    Desc.strMeshPath    = g_Meshes[0].pPath;       // 기본: cube
    Desc.strTexturePath = g_Textures[0].pPath;     // 기본: 첫 텍스처
    Desc.bEditorMode    = true;

    // 비어 있는 Prop_NN이 나올 때까지 번호 증가 (삭제 대기 중 객체, 불러온 맵과도 안 겹치게)
    wstring_t strTag;
    do {
        if (m_iNextID < 10)
            strTag = L"Prop_0" + to_wstring(m_iNextID++);    // Prop_00 ~ Prop_09 (map 정렬 순서 유지)
        else
            strTag = L"Prop_" + to_wstring(m_iNextID++);
    }
    while (nullptr != CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::MAPTOOL), TEXT("Layer_Map"), strTag));

    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::MAPTOOL), pPrototypeTag,
        ETOUI(LEVEL::MAPTOOL), TEXT("Layer_Map"), strTag, &Desc)))
    {
        MSG_BOX("Create Failed");
        return;
    }
}
```

**Render** — 빈 곳 우클릭 메뉴

```cpp
void CPanel_Hierarchy::Render(const PANEL_RECT& tRect)
{
    Set_NextPanelRect(tRect);
    if (ImGui::Begin("Hierarchy", nullptr, g_FixedPanelFlags))
    {
        // 빈 곳 우클릭 메뉴 — 항목 위에서는 안 열림 (7·8단계에서 붙는 항목 메뉴와 겹치지 않게)
        if (ImGui::BeginPopupContextWindow("HierarchyMenu",
            ImGuiPopupFlags_MouseButtonRight | ImGuiPopupFlags_NoOpenOverItems))
        {
            for (auto& Item : s_Placeables)
            {
                if (ImGui::MenuItem(Item.pName))      // "Add Static_Prop"
                    Create_Object(Item.pPrototypeTag);
            }
            ImGui::EndPopup();
        }
    }
    ImGui::End();
}
```

**처음 나오는 ImGui 함수 / 값**

| 함수 / 값 | 하는 일 | 자세히 |
|---|---|---|
| `ImGui::BeginPopupContextWindow(ID, 플래그)` | **지금 창**을 우클릭하면 열리는 메뉴(팝업) | 안에서 "이번 프레임에 오른쪽 버튼을 뗐고, 마우스가 이 창 위에 있나"를 검사해서 맞으면 팝업을 연다. 팝업이 **열려 있는 동안 매 프레임** `true` → 그 안에 `MenuItem`을 넣고 **`true`일 때만** `EndPopup()`. `ID`(`"HierarchyMenu"`)는 팝업을 구분하는 이름 |
| `ImGuiPopupFlags_MouseButtonRight` | 오른쪽 버튼으로 열기 | `MouseButtonLeft`, `MouseButtonMiddle`도 있다 |
| `ImGuiPopupFlags_NoOpenOverItems` | 마우스가 **위젯(항목) 위에 있으면 열지 않음** | 내부적으로 `IsAnyItemHovered()`를 본다. 7·8단계에서 목록 항목에 따로 메뉴를 붙이므로, 이게 없으면 항목을 우클릭했을 때 두 메뉴가 겹친다. 마우스가 항목 위인지 알려면 항목들이 먼저 그려져 있어야 하므로 이 메뉴는 목록 **뒤에** 둔다 |
| `ImGui::EndPopup()` | 팝업 끝 | `BeginPopup*`이 `true`였을 때만 호출. 팝업 안의 `MenuItem`을 클릭하면 팝업은 자동으로 닫힌다 |

- 비슷한 함수: `BeginPopupContextItem()`(바로 앞 **위젯**을 우클릭, 8단계), `BeginPopupContextVoid()`(어떤 ImGui 창도 없는 **빈 바탕**을 우클릭)

**실행 결과**
- Hierarchy 빈 곳을 우클릭 → `Add Static_Prop` → Scene 가운데(원점)에 나무상자 텍스처(`WoodCrate01`)를 입힌 큐브가 나타난다 (카메라가 `(0, 0, -5)`에서 원점을 보고 있음)
- 여러 번 누르면 같은 자리에 겹쳐 생긴다 (위치는 9단계 Inspector에서 바꾼다)
- 텍스처 로드는 한 번만 일어난다 (`CAsset_Manager::Get_Or_Load_Texture`의 `CTexture::Create` 줄에 중단점을 걸면 처음 한 번만 걸림)

**주의**
- Engine 헤더(Asset_Manager, Prototype_Manager, GameObject, Engine_Function) 수정 → **Engine 먼저 빌드** → MapTool 빌드
- 생성이 실패하면 `"Create Failed"` 메시지 박스 → 셰이더 원형(`VS_VTXTEX`, `PS_VTXTEX_NOLIGHT`)이 MAPTOOL 레벨에 등록됐는지, 텍스처 경로(`Resource/Ex/WoodCrate01.dds`)가 있는지 확인

---

## 7단계. Hierarchy 목록 + 선택

**목표**: Hierarchy에 만든 객체의 이름이 목록으로 보이고, 클릭하면 선택(하이라이트)된다. 새로 만든 객체는 바로 선택된다.
Hierarchy는 **이름 + 선택만** 담당하고, 값은 전부 Inspector(9·10단계)에서 바꾼다.

### 7-1. Engine — 레이어의 객체 목록 조회

```cpp
// Layer.h — public
	shared_ptr<CGameObject>	Find_GameObject(const wstring_t& strGameObjectTag);
	const map<const wstring_t, shared_ptr<CGameObject>>& Get_GameObjects() const { return m_GameObjects; }
```

```cpp
// Object_Manager.cpp
const map<const wstring_t, shared_ptr<CGameObject>>* CObject_Manager::Get_GameObjects(uint32_t iLayerLevelIndex, const wstring_t& strLayerTag)
{
	auto pLayer = Find_Layer(iLayerLevelIndex, strLayerTag);
	if (nullptr == pLayer)
		return nullptr;                 // 레이어가 아직 없으면 nullptr (객체를 하나도 안 만든 상태)
	return &pLayer->Get_GameObjects();
}
```

```cpp
// GameInstance.h / .cpp — 전달 함수
const map<const wstring_t, shared_ptr<CGameObject>>* Get_GameObjects(uint32_t iLayerLevelIndex, const wstring_t& strLayerTag);
// → return m_pObject_Manager->Get_GameObjects(iLayerLevelIndex, strLayerTag);
```

- `Object_Manager.h`에도 같은 선언 추가

### 7-2. EditorUI_Defines.h — 선택 상태 추가

선택은 Hierarchy가 바꾸고 Inspector가 읽으므로 `EDITOR_CONTEXT`에 둔다. (나중에 Scene 피킹으로 선택할 때도 여기에 쓴다)

맨 위 include 추가

```cpp
#pragma once
#include "MapTool_Defines.h"
#include "MapObject.h"          // 추가: weak_ptr<CMapObject>, (8단계) Is_Dead()
```

`EDITOR_CONTEXT`에 추가

```cpp
struct EDITOR_CONTEXT
{
	// ---------- 선택 ----------
	weak_ptr<CMapObject>	pSelected;			// weak_ptr: 지워지면 자동으로 만료
	wstring_t				strSelectedTag;

	// ---------- Scene 창 ---------- (4단계)
	float2_t	vImageMin = {};
	float2_t	vImageSize = {};
	bool_t		bSceneHovered = {};
	bool_t		bSceneFocused = {};

	void Select(const wstring_t& strTag, shared_ptr<CGameObject> pObject)
	{
		strSelectedTag = strTag;
		pSelected = dynamic_pointer_cast<CMapObject>(pObject);
	}
};
```

### 7-3. EditorUI_Utils.h — 문자열 변환 도우미 추가

엔진은 `wstring`, ImGui는 **UTF-8 `char*`** 를 쓴다.

```cpp
// wstring → UTF-8 (ImGui에 표시할 때)
inline string To_UTF8(const wstring_t& strWide)
{
	if (strWide.empty())
		return {};
	// 1번째 호출: 필요한 버퍼 크기만 구함
	int32_t iSize = WideCharToMultiByte(CP_UTF8, 0, strWide.c_str(), (int)strWide.size(), nullptr, 0, nullptr, nullptr);
	string strOut(iSize, '\0');
	// 2번째 호출: 실제 변환
	WideCharToMultiByte(CP_UTF8, 0, strWide.c_str(), (int)strWide.size(), strOut.data(), iSize, nullptr, nullptr);
	return strOut;
}

// UTF-8 → wstring (ImGui 입력을 엔진에 넘길 때)
inline wstring_t To_Wide(const char* pUTF8)
{
	int32_t iSize = MultiByteToWideChar(CP_UTF8, 0, pUTF8, -1, nullptr, 0);   // -1: 널 문자까지 포함
	if (iSize <= 1)
		return {};
	wstring_t strOut(iSize - 1, L'\0');                                        // 널 문자 제외
	MultiByteToWideChar(CP_UTF8, 0, pUTF8, -1, strOut.data(), iSize);
	return strOut;
}
```

### 7-4. CPanel_Hierarchy — 목록 그리기 + 선택

**Create_Object** 맨 끝에 추가 — 만든 객체를 바로 선택

```cpp
    // 만든 객체를 바로 선택
    m_Context.Select(strTag, CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::MAPTOOL), TEXT("Layer_Map"), strTag));
}
```

**Render** — `Begin` 안, 빈 곳 우클릭 메뉴 **앞**에 목록 추가

```cpp
    if (ImGui::Begin("Hierarchy", nullptr, g_FixedPanelFlags))
    {
        // ---------- 목록 (이름만) ----------
        auto pObjects = CGameInstance::Get().Get_GameObjects(ETOUI(LEVEL::MAPTOOL), TEXT("Layer_Map"));
        if (nullptr != pObjects)
        {
            for (auto& [strTag, pObject] : *pObjects)
            {
                if (nullptr == pObject)
                    continue;

                // Selectable(라벨, 선택 표시) → 클릭한 프레임에 true
                if (ImGui::Selectable(To_UTF8(strTag).c_str(), strTag == m_Context.strSelectedTag))
                    m_Context.Select(strTag, pObject);
            }
        }

        // 빈 곳 우클릭 메뉴 (6단계)
        ...
    }
    ImGui::End();
```

**처음 나오는 ImGui 함수**

| 함수 | 하는 일 | 자세히 |
|---|---|---|
| `ImGui::Selectable(라벨, 선택됨)` | 클릭할 수 있는 한 줄 | 하는 일이 두 가지다. **① 그리기**: 라벨을 한 줄로 그리고, 두 번째 인자가 `true`면 하이라이트(선택 색)로 칠한다. **② 클릭 감지**: 이 줄의 사각형 안에서 왼쪽 클릭이 일어난 **그 한 프레임에만** `true`를 돌려준다 |

- 두 번째 인자 `strTag == m_Context.strSelectedTag`는 **하이라이트로 그릴지**만 정한다. 클릭 감지는 ImGui가 마우스 위치와 버튼으로 직접 한다
- 인자는 함수 실행 **전에** 계산되므로, 클릭한 프레임에는 이전 선택이 하이라이트되고 **다음 프레임부터** 새 항목이 하이라이트된다 (60fps에서 약 16ms라 눈에는 안 보임)
- 선택 상태를 기억하는 건 ImGui가 아니라 우리(`m_Context`)라서, 매 프레임 "이 줄이 선택된 줄인가"를 다시 넘겨 줘야 한다

**실행 결과**
- 객체를 만들 때마다 Hierarchy에 `Prop_00`, `Prop_01` ... 이 순서대로 쌓이고, 방금 만든 항목이 하이라이트된다
- 항목을 클릭하면 그 항목으로 하이라이트가 옮겨간다
- 항목 위에서 우클릭하면 생성 메뉴가 열리지 않는다 (`ImGuiPopupFlags_NoOpenOverItems`)

**주의**
- 여러 항목이 같은 라벨이면 ID가 겹침 → 태그는 고유하므로 문제 없음 (같은 이름이 필요하면 `"이름##고유ID"` 또는 `PushID`)
- 객체 이름이 깨져 보이면 wstring을 `To_UTF8` 없이 넘긴 것

---

## 8단계. 삭제

**목표**: 항목 우클릭 → `Delete` 또는 Delete 키로 선택한 객체를 지운다. 지운 프레임에 바로 Scene에서 사라지고 목록에서도 빠진다.

### 8-1. Engine — 삭제(Dead) 방식

목록을 순회하는 도중(ImGui 루프, 엔진 Update 루프)에 `erase`하면 반복자가 깨진다. 그래서 **표시만 해 두고, 프레임 맨 앞에서 한꺼번에 지운다.**

**CGameObject — Dead 플래그**

```cpp
public:
	virtual void		Set_Dead() { m_bDead = true; }
	virtual bool_t		Is_Dead()const { return m_bDead; }
protected:
	bool_t				m_bDead = { false };
```

**CLayer**

```cpp
// Layer.h — public
	void		Remove_Dead();
```

```cpp
// Layer.cpp
// Update / Late_Update는 Dead 객체 건너뛰기
void CLayer::Update(f32_t fTimeDelta)
{
    for (auto& Pair : m_GameObjects)
        if (nullptr != Pair.second && !Pair.second->Is_Dead())
            Pair.second->Update(fTimeDelta);
}
// Late_Update도 같은 조건 → Dead 객체는 RenderGroup에 안 들어감 = 같은 프레임에 안 보임

void CLayer::Remove_Dead()
{
    for (auto iter = m_GameObjects.begin(); iter != m_GameObjects.end(); )
    {
        if (nullptr == iter->second || iter->second->Is_Dead())
            iter = m_GameObjects.erase(iter);      // erase가 다음 반복자를 돌려줌
        else
            ++iter;
    }
}
```

- 삭제 경로는 Dead 하나로 통일한다 (태그로 바로 erase하는 함수는 두지 않는다)

**CObject_Manager**

```cpp
void CObject_Manager::Priority_Update(f32_t fDeltaTime)
{
	for (uint32_t i = 0; i < m_iNumLevels; ++i)
		for (auto& Pair : m_pLayers[i])
			if (nullptr != Pair.second)
			{
				Pair.second->Remove_Dead();          // 순회 전에 erase (프레임 맨 앞)
				Pair.second->Priority_Update(fDeltaTime);
			}
}
```

**프레임 순서와 삭제 타이밍**
```
CEditorUI::Update (ImGui)  → Set_Dead()           ← 삭제 요청
Update_Engine              → Priority_Update      ← Remove_Dead로 실제 erase
                           → Update / Late_Update (Dead는 건너뜀)
Draw                                               ← 이미 없음 → 같은 프레임에 사라짐
```

### 8-2. EditorUI_Defines.h — 선택 해제 함수 추가

`EDITOR_CONTEXT`에 추가

```cpp
	void Clear_Selection()
	{
		pSelected.reset();
		strSelectedTag.clear();
	}

	// 선택한 객체가 지워졌으면 선택 해제 (9단계 Inspector가 매 프레임 호출)
	void Validate_Selection()
	{
		auto pObject = pSelected.lock();
		if (nullptr == pObject || pObject->Is_Dead())
			Clear_Selection();
	}
```

### 8-3. CPanel_Hierarchy — 항목 우클릭 / Delete 키

**Panel_Hierarchy.h** (최종)

```cpp
#pragma once
#include "Panel.h"

NS_BEGIN(MapTool)
// 객체 이름 목록 + 선택 + 우클릭 생성/삭제
// 값 편집은 하지 않는다 (Inspector 담당)
class CPanel_Hierarchy final : public CPanel
{
private:
	explicit CPanel_Hierarchy(EDITOR_CONTEXT& Context) : CPanel{ Context } {}
public:
	virtual ~CPanel_Hierarchy() = default;

public:
	virtual void	Render(const PANEL_RECT& tRect) override;

private:
	// 빈 곳 우클릭 메뉴에 보일 배치 가능한 목록
	struct PLACEABLE
	{
		const char*		pName;				// 메뉴에 보일 이름
		const wchar_t*	pPrototypeTag;		// Add_GameObject에 넘길 프로토타입 태그
	};

	static constexpr PLACEABLE s_Placeables[] = {
		{ "Add Static_Prop", Proto::Obj_StaticProp },
	};

private:
	uint32_t	m_iNextID = {};						// "Prop_N"의 N
	bool_t		m_bRequestDelete = { false };		// 목록 루프가 끝난 뒤 삭제

private:
	void		Create_Object(const wchar_t* pPrototypeTag);
	void		Delete_Selected();

public:
	static unique_ptr<CPanel_Hierarchy> Create(EDITOR_CONTEXT& Context);
};
NS_END
```

**Delete_Selected**

```cpp
void CPanel_Hierarchy::Delete_Selected()
{
    auto pSelected = m_Context.pSelected.lock();
    if (nullptr == pSelected)
        return;

    pSelected->Set_Dead();          // 실제 erase는 엔진 Priority_Update에서
    m_Context.Clear_Selection();    // 선택은 바로 해제 (erase 전까지 weak_ptr가 살아 있으므로)
}
```

**Render** (최종)

```cpp
void CPanel_Hierarchy::Render(const PANEL_RECT& tRect)
{
    Set_NextPanelRect(tRect);
    if (ImGui::Begin("Hierarchy", nullptr, g_FixedPanelFlags))
    {
        // ---------- 목록 (이름만) ----------
        auto pObjects = CGameInstance::Get().Get_GameObjects(ETOUI(LEVEL::MAPTOOL), TEXT("Layer_Map"));
        if (nullptr != pObjects)
        {
            for (auto& [strTag, pObject] : *pObjects)
            {
                if (nullptr == pObject || pObject->Is_Dead())     // 추가: 지운 객체는 목록에서 빼기
                    continue;

                // Selectable(라벨, 선택 표시) → 클릭한 프레임에 true
                if (ImGui::Selectable(To_UTF8(strTag).c_str(), strTag == m_Context.strSelectedTag))
                    m_Context.Select(strTag, pObject);

                // 항목 우클릭 메뉴 — 반드시 Selectable "바로 다음 줄" (바로 앞 위젯 ID로 항목별 메뉴가 됨)
                if (ImGui::BeginPopupContextItem())
                {
                    // 우클릭한 항목을 선택 상태로 (다른 객체가 지워지는 혼동 방지)
                    m_Context.Select(strTag, pObject);

                    if (ImGui::MenuItem("Delete", "Del"))
                        m_bRequestDelete = true;             // 루프 중엔 플래그만 (map 순회 중)

                    ImGui::EndPopup();
                }
            }
        }

        // 우클릭 삭제 — 목록 루프가 끝난 뒤 처리
        if (m_bRequestDelete)
        {
            Delete_Selected();
            m_bRequestDelete = false;
        }

        // Delete 키 삭제 (Hierarchy 창이 포커스일 때만)
        if (ImGui::IsWindowFocused() && ImGui::IsKeyPressed(ImGuiKey_Delete))
            Delete_Selected();

        // 빈 곳 우클릭 메뉴 — 항목 위에서는 안 열림 (두 메뉴가 겹치지 않게)
        if (ImGui::BeginPopupContextWindow("HierarchyMenu",
            ImGuiPopupFlags_MouseButtonRight | ImGuiPopupFlags_NoOpenOverItems))
        {
            for (auto& Item : s_Placeables)
            {
                if (ImGui::MenuItem(Item.pName))      // "Add Static_Prop"
                    Create_Object(Item.pPrototypeTag);
            }
            ImGui::EndPopup();
        }
    }
    ImGui::End();
}
```

**처음 나오는 ImGui 함수 / 값**

| 함수 / 값 | 하는 일 | 자세히 |
|---|---|---|
| `ImGui::BeginPopupContextItem()` | **바로 앞 위젯**을 우클릭하면 열리는 메뉴 | 인자를 생략하면 오른쪽 버튼이 기본값. 안에서 팝업 ID로 **마지막 위젯의 ID**(`LastItemData.ID`)를 쓰고, "오른쪽 버튼을 뗐고(`IsMouseReleased`) 마우스가 마지막 위젯 위에 있나(`IsItemHovered`)"를 검사해서 팝업을 연다. 그래서 반드시 `Selectable` **바로 다음 줄**에 있어야 줄마다 따로 메뉴가 된다. 열려 있는 동안 매 프레임 `true`, `true`일 때만 `EndPopup()` |
| `ImGui::IsKeyPressed(키)` | 이 키를 **누른 순간**인가 | 누르고 있으면 일정 간격으로 다시 `true`(키 반복). 반복을 막으려면 두 번째 인자에 `false`. **어느 창에서 눌렀는지는 상관하지 않는다** → 그래서 `IsWindowFocused()`와 같이 써서 Hierarchy가 포커스일 때만 반응하게 한다 |
| `ImGuiKey_Delete` | Delete 키 | ImGui 키 열거형(`ImGuiKey_A`, `ImGuiKey_Enter`, `ImGuiKey_Escape` …). Win32 백엔드가 가상 키 코드를 이 값으로 바꿔 넣어 준다 |

| | 좌클릭 (`Selectable`) | 우클릭 (`BeginPopupContextItem`) |
|---|---|---|
| 대상 | 자기 자신(그 줄) | 바로 앞 위젯(그 줄) |
| `true`가 되는 때 | 클릭한 **한 프레임** | 메뉴가 **열려 있는 동안 매 프레임** |

**실행 결과**
- 항목 우클릭 → `Delete` → 그 객체가 Scene과 목록에서 같은 프레임에 사라진다
- 항목을 클릭해 선택하고 Delete 키를 눌러도 지워진다 (Hierarchy 창이 포커스일 때)
- 지운 뒤 새로 만들면 번호가 이어진다 (지운 번호를 다시 쓰지 않음)

**주의**
- `Set_Dead()`만 하고 erase는 엔진에 맡기므로 지운 직후에도 `Find_GameObject`에는 잠깐 걸림 → 태그 생성 루프가 그것도 피함
- 삭제 시 크래시(반복자 무효)가 나면 목록 루프 안에서 지운 것 → 플래그 + 루프 뒤 처리, 실제 erase는 `Remove_Dead`

---

## 9단계. Inspector — 이름 + Transform

**목표**: 선택한 객체의 이름과 위치/회전/크기가 Inspector에 보이고, 값을 바꾸면 Scene에서 바로 움직인다.

```
Inspector
 Prop_01
 ─────────────────
 ▼ Transform            ← 모든 CMapObject 공통
   Position  x y z
   Rotation  x y z      (도)
   Scale     x y z
 ▼ Static Prop          ← 10단계
```

### 9-1. Panel_Inspector.h

```cpp
#pragma once
#include "Panel.h"

NS_BEGIN(MapTool)
// 선택한 객체의 이름, Transform, 타입별 섹션(Static Prop: Mesh / Texture)
// 타입별 섹션은 dynamic_pointer_cast로 분기 (ImGui 코드를 Client 클래스에 넣지 않기)
class CPanel_Inspector final : public CPanel
{
private:
	explicit CPanel_Inspector(EDITOR_CONTEXT& Context) : CPanel{ Context } {}
public:
	virtual ~CPanel_Inspector() = default;

public:
	virtual void	Render(const PANEL_RECT& tRect) override;

public:
	static unique_ptr<CPanel_Inspector> Create(EDITOR_CONTEXT& Context);
};
NS_END
```

### 9-2. Panel_Inspector.cpp

```cpp
#include "EditorUI_Utils.h"
#include "Panel_Inspector.h"

void CPanel_Inspector::Render(const PANEL_RECT& tRect)
{
    Set_NextPanelRect(tRect);
    if (ImGui::Begin("Inspector", nullptr, g_FixedPanelFlags))
    {
        m_Context.Validate_Selection();             // 지워졌으면 선택 해제
        auto pSelected = m_Context.pSelected.lock();
        if (nullptr == pSelected)
            ImGui::TextDisabled("No object selected");
        else
        {
            // ---------- 이름 ----------
            ImGui::TextUnformatted(To_UTF8(m_Context.strSelectedTag).c_str());
            ImGui::Separator();

            // ---------- Transform ----------
            if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
            {
                // 값 복사 → 위젯 → 바뀐 프레임에만 Set (Set이 Apply_Transform까지 호출)
                float3_t vPos = pSelected->Get_Position();
                if (ImGui::DragFloat3("Position", &vPos.x, 0.1f))
                    pSelected->Set_Position(vPos);

                float3_t vRot = pSelected->Get_Rotation();
                if (ImGui::DragFloat3("Rotation", &vRot.x, 1.f))
                    pSelected->Set_Rotation(vRot);

                float3_t vScale = pSelected->Get_Scale();
                if (ImGui::DragFloat3("Scale", &vScale.x, 0.05f, 0.01f, 100.f))   // 0 크기 방지
                    pSelected->Set_Scale(vScale);
            }

            // 10단계: 타입별 섹션
        }
    }
    ImGui::End();
}

unique_ptr<CPanel_Inspector> CPanel_Inspector::Create(EDITOR_CONTEXT& Context)
{
    return unique_ptr<CPanel_Inspector>(new CPanel_Inspector(Context));
}
```

**처음 나오는 ImGui 함수 / 값**

| 함수 / 값 | 하는 일 | 자세히 |
|---|---|---|
| `ImGui::TextDisabled(글자)` | 회색(비활성 색) 글자 | `printf`처럼 서식 문자열을 받는다(`TextDisabled("%d개", n)`). 그래서 `%`가 들어갈 수 있는 사용자 문자열은 넘기지 않는다 |
| `ImGui::TextUnformatted(글자)` | 서식 해석 없이 글자 그대로 | 객체 이름처럼 **임의의 문자열**은 이걸 쓴다 (`%`가 섞여 있어도 안전, 서식 처리도 안 해서 빠름) |
| `ImGui::Separator()` | 가로 구분선 | |
| `ImGui::CollapsingHeader(라벨, 플래그)` | 접고 펼 수 있는 섹션 제목 | 펼쳐져 있으면 `true` → 그 안에 위젯을 넣는다. `TreeNode`와 달리 **`End` 함수가 없다** |
| `ImGuiTreeNodeFlags_DefaultOpen` | 처음에 펼친 상태로 시작 | 이후에는 사용자가 접은 상태를 ImGui가 기억한다 |
| `ImGui::DragFloat3(라벨, float* v, 속도, 최소, 최대)` | float 3개를 마우스 드래그로 편집 | `v`는 float 3개가 연속된 배열의 시작 주소(`&vPos.x`). 칸을 좌우로 드래그하면 `속도`만큼씩 바뀌고, **더블클릭 / Ctrl+클릭**하면 숫자를 직접 입력한다. `최소`, `최대`를 주면 그 범위로 제한(둘 다 0이면 제한 없음). **값이 바뀐 프레임에 `true`** → 그때만 객체에 반영한다 |

- 라벨(`"Position"`, `"Rotation"`, `"Scale"`)은 칸 **오른쪽**에 표시되고, 같은 창 안에서 서로 달라야 한다 (2-0의 "라벨 = ID")

**실행 결과**
- 아무것도 선택 안 하면 회색 글씨 `No object selected`
- 객체를 선택하면 이름(`Prop_00`)과 Transform 값이 보인다
- Position 칸을 좌우로 드래그하면 Scene에서 바로 움직임 (더블클릭/Ctrl+클릭하면 숫자 직접 입력)
- Rotation은 도 단위, Scale은 0.01 ~ 100으로 제한
- 선택한 객체를 지우면 Inspector가 바로 선택 없음 상태

**주의**
- `DragFloat3`에 `&vPos.x`를 넘기는 건 `float3_t`(XMFLOAT3)가 float 3개가 연속이라 가능

---

## 10단계. Inspector — Static Prop (Mesh / Texture 교체)

**목표**: 선택한 객체가 `CStaticProp`이면 Inspector에 Mesh / Texture 콤보가 나오고, 바꾸면 즉시 모양과 텍스처가 바뀐다.

```
 ▼ Static Prop          ← dynamic_pointer_cast<CStaticProp> 성공 시만
   Mesh    [Cube        ▼]
   Texture [WoodCrate01 ▼]
```

### 10-1. EditorUI_Utils.h — 콤보 템플릿 추가

`{ pName, pPath }` 구조의 정적 배열(`g_Meshes`, `g_Textures`)이면 무엇이든 콤보로 그린다. 템플릿이라 헤더에 둔다.

`{ pName, pPath }` 구조의 정적 배열(`g_Meshes`, `g_Textures`)이면 무엇이든 콤보로 그린다. 템플릿이라 헤더에 둔다.

```cpp
// strCurrent : 객체가 지금 가진 경로 (정규화된 태그, 소문자)
// OnChange   : 다른 항목을 골랐을 때 호출 (고른 항목의 원본 경로를 넘김)
template<typename ITEM, size_t N, typename FUNC>
void Render_AssetCombo(const char* pLabel, const ITEM(&Items)[N], const wstring_t& strCurrent, FUNC&& OnChange)
{
	// 1. 현재 값이 목록의 몇 번째인지 (목록 경로도 정규화해서 비교 — 객체 경로는 소문자)
	int32_t iCurrent = -1;
	for (int32_t i = 0; i < static_cast<int32_t>(N); ++i)
	{
		if (Normalize_AssetPath(Items[i].pPath) == strCurrent)
		{
			iCurrent = i;
			break;
		}
	}

	// 2. 닫혀 있을 때 보일 글자 — 목록에 없으면(불러온 맵 등) 경로 그대로
	const string strPreview = (-1 != iCurrent) ? Items[iCurrent].pName : To_UTF8(strCurrent);

	// 3. 콤보
	if (ImGui::BeginCombo(pLabel, strPreview.c_str()))
	{
		for (int32_t i = 0; i < static_cast<int32_t>(N); ++i)
		{
			const bool_t bSelected = (i == iCurrent);
			if (ImGui::Selectable(Items[i].pName, bSelected) && !bSelected)
				OnChange(Items[i].pPath);

			if (bSelected)
				ImGui::SetItemDefaultFocus();     // 열었을 때 현재 항목으로 스크롤
		}
		ImGui::EndCombo();
	}
}
```

**처음 나오는 ImGui 함수**

| 함수 | 하는 일 | 자세히 |
|---|---|---|
| `ImGui::BeginCombo(라벨, 미리보기글자)` | 드롭다운(콤보) 시작 | 닫혀 있을 때는 `미리보기글자`만 보이고, 클릭해서 **펼쳐져 있는 동안** `true` → 그 안에 `Selectable`로 항목을 넣는다. **`true`일 때만** `EndCombo()` |
| `ImGui::EndCombo()` | 콤보 끝 | `BeginCombo()`가 `true`였을 때만 호출. 안의 `Selectable`을 클릭하면 콤보는 자동으로 닫힌다 |
| `ImGui::SetItemDefaultFocus()` | 바로 앞 위젯을 기본 포커스로 | 콤보를 열었을 때 현재 항목으로 **스크롤**되고 키보드 내비게이션이 그 항목에서 시작한다. 콤보 안에서 현재 선택된 `Selectable` 바로 다음에 부른다 |

- 콤보 안의 `Selectable`은 7단계 Hierarchy와 같은 함수다. 두 번째 인자로 현재 항목을 표시하고, 클릭하면 `true`
- `Selectable(...) && !bSelected`: 이미 선택된 항목을 다시 눌렀을 때는 리소스를 다시 바꾸지 않도록 거른다

### 10-2. Panel_Inspector.cpp — Static Prop 섹션

include 추가

```cpp
#include "EditorUI_Utils.h"
#include "Panel_Inspector.h"
#include "StaticProp.h"         // 추가: dynamic_pointer_cast<CStaticProp>
```

`Render`의 Transform 섹션 다음(`// 10단계: 타입별 섹션` 자리)에 추가

```cpp
            // ---------- 타입별 섹션 (툴에서 분기 — Client 클래스에 ImGui 코드 넣지 않기) ----------
            if (auto pProp = dynamic_pointer_cast<CStaticProp>(pSelected))
            {
                if (ImGui::CollapsingHeader("Static Prop", ImGuiTreeNodeFlags_DefaultOpen))
                {
                    Render_AssetCombo("Mesh", g_Meshes, pProp->Get_MeshPath(),
                        [&](const wchar_t* pPath) { if (FAILED(pProp->Change_Mesh(pPath)))    MSG_BOX("Mesh Change Failed"); });
                    Render_AssetCombo("Texture", g_Textures, pProp->Get_TexturePath(),
                        [&](const wchar_t* pPath) { if (FAILED(pProp->Change_Texture(pPath))) MSG_BOX("Texture Change Failed"); });
                }
            }
```

**Panel_Inspector.cpp** (최종)

```cpp
#include "EditorUI_Utils.h"
#include "Panel_Inspector.h"
#include "StaticProp.h"

void CPanel_Inspector::Render(const PANEL_RECT& tRect)
{
    Set_NextPanelRect(tRect);
    if (ImGui::Begin("Inspector", nullptr, g_FixedPanelFlags))
    {
        m_Context.Validate_Selection();             // 지워졌으면 선택 해제
        auto pSelected = m_Context.pSelected.lock();
        if (nullptr == pSelected)
            ImGui::TextDisabled("No object selected");
        else
        {
            // ---------- 이름 ----------
            ImGui::TextUnformatted(To_UTF8(m_Context.strSelectedTag).c_str());
            ImGui::Separator();

            // ---------- Transform ----------
            if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
            {
                // 값 복사 → 위젯 → 바뀐 프레임에만 Set (Set이 Apply_Transform까지 호출)
                float3_t vPos = pSelected->Get_Position();
                if (ImGui::DragFloat3("Position", &vPos.x, 0.1f))
                    pSelected->Set_Position(vPos);

                float3_t vRot = pSelected->Get_Rotation();
                if (ImGui::DragFloat3("Rotation", &vRot.x, 1.f))
                    pSelected->Set_Rotation(vRot);

                float3_t vScale = pSelected->Get_Scale();
                if (ImGui::DragFloat3("Scale", &vScale.x, 0.05f, 0.01f, 100.f))   // 0 크기 방지
                    pSelected->Set_Scale(vScale);
            }

            // ---------- 타입별 섹션 (툴에서 분기 — Client 클래스에 ImGui 코드 넣지 않기) ----------
            if (auto pProp = dynamic_pointer_cast<CStaticProp>(pSelected))
            {
                if (ImGui::CollapsingHeader("Static Prop", ImGuiTreeNodeFlags_DefaultOpen))
                {
                    Render_AssetCombo("Mesh", g_Meshes, pProp->Get_MeshPath(),
                        [&](const wchar_t* pPath) { if (FAILED(pProp->Change_Mesh(pPath)))    MSG_BOX("Mesh Change Failed"); });
                    Render_AssetCombo("Texture", g_Textures, pProp->Get_TexturePath(),
                        [&](const wchar_t* pPath) { if (FAILED(pProp->Change_Texture(pPath))) MSG_BOX("Texture Change Failed"); });
                }
            }
        }
    }
    ImGui::End();
}

unique_ptr<CPanel_Inspector> CPanel_Inspector::Create(EDITOR_CONTEXT& Context)
{
    return unique_ptr<CPanel_Inspector>(new CPanel_Inspector(Context));
}
```

**실행 결과**
- 선택한 객체의 Inspector에 `Static Prop` 섹션이 생기고, Mesh는 `Cube`, Texture는 `WoodCrate01`로 표시된다
- Mesh를 `Rect`로 바꾸면 큐브가 사각형 판 하나로 바뀐다 (컬링이 꺼져 있어 뒷면도 보임)
- Texture를 `WoodCrate02`로 바꾸면 즉시 다른 상자 텍스처로 바뀐다
- 다른 객체를 선택하면 그 객체의 값이 콤보에 표시된다

**주의**
- `DragFloat3`에 `&vPos.x`를 넘기는 건 `float3_t`(XMFLOAT3)가 float 3개가 연속이라 가능
- 텍스처/메시 목록을 늘리려면 `EditorUI_Defines.h`의 `g_Meshes` / `g_Textures`에 한 줄 추가하면 끝 (경로는 Resource 기준)

---

## 11. 현재 상태와 남은 작업

### 완료
- [x] MapTool 프로젝트 + ImGui 연동 (DPI, ESC 처리)
- [x] 메뉴바 + 3창 고정 레이아웃 (`CEditorUI` + `CPanel_Hierarchy / Scene / Inspector`)
- [x] Scene 창 RTT (비율 유지)
- [x] 맵툴 카메라 (게임오브젝트, 우클릭 + WASD + 마우스)
- [x] `CMapObject` + DESC, `CTransform::Rotation(도)`
- [x] `CAsset_Manager` (경로 정규화, Get_Or_Load, 실패 기록)
- [x] `CStaticProp` (생성/교체가 같은 `Change_Mesh/Change_Texture` 사용)
- [x] 엔진 Dead 삭제 방식, `Get_GameObjects`, 중복 태그 `E_FAIL`
- [x] Hierarchy (우클릭 생성/삭제, Delete 키, 선택)
- [x] Inspector (Transform, Mesh/Texture 콤보)

### 남은 작업 (우선순위 순)
1. **카메라 정리**
   - 마우스 회전에서 `* fDeltaTime` 제거 후 `fSensor` 재조정
   - Scene 이미지 **가로 가운데 정렬** (`vCursor.x = (vAvail.x - vSize.x) * 0.5f`)
   - (권장) 지금은 매 프레임 호버를 검사해서 회전 중 커서가 씬 밖으로 나가면 멈춤 → 우클릭을 **시작한 순간** 씬 위였으면 놓을 때까지 계속 조작, 피치 제한
2. **저장 / 불러오기** (계획서 6단계)
   - 파일 형식: 헤더 `"DKMP"` + 버전 → 개수 → [프로토 태그, 메시 경로, 텍스처 경로, 위치/회전/크기 float×9, 추가 데이터 크기, 추가 데이터]
   - `Parse_Map(경로, vector<DESC>&)` / `Spawn_Map(레벨, 레이어, Descs)`로 분리 (Client Loader 스레드 대비)
   - 메뉴 New/Open/Save/Save As 활성화, `GetOpenFileName/GetSaveFileName` + `OFN_NOCHANGEDIR`
3. **Client에서 불러오기** (계획서 7단계) → 1차 완성
4. 기존 Client 클래스를 `CMapObject`로 옮기기 (계획서 8단계)
5. 모델(fbx) 전환 (계획서 10단계), 피킹/기즈모/복제/Undo (계획서 9단계)

### 알려진 작은 문제
- `Change_Mesh/Change_Texture`: `Get_Or_Load` 성공 후 `Remove_Component` → `Add_Component`가 실패하면 기존 컴포넌트가 이미 지워진 상태가 됨 (Clone 실패는 드묾. 안전하게 하려면 Add 실패 시 기존 것을 다시 넣기)
- `CAsset_Manager` 로드 실패 시 `E_FAIL`만 반환 → 호출부(Inspector)에서 `MSG_BOX`로 알림. 생성 시 실패는 `"Create Failed"`

---

## 부록 A. 사용한 ImGui 함수/위젯 정리

> 규칙 요약
> - **`Begin`은 반환값과 상관없이 항상 `End`.**
> - **`BeginMainMenuBar / BeginMenu / BeginPopup* / BeginCombo`는 true일 때만 `End*`.**
> - 위젯은 대부분 "값이 바뀐/클릭된 프레임에 true"를 반환 → `if`로 감싸서 처리.
> - `GetItemRect*`, `IsItemHovered`, `BeginPopupContextItem`은 **바로 앞 위젯** 기준.
> - 문자열은 UTF-8 `const char*` (wstring은 `To_UTF8`로 변환).

### A-1. 초기화 / 프레임 / 종료

| 함수 | 용도 | 쓴 곳 |
|---|---|---|
| `IMGUI_CHECKVERSION()` | 헤더/소스 버전 일치 검사 | Ready_ImGui |
| `ImGui::CreateContext()` | ImGui 컨텍스트 생성 | Ready_ImGui |
| `ImGui::GetIO()` | 설정/입력/출력/폰트 구조체 (`ImGuiIO&`) | Ready_ImGui, Calc_Layout, WndProc |
| `io.ConfigFlags \|= ImGuiConfigFlags_NavEnableKeyboard` | 키보드로 위젯 이동 | Ready_ImGui |
| `ImGui::StyleColorsDark()` | 다크 테마 | Ready_ImGui |
| `ImGui_ImplWin32_EnableDpiAwareness()` | DPI 인식 (창 생성 전) | wWinMain |
| `ImGui_ImplWin32_Init(hWnd)` | Win32 백엔드 | Ready_ImGui |
| `ImGui_ImplDX11_Init(pDevice, pContext)` | DX11 백엔드 | Ready_ImGui |
| `ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam)` | 메시지를 ImGui에 먼저 전달 (헤더에서 `#if 0`이라 `extern` 직접 선언) | WndProc |
| `ImGui::GetCurrentContext()` | 컨텍스트 존재 여부 | WndProc |
| `io.WantCaptureKeyboard` | ImGui가 키보드를 쓰는 중인지 (입력칸 등) | WndProc (ESC) |
| `ImGui_ImplDX11_NewFrame()` → `ImGui_ImplWin32_NewFrame()` → `ImGui::NewFrame()` | 프레임 시작 (이 순서) | Begin_ImGui |
| `ImGui::Render()` → `ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData())` | 그리기 (씬 Draw 뒤, Present 전) | Render_ImGui |
| `ImGui_ImplDX11_Shutdown()` → `ImGui_ImplWin32_Shutdown()` → `ImGui::DestroyContext()` | 종료 (엔진 해제 전) | Shutdown_ImGui |

### A-2. 창 / 레이아웃

| 함수 | 용도 | 쓴 곳 |
|---|---|---|
| `ImGui::SetNextWindowPos(ImVec2(x, y), ImGuiCond_Always)` | 다음 Begin 창 위치 강제 | Set_NextPanelRect |
| `ImGui::SetNextWindowSize(ImVec2(w, h), ImGuiCond_Always)` | 다음 Begin 창 크기 강제 | Set_NextPanelRect |
| `ImGui::Begin(이름, nullptr, flags)` / `ImGui::End()` | 창 열기/닫기. 2번째 인자 nullptr → X 버튼 없음 | 세 창 |
| `ImGuiWindowFlags_NoMove / NoResize / NoCollapse / NoSavedSettings` | 고정 창 (`g_FixedPanelFlags`) | 세 창 |
| `ImGuiWindowFlags_NoScrollbar / NoScrollWithMouse` | 스크롤 없음 | Scene |
| `ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0))` / `ImGui::PopStyleVar()` | 창 안쪽 여백 임시 변경 (Begin 전에 Push, 후에 Pop) | Scene |
| `ImGui::GetContentRegionAvail()` | 현재 커서부터 남은 공간 크기 | Scene |
| `ImGui::SetCursorPos(ImVec2)` | 다음 위젯 위치 (창 기준) | Scene |
| `ImGui::GetWindowHeight()` | 현재 창 높이 | 메뉴바 높이 |
| `ImGui::IsWindowFocused()` | 현재 창이 포커스인지 (Begin~End 안에서) | Scene(카메라), Hierarchy(Delete 키) |
| `ImGui::ShowDemoWindow(&bOpen)` | 데모 창 (모든 위젯 예제) | View 메뉴 |

### A-3. 메뉴바 / 메뉴

| 함수 | 용도 | 쓴 곳 |
|---|---|---|
| `ImGui::BeginMainMenuBar()` / `ImGui::EndMainMenuBar()` | 화면 맨 위 메뉴바 (Begin 창 바깥에서) | Render_MenuBar |
| `ImGui::BeginMenu("File")` / `ImGui::EndMenu()` | 펼쳐지는 메뉴 | File, View |
| `ImGui::MenuItem(라벨, 단축키글자, bSelected, bEnabled)` | 메뉴 항목, 클릭 시 true. 단축키는 표시만 | File 항목(비활성), Delete, Add |
| `ImGui::MenuItem(라벨, nullptr, &bValue)` | bool 토글 (체크 표시) | ImGui Demo |

### A-4. 목록 / 팝업 (Hierarchy)

| 함수 | 용도 | 쓴 곳 |
|---|---|---|
| `ImGui::Selectable(라벨, bSelected)` | 클릭 가능한 줄, 클릭 시 true. bSelected면 하이라이트 | 객체 목록, 콤보 항목 |
| `ImGui::BeginPopupContextItem()` / `ImGui::EndPopup()` | **바로 앞 위젯** 우클릭 메뉴 | 항목 우클릭 → Delete |
| `ImGui::BeginPopupContextWindow(id, flags)` / `ImGui::EndPopup()` | 창 우클릭 메뉴 | 빈 곳 우클릭 → Add |
| `ImGuiPopupFlags_MouseButtonRight` | 우클릭으로 열기 | 위 |
| `ImGuiPopupFlags_NoOpenOverItems` | 항목 위에서는 안 열림 (항목 메뉴와 안 겹치게) | 위 |
| `ImGui::IsKeyPressed(ImGuiKey_Delete)` | 키를 누른 프레임에 true | Delete 키 삭제 |

### A-5. 표시 / 편집 (Inspector)

| 함수 | 용도 | 쓴 곳 |
|---|---|---|
| `ImGui::TextUnformatted(str)` | 서식 없는 텍스트 (`%` 해석 안 함 → 이름 표시에 안전) | 객체 이름 |
| `ImGui::TextDisabled(str)` | 회색 텍스트 | "No object selected" |
| `ImGui::Separator()` | 가로 구분선 | 이름 아래 |
| `ImGui::CollapsingHeader(라벨, ImGuiTreeNodeFlags_DefaultOpen)` | 접히는 섹션, 펼쳐져 있으면 true. 처음엔 열린 상태 | Transform, Static Prop |
| `ImGui::DragFloat3(라벨, float* v, 속도, 최소, 최대)` | float 3개 드래그 편집, 바뀐 프레임에 true. 더블클릭/Ctrl+클릭으로 직접 입력 | Position(0.1), Rotation(1.0), Scale(0.05, 0.01~100) |
| `ImGui::BeginCombo(라벨, 미리보기글자)` / `ImGui::EndCombo()` | 드롭다운. 안에서 Selectable로 항목 | Mesh, Texture |
| `ImGui::SetItemDefaultFocus()` | 콤보를 열면 이 항목으로 스크롤/포커스 | 현재 선택 항목 |

### A-6. 이미지 / 아이템 정보 (Scene)

| 함수 | 용도 | 쓴 곳 |
|---|---|---|
| `ImGui::Image((ImTextureID)pSRV, ImVec2 size)` | 텍스처 표시. DX11은 `ID3D11ShaderResourceView*`를 그대로 넘김 | 씬 RTT |
| `ImGui::GetItemRectMin()` | 바로 앞 아이템의 화면 기준 좌상단 | 피킹용 이미지 좌표 |
| `ImGui::IsItemHovered()` | 바로 앞 아이템 위에 마우스가 있는지 | 이미지 hover |

### A-7. 자주 쓰는 타입

| 타입 | 설명 |
|---|---|
| `ImVec2(x, y)` | 2D 벡터 (위치/크기) |
| `ImTextureID` | 텍스처 핸들 (DX11에서는 SRV 포인터) |
| `ImGuiWindowFlags_*`, `ImGuiPopupFlags_*`, `ImGuiTreeNodeFlags_*`, `ImGuiCond_*`, `ImGuiStyleVar_*`, `ImGuiKey_*` | 각종 옵션 열거형 (`\|`로 조합) |

---

## 부록 B. 커밋 기록

| 커밋 | 내용 |
|---|---|
| `347d306a4` ImGui 추가중 | MapTool 프로젝트 추가, ImGui 소스, Sampler_Manager, Engine.dll 복사 |
| `d91aaa0b1` 상수버퍼 크기 수정 | Default.cpp 정리 (창 크기/DPI) |
| `a553b15dc` ImGui 수정중 | ToolApp, 에디터 UI(레이아웃/메뉴/Scene), Level_MapTool, MapTool_Cam, Camera_Manager |
| `a030c72b4` 맵툴 수정 | SkyBox, Renderer(백버퍼 그리기 옵션), Scene 창 비율 |
| `0545bc72d` 파이프라인 카메라 적용 완료 | CCamera를 게임오브젝트로, PipeLine/ConstantBuffer, 셰이더 |
| `7bdfd68df` 맵툴 카메라 게임오브젝트로 변경 | CMapTool_Cam 재작성, ToolMainApp Sync_SceneView |
| `b3caf4dd7` / `364bbb3b4` | `Has_Prototype`, `Normalize_AssetPath`, MapTool_Plan.md 작성 |
| `08436eeff` 맵툴 구현중 | CMapObject, CStaticProp, CAsset_Manager, 중복 태그 E_FAIL |
| `b4d46a84e` 하이어라키창 수정중 | Dead 삭제, Get_GameObjects, Hierarchy 창 |
| `41a779582` 하이어라키 + 인스펙터창 구현 완료 | Remove_Component, Change_Mesh/Texture, Inspector 창 |

---

## 부록 C. 자주 겪는 문제

| 증상 | 원인 / 해결 |
|---|---|
| Engine 헤더를 고쳤는데 MapTool에서 안 보임 | **Engine 먼저 빌드** (EngineSDK/Inc로 복사됨) → MapTool 빌드 |
| 실행 시 Engine.dll 없음 | `MapTool/Bin/Engine.dll` 복사 확인 |
| 셰이더 로드 실패 | 빌드 후 이벤트 xcopy로 `MapTool/Bin/Shader/`에 복사됐는지, 작업 디렉터리가 `Bin`인지 |
| 객체 이름이 깨져 보임 | wstring을 `To_UTF8` 없이 ImGui에 넘김 |
| ImGui 창에 입력이 안 들어감 | WndProc 맨 앞에 `ImGui_ImplWin32_WndProcHandler` 호출 누락 |
| 입력칸에서 ESC 누르면 툴 종료 | `io.WantCaptureKeyboard` 검사 |
| Scene 창이 까맣다 | `Set_DrawToBackBuffer(false)` 후 `ImGui::Image`에 `Get_SceneSRV()`를 넘겼는지, ImGui Render가 씬 Draw 뒤인지 |
| 씬이 ImGui 창 뒤 전체 화면에도 보임 | `Set_DrawToBackBuffer(false)` 누락 |
| 씬 텍스처에 아무것도 안 그려짐 | 씬 텍스처와 깊이 버퍼의 크기/샘플 수가 다름, 또는 `OMSetRenderTargets`로 원래 타깃을 복구하지 않아 이후 그리기가 엉뚱한 곳으로 감 |
| 디버그 출력에 "still bound on input" 경고 | SRV로 묶인 채 같은 텍스처를 RTV로 묶음 → 읽기가 끝나면 `PSSetShaderResources(0, 1, {nullptr})`로 풀기 |
| 우클릭 메뉴가 두 개 겹쳐 열림 | 빈 곳 메뉴에 `ImGuiPopupFlags_NoOpenOverItems` |
| 항목 메뉴가 엉뚱한 항목에 붙음 | `BeginPopupContextItem`을 `Selectable` 바로 다음에 호출 |
| 삭제 시 크래시 (반복자 무효) | 목록 루프 안에서 지우지 말 것 → 플래그 + 루프 뒤 처리, 실제 erase는 `Remove_Dead` |
| 같은 객체를 두 번 Add하면 실패 | 정상 — 중복 태그는 `E_FAIL`. 태그 생성 루프에서 `Find_GameObject`로 피함 |
| 콤보 현재 값이 안 잡힘 | 객체 경로는 소문자 정규화됨 → 목록 경로도 `Normalize_AssetPath`해서 비교 |
| 카메라 감도가 프레임마다 다름 | 마우스 이동량에 `fDeltaTime`을 곱하지 말 것 |
