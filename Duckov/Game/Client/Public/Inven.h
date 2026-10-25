#pragma once

#include "Client_Defines.h"
#include "GameObject.h"
NS_BEGIN(INVEN_UI)
	// 패널 : 왼쪽 장비와 가방을 감싸는 큰 판
	constexpr f32_t PANEL_LEFT = 42.f, PANEL_TOP = 117.f, PANEL_WIDTH = 320.f, PANEL_HEIGHT = 543.f;

	// 장비 10칸 (5열 × 2행): 아이템 박스 45×43 + 아래 라벨 16
	constexpr f32_t EQUIP_LEFT = 65.f, EQUIP_TOP = 151.4f;
	constexpr f32_t EQUIP_WIDTH = 45.f, EQUIP_HEIGHT = 43.3f;
	constexpr f32_t EQUIP_STEP_X = 57.5f, EQUIP_STEP_Y = 64.f;// 다음 열 까지의 거리, 다음 행 까지의 거리

	// 가방 그리드: 60×60 칸, 간격 0, 5열. 칸 안의 실제 박스는 사방 2px 안쪽(56×56)
	constexpr f32_t BAG_LEFT = 52.5f, BAG_TOP = 326.4f, BAG_CELL = 60.f, BAG_INSET = 2.f;
	constexpr int32_t BAG_COLS = 5;

	constexpr f32_t RADIUS = 8.f;	// 모서리를 둥글게 깎는 반지름
NS_END

NS_BEGIN(Client)

class CInven : public CGameObject
{
public:
	enum class INVEN_AREA { NONE, EQUIP, BAG, OUTSIDE };
	struct SLOT_REF // 칸 하나를 {영역, 번호} 쌍으로 설정. ex) {EQUIP, 2} -> 장비 3번째 칸 == 근접무기
	{
		INVEN_AREA eArea = INVEN_AREA::NONE;
		int32_t    iIndex = -1;
		bool operator==(const SLOT_REF& r) const 
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

	float4_t Get_SlotRect(const SLOT_REF& t) //칸 번호를 화면 사각형으로 반환(Left, Top, Width, Height)
	{
		using namespace INVEN_UI;
		if (t.eArea == INVEN_AREA::BAG)
			return { BAG_LEFT + (t.iIndex % BAG_COLS) * BAG_CELL + BAG_INSET,
					 BAG_TOP + (t.iIndex / BAG_COLS) * BAG_CELL + BAG_INSET,
					 BAG_CELL - BAG_INSET * 2.f, BAG_CELL - BAG_INSET * 2.f };

		if (t.eArea == INVEN_AREA::EQUIP)
			return { EQUIP_LEFT + (t.iIndex % 5) * EQUIP_STEP_X, EQUIP_TOP + (t.iIndex / 5) * EQUIP_STEP_Y,
					 EQUIP_WIDTH, EQUIP_HEIGHT };
		return {};
	}

	void		AddEquipSlot(EQUIP_SLOT eSlotID, shared_ptr<ITEM> pItem);
	
	shared_ptr<ITEM>&		GetSlot(EQUIP_SLOT eSlotID) { return m_pEquipSlots[static_cast<int>(eSlotID)]; }
	//shared_ptr<ITEM>&		GetSlot(f32_t x, f32_t y) { return nullptr; }

	void		RenderEquipSlot();
	void		RenderStorage();
	void		RenderBag();

private:
	shared_ptr<CVertexShader>   m_pVSCom;
	shared_ptr<CPixelShader>    m_pPSCom;
	shared_ptr<CTexture>        m_pIconTexCom;          
	ComPtr<ID3D11Buffer>        m_pInstanceVB;
	static constexpr uint32_t   m_iMaxInstance = 1024;
	vector<VTXUI_INSTANCE>      m_Instances;


	bool_t							m_bOpen = { true };
	shared_ptr<ITEM>				m_pEquipSlots[static_cast<int>(EQUIP_SLOT::END)];
	vector<shared_ptr<ITEM>>		m_vecBackPack;
	vector<shared_ptr<ITEM>>		m_vecStorage;

private:
	void	Push_Rect(f32_t fLeft, f32_t fTop, f32_t fWidth, f32_t fHeight, float4_t vColor, f32_t fRadius = 0.f, f32_t fBorder = 0.f);// fBorder : 외곽선 두께
	void	Push_Icon(f32_t fLeft, f32_t fTop, f32_t fWidth, f32_t fHeight, int32_t iIcon, f32_t fAlpha = 1.f);
	void	Build_Instances();
	HRESULT Ready_Components();

public:
	static shared_ptr<CInven>		Create(ComPtr<ID3D11Device>pDevice, ComPtr<ID3D11DeviceContext>pContext);
	shared_ptr<CPrototype>			Clone(void* pArg) override;
};

NS_END