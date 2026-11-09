# MapTool 작업 설명서 v2

> 지금 프로젝트의 맵툴(로딩 레벨 → 에디터 레벨, 접을 수 있는 Hierarchy / Inspector 패널 + 백버퍼에 그대로 나오는 게임 화면, FBX StaticProp 생성·선택·삭제·편집, 혼합맵 지형, 방향광 + 안개, 화면 피킹, SnapToTerrain, 지형 피킹 생성, ImGuizmo)을 **처음부터 다시 만들 수 있도록** 작업 순서대로 정리한 문서입니다.
>
> **규칙: 각 단계는 그 앞 단계까지만 끝났으면 빌드·실행·확인이 된다.** 뒤 단계에서 쓰는 헤더, 함수, 원형은 앞 단계에 미리 넣지 않습니다. 그래서 같은 파일이 여러 단계에 걸쳐 조금씩 커집니다. 각 단계에는 "이번에 추가/수정하는 부분"만 적고, 파일이 짧으면 전체를 적습니다.
>
> 각 단계는 **목표 → 엔진/클라이언트 선행 조건 → 수정 파일 → 코드(블록별 설명) → 확인 → 주의** 순서입니다.

---

## 목차

- [0. 전체 그림](#0-전체-그림)
- [1단계. 프로젝트 + 엔진 초기화 + 로딩 레벨 + 빈 맵툴 레벨](#1단계-프로젝트--엔진-초기화--로딩-레벨--빈-맵툴-레벨)
- [2단계. ImGui 붙이기 + 메뉴바](#2단계-imgui-붙이기--메뉴바)
- [3단계. 패널 2개 — Hierarchy / Inspector (접기 가능)](#3단계-패널-2개--hierarchy--inspector-접기-가능)
- [4단계. 게임 화면 위에 UI — 뷰포트 입력 판정](#4단계-게임-화면-위에-ui--뷰포트-입력-판정)
- [5단계. 맵툴 카메라 + SkyBox + 카메라 조작 제한](#5단계-맵툴-카메라--skybox--카메라-조작-제한)
- [6단계. 배치 객체 — CMapObject + FBX 모델 + CStaticProp + 조명/안개 + 생성 메뉴](#6단계-배치-객체--cmapobject--fbx-모델--cstaticprop--조명안개--생성-메뉴)
- [7단계. Hierarchy 목록 + 선택](#7단계-hierarchy-목록--선택)
- [8단계. 삭제](#8단계-삭제)
- [9단계. Inspector — 이름 + Transform](#9단계-inspector--이름--transform)
- [10단계. Inspector — 모델 교체 콤보](#10단계-inspector--모델-교체-콤보)
- [11단계. 혼합맵 지형 — CHill](#11단계-혼합맵-지형--chill)
- [12단계. 뷰포트 피킹으로 선택](#12단계-뷰포트-피킹으로-선택)
- [13단계. SnapToTerrain](#13단계-snaptoterrain)
- [14단계. 지형 피킹으로 객체 생성](#14단계-지형-피킹으로-객체-생성)
- [15단계. ImGuizmo 기즈모](#15단계-imguizmo-기즈모)
- [16. 현재 상태와 남은 작업](#16-현재-상태와-남은-작업)
- [부록 A. 사용한 ImGui / ImGuizmo 함수](#부록-a-사용한-imgui--imguizmo-함수)
- [부록 B. 단계와 커밋 대응](#부록-b-단계와-커밋-대응)
- [부록 C. 자주 겪는 문제](#부록-c-자주-겪는-문제)

---

## 0. 전체 그림

### 폴더 구조

```
Duckov/Game/
├─ Engine/        엔진 DLL. 빌드하면 헤더는 EngineSDK/Inc, lib는 EngineSDK/Lib, dll은 각 Bin으로 복사
├─ EngineSDK/     Inc(헤더 복사본), Lib(Engine.lib)
├─ Client/        게임. 맵툴은 Client의 cpp 일부를 "소스째로" 같이 컴파일한다
│                 (SkyBox, MapObject, StaticProp, Hill, Fog, SunLight)
└─ MapTool/
   ├─ Default/    Default.cpp(wWinMain/WndProc), Default.vcxproj
   ├─ ImGui/      imgui 소스 + ImGuizmo.cpp/.h (15단계)
   ├─ Public/     MapTool_Defines.h, ToolMainApp.h, Level_Loading_MapTool.h, Loader_MapTool.h,
   │              Level_MapTool.h, MapTool_Cam.h,
   │              EditorUI.h, EditorUI_Defines.h, EditorUI_Utils.h,
   │              Panel.h, Panel_Hierarchy.h, Panel_Inspector.h
   ├─ Private/    위 헤더들의 cpp
   └─ Bin/        MapTool.exe, Engine.dll, assimp dll, Shader/(Client/Bin/Shader에서 빌드 후 복사)
```

### 클래스 역할

| 클래스 | 위치 | 역할 | 처음 등장 |
|---|---|---|---|
| `wWinMain` / `WndProc` | MapTool/Default | 창 생성, 60fps 루프, ImGui에 메시지 먼저 전달 | 1, 2 |
| `CToolMainApp` | MapTool | 엔진 초기화, 로딩 레벨로 시작, 매 프레임 `Update_Engine` → 클리어 → `Draw` → `Present` | 1 |
| `CLevel_Loading_MapTool` | MapTool | 시작 레벨(`LEVEL::LOADING`). 로더를 돌리고 끝나면 스페이스로 맵툴 레벨 전환 | 1 |
| `CLoader_MapTool` | MapTool | 서브 스레드에서 MAPTOOL 레벨 원형(텍스처, 모델, 셰이더, 객체) 등록 | 1 (단계마다 추가) |
| `CLevel_MapTool` | MapTool | 에디터 레벨. **ImGui 초기화/프레임/렌더/종료**, SkyBox·Fog·카메라 사본, 방향광, `CEditorUI` 소유, 뷰포트 입력 상태를 카메라에 전달 | 1 (단계마다 추가) |
| `CEditorUI` | MapTool | 메뉴바, 레이아웃 계산, 공용 상태 `EDITOR_CONTEXT`, 패널 2개 소유, **뷰포트 입력**(피킹·지형 우클릭 생성·기즈모) | 2 |
| `CPanel_Hierarchy` / `CPanel_Inspector` | MapTool | 창 하나씩(접기 가능). `CPanel` 상속, Context를 참조로 공유 | 3 |
| `CRenderer` | Engine | 씬을 렌더 타깃(텍스처)에 그리고 블러 등 후처리 → 전체 화면으로 백버퍼에 복사 | 4 |
| `CMapTool_Cam` | MapTool (namespace Client) | WASD 이동 + 우클릭 드래그 회전. 마우스/키보드를 ImGui가 쓰지 않을 때만 | 5 |
| `CMapObject` | Client | 배치 객체 부모. 위치/쿼터니언/크기/메시 경로를 DESC로 받는다 | 6 |
| `CStaticProp` | Client | FBX 모델 하나를 그리는 구조물. 모델 경로로 교체 가능 | 6 |
| `CHill` | Client | 혼합맵 지형(높이맵 + 혼합맵 + 레이어 3장). `CMapObject` 상속 | 11 |
| `CSunLight` / `CFog` | Client | 방향광(b3) / 안개 상수버퍼(b5). 없으면 조명 셰이더 결과가 검다 | 6 |

### 한 프레임의 흐름 (완성 상태, MAPTOOL 레벨)

```
wWinMain 루프 (1/60초마다)
 └ CToolMainApp::Update
     └ Update_Engine()
         ├ 객체 Priority_Update(Dead 제거) → Update → Late_Update(RenderGroup 등록)
         ├ 조명 Update (CSunLight가 b3 갱신)
         └ CLevel_MapTool::Update
             ├ Begin_ImGui()          DX11/Win32 NewFrame → ImGui::NewFrame → ImGuizmo::BeginFrame
             ├ CEditorUI::Update()    뷰포트 입력 상태 기록 → 메뉴바 → 레이아웃 → Hierarchy → Inspector
             │                        → Update_Viewport (기즈모 → 좌클릭 피킹 → 우클릭 지형 메뉴)
             └ Sync_Viewport()        뷰포트 입력 상태를 카메라에 전달
 └ CToolMainApp::Render
     ├ Clear 백버퍼/깊이, 파이프라인 상수버퍼 바인딩
     ├ Draw()
     │   ├ Renderer               씬을 SceneRTV(텍스처)에 그림 → (블러) → 전체 화면으로 백버퍼에 복사
     │   └ CLevel_MapTool::Render
     │       └ Render_ImGui()     ImGui::Render → RenderDrawData (게임 화면 위에 패널/기즈모)
     └ Present
```

### 레벨 흐름

```
CToolMainApp::Initialize
 └ Start_Level(MAPTOOL) → Change_Level(LOADING, CLevel_Loading_MapTool)
                            └ CLoader_MapTool (서브 스레드)  MAPTOOL 원형 등록, 진행 문구는 창 제목
CLevel_Loading_MapTool::Update
 └ 로딩 완료 + 스페이스 → Change_Level(MAPTOOL, CLevel_MapTool)
```

### 설계 원칙

- **프로토타입 Clone + DESC**: "무슨 클래스" = 프로토타입 태그, "무슨 값으로" = DESC.
- **자원 태그 = 정규화된 경로**: 모델/텍스처 원형 태그를 `Normalize_AssetPath(경로)`(역슬래시→슬래시, 소문자, `../../../resource/` 제거)로 등록한다. 객체는 경로 문자열만 들고 있다가 같은 함수로 정규화해서 원형을 찾는다.
- **ImGui 코드는 MapTool에만.** Client/Engine 클래스에는 넣지 않고, 타입별 UI는 툴에서 `dynamic_pointer_cast`로 분기한다.
- **회전 원본은 쿼터니언**, Inspector에 보이는 각도는 표시용(`m_vEulerHint`).
- Engine 헤더 수정 → **Engine 먼저 빌드** → MapTool. `EngineSDK/Inc`는 복사본이라 직접 고치지 않는다.

---

## 1단계. 프로젝트 + 엔진 초기화 + 로딩 레벨 + 빈 맵툴 레벨

**목표**: MapTool.exe가 1600×900 창으로 뜨고, 로딩 레벨에서 창 제목에 진행 문구가 보이다가, 스페이스를 누르면 `MapTool_Level`로 바뀐다. (화면은 아직 아무것도 없음)

로딩 레벨을 처음부터 만드는 이유: 이후 단계에서는 **로더에 원형을 한 줄씩 추가하는 것만으로** 자원이 늘어나게 하려고. 나중에 구조를 바꾸지 않아도 된다.

### 엔진 선행 조건

- `CGameInstance::Initialize_Engine / Update_Engine / Draw / Present / Change_Level / Release_Engine`
- `Clear_BackBuffer_View / Clear_DepthStencil_View / Bind_PipeLine_*_ShaderResource`
- 엔진 Renderer가 시작할 때 `../Bin/Shader/Shader_FullScreen.hlsl`을 컴파일하므로 **셰이더 폴더가 1단계부터 필요**하다 (아래 빌드 후 이벤트).

### 1-1. 프로젝트 추가

- `Game.sln`에 Windows 데스크톱 애플리케이션 추가 → 폴더 `MapTool/Default/`, 프로젝트 `Default.vcxproj`, 출력 이름 `MapTool.exe`
- 출력 폴더 `..\Bin\`. 작업 디렉터리도 `MapTool/Bin/`이 되게 한다. 셰이더 경로 `../Bin/Shader/...`, 리소스 경로 `../../../Resource/...`가 이 기준이다.
- 프로젝트 종속성: MapTool → Engine (Engine이 먼저 빌드되게)

### 1-2. 프로젝트 속성 (Debug/Release 둘 다)

| 항목 | 값 |
|---|---|
| C/C++ → 추가 포함 디렉터리 | `../Public;../ImGui;../../Client/Public;../../EngineSDK/Inc/;../../ThirdParty;` |
| C/C++ → 전처리기 정의 | `_DEBUG(또는 NDEBUG);_MAPTOOL;_WINDOWS;` |
| C/C++ → 언어 표준 | `stdcpp20` |
| 링커 → 추가 라이브러리 디렉터리 | `../../EngineSDK/Lib/` |
| 링커 → 추가 종속성 | `Engine.lib;d3dcompiler.lib;` |
| 빌드 이벤트 → 빌드 후 이벤트 | `xcopy "$(SolutionDir)Client\Bin\Shader" "$(SolutionDir)MapTool\Bin\Shader\" /E /Y /I` |

- `MapTool/Bin/`에 `Engine.dll`, `assimp-vc143-mt(d).dll`이 있어야 실행된다. (assimp는 6단계 FBX부터 실제로 쓰지만 Engine.dll이 링크하고 있으면 1단계부터 필요)
- `_MAPTOOL`: Client 코드 안에서 툴일 때만 다르게 동작할 부분을 나눈다. 예) `SkyBox.cpp`는 `_MAPTOOL`이면 `LEVEL::MAPTOOL`에서 컴포넌트를 찾는다.
- 셰이더는 **Client 쪽을 고친다.** MapTool 빌드 때마다 Client 셰이더로 덮어써지기 때문.

### 1-3. Client 코드를 쓰는 방식

맵툴은 Client 클래스를 vcxproj에 `..\..\Client\Private\XXX.cpp`로 추가해서 **같이 컴파일**한다. 단계마다 필요한 것만 추가하면 된다.

| 단계 | 추가하는 Client cpp |
|---|---|
| 5 | `SkyBox.cpp` |
| 6 | `MapObject.cpp`, `StaticProp.cpp`, `Fog.cpp`, `SunLight.cpp` |
| 11 | `Hill.cpp` |

> 실제 프로젝트에는 `Loader.cpp`, `Level_Loading.cpp`, `Player.cpp` 등 Client 파일이 더 들어 있다. 맵툴 기능에는 필요 없지만, 넣을 거라면 이름 충돌을 조심해야 한다 → 그래서 맵툴 쪽은 처음부터 `CLoader_MapTool`, `CLevel_Loading_MapTool`, `ThreadMain_MapTool`처럼 `_MapTool`을 붙인다.

### 1-4. 레벨 enum (Client_Defines.h)

```cpp
enum class LEVEL { STATIC, LOADING, LOGO, GAMEPLAY, MAPTOOL, END };
```

- `MAPTOOL`이 원형/사본을 담는 레벨 인덱스. `LOADING`은 로딩 레벨 자체가 쓰는 인덱스.
- 엔진에 `iNumLevels = LEVEL::END`를 넘기므로 enum에 추가만 하면 저장 공간이 생긴다.

### 1-5. MapTool_Defines.h

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

- `Client_Defines.h`를 포함해서 엔진 헤더, `Client_Tags.h`(Proto/GO/Layer 태그), `g_hWnd`/`hInst` extern을 한 번에 가져온다.
- 툴 창 크기는 게임(1280×720)과 달라서 따로 둔다.
- 맵툴의 모든 헤더는 이 파일부터 포함한다.

### 1-6. Default.cpp (1단계 버전: ImGui 없음)

wWinMain 부분:

```cpp
#include "framework.h"
#include "Default.h"
#include "ToolMainApp.h"

#define MAX_LOADSTRING 100
HINSTANCE hInst;
HWND      g_hWnd;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
#ifdef _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DEFAULT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

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
        if (fTimeDeltaAcc >= 1.f / 60.f)
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

- **전역 변수**: `hInst`, `g_hWnd`는 `Client_Defines.h`에서 `extern`으로 선언돼 있고 여기서 정의한다. 엔진 초기화와 `SetWindowText`가 쓴다.
- **앱 생성 → 타이머**: 엔진이 `CToolMainApp::Create` 안에서 초기화되므로, 타이머는 그 뒤에 추가한다.
- **루프**: 메시지를 다 처리한 뒤 `Timer_Default`로 시간을 누적해서 1/60초가 지나면 한 프레임 Update/Render. `Timer_60`은 실제 프레임 간격(델타)을 얻는 용도.
- **종료**: `pToolMainApp.reset()`으로 `~CToolMainApp` → `Release_Engine`이 메시지 루프가 끝난 뒤 확실히 불리게 한다.

InitInstance / WndProc:

```cpp
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance;

    // 테두리 끌기(THICKFRAME), 최대화 버튼(MAXIMIZEBOX)을 뺀 창 -> 클라이언트 영역이 항상 1600×900
    constexpr DWORD dwStyle = WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX;

    RECT rc{ 0, 0, g_iToolWinSizeX, g_iToolWinSizeY };
    AdjustWindowRectExForDpi(&rc, dwStyle, FALSE, 0, GetDpiForSystem());

    const int iWinW = rc.right - rc.left;
    const int iWinH = rc.bottom - rc.top;
    RECT rcWork{};
    SystemParametersInfoW(SPI_GETWORKAREA, 0, &rcWork, 0);
    const int iPosX = rcWork.left + ((rcWork.right - rcWork.left) - iWinW) / 2;
    const int iPosY = rcWork.top + ((rcWork.bottom - rcWork.top) - iWinH) / 2;

    HWND hWnd = CreateWindowW(szWindowClass, L"MapTool", dwStyle,
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

- **창 크기 고정 (dwStyle)**: 엔진은 `WM_SIZE`를 처리하지 않아서 창을 늘려도 스왑체인/뷰포트는 1600×900 그대로이고 화면만 늘어나 보인다. 창 크기 변경 자체를 막아서 **창 클라이언트 영역 = 엔진 뷰포트**가 항상 같게 만든다. 덕분에 12단계 피킹에서 마우스 좌표를 그대로 쓸 수 있다.
  - `WS_THICKFRAME`: 테두리를 끌어 크기 조절 → 제거
  - `WS_MAXIMIZEBOX`: 최대화 버튼(더블클릭 최대화 포함) → 제거
  - 최소화는 남겨 둔다 (크기가 바뀌는 게 아니라 숨겨지는 것)
- **AdjustWindowRectExForDpi**: 클라이언트 영역이 정확히 1600×900이 되도록 테두리 크기를 더한다. **CreateWindowW와 같은 스타일**을 넘겨야 테두리 두께가 맞는다. 2단계에서 DPI 인식을 켜므로 DPI 버전을 쓴다.
- **작업 영역 가운데 배치**: 작업 표시줄을 뺀 영역 기준으로 가운데에 띄운다.
- **메뉴 없음**: `MyRegisterClass`에서 `wcex.lpszMenuName = 0;`(Win32 기본 메뉴 제거). 메뉴는 2단계에서 ImGui로 만든다.
- **ESC 종료**: 2단계에서 "ImGui 입력창에서는 종료 안 함" 조건이 붙는다.

### 1-7. CToolMainApp

```cpp
// ToolMainApp.h
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

private:
	HRESULT								Start_Level(LEVEL eStartLevelID);

public:
	static		unique_ptr<CToolMainApp>		Create();
};
NS_END
```

- Client `CMainApp`과 같은 모양. 장치/컨텍스트는 엔진이 만들어서 out 인자로 돌려준다.
- **ImGui 멤버가 없다**: 이 프로젝트는 ImGui를 `CLevel_MapTool`이 관리한다 (2단계). 로딩 레벨에는 ImGui가 없다.

```cpp
// ToolMainApp.cpp
#include "MapTool_Defines.h"
#include "ToolMainApp.h"
#include "Level_Loading_MapTool.h"

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

    if (FAILED(Start_Level(LEVEL::MAPTOOL)))
        return E_FAIL;

    return S_OK;
}

void CToolMainApp::Update(f32_t fDeltaTime)
{
    CGameInstance::Get().Update_Engine(fDeltaTime);
}

HRESULT CToolMainApp::Render()
{
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

HRESULT CToolMainApp::Start_Level(LEVEL eStartLevelID)
{
    if (FAILED(CGameInstance::Get().Change_Level(static_cast<int>(LEVEL::LOADING),
        CLevel_Loading_MapTool::Create(m_pDevice, m_pContext, eStartLevelID))))
        return E_FAIL;
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

- **Initialize**: 엔진에 창 핸들, 툴 창 크기, 레벨 개수를 넘긴다. 그다음 바로 로딩 레벨로 시작한다. "다음 레벨 = MAPTOOL"을 인자로 넘긴다.
- **Update**: 엔진이 객체 → 조명 → 현재 레벨 Update 순으로 돌린다.
- **Render**: 백버퍼/깊이 클리어 → 카메라 행렬 상수버퍼(슬롯 1)를 VS/PS/GS에 바인딩 → `Draw`(Renderer + 현재 레벨 Render) → `Present`.
- `Set_DrawToBackBuffer`는 부르지 않는다. 기본값 true라서 씬 텍스처가 백버퍼로 복사되어 화면 전체에 나온다 (4단계 설명).

### 1-8. CLoader_MapTool (1단계 버전: 원형 없음)

```cpp
// Loader_MapTool.h
#pragma once
#include "MapTool_Defines.h"

NS_BEGIN(MapTool)
class CLoader_MapTool
{
private:
	CLoader_MapTool(ComPtr<ID3D11Device>pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	~CLoader_MapTool();

public:
	HRESULT	Initialize(LEVEL eNextLevelID);
	HRESULT	Loading();
	bool_t	isFinished() const { return m_isFinished; }

#ifdef _DEBUG
public:
	HRESULT Draw_Debug();
#endif
private:
	LEVEL				m_eNextLevelID = {};
	HANDLE				m_hThread = {};
	CRITICAL_SECTION	m_CriticalSection = {};
	tchar_t				m_szLoadingText[MAX_PATH] = {};
	bool_t				m_isFinished = { false };

private:
	ComPtr<ID3D11Device>		m_pDevice = { nullptr };
	ComPtr<ID3D11DeviceContext> m_pContext = { nullptr };

private:
	HRESULT Loading_For_MapToolLV();

public:
	static shared_ptr<CLoader_MapTool> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, LEVEL eNextLevelID);
	void Free();
};
NS_END
```

- Client `CLoader`와 같은 구조. `m_szLoadingText`는 서브 스레드가 쓰고, 메인 스레드가 `Draw_Debug`에서 창 제목으로 보여 준다.
- `m_isFinished`가 true가 되어야 로딩 레벨이 다음 레벨로 넘어간다.

```cpp
// Loader_MapTool.cpp
#include "Loader_MapTool.h"

CLoader_MapTool::CLoader_MapTool(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    : m_pDevice{ pDevice }
    , m_pContext{ pContext }
{
}

CLoader_MapTool::~CLoader_MapTool()
{
    Free();
}

// 서브 스레드
uint32_t APIENTRY ThreadMain_MapTool(void* pArg)
{
    auto       pLoader = static_cast<CLoader_MapTool*>(pArg);
    if (FAILED(pLoader->Loading()))
        return 1;
    return 0;
}

HRESULT CLoader_MapTool::Initialize(LEVEL eNextLevel)
{
    InitializeCriticalSection(&m_CriticalSection);
    m_eNextLevelID = eNextLevel;

    m_hThread = (HANDLE)_beginthreadex(nullptr, 0, ThreadMain_MapTool, this, 0, nullptr);
    if (0 == m_hThread)
        return E_FAIL;
    return S_OK;
}

HRESULT CLoader_MapTool::Loading()
{
    EnterCriticalSection(&m_CriticalSection);

    CoInitializeEx(nullptr, 0);       // WIC 텍스처(png) 로드에 필요

    HRESULT hr = {};
    switch (m_eNextLevelID)
    {
    case Client::LEVEL::MAPTOOL:
        hr = Loading_For_MapToolLV();
        break;
    }
    if (FAILED(hr))
        return E_FAIL;

    CoUninitialize();
    LeaveCriticalSection(&m_CriticalSection);
    return S_OK;
}

// 메인 스레드
HRESULT CLoader_MapTool::Draw_Debug()
{
    SetWindowText(g_hWnd, m_szLoadingText);
    return S_OK;
}

HRESULT CLoader_MapTool::Loading_For_MapToolLV()
{
    lstrcpy(m_szLoadingText, TEXT("텍스쳐를 준비중입니다."));

    lstrcpy(m_szLoadingText, TEXT("모델을 준비중입니다."));

    lstrcpy(m_szLoadingText, TEXT("셰이더를 준비중입니다."));

    lstrcpy(m_szLoadingText, TEXT("객체원형 준비중입니다."));

    lstrcpy(m_szLoadingText, TEXT("로딩이 완료되었습니다."));

    m_isFinished = true;
    return S_OK;
}

shared_ptr<CLoader_MapTool> CLoader_MapTool::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, LEVEL eNextLevelID)
{
    auto pInstance = shared_ptr<CLoader_MapTool>(new CLoader_MapTool(pDevice, pContext));
    if (FAILED(pInstance->Initialize(eNextLevelID)))
        pInstance.reset();
    return pInstance;
}

void CLoader_MapTool::Free()
{
    WaitForSingleObject(m_hThread, INFINITE);
    CloseHandle(m_hThread);
    DeleteCriticalSection(&m_CriticalSection);
}
```

- **ThreadMain_MapTool**: 스레드 시작 함수. Client `Loader.cpp`에도 `ThreadMain`이 있어서, 같이 컴파일하면 LNK2005가 난다 → 이름을 다르게.
- **Loading**: `CoInitializeEx`는 WIC(png 로더)를 쓰는 스레드마다 한 번 필요하다. 다음 레벨에 맞는 로딩 함수로 분기한다.
- **Loading_For_MapToolLV**: 지금은 문구만 바꾸고 끝난다. **4개 구역(텍스처 / 모델 / 셰이더 / 객체원형)에 단계마다 원형을 추가**한다. 이후 단계에서 "텍스처 구역에 추가"라고 하면 해당 `lstrcpy` 다음 줄을 말한다.
- **Free**: 레벨이 바뀌어 로더가 사라질 때 스레드가 끝날 때까지 기다린다.

> 주의: `Loading()`에서 실패하면 `LeaveCriticalSection` 없이 빠져나간다. 지금 구조에선 문제를 일으키진 않지만, 로딩이 실패하면 `m_isFinished`가 안 켜져 다음 레벨로 못 넘어간다 → 창 제목의 마지막 문구로 어느 구역에서 실패했는지 본다.

### 1-9. CLevel_Loading_MapTool

```cpp
// Level_Loading_MapTool.h
#pragma once
#include "MapTool_Defines.h"
#include "Level.h"

NS_BEGIN(MapTool)
class CLevel_Loading_MapTool final : public CLevel
{
private:
	CLevel_Loading_MapTool(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	~CLevel_Loading_MapTool() = default;

public:
	virtual HRESULT	Initialize(LEVEL eNextLevel);
	virtual void	Update(f32_t fDeltaTime) override;
	virtual HRESULT	Render() override;

private:
	LEVEL								m_eNextLevelID = { LEVEL::END };
	shared_ptr<class CLoader_MapTool>	m_pLoader = { nullptr };

public:
	static shared_ptr<CLevel_Loading_MapTool> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, LEVEL eNextLevel);
};
NS_END
```

```cpp
// Level_Loading_MapTool.cpp
#include "Loader_MapTool.h"
#include "Level_Loading_MapTool.h"
#include "Level_MapTool.h"

CLevel_Loading_MapTool::CLevel_Loading_MapTool(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    :CLevel{ pDevice,pContext }
{
}

HRESULT CLevel_Loading_MapTool::Initialize(LEVEL eNextLevel)
{
    if (FAILED(__super::Initialize()))
        return E_FAIL;
    m_eNextLevelID = eNextLevel;

    m_pLoader = CLoader_MapTool::Create(m_pDevice, m_pContext, eNextLevel);
    if (nullptr == m_pLoader)
        return E_FAIL;
    return S_OK;
}

void CLevel_Loading_MapTool::Update(f32_t fDeltaTime)
{
    __super::Update(fDeltaTime);
    if (true == m_pLoader->isFinished() &&
        CGameInstance::Get().Key_Pressing(DIK_SPACE))
    {
        if (FAILED(CGameInstance::Get().Change_Level(ETOI(m_eNextLevelID), CLevel_MapTool::Create(m_pDevice, m_pContext))))
            return;
        return;
    }
}

HRESULT CLevel_Loading_MapTool::Render()
{
    if (FAILED(__super::Render()))
        return E_FAIL;
#ifdef _DEBUG
    m_pLoader->Draw_Debug();
#endif
    return S_OK;
}

shared_ptr<CLevel_Loading_MapTool> CLevel_Loading_MapTool::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, LEVEL eNextLevel)
{
    auto pInstance = shared_ptr<CLevel_Loading_MapTool>(new CLevel_Loading_MapTool(pDevice, pContext));
    if (FAILED(pInstance->Initialize(eNextLevel)))
    {
        MSG_BOX("Failed to Created : CLevel_Loading");
        pInstance.reset();
    }
    return pInstance;
}
```

- **Initialize**: 로더를 만드는 순간 서브 스레드가 시작된다.
- **Update**: 로딩이 끝났고 스페이스를 누르면 `CLevel_MapTool`로 바꾼다. `Change_Level` 직후에 이 객체가 사라지므로 바로 `return`.
- **Render**: 그릴 건 없고 Debug일 때 진행 문구를 창 제목에 쓴다.

### 1-10. CLevel_MapTool (1단계 버전: 빈 레벨)

```cpp
// Level_MapTool.h
#pragma once
#include "MapTool_Defines.h"
#include "Level.h"

NS_BEGIN(MapTool)
class CLevel_MapTool final : public CLevel
{
private:
	CLevel_MapTool(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	~CLevel_MapTool();

public:
	virtual		HRESULT		Initialize() override;
	virtual		void		Update(f32_t fDeltaTime) override;
	virtual		HRESULT		Render() override;

public:
	static shared_ptr<CLevel_MapTool> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
};
NS_END
```

```cpp
// Level_MapTool.cpp
#include "Level_MapTool.h"

CLevel_MapTool::CLevel_MapTool(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    :CLevel{ pDevice,pContext }
{
}

CLevel_MapTool::~CLevel_MapTool()
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

- 창 제목을 `MapTool_Level`로 바꿔서 레벨 전환이 됐는지 눈으로 확인한다.
- 이 클래스가 이후 단계마다 커진다: ImGui(2) → EditorUI(2) → 카메라/SkyBox(5) → 조명/안개(6).

### 확인

1. 빌드 → `MapTool/Bin/Shader/`에 셰이더가 복사됐는지 확인
2. 실행 → 회색 화면, 제목이 `로딩이 완료되었습니다.` (Renderer가 씬 텍스처를 0.75 회색으로 지우고 백버퍼로 복사한 것)
3. 창을 클릭해 포커스 → 스페이스 → 제목이 `MapTool_Level`
4. 창 테두리를 끌어도 크기가 안 바뀌고, 최대화 버튼이 비활성
5. ESC → 종료, 출력 창에 메모리 누수 없음

---

## 2단계. ImGui 붙이기 + 메뉴바

**목표**: 맵툴 레벨로 넘어가면 화면 위에 ImGui 메뉴바(File)가 보이고 마우스로 열 수 있다.

### 2-0. ImGui가 동작하는 방식 (먼저 알아 둘 것)

ImGui는 **즉시 모드 GUI**다. 버튼 객체를 만들어 두는 것이 아니라 **매 프레임** 함수를 다시 부른다.

```cpp
if (ImGui::Button("저장"))        // 1) 그리기 명령을 쌓고  2) 이번 프레임에 눌렸으면 true
    Save();
ImGui::DragFloat("속도", &m_fSpeed);   // 값은 우리 변수. ImGui는 읽고, 드래그하면 바꿔 줄 뿐
```

1. **한 프레임**: `NewFrame()` → 위젯 함수들 → `Render()` → `ImGui_ImplDX11_RenderDrawData()`. 위젯 함수는 명령만 쌓고, 실제로 그리는 건 마지막 줄이다.
2. **Begin/End 짝**
   - `Begin()`(창)은 반환값과 상관없이 **항상** `End()`
   - `BeginMenu / BeginMainMenuBar / BeginPopup* / BeginCombo`는 **true일 때만** `EndXXX()`
3. **라벨 = ID**: 같은 창 안에서 라벨이 같으면 충돌. 글자는 같고 ID만 다르게 하려면 `"저장##1"`.
4. **`Item` 함수는 바로 앞 위젯 하나**, **`Window` 함수는 지금 Begin~End 중인 창** 기준이다.
5. **문자열은 UTF-8 `const char*`**. wstring은 변환해야 한다 (6단계 `To_UTF8`).

### 2-1. ImGui 소스 추가

- `MapTool/ImGui/`에 넣고 vcxproj에 추가 (**ImGuizmo는 15단계에서 추가**한다)
  - `imgui.cpp, imgui_draw.cpp, imgui_widgets.cpp, imgui_tables.cpp, imgui_impl_win32.cpp, imgui_impl_dx11.cpp`
  - `imgui.h, imconfig.h, imgui_internal.h, imgui_impl_win32.h, imgui_impl_dx11.h, imstb_rectpack.h, imstb_textedit.h, imstb_truetype.h`
- pch를 쓴다면 ImGui cpp는 "미리 컴파일된 헤더 사용 안 함"
- 각 ImGui cpp 속성 → C/C++ → 명령줄 → 추가 옵션 `/utf-8` (Debug/Release 둘 다)
- 이 프로젝트의 ImGui 버전은 `1.93.1 WIP` (`ImTextureID`가 `ImU64`)

### 2-2. Default.cpp — ImGui에 메시지 전달

맨 위 include와 선언:

```cpp
#include "imgui.h"              // ImGui::GetIO()를 사용하기 위해
#include "imgui_impl_win32.h"
#include "framework.h"
#include "Default.h"
#include "ToolMainApp.h"

// imgui_impl_win32.h에서 #if 0으로 막혀 있으므로 직접 선언
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
```

- 핸들러 선언이 헤더에서 `#if 0`으로 막혀 있다. `windows.h`가 없는 곳에서도 헤더를 쓸 수 있게 하려는 것이라 직접 선언한다.

wWinMain에서 창을 만들기 전:

```cpp
    // DPI 인식 설정
    ImGui_ImplWin32_EnableDpiAwareness();
```

- Windows 배율이 125%여도 창 크기와 마우스 좌표가 흐려지거나 어긋나지 않게 한다. 창 생성 전에 불러야 한다.

WndProc:

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

- **핸들러를 맨 앞에**: 마우스/키보드/문자 입력이 ImGui에 들어간다. 로딩 레벨처럼 ImGui 컨텍스트가 아직 없을 때는 핸들러가 알아서 0을 반환한다 (`GetCurrentContext() == nullptr` 검사가 내부에 있음).
- **ESC 조건**: 컨텍스트가 없거나(로딩 레벨) ImGui가 키보드를 쓰고 있지 않을 때만 종료한다. `GetIO()`를 컨텍스트 없이 부르면 assert가 나므로 `nullptr` 검사가 먼저다.

### 2-3. CEditorUI (2단계 버전: 메뉴바만)

```cpp
// EditorUI.h
#pragma once
#include "MapTool_Defines.h"

NS_BEGIN(MapTool)
// 에디터 화면 전체
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

private:
	void		Render_MenuBar();

public:
	static unique_ptr<CEditorUI> Create();
};
NS_END
```

```cpp
// EditorUI.cpp
#include "imgui.h"
#include "EditorUI.h"

CEditorUI::~CEditorUI()
{
}

HRESULT CEditorUI::Initialize()
{
	return S_OK;
}

void CEditorUI::Update(const f32_t& fDeltaTime)
{
    Render_MenuBar();
}

void CEditorUI::Render_MenuBar()
{
    // 화면 맨 위에 꽉 차게 붙는 메뉴 바. 일반 창(Begin) 바깥에서 호출한다.
    // false를 반환하면 EndMainMenuBar를 호출하지 않고 빠져나간다.
    if (!ImGui::BeginMainMenuBar())
        return;

    m_fMenuBarHeight = ImGui::GetWindowHeight();

    if (ImGui::BeginMenu("File"))
    {
        // MenuItem(라벨, 단축키표시, 선택됨, 활성화)
        // 단축키는 글자일 뿐이고 실제 동작은 따로 만들어야 함.
        ImGui::MenuItem("New Scene", nullptr, false, false);        // 저장/불러오기 전까지 비활성
        ImGui::MenuItem("Open Scene", "Ctrl + O", false, false);
        ImGui::MenuItem("Save", "Ctrl + S", false, false);
        ImGui::MenuItem("Save As", nullptr, false, false);
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

- **m_fMenuBarHeight**: 메뉴바 안에서 `GetWindowHeight()`로 높이를 기억해 둔다. 3단계에서 패널을 메뉴바 바로 아래부터 배치할 때 쓴다.
- **MenuItem 마지막 인자 false**: 회색으로 보이고 눌리지 않는다. 저장/불러오기는 남은 작업(16).
- `Initialize`는 지금은 비어 있고, 3단계에서 패널을 만든다.

### 2-4. CLevel_MapTool — ImGui 수명주기 + EditorUI

헤더에 추가:

```cpp
NS_BEGIN(MapTool)
class CEditorUI;                         // 전방 선언
class CLevel_MapTool final : public CLevel
{
    ...
private:
	unique_ptr<CEditorUI>	m_pEditorUI = { nullptr };
	bool_t					m_bReadyImGui = { false };
private:
	HRESULT		Ready_ImGui();
	HRESULT		Begin_ImGui();
	HRESULT		Render_ImGui();
	HRESULT		Shutdown_ImGui();
    ...
};
```

- `m_pEditorUI`를 `unique_ptr`로 들고 있어서 cpp에서만 `EditorUI.h`를 포함하면 된다. 소멸자가 cpp에 정의돼 있어야 불완전 타입 오류가 안 난다 (1단계에서 이미 cpp에 둠).
- `m_bReadyImGui`: 초기화가 끝까지 됐을 때만 Shutdown하려고.

cpp:

```cpp
#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

#include "EditorUI.h"
#include "Level_MapTool.h"

CLevel_MapTool::~CLevel_MapTool()
{
    m_pEditorUI.reset();
    Shutdown_ImGui();
}

HRESULT CLevel_MapTool::Initialize()
{
    if (FAILED(__super::Initialize()))
        return E_FAIL;

    SetWindowText(g_hWnd, L"MapTool_Level");

    if (FAILED(Ready_ImGui()))
        return E_FAIL;
    if (FAILED(Begin_ImGui()))
        return E_FAIL;
    m_pEditorUI = CEditorUI::Create();
    if (nullptr == m_pEditorUI)
        return E_FAIL;

    return S_OK;
}

void CLevel_MapTool::Update(f32_t fDeltaTime)
{
    __super::Update(fDeltaTime);
    if (FAILED(Begin_ImGui()))
        return;
    m_pEditorUI->Update(fDeltaTime);
}

HRESULT CLevel_MapTool::Render()
{
    if (FAILED(__super::Render()))
        return E_FAIL;
    if (FAILED(Render_ImGui()))
        return E_FAIL;
    return S_OK;
}
```

- **소멸 순서**: UI(패널)를 먼저 지우고 ImGui를 내린다.
- **Initialize에서 Begin_ImGui를 한 번 부르는 이유**: 레벨이 바뀌는 프레임에는 새 레벨의 `Update`가 불리지 않고 `Render`만 불린다. 그러면 `NewFrame` 없이 `ImGui::Render`가 불려 `Forgot to call ImGui::NewFrame()?` assert가 난다. 그래서 만들 때 프레임을 하나 열어 둔다.
- **Update**: 매 프레임 새 ImGui 프레임 → UI 위젯 쌓기. **Render**: 씬 그리기(`__super::Render`) 뒤에 ImGui를 그려서 UI가 항상 위에 나온다.

```cpp
HRESULT CLevel_MapTool::Ready_ImGui()
{
    // 1. 컨텍스트 생성
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // ImGui와 애플리케이션이 정보를 주고받는 구조체 (설정, 입력, 출력, 폰트)
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;   // 키보드로 위젯 이동

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

HRESULT CLevel_MapTool::Begin_ImGui()
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    return S_OK;
}

HRESULT CLevel_MapTool::Render_ImGui()
{
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    return S_OK;
}

HRESULT CLevel_MapTool::Shutdown_ImGui()
{
    if (!m_bReadyImGui)
        return E_FAIL;
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    return S_OK;
}
```

- **Ready_ImGui**: 컨텍스트 → 스타일 → Win32 백엔드(입력, 창 크기) → DX11 백엔드(폰트 텍스처, 셰이더 생성). `m_pDevice/m_pContext`는 `CLevel`이 들고 있다.
- **Begin_ImGui**: 백엔드 NewFrame을 먼저(폰트 텍스처 준비, 마우스/화면 크기 갱신) → `ImGui::NewFrame`.
- **Render_ImGui**: 쌓인 명령을 정리하고 DX11로 그린다. 그리는 대상은 그때 바인딩된 렌더 타깃(백버퍼).
- **Shutdown_ImGui**: 만든 역순으로 정리.

### 확인

- 스페이스로 맵툴 레벨에 들어가면 상단에 메뉴바, `File`을 누르면 회색 항목 4개
- 로딩 레벨에서는 메뉴바가 없다 (ImGui가 맵툴 레벨에만 있으므로 정상)
- `Default/imgui.ini`(또는 작업 디렉터리)에 ImGui 설정 파일이 생긴다

---

## 3단계. 패널 2개 — Hierarchy / Inspector (접기 가능)

**목표**: 메뉴바 아래 왼쪽에 Hierarchy, 오른쪽에 Inspector가 고정 위치로 붙어 있고, 제목 줄의 ▼ 버튼으로 접었다 펼 수 있다. 가운데에는 창이 없다. 4단계부터 이 자리에 게임 화면이 그대로 보인다.

### 3-1. 구조

```
화면 (1600×900)
┌──────────────────── 메뉴바 ────────────────────┐
│ Hierarchy │                         │ Inspector │
│   280     │  창 없음 = 뷰포트        │   280     │
│           │  (게임 화면이 그대로 보임) │           │
└───────────┴─────────────────────────┴───────────┘

CEditorUI
 ├ EDITOR_CONTEXT m_Context   패널끼리 공유하는 상태 (지금은 비어 있음, 단계마다 필드 추가)
 ├ Calc_Layout()              두 창의 PANEL_RECT 계산
 └ 패널 2개 (unique_ptr)       Render(PANEL_RECT)만 가진다
```

- **Scene 창을 만들지 않는 이유**: 엔진은 씬을 렌더 타깃(텍스처)에 그린 뒤 전체 화면 사각형으로 백버퍼에 복사한다. 렌더 타깃을 거치는 건 블러 같은 후처리 때문이다. 그 백버퍼 위에 ImGui 패널을 그리기만 하면 된다. 패널이 덮은 부분만 가려지고, 패널을 접으면 그 부분도 보인다.
- 패널끼리 직접 참조하지 않고 **Context를 참조로 공유**한다. 예) Hierarchy가 선택을 바꾸면 Inspector는 Context만 읽는다.

### 3-2. EditorUI_Defines.h (3단계 버전)

```cpp
#pragma once
#include "MapTool_Defines.h"

NS_BEGIN(MapTool)

inline constexpr ImGuiWindowFlags g_FixedPanelFlags =
ImGuiWindowFlags_NoMove                 // 제목 표시줄을 드래그해도 안 움직임
| ImGuiWindowFlags_NoResize             // 모서리를 끌어도 크기 안 바뀜
| ImGuiWindowFlags_NoSavedSettings;     // 창 정보를 저장하지 않음

// 창 하나의 위치와 크기 (CEditorUI::Calc_Layout에서 계산)
struct PANEL_RECT
{
	f32_t fX, fY, fW, fH;
};

// 패널끼리 같이 쓰는 상태. CEditorUI가 소유하고, 각 패널은 참조로 받는다.
struct EDITOR_CONTEXT
{
	// 4단계부터 필드를 채운다
};

NS_END
```

- **g_FixedPanelFlags**: 위치와 크기는 레이아웃 코드가 정하므로 사용자가 옮기거나 크기를 바꾸지 못하게 막는다. `NoSavedSettings`가 없으면 ini에 저장된 옛 위치가 끼어든다.
- **`NoCollapse`를 넣지 않는다**: 그래서 제목 줄에 ▼ 접기 버튼이 생긴다. 접으면 제목 줄만 남고 그 아래 게임 화면이 보인다. 접힘 상태는 ImGui가 창마다 기억하므로 따로 변수를 둘 필요가 없다. 위치/크기는 매 프레임 `SetNextWindow*`로 정하지만 접힘 상태는 그대로 유지된다. `NoSavedSettings` 때문에 툴을 다시 켜면 펼친 상태로 시작한다.
- **ImGuiWindowFlags 타입**을 쓰려면 imgui.h가 필요한데 이 헤더는 imgui.h를 직접 포함하지 않는다 → **이 헤더보다 imgui.h를 먼저 포함**해야 한다. 그래서 패널 cpp는 `EditorUI_Utils.h`(imgui.h 포함)를 맨 앞에 둔다.
- **EDITOR_CONTEXT가 비어 있는 이유**: 선택(7단계)은 `CMapObject`가 필요하고, 뷰포트 입력 상태(4단계)는 다음 단계에서 쓴다. 쓰지 않는 필드를 미리 넣으면 앞 단계에서 컴파일이 안 되거나 쓸모없는 코드가 된다.

### 3-3. EditorUI_Utils.h (3단계 버전)

```cpp
#pragma once
#include "imgui.h"
#include "EditorUI_Defines.h"

// 패널들이 같이 쓰는 ImGui 도우미
NS_BEGIN(MapTool)

inline void Set_NextPanelRect(const PANEL_RECT& tRect)
{
	ImGui::SetNextWindowPos(ImVec2(tRect.fX, tRect.fY), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(tRect.fW, tRect.fH), ImGuiCond_Always);
}

NS_END
```

- `SetNextWindow*`는 **바로 다음 `Begin`** 하나에만 적용된다. `ImGuiCond_Always`라 매 프레임 강제로 위치/크기를 정한다.
- 이후 `To_UTF8`(6), `Render_AssetCombo`(10)가 이 파일에 추가된다.

### 3-4. Panel.h — 패널 부모

```cpp
#pragma once
#include "EditorUI_Defines.h"

NS_BEGIN(MapTool)
// 에디터 창 하나. 위치/크기는 CEditorUI가 계산해서 Render에 넘겨준다.
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

- 참조 멤버라서 생성자에서만 묶을 수 있다. Context는 `CEditorUI`의 멤버이고 패널보다 오래 살기 때문에 참조가 안전하다.

### 3-5. 패널 2개 (빈 창)

```cpp
// Panel_Hierarchy.h
#pragma once
#include "Panel.h"

NS_BEGIN(MapTool)
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

```cpp
// Panel_Hierarchy.cpp
#include "EditorUI_Utils.h"
#include "Panel_Hierarchy.h"

void CPanel_Hierarchy::Render(const PANEL_RECT& tRect)
{
    Set_NextPanelRect(tRect);
    if (ImGui::Begin("Hierarchy", nullptr, g_FixedPanelFlags))
    {
        ImGui::TextDisabled("Empty");
    }
    ImGui::End();
}

unique_ptr<CPanel_Hierarchy> CPanel_Hierarchy::Create(EDITOR_CONTEXT& Context)
{
    return unique_ptr<CPanel_Hierarchy>(new CPanel_Hierarchy(Context));
}
```

- **Begin의 두 번째 인자 nullptr**: X(닫기) 버튼을 만들지 않는다.
- **`if (Begin)` 안쪽 = 펼쳐져 있을 때만 실행**: 창을 접으면 `Begin`이 false를 돌려줘서 안쪽 코드(목록, 우클릭 메뉴, Delete 키 처리 등)가 전부 실행되지 않는다. 접힌 동안 해당 기능이 멈추는 건 정상이다.
- **`End`는 항상**: 접혀 있어도 `End`는 불러야 한다.

Inspector는 6단계에서 모델 목록을 채울 `Initialize`를 **지금부터** 가지고 있게 만든다 (나중에 `Create`를 바꾸지 않으려고).

```cpp
// Panel_Inspector.h
#pragma once
#include "Panel.h"

NS_BEGIN(MapTool)
class CPanel_Inspector final : public CPanel
{
private:
	explicit CPanel_Inspector(EDITOR_CONTEXT& Context) : CPanel{ Context } {}
public:
	virtual ~CPanel_Inspector() = default;

public:
	virtual HRESULT	Initialize();
	virtual void	Render(const PANEL_RECT& tRect) override;

public:
	static unique_ptr<CPanel_Inspector> Create(EDITOR_CONTEXT& Context);
};
NS_END
```

```cpp
// Panel_Inspector.cpp
#include "EditorUI_Utils.h"
#include "Panel_Inspector.h"

HRESULT CPanel_Inspector::Initialize()
{
    return S_OK;            // 6단계에서 모델 목록을 채운다
}

void CPanel_Inspector::Render(const PANEL_RECT& tRect)
{
    Set_NextPanelRect(tRect);
    if (ImGui::Begin("Inspector", nullptr, g_FixedPanelFlags))
    {
        ImGui::TextDisabled("No object selected");
    }
    ImGui::End();
}

unique_ptr<CPanel_Inspector> CPanel_Inspector::Create(EDITOR_CONTEXT& Context)
{
    auto pInstance = unique_ptr<CPanel_Inspector>(new CPanel_Inspector(Context));
    if (FAILED(pInstance->Initialize()))
    {
        MSG_BOX("Failed to Create : CPanel_Inspector");
        pInstance.reset();
    }
    return pInstance;
}
```

### 3-6. CEditorUI — 레이아웃 + 패널 소유

헤더 (2단계 헤더를 아래로 교체):

```cpp
#pragma once
#include "EditorUI_Defines.h"

NS_BEGIN(MapTool)
class CPanel_Hierarchy;
class CPanel_Inspector;

// 메뉴바, 레이아웃 계산, 공용 상태(EDITOR_CONTEXT) 보관, 패널 2개 소유
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
	f32_t		m_fSidePanelWidth = { 280.f };

	PANEL_RECT	m_tHierarchy = {};
	PANEL_RECT	m_tInspector = {};

	EDITOR_CONTEXT					m_Context;		// 패널들이 참조로 공유

	unique_ptr<CPanel_Hierarchy>	m_pHierarchy;
	unique_ptr<CPanel_Inspector>	m_pInspector;

private:
	void		Calc_Layout();
	void		Render_MenuBar();

public:
	static unique_ptr<CEditorUI> Create();
};
NS_END
```

- **멤버 선언 순서**: `m_Context`가 패널들보다 위에 있어야 먼저 만들어지고 나중에 사라진다 (패널이 참조를 들고 있으므로).
- **전방 선언 + unique_ptr**: 소멸자 `~CEditorUI()`를 cpp에 둬서 패널 타입이 완전할 때 지워지게 한다.
- `#include "EditorUI_Defines.h"`로 바꿨으므로, 이 헤더를 포함하는 cpp는 그 전에 imgui.h가 있어야 한다 → `Level_MapTool.cpp`는 이미 imgui.h를 먼저 포함하고 있다.

cpp:

```cpp
#include "EditorUI_Utils.h"
#include "EditorUI.h"
#include "Panel_Hierarchy.h"
#include "Panel_Inspector.h"

HRESULT CEditorUI::Initialize()
{
    m_pHierarchy = CPanel_Hierarchy::Create(m_Context);
    m_pInspector = CPanel_Inspector::Create(m_Context);

    if (nullptr == m_pHierarchy || nullptr == m_pInspector)
        return E_FAIL;
	return S_OK;
}

void CEditorUI::Update(const f32_t& fDeltaTime)
{
    Render_MenuBar();
    Calc_Layout();

    m_pHierarchy->Render(m_tHierarchy);
    m_pInspector->Render(m_tInspector);
}

void CEditorUI::Calc_Layout()
{
    // 현재 창 영역 크기 (1600, 900)
    const ImVec2 vDisplay = ImGui::GetIO().DisplaySize;

    // 메뉴바 바로 아래부터
    const f32_t fTop    = m_fMenuBarHeight;
    const f32_t fHeight = vDisplay.y - fTop;

    // 창이 너무 좁으면 두 패널이 겹치지 않게 폭을 줄인다
    const f32_t fSide = min(m_fSidePanelWidth, vDisplay.x * 0.5f);

    // 두 창의 Rect {Left, Top, Width, Height}
    m_tHierarchy    = { 0.f, fTop, fSide, fHeight };
    m_tInspector    = { vDisplay.x - fSide, fTop, fSide, fHeight };
}
```

- **Update 순서**: 메뉴바를 먼저 그려야 그 프레임의 메뉴바 높이가 잡힌다 → 레이아웃 → 패널.
- **패널 순서 Hierarchy → Inspector**: Hierarchy가 선택을 바꾸면 같은 프레임의 Inspector가 바로 반영한다.
- **Calc_Layout**: `DisplaySize`는 Win32 백엔드가 매 프레임 클라이언트 영역 크기로 채운다. 가운데는 계산하지 않는다. 두 패널 사이가 그대로 뷰포트다.
- 접힌 창도 같은 Rect를 받는다. 접혀 있으면 ImGui가 제목 줄 높이만큼만 그린다.

### 확인

- 메뉴바 아래 왼쪽/오른쪽에 창 2개가 붙어 있고 드래그/크기 조절이 안 된다
- 제목 줄 ▼를 누르면 제목 줄만 남고, 다시 누르면 펼쳐진다
- 가운데는 회색 (Renderer가 씬 텍스처를 0.75 회색으로 지우고 백버퍼로 복사한 화면)

---

## 4단계. 게임 화면 위에 UI — 뷰포트 입력 판정

**목표**: 패널이 없는 영역(= 뷰포트)을 마우스/키보드가 쓰고 있는지 매 프레임 `EDITOR_CONTEXT`에 기록한다. 5단계 카메라, 12·14단계 피킹, 15단계 기즈모가 이 값을 쓴다.

### 엔진 선행 조건

- `CRenderer::Render_GameObject`: `m_pSceneRTV`에 객체를 그리고, `m_bUseBlur`면 블러, `m_bDrawToBackBuffer`(기본값 true)면 `Render_FullScreen`으로 백버퍼에 복사
- ImGui `io.WantCaptureMouse`, `io.WantCaptureKeyboard`

### 4-1. 화면이 그려지는 순서 (코드 변경 없음)

```
CToolMainApp::Render
 ├ 백버퍼/깊이 클리어
 └ Draw()
     ├ Renderer::Render_GameObject
     │   ├ SceneRTV(1600×900 텍스처)에 객체 그리기   ← 클리어 색 0.75 회색
     │   ├ (m_bUseBlur) 블러
     │   └ (m_bDrawToBackBuffer == true) Render_FullScreen → 백버퍼로 복사
     └ CLevel_MapTool::Render → Render_ImGui       ← 백버퍼 위에 패널
```

- **`Set_DrawToBackBuffer`는 건드리지 않는다**: 기본값 true 그대로라 게임과 똑같이 화면 전체에 씬이 나온다.
- **렌더 타깃은 그대로 둔다**: 블러 같은 후처리를 하려면 그린 화면을 텍스처로 다시 읽어야 하기 때문이다. 툴 입장에서는 결과가 백버퍼에 복사되므로 신경 쓸 게 없다.
- **좌표 기준이 같다**: 백버퍼 = 창의 클라이언트 영역이다. 그래서 ImGui 마우스 좌표(`io.MousePos`)가 게임 화면 픽셀 좌표와 같은 기준이다. 피킹(12단계)에서 좌표를 거의 변환하지 않아도 된다.

### 4-2. EDITOR_CONTEXT — 뷰포트 입력 상태

```cpp
struct EDITOR_CONTEXT
{
	// 뷰포트 (패널이 없는 게임 화면 영역)
	bool_t		bViewportHovered = {};			// 마우스를 ImGui가 쓰지 않음 -> 카메라 회전, 피킹
	bool_t		bViewportFocused = {};			// 키보드를 ImGui가 쓰지 않음 -> WASD 이동
};
```

### 4-3. CEditorUI::Update — 매 프레임 기록

```cpp
void CEditorUI::Update(const f32_t& fDeltaTime)
{
    // 이번 프레임 마우스/키보드를 ImGui가 가져가는지 (NewFrame에서 계산된 값)
    const ImGuiIO& io = ImGui::GetIO();
    m_Context.bViewportHovered = !io.WantCaptureMouse;
    m_Context.bViewportFocused = !io.WantCaptureKeyboard;

    Render_MenuBar();
    Calc_Layout();

    m_pHierarchy->Render(m_tHierarchy);
    m_pInspector->Render(m_tInspector);
}
```

- **WantCaptureMouse가 true인 경우**
  - 마우스가 ImGui 창(접힌 제목 줄, 메뉴바 포함) 위에 있을 때
  - ImGui 창 위에서 누르기 시작한 드래그 중일 때
  - 팝업이 열려 있을 때
- **WantCaptureMouse가 false인 경우**: 뷰포트에서 누르기 시작한 드래그는 중간에 패널 위를 지나가도 false가 유지된다. 그래서 카메라 회전이 끊기지 않는다.
- **WantCaptureKeyboard**: 입력칸 편집 중이거나, `NavEnableKeyboard`(2단계)가 켜진 상태로 ImGui 창에 포커스가 있으면 true다. 패널이 없는 곳을 클릭하면 ImGui 창 포커스가 풀려 false가 된다. → "뷰포트를 클릭해야 WASD가 먹는" 동작이 저절로 된다.
- **한 프레임 늦은 값**: `NewFrame` 때 지난 프레임의 창 배치로 계산된다. 한 프레임 차이는 문제없다.
- 맨 앞에서 계산하는 이유: 뒤에서 그리는 패널이나 팝업이 이번 프레임 값에 영향을 주지 않게, 그리기 전에 한 번만 읽어 둔다.

### 4-4. 확인용 표시 (임시)

`Render_MenuBar`의 `EndMainMenuBar()` 바로 위에:

```cpp
    ImGui::TextDisabled(m_Context.bViewportHovered ? "Viewport" : "UI");
```

- 메뉴바 안에서 Text를 부르면 메뉴 옆에 글자가 붙는다. 확인이 끝나면 지워도 된다.

### 확인

- 가운데 회색 영역에 마우스 → 메뉴바에 `Viewport`, 패널/메뉴바 위 → `UI`
- 패널을 접으면 그 자리도 `Viewport`
- 가운데를 누른 채 패널 위로 끌고 가도 `Viewport` 유지

---

## 5단계. 맵툴 카메라 + SkyBox + 카메라 조작 제한

**목표**: 화면에 SkyBox가 보이고, **마우스가 패널 밖에 있고 키보드를 ImGui가 쓰지 않을 때만** WASD 이동 / 우클릭 드래그 회전이 된다.

### 엔진/클라이언트 선행 조건

- 엔진: `CCamera`(`CAMERA_DESC`, `Update_PipeLines`), `Add_Camera / Set_MainCamera / Get_MainCamera`, DirectInput 함수(`Get_DIKeyState`, `Get_DIMouseState`, `Get_DIMouseMove`)
- 클라이언트: `SkyBox.cpp` — `_MAPTOOL`이면 `LEVEL::MAPTOOL`에서 `Texture_SkyBox / VIBuffer_SkyBox / VS_VTXTEX / PS_VTXTEX_SKYBOX`를 찾는다
- vcxproj에 `..\..\Client\Private\SkyBox.cpp` 추가, `MapTool_Cam.cpp` 추가

### 5-1. CMapTool_Cam

```cpp
// MapTool_Cam.h
#pragma once
#include "Camera.h"
#include "Client_Defines.h"
NS_BEGIN(Client)
class CMapTool_Cam : public CCamera
{
public:
    typedef struct tagMapToolCamDesc : public CCamera::CAMERA_DESC
    {
        f32_t			fSensor = {};
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

    virtual void        Set_ViewportFocused(bool_t bFocused) { m_bViewportFocused = bFocused; }
    virtual void        Set_ViewportHovered(bool_t bHovered) { m_bViewportHovered = bHovered; }
private:
    bool_t      m_bViewportFocused = { false };
    bool_t      m_bViewportHovered = { false };
    f32_t	    m_fMouseSensor = {};
private:
    void        KeyInput(const f32_t fDeltaTime);

public:
    static shared_ptr<CMapTool_Cam> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
    shared_ptr<CPrototype> Clone(void* pArg) override;
};
NS_END
```

- **namespace Client**: 게임 카메라들과 같은 자리에 두었다. 맵툴에서만 쓰지만 ImGui를 모른다.
- **DESC 상속**: 부모 `CAMERA_DESC`(Eye/At/Fov/Near/Far/속도)에 마우스 감도만 더한다.
- **Set_ViewportFocused/Hovered**: 카메라는 ImGui를 모르므로 레벨이 매 프레임 알려 준다 (5-4). 값은 4단계에서 기록한 뷰포트 입력 상태.

```cpp
// MapTool_Cam.cpp
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
	auto    pDesc = static_cast<tagMapToolCamDesc*>(pArg);
	m_fMouseSensor = pDesc->fSensor;

	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;
	return S_OK;
}

void CMapTool_Cam::Priority_Update(f32_t fTimeDelta)
{
}

void CMapTool_Cam::Update(f32_t fDeltaTime)
{
	__super::Update(fDeltaTime);
	if (m_bViewportFocused && m_bViewportHovered)
		KeyInput(fDeltaTime);
}

void CMapTool_Cam::Late_Update(f32_t fDeltaTime)
{
	__super::Late_Update(fDeltaTime);
}

HRESULT CMapTool_Cam::Render()
{
	return __super::Render();
}
```

- **Update 조건**: 키보드를 ImGui가 쓰지 않고(Focused) 마우스가 패널 밖일 때(Hovered)만 입력을 받는다. Inspector 입력칸에 "w"를 쳐도, 패널 위에서 우클릭 드래그를 해도 카메라가 안 움직인다.

```cpp
void CMapTool_Cam::KeyInput(const f32_t fDeltaTime)
{
	if (CGameInstance::Get().Get_DIKeyState(DIK_W))
		m_pTransformCom->Go_Straight(fDeltaTime);
	if (CGameInstance::Get().Get_DIKeyState(DIK_S))
		m_pTransformCom->Go_Backward(fDeltaTime);
	if (CGameInstance::Get().Get_DIKeyState(DIK_A))
		m_pTransformCom->Go_Left(fDeltaTime);
	if (CGameInstance::Get().Get_DIKeyState(DIK_D))
		m_pTransformCom->Go_Right(fDeltaTime);

	int32_t     iMouseMove = {};
	if (CGameInstance::Get().Get_DIMouseState(DIM::RB))
	{
		if (iMouseMove = CGameInstance::Get().Get_DIMouseMove(DIMM::Y))
			m_pTransformCom->Turn(m_pTransformCom->Get_State(STATE::RIGHT), m_fMouseSensor * iMouseMove * fDeltaTime);
		if (iMouseMove = CGameInstance::Get().Get_DIMouseMove(DIMM::X))
			m_pTransformCom->Turn(XMVectorSet(0.f, 1.f, 0.f, 0.f), m_fMouseSensor * iMouseMove * fDeltaTime);
	}
	Update_PipeLines();
}

shared_ptr<CMapTool_Cam> CMapTool_Cam::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
	auto pInstance = shared_ptr<CMapTool_Cam>(new CMapTool_Cam(pDevice, pContext));
	if (FAILED(pInstance->Initialize_Prototype()))
		pInstance.reset();
	return pInstance;
}

shared_ptr<CPrototype> CMapTool_Cam::Clone(void* pArg)
{
	auto pInstance = shared_ptr<CMapTool_Cam>(new CMapTool_Cam(*this));
	if (FAILED(pInstance->Initialize(pArg)))
		pInstance.reset();
	return pInstance;
}
```

- **WASD**: Transform이 Look/Right 방향으로 `fSpeedPerSec * dt`만큼 이동.
- **우클릭 드래그 회전**: 마우스 Y 이동 → 자기 Right축 기준(위아래 보기), X 이동 → 월드 Y축 기준(좌우 돌기). Y축을 월드 기준으로 해야 카메라가 기울지 않는다.
- **Update_PipeLines**: 바뀐 Transform으로 View/Proj 행렬을 파이프라인에 넣는다.

### 5-2. 로더에 원형 추가

```cpp
// 텍스처 구역
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::MAPTOOL), Proto::Texture_SkyBox,
        CTexture::Create(m_pDevice, m_pContext, TEXT("../../../Resource/Ex/proc_preview.png"), 1))))
        return E_FAIL;

// 모델 구역
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::MAPTOOL), Proto::VIBuffer_SkyBox,
        CVIBuffer_SkyBox::Create(m_pDevice, m_pContext))))
        return E_FAIL;

// 셰이더 구역
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::MAPTOOL), Proto::VS_VTXTEX,
        CVertexShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Model_VertexShader.hlsl", VTXNORM::Elements, VTXNORM::iNumElements, "VS_MAIN"))))
        return E_FAIL;
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::MAPTOOL), Proto::PS_VTXTEX_SKYBOX,
        CPixelShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Model_PixelShader.hlsl", "PS_MAIN_SKY"))))
        return E_FAIL;
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::MAPTOOL), Proto::PS_VTXTEX_NOLIGHT,
        CPixelShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Model_PixelShader.hlsl", "PS_MAIN_NOLIGHT"))))
        return E_FAIL;

// 객체원형 구역
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::MAPTOOL), Proto::Obj_SkyBox,
        CSkyBox::Create(m_pDevice, m_pContext))))
        return E_FAIL;
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::MAPTOOL), Proto::Obj_MapToolCam,
        CMapTool_Cam::Create(m_pDevice, m_pContext))))
        return E_FAIL;
```

- 맨 위 include에 `#include "SkyBox.h"`, `#include "MapTool_Cam.h"` 추가.
- SkyBox는 `VTXNORM` 정점(VS_MAIN) + 하늘용 PS(`PS_MAIN_SKY`). `PS_VTXTEX_NOLIGHT`는 지금은 쓰지 않지만 현재 로더에 있는 원형이라 같이 넣는다.
- **모든 원형은 `LEVEL::MAPTOOL`에 등록**: 로딩 레벨에서 맵툴 레벨로 넘어갈 때 지워지지 않는다. 사본도 같은 레벨에서 Clone한다.

### 5-3. CLevel_MapTool — 사본 생성

헤더에 추가:

```cpp
private:
	HRESULT Ready_Layer_BackGround(const tchar_t* pLayerTag);
	HRESULT Ready_Layer_GameObject(const tchar_t* pLayerTag);
	void	Sync_Viewport();
```

cpp — include에 `#include "MapTool_Cam.h"`를 추가하고, Initialize에서 **ImGui 준비 전에**:

```cpp
    if (FAILED(Ready_Layer_BackGround(TEXT("Layer_BackGround"))))
        return E_FAIL;
    if (FAILED(Ready_Layer_GameObject(TEXT("Layer_GameObject"))))
        return E_FAIL;
```

```cpp
HRESULT CLevel_MapTool::Ready_Layer_BackGround(const tchar_t* pLayerTag)
{
    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::MAPTOOL), Proto::Obj_SkyBox,
        ETOUI(LEVEL::MAPTOOL), Layer::BackGround, GO::SkyBox)))
        return E_FAIL;
    return S_OK;
}

HRESULT CLevel_MapTool::Ready_Layer_GameObject(const tchar_t* pLayerTag)
{
    CMapTool_Cam::CAMERA_MAPTOOL_CAM_DESC         CameraDesc{};
    CameraDesc.fDegreeRotPerSec = 180.f;
    CameraDesc.fSpeedPerSec = 10.f;
    CameraDesc.vEye = float4_t(0.f, 1.f, -5.f, 1.f);
    CameraDesc.vAt = float4_t(0.f, 1.f, 0.f, 1.f);
    CameraDesc.fFovy = 60.f;
    CameraDesc.fNear = 0.1f;
    CameraDesc.fFar = 1000.f;
    CameraDesc.fSensor = 0.05f;

    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::MAPTOOL), Proto::Obj_MapToolCam,
        ETOUI(LEVEL::MAPTOOL), pLayerTag, GO::MapToolCam, &CameraDesc)))
        return E_FAIL;

    auto pMapToolCam = dynamic_pointer_cast<CMapTool_Cam>(CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::MAPTOOL), pLayerTag, GO::MapToolCam));
    CGameInstance::Get().Add_Camera(CAMERA::FREE, pMapToolCam);
    CGameInstance::Get().Set_MainCamera(CAMERA::FREE);
    return S_OK;
}
```

- **SkyBox**: `Layer_BackGround`에 하나. 카메라 위치를 따라다니며 가장 먼저(Priority) 그려진다.
- **카메라**: (0,1,-5)에서 +Z를 본다. 6단계에서 원점에 만드는 객체가 정면에 보인다.
- **Add_Camera / Set_MainCamera**: 엔진 카메라 매니저에 등록하고 메인으로 지정한다. 12단계의 `Get_MainCamera()->Compute_PickingRay`가 이 카메라를 쓴다.

### 5-4. 뷰포트 입력 상태를 카메라에 전달

EditorUI.h에 getter 추가:

```cpp
public:
	bool_t		Get_ViewportFocused() { return m_Context.bViewportFocused; }
	bool_t		Get_ViewportHovered() { return m_Context.bViewportHovered; }
```

Level_MapTool.cpp:

```cpp
void CLevel_MapTool::Update(f32_t fDeltaTime)
{
    __super::Update(fDeltaTime);
    if (FAILED(Begin_ImGui()))
        return;
    m_pEditorUI->Update(fDeltaTime);
    Sync_Viewport();
}

void CLevel_MapTool::Sync_Viewport()
{
    auto pCamera = dynamic_pointer_cast<CMapTool_Cam>(CGameInstance::Get().Get_MainCamera());
    if (nullptr == pCamera)
        return;
    pCamera->Set_ViewportFocused(m_pEditorUI->Get_ViewportFocused());
    pCamera->Set_ViewportHovered(m_pEditorUI->Get_ViewportHovered());
}
```

- **순서**: 엔진은 객체 Update(카메라 포함) → 레벨 Update 순으로 돈다. 그래서 이번 프레임 UI에서 얻은 값은 **다음 프레임** 카메라가 쓴다. 한 프레임 늦어도 문제없다.
- `Get_MainCamera()`는 `CCamera`를 반환하므로 `CMapTool_Cam`으로 캐스팅한다.

### 확인

- 가운데(패널을 접으면 화면 전체)에 하늘이 보인다
- 패널이 없는 곳을 한 번 클릭 → 그 위에서 WASD / 우클릭 드래그로 시점 이동
- 마우스를 Hierarchy로 옮기거나 다른 창을 클릭하면 카메라가 멈춘다

---

## 6단계. 배치 객체 — CMapObject + FBX 모델 + CStaticProp + 조명/안개 + 생성 메뉴

**목표**: Hierarchy 빈 곳을 우클릭 → `Add Static_Prop` → 화면 가운데(원점)에 FBX 모델이 **조명을 받은 색으로** 생긴다. (아직 목록에는 안 보임 → 7단계)

### 엔진/클라이언트 선행 조건

- 엔진
  - `CModel::Create(device, context, "fbx 경로")`, `Get_NumMeshes / Bind_Material / Render`, `GetBoundinBox`
  - `CGameObject`의 `m_pRS`(래스터라이저 상태), `m_tMaterial`(머티리얼), `Remove_Component`, `Add_Component`
  - `CGameInstance::Has_Prototype`, `Get_ModelTags`
  - `Normalize_AssetPath`, `Quat_To_EulerDeg` (Engine_Function.h)
  - `CB_PER_OBJECT_LIT`(World, WorldInvTranspose, Material)
- 클라이언트 셰이더: `Model_VertexShader.hlsl`의 `VS_MAIN_MODEL`, `Model_PixelShader.hlsl`의 `PS_MAIN_MODEL`
- vcxproj에 `MapObject.cpp`, `StaticProp.cpp`, `Fog.cpp`, `SunLight.cpp` 추가 (Fog/SunLight는 Client에 이미 있는 클래스를 그대로 쓴다)

### 6-1. CMapObject — 배치 객체의 부모 (Client)

```cpp
// MapObject.h
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
        uint32_t  iLevelIndex = {};
        float3_t  vPosition = {};
        float4_t  vQuaternion = { 0.f, 0.f, 0.f, 1.f };     // 단위 쿼터니언 (회전 없음)
        float3_t  vScale = { 1.f, 1.f, 1.f };
        wstring_t strMeshPath;
        wstring_t strTexturePath;
        bool_t    bEditorMode = { false };
    }MAPOBJECT_DESC;
```

- **DESC 한 장**으로 "어디에, 어떤 회전/크기로, 어떤 메시/텍스처로" 만들지 정한다. 맵 파일 저장/불러오기도 결국 이 DESC를 쓰고 읽는 것.
- `iLevelIndex`: 자원 원형을 찾을 레벨. 툴은 MAPTOOL, 게임은 GAMEPLAY.
- `bEditorMode`: 툴에서만 다르게 동작할 때 쓰려고 둔 값.

```cpp
protected:
    CMapObject(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
    virtual ~CMapObject() = default;

public:
    virtual HRESULT Initialize(void* pArg) override;

    const float3_t& Get_Position() const { return m_vPosition; }
    const float3_t& Get_Scale()    const { return m_vScale; }
    void Set_Position(const float3_t& v) { m_vPosition = v; Apply_Transform(); }
    void Set_Scale(const float3_t& v) { m_vScale = v;    Apply_Transform(); }
    const float4_t& Get_Quaternion() const { return m_vQuaternion; }
    const float3_t& Get_EulerHint()  const { return m_vEulerHint; }
    void Set_RotationEuler(const float3_t& vDeg);
    void Set_Transform(const float3_t& vPos, const float4_t& vQuat, const float3_t& vScale);

    virtual void Save_Extra(ofstream& Out) const {}
    virtual void Load_Extra(ifstream& In, MAPOBJECT_DESC& Desc) {}
    const wstring_t& Get_MeshPath() const { return m_strMeshPath; }
protected:
    void Apply_Transform();

protected:
    uint32_t  m_iLevelIndex = {};
    float3_t  m_vPosition = {};
    float3_t  m_vScale = { 1.f, 1.f, 1.f };
    wstring_t m_strMeshPath;
    wstring_t m_strTexturePath;
    float4_t  m_vQuaternion = { 0.f, 0.f, 0.f, 1.f };   // 원본 값: Transform, 저장 모두 이 값 기준
    float3_t  m_vEulerHint = {};                        // 표시용: Inspector에 보여 줄 각도(degree)
    bool_t    m_bEditorMode = { false };
};
NS_END
```

- **위치/회전/크기를 따로 보관**: Transform 행렬에서 다시 뽑으면 오차가 쌓이고 각도가 튄다. 원본 값을 들고 있다가 바뀔 때마다 `Apply_Transform`으로 행렬을 다시 만든다.
- **회전 원본 = 쿼터니언, 표시 = EulerHint**: Inspector에서 (0, 90, 0)을 넣었는데 행렬에서 되돌리면 (180, 90, 180)처럼 다른 값이 나올 수 있다. 사용자가 넣은 각도를 표시용으로 따로 기억한다.
- **Set_Transform**: 기즈모(15단계)처럼 행렬에서 분해한 값을 한 번에 넣을 때 쓴다.
- **Save_Extra/Load_Extra**: 자식마다 추가로 저장할 값(지형 레이어 경로 등)을 위한 자리. 아직 비어 있음.
- 이 단계에서 Transform 관련 함수를 **전부** 만들어 둔다. 9단계 Inspector와 15단계 기즈모는 이 함수들을 부르기만 한다.

```cpp
// MapObject.cpp
#include "MapObject.h"

CMapObject::CMapObject(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    :CGameObject(pDevice, pContext)
{
}

HRESULT CMapObject::Initialize(void* pArg)
{
    if (nullptr == pArg)
        return E_FAIL;

    // 구조체 채우기
    auto pDesc = static_cast<MAPOBJECT_DESC*>(pArg);
    m_iLevelIndex = pDesc->iLevelIndex;
    m_vPosition = pDesc->vPosition;
    m_vScale = pDesc->vScale;
    m_strMeshPath = pDesc->strMeshPath;
    m_strTexturePath = pDesc->strTexturePath;
    m_bEditorMode = pDesc->bEditorMode;
    m_vQuaternion = pDesc->vQuaternion;

    // TransformCom 생성
    if (FAILED(__super::Initialize(pArg)))
        return E_FAIL;
    Set_Transform(m_vPosition, m_vQuaternion, m_vScale);
    return S_OK;
}
```

- DESC를 멤버로 복사 → 부모 `CGameObject::Initialize`가 Transform 컴포넌트를 만든다 → 그 Transform에 초기 값을 넣는다. Transform이 생기기 전에 `Apply_Transform`을 부르면 null이라 순서가 중요하다.

```cpp
void CMapObject::Set_RotationEuler(const float3_t& vDeg)
{
    m_vEulerHint = vDeg;
    XMStoreFloat4(&m_vQuaternion, XMQuaternionRotationRollPitchYaw(
        XMConvertToRadians(vDeg.x), XMConvertToRadians(vDeg.y), XMConvertToRadians(vDeg.z)));
    Apply_Transform();
}

void CMapObject::Set_Transform(const float3_t& vPos, const float4_t& vQuat, const float3_t& vScale)
{
    m_vPosition = vPos;
    m_vScale = vScale;
    XMStoreFloat4(&m_vQuaternion, XMQuaternionNormalize(XMLoadFloat4(&vQuat)));
    m_vEulerHint = Quat_To_EulerDeg(XMLoadFloat4(&m_vQuaternion));
    Apply_Transform();
}

void CMapObject::Apply_Transform()
{
    matrix_t World = XMMatrixScaling(m_vScale.x, m_vScale.y, m_vScale.z)
        * XMMatrixRotationQuaternion(XMLoadFloat4(&m_vQuaternion))
        * XMMatrixTranslation(m_vPosition.x, m_vPosition.y, m_vPosition.z);

    m_pTransformCom->Set_State(STATE::RIGHT, World.r[0]);
    m_pTransformCom->Set_State(STATE::UP, World.r[1]);
    m_pTransformCom->Set_State(STATE::LOOK, World.r[2]);
    m_pTransformCom->Set_State(STATE::POSITION, World.r[3]);
}
```

- **Set_RotationEuler**: Inspector용. 넣은 각도를 표시값으로 그대로 기억하고, 쿼터니언으로 바꿔 저장한다.
- **Set_Transform**: 쿼터니언을 정규화해서 저장하고, 표시값은 `Quat_To_EulerDeg`로 역계산한다.
- **Apply_Transform**: S × R × T로 월드 행렬을 만들고 행 4개를 Transform의 Right/Up/Look/Position에 넣는다.

### 6-2. CStaticProp — FBX 모델 하나를 그리는 구조물 (Client)

```cpp
// StaticProp.h
#pragma once
#include "Client_Defines.h"
#include "MapObject.h"

NS_BEGIN(Client)
class CStaticProp : public CMapObject
{
public:
    typedef struct tagStaticPropDesc : public MAPOBJECT_DESC
    {
    }STATICPROP_DESC;
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
    HRESULT Change_Mesh(const wstring_t& strMeshPath);

private:
    shared_ptr<CModel>              m_pModelCom;
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

- **텍스처 멤버가 없다**: FBX 모델이 머티리얼(디퓨즈 텍스처)을 들고 있어서 `Bind_Material`로 바인딩한다.
- **Change_Mesh**: 모델 경로만 바꾸면 `Com_Model` 컴포넌트를 갈아 끼운다. 처음 만들 때(`Ready_Mesh`)도 이 함수를 쓴다.

```cpp
// StaticProp.cpp
#include "StaticProp.h"

CStaticProp::CStaticProp(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    :CMapObject(pDevice, pContext)
{
}

HRESULT CStaticProp::Initialize_Prototype()
{
    if (FAILED(__super::Initialize_Prototype()))
        return E_FAIL;

    // 래스터라이저 설정
    D3D11_RASTERIZER_DESC rsDesc{};
    rsDesc.FillMode = D3D11_FILL_SOLID;
    rsDesc.CullMode = D3D11_CULL_NONE;
    rsDesc.FrontCounterClockwise = false;       // 시계방향이 전면
    rsDesc.DepthClipEnable = true;

    m_pDevice->CreateRasterizerState(&rsDesc, m_pRS.GetAddressOf());
    return S_OK;
}

HRESULT CStaticProp::Initialize(void* pArg)
{
    // 메시 경로, Transform 값을 MapObject가 채운다
    if (FAILED(__super::Initialize(pArg)))
        return E_FAIL;
    if (FAILED(Ready_Components()))
        return E_FAIL;
    if (FAILED(Ready_ConstantBuffer()))
        return E_FAIL;
    return S_OK;
}
```

- **원형에서 래스터라이저를 만든다**: Clone은 복사 생성이라 `m_pRS`(ComPtr)를 공유한다. 사본마다 만들 필요가 없다.
- **CULL_NONE**: 외부 FBX는 감기 방향이나 한 면짜리 메시가 섞여 있어서 뒷면도 그린다.
- **Initialize 순서**: 부모가 경로를 채워야 `Ready_Components`가 그 경로로 모델을 찾을 수 있다.

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
```

- 움직이는 로직이 없으므로 매 프레임 불투명 그룹에 자기를 등록만 한다.
- `Render_Mesh`가 월드/래스터라이저/PS를 인자로 받는 이유: 같은 메시를 그림자나 다른 PS로 한 번 더 그릴 때 재사용하려고.

```cpp
HRESULT CStaticProp::Change_Mesh(const wstring_t& strMeshPath)
{
    const wstring_t strMeshTag = Normalize_AssetPath(strMeshPath);

    if (false == CGameInstance::Get().Has_Prototype(m_iLevelIndex, strMeshTag))
        return E_FAIL;                              // 등록 안 된 경로 -> 기존 메시 유지

    shared_ptr<CModel> pNew;
    Remove_Component(TEXT("Com_Model"));
    if (FAILED(__super::Add_Component(m_iLevelIndex, strMeshTag, TEXT("Com_Model"), pNew)))
        return E_FAIL;

    m_pModelCom = pNew;
    m_strMeshPath = strMeshTag;
    return S_OK;
}
```

- **정규화 → 존재 확인 → 교체**: 경로를 원형 태그 형식으로 바꾸고, 없는 원형이면 아무것도 지우지 않고 실패만 돌려준다.
- **Remove_Component 먼저**: 같은 슬롯 이름(`Com_Model`)으로 다시 넣으려면 기존 것을 빼야 한다. 12단계 피킹이 `Find_Component(L"Com_Model")`로 이 슬롯을 찾는다.
- **m_strMeshPath에 정규화된 태그 저장**: 10단계 콤보가 "지금 어떤 모델인지"를 이 값으로 비교한다.

```cpp
HRESULT CStaticProp::Ready_Components()
{
    if (FAILED(Ready_Mesh()))
        return E_FAIL;
    if (FAILED(__super::Add_Component(m_iLevelIndex, Proto::VS_MODEL, TEXT("Com_VS"), m_pVS)))
        return E_FAIL;
    if (FAILED(__super::Add_Component(m_iLevelIndex, Proto::PS_MODEL, TEXT("Com_PS"), m_pPS)))
        return E_FAIL;
    return S_OK;
}

HRESULT CStaticProp::Ready_ConstantBuffer()
{
    m_pCB = CConstantBuffer::Create(m_pDevice, m_pContext, &m_tCBData, sizeof(m_tCBData));
    if (nullptr == m_pCB)
        return E_FAIL;
    return S_OK;
}

HRESULT CStaticProp::Ready_Mesh()
{
    if (FAILED(Change_Mesh(m_strMeshPath)))       return E_FAIL;
    return S_OK;
}

HRESULT CStaticProp::Update_ConstantBuffer(const matrix_t& matWorld)
{
    XMMATRIX matNoTrans = matWorld;
    matNoTrans.r[3] = XMVectorSet(0.f, 0.f, 0.f, 1.f);
    XMMATRIX matWorldInvTranspos = XMMatrixTranspose(XMMatrixInverse(nullptr, matNoTrans));

    XMStoreFloat4x4(&m_tCBData.mat_World, (matWorld));
    XMStoreFloat4x4(&m_tCBData.mat_WorldInvTranspose, (matWorldInvTranspos));
    m_tCBData.tMaterial = m_tMaterial;
    return S_OK;
}
```

- **셰이더**: 모델 정점(`VTXMESH`)용 VS와 조명 PS.
- **역전치 행렬**: 크기가 균일하지 않을 때도 법선이 표면에 수직이 되게 한다. 이동은 법선에 상관없으므로 지운 뒤 계산한다.
- **m_tMaterial**: 엔진 `CGameObject`에 있는 기본 머티리얼(Ambient 1 등). 조명 PS가 이 값과 광원을 곱한다.

```cpp
HRESULT CStaticProp::Bind_Shader(shared_ptr<CVertexShader> pVS, shared_ptr<CPixelShader> pPS)
{
    if (FAILED(pVS->Begin()))
        return E_FAIL;
    if (FAILED(pPS->Begin()))
        return E_FAIL;
    return S_OK;
}

HRESULT CStaticProp::Bind_ShaderResources(const matrix_t& matWorld)
{
    if (FAILED(Update_ConstantBuffer(matWorld)))
        return E_FAIL;
    if (FAILED(m_pCB->Bind_Vertex_ShaderResource(0, &m_tCBData)))
        return E_FAIL;
    if (FAILED(m_pCB->Bind_Pixel_ShaderResource(0, &m_tCBData)))
        return E_FAIL;
    return S_OK;
}

HRESULT CStaticProp::Render_Mesh(const XMMATRIX& matWorld, ID3D11RasterizerState* pRS, shared_ptr<CPixelShader> pPS)
{
    if (FAILED(__super::Render()))
        return E_FAIL;

    m_pContext->RSSetState(pRS);

    if (FAILED(Bind_ShaderResources(matWorld)))
        return E_FAIL;
    if (FAILED(Bind_Shader(m_pVS, pPS)))
        return E_FAIL;

    uint32_t iNumMeshes = m_pModelCom->Get_NumMeshes();
    for (uint32_t i = 0; i < iNumMeshes; ++i)
    {
        if (FAILED(m_pModelCom->Bind_Material(i, aiTextureType_DIFFUSE, 0, 0)))
            return E_FAIL;
        if (FAILED(m_pModelCom->Render(i)))
            return E_FAIL;
    }
    return S_OK;
}

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

- **상수버퍼 b0**: 매 프레임 지금 월드로 갱신해서 VS/PS 둘 다 바인딩한다. 한 번만 채우면 Inspector로 옮겨도 화면이 그대로다.
- **메시마다 머티리얼 → 그리기**: FBX 하나에 메시가 여러 개일 수 있고, 각자 다른 디퓨즈 텍스처(t0)를 쓴다.

### 6-3. 로더에 원형 추가

```cpp
// 맨 위 include
#include "StaticProp.h"
#include "Fog.h"

// 모델 구역 — 태그는 "Resource 기준 경로"를 정규화한 값
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::MAPTOOL),
        Normalize_AssetPath(TEXT("Characters/0_CharacterModel_Boss_Wu/0_CharacterModel_Boss_Wu.fbx")),
        CModel::Create(m_pDevice, m_pContext,
            "../../../Resource/Characters/0_CharacterModel_Boss_Wu/0_CharacterModel_Boss_Wu.fbx"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::MAPTOOL),
        Normalize_AssetPath(TEXT("Mesh/Tree/Pfb_Tree_01_1.fbx")),
        CModel::Create(m_pDevice, m_pContext,
            "../../../Resource/Mesh/Tree/Pfb_Tree_01_1.fbx"))))
        return E_FAIL;

    // SM_Container_Back / Ceiling / Ground / L / R 도 같은 모양으로 5개
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::MAPTOOL),
        Normalize_AssetPath(TEXT("Mesh/SM_Container/SM_Container_Back.fbx")),
        CModel::Create(m_pDevice, m_pContext,
            "../../../Resource/Mesh/SM_Container/SM_Container_Back.fbx"))))
        return E_FAIL;
    ...

// 셰이더 구역
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::MAPTOOL), Proto::VS_MODEL,
        CVertexShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Model_VertexShader.hlsl", VTXMESH::Elements, VTXMESH::iNumElements, "VS_MAIN_MODEL"))))
        return E_FAIL;
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::MAPTOOL), Proto::PS_MODEL,
        CPixelShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Model_PixelShader.hlsl", "PS_MAIN_MODEL"))))
        return E_FAIL;

// 객체원형 구역
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::MAPTOOL), Proto::Obj_StaticProp,
        CStaticProp::Create(m_pDevice, m_pContext))))
        return E_FAIL;
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::MAPTOOL), Proto::Obj_Fog,
        CFog::Create(m_pDevice, m_pContext))))
        return E_FAIL;
```

- **모델 태그 = 정규화된 상대 경로** (`characters/0_charactermodel_boss_wu/...fbx`): 원형 맵에 이 태그로 들어가고, Inspector 콤보 목록(`Get_ModelTags`)도 이 태그를 그대로 꺼낸다. 객체가 가진 `m_strMeshPath`와 같은 형식이라 바로 비교된다.
- `CModel::Create`에 넘기는 실제 파일 경로는 `char*`(assimp용)라 따로 적는다.
- 현재 로더에 `matrix_t PreTransformMatrix = XMMatrixRotationY(180.f);`가 있지만 아무 데도 넘기지 않는다. 따라 적을 필요 없다.
- **Fog 원형**은 조명과 함께 지금 넣는다 (6-6).

### 6-4. EditorUI_Defines.h — 생성 메뉴 목록 + 모델 목록 + 이름 번호

```cpp
struct EDITOR_CONTEXT
{
	uint32_t	m_iNextID = {};					// "Prop_N"의 N

	// 뷰포트 (4단계)
	...
};

// 빈 곳 우클릭 메뉴에 보일 배치 가능한 목록
struct PLACEABLE
{
	const char*    pName;				// 메뉴에 보일 이름
	const wchar_t* pPrototypeTag;		// Add_GameObject에 넘길 프로토타입 태그
};

static constexpr PLACEABLE s_Placeables[] = {
	{ "Add Static_Prop", Proto::Obj_StaticProp },
};

// { 표시 이름, 경로 } 목록 (Inspector 콤보, Hierarchy 생성 기본값)
struct ASSET_ENTRY
{
	string    strDisplayName;  // 콤보에 보일 이름 (ImGui용 UTF-8)
	wstring_t strPath;         // 프로토타입 태그 (정규화된 경로)
};

inline vector<ASSET_ENTRY> g_Models;
```

- **m_iNextID**: `Prop_00, Prop_01...` 이름을 만들 번호. 삭제해도 줄어들지 않는다.
- **s_Placeables**: 메뉴에 보일 이름과 원형 태그 짝. 11단계에서 `Add Terrain`이 한 줄 추가된다. 메뉴 코드를 고치지 않고 표만 늘리면 된다.
- **g_Models**: 로드된 모델 목록. 생성 기본값(`g_Models[0]`)과 10단계 콤보가 같이 쓴다. `inline` 변수라 여러 cpp에서 포함해도 하나만 생긴다.

### 6-5. 모델 목록 채우기 + To_UTF8

EditorUI_Utils.h에 추가:

```cpp
// wstring -> UTF-8 (ImGui에 표시할 때)
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
```

- 길이를 직접 넘기므로 결과 문자열에 널 문자가 끼지 않는다.

Panel_Inspector.cpp:

```cpp
HRESULT CPanel_Inspector::Initialize()
{
    auto ModelTags = CGameInstance::Get().Get_ModelTags(ETOUI(LEVEL::MAPTOOL));

    for (auto& ModelTag : ModelTags)
    {
        wchar_t szFileName[MAX_PATH] = {};
        _wsplitpath_s(ModelTag.c_str(), nullptr, 0, nullptr, 0, szFileName, MAX_PATH, nullptr, 0);
        g_Models.push_back({ To_UTF8(szFileName), ModelTag });
    }
    return S_OK;
}
```

- **Get_ModelTags**: MAPTOOL 레벨 원형 중 `CModel`인 것의 태그만 모은다. 로더에 모델을 추가하면 목록에 자동으로 생긴다.
- **_wsplitpath_s**: 경로에서 파일 이름(확장자 제외)만 떼어 콤보 표시용으로 쓴다.
- **여기서 채우는 이유**: Inspector는 맵툴 레벨 Initialize 때 만들어지고, 그 시점엔 로딩이 끝나 있다. 생성 메뉴가 `g_Models[0]`을 쓰므로 6단계에서 반드시 채워져 있어야 한다.
- 원형 맵이 태그 순으로 정렬돼 있어서 `g_Models[0]`은 `characters/0_charactermodel_boss_wu/...`가 된다.

### 6-6. CLevel_MapTool — 조명 + 안개

헤더에 `HRESULT Ready_Lights();` 추가.

cpp: include에 `#include "SunLight.h"`, Initialize에서 `Ready_Layer_GameObject` 다음:

```cpp
    if (FAILED(Ready_Lights()))
        return E_FAIL;
```

```cpp
HRESULT CLevel_MapTool::Ready_Layer_BackGround(const tchar_t* pLayerTag)
{
    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::MAPTOOL), Proto::Obj_SkyBox,
        ETOUI(LEVEL::MAPTOOL), Layer::BackGround, GO::SkyBox)))
        return E_FAIL;
    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::MAPTOOL), Proto::Obj_Fog,
        ETOUI(LEVEL::MAPTOOL), Layer::BackGround, GO::Fog)))
        return E_FAIL;
    return S_OK;
}

HRESULT CLevel_MapTool::Ready_Lights()
{
    auto pSunLight = CSunLight::Create(m_pDevice, m_pContext);
    if (nullptr == pSunLight)
        return E_FAIL;
    CGameInstance::Get().AddLight(L"SunLight", pSunLight);
    return S_OK;
}
```

- **CSunLight**: 방향광(Ambient 0.25, Diffuse 0.75, 방향 (0.5,-0.5,0.5)). 엔진 라이트 매니저에 등록하면 매 프레임 b3 상수버퍼를 갱신·바인딩한다. GameObject가 아니라 `CLight`라 `Add_GameObject`가 아니라 `AddLight`.
- **CFog**: 그리지는 않고 안개 상수버퍼(b5)만 바인딩한다. **없으면 PS에서 안개 거리로 나눌 때 0으로 나눠 조명이 있어도 검게 나온다.** 그래서 조명과 같은 단계에 넣는다.
- 원형 태그를 `Proto::Obj_Fog`로 정확히 쓸 것. `Obj_SkyBox`로 잘못 쓰면 SkyBox가 하나 더 생길 뿐 안개가 없다.

### 6-7. Hierarchy — 빈 곳 우클릭 메뉴 + 생성

헤더에 추가:

```cpp
private:
	void		Create_Object(const wstring_t& pPrototypeTag);
	void		Create_StaticProp(const wstring_t& pPrototypeTag);
```

cpp:

```cpp
#include "EditorUI_Utils.h"
#include "Panel_Hierarchy.h"
#include "StaticProp.h"

void CPanel_Hierarchy::Render(const PANEL_RECT& tRect)
{
    Set_NextPanelRect(tRect);
    if (ImGui::Begin("Hierarchy", nullptr, g_FixedPanelFlags))
    {
        // 항목 위가 아닌 창의 빈 곳을 우클릭했을 때만 열림
        if (ImGui::BeginPopupContextWindow("HierarchyMenu", ImGuiPopupFlags_MouseButtonRight | ImGuiPopupFlags_NoOpenOverItems))
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

- **BeginPopupContextWindow**: 지금 창 안에서 우클릭을 떼면 팝업을 연다. `NoOpenOverItems`는 7단계에서 생길 항목 위 우클릭(항목 메뉴)과 겹치지 않게 한다.
- **MenuItem**: 그리기 + 클릭 판정. 클릭한 프레임에 true, 팝업은 자동으로 닫힌다.

```cpp
void CPanel_Hierarchy::Create_Object(const wstring_t& pPrototypeTag)
{
    Create_StaticProp(pPrototypeTag);
}

void CPanel_Hierarchy::Create_StaticProp(const wstring_t& pPrototypeTag)
{
    CStaticProp::STATICPROP_DESC Desc{};
    Desc.iLevelIndex = ETOUI(LEVEL::MAPTOOL);
    Desc.strMeshPath = g_Models[0].strPath;           // 기본: 목록 첫 모델
    Desc.bEditorMode = true;

    wstring_t strTag;
    do {
        if (m_Context.m_iNextID < 10)
            strTag = L"Prop_0" + to_wstring(m_Context.m_iNextID++);
        else
            strTag = L"Prop_" + to_wstring(m_Context.m_iNextID++);
    } while (nullptr != CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::MAPTOOL), TEXT("Layer_Map"), strTag));

    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::MAPTOOL), pPrototypeTag,
        ETOUI(LEVEL::MAPTOOL), TEXT("Layer_Map"), strTag, &Desc)))
    {
        MSG_BOX("Create Failed");
        return;
    }
}
```

- **Create_Object**: 원형 태그에 따라 생성 방법을 나누는 입구. 지금은 하나뿐이고 11단계에서 지형 분기가 생긴다.
- **DESC**: 위치/회전/크기는 기본값(원점, 회전 없음, 1). 메시는 목록 첫 모델.
- **이름 만들기 do-while**: 번호를 하나씩 올리면서 `Layer_Map`에 같은 이름이 없을 때까지 반복한다. 엔진은 같은 태그로 Add하면 실패하기 때문. 10 미만은 `0`을 붙여 정렬이 맞게 한다.
- **Layer_Map**: 배치 객체 전용 레이어. 목록(7)과 피킹(12)은 이 레이어만 본다.

### 확인

- Hierarchy 빈 곳 우클릭 → `Add Static_Prop` → 화면 가운데(원점)에 Boss Wu 모델이 **밝게** 보인다
- 여러 번 눌러도 실패 없이 겹쳐서 생긴다 (이름이 `Prop_00`, `Prop_01`...)
- 모델이 검게 나오면 SunLight/Fog 확인 (부록 C)

---

## 7단계. Hierarchy 목록 + 선택

**목표**: Hierarchy에 `Layer_Map` 객체 이름이 나오고, 클릭하면 하이라이트된다. 새로 만든 객체는 자동으로 선택된다.

### 7-1. EDITOR_CONTEXT — 선택 상태

EditorUI_Defines.h 맨 위 include에 추가:

```cpp
#include "MapTool_Defines.h"
#include "MapObject.h"
```

EDITOR_CONTEXT 맨 앞에 추가:

```cpp
	// 선택: Hierarchy / 뷰포트 피킹이 바꾸고 Inspector가 읽는다.
	weak_ptr<CMapObject>	pSelected;			// weak_ptr: 지워지면 자동으로 만료
	wstring_t				strSelectedTag;		// 선택된 객체의 이름 ("Prop_01")

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
```

- **weak_ptr**: 선택했다고 객체 수명을 늘리지 않는다. 레이어에서 지워지면 `lock()`이 null을 돌려준다.
- **이름도 같이 저장**: 객체에는 자기 태그가 없어서(태그는 레이어 맵의 키) 목록 하이라이트와 Inspector 제목을 위해 따로 들고 있는다.
- **CMapObject로 캐스팅**: Inspector가 위치/회전/크기를 바로 부를 수 있게. 맵 객체가 아니면 null이 되어 선택이 안 된다.

### 7-2. Hierarchy — 목록 그리기

`Render`의 팝업 블록 다음에:

```cpp
        // 맵 객체 목록 가져오기
        auto pObjects = CGameInstance::Get().Get_GameObjects(ETOUI(LEVEL::MAPTOOL), TEXT("Layer_Map"));
        if (nullptr != pObjects)
        {
            for (auto& [strTag, pObject] : *pObjects)
            {
                if (nullptr == pObject || pObject->Is_Dead())
                    continue;

                // Selectable: 이름 한 줄 + 두 번째 인자가 true면 하이라이트
                //  클릭한 프레임에 true를 반환한다. 하이라이트는 Select가 끝난 다음 프레임부터 반영된다.
                if (ImGui::Selectable(To_UTF8(strTag).c_str(), strTag == m_Context.strSelectedTag))
                    m_Context.Select(strTag, pObject);
            }
        }
```

- **Get_GameObjects**: 레이어가 없으면(아직 아무것도 안 만듦) null이다.
- **Is_Dead 건너뛰기**: 8단계 삭제는 Dead 표시만 하고 실제 제거는 다음 프레임 엔진이 한다. 그 사이에 목록에 보이지 않게.
- **To_UTF8**: 엔진 태그는 wstring, ImGui는 UTF-8.

`Create_StaticProp` 끝(Add 성공 후)에 추가:

```cpp
    // 만든 객체를 바로 선택
    m_Context.Select(strTag, CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::MAPTOOL), TEXT("Layer_Map"), strTag));
```

### 확인

- 생성할 때마다 목록에 `Prop_00`, `Prop_01`... 이 추가되고 방금 만든 것이 하이라이트
- 다른 이름을 클릭하면 하이라이트가 옮겨 간다

---

## 8단계. 삭제

**목표**: 항목 우클릭 → `Delete`, 또는 Hierarchy 포커스 상태에서 Delete 키로 선택 객체를 지운다.

### 8-1. Hierarchy

헤더에 추가:

```cpp
private:
	bool_t		m_bRequestDelete = { false };		// 목록 루프가 끝난 뒤 삭제
private:
	void		Delete_Selected();
```

목록 루프 안, `Selectable` **바로 다음**:

```cpp
                // 바로 앞 Selectable 위에서 우클릭을 뗐을 때 열리는 항목 전용 메뉴
                if (ImGui::BeginPopupContextItem())
                {
                    m_Context.Select(strTag, pObject);          // 우클릭한 항목을 선택 상태로

                    if (ImGui::MenuItem("Delete", "Del"))
                        m_bRequestDelete = true;                // 루프 끝난 뒤 처리

                    ImGui::EndPopup();
                }
```

목록 블록이 끝난 뒤(`Begin` 블록 안):

```cpp
        // 우클릭 삭제
        if (m_bRequestDelete)
        {
            Delete_Selected();
            m_bRequestDelete = false;
        }
        // Delete 키 삭제: 지금 그리는 창(Hierarchy)이 포커스일 때만
        if (ImGui::IsWindowFocused() && ImGui::IsKeyPressed(ImGuiKey_Delete))
            Delete_Selected();
```

```cpp
void CPanel_Hierarchy::Delete_Selected()
{
    auto pSelected = m_Context.pSelected.lock();
    if (nullptr == pSelected)
        return;

    pSelected->Set_Dead();          // 실제 erase는 엔진 Priority_Update에서
    m_Context.Clear_Selection();    // 선택은 바로 해제
}
```

- **BeginPopupContextItem 위치**: 인자 없이 쓰면 **바로 앞 위젯의 ID**를 팝업 ID로 쓴다. Selectable 바로 다음이 아니면 엉뚱한 항목에 붙는다.
- **루프 뒤에 삭제**: 목록을 도는 중에 맵에서 지우면 반복자가 무효가 된다. 플래그만 세우고 루프 뒤에 처리한다. 게다가 `Set_Dead`는 표시만 하므로 실제 제거는 다음 프레임 엔진이 안전하게 한다.
- **Delete 키**: `IsWindowFocused`로 Hierarchy를 마지막으로 클릭했을 때만. Inspector 입력칸에서 Delete로 글자를 지울 때 객체가 지워지면 안 된다.

### 확인

- 항목 우클릭 → Delete → 목록과 화면에서 사라짐
- 항목 클릭 후 Delete 키 → 삭제
- 빈 곳 우클릭은 여전히 생성 메뉴

---

## 9단계. Inspector — 이름 + Transform

**목표**: 선택한 객체 이름과 Position / Rotation / Scale이 보이고, 드래그로 바꾸면 화면에 바로 반영된다.

### 9-1. EDITOR_CONTEXT — 선택 검사

```cpp
	// 선택한 객체가 지워졌으면 선택 해제
	void Validate_Selection()
	{
		auto pObject = pSelected.lock();
		if (nullptr == pObject || pObject->Is_Dead())
			Clear_Selection();
	}
```

- weak_ptr가 만료됐거나, 아직 레이어에 남아 있지만 Dead인 경우 둘 다 걸러 낸다.

### 9-2. Panel_Inspector::Render

```cpp
void CPanel_Inspector::Render(const PANEL_RECT& tRect)
{
    Set_NextPanelRect(tRect);
    if (ImGui::Begin("Inspector", nullptr, g_FixedPanelFlags))
    {
        m_Context.Validate_Selection();
        auto pSelected = m_Context.pSelected.lock();
        if (nullptr == pSelected)
            ImGui::TextDisabled("No object selected");
        else
        {
            // 이름
            ImGui::TextUnformatted(To_UTF8(m_Context.strSelectedTag).c_str());
            ImGui::Separator();

            // CollapsingHeader: 접을 수 있는 제목. 펼쳐져 있을 때만 true -> 그때만 안쪽을 그린다.
            if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
            {
                float3_t vPos = pSelected->Get_Position();
                if (ImGui::DragFloat3("Position", &vPos.x, 0.1f))
                    pSelected->Set_Position(vPos);

                float3_t vRot = pSelected->Get_EulerHint();
                if (ImGui::DragFloat3("Rotation", &vRot.x, 1.f))
                    pSelected->Set_RotationEuler(vRot);

                float3_t vScale = pSelected->Get_Scale();
                if (ImGui::DragFloat3("Scale", &vScale.x, 0.05f, 0.01f, 100.f))
                    pSelected->Set_Scale(vScale);
            }
        }
    }
    ImGui::End();
}
```

- **lock 한 번**: 이 프레임 동안 `pSelected`가 객체를 붙잡아 두므로 중간에 사라지지 않는다.
- **값 복사 → 위젯 → 바뀐 프레임만 Set**: `Get_Position`은 const 참조라 바로 넘길 수 없다. 지역 변수에 복사해서 위젯에 주고, 반환값이 true(값이 바뀜)일 때만 객체에 다시 넣는다.
- **Rotation은 EulerHint**: 사용자가 넣은 각도 그대로 보인다. 저장은 쿼터니언(6-1).
- **DragFloat3 인자**: `(라벨, float[3], 드래그 속도, 최소, 최대)`. Scale은 0이 되면 역행렬이 깨지므로 0.01부터.
- `TextUnformatted`: `%` 같은 서식 문자를 해석하지 않는 Text.

### 확인

- 선택하면 이름과 값이 보이고, 값을 드래그하면 화면의 모델이 움직인다
- Ctrl+클릭으로 숫자를 직접 입력할 수 있다
- 선택 객체를 삭제하면 "No object selected"

---

## 10단계. Inspector — 모델 교체 콤보

**목표**: StaticProp을 선택하면 `Components` 아래 `Model` 콤보가 보이고, 다른 모델을 고르면 바로 바뀐다.

### 10-1. EditorUI_Utils.h — 자원 콤보 도우미

```cpp
// Items         : 콤보에 보일 목록 (g_Models)
// strCurrentPath: 객체가 지금 가진 경로 (정규화된 태그)
// 반환           : 다른 항목을 고른 프레임에만 그 항목의 경로, 아니면 nullptr
inline const wchar_t* Render_AssetCombo(const char* pLabel, const vector<ASSET_ENTRY>& Items, const wstring_t& strCurrentPath)
{
	// 1. 현재 값이 목록의 몇 번째인지 찾기
	int32_t iCurrentIIndex = -1;
	for (int32_t i = 0; i < Items.size(); ++i)
	{
		if (Normalize_AssetPath(Items[i].strPath) == strCurrentPath)
		{
			iCurrentIIndex = i;
			break;
		}
	}

	// 2. 콤보가 닫혀 있을 때 보일 글자. 목록에 없으면 경로를 그대로 보여 줌
	string strPreview;
	if (-1 != iCurrentIIndex)
		strPreview = Items[iCurrentIIndex].strDisplayName;
	else
		strPreview = To_UTF8(strCurrentPath);

	// 3. 콤보 — 고른 항목은 기억만 해 두고 EndCombo 뒤에 반환
	const wchar_t* pPickedPath = {};
	// (라벨, 닫혀 있을 때 보일 글자). 열려 있을 때만 true
	if (ImGui::BeginCombo(pLabel, strPreview.c_str()))
	{
		for (int32_t i = 0; i < Items.size(); ++i)
		{
			const bool_t bSelected = (i == iCurrentIIndex);

			// 지금 쓰는 항목이 아닌데 클릭했다면 -> 새로 고른 것
			if (ImGui::Selectable(Items[i].strDisplayName.c_str(), bSelected) && !bSelected)
				pPickedPath = Items[i].strPath.c_str();

			// 콤보를 열었을 때 현재 항목으로 스크롤
			if (bSelected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}
	return pPickedPath;
}
```

- **현재 항목 찾기**: 객체 경로는 정규화돼 있으므로 목록 쪽도 정규화해서 비교한다. 대소문자 하나만 달라도 못 찾는다.
- **미리보기**: 목록에 없는 경로(나중에 맵 불러오기 등)도 빈칸이 아니라 경로로 보여 준다.
- **EndCombo 뒤 반환**: 루프 안에서 바로 메시를 바꾸면 `Items`/객체 상태가 콤보를 그리는 도중에 바뀐다. 고른 것만 기억했다가 콤보를 다 그린 뒤 돌려준다.
- 반환 포인터는 `g_Models` 안 문자열이라 이 프레임 동안 유효하다.

### 10-2. Panel_Inspector — Components

include에 `#include "StaticProp.h"`, Transform 블록 다음에:

```cpp
            if (auto pProp = dynamic_pointer_cast<CStaticProp>(pSelected))
            {
                if (ImGui::CollapsingHeader("Components", ImGuiTreeNodeFlags_DefaultOpen))
                {
                    if (auto pPath = Render_AssetCombo("Model", g_Models, pProp->Get_MeshPath()))
                    {
                        if (FAILED(pProp->Change_Mesh(pPath)))
                            MSG_BOX("Mesh Change Failed");
                    }
                }
            }
```

- **타입별 UI는 툴에서 캐스팅으로 분기**: StaticProp만 모델 콤보가 있다. 지형(11단계)은 이 블록에 안 들어온다.
- `Change_Mesh`가 실패해도 기존 메시를 유지한다 (6-2).

### 확인

- 콤보를 열면 `0_CharacterModel_Boss_Wu`, `Pfb_Tree_01_1`, `SM_Container_*`가 보이고 현재 항목이 하이라이트
- 고르면 화면의 모델이 바뀌고, 콤보 미리보기도 바뀐다

---

## 11단계. 혼합맵 지형 — CHill

**목표**: Hierarchy 빈 곳 우클릭 → `Add Terrain` → 높이맵 지형이 혼합맵(splat)으로 잔디/흙/아스팔트가 섞여 보인다. 지형은 하나만 만들 수 있다.

### 엔진/클라이언트 선행 조건

- 엔진: `CVIBuffer_Terrain::Create(device, context, L"raw 경로")`, `GetHeight(x, z)`, `GetPlane`, `Get_Vertices`, `Get_Indices`
- 엔진: `CTexture::Create(..., L"...Layer%d.png", 3)` (`%d`로 여러 장), `Set_TexturePS(인덱스, 슬롯)`
- 셰이더: `VS_TERRAIN`, `PS_TERRAIN` (t2~t4 레이어, t5 혼합맵)
- vcxproj에 `..\..\Client\Private\Hill.cpp` 추가

### 11-1. CHill (Client)

```cpp
// Hill.h
#pragma once
#include "Client_Defines.h"
#include "MapObject.h"

NS_BEGIN(Client)
class CHill : public CMapObject
{
public:
	typedef struct tagHillDesc : public MAPOBJECT_DESC
	{
		wstring_t strLayerPath = L"Duckov_Extract/Terrain/Terrain_GroundZero_Crop/Layer%d.png";
	}HILL_DESC;
private:
	CHill(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	~CHill() = default;

public:
	virtual HRESULT		Initialize_Prototype() override;
	virtual HRESULT		Initialize(void* pArg) override;
	virtual	void		Priority_Update(f32_t fDeltaTime) override;
	virtual	void		Update(f32_t fDeltaTime) override;
	virtual	void		Late_Update(f32_t fDeltaTime) override;
	virtual HRESULT		Render() override;
	virtual f32_t		GetHeight(f32_t x, f32_t z);
	virtual float4_t	GetPlane(f32_t x, f32_t z);
	virtual const vector<float3_t>& Get_Vertices() { return m_pBufferCom->Get_Vertices(); }
	virtual const vector<uint32_t>& Get_Indices() { return m_pBufferCom->Get_Indices(); }

public:
	virtual void Save_Extra(ofstream& Out) const override;
	static  void Read_Extra(ifstream& In, HILL_DESC& Desc);
	const wstring_t& Get_LayerPath() const { return m_strLayerPath; }

private:
	wstring_t m_strLayerPath;

private:
	shared_ptr<CTexture>			m_pBlendCom = { nullptr };
	shared_ptr<CTexture>			m_pLayerCom = { nullptr };
	shared_ptr<CVIBuffer_Terrain>	m_pBufferCom = { nullptr };
	shared_ptr<CVertexShader>		m_pVS = { nullptr };
	shared_ptr<CPixelShader>		m_pPS = { nullptr };
	shared_ptr<CConstantBuffer>		m_pCB = { nullptr };
	CB_PER_OBJECT_LIT				m_tCBData = {};

private:
	HRESULT			Ready_Components();
	HRESULT			Ready_ConstantBuffer();
	HRESULT			Update_ConstantBuffer(const matrix_t& matWorld);
	virtual			HRESULT Bind_Shader(shared_ptr<CVertexShader> pVS = nullptr, shared_ptr<CPixelShader> pPS = nullptr);
	virtual			HRESULT Bind_ShaderResources(const matrix_t& matWorld = XMMatrixIdentity());

public:
	static shared_ptr<CHill> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
	virtual shared_ptr<CPrototype> Clone(void* pArg) override;
};
NS_END
```

- **경로 3종**: `strMeshPath` = 높이맵 raw, `strTexturePath` = 혼합맵, `strLayerPath` = 레이어 3장(`%d`). 앞의 둘은 부모 DESC, 레이어만 자식 DESC.
- **GetHeight**: 13단계 SnapToTerrain이 쓴다. **Get_Vertices/Get_Indices**: 14단계 지형 피킹이 쓴다. 지금 함께 만들어 둔다 (엔진에 이미 있는 함수를 넘겨 주기만 함).
- `Save_Extra`/`Read_Extra`: 저장 기능용 자리 (비어 있음).

```cpp
// Hill.cpp
#include "Hill.h"
#include <fstream>

CHill::CHill(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    :CMapObject(pDevice, pContext)
{
}

HRESULT CHill::Initialize_Prototype()
{
    if (FAILED(__super::Initialize_Prototype()))
        return E_FAIL;

    D3D11_RASTERIZER_DESC rsDesc{};
    rsDesc.FillMode = D3D11_FILL_SOLID;
    rsDesc.CullMode = D3D11_CULL_BACK;
    rsDesc.FrontCounterClockwise = false;
    rsDesc.DepthClipEnable = true;

    m_pDevice->CreateRasterizerState(&rsDesc, m_pRS.GetAddressOf());
    return S_OK;
}

HRESULT CHill::Initialize(void* pArg)
{
    if (FAILED(__super::Initialize(pArg)))
        return E_FAIL;

    auto pDesc = static_cast<HILL_DESC*>(pArg);
    m_strLayerPath = pDesc->strLayerPath;

    if (FAILED(Ready_Components()))
        return E_FAIL;
    if (FAILED(Ready_ConstantBuffer()))
        return E_FAIL;
    return S_OK;
}

void CHill::Priority_Update(f32_t fDeltaTime) { __super::Priority_Update(fDeltaTime); }
void CHill::Update(f32_t fDeltaTime)          { __super::Update(fDeltaTime); }
void CHill::Late_Update(f32_t fDeltaTime)
{
    __super::Late_Update(fDeltaTime);
    CGameInstance::Get().Add_RenderGroup(RENDERID::NONALPHA, dynamic_pointer_cast<CGameObject>(shared_from_this()));
}
```

- **CULL_BACK**: 지형은 위에서만 보므로 뒷면을 버린다.
- **Initialize**: 부모가 공통 DESC(경로 2개, Transform)를 채운 뒤, 자식 DESC에서 레이어 경로를 꺼낸다. 그래서 `pArg`는 반드시 `HILL_DESC`여야 한다.

```cpp
HRESULT CHill::Render()
{
    m_pContext->RSSetState(m_pRS.Get());

    if (FAILED(Bind_Shader(m_pVS, m_pPS)))
        return E_FAIL;
    if (FAILED(Bind_ShaderResources(m_pTransformCom->Get_World())))
        return E_FAIL;
    if (FAILED(m_pBufferCom->Bind_Resources()))
        return E_FAIL;
    if (FAILED(m_pBufferCom->Render()))
        return E_FAIL;
    return S_OK;
}

f32_t CHill::GetHeight(f32_t x, f32_t z)
{
    // 월드 -> 로컬로 바꿔 버퍼에서 높이를 구한 뒤 다시 월드로
    matrix_t matWorld = m_pTransformCom->Get_World();
    matrix_t matInv = XMMatrixInverse(nullptr, matWorld);

    vector_t vLocal = XMVector3TransformCoord(XMVectorSet(x, 0.f, z, 1.f), matInv);
    f32_t fLocalY = m_pBufferCom->GetHeight(XMVectorGetX(vLocal), XMVectorGetZ(vLocal));

    vector_t vWorld = XMVector3TransformCoord(
        XMVectorSet(XMVectorGetX(vLocal), fLocalY, XMVectorGetZ(vLocal), 1.f), matWorld);
    return XMVectorGetY(vWorld);
}

float4_t CHill::GetPlane(f32_t x, f32_t z)
{
    return static_pointer_cast<CVIBuffer_Terrain>(__super::Find_Component(L"Com_Buffer"))->GetPlane(x, z);
}
```

- **GetHeight**: 버퍼는 로컬 좌표 기준 높이만 안다. 지형을 옮기거나 키워도 맞도록 역행렬로 로컬에 갔다가 다시 월드로 돌아온다.

```cpp
HRESULT CHill::Update_ConstantBuffer(const matrix_t& matWorld)
{
    XMMATRIX matNoTrans = matWorld;
    matNoTrans.r[3] = XMVectorSet(0.f, 0.f, 0.f, 1.f);
    XMMATRIX matWorldInvTranspos = XMMatrixTranspose(XMMatrixInverse(nullptr, matNoTrans));

    XMStoreFloat4x4(&m_tCBData.mat_World, (matWorld));
    XMStoreFloat4x4(&m_tCBData.mat_WorldInvTranspose, (matWorldInvTranspos));
    m_tCBData.tMaterial = m_tMaterial;
    return S_OK;
}

void CHill::Save_Extra(ofstream& Out) const
{
}

void CHill::Read_Extra(ifstream& In, HILL_DESC& Desc)
{
}

HRESULT CHill::Ready_Components()
{
    if (FAILED(__super::Add_Component(m_iLevelIndex, Normalize_AssetPath(m_strMeshPath),
        TEXT("Com_Buffer"), m_pBufferCom)))
        return E_FAIL;
    if (FAILED(__super::Add_Component(m_iLevelIndex, Normalize_AssetPath(m_strTexturePath),
        TEXT("Com_Blend"), m_pBlendCom)))
        return E_FAIL;
    if (FAILED(__super::Add_Component(m_iLevelIndex, Normalize_AssetPath(m_strLayerPath),
        TEXT("Com_Layer"), m_pLayerCom)))
        return E_FAIL;

    if (FAILED(__super::Add_Component(m_iLevelIndex, Proto::VS_TERRAIN, TEXT("Com_VS"), m_pVS)))
        return E_FAIL;
    if (FAILED(__super::Add_Component(m_iLevelIndex, Proto::PS_TERRAIN, TEXT("Com_PS"), m_pPS)))
        return E_FAIL;
    return S_OK;
}
```

- **경로 → 정규화 → 원형 태그**: StaticProp과 같은 규칙. 로더도 같은 경로를 정규화해서 등록해야 찾을 수 있다 (11-2).
- **Com_Buffer 슬롯**: 엔진의 절두체 검사(`Is_InFrustum`)가 이 이름으로 버퍼의 경계 상자를 찾는다.

```cpp
HRESULT CHill::Ready_ConstantBuffer()
{
    matrix_t matWorld = m_pTransformCom->Get_World();
    matrix_t matNoTrans = matWorld;
    matNoTrans.r[3] = XMVectorSet(0.f, 0.f, 0.f, 1.f);
    matrix_t matWorldInvTranspos = XMMatrixTranspose(XMMatrixInverse(nullptr, matNoTrans));

    XMStoreFloat4x4(&m_tCBData.mat_World, (matWorld));
    XMStoreFloat4x4(&m_tCBData.mat_WorldInvTranspose, (matWorldInvTranspos));
    m_tCBData.tMaterial = m_tMaterial;

    m_pCB = CConstantBuffer::Create(m_pDevice, m_pContext, &m_tCBData, sizeof(m_tCBData));
    if (nullptr == m_pCB)
        return E_FAIL;
    return S_OK;
}

HRESULT CHill::Bind_Shader(shared_ptr<CVertexShader> pVS, shared_ptr<CPixelShader> pPS)
{
    if (FAILED(m_pVS->Begin()))
        return E_FAIL;
    if (FAILED(m_pPS->Begin()))
        return E_FAIL;
    return S_OK;
}

HRESULT CHill::Bind_ShaderResources(const matrix_t& matWorld)
{
    // 텍스처 바인드
    if (FAILED(m_pLayerCom->Set_TexturePS(0, 2)))   // Layer0 잔디     -> t2
        return E_FAIL;
    if (FAILED(m_pLayerCom->Set_TexturePS(1, 3)))   // Layer1 흙       -> t3
        return E_FAIL;
    if (FAILED(m_pLayerCom->Set_TexturePS(2, 4)))   // Layer2 아스팔트 -> t4
        return E_FAIL;
    if (FAILED(m_pBlendCom->Set_TexturePS(0, 5)))   // 혼합맵          -> t5
        return E_FAIL;

    // 상수버퍼 바인드
    if (FAILED(Update_ConstantBuffer(matWorld)))
        return E_FAIL;
    if (FAILED(m_pCB->Bind_Vertex_ShaderResource(0, &m_tCBData)))
        return E_FAIL;
    if (FAILED(m_pCB->Bind_Pixel_ShaderResource(0, &m_tCBData)))
        return E_FAIL;
    return S_OK;
}

shared_ptr<CHill> CHill::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto pInstance = shared_ptr<CHill>(new CHill(pDevice, pContext));
    if (FAILED(pInstance->Initialize_Prototype()))
        pInstance.reset();
    return pInstance;
}

shared_ptr<CPrototype> CHill::Clone(void* pArg)
{
    auto pInstance = shared_ptr<CHill>(new CHill(*this));
    if (FAILED(pInstance->Initialize(pArg)))
        pInstance.reset();
    return pInstance;
}
```

- **텍스처 슬롯**: PS_TERRAIN이 t2~t4 레이어를 혼합맵(t5)의 RGB 비율로 섞는다. 레이어 텍스처 하나에 3장이 들어 있어 인덱스 0/1/2를 각 슬롯에 바인딩한다.
- **매 프레임 Update_ConstantBuffer**: Inspector로 지형을 옮기면 바로 반영된다.

### 11-2. 로더에 원형 추가

```cpp
// include
#include "Hill.h"

// 텍스처 구역
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::MAPTOOL), Normalize_AssetPath(TEXT("../../../Resource/Duckov_Extract/Terrain/Terrain_GroundZero_Crop/splat_0.png")),
        CTexture::Create(m_pDevice, m_pContext, TEXT("../../../Resource/Duckov_Extract/Terrain/Terrain_GroundZero_Crop/splat_0.png"), 1))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::MAPTOOL), Normalize_AssetPath(TEXT("../../../Resource/Duckov_Extract/Terrain/Terrain_GroundZero_Crop/Layer%d.png")),
        CTexture::Create(m_pDevice, m_pContext, TEXT("../../../Resource/Duckov_Extract/Terrain/Terrain_GroundZero_Crop/Layer%d.png"), 3))))
        return E_FAIL;

// 모델 구역
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::MAPTOOL), Normalize_AssetPath(TEXT("../../../Resource/Duckov_Extract/Terrain/Terrain_GroundZero_Crop/height_321x321_16bit.raw")),
        CVIBuffer_Terrain::Create(m_pDevice, m_pContext, L"../../../Resource/Duckov_Extract/Terrain/Terrain_GroundZero_Crop/height_321x321_16bit.raw"))))
        return E_FAIL;

// 셰이더 구역
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::MAPTOOL), Proto::VS_TERRAIN,
        CVertexShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Model_VertexShader.hlsl", VTXNORM::Elements, VTXNORM::iNumElements, "VS_TERRAIN"))))
        return E_FAIL;
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::MAPTOOL), Proto::PS_TERRAIN,
        CPixelShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Model_PixelShader.hlsl", "PS_TERRAIN"))))
        return E_FAIL;

// 객체원형 구역
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::MAPTOOL), Proto::Obj_Hill,
        CHill::Create(m_pDevice, m_pContext))))
        return E_FAIL;
```

- **태그를 전체 경로로 정규화**: `Normalize_AssetPath`가 `../../../resource/` 앞부분을 지우므로 결과는 `duckov_extract/terrain/.../splat_0.png`. 지형 DESC의 상대 경로(`Duckov_Extract/...`)를 정규화한 것과 같아진다.
- **지형 버퍼는 모델 구역**에 넣지만 `CModel`이 아니라 `CVIBuffer_Terrain`이라 `Get_ModelTags`에 잡히지 않는다 → Inspector 모델 콤보에 안 나온다.

### 11-3. EditorUI_Defines.h — 메뉴 항목 추가

```cpp
static constexpr PLACEABLE s_Placeables[] = {
	{ "Add Static_Prop", Proto::Obj_StaticProp },
	{ "Add Terrain", Proto::Obj_Hill },
};
```

### 11-4. Hierarchy — 지형 생성

헤더에 `void Create_Terrain();` 추가. cpp include에 `#include "Hill.h"`.

```cpp
void CPanel_Hierarchy::Create_Object(const wstring_t& pPrototypeTag)
{
    if (pPrototypeTag == Proto::Obj_Hill)
        Create_Terrain();
    else
        Create_StaticProp(pPrototypeTag);
}

void CPanel_Hierarchy::Create_Terrain()
{
    const wstring_t strTag = L"Terrain";

    // 지형은 하나만
    if (nullptr != CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::MAPTOOL), TEXT("Layer_Map"), strTag))
    {
        MSG_BOX("Terrain already exists");
        return;
    }

    CHill::HILL_DESC Desc{};
    Desc.iLevelIndex = ETOUI(LEVEL::MAPTOOL);
    Desc.strMeshPath = L"Duckov_Extract/Terrain/Terrain_GroundZero_Crop/height_321x321_16bit.raw";
    Desc.strTexturePath = L"Duckov_Extract/Terrain/Terrain_GroundZero_Crop/splat_0.png";
    Desc.strLayerPath = L"Duckov_Extract/Terrain/Terrain_GroundZero_Crop/Layer%d.png";
    Desc.bEditorMode = true;

    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::MAPTOOL), Proto::Obj_Hill,
        ETOUI(LEVEL::MAPTOOL), TEXT("Layer_Map"), strTag, &Desc)))
    {
        MSG_BOX("Create Failed");
        return;
    }
    m_Context.Select(strTag, CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::MAPTOOL), TEXT("Layer_Map"), strTag));
}
```

- **Create_Object 분기**: `wstring == const wchar_t*` 비교라 내용으로 비교된다. 지형만 DESC 모양이 달라서 따로 만든다.
- **이름 고정 `Terrain`**: 하나만 있게 하려는 것이고, 13·14단계가 `Find_GameObject(..., L"Terrain")`으로 지형을 찾는다.
- **CHill도 CMapObject**: 그래서 선택, Inspector Transform, 삭제가 코드 수정 없이 그대로 동작한다. 모델 콤보는 StaticProp이 아니라서 안 보인다.

### 확인

- `Add Terrain` → 큰 지형이 보이고 색이 섞여 있다 (카메라를 위로 올려서 확인)
- 두 번째 `Add Terrain` → "Terrain already exists"
- 지형을 선택해 Position/Scale을 바꾸면 바로 반영

---

## 12단계. 뷰포트 피킹으로 선택

**목표**: 패널이 없는 게임 화면을 좌클릭하면, 마우스 아래 가장 가까운 StaticProp이 선택된다 (지형 제외).

> 피킹, 지형 우클릭(14), 기즈모(15)는 특정 창이 아니라 **뷰포트(창 밖 영역)** 의 일이라서 `CEditorUI`가 맡는다. 패널은 각자 창 안만 처리한다.

### 엔진 선행 조건

- `CCamera::Compute_PickingRay(POINT, out 원점, out 방향)`: **뷰포트(1600×900) 픽셀 좌표**를 받아 월드 레이를 만든다.
- `CGameInstance::Get_MainCamera()`
- 1단계에서 창 크기를 고정해 둔 상태 (클라이언트 영역 = 엔진 뷰포트)
- `CModel::GetBoundinBox()`: 모델 로컬 AABB
- `CGameObject::Get_Transform()`, `CTransform::Get_World()`

### 12-1. EditorUI.h

```cpp
private:
	void		Update_Viewport();
	void		Pick_Object(const vector_t& vRayOrigin, const vector_t& vRayDir);
```

### 12-2. CEditorUI::Update — 패널 다음에 뷰포트 처리

include에 `#include "Camera.h"`, `#include "Hill.h"` 추가.

```cpp
void CEditorUI::Update(const f32_t& fDeltaTime)
{
    const ImGuiIO& io = ImGui::GetIO();
    m_Context.bViewportHovered = !io.WantCaptureMouse;
    m_Context.bViewportFocused = !io.WantCaptureKeyboard;

    Render_MenuBar();
    Calc_Layout();

    m_pHierarchy->Render(m_tHierarchy);
    m_pInspector->Render(m_tInspector);

    Update_Viewport();
}
```

- 패널 다음에 두는 이유: Hierarchy에서 같은 프레임에 삭제된 객체를 피킹 대상으로 고르지 않게 하려고. 삭제된 객체는 Dead 표시가 되어 있어서 건너뛴다.

### 12-3. Update_Viewport — 마우스 좌표 → 레이

```cpp
void CEditorUI::Update_Viewport()
{
    auto pCamera = CGameInstance::Get().Get_MainCamera();
    if (nullptr == pCamera)
        return;

    // 창 크기가 고정(1단계)이라 마우스 좌표 = 뷰포트 좌표
    const ImGuiIO&  io = ImGui::GetIO();
    POINT ptPick{
        static_cast<LONG>(io.MousePos.x),
        static_cast<LONG>(io.MousePos.y) };

    vector_t vRayOrigin, vRayDir;
    pCamera->Compute_PickingRay(ptPick, vRayOrigin, vRayDir);

    // 좌클릭: 객체 선택
    if (m_Context.bViewportHovered && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
        Pick_Object(vRayOrigin, vRayDir);
}
```

- **좌표 변환이 없다**: 게임 화면이 창 전체에 깔려 있고, 1단계에서 창 크기 변경을 막아 클라이언트 영역(`io.DisplaySize`)과 엔진 뷰포트(`Get_ViewportSize()`)가 둘 다 1600×900으로 고정이다. 그래서 마우스 좌표가 곧 뷰포트 픽셀 좌표다.
- 나중에 창 크기 변경을 허용한다면(스왑체인 리사이즈 없이) `io.MousePos.x * vpSize.x / io.DisplaySize.x`처럼 비율을 곱해야 한다.
- **레이는 매 프레임 계산**: 14단계 우클릭도 같은 레이를 쓴다.
- **bViewportHovered 검사**: 패널 위를 클릭했을 때 그 뒤 객체가 선택되면 안 된다.
- **IsMouseClicked**: 누른 그 프레임 한 번만 true.

### 12-4. Pick_Object — OBB 검사

```cpp
void CEditorUI::Pick_Object(const vector_t& vRayOrigin, const vector_t& vRayDir)
{
    auto pObjects = CGameInstance::Get().Get_GameObjects(ETOUI(LEVEL::MAPTOOL), L"Layer_Map");
    if (nullptr == pObjects)
        return;

    f32_t                   fMinDist = D3D11_FLOAT32_MAX;
    wstring_t               strPickedTag = {};
    shared_ptr<CGameObject> pPicked = { nullptr };
    for (auto& [strTag, pObject] : *pObjects)
    {
        if (nullptr == pObject || pObject->Is_Dead())
            continue;
        if (nullptr != dynamic_pointer_cast<CHill>(pObject))          // 지형 제외 (박스가 맵 전체)
            continue;
        auto pModel = static_pointer_cast<CModel>(pObject->Find_Component(L"Com_Model"));
        if (nullptr == pModel)
            continue;

        BoundingOrientedBox tWorldBox;
        BoundingOrientedBox::CreateFromBoundingBox(tWorldBox, pModel->GetBoundinBox());
        tWorldBox.Transform(tWorldBox, pObject->Get_Transform()->Get_World());

        f32_t fOutDist = {};
        if (tWorldBox.Intersects(vRayOrigin, vRayDir, fOutDist) && fMinDist > fOutDist)
        {
            fMinDist = fOutDist;
            strPickedTag = strTag;
            pPicked = pObject;
        }
    }
    if (nullptr != pPicked)
        m_Context.Select(strPickedTag, pPicked);
}
```

- **창 밖이라 Begin/End가 없다**: 중간에 `return`해도 ImGui 짝을 신경 쓸 필요가 없다.
- **지형 제외**: 지형의 경계 상자는 맵 전체라 항상 가장 먼저 맞아서 다른 객체를 못 고르게 된다.
- **AABB → OBB**: 모델 로컬 AABB를 OBB로 만든 뒤 월드 행렬로 변환한다. 회전한 객체도 박스가 같이 돈다. (AABB를 그대로 Transform하면 회전할 때 박스가 커진다)
- **가장 가까운 것**: 겹쳐 있으면 레이 거리가 가장 짧은 객체를 고른다.
- 빈 곳을 클릭하면 선택이 그대로 유지된다 (해제하지 않음).

### 확인

- 모델 여러 개를 Inspector로 떨어뜨려 놓고 화면에서 클릭 → Hierarchy 하이라이트와 Inspector가 바뀐다
- 지형 위만 클릭하면 선택이 바뀌지 않는다
- 패널 위를 클릭하면 그 뒤에 있는 객체가 선택되지 않는다

---

## 13단계. SnapToTerrain

**목표**: Inspector의 `SnapToTerrain` 버튼을 누르면 선택한 객체의 Y가 그 자리 지형 높이로 맞춰진다.

### 13-1. Panel_Inspector

include에 `#include "Hill.h"`. 이름 아래 `ImGui::Separator();` 다음, Transform 헤더 위에:

```cpp
            if (ImGui::Button("SnapToTerrain"))
            {
                if (auto pTerrain = dynamic_pointer_cast<CHill>(CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::MAPTOOL), L"Layer_Map", L"Terrain")))
                {
                    f32_t fY = pTerrain->GetHeight(pSelected->Get_Position().x, pSelected->Get_Position().z);
                    pSelected->Set_Position(float3_t(pSelected->Get_Position().x, fY, pSelected->Get_Position().z));
                }
            }
```

- **Button**: 누른 프레임에만 true.
- **지형 찾기**: 이름 `Terrain`으로 찾고 `CHill`로 캐스팅. 지형이 없으면 아무 일도 안 한다.
- **X/Z는 그대로, Y만**: `GetHeight`가 월드 X/Z에서의 지형 월드 높이를 준다 (11-1). 모델 원점(발밑)이 지면에 닿는다.
- 지형 자신을 선택하고 눌러도 동작은 하지만 의미는 없다.

### 확인

- 지형 + Prop 생성 → Prop의 X/Z를 옮긴 뒤 `SnapToTerrain` → 지면에 붙는다
- 지형이 없을 때 눌러도 크래시 없음

---

## 14단계. 지형 피킹으로 객체 생성

**목표**: 게임 화면의 지형 위를 **우클릭(드래그 없이)** 하면 메뉴가 뜨고, `Add Static_Prop`을 고르면 그 지점에 Prop이 생긴다. 우클릭 드래그는 지금처럼 카메라 회전이다.

### 엔진 선행 조건

- `TriangleTests::Intersects(원점, 방향, p0, p1, p2, out 거리)` (DirectXCollision)
- 11단계 `CHill::Get_Vertices / Get_Indices` (로컬 정점 위치 / 인덱스)

### 14-1. EditorUI.h

```cpp
private:
	float3_t	m_vPickPos = {};		// 우클릭한 지형 위 지점
private:
	bool_t		Pick_Terrain(const vector_t& vRayOrigin, const vector_t& vRayDir);
	void		Create_StaticProp(const float3_t& vPosition);
```

- `m_vPickPos`: 우클릭한 프레임에 계산한 지점. 메뉴는 다음 프레임 이후에 고르므로 멤버로 기억해 둔다.

### 14-2. Update_Viewport — 우클릭 판정 + 메뉴

12단계 `Update_Viewport`의 좌클릭 처리 다음에 추가 (include에 `#include "StaticProp.h"`):

```cpp
    // 우클릭(드래그 없이): 지형 위 지점을 구하고 메뉴 열기
    if (m_Context.bViewportHovered && ImGui::IsMouseReleased(ImGuiMouseButton_Right))
    {
        ImVec2 vDrag = ImGui::GetMouseDragDelta(ImGuiMouseButton_Right);
        if (vDrag.x * vDrag.x + vDrag.y * vDrag.y < 25.f       // 5픽셀 미만 이동 = 클릭으로 판단
            && Pick_Terrain(vRayOrigin, vRayDir))
            ImGui::OpenPopup("ViewportMenu");
    }

    if (ImGui::BeginPopup("ViewportMenu"))
    {
        if (ImGui::MenuItem(s_Placeables[0].pName))         // "Add Static_Prop"
            Create_StaticProp(m_vPickPos);
        ImGui::EndPopup();
    }
```

- **IsMouseReleased + 드래그 거리**: 우클릭은 카메라 회전에도 쓴다. 뗀 순간 누른 위치에서 5픽셀 안쪽이면 "클릭", 더 움직였으면 "회전"으로 본다. `GetMouseDragDelta`는 뗀 프레임에도 누른 동안의 이동량을 준다. 제곱끼리 비교해서 sqrt를 피한다.
- **지형에 맞았을 때만 메뉴**: 지형이 없거나 하늘을 찍었으면 생성할 지점이 없으므로 메뉴를 열지 않는다.
- **OpenPopup / BeginPopup 분리**: `OpenPopup`은 "열어라" 표시만 하고, 그리는 건 매 프레임 `BeginPopup`이 한다. 메뉴는 다음 프레임 이후에도 열려 있어야 하므로 `BeginPopup`은 조건 밖에 둔다.
- **창 밖에서 팝업**: 두 함수 모두 `Begin` 밖(같은 ID 스택)에서 불리므로 ID `"ViewportMenu"`가 맞는다. 팝업은 연 순간의 마우스 위치에 뜬다.
- **팝업이 열려 있는 동안**: `WantCaptureMouse`가 true라 `bViewportHovered`가 false다. 메뉴를 고르는 클릭이 피킹으로 새지 않는다.
- **s_Placeables[0]만**: 지형은 하나뿐이고 위치가 정해져 있어서 지점 생성은 StaticProp만 한다.

### 14-3. Pick_Terrain — 지형 삼각형 검사

```cpp
bool_t CEditorUI::Pick_Terrain(const vector_t& vRayOrigin, const vector_t& vRayDir)
{
    auto pTerrain = dynamic_pointer_cast<CHill>(
        CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::MAPTOOL), L"Layer_Map", L"Terrain"));
    if (nullptr == pTerrain)
        return false;

    const auto& vVertices = pTerrain->Get_Vertices();
    const auto& vIndices  = pTerrain->Get_Indices();

    f32_t  fMinDist = D3D11_FLOAT32_MAX;
    bool_t bHit = false;
    for (size_t i = 0; i + 2 < vIndices.size(); i += 3)
    {
        vector_t p0 = XMLoadFloat3(&vVertices[vIndices[i]]);
        vector_t p1 = XMLoadFloat3(&vVertices[vIndices[i + 1]]);
        vector_t p2 = XMLoadFloat3(&vVertices[vIndices[i + 2]]);

        f32_t fDist = {};
        if (TriangleTests::Intersects(vRayOrigin, vRayDir, p0, p1, p2, fDist) && fDist < fMinDist)
        {
            fMinDist = fDist;
            bHit = true;
        }
    }
    if (bHit)
        XMStoreFloat3(&m_vPickPos, vRayOrigin + vRayDir * fMinDist);
    return bHit;
}
```

- **삼각형 전체 검사**: 인덱스 3개씩이 삼각형 하나다. 레이와 맞는 삼각형 중 가장 가까운 거리를 고른다. 321×321 지형이면 삼각형 약 20만 개라 무겁지만 우클릭 순간에만 돈다.
- **정점은 로컬 좌표**: 지형 Transform을 기본값(원점, 회전 없음, 1)으로 두면 월드와 같다. 지형을 옮겼다면 레이를 지형 로컬로 바꾸거나 정점에 월드 행렬을 곱해야 맞는다 (16. 남은 작업).
- **맞은 지점** = 원점 + 방향 × 거리.

### 14-4. Create_StaticProp — 지점에 생성

```cpp
void CEditorUI::Create_StaticProp(const float3_t& vPosition)
{
    CStaticProp::STATICPROP_DESC Desc{};
    Desc.iLevelIndex = ETOUI(LEVEL::MAPTOOL);
    Desc.strMeshPath = g_Models[0].strPath;
    Desc.bEditorMode = true;
    Desc.vPosition   = vPosition;

    wstring_t strTag;
    do {
        if (m_Context.m_iNextID < 10)
            strTag = L"Prop_0" + to_wstring(m_Context.m_iNextID++);
        else
            strTag = L"Prop_" + to_wstring(m_Context.m_iNextID++);
    } while (nullptr != CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::MAPTOOL), TEXT("Layer_Map"), strTag));

    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::MAPTOOL), Proto::Obj_StaticProp,
        ETOUI(LEVEL::MAPTOOL), TEXT("Layer_Map"), strTag, &Desc)))
    {
        MSG_BOX("Create Failed");
        return;
    }

    // 만든 객체를 바로 선택
    m_Context.Select(strTag, CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::MAPTOOL), TEXT("Layer_Map"), strTag));
}
```

- Hierarchy의 `Create_StaticProp`(6단계)과 같고, `vPosition`에 지형 위 지점을 넣는 것만 다르다.
- 이름 번호(`m_iNextID`)를 Context로 공유하므로 두 곳에서 만들어도 이름이 안 겹친다.

### 확인

- 지형 생성 → 화면의 지형 위를 우클릭(움직이지 않고) → `Add Static_Prop` → 그 지점에 Prop
- 우클릭 드래그는 카메라 회전만 하고 메뉴가 안 뜬다
- 지형이 없거나 하늘을 우클릭하면 메뉴가 안 뜬다
- 패널 위 우클릭은 Hierarchy 메뉴(빈 곳)만 뜬다

---

## 15단계. ImGuizmo 기즈모

**목표**: 메뉴바 `Gizmo` 메뉴에서 `Move / Rotate / Scale`을 고를 수 있고, 선택한 StaticProp 위에 기즈모가 나와 드래그로 변환할 수 있다. 기즈모를 잡고 있을 때는 피킹이 일어나지 않는다.

### 15-1. ImGuizmo 소스 추가

- `MapTool/ImGui/`에 `ImGuizmo.cpp`, `ImGuizmo.h` 추가, vcxproj에 포함 (ImGui cpp와 같은 설정: pch 사용 안 함, `/utf-8`)
- ImGuizmo는 ImGui 위에 그리는 라이브러리라 ImGui 프레임 안에서 `BeginFrame` → `Manipulate` 순서로 부른다.

### 15-2. CLevel_MapTool — ImGuizmo 프레임

```cpp
#include "imgui.h"
#include "ImGuizmo.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
...
HRESULT CLevel_MapTool::Begin_ImGui()
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    ImGuizmo::BeginFrame();
    return S_OK;
}
```

- `ImGui::NewFrame` 뒤에 불러야 한다.
- `BeginFrame`은 화면 전체 크기의 **투명한 창** `"gizmo"`를 하나 만들고 기즈모를 그 창의 드로우 리스트에 그리게 정한다. 이 창은 `NoInputs`(마우스를 가로채지 않음), `NoBringToFrontOnFocus`(항상 맨 뒤) 설정이라 패널 아래, 게임 화면 위에 기즈모가 그려진다. 그래서 `SetDrawlist`를 따로 부를 필요가 없다.

### 15-3. EditorUI.h

```cpp
#pragma once
#include "EditorUI_Defines.h"
#include "ImGuizmo.h"
...
private:
	ImGuizmo::OPERATION		m_eGizmoOp = ImGuizmo::TRANSLATE;
private:
	void		Manipulate_Gizmo();
```

- `ImGuizmo.h`는 imgui.h가 먼저 있어야 한다. `EditorUI.h`를 포함하는 cpp(`EditorUI.cpp`, `Level_MapTool.cpp`)는 둘 다 imgui.h를 먼저 포함하고 있다.

### 15-4. 메뉴바 — 모드 선택

EditorUI.cpp 위쪽:

```cpp
namespace
{
    struct GIZMO_OP_ITEM
    {
        const char* pLabel;         // 글자
        ImGuizmo::OPERATION eOp;    // 바뀔 모드
    };

    static constexpr GIZMO_OP_ITEM g_GizmoOps[] =
    {
        { "Move",   ImGuizmo::TRANSLATE },
        { "Rotate", ImGuizmo::ROTATE    },
        { "Scale",  ImGuizmo::SCALE     },
    };
}
```

- 이름 없는 namespace: 이 cpp에서만 쓰는 표. 메뉴 글자와 모드를 짝으로 묶어 반복문 하나로 그린다.

`Render_MenuBar`의 `File` 메뉴 다음에:

```cpp
    if (ImGui::BeginMenu("Gizmo"))
    {
        for (auto& Item : g_GizmoOps)
        {
            // 세 번째 인자(선택됨) = 체크 표시. 클릭한 프레임에 true
            if (ImGui::MenuItem(Item.pLabel, nullptr, m_eGizmoOp == Item.eOp))
                m_eGizmoOp = Item.eOp;
        }
        ImGui::EndMenu();
    }
```

- 화면에 버튼을 띄울 창이 없으므로 메뉴바에 둔다. 현재 모드에 체크 표시가 붙는다.

### 15-5. Manipulate_Gizmo

```cpp
void CEditorUI::Manipulate_Gizmo()
{
    auto pObject = m_Context.pSelected.lock();
    if (nullptr == pObject || pObject->Is_Dead() || dynamic_pointer_cast<CHill>(pObject))
        return;

    // 카메라 -> 원근투영, 기즈모가 쓸 뷰포트 = 창 전체
    const ImGuiIO& io = ImGui::GetIO();
    ImGuizmo::SetOrthographic(false);
    ImGuizmo::SetRect(0.f, 0.f, io.DisplaySize.x, io.DisplaySize.y);

    float4x4_t ViewMatrix, ProjMatrix, WorldMatrix;
    XMStoreFloat4x4(&ViewMatrix, CGameInstance::Get().Get_Perspective_Transform(D3DTS::VIEW));
    XMStoreFloat4x4(&ProjMatrix, CGameInstance::Get().Get_Perspective_Transform(D3DTS::PROJ));
    WorldMatrix = *pObject->Get_Transform()->Get_WorldMatrixPtr();

    if (ImGuizmo::Manipulate(&ViewMatrix._11, &ProjMatrix._11,
        m_eGizmoOp, ImGuizmo::WORLD,
        &WorldMatrix._11))
    {
        vector_t vS, vQ, vT;
        if (XMMatrixDecompose(&vS, &vQ, &vT, XMLoadFloat4x4(&WorldMatrix)))
        {
            float3_t vPos, vScale;
            float4_t vQuat;
            XMStoreFloat3(&vPos, vT);
            XMStoreFloat3(&vScale, vS);
            XMStoreFloat4(&vQuat, vQ);
            pObject->Set_Transform(vPos, vQuat, vScale);
        }
    }
}
```

- **Is_Dead 검사**: Inspector를 접어 두면 `Validate_Selection`(9단계)이 불리지 않는다. 그래서 여기서 직접 걸러 낸다.
- **지형 제외**: 지형은 크기가 커서 기즈모가 화면을 덮고, 실수로 옮기기 쉽다. 지형은 Inspector로만.
- **SetRect = 창 전체**: 게임 화면이 창 전체에 깔려 있으므로 그대로 넣는다. 화면 비율과 투영 비율이 같아서 기즈모가 모델 위치에 정확히 붙는다.
- **행렬 형식**: ImGuizmo는 `float[16]` 행 우선을 받는다. DirectXMath `XMFLOAT4X4`도 같은 배치라 `._11` 주소를 그대로 넘긴다.
- **Manipulate 반환**: 이번 프레임에 드래그로 행렬이 바뀌었으면 true. 바뀐 `WorldMatrix`를 S/R/T로 분해해서 `Set_Transform`으로 넣는다. Transform에 직접 쓰지 않는 이유는 `CMapObject`의 위치/쿼터니언/크기 원본 값도 같이 바꿔야 Inspector와 맞기 때문이다 (6-1).
- **패널 뒤에 그려진다**: 선택한 객체가 펼친 패널 뒤에 있으면 기즈모도 가려진다. 패널을 접거나 카메라를 옮기면 된다.

### 15-6. Update_Viewport — 기즈모 먼저, 피킹 조건 추가

```cpp
void CEditorUI::Update_Viewport()
{
    auto pCamera = CGameInstance::Get().Get_MainCamera();
    if (nullptr == pCamera)
        return;

    // 기즈모를 먼저 처리해야 이번 프레임 IsOver / IsUsing 값이 맞다
    Manipulate_Gizmo();

    ...(12-3 레이 계산 그대로)...

    // 좌클릭: 기즈모 위가 아닐 때만 객체 선택
    if (m_Context.bViewportHovered && ImGui::IsMouseClicked(ImGuiMouseButton_Left)
        && !ImGuizmo::IsOver() && !ImGuizmo::IsUsing())
        Pick_Object(vRayOrigin, vRayDir);

    ...(14-2 우클릭 / 메뉴 그대로)...
}
```

- **기즈모 먼저**: `IsOver`(축 위에 마우스) / `IsUsing`(드래그 중)은 `Manipulate`가 부를 때 갱신된다. 피킹보다 뒤에 부르면 지난 프레임 값으로 판단하게 된다.
- **피킹 조건**: 기즈모 축을 잡으려고 클릭했는데 그 뒤에 있는 다른 모델이 선택되면 기즈모가 그 모델로 옮겨 간다. 그래서 기즈모 위에서는 피킹하지 않는다.
- 기즈모를 끌 때 `WantCaptureMouse`는 false다 (`"gizmo"` 창이 `NoInputs`). 카메라는 우클릭/WASD만 쓰므로 부딪히지 않는다.

### 확인

- Prop 선택 → 기즈모가 보이고, 축을 끌면 이동. `Gizmo` 메뉴로 회전/크기 모드 전환
- 기즈모로 바꾼 값이 Inspector 숫자에도 반영된다
- 기즈모 축을 클릭해도 뒤에 있는 다른 객체로 선택이 넘어가지 않는다
- 지형을 선택하면 기즈모가 안 나온다
- 기즈모가 패널 뒤로 가려진다 (패널이 위)

---

## 16. 현재 상태와 남은 작업

### 완료

| 기능 | 단계 |
|---|---|
| 로딩 레벨 → 에디터 레벨 | 1 |
| ImGui, 메뉴바, 고정 3분할 레이아웃 | 2, 3 |
| 접기 가능한 패널 2개 + 백버퍼 게임 화면, 뷰포트 입력 판정, 카메라 조작 제한 | 3, 4, 5 |
| FBX StaticProp 생성 / 목록 / 선택 / 삭제 | 6~8 |
| Inspector Transform, 모델 교체 | 9, 10 |
| 혼합맵 지형 (하나) | 11 |
| 뷰포트 피킹 선택, SnapToTerrain, 지형 위치에 생성 | 12~14 |
| ImGuizmo 이동/회전/크기 | 15 |

### 남은 작업

- **저장 / 불러오기**: File 메뉴가 비활성 상태. `Layer_Map`을 돌며 원형 태그 + `MAPOBJECT_DESC`(+ `Save_Extra`)를 쓰고, 읽을 때 같은 DESC로 `Add_GameObject`. `CHill::Save_Extra / Read_Extra`가 빈 함수로 준비돼 있다.
- **지형 피킹을 Transform에 맞추기**: 14단계는 지형 정점을 로컬 그대로 검사한다. 지형을 옮기거나 키우면 어긋난다 → 레이를 지형 월드 역행렬로 로컬에 보내 검사하고, 맞은 지점을 다시 월드로.
- **지형 피킹 최적화**: 삼각형 전체 검사 대신 `CVIBuffer_Terrain::GetHeight`를 이용한 레이 마칭이나 격자 범위 검사.
- **중복 코드 정리**: `CPanel_Hierarchy::Create_StaticProp`과 `CEditorUI::Create_StaticProp`이 이름 생성·Add·선택을 똑같이 한다 → Context나 공용 함수로 합치기.
- **g_Models 재진입**: `inline` 전역이라 맵툴 레벨을 다시 만들면 목록이 두 번 쌓인다. 지금은 레벨이 한 번뿐이라 문제없음. 필요하면 `Initialize` 시작에서 `clear()`.
- **Loader 실패 경로**: 실패 시 `LeaveCriticalSection`/`CoUninitialize`가 불리지 않는다.
- **모델 생성 기본값**: 지금은 항상 `g_Models[0]`. 콤보에서 고른 "현재 브러시 모델"로 만들기.

---

## 부록 A. 사용한 ImGui / ImGuizmo 함수

| 함수 | 쓰는 곳 | 설명 |
|---|---|---|
| `CreateContext / DestroyContext` | Level_MapTool | 컨텍스트 생성/삭제 |
| `GetIO()` | 여러 곳 | 설정, `DisplaySize`, `MousePos` |
| `io.WantCaptureMouse / WantCaptureKeyboard` | EditorUI | 이번 프레임 마우스/키보드를 ImGui가 쓰는지 → 뷰포트 입력 판정 |
| `StyleColorsDark()` | Ready_ImGui | 기본 다크 테마 |
| `ImGui_ImplWin32_Init / DX11_Init / *_NewFrame / *_Shutdown` | Level_MapTool | 백엔드 |
| `ImGui_ImplWin32_WndProcHandler` | WndProc | 입력 전달 |
| `ImGui_ImplWin32_EnableDpiAwareness` | wWinMain | DPI 인식 |
| `NewFrame / Render / GetDrawData` | Level_MapTool | 프레임 시작/끝 |
| `BeginMainMenuBar / EndMainMenuBar` | EditorUI | 상단 메뉴바 (true일 때만 End) |
| `BeginMenu / EndMenu / MenuItem` | EditorUI, 팝업 | 메뉴, 항목. 세 번째 인자(선택됨)로 체크 표시 |
| `GetWindowHeight` | 메뉴바 | 메뉴바 높이 |
| `SetNextWindowPos / SetNextWindowSize` | Set_NextPanelRect | 다음 창 위치/크기 |
| `Begin / End` | 패널 | 창 (End는 항상). 접혀 있으면 Begin이 false |
| `IsWindowFocused` | Hierarchy | 지금 창 포커스 |
| `Text / TextDisabled / TextUnformatted / Separator` | 패널, 메뉴바 | 글자, 구분선 |
| `Selectable` | Hierarchy, 콤보 | 한 줄 선택 항목 |
| `BeginPopupContextWindow` | Hierarchy | 창 빈 곳 우클릭 메뉴 (`NoOpenOverItems`) |
| `BeginPopupContextItem` | Hierarchy | 바로 앞 항목 우클릭 메뉴 |
| `OpenPopup / BeginPopup / EndPopup` | EditorUI | 조건부로 여는 팝업 (지형 우클릭) |
| `IsKeyPressed(ImGuiKey_Delete)` | Hierarchy | 키 입력 |
| `IsMouseClicked / IsMouseReleased / GetMouseDragDelta` | EditorUI | 피킹, 우클릭/드래그 구분 |
| `CollapsingHeader` | Inspector | 접는 제목 (`DefaultOpen`) |
| `DragFloat3` | Inspector | 3성분 드래그 입력 |
| `Button` | Inspector | 버튼 (SnapToTerrain) |
| `BeginCombo / EndCombo / SetItemDefaultFocus` | Render_AssetCombo | 콤보 |
| `ImGuizmo::BeginFrame` | Begin_ImGui | 기즈모 프레임 시작 (전체 화면 투명 창 + 드로우 리스트 준비) |
| `ImGuizmo::SetOrthographic / SetRect` | EditorUI | 투영 종류, 뷰포트 영역(창 전체) |
| `ImGuizmo::Manipulate` | EditorUI | 기즈모 그리기 + 드래그로 행렬 수정 |
| `ImGuizmo::IsOver / IsUsing` | EditorUI 피킹 | 기즈모 위/사용 중 |

---

## 부록 B. 단계와 커밋 대응

커밋 하나에 여러 단계가 섞여 있어서 대략적인 대응이다.

> 커밋 당시는 **Scene 패널(ImGui::Image로 씬 텍스처 표시)** 방식이었다. 이 문서는 Scene 패널을 없애고 **패널 2개 + 백버퍼 게임 화면** 구조로 바꿨다. 그래서 3·4·5·12·14·15단계 코드는 커밋과 다르다.

| 커밋 | 내용 | 이 문서 단계 |
|---|---|---|
| `347d306a4` ImGui 추가중, `a553b15dc` ImGui 수정중, `a030c72b4` 맵툴 수정 | ImGui 연결 | 1, 2 |
| `461e06fd7` ~ `0545bc72d` 파이프라인 카메라 적용, `7bdfd68df` 맵툴 카메라 게임오브젝트로 변경 | 카메라 | 5 |
| `08436eeff` 맵툴 구현중, `b4d46a84e` 하이어라키창 수정중, `41a779582` 하이어라키 + 인스펙터창 구현 완료 | 패널, 생성/선택/삭제/Inspector | 3, 4, 6~10 |
| `f42d173b4` 맵툴에 지형 가져오기 | CHill | 11 |
| `769d2cf95` 피킹 + 기즈모 추가, `d34ebadd9` 기즈모 적용완료 | 피킹, 기즈모 | 12, 15 |
| `2c3c22477` 모델로드 / 맵툴 피킹 / Snap기능 | FBX StaticProp, 모델 콤보, OBB 피킹, Snap | 6, 10, 12, 13 |
| `ad9bfa8e2` 머티리얼 클래스 + 지형 피킹으로 객체 생성 | `m_tMaterial`, 지형 우클릭 생성 | 6, 14 |

---

## 부록 C. 자주 겪는 문제

| 증상 | 원인 / 해결 | 단계 |
|---|---|---|
| Engine 헤더를 고쳤는데 MapTool에서 안 보임 | **Engine 먼저 빌드** (EngineSDK/Inc로 복사) → MapTool 빌드 | 전체 |
| 실행 시 Engine.dll / assimp dll 없음 | `MapTool/Bin/`에 복사됐는지 | 1 |
| 셰이더 로드 실패 | 빌드 후 xcopy로 `MapTool/Bin/Shader/`에 들어갔는지, 작업 디렉터리가 `Bin`인지 | 1 |
| MapTool 셰이더를 고쳤는데 원래대로 돌아감 | 빌드 때 Client 셰이더로 덮어씀 → Client 쪽을 고친다 | 1 |
| LNK2005 `ThreadMain` | Client `Loader.cpp`와 이름 충돌 → `ThreadMain_MapTool` | 1 |
| `CLoader` / `CLevel_Loading` 모호한 기호 | `using namespace Client; using namespace MapTool;` → 맵툴 쪽 이름에 `_MapTool` | 1 |
| 스페이스를 눌러도 안 넘어감 | 로딩 실패로 `m_isFinished`가 안 켜짐 → 창 제목의 마지막 문구로 구역 확인. 또는 창 포커스가 없음 | 1 |
| 넘어가는 순간 `Forgot to call ImGui::NewFrame()?` | 바뀌는 프레임엔 Render만 불림 → Initialize에서 `Begin_ImGui` 한 번 | 2 |
| ImGui 창에 입력이 안 들어감 | WndProc 맨 앞 `ImGui_ImplWin32_WndProcHandler` 누락 | 2 |
| 로딩 레벨에서 ESC 누르면 assert | 컨텍스트 없이 `GetIO()` → `GetCurrentContext()` null 검사 먼저 | 2 |
| `ImGuiWindowFlags` 정의 안 됨 | `EditorUI_Defines.h`보다 imgui.h를 먼저 포함 (`EditorUI_Utils.h`를 맨 앞에) | 3 |
| 패널에 접기 버튼(▼)이 없음 | `g_FixedPanelFlags`에 `ImGuiWindowFlags_NoCollapse`가 들어 있음 | 3 |
| 패널을 접었더니 Delete 키/우클릭 메뉴가 안 됨 | 정상. 접히면 `Begin`이 false라 창 안 코드가 실행되지 않는다 | 3 |
| 가운데가 회색이 아니라 검정 | `Set_DrawToBackBuffer(false)`를 불렀음 → 부르지 않는다 (기본 true) | 4 |
| 패널 위에서도 `Viewport`로 나옴 | `WantCaptureMouse`를 `ImGui::NewFrame` 전에 읽음 → `CEditorUI::Update`(NewFrame 뒤)에서 읽는다 | 4 |
| 카메라가 전혀 안 움직임 | 패널이 없는 곳을 한 번 클릭해 ImGui 창 포커스를 풀었는지, `Sync_Viewport` 호출 | 5 |
| Inspector에 글자 치면 카메라가 움직임 | 카메라 Update에 `bViewportFocused/Hovered` 조건 누락 | 5 |
| `NearZ > 0.f && FarZ > 0.f` assert | Engine 헤더와 `EngineSDK/Inc`가 달라 DESC 모양이 어긋남 → Engine 다시 빌드 후 MapTool | 5 |
| 에디터에 들어가자마자 실패 | 사본이 쓰는 원형(`Obj_SkyBox`, `Obj_MapToolCam`, `Obj_Fog`)이 `LEVEL::MAPTOOL`에 등록됐는지 | 5, 6 |
| `Add Static_Prop` 누르면 크래시 | `g_Models`가 비어서 `[0]` 접근 → 로더에 모델 원형이 있는지, Inspector `Initialize`가 채우는지 | 6 |
| `Create Failed` (StaticProp) | 모델 태그가 다름 → 로더 태그와 DESC 경로를 둘 다 `Normalize_AssetPath`했는지 | 6 |
| 모델/지형이 새까맣다 | 방향광(b3) 또는 안개(b5) 없음. 안개가 없으면 0으로 나눔 → `Ready_Lights` + Fog 사본 | 6 |
| 해와 안개를 넣었는데 검다 | Fog 사본을 `Proto::Obj_SkyBox`로 Add함 | 6 |
| 값을 바꿨는데 화면 그대로 | 상수버퍼를 생성 때 한 번만 채움 → 매 프레임 `Update_ConstantBuffer(월드)` | 6, 11 |
| 이름이 깨져 보임 | wstring을 `To_UTF8` 없이 넘김 | 7 |
| 우클릭 메뉴가 두 개 겹침 | 빈 곳 메뉴에 `ImGuiPopupFlags_NoOpenOverItems` | 8 |
| 항목 메뉴가 엉뚱한 항목에 붙음 | `BeginPopupContextItem`을 `Selectable` 바로 다음에 | 8 |
| 삭제 시 크래시 | 목록 루프 안에서 지움 → 플래그 + 루프 뒤, 실제 제거는 엔진 | 8 |
| 입력칸에서 Delete 누르면 객체가 지워짐 | Delete 키 조건에 `IsWindowFocused()` | 8 |
| 회전 값이 (180, 90, 180)처럼 튐 | 행렬에서 각도를 뽑음 → `m_vEulerHint` 표시 | 9 |
| 콤보에 현재 값이 안 잡힘 | 객체 경로는 소문자 정규화 → 목록도 `Normalize_AssetPath` 후 비교 | 10 |
| `Add Terrain` → `Create Failed` | 지형 원형(raw, splat, Layer%d)과 `VS/PS_TERRAIN`이 MAPTOOL 레벨에 있는지, DESC 경로와 같은 파일인지 | 11 |
| 피킹하면 항상 지형만/아무것도 안 잡힘 | 지형 제외 누락, 또는 `Com_Model` 슬롯 이름이 다름 | 12 |
| 우클릭 회전할 때마다 메뉴가 뜸 | 드래그 거리 검사 누락 (5픽셀) | 14 |
| 지형을 옮기니 생성 위치가 어긋남 | 지형 정점이 로컬 좌표 → 16. 남은 작업 | 14 |
| 우클릭 메뉴를 고르는 클릭이 피킹으로 선택을 바꿈 | 피킹 조건에 `bViewportHovered` 누락 (팝업이 열려 있으면 false) | 14 |
| 피킹/기즈모 위치가 마우스와 어긋남 | 창 크기가 1600×900이 아님 → `CreateWindowW`와 `AdjustWindowRectExForDpi`에 같은 `dwStyle`을 넘겼는지, 크기 변경을 막았는지 (1-6) | 12, 15 |
| 기즈모 축을 잡으면 뒤 객체가 선택됨 | 피킹 조건에 `!IsOver() && !IsUsing()`, 그리고 `Manipulate_Gizmo`를 피킹보다 **먼저** 호출 | 15 |
| 기즈모가 화면에 안 보임 | `ImGuizmo::BeginFrame` 누락, 또는 선택 객체가 펼친 패널 뒤에 있음 (기즈모는 패널 아래에 그려짐) | 15 |
| 기즈모로 바꿨는데 Inspector 숫자가 안 바뀜 | Transform에 직접 썼음 → `Set_Transform`으로 원본 값까지 | 15 |
