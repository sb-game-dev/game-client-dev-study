#include "Engine_Pixel_Shader_Defines.hlsli"

struct PS_IN
{
    float4 vPosition : SV_POSITION;
    float2 vTexCoord : TEXCOORD0;
};

static const float3 g_vCenterColor = float3(1.0f, 0.9f, 0.7f);
static const float3 g_vSideColor = float3(1.0f, 0.0f, 0.0f);

float TopDownAlpha(float v)
{
    return (v - 1) * (v - 1);
}
float Ratio(float u)
{
    return 1.f - 4 * (u - 0.5f) * (u - 0.5f);
}

float4 PS_MAIN(PS_IN In) : SV_TARGET
{
    // 보간 비율
    float fRatio = Ratio(In.vTexCoord.x - 0.5f);
    
    // 색 보간
    float3 vColor = lerp(g_vSideColor, g_vCenterColor, fRatio);

    // 알파 보간 -> 위아래(v) * 좌우(u) -> 꼬리 모양
    float fAlpha = TopDownAlpha(In.vTexCoord.y) * fRatio;

    return float4(vColor, saturate(fAlpha));
}