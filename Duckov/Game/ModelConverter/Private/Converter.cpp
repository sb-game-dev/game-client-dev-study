#include <Windows.h>
#include "Converter.h"
#include <vector>
CConverter::~CConverter()
{
	if (nullptr != m_pFile)
	{
		fclose(m_pFile);
		m_pFile = nullptr;
	}
}

bool CConverter::Convert(const string& strFbxPath, MODEL_TYPE eType)
{
	m_eType = eType; 
	uint32_t	iFlag = { aiProcess_ConvertToLeftHanded | aiProcessPreset_TargetRealtime_Fast };
	if (MODEL_TYPE::NONANIM == m_eType)
		iFlag |= aiProcess_PreTransformVertices;
	m_pScene = m_Importer.ReadFile(strFbxPath, iFlag);
	if (nullptr == m_pScene)
	{
		cout << "[Convert] 읽기 실패 : " << strFbxPath << '\n';
		cout << "          " << m_Importer.GetErrorString() << '\n';
		return false;
	}
	// 경로 만들기(파일 확장자는 .bin으로 고정)
	char	szDrive[MAX_PATH] = {};
	char	szDir[MAX_PATH] = {};
	char	szFileName[MAX_PATH] = {};

	if (0 != _splitpath_s(strFbxPath.c_str(), szDrive, MAX_PATH, szDir, MAX_PATH, szFileName, MAX_PATH, nullptr, 0))
	{
		cout << "[Convert] 경로 분해 실패 : " << strFbxPath << '\n';
		m_Importer.FreeScene();
		m_pScene = nullptr;
		return false;
	}

	char	szBinPath[MAX_PATH] = {};
	strcpy_s(szBinPath, szDrive);
	strcat_s(szBinPath, szDir);
	strcat_s(szBinPath, szFileName);
	strcat_s(szBinPath, ".bin");

	wchar_t	szWideBinPath[MAX_PATH] = {};
	MultiByteToWideChar(CP_ACP, 0, szBinPath, -1, szWideBinPath, MAX_PATH);
	
	// 파일 개방
	if (0 != _wfopen_s(&m_pFile, szWideBinPath, L"wb") || nullptr == m_pFile)
	{
		cout << "[Convert] 파일 열기 실패 : " << szBinPath << '\n';
		m_Importer.FreeScene();
		m_pScene = nullptr;
		return false;
	}

	// 파일 쓰기
	bool	bSuccess = Write_Header() && Write_Meshes() && Write_Materials();

	long	iFileSize = ftell(m_pFile);

	fclose(m_pFile);
	m_pFile = nullptr;

	m_Importer.FreeScene();
	m_pScene = nullptr;

	if (false == bSuccess)
	{
		_wremove(szWideBinPath);
		cout << "[Convert] 쓰기 실패, 파일 삭제 : " << szBinPath << '\n';
		return false;
	}
	cout << "[Convert] 완료 : " << szBinPath << " (" << iFileSize << " bytes)\n";
	return true;
}

bool CConverter::Write_Header()
{
	if( 1 != fwrite(MAGIC,sizeof(MAGIC),1,m_pFile))
		return false;
	if (1 != fwrite(&VERSION, sizeof(VERSION), 1, m_pFile))
		return false;
	uint32_t iType = static_cast<uint32_t>(m_eType);
	if (1 != fwrite(&iType, sizeof(iType), 1, m_pFile))
		return false;
	return true;
}

bool CConverter::Write_Meshes()
{
	// 메시가 몇 개 있는지 확인
	uint32_t iNumMeshes = m_pScene->mNumMeshes;
	if (1 != fwrite(&iNumMeshes, sizeof(uint32_t), 1, m_pFile))
		return false;
	for (uint32_t i = 0; i < iNumMeshes; ++i)
	{
		// i번째 메시 꺼내기
		const aiMesh* pAiMesh = m_pScene->mMeshes[i];

		// Engine에서의 CMesh DATA중 정점 정보 채우기(머티리얼의 인덱스, 정점 하나의 크기, 정점의 개수)
		uint32_t	iMaterialIndex = pAiMesh->mMaterialIndex;
		uint32_t	iVertexStride = sizeof(VERTEX_STATIC);
		uint32_t	iNumVertices = pAiMesh->mNumVertices;

		// 정점 DATA 쓰기
		if (1 != fwrite(&iMaterialIndex, sizeof(uint32_t), 1, m_pFile) ||
			1 != fwrite(&iVertexStride, sizeof(uint32_t), 1, m_pFile) ||
			1 != fwrite(&iNumVertices, sizeof(uint32_t), 1, m_pFile))
			return false;

		// Ready_Meshes_For_NonAnim + PreTransformMatirx는 bin파일을 읽는 쪽에서 수행
		vector<VERTEX_STATIC>	Vertices(iNumVertices);
		for (uint32_t j = 0; j < iNumVertices; ++j)
		{
			memcpy(&Vertices[j].vPosition, &pAiMesh->mVertices[j], sizeof(DirectX::XMFLOAT3));
			memcpy(&Vertices[j].vNormal, &pAiMesh->mNormals[j], sizeof(DirectX::XMFLOAT3));
			memcpy(&Vertices[j].vTangent, &pAiMesh->mTangents[j], sizeof(DirectX::XMFLOAT3));
			memcpy(&Vertices[j].vBinormal, &pAiMesh->mBitangents[j], sizeof(DirectX::XMFLOAT3));
			memcpy(&Vertices[j].vTexcoord, &pAiMesh->mTextureCoords[0][j], sizeof(DirectX::XMFLOAT2));
		}
		// 정점 정보(VERTEX_STATIC) 쓰기
		if (iNumVertices != fwrite(Vertices.data(), sizeof(VERTEX_STATIC), iNumVertices, m_pFile))
			return false;

		// 인덱스 DATA 채우기 (인덱스의 개수)
		uint32_t iNumIndices = pAiMesh->mNumFaces * 3;
		
		// 인덱스 DATA 쓰기
		if (1 != fwrite(&iNumIndices, sizeof(uint32_t), 1, m_pFile))
			return false;

		// 인덱스 정보 채우기
		shared_ptr<uint32_t[]>  pIndices = make_shared<uint32_t[]>(iNumIndices);
		uint32_t iIndex = {};
		for (uint32_t j = 0; j < pAiMesh->mNumFaces; ++j)
		{
			pIndices[iIndex++] = pAiMesh->mFaces[j].mIndices[0];
			pIndices[iIndex++] = pAiMesh->mFaces[j].mIndices[1];
			pIndices[iIndex++] = pAiMesh->mFaces[j].mIndices[2];
		}

		// 인덱스 정보 쓰기
		if (iNumIndices != fwrite(pIndices.get(), sizeof(uint32_t), iNumIndices, m_pFile))
			return false;

		cout << "[Write_Meshes] " << i << "번 : 정점 " << iNumVertices << ", 인덱스 " << iNumIndices << '\n';
	}
	return true;
}

bool CConverter::Write_Materials()
{
	// 머티리얼 개수 확인 + 파일 쓰기
	uint32_t	iNumMaterials = m_pScene->mNumMaterials;
	if (1 != fwrite(&iNumMaterials, sizeof(uint32_t), 1, m_pFile))
		return false;

	// 머티리얼 개수만큼 반복
	for (uint32_t i = 0; i < iNumMaterials; ++i)
	{
		const aiMaterial* pAiMaterial = m_pScene->mMaterials[i];

		// 머티리얼 하나에 들어있는 diffuse, normal, specular, emissive만 파일에 쓰기
		vector<pair<TEXTURE_TYPE, string>>	Textures;

		// 머티리얼
		for (uint32_t j = 0; j < AI_TEXTURE_TYPE_MAX; ++j)
		{
			aiTextureType eAiType = static_cast<aiTextureType>(j);
			TEXTURE_TYPE	eType = {};
			// 머티리얼 하나에 들어있는 diffuse, normal, specular, emissive만 파일에 쓰기
			if (false == To_TextureType(eAiType, eType))
				continue;
			uint32_t iNumTextures = pAiMaterial->GetTextureCount(eAiType);
			for (uint32_t k = 0; k < iNumTextures; ++k)
			{
				aiString strTexturePath = {};
				if (AI_SUCCESS != pAiMaterial->GetTexture(eAiType, k, &strTexturePath))
				{
					cout << "[Write_Materials] " << i << "번 머티리얼 텍스처 경로 읽기 실패\n";
					return false;
				}

				// 파일 이름 + 확장자만 꺼내기 (경로는 엔진에서 bin파일을 읽을 때 사용)
				char	szFileName[MAX_PATH] = {};
				char	szExt[MAX_PATH] = {};

				// 파일이름 + 확장자 추출
				_splitpath_s(strTexturePath.C_Str(), nullptr, 0, nullptr, 0, szFileName, MAX_PATH, szExt, MAX_PATH);

				Textures.push_back({ eType, string(szFileName) + szExt });
			}
		}
		// 머티리얼 하나에 들어있는 텍스처 개수
		uint32_t	iNumTextures = static_cast<uint32_t>(Textures.size());
		if (1 != fwrite(&iNumTextures, sizeof(uint32_t), 1, m_pFile))
			return false;

		// 각 텍스처마다 파일 쓰기 -> 텍스처 종류(enum), 파일 이름 길이(uint32_t), 이름(string)
		for (const auto& Texture : Textures)
		{
			uint32_t	iType = static_cast<uint32_t>(Texture.first);
			uint32_t	iLength = static_cast<uint32_t>(Texture.second.size());

			if (1 != fwrite(&iType, sizeof(uint32_t), 1, m_pFile) ||
				1 != fwrite(&iLength, sizeof(uint32_t), 1, m_pFile) ||
				iLength != fwrite(Texture.second.data(), sizeof(char), iLength, m_pFile))
				return false;

			cout << "[Write_Materials] " << i << "번 : 종류 " << iType << ", " << Texture.second << '\n';
		}
	}
	return true;
}

bool CConverter::To_TextureType(aiTextureType eAiType, TEXTURE_TYPE& eOutType)
{
	switch (eAiType)
	{
	case aiTextureType_DIFFUSE:		
		eOutType = TEXTURE_TYPE::DIFFUSE;
		return true;
	case aiTextureType_NORMALS:		
		eOutType = TEXTURE_TYPE::NORMALS;
		return true;
	case aiTextureType_SPECULAR:	
		eOutType = TEXTURE_TYPE::SPECULAR;
		return true;
	case aiTextureType_EMISSIVE:	
		eOutType = TEXTURE_TYPE::EMISSIVE;
		return true;
	default:
		return false;
	}
}

shared_ptr<CConverter> CConverter::Create()
{
	auto pInstance = shared_ptr<CConverter>(new CConverter());
	return pInstance;
}