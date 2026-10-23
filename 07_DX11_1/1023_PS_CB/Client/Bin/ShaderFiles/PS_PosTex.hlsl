
struct PS_IN
{
    float4 vPosition : SV_POSITION;
    float2 vTexcoord : TEXCOORD0;
};

struct PS_OUT
{
    float4 vColor : SV_TARGET0;
};


PS_OUT main(PS_IN In)
{
    PS_OUT Out;
    
    Out.vColor = In.vTexcoord.y;
    
    return Out;
}