#include "UI_HpBar.h"
#include "Inven.h"
#include "Player.h"
using namespace UI_HpBar;


CUI_HpBar::CUI_HpBar(ComPtr<ID3D11Device>pDevice, ComPtr<ID3D11DeviceContext>pContext)
	: CPartObject{ pDevice,pContext }
{

}


HRESULT CUI_HpBar::Initialize_Prototype()
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

	return S_OK;
}

HRESULT CUI_HpBar::Initialize(void* pArg)
{
	if (FAILED(__super::Initialize(pArg)))
		return E_FAIL;

	if (FAILED(Ready_Components()))
		return E_FAIL;
	if (FAILED(Ready_InstanceBuffer()))
		return E_FAIL;
	return S_OK;
}

void CUI_HpBar::Priority_Update(f32_t fDeltaTime)
{
	__super::Priority_Update(fDeltaTime);
}

void CUI_HpBar::Update(f32_t fDeltaTime)
{
	__super::Update(fDeltaTime);

	m_fHitTimeRemaining = max(0.f, m_fHitTimeRemaining - fDeltaTime);

	auto pInven = m_pInven.lock();
	if (nullptr == pInven)
	{
		pInven = dynamic_pointer_cast<CInven>(CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::STATIC), L"Layer_Static", GO::Inven));
		if (nullptr == pInven)
			return;
		m_pInven = pInven;
	}
}

void CUI_HpBar::Late_Update(f32_t fDeltaTime)
{
	__super::Late_Update(fDeltaTime);
	auto pInven = m_pInven.lock();
	if (nullptr == pInven)
		return;
	if (!pInven->Is_Open())
		CGameInstance::Get().Add_RenderGroup(RENDERID::ALPHA_UI, dynamic_pointer_cast<CGameObject>(shared_from_this()));
}

HRESULT CUI_HpBar::Render()
{
	//---------------- 인스턴스 버퍼 준비 ----------------//
	Build_Instances();

	//---------------- 바 UI 그리기 ----------------//
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

	m_pContext->DrawIndexedInstanced(m_iIndexCnt, iCount, 0, 0, 0);

	return S_OK;
}

void CUI_HpBar::Initialize_HitAnimation()
{
	m_fHitTimeRemaining = m_fHitDuration;
}

void CUI_HpBar::Build_Instances()
{
	// 인스턴스 초기화
	m_Instances.clear();

	auto pParent = m_pParent.lock();
	if (pParent)
	{
		vector_t vHead = m_pParentTransformCom->Get_State(STATE::POSITION)
			+ XMVectorSet(0.f, 2.f, 0.f, 0.f);
		auto matPlayerWorld = m_pParentTransformCom->Get_World(); 
		
		matrix_t matVP = CGameInstance::Get().Get_Perspective_Transform(D3DTS::VIEW) * CGameInstance::Get().Get_Perspective_Transform(D3DTS::PROJ);
		vector_t vScreenPos = XMVector3TransformCoord(vHead, matVP);

		f32_t x = XMVectorGetX(vScreenPos) * g_iWinSizeX * 0.5f;
		f32_t y = XMVectorGetY(vScreenPos) * g_iWinSizeY * 0.5f;

		// 애니메이션의 남은 시간 비율 -> 1이면 애니메이션 처음 시작, 0이면 애니메이션 끝
		f32_t fRatio = m_fHitTimeRemaining / m_fHitDuration;
		
		// 크기 -> 애니메이션 남은 시간 비율만큼 늘어남
		f32_t w = HP_SLIDER_WIDTH * (1 + fRatio * 0.2f);
		f32_t h = HP_SLIDER_HEIGHT* (1 + fRatio * 0.2f);

		// x,y 흔들기 -> 애니메이션 남은 시간 비율만큼 흔들림
		f32_t fDeltaX = (CGameInstance::Get().Random(-4, 4)) * fRatio;
		f32_t fDeltaY = (CGameInstance::Get().Random(-4, 4)) * fRatio;

		// 크기 + 흔들기에의해 새롭게 업데이트된 Left,Top 구하기
		f32_t left = x - w * 0.5f + fDeltaX;
		f32_t top = y + h * 0.5f + fDeltaY;

		Push_Bar(left - 2.f, top + 2.f, w + 4.f, h + 4.f,
			1, COLOR_HP_FILL_SIDE, h * 0.5f);

		Push_Bar(left, top, w, h, 
			pParent->Get_HP() / pParent->Get_MaxHP(), AddWhiteColor(COLOR_HP_FILL, fRatio), h * 0.5f);
	}
}

HRESULT CUI_HpBar::Ready_Components()
{
	if (FAILED(__super::Add_Component(ETOUI(LEVEL::STATIC), Proto::VS_UI,
		TEXT("Com_VS"), m_pVSCom)))
		return E_FAIL;

	if (FAILED(__super::Add_Component(ETOUI(LEVEL::STATIC), Proto::PS_UI,
		TEXT("Com_PS"), m_pPSCom)))
		return E_FAIL;
	return S_OK;
}

HRESULT CUI_HpBar::Ready_InstanceBuffer()
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

void CUI_HpBar::Push_Rect(f32_t fLeft, f32_t fTop, f32_t fWidth, f32_t fHeight, float4_t vColor, f32_t fRadius, f32_t fBorder)
{
	// 좌상단과 우하단을 각각 정수 픽셀로 반올림 (1px 테두리가 픽셀 사이에 끼지 않게)
	f32_t fSnapLeft = floorf(fLeft + 0.5f);
	f32_t fSnapTop = floorf(fTop + 0.5f);
	f32_t fSnapRight = floorf(fLeft + fWidth + 0.5f);
	f32_t fSnapBottom = floorf(fTop - fHeight + 0.5f);	// 직교 공간은 y 위쪽 -> 아래 변 = 위 변 - 높이

	m_Instances.push_back({ { fSnapLeft, fSnapTop, fSnapRight - fSnapLeft, fSnapTop - fSnapBottom },
							vColor, { fRadius, fBorder, 0.f, 0.f }, { 0.f, 0.f, 1.f, 1.f } });
}
void CUI_HpBar::Push_Bar(f32_t fLeft, f32_t fTop, f32_t fWidth, f32_t fHeight, f32_t fRatio, float4_t vFillColor, f32_t fRadius)
{
	fRatio = max(0.f, min(1.f, fRatio));
	if (fRatio > 0.f)
		Push_Rect(fLeft, fTop, fWidth * fRatio, fHeight, vFillColor, fRadius);
}

float4_t CUI_HpBar::AddWhiteColor(float4_t OriginalColor, f32_t fRatio)
{
	return float4_t(OriginalColor.x + (1 - OriginalColor.x) * fRatio,
		OriginalColor.y + (1 - OriginalColor.y) * fRatio,
		OriginalColor.z + (1 - OriginalColor.z) * fRatio,
		OriginalColor.w + (1 - OriginalColor.w) * fRatio
		);
}

shared_ptr<CUI_HpBar> CUI_HpBar::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
	auto pInstance = shared_ptr<CUI_HpBar>(new CUI_HpBar(pDevice, pContext));
	if (FAILED(pInstance->Initialize_Prototype()))
	{
		MSG_BOX("Create Failed : HUD");
		pInstance.reset();
	}
	return pInstance;
}

shared_ptr<CPrototype> CUI_HpBar::Clone(void* pArg)
{
	auto pInstance = shared_ptr<CUI_HpBar>(new CUI_HpBar(*this));
	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX("Clone Failed : HUD");
		pInstance.reset();
	}
	return pInstance;
}


