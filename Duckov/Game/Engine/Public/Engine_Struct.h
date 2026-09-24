#ifndef Engine_Struct_h__
#define Engine_Struct_h__

#include "Engine_Typedef.h"

namespace Engine
{
	typedef struct tagEngineDesc
	{
		HWND		hWnd;
		WINMODE		eWinMode;
		uint32_t	iWinSizeX, iWinSizeY;
	}ENGINE_DESC;

	typedef struct tagVtxColor
	{
		float3_t	vPosition;
		float4_t	vColor;

		static constexpr uint32_t iNumElements = 2;
		static constexpr D3D11_INPUT_ELEMENT_DESC Elements[iNumElements] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

	}VTXCOL;

	struct CB_TRANSFORM
	{
		float4x4_t WorldMatrix;
		float4x4_t ViewMatrix;
		float4x4_t ProjMatrix;
	};
	
	//D3D11_INPUT_ELEMENT_DESC desc1[] =
	//{
	//	{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
	//	 D3D11_INPUT_PER_VERTEX_DATA, 0},
	//
	//	{"COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12,
	//	 D3D11_INPUT_PER_VERTEX_DATA, 0}
	//};




	typedef struct tagVtxTex
	{
		float3_t	vPosition;
		float3_t	vNormal;
		float2_t	vTex0;
		float2_t	vTex1;
	}VTXTEX;


}


#endif // Engine_Struct_h__
