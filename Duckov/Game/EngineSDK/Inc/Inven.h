#pragma once

#include "Engine_Defines.h"
NS_BEGIN(Engine)

class ENGINE_DLL CInven
{
	DECLARE_SINGLETON(CInven)
private:
	CInven();
	~CInven();

public:
	void		AddEquipSlot(EQUIP_SLOT eSlotID, shared_ptr<ITEM> pItem);
	
	shared_ptr<ITEM>&		GetSlot(EQUIP_SLOT eSlotID) { return m_pEquipSlots[static_cast<int>(eSlotID)]; }
	//ITEM*&		GetSlot(f32_t x, f32_t y) { return nullptr; }

	void		RenderEquipSlot();
	void		RenderStorage();
	void		RenderBag();

private:
	shared_ptr<ITEM>				m_pEquipSlots[static_cast<int>(EQUIP_SLOT::END)];
	vector<shared_ptr<ITEM>>		m_vecBackPack;
	vector<shared_ptr<ITEM>>		m_vecStorage;

};

NS_END