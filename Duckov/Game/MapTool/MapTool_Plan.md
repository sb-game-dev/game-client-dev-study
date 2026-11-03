# MapTool 단계별 계획

> 방식: **프로토타입 Clone + DESC 파싱**
> - "어떤 클래스인가" → 프로토타입 태그
> - "어떤 값으로 만들까" → DESC (Transform, 경로, 클래스별 추가 값)
> - 구조물(그리기만 하는 것)은 클래스 하나(`CStaticProp`) + 경로로 처리
> - **게임에 이미 있는 객체는 Client 클래스를 그대로 맵툴로 불러온다.** 부모만 `CMapObject`로 바꾸고, 로직은 `bEditorMode`로 막는다
> - 맵 파일은 **바이너리**. "어떤 클래스를 어떤 값으로 만드나"만 담는다 (로직은 Client 코드에 이미 있음)

---

## 전체 구조

```
툴 (저장)                                      파일                         Client (불러오기)
Layer_Map 객체 ─ 태그 / 이름 / Transform / 경로 / 추가값 ─▶ Stage1.map ─▶ 읽기 ─▶ Add_GameObject(태그, &Desc)
   (bEditorMode = true → 렌더만)                                                (bEditorMode = false → 로직까지)
```

| 종류 | 예 | 방법 |
|---|---|---|
| 구조물, 소품 (그리기만 함) | 벽, 건물, 상자 | `CStaticProp` 하나 + 메시/텍스처 경로 |
| 게임에 이미 있는 객체 | 지형(`CHill`), 플레이어 시작 위치(`CPlayer`), `CTree`, `CCube`, `CMirror`, `CWave` | 기존 Client 클래스의 부모를 `CMapObject`로 + `bEditorMode` 분기 (8단계) |
| 맵과 무관한 객체 | 카메라, UI(Inven, Mouse, Scope), 조명, 안개, SkyBox | 배치 대상 아님, Level 코드에서 생성 |

**같은 클래스가 툴과 게임에서 다르게 동작하는 방법** — DESC의 두 값으로 나눈다

| 값 | 의미 | 툴 | 게임 |
|---|---|---|---|
| `iLevelIndex` | 컴포넌트 원형을 **어느 레벨에서 찾나** | `MAPTOOL` | `GAMEPLAY` |
| `bEditorMode` | **로직(입력, AI, 다른 객체 찾기)을 돌리나** | `true` → 렌더만 | `false` → 전부 |

- 로직 분기를 `iLevelIndex == GAMEPLAY`로 하지 않는다. 레벨이 늘어나면(플레이 테스트 레벨, 스테이지 2) 조건문을 전부 고쳐야 한다. 레벨 번호는 "원형 위치", 에디터 모드는 "동작"으로 역할을 나눈다
- `#ifdef _MAPTOOL`도 쓰지 않는다. 같은 exe 코드가 DESC 값만으로 갈린다

---

## 완료된 단계

- [x] 창 배치 (Hierarchy / Scene / Inspector)
- [x] Scene 창 RTT
- [x] 로딩 레벨 + `CLoader_MapTool` (원형은 서브 스레드에서 MAPTOOL 레벨에 등록)
- [x] 1~5단계 (큐브 띄우기, `CMapObject` + DESC, `CStaticProp`, Hierarchy 생성/삭제, Inspector Transform + Mesh/Texture 교체)
- [x] 지형 — `CHill`을 `CMapObject`로 옮김 (8단계의 첫 번째 클래스, Hierarchy `Add Terrain`)
- [x] 방향광(`CSunLight`) + 안개(`CFog`) — 지형 셰이더가 b3, b5를 읽으므로 맵툴에도 필요
- [ ] **다음 작업: 9단계 피킹 + 기즈모** → 그다음 6단계 저장/불러오기
- [ ] 카메라 정리 (직접 진행 중)
  - [x] `CCamera::Render`에 `return S_OK;` 추가 (Engine/Private/Camera.cpp)
  - [x] Level_MapTool의 초기화 안 된 카메라 등록 삭제
  - [ ] 마우스 회전에서 `fDeltaTime` 곱하기 제거 (감도 `fSensor`도 다시 맞추기)
  - [ ] Scene 이미지 가로 가운데 정렬 (지금은 세로만)
  - [x] `cout` 제거 (EditorUI.cpp)
  - [ ] (권장) 우클릭을 씬 위에서 시작했을 때만 드래그 / 피치 제한

---

## 1단계. VIBuffer로 큐브 하나 띄우기 (모델은 나중에)

**목표**: 내장 VIBuffer(Cube) + 텍스처로 그린 객체가 툴의 Scene 창에 보인다.

- [x] `CCube::Render_Mesh`의 순서(상수버퍼 → 셰이더 → 텍스처 → 버퍼)를 참고해서 그리기
- [x] 셰이더는 `Model_VertexShader.hlsl` / `Model_PixelShader.hlsl` (VTXNORM) — `VS_MAIN` + `PS_MAIN_NOLIGHT`
- [x] 내장 메시는 cube, rect만 사용 (pyramid는 VTXCOL이라 텍스처 셰이더와 맞지 않음)
- [x] Level_MapTool에서 코드로 하나 생성해서 확인 (4단계에서 툴 생성으로 대체 후 삭제)

**완료 기준**: Scene 창에 큐브가 보이고, 카메라로 둘러볼 수 있다.

> 메시는 처음부터 **경로 문자열**로 다룬다: 지금 `"builtin/cube"` → 나중에 `"model/wall_01.fbx"`.
> 저장 형식, 툴 UI는 그대로 두고 StaticProp 내부만 바꾸면 모델로 전환된다 (10단계).

---

## 2단계. 공통 DESC와 레벨 번호 정리

**목표**: 배치 가능한 객체가 "레벨 번호", "에디터 모드", "Transform"을 DESC로 받는다.

```cpp
typedef struct tagMapObjectDesc : public GAMEOBJECT_DESC
{
	uint32_t  iLevelIndex = {};             // 컴포넌트를 찾을 레벨 (툴: MAPTOOL, Client: GAMEPLAY)
	float3_t  vPosition = {}, vRotation = {}, vScale = { 1, 1, 1 };   // 회전은 degree
	wstring_t strMeshPath;                  // 지금 "builtin/cube", 나중 "model/xxx.fbx" (지형은 높이맵)
	wstring_t strTexturePath;               // builtin 메시용 (지형은 혼합맵)
	bool_t    bEditorMode = { false };      // true면 로직을 건너뛰고 렌더만
}MAPOBJECT_DESC;
```

- [x] `MAPOBJECT_DESC` 정의
- [x] `CMapObject` (abstract, `CGameObject` 상속) 생성
  - [x] Initialize에서 위치/회전/크기 → Transform 적용
  - [x] 위치/회전/크기 값을 멤버로 보관 (인스펙터 편집, 저장용. 행렬에서 다시 뽑지 않기)
  - [x] `virtual void Save_Extra(ofstream&) const {}` / `virtual void Load_Extra(ifstream&, MAPOBJECT_DESC&) {}`
  - [x] `bEditorMode` → `m_bEditorMode` 보관 (Hierarchy는 `true`로 생성)
- [x] Transform에 Euler 회전(도) → 행렬 적용 함수 (`CTransform::Rotation(x, y, z)`)
- [x] Engine `GAMEOBJECT_DESC`에도 `iLevelIndex` 추가 (`CGameObject::m_iLevelIndex`)
- [ ] `CMapObject`의 `iLevelIndex` / `m_iLevelIndex` 중복 제거 → `CGameObject` 것 하나로 (지금은 같은 이름이 부모·자식에 하나씩)

**완료 기준**: `CMapObject`를 상속한 객체가 DESC 값대로 위치/회전/크기가 잡힌다.

---

## 3단계. CStaticProp + 경로 = 원형 태그

**목표**: 클래스 하나로 모든 구조물을 표현한다. 메시/텍스처는 경로 문자열로 고른다.

- [x] `CStaticProp : CMapObject` 생성 (Client)
  - [x] 메시를 만드는 곳은 `Ready_Mesh()` 한 함수로 (`Change_Mesh` + `Change_Texture`를 부름). `"builtin/"`이 아니면 (지금은) 실패
  - [ ] `Render()`도 분기: 모델이 있으면 `Render_Model()`(나중), 없으면 버퍼 — 10단계에서
  - [x] `Late_Update`에서 `Add_RenderGroup(NONALPHA)` (처음엔 컬링 끄기)
- [x] 경로 = 원형 태그
  - [x] `Prototype_Manager`에 `Has_Prototype` 추가 (`Find_Prototype`이 private이라)
  - [x] 경로 정규화 (`\` → `/`, 소문자, Resource 기준 상대 경로) — `Normalize_AssetPath`
  - [x] **원형 등록은 로더가 전부** (`Normalize_AssetPath(경로)`를 태그로). 객체는 `Has_Prototype` 확인 후 Clone만
  - [x] 프로토타입 `Proto::Obj_StaticProp` 등록
- 바뀐 점: 처음에는 `CAsset_Manager`의 `Get_Or_Load_Texture / Get_or_Load_Mesh`(없으면 그 자리에서 로드)로 만들었다가, **로더에서 미리 등록하는 방식**으로 돌아왔다. 객체 생성 중에 파일을 읽지 않고, 로딩 화면에서 한 번에 읽는다. `CAsset_Manager`는 지금 쓰는 곳이 없다 (정리 대상)

**주의**
- `Add_Prototype`은 중복이면 `E_FAIL`, 원형이 `nullptr`이어도 그대로 등록 → `Create` 결과 확인
- 등록과 찾기가 **같은 `Normalize_AssetPath`**를 거쳐야 같은 태그가 나온다
- 콤보 목록(`g_Meshes` / `g_Textures`)에 넣으면 로더에도 한 줄 (두 곳)
- Engine 헤더 수정 후에는 **Engine 먼저 빌드** (EngineSDK로 복사됨)

**완료 기준**: StaticProp 여러 개를 만들고 콤보로 바꿔도 로드는 로딩 레벨에서 한 번만 일어난다.

---

## 4단계. 툴: 배치 (하이어라키)

**목표**: Hierarchy 창을 우클릭해서 객체를 만들고, 이름 목록에서 고르고, 지운다. (Unity 방식)

> Hierarchy는 **이름 + 선택만** 담당한다. 생성은 기본값으로 하고, 값은 전부 Inspector(5단계)에서 바꾼다.

**엔진 (삭제: `m_bDead` 방식)**
- [x] `CGameObject`에 `m_bDead` / `Set_Dead()` / `Is_Dead()`
- [x] `CLayer::Remove_Dead()` — `CObject_Manager::Priority_Update` 맨 앞에서 호출 (순회 전에 erase)
- [x] `CLayer` Update / Late_Update에서 `Is_Dead()` 객체 건너뛰기
- [x] 삭제 경로는 Dead 하나로 (즉시 삭제 `Remove_GameObject` 없음)
- [x] 객체 목록 조회 `Get_GameObjects(레벨, 레이어)` — Layer → Object_Manager → GameInstance
- [x] `CLayer::Add_GameObject` 중복 태그 시 `E_FAIL` + `CObject_Manager`에서 반환값 전달

**툴 (Hierarchy 창)**
- [x] 배치 가능한 목록: `{ 표시 이름, 프로토타입 태그 }` 배열 (`s_Placeables`) — `Add Static_Prop`, `Add Terrain`
- [x] `Create_Object(태그)`가 타입별 함수로 분기 (`Create_StaticProp`, `Create_Terrain`) — DESC 종류, 기본값, 이름 규칙이 타입마다 다름
- [x] 목록: `Selectable`로 **이름만** 표시, `Is_Dead()` 객체는 건너뛰기
- [x] 선택: `weak_ptr<CMapObject>` + 태그 보관
- [x] 빈 곳 우클릭 메뉴 (`BeginPopupContextWindow` + `ImGuiPopupFlags_NoOpenOverItems`)
- [x] 항목 우클릭 메뉴 (`BeginPopupContextItem`) → `Delete` (+ 나중에 Duplicate, Rename)
- [x] Delete 키로 삭제
- [x] 삭제는 `Set_Dead()`만 호출하고 **선택은 즉시 해제**
- [x] 태그는 고유하게: StaticProp은 비어 있는 `Prop_N`까지 번호 증가, 지형은 `Terrain` 고정 + 하나만

**완료 기준**: 우클릭 메뉴로 여러 개 만들면 전부 보이고 이름이 목록에 뜬다. 선택과 삭제가 되고, 지운 직후 Inspector는 선택 없음 상태가 된다.

---

## 5단계. 툴: 인스펙터 (Transform + 타입별 섹션)

**목표**: 선택한 객체의 Transform과 타입별 값을 Inspector에서 바꾼다.

```
Inspector
 Prop_01
 ▼ Transform            ← 모든 CMapObject 공통
   Position / Rotation / Scale
 ▼ Static Prop          ← dynamic_pointer_cast<CStaticProp> 성공 시
   Mesh    [Cube    ▼]
   Texture [Crate01 ▼]
 ▼ Terrain              ← dynamic_pointer_cast<CHill> 성공 시 (남은 작업)
```

- [x] `CGameObject::Remove_Component(태그)` 추가
- [x] `CStaticProp::Change_Mesh(경로)` / `Change_Texture(경로)` — `Has_Prototype` 확인 → 기존 제거 → `Add_Component`
- [x] `CMapObject`에 `Get_MeshPath()` / `Get_TexturePath()`
- [x] 선택 없음 / `Is_Dead()`면 "No object selected", 이름(태그) 표시
- [x] `CollapsingHeader("Transform")` : `DragFloat3` × 3 → `Set_Position` 등
- [x] `CollapsingHeader("Static Prop")` : Mesh / Texture 콤보 (`Render_AssetCombo`)
- [x] 타입별 섹션은 툴에서 `dynamic_pointer_cast`로 분기 (ImGui 코드를 Client 클래스에 넣지 않기)
- [ ] `CollapsingHeader("Terrain")` : 높이맵 / 혼합맵 / 레이어 경로 표시, **Rotation 숨기기** (회전하면 `GetHeight`가 어긋남)
- [ ] 8단계에서 옮기는 클래스마다 필요하면 섹션 추가 (고유 값이 있을 때만)
- [ ] (선택) 지형 높이에 스냅하는 버튼 (`CHill::GetHeight`)

**완료 기준**: Inspector 값을 바꾸면 Scene 창에서 바로 움직이고, 콤보를 바꾸면 바로 모양과 텍스처가 바뀐다.

---

## 9단계. 피킹 + 기즈모 ← 다음 작업 (6단계보다 먼저)

**목표**: Scene 창에서 객체를 클릭해서 고르고, 기즈모로 끌어서 옮기면 Inspector의 Transform이 같이 바뀐다.

> 번호는 9단계지만 모델 로드(10단계)와 상관없고 지금 있는 큐브·지형만으로 테스트할 수 있어서 먼저 한다. 순서: **피킹 → 기즈모 → 6단계 저장/불러오기**

### 9-1. 피킹 — Scene 이미지 좌표를 뷰포트 픽셀로 바꿔서 엔진 함수 그대로 쓰기

엔진의 `CCamera::Compute_PickingRay(POINT, Origin, Dir)`는 **뷰포트 픽셀 좌표**(1600 x 900 기준)를 받는다. 맵툴은 씬 텍스처를 Scene 창 안에 **축소해서** 그리므로 마우스 좌표를 그대로 넘기면 안 되고, 아래처럼 바꿔서 넘긴다. 엔진은 고치지 않는다 (NDC 오버로드 불필요).

```
씬 텍스처 픽셀 = (마우스 - vImageMin) / vImageSize * 뷰포트 크기
```

| 단계 | 계산 | 의미 |
|---|---|---|
| ① | `마우스 - vImageMin` | 화면 기준 좌표 → 이미지 왼쪽 위 기준 좌표 (둘 다 ImGui 화면 좌표라 바로 뺄 수 있음) |
| ② | `/ vImageSize` | 0~1 비율 (이미지가 몇 배로 축소됐든 상관없게) |
| ③ | `* 뷰포트 크기` | 씬 텍스처(= 뷰포트)의 픽셀 좌표 → `Compute_PickingRay`가 기대하는 값 |

**어디서**: `Panel_Scene.cpp`의 `ImGui::Image` 바로 다음 — `vImageMin`, `vImageSize`, `bSceneHovered`를 기록하는 그 자리

```cpp
ImGui::Image((ImTextureID)pSRV, vSize);

m_Context.vImageMin     = ...;          // 기존 코드
m_Context.vImageSize    = ...;
m_Context.bSceneHovered = ImGui::IsItemHovered();
m_Context.bSceneFocused = ImGui::IsWindowFocused();

// 피킹 요청: 이미지 위에서 왼쪽 버튼을 누른 프레임
if (m_Context.bSceneHovered && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
{
    const ImVec2   vMouse = ImGui::GetIO().MousePos;                  // 화면 기준 (vImageMin과 같은 좌표계)
    const float2_t vVP    = CGameInstance::Get().Get_ViewportSize();  // 1600 x 900

    const f32_t fU = (vMouse.x - m_Context.vImageMin.x) / m_Context.vImageSize.x;   // ① + ②
    const f32_t fV = (vMouse.y - m_Context.vImageMin.y) / m_Context.vImageSize.y;

    POINT ptPick{ static_cast<LONG>(fU * vVP.x), static_cast<LONG>(fV * vVP.y) };  // ③

    // 레이 만들기 (엔진 함수 그대로)
    vector_t vRayOrigin, vRayDir;
    if (auto pCamera = CGameInstance::Get().Get_MainCamera())
        pCamera->Compute_PickingRay(ptPick, vRayOrigin, vRayDir);

    // → 이 레이로 Layer_Map 객체들과 충돌 검사 (9-2)
}
```

- [ ] 위 코드 추가 (`Panel_Scene.cpp`)
  - `Get_MainCamera()`는 `shared_ptr<CCamera>`라 함수를 부르려면 `Camera.h`가 필요할 수 있다 (`GameInstance.h`는 `Camera_Manager.h`만 include). 컴파일 에러가 나면 `#include "Camera.h"`
- [ ] 좌클릭만 쓴다 — 카메라 회전이 우클릭이라 겹치지 않음
- [ ] `bSceneHovered` 조건 덕분에 비율 맞춤으로 생긴 위아래 빈 띠나 다른 창 위 클릭은 무시됨
- 왜 이 방식이 맞나: `Compute_PickingRay`는 `RSGetViewports`로 뷰포트(1600 x 900)를 읽고 그 기준으로 NDC를 만든다. 씬 텍스처도 같은 크기로 그려지므로 ③까지 바꾼 값이면 클릭한 픽셀과 레이가 정확히 맞는다

### 9-2. 피킹 — 레이와 객체 충돌

- [ ] **엔진 버그 먼저**: `VIBuffer_Cube.cpp`의 `BoundingBox::CreateFromPoints(m_tLocalBox, m_iVertexStride, …)` → 두 번째 인자는 정점 **개수**(`m_iNumVertices`). 지금은 32개를 읽어서 배열(24개) 밖을 읽는다
- [ ] `VIBuffer_Rect`도 박스 생성, `CVIBuffer`에 `Get_LocalBox()` getter 추가 (→ Engine 빌드)
- [ ] `Layer_Map`을 돌면서 객체마다
  - 레이를 **로컬 공간**으로 (월드 역행렬로 Origin은 `TransformCoord`, Dir은 `TransformNormal` 후 정규화)
  - 로컬 AABB와 `BoundingBox::Intersects(Origin, Dir, fDist)`
  - 거리를 월드 기준으로 비교해서 **가장 가까운 객체** 하나
- [ ] 맞으면 `m_Context.Select(태그, 객체)` → Hierarchy 하이라이트와 Inspector가 같이 바뀜. 빈 곳이면 `Clear_Selection()`
- [ ] **지형은 박스 피킹에서 제외** (박스가 맵 전체를 덮어서 항상 지형이 먼저 맞음). 지형은 나중에 "레이가 지형과 만나는 점"(`GetHeight`로 레이를 따라가며 찾기)을 구해서 **클릭한 자리에 객체 놓기**에 쓴다
- [ ] 충돌 검사 함수를 어디에 둘지: Panel_Scene에 피킹 요청(레이)만 `EDITOR_CONTEXT`에 남기고, 검사는 별도 함수(`Pick_Object(레이)`)로 — 패널끼리 직접 부르지 않는 규칙 유지

### 9-3. 기즈모 (ImGuizmo)

- [ ] `ImGuizmo.h/.cpp`를 `MapTool/ImGui/`에 추가 (지금 ImGui 버전에 맞는 것, cpp는 `/utf-8` + pch 안 씀)
- [ ] Scene 창 `ImGui::Image` 다음에 그리기: `SetDrawlist()`, `SetRect(vImageMin, vImageSize)`, View/Proj는 파이프라인 행렬
- [ ] `Manipulate`가 바꾼 월드 행렬은 Transform에 바로 넣지 않는다 → `DecomposeMatrixToComponents`로 위치 / 회전(도) / 크기로 나눠 `Set_Position / Set_Rotation / Set_Scale` (회전은 각도로 보관 원칙 → Inspector와 저장이 같은 값을 씀)
- [ ] Inspector는 고칠 필요 없음 — 매 프레임 `Get_*`를 읽으므로 자동으로 따라옴
- [ ] **회전 순서 확인**: `CTransform::Rotation`은 `XMQuaternionRotationRollPitchYaw`. ImGuizmo가 분해한 오일러 각과 순서가 다르면 회전 기즈모에서 값이 튐 → X / Y / Z를 하나씩 돌려 보고 확인
- [ ] **피킹과 겹치지 않게**: `ImGuizmo::IsOver()` 또는 `IsUsing()`이면 9-1의 좌클릭 피킹을 건너뜀 (안 하면 기즈모를 잡는 순간 뒤의 객체가 선택됨)
- [ ] W / E / R로 이동 / 회전 / 크기 — Scene 창 포커스일 때만, W는 카메라 이동 키와 겹치므로 우클릭 중이 아닐 때만 모드 전환
- [ ] 지형은 회전 기즈모 막기 (Inspector의 Rotation 숨기기와 같은 이유)

**완료 기준**: Scene에서 큐브를 클릭하면 Hierarchy와 Inspector에서 선택되고, 기즈모로 끌면 Inspector 숫자가 같이 바뀐다. 빈 곳을 클릭하면 선택이 풀린다.

---

## 6단계. 저장 / 불러오기 (바이너리)

**목표**: 툴에서 만든 배치를 파일로 저장하고 다시 복원한다.

파일 형식
```
[헤더]  매직 "DKMP", 버전 (uint32)
[개수]  (uint32)
[반복]  ← 지형을 맨 앞에
  프로토타입 태그        (문자열)   ← 불러올 때 이걸로 DESC 종류를 고름
  객체 이름              (문자열)   ← "Terrain", "Prop_03" ...
  메시 경로              (문자열, 없으면 빈 문자열)
  텍스처 경로            (문자열, 없으면 빈 문자열)
  위치 / 회전 / 크기      (float × 9)
  추가 데이터 크기        (uint32)   ← 모르는 클래스면 이만큼 건너뜀
  추가 데이터            (Save_Extra가 쓴 바이트)
```

- [ ] 문자열 쓰기/읽기 헬퍼 — 길이(uint32) → 내용(`wchar_t` × 길이)
- [ ] `CMapObject`에 `virtual const wchar_t* Get_PrototypeTag() const = 0` — 저장 루프가 타입을 몰라도 태그를 쓸 수 있게
- [ ] **지형을 맨 앞에** 저장 (게임에서 다른 객체가 생성될 때 `GetHeight`를 쓰므로 지형이 먼저 있어야 함)
- [ ] 추가 데이터
  - [ ] 저장: `Save_Extra(Out)` (가상 함수, 객체가 있으니 그대로 호출)
  - [ ] 불러오기: 태그로 `switch` → 클래스별 **`static Read_Extra(In, Desc)`**. `CMapObject::Load_Extra`는 인스턴스 함수라 못 쓴다 (DESC를 다 읽어야 객체를 만들 수 있는데, 읽는 시점엔 아직 객체가 없음)
  - [ ] `CHill`: `strLayerPath` (선언은 있음, 본문 비어 있음)
- [ ] `Save_Map(경로)` — **툴과 Client가 같이 쓰도록** 공용 위치에 두기
- [ ] 불러오기는 **두 함수로 나누기** (7단계에서 Loader 스레드와 메인 스레드로 나눠 쓰기 위해)
  - [ ] `Parse_Map(경로, 목록&)` : 파일 읽기 + DESC 목록 만들기 — 객체 생성 안 함. DESC가 클래스마다 달라서 목록은 `{ 태그, 이름, unique_ptr<MAPOBJECT_DESC> }`처럼 보관
  - [ ] `Spawn_Map(레벨, 에디터 모드, 목록)` : DESC에 `iLevelIndex`, `bEditorMode`를 넣고 `Add_GameObject`
  - [ ] 툴에서는 두 함수를 연달아 호출
- [ ] 메뉴바 연결: New / Open / Save / Save As (지금은 비활성으로 그려만 둠)
- [ ] 파일 대화상자 (`GetSaveFileName` / `GetOpenFileName`, `OFN_NOCHANGEDIR` 필수)
- [ ] 경로는 Resource 기준 상대 경로로 저장 (절대 경로 저장 금지)

**완료 기준**: 저장 → New → Open 하면 같은 배치가 같은 자리에 복원된다.

---

## 7단계. Client에서 불러오기

**목표**: 툴에서 만든 맵이 게임에 그대로 나온다.

- [ ] Loader에서 맵에 쓰인 원형을 **툴과 같은 태그**로 등록 — 경로 원형(`Normalize_AssetPath`), 셰이더, 객체 원형
- [ ] **Loader 스레드**: `Parse_Map(L"…/Stage1.map", 목록)` — 파일만 읽음
- [ ] **메인 스레드** (Level_GamePlay::Initialize): `Spawn_Map(ETOUI(LEVEL::GAMEPLAY), false, 목록)`
- [ ] **레이어 / 이름 맞추기**: 게임 코드가 이름으로 찾는 객체가 있다
  - `Player`, `Cube`, `Cube_Instance`, `Tree`가 `Layer_GameObject` / `GameObject_Hill`로 지형을 찾음
  - `Level_GamePlay`가 `GO::Mirror`로 거울을 찾아 `Set_Mirror`
  - → Client의 `Spawn_Map`은 `Layer_GameObject`에 만들고, 지형·플레이어·거울처럼 **찾히는 객체는 고정 이름(`GO::Hill`, `GO::Player`, `GO::Mirror`)**, 나머지는 저장된 이름
- [ ] 지금 `Level_GamePlay`에 코드로 적힌 지형 DESC 경로, 플레이어·거울 위치를 맵 파일 값으로 교체
- [ ] 카메라, UI, 조명, 안개, SkyBox는 기존처럼 코드에서 생성

**스레드 주의**
- `Add_GameObject`는 스레드에서 호출 금지 (메인이 매 프레임 레이어를 순회함)
- Prototype_Manager의 map은 잠금이 없음 → 스레드는 GAMEPLAY 레벨에만 쓰고, 메인은 LOADING 레벨만 읽는 구분 유지
- `CTexture::Create` 등이 DeviceContext를 쓰면 렌더링과 충돌할 수 있음 → 원인 모를 크래시 시 먼저 의심

**완료 기준**: 툴에서 본 배치와 게임 화면이 같다. ← **여기까지가 1차 완성**

---

## 8단계. 기존 Client 클래스를 맵툴로 불러오기

**목표**: 게임에 이미 있는 객체(플레이어, 나무, 큐브, 거울, 물 …)를 **같은 클래스 그대로** 툴에서 배치한다. 툴에서는 렌더만, 게임에서는 로직까지 돈다.

> 6·7단계와 따로 진행해도 된다. 클래스를 하나 옮길 때마다 Hierarchy에서 놓을 수 있게 되고, 저장/불러오기가 생기면 그대로 파일에 들어간다.

**옮길 대상 (의존성이 적은 순서)**

| 순서 | 클래스 | 다른 객체 의존 | 메모 |
|---|---|---|---|
| ✅ | `CHill` (지형) | 없음 | 완료. 맵에 하나 (`Terrain`) |
| 1 | `CCube` | 지형(`GetHeight`) | 패턴 잡기용 |
| 2 | `CTree` | 지형 | |
| 3 | `CMirror` | 레벨이 `GO::Mirror`로 찾아 `Set_Mirror` | 게임에서 이름 고정 |
| 4 | `CWave` | 없음 | |
| 5 | `CCube_Instance` | 지형 | 인스턴스 위치를 내부에서 정함 → 배치 의미가 있는지 먼저 판단 |
| 6 | `CPlayer` (시작 위치) | 지형, Inven, Client_Mouse, 카메라·조명이 플레이어를 참조 | 마지막. 맵에 하나 |

옮기지 않는 것: `CInven`, `CClient_Mouse`, `CScope`(UI), `CQuarterView_Cam` / `CFree_Cam`(카메라), `CPlayer_PointLight` / `CPlayer_SpotLight` / `CSunLight`(조명), `CFog`, `CSkyBox`, `CBackGround`(로고)

**클래스 하나를 옮길 때마다**
- [ ] 부모: `CGameObject` → `CMapObject`, DESC: `GAMEOBJECT_DESC` → `MAPOBJECT_DESC` 상속
  - 기존 DESC의 위치 값(`fPosX`, `fPosZ` …)은 `vPosition`으로 옮긴다 (Transform은 `CMapObject::Initialize`가 적용)
- [ ] 컴포넌트: `Add_Component(ETOUI(LEVEL::GAMEPLAY), …)` → `Add_Component(m_iLevelIndex, …)`
- [ ] 로직: `if (m_bEditorMode)`로 막는다
  - `Update` 맨 앞에서 `return` (키 입력, AI, 이동). DirectInput은 어느 창이 포커스든 입력이 들어오므로 막지 않으면 Inspector에 숫자를 치는 중에도 플레이어가 움직인다
  - `Late_Update`는 로직만 막고 **`Add_RenderGroup`은 그대로** (안 하면 툴에서 안 보임)
- [ ] **다른 객체 찾기(`Find_GameObject`)는 전부 에디터 모드 분기 안으로 + `nullptr` 검사**
  - 툴에는 Inven·Mouse가 없고, 지형은 `Layer_Map` / `Terrain`에 있다 → `static_pointer_cast` 결과를 그대로 쓰면 크래시
  - `Initialize`에서 찾는 코드는 첫 Update로 미룬다 (생성 순서와 상관없게)
  - `Priority_Update`처럼 Update가 아닌 곳에 숨어 있는 것도 확인 (예: `CPlayer::Priority_Update`의 Inven)
- [ ] 툴 로더(`CLoader_MapTool`)에 그 클래스가 쓰는 원형을 **MAPTOOL 레벨, 같은 태그**로 등록
  - 객체가 늘면 두 로더가 어긋나기 쉬움 → `Ready_Prototypes_Common(uint32_t iLevel)` 같은 공용 등록 함수를 만들어 두 로더가 같이 부르기
- [ ] 고유 값(HP, 순찰 반경 등)이 있으면 DESC 상속 + `Save_Extra` / `static Read_Extra`
- [ ] Hierarchy `s_Placeables`에 추가 + `Create_XXX` (맵에 하나만 있어야 하면 이름 고정 + 중복 검사)
- [ ] `Get_PrototypeTag()` 구현 (6단계 저장용)
- [ ] 게임의 `Level_GamePlay`에서 그 객체를 직접 만들던 코드는 7단계 `Spawn_Map`으로 대체

**완료 기준**: 옮긴 클래스가 툴(렌더만)과 게임(로직까지) 양쪽에서 같은 코드로 동작한다.

---

## 10단계. 모델(fbx)로 전환 — 모델 로드를 익힌 뒤

**목표**: `strMeshPath`에 fbx 경로를 넣으면 모델이 그려진다. 기존 `builtin/` 맵 파일도 그대로 읽힌다.

- [ ] 엔진의 모델 로딩 확인 (Assimp, `Material.h`)
- [ ] 모델 원형도 로더에서 `Normalize_AssetPath(경로)` 태그로 등록 (3단계와 같은 방식)
- [ ] `CStaticProp::Change_Mesh`에서 `builtin/`이 아니면 모델 컴포넌트로 교체
- [ ] `Render_Model()` 작성 — 모델은 **메시 여러 개 + 메시별 머티리얼**이라 메시 단위로 반복
- [ ] 모델용 정점 형식(탄젠트 등)에 맞는 셰이더 준비
- [ ] 툴 메시 목록(`g_Meshes`)에 fbx 추가 (많아지면 폴더 스캔 + `vector`로 전환)

**완료 기준**: 큐브와 모델이 한 맵에 섞여 있어도 저장/불러오기가 된다.

---

## 확장 (선택)

- [ ] 복제 (Ctrl+D), 실행 취소
- [ ] 환경 편집 — 해(`CSunLight`) / 안개(`CFog`) 값을 Inspector에서 고치고 맵 파일 앞부분에 환경 섹션으로 저장
- [ ] 점광원 여러 개 배치 — 셰이더를 배열로, `CLight_Manager`가 모아서 한 번에 바인딩 (지금은 종류별로 하나만 의미 있음)
- [ ] 모델 미리보기 / 에셋 창

---

## 메모

- 회전은 행렬이 아니라 **각도(도)로 저장** — 행렬에서 다시 뽑으면 값이 튐
- Engine 헤더 수정 → **Engine 빌드 먼저** → MapTool / Client 빌드. `EngineSDK/Inc`는 직접 고치지 않기 (헤더가 어긋나면 DESC를 밀려 읽어 카메라 Near/Far assert)
- 툴 전용 코드(ImGui)는 MapTool에만. Engine과 Client 클래스에는 넣지 않기 (Client 쪽 분기는 `m_bEditorMode` 하나)
- 원형은 로더가 등록, 객체는 Clone만. 기존 Client 클래스도 옮길 때 툴 로더에 같은 태그로 등록
- 셰이더는 `Client/Bin/Shader`를 고친다 (MapTool 빌드 후 이벤트가 MapTool 쪽을 덮어씀)
- 툴 프레임 순서: `Update_Engine`(Remove_Dead → 객체 Update… → 조명 → 레벨 Update(`CEditorUI`, ImGui)) → `Draw` — ImGui에서 `Set_Dead` 하면 다음 프레임 맨 앞에 지워짐
