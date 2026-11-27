#pragma once


namespace Engine
{
	static const wstring		g_strTransformComTag = { TEXT("Com_Transform") };

	//===========Blend_State===========
	static const wstring		g_strBS_Default = { TEXT("BS_Default") };
	static const D3D11_BLEND_DESC g_BS_Default_Desc = {
		.AlphaToCoverageEnable = false,
		.IndependentBlendEnable = false,
		.RenderTarget = {
			{
				false, D3D11_BLEND_SRC_ALPHA, D3D11_BLEND_INV_SRC_ALPHA, D3D11_BLEND_OP_ADD, D3D11_BLEND_ONE, D3D11_BLEND_ZERO, D3D11_BLEND_OP_ADD, D3D11_COLOR_WRITE_ENABLE_ALL
			},
		}
	};

	static const wstring		g_strBS_AlphaBlend = { TEXT("BS_AlphaBlend") };
	static const D3D11_BLEND_DESC g_BS_AlphaBlend_Desc = {
		.AlphaToCoverageEnable = false,
		.IndependentBlendEnable = false,
		.RenderTarget = {
			{
				true, D3D11_BLEND_SRC_ALPHA, D3D11_BLEND_INV_SRC_ALPHA, D3D11_BLEND_OP_ADD, D3D11_BLEND_ONE, D3D11_BLEND_ZERO, D3D11_BLEND_OP_ADD, D3D11_COLOR_WRITE_ENABLE_ALL
			},
		}
	};

	static const wstring		g_strBS_NoColor = { TEXT("BS_NoColor") };
	static const D3D11_BLEND_DESC g_BS_NoColor_Desc = {
		.AlphaToCoverageEnable = false,
		.IndependentBlendEnable = false,
		.RenderTarget = {
			{
				true, D3D11_BLEND_SRC_ALPHA, D3D11_BLEND_INV_SRC_ALPHA, D3D11_BLEND_OP_ADD, D3D11_BLEND_ONE, D3D11_BLEND_ZERO, D3D11_BLEND_OP_ADD, 0
			},
		}
	};

	//===========DepthStencil_State===========
	static const wstring		g_strDSS_Default = { TEXT("DSS_Default") };
	static const D3D11_DEPTH_STENCIL_DESC g_DSS_Default_Desc = {
		.DepthEnable = true,
		.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL,
		.DepthFunc = D3D11_COMPARISON_LESS_EQUAL,
		.StencilEnable = false,
	};

	static const wstring		g_strDSS_NonZ = { TEXT("DSS_NonZ") };
	static const D3D11_DEPTH_STENCIL_DESC g_DSS_NonZ_Desc = {
		.DepthEnable = false,
		.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO,
		.StencilEnable = false,
	};

	static const wstring		g_strDSS_Alpha = { TEXT("DSS_Alpha") };
	static const D3D11_DEPTH_STENCIL_DESC g_DSS_Alpha_Desc = {
		.DepthEnable = true,
		.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO,
		.DepthFunc = D3D11_COMPARISON_LESS_EQUAL,
		.StencilEnable = false,
	};

	static const wstring		g_strDSS_MirrorMark = { TEXT("DSS_MirrorMark") };
	static const D3D11_DEPTH_STENCIL_DESC g_DSS_MirrorMark_Desc = {
		.DepthEnable = true,
		.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO,
		.DepthFunc = D3D11_COMPARISON_LESS_EQUAL,
		.StencilEnable = true,
		.StencilReadMask = 0xff,
		.StencilWriteMask = 0xff,
		.FrontFace = {.StencilFailOp = D3D11_STENCIL_OP_KEEP, .StencilDepthFailOp = D3D11_STENCIL_OP_KEEP,
			   .StencilPassOp = D3D11_STENCIL_OP_REPLACE, .StencilFunc = D3D11_COMPARISON_ALWAYS },
		.BackFace = {.StencilFailOp = D3D11_STENCIL_OP_KEEP, .StencilDepthFailOp = D3D11_STENCIL_OP_KEEP,
			   .StencilPassOp = D3D11_STENCIL_OP_REPLACE, .StencilFunc = D3D11_COMPARISON_ALWAYS },
	};

	static const wstring		g_strDSS_MirrorReflect = { TEXT("DSS_MirrorReflect") };
	static const D3D11_DEPTH_STENCIL_DESC g_DSS_MirrorReflect_Desc = {
		.DepthEnable = false,
		.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO,
		.DepthFunc = D3D11_COMPARISON_LESS_EQUAL,
		.StencilEnable = true,
		.StencilReadMask = 0xff,
		.StencilWriteMask = 0xff,
		.FrontFace = {.StencilFailOp = D3D11_STENCIL_OP_KEEP, .StencilDepthFailOp = D3D11_STENCIL_OP_KEEP,
			   .StencilPassOp = D3D11_STENCIL_OP_KEEP, .StencilFunc = D3D11_COMPARISON_EQUAL },
		.BackFace = {.StencilFailOp = D3D11_STENCIL_OP_KEEP, .StencilDepthFailOp = D3D11_STENCIL_OP_KEEP,
			   .StencilPassOp = D3D11_STENCIL_OP_KEEP, .StencilFunc = D3D11_COMPARISON_EQUAL }
	};

	static const wstring		g_strDSS_SilhouetteMark = { TEXT("DSS_MarkSilhouette") };
	static const D3D11_DEPTH_STENCIL_DESC g_DSS_MarkSilhouetteMark_Desc = {
		.DepthEnable = true,
		.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL,
		.DepthFunc = D3D11_COMPARISON_LESS_EQUAL,
		.StencilEnable = true,
		.StencilReadMask = 0xff,
		.StencilWriteMask = 0xff,
		.FrontFace = {.StencilFailOp = D3D11_STENCIL_OP_KEEP, .StencilDepthFailOp = D3D11_STENCIL_OP_KEEP,
			   .StencilPassOp = D3D11_STENCIL_OP_REPLACE, .StencilFunc = D3D11_COMPARISON_ALWAYS },
		.BackFace = {.StencilFailOp = D3D11_STENCIL_OP_KEEP, .StencilDepthFailOp = D3D11_STENCIL_OP_KEEP,
			   .StencilPassOp = D3D11_STENCIL_OP_REPLACE, .StencilFunc = D3D11_COMPARISON_ALWAYS }
	};

	static const wstring		g_strDSS_NoDoubleBlend = { TEXT("DSS_NoDoubleBlend") };
	static const D3D11_DEPTH_STENCIL_DESC g_DSS_NoDoubleBlend_Desc = {
		.DepthEnable = true,
		.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL,
		.DepthFunc = D3D11_COMPARISON_LESS_EQUAL,
		.StencilEnable = true,
		.StencilReadMask = 0xff,
		.StencilWriteMask = 0xff,
		.FrontFace = {.StencilFailOp = D3D11_STENCIL_OP_KEEP, .StencilDepthFailOp = D3D11_STENCIL_OP_KEEP,
			   .StencilPassOp = D3D11_STENCIL_OP_INCR, .StencilFunc = D3D11_COMPARISON_EQUAL },
		.BackFace = {.StencilFailOp = D3D11_STENCIL_OP_KEEP, .StencilDepthFailOp = D3D11_STENCIL_OP_KEEP,
			   .StencilPassOp = D3D11_STENCIL_OP_INCR, .StencilFunc = D3D11_COMPARISON_EQUAL }
	};

	//===========Rasterizer_State===========
	static const wstring		g_strRS_Default = { TEXT("RS_Default") };
	static const D3D11_RASTERIZER_DESC g_RS_DefaultDesc = {
		.FillMode = D3D11_FILL_SOLID,
		.CullMode = D3D11_CULL_BACK,
		.FrontCounterClockwise = false
	};

	static const wstring		g_strRS_Cull_None = { TEXT("RS_Cull_None") };
	static const D3D11_RASTERIZER_DESC g_RS_Cull_None = {
		.FillMode = D3D11_FILL_SOLID,
		.CullMode = D3D11_CULL_NONE,
		.FrontCounterClockwise = false
	};
	static const wstring		g_strRS_Cull_Front = { TEXT("RS_Cull_Front") };
	static const D3D11_RASTERIZER_DESC g_RS_Cull_Front = {
		.FillMode = D3D11_FILL_SOLID,
		.CullMode = D3D11_CULL_FRONT,
		.FrontCounterClockwise = false
	};

	//===========Sampler===========
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
