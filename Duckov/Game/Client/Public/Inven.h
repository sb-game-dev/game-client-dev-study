#pragma once

#include "Client_Defines.h"
#include "GameObject.h"
NS_BEGIN(Client)

class CInven : public CGameObject
{
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
	void Push_Rect(f32_t fLeft, f32_t fTop, f32_t fWidth, f32_t fHeight, float4_t vColor, f32_t fRadius = 0.f, f32_t fBorder = 0.f);// fBorder : ¿Ü°û¼± µÎ²²
	void Push_Icon(f32_t fLeft, f32_t fTop, f32_t fWidth, f32_t fHeight, int32_t iIcon, f32_t fAlpha = 1.f);
	void Build_Instances();

public:
	static shared_ptr<CInven>		Create(ComPtr<ID3D11Device>pDevice, ComPtr<ID3D11DeviceContext>pContext);
	shared_ptr<CPrototype>			Clone(void* pArg) override;
};

NS_END