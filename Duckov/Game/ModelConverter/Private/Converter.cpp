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
	m_BoneNames.clear();
	uint32_t	iFlag = { aiProcess_ConvertToLeftHanded | aiProcessPreset_TargetRealtime_Fast };
	if (MODEL_TYPE::NONANIM == m_eType)
		iFlag |= aiProcess_PreTransformVertices;
	else
		iFlag |= aiProcess_LimitBoneWeights;

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

	bool	bSuccess = { false };
	// 파일 쓰기
	if (eType == MODEL_TYPE::NONANIM)
		bSuccess = Write_Header() && Write_Meshes() && Write_Materials();
	else
		bSuccess = Write_Header() && Write_Bone() && Write_Meshes() && Write_Materials() && Write_Animation();

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

		// 애니메이션 유무에 따라 분기
		bool bOk = (MODEL_TYPE::NONANIM == m_eType) ? Write_Vertices_Static(pAiMesh) : Write_Vertices_Anim(pAiMesh);
		if (false == bOk)
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
		if (m_eType == MODEL_TYPE::NONANIM)
			continue;
		uint32_t iNumBones = pAiMesh->mNumBones;
		fwrite(&iNumBones, sizeof(uint32_t), 1, m_pFile);
		for (uint32_t j = 0; j < iNumBones; ++j)
		{
			int32_t iBoneIndex = Get_BoneIndex(pAiMesh->mBones[j]->mName.C_Str());
			fwrite(&iBoneIndex, sizeof(int32_t), 1, m_pFile);

			aiMatrix4x4 OffsetMatrix = pAiMesh->mBones[j]->mOffsetMatrix;
			fwrite(&OffsetMatrix, sizeof(OffsetMatrix), 1, m_pFile);
		}

	}
	return true;
}

bool CConverter::Write_Vertices_Static(const aiMesh* pAiMesh)
{
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
	return true;
}

bool CConverter::Write_Vertices_Anim(const aiMesh* pAiMesh)
{
	// Engine에서의 CMesh DATA중 정점 정보 채우기(머티리얼의 인덱스, 정점 하나의 크기, 정점의 개수)
	uint32_t	iMaterialIndex = pAiMesh->mMaterialIndex;
	uint32_t	iVertexStride = sizeof(VERTEX_ANIM);
	uint32_t	iNumVertices = pAiMesh->mNumVertices;

	// 정점 DATA 쓰기
	if (1 != fwrite(&iMaterialIndex, sizeof(uint32_t), 1, m_pFile) ||
		1 != fwrite(&iVertexStride, sizeof(uint32_t), 1, m_pFile) ||
		1 != fwrite(&iNumVertices, sizeof(uint32_t), 1, m_pFile))
		return false;

	// Ready_Meshes_For_NonAnim + PreTransformMatirx는 bin파일을 읽는 쪽에서 수행
	vector<VERTEX_ANIM>	Vertices(iNumVertices);
	for (uint32_t j = 0; j < iNumVertices; ++j)
	{
		memcpy(&Vertices[j].vPosition, &pAiMesh->mVertices[j], sizeof(DirectX::XMFLOAT3));
		memcpy(&Vertices[j].vNormal, &pAiMesh->mNormals[j], sizeof(DirectX::XMFLOAT3));
		memcpy(&Vertices[j].vTangent, &pAiMesh->mTangents[j], sizeof(DirectX::XMFLOAT3));
		memcpy(&Vertices[j].vBinormal, &pAiMesh->mBitangents[j], sizeof(DirectX::XMFLOAT3));
		memcpy(&Vertices[j].vTexcoord, &pAiMesh->mTextureCoords[0][j], sizeof(DirectX::XMFLOAT2));
	}

	for (uint32_t j = 0; j < pAiMesh->mNumBones; ++j)       // j = 이 메시 안에서 몇 번째 뼈인지
	{
		const aiBone* pBone = pAiMesh->mBones[j];
		for (uint32_t k = 0; k < pBone->mNumWeights; ++k)
		{
			VERTEX_ANIM& v = Vertices[pBone->mWeights[k].mVertexId];
			float w = pBone->mWeights[k].mWeight;
			if (0.f == v.vBlendWeight.x) { v.vBlendIndex.x = j; v.vBlendWeight.x = w; }
			else if (0.f == v.vBlendWeight.y) { v.vBlendIndex.y = j; v.vBlendWeight.y = w; }
			else if (0.f == v.vBlendWeight.z) { v.vBlendIndex.z = j; v.vBlendWeight.z = w; }
			else if (0.f == v.vBlendWeight.w) { v.vBlendIndex.w = j; v.vBlendWeight.w = w; }
		}
	}

	// 정점 정보(VERTEX_ANIM) 쓰기
	if (iNumVertices != fwrite(Vertices.data(), sizeof(VERTEX_ANIM), iNumVertices, m_pFile))
		return false;
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

bool CConverter::Write_Bone()
{
	uint32_t iNumBones = Count_Nodes(m_pScene->mRootNode);
	if (1 != fwrite(&iNumBones, sizeof(uint32_t), 1, m_pFile))
		return false;

	return Write_Bone(m_pScene->mRootNode, -1);
}

bool CConverter::Write_Bone(const aiNode* pAINode, int32_t iParentIndex)
{
	uint32_t	iNameLength = pAINode->mName.length;
	
	fwrite(&iNameLength, sizeof(uint32_t), 1, m_pFile);
	if (iNameLength != fwrite(pAINode->mName.C_Str(), sizeof(char), iNameLength, m_pFile))
		return false;

	int32_t iMyIndex = static_cast<int32_t>(m_BoneNames.size());
	m_BoneNames.push_back(pAINode->mName.C_Str());

	int32_t iPIndex = iParentIndex;
	if (1 != fwrite(&iPIndex, sizeof(int32_t), 1, m_pFile))
		return false;
	fwrite(&pAINode->mTransformation, sizeof(aiMatrix4x4), 1, m_pFile);

	for (uint32_t i = 0; i < pAINode->mNumChildren; ++i)
	{
		Write_Bone(pAINode->mChildren[i], iMyIndex);
	}

	return true;
}

uint32_t CConverter::Count_Nodes(const aiNode* pAINode)
{
	uint32_t iCount = 1;
	for (uint32_t i = 0; i < pAINode->mNumChildren; ++i)
		iCount += Count_Nodes(pAINode->mChildren[i]);
	return iCount;
}
bool CConverter::Write_Animation()
{
	auto iNumAnimation = m_pScene->mNumAnimations;
	fwrite(&iNumAnimation, sizeof(uint32_t), 1, m_pFile);
	for (uint32_t i = 0; i < iNumAnimation; ++i)
	{
		auto pAnimations = m_pScene->mAnimations[i];
		uint32_t iLength = pAnimations->mName.length;
		fwrite(&iLength, sizeof(uint32_t), 1, m_pFile);
		fwrite(pAnimations->mName.C_Str(), sizeof(char), iLength, m_pFile);

		float fDuration = (float)pAnimations->mDuration;
		fwrite(&fDuration, sizeof(float), 1, m_pFile);

		float fTickPerSecond = (float)pAnimations->mTicksPerSecond;
		fwrite(&fTickPerSecond, sizeof(float), 1, m_pFile);
		
		uint32_t iNumChannels = pAnimations->mNumChannels;
		fwrite(&iNumChannels, sizeof(uint32_t), 1, m_pFile);

		for (uint32_t j = 0; j < iNumChannels; ++j)
		{
			auto pAIChannel = pAnimations->mChannels[j];
			int32_t iBoneIndex = Get_BoneIndex(pAIChannel->mNodeName.C_Str());
			fwrite(&iBoneIndex, sizeof(int32_t), 1, m_pFile);

			uint32_t iNumKeyFrames = max(pAIChannel->mNumScalingKeys, pAIChannel->mNumRotationKeys);
			iNumKeyFrames = max(iNumKeyFrames, pAIChannel->mNumPositionKeys);

			fwrite(&iNumKeyFrames, sizeof(uint32_t), 1, m_pFile);
			
			vector<float> vScale, vRotation, vPosition;

			vScale.resize(3);
			vRotation.resize(4);
			vPosition.resize(3);
			for (uint32_t k = 0; k < iNumKeyFrames; ++k)
			{
				KEYFRAME tKeyFrame{};
				if (k < pAIChannel->mNumScalingKeys)
				{
					tKeyFrame.fTrackPosition = (float)pAIChannel->mScalingKeys[k].mTime;
					vScale[0] = pAIChannel->mScalingKeys[k].mValue.x;
					vScale[1] = pAIChannel->mScalingKeys[k].mValue.y;
					vScale[2] = pAIChannel->mScalingKeys[k].mValue.z;

				}
				if (k < pAIChannel->mNumRotationKeys)
				{
					tKeyFrame.fTrackPosition = (float)pAIChannel->mRotationKeys[k].mTime;
					vRotation[0] = pAIChannel->mRotationKeys[k].mValue.x;
					vRotation[1] = pAIChannel->mRotationKeys[k].mValue.y;
					vRotation[2] = pAIChannel->mRotationKeys[k].mValue.z;
					vRotation[3] = pAIChannel->mRotationKeys[k].mValue.w;
				}
				if (k < pAIChannel->mNumPositionKeys)
				{
					tKeyFrame.fTrackPosition = (float)pAIChannel->mPositionKeys[k].mTime;
					vPosition[0] = pAIChannel->mPositionKeys[k].mValue.x;
					vPosition[1] = pAIChannel->mPositionKeys[k].mValue.y;
					vPosition[2] = pAIChannel->mPositionKeys[k].mValue.z;
				}
				tKeyFrame.vScale.x = vScale[0];
				tKeyFrame.vScale.y = vScale[1];
				tKeyFrame.vScale.z = vScale[2];

				tKeyFrame.vRotation.x = vRotation[0];
				tKeyFrame.vRotation.y = vRotation[1];
				tKeyFrame.vRotation.z = vRotation[2];
				tKeyFrame.vRotation.w = vRotation[3];

				tKeyFrame.vPosition.x = vPosition[0];
				tKeyFrame.vPosition.y = vPosition[1];
				tKeyFrame.vPosition.z = vPosition[2];

				fwrite(&tKeyFrame, sizeof(KEYFRAME), 1, m_pFile);
			}
		}
	}
	return true;
}

int32_t CConverter::Get_BoneIndex(const char* pBoneName)
{
	for (size_t i = 0; i < m_BoneNames.size(); ++i)
	{
		if (pBoneName == m_BoneNames[i])
			return static_cast<int32_t>(i);
	}
	return -1;
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