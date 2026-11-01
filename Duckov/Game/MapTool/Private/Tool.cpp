#include "imgui.h"
#include "Tool.h"
#include "StaticProp.h" 
namespace
{
    constexpr ImGuiWindowFlags g_FixedPanelFlags =
        ImGuiWindowFlags_NoMove                 // 제목 표시줄을 드래그해도 안 움직임
        | ImGuiWindowFlags_NoResize             // 모서리를 끌어도 크기 안 바뀜
        | ImGuiWindowFlags_NoCollapse           // 제목 표시줄의 접기 버튼 제거
        | ImGuiWindowFlags_NoSavedSettings;     // 창 정보를 저장하지 않음

    void Set_NextPanelRect(f32_t fX, f32_t fY, f32_t fW, f32_t fH)
    {
        ImGui::SetNextWindowPos(ImVec2(fX, fY), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(fW, fH), ImGuiCond_Always);
    }

    // wstring → UTF-8 (ImGui에 표시할 때)
    string To_UTF8(const wstring_t& strWide)
    {
        if (strWide.empty())
            return {};
        // 1번째 호출: 필요한 버퍼 크기만 구함
        int32_t iSize = WideCharToMultiByte(CP_UTF8, 0, strWide.c_str(), (int)strWide.size(), nullptr, 0, nullptr, nullptr);
        string strOut(iSize, '\0');
        // 2번째 호출: 실제 변환
        WideCharToMultiByte(CP_UTF8, 0, strWide.c_str(), (int)strWide.size(), strOut.data(), iSize, nullptr, nullptr);
        return strOut;
    }

    // UTF-8 → wstring (ImGui 입력을 엔진에 넘길 때)
    wstring_t To_Wide(const char* pUTF8)
    {
        int32_t iSize = MultiByteToWideChar(CP_UTF8, 0, pUTF8, -1, nullptr, 0);   // -1: 널 문자까지 포함
        if (iSize <= 1)
            return {};
        wstring_t strOut(iSize - 1, L'\0');                                        // 널 문자 제외
        MultiByteToWideChar(CP_UTF8, 0, pUTF8, -1, strOut.data(), iSize);
        return strOut;
    }
}

HRESULT CTool::Initialize()
{
	return S_OK;
}

void CTool::Update(const f32_t& fDeltaTime)
{
    Render_MenuBar();
    Calc_Layout();

    Render_Hierachy();
    Render_Scene();
    Render_Inspector();

    if (m_bShowDemo)
        ImGui::ShowDemoWindow(&m_bShowDemo);
}

void CTool::Create_Object()
{
    CStaticProp::STATICPROP_DESC Desc{};
    Desc.iLevelIndex = ETOUI(LEVEL::MAPTOOL);
    Desc.strMeshPath = s_Meshes[m_iMeshIndex].pPath;
    Desc.strTexturePath = s_Textures[m_iTextureIndex].pPath;
    Desc.bEditorMode = true;
    // 위치: 카메라 앞에 두면 편함 (카메라 Position + Look * 5)

    wstring_t strTag = L"Prop_" + to_wstring(m_iNextID++);

    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::MAPTOOL), s_Placeables[m_iPlaceableIndex].pPrototypeTag,
        ETOUI(LEVEL::MAPTOOL), TEXT("Layer_Map"), strTag, &Desc)))
    {
        MSG_BOX("Create Failed");   // 텍스처 경로가 틀리면 여기로 옴
        return;
    }

    // 만든 객체를 바로 선택
    m_strSelectedTag = strTag;
    m_pSelected = dynamic_pointer_cast<CMapObject>(
        CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::MAPTOOL), TEXT("Layer_Map"), strTag));
}

void CTool::Delete_Selected()
{
    auto pSelected = m_pSelected.lock();
    if (nullptr == pSelected)
        return;

    pSelected->Set_Dead();          // 실제 erase는 엔진 Priority_Update에서
    m_pSelected.reset();            // 선택은 바로 해제
    m_strSelectedTag.clear();
}

void CTool::Validate_Selection()
{
    auto pSelected = m_pSelected.lock();
    if (nullptr == pSelected || pSelected->Is_Dead())
    {
        m_pSelected.reset();
        m_strSelectedTag.clear();
    }
}

void CTool::Calc_Layout()
{
    // 현재 창 영역 크기
    const ImVec2 vDisplay = ImGui::GetIO().DisplaySize;

    // 메뉴바 바로 아래부터의 시작 좌표
    const f32_t fTop    = m_fMenuBarHeight;
    const f32_t fHeight = vDisplay.y - fTop;
    
    // 최소 씬 폭 보정
    f32_t fSide = m_fSidePamelWidth;
    const f32_t fMinScene = 200.f;
    if (vDisplay.x - fSide * 2.f < fMinScene)
        fSide = max(0.f, (vDisplay.x - fMinScene) * 0.5f);

    // 세 창의 Rect 정보
    m_tHierarchy    = { 0.f, fTop, fSide, fHeight };
    m_tScene        = { fSide, fTop, vDisplay.x - fSide * 2.f, fHeight };
    m_tInspector    = { vDisplay.x - fSide, fTop, fSide, fHeight };
}

void CTool::Render_MenuBar()
{
    // 화면 맨 위에 꽉 차게 붙는 메뉴 바.
    // 일반 창(Begin) 안이 아니라 바깥에서 호출한다.
    // 일반 창(Begin)과는 다르게 false를 반환하면 EndMainMenuBar를 호출하지 않고 빠져나간다.
    if (!ImGui::BeginMainMenuBar())
        return;

    m_fMenuBarHeight = ImGui::GetWindowHeight();

    // 펼쳐지는 메뉴
    // true일 때만 EndMenu를 호출.
    if (ImGui::BeginMenu("File"))
    {   
        // MenuItem(라벨, 단축키표시, 선택됨, 활성화);
        // 단축키는 오른쪽에 보이는 글자일 뿐이고 실제 동작은 따로 만들어야 함.
        ImGui::MenuItem("New Scene", nullptr, false, false);
        ImGui::MenuItem("Open Scene", "Ctrl + O", false, false);
        ImGui::MenuItem("Save", "Ctrl + S", false, false);
        ImGui::MenuItem("Save As", nullptr, false, false);
        ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("View"))
    {
        ImGui::MenuItem("ImGui Demo", nullptr, &m_bShowDemo);
        ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
}

void CTool::Render_Hierachy()
{
    Set_NextPanelRect(m_tHierarchy.fX, m_tHierarchy.fY, m_tHierarchy.fW, m_tHierarchy.fH);
    if (ImGui::Begin("Hierarchy", nullptr, g_FixedPanelFlags))
    {
        // ---------- 생성 ----------
        ImGui::Combo("Type", &m_iPlaceableIndex, 
            [](void*, int i) { return s_Placeables[i].pName; }, nullptr, IM_ARRAYSIZE(s_Placeables));

        // 메시 선택 (s_Meshes가 wchar_t라서 표시할 때 char로 바꿔야 함)
        ImGui::Combo("Mesh", &m_iMeshIndex,
            [](void*, int i) { return s_Meshes[i].pName; }, nullptr, IM_ARRAYSIZE(s_Meshes));

        // 텍스처 경로 입력 (Resource 기준 상대 경로)
        ImGui::Combo("Texture", &m_iTextureIndex,
            [](void*, int i) { return s_Textures[i].pName; }, nullptr, IM_ARRAYSIZE(s_Textures));

        if (ImGui::Button("Create"))
            Create_Object();

        ImGui::Separator();

        auto pObjects = CGameInstance::Get().Get_GameObjects(ETOUI(LEVEL::MAPTOOL), TEXT("Layer_Map"));

        uint32_t iVisibleCount = {};
        if (nullptr != pObjects)
        {
            for (auto& [strTag, pObject] : *pObjects)
            {
                if (nullptr == pObject || pObject->Is_Dead())
                    continue;

                ++iVisibleCount;

                const bool_t bSelected = (strTag == m_strSelectedTag);
                string strLabel(strTag.begin(), strTag.end());          // wstring -> string

                if (ImGui::Selectable(strLabel.c_str(), bSelected))
                {
                    m_strSelectedTag = strTag;
                    m_pSelected = dynamic_pointer_cast<CMapObject>(pObject);
                }
            }
        }
        if (0 == iVisibleCount)
            ImGui::TextDisabled("(empty)");
        Validate_Selection();

        // 삭제버튼
        ImGui::Separator();
        ImGui::BeginDisabled(m_pSelected.expired());
        if (ImGui::Button("Delete"))
            Delete_Selected();
        ImGui::EndDisabled();
    }
    ImGui::End();
}

void CTool::Render_Scene()
{
    // 창의 크기와 위치 지정
    Set_NextPanelRect(m_tScene.fX, m_tScene.fY, m_tScene.fW, m_tScene.fH);

    // 창 옵션
    constexpr ImGuiWindowFlags eSceneFlags = g_FixedPanelFlags
        | ImGuiWindowFlags_NoScrollbar 
        | ImGuiWindowFlags_NoScrollWithMouse;

    // 스타일 스택 호출 -> 여백 없애기
    // 매개변수 1 -> ImGuiStyleVar idx : 바꿀 스타일 항목
    // ImGuiStyleVar_WindowPadding : 창 테두리와 그 안의 내용 사이 안쪽 여백을 바꾸겠다 (기본값은 8,8)
    // 매개변수 2 -> val : 새로운 값
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
    
    // 스타일 스택이 호출된 창 열기
    // 두 번째 매개변수를 nullptr로 받아서 X 버튼을 생성하지 않는다.
    ImGui::Begin("Scene", nullptr, eSceneFlags);

    // 스타일 스택 복구
    ImGui::PopStyleVar();

    // 사용할 수 있는 공간 계산
    // 현재 커서위치부터 창 오른쪽 아리까지 실제 위젯을 놓을 수 있는 공간 -> vAvail = (1040,854)
    const ImVec2 vAvail = ImGui::GetContentRegionAvail();

    // 씬 텍스처의 가로세로 비율
    float2_t vpSize = CGameInstance::Get().Get_ViewportSize();
    const f32_t fAspect = static_cast<f32_t>(vpSize.x) / vpSize.y;

    // 비율 맞추기                            
    ImVec2 vSize = vAvail; 
    if (vAvail.x / fAspect <= vAvail.y) 
        vSize.y = vAvail.x / fAspect;
    else                                
        vSize.x = vAvail.y * fAspect;

    // 가운데 정렬
    // ImGui의 "커서"
    // 위젯을 커서 위치에 놓고, 놓을 때마다 커서를 다음 줄로 옮긴다.

    // 커서의 위치를 설정한다.
    // 왼쪽 위에서 y좌표만 아래로 내린다.
    const ImVec2 vCursor = ImVec2(0, (vAvail.y - vSize.y) * 0.5f);   
    ImGui::SetCursorPos(vCursor);
    
    // 씬 텍스처 그리기
    // Renderer의 SRV를 가져와서 그린다
    ID3D11ShaderResourceView* pSRV = CGameInstance::Get().Get_SceneSRV();

    // (ImTextureID)pSRV -> 포인터를 ImGui의 텍스처 ID로 바꿔 담는다.
    // DX11 백엔드가 그릴 때 다시 ID3D11ShaderResourceView로 되돌려서 PS 0번 슬롯에 바인딩함.
    // vSize -> 화면에 그릴 크기
    // 실제로 그리는 것이 아닌 그리기 명령만 기록한다.
    // Image도 하나의 아이템으로 등록된다.
    ImGui::Image((ImTextureID)pSRV, vSize);

    // 나중에 쓸 정보 저장
    // Item 함수들은 바로 앞 아이템에대한 값을 준다. (다른 위젯을 넣으면 안됨)
    m_vImageMin     = float2_t(ImGui::GetItemRectMin().x, ImGui::GetItemRectMin().y);  // 화면 기준 좌상단 좌표
    m_vImageSize    = float2_t(vSize.x, vSize.y);   // 씬 화면 크기 -> 피킹에서 NDC로 바꿀 때 나누는 값
    m_bHovered      = ImGui::IsItemHovered();       // 카메라 드래그 + 카메라 피킹에 사용
    m_bFocused      = ImGui::IsWindowFocused();     // 마지막으로 클릭된 창일 때 true 카메라 조작 허용 
                                                    // (Begin과 End 사이에서 불려야 이 창에 대한 값이 나옴)
    ImGui::End();
}

void CTool::Render_Inspector()
{
    Set_NextPanelRect(m_tInspector.fX, m_tInspector.fY, m_tInspector.fW, m_tInspector.fH);
    if (ImGui::Begin("Inspector", nullptr, g_FixedPanelFlags))
    {
        ImGui::TextDisabled("No object selected");
    }
    ImGui::End();
}

unique_ptr<CTool> CTool::Create()
{
    auto pInstance = unique_ptr<CTool>(new CTool());
    if (FAILED(pInstance->Initialize()))
    {
        MSG_BOX("Failed to Created : CTool");
        pInstance.reset();
    }
    return pInstance;
}
