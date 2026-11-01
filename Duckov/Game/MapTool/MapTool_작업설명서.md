# MapTool 작업 설명서

> 이 문서만 보고 **지금의 맵툴(Hierarchy + Scene + Inspector, StaticProp 생성/삭제/편집)을 처음부터 똑같이 다시 만들 수 있도록** 작업 순서대로 정리한 설명서입니다.
> 각 단계는 **목표 → 수정 파일 → 코드 → 확인 방법 → 주의** 순서로 적었습니다.
> 마지막에 **사용한 ImGui 함수/위젯 정리**(부록 A)가 있습니다.

---

## 목차

- [0. 전체 그림](#0-전체-그림)
- [1단계. MapTool 프로젝트 만들기](#1단계-maptool-프로젝트-만들기)
- [2단계. ImGui 붙이기 (WinMain / WndProc / 초기화 / 프레임 순서)](#2단계-imgui-붙이기)
- [3단계. 에디터 UI 뼈대 — 메뉴바 + 창 3개](#3단계-에디터-ui-뼈대--메뉴바--창-3개)
- [4단계. Scene 창에 게임 화면 넣기 (RTT)](#4단계-scene-창에-게임-화면-넣기-rtt)
- [5단계. 맵툴 카메라 (게임오브젝트 카메라)](#5단계-맵툴-카메라)
- [6단계. Level_MapTool 구성 (SkyBox, 카메라, 맵 레이어)](#6단계-level_maptool-구성)
- [7단계. CMapObject + MAPOBJECT_DESC](#7단계-cmapobject--mapobject_desc)
- [8단계. CAsset_Manager (경로로 찾고, 없으면 로드)](#8단계-casset_manager)
- [9단계. CStaticProp](#9단계-cstaticprop)
- [10단계. 엔진: 삭제(Dead)와 객체 목록 조회](#10단계-엔진-삭제dead와-객체-목록-조회)
- [11단계. Hierarchy 창](#11단계-hierarchy-창)
- [12단계. Inspector 창](#12단계-inspector-창)
- [13. 현재 상태와 남은 작업](#13-현재-상태와-남은-작업)
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
   ├─ Public/     MapTool_Defines.h, ToolMainApp.h, Level_MapTool.h, MapTool_Cam.h, ImGui_Manager.h,
   │              EditorUI.h, EditorUI_Defines.h, EditorUI_Utils.h,
   │              Panel.h, Panel_Hierarchy.h, Panel_Scene.h, Panel_Inspector.h
   ├─ Private/    ToolMainApp.cpp, Level_MapTool.cpp, MapTool_Cam.cpp, ImGui_Manager.cpp,
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

## 1단계. MapTool 프로젝트 만들기

**목표**: 솔루션에 MapTool 실행 프로젝트를 추가하고, Engine.dll과 Client 코드를 가져다 쓸 수 있게 한다.

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

### 1-3. Client 코드 가져오기
- 맵툴은 Client 클래스를 **소스째로 같이 컴파일**한다 (vcxproj에 `..\..\Client\Private\*.cpp` 추가)
  - 현재 포함: `MapObject.cpp`, `StaticProp.cpp`, `SkyBox.cpp`, `Free_Cam.cpp`, `BackGround.cpp`, `Cube.cpp` 등
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

---

## 2단계. ImGui 붙이기

**목표**: 툴 창 위에 ImGui가 그려지고 마우스/키보드 입력이 ImGui로 들어간다.

### 2-1. ImGui 소스 추가
- `MapTool/ImGui/`에 아래 파일을 넣고 vcxproj에 추가
  - `imgui.cpp, imgui_draw.cpp, imgui_widgets.cpp, imgui_tables.cpp, imgui_demo.cpp`
  - `imgui_impl_win32.cpp/.h, imgui_impl_dx11.cpp/.h`
  - `imgui.h, imconfig.h, imgui_internal.h, imstb_rectpack.h, imstb_textedit.h, imstb_truetype.h`
- ImGui cpp 파일들은 **미리 컴파일된 헤더 사용 안 함**으로 설정 (pch를 쓰는 경우)

### 2-2. Default.cpp (WinMain / WndProc)

```cpp
#include "imgui.h"              // ImGui::GetIO()를 사용하기 위해
#include "imgui_impl_win32.h"
#include "framework.h"
#include "Default.h"
#include "ToolMainApp.h"

HINSTANCE hInst;
HWND      g_hWnd;

// imgui_impl_win32.h에서 #if 0으로 막혀 있으므로 직접 선언
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int APIENTRY wWinMain(...)
{
#ifdef _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
    ImGui_ImplWin32_EnableDpiAwareness();     // DPI 인식 (창을 만들기 전에)
    ... MyRegisterClass / InitInstance ...

    unique_ptr<CToolMainApp> pToolMainApp = CToolMainApp::Create();
    CGameInstance::Get().Add_Timer(TEXT("Timer_Default"));
    CGameInstance::Get().Add_Timer(TEXT("Timer_60"));

    f32_t fTimeDeltaAcc = {};
    bool_t bDone = false;
    while (!bDone)
    {
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (WM_QUIT == msg.message) bDone = true;
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
        }
        if (bDone) break;

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
```

- `MyRegisterClass`: `wcex.lpszMenuName = 0;` (윈도우 기본 메뉴 제거 — ImGui 메뉴바를 쓰므로)
- `InitInstance`: 클라이언트 영역이 정확히 1600x900이 되도록 DPI 고려해서 창 크기 계산 + 작업 영역 가운데 배치

```cpp
RECT rc{ 0, 0, g_iToolWinSizeX, g_iToolWinSizeY };
AdjustWindowRectExForDpi(&rc, WS_OVERLAPPEDWINDOW, FALSE, 0, GetDpiForSystem());
const int iWinW = rc.right - rc.left;
const int iWinH = rc.bottom - rc.top;
RECT rcWork{};
SystemParametersInfoW(SPI_GETWORKAREA, 0, &rcWork, 0);
const int iPosX = rcWork.left + ((rcWork.right - rcWork.left) - iWinW) / 2;
const int iPosY = rcWork.top  + ((rcWork.bottom - rcWork.top) - iWinH) / 2;
HWND hWnd = CreateWindowW(szWindowClass, L"MapTool", WS_OVERLAPPEDWINDOW,
    iPosX, iPosY, iWinW, iWinH, nullptr, nullptr, hInstance, nullptr);
```

- `WndProc`: **ImGui가 먼저** 메시지를 받는다

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

### 2-3. CToolMainApp (엔진 + ImGui 초기화)

**ToolMainApp.h**

```cpp
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
	unique_ptr<CEditorUI>					m_pEditorUI = { nullptr };
	bool_t								m_bReadyImGui = { false };
private:
	HRESULT		Ready_ImGui();
	HRESULT		Begin_ImGui();
	HRESULT		Render_ImGui();
	HRESULT		Shutdown_ImGui();
	void		Sync_SceneView();
public:
	static unique_ptr<CToolMainApp> Create();
};
NS_END
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
    if (FAILED(Ready_ImGui()))
        return E_FAIL;

    m_pEditorUI = CEditorUI::Create();
    if (nullptr == m_pEditorUI)
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Change_Level(static_cast<int>(LEVEL::MAPTOOL),
        CLevel_MapTool::Create(m_pDevice, m_pContext))))
        return E_FAIL;

    CGameInstance::Get().Set_DrawToBackBuffer(false);   // 4단계: 씬을 백버퍼에 그리지 않음
    return S_OK;
}
```

**Ready_ImGui** — 컨텍스트 → IO 설정 → 스타일 → 백엔드 (폰트는 따로 넣지 않으면 ImGui 기본 폰트 사용)

```cpp
HRESULT CToolMainApp::Ready_ImGui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();                           // 설정, 입력, 출력, 폰트
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;   // 키보드로 위젯 이동

    ImGui::StyleColorsDark();

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

CToolMainApp::~CToolMainApp()
{
    m_pEditorUI.reset();            // 툴 먼저
    Shutdown_ImGui();           // ImGui 정리
    CGameInstance::Get().Release_Engine();   // 엔진은 마지막
}
```

**Update / Render** — 프레임 순서가 중요

```cpp
void CToolMainApp::Update(f32_t fDeltaTime)
{
    if (FAILED(Begin_ImGui()))
        return;
    m_pEditorUI->Update(fDeltaTime);      // ImGui 화면 (생성/삭제/편집이 여기서 일어남)
    Sync_SceneView();                  // Scene 창 포커스 → 카메라
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

    CGameInstance::Get().Draw();      // 씬 → SceneRTV

    if (FAILED(Render_ImGui()))       // ImGui → 백버퍼 (씬보다 나중!)
        return E_FAIL;

    CGameInstance::Get().Present();
    return S_OK;
}
```

> 참고: `CImGui_Manager` 클래스(Initialize/Begin_Frame/Render)도 같은 내용으로 만들어 두었지만, 현재는 `CToolMainApp`이 직접 처리하고 있다. 둘 중 하나만 쓰면 된다.

**확인**: `View → ImGui Demo`로 데모 창이 뜨고, 클릭/드래그가 된다.

---

## 3단계. 에디터 UI 뼈대 — 메뉴바 + 창 3개

**목표**: 위에 메뉴바, 아래에 `Hierarchy | Scene | Inspector` 세 창이 화면을 꽉 채우고 움직이지 않는다. (도킹 없이 직접 좌표 계산)
창 하나가 클래스 하나가 되도록 구조를 잡고 시작한다.

### 3-1. 구조

```
CEditorUI  (메뉴바 + 레이아웃 계산 + EDITOR_CONTEXT 보관 + 패널 3개 소유)
 ├─ CPanel_Hierarchy   객체 목록, 선택, 생성/삭제          (11단계)
 ├─ CPanel_Scene       씬 텍스처 표시, 포커스/hover 기록    (4단계)
 └─ CPanel_Inspector   선택 객체의 값 편집                 (12단계)
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
#include "MapObject.h"

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
	// 11단계: 선택 상태
};

NS_END
```

- `MapObject.h`는 11단계에서 선택 객체(`CMapObject`)의 `Is_Dead()`를 부르기 위해 include (완전한 타입 필요)

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

// 11단계: To_UTF8, To_Wide
// 12단계: Render_AssetCombo

NS_END
```

- 헤더에 함수 본문을 두므로 `inline` 필수 (여러 cpp에서 include해도 중복 정의 에러가 안 나게)

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
        // 11단계에서 채움
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
- `Panel_Inspector.cpp` → 창 이름 `"Inspector"` (본문은 12단계)

### 3-6. EditorUI.h

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

- `CToolMainApp`에서 `#include "EditorUI.h"`, 멤버 `unique_ptr<CEditorUI> m_pEditorUI`, `Initialize`에서 `m_pEditorUI = CEditorUI::Create();`, `Update`에서 `m_pEditorUI->Update(fDeltaTime);` (2-3 참고)

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

**확인**: 창 크기를 바꿔도 세 창이 화면을 꽉 채우고, 드래그/리사이즈가 안 된다. `View → ImGui Demo`로 데모 창이 뜬다.

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

**텍스처 하나에 "뷰"를 여러 개 만든다**

| 뷰 | 용도 | 여기서 쓰는 곳 |
|---|---|---|
| RTV (Render Target View) | 그리기 대상 (쓰기) | 씬 오브젝트를 그릴 때 |
| SRV (Shader Resource View) | 셰이더에서 읽기 | 백버퍼로 복사(Client), `ImGui::Image`(MapTool) |
| UAV (Unordered Access View) | 컴퓨트 셰이더 읽기/쓰기 | 블러 |

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
public:
	void	Set_DrawToBackBuffer(bool_t bDraw)			{ m_bDrawToBackBuffer = bDraw; }
	ID3D11ShaderResourceView* Get_SceneSRV()const		{ return m_pSceneSRV.Get(); }
	void	SetBlurUse(bool_t bUseBlur)					{ m_bUseBlur = bUseBlur; }
private:
	// 씬 텍스처 (텍스처 하나에 뷰 3개)
	ComPtr<ID3D11RenderTargetView>		m_pSceneRTV;      // 그리기
	ComPtr<ID3D11ShaderResourceView>	m_pSceneSRV;      // 읽기
	ComPtr<ID3D11UnorderedAccessView>	m_pSceneUAV;      // 블러 (컴퓨트 셰이더)

	// 씬 텍스처 → 백버퍼 복사용
	ComPtr<ID3D11VertexShader>			m_pVS_FullScreen;
	ComPtr<ID3D11PixelShader>			m_pPS_FullScreen;
	ComPtr<ID3D11DepthStencilState>		m_pDSS_NoDepth;   // 복사할 때는 깊이 테스트 끔

	unique_ptr<CBlurFilter>				m_pBlurFilter;
	bool_t								m_bUseBlur = { false };
	bool_t								m_bDrawToBackBuffer = { true };   // Client는 true, 툴은 false
private:
	void	Render_FullScreen();
	HRESULT	Ready_SceneTarget(uint32_t iWinSizeX, uint32_t iWinsizeY);
```

### 4-3. Ready_SceneTarget — 씬 텍스처 만들기

`CRenderer::Initialize`에서 다른 상태 객체들과 함께 한 번 호출한다.

```cpp
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
	               | D3D11_BIND_SHADER_RESOURCE     // SRV를 만들려면
	               | D3D11_BIND_UNORDERED_ACCESS;   // UAV를 만들려면 (블러)

	ComPtr<ID3D11Texture2D> pTex;
	m_pDevice->CreateTexture2D(&desc, nullptr, &pTex);

	// 2. 같은 텍스처에 뷰 3개
	m_pDevice->CreateRenderTargetView(pTex.Get(), nullptr, &m_pSceneRTV);
	m_pDevice->CreateShaderResourceView(pTex.Get(), nullptr, &m_pSceneSRV);
	m_pDevice->CreateUnorderedAccessView(pTex.Get(), nullptr, &m_pSceneUAV);
	// pTex는 여기서 사라져도 됨 — 뷰들이 텍스처 참조를 들고 있음

	// 3. 백버퍼로 복사할 때 쓸 "깊이 끔" 상태
	D3D11_DEPTH_STENCIL_DESC noDepth{};
	noDepth.DepthEnable = FALSE;
	if (FAILED(m_pDevice->CreateDepthStencilState(&noDepth, m_pDSS_NoDepth.GetAddressOf())))
		return E_FAIL;

	// 4. 복사용 셰이더 (Shader_Blur.hlsl의 VS_FullScreen / PS_FullScreen)
	ComPtr<ID3DBlob> pVSBlob, pPSBlob, pErrBlob;
	uint32_t iFlags = 0;
#ifdef _DEBUG
	iFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif
	if (FAILED(D3DCompileFromFile(L"../Bin/Shader/Shader_Blur.hlsl", nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"VS_FullScreen", "vs_5_0", iFlags, 0, &pVSBlob, &pErrBlob)))
	{
		if (pErrBlob) OutputDebugStringA((char*)pErrBlob->GetBufferPointer());
		return E_FAIL;
	}
	if (FAILED(D3DCompileFromFile(L"../Bin/Shader/Shader_Blur.hlsl", nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"PS_FullScreen", "ps_5_0", iFlags, 0, &pPSBlob, &pErrBlob)))
	{
		if (pErrBlob) OutputDebugStringA((char*)pErrBlob->GetBufferPointer());
		return E_FAIL;
	}
	if (FAILED(m_pDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &m_pVS_FullScreen)))
		return E_FAIL;
	if (FAILED(m_pDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &m_pPS_FullScreen)))
		return E_FAIL;

	// 5. 블러 필터 (선택)
	m_pBlurFilter = CBlurFilter::Create(m_pDevice, m_pContext, iWinSizeX, iWinSizeY);
	if (nullptr == m_pBlurFilter)
		return E_FAIL;

	return S_OK;
}
```

- **크기를 창과 같게 하는 이유**: 깊이 버퍼는 새로 만들지 않고 기존 것을 같이 쓰는데, 렌더 타깃과 깊이 버퍼의 크기·샘플 수가 다르면 그려지지 않는다. 뷰포트도 그대로 쓸 수 있다
- 셰이더 경로 `../Bin/Shader/`는 실행 폴더 기준 → MapTool도 `MapTool/Bin/Shader/`에 `Shader_Blur.hlsl`이 있어야 함 (1-2의 xcopy)

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

	// 6. (선택) 씬 텍스처에 블러 — UAV로 컴퓨트 셰이더가 직접 수정
	if (m_bUseBlur)
		m_pBlurFilter->BlurInPlace(m_pSceneSRV.Get(), m_pSceneUAV.Get(), 4);

	// 7. Client: 씬 텍스처를 백버퍼에 복사 / MapTool: 건너뜀 (ImGui::Image가 대신 보여줌)
	if (m_bDrawToBackBuffer)
		Render_FullScreen();

	// 8. UI는 씬 텍스처가 아니라 백버퍼에 바로 그림
	Render_NonAlpha_UI();
	Render_Alpha_UI();
}
```

- **백업을 하는 이유**: Renderer가 백버퍼 RTV를 직접 들고 있지 않아도, 원래 타깃이 무엇이었든 그대로 되돌릴 수 있다
- `OMGetRenderTargets`는 받은 뷰의 참조 카운트를 올려 준다 → `ComPtr`로 받으면 함수가 끝날 때 자동으로 `Release`
- 깊이 버퍼는 `CToolMainApp::Render`(Client는 `CMainApp::Render`) 맨 앞의 `Clear_DepthStencil_View()`에서 이미 지워졌으므로 여기서는 색만 지운다
- 씬 텍스처는 창과 같은 크기라 **뷰포트를 바꿀 필요가 없다** (크기가 다른 텍스처에 그릴 때는 `RSSetViewports`도 같이 바꾸고 복구해야 함)
- 8번 UI 그룹은 백버퍼에 그려지므로 MapTool에서는 Scene 창 안이 아니라 ImGui 창 뒤에 깔린다 → 맵툴 레벨에서는 UI 객체를 만들지 않는다

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

**Shader_Blur.hlsl**

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

**MapTool**: `CToolMainApp::Initialize` 마지막에 `CGameInstance::Get().Set_DrawToBackBuffer(false);` (2-3)

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

### 4-7. EditorUI_Defines.h — EDITOR_CONTEXT에 Scene 상태 추가

```cpp
struct EDITOR_CONTEXT
{
	// ---------- Scene 창 ----------
	float2_t	vImageMin = {};					// 화면 기준 씬 이미지 좌상단 (피킹용)
	float2_t	vImageSize = {};				// 씬 이미지 크기 (피킹에서 NDC로 바꿀 때 나누는 값)
	bool_t		bSceneHovered = {};				// 씬 이미지 위에 마우스가 있는지
	bool_t		bSceneFocused = {};				// Scene 창이 포커스인지 → 카메라 조작 허용

	// 11단계: 선택 상태
};
```

`EditorUI.h`의 public에 카메라용 조회 함수 추가 (5-3에서 사용)

```cpp
	bool_t		GetSceneCliked() { return m_Context.bSceneFocused; }
```

### 4-8. CPanel_Scene::Render

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

**확인**: Scene 창 안에 회색 배경(clearColor 0.75) + SkyBox가 보이고, 창 크기를 바꿔도 찌그러지지 않는다.

**주의**
- 툴에서 `Set_DrawToBackBuffer(false)`를 안 하면 씬이 백버퍼 전체에도 그려져 ImGui 창 뒤에 겹쳐 보인다
- `ImGui::Render`는 반드시 씬 `Draw()` **뒤**에 (그래야 SceneSRV에 이번 프레임 그림이 들어 있음)
- 현재 가로 방향 가운데 정렬은 안 되어 있음 (`vCursor.x = (vAvail.x - vSize.x) * 0.5f` 추가하면 됨 — 남은 작업)

---

## 5단계. 맵툴 카메라

**목표**: Scene 창을 클릭한 상태에서 **우클릭을 누르고** WASD로 이동, 마우스로 회전한다. (유니티 씬 뷰 방식)

### 5-1. Engine — 카메라를 게임오브젝트로 (커밋 `0545bc72d`, `7bdfd68df`)

- `CCamera : CGameObject` (abstract). Transform 컴포넌트가 카메라의 월드 행렬
- DESC

```cpp
typedef struct tagCameraDesc : public CGameObject::GAMEOBJECT_DESC
{
	float4_t		vEye, vAt;
	f32_t			fFovy, fNear, fFar;
}CAMERA_DESC;
```

- `Initialize`: Fovy/Near/Far 저장 → `__super::Initialize`(Transform 생성, 속도/회전속도) → 위치=vEye, `LookAt(vAt)` → `Update_PipeLines()`
- `Update_PipeLines()`: **View = 월드행렬의 역행렬**, **Proj = PerspectiveFovLH(fovy, 뷰포트 가로/세로, near, far)** 를 파이프라인에 설정

```cpp
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

void				Add_Camera(CAMERA eCameraID, shared_ptr<CCamera> pCamera);
void				Set_MainCamera(CAMERA eCameraID);
shared_ptr<CCamera> Get_MainCamera() { return m_pMainCamera.lock(); }
```

### 5-2. CMapTool_Cam

**MapTool_Cam.h**

```cpp
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
private:
    bool_t      m_bSceneClicked = { false };
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
	if (m_bSceneClicked)                                    // Scene 창이 포커스일 때만
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

### 5-3. 툴 → 카메라 연결 (CToolMainApp::Sync_SceneView)

```cpp
void CToolMainApp::Sync_SceneView()
{
    auto pCamera = dynamic_pointer_cast<CMapTool_Cam>(CGameInstance::Get().Get_MainCamera());
    if (nullptr == pCamera)
        return;
    pCamera->Set_SceneClicked(m_pEditorUI->GetSceneCliked());   // = Scene 창 IsWindowFocused
}
```

**확인**: Scene 창을 한 번 클릭 → 우클릭 누른 채 WASD/마우스로 카메라가 움직인다. Hierarchy/Inspector가 포커스일 때는 안 움직인다.

**주의 / 남은 것**
- 마우스 이동량은 이미 "이번 프레임 이동 픽셀"이라 `fDeltaTime`을 곱하면 프레임에 따라 감도가 달라짐 → 곱하기 제거 + `fSensor` 재조정 (남은 작업)
- 피치(위아래) 제한 없음 → 90도 넘으면 뒤집힘 (남은 작업)

---

## 6단계. Level_MapTool 구성

**목표**: 툴 레벨이 시작되면 SkyBox, 카메라, StaticProp 원형이 준비된다. 맵 객체는 `Layer_Map`에 들어간다.

```cpp
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

### 6-1. Ready_Layer_BackGround — SkyBox + 공용 VS

```cpp
// 원형
Add_Prototype(MAPTOOL, Proto::Texture_SkyBox,
    CTexture::Create(m_pDevice, m_pContext, TEXT("../../../Resource/Ex/proc_preview.png"), 1));
Add_Prototype(MAPTOOL, Proto::Obj_SkyBox, CSkyBox::Create(m_pDevice, m_pContext));
Add_Prototype(MAPTOOL, Proto::VS_VTXTEX,
    CVertexShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Shader_VtxTex.hlsl",
                          VTXNORM::Elements, VTXNORM::iNumElements, "VS_MAIN"));
Add_Prototype(MAPTOOL, Proto::PS_VTXTEX_SKYBOX,
    CPixelShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Shader_VtxTex.hlsl", "PS_MAIN_SKY"));
Add_Prototype(MAPTOOL, Proto::VIBuffer_SkyBox, CVIBuffer_SkyBox::Create(m_pDevice, m_pContext));

// 사본
Add_GameObject(MAPTOOL, Proto::Obj_SkyBox, MAPTOOL, Layer::BackGround, GO::SkyBox);
```
(위 코드의 `MAPTOOL`은 `ETOUI(LEVEL::MAPTOOL)`, 각 호출은 `if (FAILED(...)) return E_FAIL;`로 감쌈)

### 6-2. Ready_Layer_GameObject — 카메라

```cpp
Add_Prototype(MAPTOOL, Proto::Obj_MapToolCam, CMapTool_Cam::Create(m_pDevice, m_pContext));

CMapTool_Cam::CAMERA_MAPTOOL_CAM_DESC CameraDesc{};
CameraDesc.fDegreeRotPerSec = 180.f;
CameraDesc.fSpeedPerSec     = 20.f;
CameraDesc.vEye  = float4_t(0.f, 0.f, -5.f, 1.f);
CameraDesc.vAt   = float4_t(0.f, 0.f,  0.f, 1.f);
CameraDesc.fFovy = 60.f;
CameraDesc.fNear = 0.1f;
CameraDesc.fFar  = 1000.f;
CameraDesc.fSensor = 0.05f;

Add_GameObject(MAPTOOL, Proto::Obj_MapToolCam, MAPTOOL, pLayerTag, GO::MapToolCam, &CameraDesc);

auto pMapToolCam = dynamic_pointer_cast<CMapTool_Cam>(
    CGameInstance::Get().Find_GameObject(MAPTOOL, pLayerTag, GO::MapToolCam));
CGameInstance::Get().Add_Camera(CAMERA::FREE, pMapToolCam);
CGameInstance::Get().Set_MainCamera(CAMERA::FREE);
```

### 6-3. Ready_Layer_Map — StaticProp 원형

```cpp
// 픽셀 셰이더 (VS_VTXTEX는 BackGround에서 이미 등록)
Add_Prototype(MAPTOOL, Proto::PS_VTXTEX_NOLIGHT,
    CPixelShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Shader_VtxTex.hlsl", "PS_MAIN_NOLIGHT"));
// 객체 원형
Add_Prototype(MAPTOOL, Proto::Obj_StaticProp, CStaticProp::Create(m_pDevice, m_pContext));
```

- **메시/텍스처 원형은 여기서 등록하지 않는다** — `CAsset_Manager`가 필요할 때 로드 (8단계)
- 처음엔 테스트용으로 `Prop_0~2`를 코드로 만들었다가, Hierarchy 생성(11단계)이 생긴 뒤 삭제

---

## 7단계. CMapObject + MAPOBJECT_DESC

**목표**: 배치 가능한 객체가 "레벨 번호 + Transform + 메시/텍스처 경로"를 DESC로 받는다. 툴/게임 어느 레벨이든 같은 코드로 동작.

### 7-1. MapObject.h (Client/Public)

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

### 7-2. MapObject.cpp

```cpp
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

### 7-3. Engine — CTransform::Rotation(도 x, y, z)

현재 크기를 유지한 채 기본 축을 오일러 회전시킨다.

```cpp
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

---

## 8단계. CAsset_Manager

**목표**: "경로로 원형을 찾고, 없으면 로드해서 등록" — 같은 메시/텍스처는 **한 번만** 로드된다.
`Proto::Texture_XXX`처럼 태그를 미리 만들지 않고 **정규화된 경로 자체가 프로토타입 태그**가 된다.

### 8-1. Engine_Function.h — 경로 정규화 + 상수

```cpp
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
```
- 예: `L"Ex\\WoodCrate01.dds"` → `L"ex/woodcrate01.dds"`
- `Engine_Defines.h`에 `<algorithm>` 등 필요한 헤더 추가

### 8-2. Prototype_Manager — Has_Prototype 추가 (`Find_Prototype`이 private이라)

```cpp
bool_t CPrototype_Manager::Has_Prototype(uint32_t iLevelIndex, const wstring_t& strPrototypeTag)
{
	if (iLevelIndex >= m_iNumLevels)
		return false;
	return nullptr != Find_Prototype(iLevelIndex, strPrototypeTag);
}
```
+ `GameInstance::Has_Prototype` 전달 함수

### 8-3. Asset_Manager.h / .cpp (Engine)

```cpp
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

```cpp
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
    // else: 10단계에서 fbx 모델 로드

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

### 8-4. GameInstance가 소유

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

---

## 9단계. CStaticProp

**목표**: 클래스 하나로 모든 구조물을 표현. 메시/텍스처를 경로로 받고, **생성 후에도 교체**할 수 있다.

### 9-1. Engine — CGameObject::Remove_Component

`Add_Component`는 같은 태그가 있으면 실패하므로, 교체하려면 먼저 지워야 한다.

```cpp
virtual void Remove_Component(const wstring_t& strComponentTag) { m_Components.erase(strComponentTag); }
```

### 9-2. 태그 (Client_Tags.h)

```cpp
inline constexpr const wchar_t* Obj_StaticProp = L"Prototype_GameObject_StaticProp";   // Proto
inline constexpr const wchar_t* StaticProp     = L"GameObject_StaticProp";             // GO
```

### 9-3. StaticProp.h

```cpp
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

### 9-4. StaticProp.cpp

**Initialize_Prototype** — 래스터라이저(컬링 없음) + 머티리얼 (원형에서 한 번, 사본은 복사됨)

```cpp
D3D11_RASTERIZER_DESC rsDesc{};
rsDesc.FillMode = D3D11_FILL_SOLID;
rsDesc.CullMode = D3D11_CULL_NONE;          // 처음엔 컬링 끄기 (rect 뒷면도 보이게)
rsDesc.FrontCounterClockwise = false;       // 시계 방향이 앞면
rsDesc.DepthClipEnable = true;
m_pDevice->CreateRasterizerState(&rsDesc, m_pRS.GetAddressOf());

m_tMaterial.Ambient  = float4_t(1.f, 1.f, 1.f, 1.f);
m_tMaterial.Diffuse  = float4_t(1.f, 1.f, 1.f, 1.f);
m_tMaterial.Specular = float4_t(0.2f, 0.2f, 0.2f, 16.f);   // w = 반사 강도
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
        return E_FAIL;                              // 모델은 10단계에서

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

**확인**: DESC(`builtin/cube` + `Ex/WoodCrate01.dds`)로 여러 개 만들면 전부 보이고, 텍스처 로드는 한 번만 일어난다.

---

## 10단계. 엔진: 삭제(Dead)와 객체 목록 조회

**목표**: 툴이 객체를 안전하게 지우고(순회 중 erase 금지), 레이어의 객체 목록을 읽을 수 있다.

### 10-1. CGameObject — Dead 플래그

```cpp
public:
	virtual void		Set_Dead() { m_bDead = true; }
	virtual bool_t		Is_Dead()const { return m_bDead; }
protected:
	bool_t				m_bDead = { false };
```

### 10-2. CLayer

```cpp
// Layer.h
	void		Remove_Dead();
	shared_ptr<CGameObject>	Find_GameObject(const wstring_t& strGameObjectTag);
	const map<const wstring_t, shared_ptr<CGameObject>>& Get_GameObjects() const { return m_GameObjects; }
```

```cpp
// 중복 태그면 실패 (예전에는 조용히 무시됨)
HRESULT CLayer::Add_GameObject(const wstring_t& strGameObjectTag, shared_ptr<class CGameObject> pGameObject)
{
    if (false == m_GameObjects.emplace(strGameObjectTag, pGameObject).second)
        return E_FAIL;
    return S_OK;
}

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

- 처음 만들었던 즉시 삭제 `Remove_GameObject(태그)`는 제거 (삭제 경로는 Dead 하나로 통일)

### 10-3. CObject_Manager

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

// Add_GameObject: pLayer->Add_GameObject 실패(중복 태그) 시 E_FAIL을 그대로 반환하도록 수정

const map<const wstring_t, shared_ptr<CGameObject>>* CObject_Manager::Get_GameObjects(uint32_t iLayerLevelIndex, const wstring_t& strLayerTag)
{
	auto pLayer = Find_Layer(iLayerLevelIndex, strLayerTag);
	if (nullptr == pLayer)
		return nullptr;                 // 레이어가 아직 없으면 nullptr (객체를 하나도 안 만든 상태)
	return &pLayer->Get_GameObjects();
}
```

### 10-4. CGameInstance — 전달 함수

```cpp
const map<const wstring_t, shared_ptr<CGameObject>>* Get_GameObjects(uint32_t iLayerLevelIndex, const wstring_t& strLayerTag);
```

**프레임 순서와 삭제 타이밍**
```
CEditorUI::Update (ImGui)  → Set_Dead()           ← 삭제 요청
Update_Engine         → Priority_Update      ← Remove_Dead로 실제 erase
                      → Update / Late_Update (Dead는 건너뜀)
Draw                                          ← 이미 없음 → 같은 프레임에 사라짐
```

---

## 11단계. Hierarchy 창

**목표**: Hierarchy 빈 곳 우클릭 → 객체 생성, 이름 목록에서 클릭 → 선택, 항목 우클릭/Delete 키 → 삭제. (Unity 방식)
Hierarchy는 **이름 + 선택만** 담당하고, 값은 전부 Inspector(12단계)에서 바꾼다.

### 11-1. EditorUI_Defines.h — 선택 상태 + 에셋 목록 추가

선택은 Hierarchy가 바꾸고 Inspector가 읽으므로 `EDITOR_CONTEXT`에 둔다. (나중에 Scene 피킹으로 선택할 때도 여기에 쓴다)

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

	void Clear_Selection()
	{
		pSelected.reset();
		strSelectedTag.clear();
	}

	// 선택한 객체가 지워졌으면 선택 해제
	void Validate_Selection()
	{
		auto pObject = pSelected.lock();
		if (nullptr == pObject || pObject->Is_Dead())
			Clear_Selection();
	}
};
```

같은 파일, `EDITOR_CONTEXT` 아래에 메시/텍스처 목록 추가 (생성 기본값 + 12단계 Inspector 콤보가 같이 씀)

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

### 11-2. EditorUI_Utils.h — 문자열 변환 도우미 추가

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

### 11-3. Panel_Hierarchy.h

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

### 11-4. Panel_Hierarchy.cpp — Create_Object (기본값으로 생성 + 고유 태그 + 바로 선택)

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

    // 비어 있는 Prop_NN이 나올 때까지 번호 증가 (Dead 대기 중 객체, 불러온 맵과도 안 겹치게)
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

    // 만든 객체를 바로 선택
    m_Context.Select(strTag, CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::MAPTOOL), TEXT("Layer_Map"), strTag));
}
```

### 11-5. Delete_Selected

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

### 11-6. Render

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
                if (nullptr == pObject || pObject->Is_Dead())
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

unique_ptr<CPanel_Hierarchy> CPanel_Hierarchy::Create(EDITOR_CONTEXT& Context)
{
    return unique_ptr<CPanel_Hierarchy>(new CPanel_Hierarchy(Context));
}
```

**확인**
- 빈 곳 우클릭 → `Add Static_Prop` → `Prop_00`, `Prop_01` ... 생성, 바로 선택(하이라이트)
- 항목 클릭 → 선택, 항목 우클릭 → `Delete`, 또는 Delete 키 → 같은 프레임에 Scene에서 사라짐

**주의**
- `Set_Dead()`만 하고 erase는 엔진에 맡기므로 지운 직후에도 `Find_GameObject`에는 잠깐 걸림 → 태그 생성 루프가 그것도 피함
- 여러 항목이 같은 라벨이면 ID가 겹침 → 태그는 고유하므로 문제 없음 (같은 이름이 필요하면 `"이름##고유ID"` 또는 `PushID`)

---

## 12단계. Inspector 창

**목표**: 선택한 객체의 이름, Transform(위치/회전/크기), Mesh/Texture를 편집하면 Scene에 즉시 반영된다.

```
Inspector
 Prop_01
 ─────────────────
 ▼ Transform            ← 모든 CMapObject 공통
   Position  x y z
   Rotation  x y z      (도)
   Scale     x y z
 ▼ Static Prop          ← dynamic_pointer_cast<CStaticProp> 성공 시만
   Mesh    [Cube        ▼]
   Texture [WoodCrate01 ▼]
```

### 12-1. EditorUI_Utils.h — 콤보 템플릿 추가

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

### 12-2. Panel_Inspector.h

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

### 12-3. Panel_Inspector.cpp

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

**확인**
- 아무것도 선택 안 하면 회색 글씨 `No object selected`
- Position 칸을 좌우로 드래그하면 Scene에서 바로 움직임 (더블클릭/Ctrl+클릭하면 숫자 직접 입력)
- Mesh를 Rect로, Texture를 WoodCrate02로 바꾸면 즉시 반영
- 객체를 지우면 Inspector가 바로 선택 없음 상태

**주의**
- `DragFloat3`에 `&vPos.x`를 넘기는 건 `float3_t`(XMFLOAT3)가 float 3개가 연속이라 가능
- 텍스처/메시 목록을 늘리려면 `EditorUI_Defines.h`의 `g_Meshes` / `g_Textures`에 한 줄 추가하면 끝 (경로는 Resource 기준)

---

## 13. 현재 상태와 남은 작업

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
   - (권장) 우클릭을 Scene 위에서 시작했을 때만 조작(`m_Context.bSceneHovered` 활용), 피치 제한
2. **저장 / 불러오기** (계획서 6단계)
   - 파일 형식: 헤더 `"DKMP"` + 버전 → 개수 → [프로토 태그, 메시 경로, 텍스처 경로, 위치/회전/크기 float×9, 추가 데이터 크기, 추가 데이터]
   - `Parse_Map(경로, vector<DESC>&)` / `Spawn_Map(레벨, 레이어, Descs)`로 분리 (Client Loader 스레드 대비)
   - 메뉴 New/Open/Save/Save As 활성화, `GetOpenFileName/GetSaveFileName` + `OFN_NOCHANGEDIR`
3. **Client에서 불러오기** (7단계) → 1차 완성
4. 기존 Client 클래스를 `CMapObject`로 옮기기 (8단계)
5. 모델(fbx) 전환 (10단계), 피킹/기즈모/복제/Undo (9단계)

### 알려진 작은 문제
- `Change_Mesh/Change_Texture`: `Get_Or_Load` 성공 후 `Remove_Component` → `Add_Component`가 실패하면 기존 컴포넌트가 이미 지워진 상태가 됨 (Clone 실패는 드묾. 안전하게 하려면 Add 실패 시 기존 것을 다시 넣기)
- `CAsset_Manager` 로드 실패 시 `E_FAIL`만 반환 → 호출부(Inspector)에서 `MSG_BOX`로 알림. 생성 시 실패는 `"Create Failed"`
- `CImGui_Manager`는 현재 미사용 (ToolMainApp이 직접 처리) — 정리 대상

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
