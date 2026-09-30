# 3D 공부 정리

### Chapter6. DX11 그리기 연산 과정1 - 큐브 출력

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
m_iNumIndices = indices.size();
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

### Chapter6. DX11 그리기 연산 과정2 - 지형 출력

<details>
	<summary> 1. 지형 버퍼 생성 </summary>

```cpp

HRESULT CHill::Initialize()
{
    if (FAILED(__super::Initialize()))
        return E_FAIL;

    uint32_t    ivtxCntX = 129;
    uint32_t    ivtxCntZ = 129;

    uint32_t    ivtxCnt = ivtxCntX * ivtxCntZ;
    uint32_t    iFaceCnt = (ivtxCntX - 1) * (ivtxCntZ - 1) * 2;
    f32_t       fHalfWidth = 0.5f * (ivtxCntX -1);
    f32_t       fHalfDepth = 0.5f * (ivtxCntZ -1);

    f32_t   dx = 1.f;//128.f / (ivtxCntZ);
    f32_t   dz = 1.f;//128.f / (ivtxCntX);

    f32_t   du = 1.f / (ivtxCntX);
    f32_t   dv = 1.f / (ivtxCntZ);

	// MESHDATA 구조체는 단순히 버텍스 벡터, 인덱스 벡터로 이루어진 구조체
    MESHDATA tMeshData = {};
    tMeshData.Vertices.resize(ivtxCnt);
    tMeshData.Indices.resize(iFaceCnt * 3);

	// 지형의 중심을 (0,0)으로 설정, 왼쪽 위 부터 정점 생성
    for (uint32_t i = 0; i < ivtxCntZ; ++i)
    {
        float z = fHalfDepth - i * dz;
        for (uint32_t j = 0; j < ivtxCntX; ++j)
        {
            float x = -fHalfWidth + j * dx;
            tMeshData.Vertices[i * ivtxCntX + j].vPosition = float3_t(x, 0.f, z);
            
            // 조명
            tMeshData.Vertices[i * ivtxCntX + j].vNormal = float3_t(0.f, 1.f, 0.f);
            tMeshData.Vertices[i * ivtxCntX + j].vTangentU = float3_t(1.f, 0.f, 0.f);

            // 텍스처uv값 설정
            tMeshData.Vertices[i * ivtxCntX + j].TexC.x = j*du;
            tMeshData.Vertices[i * ivtxCntX + j].TexC.y = i*dv;
        }
    }

    uint32_t k = 0;
    for (uint32_t i = 0; i < ivtxCntZ - 1; ++i)
    {
        for (uint32_t j = 0; j < ivtxCntX - 1; ++j)
        {
            tMeshData.Indices[k] 	 = i * ivtxCntX + j;
            tMeshData.Indices[k + 1] = i * ivtxCntX + j + 1;
            tMeshData.Indices[k + 2] = (i + 1) * ivtxCntX + j;
            tMeshData.Indices[k + 3] = (i + 1) * ivtxCntX + j;
            tMeshData.Indices[k + 4] = i * ivtxCntX + j + 1;
            tMeshData.Indices[k + 5] = (i + 1) * ivtxCntX + j + 1;

            k += 6;
        }
    }
    m_iIndexCnt = tMeshData.Indices.size();
    vector<VTXCOL> vertices(tMeshData.Vertices.size());
    for (size_t i = 0; i < tMeshData.Vertices.size(); ++i)
    {
        float3_t p = tMeshData.Vertices[i].vPosition;
        p.y = GetHeight(p.x, p.z);
        vertices[i].vPosition = p;
        if (p.y < -10.0f)
            vertices[i].vColor = XMFLOAT4(1.0f, 0.96f, 0.62f, 1.0f);
        else if (p.y < 5.0f)
            vertices[i].vColor = XMFLOAT4(0.48f, 0.77f, 0.46f, 1.0f);
        else if (p.y < 12.0f)
            vertices[i].vColor = XMFLOAT4(0.1f, 0.48f, 0.19f, 1.0f);
        else if (p.y < 20.0f)
            vertices[i].vColor = XMFLOAT4(0.45f, 0.39f, 0.34f, 1.0f);
        else
            vertices[i].vColor = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
    }


    // 정점 버퍼 생성
    D3D11_BUFFER_DESC   VBDesc{};
    VBDesc.ByteWidth = sizeof(VTXCOL) * tMeshData.Vertices.size();
    VBDesc.Usage = D3D11_USAGE_IMMUTABLE;
    VBDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA  VBData{};
    VBData.pSysMem = &vertices[0];  // 정점 버퍼를 초기화할 자료를 담은 시스템 메모리 배열을 가리키는 포인터
    if (FAILED(m_pDevice->CreateBuffer(&VBDesc, &VBData, &m_pVB)))
        return E_FAIL;

    
    // 인덱스 버퍼 생성
    D3D11_BUFFER_DESC IBDesc{};
    IBDesc.ByteWidth = sizeof(UINT) * m_iIndexCnt;
    IBDesc.Usage = D3D11_USAGE_IMMUTABLE;
    IBDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;


    D3D11_SUBRESOURCE_DATA IBData{};
    IBData.pSysMem = &tMeshData.Indices[0];
    if (FAILED(m_pDevice->CreateBuffer(&IBDesc, &IBData, &m_pIB)))
        return E_FAIL;

    // 상수 버퍼 생성
    D3D11_BUFFER_DESC CBDesc{};
    CBDesc.ByteWidth = sizeof(CB_TRANSFORM);
    CBDesc.Usage = D3D11_USAGE_DEFAULT;
    CBDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

    // 상수 버퍼를 초기화 할 때 SubResource는 nullptr로 설정. 나중에 UpdateSubresource 할 예정
    if (FAILED(m_pDevice->CreateBuffer(&CBDesc, nullptr, &m_pCB)))
        return E_FAIL;

    // Blob은 크기가 정해진 바이트 덩어리를 담는 COM객체
    // 컴파일 결과를 담으면 바이트코드상자(pVSBlob, pPSBlob)
    // 에러메세지를 담으면 문자열 상수가 됨
    // Blob 정보를 이용하여 버텍스 셰이더객체, 픽셀 셰이더 객체를 생성함
    ComPtr<ID3DBlob> pVSBlob, pPSBlob, pErrBlob;

    uint32_t iFlags = 0;
#ifdef _DEBUG
    iFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
    // 셰이더를 디버그 모드에서 컴파일한다. | 컴파일시 최적화를 사용하지 않는다(디버깅에 유용함)
#endif
    //VS 컴파일
    if (FAILED(D3DCompileFromFile(
        L"../Shader/Shader_VtxCol.hlsl",  // 파일 경로 (작업 디렉터리 기준)
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

    // Input Layout 생성 (VS 바이트코드와 대조)
    if (FAILED(m_pDevice->CreateInputLayout(VTXCOL::Elements,               // 정점 구조체를 서술하는 D3D11_INPUT_LEELMENT_DESC들의 배열
        VTXCOL::iNumElements,           // 배열 원소의 개수
        pVSBlob->GetBufferPointer(),    // 정점셰이더를 컴파일해서 얻은 바이트코드를 가리키는 포인터
        pVSBlob->GetBufferSize(),       // 바이트코드의 크기
        &m_pInputLayout)))              // 생성된 입력 배치를 돌려줄 포인터
        return E_FAIL;

    // 레스터라이저 설정
    D3D11_RASTERIZER_DESC rsDesc{};
    rsDesc.FillMode = D3D11_FILL_SOLID;         //D3D11_FILL_WIREFRAME , D3D11_FILL_SOLID
    rsDesc.CullMode = D3D11_CULL_BACK;          // D3D11_CULL_BACK , D3D11_CULL_FRONT
    rsDesc.FrontCounterClockwise = false;       // 시계방향이 전면
    rsDesc.DepthClipEnable = true;

    m_pDevice->CreateRasterizerState(&rsDesc, m_pRS.GetAddressOf());
    return S_OK;
}
```
</details>

### Chapter7. DX11 조명1 - 점조명

<details>
	<summary> 1. 구조체 생성 </summary>

> 빛 구조체 

```cpp
// c++에서 선언한 구조체
struct PointLight
{
	PointLight() { ZeroMemory(this, sizeof(*this)); }

	float4_t	Ambient;
	float4_t	Diffuse;
	float4_t	Specular;

	float3_t	Position;
	f32_t		Range;

	float3_t	Att;
	f32_t		Pad;
};
typedef struct tagCBLight
{
	PointLight	tPointLight;	// 80 바이트
	float3_t	vEyePosW;		// 12 바이트
	f32_t		fPad;			// 4  바이트
}CB_LIGHT;					// 총 96 바이트 (16의 배수)
```

```hlsl
// hlsl에서 선언한 구조체
struct PointLight
{
    float4 Ambient;
    float4 Diffuse;
    float4 Specular;
    
    float3 Position;
    float  Range;
    
    float3 Att;
    float  Pad;
};
cbuffer cbLight : register(b2)
{
    PointLight  g_PointLight;
    float3      g_vEyePosW;
    float       g_fPad;
}
```

- **Pad를 두는 이유**: HLSL의 cbuffer는 16바이트(float4) 단위로 묶이고, 변수 하나가 16바이트 경계를 넘어갈 수 없다. 그래서 `float3` 뒤에 `float` 하나를 붙여 C++ 쪽 메모리 배치를 HLSL과 똑같이 맞춘다. 상수 버퍼의 `ByteWidth`도 16의 배수여야 한다.
- **Range**: 이 거리보다 멀리 있는 픽셀은 조명 계산을 생략한다.
- **Att**: 감쇠 계수 (a0, a1, a2). 감쇠 = `1 / (a0 + a1·d + a2·d²)`
- **register(b2)**: C++에서 `PSSetConstantBuffers(2, ...)`로 같은 슬롯 번호에 바인딩해야 한다.

> 재질(Material) 구조체

```cpp
// c++에서 선언한 구조체
typedef struct tagMaterial
{
	tagMaterial() { ZeroMemory(this, sizeof(*this)); }

	float4_t	Ambient;
	float4_t	Diffuse;
	float4_t	Specular;	// w = SpecPower (광택 지수)
	float4_t	Reflect;
}MATERIAL;					// 64 바이트
```

```hlsl
// hlsl에서 선언한 구조체
struct Material
{
    float4 Ambient;
    float4 Diffuse;
    float4 Specular; // w = SpecPower
    float4 Reflect;
};
```

> 버텍스 버퍼용 구조체

```cpp
// c++에서 선언한 구조체
typedef struct tagVtxNorm
{
	float3_t	vPosition;
	float3_t	vNormal;

	static constexpr uint32_t iNumElements = 2;
	static constexpr D3D11_INPUT_ELEMENT_DESC Elements[iNumElements] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT,0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

}VTXNORM;
```

```hlsl
// hlsl에서 선언한 구조체
struct VS_IN
{
    float3 vPosition    : POSITION;
    float3 vNormal      : NORMAL;
};

struct VS_OUT
{
    float4 vPosition    : SV_POSITION; 	// 클립 공간 위치 (월드,뷰,투영변환 완료된 위치)
    float3 vPosW        : POSITION;
    float3 vNormalW     : NORMAL; 		// 버텍스 셰이더 이후 픽셀 셰이더에서 필요하기 때문에 계산해서 넘겨줘야함
};
```

> 버텍스 셰이더와 픽셀 셰이더에 연결할 상수버퍼 구조체

```cpp
// c++에서 선언한 구조체
typedef struct tagCBPerObjectLit
{
	float4x4_t	mat_World;
	float4x4_t	mat_WorldInvTranspose;
	MATERIAL	tMaterial;
}CB_PER_OBJECT_LIT;
```

```hlsl
// hlsl에서 선언한 구조체
cbuffer cbPerObject : register(b0)
{
    float4x4 g_matWorld;
    float4x4 g_matWorldInvTranspose;
    Material g_Material;
};
```
</details>

<details> 
	<summary> 2. Hill의 법선 벡터 설정 </summary>

- Hill의 MeshData에서 기존에는 `vNormal = float3_t(0.f,1.f,0.f)` 이었으나 `vNormal = GetNormal(x,z)`로 변경
- 높이 함수 `y = f(x, z)`의 곡면에서 x방향 접선은 `(1, ∂f/∂x, 0)`, z방향 접선은 `(0, ∂f/∂z, 1)`
- 두 접선을 외적하면 법선 `(-∂f/∂x, 1, -∂f/∂z)`가 나오고, 이를 정규화해서 사용

> GetNormal()

```cpp
float3_t CHill::GetNormal(f32_t x, f32_t z)
{
    // y = 0.3f * (z * sinf(0.1f * x) + x * cosf(0.1f * z));
	// 편미분을 이용하여 법선벡터 구함
    f32_t fDfDx = 0.03f * z * cosf(0.1f * x) + 0.3f * cosf(0.1f * z);
    f32_t fDfDz = 0.3f * sinf(0.1f * x) - 0.03f * x * sinf(0.1f * z);
    float3_t vNormal = { -fDfDx,1.f,-fDfDz };
    XMStoreFloat3(&vNormal, XMVector3Normalize(XMLoadFloat3(&vNormal)));
    return vNormal;
}
```

> CHill::Initialize()

```cpp
for (uint32_t i = 0; i < ivtxCntZ; ++i)
{
    float z = fHalfDepth - i * dz;
    for (uint32_t j = 0; j < ivtxCntX; ++j)
    {
        float x = -fHalfWidth + j * dx;
        m_tMeshData.Vertices[i * ivtxCntX + j].vPosition = float3_t(x, 0.f, z);
        
        m_tMeshData.Vertices[i * ivtxCntX + j].vNormal = GetNormal(x, z);	//GetNormal로 변경
        m_tMeshData.Vertices[i * ivtxCntX + j].vTangentU = float3_t(1.f, 0.f, 0.f);

        m_tMeshData.Vertices[i * ivtxCntX + j].TexC.x = j*du;
        m_tMeshData.Vertices[i * ivtxCntX + j].TexC.y = i*dv;
    }
}
```
</details>

<details>
	<summary> 3. Hill의 버텍스 버퍼 및 머티리얼 설정 </summary>

- 기존에는 높이(y값)에 따라 색을 설정했으나 이제는 법선을 설정
- 높이와 무관하게 모든 버텍스가 같은 Material로 설정

```cpp
// 버텍스 버퍼 설정
vector<VTXNORM> vertices(m_tMeshData.Vertices.size());
for (size_t i = 0; i < m_tMeshData.Vertices.size(); ++i)
{
    float3_t& p = m_tMeshData.Vertices[i].vPosition;
    p.y = GetHeight(p.x, p.z);
    vertices[i].vPosition = p;
    vertices[i].vNormal = m_tMeshData.Vertices[i].vNormal; // 법선 설정
}

D3D11_BUFFER_DESC   VBDesc{}; 
VBDesc.ByteWidth = sizeof(VTXNORM) * m_tMeshData.Vertices.size();
VBDesc.Usage = D3D11_USAGE_IMMUTABLE;
VBDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

D3D11_SUBRESOURCE_DATA  VBData{};
VBData.pSysMem = &vertices[0];  
if (FAILED(m_pDevice->CreateBuffer(&VBDesc, &VBData, &m_pVB)))
    return E_FAIL;

// Material
m_tMaterial.Ambient = float4_t(0.48f, 0.77f, 0.46f, 1.f);
m_tMaterial.Diffuse = float4_t(0.48f, 0.77f, 0.46f, 1.f);
m_tMaterial.Specular = float4_t(0.2f, 0.2f, 0.2f, 16.f);   // w = 광택 지수, 0이면 안 됨
```
</details>

<details>
	<summary> 4. Hill::Render() </summary>

> cbPerObject 상수 버퍼 값 채우기

```cpp
XMMATRIX matWorld = GetWorld();

// 역전치 행렬 설정시 이동부분인 마지막 행은{0, 0, 0, 1}로 설정
// 주의: matWorld를 직접 바꾸면 mat_World에서도 이동 성분이 사라지므로 복사본을 사용
XMMATRIX matNoTrans = matWorld;
matNoTrans.r[3] = XMVectorSet(0.f, 0.f, 0.f, 1.f);
XMMATRIX matWorldInvTranspos = XMMatrixTranspose(XMMatrixInverse(nullptr, matNoTrans));

// HLSL은 기본이 column-major이므로 업로드하는 모든 행렬을 전치해서 넘긴다
// (역전치 행렬도 예외 없이 한 번 더 전치)
CB_PER_OBJECT_LIT cbData;
XMStoreFloat4x4(&cbData.mat_World, XMMatrixTranspose(matWorld));
XMStoreFloat4x4(&cbData.mat_WorldInvTranspose, XMMatrixTranspose(matWorldInvTranspos));
cbData.tMaterial = m_tMaterial;

m_pContext->UpdateSubresource(m_pCB.Get(), 0, nullptr, &cbData, 0, 0);
```

> 버텍스 셰이더와 픽셀 셰이더에 버퍼 세팅

```cpp
// 월드 변환을 위한 상수 버퍼
// Position, Normal 계산을 위해 matWorld, matWorldInvTranspose만 사용
m_pContext->VSSetConstantBuffers(0, //레지스터 슬롯 번호
    1,
    m_pCB.GetAddressOf());

// 조명 계산을 위한 상수 버퍼
// 조명 계산에 필요한 Material만 사용
m_pContext->PSSetConstantBuffers(0, //레지스터 슬롯 번호
    1,
    m_pCB.GetAddressOf());
```

</details>

<details>
	<summary> 5. 조명 생성 </summary>

> 조명 구조체 값 설정 (CPlayer에서 조명을 소유)

```cpp
m_tPointLight.Ambient = float4_t(0.3f, 0.3f, 0.3f, 1.f);
m_tPointLight.Diffuse = float4_t(0.7f, 0.7f, 0.7f, 1.f);
m_tPointLight.Specular = float4_t(0.7f, 0.7f, 0.7f, 1.f);
m_tPointLight.Att = float3_t(1.f, 0.1f, 0.05f);   // a0 = 1: 가까워도 과노출 안 됨
m_tPointLight.Range = 5.f;
```

> 점조명 상수버퍼 설정

```cpp
D3D11_BUFFER_DESC LightCBDesc{};
LightCBDesc.ByteWidth = sizeof(CB_LIGHT);
LightCBDesc.Usage = D3D11_USAGE_DEFAULT;
LightCBDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

if (FAILED(m_pDevice->CreateBuffer(&LightCBDesc, nullptr, &m_pLightCB)))
    return E_FAIL;
```

</details>

<details>
	<summary> 6. 조명 Bind </summary>

- 조명은 플레이어 머리 위에 있기 때문에 플레이어가 소유
- 조명 Bind는 Late_Update에서 호출

```cpp
void CPlayer::BindLight()
{
    // 점조명 위치 초기화
    float3_t vPos = m_vInfo[ETOUI(INFO::POS)];
    m_tPointLight.Position = float3_t(vPos.x, vPos.y + 2.f, vPos.z);

    // 조명 상수 버퍼 채우기
    CB_LIGHT cbLight;
    cbLight.tPointLight = m_tPointLight;
    // TODO: 카메라 오프셋을 하드코딩 중 -> 카메라가 바뀌면 스페큘러가 틀어지므로 실제 카메라 위치로 교체
    XMStoreFloat3(&cbLight.vEyePosW, XMLoadFloat3(&vPos) + XMVECTOR({ 0.f, 15.f, -5.f }));

    // 갱신하고 PS b2에 꽂기
    m_pContext->UpdateSubresource(m_pLightCB.Get(), 0, nullptr, &cbLight, 0, 0);
    m_pContext->PSSetConstantBuffers(2, 1, m_pLightCB.GetAddressOf());
}
```
</details>


<details>
	<summary> 7. 조명 연산 </summary>

> 퐁 셰이딩

| 용어 | 의미 | 내용 |
|---|---|---|
| Phong 반사 모델 (Phong reflection model) | 한 점의 색을 어떤 공식으로 계산할지 | Ambient + Diffuse + Specular |
| Phong 셰이딩 (Phong interpolation) | 그 공식을 어디서 계산할지 | 법선을 보간한 뒤 픽셀마다 조명 계산 |

> Phong 반사 모델 공식

```text
최종색 = Ambient + Diffuse + Specular

Ambient  = Ma ⊗ La
Diffuse  = max(N·L, 0) × (Md ⊗ Ld)
Specular = max(R·V, 0)^p × (Ms ⊗ Ls)      (N·L > 0 일 때만)

N : 표면 법선 (단위벡터)
L : 표면 → 광원 방향 (단위벡터)
V : 표면 → 눈 방향 (단위벡터)
R : L을 N 기준으로 반사한 벡터 = reflect(-L, N)
p : 광택 지수 (Shininess / SpecPower)
⊗ : 성분별 곱 (RGB 각각 곱하기)
M* : 재질 색, L* : 조명 색
```

**1. Ambient (주변광)**

벽이나 바닥에 여러 번 튕겨서 들어오는 간접광을 상수 하나로 흉내 낸 항. 방향과 상관없이 똑같이 더해지기 때문에, 이 항이 없으면 빛이 닿지 않는 면은 완전히 검게 나옴.  

```text
Ambient  = Ma ⊗ La
```

**2. Diffuse (난반사, Lambert)**

거친 표면은 빛을 모든 방향으로 고르게 흩뿌림. 그래서 보는 방향(V)과는 관계가 없고, 빛이 얼마나 정면으로 들어오는지만 중요.  

빛이 수직으로 들어오면(N·L = 1) 단위 면적에 에너지가 가장 많이 들어옴.  
빛이 비스듬해지면 같은 양의 빛이 더 넓은 면적에 퍼지므로 cosθ만큼 어두워짐(Lambert 코사인 법칙).  
N·L < 0이면 빛이 뒤에서 오는 것이므로 0으로 처리.  

```text
Diffuse  = max(N·L, 0) × (Md ⊗ Ld)

N : 표면 법선 (단위벡터)
L : 표면 → 광원 방향 (단위벡터)
```

**3. Specular (정반사, 하이라이트)**

매끄러운 표면에서 거울처럼 반사된 빛이 눈 방향과 가까울수록 밝게 보이는 항. 그래서 이 항만 시점(V)에 의존. 카메라가 움직이면 하이라이트도 따라서 이동.  

R·V는 반사 방향과 눈 방향 사이 각도의 코사인.  
지수 p는 하이라이트의 크기를 정함. p가 크면 좁고 날카로워지고(금속, 플라스틱), p가 작으면 넓고 뿌옇게 퍼짐(고무, 흙).  

```text
Specular = max(R·V, 0)^p × (Ms ⊗ Ls)      (N·L > 0 일 때만)

V : 표면 → 눈 방향 (단위벡터)
R : L을 N 기준으로 반사한 벡터 = reflect(-L, N)
p : 광택 지수 (Shininess / SpecPower)
p = 2   → 하이라이트가 넓게 번짐
p = 16  → 적당한 광택
p = 128 → 작은 점 같은 하이라이트
```

> Shader에서의 계산 (LightHelper.hlsli)

```hlsl
// out = 함수가 끝날 때 결과를 호출자 변수에 복사(레퍼런스와 결과가 비슷하지만 레퍼런스와 같지 않음)
// 들어오는 값이 정의되지 않으므로 모든 경로에서 반드시 값을 써야 함 (그래서 맨 처음에 0으로 초기화)
void ComputePointLight(Material mat, PointLight L, float3 pos, float3 normal, float3 toEye,
                       out float4 ambient, out float4 diffuse, out float4 spec)
{
    // Initialize outputs.
    ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
    diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
    spec = float4(0.0f, 0.0f, 0.0f, 0.0f);

	// The vector from the surface to the light.
    float3 lightVec = L.Position - pos;
		
	// The distance from surface to light.
    float d = length(lightVec);
	
	// Range test.
    if (d > L.Range)
        return;
		
	// Normalize the light vector.
    lightVec /= d;
	
	// Ambient term.
    ambient = mat.Ambient * L.Ambient;

	// Add diffuse and specular term, provided the surface is in 
	// the line of site of the light.

    float diffuseFactor = dot(lightVec, normal);

	// flatten -> GPU에게 실제로 분기하지말고 양쪽을 다 계산한 뒤 결과를 고르라
	[flatten]
    if (diffuseFactor > 0.0f)
    {
        // reflect 
        // -> 반사되어 나가는 벡터를 구하는 함수
        // -> 빛이 들어오는 방향을 매개변수로 받음 -> -lightVec
        float3 v = reflect(-lightVec, normal);
        float specFactor = pow(max(dot(v, toEye), 0.0f), mat.Specular.w);
					
        diffuse = diffuseFactor * mat.Diffuse * L.Diffuse;
        spec = specFactor * mat.Specular * L.Specular;
    }

	// Attenuate
    float att = 1.0f / dot(L.Att, float3(1.0f, d, d * d));

    diffuse *= att;
    spec *= att;
}
```

- 감쇠는 diffuse, spec에만 적용하고 ambient에는 적용하지 않는다. ambient는 특정 광원에서 직접 오는 빛이 아니라 주변 전체의 간접광을 흉내 낸 값이라, 광원과의 거리와 무관하게 둔다.

> 셰이더 진입점 (Shader_VtxNorm.hlsl)

```hlsl
VS_OUT VS_MAIN(VS_IN In)
{
    VS_OUT Out;

    float4 vPosW = mul(float4(In.vPosition, 1.f), g_matWorld);
    Out.vPosW = vPosW.xyz;

    // 법선은 방향 벡터이므로 이동이 없어야 함 -> 3x3으로 잘라서 곱함
    // 비균등 스케일에서도 법선이 표면에 수직이 되도록 역전치 행렬 사용
    Out.vNormalW = mul(In.vNormal, (float3x3) g_matWorldInvTranspose);

    Out.vPosition = mul(mul(vPosW, g_matView), g_matProj);
    return Out;
}

float4 PS_MAIN(VS_OUT In) : SV_TARGET
{
    // 래스터라이저가 보간한 법선은 길이가 1이 아니므로 다시 정규화
    float3 vNormal = normalize(In.vNormalW);
    float3 vToEye = normalize(g_vEyePosW - In.vPosW);

    float4 vAmbient, vDiffuse, vSpec;
    ComputePointLight(g_Material, g_PointLight, In.vPosW, vNormal, vToEye, vAmbient, vDiffuse, vSpec);
    float4 vColor = vAmbient + vDiffuse + vSpec;

    vColor.a = g_Material.Diffuse.a;    // 알파값은 diffuse의 알파값으로 대체

    return vColor;
}
```

</details>
