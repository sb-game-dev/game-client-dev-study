// cbuffer -> c++에서 넘겨주는 상수 데이터 묶음
// register(b0) -> 상수 버퍼 슬롯 0번
// register(b1) -> 상수 버퍼 슬롯 1번

#include "LightHelper.hlsli"

cbuffer cbPerObject : register(b0)
{
    row_major float4x4 g_matWorld;
    row_major float4x4 g_matWorldInvTranspose;
    Material g_Material;
};

cbuffer FrameData : register(b1)
{
    row_major matrix g_ViewMatrix, g_ProjMatrix;
    row_major matrix g_OrthoViewMatrix, g_OrthoProjMatrix;
    
    row_major matrix g_ViewInverseMatrix, g_ProjInverseMatrix;
    row_major matrix g_OrthoViewInverseMatrix, g_OrthoProjInverseMatrix;
    float4 g_vEye;
};

cbuffer cbPointLight : register(b2)
{
    PointLight g_PointLight;
}

cbuffer cbDirLight : register(b3)
{
    DirectionalLight g_DirLight;
}

cbuffer cbSpotLight : register(b4)
{
    SpotLight g_SpotLight;
}
cbuffer cbFog : register(b5)
{
    float4 g_vFogColor; // 안개 색
    float g_fFogStart; // 안개 시작 위치
    float g_fFogRange; // 안개 범위
    float2 g_vFogPad; // 패딩용 변수
}

Texture2D g_DiffuseTex : register(t0); //SRV

SamplerState g_Sampler : register(s0);

// 상수로 선언
static const float2 g_TexC[4] =
{
    float2(0.0f, 1.0f),
	float2(0.0f, 0.0f),
	float2(1.0f, 1.0f),
	float2(1.0f, 0.0f)
};

struct VS_IN
{
    float3 PosW : POSITION;
    float2 SizeW : SIZE;
};

struct VS_OUT
{
    float3 CenterW : POSITION;
    float2 SizeW : SIZE;
};

struct GeoOut
{
    float4 PosH : SV_POSITION;
    float3 PosW : POSITION;
    float3 NormalW : NORMAL;
    float2 Tex : TEXCOORD;
    uint PrimID : SV_PrimitiveID;
};

VS_OUT VS_MAIN(VS_IN In)
{
    VS_OUT vout;
    
    vout.CenterW = In.PosW;
    vout.SizeW = In.SizeW;

    return vout;
}
[maxvertexcount(4)]
void GS_MAIN(point VS_OUT gin[1],
        uint primID : SV_PrimitiveID,
        inout TriangleStream<GeoOut> triStream)
{
    float3 up = float3(0.0f, 1.0f, 0.0f);
    //float3 look = g_vEye - gin[0].CenterW;
    //look.y = 0.0f; // y-axis aligned, so project to xz-plane
    //look = normalize(look);
    
    float3 look = float3(g_ViewMatrix._31, 0, g_ViewMatrix._33);
    look = normalize(-look);
    float3 right = cross(up, look);
    
    float halfWidth = 0.5f * gin[0].SizeW.x;
    float halfHeight = 0.5f * gin[0].SizeW.y;
	
    float4 v[4];
    v[0] = float4(gin[0].CenterW + halfWidth * right - halfHeight * up, 1.0f);
    v[1] = float4(gin[0].CenterW + halfWidth * right + halfHeight * up, 1.0f);
    v[2] = float4(gin[0].CenterW - halfWidth * right - halfHeight * up, 1.0f);
    v[3] = float4(gin[0].CenterW - halfWidth * right + halfHeight * up, 1.0f);

	//
	// Transform quad vertices to world space and output 
	// them as a triangle strip.
	//
    GeoOut gout;
	[unroll]
    for (int i = 0; i < 4; ++i)
    {
        gout.PosH = mul(mul(v[i], g_ViewMatrix),g_ProjMatrix);
        gout.PosW = v[i].xyz;
        gout.NormalW = look;
        gout.Tex = g_TexC[i];
        gout.PrimID = primID;
		
        triStream.Append(gout);
    }
}

float4 PS_MAIN(GeoOut In) : SV_TARGET //몇 번째 렌더타겟에 색을 쓸지
{
    float3 vNormal = normalize(In.NormalW);
    float3 vToEye = normalize(g_vEye.xyz - In.PosW);
    
    float4 vAmbient, vDiffuse, vSpec;
    float4 vAmbientSum, vDiffuseSum, vSpecSum;
    float4 vColor = float4(0.f, 0.f, 0.f, 0.f);
    
    //float3 uvw = float3(In.Tex, In.PrimID % 4);
    float4 vTexColor = g_DiffuseTex.Sample(g_Sampler, In.Tex);
    
    // 알파 테스트에 해당 알파값이 0.1이하인 경우 픽셀을 탈락시킴
    clip(vTexColor.a - 0.1f);
    
    ComputePointLight(g_Material, g_PointLight, In.PosW, vNormal, vToEye, vAmbient, vDiffuse, vSpec);
    vAmbientSum = vAmbient;
    vDiffuseSum = vDiffuse;
    vSpecSum = vSpec;
    
    ComputeDirectionalLight(g_Material, g_DirLight, vNormal, vToEye, vAmbient, vDiffuse, vSpec);
    vAmbientSum += vAmbient;
    vDiffuseSum += vDiffuse;
    vSpecSum += vSpec;
    
    ComputeSpotLight(g_Material, g_SpotLight, In.PosW, vNormal, vToEye, vAmbient, vDiffuse, vSpec);
    vAmbientSum += vAmbient;
    vDiffuseSum += vDiffuse;
    vSpecSum += vSpec;
    
    vColor = vTexColor * (vAmbientSum + vDiffuseSum) + vSpecSum;
    vColor.a = g_Material.Diffuse.a * vTexColor.a;
    
    float distToEye = length(g_vEye.xyz - In.PosW);
    float fogLerp = saturate((distToEye - g_fFogStart) / g_fFogRange);
    vColor.rgb = lerp(vColor.rgb, g_vFogColor.rgb, fogLerp);
    
    return vColor;
}

float4 PS_SHADOW(GeoOut In) : SV_TARGET
{
    float4 vTexColor = g_DiffuseTex.Sample(g_Sampler, In.Tex);
    clip(vTexColor.a - 0.1f);
    return float4(0.f, 0.f, 0.f, 0.5f);
}