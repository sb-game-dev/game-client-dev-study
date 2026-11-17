cbuffer FrameData : register(b1)
{
    row_major matrix g_ViewMatrix, g_ProjMatrix;
    row_major matrix g_OrthoViewMatrix, g_OrthoProjMatrix;
    
    row_major matrix g_ViewInverseMatrix, g_ProjInverseMatrix;
    row_major matrix g_OrthoViewInverseMatrix, g_OrthoProjInverseMatrix;
    float4 g_vEye;
};

static const float PI = 3.14159265358979f;
static const float TWO_PI = 6.28318530717958f;

static const float2 g_vWinSize = float2(1280.f, 720.f); 

Texture2DArray g_IconArray : register(t0);
Texture2DArray g_HUDIconArray : register(t1);

SamplerState g_PointSampler : register(s0);
SamplerState g_LinearSampler : register(s1);

struct VS_IN
{
    // 버텍스 버퍼
    float3 vPosition : POSITION; 
    float3 vNormal : NORMAL;
    float2 vTexCoord : TEXCOORD0;
    
    // 인스턴스 버퍼
    float4 vRect : UIRECT;
    float4 vColor : UICOLOR;
    float4 vShape : UISHAPE;
    float4 vUV : UIUV;
};

struct VS_IN_CIRCLE
{
    // 버텍스 버퍼
    float3 vPosition : POSITION;
    float3 vNormal : NORMAL;
    float2 vTexCoord : TEXCOORD0;
    
    // 인스턴스 버퍼
    float4 vCircleInfo : CIRCLEINFO;
    float4 vColor : UICOLOR;
    float  fDegree : DEGREE;
    float2 vShape : SHAPE;
    float fCirclePad : CIRCLEPAD;
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

struct VS_OUT_CIRCLE
{
    float4 vPosition : SV_POSITION;
    float2 vLocal : LOCAL;
    float2 vTexCoord : TEXCOORD0;
    float  fDegree : DEGREE;
    float  fLargeR : LARGER;
    float  fSmallR : SMALLR;
    
    nointerpolation float2 vShape : SHAPE;
    nointerpolation float4 vColor : COLOR;
};

VS_OUT VS_MAIN(VS_IN In)
{
    VS_OUT Out;
    float2 vSize = In.vRect.zw;
    float2 vCenter = float2(In.vRect.x + vSize.x * 0.5f, In.vRect.y - vSize.y * 0.5f);
    float2 vLocal = In.vPosition.xy * vSize;
    float2 vOrtho = vCenter + vLocal;

    // 픽셀 셰이더에서 사용하지 않음. 다만 레스터라이즈 단계에서 픽셀의 Local, Color 값을 보간을 하기위해 계산해야함
    Out.vPosition = mul(mul(float4(vOrtho, 1.f, 1.f), g_OrthoViewMatrix), g_OrthoProjMatrix);
    Out.vLocal = vLocal;
    Out.vTexCoord = lerp(In.vUV.xy, In.vUV.zw, In.vTexCoord);
    Out.vColor = In.vColor;
    Out.vShape = In.vShape;
    Out.vSize = vSize;
    return Out;
}


VS_OUT_CIRCLE VS_MAIN_CIRCLE(VS_IN_CIRCLE In)
{
    VS_OUT_CIRCLE Out;    
    float fR = In.vCircleInfo.z; // 큰 반지름
    float2 vLocal = In.vPosition.xy * (fR * 2.f); // 크기변환만 적용
    float2 vOrtho = In.vCircleInfo.xy + vLocal;

    // 픽셀 셰이더에서 사용하지 않음. 다만 레스터라이즈 단계에서 픽셀의 Local, Color 값을 보간을 하기위해 계산해야함
    Out.vPosition = mul(mul(float4(vOrtho, 1.f, 1.f), g_OrthoViewMatrix), g_OrthoProjMatrix);
    Out.vLocal = vLocal;
    Out.vTexCoord = In.vTexCoord;
    Out.vColor = In.vColor;
    Out.fDegree = In.fDegree;
    Out.fLargeR = In.vCircleInfo.z;
    Out.fSmallR = In.vCircleInfo.w;
    Out.vShape = In.vShape;
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

bool InRing(float2 PixelPos, float fDegree, float R, float r)
{
	if (PixelPos.x * PixelPos.x + PixelPos.y * PixelPos.y > R*R)
        return false;
	if (PixelPos.x * PixelPos.x + PixelPos.y * PixelPos.y < r*r)
        return false;
    if (fDegree == 0.f)
        return false;
    if (fDegree < 180.f && PixelPos.x < 0 && PixelPos.y > tan(radians(fDegree) + PI / 2) * PixelPos.x)
        return true;
    if (fDegree == 180.f && PixelPos.x < 0)
        return true;
    if (180 < fDegree && fDegree < 360.f && (PixelPos.x <= 0 || PixelPos.y < tan(radians(fDegree) + PI / 2) * PixelPos.x))
        return true;
    if (fDegree == 360.f)
        return true;
    return false;
}

float4 PS_MAIN(VS_OUT In) : SV_TARGET
{
    // 아이콘인 경우
    if (In.vShape.z > 1.5f)
        return g_HUDIconArray.Sample(g_LinearSampler, float3(In.vTexCoord, In.vShape.w)) * In.vColor;
    
    if (In.vShape.z > 0.5f)
        return g_IconArray.Sample(g_LinearSampler, float3(In.vTexCoord, In.vShape.w)) * In.vColor;

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

float4 PS_MAIN_CIRCLE(VS_OUT_CIRCLE In) : SV_TARGET
{
    // 아이콘인 경우
    if (In.vShape.x > 0.5f)
        return g_HUDIconArray.Sample(g_LinearSampler, float3(In.vTexCoord, In.vShape.y)) * In.vColor;
    
    if (!InRing(In.vLocal, In.fDegree, In.fLargeR, In.fSmallR))
        discard;
    
    return In.vColor;
}