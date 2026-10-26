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
    float2 vLocal : LOCAL;
    float2 vTexCoord : TEXCOORD0;
    nointerpolation float4 vColor : COLOR;
    nointerpolation float4 vShape : SHAPE;
    nointerpolation float2 vSize : SIZE;
};

VS_OUT VS_MAIN(VS_IN In)
{
    VS_OUT Out;
    float2 vSize = In.vRect.zw;
    float2 vCenter = In.vRect.xy + vSize * 0.5f; 
    float2 vLocal = In.vPosition.xy * vSize;
    float2 vOrtho = float2(vCenter.x - g_vWinSize.x * 0.5f,
                            g_vWinSize.y * 0.5f - vCenter.y) + vLocal;

    // 픽셀 셰이더에서 사용하지 않음. 다만 레스터라이즈 단계에서 픽셀의 Local, Color 값을 보간을 하기위해 계산해야함
    Out.vPosition = mul(mul(float4(vOrtho, 1.f, 1.f), g_matView), g_matProj);
    Out.vLocal = vLocal;
    Out.vTexCoord = lerp(In.vUV.xy, In.vUV.zw, In.vTexCoord);
    Out.vColor = In.vColor;
    Out.vShape = In.vShape;
    Out.vSize = vSize;
    return Out;
}

//p에는 크기만 늘린 로컬 스페이스의 픽셀 좌표(vLocal)가 들어감
bool InRoundRect(float2 p, float2 vHalf, float r)
{
	// 모든 사분면에서 동일한 계산을 하므로 절댓값을 취해서 1사분면에서만 계산함
    p = abs(p);

	// 둥근 모서리계산하기 전에 이미 모서리 밖인 점들은 계산 안함
    if (p.x > vHalf.x || p.y > vHalf.y)
        return false;

	// 둥근 모서리 중심 = vHalf - r
	// 원의 중심 기준 1사분면 범위에 있다면
    if (p.x > (vHalf.x - r) && p.y > (vHalf.y - r))
    {
        float x = p.x - (vHalf.x - r);
        float y = p.y - (vHalf.y - r);

		// 원 안에 있어야 한다.
        return x * x + y * y <= r * r;
    }
	// 둥근 모서리 부근이 아니고 사각형 안에 있는 점
    return true;
}

float4 PS_MAIN(VS_OUT In) : SV_TARGET
{
    // 아이콘인 경우
    if (In.vShape.z > 0.5f)
        return g_IconArray.Sample(g_Sampler, float3(In.vTexCoord, In.vShape.w)) * In.vColor;

    float2 vHalf = In.vSize * 0.5f;
    float fRadius = min(In.vShape.x, min(vHalf.x, vHalf.y)); // 너무 크면 알약 모양
    float fBorder = In.vShape.y;

    // 테두리없는 투명한 배경을 그리는 경우 + 테두리만 그리는 경우
	// 두 경우 모두 둥근 모서리 밖의 픽셀은 탈락시켜야 한다.
    if (!InRoundRect(In.vLocal, vHalf, fRadius))
        discard;

    // 테두리만 그리는 경우 테두리 간격(fBorder) 안쪽 픽셀을 탈락 시켜야 한다.
    if (fBorder > 0.f &&
        InRoundRect(In.vLocal, vHalf - fBorder, max(fRadius - fBorder, 0.f)))
        discard;

    return In.vColor;
}