
#include "Engine_Vertex_Shader_Defines.hlsli"

struct VS_IN
{
    float3 vPosition : POSITION;
    float3 vNormal : NORMAL;
    float3 vTexcoord : TEXCOORD;
};

struct VS_OUT
{
    float4 vPosition : SV_POSITION;
    float3 vPosW : POSITION;
    float3 vNormalW : NORMAL;
    float3 vTexCoord : TEXCOORD; //UV°ª
};

struct VS_OUT_SKY
{
    float4 vPosition : SV_POSITION;
    float3 vNormal : NORMAL;
    float3 vTexcoord : TEXCOORD;
};

VS_OUT VS_MAIN(VS_IN In)
{
    VS_OUT Out;

    float4 vPosW = mul(float4(In.vPosition, 1.f), g_matWorld);
    Out.vPosW = vPosW.xyz;
    Out.vNormalW = mul(In.vNormal, (float3x3) g_matWorldInvTranspose);
    
    Out.vPosition = mul(mul(vPosW, g_ViewMatrix), g_ProjMatrix);
    Out.vTexCoord = In.vTexcoord;
    return Out;
}

VS_OUT_SKY VS_MAIN_SKY(VS_IN In)
{
    VS_OUT_SKY Out;
    
    float4 vPosition = mul(float4(In.vPosition, 1.f), g_matWorld);
    vPosition = mul(vPosition, g_ViewMatrix);
    vPosition = mul(vPosition, g_ProjMatrix);
    
    Out.vPosition = vPosition;
    Out.vNormal = In.vNormal;
    Out.vTexcoord = In.vTexcoord;
    
    return Out;
}


