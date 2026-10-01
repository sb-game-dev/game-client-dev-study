#include "Loader.h"
#include "BackGround.h"
#include "Cube.h"
#include "Player.h"
#include "Hill.h"
#include "QuarterView_Cam.h"

CLoader::CLoader(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    : m_pDevice{pDevice}
    , m_pContext{ pContext }
{
}

CLoader::~CLoader()
{
    Free();
}

// 서브 스레드
uint32_t APIENTRY ThreadMain(void* pArg)
{
    auto       pLoader = static_cast<CLoader*>(pArg);

    // 서브 스레드
    if (FAILED(pLoader->Loading()))
        return 1;

    return 0;
}

HRESULT CLoader::Initialize(LEVEL eNextLevel)
{
    InitializeCriticalSection(&m_CriticalSection);

    m_eNextLevelID = eNextLevel;

    m_hThread = (HANDLE)_beginthreadex(nullptr, 0, ThreadMain, this, 0, nullptr);
    if (0 == m_hThread)
        return E_FAIL;

    return S_OK;
}

HRESULT CLoader::Loading()
{
    //메모리를 공유하는 임계영역에 접근
    EnterCriticalSection(&m_CriticalSection);

    // 현재 스레드에서 COM 라이브러리를 사용할 수 있도록 초기화
    CoInitializeEx(nullptr, 0);

    HRESULT hr = {};
    switch (m_eNextLevelID)
    {
    case Client::LEVEL::LOGO:
        hr = Loading_For_LogoLV();//S_OK or E_FAIL
        break;
    case Client::LEVEL::GAMEPLAY:
        hr = Loading_For_GamePlayLV();
        break;
    }
    if (FAILED(hr))
        return E_FAIL;
    // 현재 스레드에서 COM 라이브러리를 사용할 수 있도록 초기화 해체
    CoUninitialize();
    //메모리를 공유하는 임계영역을 떠남
    LeaveCriticalSection(&m_CriticalSection);

    return S_OK;
}

// 메인 스레드
HRESULT CLoader::Draw_Debug()
{
    SetWindowText(g_hWnd, m_szLoadingText);
    return S_OK;
}

// 서브 스레드
HRESULT CLoader::Loading_For_LogoLV()
{
    lstrcpy(m_szLoadingText, TEXT("텍스쳐를 준비중입니다."));
    for (uint32_t i = 0; i < 99999999; i++)
        uint32_t iData = 10;

    lstrcpy(m_szLoadingText, TEXT("모델을 준비중입니다."));
    for (uint32_t i = 0; i < 99999999; i++)
        uint32_t iData = 10;

    lstrcpy(m_szLoadingText, TEXT("셰이더를 준비중입니다."));
    for (uint32_t i = 0; i < 99999999; i++)
        uint32_t iData = 10;

    lstrcpy(m_szLoadingText, TEXT("객체원형 준비중입니다."));
    CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::LOGO), TEXT("Prototype_GameObejct_BackGround"),
        CBackGround::Create(m_pDevice, m_pContext));

    lstrcpy(m_szLoadingText, TEXT("로딩이 완료되었습니다."));

    m_isFinished = true;
    return S_OK;
}

HRESULT CLoader::Loading_For_GamePlayLV()
{
    lstrcpy(m_szLoadingText, TEXT("텍스쳐를 준비중입니다."));
    for (uint32_t i = 0; i < 99999999; i++)
        uint32_t iData = 10;

    lstrcpy(m_szLoadingText, TEXT("모델을 준비중입니다."));
    for (uint32_t i = 0; i < 99999999; i++)
        uint32_t iData = 10;

    lstrcpy(m_szLoadingText, TEXT("셰이더를 준비중입니다."));
    for (uint32_t i = 0; i < 99999999; i++)
        uint32_t iData = 10;

    lstrcpy(m_szLoadingText, TEXT("객체원형 준비중입니다."));

    auto pPlayer = CPlayer::Create(m_pDevice, m_pContext);
    pPlayer->SetPos({ 0.f,0.f,0.f });
    CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY), TEXT("Prototype_GameObject_Player"),pPlayer);

    shared_ptr<CGameObject> pGameObject = {};
    for (uint32_t i = 0; i < 16; ++i)
    {
        pGameObject = CCube::Create(m_pDevice, m_pContext);
        f32_t   fTheta = XM_2PI / 16 * i;
        pGameObject->SetPos({ 5 * sinf(fTheta),0.f,5 * cosf(fTheta) });
        CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY), L"Prototype_GameObject_Cube" + to_wstring(i), pGameObject);
    }

    pGameObject = CHill::Create(m_pDevice, m_pContext);
    CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::GAMEPLAY), L"Prototype_GameObject_Hill", pGameObject);

    // Find_Object로 불러서 해야할듯?
    //static_pointer_cast<CPlayer>(pPlayer)->SetHill(static_pointer_cast<CHill>(pGameObject));

    lstrcpy(m_szLoadingText, TEXT("로딩이 완료되었습니다."));

    m_isFinished = true;
    return S_OK;
}
shared_ptr<CLoader> CLoader::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, LEVEL eNextLevelID)
{
    auto pInstance = shared_ptr<CLoader>(new CLoader(pDevice, pContext));

    if (FAILED(pInstance->Initialize(eNextLevelID)))
        pInstance.reset();
    return pInstance;
}
void CLoader::Free()
{
    WaitForSingleObject(m_hThread, INFINITE);

    //DeleteObject(m_hThread);

    CloseHandle(m_hThread);

    DeleteCriticalSection(&m_CriticalSection);
}