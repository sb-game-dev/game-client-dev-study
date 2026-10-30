#ifndef Engine_Enum_h__
#define Engine_Enum_h__

namespace Engine
{

	enum class WINMODE { FULL, WIN, END };	

	enum class STATE { RIGHT, UP, LOOK, POSITION, END };

	enum class RENDERGROUP { PRIORITY, NONBLEND, BLEND, UI, END };

	enum class D3DTS { VIEW, PROJ, END };

	enum class DIMK { LB, RB, WHEEL, END };

	enum class DIMM { X, Y, WHEEL, END };

	//enum ROTATION { ROT_X, ROT_Y, ROT_Z, ROT_END };

	//enum TEXTUREID { TEX_NORMAL, TEX_CUBE, TEX_END };

	

	

}
#endif // Engine_Enum_h__
