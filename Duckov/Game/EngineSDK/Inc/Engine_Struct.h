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

	typedef struct tagVtxTex
	{
		float3_t	vPosition;
		float2_t	vUV;
	}VTXTEX;

}


#endif // Engine_Struct_h__
