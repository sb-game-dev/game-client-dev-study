# 루나책 Chapter 8 — Texturing (텍스처 적용)

> 7장(조명)까지는 정점마다 **재질(Material) 색** 하나만 줬다. 그래서 상자는 "갈색 상자", 땅은 "초록 땅"처럼 밋밋했다.
> 8장의 목표는 **이미지(텍스처)를 삼각형 표면에 붙여서** 나무 무늬, 풀, 물결 같은 디테일을 표현하는 것이다.

---

## 0. 한눈에 보는 8장 흐름

```
[이미지 파일(.dds)]
      │  ① 로딩 (CreateDDSTextureFromFile / D3DX11CreateShaderResourceViewFromFile)
      ▼
[ID3D11Texture2D]  ← 실제 픽셀 데이터(리소스)
      │  ② 뷰 생성
      ▼
[ID3D11ShaderResourceView (SRV)]  ← "셰이더야, 이거 읽어도 돼" 라는 출입증
      │  ③ 셰이더에 바인딩 (SetResource / PSSetShaderResources)
      ▼
[HLSL: Texture2D gDiffuseMap]
      │  ④ 픽셀마다 UV 좌표로 샘플링 (SamplerState로 필터/주소 모드 결정)
      ▼
texColor = gDiffuseMap.Sample(sampler, uv)
      │  ⑤ 조명 결과와 곱하기
      ▼
최종 색 = texColor * (ambient + diffuse) + specular
```

이 장에서 배우는 것 = 위 그림의 각 단계를 하나씩 이해하는 것.

| 절 | 내용 | 한 줄 요약 |
|---|---|---|
| 8.1 | 텍스처와 리소스 복습 | 텍스처 = GPU 메모리에 올라간 이미지, SRV로 셰이더에 연결 |
| 8.2 | 텍스처 좌표 | 정점에 (u, v)를 줘서 "이미지의 어느 부분을 붙일지" 지정 |
| 8.3 | 텍스처 생성/활성화 | DDS 파일 로드 → SRV 생성 → 이펙트 변수에 세팅 |
| 8.4 | 필터링 | 텍스처가 확대/축소될 때 픽셀 색을 어떻게 계산할지 |
| 8.5 | 텍스처 샘플링 | HLSL `Sample()` 함수 |
| 8.6 | 재질과 텍스처 | 텍스처 색을 디퓨즈 반사율로 사용 |
| 8.7 | 예제: Crate | 나무 상자에 텍스처 입히기 |
| 8.8 | 주소 모드 | UV가 [0,1] 밖으로 나갔을 때 처리 방법 |
| 8.9 | 텍스처 변환 | UV에 행렬을 곱해 타일링/애니메이션 |
| 8.10 | 예제: Textured Hills and Waves | 땅 타일링 + 흐르는 물 |
| 8.11 | 압축 텍스처 포맷 | BC1~BC7, DDS 포맷 |

---

## 1. 텍스처란? (8.1)

- **텍스처(Texture)** = GPU가 읽을 수 있는 형태로 만든 **이미지 데이터**.
- 각 픽셀을 **텍셀(Texel, Texture Element)** 이라고 부른다. (화면의 '픽셀'과 구분하기 위함)
- 종류: 1D / 2D / 3D 텍스처. 8장은 거의 **2D 텍스처**만 다룬다.

### 리소스(Resource)와 뷰(View)의 관계 — 중요!

DX11에서는 텍스처를 **바로 셰이더에 꽂지 않는다.** 반드시 **뷰(View)** 를 통해 연결한다.

```
ID3D11Texture2D  (데이터 덩어리 그 자체)
   ├─ ID3D11ShaderResourceView  → 셰이더에서 "읽기"용   (8장에서 사용)
   ├─ ID3D11RenderTargetView    → "그리기 대상"용        (4장 백버퍼)
   └─ ID3D11DepthStencilView    → 깊이/스텐실용          (4장 깊이버퍼)
```

- 비유: 텍스처 = 책, 뷰 = "이 책을 열람실에서 읽을 수 있음" 이라는 **대출 카드**.
- 같은 텍스처를 여러 용도로 쓰려면 생성할 때 `BindFlags`에 여러 플래그를 OR로 줘야 한다.
  - 예) `D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET` → 렌더 투 텍스처(나중 장에서 사용)

---

## 2. 텍스처 좌표 (UV) (8.2)

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
- **왼쪽 위가 (0,0)**, 오른쪽 아래가 (1,1). (수학 좌표계처럼 v가 위로 가는 게 아니라 **아래로 증가**함에 주의!)
- 정규화 좌표를 쓰는 이유: 이미지 크기가 256×256이든 1024×1024이든 **같은 UV를 그대로 쓸 수 있다.**
  - 실제 텍셀 위치 = (u × 너비, v × 높이)

### 2-2. 정점에 UV를 넣는다

삼각형의 각 정점에 "이 정점은 이미지의 (u, v) 위치에 대응한다"고 지정한다.

```
 정점 구조체 (Vertex.h - Basic32)
 struct Basic32
 {
     XMFLOAT3 Pos;     // 위치
     XMFLOAT3 Normal;  // 법선 (조명용)
     XMFLOAT2 Tex;     // ★ 텍스처 좌표 (u, v) 추가!
 };
```

입력 레이아웃에도 `TEXCOORD`를 추가해야 한다. (오프셋: Pos 12바이트 + Normal 12바이트 = 24)

```cpp
const D3D11_INPUT_ELEMENT_DESC InputLayoutDesc::Basic32[3] =
{
    {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0},
    {"NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
    {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0}
};
```

### 2-3. 삼각형 내부는 어떻게 되나? → 보간(Interpolation)

- UV는 정점 3개에만 주어진다.
- 래스터라이저가 삼각형 내부 픽셀마다 UV를 **선형 보간**해서 픽셀 셰이더로 넘겨준다. (법선, 색 보간과 똑같은 원리)
- 그래서 픽셀 셰이더에서는 "이 픽셀의 UV"를 받아 이미지에서 색을 읽기만 하면 된다.

```
  정점 A (0,0)        정점 B (1,0)
       ●───────────────●
        \   이 픽셀은  /
         \  UV≈(0.5,0.3) 으로 자동 보간됨
          \         /
           \       /
            ●
       정점 C (0.5,1)
```

### 2-4. 예시: 사각형(쿼드) 한 면

```
v0 (-1, +1) UV(0,0)    v1 (+1, +1) UV(1,0)
      ┌──────────────┐
      │              │
      │   텍스처 전체  │
      │              │
      └──────────────┘
v3 (-1, -1) UV(0,1)    v2 (+1, -1) UV(1,1)
```

- `GeometryGenerator::CreateBox`, `CreateGrid` 등은 이미 `TexC`(UV)를 채워서 만들어 준다.
- 예제에서는 이를 그대로 복사해서 사용: `vertices[k].Tex = box.Vertices[i].TexC;`

---

## 3. 텍스처 생성과 활성화 (8.3)

### 3-1. 파일에서 로드하기

책 원본(2011)은 D3DX 함수를 쓴다.

```cpp
ID3D11ShaderResourceView* mDiffuseMapSRV;

HR(D3DX11CreateShaderResourceViewFromFile(md3dDevice,
    L"Textures/WoodCrate01.dds", // 파일 경로
    0, 0,                        // 로드 옵션, 스레드 펌프 (안 씀)
    &mDiffuseMapSRV,             // ★ 결과: SRV
    0));
```

- 이 함수 하나가 **파일 읽기 → ID3D11Texture2D 생성 → SRV 생성**을 전부 해준다.
- **D3DX는 Windows 8 SDK부터 폐기(deprecated)** 되었다. 그래서 이 저장소의 FDLuna 예제는 **DirectXTK의 `DDSTextureLoader`** 로 바꿔 놓았다.

```cpp
// CrateDemo.cpp (이 저장소 버전)
#include "DDSTextureLoader.h"

ID3D11Resource* texResource = nullptr;
HR(CreateDDSTextureFromFile(md3dDevice, L"../../Assets/Textures/WoodCrate01.dds",
                            &texResource, &mDiffuseMapSRV));
ReleaseCOM(texResource); // SRV가 텍스처 참조를 들고 있으므로 여기선 해제해도 됨
```

> 💡 `ReleaseCOM(texResource)` 를 해도 텍스처가 사라지지 않는 이유:
> COM 객체는 **참조 카운트**로 관리된다. SRV가 내부적으로 텍스처의 참조를 하나 쥐고 있기 때문에,
> 우리가 들고 있던 참조만 놓는 것이다. SRV를 Release할 때 텍스처도 같이 해제된다.

- PNG/JPG 등 일반 이미지를 읽고 싶으면 DirectXTK의 `WICTextureLoader`(`CreateWICTextureFromFile`)를 쓴다.
- 수업 엔진에서 쓰는 **DirectXTex** 라이브러리(`LoadFromDDSFile`, `LoadFromWICFile` + `CreateShaderResourceView`)도 같은 역할이다.

### 3-2. 직접 만들 때의 텍스처 설명 구조체 (참고)

파일 로더가 내부에서 채워주는 값들이다. 의미만 알아두자.

```cpp
D3D11_TEXTURE2D_DESC desc;
desc.Width              = 256;                          // 가로 텍셀 수
desc.Height             = 256;                          // 세로 텍셀 수
desc.MipLevels          = 0;                            // 밉맵 단계 수 (0 = 끝까지 자동)
desc.ArraySize          = 1;                            // 텍스처 배열 크기
desc.Format             = DXGI_FORMAT_R8G8B8A8_UNORM;   // 텍셀 하나의 형식
desc.SampleDesc.Count   = 1;                            // 멀티샘플링 안 함
desc.Usage              = D3D11_USAGE_DEFAULT;          // GPU가 읽고 쓰기
desc.BindFlags          = D3D11_BIND_SHADER_RESOURCE;   // ★ 셰이더에서 읽을 것
desc.CPUAccessFlags     = 0;
desc.MiscFlags          = 0;
```

### 3-3. 셰이더(HLSL)에 텍스처 변수 선언

```hlsl
// 텍스처는 숫자가 아니라서 cbuffer 안에 넣을 수 없다! (따로 선언)
Texture2D gDiffuseMap;
```

### 3-4. C++에서 셰이더로 넘기기

```cpp
// Effects.h — 이펙트 프레임워크 사용 시
ID3DX11EffectShaderResourceVariable* DiffuseMap;
DiffuseMap = mFX->GetVariableByName("gDiffuseMap")->AsShaderResource();

void SetDiffuseMap(ID3D11ShaderResourceView* tex) { DiffuseMap->SetResource(tex); }

// DrawScene() 에서
Effects::BasicFX->SetDiffuseMap(mDiffuseMapSRV);
activeTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext); // Apply 해야 실제 반영!
```

이펙트 프레임워크 없이 직접 할 경우:

```cpp
// 픽셀 셰이더의 t0 레지스터에 SRV 1개 바인딩
md3dImmediateContext->PSSetShaderResources(0, 1, &mDiffuseMapSRV);
```

> **텍스처 = 이미지 데이터**이므로 실행 중에 SRV만 바꿔 끼우면 같은 메시에 다른 그림을 입힐 수 있다.
> (예: 같은 상자 메시 + 나무 텍스처 / 철 텍스처)

---

## 4. 필터링 (8.4) — 이 장의 핵심 개념

화면 픽셀과 텍스처 텍셀은 **1:1로 딱 맞는 경우가 거의 없다.**

- 물체가 카메라에 **가까우면** → 텍셀 1개가 화면 픽셀 여러 개를 덮음 → **확대(Magnification)**
- 물체가 카메라에서 **멀면** → 화면 픽셀 1개에 텍셀 여러 개가 몰림 → **축소(Minification)**

이때 "픽셀의 색을 어떤 텍셀들로 어떻게 계산할지" 정하는 게 **필터링**이다.

### 4-1. 확대(Magnification) 필터

64×64 텍스처를 화면 512×512 영역에 그린다고 해보자. UV가 텍셀 사이 어중간한 위치를 가리키게 된다.

#### ① 점 필터링 (Point / Nearest)

- 가장 **가까운 텍셀 하나**의 색을 그대로 쓴다.
- 빠르지만 **계단 현상(블록처럼 각진 모양)** 이 생긴다. → 마인크래프트 느낌
- 픽셀 아트 게임에서는 오히려 일부러 쓴다.

#### ② 선형 필터링 (Linear / Bilinear)

- 주변 **텍셀 4개**를 거리에 따라 **가중 평균**한다.
- 부드럽게 보이지만, 많이 확대하면 흐릿(blurry)해진다.

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

> 확대 문제의 근본 해결책은 "더 큰 텍스처를 쓰는 것"이지만 메모리 한계가 있으니 필터링으로 보완한다.

### 4-2. 축소(Minification) 필터 — 밉맵(Mipmap)

멀리 있는 물체는 화면 픽셀 하나에 수십 개의 텍셀이 들어간다.
그중 하나만 집어 오면 → 카메라가 조금만 움직여도 집히는 텍셀이 계속 바뀌어 **지글지글 깜빡임(Aliasing, Shimmering)** 이 생긴다.

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
- 메모리는 원본 대비 약 **1/3(33%)만 추가**된다. (1/4 + 1/16 + ... ≈ 1/3)
- GPU가 화면에서 텍스처가 차지하는 크기를 보고 **적절한 밉 레벨을 자동 선택**한다.
- 밉맵은 DDS 파일에 미리 넣어둘 수 있다 (DirectX Texture Tool / texconv로 생성).
  - 이 폴더의 `mipmaps.dds` 가 각 레벨을 다른 색으로 칠한 학습용 파일이다.

밉 레벨 사이를 어떻게 처리할지도 두 가지:

| 방식 | 설명 |
|---|---|
| 점(Point) 밉 필터 | 가장 가까운 밉 레벨 **하나**만 사용 → 레벨이 바뀌는 경계선이 보일 수 있음 |
| 선형(Linear) 밉 필터 | 가장 가까운 **두 레벨**에서 각각 샘플링 후 그 결과를 다시 보간 → 경계가 부드러움 |

> **삼선형(Trilinear) 필터링** = 각 밉 레벨 안에서 Bilinear(2번 보간) + 레벨 사이 Linear(1번 보간) = 총 3방향 보간.
> → DX11의 `D3D11_FILTER_MIN_MAG_MIP_LINEAR` 가 이것이다.

### 4-3. 비등방성 필터링 (Anisotropic)

- 땅바닥처럼 **비스듬히 기울어진 면**을 보면, 화면 픽셀 하나가 텍스처 위에서는 **길쭉한 영역**을 덮는다.
- 일반 밉맵은 정사각형 영역 기준이라 → 멀리 있는 바닥이 **뿌옇게 뭉개진다**.
- 비등방성 필터는 그 길쭉한 방향을 따라 **여러 번 샘플링**해서 선명하게 만든다.
- 가장 비싸지만 품질이 가장 좋다. `MaxAnisotropy` 값(1~16)이 클수록 좋고 느림.
- 게임 옵션의 "비등방성 필터링 x4, x8, x16" 이 바로 이것!

```
  등방성(isotropic) = 모든 방향 동일   → 정사각형 영역 샘플
  비등방성(anisotropic) = 방향마다 다름 → 기울어진 면에 맞춘 길쭉한 영역 샘플
```

### 4-4. 샘플러 상태 (SamplerState) — 필터를 지정하는 곳

**이펙트 파일(.fx)에서 정의하는 방식** (책 예제):

```hlsl
SamplerState samAnisotropic
{
    Filter        = ANISOTROPIC;
    MaxAnisotropy = 4;

    AddressU = WRAP;   // 주소 모드 (8.8에서 설명)
    AddressV = WRAP;
};

SamplerState samLinear
{
    Filter = MIN_MAG_MIP_LINEAR;  // 삼선형
};
```

자주 쓰는 필터 조합 (이름 = MIN_MAG_MIP 순서로 읽으면 된다):

| 필터 이름 | 축소 | 확대 | 밉 | 비고 |
|---|---|---|---|---|
| `MIN_MAG_MIP_POINT` | 점 | 점 | 점 | 가장 빠름, 각짐 |
| `MIN_MAG_LINEAR_MIP_POINT` | 선형 | 선형 | 점 | 쌍선형 |
| `MIN_MAG_MIP_LINEAR` | 선형 | 선형 | 선형 | **삼선형**, 무난한 기본값 |
| `ANISOTROPIC` | 비등방 | 비등방 | 비등방 | 최고 품질 |

**C++ 코드로 직접 만드는 방식** (이펙트 프레임워크 안 쓸 때, 수업 엔진에서 보게 될 형태):

```cpp
D3D11_SAMPLER_DESC sd = {};
sd.Filter         = D3D11_FILTER_ANISOTROPIC;
sd.MaxAnisotropy  = 4;
sd.AddressU       = D3D11_TEXTURE_ADDRESS_WRAP;
sd.AddressV       = D3D11_TEXTURE_ADDRESS_WRAP;
sd.AddressW       = D3D11_TEXTURE_ADDRESS_WRAP;
sd.ComparisonFunc = D3D11_COMPARISON_NEVER;
sd.MinLOD         = 0;
sd.MaxLOD         = D3D11_FLOAT32_MAX;     // 모든 밉 레벨 사용 허용

ID3D11SamplerState* pSampler = nullptr;
md3dDevice->CreateSamplerState(&sd, &pSampler);
md3dImmediateContext->PSSetSamplers(0, 1, &pSampler);  // s0 레지스터
```

---

## 5. 텍스처 샘플링 (8.5)

픽셀 셰이더에서 **"텍스처 + 샘플러 + UV"** 세 가지로 색을 읽는다.

```hlsl
float4 texColor = gDiffuseMap.Sample(samAnisotropic, pin.Tex);
//                  ↑ 어떤 텍스처    ↑ 어떻게 읽을지   ↑ 어디를 읽을지
```

- 결과는 `float4` (r, g, b, a), 각 값은 0~1 범위 (UNORM 포맷일 때).
- `Sample()`은 **픽셀 셰이더에서만** 사용 가능하다.
  - 밉 레벨을 고르려면 "옆 픽셀과 UV가 얼마나 차이 나는지(미분값)"를 알아야 하는데, 이건 픽셀 셰이더에서만 계산 가능하기 때문.
  - 정점 셰이더 등에서는 밉 레벨을 직접 지정하는 `SampleLevel(sampler, uv, mipLevel)` 을 써야 한다.

---

## 6. 재질과 텍스처 결합 (8.6)

텍스처 색을 **디퓨즈(+앰비언트) 반사율**로 사용한다. 즉 "이 표면이 빛을 어떤 색으로 반사하는가"를 픽셀 단위로 바꿔주는 것.

```hlsl
// Basic.fx 픽셀 셰이더 핵심 부분
float4 texColor = float4(1, 1, 1, 1);           // 기본값 = 흰색 (곱해도 변화 없음)
if (gUseTexure)
    texColor = gDiffuseMap.Sample(samAnisotropic, pin.Tex);

float4 litColor = texColor;
if (gLightCount > 0)
{
    // ... 조명 계산으로 ambient, diffuse, spec 누적 ...

    // ★ 텍스처는 ambient/diffuse에만 곱하고, specular는 나중에 더한다
    litColor = texColor * (ambient + diffuse) + spec;
}

// 알파값 = 재질 디퓨즈 알파 × 텍스처 알파  (9장 블렌딩에서 사용)
litColor.a = gMaterial.Diffuse.a * texColor.a;
```

### 왜 specular는 텍스처와 곱하지 않을까? ("Modulate with late add")

- 반짝이는 하이라이트(정반사)는 보통 **빛의 색** 그대로 보인다. (빨간 사과의 하이라이트도 흰색)
- 만약 spec까지 텍스처와 곱하면 어두운 텍스처에서는 하이라이트가 거의 사라져 버린다.
- 그래서 **텍스처 × (앰비언트 + 디퓨즈)** 를 먼저 하고, **스펙큘러는 마지막에 더한다.**

### 왜 기본값이 흰색(1,1,1,1)인가?

- 곱셈의 항등원이기 때문. 텍스처를 안 쓰는 테크닉(`Light1`, `Light2`...)에서도 같은 코드를 쓸 수 있다.
- `uniform bool gUseTexure` 는 컴파일 타임 상수라서, 컴파일러가 `if`를 아예 제거한 별도 셰이더를 만든다. (`PS(2, true)` → `Light2Tex`)

> 이 장부터는 재질의 Diffuse 색을 보통 **흰색(1,1,1)** 근처로 두고, 실제 색은 텍스처가 담당하게 한다.

---

## 7. 예제 ① Crate Demo (8.7)

> 상자(Box) 메시에 나무 상자 텍스처(`WoodCrate01.dds`)를 입히는 가장 기본 예제

### 바뀐 점 정리 (7장 대비)

| 구분 | 7장 (Lighting) | 8장 (Crate) |
|---|---|---|
| 정점 | `PosNormal` (위치+법선) | `Basic32` (위치+법선+**UV**) |
| 입력 레이아웃 | POSITION, NORMAL | + **TEXCOORD** |
| 리소스 | 없음 | `ID3D11ShaderResourceView* mDiffuseMapSRV` |
| cbuffer | gWorld, gWorldInvTranspose, gWorldViewProj, gMaterial | + **gTexTransform** |
| 셰이더 변수 | - | `Texture2D gDiffuseMap`, `SamplerState samAnisotropic` |
| 테크닉 | Light1/2/3 | + **Light0Tex ~ Light3Tex** |

### 흐름

```cpp
// 1) Init(): 텍스처 로드
HR(CreateDDSTextureFromFile(md3dDevice, L"../../Assets/Textures/WoodCrate01.dds",
                            &texResource, &mDiffuseMapSRV));

// 2) BuildGeometryBuffers(): GeometryGenerator 박스의 UV를 정점에 복사
vertices[k].Tex = box.Vertices[i].TexC;

// 3) DrawScene(): 상수 + 텍스처 세팅 후 그리기
ID3DX11EffectTechnique* activeTech = Effects::BasicFX->Light2TexTech;
Effects::BasicFX->SetWorld(world);
Effects::BasicFX->SetWorldInvTranspose(worldInvTranspose);
Effects::BasicFX->SetWorldViewProj(worldViewProj);
Effects::BasicFX->SetTexTransform(XMLoadFloat4x4(&mTexTransform)); // 단위 행렬
Effects::BasicFX->SetMaterial(mBoxMat);
Effects::BasicFX->SetDiffuseMap(mDiffuseMapSRV);                   // ★ 텍스처
activeTech->GetPassByIndex(p)->Apply(0, md3dImmediateContext);
md3dImmediateContext->DrawIndexed(mBoxIndexCount, mBoxIndexOffset, mBoxVertexOffset);

// 4) 소멸자: 해제
ReleaseCOM(mDiffuseMapSRV);
```

### 정점 셰이더

```hlsl
VertexOut VS(VertexIn vin)
{
    VertexOut vout;
    vout.PosW    = mul(float4(vin.PosL, 1.0f), gWorld).xyz;
    vout.NormalW = mul(vin.NormalL, (float3x3)gWorldInvTranspose);
    vout.PosH    = mul(float4(vin.PosL, 1.0f), gWorldViewProj);

    // ★ UV도 행렬로 변환해서 넘긴다 (8.9 텍스처 변환)
    vout.Tex = mul(float4(vin.Tex, 0.0f, 1.0f), gTexTransform).xy;
    return vout;
}
```

---

## 8. 주소 모드 (Address Mode) (8.8)

UV는 보통 [0, 1]이지만, **일부러 그 밖의 값**(예: 0~4)을 줄 수도 있다. 그때 어떻게 할지 정하는 게 주소 모드.

UV를 0 ~ 3으로 줬을 때 결과 (텍스처 그림을 `F`라고 하면):

| 모드 | 동작 | 모양 | 용도 |
|---|---|---|---|
| **WRAP** (반복) | 정수 부분 버리고 반복 | `F F F` | 바닥 타일, 벽돌 (가장 많이 씀) |
| **MIRROR** (거울) | 한 번씩 뒤집으며 반복 | `F ꟻ F` | 이음새가 티 안 나게 반복 |
| **CLAMP** (고정) | 범위 밖은 가장자리 텍셀 색으로 늘림 | `F▬▬` | 반복하면 안 되는 이미지(UI, 하늘 등) |
| **BORDER** (테두리) | 범위 밖은 지정한 `BorderColor` | `F□□` | 그림자맵 등 |

```hlsl
SamplerState samBorder
{
    Filter      = MIN_MAG_MIP_LINEAR;
    AddressU    = BORDER;
    AddressV    = BORDER;
    BorderColor = float4(0.0f, 0.0f, 1.0f, 1.0f);  // 파란 테두리
};
```

- 기본값(아무것도 지정 안 함)은 **CLAMP**.
- WRAP을 쓸 때는 텍스처가 **이음새 없이 이어지는(seamless / tileable)** 이미지여야 반복 경계가 티 나지 않는다.
- 주소 모드는 u, v(, w) 축마다 **따로** 지정할 수 있다.

> ⚠️ CLAMP인데 이미지 가장자리에 반투명 픽셀이 있으면 테두리 색이 길게 늘어나는 현상이 생길 수 있다.

---

## 9. 텍스처 변환 (Texture Transform) (8.9)

UV도 결국 2D 좌표이므로 **행렬로 이동/회전/크기 변환**을 할 수 있다.
정점 셰이더에서 `gTexTransform` 행렬을 곱하는 이유가 이것.

```hlsl
vout.Tex = mul(float4(vin.Tex, 0.0f, 1.0f), gTexTransform).xy;
//               ↑ (u, v, 0, 1) 동차좌표로 만들어서 4x4 행렬과 곱함 → 이동(translation) 적용 가능
```

### 용도 1: 타일링 (크기 변환)

```cpp
// UV를 5배 → 0~1 이 0~5 가 됨 → WRAP 모드와 합쳐져 텍스처가 5x5번 반복됨
XMMATRIX grassTexScale = XMMatrixScaling(5.0f, 5.0f, 0.0f);
```

- 넓은 땅에 텍스처 한 장을 늘려 붙이면 텍셀이 엄청 커져서 흐릿해진다.
- 작은 텍스처를 **여러 번 반복**하면 가까이서 봐도 디테일이 유지된다.
- z 스케일을 0으로 준 이유: UV는 2D라서 z는 쓸 일이 없다.

> ⚠️ 헷갈리는 포인트: UV를 **키우면** 텍스처는 **작아지며 더 많이 반복**된다. (화면에서 그림이 커지는 게 아니다!)

### 용도 2: 애니메이션 (이동 변환)

```cpp
// 매 프레임 UV 오프셋을 조금씩 증가 → 텍스처가 표면 위를 흘러감
mWaterTexOffset.y += 0.05f * dt;
mWaterTexOffset.x += 0.1f  * dt;
XMMATRIX wavesOffset = XMMatrixTranslation(mWaterTexOffset.x, mWaterTexOffset.y, 0.0f);
```

- 정점은 그대로인데 그림만 움직이는 효과 → 흐르는 물, 용암, 구름, 컨베이어 벨트, 스크롤 배경 등.
- 회전 행렬을 쓰면 소용돌이 같은 효과도 가능.

> 텍스처 변환 행렬을 **CPU에서 만들어 상수 버퍼로 넘기기만** 하면 되므로 정점 버퍼를 건드릴 필요가 없다. (값싸다!)

---

## 10. 예제 ② Textured Hills and Waves (8.10)

> 7장의 "언덕 + 물결" 장면에 풀 텍스처와 물 텍스처를 입힌 예제. **타일링**과 **텍스처 애니메이션**을 둘 다 보여준다.

### 10-1. 땅(언덕) — 타일링

```cpp
// 생성자에서 한 번 설정
XMMATRIX grassTexScale = XMMatrixScaling(5.0f, 5.0f, 0.0f);
XMStoreFloat4x4(&mGrassTexTransform, grassTexScale);

// Init()
CreateDDSTextureFromFile(md3dDevice, L"../../Assets/Textures/grass.dds", &texResource, &mGrassMapSRV);
```

- `GeometryGenerator::CreateGrid`가 그리드 전체에 0~1 범위 UV를 깔아준다.
- 텍스처 변환으로 ×5 → 풀 텍스처가 5×5번 반복된다.

### 10-2. 물(Waves) — 매 프레임 UV를 직접 계산 + 흘러가기

물결 정점은 매 프레임 높이가 바뀌므로 동적 버퍼(`Map / Unmap`)로 갱신한다. 이때 UV도 위치로부터 계산:

```cpp
// 위치 x ∈ [-w/2, w/2] → u ∈ [0, 1]   /   z ∈ [-d/2, d/2] → v ∈ [1, 0]
v[i].Tex.x = 0.5f + mWaves[i].x / mWaves.Width();
v[i].Tex.y = 0.5f - mWaves[i].z / mWaves.Depth();   // v는 아래로 증가하니까 z와 부호 반대
```

그리고 매 프레임 텍스처 변환:

```cpp
XMMATRIX wavesScale  = XMMatrixScaling(5.0f, 5.0f, 0.0f);                      // 5x5 반복
mWaterTexOffset.y   += 0.05f * dt;
mWaterTexOffset.x   += 0.1f  * dt;
XMMATRIX wavesOffset = XMMatrixTranslation(mWaterTexOffset.x, mWaterTexOffset.y, 0.0f);

// 먼저 스케일, 그 다음 이동 (행 벡터 방식이라 왼쪽부터 적용)
XMStoreFloat4x4(&mWaterTexTransform, wavesScale * wavesOffset);
```

- 오프셋이 계속 커져도 **WRAP 모드**라서 상관없이 무한히 반복해서 흘러간다.

### 10-3. 그리기

물체마다 **텍스처 변환 행렬과 SRV를 바꿔 끼우고** 그린다.

```cpp
// 땅
Effects::BasicFX->SetTexTransform(XMLoadFloat4x4(&mGrassTexTransform));
Effects::BasicFX->SetDiffuseMap(mGrassMapSRV);
// ... Apply, DrawIndexed

// 물
Effects::BasicFX->SetTexTransform(XMLoadFloat4x4(&mWaterTexTransform));
Effects::BasicFX->SetDiffuseMap(mWavesMapSRV);
// ... Apply, DrawIndexed
```

> 셰이더(Basic.fx)는 Crate와 **완전히 동일**하다. C++ 쪽에서 넘기는 값만 다를 뿐!

---

## 11. 압축 텍스처 포맷 (8.11)

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
- 이 포맷들을 저장하는 파일 형식이 바로 **DDS(DirectDraw Surface)**.
  - DDS는 **밉맵, 압축 포맷, 큐브맵, 텍스처 배열**까지 다 담을 수 있다 → 그래서 DX 예제는 전부 .dds 사용.
- 변환 도구: DirectX Texture Tool(구), **texconv**(DirectXTex에 포함), Photoshop/GIMP 플러그인 등.

```bash
texconv -f BC3_UNORM -m 0 WoodCrate01.png   # BC3 압축 + 밉맵 전체 생성
```

---

## 12. 자주 하는 실수 체크리스트

| 증상 | 원인 |
|---|---|
| 물체가 새까맣거나 이상한 색 | SRV를 바인딩 안 함 / `Apply()` 호출 안 함 / 파일 경로 틀림 (HR 실패 확인) |
| 텍스처가 위아래 뒤집힘 | v축은 **아래로 증가**하는데 위로 증가한다고 생각하고 UV를 줌 |
| 텍스처가 한 픽셀 색으로만 보임 | 입력 레이아웃의 TEXCOORD 오프셋/포맷 틀림 → UV가 전부 0 |
| 반복이 안 되고 가장자리가 늘어남 | 주소 모드가 기본값 **CLAMP** 인 상태 |
| 멀리 있는 바닥이 지글거림 | 밉맵 없음 / 포인트 필터 사용 → 밉맵 생성 + Linear/Anisotropic |
| 멀리 있는 바닥이 뿌옇게 뭉개짐 | 삼선형만 사용 → 비등방성 필터 사용 |
| 정점 셰이더에서 `Sample` 컴파일 에러 | VS에서는 `SampleLevel` 사용 |
| 텍스처를 cbuffer 안에 넣었더니 에러 | 텍스처/샘플러는 숫자가 아니라서 cbuffer에 못 들어감 |

---

## 13. 최종 요약

1. **텍스처 좌표(UV)** 는 [0,1] 정규화 좌표, 왼쪽 위가 (0,0), v는 아래로 증가. 정점에 지정하면 삼각형 내부는 자동 보간된다.
2. 텍스처는 **ID3D11Texture2D(데이터) + ShaderResourceView(셰이더 출입증)** 조합으로 사용한다. 파일 로드는 `CreateDDSTextureFromFile`(구: `D3DX11CreateShaderResourceViewFromFile`).
3. **필터링**
   - 확대: Point(각짐) / Linear(부드러움, 4텍셀 쌍선형 보간)
   - 축소: **밉맵** 사용. 밉 사이도 Point/Linear → 전부 Linear = **삼선형**
   - 기울어진 면: **비등방성**이 최고 품질
4. **샘플링**: `texture.Sample(sampler, uv)` — 픽셀 셰이더 전용. (그 외는 `SampleLevel`)
5. **조명과 결합**: `litColor = texColor * (ambient + diffuse) + spec`, 알파 = 재질 알파 × 텍스처 알파.
6. **주소 모드**: WRAP(반복) / MIRROR(거울 반복) / CLAMP(가장자리 늘림, 기본값) / BORDER(지정 색).
7. **텍스처 변환**: UV에 행렬 곱하기. 스케일 → **타일링**, 이동 → **흐르는 애니메이션**.
8. **압축 포맷(BC1~7)** + **DDS** 로 VRAM과 대역폭을 아낀다. 크기는 4의 배수.

---

## 14. 연습문제 핵심 아이디어 (참고)

- **UV 범위를 [0,3]으로 바꾸고 주소 모드를 바꿔보기** → WRAP / MIRROR / CLAMP / BORDER 차이를 눈으로 확인.
- **텍스처 회전 애니메이션** → 중심 (0.5, 0.5)로 이동 → 회전 → 다시 (-0.5, -0.5) 이동 순서로 행렬을 합성해야 텍스처 중앙 기준으로 돈다.
  ```cpp
  XMMATRIX T = XMMatrixTranslation(-0.5f, -0.5f, 0.0f) *
               XMMatrixRotationZ(angle) *
               XMMatrixTranslation(0.5f, 0.5f, 0.0f);
  ```
- **두 텍스처 곱하기 (멀티 텍스처링)** → 이 폴더의 `flare.dds` × `flarealpha.dds` 를 픽셀 셰이더에서 곱해서 상자에 입히기 + 회전 애니메이션.
  ```hlsl
  float4 c = gFlareMap.Sample(sam, pin.Tex) * gFlareAlphaMap.Sample(sam, pin.Tex);
  ```
- **밉맵 레벨 시각화** → `mipmaps.dds` (레벨마다 색이 다름)를 바닥에 입히고, 카메라를 멀리/가까이 하며 레벨이 바뀌는 것 + Point/Linear 밉 필터 차이 관찰.
- **여러 장의 텍스처로 불꽃 애니메이션** → 프레임 이미지 여러 장을 미리 로드해두고, 시간에 맞춰 SRV를 교체 (`SetDiffuseMap`에 넘기는 SRV를 바꿈).
