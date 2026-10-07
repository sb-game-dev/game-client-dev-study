# DX11 공부 정리(물방울책) - 9장

### Chapter9. DX11 블렌딩 - 반투명 물, 철조망 상자, 안개

<details>
	<summary> 0. 블렌딩을 적용하는 과정 </summary>

```cpp
[초기화]  
0. D3D11_BLEND_DESC 구조체 채우기 (공식의 계수, 연산 설정)  
1. CreateBlendState로 ID3D11BlendState 생성  
2. (알파 클리핑용) CullMode = NONE 인 RasterizerState 생성  

[렌더링 - 매 프레임]  
3. 불투명 오브젝트를 먼저 그림 (블렌딩 OFF)  
4. OMSetBlendState(투명 BlendState, ...) 로 블렌딩 ON  
5. 투명 오브젝트를 그림 (멀리 있는 것부터)  
6. OMSetBlendState(nullptr, ...) 로 기본값 복구  

[HLSL]  
7. 최종색.a = 재질 Diffuse.a * 텍스처.a  → 이 알파가 블렌딩 공식에 들어감  
8. (철조망 같은 구멍) clip(texColor.a - 0.1f) 로 픽셀 버리기  
9. (안개) lerp(조명색, 안개색, 거리비율)  
```

</details>

<details>
	<summary> 1. 블렌딩이란? </summary>

- 지금까지는 픽셀 셰이더가 색을 출력하면 후면 버퍼의 기존 색을 **그냥 덮어썼음**
- 블렌딩은 덮어쓰지 않고 **새 색과 원래 있던 색을 섞어서** 기록하는 것
- 물, 유리, 연기, 불꽃 같은 표현에 사용

> 용어 2개만 기억하면 됨

| 용어 | 의미 | 쉽게 말하면 |
|---|---|---|
| **Source (Src)** | 지금 픽셀 셰이더가 출력한 색 | 새로 칠하려는 색 |
| **Destination (Dest)** | 후면 버퍼에 이미 있던 색 | 원래 바닥에 칠해져 있던 색 |

- 예) 땅을 먼저 그리고 그 위에 물을 그린다면
  - Dest = 땅 색 (이미 그려져 있음)
  - Src  = 물 색 (지금 그리는 중)
  - 결과 = 물 색과 땅 색을 섞은 색 → 물이 반투명하게 보임

- 블렌딩은 **출력 병합기(OM, Output Merger)** 단계에서 일어남
  - 그래서 함수 이름이 `OMSetBlendState`
  - 셰이더에서 직접 섞는 게 아니라 **고정 기능 하드웨어**가 공식대로 섞어줌. 우리는 공식의 옵션만 정해줌

</details>

<details>
	<summary> 2. 블렌딩 공식 </summary>

> RGB(색)

```
C = (Csrc ⊗ Fsrc)  ⊞  (Cdst ⊗ Fdst)
```

> A(알파)

```
A = (Asrc * Fsrc)  ⊞  (Adst * Fdst)
```

- `Csrc` : 픽셀 셰이더가 출력한 색 (새 색)
- `Cdst` : 후면 버퍼의 기존 색
- `Fsrc` : Src에 곱할 **블렌드 계수** → `SrcBlend`
- `Fdst` : Dest에 곱할 **블렌드 계수** → `DestBlend`
- `⊗` : 성분별 곱셈 (r*r, g*g, b*b)
- `⊞` : **블렌드 연산** (더하기, 빼기, min, max 중 하나) → `BlendOp`

- RGB와 A는 **따로 설정**함
  - RGB : `SrcBlend`, `DestBlend`, `BlendOp`
  - A   : `SrcBlendAlpha`, `DestBlendAlpha`, `BlendOpAlpha`
  - 화면에 보이는 건 RGB이므로 대부분 RGB 쪽만 신경쓰면 됨. 알파는 후면 버퍼의 알파를 나중에 다시 읽을 때만 의미있음

> 예시 : 반투명 (가장 많이 쓰는 공식)

- Fsrc = Src 알파 (`SRC_ALPHA`), Fdst = 1 - Src 알파 (`INV_SRC_ALPHA`), 연산 = 더하기

```
C = Csrc * a  +  Cdst * (1 - a)
```

- 물 색 = 파랑(0,0,1), 땅 색 = 초록(0,1,0), 물 알파 = 0.5 라면
  - C = (0,0,1)*0.5 + (0,1,0)*0.5 = (0, 0.5, 0.5) → 청록색
- a = 1.0 이면 → Csrc 그대로 (완전 불투명, 덮어쓰기와 같음)
- a = 0.0 이면 → Cdst 그대로 (완전 투명, 아무것도 안 그린 것과 같음)
- 즉 **알파 = 불투명도**

</details>

<details>
	<summary> 3. 블렌드 연산 (BlendOp) </summary>

| 값 | 공식 | 설명 |
|---|---|---|
| `D3D11_BLEND_OP_ADD` | Src + Dst | **기본. 거의 이것만 씀** |
| `D3D11_BLEND_OP_SUBTRACT` | Src - Dst | Src에서 Dst를 뺌 |
| `D3D11_BLEND_OP_REV_SUBTRACT` | Dst - Src | Dst에서 Src를 뺌 (화면을 어둡게 할 때) |
| `D3D11_BLEND_OP_MIN` | min(Src, Dst) | 더 작은 값 (계수 무시됨) |
| `D3D11_BLEND_OP_MAX` | max(Src, Dst) | 더 큰 값 (계수 무시됨) |

- MIN, MAX는 계수(Fsrc, Fdst)를 곱하지 않고 원래 색끼리 비교함

</details>

<details>
	<summary> 4. 블렌드 계수 (SrcBlend / DestBlend) </summary>

- 계수 = Src나 Dest에 **곱해지는 값**. "각 색을 얼마나 반영할지"

| 값 | 곱해지는 값 (RGB 기준) | 
|---|---|
| `D3D11_BLEND_ZERO` | (0, 0, 0) → 아예 반영 안 함 |
| `D3D11_BLEND_ONE` | (1, 1, 1) → 그대로 반영 |
| `D3D11_BLEND_SRC_COLOR` | (Rs, Gs, Bs) |
| `D3D11_BLEND_INV_SRC_COLOR` | (1-Rs, 1-Gs, 1-Bs) |
| `D3D11_BLEND_SRC_ALPHA` | (As, As, As) |
| `D3D11_BLEND_INV_SRC_ALPHA` | (1-As, 1-As, 1-As) |
| `D3D11_BLEND_DEST_ALPHA` | (Ad, Ad, Ad) |
| `D3D11_BLEND_INV_DEST_ALPHA` | (1-Ad, 1-Ad, 1-Ad) |
| `D3D11_BLEND_DEST_COLOR` | (Rd, Gd, Bd) |
| `D3D11_BLEND_INV_DEST_COLOR` | (1-Rd, 1-Gd, 1-Bd) |
| `D3D11_BLEND_SRC_ALPHA_SAT` | min(As, 1-Ad) |
| `D3D11_BLEND_BLEND_FACTOR` | OMSetBlendState에 넘긴 blendFactor 값 |
| `D3D11_BLEND_INV_BLEND_FACTOR` | 1 - blendFactor |

- 이름 규칙만 알면 외울 필요 없음
  - `SRC` / `DEST` : 누구 값을 쓸지
  - `COLOR` / `ALPHA` : 색을 쓸지 알파를 쓸지
  - `INV_` : 1에서 뺀 값 (Inverse)
- 주의 : **알파 쪽(SrcBlendAlpha, DestBlendAlpha)에는 `_COLOR`로 끝나는 계수를 쓸 수 없음** (알파는 숫자 하나라서)

</details>

<details>
	<summary> 5. D3D11_BLEND_DESC 구조체 </summary>

```cpp
typedef struct D3D11_BLEND_DESC {
    BOOL AlphaToCoverageEnable;      // 1. 알파 투 커버리지 (MSAA + 풀/나뭇잎용). 보통 false
    BOOL IndependentBlendEnable;     // 2. 렌더타겟마다 블렌딩을 다르게 할지. 보통 false
    D3D11_RENDER_TARGET_BLEND_DESC RenderTarget[8];  // 3. 렌더타겟별 설정 (최대 8개)
} D3D11_BLEND_DESC;

typedef struct D3D11_RENDER_TARGET_BLEND_DESC {
    BOOL           BlendEnable;          // 블렌딩 켤지
    D3D11_BLEND    SrcBlend;             // Fsrc (RGB)
    D3D11_BLEND    DestBlend;            // Fdst (RGB)
    D3D11_BLEND_OP BlendOp;              // ⊞   (RGB)
    D3D11_BLEND    SrcBlendAlpha;        // Fsrc (A)
    D3D11_BLEND    DestBlendAlpha;       // Fdst (A)
    D3D11_BLEND_OP BlendOpAlpha;         // ⊞   (A)
    UINT8          RenderTargetWriteMask;// 어떤 채널(RGBA)에 쓸지
} D3D11_RENDER_TARGET_BLEND_DESC;
```

- AlphaToCoverageEnable
  - MSAA가 켜져 있을 때 알파값을 "픽셀 안 샘플 몇 개를 칠할지"로 바꿔줌
  - 풀, 나뭇잎처럼 가장자리를 부드럽게 자를 때 사용 (11장 나무 빌보드에서 사용)
  - MSAA가 꺼져 있으면 의미 없음

- IndependentBlendEnable
  - false : `RenderTarget[0]` 설정 하나를 **모든 렌더타겟에 똑같이** 적용
  - true  : `RenderTarget[0~7]` 각각 따로 적용 (디퍼드 렌더링처럼 렌더타겟을 여러 개 쓸 때)
  - 지금은 렌더타겟이 하나라서 false + `RenderTarget[0]`만 채우면 됨

- RenderTargetWriteMask
  - `D3D11_COLOR_WRITE_ENABLE_ALL` : RGBA 전부 기록 (보통 이것)
  - `D3D11_COLOR_WRITE_ENABLE_RED / GREEN / BLUE / ALPHA` 를 `|`로 조합 가능
  - `0` 으로 하면 **색을 아예 안 씀** → 깊이/스텐실 버퍼에만 기록하고 싶을 때 (10장 스텐실에서 사용)
  - 주의 : WriteMask는 **BlendEnable이 false여도 적용됨**

</details>

<details>
	<summary> 6. BlendState 생성 + 바인드 </summary>

> 멤버 변수 + 생성 (반투명 BlendState)

```cpp
// 멤버 변수
ComPtr<ID3D11BlendState>        m_pTransparentBS;

// 생성 (초기화 때 한 번)
D3D11_BLEND_DESC blendDesc{};
blendDesc.AlphaToCoverageEnable  = FALSE;
blendDesc.IndependentBlendEnable = FALSE;

blendDesc.RenderTarget[0].BlendEnable    = TRUE;
blendDesc.RenderTarget[0].SrcBlend       = D3D11_BLEND_SRC_ALPHA;       // Src * a
blendDesc.RenderTarget[0].DestBlend      = D3D11_BLEND_INV_SRC_ALPHA;   // Dst * (1 - a)
blendDesc.RenderTarget[0].BlendOp        = D3D11_BLEND_OP_ADD;          // 더하기
blendDesc.RenderTarget[0].SrcBlendAlpha  = D3D11_BLEND_ONE;             // 알파는 Src 알파를 그대로
blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
blendDesc.RenderTarget[0].BlendOpAlpha   = D3D11_BLEND_OP_ADD;
blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

if (FAILED(m_pDevice->CreateBlendState(&blendDesc, m_pTransparentBS.GetAddressOf())))
    return E_FAIL;
```

- Sampler처럼 **State 객체는 초기화 때 한 번 만들고**, 렌더링 때는 바인드만 함
- 매 프레임 Create하면 안 됨

> 바인드 (렌더링 때)

```cpp
float blendFactor[4] = { 0.f, 0.f, 0.f, 0.f };

// 블렌딩 ON
m_pContext->OMSetBlendState(m_pTransparentBS.Get(), blendFactor, 0xffffffff);

// ... 투명 오브젝트 그리기 ...

// 기본값으로 복구 (nullptr = 블렌딩 OFF, 덮어쓰기)
m_pContext->OMSetBlendState(nullptr, blendFactor, 0xffffffff);
```

- `OMSetBlendState(BlendState, BlendFactor, SampleMask)`
  - BlendFactor[4] : 계수가 `D3D11_BLEND_BLEND_FACTOR`일 때만 쓰는 RGBA 값. 안 쓰면 아무 값이나 넣어도 됨 (nullptr도 가능 → (1,1,1,1))
  - SampleMask : MSAA 샘플 중 어떤 샘플에 기록할지 비트마스크. **항상 `0xffffffff` (전부)** 로 두면 됨
- **복구를 꼭 해야 함**
  - State는 한 번 바인드하면 다른 걸 바인드할 때까지 계속 유지됨
  - 복구 안 하면 다음 프레임의 불투명 오브젝트까지 반투명으로 그려짐

</details>

<details>
	<summary> 7. 자주 사용하는 BlendState </summary>

> 반투명 (Alpha Blending) → 물, 유리, UI 페이드

```cpp
SrcBlend  = D3D11_BLEND_SRC_ALPHA;
DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
BlendOp   = D3D11_BLEND_OP_ADD;
// C = Src * a + Dst * (1 - a)
```

> 가산 (Additive) → 불꽃, 레이저, 빛 번짐, 파티클

```cpp
SrcBlend  = D3D11_BLEND_ONE;
DestBlend = D3D11_BLEND_ONE;
BlendOp   = D3D11_BLEND_OP_ADD;
// C = Src + Dst  → 겹칠수록 밝아짐
```

- 알파까지 반영하고 싶으면 `SrcBlend = SRC_ALPHA, DestBlend = ONE` (C = Src * a + Dst)

> 곱셈 (Multiplicative) → 그림자 얼룩, 데칼, 어두운 유리

```cpp
SrcBlend  = D3D11_BLEND_ZERO;
DestBlend = D3D11_BLEND_SRC_COLOR;
BlendOp   = D3D11_BLEND_OP_ADD;
// C = Src * 0 + Dst * Src = Dst * Src  → 겹칠수록 어두워짐
```

> 빼기 (Subtractive) → 화면 일부를 어둡게

```cpp
SrcBlend  = D3D11_BLEND_ONE;
DestBlend = D3D11_BLEND_ONE;
BlendOp   = D3D11_BLEND_OP_REV_SUBTRACT;
// C = Dst - Src
```

> 색 쓰기 금지 → 깊이/스텐실만 기록 (10장 거울)

```cpp
BlendEnable = FALSE;
RenderTargetWriteMask = 0;
// 또는 SrcBlend = ZERO, DestBlend = ONE (C = Dst → 원래 색 유지)
```

| 종류 | Src | Dest | Op | 결과 | 순서 중요? |
|---|---|---|---|---|---|
| 반투명 | SRC_ALPHA | INV_SRC_ALPHA | ADD | Src·a + Dst·(1-a) | **중요** |
| 가산 | ONE | ONE | ADD | Src + Dst | 상관없음 |
| 곱셈 | ZERO | SRC_COLOR | ADD | Src · Dst | 상관없음 |
| 빼기 | ONE | ONE | REV_SUBTRACT | Dst - Src | 상관없음 |

</details>

<details>
	<summary> 8. 알파값은 어디서 오나? </summary>

- 블렌딩 공식에 들어가는 `a`는 **픽셀 셰이더가 출력한 float4의 w(a) 값**
- 물방울책 예제에서는 두 가지를 곱해서 만듦

```hlsl
// 재질 알파 * 텍스처 알파
vColor.a = g_Material.Diffuse.a * vTexColor.a;
```

- 재질 알파 (`Material.Diffuse.a`)
  - 오브젝트 **전체**의 투명도 (물 전체를 50% 투명하게)
  - 예제에서 물 재질 : `Diffuse = (1, 1, 1, 0.5f)` → 알파 0.5

- 텍스처 알파 (`vTexColor.a`)
  - 텍셀 **하나하나**의 투명도 (철조망의 철사 부분은 1, 구멍 부분은 0)
  - 이미지 파일에 알파 채널이 있어야 함 → DDS(BC3/DXT5, R8G8B8A8 등), PNG 등
  - 알파 채널이 없는 이미지는 알파가 항상 1

- 8장에서 이미 이 코드를 넣어놨기 때문에, 9장에서는 **BlendState만 켜면 바로 반투명이 됨**

</details>

<details>
	<summary> 9. 그리는 순서와 깊이 버퍼 (중요) </summary>

> 왜 순서가 중요한가?

- 반투명 공식 `Src·a + Dst·(1-a)` 는 **Dst(이미 그려진 색)** 가 있어야 섞을 수 있음
- 물을 먼저 그리고 땅을 나중에 그리면?
  - 물을 그릴 때 Dst = 배경색 → 배경색이랑 섞임
  - 깊이 버퍼에 물의 깊이가 기록됨 → 물 아래 땅은 깊이 테스트에 떨어져서 **아예 안 그려짐**
  - 결과 : 물이 투명한데 아래가 안 보임

> 규칙

```
1. 불투명 오브젝트를 먼저 전부 그림  (블렌딩 OFF)
2. 투명 오브젝트를 나중에 그림        (블렌딩 ON)
3. 투명 오브젝트끼리는 카메라에서 먼 것 → 가까운 것 순서로 정렬해서 그림 (Back-to-Front)
```

- 3번이 필요한 이유 : 반투명 공식은 순서를 바꾸면 결과가 달라짐 (A 위에 B ≠ B 위에 A)
- 가산/곱셈은 더하기·곱하기라서 **순서를 바꿔도 결과가 같음** → 정렬 안 해도 됨
- 투명 오브젝트를 그릴 때 **깊이 테스트는 켜고, 깊이 쓰기는 끄는 것**이 일반적
  - 깊이 테스트 ON : 불투명 벽 뒤에 있는 물은 가려져야 하므로
  - 깊이 쓰기 OFF : 투명 오브젝트끼리 서로를 가리지 않게
  - DepthStencilState의 `DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO` (10장에서 자세히)

> 게임 엔진에서는 보통 이렇게 렌더 그룹을 나눔

```cpp
enum RENDERGROUP { RG_PRIORITY, RG_NONBLEND, RG_BLEND, RG_UI, RG_END };
// PRIORITY(스카이박스) → NONBLEND(불투명) → BLEND(투명, 거리순 정렬) → UI
```

</details>

<details>
	<summary> 10. 알파 클리핑 - clip() </summary>

> 문제 상황

- 철조망 상자처럼 **완전히 뚫린 부분(알파 0)** 과 **완전히 막힌 부분(알파 1)** 만 있는 경우
- 블렌딩으로 처리해도 되지만
  - 투명 오브젝트로 분류해야 함 → 정렬 필요, 순서 신경써야 함
  - 알파 0인 픽셀도 깊이 버퍼에 기록돼서 뒤에 있는 물체를 가려버릴 수 있음

> 해결 : 픽셀을 아예 버림

```hlsl
float4 vTexColor = g_DiffuseTex.Sample(g_Sampler, In.vTexCoord);

// 알파가 0.1보다 작으면 이 픽셀을 버림
clip(vTexColor.a - 0.1f);
```

- `clip(x)` : x < 0 이면 **현재 픽셀을 폐기** (색도 안 쓰고 깊이도 안 씀)
  - `vTexColor.a - 0.1f < 0` → `a < 0.1` 인 픽셀을 버림
  - 0이 아니라 0.1로 하는 이유 : 필터링 때문에 구멍 가장자리 알파가 0.0x처럼 애매하게 섞일 수 있어서
- **블렌딩이 필요 없음** → BlendState 안 켜도 됨, 불투명 오브젝트처럼 아무 순서로 그려도 됨
- 샘플링 직후, **조명 계산 전에** 최대한 빨리 호출 → 버릴 픽셀이면 뒤의 조명 계산을 건너뛸 수 있음
- 반투명(알파 0.5 같은 중간값)은 표현 못 함. **뚫렸다 / 막혔다 두 가지만**

| | 알파 블렌딩 | 알파 클리핑 (clip) |
|---|---|---|
| 표현 | 반투명 (0~1 사이 전부) | 구멍 (있다/없다) |
| BlendState | 필요 | 불필요 |
| 그리는 순서 | 정렬 필요 | 상관없음 |
| 깊이 버퍼 | 쓰기 끄는 게 일반적 | 그대로 사용 |
| 예시 | 물, 유리, 연기 | 철조망, 나뭇잎, 풀, 머리카락 카드 |

> 후면 컬링 끄기 (NoCull RasterizerState)

- 철조망 상자는 구멍으로 **상자의 안쪽 면(뒷면)** 이 보여야 함
- 기본 래스터라이저는 뒷면을 컬링 → 안쪽 면이 안 그려짐
- 그래서 상자를 그릴 때만 `CullMode = D3D11_CULL_NONE`

```cpp
// 멤버 변수
ComPtr<ID3D11RasterizerState>   m_pNoCullRS;

// 생성 (초기화 때 한 번)
D3D11_RASTERIZER_DESC rsDesc{};
rsDesc.FillMode = D3D11_FILL_SOLID;
rsDesc.CullMode = D3D11_CULL_NONE;          // 앞, 뒤 모두 그림
rsDesc.FrontCounterClockwise = FALSE;
rsDesc.DepthClipEnable = TRUE;

if (FAILED(m_pDevice->CreateRasterizerState(&rsDesc, m_pNoCullRS.GetAddressOf())))
    return E_FAIL;

// 렌더링
m_pContext->RSSetState(m_pNoCullRS.Get());
// ... 철조망 상자 그리기 ...
m_pContext->RSSetState(nullptr);            // 기본값 복구 (CULL_BACK)
```

- Render에서 매 프레임 `RSSetState`로 바인드하고 있고 큐브만 그린다면, 기존 RasterizerState의 `CullMode`만 `D3D11_CULL_NONE`으로 바꿔도 됨

> 구멍이 뚫리는 원리

1. 텍스처의 알파 채널에 구멍 정보가 들어 있음 (철사 = 1.0, 구멍 = 0.0)
2. 큐브의 픽셀마다 PS가 실행되면서 자기 UV 위치의 알파를 읽음
3. `clip`이 구멍 픽셀을 버림

| 픽셀 | 계산 | 결과 |
|---|---|---|
| 철사 | 1.0 - 0.1 = 0.9 | 통과 → 그려짐 |
| 구멍 | 0.0 - 0.1 = -0.1 | 음수 → **버려짐** |

4. 버려진 픽셀은 OM 단계까지 가지 않음
   - 후면 버퍼에 색을 안 씀 → 원래 있던 색이 그대로 남음
   - 깊이 버퍼에 깊이를 안 씀 → 뒤에 있는 물체를 가리지 않음
   - 결국 그 자리는 **상자를 안 그린 것과 똑같음** → 구멍처럼 보임
5. 컬링을 껐으므로 구멍 너머로 상자 뒤쪽 면도 그려짐

```
카메라 →  [앞면: 철사 그림 / 구멍 버림]  →  [뒷면: 철조망]  →  배경
```

- 앞면, 뒷면 중 어느 걸 먼저 그려도 결과가 같음
  - 구멍 픽셀은 깊이를 안 썼으므로 뒷면이 나중에 그려져도 깊이 테스트를 통과함
  - 철사 픽셀은 깊이를 썼으므로 그 뒤의 뒷면은 제대로 가려짐
- 기준값(0.1)을 올리면 철사가 가늘어지고, 내리면 두꺼워짐

> clip = DX11의 알파 테스트

- DX9에는 알파 테스트가 렌더 스테이트(고정 기능)로 있었음
- DX10부터 이 기능이 빠졌기 때문에 셰이더에서 직접 `clip`으로 처리함

```cpp
// DX9 : 렌더 스테이트로 설정
m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
m_pDevice->SetRenderState(D3DRS_ALPHAREF, 0x1A);              // 기준값 (약 0.1)
m_pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);   // 알파 > 기준값이면 통과
```

```hlsl
// DX11 : 셰이더에서 직접
clip(vTexColor.a - 0.1f);   // 알파 < 0.1 이면 버림
```

| | DX9 알파 테스트 | DX11 `clip` |
|---|---|---|
| 위치 | 고정 기능 (렌더 스테이트) | 픽셀 셰이더 코드 |
| 기준값 | `D3DRS_ALPHAREF` | 직접 쓴 숫자 (0.1) |
| 비교 방식 | `D3DRS_ALPHAFUNC` | 직접 쓴 식 |
| 결과 | 실패하면 픽셀 폐기 | 음수면 픽셀 폐기 |

- DX11 쪽이 더 자유로움 → 알파가 아닌 값으로도 버릴 수 있음
  - 예) 노이즈 텍스처 값으로 `clip` → 타들어 가며 사라지는 디졸브 효과

> discard

```hlsl
if (vTexColor.a < 0.1f)
    discard;
```

- `clip(x)`는 "x가 음수면 `discard`"를 한 줄로 쓴 것. 둘 다 같은 기능

> 성능 주의

- PS에서 `clip`, `discard`를 쓰면 Early-Z(PS 실행 전에 깊이 테스트로 가려진 픽셀을 미리 거르는 최적화)가 제한될 수 있음
  - 픽셀이 버려질지 PS를 실행해 봐야 알기 때문
- 그래서 실제 게임에서는 철조망, 나뭇잎처럼 구멍이 필요한 오브젝트만 `clip` 있는 셰이더(패스)로 그리고, 일반 오브젝트는 `clip` 없는 셰이더로 그림

</details>

<details>
	<summary> 11. 안개 (Fog) </summary>

- 블렌딩 "상태"는 아니지만, **조명색과 안개색을 섞는다**는 점에서 9장에 같이 나옴
- 효과
  - 먼 곳이 뿌옇게 → 날씨/분위기 표현
  - 먼 지형이 갑자기 튀어나오는(팝핑) 현상을 가려줌

> 공식

```
s = saturate( (dist - FogStart) / FogRange )
최종색 = lerp(조명색, 안개색, s) = 조명색 + s * (안개색 - 조명색)
```

- `dist` : 카메라 ~ 픽셀 거리
- `FogStart` : 안개가 시작되는 거리 (이것보다 가까우면 안개 없음)
- `FogRange` : 안개가 꽉 차기까지의 거리 범위 (FogStart + FogRange 부터는 완전히 안개색)
- `saturate` : 0 ~ 1 로 잘라줌

| 거리 | s | 결과 |
|---|---|---|
| dist ≤ FogStart | 0 | 조명색 그대로 |
| FogStart ~ FogStart+FogRange | 0 ~ 1 | 점점 안개색 |
| dist ≥ FogStart+FogRange | 1 | 완전히 안개색 |

> 상수 버퍼에 추가

```hlsl
cbuffer PerFrame : register(b1)
{
    // ... 기존 조명, 카메라 위치 ...
    float  g_FogStart;
    float  g_FogRange;
    float2 g_Pad;       // 16바이트 정렬용 패딩
    float4 g_FogColor;
};
```

- C++ 구조체도 같은 순서로 맞추고, 16바이트 정렬 주의 (7장 상수 버퍼 규칙)

> PS

```hlsl
float3 vToEye   = g_vCamPosition.xyz - In.vPosW;
float  fDistToEye = length(vToEye);
vToEye /= fDistToEye;                          // 정규화 (length를 재사용)

// ... 텍스처 샘플링 + 조명 계산 ...

// 안개 : 조명까지 끝난 색에 마지막으로 섞음
float fFogLerp = saturate((fDistToEye - g_FogStart) / g_FogRange);
vColor = lerp(vColor, g_FogColor, fFogLerp);

// 알파는 안개 뒤에 설정 (lerp가 알파까지 바꾸므로)
vColor.a = g_Material.Diffuse.a * vTexColor.a;
```

- 예제 값 : `FogColor = Silver`, `FogStart = 15`, `FogRange = 175`
- **배경 클리어 색을 안개색과 같게** 해야 자연스러움 (예제도 둘 다 Silver)
- 안개는 **스페큘러까지 포함한 최종색**에 적용 → 멀리 있으면 하이라이트도 사라짐

</details>

<details>
	<summary> 12. 예제(BlendDemo) 흐름 정리 </summary>

> 장면 구성

| 오브젝트 | 처리 방식 | 이유 |
|---|---|---|
| 언덕(Hills) | 불투명 + 안개 | 일반 지형 |
| 철조망 상자 | 알파 클리핑 + NoCull + 안개 | 구멍 뚫린 텍스처, 안쪽 면 보여야 함 |
| 물(Waves) | 알파 블렌딩(재질 알파 0.5) + 안개 | 반투명 |

> DrawScene 순서

```cpp
// 0. 배경을 안개색으로 클리어
ClearRenderTargetView(..., Silver);

// 1. 철조망 상자 : clip 사용 → 불투명 취급, 블렌딩 OFF
RSSetState(NoCullRS);
Draw(Box);                              // PS 안에서 clip(a - 0.1)
RSSetState(nullptr);

// 2. 언덕 : 불투명
Draw(Hills);

// 3. 물 : 마지막에 블렌딩 ON
OMSetBlendState(TransparentBS, blendFactor, 0xffffffff);
Draw(Waves);
OMSetBlendState(nullptr, blendFactor, 0xffffffff);   // 복구

Present();
```

- 키 입력으로 모드 전환 : 1 = 조명만, 2 = 텍스처, 3 = 텍스처 + 안개
- 물 텍스처는 `TexTransform` 행렬로 UV를 매 프레임 이동(Translation)시켜 흐르는 것처럼 보이게 함

```hlsl
// VS : UV에 텍스처 변환 행렬 적용
Out.vTexCoord = mul(float4(In.vTexCoord, 0.f, 1.f), g_TexTransform).xy;
```

```cpp
// Update : 시간에 따라 UV 오프셋 증가 → Address가 WRAP이라 계속 반복됨
m_vWaterTexOffset.x += 0.1f  * fTimeDelta;
m_vWaterTexOffset.y += 0.05f * fTimeDelta;
XMMATRIX matScale  = XMMatrixScaling(5.f, 5.f, 0.f);   // 5번 반복
XMMATRIX matOffset = XMMatrixTranslation(m_vWaterTexOffset.x, m_vWaterTexOffset.y, 0.f);
XMStoreFloat4x4(&m_WaterTexTransform, matScale * matOffset);
```

</details>

<details>
	<summary> 13. 한 줄 요약 </summary>

- 블렌딩 = `Src * Fsrc ⊞ Dst * Fdst`. 계수(Fsrc, Fdst)와 연산(⊞)을 BlendState로 정함
- BlendState는 **초기화 때 생성, 그릴 때 OMSetBlendState로 켜고, 다 그리면 nullptr로 복구**
- 반투명 = `SRC_ALPHA / INV_SRC_ALPHA / ADD`, 가산 = `ONE / ONE / ADD`
- 알파 = 재질 Diffuse.a × 텍스처 a
- **불투명 먼저 → 투명은 나중에, 먼 것부터** (가산/곱셈은 순서 무관)
- 구멍만 뚫으면 되는 건 블렌딩 말고 `clip()` → 정렬 필요 없음 + NoCull
- 안개 = `lerp(조명색, 안개색, saturate((거리 - 시작) / 범위))`, 배경색 = 안개색

</details>
