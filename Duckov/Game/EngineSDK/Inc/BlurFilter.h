#pragma once
#include "Engine_Defines.h"
/* 텍스처를 하나 받아서, 그 텍스처를 흐리게 만들어 주는 도구 */
NS_BEGIN(Engine)
class CBlurFilter final
{
private:
	CBlurFilter(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);

public:
	~CBlurFilter() = default;

public:
	HRESULT		Initialize(uint32_t iWidth, uint32_t iHeight);
	void		BlurInPlace(ID3D11ShaderResourceView* pInputSRV, ID3D11UnorderedAccessView* pInputUAV, uint32_t iBlurCount);

private:
	ComPtr<ID3D11Device>				m_pDevice = { nullptr };
	ComPtr<ID3D11DeviceContext>			m_pContext = { nullptr };

	uint32_t	m_iWidth = {};
	uint32_t	m_iHeight = {};

	ComPtr<ID3D11Buffer>				m_pCB_Mouse = { nullptr };
	ComPtr<ID3D11ShaderResourceView>	m_pSRV_B = { nullptr };
	ComPtr<ID3D11UnorderedAccessView>	m_pUAV_B = { nullptr };

	ComPtr<ID3D11ComputeShader>			m_pCS_Horz = { nullptr };
	ComPtr<ID3D11ComputeShader>			m_pCS_Vert = { nullptr };
private:
	HRESULT	Ready_Texture_B();
	HRESULT	Ready_ComputeShader();
	HRESULT	Ready_MouseBuffer();
public:
	static unique_ptr<CBlurFilter> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, uint32_t iWidth, uint32_t iHeight);
};

NS_END