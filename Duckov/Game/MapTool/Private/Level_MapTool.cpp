#include "imgui.h" 
#include "ImGuizmo.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"

#include "SunLight.h"
#include "EditorUI.h"
#include "Level_MapTool.h"
#include "MapTool_Cam.h"
CLevel_MapTool::CLevel_MapTool(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    :CLevel{ pDevice,pContext }
{
}

CLevel_MapTool::~CLevel_MapTool()
{
    m_pEditorUI.reset();
    Shutdown_ImGui();
}

HRESULT CLevel_MapTool::Initialize()
{
    if (FAILED(__super::Initialize()))
        return E_FAIL;

    SetWindowText(g_hWnd, L"MapTool_Level");

    if (FAILED(Ready_Layer_BackGround(TEXT("Layer_BackGround"))))
        return E_FAIL;
    if (FAILED(Ready_Layer_GameObject(TEXT("Layer_GameObject"))))
        return E_FAIL;
    if (FAILED(Ready_Lights()))
        return E_FAIL;

    if (FAILED(Ready_ImGui()))
        return E_FAIL;
    if (FAILED(Begin_ImGui()))
        return E_FAIL;
    m_pEditorUI = CEditorUI::Create();
    if (nullptr == m_pEditorUI)
        return E_FAIL;

    return S_OK;
}

void CLevel_MapTool::Update(f32_t fDeltaTime)
{
    __super::Update(fDeltaTime);
    if (FAILED(Begin_ImGui()))
        return;
    m_pEditorUI->Update(fDeltaTime);
    Sync_SceneView();
}

HRESULT CLevel_MapTool::Render()
{
    if (FAILED(__super::Render()))
        return E_FAIL;
    if (FAILED(Render_ImGui()))
        return E_FAIL;
    return S_OK;
}
HRESULT CLevel_MapTool::Ready_Layer_BackGround(const tchar_t* pLayerTag)
{
    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::MAPTOOL), Proto::Obj_SkyBox,
        ETOUI(LEVEL::MAPTOOL), Layer::BackGround, GO::SkyBox)))
        return E_FAIL;
    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::MAPTOOL), Proto::Obj_Fog,
        ETOUI(LEVEL::MAPTOOL), Layer::BackGround, GO::Fog)))
        return E_FAIL;
    return S_OK;
}

HRESULT CLevel_MapTool::Ready_Layer_GameObject(const tchar_t* pLayerTag)
{
    // 카메라 사본
    CMapTool_Cam::CAMERA_MAPTOOL_CAM_DESC         CameraDesc{};
    CameraDesc.fDegreeRotPerSec = 180.f;
    CameraDesc.fSpeedPerSec = 10.f;
    CameraDesc.vEye = float4_t(0.f, 1.f, -5.f, 1.f);
    CameraDesc.vAt = float4_t(0.f, 1.f, 0.f, 1.f);
    CameraDesc.fFovy = 60.f;
    CameraDesc.fNear = 0.1f;
    CameraDesc.fFar = 1000.f;
    CameraDesc.fSensor = 0.05f;

    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::MAPTOOL), Proto::Obj_MapToolCam,
        ETOUI(LEVEL::MAPTOOL), pLayerTag, GO::MapToolCam, &CameraDesc)))
        return E_FAIL;

    auto pMapToolCam = dynamic_pointer_cast<CMapTool_Cam>(CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::MAPTOOL), pLayerTag, GO::MapToolCam));
    CGameInstance::Get().Add_Camera(CAMERA::FREE, pMapToolCam);
    CGameInstance::Get().Set_MainCamera(CAMERA::FREE);

    return S_OK;
}

HRESULT CLevel_MapTool::Ready_Lights()
{
    auto pSunLight = CSunLight::Create(m_pDevice, m_pContext);
    if (nullptr == pSunLight)
        return E_FAIL;
    CGameInstance::Get().AddLight(L"SunLight", pSunLight);

    return S_OK;
}

HRESULT CLevel_MapTool::Ready_ImGui()
{
    // 1. 컨텍스트 생성
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // ImGui와 애플리케이션이 정보를 주고받는 구조체
    // 설정, 입력, 출력, 폰트가 있음
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;   // 키보드로 위젯 이동

    // 2. 스타일
    ImGui::StyleColorsDark();

    // 3. 플랫폼/렌더러 백엔드
    if (!ImGui_ImplWin32_Init(g_hWnd))
        return E_FAIL;
    if (!ImGui_ImplDX11_Init(m_pDevice.Get(), m_pContext.Get()))
        return E_FAIL;

    m_bReadyImGui = true;
    return S_OK;
}

HRESULT CLevel_MapTool::Begin_ImGui()
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    ImGuizmo::BeginFrame();
    return S_OK;
}

HRESULT CLevel_MapTool::Render_ImGui()
{
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    return S_OK;
}

HRESULT CLevel_MapTool::Shutdown_ImGui()
{
    if (!m_bReadyImGui)
        return E_FAIL;
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    return S_OK;
}

void CLevel_MapTool::Sync_SceneView()
{
    auto pCamera = dynamic_pointer_cast<CMapTool_Cam>(CGameInstance::Get().Get_MainCamera());
    if (nullptr == pCamera)
        return;
    pCamera->Set_SceneClicked(m_pEditorUI->GetSceneCliked());
    pCamera->Set_SceneHovered(m_pEditorUI->GetSceneHovered());
}


shared_ptr<CLevel_MapTool> CLevel_MapTool::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto pInstance = shared_ptr<CLevel_MapTool>(new CLevel_MapTool(pDevice, pContext));
    if (FAILED(pInstance->Initialize()))
        pInstance.reset();

    return pInstance;
}