#pragma once
#include "MapTool_Defines.h"
#include "MapObject.h"

NS_BEGIN(MapTool)

inline constexpr ImGuiWindowFlags g_FixedPanelFlags =
ImGuiWindowFlags_NoMove                 // 제목 표시줄을 드래그해도 안 움직임
| ImGuiWindowFlags_NoResize             // 모서리를 끌어도 크기 안 바뀜
| ImGuiWindowFlags_NoCollapse           // 제목 표시줄의 접기 버튼 제거
| ImGuiWindowFlags_NoSavedSettings;     // 창 정보를 저장하지 않음

// 창 하나의 위치와 크기 (CEditorUI::Calc_Layout에서 계산)
struct PANEL_RECT
{
	f32_t fX, fY, fW, fH;
};

// 패널끼리 같이 쓰는 상태
// CEditorUI가 소유하고, 각 패널은 참조로 받는다.
struct EDITOR_CONTEXT
{
	// 선택
	// Hierarchy가 바꾸고 Inspector가 읽는다. (나중에 Scene 피킹도 여기에 쓴다)
	weak_ptr<CMapObject>	pSelected;			// weak_ptr: 지워지면 자동으로 만료
	wstring_t				strSelectedTag;		// 선택된 객체의 이름 ("Prop_01")
	uint32_t				m_iNextID = {};		// "Prop_N"의 N

	// Scene 창
	float2_t	vImageMin = {};					// 화면 기준 씬 이미지 좌상단 (피킹용)
	float2_t	vImageSize = {};				// 씬 이미지 크기 (피킹에서 NDC로 바꿀 때 나누는 값)
	bool_t		bSceneHovered = {};				// 씬 이미지 위에 마우스가 있는지
	bool_t		bSceneFocused = {};				// Scene 창이 포커스인지 -> 카메라 조작 허용

	void Select(const wstring_t& strTag, shared_ptr<CGameObject> pObject)
	{
		strSelectedTag = strTag;
		pSelected = dynamic_pointer_cast<CMapObject>(pObject);
	}

	void Clear_Selection()
	{
		pSelected.reset();
		strSelectedTag.clear();
	}

	// 선택한 객체가 지워졌으면 선택 해제
	void Validate_Selection()
	{
		auto pObject = pSelected.lock();
		if (nullptr == pObject || pObject->Is_Dead())
			Clear_Selection();
	}
};

// 빈 곳 우클릭 메뉴에 보일 배치 가능한 목록
struct PLACEABLE
{
	const char* pName;				// 메뉴에 보일 이름
	const wchar_t* pPrototypeTag;		// Add_GameObject에 넘길 프로토타입 태그
};

static constexpr PLACEABLE s_Placeables[] = {
	{ "Add Static_Prop", Proto::Obj_StaticProp },
	{ "Add Terrain", Proto::Obj_Hill },
};

// { 표시 이름, 경로 } 목록 (Inspector 콤보, Hierarchy 생성 기본값)
struct ASSET_ITEM
{
	const char*		pDisplayName;	// 콤보 표시용
	const wchar_t*	pPath;			// DESC에 넣을 경로 (텍스처는 Resource 기준 상대 경로)
};

struct ASSET_ENTRY
{
	string    strDisplayName;  // 콤보에 보일 이름 (ImGui용 UTF-8)
	wstring_t strPath;         // 프로토타입 태그 (정규화된 경로)
};

inline vector<ASSET_ENTRY> g_Meshes;

//inline constexpr ASSET_ITEM g_Meshes[] = {
//	{ "Duck", L"Characters/0_CharacterModel_Boss_Wu/0_CharacterModel_Boss_Wu.fbx" },
//	{ "ZeroZoneTree", L"Mesh/Tree/Pfb_Tree_01_1.fbx" },
//};

inline constexpr ASSET_ITEM g_Textures[] = {
	{ "WoodCrate01", L"Ex/WoodCrate01.dds" },
	{ "WoodCrate02", L"Ex/WoodCrate02.dds" },
	{ "WireFence", L"Ex/WireFence.dds" },
};

NS_END
