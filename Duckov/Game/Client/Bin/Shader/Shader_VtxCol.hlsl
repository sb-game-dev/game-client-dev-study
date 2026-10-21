// cbuffer -> c++에서 넘겨주는 상수 데이터 묶음
// register(b0) -> 상수 버퍼 슬롯 0번
// register(b1) -> 상수 버퍼 슬롯 1번

cbuffer cbPerObject : register(b0)
{
    float4x4 g_matWorld;
};

cbuffer cbCamera : register(b1)
{
    float4x4 g_matView;
    float4x4 g_matProj;
    float3 g_vEye;
    float g_Pad;
}

cbuffer cbMousePos : register(b2)
{
    float2 g_MousePos;
    float g_fRange;
    float Pad2;
}

struct VS_IN
{
    float3 vPosition : POSITION;
    float4 vColor : COLOR;
};

cbuffer cbFog : register(b5)
{
    float4 g_vFogColor; // 안개 색
    float g_fFogStart; // 안개 시작 위치
    float g_fFogRange; // 안개 범위
    float2 g_vFogPad; // 패딩용 변수
}

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

float4 PS_SHADOW(VS_OUT In) : SV_TARGET
{
    return float4(0.f, 0.f, 0.f, 0.5f);
}

float4 PS_OCCLUDEDPLAYER(VS_OUT In) : SV_TARGET
{
    return float4(0.f, 0.25f, 0.25f, 0.5f);
}

float4 PS_SCOPE(VS_OUT In) : SV_TARGET
{
    if ((g_MousePos.x - In.vPosition.x) * (g_MousePos.x - In.vPosition.x) + (g_MousePos.y - In.vPosition.y) * (g_MousePos.y - In.vPosition.y) < g_fRange * g_fRange)
    {
        if ((g_MousePos.x - In.vPosition.x) * (g_MousePos.x - In.vPosition.x) + (g_MousePos.y - In.vPosition.y) * (g_MousePos.y - In.vPosition.y) < 5.f * 5.f)
            return float4(0.6f, 0.f, 0.f, 0.6f);
        else if(abs(g_MousePos.x - In.vPosition.x) < 2.f || abs(g_MousePos.y - In.vPosition.y) < 2.f)
            return float4(0.f, 0.f, 0.f, 0.6f);
        else
            return float4(0.f, 0.f, 0.f, 0.f);        
    }
    else
    {
        return float4(0.f, 0.f, 0.f, 0.6f);  
    }
}