
#include "Engine_Vertex_Shader_Defines.hlsli"

// 지형 전체에 레이어를 반복할 횟수 (지형 크기 : 320(정점 수) * 2(간격) / 잔디 크기 tileSize 4m)
static const float2 g_vTexScale = float2(160.f, 160.f);

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

struct VS_OUT
{
    float4 vPosition : SV_POSITION; // 클립 공간 위치 (월드,뷰,투영변환 완료된 위치)
    float3 vPosW : POSITION;
    float3 vNormalW : NORMAL;
    float2 vTexCoord : TEXCOORD; //UV값
};

struct VS_OUT_TERRAIN
{
    float4 vPosition : SV_POSITION;
    float3 vPosW : POSITION;
    float3 vNormalW : NORMAL;
    float2 vTex : TEXCOORD0; // 혼합맵용 0~1   
    float2 vTiledTex : TEXCOORD1; // 레이어용 반복   
};

VS_OUT VS_MAIN(VS_IN In)
{
    VS_OUT Out;

    float4 vPosW = mul(float4(In.vPosition, 1.f), g_matWorld);
    Out.vPosW = vPosW.xyz;
    Out.vNormalW = mul(In.vNormal, (float3x3) g_matWorldInvTranspose);
    
    Out.vPosition = mul(mul(vPosW, g_ViewMatrix), g_ProjMatrix);
    Out.vTexCoord = In.vTexCoord;
    return Out;
}


VS_OUT VS_MAIN_INST(VS_IN_INST In)
{
    VS_OUT Out;

    float4 vPosW = mul(float4(In.vPosition, 1.f), In.matWorld);
    Out.vPosW = vPosW.xyz;
    Out.vNormalW = mul(In.vNormal, (float3x3) In.matWorld);
    
    Out.vPosition = mul(mul(vPosW, g_ViewMatrix), g_ProjMatrix);
    Out.vTexCoord = In.vTexCoord;
    return Out;
}

VS_OUT_TERRAIN VS_TERRAIN(VS_IN In)
{
    VS_OUT_TERRAIN Out;

    float4 vPosW = mul(float4(In.vPosition, 1.f), g_matWorld);
    Out.vPosW = vPosW.xyz;
    Out.vNormalW = mul(In.vNormal, (float3x3) g_matWorldInvTranspose);
    Out.vPosition = mul(mul(vPosW, g_ViewMatrix), g_ProjMatrix);

    Out.vTex = In.vTexCoord;
    Out.vTiledTex = In.vTexCoord * g_vTexScale; // Tile layer textures over terrain.
    return Out;
}

