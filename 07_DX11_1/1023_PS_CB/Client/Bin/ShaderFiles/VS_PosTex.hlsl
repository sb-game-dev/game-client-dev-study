

cbuffer ObjectData : register(b0)
{
    matrix g_WorldMatrix;
};

cbuffer FrameData : register(b1)
{
    matrix g_ViewMatrix;
    matrix g_ProjMatrix;
};

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
    //vPosition = mul(vPosition, g_ViewMatrix);
    //vPosition = mul(vPosition, g_ProjMatrix);   
    
    Out.vPosition = vPosition;
    Out.vTexcoord = In.vTexcoord;   
    
    return Out;    
}