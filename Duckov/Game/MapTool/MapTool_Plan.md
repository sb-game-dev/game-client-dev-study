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
- [ ] 카메라 정리 (직접 진행 중)
  - [ ] `CCamera::Render`에 `return S_OK;` 추가 (Engine/Private/Camera.cpp)
  - [ ] Level_MapTool.cpp 65~67줄 (초기화 안 된 카메라 등록) 삭제
  - [ ] 마우스 회전에서 `fDeltaTime` 곱하기 제거
  - [ ] Scene 이미지 비율을 가로/세로 모두 맞추기 + `cout` 제거 (Tool.cpp)
  - [ ] (권장) 우클릭을 씬 위에서 시작했을 때만 드래그 / `Update_PipeLines` 매 프레임 / 피치 제한

---

## 1단계. VIBuffer로 큐브 하나 띄우기 (모델은 나중에)

**목표**: 내장 VIBuffer(Cube) + 텍스처로 그린 객체가 툴의 Scene 창에 보인다.

- [ ] `CCube::Render_Mesh`의 순서(상수버퍼 → 셰이더 → 텍스처 → 버퍼)를 참고해서 그리기
- [ ] 셰이더는 `Shader_VtxTex.hlsl` (VTXNORM용) 사용
- [ ] 내장 메시는 cube, rect만 사용 (pyramid는 VTXCOL이라 텍스처 셰이더와 맞지 않음)
- [ ] Level_MapTool에서 코드로 하나 생성해서 확인

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

- [ ] `MAP_OBJECT_DESC` 정의
- [ ] `CMapObject` (abstract, `CGameObject` 상속) 생성
  - [ ] Initialize에서 위치/회전/크기 → Transform 적용
  - [ ] 위치/회전/크기 값을 멤버로 보관 (인스펙터 편집, 저장용. 행렬에서 다시 뽑지 않기)
  - [ ] `virtual void Save_Extra(ofstream&) const {}` / `virtual void Load_Extra(ifstream&, MAP_OBJECT_DESC&) {}`
- [ ] Transform에 Euler 회전(도) → 행렬 적용 함수 확인 또는 추가

**완료 기준**: `CMapObject`를 상속한 테스트 객체가 DESC 값대로 위치/회전/크기가 잡힌다.

---

## 3단계. CStaticProp + 에셋 캐시

**목표**: 클래스 하나로 모든 구조물을 표현한다. 같은 메시/텍스처는 한 번만 로드한다.

- [ ] `CStaticProp : CMapObject` 생성 (Client)
  - [ ] 메시를 만드는 곳은 `Ready_Mesh()` 한 함수로: `"builtin/"`이면 VIBuffer + 텍스처, 아니면 (지금은) 실패
  - [ ] `Render()`도 분기: `m_pModel`이 있으면 `Render_Model()`(나중), 없으면 `Render_Buffer()`
  - [ ] `Late_Update`에서 `Add_RenderGroup(NONALPHA)` (처음엔 컬링 끄기)
- [ ] 에셋 캐시: "경로로 찾고, 없으면 로드"
  - [ ] `Prototype_Manager`에 `Has_Prototype` 추가 (`Find_Prototype`이 private이라)
  - [ ] 경로 정규화 (`\` → `/`, 소문자, Resource 기준 상대 경로)
  - [ ] `Get_Or_Load_Texture(레벨, 경로)`, `Get_Or_Load_Mesh(레벨, "builtin/cube")` : 확인 → 없으면 생성 + `Add_Prototype` → Clone
  - [ ] Device가 필요한 곳 결정 (추천: `CAsset_Manager::Create(pDevice, pContext, Prototype_Manager*)`)
- [ ] 프로토타입 `Proto::Obj_StaticProp` 등록

**주의**
- `Add_Prototype`은 중복이면 `E_FAIL` → 반드시 "확인 → 생성 → 등록" 순서
- 없는 경로를 매 프레임 요청하지 않기 (실패하면 메시지 박스)
- Engine 헤더 수정 후에는 **Engine 먼저 빌드** (EngineSDK로 복사됨)

**완료 기준**: 같은 모델의 StaticProp 여러 개를 생성해도 로드는 한 번만 일어난다.

---

## 4단계. 툴: 배치 (하이어라키)

**목표**: 툴에서 클릭으로 객체를 만들고, 고르고, 지운다.

- [ ] 배치 가능한 목록: `{ 표시 이름, 프로토타입 태그 }` 배열
- [ ] 메시 목록: 지금은 `builtin/cube`, `builtin/rect` (10단계 이후 fbx 추가)
- [ ] 텍스처 선택: 경로 입력 또는 파일 대화상자
- [ ] Hierarchy 창
  - [ ] 생성: 목록에서 골라 `Add_GameObject` (StaticProp이면 모델 경로 포함)
  - [ ] 선택: `Selectable`로 목록 표시, 선택 객체 보관 (`weak_ptr`)
  - [ ] 삭제: Layer에 `Remove_GameObject` 추가 (Update 중 삭제 주의 → Dead 표시 후 정리)
- [ ] Layer 태그는 고유하게 (`Prop_0`, `Prop_1` …) — `CLayer::Add_GameObject`는 중복 태그를 **조용히 무시**함
- [ ] Layer에 객체 목록 조회 함수 추가 (Hierarchy 표시용)

**완료 기준**: 같은 모델을 여러 개 배치해도 전부 보이고, 선택과 삭제가 된다.

---

## 5단계. 툴: Transform 편집 (인스펙터)

**목표**: 선택한 객체의 위치/회전/크기를 편집한다.

- [ ] Inspector에 이름, 태그, 모델 경로 표시
- [ ] `DragFloat3` × 3 (위치 / 회전 / 크기) → 값이 바뀌면 Transform 다시 적용
- [ ] (선택) 지형 높이에 스냅하는 버튼

**완료 기준**: 인스펙터 값을 바꾸면 Scene 창에서 바로 움직인다.

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
- [ ] `Save_Map(경로)` / `Load_Map(레벨, 경로, 레이어)` — **툴과 Client가 같이 쓰도록** 공용 위치에 두기
- [ ] 메뉴바 연결: New / Open / Save / Save As
- [ ] 파일 대화상자 (`GetSaveFileName` / `GetOpenFileName`, `OFN_NOCHANGEDIR` 필수)
- [ ] 경로는 Resource 기준 상대 경로로 저장 (절대 경로 저장 금지)

**완료 기준**: 저장 → New → Open 하면 같은 배치가 같은 자리에 복원된다.

---

## 7단계. Client에서 불러오기

**목표**: 툴에서 만든 맵이 게임에 그대로 나온다.

- [ ] Level_GamePlay에서 프로토타입 등록 (같은 태그)
- [ ] `Load_Map(ETOUI(LEVEL::GAMEPLAY), L"…/Stage1.map", L"Layer_Map")`
- [ ] 카메라, UI, 조명, 플레이어는 기존처럼 코드에서 생성

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

**완료 기준**: 옮긴 클래스가 툴과 게임 양쪽에서 같은 코드로 동작한다.

---

## 10단계. 모델(fbx)로 전환 — 모델 로드를 익힌 뒤

**목표**: `strMeshPath`에 fbx 경로를 넣으면 모델이 그려진다. 기존 `builtin/` 맵 파일도 그대로 읽힌다.

- [ ] 엔진의 모델 로딩 확인 (Assimp, `Material.h`)
- [ ] `Get_Or_Load_Model(레벨, 경로)` 추가 (3단계 캐시와 같은 방식)
- [ ] `CStaticProp::Ready_Mesh`의 else 블록 채우기
- [ ] `Render_Model()` 작성 — 모델은 **메시 여러 개 + 메시별 머티리얼**이라 메시 단위로 반복
- [ ] 모델용 정점 형식(탄젠트 등)에 맞는 셰이더 준비
- [ ] 툴 메시 목록에 Resource/Model 폴더의 fbx 추가

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
