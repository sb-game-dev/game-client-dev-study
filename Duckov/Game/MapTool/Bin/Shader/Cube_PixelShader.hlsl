#include "Engine_Pixel_Shader_Defines.hlsli"

textureCUBE g_Texture[4] : register(t0);

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
    float g_fFogStart; // 안개 시작 위치
    float g_fFogRange; // 안개 범위
    float2 g_vFogPad; // 패딩용 변수
}
cbuffer cbHitRaito : register(b7)
{
    float4 g_vHitRatio;
}
struct PS_IN_SKY
{
    float4 vPosition : SV_POSITION;
    float3 vNormal : NORMAL;
    float3 vTexcoord : TEXCOORD;
};
struct PS_IN
{
    float4 vPosition : SV_POSITION; // 클립 공간 위치 (월드,뷰,투영변환 완료된 위치)
    float3 vPosW : POSITION;
    float3 vNormalW : NORMAL;
    float3 vTexCoord : TEXCOORD; //UV값
};

struct PS_OUT
{
    float4 vColor : SV_TARGET0;
};


PS_OUT PS_MAIN_SKY(PS_IN_SKY In)
{
    PS_OUT Out;
    
    Out.vColor = g_Texture[0].Sample(g_LinearSampler, In.vTexcoord);
    
    return Out;
}

PS_OUT PS_MAIN (PS_IN In)
{
    float3 vNormal = normalize(In.vNormalW);
    float3 vToEye = normalize(g_vEye.xyz - In.vPosW);
    
    float4 vAmbient, vDiffuse, vSpec;
    float4 vAmbientSum, vDiffuseSum, vSpecSum;
    float4 vColor = float4(0.f, 0.f, 0.f, 0.f);
    float4 vTexColor = g_Texture[0].Sample(g_LinearSampler, In.vTexCoord);
    
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
    
    vColor.r = vColor.r + (1 - vColor.r) * g_vHitRatio.r;
    vColor.g = vColor.g + (1 - vColor.g) * g_vHitRatio.g;
    vColor.b = vColor.b + (1 - vColor.b) * g_vHitRatio.b;
    
    float distToEye = length(g_vEye.xyz - In.vPosW);
    float fogLerp = saturate((distToEye - g_fFogStart) / g_fFogRange);
    vColor.rgb = lerp(vColor.rgb, g_vFogColor.rgb, fogLerp);
    
    
    PS_OUT Out;
    Out.vColor = vColor;
    return Out;
}

PS_OUT PS_SHADOW(PS_IN In)
{
    PS_OUT Out;

    float4 vTexColor = g_Texture[0].Sample(g_LinearSampler, In.vTexCoord);
    clip(vTexColor.a - 0.1f);

    Out.vColor = float4(0.f, 0.f, 0.f, 0.5f);
    return Out;
}
