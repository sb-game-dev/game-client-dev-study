#pragma once

#include "Client_Defines.h"
#include "GameObject.h"
NS_BEGIN(HUD_UI)
// 위치 좌표 : 직교 공간 (화면 중앙 원점, x 오른쪽, y 위쪽, 1 = 1px). LEFT/TOP 은 사각형의 왼쪽 변 x, 위쪽 변 y
// 무기 칸 
constexpr f32_t WEAPON_LEFT = -159.5f, WEAPON_TOP = -271.f;
constexpr f32_t WEAPON_SIZE = 64.f, WEAPON_STEP = 74.f;          // 무기1 -159.5, 무기2 -85.5

constexpr f32_t MELEE_LEFT = -11.5f, MELEE_TOP = -295.f, MELEE_SIZE = 40.f;

constexpr f32_t WEAPON_RADIUS = 16.f;
constexpr f32_t BORDER_FRAME = 1.f;			// 칸 테두리 
constexpr f32_t BORDER_SELECTED = 2.f;		// 선택 테두리   

// 퀵슬롯 3~8 
constexpr f32_t QUICK_LEFT = 37.5f, QUICK_TOP = -285.f;
constexpr f32_t QUICK_SIZE = 50.f, QUICK_STEP = 60.f;

// 키 배지 
constexpr f32_t BADGE_GAP = 2.5f, BADGE_HEIGHT = 20.f, BADGE_PAD_X = 6.f, BADGE_RADIUS = 4.f;

// HP 바
constexpr f32_t HP_LEFT = -427.f, HP_TOP = -308.2f, HP_WIDTH = 130.f, HP_HEIGHT = 25.f;
constexpr f32_t HP_SLIDER_LEFT = -403.2f, HP_SLIDER_TOP = -312.2f, HP_SLIDER_WIDTH = 102.7f, HP_SLIDER_HEIGHT = 17.f;

// HP바 아이콘 
constexpr f32_t HEART_LEFT = -423.1f, HEART_TOP = -311.9f, HEART_SIZE = 17.5f;

// 물방울, 번개 아이콘 크기
constexpr f32_t HUD_ICON_SIZE = 20.f;

// 물방울, 번개 아이콘 위치
const float2_t HUD_ENERGY_CENTER = { -209.5f, -308.2f };
const float2_t HUD_WATER_CENTER  = { -266.8f, -308.2f };

// 불방울 번개 아이콘 반지름
const f32_t HUD_RING_OUTER_SIZE = 25.f;			// 바깥 링 반지름
const f32_t HUD_RING_BORDER = 8.f;				// 바깥 링 두께
const f32_t HUD_RING_INNER_SIZE = 14.5f;		// 안쪽 원 반지름
const f32_t HUD_RING_FILL_SIZE = 22.5f;			// 채움 링 반지름
const f32_t HUD_RING_FILL_BORDER = 0.5f;		// 채움 링 두께
const f32_t HUD_RING_FILL_INNER_SIZE = 18.5f;	// 채움 링 안쪽 반지름
const f32_t HUD_RING_ICON_SIZE = 10.f;			// 아이콘 크기

// 스테미너 
const f32_t HUD_RING_STAMINA_BG_OUTER_SIZE = 11.25;
const f32_t HUD_RING_STAMINA_BG_INNER_SIZE = 3.75;
const f32_t HUD_RING_STAMINA_FILL_OUTER_SIZE = 8.75;
const f32_t HUD_RING_STAMINA_FILL_INNER_SIZE = 6.25;
const float2_t STAMINA_OFFSET = { -30.f,-15.f };


// 색상
constexpr float4_t COLOR_HUD_SLOT_BG_LIGHT = { 0.f, 0.f, 0.f, 0.3f };	// 1, 2, V (무기 칸)
constexpr float4_t COLOR_HUD_SLOT_BG_DARK = { 0.f, 0.f, 0.f, 0.58f };	// 3 ~ 8 (퀵슬롯)
constexpr float4_t COLOR_SELECTED = { 1.f, 1.f, 1.f, 1.f };				// 선택 테두리  
constexpr float4_t COLOR_HP_BG = { 0.f, 0.f, 0.f, 0.745f };
constexpr float4_t COLOR_HP_FILL_SIDE = { 0.f, 0.f, 0.f, 1.f };
constexpr float4_t COLOR_HP_FILL = { 1.f, 0.553f, 0.553f, 1.f };
constexpr float4_t COLOR_WATER_ICON  = { 0.165f, 0.678f, 1.f, 0.75f };
constexpr float4_t COLOR_ENERGY_ICON = { 1.f, 0.596f, 0.165f, 0.75f };
constexpr float4_t COLOR_STAMINA_FILL = { 0.678f, 1.0f, 0.427f, 1.0f };
constexpr float4_t COLOR_STAMINA_FILL_YELLOW = { 1.f, 0.976f, 0.016f, 1.f };
NS_END

NS_BEGIN(Client)

class CHUD : public CGameObject
{
private:
	enum class HUD_AREA { GUN, MELEE, SLOT, END };
	struct HUD_POS
	{
		HUD_AREA eArea = HUD_AREA::END;
		int32_t    iIndex = -1;
		bool operator==(const HUD_POS& r) const
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
	virtual		void		Priority_Update(f32_t fDeltaTime)override;
	virtual		void		Update(f32_t fDeltaTime)override;
	virtual		void		Late_Update(f32_t fDeltaTime)override;
	virtual		HRESULT		Render() override;


private:
	shared_ptr<CVertexShader>		m_pVSCom;
	shared_ptr<CPixelShader>		m_pPSCom;
	shared_ptr<CVertexShader>		m_pVSCircleCom;
	shared_ptr<CPixelShader>		m_pPSCircleCom;
	shared_ptr<CTexture>			m_pIconTexCom;
	shared_ptr<CTexture>			m_pHUDIconTexCom;
	ComPtr<ID3D11Buffer>			m_pVB = { nullptr };
	ComPtr<ID3D11Buffer>			m_pIB = { nullptr };
	uint32_t						m_iIndexCnt = {};
	ComPtr<ID3D11Buffer>			m_pInstanceVB;
	ComPtr<ID3D11Buffer>			m_pInstanceVB_Circle;
	static constexpr uint32_t		m_iMaxInstance = 1024;
	vector<VTXUI_INSTANCE>			m_Instances;
	vector<VTXUI_INSTANCE_CIRCLE>	m_Instances_Circle;

	weak_ptr<class CInven>		m_pInven;
	weak_ptr<class CPlayer>		m_pPlayer;

private:
	HRESULT					Ready_Components();
	HRESULT					Ready_InstanceBuffer();
	void					Build_Instances();

	float4_t				Get_SlotRect(const HUD_POS& t);
	const shared_ptr<ITEM>&	Get_SlotItem(const HUD_POS& t);

	void					Push_Rect(f32_t fLeft, f32_t fTop, f32_t fWidth, f32_t fHeight, float4_t vColor, f32_t fRadius = 0.f, f32_t fBorder = 0.f);// fBorder : 외곽선 두께
	void					Push_Bar(f32_t fLeft, f32_t fTop, f32_t fWidth, f32_t fHeight, f32_t fRatio, float4_t vBgColor, float4_t vFillColor, f32_t fRadius);
	void					Push_Icon(f32_t fLeft, f32_t fTop, f32_t fWidth, f32_t fHeight, int32_t iIcon, f32_t fAlpha = 1.f);
	void					Push_HUDIcon(f32_t fLeft, f32_t fTop, f32_t fWidth, f32_t fHeight, int32_t iIcon, float4_t vColor);
	void					Push_ItemIcon(const float4_t& vRect, const shared_ptr<ITEM>& pItem, f32_t fAlpha);
	void					Push_Slot(const HUD_POS& t);

	void					Push_Circle(f32_t fCenterX, f32_t fCenterY, f32_t R, f32_t r, float4_t vColor, f32_t fDegree = 0.f);
	void					Push_Circle_Icon(f32_t fCenterX, f32_t fCenterY, int32_t iIcon, f32_t fAlpha = 1.f);
public:
	static shared_ptr<CHUD>	Create(ComPtr<ID3D11Device>pDevice, ComPtr<ID3D11DeviceContext>pContext);
	shared_ptr<CPrototype>	Clone(void* pArg) override;
};

NS_END