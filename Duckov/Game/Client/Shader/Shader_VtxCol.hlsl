// cbuffer -> c++에서 넘겨주는 상수 데이터 묶음
// register(b0) -> 상수 버퍼 슬롯 0번

cbuffer cbPerObject : register(b0)
{
    float4x4 g_matWorld;
};

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

struct VS_IN
{
    float3 vPosition : POSITION;
    float4 vColor : COLOR;
};

struct VS_OUT
{
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

float4 PS_MAIN(VS_OUT In) : SV_TARGET   //몇 번째 렌더타겟에 색을 쓸지
{
    return In.vColor;
}