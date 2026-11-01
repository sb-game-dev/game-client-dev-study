# MapTool 단계별 계획

> 방식: **프로토타입 Clone + DESC 파싱**
> - "어떤 클래스인가" → 프로토타입 태그
> - "어떤 값으로 만들까" → DESC (Transform, 모델 경로, 클래스별 추가 값)
> - 구조물은 클래스 하나(`CStaticProp`) + 모델 경로로 처리
> - 로직 있는 객체는 `CMapObject`를 상속한 기존 Client 클래스

---

## 전체 구조

```
툴 (저장)                              파일                               Client (불러오기)
객체 목록 ─ 태그 / 모델경로 / Transform / 추가값 ─▶ Stage1.map ─▶ 읽기 ─▶ Add_GameObject(태그, &Desc)
```

| 종류 | 예 | 방법 |
|---|---|---|
| 구조물, 소품 (그리기만 함) | 벽, 건물, 상자, 나무 | `CStaticProp` 하나 + 모델 경로 |
| 로직 있는 객체 | 몬스터, 문, 아이템, 스폰 지점 | `CMapObject` 상속 + 필요하면 `Save_Extra/Load_Extra` |
| 맵과 무관한 객체 | 카메라, UI, 조명 | 배치 대상 아님, Level 코드에서 생성 |

---

## 완료된 단계

- [x] 창 배치 (Hierarchy / Scene / Inspector)
- [x] Scene 창 RTT
- [x] 1~3단계 (큐브 띄우기, `CMapObject` + DESC, `CStaticProp` + `CAsset_Manager`)
- [x] 4~5단계 (Hierarchy 우클릭 생성/삭제, Inspector Transform + Mesh/Texture 교체) — 실행 확인 필요
- [ ] 카메라 정리 (직접 진행 중)
  - [x] `CCamera::Render`에 `return S_OK;` 추가 (Engine/Private/Camera.cpp)
  - [x] Level_MapTool.cpp 65~67줄 (초기화 안 된 카메라 등록) 삭제
  - [ ] 마우스 회전에서 `fDeltaTime` 곱하기 제거 (감도 `fSensor`도 다시 맞추기)
  - [ ] Scene 이미지 비율을 가로/세로 모두 맞추기 (지금은 세로만 가운데 정렬)
  - [x] `cout` 제거 (EditorUI.cpp)
  - [ ] (권장) 우클릭을 씬 위에서 시작했을 때만 드래그 / `Update_PipeLines` 매 프레임 / 피치 제한

---

## 1단계. VIBuffer로 큐브 하나 띄우기 (모델은 나중에)

**목표**: 내장 VIBuffer(Cube) + 텍스처로 그린 객체가 툴의 Scene 창에 보인다.

- [x] `CCube::Render_Mesh`의 순서(상수버퍼 → 셰이더 → 텍스처 → 버퍼)를 참고해서 그리기
- [x] 셰이더는 `Shader_VtxTex.hlsl` (VTXNORM용) 사용
- [x] 내장 메시는 cube, rect만 사용 (pyramid는 VTXCOL이라 텍스처 셰이더와 맞지 않음)
- [x] Level_MapTool에서 코드로 하나 생성해서 확인 (`Prop_0~2` — 4단계에서 툴 생성으로 대체 후 삭제)

**완료 기준**: Scene 창에 큐브가 보이고, 카메라로 둘러볼 수 있다.

> 메시는 처음부터 **경로 문자열**로 다룬다: 지금 `"builtin/cube"` → 나중에 `"model/wall_01.fbx"`.
> 저장 형식, 툴 UI, 로더는 그대로 두고 StaticProp 내부만 바꾸면 모델로 전환된다 (10단계).

---

## 2단계. 공통 DESC와 레벨 번호 정리

**목표**: 배치 가능한 객체가 "레벨 번호"와 "Transform"을 DESC로 받는다. `#ifdef _MAPTOOL`이 필요 없어진다.

```cpp
struct MAP_OBJECT_DESC : public CGameObject::GAMEOBJECT_DESC
{
	uint32_t  iLevelIndex = {};             // 컴포넌트를 찾을 레벨 (툴: MAPTOOL, Client: GAMEPLAY)
	float3_t  vPosition = {}, vRotation = {}, vScale = { 1, 1, 1 };   // 회전은 degree
	wstring_t strMeshPath;                  // 지금 "builtin/cube", 나중 "model/xxx.fbx"
	wstring_t strTexturePath;               // builtin 메시용 (모델은 자체 머티리얼 사용)
	bool_t    bEditorMode = { false };      // true면 로직을 건너뛰고 렌더만
};
```

- [x] `MAP_OBJECT_DESC` 정의 (`MAPOBJECT_DESC`)
- [x] `CMapObject` (abstract, `CGameObject` 상속) 생성
  - [x] Initialize에서 위치/회전/크기 → Transform 적용
  - [x] 위치/회전/크기 값을 멤버로 보관 (인스펙터 편집, 저장용. 행렬에서 다시 뽑지 않기)
  - [x] `virtual void Save_Extra(ofstream&) const {}` / `virtual void Load_Extra(ifstream&, MAP_OBJECT_DESC&) {}`
- [x] Transform에 Euler 회전(도) → 행렬 적용 함수 확인 또는 추가 (`CTransform::Rotation(x, y, z)`)

**완료 기준**: `CMapObject`를 상속한 테스트 객체가 DESC 값대로 위치/회전/크기가 잡힌다.

---

## 3단계. CStaticProp + 에셋 캐시

**목표**: 클래스 하나로 모든 구조물을 표현한다. 같은 메시/텍스처는 한 번만 로드한다.

- [x] `CStaticProp : CMapObject` 생성 (Client)
  - [x] 메시를 만드는 곳은 `Ready_Mesh()` 한 함수로: `"builtin/"`이면 VIBuffer + 텍스처, 아니면 (지금은) 실패
  - [ ] `Render()`도 분기: `m_pModel`이 있으면 `Render_Model()`(나중), 없으면 `Render_Buffer()` — 10단계에서
  - [x] `Late_Update`에서 `Add_RenderGroup(NONALPHA)` (처음엔 컬링 끄기)
- [x] 에셋 캐시: "경로로 찾고, 없으면 로드"
  - [x] `Prototype_Manager`에 `Has_Prototype` 추가 (`Find_Prototype`이 private이라)
  - [x] 경로 정규화 (`\` → `/`, 소문자, Resource 기준 상대 경로) — `Normalize_AssetPath`
  - [x] `Get_Or_Load_Texture(레벨, 경로)`, `Get_or_Load_Mesh(레벨, "builtin/cube")` : 확인 → 없으면 생성 + `Add_Prototype` → Clone
  - [x] Device가 필요한 곳 결정 → `CAsset_Manager`를 Engine에 두고 GameInstance가 소유
  - [ ] 로드 실패 시 메시지 박스 (지금은 `m_FailedTags`에 기록하고 `E_FAIL`만 반환)
- [x] 프로토타입 `Proto::Obj_StaticProp` 등록

**주의**
- `Add_Prototype`은 중복이면 `E_FAIL` → 반드시 "확인 → 생성 → 등록" 순서
- 없는 경로를 매 프레임 요청하지 않기 (실패하면 메시지 박스)
- Engine 헤더 수정 후에는 **Engine 먼저 빌드** (EngineSDK로 복사됨)

**완료 기준**: 같은 모델의 StaticProp 여러 개를 생성해도 로드는 한 번만 일어난다.

---

## 4단계. 툴: 배치 (하이어라키)

**목표**: Hierarchy 창을 우클릭해서 객체를 만들고, 이름 목록에서 고르고, 지운다. (Unity 방식)

> Hierarchy는 **이름 + 선택만** 담당한다. 생성은 기본값(cube + 첫 번째 텍스처)으로 하고, 값은 전부 Inspector(5단계)에서 바꾼다.

**엔진 (삭제: `m_bDead` 방식)**
- [x] `CGameObject`에 `m_bDead` / `Set_Dead()` / `Is_Dead()`
- [x] `CLayer::Remove_Dead()` — `CObject_Manager::Priority_Update` 맨 앞에서 호출 (순회 전에 erase)
- [x] `CLayer` Update / Late_Update에서 `Is_Dead()` 객체 건너뛰기
- [x] `Layer.h`에 `Remove_Dead()` 선언 추가
- [x] `Remove_Dead()`에 nullptr 체크
- [x] 즉시 삭제 `Remove_GameObject`는 정리 (삭제 경로는 Dead 하나로)
- [x] 객체 목록 조회 `Get_GameObjects(레벨, 레이어)` — Layer → Object_Manager → GameInstance
- [x] `CLayer::Add_GameObject` 중복 태그 시 `E_FAIL` + `CObject_Manager`에서 반환값 전달

**툴 (Hierarchy 창)**
- [x] 배치 가능한 목록: `{ 표시 이름, 프로토타입 태그 }` 배열 (`s_Placeables`)
- [x] 목록: `Selectable`로 **이름만** 표시, `Is_Dead()` 객체는 건너뛰기
- [x] 선택: `weak_ptr<CMapObject>` + 태그 보관
- [x] 빈 곳 우클릭 메뉴 (`BeginPopupContextWindow` + `ImGuiPopupFlags_NoOpenOverItems`)
  - [x] `Add StaticProp` 등 `s_Placeables` 항목 → 기본 DESC로 `Add_GameObject` 후 바로 선택
- [x] 항목 우클릭 메뉴 (`BeginPopupContextItem`) → `Delete` (+ 나중에 Duplicate, Rename)
  - [x] `Selectable` **바로 다음 줄**에 호출 (바로 앞 위젯의 ID로 항목별 메뉴가 됨)
  - [x] 메뉴가 열리면 우클릭한 항목을 선택 상태로 변경 (다른 객체가 지워지는 혼동 방지)
  - [x] `Delete`는 `m_bRequestDelete` 플래그만 세우고, 목록 루프가 끝난 뒤 `Delete_Selected()` 호출
  - [x] 빈 곳 메뉴는 `ImGuiPopupFlags_NoOpenOverItems`를 유지 (항목 위에서 두 메뉴가 겹쳐 열리지 않게)
- [x] Delete 키로 삭제
- [x] 삭제는 `Set_Dead()`만 호출하고 **선택은 즉시 해제** (erase 전까지 `weak_ptr`가 살아 있음)
- [x] 태그는 고유하게: `Find_GameObject`로 비어 있는 `Prop_N`이 나올 때까지 번호 증가 (불러온 맵, Dead 대기 중 객체와도 안 겹치게)
- [x] Hierarchy에 넣었던 Type / Mesh / Texture 콤보와 Create 버튼 제거
- [x] Level_MapTool의 테스트 객체 `Prop_0~2` 삭제

**완료 기준**: 우클릭 메뉴로 여러 개 만들면 전부 보이고 이름이 목록에 뜬다. 선택과 삭제가 되고, 지운 직후 Inspector는 선택 없음 상태가 된다.

---

## 5단계. 툴: 인스펙터 (Transform + 컴포넌트)

**목표**: 선택한 객체의 Transform과 Mesh / Texture를 Inspector에서 바꾼다.

```
Inspector
 Prop_1
 ▼ Transform            ← 모든 CMapObject 공통
   Position / Rotation / Scale
 ▼ Static Prop          ← dynamic_pointer_cast<CStaticProp> 성공 시
   Mesh    [Cube    ▼]
   Texture [Crate01 ▼]
```

**엔진 / Client: 이미 만든 객체의 메시·텍스처 교체**
- [x] `CGameObject::Remove_Component(태그)` 추가 (`Add_Component`는 같은 태그가 있으면 `E_FAIL`)
- [x] `CStaticProp::Change_Mesh(경로)` / `Change_Texture(경로)`
  - [x] **새 리소스를 먼저 `Get_Or_Load`** → 성공 시에만 기존 컴포넌트 제거 → `Add_Component` (실패하면 기존 것 유지)
  - [x] 저장하는 경로는 정규화된 태그
- [ ] `Ready_Mesh()`는 두 함수를 호출하도록 정리 (생성과 교체가 같은 코드) — 지금은 옛 코드 그대로, 동작은 정상
- [x] `CMapObject`에 `Get_MeshPath()` / `Get_TexturePath()`

**툴 (Inspector 창)**
- [x] 선택 없음 / `Is_Dead()`면 "No object selected"
- [x] 이름(태그) 표시
- [x] `CollapsingHeader("Transform")` : `DragFloat3` × 3 (위치 / 회전 / 크기) → `Set_Position` 등
- [x] `CollapsingHeader("Static Prop")` : Mesh / Texture 콤보
  - [x] 목록은 `s_Placeables`처럼 `{ 표시 이름, 경로 }` 배열로 미리 등록 (`s_Meshes`, `s_Textures`)
  - [x] `BeginCombo` + `Selectable`로 그리기, 바뀌면 `Change_Mesh` / `Change_Texture`
  - [x] 현재 값 비교는 `Normalize_AssetPath(목록 경로) == 객체 경로` (저장 경로는 소문자)
  - [x] 목록에 없는 경로(불러온 맵 등)는 미리보기에 경로 그대로 표시
- [x] 타입별 섹션은 툴에서 `dynamic_pointer_cast`로 분기 (ImGui 코드를 Client 클래스에 넣지 않기)
- [ ] (선택) 지형 높이에 스냅하는 버튼

**완료 기준**: Inspector 값을 바꾸면 Scene 창에서 바로 움직이고, Mesh / Texture 콤보를 바꾸면 바로 모양과 텍스처가 바뀐다.

---

## 6단계. 저장 / 불러오기

**목표**: 툴에서 만든 배치를 파일로 저장하고 다시 복원한다.

파일 형식 (바이너리 예시)
```
[헤더]  매직 "DKMP", 버전
[개수]
[반복]
  프로토타입 태그        (문자열)
  메시 경로              (문자열, "builtin/cube" 또는 "model/xxx.fbx", 없으면 빈 문자열)
  텍스처 경로            (문자열, builtin 메시용)
  위치 / 회전 / 크기      (float × 9)
  추가 데이터 크기        (uint32)   ← 모르는 클래스면 이만큼 건너뜀
  추가 데이터            (Save_Extra가 쓴 바이트)
```

- [ ] 문자열 쓰기/읽기 헬퍼 (길이 + 내용)
- [ ] `Save_Map(경로)` — **툴과 Client가 같이 쓰도록** 공용 위치에 두기
- [ ] 불러오기는 **두 함수로 나누기** (7단계에서 Loader 스레드와 메인 스레드로 나눠 쓰기 위해)
  - [ ] `Parse_Map(경로, vector<MAPOBJECT_DESC>&)` : 파일 읽기 + DESC 목록 만들기 (+ 메시/텍스처 `Get_Or_Load`) — 객체 생성 안 함
  - [ ] `Spawn_Map(레벨, 레이어, const vector<…>&)` : 목록으로 `Add_GameObject` — 캐시에 있으니 Clone만
  - [ ] 툴에서는 두 함수를 연달아 호출
- [ ] 메뉴바 연결: New / Open / Save / Save As
- [ ] 파일 대화상자 (`GetSaveFileName` / `GetOpenFileName`, `OFN_NOCHANGEDIR` 필수)
- [ ] 경로는 Resource 기준 상대 경로로 저장 (절대 경로 저장 금지)

**완료 기준**: 저장 → New → Open 하면 같은 배치가 같은 자리에 복원된다.

---

## 7단계. Client에서 불러오기

**목표**: 툴에서 만든 맵이 게임에 그대로 나온다.

- [ ] Loader에서 프로토타입 등록 (같은 태그) — 셰이더, 객체 원형(`Obj_StaticProp` 등)
- [ ] **Loader 스레드**: `Parse_Map(L"…/Stage1.map", Descs)` → 메시/텍스처가 로딩 화면 동안 캐시에 로드됨
- [ ] **메인 스레드** (Level_GamePlay::Initialize): `Spawn_Map(ETOUI(LEVEL::GAMEPLAY), L"Layer_Map", Descs)`
- [ ] 카메라, UI, 조명, 플레이어는 기존처럼 코드에서 생성

**스레드 주의**
- `Add_GameObject`는 스레드에서 호출 금지 (메인이 매 프레임 레이어를 순회함)
- Prototype_Manager의 map은 잠금이 없음 → 스레드는 GAMEPLAY 레벨에만 쓰고, 메인은 LOADING 레벨만 읽는 구분 유지
- `CTexture::Create` 등이 DeviceContext를 쓰면 렌더링과 충돌할 수 있음 → 원인 모를 크래시 시 먼저 의심
- 이후 Loader의 맵 구조물용 텍스처/버퍼 수동 등록은 8단계에서 클래스를 옮길 때 하나씩 제거

**완료 기준**: 툴에서 본 배치와 게임 화면이 같다. ← **여기까지가 1차 완성**

---

## 8단계. 기존 Client 클래스를 배치 가능하게 옮기기

**목표**: 몬스터, 문, 아이템처럼 로직 있는 객체도 툴에서 배치한다. 단순한 것(Cube)부터 하나씩 옮긴다.

클래스 하나를 옮길 때마다:
- [ ] `CGameObject` → `CMapObject` 상속으로 변경
- [ ] `Add_Component(ETOUI(LEVEL::GAMEPLAY), …)` → `Add_Component(pDesc->iLevelIndex, …)`
- [ ] Initialize에서 다른 객체를 찾는 코드는 첫 Update / `Late_Initialize`로 미루고, 못 찾으면 넘어가기
  - 예: `Cube.cpp:42`의 `GameObject_Hill` 검색
- [ ] `bEditorMode`면 AI, 입력 같은 로직은 건너뛰고 렌더만
- [ ] 고유 값(HP, 순찰 반경 등)이 있으면 DESC 상속 + `Save_Extra / Load_Extra`
- [ ] 툴 배치 목록에 추가
- [ ] SkyBox처럼 `#ifdef _MAPTOOL`이 있던 클래스는 분기 제거
  - SkyBox는 배치 대상은 아니지만, 이때 텍스처를 `Get_Or_Load_Texture`로 바꾸면 Level의 `Proto::Texture_SkyBox` 수동 등록 제거 가능

**완료 기준**: 옮긴 클래스가 툴과 게임 양쪽에서 같은 코드로 동작한다.

---

## 10단계. 모델(fbx)로 전환 — 모델 로드를 익힌 뒤

**목표**: `strMeshPath`에 fbx 경로를 넣으면 모델이 그려진다. 기존 `builtin/` 맵 파일도 그대로 읽힌다.

- [ ] 엔진의 모델 로딩 확인 (Assimp, `Material.h`)
- [ ] `Get_Or_Load_Model(레벨, 경로)` 추가 (3단계 캐시와 같은 방식)
- [ ] `CStaticProp::Ready_Mesh`의 else 블록 채우기
- [ ] `Render_Model()` 작성 — 모델은 **메시 여러 개 + 메시별 머티리얼**이라 메시 단위로 반복
- [ ] 모델용 정점 형식(탄젠트 등)에 맞는 셰이더 준비
- [ ] `Change_Mesh`에서 모델 경로면 `Com_Buffer` 대신 모델 컴포넌트로 교체
- [ ] 툴 메시 목록(`s_Meshes`)에 fbx 추가 (많아지면 폴더 스캔 + `vector`로 전환)

**완료 기준**: 큐브와 모델이 한 맵에 섞여 있어도 저장/불러오기가 된다.

---

## 9단계. 확장 (선택)

- [ ] 피킹 (씬 이미지 좌표 → NDC → 레이, `Compute_PickingRay`에 NDC 오버로드 추가)
- [ ] 기즈모 (ImGuizmo, W/E/R)
- [ ] 복제 (Ctrl+D), 실행 취소
- [ ] 모델 미리보기 / 에셋 창
- [ ] 필요해지면 데이터 주도 구조(CEntity + 컴포넌트)를 배치 목록의 한 종류로 추가

---

## 메모

- 회전은 행렬이 아니라 **각도(도)로 저장** — 행렬에서 다시 뽑으면 값이 튐
- Engine 헤더 수정 → **Engine 빌드 먼저** → MapTool / Client 빌드
- 툴 전용 코드(ImGui)는 MapTool에만. Engine과 Client 클래스에는 넣지 않기
- 텍스처 원형 직접 등록이 필요 없는 건 **`Get_Or_Load`를 쓰는 클래스뿐** (지금은 StaticProp). 기존 Client 클래스는 옮기기 전까지 직접 등록
- 툴 프레임 순서: `CEditorUI::Update`(ImGui) → `Update_Engine`(Remove_Dead → Update…) → `Draw` — ImGui에서 `Set_Dead` 하면 같은 프레임에 사라짐
