// cbuffer -> c++에서 넘겨주는 상수 데이터 묶음
// register(b0) -> 상수 버퍼 슬롯 0번
cbuffer TransformBuffer : register(b0)
{
    matrix g_WorldMatrix;
    matrix g_ViewMatrix;
    matrix g_ProjMatrix;
};

struct VS_IN
{
    float3 vPosition : POSITION;
    float4 vColor : COLOR;
};

struct VS_OUT
{
    float4 vPosition : SV_POSITION;
    float4 vColor : COLOR;
};

VS_OUT VS_MAIN(VS_IN In)
{
    VS_OUT Out;

    float4 vPosition = float4(In.vPosition, 1.f);// 행렬 연산을 하기 위해 w = 1 추가(위치니까 1 추가, 방향이면 0 추가)
    //mul(벡터, 행렬) 곱연산
    vPosition = mul(vPosition, g_WorldMatrix);  // 로컬       -> 월드
    vPosition = mul(vPosition, g_ViewMatrix);   // 월드       -> 뷰스페이스
    vPosition = mul(vPosition, g_ProjMatrix);   // 뷰스페이스 -> 투영  (z나누기 직전, z나누기는 VS끝나고 레스터라이저에서 수행)

    Out.vPosition = vPosition;
    Out.vColor = In.vColor;
    return Out;
}

float4 PS_MAIN(VS_OUT In) : SV_TARGET
{
    return In.vColor;
}