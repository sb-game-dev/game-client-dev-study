#pragma once

#include "Client_Defines.h"
#include "PartObject.h"
NS_BEGIN(UI_HpBar)
// 위치 좌표 : 직교 공간 (화면 중앙 원점, x 오른쪽, y 위쪽, 1 = 1px). LEFT/TOP 은 사각형의 왼쪽 변 x, 위쪽 변 y
// HP 바
constexpr f32_t HP_SLIDER_WIDTH = 54.5f, HP_SLIDER_HEIGHT = 6.f;
const float2_t HP_OFFSET = { -28.f, 60.f };

// 색상
constexpr float4_t COLOR_HUD_SLOT_BG_LIGHT = { 0.f, 0.f, 0.f, 0.3f };	// 1, 2, V (무기 칸)
constexpr float4_t COLOR_HUD_SLOT_BG_DARK = { 0.f, 0.f, 0.f, 0.58f };	// 3 ~ 8 (퀵슬롯)
constexpr float4_t COLOR_HP_BG = { 0.f, 0.f, 0.f, 0.745f };
constexpr float4_t COLOR_HP_FILL_SIDE = { 0.f, 0.f, 0.f, 0.7f };
constexpr float4_t COLOR_HP_FILL = { 1.f,0.353f, 0.286f, 1.f };
constexpr float4_t COLOR_STAMINA_FILL = { 0.678f, 1.0f, 0.427f, 1.0f };
constexpr float4_t COLOR_STAMINA_FILL_YELLOW = { 1.f, 0.976f, 0.016f, 1.f };
NS_END

NS_BEGIN(Client)

class CUI_HpBar : public CPartObject
{
public:
	typedef struct tagUI_HpBarDesc : public CPartObject::PARTOBJECT_DESC
	{
		const float4x4_t* pSocketMatrix = { nullptr };
		const uint32_t* pParentState = { nullptr };
	}UIHPBAR_DESC;

private:
	CUI_HpBar(ComPtr<ID3D11Device>pDevice, ComPtr<ID3D11DeviceContext>pContext);
public:
	~CUI_HpBar() = default;

public:
	virtual		HRESULT		Initialize_Prototype() override;
	virtual		HRESULT		Initialize(void* pArg) override;
	virtual		void		Priority_Update(f32_t fDeltaTime)override;
	virtual		void		Update(f32_t fDeltaTime)override;
	virtual		void		Late_Update(f32_t fDeltaTime)override;
	virtual		HRESULT		Render() override;

public:
	void	Initialize_HitAnimation();

private:
	shared_ptr<CVertexShader>		m_pVSCom;
	shared_ptr<CPixelShader>		m_pPSCom;
	ComPtr<ID3D11Buffer>			m_pVB = { nullptr };
	ComPtr<ID3D11Buffer>			m_pIB = { nullptr };
	uint32_t						m_iIndexCnt = {};
	ComPtr<ID3D11Buffer>			m_pInstanceVB;
	static constexpr uint32_t		m_iMaxInstance = 1024;
	vector<VTXUI_INSTANCE>			m_Instances;

	weak_ptr<class CInven>			m_pInven;

	f32_t       m_fHitTimeRemaining = { 0.f };	// 남은 시간
	f32_t       m_fHitDuration = { 0.15f };		// 전체 애니메이션 길이

private:
	HRESULT					Ready_Components();
	HRESULT					Ready_InstanceBuffer();
	void					Build_Instances();

	void					Push_Rect(f32_t fLeft, f32_t fTop, f32_t fWidth, f32_t fHeight, float4_t vColor, f32_t fRadius = 0.f, f32_t fBorder = 0.f);// fBorder : 외곽선 두께
	void					Push_Bar(f32_t fLeft, f32_t fTop, f32_t fWidth, f32_t fHeight, f32_t fRatio, float4_t vFillColor, f32_t fRadius);

	float4_t				AddWhiteColor(float4_t OriginalColor, f32_t fRatio);
public:
	static shared_ptr<CUI_HpBar>	Create(ComPtr<ID3D11Device>pDevice, ComPtr<ID3D11DeviceContext>pContext);
	shared_ptr<CPrototype>	Clone(void* pArg) override;
};

NS_END