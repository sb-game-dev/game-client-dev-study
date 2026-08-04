#ifndef Engine_Function_h__
#define Engine_Function_h__

#include "Engine_Typedef.h"

namespace Engine
{
	// 템플릿은 기능의 정해져있으나 자료형은 정해져있지 않은 것
	// 기능을 인스턴스화 하기 위하여 만들어두는 틀

	static D3DXVECTOR3	GetMouse(HWND hWnd)
	{
		POINT		pt{};

		GetCursorPos(&pt);
		ScreenToClient(hWnd, &pt);

		return D3DXVECTOR3((float)pt.x, (float)pt.y, 0.f);
	}
	static RAY CalPickingRay(LPDIRECT3DDEVICE9 pGraphicDev, D3DVIEWPORT9 vp, _matrix proj,int iX, int iY)
	{
		float px = 0.f;
		float py = 0.f;

		//D3DVIEWPORT9 vp;
		//pGraphicDev->GetViewport(&vp);
		//
		//_matrix proj;
		//pGraphicDev->GetTransform(D3DTS_PROJECTION, &proj);

		px = (((2.f * iX) / vp.Width) - 1.f) / proj(0, 0);
		py = (((-2.f * iY) / vp.Height) + 1.f) / proj(1, 1);

		RAY ray;
		ray.vOrig = _vec3(0, 0, 0);
		ray.vDir = _vec3(px, py, 1);

		return ray;
	}

	static void TransformRay(RAY* ray, _matrix* mat)
	{
		D3DXVec3TransformCoord(
			&ray->vOrig,
			&ray->vOrig,
			mat
		);

		D3DXVec3TransformNormal(
			&ray->vDir,
			&ray->vDir,
			mat
		);

		D3DXVec3Normalize(&ray->vDir, &ray->vDir);
	}

	template<typename T>
	void	Safe_Delete(T& Pointer)
	{
		if (nullptr != Pointer)
		{
			delete Pointer;
			Pointer = nullptr;
		}
	}

	template<typename T>
	void	Safe_Delete_Array(T& Pointer)
	{
		if (nullptr != Pointer)
		{
			delete [] Pointer;
			Pointer = nullptr;
		}
	}

	template<typename T>
	unsigned long Safe_Release(T& pInstance)
	{
		unsigned long		dwRefCnt = 0;

		if (nullptr != pInstance)
		{
			dwRefCnt = pInstance->Release();

			if (0 == dwRefCnt)
				pInstance = NULL;
		}

		return dwRefCnt;
	}


	// Functor
	class CTag_Finder
	{
	public:
		explicit CTag_Finder(const _tchar* pTag) : m_pTargetTag(pTag){}
		~CTag_Finder(void) {}

	public:
		template<typename T> 
		_bool		operator()(const T& pair)
		{
			if (0 == lstrcmpW(m_pTargetTag, pair.first))
				return true;
			
			return false;
		}

	private:
		const _tchar*		m_pTargetTag = nullptr;
	};

	class CDeleteObj
	{
	public:
		explicit CDeleteObj(void) {}
		~CDeleteObj(void) {}
	public: // operator
		template <typename T>
		void operator () (T& pInstance)
		{
			_ulong dwRefCnt = 0;

			dwRefCnt = pInstance->Release();

			if (0 == dwRefCnt)
				pInstance = nullptr;
		}
	};

	// 연관컨테이너 삭제용
	class CDeleteMap
	{
	public:
		explicit CDeleteMap(void) {}
		~CDeleteMap(void) {}
	public: // operator	
		template <typename T>
		void operator () (T& Pair)
		{
			_ulong dwRefCnt = 0;

			dwRefCnt = Pair.second->Release();

			if (0 == dwRefCnt)
				Pair.second = NULL;
		}
	};

}


#endif // Engine_Function_h__
