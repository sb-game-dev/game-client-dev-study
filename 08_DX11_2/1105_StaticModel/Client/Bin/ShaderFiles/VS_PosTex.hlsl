
#include "../../../EngineSDK/Hlsl/Engine_Vertex_Shader_Defines.hlsli"

/* VertexShader를 수행하기위한 진입점 함수 */ 
struct VS_IN
{
    float3 vPosition : POSITION;
    float2 vTexcoord : TEXCOORD0;
};

struct VS_OUT
{
    float4 vPosition : SV_POSITION;
    float2 vTexcoord : TEXCOORD0;
};

VS_OUT main(VS_IN In)
{
    VS_OUT Out;
    
    float4      vPosition = mul(float4(In.vPosition, 1.f), g_WorldMatrix);
    vPosition = mul(vPosition, g_OrthoViewMatrix);
    vPosition = mul(vPosition, g_OrthoProjMatrix);
    
    Out.vPosition = vPosition;
    Out.vTexcoord = In.vTexcoord;   
    
    return Out;    
}