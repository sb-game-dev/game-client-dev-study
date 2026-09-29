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
		vector<UINT> Indices;
	}MESHDATA;

	typedef struct tagVtxTex
	{
		float3_t	vPosition;
		float3_t	vNormal;
		float2_t	vTex0;
		float2_t	vTex1;
	}VTXTEX;

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
		float		Range;

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

	typedef struct tagCBLight
	{
		PointLight	tPointLight;	// 80 바이트
		float3_t	vEyePosW;		// 12 바이트
		f32_t		fPad;			// 4  바이트
	}CB_LIGHT;

}

#endif // Engine_Struct_h__
