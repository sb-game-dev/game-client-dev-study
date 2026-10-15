Texture2D           g_Input     : register(t0); // SRV
RWTexture2D<float4> g_Output    : register(u0); // UAV
SamplerState        g_Sampler   : register(s0); // Sampler

static const int g_iBlurRadius = 5;

static const float g_Weights[11] =
{
    0.05f, 0.05f, 0.1f, 0.1f, 0.1f, 0.2f, 0.1f, 0.1f, 0.1f, 0.05f, 0.05f
};

#define N 256
#define CacheSize (N + 2 * g_iBlurRadius)
groupshared float4 g_Cache[CacheSize];


[numthreads(N, 1, 1)]
void CS_HorzBlur(int3 vGroupThreadID : SV_GroupThreadID,// 그룹 안에서의 번호
                 int3 vDispatchThreadID : SV_DispatchThreadID) // 전체 번호
{   
    //
    // 대역폭을 줄이기 위해 지역 스레드 저장소를 채운다
    // 픽셀 N개를 흐리려면 N + 2*BlurRadius개의 픽셀을 읽어야 한다.
    //
    // 이 스레드 그룹은 B개의 스레드를 실행한다. 여분의 픽셀 2*BlurRadius개를 위해
    // 2* BlurRadius개의  스레드가 픽셀을 하나 더 추출하게 한다.
    
    if (vGroupThreadID.x < g_iBlurRadius)   // 팀 번호가 0 ~ 4번인 스레드라면
    {
        int x = max(vDispatchThreadID.x - g_iBlurRadius, 0);    // 만약 왼쪽 경계면을 넘어간다면 x좌표를 0으로 설정한다.
                                                                // 그게 아니라면 전체 번호를 이용하여 왼쪽 그룹의 x좌표를 가져온다.
        g_Cache[vGroupThreadID.x] = g_Input[int2(x, vDispatchThreadID.y)];
    }
    
    if (vGroupThreadID.x >= N - g_iBlurRadius) // 팀 번호가 251 ~ 255번인 스레드라면
    {
        int x = min(vDispatchThreadID.x + g_iBlurRadius, g_Input.Length.x - 1); // 만약 오른쪽 경계면을 넘어간다면 x좌표를 1279로 설정한다.
                                                                                // 그게 아니라면 전체 번호를 이용하여 오른쪽 그룹의 x좌표를 가져온다.
        g_Cache[vGroupThreadID.x + 2 * g_iBlurRadius] = g_Input[int2(x, vDispatchThreadID.y)];
    }
  
    g_Cache[vGroupThreadID.x + g_iBlurRadius] = g_Input[min(vDispatchThreadID.xy, g_Input.Length.xy - 1)];
    
    /*
    g_Cache:  [ 0  1  2  3  4 | 5  6  7 ... 259 260 | 261 262 263 264 265 ]
               --------------    ------------------   -------------------
                   블록 1               블록 3              블록 2
                 스레드 0~4가       스레드 0~255가      스레드 251~255가
                 추가로 1칸씩      자기 픽셀 1칸씩       추가로 1칸씩
    */
    
    GroupMemoryBarrierWithGroupSync();  // 같은 그륩의 256개의 스레드 누구도, 캐시 266칸이 다 채워지기 전에는 아래의 계산 단계로 넘어가지 못함.

    float4 vBlurColor = float4(0.f, 0.f, 0.f, 0.f);
    [unroll]
    for (int i = -g_iBlurRadius; i <= g_iBlurRadius; ++i)
    {
        int k = vGroupThreadID.x + g_iBlurRadius + i;
        vBlurColor += g_Weights[i + g_iBlurRadius] * g_Cache[k];
    }
    g_Output[vDispatchThreadID.xy] = vBlurColor;
}



[numthreads(1, N, 1)]
void CS_VertBlur(int3 vGroupThreadID : SV_GroupThreadID,
                 int3 vDispatchThreadID : SV_DispatchThreadID)
{ 
    if (vGroupThreadID.y < g_iBlurRadius)
    {
        int y = max(vDispatchThreadID.y - g_iBlurRadius, 0);
        g_Cache[vGroupThreadID.y] = g_Input[int2(vDispatchThreadID.x, y)];
    }
    
    if (vGroupThreadID.y >= N - g_iBlurRadius)
    {
        int y = min(vDispatchThreadID.y + g_iBlurRadius, g_Input.Length.y - 1);
        g_Cache[vGroupThreadID.y + 2 * g_iBlurRadius] = g_Input[int2(vDispatchThreadID.x, y)];
    }
    
    g_Cache[vGroupThreadID.y + g_iBlurRadius] = g_Input[min(vDispatchThreadID.xy, g_Input.Length.xy - 1)];

    GroupMemoryBarrierWithGroupSync();

    float4 vBlurColor = float4(0.f, 0.f, 0.f, 0.f);
    [unroll]
    for (int i = -g_iBlurRadius; i <= g_iBlurRadius; ++i)
    {
        int k = vGroupThreadID.y + g_iBlurRadius + i;
        vBlurColor += g_Weights[i + g_iBlurRadius] * g_Cache[k];
    }
    g_Output[vDispatchThreadID.xy] = vBlurColor;
}

// 풀스크린 출력
//  정점 버퍼 없이 Draw(3, 0) 호출
//  화면을 덮는 큰 삼각형 하나 : (-1,1) (3,1) (-1,-3)
struct VS_OUT
{
    float4 vPosition : SV_POSITION;
};

// SV_VertexID : 이 값은 입력 조립기(IA)가 직접 만들어주는 시스템 값, 이번 정점이 몇 번째인지

// Draw(3,0) 에 의해 이 VS_FullScreen 함수가 세 번 호출되고 iVertexID로 0,1,2가 하나씩 들어감

VS_OUT VS_FullScreen(uint iVertexID : SV_VertexID) 
{
    VS_OUT Out;
    
    float2 g_vUVs[3] = { float2(0, 0), float2(2, 0), float2(0, 2) };
    
    // iVertexID 0, 1, 2 -> (0,0) (2,0) (0,2)
    float2 vUV = g_vUVs[iVertexID];

    // UV(0~2) -> NDC : x는 -1 ~ 3, y는 뒤집어서 1 ~ -3
    Out.vPosition = float4(vUV * float2(2.f, -2.f) + float2(-1.f, 1.f), 0.f, 1.f);

    return Out;
}
// 1. 클리핑         화면 밖 부분 잘라냄 -> 화면 크기 사각형만 남음
// 2. 원근 나눗셈    x/w, y/w  (w=1이라 그대로)  -> NDC
// 3. 뷰포트 변환    NDC -> 픽셀 좌표 (RSSetViewports의 1280 x 720 기준)
// 4. 래스터화       삼각형 안의 픽셀마다 PS 호출
float4 PS_FullScreen(VS_OUT In) : SV_TARGET
{
    // PS의 SV_POSITION은 화면 픽셀 좌표 (0.5, 0.5), (1.5, 0.5) ...
    // 정수로 바꾸면 텍셀 인덱스가 됨 (텍스처와 화면 크기가 같으므로 1:1)
    // 기존의 UV값을 활용한 Sampler와는 다르게 텍셀 인덱스를 사용하는 방식 따라서 정수로 변환후 사용해야 한다
    return g_Input[uint2(In.vPosition.xy)];
}