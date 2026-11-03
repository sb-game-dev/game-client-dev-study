#include "Loader_MapTool.h"
#include "Level_Loading_MapTool.h"
#include "Level_MapTool.h"
#include "BackGround.h"

CLevel_Loading_MapTool::CLevel_Loading_MapTool(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    :CLevel{ pDevice,pContext }
{
}

HRESULT CLevel_Loading_MapTool::Initialize(LEVEL eNextLevel)
{
    if (FAILED(__super::Initialize()))
        return E_FAIL;
    m_eNextLevelID = eNextLevel;

    /* 다음 레벨을 위한 자원 준비하는 과정*/
    m_pLoader = CLoader_MapTool::Create(m_pDevice, m_pContext, eNextLevel);
    if (nullptr == m_pLoader)
        return E_FAIL;

    return S_OK;
}

void CLevel_Loading_MapTool::Update(f32_t fDeltaTime)
{
    __super::Update(fDeltaTime);
    if (true == m_pLoader->isFinished() &&
        CGameInstance::Get().Key_Pressing(DIK_SPACE))
    {
        if (FAILED(CGameInstance::Get().Change_Level(ETOI(m_eNextLevelID), CLevel_MapTool::Create(m_pDevice, m_pContext))))
            return;
        return;
    }
}

HRESULT CLevel_Loading_MapTool::Render()
{
    if (FAILED(__super::Render()))
        return E_FAIL;
#ifdef _DEBUG
    m_pLoader->Draw_Debug();
#endif
    return S_OK;
}

shared_ptr<CLevel_Loading_MapTool> CLevel_Loading_MapTool::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, LEVEL eNextLevel)
{
    auto pInstance = shared_ptr<CLevel_Loading_MapTool>(new CLevel_Loading_MapTool(pDevice, pContext));

    if (FAILED(pInstance->Initialize(eNextLevel)))
    {
        MSG_BOX("Failed to Created : CLevel_Loading");
        pInstance.reset();
    }

    return pInstance;
}