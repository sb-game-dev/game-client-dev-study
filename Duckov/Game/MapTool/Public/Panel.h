#pragma once
#include "EditorUI_Defines.h"

NS_BEGIN(MapTool)
// 에디터 창 하나 (Hierarchy, Scene, Inspector)
// 위치/크기는 CEditorUI가 계산해서 Render에 넘겨준다.
class CPanel abstract
{
protected:
	explicit CPanel(EDITOR_CONTEXT& Context) : m_Context{ Context } {}
public:
	virtual ~CPanel() = default;

public:
	virtual void	Render(const PANEL_RECT& tRect) = 0;

protected:
	EDITOR_CONTEXT&		m_Context;		// CEditorUI가 소유한 공용 상태
};
NS_END
