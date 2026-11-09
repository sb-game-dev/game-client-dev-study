#pragma once
#include "Panel.h"
#include "ImGuizmo.h"

NS_BEGIN(MapTool)
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
	float3_t m_vPickPos = {};
private:
	void		Create_Object(const wstring_t& pPrototypeTag, float3_t vPickPos);
	void		Create_StaticProp(const wstring_t& pPrototypeTag);

public:
	static unique_ptr<CPanel_Scene> Create(EDITOR_CONTEXT& Context);
};
NS_END
