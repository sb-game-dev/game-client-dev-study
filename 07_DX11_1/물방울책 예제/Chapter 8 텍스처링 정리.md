# 루나책 Chapter 8 — Texturing (텍스처 적용)

> 7장(조명)까지는 정점마다 **재질(Material) 색** 하나만 줬다. 그래서 상자는 "갈색 상자", 땅은 "초록 땅"처럼 밋밋했다.
> 8장의 목표는 **이미지(텍스처)를 삼각형 표면에 붙여서** 나무 무늬, 풀, 물결 같은 디테일을 표현하는 것이다.

> 📌 **이 정리는 이펙트 프레임워크(Effects11) 없이 진행한다.**
> 책 예제는 `.fx` 파일과 `ID3DX11Effect`를 쓰지만, 수업 엔진(`CHill`, `CCube`)은 `D3DCompileFromFile` + `VSSetShader`로 셰이더를 직접 다룬다.
> 그래서 모든 코드를 **D3D11 API 직접 호출** 방식으로 바꿔서 정리했다. 개념은 책과 100% 같고, 값을 GPU에 넘기는 방법만 다르다.
> 책 코드를 읽을 때 쓸 수 있는 대응표는 맨 끝 [부록](#부록-책의-이펙트-코드--직접-호출-대응표)에 있다.

---

## 0. 한눈에 보는 8장 흐름

```
[이미지 파일 (.dds)]
      │  ① 로딩: DirectX::CreateDDSTextureFromFile
      ▼
[ID3D11Texture2D]  ← 실제 픽셀 데이터 (리소스)
      │  ② 뷰 생성 (로더가 같이 해줌)
      ▼
[ID3D11ShaderResourceView (SRV)]  ← "셰이더야, 이거 읽어도 돼"라는 출입증
      │  ③ PSSetShaderResources(0, 1, &srv)   → 셰이더 t0 슬롯
      │     PSSetSamplers(0, 1, &sampler)      → 셰이더 s0 슬롯
      ▼
[HLSL: Texture2D g_DiffuseTex : register(t0);  SamplerState g_Sampler : register(s0);]
      │  ④ 픽셀마다 UV 좌표로 샘플링
      ▼
vTexColor = g_DiffuseTex.Sample(g_Sampler, In.vTexcoord)
      │  ⑤ 조명 결과와 합치기
      ▼
최종 색 = vTexColor * (ambient + diffuse) + specular
```

| 절 | 내용 | 한 줄 요약 |
|---|---|---|
| 1 | 텍스처와 리소스/뷰 | 텍스처 = GPU 메모리의 이미지, SRV로 셰이더에 연결 |
| 2 | 텍스처 좌표(UV) | 정점에 (u, v)를 줘서 "이미지의 어느 부분을 붙일지" 지정 |
| 3 | 텍스처 로드 | DDS 파일 → SRV (DDSTextureLoader) |
| 4 | 셰이더 레지스터 | b# / t# / s# 슬롯과 C++ 바인딩 함수 |
| 5 | 필터링과 샘플러 | 텍스처가 확대/축소될 때 색 계산 방법 + `CreateSamplerState` |
| 6 | 샘플링 | HLSL `Sample()` |
| 7 | 재질과 텍스처 결합 | 텍스처 색을 디퓨즈 반사율로 사용 |
| 8 | 주소 모드 | UV가 [0,1] 밖으로 나갔을 때 처리 |
| 9 | 텍스처 변환 | UV에 행렬을 곱해 타일링/애니메이션 |
| 10 | 실습 ① 지형에 풀 텍스처 입히기 | 책 Crate 예제의 과정을 수업 엔진(`CHill`)으로 |
| 11 | 실습 ② 흐르는 물 | 책 Textured Hills and Waves 예제의 과정 |
| 12 | 로더 없이 텍스처 직접 만들기 | 로더가 내부에서 하는 일 |
| 13 | 압축 텍스처 포맷 | BC1~BC7, DDS |
| 14~16 | 실수 체크리스트 / 요약 / 연습문제 | |

---

## 1. 텍스처란?

- **텍스처(Texture)** = GPU가 읽을 수 있는 형태로 만든 **이미지 데이터**.
- 텍스처의 픽셀 하나하나를 **텍셀(Texel, Texture Element)** 이라고 부른다. (화면의 '픽셀'과 구분하기 위함)
- 종류: 1D / 2D / 3D 텍스처. 8장은 **2D 텍스처**만 다룬다.

### 리소스(Resource)와 뷰(View)의 관계 — 중요!

DX11에서는 텍스처를 **바로 셰이더에 꽂지 않는다.** 반드시 **뷰(View)** 를 거쳐서 연결한다.

```
ID3D11Texture2D  (데이터 덩어리 그 자체)
   ├─ ID3D11ShaderResourceView  → 셰이더에서 "읽기"용   (8장에서 사용)
   ├─ ID3D11RenderTargetView    → "그리기 대상"용        (4장 백버퍼)
   └─ ID3D11DepthStencilView    → 깊이/스텐실용          (4장 깊이버퍼)
```

- 비유: 텍스처 = 책, 뷰 = "이 책을 열람실에서 읽을 수 있음"이라는 **대출 카드**.
- 같은 텍스처를 여러 용도로 쓰려면 생성할 때 `BindFlags`에 여러 플래그를 OR로 준다.
  - 예) `D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET` → 렌더 투 텍스처 (나중 장에서 사용)
- **셰이더 쪽에서 보는 것은 항상 SRV**다. 그래서 C++ 멤버로 보관하는 것도 보통 `ComPtr<ID3D11ShaderResourceView>` 하나면 충분하다.

---

## 2. 텍스처 좌표 (UV)

### 2-1. 텍스처 좌표계

```
(0,0) ──────────► u (가로)
  │  ┌────────────┐
  │  │            │
  │  │   이미지    │
  │  │            │
  ▼  └────────────┘ (1,1)
  v (세로)
```

- 가로축 **u**, 세로축 **v**. 범위는 **[0, 1]** 로 정규화(normalized)되어 있다.
- **왼쪽 위가 (0,0)**, 오른쪽 아래가 (1,1). 수학 좌표계와 달리 **v는 아래로 갈수록 커진다!**
- 정규화 좌표를 쓰는 이유: 이미지가 256×256이든 1024×1024이든 **같은 UV를 그대로 쓸 수 있다.**
  - 실제 텍셀 위치 = (u × 너비, v × 높이)

### 2-2. 정점에 UV를 넣는다

수업 엔진의 `VTXNORM`에는 이미 UV(`Tex`)와 입력 레이아웃의 `TEXCOORD`가 들어 있다. (`Engine/Public/Engine_Struct.h`)

```cpp
typedef struct tagVtxNorm
{
    float3_t    vPosition;   // 위치  (12바이트)
    float3_t    vNormal;     // 법선  (12바이트)
    float2_t    Tex;         // ★ 텍스처 좌표 (u, v)
    static constexpr uint32_t iNumElements = 3;
    static constexpr D3D11_INPUT_ELEMENT_DESC Elements[iNumElements] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT,0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,   0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        //                                              ↑ 오프셋 = 12 + 12
    };
}VTXNORM;
```

### 2-3. 삼각형 내부는 어떻게 되나? → 보간(Interpolation)

- UV는 정점 3개에만 주어진다.
- 래스터라이저가 삼각형 안쪽 픽셀마다 UV를 **선형 보간**해서 픽셀 셰이더로 넘긴다. (법선, 색 보간과 같은 원리)
- 그래서 픽셀 셰이더는 "이 픽셀의 UV"를 받아 이미지에서 색을 읽기만 하면 된다.

```
  정점 A UV(0,0)       정점 B UV(1,0)
       ●───────────────●
        \   이 픽셀은   /
         \ UV≈(0.5,0.3)으로 자동 보간
          \           /
           \         /
            ●
       정점 C UV(0.5,1)
```

### 2-4. 예시: 사각형 한 면 / 그리드

```
v0 (-1, +1) UV(0,0)    v1 (+1, +1) UV(1,0)
      ┌──────────────┐
      │              │
      │  텍스처 전체   │
      │              │
      └──────────────┘
v3 (-1, -1) UV(0,1)    v2 (+1, -1) UV(1,1)
```

그리드(지형)는 왼쪽 위 정점이 (0,0), 오른쪽 아래 정점이 (1,1)이 되도록 칸 수로 나눠서 준다. `CHill`이 이미 이렇게 계산하고 있다.

```cpp
f32_t du = 1.f / (ivtxCntX - 1);
f32_t dv = 1.f / (ivtxCntZ - 1);
// ...
m_tMeshData.Vertices[i * ivtxCntX + j].TexC.x = j * du;   // 오른쪽으로 갈수록 u 증가
m_tMeshData.Vertices[i * ivtxCntX + j].TexC.y = i * dv;   // 아래(앞쪽)로 갈수록 v 증가
```

> ⚠️ **계산한 UV를 실제 정점 버퍼용 배열에 복사해야 한다.** 이걸 빠뜨리면 UV가 전부 (0,0)이라 텍스처의 왼쪽 위 한 점 색만 보인다.
> ```cpp
> vertices[i].Tex = m_tMeshData.Vertices[i].TexC;   // ★ 필수
> ```

---

## 3. 텍스처 로드 (파일 → SRV)

### 3-1. 로더 고르기

DX11 자체에는 "이미지 파일 → 텍스처" 함수가 **없다.** (책 원본의 `D3DX11CreateShaderResourceViewFromFile`은 D3DX가 폐기되면서 사라졌다.)

| 방법 | 지원 포맷 | 준비물 |
|---|---|---|
| **DDSTextureLoader** (DirectXTK) | `.dds` | `DDSTextureLoader.h/.cpp` 2개 파일만 프로젝트에 추가 — `FDLuna-master/Common/`에 있음 |
| **WICTextureLoader** (DirectXTK) | `.png .jpg .bmp .tiff` | `WICTextureLoader.h/.cpp` 추가 (GitHub DirectXTK) |
| **DirectXTex** | 거의 전부 (`.dds .tga .hdr .png ...`) | 라이브러리 빌드/링크 필요. 실무에서 많이 씀 |

가장 쉬운 방법: `FDLuna-master/Common/DDSTextureLoader.h`, `DDSTextureLoader.cpp`를 엔진 프로젝트에 복사해서 추가한다. (`namespace DirectX` 안에 들어 있음)

### 3-2. 텍스처 파일 위치

- 예제 텍스처: `07_DX11_1/물방울책 예제/FDLuna-master/Assets/Textures/` (grass.dds, water2.dds, WoodCrate01.dds 등)
- Client 프로젝트는 작업 디렉터리가 기본값(`Client/Default`, .vcxproj 위치)이다. 셰이더 경로 `../Shader/...`가 `Client/Shader`를 가리키는 이유.
- 그래서 텍스처를 `Client/Resources/Textures/`에 두면 경로는 `L"../Resources/Textures/grass.dds"`가 된다.

```
Duckov/Game/Client/
 ├─ Default/      ← 작업 디렉터리 (.vcxproj)
 ├─ Shader/
 └─ Resources/
     └─ Textures/
         └─ grass.dds
```

### 3-3. 로드 코드

```cpp
#include "DDSTextureLoader.h"

// 멤버 변수
ComPtr<ID3D11ShaderResourceView> m_pDiffuseSRV;

// Initialize_Prototype()
if (FAILED(DirectX::CreateDDSTextureFromFile(
        m_pDevice.Get(),                     // 디바이스
        L"../Resources/Textures/grass.dds",  // 작업 디렉터리 기준 상대경로
        nullptr,                             // ID3D11Resource** — 텍스처 자체는 필요 없으니 nullptr
        m_pDiffuseSRV.GetAddressOf())))      // ★ 결과: SRV
    return E_FAIL;
```

- 이 함수 하나가 **파일 읽기 → `ID3D11Texture2D` 생성 → SRV 생성**을 전부 해준다.
- 텍스처 포인터를 nullptr로 받아도 되는 이유: COM 객체는 **참조 카운트**로 관리되는데, SRV가 내부에서 텍스처 참조를 하나 쥐고 있다. SRV가 해제될 때 텍스처도 같이 해제된다.
- `ComPtr`이라 소멸할 때 자동으로 Release된다. (`ReleaseCOM` 불필요)
- `CreateDDSTextureFromFile(device, context, path, ...)`처럼 **컨텍스트를 같이 넘기는 버전**을 쓰면, DDS에 밉맵이 없을 때 밉맵을 자동으로 만들어 준다.

> 💡 텍스처 = 그냥 이미지 데이터라서, 같은 메시에 SRV만 바꿔 끼우면 다른 그림이 입혀진다. (같은 상자 + 나무 텍스처 / 철 텍스처)

---

## 4. 셰이더 레지스터와 바인딩

### 4-1. 셰이더에 텍스처/샘플러 선언

```hlsl
Texture2D    g_DiffuseTex : register(t0);   // 텍스처 = t 레지스터
SamplerState g_Sampler    : register(s0);   // 샘플러 = s 레지스터
```

- 텍스처와 샘플러는 **숫자가 아니라서 cbuffer 안에 넣을 수 없다.** 전역으로 따로 선언한다.
- `register(t0)`처럼 **슬롯 번호를 직접 정해 주고**, C++에서 같은 번호로 꽂아야 한다.

### 4-2. 레지스터 종류 정리

| 레지스터 | 담는 것 | HLSL 선언 | C++ 바인딩 함수 |
|---|---|---|---|
| `b#` | 상수 버퍼 | `cbuffer cbPerObject : register(b0)` | `VSSetConstantBuffers` / `PSSetConstantBuffers` |
| `t#` | 텍스처 (SRV) | `Texture2D g_Tex : register(t0)` | `PSSetShaderResources` |
| `s#` | 샘플러 | `SamplerState g_Sam : register(s0)` | `PSSetSamplers` |

- 슬롯 번호는 **종류별로 따로** 센다. 그래서 `b0`, `t0`, `s0`는 서로 겹치지 않는다.
- 바인딩은 **셰이더 단계별로 따로**다. 픽셀 셰이더에서 쓰는 텍스처는 `PS`SetShaderResources로 꽂는다. (정점 셰이더에서 쓰려면 `VSSetShaderResources`)

### 4-3. Render()에서 바인딩

```cpp
m_pContext->PSSetShaderResources(0,                              // 시작 슬롯 (t0)
                                 1,                              // 개수
                                 m_pDiffuseSRV.GetAddressOf());

m_pContext->PSSetSamplers(0,                                     // 시작 슬롯 (s0)
                          1,
                          m_pSampler.GetAddressOf());
```

- 바인딩은 **컨텍스트에 계속 남아 있다.** 다른 물체가 t0를 다른 텍스처로 덮어쓰기 전까지 유지된다.
  - 그래서 물체마다 Render에서 **자기 텍스처를 매번 다시 꽂는 것**이 안전하다.
- t0에 아무것도 꽂지 않고 `Sample()`하면 (0,0,0,0)이 나온다 → 화면이 검게 보인다.

---

## 5. 필터링과 샘플러 상태 — 이 장의 핵심 개념

화면 픽셀과 텍스처 텍셀은 **1:1로 딱 맞는 경우가 거의 없다.**

- 물체가 카메라에 **가까우면** → 텍셀 1개가 화면 픽셀 여러 개를 덮음 → **확대(Magnification)**
- 물체가 카메라에서 **멀면** → 화면 픽셀 1개에 텍셀 여러 개가 몰림 → **축소(Minification)**

이때 "픽셀의 색을 어떤 텍셀들로 어떻게 계산할지" 정하는 게 **필터링**이다.

### 5-1. 확대(Magnification) 필터

64×64 텍스처를 화면 512×512 영역에 그린다고 해보자. UV가 텍셀과 텍셀 사이 어중간한 위치를 가리키게 된다.

#### ① 점 필터링 (Point / Nearest)

- **가장 가까운 텍셀 하나**의 색을 그대로 쓴다.
- 빠르지만 **계단 현상(블록처럼 각진 모양)** 이 생긴다. → 마인크래프트 느낌
- 픽셀 아트 게임에서는 일부러 쓰기도 한다.

#### ② 선형 필터링 (Linear / Bilinear)

- 주변 **텍셀 4개**를 거리에 따라 **가중 평균**한다.
- 부드럽게 보이지만, 많이 확대하면 흐릿해진다.

```
   c00 ●─────────● c10
       │   ·(s,t)│        s, t = 샘플 위치가 텍셀 사이 어디쯤인지 (0~1)
       │         │
   c01 ●─────────● c11

  ① 가로로 보간:  top    = lerp(c00, c10, s)
                  bottom = lerp(c01, c11, s)
  ② 세로로 보간:  result = lerp(top, bottom, t)
     → 가로·세로 2번 선형보간 = "Bi"-linear
```

> 확대 문제의 근본 해결책은 더 큰 텍스처를 쓰는 것이지만, 메모리에 한계가 있으니 필터링으로 보완한다.

### 5-2. 축소(Minification) 필터 — 밉맵(Mipmap)

멀리 있는 물체는 화면 픽셀 하나에 수십 개의 텍셀이 들어간다.
그중 하나만 집어 오면 카메라가 조금만 움직여도 집히는 텍셀이 계속 바뀌어 **지글지글 깜빡인다(Aliasing, Shimmering).**

**해결책: 밉맵(Mipmap)** — 미리 작게 줄인 이미지들을 만들어 둔다.

```
 Level 0: 256 x 256  (원본)
 Level 1: 128 x 128
 Level 2:  64 x  64
 Level 3:  32 x  32
 Level 4:  16 x  16
 Level 5:   8 x   8
 Level 6:   4 x   4
 Level 7:   2 x   2
 Level 8:   1 x   1
 → 총 9단계 = log2(256) + 1
```

- 각 단계는 이전 단계를 **가로세로 절반**으로 줄인 것 (2×2 텍셀을 평균).
- 메모리는 원본 대비 약 **1/3(33%)만 더** 든다. (1/4 + 1/16 + ... ≈ 1/3)
- GPU가 화면에서 텍스처가 차지하는 크기를 보고 **알맞은 밉 레벨을 자동으로 고른다.**
- 밉맵은 DDS 파일 안에 미리 넣어 둘 수 있다. (texconv 등으로 생성)
  - 이 폴더의 `mipmaps.dds`는 레벨마다 다른 색을 칠해 둔 학습용 파일이다.

밉 레벨 사이를 어떻게 처리할지도 두 가지가 있다.

| 방식 | 설명 |
|---|---|
| 점(Point) 밉 필터 | 가장 가까운 밉 레벨 **하나**만 사용 → 레벨이 바뀌는 경계선이 보일 수 있음 |
| 선형(Linear) 밉 필터 | 가장 가까운 **두 레벨**에서 각각 샘플링한 뒤 그 결과를 다시 보간 → 경계가 부드러움 |

> **삼선형(Trilinear) 필터링** = 각 밉 레벨 안에서 Bilinear(2번 보간) + 레벨 사이 Linear(1번 보간) = 총 3방향 보간.
> → `D3D11_FILTER_MIN_MAG_MIP_LINEAR`가 이것이다.

### 5-3. 비등방성 필터링 (Anisotropic)

- 땅바닥처럼 **비스듬히 기울어진 면**을 보면, 화면 픽셀 하나가 텍스처 위에서는 **길쭉한 영역**을 덮는다.
- 일반 밉맵은 정사각형 영역 기준이라 멀리 있는 바닥이 **뿌옇게 뭉개진다.**
- 비등방성 필터는 그 길쭉한 방향을 따라 **여러 번 샘플링**해서 선명하게 만든다.
- 가장 비싸지만 품질이 가장 좋다. `MaxAnisotropy`(1~16)가 클수록 좋고 느리다.
- 게임 옵션의 "비등방성 필터링 x4, x8, x16"이 바로 이것!

```
  등방성(isotropic)     = 모든 방향 동일   → 정사각형 영역 샘플
  비등방성(anisotropic) = 방향마다 다름    → 기울어진 면에 맞춘 길쭉한 영역 샘플
```

### 5-4. 샘플러 상태 만들기 — `CreateSamplerState`

필터와 주소 모드(8절)는 **샘플러 상태 객체**에 담아 C++에서 만든다.

```cpp
// 멤버 변수
ComPtr<ID3D11SamplerState> m_pSampler;

// Initialize_Prototype()
D3D11_SAMPLER_DESC SamplerDesc{};
SamplerDesc.Filter         = D3D11_FILTER_ANISOTROPIC;     // 필터 방식
SamplerDesc.MaxAnisotropy  = 4;                            // 비등방성일 때만 의미 있음 (1~16)
SamplerDesc.AddressU       = D3D11_TEXTURE_ADDRESS_WRAP;   // 주소 모드 (8절)
SamplerDesc.AddressV       = D3D11_TEXTURE_ADDRESS_WRAP;
SamplerDesc.AddressW       = D3D11_TEXTURE_ADDRESS_WRAP;
SamplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;       // 비교 샘플러(그림자맵) 아니면 NEVER
SamplerDesc.MinLOD         = 0.f;                          // 사용할 밉 레벨 범위
SamplerDesc.MaxLOD         = D3D11_FLOAT32_MAX;            // ⚠️ 끝까지 허용해야 밉맵이 동작함

if (FAILED(m_pDevice->CreateSamplerState(&SamplerDesc, m_pSampler.GetAddressOf())))
    return E_FAIL;
```

> ⚠️ `{}`로 0 초기화만 하고 `MaxLOD`를 넣지 않으면 **MaxLOD = 0**이 되어 밉맵 0레벨만 쓴다. (멀리서 지글거림)
> 💡 샘플러는 물체마다 만들 필요가 없다. 보통 엔진에서 Linear / Point / Anisotropic 몇 개만 만들어 두고 **공유**한다.

자주 쓰는 필터 값 (이름을 MIN_MAG_MIP 순서로 읽으면 된다):

| `D3D11_FILTER_...` | 축소 | 확대 | 밉 | 비고 |
|---|---|---|---|---|
| `MIN_MAG_MIP_POINT` | 점 | 점 | 점 | 가장 빠름, 각짐 |
| `MIN_MAG_LINEAR_MIP_POINT` | 선형 | 선형 | 점 | 쌍선형 |
| `MIN_MAG_MIP_LINEAR` | 선형 | 선형 | 선형 | **삼선형**, 무난한 기본값 |
| `ANISOTROPIC` | 비등방 | 비등방 | 비등방 | 최고 품질 |

> ⚠️ **샘플러를 꽂지 않으면** 기본 샘플러(**선형 필터 + CLAMP**)가 쓰인다. "WRAP으로 반복하려 했는데 가장자리만 늘어난다"면 `PSSetSamplers`를 빠뜨린 것이다.
> ⚠️ 책의 `.fx`처럼 HLSL 안에 `SamplerState s { Filter = ...; AddressU = WRAP; };`라고 써도 **일반 셰이더 컴파일에서는 적용되지 않는다.** (이건 이펙트 프레임워크 전용 문법) 반드시 C++에서 만든다.

---

## 6. 텍스처 샘플링

픽셀 셰이더에서 **"텍스처 + 샘플러 + UV"** 세 가지로 색을 읽는다.

```hlsl
float4 vTexColor = g_DiffuseTex.Sample(g_Sampler, In.vTexcoord);
//                   ↑ 어떤 텍스처       ↑ 어떻게 읽을지  ↑ 어디를 읽을지
```

- 결과는 `float4` (r, g, b, a), 각 값은 0~1 범위 (UNORM 포맷일 때).
- `Sample()`은 **픽셀 셰이더에서만** 쓸 수 있다.
  - 밉 레벨을 고르려면 "옆 픽셀과 UV가 얼마나 차이 나는지(미분값)"를 알아야 하는데, 이건 픽셀 셰이더에서만 계산할 수 있기 때문.
  - 정점 셰이더 등에서는 밉 레벨을 직접 지정하는 `SampleLevel(sampler, uv, mipLevel)`을 쓴다.

---

## 7. 재질과 텍스처 결합

텍스처 색을 **디퓨즈(+앰비언트) 반사율**로 사용한다. 즉 "이 표면이 빛을 어떤 색으로 반사하는가"를 픽셀 단위로 바꿔주는 것.

### 7-1. 셰이더 전체 (Shader_VtxNorm.hlsl을 텍스처용으로 수정)

```hlsl
#include "LightHelper.hlsli"

cbuffer cbPerObject : register(b0)
{
    float4x4 g_matWorld;
    float4x4 g_matWorldInvTranspose;
    Material g_Material;
    float4x4 g_matTex;                      // ★ 텍스처 변환 행렬 (9절)
};

cbuffer cbCamera : register(b1)
{
    float4x4 g_matView;
    float4x4 g_matProj;
    float3   g_vEye;
    float    g_Pad;
}

cbuffer cbPointLight : register(b2) { PointLight       g_PointLight; }
cbuffer cbDirLight   : register(b3) { DirectionalLight g_DirLight;   }
cbuffer cbSpotLight  : register(b4) { SpotLight        g_SpotLight;  }

Texture2D    g_DiffuseTex : register(t0);   // ★ 텍스처
SamplerState g_Sampler    : register(s0);   // ★ 샘플러

struct VS_IN
{
    float3 vPosition : POSITION;
    float3 vNormal   : NORMAL;
    float2 vTexcoord : TEXCOORD0;           // ★ 입력 레이아웃의 TEXCOORD와 연결
};

struct VS_OUT
{
    float4 vPosition : SV_POSITION;
    float3 vPosW     : POSITION;
    float3 vNormalW  : NORMAL;
    float2 vTexcoord : TEXCOORD0;           // ★ 래스터라이저가 보간해서 PS로 넘겨줌
};

VS_OUT VS_MAIN(VS_IN In)
{
    VS_OUT Out;

    float4 vPosW  = mul(float4(In.vPosition, 1.f), g_matWorld);
    Out.vPosW     = vPosW.xyz;
    Out.vNormalW  = mul(In.vNormal, (float3x3) g_matWorldInvTranspose);
    Out.vPosition = mul(mul(vPosW, g_matView), g_matProj);

    // ★ UV도 행렬로 변환 (9절). 변환이 필요 없으면 Out.vTexcoord = In.vTexcoord;
    Out.vTexcoord = mul(float4(In.vTexcoord, 0.f, 1.f), g_matTex).xy;
    return Out;
}

float4 PS_MAIN(VS_OUT In) : SV_TARGET
{
    float3 vNormal = normalize(In.vNormalW);   // 보간되면 길이가 1이 아니게 되므로 다시 정규화
    float3 vToEye  = normalize(g_vEye - In.vPosW);

    // ★ 텍스처 샘플링
    float4 vTexColor = g_DiffuseTex.Sample(g_Sampler, In.vTexcoord);

    float4 vA, vD, vS;
    float4 vAmbient = 0, vDiffuse = 0, vSpec = 0;

    ComputePointLight(g_Material, g_PointLight, In.vPosW, vNormal, vToEye, vA, vD, vS);
    vAmbient += vA; vDiffuse += vD; vSpec += vS;

    ComputeDirectionalLight(g_Material, g_DirLight, vNormal, vToEye, vA, vD, vS);
    vAmbient += vA; vDiffuse += vD; vSpec += vS;

    ComputeSpotLight(g_Material, g_SpotLight, In.vPosW, vNormal, vToEye, vA, vD, vS);
    vAmbient += vA; vDiffuse += vD; vSpec += vS;

    // ★ 텍스처는 앰비언트+디퓨즈에만 곱하고, 스펙큘러는 마지막에 더한다
    float4 vColor = vTexColor * (vAmbient + vDiffuse) + vSpec;

    // 알파 = 재질 디퓨즈 알파 × 텍스처 알파 (9장 블렌딩에서 사용)
    vColor.a = g_Material.Diffuse.a * vTexColor.a;
    return vColor;
}
```

### 7-2. 왜 스펙큘러는 텍스처와 곱하지 않을까? (책: "Modulate with late add")

- 반짝이는 하이라이트(정반사)는 보통 **빛의 색** 그대로 보인다. (빨간 사과의 하이라이트도 흰색)
- 스펙큘러까지 텍스처와 곱하면 어두운 텍스처에서는 하이라이트가 거의 사라진다.
- 그래서 **텍스처 × (앰비언트 + 디퓨즈)** 를 먼저 하고, **스펙큘러는 마지막에 더한다.**

### 7-3. 재질 색은 흰색으로

텍스처가 색을 담당하므로 재질의 Ambient/Diffuse는 **흰색에 가깝게** 둔다.
(초록 재질 × 풀 텍스처 = 칙칙한 초록이 된다.)

```cpp
m_tMaterial.Ambient  = float4_t(1.f, 1.f, 1.f, 1.f);
m_tMaterial.Diffuse  = float4_t(1.f, 1.f, 1.f, 1.f);
m_tMaterial.Specular = float4_t(0.2f, 0.2f, 0.2f, 16.f);   // w = 광택 지수
```

> 💡 책은 하나의 `.fx`에서 `uniform bool gUseTexure`로 "텍스처 있는 버전 / 없는 버전" 셰이더를 둘 다 만든다.
> 이펙트 없이 같은 걸 하려면 진입 함수를 따로 만들거나(`PS_MAIN`, `PS_MAIN_TEX`), `D3DCompileFromFile`의 두 번째 인자 `D3D_SHADER_MACRO`로 `#define`을 다르게 줘서 두 번 컴파일하면 된다.
> 처음엔 **텍스처 쓰는 셰이더 하나만** 만드는 것으로 충분하다.

---

## 8. 주소 모드 (Address Mode)

UV는 보통 [0, 1]이지만, **일부러 그 밖의 값**(예: 0~4)을 줄 수도 있다. 이때 어떻게 할지 정하는 게 주소 모드다.
샘플러 desc의 `AddressU / AddressV / AddressW`에 지정한다. (축마다 따로 지정 가능)

UV를 0~3으로 줬을 때 (텍스처 그림을 `F`라고 하면):

| `D3D11_TEXTURE_ADDRESS_...` | 동작 | 모양 | 용도 |
|---|---|---|---|
| **WRAP** (반복) | 정수 부분을 버리고 반복 | `F F F` | 바닥 타일, 벽돌 (가장 많이 씀) |
| **MIRROR** (거울) | 한 번씩 뒤집으며 반복 | `F ꟻ F` | 이음새가 티 나지 않게 반복 |
| **CLAMP** (고정) | 범위 밖은 가장자리 텍셀 색으로 늘림 | `F▬▬` | 반복하면 안 되는 이미지 (UI, 하늘 등) |
| **BORDER** (테두리) | 범위 밖은 지정한 테두리 색 | `F□□` | 그림자맵 등 |

```cpp
// BORDER 예시: 범위 밖은 파란색
SamplerDesc.AddressU       = D3D11_TEXTURE_ADDRESS_BORDER;
SamplerDesc.AddressV       = D3D11_TEXTURE_ADDRESS_BORDER;
SamplerDesc.BorderColor[0] = 0.f;   // R
SamplerDesc.BorderColor[1] = 0.f;   // G
SamplerDesc.BorderColor[2] = 1.f;   // B
SamplerDesc.BorderColor[3] = 1.f;   // A
```

- 샘플러를 아예 꽂지 않았을 때의 기본값은 **CLAMP**.
- WRAP을 쓸 때는 텍스처가 **이음새 없이 이어지는(seamless / tileable)** 이미지여야 반복 경계가 티 나지 않는다.
- 주소 모드가 다른 샘플러가 필요하면 샘플러를 하나 더 만들어 `s1`에 꽂고, 셰이더에서 `SamplerState g_SamClamp : register(s1);`처럼 골라 쓴다.

---

## 9. 텍스처 변환 (Texture Transform)

UV도 결국 2D 좌표이므로 **행렬로 이동/회전/크기 변환**을 할 수 있다. 정점 셰이더에서 `g_matTex`를 곱하는 이유가 이것이다.

```hlsl
Out.vTexcoord = mul(float4(In.vTexcoord, 0.f, 1.f), g_matTex).xy;
//                 ↑ (u, v, 0, 1) 동차좌표로 만들어야 4x4 행렬의 이동(translation)이 적용됨
```

### 9-1. C++ 상수 버퍼에 행렬 추가

C++ 구조체에 **HLSL cbuffer와 같은 순서로** 행렬을 추가한다.

```cpp
typedef struct tagCBPerObjectLit
{
    float4x4_t  mat_World;
    float4x4_t  mat_WorldInvTranspose;
    MATERIAL    tMaterial;
    float4x4_t  mat_Tex;          // ★ 추가 (HLSL cbuffer 멤버 순서와 반드시 일치)
}CB_PER_OBJECT_LIT;
```

```cpp
// Render()
XMMATRIX matTex = XMMatrixScaling(5.f, 5.f, 0.f);
XMStoreFloat4x4(&cbData.mat_Tex, XMMatrixTranspose(matTex));    // ★ 다른 행렬처럼 전치!
m_pContext->UpdateSubresource(m_pCB.Get(), 0, nullptr, &cbData, 0, 0);
```

> 💡 **왜 전치(Transpose)하나?** HLSL cbuffer의 행렬은 기본적으로 **열 우선(column-major)** 으로 읽힌다.
> DirectXMath의 행렬은 행 우선이므로, `UpdateSubresource`로 올리기 전에 전치해야 셰이더에서 올바르게 읽힌다. (`mat_World`를 전치하는 이유와 같다.)
>
> 💡 cbuffer는 **16바이트 단위로 정렬**된다. `MATERIAL`(float4 × 4 = 64바이트)과 `float4x4`(64바이트)는 딱 맞으니 걱정 없지만, `float3` 같은 걸 끼워 넣을 때는 패딩(`fPad`)을 넣어야 C++과 HLSL의 배치가 어긋나지 않는다.

### 9-2. 용도 ① 타일링 (크기 변환)

```cpp
// UV를 5배 → 0~1이 0~5가 됨 → WRAP 모드와 합쳐져 텍스처가 5x5번 반복됨
XMMATRIX matTex = XMMatrixScaling(5.f, 5.f, 0.f);
```

- 넓은 땅에 텍스처 한 장을 늘려 붙이면 텍셀이 엄청 커져서 흐릿해진다.
- 작은 텍스처를 **여러 번 반복**하면 가까이서 봐도 디테일이 살아 있다.
- z 스케일이 0인 이유: UV는 2D라서 z는 쓸 일이 없다.
- **WRAP 샘플러가 꽂혀 있어야** 반복된다. (CLAMP면 가장자리만 늘어남)

> ⚠️ 헷갈리는 포인트: UV를 **키우면** 화면의 그림은 **작아지고 더 많이 반복**된다.

### 9-3. 용도 ② 애니메이션 (이동 변환)

```cpp
// 멤버: float2_t m_vTexOffset = {};
// Update(): 매 프레임 UV 오프셋을 조금씩 증가 → 텍스처가 표면 위를 흘러감
m_vTexOffset.x += 0.1f  * fDeltaTime;
m_vTexOffset.y += 0.05f * fDeltaTime;

// Render()
XMMATRIX matScale  = XMMatrixScaling(5.f, 5.f, 0.f);
XMMATRIX matOffset = XMMatrixTranslation(m_vTexOffset.x, m_vTexOffset.y, 0.f);
XMStoreFloat4x4(&cbData.mat_Tex, XMMatrixTranspose(matScale * matOffset));   // 스케일 → 이동 순서
```

- 정점은 그대로인데 그림만 움직이는 효과 → 흐르는 물, 용암, 구름, 컨베이어 벨트, 스크롤 배경 등.
- 오프셋이 계속 커져도 **WRAP 모드**라서 문제없이 무한히 흐른다.
- 행렬을 CPU에서 만들어 상수 버퍼로 넘기기만 하면 되므로 정점 버퍼를 건드릴 필요가 없다. (아주 싸다!)

---

## 10. 실습 ① 지형에 풀 텍스처 입히기 (책: Crate 예제)

> 책의 Crate 예제는 상자에 나무 텍스처를 입힌다. 과정은 똑같으니 수업 엔진의 `CHill`에 `grass.dds`를 입히는 것으로 실습한다.

### 7장(조명) 대비 바뀌는 점

| 구분 | 7장 (조명) | 8장 (텍스처) |
|---|---|---|
| 정점 | 위치 + 법선 | + **UV** (VTXNORM.Tex) |
| 입력 레이아웃 | POSITION, NORMAL | + **TEXCOORD** |
| C++ 멤버 | VB, IB, CB, 셰이더, RS | + **SRV**, **샘플러** |
| cbuffer | World, WorldInvTranspose, Material | + **mat_Tex** |
| HLSL | - | `Texture2D : register(t0)`, `SamplerState : register(s0)` |
| 재질 | 초록색 | **흰색** (색은 텍스처가 담당) |
| Render | - | + `PSSetShaderResources`, `PSSetSamplers` |

### 10-1. 헤더 (Hill.h)

```cpp
private:
    MESHDATA m_tMeshData = {};
    MATERIAL m_tMaterial = {};

    ComPtr<ID3D11ShaderResourceView>  m_pDiffuseSRV;   // ★ 텍스처
    ComPtr<ID3D11SamplerState>        m_pSampler;      // ★ 샘플러
```

### 10-2. Initialize_Prototype()

```cpp
// ① UV 복사 (정점 버퍼용 배열로)
for (size_t i = 0; i < m_tMeshData.Vertices.size(); ++i)
{
    float3_t& p = m_tMeshData.Vertices[i].vPosition;
    p.y = GetHeight(p.x, p.z);
    vertices[i].vPosition = p;
    vertices[i].vNormal   = m_tMeshData.Vertices[i].vNormal;
    vertices[i].Tex       = m_tMeshData.Vertices[i].TexC;     // ★
}

// ② 재질은 흰색
m_tMaterial.Ambient  = float4_t(1.f, 1.f, 1.f, 1.f);
m_tMaterial.Diffuse  = float4_t(1.f, 1.f, 1.f, 1.f);
m_tMaterial.Specular = float4_t(0.2f, 0.2f, 0.2f, 16.f);

// ... VB, IB, CB 생성 / 셰이더 컴파일 / 입력 레이아웃 생성은 기존과 동일 ...

// ③ 텍스처 로드
if (FAILED(DirectX::CreateDDSTextureFromFile(m_pDevice.Get(),
        L"../Resources/Textures/grass.dds", nullptr, m_pDiffuseSRV.GetAddressOf())))
    return E_FAIL;

// ④ 샘플러 생성
D3D11_SAMPLER_DESC SamplerDesc{};
SamplerDesc.Filter         = D3D11_FILTER_ANISOTROPIC;
SamplerDesc.MaxAnisotropy  = 4;
SamplerDesc.AddressU       = D3D11_TEXTURE_ADDRESS_WRAP;
SamplerDesc.AddressV       = D3D11_TEXTURE_ADDRESS_WRAP;
SamplerDesc.AddressW       = D3D11_TEXTURE_ADDRESS_WRAP;
SamplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
SamplerDesc.MaxLOD         = D3D11_FLOAT32_MAX;
if (FAILED(m_pDevice->CreateSamplerState(&SamplerDesc, m_pSampler.GetAddressOf())))
    return E_FAIL;
```

### 10-3. Render()

```cpp
HRESULT CHill::Render()
{
    XMMATRIX matWorld = GetWorld();
    XMMATRIX matNoTrans = matWorld;
    matNoTrans.r[3] = XMVectorSet(0.f, 0.f, 0.f, 1.f);
    XMMATRIX matWorldInvTranspos = XMMatrixTranspose(XMMatrixInverse(nullptr, matNoTrans));

    CB_PER_OBJECT_LIT cbData;
    XMStoreFloat4x4(&cbData.mat_World,             XMMatrixTranspose(matWorld));
    XMStoreFloat4x4(&cbData.mat_WorldInvTranspose, XMMatrixTranspose(matWorldInvTranspos));
    cbData.tMaterial = m_tMaterial;
    XMStoreFloat4x4(&cbData.mat_Tex, XMMatrixTranspose(XMMatrixScaling(5.f, 5.f, 0.f)));  // ★ 5x5 타일링
    m_pContext->UpdateSubresource(m_pCB.Get(), 0, nullptr, &cbData, 0, 0);

    uint32_t iStride = sizeof(VTXNORM);
    uint32_t iOffset = 0;
    m_pContext->IASetVertexBuffers(0, 1, m_pVB.GetAddressOf(), &iStride, &iOffset);
    m_pContext->IASetIndexBuffer(m_pIB.Get(), DXGI_FORMAT_R32_UINT, 0);
    m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    m_pContext->IASetInputLayout(m_pInputLayout.Get());

    m_pContext->VSSetShader(m_pVS.Get(), nullptr, 0);
    m_pContext->VSSetConstantBuffers(0, 1, m_pCB.GetAddressOf());

    m_pContext->PSSetShader(m_pPS.Get(), nullptr, 0);
    m_pContext->PSSetConstantBuffers(0, 1, m_pCB.GetAddressOf());
    m_pContext->PSSetShaderResources(0, 1, m_pDiffuseSRV.GetAddressOf());   // ★ t0
    m_pContext->PSSetSamplers(0, 1, m_pSampler.GetAddressOf());              // ★ s0

    m_pContext->RSSetState(m_pRS.Get());
    m_pContext->DrawIndexed(m_iIndexCnt, 0, 0);
    return S_OK;
}
```

> 셰이더는 7-1의 것을 그대로 쓴다. C++ 쪽에서 넘기는 값만 물체마다 다르다.

---

## 11. 실습 ② 흐르는 물 (책: Textured Hills and Waves 예제)

> 책 예제는 언덕에는 풀 텍스처(타일링), 물결에는 물 텍스처(흐르는 애니메이션)를 입힌다.
> **셰이더는 실습 ①과 완전히 같고**, 물체마다 넘기는 **SRV와 `mat_Tex`만 다르다.**

### 11-1. 물결 정점의 UV는 위치에서 계산

책의 물결은 매 프레임 높이가 바뀌어서 동적 버퍼(`D3D11_USAGE_DYNAMIC` + `Map / Unmap`)로 갱신한다. 이때 UV도 위치로부터 계산한다.

```cpp
D3D11_MAPPED_SUBRESOURCE mappedData;
m_pContext->Map(m_pWavesVB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);

VTXNORM* v = reinterpret_cast<VTXNORM*>(mappedData.pData);
for (uint32_t i = 0; i < iVertexCount; ++i)
{
    v[i].vPosition = ...;  // 물결 위치
    v[i].vNormal   = ...;

    // 위치 x ∈ [-w/2, w/2] → u ∈ [0, 1]
    // 위치 z ∈ [-d/2, d/2] → v ∈ [1, 0]  (v는 아래로 증가하니까 z와 부호가 반대)
    v[i].Tex.x = 0.5f + v[i].vPosition.x / fWidth;
    v[i].Tex.y = 0.5f - v[i].vPosition.z / fDepth;
}
m_pContext->Unmap(m_pWavesVB.Get(), 0);
```

### 11-2. 물 텍스처 흘리기

```cpp
// Update()
m_vTexOffset.x += 0.1f  * fDeltaTime;
m_vTexOffset.y += 0.05f * fDeltaTime;

// Render()
XMMATRIX matScale  = XMMatrixScaling(5.f, 5.f, 0.f);                                 // 5x5 반복
XMMATRIX matOffset = XMMatrixTranslation(m_vTexOffset.x, m_vTexOffset.y, 0.f);       // 흘러감
XMStoreFloat4x4(&cbData.mat_Tex, XMMatrixTranspose(matScale * matOffset));
```

### 11-3. 그리기: 물체마다 SRV와 행렬만 바꿔 끼운다

```cpp
// 언덕 (CHill::Render)
cbData.mat_Tex = (5x5 스케일);
m_pContext->PSSetShaderResources(0, 1, m_pGrassSRV.GetAddressOf());

// 물 (CWaves::Render)
cbData.mat_Tex = (5x5 스케일 × 이동);
m_pContext->PSSetShaderResources(0, 1, m_pWaterSRV.GetAddressOf());
```

> 책에서는 물이 반투명하게 보이는 건 9장(블렌딩)에서 다룬다. 8장에서는 불투명한 물이다.

---

## 12. (참고) 로더 없이 텍스처 직접 만들기 — 로더가 내부에서 하는 일

파일 없이 코드로 체크무늬 텍스처를 만들어 보면 **텍스처 → SRV** 과정이 그대로 보인다. 텍스처 테스트용으로도 쓸모 있다.

```cpp
const uint32_t iSize = 256;
vector<uint32_t> Pixels(iSize * iSize);
for (uint32_t y = 0; y < iSize; ++y)
    for (uint32_t x = 0; x < iSize; ++x)
        // 32픽셀마다 흰/검 교차 (R8G8B8A8 → 메모리상 0xAABBGGRR)
        Pixels[y * iSize + x] = (((x / 32) + (y / 32)) % 2) ? 0xFFFFFFFF : 0xFF000000;

// 1) 텍스처 리소스 생성
D3D11_TEXTURE2D_DESC TexDesc{};
TexDesc.Width            = iSize;                        // 가로 텍셀 수
TexDesc.Height           = iSize;                        // 세로 텍셀 수
TexDesc.MipLevels        = 1;                            // 밉맵 단계 수 (여기선 원본만)
TexDesc.ArraySize        = 1;                            // 텍스처 배열 크기
TexDesc.Format           = DXGI_FORMAT_R8G8B8A8_UNORM;   // 텍셀 하나의 형식
TexDesc.SampleDesc.Count = 1;                            // 멀티샘플링 안 함
TexDesc.Usage            = D3D11_USAGE_IMMUTABLE;        // 만든 뒤 안 바꿈
TexDesc.BindFlags        = D3D11_BIND_SHADER_RESOURCE;   // ★ 셰이더에서 읽을 것

D3D11_SUBRESOURCE_DATA InitData{};
InitData.pSysMem     = Pixels.data();
InitData.SysMemPitch = iSize * sizeof(uint32_t);         // ★ 한 줄(row)의 바이트 수

ComPtr<ID3D11Texture2D> pTexture;
if (FAILED(m_pDevice->CreateTexture2D(&TexDesc, &InitData, pTexture.GetAddressOf())))
    return E_FAIL;

// 2) SRV 생성 (desc에 nullptr → 텍스처 전체를 그대로 보는 뷰)
if (FAILED(m_pDevice->CreateShaderResourceView(pTexture.Get(), nullptr, m_pDiffuseSRV.GetAddressOf())))
    return E_FAIL;
// pTexture는 지역변수라 사라져도 OK — SRV가 참조를 쥐고 있음
```

> `CreateDDSTextureFromFile`도 결국 **파일 헤더를 읽어 `D3D11_TEXTURE2D_DESC`를 채우고 → `CreateTexture2D` → `CreateShaderResourceView`** 를 하는 것뿐이다.

---

## 13. 압축 텍스처 포맷

텍스처는 메모리를 많이 먹는다.

- 1024×1024 RGBA8 텍스처 = 1024 × 1024 × 4바이트 = **4MB** (밉맵 포함 약 5.3MB)
- 이런 텍스처가 수백 장이면 VRAM이 금방 찬다 → **GPU가 직접 읽을 수 있는 압축 포맷**을 쓴다.

### BC(Block Compression) 포맷

- 텍셀을 **4×4 블록 단위**로 묶어 압축한다.
- PNG/JPG와 달리 **GPU가 압축된 상태 그대로 샘플링**할 수 있다. (메모리 절약 + 대역폭 절약 = 성능 향상)
- 손실 압축이라 화질은 약간 떨어진다.

| 포맷 | 용도 | 비고 |
|---|---|---|
| **BC1** (DXT1) | RGB + 1비트 알파 (있다/없다) | 4bpp, 가장 작음 (RGBA8 대비 1/8) |
| **BC2** (DXT3) | RGB + 4비트 명시 알파 | 거의 안 씀 |
| **BC3** (DXT5) | RGB + 부드러운 8비트 알파 | 반투명 텍스처 |
| **BC4** | 단일 채널 (흑백) | 높이맵, 마스크 |
| **BC5** | 2채널 | 노멀맵 (x, y 저장, z는 계산) |
| BC6H | HDR (부동소수점) RGB | DX11 추가 |
| BC7 | 고품질 RGB(A) | DX11 추가 |

- 압축 텍스처는 **너비/높이가 4의 배수**여야 한다. (4×4 블록 단위이므로)
- 이 포맷들을 담는 파일 형식이 **DDS(DirectDraw Surface)**.
  - DDS는 **밉맵, 압축 포맷, 큐브맵, 텍스처 배열**까지 다 담을 수 있다 → 그래서 DX 예제는 전부 .dds를 쓴다.
- 변환 도구: **texconv** (DirectXTex에 포함), Photoshop/GIMP 플러그인 등.

```bash
texconv -f BC3_UNORM -m 0 WoodCrate01.png
```

(`-f` = 포맷, `-m 0` = 밉맵을 끝까지 생성)

---

## 14. 자주 하는 실수 체크리스트

| 증상 | 원인 |
|---|---|
| 물체가 새까맣게 나옴 | `PSSetShaderResources`를 안 함 (빈 t0에서 `Sample()` → 0) / 로드 실패 (HRESULT 확인) |
| 텍스처 왼쪽 위 한 점 색만 보임 | UV를 정점 버퍼용 배열에 복사 안 함 / 입력 레이아웃의 TEXCOORD 오프셋·포맷 틀림 → UV가 전부 0 |
| 텍스처가 위아래로 뒤집힘 | v축은 **아래로 증가**하는데 위로 증가한다고 생각하고 UV를 줌 |
| 반복이 안 되고 가장자리가 늘어남 | `PSSetSamplers`를 안 함 → 기본 샘플러(**CLAMP**) / 샘플러의 주소 모드가 CLAMP |
| 멀리 있는 바닥이 지글거림 | 밉맵 없음 / 포인트 필터 / 샘플러 `MaxLOD`가 0 |
| 멀리 있는 바닥이 뿌옇게 뭉개짐 | 삼선형만 사용 → 비등방성 필터 사용 |
| 텍스처 색이 칙칙하거나 이상하게 물듦 | 재질 Ambient/Diffuse가 흰색이 아님 |
| 정점 셰이더에서 `Sample` 컴파일 에러 | VS에서는 `SampleLevel` 사용 |
| 텍스처를 cbuffer 안에 넣었더니 에러 | 텍스처/샘플러는 숫자가 아니라서 cbuffer에 못 넣음 |
| `TEXCOORD` 관련 셰이더 컴파일 에러 | VS_IN / VS_OUT 시멘틱 이름 오타, VS_OUT에 넣고 PS에서 안 받음 등 |
| UV 변환을 넣으니 이상하게 늘어남 | `mat_Tex` 전치 안 함 / C++ 구조체와 HLSL cbuffer 멤버 순서 불일치 |
| 다른 물체 텍스처가 묻어나옴 | 이전 물체가 꽂아둔 t0가 남아 있음 → 물체마다 자기 SRV를 다시 바인딩 |
| `CreateDDSTextureFromFile` 실패 | 경로가 **작업 디렉터리 기준**이 아님 / PNG를 DDS 로더로 읽으려 함 |
| HLSL에 `SamplerState { AddressU = WRAP; }` 썼는데 반복이 안 됨 | 이펙트 전용 문법이라 일반 컴파일에서는 무시됨 → C++에서 샘플러 생성 |

---

## 15. 최종 요약

1. **텍스처 좌표(UV)** 는 [0,1] 정규화 좌표, 왼쪽 위가 (0,0), v는 아래로 증가. 정점에 지정하면 삼각형 안쪽은 자동으로 보간된다.
2. 텍스처는 **`ID3D11Texture2D`(데이터) + SRV(셰이더 출입증)** 로 쓴다. 파일 로드는 `DirectX::CreateDDSTextureFromFile`.
3. **레지스터**: 상수 버퍼 `b#`, 텍스처 `t#`, 샘플러 `s#`. HLSL에서 번호를 정하고, C++에서 같은 번호로 `PSSetShaderResources` / `PSSetSamplers`.
4. **필터링** (샘플러 desc의 `Filter`)
   - 확대: Point(각짐) / Linear(부드러움, 4텍셀 쌍선형 보간)
   - 축소: **밉맵** 사용. 밉 사이도 Point/Linear → 전부 Linear = **삼선형**
   - 기울어진 면: **비등방성**이 최고 품질
5. **샘플링**: `texture.Sample(sampler, uv)` — 픽셀 셰이더 전용. (그 외는 `SampleLevel`)
6. **조명과 결합**: `color = texColor * (ambient + diffuse) + spec`, 알파 = 재질 알파 × 텍스처 알파. 재질 색은 흰색으로.
7. **주소 모드** (샘플러 desc의 `AddressU/V/W`): WRAP(반복) / MIRROR(거울 반복) / CLAMP(가장자리 늘림, 기본값) / BORDER(지정 색).
8. **텍스처 변환**: UV에 행렬 곱하기. 스케일 → **타일링**, 이동 → **흐르는 애니메이션**. C++에서 **전치해서** 상수 버퍼로 넘긴다.
9. **압축 포맷(BC1~7)** + **DDS**로 VRAM과 대역폭을 아낀다. 크기는 4의 배수.

---

## 16. 연습문제 핵심 아이디어 (참고)

- **UV 범위를 [0,3]으로 바꾸고 주소 모드를 바꿔 보기** → 샘플러 desc의 `AddressU/V`만 바꿔서 WRAP / MIRROR / CLAMP / BORDER 차이를 눈으로 확인.
- **텍스처 회전 애니메이션** → 텍스처 중심 (0.5, 0.5) 기준으로 돌리려면 원점으로 옮김 → 회전 → 되돌림 순서로 합성한다.
  ```cpp
  XMMATRIX matTex = XMMatrixTranslation(-0.5f, -0.5f, 0.f) *
                    XMMatrixRotationZ(fAngle) *
                    XMMatrixTranslation( 0.5f,  0.5f, 0.f);
  XMStoreFloat4x4(&cbData.mat_Tex, XMMatrixTranspose(matTex));
  ```
- **두 텍스처 곱하기 (멀티 텍스처링)** → 이 폴더의 `flare.dds` × `flarealpha.dds`를 상자에 입히고 회전시키기. 텍스처 2개를 t0, t1에 꽂는다.
  ```hlsl
  Texture2D g_FlareTex      : register(t0);
  Texture2D g_FlareAlphaTex : register(t1);
  // PS
  float4 c = g_FlareTex.Sample(g_Sampler, In.vTexcoord) * g_FlareAlphaTex.Sample(g_Sampler, In.vTexcoord);
  ```
  ```cpp
  ID3D11ShaderResourceView* pSRVs[2] = { m_pFlareSRV.Get(), m_pFlareAlphaSRV.Get() };
  m_pContext->PSSetShaderResources(0, 2, pSRVs);   // t0, t1에 한 번에
  ```
- **밉맵 레벨 시각화** → `mipmaps.dds`(레벨마다 색이 다름)를 바닥에 입히고 카메라를 멀리/가까이 하며 레벨이 바뀌는 것 관찰. 샘플러 Filter를 `MIN_MAG_LINEAR_MIP_POINT` ↔ `MIN_MAG_MIP_LINEAR`로 바꿔서 경계 차이 보기.
- **여러 장의 텍스처로 불꽃 애니메이션** → 프레임 이미지 여러 장을 SRV 배열로 미리 로드해 두고, 시간에 맞춰 `PSSetShaderResources`에 넘기는 SRV를 바꾼다.

---

## 부록. 책의 이펙트 코드 ↔ 직접 호출 대응표

책 예제 코드를 읽을 때 아래처럼 바꿔 읽으면 된다.

| 책 (Effects11) | 이 정리 (직접 호출) |
|---|---|
| `D3DX11CreateShaderResourceViewFromFile(...)` | `DirectX::CreateDDSTextureFromFile(...)` |
| `Texture2D gDiffuseMap;` | `Texture2D g_DiffuseTex : register(t0);` |
| `.fx`의 `SamplerState samAnisotropic { Filter = ANISOTROPIC; ... };` | C++ `D3D11_SAMPLER_DESC` → `CreateSamplerState` |
| `Effects::BasicFX->SetDiffuseMap(srv)` | `PSSetShaderResources(0, 1, &srv)` |
| (샘플러는 `Apply()`가 자동 세팅) | `PSSetSamplers(0, 1, &sampler)` |
| `Effects::BasicFX->SetTexTransform(M)` | cbuffer에 `mat_Tex` 추가 → `XMMatrixTranspose(M)` 후 `UpdateSubresource` |
| `SetWorld / SetMaterial / ...` | cbuffer 구조체 채우고 `UpdateSubresource` + `VS/PSSetConstantBuffers` |
| `activeTech->GetPassByIndex(p)->Apply(0, context)` | `VSSetShader`, `PSSetShader`, `XXSetConstantBuffers`, `PSSetShaderResources`, `PSSetSamplers`를 각각 호출 |
| `technique11 Light2Tex` + `uniform bool gUseTexure` | 진입 함수(`VS_MAIN`, `PS_MAIN`)를 `D3DCompileFromFile`로 직접 컴파일 (필요하면 `D3D_SHADER_MACRO`로 버전 분리) |
| `ReleaseCOM(mDiffuseMapSRV)` | `ComPtr`이 자동 해제 |
