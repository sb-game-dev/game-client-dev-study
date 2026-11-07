#include "HUD.h"
#include "Inven.h"
using namespace HUD_UI;


CHUD::CHUD(ComPtr<ID3D11Device>pDevice, ComPtr<ID3D11DeviceContext>pContext)
	: CGameObject{ pDevice,pContext }
{

}


HRESULT CHUD::Initialize_Prototype()
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


	return S_OK;
}

HRESULT CHUD::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	if (FAILED(Ready_Components()))
		return E_FAIL;
	if (FAILED(Ready_InstanceBuffer()))
		return E_FAIL;
	return S_OK;
}

void CHUD::Priority_Update(f32_t fTimeDelta)
{
	__super::Priority_Update(fTimeDelta);
}

void CHUD::Update(f32_t fTimeDelta)
{
	__super::Update(fTimeDelta);
	if (nullptr != m_pInven)
		return;
	m_pInven = dynamic_pointer_cast<CInven>(CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::GAMEPLAY), L"Layer_GameObject", GO::Inven));
	if (nullptr == m_pInven)
		return;
}

void CHUD::Late_Update(f32_t fTimeDelta)
{
	__super::Late_Update(fTimeDelta);
	if (nullptr == m_pInven)
		return;
	if (!m_pInven->Is_Open())
		CGameInstance::Get().Add_RenderGroup(RENDERID::ALPHA_UI, dynamic_pointer_cast<CGameObject>(shared_from_this()));
}

HRESULT CHUD::Render()
{
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

	if (FAILED(m_pVSCom->Begin()))
		return E_FAIL;

	if (FAILED(m_pPSCom->Begin()))
		return E_FAIL;

	if (FAILED(m_pIconTexCom->Set_TexturePS(0, 0)))
		return E_FAIL;

	m_pContext->RSSetState(m_pRS.Get());

	m_pContext->DrawIndexedInstanced(m_iIndexCnt, iCount, 0, 0, 0);
	return S_OK;
}



void CHUD::Build_Instances()
{
	// 인스턴스 초기화
	m_Instances.clear();

	// 퀵 슬롯 총 2개 칸그리기
	for (int32_t i = 0; i < 2; ++i)
		Push_Slot(HUD_AREA::GUN);

	// 퀵 슬롯 근접무기칸 그리기
	Push_Slot(HUD_AREA::MELEE);

	// 퀵 슬롯 3 ~ 8 숫자칸 그리기
	for (int32_t i = 3; i < 9; ++i)
		Push_Slot({ INVEN_AREA::EQUIP, i });
}

float4_t CHUD::Get_SlotRect(const HUD_POS& t)
{

	if (t.eArea == HUD_AREA::GUN)
		return { WEAPON_LEFT + (t.iIndex % 2) * WEAPON_STEP,
				 WEAPON_TOP+ (t.iIndex / 2) * WEAPON_STEP,
				 WEAPON_SIZE,
				 WEAPON_SIZE };

	if (t.eArea == HUD_AREA::SLOT)
		return { QUICK_LEFT + (t.iIndex % 6) * QUICK_STEP,
				 QUICK_TOP + (t.iIndex / 6) * QUICK_STEP,
				 QUICK_SIZE,
				 QUICK_SIZE };

	return float4_t();
}

shared_ptr<ITEM>& CHUD::Get_SlotItem(const HUD_POS& t)
{
	if (t.eArea == HUD_AREA::GUN)
	{
		if (t.iIndex == 0)
		{
			auto pItem = m_pInven->GetEquipSlot(EQUIP_SLOT::GUN_1);
			return pItem;
		}
		else if (t.iIndex == 1)
		{
			auto pItem = m_pInven->GetEquipSlot(EQUIP_SLOT::GUN_2);
			return pItem;
		}
	}
	else if (t.eArea == HUD_AREA::MELEE)
	{
		auto pItem = m_pInven->GetEquipSlot(EQUIP_SLOT::MELEE);
		return pItem;
	}
	else if (t.eArea == HUD_AREA::SLOT)
	{
		auto pItem = m_pInven->GetQuickSlot(QUICK_SLOT(t.iIndex + 3));
		return pItem;
	}
}

HRESULT CHUD::Ready_Components()
{
	if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), Proto::VS_UI,
		TEXT("Com_VS"), m_pVSCom)))
		return E_FAIL;

	if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), Proto::PS_UI,
		TEXT("Com_PS"), m_pPSCom)))
		return E_FAIL;

	if (FAILED(__super::Add_Component(ETOUI(LEVEL::GAMEPLAY), Proto::Texture_ItemIcons,
		TEXT("Com_IconTex"), m_pIconTexCom)))
		return E_FAIL;
	return S_OK;
}

HRESULT CHUD::Ready_InstanceBuffer()
{
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

void CHUD::Push_Rect(f32_t fLeft, f32_t fTop, f32_t fWidth, f32_t fHeight, float4_t vColor, f32_t fRadius, f32_t fBorder)
{
	// 좌상단과 우하단을 각각 정수 픽셀로 반올림 (1px 테두리가 픽셀 사이에 끼지 않게)
	f32_t fSnapLeft = floorf(fLeft + 0.5f);
	f32_t fSnapTop = floorf(fTop + 0.5f);
	f32_t fSnapRight = floorf(fLeft + fWidth + 0.5f);
	f32_t fSnapBottom = floorf(fTop + fHeight + 0.5f);

	m_Instances.push_back({ { fSnapLeft, fSnapTop, fSnapRight - fSnapLeft, fSnapBottom - fSnapTop },
							vColor, { fRadius, fBorder, 0.f, 0.f }, { 0.f, 0.f, 1.f, 1.f } });
}
void CHUD::Push_Icon(f32_t fLeft, f32_t fTop, f32_t fWidth, f32_t fHeight, int32_t iIconIndex, f32_t fAlpha)
{
	f32_t fSnapLeft = floorf(fLeft + 0.5f);
	f32_t fSnapTop = floorf(fTop + 0.5f);
	f32_t fSnapRight = floorf(fLeft + fWidth + 0.5f);
	f32_t fSnapBottom = floorf(fTop + fHeight + 0.5f);

	m_Instances.push_back({ { fSnapLeft, fSnapTop, fSnapRight - fSnapLeft, fSnapBottom - fSnapTop },
							{ 1.f, 1.f, 1.f, fAlpha }, { 0.f, 0.f, 1.f, (f32_t)iIconIndex }, { 0.f, 0.f, 1.f, 1.f } });
}

void CHUD::Push_Slot(const HUD_POS& t)
{
	// 매개변수 t를 통째로 그리는 함수

	// 칸 그리기
	float4_t r = Get_SlotRect(t);
	Push_Rect(r.x, r.y, r.z, r.w, COLOR_HUD_SLOT_BG_DARK, WEAPON_RADIUS);			// 어두운 배경
	Push_Rect(r.x, r.y, r.z, r.w, COLOR_HUD_SLOT_BG_LIGHT, WEAPON_RADIUS, BORDER_FRAME);	// 밝은 흰색 테두리

	// 아이템 그리기
	// 드래그를 한 상태이고 현재 위치가 드래그를 시작한 위치라면 알파값을 0.3으로 설정하여 살짝 투명하게 그림
	// 드래그를 한 상태가 아니라면 현재 위치에 있는 아이템을 알파값 1로 설정하여 그린다.
	Push_ItemIcon(r, Get_SlotItem(t), 1.f);
}

void CHUD::Push_ItemIcon(const float4_t& vRect, const shared_ptr<ITEM>& pItem, f32_t fAlpha)
{
	if (nullptr == pItem)
		return;

	f32_t fIconSize = min(vRect.z, vRect.w) - 6.f;
	f32_t fIconLeft = vRect.x + (vRect.z - fIconSize) * 0.5f;
	f32_t fIconTop = vRect.y + (vRect.w - fIconSize) * 0.5f;
	Push_Icon(fIconLeft, fIconTop, fIconSize, fIconSize, pItem->iIconIndex, fAlpha);
}

shared_ptr<CHUD> CHUD::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
	auto pInstance = shared_ptr<CHUD>(new CHUD(pDevice, pContext));
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Create Failed : HUD");
		pInstance.reset();
	}
	return pInstance;
}

shared_ptr<CPrototype> CHUD::Clone(void* pArg)
{
	auto pInstance = shared_ptr<CHUD>(new CHUD(*this));
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Clone Failed : HUD");
		pInstance.reset();
	}
	return pInstance;
}


