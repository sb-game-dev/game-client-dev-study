#include "../../../EngineSDK/Hlsl/Engine_Pixel_Shader_Defines.hlsli"

textureCUBE g_Texture[4] : register(t0);

struct PS_IN
{
    float4 vPosition : SV_POSITION;
    float3 vTexcoord : TEXCOORD0;
};

struct PS_OUT
{
    float4 vColor : SV_TARGET0;
};


PS_OUT main(PS_IN In)
{
    PS_OUT Out;
    
    Out.vColor = g_Texture[3].Sample(g_LinearSampler, In.vTexcoord);
    
    return Out;
}