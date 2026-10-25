cbuffer cbCamera : register(b1)
{
    float4x4 g_matView;
    float4x4 g_matProj;
    float3 g_vEye;
    float g_Pad;
};

static const float2 g_vWinSize = float2(1280.f, 720.f); 

Texture2DArray g_IconArray : register(t0);
SamplerState g_Sampler : register(s0);

struct VS_IN
{
    float3 vPosition : POSITION; 
    float3 vNormal : NORMAL;
    float2 vTexCoord : TEXCOORD0;
    float4 vRect : UIRECT;
    float4 vColor : UICOLOR;
    float4 vShape : UISHAPE;
    float4 vUV : UIUV;
};

struct VS_OUT
{
    float4 vPosition : SV_POSITION;
    float2 vLocal : TEXCOORD0; 
    float2 vTexCoord : TEXCOORD1;
    nointerpolation float4 vColor : TEXCOORD2;
    nointerpolation float4 vShape : TEXCOORD3;
    nointerpolation float2 vSize : TEXCOORD4;
};

VS_OUT VS_MAIN(VS_IN In)
{
    VS_OUT Out;
    float2 vSize = In.vRect.zw;
    float2 vCenter = In.vRect.xy + vSize * 0.5f; 
    float2 vLocal = In.vPosition.xy * vSize;
    float2 vOrtho = float2(vCenter.x - g_vWinSize.x * 0.5f,
                            g_vWinSize.y * 0.5f - vCenter.y) + vLocal;

    Out.vPosition = mul(mul(float4(vOrtho, 1.f, 1.f), g_matView), g_matProj);
    Out.vLocal = vLocal;
    Out.vTexCoord = lerp(In.vUV.xy, In.vUV.zw, In.vTexCoord);
    Out.vColor = In.vColor;
    Out.vShape = In.vShape;
    Out.vSize = vSize;
    return Out;
}

float SdRoundRect(float2 p, float2 halfSize, float r)
{
    float2 q = abs(p) - halfSize + r;
    return length(max(q, 0.f)) + min(max(q.x, q.y), 0.f) - r;
}

float4 PS_MAIN(VS_OUT In) : SV_TARGET
{
    if (In.vShape.z > 0.5f)    
        return g_IconArray.Sample(g_Sampler, float3(In.vTexCoord, In.vShape.w)) * In.vColor;

    float r = min(In.vShape.x, min(In.vSize.x, In.vSize.y) * 0.5f);
    float d = SdRoundRect(In.vLocal, In.vSize * 0.5f, r);
    float a = saturate(0.5f - d);
    if (In.vShape.y > 0.f)
        a *= saturate(d + In.vShape.y + 0.5f);
    return float4(In.vColor.rgb, In.vColor.a * a);
}