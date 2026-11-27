#pragma once


namespace Engine
{
	static const wstring		g_strTransformComTag = { TEXT("Com_Transform") };

	static const wstring		g_strBS_Default = { TEXT("BS_Default") };
	static const D3D11_BLEND_DESC g_BSDefault_Desc = {
		.AlphaToCoverageEnable = false,
		.IndependentBlendEnable = false,
		.RenderTarget = {
			{ 
				false, D3D11_BLEND_SRC_ALPHA, D3D11_BLEND_INV_SRC_ALPHA, D3D11_BLEND_OP_ADD, D3D11_BLEND_ONE, D3D11_BLEND_ZERO, D3D11_BLEND_OP_ADD, D3D11_COLOR_WRITE_ENABLE_ALL 
			},		
		}
	};
	
	static const wstring		g_strBS_AlphaBlend = { TEXT("BS_AlphaBlend") };
	static const D3D11_BLEND_DESC g_BSAlphaBlend_Desc = {
		.AlphaToCoverageEnable = false,
		.IndependentBlendEnable = false,
		.RenderTarget = {
			{ 
				true, D3D11_BLEND_SRC_ALPHA, D3D11_BLEND_INV_SRC_ALPHA, D3D11_BLEND_OP_ADD, D3D11_BLEND_ONE, D3D11_BLEND_ZERO, D3D11_BLEND_OP_ADD, D3D11_COLOR_WRITE_ENABLE_ALL 
			},			
		}
	};


	static const wstring		g_strDSS_Default = { TEXT("DSS_Default") };
	static const D3D11_DEPTH_STENCIL_DESC g_DSSDefault_Desc = {
		.DepthEnable = true, 
		.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL, 
		.DepthFunc = D3D11_COMPARISON_LESS_EQUAL, 
		.StencilEnable = false, 
	};

	static const wstring		g_strDSS_NonZ = { TEXT("DSS_NonZ") };
	static const D3D11_DEPTH_STENCIL_DESC g_DSSNonZ_Desc = {
		.DepthEnable = false,
		.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO,		
		.StencilEnable = false,
	};

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
