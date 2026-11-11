#pragma once
#include <cstdint>
#include <DirectXMath.h>

namespace Engine::ModelFile
{
	constexpr char MAGIC[4] = { 'D','K','M','D' };
	constexpr uint32_t VERSION = 1;

	enum class TEXTURE_TYPE : uint32_t	{ DIFFUSE,NORMALS,SPECULAR,EMISSIVE,END };

	struct VERTEX_STATIC
	{
		DirectX::XMFLOAT3	vPosition;
		DirectX::XMFLOAT3	vNormal;
		DirectX::XMFLOAT3	vTangent;
		DirectX::XMFLOAT3	vBinormal;
		DirectX::XMFLOAT2	vTexcoord;
	};

}