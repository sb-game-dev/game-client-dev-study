#pragma once
#include "Panel.h"

NS_BEGIN(MapTool)
// 선택한 객체의 이름, Transform, 타입별 섹션(Static Prop: Mesh / Texture)
// 타입별 섹션은 dynamic_pointer_cast로 분기 (ImGui 코드를 Client 클래스에 넣지 않기)
class CPanel_Inspector final : public CPanel
{
private:
	explicit CPanel_Inspector(EDITOR_CONTEXT& Context) : CPanel{ Context } {}
public:
	virtual ~CPanel_Inspector() = default;

public:
	virtual void	Render(const PANEL_RECT& tRect) override;

public:
	static unique_ptr<CPanel_Inspector> Create(EDITOR_CONTEXT& Context);
};
NS_END
