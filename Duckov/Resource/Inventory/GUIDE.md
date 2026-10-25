# Duckov 인벤토리 구현 가이드 (DX11 인스턴싱)

2026-10-23 작업 정리. 다른 컴퓨터에서 이어서 작업할 때 이 문서부터 읽을 것.
대상 프로젝트: `Duckov/Game` (Engine + Client, 창 1280x720)

---

## 목차

1. [원작에서 확인한 사실](#1-원작에서-확인한-사실)
2. [이 폴더에 있는 것](#2-이-폴더에-있는-것)
3. [설계 개요](#3-설계-개요)
4. [단계별 구현](#4-단계별-구현) (1~10단계)
5. [배치 수치 (1280x720)](#5-배치-수치-1280x720)
6. [추출/미리보기 스크립트 다시 돌리기](#6-추출미리보기-스크립트-다시-돌리기)

---

## 1. 원작에서 확인한 사실

- 인벤토리 UI는 `Duckov_Data/resources.assets`의 `LevelManager/GameplayUICanvas` 아래에 있다. 기준 해상도는 **2560x1440**이고 CanvasScaler match=1(높이 기준)이다.
  → 우리 창 1280x720은 **정확히 절반**이다. 추출한 수치를 전부 x0.5 하면 된다.
- **Tab 인벤토리는 `InventoryView`가 아니라 `LootView`다.** 상단 가방 탭 버튼이 `viewTypeName = "LootView"`로 연결되어 있다. `InventoryView`는 평소에 꺼져 있는 별도 창이다.
  - LootView 구성: 장비 10칸, 가방 그리드, 펫 칸, 소지 중량 바, 아이템 상세(가운데), 퀵슬롯(하단). 상자를 열면 오른쪽에 LootTarget(상자 인벤토리 + 필터)이 추가된다.
- **슬롯 칸은 9-slice 스프라이트가 아니다.** `ProceduralImage`(셰이더로 그리는 둥근 사각형)를 쓰고, 인벤토리 UI에서 601곳이 이 방식이다. 필요한 값은 크기, 모서리 반지름, 테두리 두께, 색뿐이다.
  9-slice 스프라이트(`Rect16`, `Frame_Basic_Rectangle`, `Slider01` 등)는 타이틀바, 패널 테두리, 스크롤바에만 쓴다.
- 아이콘 주위의 등급 색 테두리는 `TrueShadow`(아이콘 알파를 블러해 색을 입힌 글로우)다. 색은 `quality_colors.csv` 참고.
- 장비 슬롯 순서는 원작과 `Client_Defines.h`의 `EQUIP_SLOT`이 같다.
  원작: `PrimaryWeapon | SecondaryWeapon | MeleeWeapon | Helmat | Armor | FaceMask | Headset | Backpack | Totem1 | Totem2`
- UI 폰트 `ResourceHanRoundedCN-Medium`에는 **한글이 없다.** 미리보기는 한글만 `Resource_100/Font/Jua-Regular.ttf`로 그렸다. 실제 게임의 한글 대체 폰트는 확인하지 못했다.
- 패널 배경은 `TranslucentImage`(뒤 화면을 블러한 반투명)이고, 틴트 색은 주로 `#325978`이다. 처음엔 단색 반투명으로 대신해도 충분하다.

### 칸 하나(InventoryEntry)의 원작 값

| 레이어 | 원작 (2560) | 1280 기준 | 색 (RGBA) |
|---|---|---|---|
| 칸 | 120x120 | 60x60 | - |
| 안쪽 영역 | 칸 - 8 | 칸 - 4 (사방 2) | - |
| BG | 채움, 반지름 16 | 반지름 8 | `#00000033` → (0, 0, 0, 0.2) |
| Frame | 테두리 2px | 1px | `#FFFFFF4C` → (1, 1, 1, 0.3) |
| Hovering | 채움 | 채움 | `#FFFFFF0D` → (1, 1, 1, 0.05) |
| 선택 | 테두리 3px | 1.5px | `#FF9E3A` → (1, 0.62, 0.23, 1) |
| 내구도 0 | 채움 | 채움 | `#FF000033` |
| 놓을 수 있는 칸 (PluggableIndicator) | 테두리 2.5px + 안쪽 글로우 | 1.25px | 흰색 + `#79FF9E` |
| 개수 알약 | 높이 기준 알약 모양 | - | `#585F66`, 글자 `#F8F2EA` 16pt(→8pt) |
| 내구도 바 | 40x12 알약 | 20x6 | 바탕 `#414141`, 채움 `#CCED98`, 손실 `#D04F6D` |

### 등급 글로우 색

| 등급 | 색 |
|---|---|
| 1 | `#FFFFFF` |
| 2 | `#8BE913` |
| 3 | `#11B8F1` |
| 4 | `#990FF5` |
| 5 | `#FF7D25` |
| 6 | `#FF2F2F` |
| 그 외 | 검정 72% 그림자, 오프셋 8 |

등급을 정하는 필드가 `quality`인지 `displayQuality`인지는 코드를 보지 않아 확실하지 않다. 미리보기는 `quality`로 그렸다.

---

## 2. 이 폴더에 있는 것

| 경로 | 내용 |
|---|---|
| `README.md` | 폴더 구성, Layout 파일 읽는 법, 9-slice 표, items.csv 열 설명 |
| `GUIDE.md` | 이 문서 |
| `preview_inventory_tab.png` | Tab 인벤토리 창 전체 미리보기 (2560x1440) |
| `preview_inventory_loot.png` | 상자 루팅 창 미리보기 |
| `preview_inventory_grid.png` | 5열 그리드만 그린 검증용 이미지 |
| `items.csv` | 아이템 1570개 (한국어 이름, 등급, 무게, 가격, 최대 겹침, 태그, 아이콘 파일명) |
| `quality_colors.csv` | 등급 색 |
| `Layout/*.txt` | UI 계층 트리 (사람이 읽는 용). `03_LootView.txt`가 Tab 인벤토리 |
| `Layout/*.json` | 같은 트리의 전체 필드 |
| `Sprites/ui_sprites_9slice.csv` | 인벤토리 UI가 쓰는 스프라이트와 9-slice 값 |
| `Sprites/Items/` | 아이템 아이콘 PNG (`<typeID>_<이름>.png`, 대부분 256x256) |
| `Sprites/UI`, `Picto`, `Status`, `UI_Other` | UI 스프라이트, 흰색 실루엣 아이콘, 무게 상태 아이콘 |
| `Sound/` | 가방 열기/닫기, 아이템 줍기/장착, UI 확인/취소 WAV |
| `Font/` | `ResourceHanRoundedCN-Medium.ttf` |
| `_scripts/` | 추출(`dump_*.py`)과 미리보기(`render_view.py`, `preview.py`) 스크립트 |

---

## 3. 설계 개요

### 핵심 아이디어

**사각형 1개 = 인스턴스 1개.** 인벤토리 전체(패널, 칸, 아이콘, 테두리, 드래그 중인 아이콘)를 `DrawIndexedInstanced` **한 번**으로 그린다.

```
[Update]       Tab 토글 → 마우스 좌표/버튼 → Find_CollidedSlot → 드래그 상태머신 → 놓기(데이터 이동)
[Late_Update]  열려 있으면 Add_RenderGroup(RENDERID::ALPHA_UI)
[Render]       m_Instances를 매 프레임 새로 채움 → Map(WRITE_DISCARD) → DrawIndexedInstanced 1번
```

- **도형:** 픽셀 셰이더의 SDF(signed distance field)로 둥근 사각형과 테두리를 그린다. 텍스처가 필요 없다.
- **아이콘:** 드로우콜 하나에는 SRV 하나만 묶을 수 있다. 그래서 아이콘 전부를 **Texture2DArray**(배열 `.dds`) 하나에 넣고, 인스턴스에는 슬라이스 번호만 넣는다.
- **그리는 순서:** 한 드로우콜 안에서는 인스턴스 순서대로 겹쳐 그려진다. 그래서 버퍼에 아래 → 위 순서로 넣으면 된다. 드래그 중인 아이콘은 맨 마지막에 넣는다.
- **드래그:** 인스턴스 버퍼를 매 프레임 다시 채우므로, 잡은 아이콘은 마우스 위치에 인스턴스를 하나 더 넣기만 하면 된다.

### 좌표 규칙

**전부 "좌상단 원점, 픽셀, y는 아래로"로 통일한다.**

`ScreenToClient`로 얻은 마우스 좌표와 인스턴스 `vRect`가 같은 좌표계라서, 히트 테스트와 그리기가 같은 숫자를 쓴다. 직교 카메라 좌표(중심 원점, y 위)로 바꾸는 건 VS 안에서만 한다.

### 프로젝트에 이미 있어서 그대로 쓰는 것

| 이미 있는 것 | 위치 | 쓰는 방법 |
|---|---|---|
| UI 인스턴싱 예제 | `Client/Private/Client_Mouse.cpp` | 쿼드 VB/IB, 래스터라이저, 샘플러 생성 코드를 그대로 복사 |
| 인스턴스 입력 레이아웃 형식 | `Engine/Public/Engine_Struct.h`의 `VTXNORM_INSTANCE` | 같은 형식(`static Elements`)으로 UI용 구조체 추가 |
| 알파 UI 패스 | `Engine/Private/Renderer.cpp`의 `Render_Alpha_UI()` | 블렌드가 이미 켜져 있음. `RENDERID::ALPHA_UI`에 등록만 |
| 직교 카메라 | `Client/Private/Orthographic_Cam.cpp` | `Render_GameObject`가 UI 패스 전에 `Set_MainCamera(L"COrthographic_Cam")`으로 cbCamera(b1)를 바인딩해 줌 |
| 텍스처 로드 | `Engine/Private/Texture.cpp` | `.dds`는 `CreateDDSTextureFromFile`이라 배열 dds를 그대로 Texture2DArray로 읽음 |
| 인벤토리 데이터 | `Client/Public/Inven.h`, `Client_Defines.h` | `ITEM`, `EQUIP_SLOT` 이미 있음. `Render()`만 비어 있음 |

### 수정할 파일

| 파일 | 할 일 |
|---|---|
| `Engine/Public/Engine_Struct.h` | `VTXUI_INSTANCE` 추가 (EngineSDK/Inc에도 반영) |
| `Client/Bin/Shader/Shader_UI.hlsl` | 새로 만들기 |
| `Client/Private/Loader.cpp` | 셰이더, 텍스처, 인벤 프로토타입 등록 |
| `Client/Private/Level_GamePlay.cpp` | 인벤 오브젝트 추가 |
| `Client/Public/Client_Defines.h` | `ITEM`에 필드 추가 |
| `Client/Public/Inven.h`, `Client/Private/Inven.cpp` | 본체 |
| `Client/Private/Client_Mouse.cpp` | 인벤이 열려 있을 때 사격 입력 막기 |

---

## 4. 단계별 구현

각 단계 끝의 ✅가 "여기까지 되면 이렇게 보인다"는 확인 지점이다.

### 1단계: 인벤을 게임 오브젝트로 띄우기

`CInven`은 만들어만 있고 레벨에 등록되어 있지 않다(`MainApp.cpp`의 `CInven::Get()` 호출도 주석 처리됨).

**Loader.cpp** (`Prototype_GameObject_Scope` 등록하는 곳 근처)
```cpp
if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY), L"Prototype_GameObject_Inven",
    CInven::Create(m_pDevice, m_pContext))))
    return E_FAIL;
```

**Level_GamePlay.cpp** (`Ready_Layer_GameObject`)
```cpp
if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::GAMEPLAY), TEXT("Prototype_GameObject_Inven"),
    ETOUI(LEVEL::GAMEPLAY), pLayerTag, TEXT("GameObject_Inven"))))
    return E_FAIL;
```

**Inven.cpp**
```cpp
HRESULT CInven::Initialize(void* pArg)
{
    GAMEOBJECT_DESC Desc{};
    Desc.fPosZ = 0.5f;          // ALPHA_UI는 Z 큰 것부터 그림 → Scope(z=1)보다 위에 오게
    if (FAILED(__super::Initialize(&Desc)))
        return E_FAIL;
    m_vecBackPack.resize(25);   // reserve가 아니라 resize: 빈칸은 nullptr, 칸 번호 = 인덱스
    return S_OK;
}

void CInven::Update(f32_t fTimeDelta)
{
    __super::Update(fTimeDelta);
    bool bTab = (GetAsyncKeyState(VK_TAB) & 0x8000) != 0;
    if (bTab && !m_bPrevTab)
    {
        m_bOpen = !m_bOpen;
        cout << "Inven " << (m_bOpen ? "open" : "close") << endl;
    }
    m_bPrevTab = bTab;
}

void CInven::Late_Update(f32_t fTimeDelta)
{
    __super::Late_Update(fTimeDelta);
    if (m_bOpen)
        CGameInstance::Get().Add_RenderGroup(RENDERID::ALPHA_UI, dynamic_pointer_cast<CGameObject>(shared_from_this()));
}
```
- 멤버 `bool m_bOpen = false, m_bPrevTab = false;` 추가
- 생성자의 `ZeroMemory(m_pEquipSlots, …)`는 지운다. `shared_ptr` 배열은 이미 nullptr로 생성되고, 메모리를 직접 0으로 밀면 위험하다.

✅ Tab을 누를 때마다 콘솔에 open/close가 찍힌다.

---

### 2단계: 인스턴스 구조체 (`Engine_Struct.h`)

`VTXNORM_INSTANCE` 아래에 같은 형식으로 추가한다. 슬롯 0은 `Client_Mouse`가 쓰는 `VTXNORM` 쿼드를 그대로 쓴다.

```cpp
typedef struct tagVtxUIInstance
{
    float4_t    vRect;      // left, top, width, height (화면 픽셀, 좌상단 원점)
    float4_t    vColor;     // RGBA
    float4_t    vShape;     // x: 모서리 반지름, y: 테두리 두께(0=채움), z: 0 도형 / 1 아이콘, w: 아이콘 번호
    float4_t    vUV;        // 아이콘 UV (0,0,1,1)

    static constexpr uint32_t iNumElements = 7;
    static constexpr D3D11_INPUT_ELEMENT_DESC Elements[iNumElements] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0,  0, D3D11_INPUT_PER_VERTEX_DATA,   0 },
        { "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT,    0, 12, D3D11_INPUT_PER_VERTEX_DATA,   0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,       0, 24, D3D11_INPUT_PER_VERTEX_DATA,   0 },
        { "UIRECT",   0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1,  0, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
        { "UICOLOR",  0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 16, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
        { "UISHAPE",  0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 32, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
        { "UIUV",     0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 48, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
    };
}VTXUI_INSTANCE;
```
월드 행렬(64바이트) 대신 사각형 정보를 직접 넣는 이유는, 색과 모양까지 인스턴스마다 다르게 줘야 하기 때문이다.

---

### 3단계: 셰이더 (`Client/Bin/Shader/Shader_UI.hlsl`)

```hlsl
cbuffer cbCamera : register(b1)
{
    float4x4 g_matView;
    float4x4 g_matProj;
    float3   g_vEye;
    float    g_Pad;
};

static const float2 g_vWinSize = float2(1280.f, 720.f);   // g_iWinSizeX/Y와 맞추기

Texture2DArray g_IconArray : register(t0);
SamplerState   g_Sampler   : register(s0);

struct VS_IN
{
    float3 vPosition : POSITION;     // ±0.5 쿼드 (y 위)
    float3 vNormal   : NORMAL;
    float2 vTexCoord : TEXCOORD0;
    float4 vRect     : UIRECT;
    float4 vColor    : UICOLOR;
    float4 vShape    : UISHAPE;
    float4 vUV       : UIUV;
};

struct VS_OUT
{
    float4 vPosition : SV_POSITION;
    float2 vLocal    : TEXCOORD0;    // 사각형 중심 기준 픽셀 (SDF용)
    float2 vTexCoord : TEXCOORD1;
    nointerpolation float4 vColor : TEXCOORD2;
    nointerpolation float4 vShape : TEXCOORD3;
    nointerpolation float2 vSize  : TEXCOORD4;
};

VS_OUT VS_MAIN(VS_IN In)
{
    VS_OUT Out;
    float2 vSize   = In.vRect.zw;
    float2 vCenter = In.vRect.xy + vSize * 0.5f;              // 좌상단 기준 픽셀
    float2 vLocal  = In.vPosition.xy * vSize;                  // 중심 기준, y 위
    float2 vOrtho  = float2(vCenter.x - g_vWinSize.x * 0.5f,
                            g_vWinSize.y * 0.5f - vCenter.y) + vLocal;

    Out.vPosition = mul(mul(float4(vOrtho, 1.f, 1.f), g_matView), g_matProj);
    Out.vLocal    = vLocal;
    Out.vTexCoord = lerp(In.vUV.xy, In.vUV.zw, In.vTexCoord);
    Out.vColor    = In.vColor;
    Out.vShape    = In.vShape;
    Out.vSize     = vSize;
    return Out;
}

// 둥근 사각형까지의 거리: 안쪽 음수, 바깥 양수 (픽셀 단위)
float SdRoundRect(float2 p, float2 halfSize, float r)
{
    float2 q = abs(p) - halfSize + r;
    return length(max(q, 0.f)) + min(max(q.x, q.y), 0.f) - r;
}

float4 PS_MAIN(VS_OUT In) : SV_TARGET
{
    if (In.vShape.z > 0.5f)     // 아이콘
        return g_IconArray.Sample(g_Sampler, float3(In.vTexCoord, In.vShape.w)) * In.vColor;

    float r = min(In.vShape.x, min(In.vSize.x, In.vSize.y) * 0.5f);   // 반지름이 크면 알약 모양
    float d = SdRoundRect(In.vLocal, In.vSize * 0.5f, r);
    float a = saturate(0.5f - d);                                     // 경계 1px 안티에일리어싱 (원작 falloff=1)
    if (In.vShape.y > 0.f)
        a *= saturate(d + In.vShape.y + 0.5f);                        // 안쪽으로 두께만큼만 남김 (테두리)
    return float4(In.vColor.rgb, In.vColor.a * a);
}
```

**Loader.cpp에 등록**
```cpp
if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY), TEXT("Prototype_Component_VS_UI"),
    CVertexShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Shader_UI.hlsl",
                          VTXUI_INSTANCE::Elements, VTXUI_INSTANCE::iNumElements, "VS_MAIN"))))
    return E_FAIL;

if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY), TEXT("Prototype_Component_PS_UI"),
    CPixelShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Shader_UI.hlsl", "PS_MAIN"))))
    return E_FAIL;
```

---

### 4단계: 인스턴스 그리기 틀 (사각형 하나 띄우기)

**Inven.h 멤버**

`CGameObject`에 이미 `m_pVS`, `m_pPS`(ComPtr)가 있어서 이름이 겹치지 않게 `Com`을 붙인다.
```cpp
shared_ptr<CVertexShader>   m_pVSCom;
shared_ptr<CPixelShader>    m_pPSCom;
shared_ptr<CTexture>        m_pIconTexCom;          // 6단계
ComPtr<ID3D11Buffer>        m_pInstanceVB;
static constexpr uint32_t   m_iMaxInstance = 1024;
vector<VTXUI_INSTANCE>      m_Instances;

void Push_Rect(f32_t x, f32_t y, f32_t w, f32_t h, float4_t vColor, f32_t fRadius = 0.f, f32_t fBorder = 0.f);
void Push_Icon(f32_t x, f32_t y, f32_t w, f32_t h, int32_t iIcon, f32_t fAlpha = 1.f);
void Build_Instances();
```

**Initialize_Prototype**
- 쿼드 VB/IB, 래스터라이저, 샘플러 생성 부분을 `Client_Mouse::Initialize_Prototype`에서 그대로 복사한다.
- 상수 버퍼(`m_pCB`)는 필요 없다.

**Initialize**: `Ready_Components()`(VS_UI, PS_UI)를 호출한 뒤 인스턴스 VB를 만든다.
```cpp
D3D11_BUFFER_DESC desc{};
desc.ByteWidth      = sizeof(VTXUI_INSTANCE) * m_iMaxInstance;
desc.Usage          = D3D11_USAGE_DYNAMIC;
desc.BindFlags      = D3D11_BIND_VERTEX_BUFFER;
desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
if (FAILED(m_pDevice->CreateBuffer(&desc, nullptr, &m_pInstanceVB)))
    return E_FAIL;
m_Instances.reserve(m_iMaxInstance);
```

**헬퍼**
```cpp
void CInven::Push_Rect(f32_t x, f32_t y, f32_t w, f32_t h, float4_t vColor, f32_t fRadius, f32_t fBorder)
{
    m_Instances.push_back({ { x, y, w, h }, vColor, { fRadius, fBorder, 0.f, 0.f }, { 0.f, 0.f, 1.f, 1.f } });
}
void CInven::Push_Icon(f32_t x, f32_t y, f32_t w, f32_t h, int32_t iIcon, f32_t fAlpha)
{
    m_Instances.push_back({ { x, y, w, h }, { 1.f, 1.f, 1.f, fAlpha }, { 0.f, 0.f, 1.f, (f32_t)iIcon }, { 0.f, 0.f, 1.f, 1.f } });
}
```

**Render**
```cpp
HRESULT CInven::Render()
{
    m_Instances.clear();
    Build_Instances();
    if (m_Instances.empty())
        return S_OK;
    uint32_t iCount = min((uint32_t)m_Instances.size(), m_iMaxInstance);

    D3D11_MAPPED_SUBRESOURCE tMapped{};
    if (FAILED(m_pContext->Map(m_pInstanceVB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &tMapped)))
        return E_FAIL;
    memcpy(tMapped.pData, m_Instances.data(), sizeof(VTXUI_INSTANCE) * iCount);
    m_pContext->Unmap(m_pInstanceVB.Get(), 0);

    ID3D11Buffer* pVBs[]  = { m_pVB.Get(), m_pInstanceVB.Get() };
    uint32_t iStrides[]   = { sizeof(VTXNORM), sizeof(VTXUI_INSTANCE) };
    uint32_t iOffsets[]   = { 0, 0 };
    m_pContext->IASetVertexBuffers(0, 2, pVBs, iStrides, iOffsets);
    m_pContext->IASetIndexBuffer(m_pIB.Get(), DXGI_FORMAT_R32_UINT, 0);
    m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    m_pContext->IASetInputLayout(m_pVSCom->Get_InputLayout().Get());
    m_pContext->VSSetShader(m_pVSCom->Get_Shader().Get(), nullptr, 0);
    m_pContext->PSSetShader(m_pPSCom->Get_Shader().Get(), nullptr, 0);
    if (m_pIconTexCom) m_pIconTexCom->Set_TexturePS(0, 0);
    m_pContext->PSSetSamplers(0, 1, m_pSampler.GetAddressOf());
    m_pContext->RSSetState(m_pRS.Get());

    m_pContext->DrawIndexedInstanced(m_iIndexCnt, iCount, 0, 0, 0);
    return S_OK;
}

void CInven::Build_Instances()
{
    Push_Rect(100.f, 100.f, 200.f, 120.f, { 1.f, 0.f, 0.f, 0.8f }, 16.f);       // 테스트: 채움
    Push_Rect(100.f, 260.f, 200.f, 120.f, { 1.f, 1.f, 1.f, 1.f }, 16.f, 3.f);   // 테스트: 테두리만
}
```

✅ Tab을 누르면 화면 왼쪽 위(100, 100)에 둥근 빨간 사각형과 흰 테두리 사각형이 보인다.

**안 보일 때 확인할 것**
- 위아래가 뒤집혀 있으면 VS의 `g_vWinSize.y * 0.5f - vCenter.y` 부호를 본다.
- 아무것도 안 보이면 래스터라이저를 `CULL_NONE`으로 바꿔 본다(감기 방향 문제). z를 1로 두면 깊이 테스트에는 걸리지 않는다.

---

### 5단계: 원작 레이아웃으로 칸 그리기

배치 수치는 [5. 배치 수치](#5-배치-수치-1280x720) 참고.

**칸 위치 함수** (히트 테스트와 그리기가 함께 쓴다)
```cpp
enum class INVEN_AREA { NONE, EQUIP, BAG, OUTSIDE };
struct SLOT_POS
{
    INVEN_AREA eArea = INVEN_AREA::NONE;
    int32_t    iIndex = -1;
    bool operator==(const SLOT_POS& r) const { return eArea == r.eArea && iIndex == r.iIndex; }
};

float4_t CInven::Get_SlotRect(const SLOT_POS& t) const
{
    using namespace INVEN_UI;
    if (t.eArea == INVEN_AREA::BAG)
        return { BAG_X + (t.iIndex % BAG_COLS) * BAG_CELL + BAG_INSET,
                 BAG_Y + (t.iIndex / BAG_COLS) * BAG_CELL + BAG_INSET,
                 BAG_CELL - BAG_INSET * 2.f, BAG_CELL - BAG_INSET * 2.f };
    if (t.eArea == INVEN_AREA::EQUIP)
        return { EQUIP_X + (t.iIndex % 5) * EQUIP_STEP_X, EQUIP_Y + (t.iIndex / 5) * EQUIP_STEP_Y,
                 EQUIP_W, EQUIP_BOX_H };
    return {};
}
```

**Build_Instances**
```cpp
using namespace INVEN_UI;
Push_Rect(PANEL_X, PANEL_Y, PANEL_W, PANEL_H, { 0.20f, 0.35f, 0.47f, 0.9f }, RADIUS);    // 패널

auto Push_Slot = [&](const SLOT_POS& t)
{
    float4_t r = Get_SlotRect(t);
    Push_Rect(r.x, r.y, r.z, r.w, { 0.f, 0.f, 0.f, 0.2f }, RADIUS);          // BG
    Push_Rect(r.x, r.y, r.z, r.w, { 1.f, 1.f, 1.f, 0.3f }, RADIUS, 1.f);     // Frame
};
for (int32_t i = 0; i < static_cast<int32_t>(EQUIP_SLOT::END); ++i) Push_Slot({ INVEN_AREA::EQUIP, i });
for (int32_t i = 0; i < (int32_t)m_vecBackPack.size(); ++i)        Push_Slot({ INVEN_AREA::BAG, i });
```

✅ 파란 패널 위에 장비 2줄 10칸, 그 아래 5x5 가방 칸이 보인다. `preview_inventory_tab.png` 왼쪽 패널과 같은 배치여야 한다.

가방 칸이 25개보다 많아져 패널을 넘치는 경우(스크롤)는 나중에 `RSSetScissorRects`로 처리한다. 처음엔 25칸으로 시작한다.

---

### 6단계: 아이템 데이터와 아이콘

**`Client_Defines.h`의 `ITEM`에 추가**
```cpp
int32_t     iTypeID;        // 같은 아이템인지 판단 (스택 합치기) - items.csv의 typeID
int32_t     iMaxStack;      // 최대 겹침 수 - items.csv의 maxStack
int32_t     iIconIndex;     // 아이콘 배열 슬라이스 번호
int32_t     iQuality;       // 1~6 - items.csv의 quality
```

**아이콘 텍스처 배열**
- 반드시 **배열로 만든 `.dds`**여야 한다. 일반 PNG나 단일 dds를 `Texture2DArray` 슬롯에 묶으면 타입이 맞지 않는다.
- 칸 안의 아이콘은 1280 기준 약 50px로 표시되므로 **128x128이면 충분하다.**

  | 크기 / 포맷 | 1장 | 806장 전부 |
  |---|---|---|
  | 256² RGBA8 | 256KB | 약 206MB |
  | 128² RGBA8 | 64KB | 약 52MB |
  | 128² BC7 | 16KB | 약 13MB |

- 공부용이면 실제로 쓸 아이템 수십 개만 넣는다. 상세 패널의 큰 아이콘은 하나만 그리면 되니 그때만 원본 256 PNG를 따로 로드한다.
- **테스트용 배열은 이미 있다:** `IconArray/icons_test_128.dds` (42장, 128x128, 밉맵 8단계, R8G8B8A8_UNORM, 일반 알파, 3.5MB)
  - `IconArray/icon_index.csv`: 슬라이스 번호 → typeID, 한국어 이름, `ITEM_TYPE`, `ARMOR_SLOT`, 등급, 겹침, 무게, 가격, 설명
  - `IconArray/icons_test_preview.png`: 슬라이스 번호와 아이콘을 한눈에 보는 시트
  - 다시 만들거나 아이템을 바꾸려면 `_scripts/make_icon_array.py`의 `PICKS` 목록을 고치고 실행한다(전부 상대 경로라 다른 컴퓨터에서도 그대로 된다).

```cpp
// Loader.cpp - 기존 텍스처들처럼 Client 작업 폴더 기준 상대 경로
CTexture::Create(m_pDevice, m_pContext, TEXT("../../../Resource/Inventory/IconArray/icons_test_128.dds"), 1)
// Inven::Ready_Components
__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), L"Prototype_Component_Texture_ItemIcons", L"Com_IconTex", m_pIconTexCom);
```

**테스트 아이템** (`icon_index.csv` 값 그대로)
```cpp
auto pAmmo = make_shared<ITEM>();
pAmmo->strItemName = L"S-일반 탄환"; pAmmo->eItemType = ITEM_TYPE::BULLET;
pAmmo->bStackable = true; pAmmo->iCount = 20; pAmmo->iMaxStack = 320;
pAmmo->iTypeID = 595; pAmmo->iIconIndex = 9; pAmmo->iQuality = 2;
m_vecBackPack[0] = pAmmo;

auto pHelmet = make_shared<ARMOR>();                 // 방어구는 ARMOR로 생성
pHelmet->strItemName = L"구식 철모"; pHelmet->eItemType = ITEM_TYPE::ARMOR;
pHelmet->eSlot = ARMOR_SLOT::HEAD; pHelmet->iCount = 1; pHelmet->iMaxStack = 1;
pHelmet->iTypeID = 42; pHelmet->iIconIndex = 13; pHelmet->iQuality = 2;
m_vecBackPack[1] = pHelmet;
```
슬라이스 번호는 `icons_test_preview.png`에서 확인한다. 예: 0~5 총, 6~7 근접, 8~11 탄환, 12~14 헬멧, 15~17 방탄복, 18~20 가방, 21~22 토템, 26~29 의료품.
**방어구는 반드시 `make_shared<ARMOR>()`로 만든다.** `ITEM`으로 만들고 타입만 ARMOR로 바꾸면 9단계의 `static_pointer_cast<ARMOR>`가 깨진다. 총·가방도 마찬가지다.

**아이콘 그리기**: 칸마다 BG → Frame → 아이콘 순서
```cpp
auto Push_SlotItem = [&](const SLOT_POS& t, const shared_ptr<ITEM>& p, f32_t fAlpha)
{
    if (!p) return;
    float4_t r = Get_SlotRect(t);
    Push_Icon(r.x + 3.f, r.y + 3.f, r.z - 6.f, r.w - 6.f, p->iIconIndex, fAlpha);
};
```
`Push_Slot` 안에서 Frame 다음에 `Push_SlotItem(t, Get_SlotItem(t), fA)`를 호출한다.

✅ 가방 첫 칸에 탄환 아이콘이 보인다.

---

### 7단계: 마우스 위치와 호버

```cpp
CInven::SLOT_POS CInven::Find_CollidedSlot(POINT pt) const
{
    using namespace INVEN_UI;
    // 가방
    f32_t fx = pt.x - BAG_X, fy = pt.y - BAG_Y;
    if (fx >= 0.f && fy >= 0.f && fx < BAG_COLS * BAG_CELL)
    {
        int32_t i = int32_t(fy / BAG_CELL) * BAG_COLS + int32_t(fx / BAG_CELL);
        if (i < (int32_t)m_vecBackPack.size())
            return { INVEN_AREA::BAG, i };
    }
    // 장비
    for (int32_t i = 0; i < static_cast<int32_t>(EQUIP_SLOT::END); ++i)
    {
        float4_t r = Get_SlotRect({ INVEN_AREA::EQUIP, i });
        if (pt.x >= r.x && pt.x < r.x + r.z && pt.y >= r.y && pt.y < r.y + r.w)
            return { INVEN_AREA::EQUIP, i };
    }
    // 패널 안의 빈 곳이면 NONE, 패널 밖이면 OUTSIDE (버리기)
    if (pt.x >= PANEL_X && pt.x < PANEL_X + PANEL_W && pt.y >= PANEL_Y && pt.y < PANEL_Y + PANEL_H)
        return { INVEN_AREA::NONE, -1 };
    return { INVEN_AREA::OUTSIDE, -1 };
}

shared_ptr<ITEM>& CInven::Get_SlotItem(const SLOT_POS& t)
{
    return (t.eArea == INVEN_AREA::EQUIP) ? m_pEquipSlots[t.iIndex] : m_vecBackPack[t.iIndex];
}

bool CInven::Is_Slot(const SLOT_POS& t) const
{
    return t.eArea == INVEN_AREA::EQUIP || t.eArea == INVEN_AREA::BAG;
}
```

**Update** (열려 있을 때만)
```cpp
POINT pt{};
GetCursorPos(&pt);
ScreenToClient(g_hWnd, &pt);
m_ptMouse = pt;
m_tHoveredSlot  = Find_CollidedSlot(pt);
```

**Build_Instances**: 칸을 다 그린 뒤
```cpp
if (Is_Slot(m_tHoveredSlot))
{
    float4_t r = Get_SlotRect(m_tHoveredSlot);
    Push_Rect(r.x, r.y, r.z, r.w, { 1.f, 1.f, 1.f, 0.08f }, RADIUS);     // 원작은 5%, 잘 보이게 조금 올림
}
```

**Client_Mouse.cpp에서 사격 막기**: `Update`의 `VK_LBUTTON` 처리 앞에 추가
```cpp
auto pInven = static_pointer_cast<CInven>(CGameInstance::Get().Find_GameObject(
    ETOUI(LEVEL::GAMEPLAY), L"Layer_GameObject", L"GameObject_Inven"));
if (pInven && pInven->Is_Open())
    return;
```
(`CInven`에 `bool Is_Open() const { return m_bOpen; }` 추가)

✅ 칸 위에 마우스를 올리면 그 칸만 살짝 밝아진다. 이게 되면 좌표계가 맞다는 뜻이다.

---

### 8단계: 클릭(선택)과 드래그 상태 머신

```
IDLE ──(아이템 있는 칸에서 누름)──▶ PRESSED ──(4px 이상 움직임)──▶ DRAGGING
  ▲                                   │                              │
  └──────(그냥 뗌 = 클릭/선택)─────────┘           (뗌 = 놓기 처리)────┘
```
PRESSED에서 바로 드래그로 넘기지 않는 이유는 클릭(선택 → 상세 표시)과 구분하기 위해서다.

```cpp
enum class DRAG_STATE { IDLE, PRESSED, DRAGGING };
// 멤버
bool        m_bPrevLButton = false;
DRAG_STATE  m_eDragState = DRAG_STATE::IDLE;
SLOT_POS    m_tHoveredSlot, m_tSelectedSlot, m_tDragFromSlot;
POINT       m_ptMouse{}, m_ptPress{};
float2_t    m_vGrabOffset{};
```

**Update** (7단계 코드 다음)
```cpp
bool bDown     = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;
bool bPressed  = bDown && !m_bPrevLButton;     // 눌린 순간
bool bReleased = !bDown && m_bPrevLButton;     // 뗀 순간
m_bPrevLButton = bDown;

switch (m_eDragState)
{
case DRAG_STATE::IDLE:
    if (bPressed)
    {
        if (Is_Slot(m_tHoveredSlot) && Get_SlotItem(m_tHoveredSlot))
        {
            m_eDragState     = DRAG_STATE::PRESSED;
            m_tDragFromSlot = m_tHoveredSlot;
            m_ptPress   = pt;
            float4_t r  = Get_SlotRect(m_tHoveredSlot);
            m_vGrabOffset = { pt.x - r.x, pt.y - r.y };     // 잡은 위치 그대로 따라오게
        }
        else
            m_tSelectedSlot = {};                               // 빈 곳 클릭 → 선택 해제
    }
    break;

case DRAG_STATE::PRESSED:
    if (bReleased)                                          // 안 움직이고 뗌 = 클릭
    {
        m_tSelectedSlot = m_tDragFromSlot;
        m_eDragState = DRAG_STATE::IDLE;
    }
    else if (abs(pt.x - m_ptPress.x) + abs(pt.y - m_ptPress.y) > 4)
        m_eDragState = DRAG_STATE::DRAGGING;
    break;

case DRAG_STATE::DRAGGING:
    if (bReleased)
    {
        Drop(m_tDragFromSlot, m_tHoveredSlot);                        // 9단계
        m_eDragState = DRAG_STATE::IDLE;
    }
    break;
}
```
- Tab으로 닫을 때 `m_eDragState = DRAG_STATE::IDLE`로 초기화한다(드래그 도중 닫으면 원위치).
- 입력을 `GetAsyncKeyState`로 폴링하므로 창 밖에서 버튼을 떼도 감지된다. `SetCapture`는 필요 없다.

**Build_Instances 순서** (뒤에 넣을수록 위에 그려짐)
```cpp
// 1) 패널
// 2) 칸마다 BG → Frame → 아이콘
//    드래그 중인 원래 칸은 아이콘을 흐리게:
//    f32_t fA = (m_eDragState == DRAG_STATE::DRAGGING && t == m_tDragFromSlot) ? 0.3f : 1.f;
// 3) 선택 테두리
if (Is_Slot(m_tSelectedSlot))
{
    float4_t r = Get_SlotRect(m_tSelectedSlot);
    Push_Rect(r.x, r.y, r.z, r.w, { 1.f, 0.62f, 0.23f, 1.f }, RADIUS, 1.5f);
}
// 4) 호버 (7단계)
// 5) 드래그 중: 놓을 수 있는 장비칸 초록 표시 (9단계 끝 참고)
// 6) 드래그 중인 아이콘 - 반드시 맨 마지막
if (m_eDragState == DRAG_STATE::DRAGGING)
{
    auto& p = Get_SlotItem(m_tDragFromSlot);
    Push_Icon(m_ptMouse.x - m_vGrabOffset.x + 3.f, m_ptMouse.y - m_vGrabOffset.y + 3.f, 50.f, 50.f, p->iIconIndex, 0.9f);
}
```

✅ 클릭하면 주황 테두리가 생긴다. 끌면 아이콘이 커서를 따라오고 원래 칸은 흐려진다(아직 놓으면 그대로 돌아간다).

---

### 9단계: 놓기 (데이터 이동)

```cpp
void CInven::Drop(const SLOT_POS& tFrom, const SLOT_POS& tTo)
{
    auto& rFrom = Get_SlotItem(tFrom);
    if (!rFrom) return;

    if (tTo.eArea == INVEN_AREA::OUTSIDE)       // 패널 밖 → 버리기
    {
        // TODO: 월드에 아이템 오브젝트 생성
        rFrom = nullptr;
        return;
    }
    if (!Is_Slot(tTo) || tTo == tFrom)          // 패널 안 빈 곳, 같은 칸 → 원위치
        return;

    auto& rTo = Get_SlotItem(tTo);
    if (!CanPlace(rFrom, tTo))
        return;

    // 같은 아이템 + 겹치기 가능 → 합치기
    if (rTo && rTo->bStackable && rTo->iTypeID == rFrom->iTypeID)
    {
        int32_t iMove = min(rFrom->iCount, rTo->iMaxStack - rTo->iCount);
        rTo->iCount   += iMove;
        rFrom->iCount -= iMove;
        if (rFrom->iCount <= 0)
            rFrom = nullptr;
        return;
    }

    // 빈칸이면 이동, 아니면 교환 (반대 방향도 들어갈 수 있어야 함)
    if (rTo && !CanPlace(rTo, tFrom))
        return;
    swap(rFrom, rTo);

    if (m_tSelectedSlot == tFrom) m_tSelectedSlot = tTo;    // 선택이 아이템을 따라가게
}

bool CInven::CanPlace(const shared_ptr<ITEM>& p, const SLOT_POS& t) const
{
    if (!p) return true;                                 // 빈 것은 어디든
    if (t.eArea == INVEN_AREA::BAG) return true;

    switch (static_cast<EQUIP_SLOT>(t.iIndex))
    {
    case EQUIP_SLOT::GUN_1:   case EQUIP_SLOT::GUN_2:   return p->eItemType == ITEM_TYPE::GUN;
    case EQUIP_SLOT::MELEE:                             return p->eItemType == ITEM_TYPE::MELEE;
    case EQUIP_SLOT::HEAD:
        return p->eItemType == ITEM_TYPE::ARMOR && static_pointer_cast<ARMOR>(p)->eSlot == ARMOR_SLOT::HEAD;
    case EQUIP_SLOT::BODY:
        return p->eItemType == ITEM_TYPE::ARMOR && static_pointer_cast<ARMOR>(p)->eSlot == ARMOR_SLOT::BODY;
    case EQUIP_SLOT::BACKPACK:                          return p->eItemType == ITEM_TYPE::BACKPACK;
    case EQUIP_SLOT::TOTEM_1: case EQUIP_SLOT::TOTEM_2: return p->eItemType == ITEM_TYPE::TOTEM;
    default:                                            return false;   // FACE, HEADSET: 아직 아이템 타입 없음
    }
}
```

**놓을 수 있는 장비칸 초록 표시** (8단계 Build_Instances의 5번)
```cpp
if (m_eDragState == DRAG_STATE::DRAGGING)
    for (int32_t i = 0; i < static_cast<int32_t>(EQUIP_SLOT::END); ++i)
        if (CanPlace(Get_SlotItem(m_tDragFromSlot), { INVEN_AREA::EQUIP, i }))
        {
            float4_t r = Get_SlotRect({ INVEN_AREA::EQUIP, i });
            Push_Rect(r.x, r.y, r.z, r.w, { 0.47f, 1.f, 0.62f, 0.9f }, RADIUS, 1.25f);   // 원작 PluggableIndicator
        }
```

✅ 확인 순서
1. 탄환을 빈칸에 → 이동
2. 다른 아이템 위에 → 교환
3. 같은 탄환끼리 → 합쳐짐
4. 총을 끌면 총기 칸 2개만 초록 → 총기 칸에 들어감
5. 헬멧 칸에 총 → 거부
6. 패널 밖에 놓기 → 사라짐

이 단계는 렌더링과 상관없는 로직이다. 기존 `RenderEquipSlot()`처럼 콘솔에 칸 상태를 찍으면서 디버깅하면 편하다.

---

### 10단계: 다듬기 (나중에)

| 기능 | 방법 |
|---|---|
| 개수·이름·무게 텍스트 | 엔진에 있는 DirectXTK `SpriteBatch`/`SpriteFont`로 인스턴스 패스 다음에 그린다. 한글은 쓸 글자만 넣어 spritefont로 변환 |
| 개수 알약 배경 | 칸 우하단에 `Push_Rect(w 15, h 9, #585F66, 반지름 = 높이/2)` |
| 내구도 바 | 칸 하단에 20x6 알약 3개(바탕, 채움, 손실) |
| 등급 글로우 | 흐린 아이콘 배열을 하나 더 만들어 `vShape.z = 2`로 아이콘 앞에 그림. 색은 등급 색 |
| 가방 스크롤 | 휠 입력으로 오프셋, 스크리서를 켠 래스터라이저와 `RSSetScissorRects`로 영역 밖 자르기 |
| 아이템 상세 패널 | 선택 칸(`m_tSelectedSlot`)의 아이템을 오른쪽 패널(452, 118, 375x160)에 표시 |
| 가방 해제 제한 | 가방을 장비칸에서 뺄 때 가방 칸이 비어 있지 않으면 거부 |
| 스택 나누기 | 원작에도 있음(`UI_Item_Split`). Shift+드래그 등으로 나중에 |

**추천 진행 순서:** 1~5단계(텍스처 없이 가능) → 7단계 호버 → 6단계 아이콘 → 8단계 → 9단계 → 10단계

---

## 5. 배치 수치 (1280x720)

`Layout/03_LootView.json`을 유니티 레이아웃 규칙대로 다시 계산한 값을 x0.5 했다. 좌상단 원점, 픽셀 단위.

```cpp
namespace INVEN_UI
{
    // 장비 + 가방 패널
    constexpr f32_t PANEL_X = 42.f,  PANEL_Y = 117.f, PANEL_W = 320.f, PANEL_H = 543.f;

    // 장비 10칸 (5열 x 2행): 아이템 박스 45x43.3 + 아래 라벨 16
    constexpr f32_t EQUIP_X = 65.f,  EQUIP_Y = 151.4f;
    constexpr f32_t EQUIP_W = 45.f,  EQUIP_BOX_H = 43.3f;
    constexpr f32_t EQUIP_STEP_X = 57.5f, EQUIP_STEP_Y = 64.f;

    // 가방 그리드: 60x60 칸, 간격 0, 5열. 실제 박스는 사방 2px 안쪽(56x56)
    constexpr f32_t BAG_X = 52.5f,   BAG_Y = 326.4f, BAG_CELL = 60.f, BAG_INSET = 2.f;
    constexpr int32_t BAG_COLS = 5;

    constexpr f32_t RADIUS = 8.f;     // 원작 16 x 0.5
}
```

| 영역 | x, y (좌상단) | 크기 |
|---|---|---|
| 장비 + 가방 패널 | 42, 117 | 320 x 543 |
| 장비 타이틀바 ("장비") | 46.5, 121 | 312 x 22 |
| 장비 첫 칸 | 65, 151.4 | 박스 45 x 43.3, 라벨 45 x 16 (y 195.6) |
| 가방 타이틀바 ("아이템 (n/m)" + 정리 버튼) | 46.5, 282 | 312 x 40 |
| 가방 첫 칸 | 52.5, 326.4 | 60 x 60 (5열) |
| 가방 보이는 영역 (스크롤 뷰포트) | 46.5, 277 | 312 x 379 → 약 5.5줄 |
| 펫 칸 (1열) | 366, 117 | 79 x 224 |
| 아이템 상세 | 452, 118 | 375 x 160 이상 (내용에 따라 늘어남) |
| 퀵슬롯 (4칸) | 514, 572 | 252 x 88 |
| 소지 중량 바 | 42, 668 | 170 x 24 |
| 상단 탭 버튼 바 | 화면 가운데 위 | 버튼 40x40, 간격 20 |

원작 GridLayoutGroup 설정 (2560 기준):

| 그리드 | 셀 | 간격 | 패딩 | 열 |
|---|---|---|---|---|
| 가방 / 상자 | 120x120 | 0, 0 | L4 R4 T8 B8 | 5열 고정 |
| 장비 슬롯 | 90x120 | 25, 8 | T16 B4 | 유동 (폭에 따라 5열) |
| 펫 | 120x120 | 0, 0 | L4 R4 T8 B8 | 1열 |
| 퀵슬롯 | 110x110 | 16 (가로 정렬) | 8 | - |

---

## 6. 추출/미리보기 스크립트 다시 돌리기

코드 작업만 할 거면 필요 없다. 다시 추출하거나 미리보기를 다시 그릴 때만 필요하다.

**준비**
- 게임 설치 경로: `D:\STEAM\steamapps\common\Escape from Duckov`. 다르면 각 스크립트 상단의 경로를 바꾼다(`common.py`의 `D`, `render_view.py`의 `LOC`).
- 출력 경로: `dump_*.py`, `preview.py`의 `OUT`/`I`는 원래 컴퓨터의 절대 경로(`C:\Users\cho99\...\Duckov\Resource\Inventory`)로 적혀 있다. 다른 컴퓨터에서는 이 폴더 경로로 바꾼다. `render_view.py`는 상대 경로라 그대로 된다.
- 패키지:
  ```bash
  python -m pip install UnityPy TypeTreeGeneratorAPI fonttools pillow
  ```

**스크립트**

| 스크립트 | 하는 일 |
|---|---|
| `_scripts/scan.py` | MonoScript 표(`scripts.json`)를 만들고 인벤토리 컴포넌트가 어느 파일에 있는지 찾기 |
| `_scripts/dump_layout.py` | `Layout/*.json`, `*.txt` 생성 |
| `_scripts/dump_sprites_items.py` | UI 스프라이트와 9-slice CSV |
| `_scripts/dump_items.py` | `items.csv`, 아이템 아이콘, GameplayDataSettings |
| `_scripts/preview.py` | `quality_colors.csv`, `preview_inventory_grid.png` |
| `_scripts/render_view.py` | `preview_inventory_tab.png`, `preview_inventory_loot.png` (유니티 레이아웃 재계산 + 렌더) |

**주의**
- `common.py`는 `scripts.json`(scan.py 결과)을 같은 폴더에서 읽는다. 처음 돌릴 때는 `scan.py`부터 실행한다.
- UnityPy에서 MonoBehaviour의 `m_Script`는 PPtr 해석이 실패한다. 그래서 `globalgamemanagers.assets`의 MonoScript를 path_id로 직접 매핑하고, `TypeTreeGenerator`(게임의 `Managed` 폴더 DLL)로 `read_typetree` 한다.
- `GameplayDataSettings`는 전체 `read_typetree`가 실패한다. 그래서 노드를 `uiStyleData`까지만 잘라서 읽는다(등급 색).
- 한국어 문자열은 `StreamingAssets/Localization/Korean.csv`에 있다. 값의 `\ `, `\.`처럼 백슬래시로 이스케이프된 부분은 백슬래시를 빼고 읽는다.
