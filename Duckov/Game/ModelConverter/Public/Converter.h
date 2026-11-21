#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <cstdio>

#include "Assimp/Importer.hpp"
#include "Assimp/scene.h"
#include "Assimp/postprocess.h"
#include "Model_Format.h"
using namespace std;
using namespace Engine::ModelFile;

class CConverter
{
private:
	CConverter() = default;
public:
	~CConverter();

public:
	bool	Initialize();
	bool	Convert(const string& strFbxPath, MODEL_TYPE eType);

private:
	Assimp::Importer				m_Importer;
	const aiScene*					m_pScene = { nullptr };
	FILE*							m_pFile = { nullptr };
	MODEL_TYPE	m_eType = { MODEL_TYPE::NONANIM };

private:
	bool	Write_Header();
	bool	Write_Meshes();
	bool	Write_Vertices_Static(const aiMesh* pAiMesh);
	bool	Write_Vertices_Anim(const aiMesh* pAiMesh);
	bool	Write_Materials();

	bool	Write_Bone();
	bool	Write_Bone(const aiNode* pAINode, int32_t iParentIndex);

	static uint32_t	Count_Nodes(const aiNode* pAINode);
	bool	Write_Animation();

	int32_t Get_BoneIndex(const char* pBoneName);
	vector<string> m_BoneNames;

	static bool	To_TextureType(aiTextureType eAiType, TEXTURE_TYPE& eOutType);

public:
	static shared_ptr<CConverter> Create();
};

