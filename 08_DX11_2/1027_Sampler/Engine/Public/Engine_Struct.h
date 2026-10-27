#ifndef Engine_Struct_h__
#define Engine_Struct_h__

namespace Engine
{
	typedef struct tagEngineDesc
	{
		HWND			hWnd;
		WINMODE			eWinMode;
		uint32_t		iWinSizeX, iWinSizeY;
		uint32_t		iNumLevels;
	}ENGINE_DESC;

	typedef struct tagPipeLineDesc
	{
		XMFLOAT4X4						PerspectiveTransformMatrices[ETOI(D3DTS::END)];
		XMFLOAT4X4						OrthoTransformMatrices[ETOI(D3DTS::END)];
		XMFLOAT4X4						PerspectiveTransformInverseMatrices[ETOI(D3DTS::END)];
		XMFLOAT4X4						OrthoTransformInverseMatrices[ETOI(D3DTS::END)];
		XMFLOAT4						vCamPosition;
	}PIPELINE_DESC;

	typedef struct tagVertexPositionTexcoord
	{
		XMFLOAT3		vPosition;
		XMFLOAT2		vTexcoord;
	}VTXPOSTEX;


}


#endif // Engine_Struct_h__
