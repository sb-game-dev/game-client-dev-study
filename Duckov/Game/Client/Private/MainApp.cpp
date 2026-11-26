#include "MainApp.h"
#include "Client_Defines.h"
#include "Level_Loading.h"
#include "Body_Player.h"
#include "Weapon.h"
#include "Helmet.h"
#include "Armor.h"
#include "BackPack.h"
#include "Headset.h"
#include "FaceMask.h"
#include "Player.h"
#include "Client_Mouse.h"
#include "Scope.h"
#include "Inven.h"
#include "HUD.h"
#include "Bullet.h"
#include "UI_StaminaRing.h"
#include "UI_HpBar.h"

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
//#ifdef _DEBUG
//
//    if (::AllocConsole() == TRUE)
//    {
//        FILE* nfp[3];
//        freopen_s(nfp + 0, "CONOUT$", "rb", stdin);
//        freopen_s(nfp + 1, "CONOUT$", "wb", stdout);
//        freopen_s(nfp + 2, "CONOUT$", "wb", stderr);
//        std::ios::sync_with_stdio();
//    }
//
//#endif // _DEBUG


    ENGINE_DESC EngineDesc{};
    EngineDesc.hWnd = g_hWnd;
    EngineDesc.iWinSizeX = g_iWinSizeX;
    EngineDesc.iWinSizeY = g_iWinSizeY;
    EngineDesc.eWinMode = WINMODE::WIN;
    EngineDesc.iNumLevels = ETOUI(LEVEL::END);
    EngineDesc.hInstance = hInst;

    if (FAILED(CGameInstance::Get().Initialize_Engine(EngineDesc,m_pDevice,m_pContext)))
        return E_FAIL;

    if (FAILED(Ready_Prototype_For_StaticLV()))
        return E_FAIL;
    if (FAILED(Ready_Static_Layer()))
        return E_FAIL;
    
    // 씬 생성
    if (FAILED(Start_Level(LEVEL::ZEROZONE)))
        return E_FAIL;

    //Test_Write();
    //Test_Read();

    return S_OK;
}

void CMainApp::Update(f32_t fDeltaTime)
{
    CGameInstance::Get().Update_Engine(fDeltaTime);
}

HRESULT CMainApp::Render()
{
// Clear
    float4_t    vClearColor = float4_t{ 0.75, 0.75, 0.75, 1 };
    CGameInstance::Get().Clear_BackBuffer_View(&vClearColor);
    CGameInstance::Get().Clear_DepthStencil_View();

    CGameInstance::Get().Bind_PipeLine_Vertex_ShaderResource(1);
    CGameInstance::Get().Bind_PipeLine_Pixel_ShaderResource(1);
    CGameInstance::Get().Bind_PipeLine_Geometry_ShaderResource(1);

    CGameInstance::Get().Draw();

    CGameInstance::Get().Present();
    return S_OK;
}


HRESULT CMainApp::Start_Level(LEVEL eStartLevelID)
{
    if(FAILED(CGameInstance::Get().Change_Level(static_cast<int>(LEVEL::LOADING), 
                                                CLevel_Loading::Create(m_pDevice, m_pContext, eStartLevelID))))
        return E_FAIL;
    return S_OK;
}

HRESULT CMainApp::Ready_Prototype_For_StaticLV()
{
    //================== 셰이더 ==================
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::VS_UI,
        CVertexShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Shader_Inventory.hlsl",
            VTXUI_INSTANCE::Elements, VTXUI_INSTANCE::iNumElements, "VS_MAIN"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::PS_UI,
        CPixelShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Shader_Inventory.hlsl", "PS_MAIN"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::VS_UI_CIRCLE,
        CVertexShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Shader_Inventory.hlsl",
            VTXUI_INSTANCE_CIRCLE::Elements, VTXUI_INSTANCE_CIRCLE::iNumElements, "VS_MAIN_CIRCLE"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::PS_UI_CIRCLE,
        CPixelShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Shader_Inventory.hlsl", "PS_MAIN_CIRCLE"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::VS_VTXCOL_UI,
        CVertexShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/UI_VertexShader.hlsl", VTXCOL::Elements, VTXCOL::iNumElements, "VS_UI_SCOPE"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::PS_VTXCOL_SCOPE,
        CPixelShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/UI_PixelShader.hlsl", "PS_SCOPE"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::PS_VTXCOL_SHADOW,
        CPixelShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Model_PixelShader.hlsl", "PS_SHADOW_MODEL"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::PS_VTXCOL_OCCLUDED,
        CPixelShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Model_PixelShader.hlsl", "PS_OCCLUDEDPLAYER"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::VS_VTXTEX,
        CVertexShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Model_VertexShader.hlsl", VTXNORM::Elements, VTXNORM::iNumElements, "VS_MAIN"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::VS_VTXTEX_INSTANCE,
        CVertexShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Model_VertexShader.hlsl", VTXNORM_INSTANCE::Elements, VTXNORM_INSTANCE::iNumElements, "VS_MAIN_INST"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::VS_VTXTEX_INSTANCE_UI,
        CVertexShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/UI_VertexShader.hlsl", VTXNORM_INSTANCE::Elements, VTXNORM_INSTANCE::iNumElements, "VS_MAIN_INST_UI"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::PS_VTXTEX,
        CPixelShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Model_PixelShader.hlsl", "PS_MAIN"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::PS_VTXTEX_SHADOW,
        CPixelShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Model_PixelShader.hlsl", "PS_SHADOW"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::PS_VTXTEX_NOLIGHT,
        CPixelShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Model_PixelShader.hlsl", "PS_MAIN_NOLIGHT"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::VS_TERRAIN,
        CVertexShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Model_VertexShader.hlsl", VTXNORM::Elements, VTXNORM::iNumElements, "VS_TERRAIN"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::PS_TERRAIN,
        CPixelShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Model_PixelShader.hlsl", "PS_TERRAIN"))))
        return E_FAIL;


    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::VS_MODEL,
        CVertexShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Model_VertexShader.hlsl", VTXMESH::Elements, VTXMESH::iNumElements, "VS_MAIN_MODEL"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::VS_ANIM_MODEL,
        CVertexShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Model_VertexShader.hlsl", VTXANIMMESH::Elements, VTXANIMMESH::iNumElements, "VS_MAIN_ANIM_MODEL"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::PS_MODEL,
        CPixelShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Model_PixelShader.hlsl", "PS_MAIN_MODEL"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::VS_MODEL_INSTANCE,
        CVertexShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Model_VertexShader.hlsl",
            VTXMESH_INSTANCE::Elements, VTXMESH_INSTANCE::iNumElements, "VS_MAIN_MODEL_INST"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::VS_VTXTEX_UI,
        CVertexShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/UI_VertexShader.hlsl", VTXNORM::Elements, VTXNORM::iNumElements, "VS_MAIN_UI"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::VS_TRAIL,
        CVertexShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Trail_VertexShader.hlsl", VTXNORM::Elements, VTXNORM::iNumElements, "VS_MAIN"))))
        return E_FAIL;
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::PS_TRAIL,
        CPixelShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Trail_PixelShader.hlsl", "PS_MAIN"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::VS_CUBE,
        CVertexShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Cube_VertexShader.hlsl", VTXCUBE::Elements, VTXCUBE::iNumElements, "VS_MAIN"))))
        return E_FAIL;
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::PS_CUBE,
        CPixelShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Cube_PixelShader.hlsl", "PS_MAIN"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::VS_CUBE_SKY,
        CVertexShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Cube_VertexShader.hlsl", VTXCUBE::Elements, VTXCUBE::iNumElements, "VS_MAIN_SKY"))))
        return E_FAIL;
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::PS_CUBE_SKY,
        CPixelShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Cube_PixelShader.hlsl", "PS_MAIN_SKY"))))
        return E_FAIL;
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::PS_CUBE_SHADOW,
        CPixelShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Cube_PixelShader.hlsl", "PS_SHADOW"))))
        return E_FAIL;
    //================== 객체 원형 ==================
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::Obj_Player,
        CPlayer::Create(m_pDevice, m_pContext))))
        return E_FAIL;
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::Obj_Body_Player,
        CBody_Player::Create(m_pDevice, m_pContext))))
        return E_FAIL;
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::Obj_Weapon,
        CWeapon::Create(m_pDevice, m_pContext))))
        return E_FAIL;
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::Obj_Helmet,
        CHelmet::Create(m_pDevice, m_pContext))))
        return E_FAIL;
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::Obj_Armor,
        CArmor::Create(m_pDevice, m_pContext))))
        return E_FAIL;
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::Obj_BackPack,
        CBackPack::Create(m_pDevice, m_pContext))))
        return E_FAIL;
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::Obj_Headset,
        CHeadset::Create(m_pDevice, m_pContext))))
        return E_FAIL;
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::Obj_FaceMask,
        CFaceMask::Create(m_pDevice, m_pContext))))
        return E_FAIL;
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::Obj_Client_Mouse,
        CClient_Mouse::Create(m_pDevice, m_pContext))))
        return E_FAIL;
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::Obj_Scope,
        CScope::Create(m_pDevice, m_pContext))))
        return E_FAIL;
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::Obj_Inven,
        CInven::Create(m_pDevice, m_pContext))))
        return E_FAIL;
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::Obj_HUD,
        CHUD::Create(m_pDevice, m_pContext))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::Obj_UI_HpBar,
        CUI_HpBar::Create(m_pDevice, m_pContext))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::Obj_UI_StaminaRing,
        CUI_StaminaRing::Create(m_pDevice, m_pContext))))
        return E_FAIL;
    
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::Obj_Bullet,
        CBullet::Create(m_pDevice, m_pContext))))
        return E_FAIL;

    //================== 모델 원형 ==================
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC),
        Proto::Model_Duck,
        CModel::Create(m_pDevice, m_pContext, MODEL::ANIM,
            "../../../Resource/Characters/S12_DuckV2_2/S12_DuckV2_2.bin"))))
        return E_FAIL;
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC),
        Proto::Model_Weapon_AK47,
        CModel::Create(m_pDevice, m_pContext, MODEL::NONANIM,
            "../../../Resource/prefabs/weapons/guns/ig_gun_ak47.bin"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC),
        Proto::Model_Weapon_M700,
        CModel::Create(m_pDevice, m_pContext, MODEL::NONANIM,
            "../../../Resource/prefabs/weapons/guns/ig_gun_m700.bin"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC),
        Proto::Model_Weapon_PM,
        CModel::Create(m_pDevice, m_pContext, MODEL::NONANIM,
            "../../../Resource/prefabs/weapons/guns/ig_gun_pm.bin"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC),
        Proto::Model_Weapon_Axe,
        CModel::Create(m_pDevice, m_pContext, MODEL::NONANIM,
            "../../../Resource/prefabs/weapons/melee_handheld/MeleeWeaponAgent_Axe.bin"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC),
        Proto::Model_Helmet_LV2,
        CModel::Create(m_pDevice, m_pContext, MODEL::NONANIM,
            "../../../Resource/prefabs/equipment/helmet/ig_helmat_LV2.bin"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC),
        Proto::Model_Helmet_LV3,
        CModel::Create(m_pDevice, m_pContext, MODEL::NONANIM,
            "../../../Resource/prefabs/equipment/helmet/ig_helmat_LV3.bin"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC),
        Proto::Model_Armor_LV2,
        CModel::Create(m_pDevice, m_pContext, MODEL::NONANIM,
            "../../../Resource/prefabs/equipment/armor/ig_armor_LV2.bin"))))
        return E_FAIL;
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC),
        Proto::Model_Armor_LV3,
        CModel::Create(m_pDevice, m_pContext, MODEL::NONANIM,
            "../../../Resource/prefabs/equipment/armor/ig_armor_LV3.bin"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC),
        Proto::Model_BackPack_LV2,
        CModel::Create(m_pDevice, m_pContext, MODEL::NONANIM,
            "../../../Resource/prefabs/equipment/backpack/ig_backpack_LV2.bin"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC),
        Proto::Model_BackPack_LV3,
        CModel::Create(m_pDevice, m_pContext, MODEL::NONANIM,
            "../../../Resource/prefabs/equipment/backpack/ig_backpack_LV3.bin"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC),
        Proto::Model_Headset_LV0,
        CModel::Create(m_pDevice, m_pContext, MODEL::NONANIM,
            "../../../Resource/prefabs/equipment/headset/ig_headset_LV0.bin"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC),
        Proto::Model_Headset_LV1,
        CModel::Create(m_pDevice, m_pContext, MODEL::NONANIM,
            "../../../Resource/prefabs/equipment/headset/IG_Headset_LV1V2.bin"))))
        return E_FAIL;
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC),
        Proto::Model_FaceMask_FlyMask,
        CModel::Create(m_pDevice, m_pContext, MODEL::NONANIM,
            "../../../Resource/prefabs/equipment/facemask/IG_fackmask_flymask.bin"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC),
        Proto::Model_FaceMask_GasMask,
        CModel::Create(m_pDevice, m_pContext, MODEL::NONANIM,
            "../../../Resource/prefabs/equipment/facemask/IG_fackmask_gasmask_01.bin"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC),
        Proto::Model_FaceMask_NightVision,
        CModel::Create(m_pDevice, m_pContext, MODEL::NONANIM,
            "../../../Resource/prefabs/equipment/facemask/IG_fackmask_nightvision.bin"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::VIBuffer_Cube,
        CVIBuffer_Cube::Create(m_pDevice, m_pContext))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::VIBuffer_Rect,
        CVIBuffer_Rect::Create(m_pDevice, m_pContext))))
        return E_FAIL;

    //================== 텍스처 ==================
        // 마우스 조준선
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::Texture_Mouse,
        CTexture::Create(m_pDevice, m_pContext, TEXT("../../../Resource/UI/Mouse/cursor%d.png"), 4))))
        return E_FAIL;

    // 아이템 아이콘
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::Texture_ItemIcons,
        CTexture::Create(m_pDevice, m_pContext, TEXT("../../../Resource/Inventory/IconArray/icons_128.dds"), 1))))
        return E_FAIL;

    // 아이템 아이콘
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::Texture_HUDIcons,
        CTexture::Create(m_pDevice, m_pContext, TEXT("../../../Resource/Inventory/IconArray/hud_icons.dds"), 1))))
        return E_FAIL;
    //================== Collider ==================
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::STATIC), Proto::Cube_Collider,
        CCube_Collider::Create(m_pDevice, m_pContext))))
        return E_FAIL;

    return S_OK;
}

HRESULT CMainApp::Ready_Static_Layer()
{
    auto pLayerTag = L"Layer_Static";

    CPlayer::PLAYER_DESC Player_Desc{};
    Player_Desc.fDegreeRotPerSec = { 180.f };
    Player_Desc.fPosX = { 38.2f };
    Player_Desc.fPosZ = { -207.2f };

    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::STATIC), Proto::Obj_Player,
        ETOUI(LEVEL::STATIC), pLayerTag, GO::Player, &Player_Desc)))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::STATIC), Proto::Obj_Inven,
        ETOUI(LEVEL::STATIC), pLayerTag, GO::Inven)))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::STATIC), Proto::Obj_HUD,
        ETOUI(LEVEL::STATIC), pLayerTag, GO::HUD)))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::STATIC), Proto::Obj_Client_Mouse,
        ETOUI(LEVEL::STATIC), pLayerTag, GO::Client_Mouse)))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::STATIC), Proto::Obj_Scope,
        ETOUI(LEVEL::STATIC), pLayerTag, GO::Scope)))
        return E_FAIL;



    return S_OK;
}

void CMainApp::Test_Write()
{
    // 1. 쓰기 + 바이너리 모드로 파일 개방
    // 파일 개방에 실패하면 pFile이 없으니 닫을 것도 없어서 바로 return
    // 경로는 실행파일 기준 상대경로
    FILE* pFile = nullptr;
    if (0 != _wfopen_s(&pFile, L"../Bin/Test.bin", L"wb") || nullptr == pFile)
        return;
    int32_t iNum = 1234567;
    f32_t   fValue = 3.14f;
    // 2. 숫자 하나씩 쓰기
    // fwrite(저장할 데이터들의 첫 번째 주소, 저장할 데이터들 하나의 크기, 저장할 데이터의 개수, fopen으로 열어둔 파일)
    // 배열을 기본 단위로 생각하도록 설계된것
    // 데이터들은 메모리에 연속적으로 붙어 있어야 한다. 
    // 일반 벡터나 배열들은 가능하지만 리스트나 vector<shared_ptr<CMesh>> 는 쓸 수 없다.
    // 반환값 -> 실제로 저장한 데이터의 개수
    fwrite(&iNum, sizeof(int32_t), 1, pFile);
    fwrite(&fValue, sizeof(f32_t), 1, pFile);

    // 3. 배열 쓰기
    vector<VTXMESH> Vertices(3);
    Vertices[0].vPosition = { 1.f,2.f,3.f };
    Vertices[1].vPosition = { 4.f,5.f,6.f };
    Vertices[2].vPosition = { 7.f,8.f,9.f };

    uint32_t iNumVertices = static_cast<uint32_t>(Vertices.size());
    fwrite(&iNumVertices, sizeof(uint32_t), 1, pFile);
    fwrite(Vertices.data(), sizeof(VTXMESH), iNumVertices, pFile);

    // 4. 문자열 쓰기
    // 마지막의 널문자 '\0'은 쓰지 않는다.
    string strName = "Bone_Root";
    uint32_t iLength = static_cast<uint32_t>(strName.size());
    fwrite(&iLength, sizeof(uint32_t), 1, pFile);
    fwrite(strName.data(), sizeof(char), iLength, pFile);

    // 5. 파일 닫기
    fclose(pFile);
}

void CMainApp::Test_Read()
{
    // 1. 읽기 + 바이너리모드로 파일 개방
    FILE* pFile = nullptr;
    if (0 != _wfopen_s(&pFile, L"../Bin/Test.bin", L"rb") || nullptr == pFile)
        return;
    // 2. 숫자 읽기
    //  fread(읽어온 데이터들을 채워 넣을 첫 번째 주소, 읽어올 데이터들 하나의 크기, 읽어올 데이터의 개수, fopen으로 열어둔 파일)
    // 채워 넣을 공간은 읽기 전에 미리 확보해 두어야 한다. (vector는 resize 먼저, 그래서 개수를 먼저 저장/로드한다)
    // 채워 넣을 공간도 메모리에 연속적으로 붙어 있어야 한다. (vector, 배열 O / list X)
    // 포인터를 가진 타입에는 읽어 넣으면 안 된다. 저장 당시의 주소값이 들어오기 때문이다. (vector<shared_ptr<CMesh>>, string 객체 X)
    // 쓴 순서와 같은 순서로 읽어야 한다. 순서가 어긋나도 에러 없이 엉뚱한 값이 들어온다.
    // 반환값 -> 실제로 읽어온 데이터의 개수 (요청한 개수보다 작으면 파일 끝에 도달했거나 오류)
    int32_t iNum = {};
    f32_t   fValue = {};
    fread(&iNum, sizeof(int32_t), 1, pFile);
    fread(&fValue, sizeof(f32_t), 1, pFile);

    // 3. 배열 읽기
    // 개수를 먼저 읽고 벡터 resize
    // 공간없이 fread하면 남의 메모리를 덮어서 크래시가 난다.
    // fread의 반환값을 비교해서 정점 3개를 다 읽었는지 확인
    uint32_t iNumVertices = {};
    fread(&iNumVertices, sizeof(uint32_t), 1, pFile);

    vector<VTXMESH> Vertices(iNumVertices);
    if (iNumVertices != fread(Vertices.data(), sizeof(VTXMESH), iNumVertices, pFile))
    {
        fclose(pFile);
        return;
    }

    // 4. 문자열 읽기
    uint32_t iLength = {};
    fread(&iLength, sizeof(uint32_t), 1, pFile);

    string strName(iLength, '\0');
    fread(strName.data(), sizeof(char), iLength, pFile);

    fclose(pFile);
}

unique_ptr<CMainApp> CMainApp::Create()
{
    auto    pInstance = unique_ptr<CMainApp>(new CMainApp());
    
    if (FAILED(pInstance->Initialize()))
        pInstance.reset();  // 유저가 임의로 삭제 + nullptr로 채워줌. 나중에 삭제하지 않고 즉시 삭제
    
    return pInstance;
}
