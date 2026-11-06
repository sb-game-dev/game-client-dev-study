#pragma once

#include "Client_Defines.h"
#include "GameObject.h"
NS_BEGIN(HUD_UI)
// 무기 칸 
constexpr f32_t WEAPON_LEFT = 480.5f, WEAPON_TOP = 631.f;
constexpr f32_t WEAPON_SIZE = 64.f, WEAPON_STEP = 74.f;          // 무기1 480.5, 무기2 554.5
constexpr f32_t MELEE_LEFT = 628.5f, MELEE_TOP = 655.f, MELEE_SIZE = 40.f;
constexpr f32_t WEAPON_RADIUS = 16.f;

// 퀵슬롯 3~8 
constexpr f32_t QUICK_LEFT = 677.5f, QUICK_TOP = 645.f;
constexpr f32_t QUICK_SIZE = 50.f, QUICK_STEP = 60.f;

// 키 배지 
constexpr f32_t BADGE_GAP = 2.5f, BADGE_HEIGHT = 20.f, BADGE_PAD_X = 6.f, BADGE_RADIUS = 4.f;

// 원형 게이지 
constexpr f32_t WATER_CX = 373.2f, ENERGY_CX = 430.5f, GAUGE_CY = 668.2f;
constexpr f32_t GAUGE_SIZE = 50.f;

// HP 바
constexpr f32_t HP_LEFT = 213.f, HP_TOP = 668.2f, HP_WIDTH = 130.f, HP_HEIGHT = 25.f;
constexpr f32_t HP_SLIDER_LEFT = 236.8f, HP_SLIDER_TOP = 672.2f, HP_SLIDER_WIDTH = 102.7f, HP_SLIDER_HEIGHT = 17.f;
NS_END

NS_BEGIN(Client)

class CHUD : public CGameObject
{
public:
	enum class INVEN_AREA { EQUIP, BAG, QUICK, OUTSIDE, END };
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
	CHUD(ComPtr<ID3D11Device>pDevice, ComPtr<ID3D11DeviceContext>pContext);
public:
	~CHUD() = default;

public:
	virtual		HRESULT		Initialize_Prototype() override;
	virtual		HRESULT		Initialize(void* pArg) override;
	virtual		void		Priority_Update(f32_t fTimeDelta)override;
	virtual		void		Update(f32_t fTimeDelta)override;
	virtual		void		Late_Update(f32_t fTimeDelta)override;
	virtual		HRESULT		Render() override;

	const bool_t& Is_Open() { return m_bOpen; }

private:
	shared_ptr<CVertexShader>   m_pVSCom;
	shared_ptr<CPixelShader>    m_pPSCom;
	shared_ptr<CTexture>        m_pIconTexCom;
	ComPtr<ID3D11Buffer>        m_pInstanceVB;
	static constexpr uint32_t   m_iMaxInstance = 1024;
	vector<VTXUI_INSTANCE>      m_Instances;

	bool_t						m_bOpen = { false };

	shared_ptr<ITEM>			m_pEquipSlots[ETOUI(EQUIP_SLOT::END)];
	shared_ptr<ITEM>			m_pQuickSlots[ETOUI(EQUIP_SLOT::END)];
	vector<shared_ptr<ITEM>>	m_vecBackPack;
	vector<shared_ptr<ITEM>>	m_vecStorage;

	DRAG_STATE					m_eDragState = { DRAG_STATE::IDLE };
	POINT						m_ptMouse = {};				// 마우스 위치 (뷰포트 좌표, 좌상단 원점)
	SLOT_POS					m_tHoveredSlot = {};		// 마우스 아래의 슬롯 칸 정보
	SLOT_POS					m_tSelectedSlot = {};       // 클릭된 칸 (주황 테두리)
	SLOT_POS					m_tDraggedItemSlot = {};    // 집어 든 칸
	POINT						m_ptPress = {};             // 누른 위치 (4px 판정용)

private:
	HRESULT					Ready_Components();
	HRESULT					Ready_InstanceBuffer();
	void					Build_Instances();

	float4_t				Get_SlotRect(const SLOT_POS& t);
	shared_ptr<ITEM>& Get_SlotItem(const SLOT_POS& t);	// 슬롯 정보로 아이템의 주소를 받아오는 함수

	void					Push_Rect(f32_t fLeft, f32_t fTop, f32_t fWidth, f32_t fHeight, float4_t vColor, f32_t fRadius = 0.f, f32_t fBorder = 0.f);// fBorder : 외곽선 두께
	void					Push_Icon(f32_t fLeft, f32_t fTop, f32_t fWidth, f32_t fHeight, int32_t iIcon, f32_t fAlpha = 1.f);
	void					Push_ItemIcon(const float4_t& vRect, const shared_ptr<ITEM>& pItem, f32_t fAlpha);
	void					Push_Slot(const SLOT_POS& t);

	SLOT_POS				Find_CollidedSlot(POINT pt);
	static bool_t			Is_InRect(POINT pt, const float4_t& vRect);
	static bool_t			Is_Slot(const SLOT_POS& t);

	void					Update_DragState();												// 드래그 상태 머신 + 선택된 아이템 정보 + 위치 저장
	void					Drop(const SLOT_POS& tSrcSlot, const SLOT_POS& tDstSlot);		// 놓기 

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
	static shared_ptr<CHUD>		Create(ComPtr<ID3D11Device>pDevice, ComPtr<ID3D11DeviceContext>pContext);
	shared_ptr<CPrototype>			Clone(void* pArg) override;
};

NS_END