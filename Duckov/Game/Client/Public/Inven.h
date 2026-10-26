#pragma once

#include "Client_Defines.h"
#include "GameObject.h"
NS_BEGIN(INVEN_UI)
// 패널 : 왼쪽 장비와 가방을 감싸는 큰 판
constexpr f32_t PANEL_LEFT = 42.f, PANEL_TOP = 117.f, PANEL_WIDTH = 320.f, PANEL_HEIGHT = 543.f;

// 장비 10칸 (2행 x 5열)
constexpr f32_t EQUIP_LEFT = 65.f, EQUIP_TOP = 151.4f;
constexpr f32_t EQUIP_WIDTH = 45.f, EQUIP_HEIGHT = 43.3f;
constexpr f32_t EQUIP_STEP_X = 57.5f, EQUIP_STEP_Y = 64.f;
constexpr int32_t EQUIP_COLS = 5;

// 가방 그리드
constexpr f32_t BAG_LEFT = 52.5f, BAG_TOP = 326.4f;
constexpr f32_t BAG_SIZE = 56.f;
constexpr f32_t BAG_STEP = 60.f;
constexpr int32_t BAG_COLS = 5;            

constexpr f32_t RADIUS = 8.f;	// 모서리를 둥글게 깎는 반지름
NS_END

NS_BEGIN(Client)

class CInven : public CGameObject
{
public:
	enum class INVEN_AREA { EQUIP, BAG, OUTSIDE, END };
	enum class DRAG_STATE { IDLE, PRESSED, DRAGGING, END };
	struct SLOT_POS // 칸 하나를 {영역, 번호} 쌍으로 설정. ex) {EQUIP, 2} -> 장비 3번째 칸 == 근접무기
	{
		INVEN_AREA eArea = INVEN_AREA::END;
		int32_t    iIndex = -1;
		bool operator==(const SLOT_POS& r) const 
		{ 
			return eArea == r.eArea && iIndex == r.iIndex; 
		}
	};

private:
	CInven(ComPtr<ID3D11Device>pDevice, ComPtr<ID3D11DeviceContext>pContext);
public:
	~CInven() = default;

public:
	virtual		HRESULT		Initialize_Prototype() override;
	virtual		HRESULT		Initialize(void* pArg) override;
	virtual		void		Priority_Update(f32_t fTimeDelta)override;
	virtual		void		Update(f32_t fTimeDelta)override;
	virtual		void		Late_Update(f32_t fTimeDelta)override;
	virtual		HRESULT		Render() override;

	const bool_t&		Is_Open() { return m_bOpen; }

private:
	shared_ptr<CVertexShader>   m_pVSCom;
	shared_ptr<CPixelShader>    m_pPSCom;
	shared_ptr<CTexture>        m_pIconTexCom;
	ComPtr<ID3D11Buffer>        m_pInstanceVB;
	static constexpr uint32_t   m_iMaxInstance = 1024;
	vector<VTXUI_INSTANCE>      m_Instances;

	bool_t						m_bOpen = { false };

	shared_ptr<ITEM>			m_pEquipSlots[ETOUI(EQUIP_SLOT::END)];
	vector<shared_ptr<ITEM>>	m_vecBackPack;
	vector<shared_ptr<ITEM>>	m_vecStorage;

	DRAG_STATE					m_eDragState = { DRAG_STATE::IDLE };
	POINT						m_ptMouse = {};				// 마우스 위치 (뷰포트 좌표, 좌상단 원점)
	SLOT_POS					m_tHoveredSlot = {};		// 마우스 아래의 슬롯 칸 정보
	SLOT_POS					m_tSelectedSlot = {};       // 클릭된 칸 (주황 테두리)
	SLOT_POS					m_tDraggedItemSlot = {};       // 집어 든 칸
	POINT						m_ptPress = {};             // 누른 위치 (4px 판정용)

private:
	HRESULT					Ready_Components();
	void					Build_Instances();

	float4_t				Get_SlotRect(const SLOT_POS& t);
	shared_ptr<ITEM>&		Get_SlotItem(const SLOT_POS& t);	// 슬롯 정보로 아이템의 주소를 받아오는 함수

	void					Push_Rect(f32_t fLeft, f32_t fTop, f32_t fWidth, f32_t fHeight, float4_t vColor, f32_t fRadius = 0.f, f32_t fBorder = 0.f);// fBorder : 외곽선 두께
	void					Push_Icon(f32_t fLeft, f32_t fTop, f32_t fWidth, f32_t fHeight, int32_t iIcon, f32_t fAlpha = 1.f);
	void					Push_ItemIcon(const float4_t& vRect, const shared_ptr<ITEM>& pItem, f32_t fAlpha);
	void					Push_Slot(const SLOT_POS& t);

	SLOT_POS				Find_CollidedSlot(POINT pt);
	static bool_t			Is_InRect(POINT pt, const float4_t& vRect);
	static bool_t			Is_Slot(const SLOT_POS& t);

	void					Update_DragState();                                        // 드래그 상태 머신 + 선택된 아이템 정보 + 위치 저장
	void					Drop(const SLOT_POS& tSrcSlot, const SLOT_POS& tDstSlot);     // 놓기 

	bool_t					CanPlace(const shared_ptr<ITEM>& pItem, const SLOT_POS& tDstSlot);

	static shared_ptr<ITEM>	Init_TestItem(shared_ptr<ITEM> pItem, ITEM_TYPE eType, const wchar_t* pName,
										  int32_t iTypeID, int32_t iIconIndex, int32_t iQuality,
										  int32_t iCount = 1, int32_t iMaxStack = 1)

	{
		pItem->eItemType = eType;
		pItem->strItemName = pName;
		pItem->iTypeID = iTypeID;
		pItem->iIconIndex = iIconIndex;
		pItem->iQuality = iQuality;
		pItem->iCount = iCount;
		pItem->iMaxStack = iMaxStack;
		pItem->bStackable = iMaxStack > 1;
		return pItem;
	}


public:
	static shared_ptr<CInven>		Create(ComPtr<ID3D11Device>pDevice, ComPtr<ID3D11DeviceContext>pContext);
	shared_ptr<CPrototype>			Clone(void* pArg) override;
};

NS_END