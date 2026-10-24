#include "Inven.h"
#include <io.h>
#include <iostream>


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

	m_vecBackPack.resize(10);
	m_vecStorage.resize(100);

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

void CInven::Build_Instances()
{
	Push_Rect(100.f, 100.f, 200.f, 120.f, { 1.f, 0.f, 0.f, 0.8f }, 16.f);       // 테스트
	Push_Rect(100.f, 260.f, 200.f, 120.f, { 1.f, 1.f, 1.f, 1.f }, 16.f, 3.f);   // 테두리만
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
void CInven::Push_Rect(f32_t x, f32_t y, f32_t w, f32_t h, float4_t vColor, f32_t fRadius, f32_t fBorder)
{
	m_Instances.push_back({ { x, y, w, h }, vColor, { fRadius, fBorder, 0.f, 0.f }, { 0.f, 0.f, 1.f, 1.f } });
}
void CInven::Push_Icon(f32_t x, f32_t y, f32_t w, f32_t h, int32_t iIcon, f32_t fAlpha)
{
	m_Instances.push_back({ { x, y, w, h }, { 1.f, 1.f, 1.f, fAlpha }, { 0.f, 0.f, 1.f, (f32_t)iIcon }, { 0.f, 0.f, 1.f, 1.f } });
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


