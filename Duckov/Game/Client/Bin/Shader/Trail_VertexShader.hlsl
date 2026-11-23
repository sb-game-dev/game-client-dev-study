#include "Engine_Vertex_Shader_Defines.hlsli"

struct VS_IN
{
    float3 vPosition : POSITION;
    float3 vNormal : NORMAL;
    float2 vTexCoord : TEXCOORD;
};

struct VS_OUT
{
    float4 vPosition : SV_POSITION;
    float2 vTexCoord : TEXCOORD;
};

VS_OUT VS_MAIN(VS_IN In)
{
    VS_OUT Out;
    Out.vPosition = mul(mul(mul(float4(In.vPosition, 1.f), g_matWorld), g_ViewMatrix), g_ProjMatrix);
    Out.vTexCoord = In.vTexCoord;
    return Out;
}