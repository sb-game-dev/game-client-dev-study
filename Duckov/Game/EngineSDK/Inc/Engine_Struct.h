#ifndef Engine_Struct_h__
#define Engine_Struct_h__

#include "Engine_Typedef.h"

namespace Engine
{
	typedef struct tagEngineDesc
	{
		HWND			hWnd;
		WINMODE			eWinMode;
		uint32_t		iWinSizeX, iWinSizeY;
		uint32_t		iNumLevels;
	}ENGINE_DESC;

	// GPU가 사용하는 정점 정보
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

	typedef struct tagVtxNorm
	{
		float3_t	vPosition;
		float3_t	vNormal;

		static constexpr uint32_t iNumElements = 2;
		static constexpr D3D11_INPUT_ELEMENT_DESC Elements[iNumElements] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT,0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

	}VTXNORM;

	typedef struct tagCBPerObject
	{
		float4x4_t WorldMatrix;
	}CB_PER_OBJECT;

	typedef struct tagCBCamera
	{
		float4x4_t ViewMatrix;
		float4x4_t ProjMatrix;
		float3_t   vEye;
		f32_t	   fPad;

	}CB_CAMERA;

	// CPU가 사용하는 정점 정보
	typedef struct tagMeshVertex
	{
		tagMeshVertex() {};
		tagMeshVertex(const float3_t& p, const float3_t& n, const float3_t& t, const float2_t& uv)
			: vPosition(p), vNormal(n), vTangentU(t), TexC(uv) {
		}
		tagMeshVertex(
			float px, float py, float pz,
			float nx, float ny, float nz,
			float tx, float ty, float tz,
			float u, float v)
			: vPosition(px, py, pz), vNormal(nx, ny, nz),
			vTangentU(tx, ty, tz), TexC(u, v) {
		}
		float3_t vPosition;
		float3_t vNormal;
		float3_t vTangentU;
		float2_t TexC;
	}VERTEX;

	typedef struct tagMeshData
	{
		vector<VERTEX>	Vertices;
		vector<UINT>	Indices;
	}MESHDATA;

	struct DirectionalLight
	{
		DirectionalLight() { ZeroMemory(this, sizeof(*this)); }

		float4_t	Ambient;
		float4_t	Diffuse;
		float4_t	Specular;
		float3_t	Direction;
		f32_t		Pad;
	};

	struct PointLight
	{
		PointLight() { ZeroMemory(this, sizeof(*this)); }

		float4_t	Ambient;
		float4_t	Diffuse;
		float4_t	Specular;

		float3_t	Position;
		f32_t		Range;

		float3_t	Att;
		f32_t		Pad;
	};

	struct SpotLight
	{
		SpotLight() { ZeroMemory(this, sizeof(*this)); }

		float4_t	Ambient;
		float4_t	Diffuse;
		float4_t	Specular;

		float3_t	Position;
		f32_t		Range;

		float3_t	Direction;
		f32_t		Spot;

		float3_t	Att;
		f32_t		Pad;
	};

	typedef struct tagMaterial
	{
		tagMaterial() { ZeroMemory(this, sizeof(*this)); }

		float4_t	Ambient;
		float4_t	Diffuse;
		float4_t	Specular; // w = SpecPower
		float4_t	Reflect;
	}MATERIAL;


	typedef struct tagCBPerObjectLit
	{
		float4x4_t	mat_World;
		float4x4_t	mat_WorldInvTranspose;
		MATERIAL	tMaterial;
	}CB_PER_OBJECT_LIT;

	typedef struct tagCBPointLight
	{
		PointLight			tPointLight;	// 점 조명이 여러 개 인 경우 이 구조체를 배열로 선언
											// 이후 점 조명들을 하나로 모아서 배열의 값을 채워주는 메니저가 필요함
											// 셰이더 코드에서도 구조체를 배열로 선언한 뒤 PS에서 for문으로 순회하며 조명값 더하기
	}CB_POINTLIGHT;

	typedef struct tagCBSpotLight
	{
		SpotLight			tSpotLight;
	}CB_SPOTLIGHT;

}

#endif // Engine_Struct_h__
