#pragma once
#include "Panel.h"
#include "ImGuizmo.h"

NS_BEGIN(MapTool)
class CPanel_Scene final : public CPanel
{
public:
	enum class BRUSH_MODE { PAINT, ERASE };
private:
	explicit CPanel_Scene(EDITOR_CONTEXT& Context) : CPanel{ Context } {}
public:
	virtual ~CPanel_Scene() = default;

public:
	virtual void	Render(const PANEL_RECT& tRect) override;
	void	Ready_Ray(vector_t& vRayOrigin, vector_t& vRayDir, const float2_t& vpSize);
	void	PickObject(vector_t vRayOrigin, vector_t vRayDir);
	void	PickTerrain(vector_t vRayOrigin, vector_t vRayDir);
	void	Change_BrushMode();
	void	Brush(vector_t vRayOrigin, vector_t vRayDir);
	void	Erase(vector_t vRayOrigin, vector_t vRayDir);
	void	Render_Guizmo(const ImVec2& vCursor);

private:
	ImGuizmo::OPERATION		m_eGizmoOp = ImGuizmo::TRANSLATE;
	float3_t m_vPickPos = {};

	BRUSH_MODE	m_eBrushMode = { BRUSH_MODE::PAINT };

private:
	void		Create_Object(const wstring_t& pPrototypeTag, float3_t vPickPos, const wstring_t& strModelTag = g_Models[0].strPrototypeTag);

public:
	static unique_ptr<CPanel_Scene> Create(EDITOR_CONTEXT& Context);
};
NS_END
