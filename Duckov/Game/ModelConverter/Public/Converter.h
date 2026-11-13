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
	bool	Write_Materials();

	static bool	To_TextureType(aiTextureType eAiType, TEXTURE_TYPE& eOutType);

public:
	static shared_ptr<CConverter> Create();
};

