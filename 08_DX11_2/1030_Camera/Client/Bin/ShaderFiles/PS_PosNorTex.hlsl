
texture2D g_Texture : register(t0);

sampler g_PointSampler : register(s0);

struct PS_IN
{
    float4 vPosition : SV_POSITION;
    float4 vNormal : NORMAL;
    float2 vTexcoord : TEXCOORD0;
};

struct PS_OUT
{
    float4 vColor : SV_TARGET0;
};


PS_OUT main(PS_IN In)
{
    PS_OUT Out;
    
    Out.vColor = g_Texture.Sample(g_PointSampler, In.vTexcoord);
    
    return Out;
}