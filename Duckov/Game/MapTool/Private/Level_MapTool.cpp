#include "Level_MapTool.h"
#include "MapTool_Cam.h"
#include "SkyBox.h"
CLevel_MapTool::CLevel_MapTool(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    :CLevel{ pDevice,pContext }
{
}

HRESULT CLevel_MapTool::Initialize()
{
    if (FAILED(__super::Initialize()))
        return E_FAIL;

    SetWindowText(g_hWnd, L"MapTool_Level");
    Ready_Layer_BackGround(TEXT("Layer_BackGround"));
    Ready_Layer_GameObject(TEXT("Layer_GameObject"));

    return S_OK;
}

void CLevel_MapTool::Update(f32_t fDeltaTime)
{
    __super::Update(fDeltaTime);
}

HRESULT CLevel_MapTool::Render()
{
    if (FAILED(__super::Render()))
        return E_FAIL;
    return S_OK;
}
HRESULT CLevel_MapTool::Ready_Layer_BackGround(const tchar_t* pLayerTag)
{
    //-----------------원형-----------------
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::MAPTOOL), Proto::Texture_SkyBox,
        CTexture::Create(m_pDevice, m_pContext, TEXT("../../../Resource/Ex/proc_preview.png"), 1))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::MAPTOOL), Proto::Obj_SkyBox,
        CSkyBox::Create(m_pDevice, m_pContext))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::MAPTOOL), Proto::VS_VTXTEX,
        CVertexShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Shader_VtxTex.hlsl", VTXNORM::Elements, VTXNORM::iNumElements, "VS_MAIN"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::MAPTOOL), Proto::PS_VTXTEX_SKYBOX,
        CPixelShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Shader_VtxTex.hlsl", "PS_MAIN_SKY"))))
        return E_FAIL;

    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::MAPTOOL), Proto::VIBuffer_SkyBox,
        CVIBuffer_SkyBox::Create(m_pDevice, m_pContext))))
        return E_FAIL;
    //-----------------사본-----------------
    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::MAPTOOL), Proto::Obj_SkyBox,
        ETOUI(LEVEL::MAPTOOL), Layer::BackGround, GO::SkyBox)))
        return E_FAIL;

    return S_OK;
}

HRESULT CLevel_MapTool::Ready_Layer_GameObject(const tchar_t* pLayerTag)
{
    auto pCamera = CMapTool_Cam::Create(m_pDevice, m_pContext);
    CGameInstance::Get().Add_Camera(CAMERA::FREE, pCamera);
    CGameInstance::Get().Set_MainCamera(CAMERA::FREE);


    return S_OK;
}

shared_ptr<CLevel_MapTool> CLevel_MapTool::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto pInstance = shared_ptr<CLevel_MapTool>(new CLevel_MapTool(pDevice, pContext));
    if (FAILED(pInstance->Initialize()))
        pInstance.reset();

    return pInstance;
}