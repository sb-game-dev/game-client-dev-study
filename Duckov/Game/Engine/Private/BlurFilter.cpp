#include "BlurFilter.h"

/* 셰이더의 [numthreads(N, 1, 1)]의 N과 반드시 같아야 함 */
static constexpr uint32_t s_iThreadsPerGroup = 256;

CBlurFilter::CBlurFilter(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	: m_pDevice{ pDevice }
	, m_pContext{ pContext }
{
}

HRESULT CBlurFilter::Initialize(uint32_t iWidth, uint32_t iHeight)
{
	m_iWidth = iWidth;
	m_iHeight = iHeight;

	if (FAILED(Ready_Texture_B()))
		return E_FAIL;

	if (FAILED(Ready_ComputeShader()))
		return E_FAIL;

	if (FAILED(Ready_Sampler()))
		return E_FAIL;

	return S_OK;
}

void CBlurFilter::BlurInPlace(ID3D11ShaderResourceView* pInputSRV, ID3D11UnorderedAccessView* pInputUAV, uint32_t iBlurCount)
{
	/* 바인딩 해제용 */
	ID3D11ShaderResourceView* pNullSRV[1] = {nullptr};
	ID3D11UnorderedAccessView* pNullUAV[1] = {nullptr};

	/* 그룹 수 = 올림(픽셀 수 / 그룹당 스레드 수) */
	uint32_t iNumGroupsX = (m_iWidth + s_iThreadsPerGroup - 1) / s_iThreadsPerGroup; // (1280 + 256 - 1) /256 = 5
	uint32_t iNumGroupsY = (m_iHeight + s_iThreadsPerGroup - 1) / s_iThreadsPerGroup;// (720 + 256 - 1) / 256 = 4

	m_pContext->CSSetSamplers(0, 1, m_pSampler.GetAddressOf());

	for (uint32_t i = 0; i < iBlurCount; ++i)
	{
		m_pContext->CSSetShader(m_pCS_Horz.Get(), nullptr, 0);
		m_pContext->CSSetShaderResources(0, 1, &pInputSRV);								// A텍스처의 SRV 바인드
		m_pContext->CSSetUnorderedAccessViews(0, 1, m_pUAV_B.GetAddressOf(), nullptr);	// B텍스처의 UAV 바인드

		m_pContext->Dispatch(iNumGroupsX, m_iHeight, 1); // Dispatch(5, 720, 1)
	}

	m_pContext->CSSetShaderResources(0, 1, pNullSRV);
	m_pContext->CSSetUnorderedAccessViews(0, 1, pNullUAV, nullptr);

	for(uint32_t i = 0 ; i < iBlurCount; ++i)
	{
		m_pContext->CSSetShader(m_pCS_Vert.Get(), nullptr, 0);
		m_pContext->CSSetShaderResources(0, 1, m_pSRV_B.GetAddressOf());	// B텍스처의 SRV 바인드
		m_pContext->CSSetUnorderedAccessViews(0, 1, &pInputUAV, nullptr);	// A텍스처의 UAV 바인드

		m_pContext->Dispatch(m_iWidth, iNumGroupsY, 1);	// Dispatch(1280, 4, 1)
	}
	m_pContext->CSSetShaderResources(0, 1, pNullSRV);
	m_pContext->CSSetUnorderedAccessViews(0, 1, pNullUAV, nullptr);

	m_pContext->CSSetShader(nullptr, nullptr, 0);
}

HRESULT CBlurFilter::Ready_Texture_B()
{
	D3D11_TEXTURE2D_DESC TextureDesc{};
	TextureDesc.Width = m_iWidth;
	TextureDesc.Height = m_iHeight;
	TextureDesc.MipLevels = 1;
	TextureDesc.ArraySize = 1;
	TextureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;		// 입력 텍스처 A와 같은 포맷
	TextureDesc.SampleDesc.Count = 1;
	TextureDesc.SampleDesc.Quality = 0;
	TextureDesc.Usage = D3D11_USAGE_DEFAULT;
	TextureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;	
	TextureDesc.CPUAccessFlags = 0;
	TextureDesc.MiscFlags = 0;

	ComPtr<ID3D11Texture2D> pTexture_B;
	if (FAILED(m_pDevice->CreateTexture2D(&TextureDesc, nullptr, &pTexture_B)))
		return E_FAIL;

	// 포맷이 확정된 텍스처라 뷰 desc는 nullptr로 설정
	if (FAILED(m_pDevice->CreateShaderResourceView(pTexture_B.Get(), nullptr, &m_pSRV_B)))
		return E_FAIL;

	if (FAILED(m_pDevice->CreateUnorderedAccessView(pTexture_B.Get(), nullptr, &m_pUAV_B)))
		return E_FAIL;

	return S_OK;
}

HRESULT CBlurFilter::Ready_ComputeShader()
{
	ComPtr<ID3DBlob> pHorzBlob, pVertBlob, pErrBlob;

	uint32_t iFlags = 0;
#ifdef _DEBUG
	iFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	if (FAILED(D3DCompileFromFile(L"../Shader/Shader_Blur.hlsl", nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"CS_HorzBlur", "cs_5_0", iFlags, 0, &pHorzBlob, &pErrBlob)))
	{
		if (pErrBlob) OutputDebugStringA((char*)pErrBlob->GetBufferPointer());
		return E_FAIL;
	}

	if (FAILED(D3DCompileFromFile(L"../Shader/Shader_Blur.hlsl", nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		"CS_VertBlur", "cs_5_0", iFlags, 0, &pVertBlob, &pErrBlob)))
	{
		if (pErrBlob) OutputDebugStringA((char*)pErrBlob->GetBufferPointer());
		return E_FAIL;
	}

	if (FAILED(m_pDevice->CreateComputeShader(pHorzBlob->GetBufferPointer(), pHorzBlob->GetBufferSize(), nullptr, &m_pCS_Horz)))
		return E_FAIL;

	if (FAILED(m_pDevice->CreateComputeShader(pVertBlob->GetBufferPointer(), pVertBlob->GetBufferSize(), nullptr, &m_pCS_Vert)))
		return E_FAIL;

	return S_OK;
}

HRESULT CBlurFilter::Ready_Sampler()
{
	// 샘플러 생성
	D3D11_SAMPLER_DESC samplerDesc{};

	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	samplerDesc.AddressU = samplerDesc.AddressV = samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	if (FAILED(m_pDevice->CreateSamplerState(&samplerDesc, m_pSampler.GetAddressOf())))
		return E_FAIL;


	return S_OK;
}

unique_ptr<CBlurFilter> CBlurFilter::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, uint32_t iWidth, uint32_t iHeight)
{
	auto pInstance = unique_ptr<CBlurFilter>(new CBlurFilter(pDevice, pContext));

	if (FAILED(pInstance->Initialize(iWidth, iHeight)))
	{
		MSG_BOX("Failed to Created : CBlurFilter");
		pInstance.reset();
	}

	return pInstance;
}