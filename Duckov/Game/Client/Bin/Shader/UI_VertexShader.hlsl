
#include "Engine_Vertex_Shader_Defines.hlsli"

struct VS_IN
{
    float3 vPosition : POSITION;
    float3 vNormal : NORMAL;
    float2 vTexCoord : TEXCOORD; //UV값
};

struct VS_IN_INST
{
    float3 vPosition : POSITION;
    float3 vNormal : NORMAL;
    float2 vTexCoord : TEXCOORD; //UV값
    row_major float4x4 matWorld : WORLD;
};

struct VS_IN_POS
{
    float3 vPosition : POSITION;
};

struct VS_OUT
{
    float4 vPosition : SV_POSITION; // 클립 공간 위치 (월드,뷰,투영변환 완료된 위치)
    float3 vPosW : POSITION;
    float3 vNormalW : NORMAL;
    float2 vTexCoord : TEXCOORD; //UV값
};

struct VS_OUT_POS
{
    float4 vPosition : SV_POSITION; // 클립 공간 위치 (월드,뷰,투영변환 완료된 위치)
};

VS_OUT VS_MAIN_UI(VS_IN In)
{
    VS_OUT Out;

    float4 vPosW = mul(float4(In.vPosition, 1.f), g_matWorld);
    Out.vPosW = vPosW.xyz;
    Out.vNormalW = mul(In.vNormal, (float3x3) g_matWorldInvTranspose);
    
    Out.vPosition = mul(mul(vPosW, g_OrthoViewMatrix), g_OrthoProjMatrix);
    Out.vTexCoord = In.vTexCoord;
    return Out;
}


VS_OUT VS_MAIN_INST_UI(VS_IN_INST In)
{
    VS_OUT Out;

    float4 vPosW = mul(float4(In.vPosition, 1.f), In.matWorld);
    Out.vPosW = vPosW.xyz;
    Out.vNormalW = mul(In.vNormal, (float3x3) In.matWorld);
    
    Out.vPosition = mul(mul(vPosW, g_OrthoViewMatrix), g_OrthoProjMatrix);
    Out.vTexCoord = In.vTexCoord;
    return Out;
}

VS_OUT_POS VS_UI_SCOPE(VS_IN_POS In)
{
    VS_OUT_POS Out;
    float4 vPos = mul(float4(In.vPosition, 1.f), g_matWorld);
    Out.vPosition = mul(mul(vPos, g_OrthoViewMatrix), g_OrthoProjMatrix);    
    return Out;
}