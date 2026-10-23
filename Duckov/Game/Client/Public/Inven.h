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
	shared_ptr<ITEM>				m_pEquipSlots[static_cast<int>(EQUIP_SLOT::END)];
	vector<shared_ptr<ITEM>>		m_vecBackPack;
	vector<shared_ptr<ITEM>>		m_vecStorage;
public:
	static shared_ptr<CInven>		Create(ComPtr<ID3D11Device>pDevice, ComPtr<ID3D11DeviceContext>pContext);
	shared_ptr<CPrototype>			Clone(void* pArg) override;
};

NS_END