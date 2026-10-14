Texture2D g_Input : register(t0);
RWTexture2D<float4> g_Output : register(u0); 

// ---------------------------------------------------------------------
// 블러 설정
// ---------------------------------------------------------------------
// 블러 반지름 : 한쪽으로 몇 픽셀까지 섞을지 (총 2R + 1개 샘플)
static const int g_iBlurRadius = 5;

// 가우스 가중치 (합이 반드시 1이어야 밝기가 유지됨)
// 0.05*4 + 0.1*6 + 0.2 = 1.0
static const float g_Weights[11] =
{
    0.05f, 0.05f, 0.1f, 0.1f, 0.1f, 0.2f, 0.1f, 0.1f, 0.1f, 0.05f, 0.05f
};

// 그룹당 스레드 수 (C++ BlurFilter.cpp의 s_iThreadsPerGroup과 같아야 함)
#define N 256

// 캐시 크기 = 그룹이 맡은 픽셀 N개 + 양쪽 이웃 R개씩
#define CacheSize (N + 2 * g_iBlurRadius)

// 그룹 내 스레드끼리 공유하는 캐시 (12.6절)
groupshared float4 g_Cache[CacheSize];

// ---------------------------------------------------------------------
// 가로 블러
//  그룹 하나 = 가로 256픽셀 한 줄
//  Dispatch(ceil(Width / 256), Height, 1)
// ---------------------------------------------------------------------
[numthreads(N, 1, 1)]
void CS_HorzBlur(int3 vGroupThreadID : SV_GroupThreadID,
                 int3 vDispatchThreadID : SV_DispatchThreadID)
{
    uint iWidth, iHeight;
    g_Input.GetDimensions(iWidth, iHeight);
    int2 vMaxIndex = int2(iWidth, iHeight) - 1;

    // -----------------------------------------------------------------
    // 1) 캐시 채우기
    //    캐시 인덱스 : [0 ~ R-1]         왼쪽 이웃 (앞쪽 R개 스레드가 추가로 읽음)
    //                 [R ~ R+N-1]       내 픽셀   (모든 스레드가 하나씩 읽음)
    //                 [R+N ~ 2R+N-1]    오른쪽 이웃 (뒤쪽 R개 스레드가 추가로 읽음)
    // -----------------------------------------------------------------

    // 왼쪽 이웃 : 그룹의 앞쪽 R개 스레드가 담당
    if (vGroupThreadID.x < g_iBlurRadius)
    {
        // 화면 왼쪽 끝을 넘어가면 0번 픽셀로 고정 (범위 밖 읽기는 0=검은색이라 가장자리가 어두워짐)
        int x = max(vDispatchThreadID.x - g_iBlurRadius, 0);
        g_Cache[vGroupThreadID.x] = g_Input[int2(x, vDispatchThreadID.y)];
    }

    // 오른쪽 이웃 : 그룹의 뒤쪽 R개 스레드가 담당
    if (vGroupThreadID.x >= N - g_iBlurRadius)
    {
        int x = min(vDispatchThreadID.x + g_iBlurRadius, vMaxIndex.x);
        g_Cache[vGroupThreadID.x + 2 * g_iBlurRadius] = g_Input[int2(x, vDispatchThreadID.y)];
    }

    // 내 픽셀 : 모든 스레드가 담당
    // (마지막 그룹은 텍스처 밖 스레드가 있으므로 클램프)
    g_Cache[vGroupThreadID.x + g_iBlurRadius] = g_Input[min(vDispatchThreadID.xy, vMaxIndex)];

    // -----------------------------------------------------------------
    // 2) 그룹의 모든 스레드가 캐시를 다 채울 때까지 대기
    //    이게 없으면 아직 안 채워진 이웃 칸을 읽게 됨
    // -----------------------------------------------------------------
    GroupMemoryBarrierWithGroupSync();

    // -----------------------------------------------------------------
    // 3) 캐시에서 이웃들을 읽어 가중 평균
    // -----------------------------------------------------------------
    float4 vBlurColor = float4(0.f, 0.f, 0.f, 0.f);

    for (int i = -g_iBlurRadius; i <= g_iBlurRadius; ++i)
    {
        int k = vGroupThreadID.x + g_iBlurRadius + i;
        vBlurColor += g_Weights[i + g_iBlurRadius] * g_Cache[k];
    }

    // 텍스처 밖 스레드의 쓰기는 자동으로 무시됨
    g_Output[vDispatchThreadID.xy] = vBlurColor;
}

[numthreads(N, 1, 1)]
void CS_HorzBlur_Simple(int3 vDispatchThreadID : SV_DispatchThreadID)
{
    uint iWidth, iHeight;
    g_Input.GetDimensions(iWidth, iHeight); // 지금 묶여있는 텍스처 크기 iWidth, iHeight에 저장 clamp에 사용하기 위함 (1280, 720)

    float4 vBlurColor = float4(0.f, 0.f, 0.f, 0.f);

    for (int i = -g_iBlurRadius; i <= g_iBlurRadius; ++i)   // i = -5 ~ +5
    {
        int x = vDispatchThreadID.x + i; // 이웃 픽셀의 x좌표
        x = clamp(x, 0, (int) iWidth - 1); // 화면 밖이면 끝 픽셀로 고정
        vBlurColor += g_Weights[i + g_iBlurRadius] * g_Input[int2(x, vDispatchThreadID.y)];
    }

    g_Output[vDispatchThreadID.xy] = vBlurColor;
}

// ---------------------------------------------------------------------
// 세로 블러
//  그룹 하나 = 세로 256픽셀 한 줄
//  Dispatch(Width, ceil(Height / 256), 1)
//  (가로 블러에서 x <-> y만 바꾼 것)
// ---------------------------------------------------------------------
[numthreads(1, N, 1)]
void CS_VertBlur(int3 vGroupThreadID : SV_GroupThreadID,
                 int3 vDispatchThreadID : SV_DispatchThreadID)
{
    uint iWidth, iHeight;
    g_Input.GetDimensions(iWidth, iHeight);
    int2 vMaxIndex = int2(iWidth, iHeight) - 1;

    // 1) 캐시 채우기
    // 위쪽 이웃
    if (vGroupThreadID.y < g_iBlurRadius)
    {
        int y = max(vDispatchThreadID.y - g_iBlurRadius, 0);
        g_Cache[vGroupThreadID.y] = g_Input[int2(vDispatchThreadID.x, y)];
    }

    // 아래쪽 이웃
    if (vGroupThreadID.y >= N - g_iBlurRadius)
    {
        int y = min(vDispatchThreadID.y + g_iBlurRadius, vMaxIndex.y);
        g_Cache[vGroupThreadID.y + 2 * g_iBlurRadius] = g_Input[int2(vDispatchThreadID.x, y)];
    }

    // 내 픽셀
    g_Cache[vGroupThreadID.y + g_iBlurRadius] = g_Input[min(vDispatchThreadID.xy, vMaxIndex)];

    // 2) 대기
    GroupMemoryBarrierWithGroupSync();

    // 3) 가중 평균
    float4 vBlurColor = float4(0.f, 0.f, 0.f, 0.f);

    for (int i = -g_iBlurRadius; i <= g_iBlurRadius; ++i)
    {
        int k = vGroupThreadID.y + g_iBlurRadius + i;
        vBlurColor += g_Weights[i + g_iBlurRadius] * g_Cache[k];
    }

    g_Output[vDispatchThreadID.xy] = vBlurColor;
}

// ---------------------------------------------------------------------
// 풀스크린 출력
//  정점 버퍼 없이 Draw(3, 0) 호출
//  화면을 덮는 큰 삼각형 하나 : (-1,1) (3,1) (-1,-3)
// ---------------------------------------------------------------------
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

    // UV(0~2) -> NDC : x는 -1~3, y는 뒤집어서 1~-3
    Out.vPosition = float4(vUV * float2(2.f, -2.f) + float2(-1.f, 1.f), 0.f, 1.f);

    return Out;
}
// ▼  ① 클리핑         화면 밖 부분 잘라냄 → 화면 크기 사각형만 남음
// ▼  ② 원근 나눗셈    x/w, y/w  (w=1이라 그대로)  → NDC
// ▼  ③ 뷰포트 변환    NDC → 픽셀 좌표 (RSSetViewports의 1280×720 기준)
// ▼  ④ 래스터화       삼각형 안의 픽셀마다 PS 호출
float4 PS_FullScreen(VS_OUT In) : SV_TARGET
{
    // PS의 SV_POSITION은 화면 픽셀 좌표 (0.5, 0.5), (1.5, 0.5) ...
    // 정수로 바꾸면 텍셀 인덱스가 됨 (텍스처와 화면 크기가 같으므로 1:1)
    // 기존의 UV값을 활용한 Sampler와는 다르게 텍셀 인덱스를 사용하는 방식 따라서 정수로 변환후 사용해야 한다
    return g_Input.Load(int3(In.vPosition.xy, 0));
}