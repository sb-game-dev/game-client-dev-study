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



<details>
	<summary> 8. Render </summary>

> Scene_Render

```cpp
HRESULT CLevel_GamePlay::Render()
{
    // 카메라가 먼저 b1에 뷰/투영 행렬을 꽂아 둠
    // 상수 버퍼 슬롯은 다른 버퍼로 교체하기 전까지 컨텍스트에 계속 꽂혀 있으므로
    // 한 번만 Bind해도 이후 모든 오브젝트가 같은 뷰/투영을 공유함
    // 오브젝트 렌더(__super::Render)보다 먼저 호출해야 함
    if (FAILED(m_pCamera->Bind()))
        return E_FAIL;
    if (FAILED(__super::Render()))
        return E_FAIL;
    return S_OK;
}
```

> CameraInitialize & CameraLateUpdate & CameraBind

```cpp
typedef struct tagCBCamera
{
	float4x4_t ViewMatrix;
	float4x4_t ProjMatrix;
}CB_CAMERA;

HRESULT CCamera::Initialize()
{
	// 상수 버퍼 구조체 생성
	D3D11_BUFFER_DESC	CBDesc{};
	CBDesc.ByteWidth = sizeof(CB_CAMERA);
	CBDesc.Usage = D3D11_USAGE_DEFAULT;
	CBDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	
	// 버퍼 생성
	if (FAILED(m_pDevice->CreateBuffer(&CBDesc, nullptr, m_pCB.GetAddressOf())))
		return E_FAIL;
	return S_OK;
}
```

```cpp
void CCamera::LateUpdate(f32_t fDeltTime)
{
	// 매 프레임 뷰 행렬, 투영 행렬 계산
	XMMATRIX	matView = XMMatrixLookAtLH(XMLoadFloat3(&m_vEye), XMLoadFloat3(&m_vAt), XMLoadFloat3(&m_vUp));
	XMMATRIX	matProj = XMMatrixPerspectiveFovLH(m_fFov, m_fAspect, m_fNear, m_fFar);

	XMStoreFloat4x4(&m_matView, matView);
	XMStoreFloat4x4(&m_matProj, matProj);
}

HRESULT CCamera::Bind()
{
	CB_CAMERA	cbData;
	XMStoreFloat4x4(&cbData.ViewMatrix, XMMatrixTranspose(XMLoadFloat4x4(&m_matView)));
	XMStoreFloat4x4(&cbData.ProjMatrix, XMMatrixTranspose(XMLoadFloat4x4(&m_matProj)));

	// 카메라 상수 버퍼의 내용 갱신
	m_pContext->UpdateSubresource(m_pCB.Get(), 0, nullptr, &cbData, 0, 0);

	// VS의 상수 버퍼 슬롯 1번(register(b1))에 꽂기
	m_pContext->VSSetConstantBuffers(1, 1, m_pCB.GetAddressOf());
	return S_OK;
}
```

> Obj_Render

```cpp
HRESULT CCube::Render()
{    
	// 변환 행렬 계산 -> 상수 버퍼(월드 행렬) 갱신
	// 뷰/투영 행렬은 카메라가 b1에 이미 바인딩해 둠 → 여기서는 월드 행렬만 다룸
	XMMATRIX matWorld = GetWorld();

	// VS로 전달할 구조체 채우기
	// 전치하는 이유 :
	// DirectXMath의 XMFLOAT4X4는 메모리에 행 우선(row-major)으로 저장되고,
	// HLSL은 상수 버퍼의 행렬을 기본적으로 열 우선(column-major)으로 해석함
	// → 그대로 보내면 셰이더에서 전치된 행렬로 보이므로, 미리 전치해서 보내면 셰이더에서 원래 행렬로 보임
	// (대안 : 셰이더에서 row_major float4x4로 선언하거나, 컴파일 플래그 D3DCOMPILE_PACK_MATRIX_ROW_MAJOR 사용)
	CB_TRANSFORM cbData;
	XMStoreFloat4x4(&cbData.WorldMatrix, XMMatrixTranspose(matWorld));

	// 월드 행렬을 담는 m_pCB 버퍼로 복사 (USAGE_DEFAULT로 생성해서 드라이버를 통해 복사)
	// 아래에서 VS의 b0 레지스터에 꽂을 예정
	m_pContext->UpdateSubresource(m_pCB.Get(), 0, nullptr, &cbData, 0, 0);

	// ===== 파이프라인에 꽂기 (IA → VS → RS → PS → OM 순서) =====
	// 실제 사용은 Draw 호출 시점에 한꺼번에 이루어지므로 꽂는 순서 자체는 기능에 영향 없음

	// [IA] 입력 조립기 단계
	// 정점 하나의 크기와 버퍼의 시작 위치 설정 (둘 다 바이트 단위)
	uint32_t iStride = sizeof(VTXCOL);
	uint32_t iOffset = 0;

	// 정점 버퍼 꽂기
	// stride, offset을 주소로 넘기는 이유 : 버퍼를 여러 개 한 번에 꽂을 수 있으므로
	// 버퍼 개수만큼의 배열로 받음 → 지금은 1개라 변수 하나의 주소를 "원소 1개짜리 배열"로 넘김
	m_pContext->IASetVertexBuffers(0,                        // 정점 버퍼를 붙이기 시작할 입력 슬롯 번호
									1,                       // 입력 슬롯에 붙이고자 하는 버퍼의 개수
                               		m_pVB.GetAddressOf(),    // 버퍼를 담은 배열의 첫 원소를 가리키는 포인터
                               		&iStride,                // 버퍼 한 원소(정점 하나)의 바이트 크기
									&iOffset);               // 버퍼 시작에서부터 건너뛸 바이트 수
                                      	                     // 정점 n개를 건너뛰려면 n * sizeof(VTXCOL)
 
	// 인덱스 버퍼 꽂기
	m_pContext->IASetIndexBuffer(m_pIB.Get(),               // 인덱스 버퍼
	                             DXGI_FORMAT_R32_UINT,      // 인덱스 하나의 형식 (인덱스 배열 타입 uint32_t와 일치해야 함)
	                                                        // 정점이 65535개 이하라면 R16_UINT + uint16_t로 메모리 절반
	                             0);                        // 버퍼 시작에서부터 건너뛸 바이트 수

	// 기본 도형 위상 : 정점 3개씩 묶어 삼각형 하나
	m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
	// InputLayout 꽂기 (DX9 FVF의 역할)
	// 차이점 : FVF는 고정된 플래그 조합이었지만, InputLayout은 생성 시 셰이더 입력 시그니처와 검증됨
	m_pContext->IASetInputLayout(m_pInputLayout.Get());

	// [VS] 버텍스 셰이더 단계
	// 정점 버퍼에서 정점을 "읽어서" 월드 → 뷰 → 투영 변환한 결과를 다음 단계(래스터라이저)로 넘김
	// 정점 버퍼에 결과를 다시 쓰지 않음 → 같은 정점 버퍼로 월드 행렬만 바꿔 여러 번 그릴 수 있음
	m_pContext->VSSetShader(m_pVS.Get(), nullptr, 0);

	// VS의 상수 버퍼 슬롯 0번에 월드 행렬 버퍼 꽂기
	m_pContext->VSSetConstantBuffers(0,                     // register(b0)과 연결됨
   		                             1,
									 m_pCB.GetAddressOf());

	// [RS] 래스터라이저 단계 (고정 기능, 상태 객체로 설정)
	m_pContext->RSSetState(m_pRS.Get());

	// [PS] 픽셀 셰이더 단계 -> 지금은 보간된 색을 그대로 반환
	m_pContext->PSSetShader(m_pPS.Get(), nullptr, 0);

	// [OM] 출력 병합기 / 뷰포트
	// 이 함수에서는 설정하지 않음 → 프레임 시작 시 설정한 렌더 타깃(OMSetRenderTargets)과
	// 뷰포트(RSSetViewports)가 그대로 사용됨

	// 그리기 (이 시점에 위에서 꽂은 설정들이 실제로 사용됨)
	m_pContext->DrawIndexed(m_iNumIndices,  // IndexCount : 그릴 인덱스 개수 (인덱스 버퍼 생성 시 저장해 둔 값, 큐브는 36)
 	                       0,              // StartIndexLocation : 인덱스 버퍼에서 읽기 시작할 인덱스 위치
      	                  0);             // BaseVertexLocation : 읽어 온 인덱스 값에 더해지는 정수
                       	                 // 예) 인덱스 0, 1, 2 + BaseVertexLocation 8 → 8, 9, 10번 정점을 읽음
                              	          // 여러 메시를 정점 버퍼 하나에 이어 붙여 두고 인덱스 버퍼를 재사용할 때 사용

	return S_OK;
}
```
</details>






