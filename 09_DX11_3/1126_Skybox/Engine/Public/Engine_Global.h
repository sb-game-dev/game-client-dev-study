#pragma once


namespace Engine
{
	static const wstring		g_strTransformComTag = { TEXT("Com_Transform") };

	static const wstring		g_strRS_Default = { TEXT("RS_Default") };
	static const D3D11_RASTERIZER_DESC g_RSDefault_Desc = {
		.FillMode = D3D11_FILL_SOLID,
		.CullMode = D3D11_CULL_BACK,
		.FrontCounterClockwise = false, 		
	};

	static const wstring		g_strRS_NonCull = { TEXT("RS_NonCull") };
	static const D3D11_RASTERIZER_DESC g_RSNonCull_Desc = {
		.FillMode = D3D11_FILL_SOLID,
		.CullMode = D3D11_CULL_NONE,
		.FrontCounterClockwise = false,
	};

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
