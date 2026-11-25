#pragma once

#include "Client_Defines.h"
#include "PartObject.h"
NS_BEGIN(UI_StaminaRing)
// 위치 좌표 : 직교 공간 (화면 중앙 원점, x 오른쪽, y 위쪽, 1 = 1px). LEFT/TOP 은 사각형의 왼쪽 변 x, 위쪽 변 y
// HP 바
constexpr f32_t HP_SLIDER_WIDTH = 54.5f, HP_SLIDER_HEIGHT = 6.f;
const float2_t HP_OFFSET = { -28.f, 60.f };

// 스테미너 
constexpr float4_t COLOR_HUD_SLOT_BG_LIGHT = { 0.f, 0.f, 0.f, 0.3f };	// 1, 2, V (무기 칸)
constexpr float4_t COLOR_HUD_SLOT_BG_DARK = { 0.f, 0.f, 0.f, 0.58f };	// 3 ~ 8 (퀵슬롯)
const f32_t HUD_RING_STAMINA_BG_OUTER_SIZE = 11.25;
const f32_t HUD_RING_STAMINA_BG_INNER_SIZE = 3.75;
const f32_t HUD_RING_STAMINA_FILL_OUTER_SIZE = 8.75;
const f32_t HUD_RING_STAMINA_FILL_INNER_SIZE = 6.25;
const float2_t STAMINA_OFFSET = { -30.f,-90.f };

// 색상
constexpr float4_t COLOR_STAMINA_FILL = { 0.678f, 1.0f, 0.427f, 1.0f };
constexpr float4_t COLOR_STAMINA_FILL_YELLOW = { 1.f, 0.976f, 0.016f, 1.f };
NS_END

NS_BEGIN(Client)

class CUI_StaminaRing : public CPartObject
{
public:
	typedef struct tagUI_StaminaRingDesc : public CPartObject::PARTOBJECT_DESC
	{
		const float4x4_t* pSocketMatrix = { nullptr };
		const uint32_t* pParentState = { nullptr };
	}UIPLAYER_DESC;

private:
	CUI_StaminaRing(ComPtr<ID3D11Device>pDevice, ComPtr<ID3D11DeviceContext>pContext);
public:
	~CUI_StaminaRing() = default;

public:
	virtual		HRESULT		Initialize_Prototype() override;
	virtual		HRESULT		Initialize(void* pArg) override;
	virtual		void		Priority_Update(f32_t fTimeDelta)override;
	virtual		void		Update(f32_t fTimeDelta)override;
	virtual		void		Late_Update(f32_t fTimeDelta)override;
	virtual		HRESULT		Render() override;


private:
	shared_ptr<CVertexShader>		m_pVSCircleCom;
	shared_ptr<CPixelShader>		m_pPSCircleCom;
	ComPtr<ID3D11Buffer>			m_pVB = { nullptr };
	ComPtr<ID3D11Buffer>			m_pIB = { nullptr };
	uint32_t						m_iIndexCnt = {};
	ComPtr<ID3D11Buffer>			m_pInstanceVB_Circle;
	static constexpr uint32_t		m_iMaxInstance = 1024;
	vector<VTXUI_INSTANCE_CIRCLE>	m_Instances_Circle;

	weak_ptr<class CInven>		m_pInven;

private:
	HRESULT					Ready_Components();
	HRESULT					Ready_InstanceBuffer();
	void					Build_Instances();

	void					Push_Circle(f32_t fCenterX, f32_t fCenterY, f32_t R, f32_t r, float4_t vColor, f32_t fDegree = 0.f);
public:
	static shared_ptr<CUI_StaminaRing>	Create(ComPtr<ID3D11Device>pDevice, ComPtr<ID3D11DeviceContext>pContext);
	shared_ptr<CPrototype>	Clone(void* pArg) override;
};

NS_END