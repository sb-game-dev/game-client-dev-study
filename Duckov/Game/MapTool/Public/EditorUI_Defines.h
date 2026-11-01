#pragma once
#include "MapTool_Defines.h"
#include "MapObject.h"

NS_BEGIN(MapTool)

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

// { 표시 이름, 경로 } 목록 (Inspector 콤보, Hierarchy 생성 기본값)
struct ASSET_ITEM
{
	const char*		pName;		// 콤보 표시용
	const wchar_t*	pPath;		// DESC에 넣을 경로 (텍스처는 Resource 기준 상대 경로)
};

inline constexpr ASSET_ITEM g_Meshes[] = {
	{ "Cube", L"builtin/cube" },
	{ "Rect", L"builtin/rect" },
};

inline constexpr ASSET_ITEM g_Textures[] = {
	{ "WoodCrate01", L"Ex/WoodCrate01.dds" },
	{ "WoodCrate02", L"Ex/WoodCrate02.dds" },
};

NS_END
