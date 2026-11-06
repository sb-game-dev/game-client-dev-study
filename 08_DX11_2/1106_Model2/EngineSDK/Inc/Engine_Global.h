#pragma once


namespace Engine
{
	static const wstring		g_strTransformComTag = { TEXT("Com_Transform") };

	static const wstring		g_strSampler_Point = { TEXT("Sampler_Point") };
	static const D3D11_SAMPLER_DESC g_Sampler_Point_Desc = {
		.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT,
		.AddressU = D3D11_TEXTURE_ADDRESS_WRAP,
		.AddressV = D3D11_TEXTURE_ADDRESS_WRAP,
		.AddressW = D3D11_TEXTURE_ADDRESS_WRAP,
		.MipLODBias = 0,
		.MaxAnisotropy = 0,
		.ComparisonFunc = D3D11_COMPARISON_NEVER,
		.BorderColor = 0.f,
		.MinLOD = 0.f,
		.MaxLOD = D3D11_FLOAT32_MAX
	};

	static const wstring		g_strSampler_Linear = { TEXT("Sampler_Linear") };
	static const D3D11_SAMPLER_DESC g_Sampler_Linear_Desc = {
		.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR,
		.AddressU = D3D11_TEXTURE_ADDRESS_WRAP,
		.AddressV = D3D11_TEXTURE_ADDRESS_WRAP,
		.AddressW = D3D11_TEXTURE_ADDRESS_WRAP,
		.MipLODBias = 0,
		.MaxAnisotropy = 0,
		.ComparisonFunc = D3D11_COMPARISON_NEVER,
		.BorderColor = 0.f,
		.MinLOD = 0.f,
		.MaxLOD = D3D11_FLOAT32_MAX
	};
}
