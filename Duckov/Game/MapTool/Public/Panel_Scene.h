#pragma once
#include "Panel.h"
#include "ImGuizmo.h"

NS_BEGIN(MapTool)
// 엔진이 그린 씬 텍스처(RTT)를 비율에 맞춰 표시
// 포커스/hover/이미지 영역을 Context에 기록한다 (카메라, 피킹용)
class CPanel_Scene final : public CPanel
{
private:
	explicit CPanel_Scene(EDITOR_CONTEXT& Context) : CPanel{ Context } {}
public:
	virtual ~CPanel_Scene() = default;

public:
	virtual void	Render(const PANEL_RECT& tRect) override;

private:
	ImGuizmo::OPERATION		m_eGizmoOp = ImGuizmo::TRANSLATE;
	ImGuizmo::MODE			m_eGizmoMode = ImGuizmo::WORLD;

public:
	static unique_ptr<CPanel_Scene> Create(EDITOR_CONTEXT& Context);
};
NS_END
