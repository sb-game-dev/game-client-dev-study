#include "Inven.h"
#include <io.h>
#include <iostream>


CInven::CInven()
{
	ZeroMemory(m_pEquipSlots, sizeof(m_pEquipSlots));
	m_vecBackPack.reserve(10);
	m_vecStorage.reserve(100);
}

CInven::~CInven()
{
}

void CInven::AddEquipSlot(EQUIP_SLOT eSlotID, shared_ptr<ITEM> pItem)
{
	if (m_pEquipSlots[static_cast<int>(eSlotID)] == nullptr)
	{
		m_pEquipSlots[static_cast<int>(eSlotID)] = pItem;
		return;
	}
}

void CInven::RenderEquipSlot()
{
	wcout.imbue(locale("kor"));
	for (int i = 0; i < size(m_pEquipSlots); ++i)
	{
		wcout << i << L"번째 슬롯: ";
		if (m_pEquipSlots[i] == nullptr)
			wcout << L"비어있음" << endl;
		else
			wcout << m_pEquipSlots[i]->strItemName << endl;
	}
	wcout << L"==============================" << endl;
}

void CInven::RenderStorage()
{
}

void CInven::RenderBag()
{
}


