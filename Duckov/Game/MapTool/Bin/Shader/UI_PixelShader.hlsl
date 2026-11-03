
#include "Engine_Pixel_Shader_Defines.hlsli"

// 텍스처
Texture2D g_DiffuseTex : register(t0); //SRV

cbuffer cbMousePos : register(b2)
{
    float2 g_MousePos;
    float g_fRange;
    float Pad2;
}

struct PS_IN
{
    float4 vPosition : SV_POSITION; // 클립 공간 위치 (월드,뷰,투영변환 완료된 위치)
    float3 vPosW : POSITION;
    float3 vNormalW : NORMAL;
    float2 vTexCoord : TEXCOORD; //UV값
};

struct PS_IN_POS
{
    float4 vPosition : SV_POSITION;
};

float4 PS_MAIN(PS_IN In) : SV_TARGET
{
    float4 vTexColor = g_DiffuseTex.Sample(g_Sampler, In.vTexCoord);
    // 알파 테스트에 해당 알파값이 0.1이하인 경우 픽셀을 탈락시킴
    clip(vTexColor.a - 0.1f);
    
    return vTexColor;
}

float4 PS_SCOPE(PS_IN_POS In) : SV_TARGET
{
    if ((g_MousePos.x - In.vPosition.x) * (g_MousePos.x - In.vPosition.x) + (g_MousePos.y - In.vPosition.y) * (g_MousePos.y - In.vPosition.y) < g_fRange * g_fRange)
    {
        if ((g_MousePos.x - In.vPosition.x) * (g_MousePos.x - In.vPosition.x) + (g_MousePos.y - In.vPosition.y) * (g_MousePos.y - In.vPosition.y) < 5.f * 5.f)
            return float4(0.6f, 0.f, 0.f, 0.6f);
        else if (abs(g_MousePos.x - In.vPosition.x) < 2.f || abs(g_MousePos.y - In.vPosition.y) < 2.f)
            return float4(0.f, 0.f, 0.f, 0.6f);
        else
            return float4(0.f, 0.f, 0.f, 0.f);
    }
    else
    {
        return float4(0.f, 0.f, 0.f, 0.6f);
    }
}