#include "Inven.h"
#include <io.h>
#include <iostream>

using namespace INVEN_UI;


CInven::CInven(ComPtr<ID3D11Device>pDevice, ComPtr<ID3D11DeviceContext>pContext)
	: CGameObject{pDevice,pContext}
{
	
}


HRESULT CInven::Initialize_Prototype()
{
	if (FAILED(__super::Initialize_Prototype()))
		return E_FAIL;
	VTXNORM vertices[] =
	{
		{ float3_t(-0.5f, -0.5f, 0.f), float3_t(0.f, 0.f, -1.f), float2_t(0.f, 1.f) },
		{ float3_t(-0.5f, +0.5f, 0.f), float3_t(0.f, 0.f, -1.f), float2_t(0.f, 0.f) },
		{ float3_t(+0.5f, +0.5f, 0.f), float3_t(0.f, 0.f, -1.f), float2_t(1.f, 0.f) },
		{ float3_t(+0.5f, -0.5f, 0.f), float3_t(0.f, 0.f, -1.f), float2_t(1.f, 1.f) },
	};

	// 정점 버퍼 생성
	D3D11_BUFFER_DESC   VBDesc{};
	VBDesc.ByteWidth = sizeof(vertices);
	VBDesc.Usage = D3D11_USAGE_IMMUTABLE;
	VBDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA  VBData{};
	VBData.pSysMem = vertices;
	if (FAILED(m_pDevice->CreateBuffer(&VBDesc, &VBData, &m_pVB)))
		return E_FAIL;
	// 인덱스 정보
	UINT indices[] = {
		0, 1, 2,
		0, 2, 3,
	};

	// 인덱스 버퍼 생성
	D3D11_BUFFER_DESC IBDesc{};
	IBDesc.ByteWidth = sizeof(indices);
	IBDesc.Usage = D3D11_USAGE_IMMUTABLE;
	IBDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	D3D11_SUBRESOURCE_DATA IBData{};
	IBData.pSysMem = indices;
	m_iIndexCnt = size(indices);
	if (FAILED(m_pDevice->CreateBuffer(&IBDesc, &IBData, &m_pIB)))
		return E_FAIL;

	// 상수 버퍼 생성
	D3D11_BUFFER_DESC CBDesc{};
	CBDesc.ByteWidth = sizeof(CB_PER_OBJECT_LIT);
	CBDesc.Usage = D3D11_USAGE_DEFAULT;
	CBDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	// 상수 버퍼를 초기화 할 때 SubResource는 nullptr로 설정. 나중에 UpdateSubresource 할 예정
	if (FAILED(m_pDevice->CreateBuffer(&CBDesc, nullptr, &m_pCB)))
		return E_FAIL;

	// 래스터라이저 설정
	D3D11_RASTERIZER_DESC rsDesc{};
	rsDesc.FillMode = D3D11_FILL_SOLID;         // D3D11_FILL_WIREFRAME , D3D11_FILL_SOLID
	rsDesc.CullMode = D3D11_CULL_BACK;          // D3D11_CULL_BACK , D3D11_CULL_FRONT
	rsDesc.FrontCounterClockwise = false;       // 시계방향이 전면
	rsDesc.DepthClipEnable = true;

	m_pDevice->CreateRasterizerState(&rsDesc, m_pRS.GetAddressOf());

	// 샘플러 생성
	D3D11_SAMPLER_DESC samplerDesc{};

	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = samplerDesc.AddressV = samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	if (FAILED(m_pDevice->CreateSamplerState(&samplerDesc, m_pSampler.GetAddressOf())))
		return E_FAIL;


	return S_OK;
}

HRESULT CInven::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	m_vecBackPack.resize(25);
	m_vecStorage.resize(100);
	if (FAILED(Ready_Components()))
		return E_FAIL;
	
	// 테스트용
	// 가방
	m_vecBackPack[0] = Init_TestItem(make_shared<ITEM>(), ITEM_TYPE::BULLET, L"S-일반 탄환", 595, 9, 2, 20, 320);
	m_vecBackPack[1] = Init_TestItem(make_shared<ITEM>(), ITEM_TYPE::MEDICAL, L"소형 구급상자", 17, 27, 2);
	m_vecBackPack[2] = Init_TestItem(make_shared<ITEM>(), ITEM_TYPE::FOOD, L"생수", 428, 33, 2);
	m_vecBackPack[3] = Init_TestItem(make_shared<ITEM>(), ITEM_TYPE::BULLET, L"S-일반 탄환", 595, 9, 2, 300, 320);
	m_vecBackPack[4] = Init_TestItem(make_shared<ITEM>(), ITEM_TYPE::MEDICAL, L"지혈 붕대", 10, 26, 1, 2, 3);

	auto pHelmet = make_shared<ARMOR>();
	pHelmet->eSlot = ARMOR_SLOT::HEAD;
	m_vecBackPack[5] = Init_TestItem(pHelmet, ITEM_TYPE::ARMOR, L"구식 철모", 42, 13, 2);

	auto pVest = make_shared<ARMOR>();
	pVest->eSlot = ARMOR_SLOT::BODY;
	m_vecBackPack[6] = Init_TestItem(pVest, ITEM_TYPE::ARMOR, L"Lv.2 방탄복", 33, 16, 2);

	m_vecBackPack[7] = Init_TestItem(make_shared<GUN>(), ITEM_TYPE::GUN, L"PM", 784, 2, 1);
	m_vecBackPack[8] = Init_TestItem(make_shared<ITEM>(), ITEM_TYPE::TOTEM, L"토템: 갑옷 Ⅰ", 319, 21, 1);

	// 장비 칸
	m_pEquipSlots[ETOI(EQUIP_SLOT::GUN_1)] = Init_TestItem(make_shared<GUN>(), ITEM_TYPE::GUN, L"AK-74U", 252, 3, 2);
	m_pEquipSlots[ETOI(EQUIP_SLOT::BACKPACK)] = Init_TestItem(make_shared<BACKPACK>(), ITEM_TYPE::BACKPACK, L"여행 가방", 38, 20, 3);

	return S_OK;
}

void CInven::Priority_Update(f32_t fTimeDelta)
{
	__super::Priority_Update(fTimeDelta);
}

void CInven::Update(f32_t fTimeDelta)
{
	__super::Update(fTimeDelta);  
	if (CGameInstance::Get().Key_Down(DIK_TAB))
	{
		m_bOpen = !m_bOpen;
		m_eDragState = DRAG_STATE::IDLE;
	}
	if (false == m_bOpen)
	{
		m_tHoveredSlot = {};
		return;
	}

	m_ptMouse = CGameInstance::Get().Get_MousePos();
	m_tHoveredSlot = Find_CollidedSlot(m_ptMouse);
	Update_DragState();
}

void CInven::Late_Update(f32_t fTimeDelta)
{
	__super::Late_Update(fTimeDelta); 
	if (m_bOpen)
		CGameInstance::Get().Add_RenderGroup(RENDERID::ALPHA_UI, dynamic_pointer_cast<CGameObject>(shared_from_this()));
}

HRESULT CInven::Render()
{
	m_Instances.clear();
	Build_Instances();
	if (m_Instances.empty())
		return S_OK;
	uint32_t iCount = min((uint32_t)m_Instances.size(), m_iMaxInstance);

	D3D11_MAPPED_SUBRESOURCE tMapped{};
	if (FAILED(m_pContext->Map(m_pInstanceVB.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &tMapped)))
		return E_FAIL;
	memcpy(tMapped.pData, m_Instances.data(), sizeof(VTXUI_INSTANCE) * iCount);
	m_pContext->Unmap(m_pInstanceVB.Get(), 0);

	ID3D11Buffer* pVBs[] = { m_pVB.Get(), m_pInstanceVB.Get() };
	uint32_t iStrides[] = { sizeof(VTXNORM), sizeof(VTXUI_INSTANCE) };
	uint32_t iOffsets[] = { 0, 0 };
	m_pContext->IASetVertexBuffers(0, 2, pVBs, iStrides, iOffsets);
	m_pContext->IASetIndexBuffer(m_pIB.Get(), DXGI_FORMAT_R32_UINT, 0);
	m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	m_pContext->IASetInputLayout(m_pVSCom->Get_InputLayout().Get());
	m_pContext->VSSetShader(m_pVSCom->Get_Shader().Get(), nullptr, 0);
	m_pContext->PSSetShader(m_pPSCom->Get_Shader().Get(), nullptr, 0);

	if (m_pIconTexCom) 
		m_pIconTexCom->Set_TexturePS(0, 0);

	m_pContext->PSSetSamplers(0, 1, m_pSampler.GetAddressOf());
	m_pContext->RSSetState(m_pRS.Get());

	m_pContext->DrawIndexedInstanced(m_iIndexCnt, iCount, 0, 0, 0);
	return S_OK;
}

float4_t CInven::Get_SlotRect(const SLOT_POS& t)
{
	if (t.eArea == INVEN_AREA::BAG)
		return { BAG_LEFT + (t.iIndex % BAG_COLS) * BAG_STEP,
				 BAG_TOP + (t.iIndex / BAG_COLS) * BAG_STEP,
				 BAG_SIZE,
				 BAG_SIZE };

	if (t.eArea == INVEN_AREA::EQUIP)
		return { EQUIP_LEFT + (t.iIndex % EQUIP_COLS) * EQUIP_STEP_X,
				 EQUIP_TOP + (t.iIndex / EQUIP_COLS) * EQUIP_STEP_Y,
				 EQUIP_WIDTH,
				 EQUIP_HEIGHT };

	return float4_t();
}

shared_ptr<ITEM>& CInven::Get_SlotItem(const SLOT_POS& t)
{
	if (t.eArea == INVEN_AREA::EQUIP)
		return m_pEquipSlots[t.iIndex];
	return m_vecBackPack[t.iIndex];
}

void CInven::Build_Instances()
{ 
	// 패널 그리기
	Push_Rect(PANEL_LEFT, PANEL_TOP, PANEL_WIDTH, PANEL_HEIGHT, { 0.08f, 0.14f, 0.22f, 0.6f }, RADIUS);
	
	// 장비칸 그리기
	for (int32_t i = 0; i < ETOI(EQUIP_SLOT::END); ++i)        
		Push_Slot({ INVEN_AREA::EQUIP, i });
	
	// 가방칸 그리기
	for (int32_t i = 0; i < (int32_t)m_vecBackPack.size(); ++i) 
		Push_Slot({ INVEN_AREA::BAG, i });

	// 선택된 칸 주황 테두리 강조
	if (Is_Slot(m_tSelectedSlot))
	{
		float4_t r = Get_SlotRect(m_tSelectedSlot);
		Push_Rect(r.x, r.y, r.z, r.w, { 1.f, 0.62f, 0.23f, 1.f }, RADIUS, 1.5f);
	}

	// 마우스 호버 칸 강조
	if (Is_Slot(m_tHoveredSlot))
	{
		float4_t r = Get_SlotRect(m_tHoveredSlot);
		Push_Rect(r.x, r.y, r.z, r.w, { 1.f, 1.f, 1.f, 0.08f }, RADIUS);
	}

	if (m_eDragState == DRAG_STATE::DRAGGING)
	{
		// 마우스가 잡고 있는 아이템 아이콘
		float4_t rFromSlot = Get_SlotRect(m_tDraggedItemSlot);		
		float4_t rDraggedIcon = { m_ptMouse.x - rFromSlot.z * 0.5f,     
								  m_ptMouse.y - rFromSlot.w * 0.5f,
								  rFromSlot.z, rFromSlot.w };			
		Push_ItemIcon(rDraggedIcon, Get_SlotItem(m_tDraggedItemSlot), 0.9f);

		// 이 아이템이 들어갈 수 있는 장비 칸을 초록 테두리로 표현
		const shared_ptr<ITEM>& pDraggedItem = Get_SlotItem(m_tDraggedItemSlot);
		for (int32_t i = 0; i < ETOI(EQUIP_SLOT::END); ++i)
		{
			SLOT_POS tDstEquipSlot = { INVEN_AREA::EQUIP, i };
			if (tDstEquipSlot == m_tDraggedItemSlot || false == CanPlace(pDraggedItem, tDstEquipSlot))
				continue;

			float4_t r = Get_SlotRect(tDstEquipSlot);
			Push_Rect(r.x, r.y, r.z, r.w, { 0.47f, 1.f, 0.62f, 0.35f }, RADIUS);          
			Push_Rect(r.x, r.y, r.z, r.w, { 1.f, 1.f, 1.f, 0.9f }, RADIUS, 1.5f);         
		}
	}
}

HRESULT CInven::Ready_Components()
{
	if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), TEXT("Prototype_Component_VS_UI"),
		TEXT("Com_VS"), m_pVSCom)))
		return E_FAIL;

	if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), TEXT("Prototype_Component_PS_UI"),
		TEXT("Com_PS"), m_pPSCom)))
		return E_FAIL; 

	if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), TEXT("Prototype_Component_Texture_ItemIcons"),
			TEXT("Com_IconTex"), m_pIconTexCom)))
		return E_FAIL;

	D3D11_BUFFER_DESC desc{};
	desc.ByteWidth = sizeof(VTXUI_INSTANCE) * m_iMaxInstance;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	if (FAILED(m_pDevice->CreateBuffer(&desc, nullptr, &m_pInstanceVB)))
		return E_FAIL;
	m_Instances.reserve(m_iMaxInstance);
	return S_OK;
}

void CInven::Push_Rect(f32_t fLeft, f32_t fTop, f32_t fWidth, f32_t fHeight, float4_t vColor, f32_t fRadius, f32_t fBorder)
{
	// 좌상단과 우하단을 각각 정수 픽셀로 반올림 (1px 테두리가 픽셀 사이에 끼지 않게)
	f32_t fSnapLeft = floorf(fLeft + 0.5f);
	f32_t fSnapTop = floorf(fTop + 0.5f);
	f32_t fSnapRight = floorf(fLeft + fWidth + 0.5f);
	f32_t fSnapBottom = floorf(fTop + fHeight + 0.5f);

	m_Instances.push_back({ { fSnapLeft, fSnapTop, fSnapRight - fSnapLeft, fSnapBottom - fSnapTop },
							vColor, { fRadius, fBorder, 0.f, 0.f }, { 0.f, 0.f, 1.f, 1.f } });
}
void CInven::Push_Icon(f32_t fLeft, f32_t fTop, f32_t fWidth, f32_t fHeight, int32_t iIcon, f32_t fAlpha)
{
	f32_t fSnapLeft = floorf(fLeft + 0.5f);
	f32_t fSnapTop = floorf(fTop + 0.5f);
	f32_t fSnapRight = floorf(fLeft + fWidth + 0.5f);
	f32_t fSnapBottom = floorf(fTop + fHeight + 0.5f);

	m_Instances.push_back({ { fSnapLeft, fSnapTop, fSnapRight - fSnapLeft, fSnapBottom - fSnapTop },
							{ 1.f, 1.f, 1.f, fAlpha }, { 0.f, 0.f, 1.f, (f32_t)iIcon }, { 0.f, 0.f, 1.f, 1.f } });
}
void CInven::Push_Slot(const SLOT_POS& t)
{
	// 매개변수 t를 통째로 그리는 함수

	// 칸 그리기
	float4_t r = Get_SlotRect(t);
	Push_Rect(r.x, r.y, r.z, r.w, { 0.f, 0.f, 0.f, 0.2f }, RADIUS);			// 어두운 배경
	Push_Rect(r.x, r.y, r.z, r.w, { 1.f, 1.f, 1.f, 0.3f }, RADIUS, 1.f);	// 밝은 흰색 테두리

	// 아이템 그리기
	// 드래그를 한 상태이고 현재 위치가 드래그를 시작한 위치라면 알파값을 0.3으로 설정하여 살짝 투명하게 그림
	// 드래그를 한 상태가 아니라면 현재 위치에 있는 아이템을 알파값 1로 설정하여 그린다.
	bool_t bDragSource = (m_eDragState == DRAG_STATE::DRAGGING && t == m_tDraggedItemSlot);
	Push_ItemIcon(r, Get_SlotItem(t), bDragSource ? 0.3f : 1.f);
}

CInven::SLOT_POS CInven::Find_CollidedSlot(POINT pt)
{
	for (int32_t i = 0; i < ETOI(EQUIP_SLOT::END); ++i)
	{
		if (Is_InRect(pt, Get_SlotRect({ INVEN_AREA::EQUIP, i })))
			return { INVEN_AREA::EQUIP, i };
	}
	for (int32_t i = 0; i < (int32_t)m_vecBackPack.size(); ++i)
	{
		if (Is_InRect(pt, Get_SlotRect({ INVEN_AREA::BAG, i })))
			return { INVEN_AREA::BAG, i };
	}
	if (Is_InRect(pt, { PANEL_LEFT, PANEL_TOP, PANEL_WIDTH, PANEL_HEIGHT }))
	{
		return { INVEN_AREA::END, -1 };
	}
	return { INVEN_AREA::OUTSIDE, -1 };
}

bool_t CInven::Is_InRect(POINT pt, const float4_t& vRect)
{
	return pt.x >= vRect.x && pt.x < vRect.x + vRect.z
		&& pt.y >= vRect.y && pt.y < vRect.y + vRect.w;
}

bool_t CInven::Is_Slot(const SLOT_POS& t)
{
	return t.eArea == INVEN_AREA::EQUIP || t.eArea == INVEN_AREA::BAG;
}

void CInven::Update_DragState()
{
	bool_t bPressed = CGameInstance::Get().Mouse_Down(DIM::LB);    // 눌린 순간
	bool_t bReleased = CGameInstance::Get().Mouse_Up(DIM::LB);     // 뗀 순간

	switch (m_eDragState)
	{
	case DRAG_STATE::IDLE:
		if (false == bPressed)
			break;
		// 장비 or 가방칸을 눌렀는지 확인 + 아이템이 있는 칸인지 확인
		if (Is_Slot(m_tHoveredSlot) && nullptr != Get_SlotItem(m_tHoveredSlot))
		{
			// 아이템 있는 칸을 누름 -> 아직 클릭인지 드래그인지 모름
			m_eDragState = DRAG_STATE::PRESSED;
			m_tDraggedItemSlot = m_tHoveredSlot;
			m_ptPress = m_ptMouse;
		}
		else
		{
			m_tSelectedSlot = {};
		}
		break;

	case DRAG_STATE::PRESSED:
		if (bReleased)
		{
			// 안 움직이고 뗌 = 클릭 -> 선택
			m_tSelectedSlot = m_tDraggedItemSlot;
			m_eDragState = DRAG_STATE::IDLE;
		}
		else if (labs(m_ptMouse.x - m_ptPress.x) + labs(m_ptMouse.y - m_ptPress.y) > 4)
		{
			// 누른 채로 4px 넘게 움직임 = 드래그 시작
			m_eDragState = DRAG_STATE::DRAGGING;
		}
		break;

	case DRAG_STATE::DRAGGING:
		if (bReleased)
		{
			Drop(m_tDraggedItemSlot, m_tHoveredSlot);            // 마우스 아래 칸에 놓기
			m_eDragState = DRAG_STATE::IDLE;
		}
		break;
	}
}

void CInven::Drop(const SLOT_POS& tSrcSlot, const SLOT_POS& tDstSlot)
{
	// 0. 마우스로 잡은 슬롯에 아이템이 없다면(nullptr) return
	shared_ptr<ITEM>& rSrcItem = Get_SlotItem(tSrcSlot);
	if (nullptr == rSrcItem)
		return;

	// 1. 패널 밖 -> 버리기
	if (tDstSlot.eArea == INVEN_AREA::OUTSIDE)
	{
		// 나중에 월드에 아이템 오브젝트를 떨어뜨리기
		rSrcItem = nullptr;
		if (m_tSelectedSlot == tSrcSlot)
			m_tSelectedSlot = {};
		return;
	}

	// 2. 칸이 아닌 곳(칸 사이 틈) 또는 같은 칸 -> 원위치
	if (false == Is_Slot(tDstSlot) || tDstSlot == tSrcSlot)
		return;

	shared_ptr<ITEM>& rDstItem = Get_SlotItem(tDstSlot);

	// 3. 집은 아이템이 놓은 칸에 못 들어감 -> 원위치
	if (false == CanPlace(rSrcItem, tDstSlot))
		return;

	// 4. 같은 아이템 + 겹치기 가능 -> 합치기
	if (nullptr != rDstItem && rDstItem->bStackable && rDstItem->iTypeID == rSrcItem->iTypeID)
	{
		int32_t iSpace = rDstItem->iMaxStack - rDstItem->iCount;        // 놓은 칸에 남은 자리
		int32_t iItemCnt = min(rSrcItem->iCount, iSpace);				// 실제로 옮길 개수

		if (iItemCnt > 0)
		{
			rDstItem->iCount += iItemCnt;
			rSrcItem->iCount -= iItemCnt;
			if (rSrcItem->iCount <= 0)                             // 다 옮겼으면 집은 칸 비우기
				rSrcItem = nullptr;
			return;
		}
		// 놓은 칸이 이미 꽉 차 있으면(iItemCnt == 0) 아래로 내려가서 교환
	}

	// 5. 이동 또는 교환
	//    놓은 칸에 아이템이 있으면, 그게 집은 칸으로 갈 수 있어야 함
	if (false == CanPlace(rDstItem, tSrcSlot))
		return;
	swap(rSrcItem, rDstItem);

	// 선택 테두리가 아이템을 따라가게
	if (m_tSelectedSlot == tSrcSlot)
		m_tSelectedSlot = tDstSlot;
	else if (m_tSelectedSlot == tDstSlot)
		m_tSelectedSlot = tSrcSlot;
}

void CInven::Push_ItemIcon(const float4_t& vRect, const shared_ptr<ITEM>& pItem, f32_t fAlpha)
{
	if (nullptr == pItem)
		return;

	f32_t fIconSize = min(vRect.z, vRect.w) - 6.f;
	f32_t fIconLeft = vRect.x + (vRect.z - fIconSize) * 0.5f;
	f32_t fIconTop = vRect.y + (vRect.w - fIconSize) * 0.5f;
	Push_Icon(fIconLeft, fIconTop, fIconSize, fIconSize, pItem->iIconIndex, fAlpha);
}

bool_t CInven::CanPlace(const shared_ptr<ITEM>& pItem, const SLOT_POS& tDstSlot)
{
	// CanPlace -> pItem을 tDstSlot에 넣을 수 있는지를 확인하는 함수

	// 놓을 칸이 비어있다면 비어있는 칸의 pItem은 nullptr이 들어온다 -> CanPlace(nullptr, tSrcSlot)이 불린다.
	// Drop에서 빈 칸에 놓을 때, 놓은 칸의 "빈 것"이 집은 칸으로 가는지 검사하므로 필요
	// (예: 장착한 총을 빈 가방 칸으로 → 총 칸이 비게 됨 = 허용)
	if (nullptr == pItem)                       // 빈 슬롯은 어디든 놓을 수 있음
		return true;

	if (tDstSlot.eArea == INVEN_AREA::BAG)     // 가방 칸에는 뭐든 들어감
		return true;

	// 장비 칸의 규칙(장비칸에서의 iIndex -> 장비칸 슬롯 정보)
	switch (static_cast<EQUIP_SLOT>(tDstSlot.iIndex))  
	{
	case EQUIP_SLOT::GUN_1:
	case EQUIP_SLOT::GUN_2:
		return pItem->eItemType == ITEM_TYPE::GUN;

	case EQUIP_SLOT::MELEE:
		return pItem->eItemType == ITEM_TYPE::MELEE;

	case EQUIP_SLOT::HEAD:
		return pItem->eItemType == ITEM_TYPE::ARMOR
			&& static_pointer_cast<ARMOR>(pItem)->eSlot == ARMOR_SLOT::HEAD;

	case EQUIP_SLOT::BODY:
		return pItem->eItemType == ITEM_TYPE::ARMOR
			&& static_pointer_cast<ARMOR>(pItem)->eSlot == ARMOR_SLOT::BODY;

	case EQUIP_SLOT::BACKPACK:
		return pItem->eItemType == ITEM_TYPE::BACKPACK;

	case EQUIP_SLOT::TOTEM_1:
	case EQUIP_SLOT::TOTEM_2:
		return pItem->eItemType == ITEM_TYPE::TOTEM;

	default: // FACE, HEADSET: 아직 맞는 아이템 타입이 없음
		return false;
	}
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


