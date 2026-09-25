#ifndef Engine_Defines_h__
#define Engine_Defines_h__

#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")
//#include <d3dx9.h>

#include <DirectXMath.h> 
#include <DirectXColors.h>
using namespace DirectX;

#include <memory>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <functional>
#include <string>
#include <unordered_map>
#include <ctime>
#include <io.h>
#include <iostream>


using namespace std;

#include <wrl/client.h>
using namespace Microsoft::WRL;

#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")

#include "Engine_Enum.h"
#include "Engine_Macro.h"
#include "Engine_Struct.h"
#include "Engine_Typedef.h"
#include "Engine_Function.h"

// dinput 사용
#define DIRECTINPUT_VERSION	0x0800
#include <dinput.h>

// 경고 처리 무시
#pragma warning(disable : 4251)

#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifndef DBG_NEW 

#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#define new DBG_NEW 

#endif
#endif

using namespace Engine;

#endif // Engine_Defines_h__
