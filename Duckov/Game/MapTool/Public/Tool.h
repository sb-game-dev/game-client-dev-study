#pragma once
#include "MapTool_Defines.h"
NS_BEGIN(Client)
class CMapObject;
NS_END
NS_BEGIN(MapTool)
class CTool final
{

private:
	CTool() = default;
public:
	~CTool() = default;

public:
	HRESULT		Initialize();
	void		Update(const f32_t& fDeltaTime);
	bool_t		GetSceneCliked() { return m_bFocused; }
private:
	struct PANEL_RECT
	{
		f32_t fX, fY, fW, fH;
	};

private:
	f32_t		m_fMenuBarHeight = {};
	f32_t		m_fSidePamelWidth = { 280.f };
	bool_t		m_bShowDemo = { false };

	PANEL_RECT	m_tHierarchy = {};
	PANEL_RECT	m_tScene = {};
	PANEL_RECT	m_tInspector = {};

	float2_t	m_vImageMin = {};
	float2_t	m_vImageSize = {};
	bool_t		m_bHovered = {};
	bool_t		m_bFocused = {};

private:
	// Type 콤보박스
	struct PLACEABLE
	{
		const char* pName;				// 콤보 박스에 보일 이름
		const wchar_t* pPrototypeTag;	// Add_GameObject에 넘길 프로토타입 태그
	};
	
	static constexpr PLACEABLE s_Placeables[] = {
		{ "Add Static_Prop", Proto::Obj_StaticProp },
	};

	// Mesh 콤보박스
	struct MESH_ITEM
	{
		const char* pName;		// 콤보 표시용
		const wchar_t* pPath;   // DESC에 넣을 경로
	};
	static constexpr MESH_ITEM s_Meshes[] = {
		{ "Cube", L"builtin/cube" },
		{ "Rect", L"builtin/rect" },
	};

	// 텍스처 콤보박스
	struct TEXTURE_ITEM
	{
		const char* pName;   // 콤보 표시용
		const wchar_t* pPath;   // Resource 기준 상대 경로
	};
	static constexpr TEXTURE_ITEM s_Textures[] = {
		{ "WoodCrate01", L"Ex/WoodCrate01.dds" },
		{ "WoodCrate02", L"Ex/WoodCrate02.dds" },
	};


	// 생성 설정 (UI 입력값)
	int32_t     m_iPlaceableIndex = {};								// s_Placeables 중 몇 번째인지
	int32_t     m_iMeshIndex = {};									// s_Meshes 중 몇 번째인지
	int32_t     m_iTextureIndex = {};
	uint32_t    m_iNextID = {};										// "Prop_N"의 N

	// 오브젝트 선택
	weak_ptr<CMapObject>	m_pSelected;								// 지금 선택한 객체
	wstring_t				m_strSelectedTag;							// 선택한 객체의 태그
	bool_t					m_bRequestDelete = { false };

private:
	void        Create_Object(const wchar_t* pPrototypeTag);
	void        Delete_Selected(); 
	void		Validate_Selection();
private:
	void		Calc_Layout();
	void		Render_MenuBar();
	void		Render_Hierachy();
	void		Render_Scene();
	void		Render_Inspector();

public:
	static unique_ptr<CTool> Create();

};

NS_END