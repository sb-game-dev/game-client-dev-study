#include "Converter.h"
#include <Windows.h>
CConverter::~CConverter()
{
	if (nullptr != m_pFile)
	{
		fclose(m_pFile);
		m_pFile = nullptr;
	}
}

bool CConverter::Initialize()
{
	return true;
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

	if (0 != _wfopen_s(&m_pFile, szWideBinPath, L"wb") || nullptr == m_pFile)
	{
		cout << "[Convert] 파일 열기 실패 : " << szBinPath << '\n';
		m_Importer.FreeScene();
		m_pScene = nullptr;
		return false;
	}
}

bool CConverter::Dump(const string& strBinPath)
{
	return false;
}

bool CConverter::Write_Header()
{
	return true;
}

bool CConverter::Write_Meshes()
{
	return true;
}

bool CConverter::Write_Materials()
{
	return true;
}

bool CConverter::To_TextureType(aiTextureType eAiType, TEXTURE_TYPE& eOutType)
{
	return true;
}

shared_ptr<CConverter> CConverter::Create()
{
	auto pInstance = shared_ptr<CConverter>(new CConverter());

	if (false == pInstance->Initialize())
	{
		cout << "Failed to Create : CConverter\n";
		return nullptr;
	}
	return pInstance;
}