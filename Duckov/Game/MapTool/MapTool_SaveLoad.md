# MapTool 저장 / 불러오기 설계

> 방향
> - 이번 맵 파일에는 **지형을 뺀, 움직이지 않는 장식물**(`CStaticProp`)만 담는다
> - 레이어를 나눈다: `Layer_Terrain` / `Layer_Prop`
> - **원본(프로토타입)은 Client `Loader`가 미리 준비**한다. 맵 파일은 **사본을 만들 정보**만 가진다
> - 같은 저장/로드 코드를 **Client와 MapTool이 함께** 쓴다

---

## 1. 무엇을 저장하나

### `MAPOBJECT_DESC` 필드 정리

| 필드 | 저장 | 이유 |
|---|---|---|
| `strPrototypeTag` (**새로 추가**) | O | 로드할 때 어떤 프로토타입을 Clone할지, 어떤 DESC/`Read_Extra`를 쓸지 결정 |
| `vPosition` | O | 위치 |
| `vQuaternion` | O | 회전의 원본 값 (Transform, 저장 모두 이 값 기준) |
| `vScale` | O | 크기 |
| `strMeshPath` | O | 모델 컴포넌트 키 (`Normalize_AssetPath`) |
| `strTexturePath` | O | 텍스처 경로 |
| `iLevelIndex` | **X** | 로드하는 쪽이 정함 (Client = `GAMEPLAY`, 툴 = `MAPTOOL`) |
| `bEditorMode` | **X** | 로드하는 쪽이 정함 (Client = `false`, 툴 = `true`) |
| `GAMEOBJECT_DESC`(`TRANSFORM_DESC`)의 속도, `fPosX` 등 | **X** | 위치는 `vPosition`과 겹치고, 속도는 맵 데이터가 아님 |
| `m_vEulerHint` | **X** | Inspector 표시용. 로드할 때 쿼터니언에서 다시 계산 |

DESC에는 없지만 저장할 것:
- **객체 이름** (`"Prop_3"` 같은 GameObject 태그) → `Add_GameObject`에 따로 넘기는 인자. Hierarchy에 같은 이름을 다시 보여 주려고 저장한다

### 자식 DESC 고유 필드
- `STATICPROP_DESC`: 없음 → 공통 필드만 저장
- `HILL_DESC::strLayerPath`: 있음 → 지형은 이번 파일에서 빠지므로 **나중에 지형 파일을 따로 만들 때** 사용

---

## 2. Extra 함수 통일: `Read_Extra` 방식

**저장 = 가상 멤버 `Save_Extra`, 읽기 = static `Read_Extra(ifstream&, 자식_DESC&)`**
→ `CMapObject::Load_Extra`는 삭제

| | 저장할 때 | 읽을 때 |
|---|---|---|
| 객체가 있나 | 있음 | **아직 없음** (DESC를 채운 뒤에 생성) |
| 방법 | 가상함수 → 다형성 | 프로토타입 태그를 보고 해당 타입의 static 함수를 직접 호출 |

멤버 함수 `Load_Extra(ifstream&, MAPOBJECT_DESC&)`가 안 맞는 이유
1. 읽는 시점에는 객체가 없어서 멤버 함수를 부를 수 없다
2. 베이스 DESC로는 자식 필드(`strLayerPath` 등)에 접근할 수 없어 캐스팅이 필요하다

```cpp
// MapObject.h
virtual void Save_Extra(ofstream& Out) const {}
// Load_Extra 삭제
```
- 베이스에는 저장 쪽 훅만 남긴다. 추가 데이터가 없는 `CStaticProp`은 오버라이드하지 않는다

```cpp
// Hill.h (현재 형태 유지)
virtual void Save_Extra(ofstream& Out) const override;
static  void Read_Extra(ifstream& In, HILL_DESC& Desc);
```
- 자식 클래스는 두 함수를 짝으로 가진다. **쓰는 순서와 읽는 순서만 맞추면 된다**

---

## 3. 프로토타입 태그를 DESC에 추가

```cpp
// MapObject.h - MAPOBJECT_DESC
wstring_t strPrototypeTag;   // Proto::Obj_StaticProp 등
```
- 저장 데이터와 생성 인자가 같은 구조체 하나로 맞춰진다
- 로드할 때 `Add_GameObject(..., Desc.strPrototypeTag, ..., &Desc)`로 바로 생성할 수 있다

```cpp
// MapObject.h - 멤버 + Getter
wstring_t m_strPrototypeTag;
const wstring_t& Get_PrototypeTag() const { return m_strPrototypeTag; }

// MapObject.cpp - Initialize
m_strPrototypeTag = pDesc->strPrototypeTag;
```
- 저장할 때 객체에서 값을 꺼내야 하므로 멤버로 보관한다 (위치, 메시 경로와 같은 방식)

**주의:** 맵툴에서 객체를 만드는 곳에서 반드시 채운다
- `CPanel_Hierarchy::Create_StaticProp(pPrototypeTag)` → `Desc.strPrototypeTag = pPrototypeTag;`
- 비어 있으면 저장은 되지만 로드할 때 생성이 실패한다

---

## 4. 레이어 분리

```cpp
// Client_Tags.h - namespace Layer
inline constexpr const wchar_t* Terrain = L"Layer_Terrain";
inline constexpr const wchar_t* Prop    = L"Layer_Prop";
```
- 지금은 Hill과 Prop을 모두 `TEXT("Layer_Map")`에 넣고 있다 → 둘로 나눈다
- 저장할 때 `Get_GameObjects(레벨, Layer::Prop)`만 돌면 되니까 지형을 걸러내는 코드가 필요 없다
- `Client_Tags.h`에 두면 Client와 MapTool이 같은 문자열을 쓴다. 하드코딩된 `TEXT("Layer_Map")`도 이 상수로 바꾼다

---

## 5. 원본은 Client Loader에서 준비

현재 상태: Client `Loader.cpp`에는 `Proto::Obj_StaticProp`도, 맵툴에서 쓰는 모델 프로토타입도 **없다** (`Loader_MapTool.cpp`에만 있음)

해야 할 일
1. `CStaticProp::Create(...)`를 `Proto::Obj_StaticProp`으로 `LEVEL::GAMEPLAY`에 등록
2. 모델 프로토타입을 **맵툴과 똑같은 키**(`Normalize_AssetPath(경로)`)로 등록
   - `CStaticProp`은 저장된 `strMeshPath`를 정규화해서 컴포넌트 키로 쓴다 → 키가 다르면 Client에서 `Add_Component` 실패

### 모델 목록을 표 하나로 공유

```cpp
// Client 쪽 공용 헤더 (Client_Tags.h 등)
struct MODEL_ENTRY { const wchar_t* pKey; const char* pBinPath; };
inline constexpr MODEL_ENTRY g_PropModels[] = {
    { L"Characters/0_CharacterModel_Boss_Wu/0_CharacterModel_Boss_Wu.fbx",
      "../../../Resource/Characters/0_CharacterModel_Boss_Wu/0_CharacterModel_Boss_Wu.bin" },
    // ...
};
```
- 두 Loader가 같은 표를 돌며 등록한다. 레벨 인자만 `GAMEPLAY` / `MAPTOOL`로 다르다
- 맵툴 Inspector 콤보의 `g_Models`도 이 표로 채운다 → "툴에서 고를 수 있는 모델 = Client가 로드하는 모델"이 항상 같게 유지된다
- `Client/Bin`과 `MapTool/Bin`은 깊이가 같아서 `../../../Resource` 상대경로를 양쪽에서 그대로 쓸 수 있다

---

## 6. 저장 / 로드 코드 (Client와 MapTool 공용)

- MapTool이 Client의 cpp를 같이 컴파일하고 있다 (`Hill.obj`, `Cube.obj` 등)
- → `MapData.h / .cpp`를 **Client 쪽에 한 번만 작성**하고 MapTool 프로젝트에도 추가한다

### 파일 구조

```
[uint32 Version] [uint32 Count]
반복 Count번:
  [wstr PrototypeTag] [wstr ObjectTag]
  [float3 Pos] [float4 Quat] [float3 Scale]
  [wstr MeshPath] [wstr TexturePath]
  [Extra...]
```
- `Version`: 나중에 필드가 추가됐을 때 예전 파일을 구분하는 용도
- `Count`: 읽는 쪽이 반복 횟수를 알 수 있다
- `wstr`: **길이(uint32) → `wchar_t` × 길이**. 헬퍼(`Write_WString` / `Read_WString`) 두 개를 만들어 쓴다 (모델 바이너리화와 같은 방식)

### 저장 (맵툴만 사용)

```cpp
HRESULT Save_Map(const wstring_t& strFile, uint32_t iLevel, const wstring_t& strLayer)
{
    auto pObjects = CGameInstance::Get().Get_GameObjects(iLevel, strLayer);
    // 1) Is_Dead가 아니고 CMapObject로 캐스팅되는 것만 골라 개수 세기
    // 2) Version, Count 쓰기
    // 3) 객체마다: PrototypeTag, map의 key(ObjectTag), Pos/Quat/Scale, Mesh/Tex, Save_Extra(Out)
}
```
- `Get_GameObjects`가 `map<tag, 객체>`를 돌려준다 → map의 key가 곧 저장할 객체 이름
- 지워진 객체가 map에 남아 있을 수 있으니 **개수를 먼저 센다**. `Count`와 실제로 쓴 개수가 다르면 로드가 깨진다

### 로드 (양쪽 모두 사용)

```cpp
HRESULT Load_Map(const wstring_t& strFile, uint32_t iLevel, const wstring_t& strLayer, bool_t bEditorMode)
{
    // Count만큼 반복:
    //   PrototypeTag, ObjectTag 읽기
    //   if (PrototypeTag == Proto::Obj_StaticProp) { STATICPROP_DESC Desc; 공통 필드 읽기 }
    //   (타입이 늘어나면 else if로 X::Read_Extra(In, Desc) 추가)
    //   Desc.strPrototypeTag = PrototypeTag;
    //   Desc.iLevelIndex = iLevel;  Desc.bEditorMode = bEditorMode;
    //   Add_GameObject(iLevel, PrototypeTag, iLevel, strLayer, ObjectTag, &Desc);
}
```
- 태그를 **먼저** 읽어서 어떤 DESC 타입을 만들지, 어떤 `Read_Extra`를 부를지 정한다 (2번에서 static으로 통일한 이유)
- `iLevelIndex`, `bEditorMode`는 파일에서 읽지 않고 **호출하는 쪽이 넣어 준다**

| 호출하는 곳 | 호출 |
|---|---|
| Client `Level_GamePlay::Ready_Layer_...` | `Load_Map(path, GAMEPLAY, Layer::Prop, false)` |
| MapTool Hierarchy의 Load 메뉴 | `Load_Map(path, MAPTOOL, Layer::Prop, true)` |

---

## 7. 맵툴에서 로드할 때 주의할 점

- [ ] 다시 로드하기 전에 `Layer::Prop`의 기존 객체를 지우고 `m_Context.Clear_Selection()` 호출 → 같은 태그 때문에 `Add_GameObject` 실패 방지
- [ ] 로드한 이름 중 가장 큰 `Prop_N`보다 크게 `m_iNextID` 갱신 (`Create_StaticProp`이 중복 검사를 하긴 하지만, 미리 맞춰 두면 그 반복이 필요 없다)
- [ ] 로드한 쿼터니언으로 `m_vEulerHint`를 다시 계산해서 Inspector 표시 맞추기

---

## 작업 체크리스트

- [ ] `MAPOBJECT_DESC`에 `strPrototypeTag` 추가 + 멤버/Getter + `Initialize`에서 복사
- [ ] `CMapObject::Load_Extra` 삭제 (`Save_Extra` + static `Read_Extra`로 통일)
- [ ] `Client_Tags.h`에 `Layer::Terrain`, `Layer::Prop` 추가, `TEXT("Layer_Map")` 교체
- [ ] `Create_StaticProp` / `Create_Hill`에서 `strPrototypeTag` 채우기
- [ ] 공용 모델 표(`g_PropModels`) 만들고 두 Loader + `g_Models`가 같이 사용
- [ ] Client `Loader`에 `Proto::Obj_StaticProp` + 모델 프로토타입 등록 (`LEVEL::GAMEPLAY`)
- [ ] `MapData.h/.cpp` 작성 (`Write_WString` / `Read_WString`, `Save_Map`, `Load_Map`), MapTool 프로젝트에도 추가
- [ ] MapTool Hierarchy에 Save / Load 메뉴
- [ ] Client `Level_GamePlay`에서 `Load_Map` 호출
