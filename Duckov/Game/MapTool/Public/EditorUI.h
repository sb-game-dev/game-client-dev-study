#pragma once
#include "EditorUI_Defines.h"

NS_BEGIN(MapTool)
class CPanel_Hierarchy;
class CPanel_Scene;
class CPanel_Inspector;

// 에디터 화면 전체
// 메뉴바, 레이아웃 계산, 공용 상태(EDITOR_CONTEXT) 보관, 패널 3개 소유
class CEditorUI final
{
private:
	CEditorUI() = default;
public:
	~CEditorUI();

public:
	HRESULT		Initialize();
	void		Update(const f32_t& fDeltaTime);
	bool_t		GetSceneCliked() { return m_Context.bSceneFocused; }
	bool_t		GetSceneHovered() { return m_Context.bSceneHovered; }

private:
	f32_t		m_fMenuBarHeight = {};
	f32_t		m_fSidePamelWidth = { 280.f };

	PANEL_RECT	m_tHierarchy = {};
	PANEL_RECT	m_tScene = {};
	PANEL_RECT	m_tInspector = {};

	EDITOR_CONTEXT					m_Context;		// 패널들이 참조로 공유

	unique_ptr<CPanel_Hierarchy>	m_pHierarchy;
	unique_ptr<CPanel_Scene>		m_pScene;
	unique_ptr<CPanel_Inspector>	m_pInspector;

private:
	void		Calc_Layout();
	void		Render_MenuBar();

public:
	static unique_ptr<CEditorUI> Create();
};

NS_END
