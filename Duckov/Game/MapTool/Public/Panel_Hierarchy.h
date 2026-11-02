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
	// 빈 곳 우클릭 메뉴에 보일 배치 가능한 목록
	struct PLACEABLE
	{
		const char*		pName;				// 메뉴에 보일 이름
		const wchar_t*	pPrototypeTag;		// Add_GameObject에 넘길 프로토타입 태그
	};

	static constexpr PLACEABLE s_Placeables[] = {
		{ "Add Static_Prop", Proto::Obj_StaticProp },
	};

private:
	uint32_t	m_iNextID = {};						// "Prop_N"의 N
	bool_t		m_bRequestDelete = { false };		// 목록 루프가 끝난 뒤 삭제

private:
	void		Create_Object(const wstring_t& pPrototypeTag);
	void		Delete_Selected();

public:
	static unique_ptr<CPanel_Hierarchy> Create(EDITOR_CONTEXT& Context);
};
NS_END
