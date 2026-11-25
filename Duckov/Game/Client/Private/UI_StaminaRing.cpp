#include "UI_StaminaRing.h"
#include "Inven.h"
#include "Player.h"
using namespace UI_StaminaRing;


CUI_StaminaRing::CUI_StaminaRing(ComPtr<ID3D11Device>pDevice, ComPtr<ID3D11DeviceContext>pContext)
	: CPartObject{ pDevice,pContext }
{

}


HRESULT CUI_StaminaRing::Initialize_Prototype()
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

	// 래스터라이저 설정
	D3D11_RASTERIZER_DESC rsDesc{};
	rsDesc.FillMode = D3D11_FILL_SOLID;         // D3D11_FILL_WIREFRAME , D3D11_FILL_SOLID
	rsDesc.CullMode = D3D11_CULL_BACK;          // D3D11_CULL_BACK , D3D11_CULL_FRONT
	rsDesc.FrontCounterClockwise = false;       // 시계방향이 전면
	rsDesc.DepthClipEnable = true;

	m_pDevice->CreateRasterizerState(&rsDesc, m_pRS.GetAddressOf());


	return S_OK;
}

HRESULT CUI_StaminaRing::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	if (FAILED(Ready_Components()))
		return E_FAIL;
	if (FAILED(Ready_InstanceBuffer()))
		return E_FAIL;
	return S_OK;
}

void CUI_StaminaRing::Priority_Update(f32_t fTimeDelta)
{
	__super::Priority_Update(fTimeDelta);
}

void CUI_StaminaRing::Update(f32_t fTimeDelta)
{
	__super::Update(fTimeDelta);

	auto pInven = m_pInven.lock();
	if (nullptr == pInven)
	{
		pInven = dynamic_pointer_cast<CInven>(CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::STATIC), L"Layer_Static", GO::Inven));
		if (nullptr == pInven)
			return;
		m_pInven = pInven;
	}
}

void CUI_StaminaRing::Late_Update(f32_t fTimeDelta)
{
	__super::Late_Update(fTimeDelta);
	auto pInven = m_pInven.lock();
	if (nullptr == pInven)
		return;
	if (!pInven->Is_Open())
		CGameInstance::Get().Add_RenderGroup(RENDERID::ALPHA_UI, dynamic_pointer_cast<CGameObject>(shared_from_this()));
}

HRESULT CUI_StaminaRing::Render()
{
	//---------------- 인스턴스 버퍼 준비 ----------------//
	Build_Instances();

	//---------------- 원형 UI 그리기 ----------------//
	if (m_Instances_Circle.empty())
		return S_OK;
	uint32_t iCount = min((uint32_t)m_Instances_Circle.size(), m_iMaxInstance);

	D3D11_MAPPED_SUBRESOURCE tCircleMapped{};
	if (FAILED(m_pContext->Map(m_pInstanceVB_Circle.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &tCircleMapped)))
		return E_FAIL;
	memcpy(tCircleMapped.pData, m_Instances_Circle.data(), sizeof(VTXUI_INSTANCE_CIRCLE) * iCount);
	m_pContext->Unmap(m_pInstanceVB_Circle.Get(), 0);

	ID3D11Buffer* pCircleVBs[] = { m_pVB.Get(), m_pInstanceVB_Circle.Get() };
	uint32_t iCircleStrides[] = { sizeof(VTXNORM), sizeof(VTXUI_INSTANCE_CIRCLE) };
	uint32_t iCircleOffsets[] = { 0, 0 };
	m_pContext->IASetVertexBuffers(0, 2, pCircleVBs, iCircleStrides, iCircleOffsets);
	m_pContext->IASetIndexBuffer(m_pIB.Get(), DXGI_FORMAT_R32_UINT, 0);
	m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	if (FAILED(m_pVSCircleCom->Begin()))
		return E_FAIL;

	if (FAILED(m_pPSCircleCom->Begin()))
		return E_FAIL;

	m_pContext->DrawIndexedInstanced(m_iIndexCnt, iCount, 0, 0, 0);
	return S_OK;
}



void CUI_StaminaRing::Build_Instances()
{
	// 인스턴스 초기화
	m_Instances_Circle.clear();

	auto pPlayer = dynamic_pointer_cast<CPlayer>(m_pParent.lock());
	if (pPlayer)
	{
		vector_t vHead = m_pParentTransformCom->Get_State(STATE::POSITION)
			+ XMVectorSet(-0.5f, 2.f, 0.f, 0.f);
		auto matPlayerWorld = m_pParentTransformCom->Get_World(); 
		
		matrix_t matVP = CGameInstance::Get().Get_Perspective_Transform(D3DTS::VIEW) * CGameInstance::Get().Get_Perspective_Transform(D3DTS::PROJ);
		vector_t vNDC = XMVector3TransformCoord(vHead, matVP);

		f32_t x = XMVectorGetX(vNDC) * g_iWinSizeX * 0.5f;
		f32_t y = XMVectorGetY(vNDC) * g_iWinSizeY * 0.5f;

		// ---------- 스테미너 ----------
		if (pPlayer->Get_Stamina() >= 100.f)
			return;

		// 스테미너 배경
		Push_Circle(x + STAMINA_OFFSET.x, y + STAMINA_OFFSET.y, 
			HUD_RING_STAMINA_BG_OUTER_SIZE, HUD_RING_STAMINA_BG_INNER_SIZE, 
			COLOR_HUD_SLOT_BG_DARK, 
			360.f);
		// 스테미너 게이지
		Push_Circle(x + STAMINA_OFFSET.x, y + STAMINA_OFFSET.y, 
			HUD_RING_STAMINA_FILL_OUTER_SIZE, HUD_RING_STAMINA_FILL_INNER_SIZE, 
			pPlayer->Get_Stamina() > 30.f ? COLOR_STAMINA_FILL : COLOR_STAMINA_FILL_YELLOW,
			pPlayer->Get_Stamina() / pPlayer->Get_MaxStamina() * 360.f);

	}
}

HRESULT CUI_StaminaRing::Ready_Components()
{
	
	if (FAILED(__super::Add_Component(ETOUI(LEVEL::STATIC), Proto::VS_UI_CIRCLE,
		TEXT("Com_VS_Circle"), m_pVSCircleCom)))
		return E_FAIL;

	if (FAILED(__super::Add_Component(ETOUI(LEVEL::STATIC), Proto::PS_UI_CIRCLE,
		TEXT("Com_PS_Circle"), m_pPSCircleCom)))
		return E_FAIL;

	return S_OK;
}

HRESULT CUI_StaminaRing::Ready_InstanceBuffer()
{
	D3D11_BUFFER_DESC desc{};

	desc.ByteWidth = sizeof(VTXUI_INSTANCE_CIRCLE) * m_iMaxInstance;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	if (FAILED(m_pDevice->CreateBuffer(&desc, nullptr, &m_pInstanceVB_Circle)))
		return E_FAIL;
	m_Instances_Circle.reserve(m_iMaxInstance);
	return S_OK;
}

void CUI_StaminaRing::Push_Circle(f32_t fCenterX, f32_t fCenterY, f32_t R, f32_t r, float4_t vColor, f32_t fDegree)
{
	VTXUI_INSTANCE_CIRCLE VtxUIInstanceCircle{};

	VtxUIInstanceCircle.vCircleInfo = { fCenterX,fCenterY,R,r };
	VtxUIInstanceCircle.vColor = vColor;
	VtxUIInstanceCircle.fDegree = fDegree;

	m_Instances_Circle.push_back(VtxUIInstanceCircle);
}


shared_ptr<CUI_StaminaRing> CUI_StaminaRing::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
	auto pInstance = shared_ptr<CUI_StaminaRing>(new CUI_StaminaRing(pDevice, pContext));
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Create Failed : HUD");
		pInstance.reset();
	}
	return pInstance;
}

shared_ptr<CPrototype> CUI_StaminaRing::Clone(void* pArg)
{
	auto pInstance = shared_ptr<CUI_StaminaRing>(new CUI_StaminaRing(*this));
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Clone Failed : HUD");
		pInstance.reset();
	}
	return pInstance;
}


