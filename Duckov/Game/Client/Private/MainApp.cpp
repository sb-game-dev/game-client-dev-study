#include "MainApp.h"
#include "Engine_Defines.h"
#include "Client_Defines.h"
#include "Inven.h"

CMainApp::CMainApp()
{

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
    CInven::GetInstance()->AddEquipSlot(EQUIP_SLOT::GUN_1, pGun_test);
    pGun_test = nullptr;

    shared_ptr<ITEM> pGun_test2 = shared_ptr<ITEM>(new GUN);
    pGun_test2->strItemName = L"Gun2";
    CInven::GetInstance()->AddEquipSlot(EQUIP_SLOT::GUN_2, pGun_test2);
    pGun_test2 = nullptr;

    shared_ptr<ITEM> pBag_test = shared_ptr<ITEM>(new BACKPACK);
    pBag_test->strItemName = L"LV5 BackPack";
    CInven::GetInstance()->AddEquipSlot(EQUIP_SLOT::BACKPACK, pBag_test);
    pBag_test = nullptr;

    swap(
        CInven::GetInstance()->GetSlot(EQUIP_SLOT::GUN_1), 
        CInven::GetInstance()->GetSlot(EQUIP_SLOT::GUN_2)
    );

    return S_OK;
}

void CMainApp::Update()
{
}

HRESULT CMainApp::Render()
{
    CInven::GetInstance()->RenderEquipSlot();
    return S_OK;
}

unique_ptr<CMainApp> CMainApp::Create()
{
    auto    pInstance = unique_ptr<CMainApp>(new CMainApp());
    
    if (FAILED(pInstance->Initialize()))
        pInstance.reset();  // 유저가 임의로 삭제 + nullptr로 채워줌. 나중에 삭제하지 않고 즉시 삭제
    
    return pInstance;
}
