#include "EditorUI_Utils.h"
#include "EditorUI.h"
#include "Panel_Hierarchy.h"
#include "Panel_Scene.h"
#include "Panel_Inspector.h"
#include "StaticProp.h"

CEditorUI::~CEditorUI()
{
}

HRESULT CEditorUI::Initialize()
{
    m_pHierarchy = CPanel_Hierarchy::Create(m_Context);
    m_pScene     = CPanel_Scene::Create(m_Context);
    m_pInspector = CPanel_Inspector::Create(m_Context);

    if (nullptr == m_pHierarchy || nullptr == m_pScene || nullptr == m_pInspector)
        return E_FAIL;

	return S_OK;
}

void CEditorUI::Update(const f32_t& fDeltaTime)
{
    Render_MenuBar();
    Calc_Layout();

    m_pHierarchy->Render(m_tHierarchy);
    m_pScene->Render(m_tScene);
    m_pInspector->Render(m_tInspector);


}

void CEditorUI::Calc_Layout()
{
    // 현재 창 영역 크기 (뷰포트 크기 가져오는 것과 비슷)
    const ImVec2 vDisplay = ImGui::GetIO().DisplaySize; // <- (1600,900)

    // 메뉴바 바로 아래부터의 시작 좌표
    const f32_t fTop    = m_fMenuBarHeight;
    const f32_t fHeight = vDisplay.y - fTop;

    // 최소 씬 폭 보정
    f32_t fSide = m_fSidePamelWidth;
    const f32_t fMinScene = 200.f;
    if (vDisplay.x - fSide * 2.f < fMinScene)
        fSide = max(0.f, (vDisplay.x - fMinScene) * 0.5f);

    // 세 창의 Rect 정보{Left,Top,Width,Height}
    m_tHierarchy    = { 0.f, fTop, fSide, fHeight };
    m_tScene        = { fSide, fTop, vDisplay.x - fSide * 2.f, fHeight };
    m_tInspector    = { vDisplay.x - fSide, fTop, fSide, fHeight };
}

void CEditorUI::Render_MenuBar()
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

        ImGui::MenuItem("New Scene", nullptr, false, true);        

        ImGui::MenuItem("Open Scene", "Ctrl + O", false, true);

        ImGui::MenuItem("Save", "Ctrl + S", false, true);

        ImGui::MenuItem("Save As", nullptr, false, true);
        ImGui::EndMenu();
    }

    ImGui::EndMainMenuBar();
}

HRESULT CEditorUI::Reset_Scene()
{

    return S_OK;
}

HRESULT CEditorUI::Save_Scene(const wstring& strPath)
{
    FILE* pFile;
    _wfopen_s(&pFile, strPath.c_str(), L"wb");

    auto Objects = CGameInstance::Get().Get_GameObjects(ETOUI(LEVEL::MAPTOOL), TEXT("Layer_Map"));
    uint32_t iNumObject = static_cast<uint32_t>(Objects->size());
    fwrite(&iNumObject, sizeof(uint32_t), 1, pFile);

    for (auto& [Tag, pObj] : *Objects)
    {
        auto pMapObj = dynamic_pointer_cast<CMapObject>(pObj);
        if (nullptr == pMapObj)
            continue;
        const wstring_t& strTag = pMapObj->Get_PrototypeTag();
        uint32_t iLength = static_cast<uint32_t>(strTag.length());

        fwrite(&iLength, sizeof(uint32_t), 1, pFile);
        fwrite(strTag.data(), sizeof(wchar_t), iLength, pFile);

        float3_t vPos = pMapObj->Get_Position();
        fwrite(&vPos, sizeof(float3_t), 1, pFile);

        float4_t vQuatern = pMapObj->Get_Quaternion();
        fwrite(&vQuatern, sizeof(float4_t), 1, pFile);

        float3_t vScale = pMapObj->Get_Scale();
        fwrite(&vScale, sizeof(float3_t), 1, pFile);

        wstring_t strModelPath = pMapObj->Get_MeshPath();
        uint32_t  iModelPathLength = strModelPath.length();

        fwrite(&iModelPathLength, sizeof(uint32_t), 1, pFile);
        fwrite(strModelPath.data(), sizeof(wchar_t), iModelPathLength, pFile);
    }
    
    fclose(pFile);
    return S_OK;
}

HRESULT CEditorUI::Load_Scene(const wstring& strPath)
{
    FILE* pFile;
    _wfopen_s(&pFile, strPath.c_str(), L"rb");

    auto Objects = CGameInstance::Get().Get_GameObjects(ETOUI(LEVEL::MAPTOOL), TEXT("Layer_Map"));
    uint32_t iNumObject = {};
    fread(&iNumObject, sizeof(uint32_t), 1, pFile);

    for (uint32_t i = 0; i < iNumObject; ++i)
    {
        uint32_t iLength = {};
        fread(&iLength, sizeof(uint32_t), 1, pFile);

        CStaticProp::STATICPROP_DESC Desc = {};
        Desc.strPrototypeTag.resize(iLength);
        fread(Desc.strPrototypeTag.data(), sizeof(wchar_t), iLength, pFile);
        fread(&Desc.vPosition, sizeof(float3_t), 1, pFile);
        fread(&Desc.vQuaternion, sizeof(float4_t), 1, pFile);
        fread(&Desc.vScale, sizeof(float3_t), 1, pFile);

        uint32_t  iModelPathLength = {};
        fread(&iModelPathLength, sizeof(uint32_t), 1, pFile);
        Desc.strMeshPath.resize(iModelPathLength);
        fread(Desc.strMeshPath.data(), sizeof(wchar_t), iModelPathLength, pFile);


        Desc.iLevelIndex = ETOUI(LEVEL::MAPTOOL);
        Desc.bEditorMode = true;

        wstring_t strTag;
        do {
            if (m_Context.m_iNextID < 10)
                strTag = L"Prop_0" + to_wstring(m_Context.m_iNextID++);
            else
                strTag = L"Prop_" + to_wstring(m_Context.m_iNextID++);
        } while (nullptr != CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::MAPTOOL), TEXT("Layer_Map"), strTag));

        if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::MAPTOOL), Desc.strPrototypeTag,
            ETOUI(LEVEL::MAPTOOL), TEXT("Layer_Map"), strTag, &Desc)))
        {
            MSG_BOX("Create Failed");
            return E_FAIL;
        }
        // 만든 객체를 바로 선택
        m_Context.Select(strTag, CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::MAPTOOL), TEXT("Layer_Map"), strTag));
    }
    fclose(pFile);
    return S_OK;
}

unique_ptr<CEditorUI> CEditorUI::Create()
{
    auto pInstance = unique_ptr<CEditorUI>(new CEditorUI());
    if (FAILED(pInstance->Initialize()))
    {
        MSG_BOX("Failed to Created : CEditorUI");
        pInstance.reset();
    }
    return pInstance;
}
