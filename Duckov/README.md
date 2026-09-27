# 3D 공부 정리

### Chapter6. DX11 그리기 연산

<details>
  <summary> 0. 멤버 변수 설정 </summary>
```cpp
#pragma once
#include "Engine_Defines.h"
NS_BEGIN(Engine)
class ENGINE_DLL CGameObject
{
protected:
	CGameObject(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	virtual ~CGameObject() = default;

public:
	virtual HRESULT		Initialize();
	virtual void		Update(f32_t fDeltaTime);
	virtual void		LateUpdate(f32_t fDeltaTime);
	virtual HRESULT		Render();
	

	virtual	void		SetPos(float3_t vPos) { m_vInfo[static_cast<uint32_t>(INFO::POS)] = vPos; }
	virtual	void		MovePos(XMVECTOR vDir, f32_t fSpeed, f32_t fDeltaTime);
	virtual	void		SetWorld(XMMATRIX matWorld)		{ XMStoreFloat4x4(&m_matWorld, matWorld); }
	virtual	void		SetWorld(float4x4_t matWorld)	{ m_matWorld = matWorld; }
	virtual	float3_t	GetInfo(INFO eID)				{ return m_vInfo[static_cast<int>(eID)]; }

	virtual XMMATRIX	GetWorld();

protected:
	ComPtr<ID3D11Device>				m_pDevice = { nullptr };
	ComPtr<ID3D11DeviceContext>			m_pContext = { nullptr };

	ComPtr<ID3D11Buffer>				m_pVB;				// 버텍스 버퍼
	ComPtr<ID3D11Buffer>				m_pIB;				// 인덱스 버퍼
	uint32_t							m_iIndexCnt;		// 인덱스 개수
	ComPtr<ID3D11Buffer>				m_pCB;				// 변환 정보를 가지고있는 상수버퍼

	ComPtr<ID3D11InputLayout>			m_pInputLayout;		// 정점 메모리 해석표(FVF의 역할)

	ComPtr<ID3D11VertexShader>			m_pVS;				// 버텍스 셰이더
	ComPtr<ID3D11PixelShader>			m_pPS;				// 픽셀 셰이더
	ComPtr<ID3D11RasterizerState>		m_pRS;				// 레스터라이저

	float4x4_t			m_matWorld;

	float3_t			m_vInfo[static_cast<int>(INFO::END)];

	float3_t			m_vScale = { 1.f,1.f,1.f };
	
	f32_t               m_fRotX = 0.f;
	f32_t               m_fRotY = 0.f;
	f32_t               m_fRotZ = 0.f;

	f32_t				m_fSpeed = 1.f;
};
NS_END
```
</details>

<details>
  <summary> 1. 정점과 입력 배치 </summary>

```cpp
// 버텍스에 사용할 정점의 구조체를 만들어야 함
// 이 예제에서는 VTXCOL 이라는 구조체를 선언하여 사용함

typedef struct tagVtxColor
{
  // 멤버 변수 2개(위치, 색상)
	float3_t	vPosition;  
	float4_t	vColor;

  // 입력 배치(InputLayout)에 사용할 정보 선언 -> DX9의 FVF와 비슷한 역할
  // 정점 구조체를 서술하는 D3D11_INPUT_LEELMENT_DESC들의 배열
  // static으로 선언하여 VTXCOL의 크기에 영향을 주지 않음. sizeof(VTXCOL) == 28 -> float3(12) + float4(16)
  // constexpr을 사용하여 구조체 내부에서 static멤버를 선언과 동시에 초기화
  // 셰이더 파일의 : 뒤에 있는 시멘트값과 맞춰줘야 함
	static constexpr D3D11_INPUT_ELEMENT_DESC Elements[iNumElements] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

  // D3D11_INPUT_LEELMENT_DESC 배열 원소의 개수(멤버 변수의 개수)
	static constexpr uint32_t iNumElements = static_cast<uint32_t>(std::size(Elements)); 
}VTXCOL;

// 정점 정보를 저장
VTXCOL vertices[] =
{
    { float3_t(-0.5f, -0.5f, -0.5f), float4_t(Colors::White)},
    { float3_t(-0.5f, +0.5f, -0.5f), float4_t(Colors::Black)},
    { float3_t(+0.5f, +0.5f, -0.5f), float4_t(Colors::Red)},
    { float3_t(+0.5f, -0.5f, -0.5f), float4_t(Colors::Green)},
    { float3_t(-0.5f, -0.5f, +0.5f), float4_t(Colors::Blue)},
    { float3_t(-0.5f, +0.5f, +0.5f), float4_t(Colors::Yellow)},
    { float3_t(+0.5f, +0.5f, +0.5f), float4_t(Colors::Cyan)},
    { float3_t(+0.5f, -0.5f, +0.5f), float4_t(Colors::Magenta)}
};

// 버퍼 정보 서술
D3D11_BUFFER_DESC   VBDesc{};
VBDesc.ByteWidth = sizeof(vertices);           // 정점 배열의 크기(버퍼의 크기)
VBDesc.Usage     = D3D11_USAGE_IMMUTABLE;      // 정점의 사용 용도(버퍼의 정보를 생성이후에는 바꾸지 않는다.)
VBDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;   // BindFlag(버텍스 버퍼)

// 버퍼 SubResourceData
D3D11_SUBRESOURCE_DATA  VBData{};
VBData.pSysMem = vertices;  // 정점 버퍼를 초기화할 자료를 담은 시스템 메모리 배열을 가리키는 포인터

// 버퍼 생성
if (FAILED(m_pDevice->CreateBuffer(&VBDesc, &VBData, &m_pVB)))
    return E_FAIL;
```
</details>

<details>
  <summary> 2. 인덱스 버퍼 </summary>

```cpp
// 인덱스 정보 선언
UINT indices[] = {
     0, 1, 2,
     0, 2, 3,

     4, 6, 5,
     4, 7, 6,

     4, 5, 1,
     4, 1, 0,

     3, 2, 6,
     3, 6, 7,

     1, 5, 6,
     1, 6, 2,

     4, 0, 3,
     4, 3, 7
};

// 버퍼 정보 서술
D3D11_BUFFER_DESC IBDesc{};
IBDesc.ByteWidth = sizeof(indices);  
IBDesc.Usage     = D3D11_USAGE_IMMUTABLE;
IBDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

D3D11_SUBRESOURCE_DATA IBData{};
IBData.pSysMem = indices;
// 인덱스 버퍼 생성
if (FAILED(m_pDevice->CreateBuffer(&IBDesc, &IBData, &m_pIB)))
    return E_FAIL;
```
</details>

<details>
  <summary> 3. 상수 버퍼 </summary>

```cpp
// 월드, 뷰, 투영 변환행렬과 같은 정보를 버텍스 셰이더에 전달하기 위한 버퍼
// 상수 버퍼를 초기화 할 때 SubResource는 nullptr로 설정. 나중에 UpdateSubresource 할 예정
// 버퍼 정보 서술
D3D11_BUFFER_DESC CBDesc{};
CBDesc.ByteWidth = sizeof(CB_TRANSFORM);
CBDesc.Usage     = D3D11_USAGE_DEFAULT;         // 매 프레임 버퍼의 내용을 바꾸기 위한 설정
CBDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;  // 상수 버퍼임을 나타내는 BindFlag

// 상수 버퍼 생성
if (FAILED(m_pDevice->CreateBuffer(&CBDesc, nullptr, &m_pCB)))
    return E_FAIL;
```
</details>

<details>
  <summary> 4. 셰이더 코드(.hlsl) </summary>

```cpp
// cbuffer -> c++에서 넘겨주는 상수 데이터 묶음
// register(b0) -> 상수 버퍼 슬롯 0번(객체의 월드 변환 행렬)
cbuffer cbPerObject : register(b0)
{
    float4x4 g_matWorld;
};

// register(b1) -> 상수 버퍼 슬롯 1번(카메라에서 설정하는 뷰, 투영 변환 행렬)
cbuffer cbCamera : register(b1)
{
    float4x4 g_matView;
    float4x4 g_matProj;
}

cbuffer cbPerFrame
{
    float3 gLightDirection;
    float3 gLightPosition;
    float4 gLightColor;
};

cbuffer cbRarely
{
    float4 gFogColor;
    float gFogStart;
    float gFogEnd;
};

// VS_MAIN의 입력 구조체
struct VS_IN
{
    float3 vPosition : POSITION;
    float4 vColor : COLOR;
};

// VS_MAIN의 출력 구조체
struct VS_OUT
{
    // SV_ 로 시작하는 시멘틱은 사용자가 임의로 설정하는 값이 아닌 의미가 정해져있는 값
    float4 vPosition : SV_POSITION; // 클립 공간 위치
    float4 vColor : COLOR;
};

VS_OUT VS_MAIN(VS_IN In)
{
    VS_OUT Out;

    float4 vPosition = float4(In.vPosition, 1.f);// 행렬 연산을 하기 위해 w = 1 추가(위치니까 1 추가, 방향이면 0 추가)
    //mul(벡터, 행렬) 곱연산
    vPosition = mul(vPosition, g_matWorld);     // 로컬       -> 월드
    vPosition = mul(vPosition, g_matView);      // 월드       -> 뷰스페이스
    vPosition = mul(vPosition, g_matProj);      // 뷰스페이스 -> 투영  (z나누기 직전, z나누기는 VS끝나고 레스터라이저에서 수행)

    Out.vPosition = vPosition;
    Out.vColor = In.vColor;
    return Out;
}
// VS_MAIN이 반환한 Out값의 이후 흐름 (레스터라이저)
// 1. PrimitiveTopology에서 지정한 방식으로 VS의 출력 3개를 묶어 삼각형 하나를 만듬
// 2. 클립 공간에서 -w ≤ x ≤ w, -w ≤ y ≤ w,  0 ≤ z ≤ w 아래 조건을 벗어나는 부분을 잘라냄
// 3. 원근 나누기(w나누기)를 통해 NDC 공간으로 바꿈 -> -1 ≤ x ≤ 1, -1 ≤ y ≤ 1,  0 ≤ z ≤ 1
// 4. 후면 컬링(삼각형 두르기 컬링)
// 5. 뷰포트 변환 x -> 0 ~ Width, y -> 0 ~ Height, z -> MinDepth ~ MaxDepth
// 6. 래스터화 + 속성 보간(원근 보정)
//    삼각형이 덮는 픽셀을 골라내고, 픽셀마다 VS_OUT의 속성(색, UV 등)을 보간해서
//    PS 입력(픽셀 좌표 + 보간된 속성)으로 만드는 단계

float4 PS_MAIN(VS_OUT In) : SV_TARGET   //몇 번째 렌더타겟에 색을 쓸지
{
    return In.vColor;  // 위치정보는 위 흐름 중 6. 래스터화 단계에서 이미 저장되어있음
}
// PS_Main이 반환한 값(색) + 래스터라이저의 픽셀 좌표(x,y), 보간된 깊이 값이 출력 병합기로 이동(OutputMerger)
// 1. 깊이테스트, 스텐실 테스트
// 2. 블렌드 상태에 따라 블렌딩
// 3. 렌더타겟에 기록

```

</details>

<details>
  <summary> 5. 셰이더 컴파일 </summary>

```cpp
    // Blob은 크기가 정해진 바이트 덩어리를 담는 COM객체
    // 컴파일 결과를 담으면 바이트코드상자(pVSBlob, pPSBlob)
    // 에러메세지를 담으면 문자열 상수가 됨
    // 컴파일 결과인 Blob 정보를 이용하여 버텍스 셰이더객체, 픽셀 셰이더 객체를 생성함
    ComPtr<ID3DBlob> pVSBlob, pPSBlob, pErrBlob;

    uint32_t iFlags = 0;
#ifdef _DEBUG
    iFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
    // 셰이더를 디버그 모드에서 컴파일한다. | 컴파일시 최적화를 사용하지 않는다(디버깅에 유용함)
#endif
    //VS 컴파일
    if (FAILED(D3DCompileFromFile(
        L"../Shader/Shader_VtxCol.hlsl",   // 파일 경로 (작업 디렉터리 기준)
        nullptr,                           // 이 책에서는 사용하지 않는 고급 옵션(항상 NULL 또는 0)
        nullptr,                           // 이 책에서는 사용하지 않는 고급 옵션(항상 NULL 또는 0)
        "VS_MAIN",                         // 진입점 함수 이름
        "vs_5_0",                          // 타깃: 버텍스 셰이더, 셰이더 모델 5.0
        iFlags,                            // 컴파일 옵션
        0,                                 // 이 책에서는 사용하지 않는 고급 효과 컴파일 옵션(항상 NULL 또는 0)
        &pVSBlob,                          // 결과: 컴파일된 바이트코드
        &pErrBlob)))                       // 실패 시 에러 메시지
    {
        if (pErrBlob) OutputDebugStringA((char*)pErrBlob->GetBufferPointer());
        return E_FAIL;
    }
    // PS 컴파일
    if (FAILED(D3DCompileFromFile(L"../Shader/Shader_VtxCol.hlsl", nullptr, nullptr,
        "PS_MAIN", "ps_5_0", iFlags, 0, &pPSBlob, &pErrBlob)))
    {
        if (pErrBlob) OutputDebugStringA((char*)pErrBlob->GetBufferPointer());
        return E_FAIL;
    }

    // 버텍스 셰이더 객체 생성
    if (FAILED(m_pDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), nullptr, &m_pVS)))
        return E_FAIL;

    // 픽셀 셰이더 객체 생성
    if (FAILED(m_pDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), nullptr, &m_pPS)))
        return E_FAIL;
```
</details>

<details>
  <summary> 6. InputLayout 생성 </summary>

```cpp
// Input Layout 생성 (VS 바이트코드와 대조)
if (FAILED(m_pDevice->CreateInputLayout(VTXCOL::Elements,               // 정점 구조체를 서술하는 D3D11_INPUT_LEELMENT_DESC들의 배열
                                        VTXCOL::iNumElements,           // 배열 원소의 개수
                                        pVSBlob->GetBufferPointer(),    // 정점셰이더를 컴파일해서 얻은 바이트코드를 가리키는 포인터
                                        pVSBlob->GetBufferSize(),       // 바이트코드의 크기
                                        &m_pInputLayout)))              // 생성된 입력 배치를 돌려줄 포인터
    return E_FAIL;
```
</details>

<details>
  <summary> 7. 래스터라이저 설정 </summary>

```cpp
// 레스터라이저 설정
D3D11_RASTERIZER_DESC rsDesc{};
rsDesc.FillMode = D3D11_FILL_SOLID;         // D3D11_FILL_WIREFRAME , D3D11_FILL_SOLID
rsDesc.CullMode = D3D11_CULL_BACK;          // D3D11_CULL_BACK , D3D11_CULL_FRONT
rsDesc.FrontCounterClockwise = false;       // 시계방향이 전면
rsDesc.DepthClipEnable = true;

m_pDevice->CreateRasterizerState(&rsDesc, m_pRS.GetAddressOf());
```
</details>









