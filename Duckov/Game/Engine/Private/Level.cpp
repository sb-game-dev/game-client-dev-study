#include "Level.h"
#include "GameInstance.h"
#include "StaticProp.h"

CLevel::CLevel(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	:m_pDevice{pDevice}
	,m_pContext{pContext}
{
}


HRESULT CLevel::Initialize()
{
	return S_OK;
}
void CLevel::Update(f32_t fDeltaTime)
{

}

HRESULT	CLevel::Render()
{
	return S_OK;
}

HRESULT CLevel::Load_Scene(const wstring& strPath, uint32_t iLevelIndex, wstring_t strLayerTag)
{
    FILE* pFile;
    _wfopen_s(&pFile, strPath.c_str(), L"rb");

    uint32_t iNumObject = {};
    fread(&iNumObject, sizeof(uint32_t), 1, pFile);

    wstring_t strTag = {};
    for (uint32_t i = 0; i < iNumObject; ++i)
    {
        uint32_t iLength = {};
        fread(&iLength, sizeof(uint32_t), 1, pFile);

        CStaticProp::STATICPROP_DESC Desc = {};
        Desc.strPrototypeTag.resize(iLength);
        fread(Desc.strPrototypeTag.data(), sizeof(wchar_t), iLength, pFile);
        fread(&Desc.vPosition, sizeof(float3_t), 1, pFile);
        fread(&Desc.vQuaternion, sizeof(float4_t), 1, pFile);
        fread(&Desc.vScale, sizeof(float3_t), 1, pFile);

        uint32_t  iModelPathLength = {};
        fread(&iModelPathLength, sizeof(uint32_t), 1, pFile);
        Desc.strMeshPath.resize(iModelPathLength);
        fread(Desc.strMeshPath.data(), sizeof(wchar_t), iModelPathLength, pFile);

        Desc.iLevelIndex = iLevelIndex;
        Desc.bEditorMode = false;

        strTag = L"Prop_" + to_wstring(i);

        if (FAILED(CGameInstance::Get().Add_GameObject(iLevelIndex, Desc.strPrototypeTag,
            iLevelIndex, strLayerTag, strTag, &Desc)))
        {
            MSG_BOX("Create Failed");
            return E_FAIL;
        }
    }
    fclose(pFile);
    return S_OK;
}
