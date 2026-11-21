# 플레이어 STATIC 레벨 이전 정리

## 0. 핵심 개념
- **원형(프로토타입) 레벨** = 설계도를 어디서 찾을지 / **사본의 레이어 레벨** = 객체의 수명
- `Change_Level` 시 **떠나는 레벨 칸**의 원형·사본만 Clear된다 (`Level_Manager.cpp:13`). STATIC(0)은 하나뿐이고 지워지지 않는다.
- `Object_Manager`는 `m_pLayers[레벨]` 배열 구조이며, **모든 레벨 칸을 매 프레임 Update/Render**한다 (`Object_Manager.cpp:47~`).
  → STATIC 사본은 로딩 중에도 돌아간다 → **켜고 끄는 장치가 필요**
- "STATIC 레이어"는 레벨마다 있는 게 아니라 `m_pLayers[STATIC]` **한 칸**을 모든 레벨이 공유하는 것이다.
- `Clone_Prototype`은 복제본에 `Set_LevelIndex(원형 레벨)`을 넣는다.
  → 파츠의 `m_iLevelIndex`가 STATIC이 되고, `Change_Model`의 `Has_Prototype(m_iLevelIndex, ...)`이 STATIC에서 모델을 찾으므로 **장비 모델도 STATIC에 있어야 한다.**

```
m_pLayers[0] (STATIC)   → { "Layer_Player" : Player, Inven, HUD ... }  ← 하나뿐, 지워지지 않음
m_pLayers[1] (LOADING)  → { "Layer_BackGround" : ... }
m_pLayers[2] (LOGO)     → { ... }
m_pLayers[3] (GAMEPLAY) → { "Layer_GameObject" : Hill, SkyBox ... }
```

---

## 1. STATIC으로 옮길 원형 (`CMainApp::Ready_Prototype_For_StaticLV`)

| 종류 | 항목 |
|---|---|
| 객체 | Player, Player_Body, Weapon, Helmet, Armor, BackPack, Headset, FaceMask, Inven, HUD, Client_Mouse, Scope |
| 모델 | Model_Duck, Weapon(AK47/M700/PM/Axe), Helmet LV2/3, Armor LV2/3, BackPack LV2/3, Headset LV0/1, FaceMask(FlyMask/GasMask/NightVision) |
| 셰이더 | **전부** (VS/PS_MODEL, VS_ANIM_MODEL, PS_VTXCOL_SHADOW/OCCLUDED, UI 계열, VTXTEX 계열, TERRAIN, MODEL_INSTANCE …) |
| 버퍼 | VIBuffer_Rect, VIBuffer_Cube, VIBuffer_SkyBox |
| 텍스처 | Texture_Mouse, Texture_ItemIcons, Texture_HUDIcons |

> 셰이더를 전부 STATIC에 두는 이유: VS_MODEL/PS_MODEL처럼 STATIC 객체와 레벨 객체가 공용으로 쓰는 것이 많다.
> 한쪽에만 두면 다른 쪽이 못 찾고, 양쪽에 두면 같은 셰이더를 두 번 컴파일하게 된다.

## 2. 레벨(GAMEPLAY 등)에 남길 원형 (`Loader`)

| 종류 | 항목 |
|---|---|
| 객체 | QuaterViewCam, Hill, SkyBox, Fog, Mirror, Cube, Cube_Instance, Tree_Instance, StaticProp |
| 모델 | Tree_01, Boss_Wu, Container(Back/Ceiling/Ground/L/R) |
| 버퍼 | VIBuffer_Terrain |
| 텍스처 | Hill, splat_0, Layer%d, SkyBox, Cube, Mirror |
| 그대로 | BackGround (LOGO / LOADING) |

---

## 3. 등록 순서
- `MainApp.cpp:45`: `Ready_Prototype_For_StaticLV()`를 `Start_Level` **앞으로** 옮긴다.
  - 로더 서브 스레드와 프로토타입 맵을 동시에 건드리는 문제(스레드 안전 X)를 막는다.
  - 레벨이 STATIC 원형을 필요로 하기 전에 등록을 끝낸다.
- Loader에서는 STATIC으로 옮긴 항목을 삭제한다. `Add_Prototype`은 중복 태그면 E_FAIL을 반환한다.
- `Level_Loading.cpp:79, 88`에서 LOADING에 따로 등록하던 Rect/NOLIGHT는 STATIC 것을 사용하도록 정리해도 된다.

---

## 4. 레벨 인자 수정

### `Add_Component` → STATIC
- Body_Player(169~196), 장비 파츠 6종(124~134), Inven(311~319), HUD(322~342), Scope(112~120), Client_Mouse(236~244)
- 공용 셰이더·버퍼를 쓰는 레벨 객체: Tree_Instance(76~80), Mirror(89~97), SkyBox(88~105), Cube 계열
- **StaticProp.cpp:89, 93**: 셰이더만 `LEVEL::STATIC`으로 고정한다. 모델(77)은 `m_iLevelIndex` 그대로 둔다.

### `Add_PartObject` → STATIC
- `Player.cpp:105~148` (7개)

### `Add_GameObject`
- Level_GamePlay의 Player, Inven, HUD, Mouse, Scope → **원형 레벨과 레이어 레벨 모두 STATIC**

### `Find_GameObject`
- Player/Inven/Mouse를 찾는 곳 → **STATIC**
  - Player(52, 264, 447), 각 파츠(51), HUD(91, 99), Scope(61, 70), Client_Mouse(114, 122), QuarterView_Cam(34, 69, 80, 89), Level_GamePlay(127)
- Hill을 찾는 곳 → **GAMEPLAY 유지**
  - Player(161), Tree_Instance(96, 139)

---

## 5. 활성 플래그 (엔진)
- `GameObject`: `m_bActive`, `Set_Active()`, `Is_Active()` 추가 (`m_bDead`와 같은 방식)
- (권장) `Layer`: 활성 플래그를 두고, STATIC 객체를 `L"Layer_Player"` 같은 전용 태그에 모아 한 번에 끄고 켠다.
  - `Set_LayerActive(STATIC, L"Layer_Player", false)` 한 줄로 처리
- Layer / Object_Manager 루프에서 비활성 객체나 레이어는 Priority/Update/Late_Update를 건너뛴다.
  - Late_Update를 건너뛰면 렌더 그룹에도 등록되지 않는다.
- 파츠는 Player의 Update 안에서 갱신되므로 Player만 끄면 같이 꺼진다.

---

## 6. 레벨별 Initialize에서 할 일
레벨 전환 흐름은 `Create(→Initialize)` 다음 `Change_Level(→이전 레벨 Clear)` 순서다 (`Level_Loading.cpp:49~53`). 같은 Update 안에서 일어나므로 프레임이 비는 틈이 없다.

| 레벨 | 처리 |
|---|---|
| Loading / Logo / MapTool | STATIC 플레이어 계열 **비활성화** |
| GamePlay (플레이어가 등장하는 레벨) | Player가 **없으면 생성, 있으면 활성화**. 이어서 스폰 위치 재설정, 캐싱한 레벨 객체 참조(Hill 등) 재조회, 입력(`m_tInput`)·이전 프레임 플래그(`m_bPreInvenOpen` 등) 초기화 |

```cpp
// 생성 가드 예시 흐름
auto pPlayer = Find_GameObject(STATIC, L"Layer_Player", GO::Player);
if (nullptr == pPlayer)
    Add_GameObject(STATIC, Proto::Obj_Player, STATIC, L"Layer_Player", GO::Player, &Desc); // 최초 1회 생성
else
{
    pPlayer->Set_Active(true);   // 재진입 시 활성화
    // 위치 재설정, 상태 초기화
}
```

---

## 7. 따로 챙길 것
- **조명**: `Level_GamePlay.cpp:131~140`의 Player_PointLight, Player_SpotLight, SunLight는 Light_Manager 소속이라 레벨 Clear와 관계가 없다.
  - 다시 진입할 때 같은 이름으로 중복 추가되거나, 로딩 중에 남아 있을 수 있다.
  - 레벨이 끝날 때 제거할지, 한 번만 추가하고 켜고 끄기만 할지 정해야 한다.
- **카메라(QuaterViewCam)**: 레벨 객체로 두고, 레벨마다 STATIC에 있는 Player를 다시 찾아 연결한다.
- **null 처리**: STATIC 객체가 레벨 객체(Hill, Mirror 등)를 참조하는 곳은, 객체가 없을 때 안전하게 넘어가도록 만든다.

---

## 작업 순서 추천
1. 엔진에 활성 플래그 추가 (Layer 또는 GameObject)
2. 셰이더, 버퍼, 공용 텍스처를 STATIC으로 이전하고 `Add_Component` 인자 수정 → 한 번 실행해서 확인
3. 플레이어 관련 모델과 객체 원형을 STATIC으로 이전하고 `Add_PartObject` / `Find_GameObject` 인자 수정
4. Level_GamePlay에서 사본을 STATIC에 생성(한 번만 생성하는 가드 포함)하고, 각 레벨 Initialize에 Active 관리 추가
5. 조명 처리 정리
