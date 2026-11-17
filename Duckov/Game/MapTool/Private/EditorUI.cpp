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

        if (ImGui::MenuItem("New Scene", nullptr, false, true))
        {
            Reset_Scene();
            m_strCurrentPath.clear();
        }

        if (ImGui::MenuItem("Open Scene", "Ctrl + O", false, true))
        {
            wstring strPath;
            if (Open_FileDialog(strPath, false))
            {
                if (FAILED(Load_Scene(strPath)))
                    return;
                m_strCurrentPath = strPath;
            }
        }

        if (ImGui::MenuItem("Save", "Ctrl + S", false, true))
        {
            if (m_strCurrentPath.empty())
                Save_As();
            else
                Save_Scene(m_strCurrentPath);   
        }

        if (ImGui::MenuItem("Save As", nullptr, false, true))
            Save_As();
        ImGui::EndMenu();
    }
    
    ImGui::EndMainMenuBar();
}

HRESULT CEditorUI::Reset_Scene()
{
    auto pObjects = CGameInstance::Get().Get_GameObjects(ETOUI(LEVEL::MAPTOOL), TEXT("Layer_Map"));
    if (nullptr == pObjects)
        return S_OK;
    for (auto& pObj : *pObjects)
    {
        pObj.second->Set_Dead();
    }
    m_Context.Clear_Selection();
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
        uint32_t  iModelPathLength = static_cast<uint32_t>(strModelPath.length());

        fwrite(&iModelPathLength, sizeof(uint32_t), 1, pFile);
        fwrite(strModelPath.data(), sizeof(wchar_t), iModelPathLength, pFile);
    }
    fclose(pFile);
    return S_OK;
}

HRESULT CEditorUI::Load_Scene(const wstring& strPath)
{
    Reset_Scene();
    FILE* pFile;
    _wfopen_s(&pFile, strPath.c_str(), L"rb");

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
        if (m_Context.iNumObject < 10)
            strTag = L"Prop_0" + to_wstring(m_Context.iNumObject++);
        else
            strTag = L"Prop_" + to_wstring(m_Context.iNumObject++);

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

bool_t CEditorUI::Open_FileDialog(wstring& strOutPath, bool_t bSave)
{
    wchar_t szFile[MAX_PATH] = L"NewScene.bin";
    if (!m_strCurrentPath.empty())
        lstrcpynW(szFile, m_strCurrentPath.c_str(), MAX_PATH);

    wchar_t szInitDir[MAX_PATH] = {};
    GetFullPathNameW(L"../../../Resource/SceneData", MAX_PATH, szInitDir, nullptr);

    // 입력: 대화상자를 어떻게 띄울지 알려줌.
    // 출력: 사용자가 무엇을 골랐는지 돌려받음.
    OPENFILENAMEW ofn = {};

    // 반드시 채워야하는 구조체 크기
    ofn.lStructSize = sizeof(ofn);

    // 대화상자의 주인 창 지정(입력)
    // 대화상자를 닫을 때 까지 맵툴 창이 비활성화됨.(대화상자가 열려있는 채로 맵툴 조작 불가)
    ofn.hwndOwner = g_hWnd;

    // 파일 형식 목록(입력)
    // 대화상자 우측 하단에 파일형식 콤보박스의 내용
    // 문자열 하나에 여러 항목을 \0으로 구분해서 넣는 형식
    // "표시이름\0패턴\0표시이름\0패턴\0" 형식이고 끝은 \0이 두번이어야 한다.
    ofn.lpstrFilter = L"Scene Data (*.bin)\0*.bin\0All Files (*.*)\0*.*\0";

    // 처음 선택될 필터(입력/출력)
    ofn.nFilterIndex = 1;

    // 파일 경로 버퍼(입력/출력)
    // 입력일 경우 대화상자가 열릴 때 "파일 이름" 칸에 미리 채워지는 값
    // 출력일 경우 사용자가 "열기/저장"을 누르면 고른 파일의 전체 절대경로가 저장됨
    ofn.lpstrFile = szFile;

    // 버퍼 크기(입력)
    ofn.nMaxFile = MAX_PATH;

    // 처음 열릴 폴더의 경로(입력)
    ofn.lpstrInitialDir = szInitDir;

    // 기본 확장자(입력)
    ofn.lpstrDefExt = L"bin";

    // 플래그 - 동작 옵션
    ofn.Flags = OFN_NOCHANGEDIR | OFN_PATHMUSTEXIST; // 현재 작업 디렉터리를 원래대로  | 사용자가 입력한 폴더가 실제로 있어야함

    if (bSave)
        ofn.Flags |= OFN_OVERWRITEPROMPT;   // 저장할 때 같은 이름의 파일이 있다면 "바꾸시겠습니까?"를 물음
    else
        ofn.Flags |= OFN_FILEMUSTEXIST;     // 파일까지 실제로 있어야 열 수 있음

    // 확인을 누르면 TRUE, 취소하거나 닫으면 FALSE.
    const BOOL bOK = bSave ? GetSaveFileNameW(&ofn) : GetOpenFileNameW(&ofn);
    if (!bOK)
        return false;

    strOutPath = szFile;
    return true;
}

void CEditorUI::Save_As()
{
    wstring_t   strPath;
    if (!Open_FileDialog(strPath, true))
        return;
    if(FAILED(Save_Scene(strPath)))
        return;
    m_strCurrentPath = strPath;
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
