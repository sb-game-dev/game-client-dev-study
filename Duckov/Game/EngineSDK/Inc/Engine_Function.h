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
		replace(strPath.begin(), strPath.end(), L'\\', L'/');
		
		// 대문자 -> 소문자
		transform(strPath.begin(), strPath.end(), strPath.begin(), ::towlower);
	
		// 앞에 붙은 루트 제거
		const wstring_t strRoot = L"../../../resource/";
		if (0 == strPath.rfind(strRoot, 0))
			strPath.erase(0, strRoot.size());
		return strPath;
	}

	// 쿼터니언 -> Euler 각 (도)
	// CTransform::Rotation(x, y, z)이 쓰는 XMQuaternionRotationRollPitchYaw와 같은 순서(Z -> X -> Y)로 푼다.
	// 반환값은 { Pitch(X), Yaw(Y), Roll(Z) }이고, Set_Rotation에 그대로 넘기면 된다.
	inline float3_t Quat_To_EulerDeg(fvector_t vQuat)
	{
		// 1. 쿼터니언 -> 회전 행렬
		float4x4_t m;
		XMStoreFloat4x4(&m, XMMatrixRotationQuaternion(XMQuaternionNormalize(vQuat)));

		// 2. Pitch(X) : _32 = -sin(pitch) -> Look의 y성분을 바꾸는것은 Pitch회전밖에 없기 때문에 가장 먼저구한다.
		f32_t fSinPitch = -m._32;
		// 부동소수점 오차 1.000001f 과 같은 오류 방지
		if (fSinPitch > 1.f)	fSinPitch = 1.f;
		if (fSinPitch < -1.f)	fSinPitch = -1.f;
		const f32_t fPitch = asinf(fSinPitch);

		// 3. Yaw(Y), Roll(Z)
		f32_t fYaw = {}, fRoll = {};
		if (fabsf(fSinPitch) < 0.9999f)
		{
			fYaw = atan2f(m._31, m._33);		// cos(p)sin(y) / cos(p)cos(y)
			fRoll = atan2f(m._12, m._22);		// sin(r)cos(p) / cos(r)cos(p)
		}
		else
		{
			fYaw = atan2f(-m._13, m._11);	// 짐벌락: Roll을 0으로 두고 Yaw에 몰아줌
			fRoll = 0.f;
		}

		// 4. 라디안 -> 도
		return float3_t{ XMConvertToDegrees(fPitch), XMConvertToDegrees(fYaw), XMConvertToDegrees(fRoll) };
	}
}

#endif // Engine_Function_h__
