

#include "../../../EngineSDK/Hlsl/Engine_Pixel_Shader_Defines.hlsli"


texture2D g_DiffuseTexture : register(t0);

struct PS_IN
{
    float4 vPosition : SV_POSITION;
    float4 vNormal : NORMAL;
    float4 vTangent : TANGENT;
    float4 vBinormal : BINORMAL;
    float2 vTexcoord : TEXCOORD0;
    float4 vWorldPos : TEXCOORD1;
};

struct PS_OUT
{
    float4 vColor : SV_TARGET0;
};


PS_OUT main(PS_IN In)
{
    PS_OUT Out;
    
    vector      vMtrlDiffuse = g_DiffuseTexture.Sample(g_LinearSampler, In.vTexcoord);   
    if (vMtrlDiffuse.a <= 0.3f)
        discard;
    
    vector vShade = max(dot(normalize(g_vLightDirection) * -1.f, normalize(In.vNormal)), 0.f)
        + (g_vLightAmbient * g_vMtrlAmbient);
    
    vector vReflect = reflect(normalize(g_vLightDirection), normalize(In.vNormal));
    vector vLook = In.vWorldPos - g_vCamPosition;
    
    float fSpecular = pow(max(dot(normalize(vReflect) * -1.f, normalize(vLook)), 0.f), 50.f);
    
    Out.vColor = g_vLightDiffuse * vMtrlDiffuse * vShade + 
        (g_vLightSpecular * g_vMtrlSpecular) * fSpecular;
    
    return Out;
}