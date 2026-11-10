#pragma once
#include "Engine_Defines.h"
/* 텍스처를 하나 받아서, 그 텍스처를 흐리게 만들어 주는 도구 */
NS_BEGIN(Engine)
class CBlurFilter final
{
private:
	static constexpr uint32_t MAX_BLUR_FIELD = 10;
private:
	CBlurFilter(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);

public:
	~CBlurFilter() = default;

public:
	HRESULT		Initialize(uint32_t iWidth, uint32_t iHeight);
	void		BlurInPlace(ID3D11ShaderResourceView* pInputSRV, ID3D11UnorderedAccessView* pInputUAV, uint32_t iBlurCount);

	void		AddBlurField(f32_t fLeft, f32_t fTop, f32_t fWidth, f32_t fHeight) {
		if (m_BlurField.size() < MAX_BLUR_FIELD)
			m_BlurField.push_back({ fLeft,fTop,fWidth,fHeight });
	}

private:
	ComPtr<ID3D11Device>				m_pDevice = { nullptr };
	ComPtr<ID3D11DeviceContext>			m_pContext = { nullptr };

	uint32_t	m_iWidth = {};
	uint32_t	m_iHeight = {};

	ComPtr<ID3D11ShaderResourceView>	m_pSRV_B = { nullptr };
	ComPtr<ID3D11UnorderedAccessView>	m_pUAV_B = { nullptr };

	ComPtr<ID3D11ComputeShader>			m_pCS_Horz = { nullptr };
	ComPtr<ID3D11ComputeShader>			m_pCS_Vert = { nullptr };

	struct BLUR_FIELD
	{
		f32_t fLeft, fTop, fWidth, fHeight;
	};
	struct CB_BLUR_DATA
	{
		BLUR_FIELD 	BlurFields[MAX_BLUR_FIELD];
		uint32_t	iNumField;
		f32_t		vPad[3];
	};
	vector<BLUR_FIELD>					m_BlurField;
	shared_ptr<class CConstantBuffer>			m_pCB = {};

private:
	HRESULT	Ready_Texture_B();
	HRESULT	Ready_ComputeShader();
	HRESULT	Ready_ConstantBuffer();

public:
	static unique_ptr<CBlurFilter> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, uint32_t iWidth, uint32_t iHeight);
};

NS_END