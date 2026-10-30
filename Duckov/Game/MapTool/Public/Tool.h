#pragma once
#include "MapTool_Defines.h"
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

	ImVec2 m_vImageMin = {};
	ImVec2 m_vImageSize = {};
	bool_t m_bHovered = {};
	bool_t m_bFocused = {};

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