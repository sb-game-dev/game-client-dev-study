#include "Inven.h"
#include <io.h>
#include <iostream>


CInven::CInven(ComPtr<ID3D11Device>pDevice, ComPtr<ID3D11DeviceContext>pContext)
	: CGameObject{pDevice,pContext}
{
	ZeroMemory(m_pEquipSlots, sizeof(m_pEquipSlots));
	m_vecBackPack.reserve(10);
	m_vecStorage.reserve(100);
}

CInven::~CInven()
{
}

HRESULT CInven::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;
	return S_OK;
}

HRESULT CInven::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;
	return S_OK;
}

void CInven::Priority_Update(f32_t fTimeDelta)
{
	__super::Priority_Update(fTimeDelta);
}

void CInven::Update(f32_t fTimeDelta)
{
	__super::Update(fTimeDelta);
}

void CInven::Late_Update(f32_t fTimeDelta)
{
	__super::Late_Update(fTimeDelta);
}

HRESULT CInven::Render()
{
	return S_OK;
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

shared_ptr<CInven> CInven::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
	auto pInstance= shared_ptr<CInven>(new CInven(pDevice, pContext));
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Create Failed : Inven");
		pInstance.reset();
	}
	return pInstance;
}

shared_ptr<CPrototype> CInven::Clone(void* pArg)
{
	auto pInstance = shared_ptr<CInven>(new CInven(*this));
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Clone Failed : Inven");
		pInstance.reset();
	}
	return pInstance;
}


