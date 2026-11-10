#ifndef Engine_Enum_h__
#define Engine_Enum_h__

namespace Engine
{
	enum class WINMODE { FULL, WIN, END };

	enum class STATE { RIGHT, UP, LOOK, POSITION, END };

	enum class MODEL { NONANIM, ANIM, END };

	enum class DIM { LB, RB, WHEEL, END };    

	enum class DIMM { X, Y, WHEEL, END };   

	enum class D3DTS { VIEW, PROJ, END };

	enum class CAMERA { ORTHOGRAPHIC, QUARTERVIEW, FREE, END };

	enum class INFO { RIGHT, UP, LOOK, POS, END };

	enum class ROTATION { X, Y, Z, END };

	enum class RENDERID { PRIORITY, NONALPHA, OCCLUDEDPLAYER, PLAYER, ALPHA_PRE, SHADOW, REFLECT, ALPHA, NONALPHA_UI, ALPHA_UI, END };

	enum class VSLOT { WORLD, CAMERA, END };

	enum class PSLOT { LIGHT, CAMERA, END };

	enum class SAMPLER_SLOT { POINT, LINEAR, END };

}
#endif // Engine_Enum_h__
