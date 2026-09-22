#include "MainApp.h"
#include "Engine_Defines.h"
#include "Client_Defines.h"
#include "Inven.h"

CMainApp::CMainApp()
{

}

CMainApp::~CMainApp()
{
    CGameInstance::Get().Release_Engine();
}

HRESULT CMainApp::Initialize()
{
    /* 엔진 프로젝트에 대한 준비 */
#ifdef _DEBUG

    if (::AllocConsole() == TRUE)
    {
        FILE* nfp[3];
        freopen_s(nfp + 0, "CONOUT$", "rb", stdin);
        freopen_s(nfp + 1, "CONOUT$", "wb", stdout);
        freopen_s(nfp + 2, "CONOUT$", "wb", stderr);
        std::ios::sync_with_stdio();
    }

#endif // _DEBUG

    shared_ptr<ITEM> pGun_test = shared_ptr<ITEM>(new GUN);
    pGun_test->strItemName = L"Gun";
    CInven::Get().AddEquipSlot(EQUIP_SLOT::GUN_1, pGun_test);
    pGun_test = nullptr;

    shared_ptr<ITEM> pGun_test2 = shared_ptr<ITEM>(new GUN);
    pGun_test2->strItemName = L"Gun2";
    CInven::Get().AddEquipSlot(EQUIP_SLOT::GUN_2, pGun_test2);
    pGun_test2 = nullptr;

    shared_ptr<ITEM> pBag_test = shared_ptr<ITEM>(new BACKPACK);
    pBag_test->strItemName = L"LV5 BackPack";
    CInven::Get().AddEquipSlot(EQUIP_SLOT::BACKPACK, pBag_test);
    pBag_test = nullptr;

    swap(
        CInven::Get().GetSlot(EQUIP_SLOT::GUN_1),
        CInven::Get().GetSlot(EQUIP_SLOT::GUN_2)
    );

    ENGINE_DESC EngineDesc{};
    EngineDesc.hWnd = g_hWnd;
    EngineDesc.iWinSizeX = g_iWinSizeX;
    EngineDesc.iWinSizeY = g_iWinSizeY;
    EngineDesc.eWinMode = WINMODE::WIN;


    if (FAILED(CGameInstance::Get().Initialize_Engine(EngineDesc,m_pDevice,m_pContext)))
        return E_FAIL;

    return S_OK;
}

void CMainApp::Update(f32_t fDeltaTime)
{
}

HRESULT CMainApp::Render()
{
    float4_t    vClearColor = float4_t(0.f, 0.f, 1.f, 1.f);
    CGameInstance::Get().Clear_BackBuffer_View(&vClearColor);
    CGameInstance::Get().Clear_DepthStencil_View();

    CInven::Get().RenderEquipSlot();

    //// 정점 정보
    //VTXTEX vertices[] =
    //{
    //    { float3_t(-0.5f,  0.5f, 0.f),  float2_t(0.f, 0.f) },  
    //    { float3_t(0.5f,  0.5f, 0.f),   float2_t(1.f, 0.f) },  
    //    { float3_t(0.5f, -0.5f, 0.f),   float2_t(1.f, 1.f) },  
    //    { float3_t(-0.5f, -0.5f, 0.f),  float2_t(0.f, 1.f) },  
    //};
    //
    //unsigned short indices[] = { 0,1,2, 0,2,3 };
    //
    //// 정점 버퍼 생성
    //D3D11_BUFFER_DESC   VBDesc{};
    //VBDesc.ByteWidth    =   sizeof(vertices);
    //VBDesc.Usage        =   D3D11_USAGE_IMMUTABLE;
    //VBDesc.BindFlags    =   D3D11_BIND_VERTEX_BUFFER;
    //
    //D3D11_SUBRESOURCE_DATA  VBData{};
    //VBData.pSysMem = vertices;
    //m_pDevice->CreateBuffer(&VBDesc, &VBData, &m_pVB);
    //
    //// 인덱스 버퍼 생성
    //D3D11_BUFFER_DESC IBDesc{};
    //IBDesc.ByteWidth    =   sizeof(indices);              // 2 x 6 = 12바이트
    //IBDesc.Usage        =   D3D11_USAGE_IMMUTABLE;
    //IBDesc.BindFlags    =   D3D11_BIND_INDEX_BUFFER;
    //
    //D3D11_SUBRESOURCE_DATA IBData{};
    //IBData.pSysMem = indices;
    //m_pDevice->CreateBuffer(&IBDesc, &IBData, &m_pIB);


    CGameInstance::Get().Present();
    return S_OK;
}

unique_ptr<CMainApp> CMainApp::Create()
{
    auto    pInstance = unique_ptr<CMainApp>(new CMainApp());
    
    if (FAILED(pInstance->Initialize()))
        pInstance.reset();  // 유저가 임의로 삭제 + nullptr로 채워줌. 나중에 삭제하지 않고 즉시 삭제
    
    return pInstance;
}
