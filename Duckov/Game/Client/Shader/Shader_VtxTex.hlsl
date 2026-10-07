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
cbuffer cbFog : register(b5)
{
    float4 g_vFogColor; // 안개 색
    float g_fFogStart;  // 안개 시작 위치
    float g_fFogRange;  // 안개 범위
    float2 g_vFogPad;   // 패딩용 변수
    
}

Texture2D g_DiffuseTex : register(t0);  //SRV

SamplerState g_Sampler : register(s0);

struct VS_IN
{
    float3 vPosition : POSITION;
    float3 vNormal : NORMAL;
    float2 vTexCoord : TEXCOORD; //UV값
};

struct VS_OUT
{
    float4 vPosition : SV_POSITION; // 클립 공간 위치 (월드,뷰,투영변환 완료된 위치)
    float3 vPosW : POSITION;
    float3 vNormalW : NORMAL;
    float2 vTexCoord : TEXCOORD;    //UV값
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

float4 PS_MAIN(VS_OUT In) : SV_TARGET //몇 번째 렌더타겟에 색을 쓸지
{
    float3 vNormal = normalize(In.vNormalW);
    float3 vToEye = normalize(g_vEye - In.vPosW);
    float distToEye = length(vToEye);
    
    float4 vAmbient, vDiffuse, vSpec;
    float4 vAmbientSum, vDiffuseSum, vSpecSum;
    float4 vColor = float4(0.f, 0.f, 0.f, 0.f);
    float4 vTexColor = g_DiffuseTex.Sample(g_Sampler, In.vTexCoord);
    
    // 알파 테스트에 해당 알파값이 0.1이하인 경우 픽셀을 탈락시킴
    clip(vTexColor.a - 0.1f);
    
    ComputePointLight(g_Material, g_PointLight, In.vPosW, vNormal, vToEye, vAmbient, vDiffuse, vSpec);
    vAmbientSum = vAmbient;
    vDiffuseSum = vDiffuse;
    vSpecSum = vSpec;
    
    ComputeDirectionalLight(g_Material, g_DirLight, vNormal, vToEye, vAmbient, vDiffuse, vSpec);
    vAmbientSum += vAmbient;
    vDiffuseSum += vDiffuse;
    vSpecSum += vSpec;
    
    ComputeSpotLight(g_Material, g_SpotLight, In.vPosW, vNormal, vToEye, vAmbient, vDiffuse, vSpec);
    vAmbientSum += vAmbient;
    vDiffuseSum += vDiffuse;
    vSpecSum += vSpec;
    
    vColor = vTexColor * (vAmbientSum + vDiffuseSum) + vSpecSum;
    vColor.a = g_Material.Diffuse.a * vTexColor.a;
    
    float fogLerp = saturate((distToEye - g_fFogStart) / g_fFogRange);
    vColor.rgb = lerp(vColor.rgb, g_vFogColor.rgb, fogLerp);
    
    return vColor;
}

float4 PS_MAIN_NOLIGHT(VS_OUT In) : SV_TARGET
{
    float4 vTexColor = g_DiffuseTex.Sample(g_Sampler, In.vTexCoord);
    // 알파 테스트에 해당 알파값이 0.1이하인 경우 픽셀을 탈락시킴
    clip(vTexColor.a - 0.1f);
    return vTexColor;
}
