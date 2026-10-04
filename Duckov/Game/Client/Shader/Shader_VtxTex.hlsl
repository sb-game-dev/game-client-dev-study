// cbuffer -> c++에서 넘겨주는 상수 데이터 묶음
// register(b0) -> 상수 버퍼 슬롯 0번
// register(b1) -> 상수 버퍼 슬롯 1번

#include "LightHelper.hlsli"

cbuffer cbPerObject : register(b0)
{
    float4x4 g_matWorld;
    float4x4 g_matWorldInvTranspose;
    Material g_Material;
};

cbuffer cbCamera : register(b1)
{
    float4x4 g_matView;
    float4x4 g_matProj;
    float3 g_vEye;
    float g_Pad;
}

cbuffer cbPointLight : register(b2)
{
    PointLight g_PointLight;
}

cbuffer cbDirLight : register(b3)
{
    DirectionalLight g_DirLight;
}

cbuffer cbSpotLight : register(b4)
{
    SpotLight g_SpotLight;
}
Texture2D g_DiffuseTex : register(t0);

SamplerState g_Sampler : register(s0);

struct VS_IN
{
    float3 vPosition : POSITION;
    float3 vNormal : NORMAL;
    float2 vTexCoord : TEXCOORD;
};

struct VS_OUT
{
    float4 vPosition : SV_POSITION; // 클립 공간 위치 (월드,뷰,투영변환 완료된 위치)
    float3 vPosW : POSITION;
    float3 vNormalW : NORMAL;
    float2 vTexCoord : TEXCOORD;
};

VS_OUT VS_MAIN(VS_IN In)
{
    VS_OUT Out;

    float4 vPosW = mul(float4(In.vPosition, 1.f), g_matWorld);
    Out.vPosW = vPosW.xyz;
    Out.vNormalW = mul(In.vNormal, (float3x3) g_matWorldInvTranspose);
    
    Out.vPosition = mul(mul(vPosW, g_matView), g_matProj);
    Out.vTexCoord = In.vTexCoord;
    return Out;
}

float4 GetHeightColor(float y)
{
    if (y < -10.f)
        return float4(1.0f, 0.96f, 0.62f, 1.f); // 모래
    if (y < 5.f)
        return float4(0.48f, 0.77f, 0.46f, 1.f); // 연한 풀
    if (y < 12.f)
        return float4(0.1f, 0.48f, 0.19f, 1.f); // 진한 풀
    if (y < 20.f)
        return float4(0.45f, 0.39f, 0.34f, 1.f); // 바위
    return float4(1.f, 1.f, 1.f, 1.f); // 눈
}

float4 PS_MAIN(VS_OUT In) : SV_TARGET //몇 번째 렌더타겟에 색을 쓸지
{
    //float3 vNormal = normalize(In.vNormalW);
    //float3 vToEye = normalize(g_vEye - In.vPosW);
    //
    //float4 vAmbient, vDiffuse, vSpec;
    //float4 vColor = float4(0.f, 0.f, 0.f, 0.f);
    //
    //// 높이에 따라 머티리얼 색만 교체 (Specular는 cbuffer 값 그대로)
    //Material tMtrl = g_Material;
    ////float4 vHeightColor = GetHeightColor(In.vPosW.y);
    ////tMtrl.Ambient = vHeightColor;
    ////tMtrl.Diffuse = vHeightColor;
    //
    //ComputePointLight(tMtrl, g_PointLight, In.vPosW, vNormal, vToEye, vAmbient, vDiffuse, vSpec);
    //vColor += vAmbient + vDiffuse + vSpec;
    //
    //ComputeDirectionalLight(tMtrl, g_DirLight, vNormal, vToEye, vAmbient, vDiffuse, vSpec);
    //vColor += vAmbient + vDiffuse + vSpec;
    //
    //ComputeSpotLight(tMtrl, g_SpotLight, In.vPosW, vNormal, vToEye, vAmbient, vDiffuse, vSpec);
    //vColor += vAmbient + vDiffuse + vSpec;
    //
    //vColor.a = tMtrl.Diffuse.a; // 알파값은 diffuse의 알파값으로 대체
    //
    //return vColor;
    
    return g_DiffuseTex.Sample(g_Sampler, In.vTexCoord);
}