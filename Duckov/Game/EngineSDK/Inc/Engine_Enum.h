#ifndef Engine_Enum_h__
#define Engine_Enum_h__

namespace Engine
{
	enum class WINMODE { FULL, WIN, END };

	enum class STATE { RIGHT, UP, LOOK, POSITION, END };

	enum class MODEL { NONANIM, ANIM, END };

	enum class DIM { LB, RB, WHEEL, END };    

	enum class DIMM { X, Y, WHEEL, END };   

	//// Dynamic 컴포넌트 경우 매 프레임마다 갱신해야하는 컴포넌트 집단
	//enum COMPONENTID { ID_DYNAMIC, ID_STATIC, ID_END };
	//
	enum class INFO { RIGHT, UP, LOOK, POS, END };
	//
	enum class ROTATION { X, Y, Z, END };
	//
	//enum TEXTUREID { TEX_NORMAL, TEX_CUBE, TEX_END };
	//
	enum class RENDERID { PRIORITY, NONALPHA, OCCLUDEDPLAYER, PLAYER, ALPHA_PRE, SHADOW, REFLECT, ALPHA, NONALPHA_UI, ALPHA_UI, END };
}
#endif // Engine_Enum_h__
