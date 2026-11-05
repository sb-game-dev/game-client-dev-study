#pragma once
#include "Panel.h"

NS_BEGIN(MapTool)
// 객체 이름 목록 + 선택 + 우클릭 생성/삭제
// 값 편집은 하지 않는다 (Inspector 담당)
class CPanel_Hierarchy final : public CPanel
{
private:
	explicit CPanel_Hierarchy(EDITOR_CONTEXT& Context) : CPanel{ Context } {}
public:
	virtual ~CPanel_Hierarchy() = default;

public:
	virtual void	Render(const PANEL_RECT& tRect) override;

private:
	uint32_t	m_iNextID = {};						// "Prop_N"의 N
	bool_t		m_bRequestDelete = { false };		// 목록 루프가 끝난 뒤 삭제

private:
	void		Create_Object(const wstring_t& pPrototypeTag);
	void		Create_Terrain();
	void		Create_Cube();
	void		Create_StaticProp(const wstring_t& pPrototypeTag);
	void		Delete_Selected();

public:
	static unique_ptr<CPanel_Hierarchy> Create(EDITOR_CONTEXT& Context);
};
NS_END
