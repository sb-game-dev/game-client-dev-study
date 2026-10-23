# Duckov 인벤토리 리소스 모음

Escape from Duckov 원본(`Duckov_Data`)에서 UnityPy로 추출한 것과, 프로젝트 곳곳에 흩어져 있던 인벤토리 관련 파일을 한곳에 모은 폴더 (2026-10-23).
개인 학습용. 저장소/배포 금지.

## 핵심 요약 (먼저 읽을 것)

- 인벤토리 UI는 `resources.assets`의 `LevelManager/GameplayUICanvas` 아래에 있다.
  캔버스 기준 해상도는 **2560x1440**이고 CanvasScaler match=1(높이 기준)이다. 아래 숫자는 모두 이 해상도 기준 픽셀이다.
- **슬롯 칸은 9-slice 스프라이트가 아니다.** `ProceduralImage`(셰이더로 그리는 둥근 사각형)로 그린다. 인벤토리 UI에서 601곳이 이 방식이다.
  필요한 값은 **크기, 모서리 반지름, 테두리 두께(0이면 채움), 색** 네 가지뿐이다.
  9-slice 스프라이트(`Rect16`, `Frame_Basic_Rectangle` 등)는 타이틀바, 스크롤 프레임처럼 일부에만 쓴다.
- 아이콘 주위의 등급 색 테두리는 `TrueShadow`(아이콘 알파를 블러해 색을 입힌 글로우)다. 색은 `quality_colors.csv` 참고.

### 인벤토리 칸 (InventoryEntry 프리팹, `Layout/10_Prefab_InventoryEntry.txt`)

| 레이어 | 크기 | 모양 | 색 (RGBA) |
|---|---|---|---|
| 칸 전체 | 120x120 | - | - |
| ItemDisplay | 칸 - 8 (112x112) | - | - |
| BG | ItemDisplay와 같음 | 채움, radius 16 | `#00000033` |
| Frame | 〃 | 테두리 2px, radius 16 | `#FFFFFF4C` |
| Hovering (마우스 오버) | 〃 | 채움, radius 16 | `#FFFFFF0D` |
| SelectionIndicator (선택) | 〃 | 테두리 3px, radius 16 + 그림자 | `#FF9E3AFF` |
| Highlight | 칸 - 10 | 안쪽 글로우 size 15 | `#7AE58F` |
| DurabilityZero (내구도 0) | ItemDisplay와 같음 | 채움, radius 16 | `#FF000033` |
| Icon | ItemDisplay와 같음, 비율 유지 | 등급 글로우 size 3, spread 0.5 | - |
| 개수 텍스트 | 우하단 | 폰트 16, 자동 크기 | `#F8F2EA` |
| 이름 텍스트 | 하단 | 폰트 16 | `#FFFFFF` |
| 슬롯 표시 점 (부착물 칸) | 12x12, 간격 2 | 알약 모양, 검정 + 흰 점 | - |
| 내구도 바 | 40x12 | 알약 모양 | 색은 내구도에 따라 빨강 → 주황 → 파랑 |

### 그리드 (GridLayoutGroup)

| 용도 | 셀 | 간격 | 패딩 | 열 |
|---|---|---|---|---|
| 가방/보관함 인벤토리 | 120x120 | 0, 0 | L4 R4 T8 B8 | 5열 고정 |
| 장비 슬롯 (SlotDisplay) | 100x140 또는 90x120 | 25, 8 | T16 B4 | 유동 |
| 빠른 사용칸 (ShortcutEditor) | 110x110 | 16 (가로 정렬) | 8 | - |

- 인벤토리 창(InventoryView)의 왼쪽 패널(EquipmentAndInventory) 폭은 588이다. 가운데 상세 패널(ItemDetails)은 588 / 750이다.
- 패널 배경은 `TranslucentImage`(뒤를 블러하는 반투명 배경)를 쓴다. 틴트 색은 주로 `#325978`(진한 파랑)이고, `#5491B7`, `#575757`, `#000000`도 쓴다. 그림자는 검정 60%, 거리 8이다.

## 폴더 구성

```
Inventory/
  README.md                       이 파일
  preview_inventory_grid.png      추출한 값으로 다시 그린 5열 인벤토리 미리보기 (검증용)
  items.csv                       아이템 1570개 데이터 (아래 설명)
  quality_colors.csv              등급별 아이콘 글로우 색
  Layout/                         UI 계층 덤프 (RectTransform + 컴포넌트)
    *.txt                           사람이 읽는 트리
    *.json                          모든 필드를 담은 원본 트리
    GameplayDataSettings_uiStyle.json  등급 색 원본
  Sprites/
    ui_sprites_9slice.csv           인벤토리 UI가 실제로 참조하는 스프라이트 46개 + 9-slice 값 + 사용 위치
    all_sliced_sprites_9slice.csv   게임 전체에서 9-slice 값이 있는 스프라이트 16개
    UI/                             위 46개 PNG (아틀라스에서 잘라낸 것)
    UI_Other/                       인벤토리에서는 안 쓰지만 9-slice가 있는 UI 도형 (Rounded Rect, Panel 등)
    Picto/                          PictoIcon_* 31개 (흰색 실루엣, 장비칸/카테고리용)
    Status/                         무게 상태 버프 아이콘, 가방 용량/최대 무게 퍽 아이콘
    Items/                          아이템 아이콘 ("<typeID>_<스프라이트명>.png", items.csv의 icon 열과 매칭)
  Sound/                          가방 열기/닫기, 아이템 줍기/장착/판매, UI 확인/취소/호버 (WAV 31개)
  Font/                           ResourceHanRoundedCN-Medium.ttf (UI 기본 폰트)
  _scripts/                       추출에 쓴 파이썬 스크립트 (UnityPy + TypeTreeGeneratorAPI)
```

## Layout 파일 읽는 법

```
Frame  a[0.0, 0.0]-[1.0, 1.0] pos[0.0, 0.0] size[0.0, 0.0] pv[0.5, 0.5]
    · ProceduralImage[outline 2px #FFFFFF4C falloff=1.0]
    ·   └ 모서리 radius=16.0
```

- `a[min]-[max]` = 앵커, `pos` = anchoredPosition, `size` = sizeDelta, `pv` = 피벗. 유니티 UI 좌표라 **y가 위로 증가**한다.
- 앵커가 `[0,0]-[1,1]`이면 부모 크기를 따라가고, `size`는 부모 대비 더하고 빼는 값이다. 예를 들어 `size[-8,-8]`은 "부모보다 8 작게(사방 4씩)"라는 뜻이다.
- 레이아웃 그룹(Grid/Horizontal/Vertical) 아래 자식의 pos/size는 런타임에 다시 계산된다. 이 경우 덤프의 값보다 레이아웃 그룹 설정과 LayoutElement(Preferred 크기)를 믿을 것.
- `(off)` = 프리팹에서 비활성 상태인 오브젝트다. 상황에 따라 켜진다(선택, 내구도 0 등).
- 색은 `#RRGGBBAA`.
- `ProceduralImage[filled …]`는 채운 둥근 사각형이다. `outline Npx`는 테두리만 그린 사각형이다.
- `RoundModifier`는 radius = 짧은 변 / 2라서 알약 모양이 된다. `FreeModifier`는 네 모서리 반지름이 각각 다르다.
- `TrueShadow[drop …]`은 바깥 그림자이고, `inset`은 안쪽 글로우다. `blend=1`은 가산이다.

| 파일 | 내용 |
|---|---|
| 00_GameplayUICanvas_root | 캔버스 루트 (CanvasScaler 2560x1440). 하위는 이름만 표시 |
| 01_Tabs | 상단 탭 바 (인벤토리/지도/퀘스트…) |
| 02_InventoryView | 인벤토리 창 전체 (장비 + 가방 + 상세 + 빠른 사용칸 + 무게 바) |
| 03_LootView | 상자를 열었을 때의 루팅 창 (내 인벤토리 + 상대 인벤토리 + 필터) |
| 04_ItemDetails_Panel | 아이템 상세 패널 |
| 05_ItemOperationMenu | 우클릭 메뉴 (사용/버리기/분할 …) |
| 06_Tooltips | 툴팁 |
| 10~15_Prefab_* | 칸 단위 프리팹 (InventoryEntry, ItemDisplay, SlotDisplay, SlotIndicator 등) |

## 9-slice 값

`Sprites/*.csv`의 border 값 순서는 유니티 그대로 **L, B, R, T**(좌, 하, 우, 상, 픽셀)다. DirectX에서 쓸 때는 B와 T의 위치에 주의할 것.

| 스프라이트 | 크기 | border L,B,R,T | 인벤토리에서 쓰는 곳 |
|---|---|---|---|
| Rect16 | 64x64 | 17,17,17,17 | 인벤토리 타이틀바 (`#00000089`, 줄무늬 머티리얼 겹침), 페이지 버튼 |
| Frame_Basic_Rectangle | 59x61 | 29,31,30,30 | 장비+인벤토리 패널, 상세 패널 테두리 |
| UpFrameMask16 / DownFrameMask16 | 126x11 | 18,0,18,11 / 18,11,18,0 | 스크롤 영역 위/아래 테두리 |
| UISprite / Background | 32x32 | 10,10,10,10 | 가로 스크롤바 핸들 / 배경 |
| Slider01 | 18x30 | 9,15,9,15 | 세로 스크롤바 핸들 |
| procedural_ui_image_default_sprite | 4x4 | 없음 | ProceduralImage용 더미 (모양은 셰이더가 만든다) |

## items.csv 열

| 열 | 뜻 |
|---|---|
| typeID | 아이템 ID (아이콘 파일명 앞 숫자) |
| prefab | 프리팹 이름 |
| nameKey / name_ko / name_en / desc_ko | 로컬라이즈 키와 한국어·영어 이름, 한국어 설명 (StreamingAssets/Localization) |
| quality | 등급. 1~6은 `quality_colors.csv`의 색을 쓴다. 9/99/999 등은 특수 아이템(퀘스트, 재료 등)이다 |
| displayQuality | 표시용 등급 (대부분 0) |
| value / weight / maxStack | 가격, 무게(kg), 최대 겹침 수 |
| inventoryCapacity | 자체 인벤토리가 있는 아이템의 칸 수 |
| slots / slotKeys | 부착물/장비 슬롯 수와 이름 (총의 조준경, 탄창 등) |
| tags | 태그 (카테고리 필터용: Weapon, Gun, Bullet, Equipment, Helmat, Accessory, Key, Quest …) |
| icon | `Sprites/Items/` 안의 파일명 |

## 참고

- 등급 글로우의 색을 정하는 필드가 quality인지 displayQuality인지는 코드를 보지 않아 확실하지 않다. 미리보기는 quality로 그렸다.
- 타이틀바의 `RollingStripes_InventoryTitleBar` 머티리얼(흐르는 줄무늬)은 셰이더라 추출하지 않았다. 비슷한 텍스처로 `Sprites/UI/Stripes.png`가 있다.
- 원본 `Resource_100/MonoBehaviour/Inventory*.json` 등은 컴포넌트 값만 있고 계층·크기 정보가 없다. 이 폴더의 Layout이 그것을 대신한다.
