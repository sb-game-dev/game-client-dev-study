#ifndef Engine_Function_h__
#define Engine_Function_h__

//#include "Engine_Typedef.h"

namespace Engine
{
	// 템플릿은 기능의 정해져있으나 자료형은 정해져있지 않은 것
	// 기능을 인스턴스화 하기 위하여 만들어두는 틀

	template<typename T>
	void Safe_Delete(T& Pointer)
	{
		if (nullptr != Pointer)
		{
			delete Pointer;
			Pointer = nullptr;
		}
	}

	template<typename T>
	void Safe_Delete_Array(T& Pointer)
	{
		if (nullptr != Pointer)
		{
			delete [] Pointer;
			Pointer = nullptr;
		}
	}

	constexpr const tchar_t* g_strResourceRoot = TEXT("../../../Resource/");
	constexpr const tchar_t* g_strBuiltinPrefix = TEXT("builtin/");

	inline wstring_t Normalize_AssetPath(wstring_t strPath)
	{
		// 역슬래시 -> 슬래시로 대체
		replace(strPath.begin(), strPath.end(), L"\\", L"/");
		
		// 대문자 -> 소문자
		transform(strPath.begin(), strPath.end(), strPath.begin(), ::towlower);

		// 앞에 붙은 루트 제거
		const wstring_t strRoot = L"../../../resource/";
		if (0 == strPath.rfind(strRoot, 0))
			strPath.erase(0, strRoot.size());
		return strPath;
	}
}

#endif // Engine_Function_h__
