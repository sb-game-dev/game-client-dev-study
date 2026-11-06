#include "Engine_Pixel_Shader_Defines.hlsli"

// 텍스처
Texture2D g_DiffuseTex : register(t0); //SRV

// 혼합맵 전용 텍스처
Texture2D g_LayerMap0 : register(t2); // 잔디     (blend.r)
Texture2D g_LayerMap1 : register(t3); // 흙       (blend.g)
Texture2D g_LayerMap2 : register(t4); // 아스팔트 (blend.b)
Texture2D g_BlendMap : register(t5);


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

struct PS_IN
{
    float4 vPosition : SV_POSITION; // 클립 공간 위치 (월드,뷰,투영변환 완료된 위치)
    float3 vPosW : POSITION;
    float3 vNormalW : NORMAL;
    float2 vTexCoord : TEXCOORD; //UV값
};

struct PS_IN_TERRAIN
{
    float4 vPosition : SV_POSITION;
    float3 vPosW : POSITION;
    float3 vNormalW : NORMAL;
    float2 vTex : TEXCOORD0; // 혼합맵용 0~1   
    float2 vTiledTex : TEXCOORD1; // 레이어용 반복   
};

struct PS_IN_MODEL
{
    float4 vPosition : SV_POSITION;
    float3 vNormalW : NORMAL;
    float4 vTangent : TANGENT;
    float4 vBinormal : BINORMAL;
    float2 vTexCoord : TEXCOORD0;
    float3 vPosW : TEXCOORD1;
};

float4 PS_MAIN(PS_IN In) : SV_TARGET //몇 번째 렌더타겟에 색을 쓸지
{
    float3 vNormal = normalize(In.vNormalW);
    float3 vToEye = normalize(g_vEye.xyz - In.vPosW);
    
    float4 vAmbient, vDiffuse, vSpec;
    float4 vAmbientSum, vDiffuseSum, vSpecSum;
    float4 vColor = float4(0.f, 0.f, 0.f, 0.f);
    float4 vTexColor = g_DiffuseTex.Sample(g_LinearSampler, In.vTexCoord);
    
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
    
    float distToEye = length(g_vEye.xyz - In.vPosW);
    float fogLerp = saturate((distToEye - g_fFogStart) / g_fFogRange);
    vColor.rgb = lerp(vColor.rgb, g_vFogColor.rgb, fogLerp);
    
    return vColor;
}

float4 PS_MAIN_MODEL(PS_IN_MODEL In) : SV_TARGET //몇 번째 렌더타겟에 색을 쓸지
{
    float3 vNormal = normalize(In.vNormalW);
    float3 vToEye = normalize(g_vEye.xyz - In.vPosW);
    
    float4 vAmbient, vDiffuse, vSpec;
    float4 vAmbientSum, vDiffuseSum, vSpecSum;
    float4 vColor = float4(0.f, 0.f, 0.f, 0.f);
    
    float4 vMtrlDiffuse = 1.f; //g_DiffuseTex.Sample(g_LinearSampler, In.vTexCoord);
    
    // 알파 테스트에 해당 알파값이 0.1이하인 경우 픽셀을 탈락시킴
    //clip(vTexColor.a - 0.1f);
    float4 vDirLight_Direction = float4(g_DirLight.Direction, 0.f);
    float4 vNormalW = float4(In.vNormalW, 0.f);
    float4 vPosW = float4(In.vPosW, 1.f);
    
    vector vShade = max(dot(normalize(g_DirLight.Direction) * -1.f, normalize(In.vNormalW)), 0.f)
        + (g_DirLight.Ambient * 1.f);
    
    vector vReflect = reflect(normalize(vDirLight_Direction), normalize(vNormalW));
    
    vector vLook = vPosW - g_vEye;
    
    float fSpecular = pow(max(dot(normalize(vReflect) * -1.f, normalize(vLook)), 0.f), 50.f);
    
    vColor = g_DirLight.Diffuse * vMtrlDiffuse * vShade +
        (g_DirLight.Specular * g_DirLight.Specular) * fSpecular;
    

    return vColor;
}



float4 PS_MAIN_NOLIGHT(PS_IN In) : SV_TARGET
{
    float4 vTexColor = g_DiffuseTex.Sample(g_LinearSampler, In.vTexCoord);
    // 알파 테스트에 해당 알파값이 0.1이하인 경우 픽셀을 탈락시킴
    clip(vTexColor.a - 0.1f);
    
    return vTexColor;
}

float4 PS_SHADOW(PS_IN In) : SV_TARGET
{
    float4 vTexColor = g_DiffuseTex.Sample(g_LinearSampler, In.vTexCoord);
    clip(vTexColor.a - 0.1f);
    return float4(0.f, 0.f, 0.f, 0.5f);
}

float4 PS_MAIN_SKY(PS_IN In) : SV_TARGET
{
    float4 vTexColor = g_DiffuseTex.Sample(g_LinearSampler, In.vTexCoord);
    
    //vTexColor.rgb = lerp(vTexColor.rgb, g_vFogColor.rgb, 0.7);
    
    return vTexColor;
}


float4 PS_TERRAIN(PS_IN_TERRAIN In) : SV_TARGET
{
    float3 vNormal = normalize(In.vNormalW);
    float3 vToEye = normalize(g_vEye.xyz - In.vPosW);

    //
    // Texturing
    //
    
    // Sample layers.
    float4 c0 = g_LayerMap0.Sample(g_LinearSampler, In.vTiledTex); // 잔디
    float4 c1 = g_LayerMap1.Sample(g_LinearSampler, In.vTiledTex); // 흙
    float4 c2 = g_LayerMap2.Sample(g_LinearSampler, In.vTiledTex); // 아스팔트

    // Sample the blend map.
    float4 t = g_BlendMap.Sample(g_LinearSampler, In.vTex);
    
    // 잔디 x R + 흙 x G + 아스팔트 x B
    float4 vTexColor = c0 * t.r + c1 * t.g + c2 * t.b;

    //
    // Lighting 
    //
    float4 vAmbient, vDiffuse, vSpec;
    float4 vAmbientSum, vDiffuseSum, vSpecSum;

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

    float4 vColor = vTexColor * (vAmbientSum + vDiffuseSum) + vSpecSum;
    vColor.a = 1.f;

    float distToEye = length(g_vEye.xyz - In.vPosW);
    float fogLerp = saturate((distToEye - g_fFogStart) / g_fFogRange);
    vColor.rgb = lerp(vColor.rgb, g_vFogColor.rgb, fogLerp);

    return vColor;
}

float4 PS_OCCLUDEDPLAYER(PS_IN_MODEL In) : SV_TARGET
{
    // 화면 픽셀 가져오기
    float2 vPix = In.vPosition.xy;
    
    // 격자선 -> 알파값으로 구현
    float2 vCell = frac(vPix / 6.f); // 6픽셀 격자
    float fLine = (vCell.x < 0.4f || vCell.y < 0.4f) ? 1.f : 0.f; // 선 두께 0.4
    
    float fAlpha = (0.2f + fLine * 0.5f);
    
    return float4(float3(0.3f, 0.75f, 1.0f), saturate(fAlpha));
}