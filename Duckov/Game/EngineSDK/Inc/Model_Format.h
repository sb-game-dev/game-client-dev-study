#pragma once
#include <cstdint>
#include <DirectXMath.h>

namespace Engine::ModelFile
{
	constexpr char MAGIC[4] = { 'D','K','M','D' };
	constexpr uint32_t VERSION = 1;

	enum class TEXTURE_TYPE { DIFFUSE, NORMALS, SPECULAR, EMISSIVE, END };
	enum class MODEL_TYPE { NONANIM, ANIM };
	struct VERTEX_STATIC
	{
		DirectX::XMFLOAT3	vPosition;
		DirectX::XMFLOAT3	vNormal;
		DirectX::XMFLOAT3	vTangent;
		DirectX::XMFLOAT3	vBinormal;
		DirectX::XMFLOAT2	vTexcoord;
	};
	struct VERTEX_ANIM
	{
		DirectX::XMFLOAT3	vPosition;
		DirectX::XMFLOAT3	vNormal;
		DirectX::XMFLOAT3	vTangent;
		DirectX::XMFLOAT3	vBinormal;
		DirectX::XMFLOAT2	vTexcoord;
		DirectX::XMUINT4	vBlendIndex;
		DirectX::XMFLOAT4	vBlendWeight;
	};
	struct KEYFRAME
	{
		DirectX::XMFLOAT3		vScale;
		DirectX::XMFLOAT4		vRotation;
		DirectX::XMFLOAT3		vPosition;
		float					fTrackPosition;
	};

}