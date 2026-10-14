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

	return S_OK;
}

void CBlurFilter::BlurInPlace(ID3D11ShaderResourceView* pInputSRV, ID3D11UnorderedAccessView* pInputUAV, uint32_t iBlurCount)
{
	/* 바인딩 해제용 */
	ID3D11ShaderResourceView* pNullSRV = { nullptr };
	ID3D11UnorderedAccessView* pNullUAV = { nullptr };

	/* 그룹 수 = 올림(픽셀 수 / 그룹당 스레드 수) */
	uint32_t iNumGroupsX = (m_iWidth + s_iThreadsPerGroup - 1) / s_iThreadsPerGroup;
	uint32_t iNumGroupsY = (m_iHeight + s_iThreadsPerGroup - 1) / s_iThreadsPerGroup;

	for (uint32_t i = 0; i < iBlurCount; ++i)
	{
		/* 가로 블러 : A(SRV) -> B(UAV) */
		m_pContext->CSSetShader(m_pCS_Horz.Get(), nullptr, 0);
		m_pContext->CSSetShaderResources(0, 1, &pInputSRV);
		m_pContext->CSSetUnorderedAccessViews(0, 1, m_pUAV_B.GetAddressOf(), nullptr);

		/* 그룹 하나가 가로 256픽셀 한 줄을 맡음 -> 가로 그룹 iNumGroupsX개, 세로는 줄 수만큼 */
		m_pContext->Dispatch(iNumGroupsX, m_iHeight, 1);

		/* B를 다음 패스에서 SRV로 써야 하므로 해제 (입력/출력 동시 바인딩 불가) */
		m_pContext->CSSetShaderResources(0, 1, &pNullSRV);
		m_pContext->CSSetUnorderedAccessViews(0, 1, &pNullUAV, nullptr);

		/* 세로 블러 : B(SRV) -> A(UAV) */
		m_pContext->CSSetShader(m_pCS_Vert.Get(), nullptr, 0);
		m_pContext->CSSetShaderResources(0, 1, m_pSRV_B.GetAddressOf());
		m_pContext->CSSetUnorderedAccessViews(0, 1, &pInputUAV, nullptr);

		/* 그룹 하나가 세로 256픽셀 한 줄을 맡음 */
		m_pContext->Dispatch(m_iWidth, iNumGroupsY, 1);

		m_pContext->CSSetShaderResources(0, 1, &pNullSRV);
		m_pContext->CSSetUnorderedAccessViews(0, 1, &pNullUAV, nullptr);
	}

	/* 계산 셰이더 해제 */
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
	TextureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE		// 세로 패스 입력
		| D3D11_BIND_UNORDERED_ACCESS;	// 가로 패스 출력 (렌더 타겟으로는 안 쓰므로 RTV 불필요)
	TextureDesc.CPUAccessFlags = 0;
	TextureDesc.MiscFlags = 0;

	ComPtr<ID3D11Texture2D> pTexture_B;
	if (FAILED(m_pDevice->CreateTexture2D(&TextureDesc, nullptr, &pTexture_B)))
		return E_FAIL;

	/* 포맷이 확정된 텍스처라 뷰 desc는 nullptr로 충분 */
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