#ifndef LIGHT_HELPER_HLSLI
#define LIGHT_HELPER_HLSLI

struct PointLight
{
    float4 Ambient;
    float4 Diffuse;
    float4 Specular;
    
    float3 Position;
    float  Range;
    
    float3 Att;
    float  Pad;
};


struct Material
{
    float4 Ambient;
    float4 Diffuse;
    float4 Specular; // w = SpecPower
    float4 Reflect;
};

void ComputePointLight(Material mat, PointLight L, float3 pos, float3 normal, float3 toEye,
                       out float4 ambient, out float4 diffuse, out float4 spec)
{
    // Initialize outputs.
    ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
    diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
    spec = float4(0.0f, 0.0f, 0.0f, 0.0f);

	// The vector from the surface to the light.
    float3 lightVec = L.Position - pos;
		
	// The distance from surface to light.
    float d = length(lightVec);
	
	// Range test.
    if (d > L.Range)
        return;
		
	// Normalize the light vector.
    lightVec /= d;
	
	// Ambient term.
    ambient = mat.Ambient * L.Ambient;

	// Add diffuse and specular term, provided the surface is in 
	// the line of site of the light.

    float diffuseFactor = dot(lightVec, normal);

	// flatten -> GPU에게 실제로 분기하지말고 양쪽을 다 계산한 뒤 결과를 고르라
	[flatten]
    if (diffuseFactor > 0.0f)
    {
        // reflect 
        // -> 반사되어 나가는 벡터를 구하는 함수
        // -> 빛이 들어오는 방향을 매개변수로 받음 -> -lightVec
        float3 v = reflect(-lightVec, normal);
        float specFactor = pow(max(dot(v, toEye), 0.0f), mat.Specular.w);
					
        diffuse = diffuseFactor * mat.Diffuse * L.Diffuse;
        spec = specFactor * mat.Specular * L.Specular;
    }

	// Attenuate
    float att = 1.0f / dot(L.Att, float3(1.0f, d, d * d));

    diffuse *= att;
    spec *= att;
}
#endif