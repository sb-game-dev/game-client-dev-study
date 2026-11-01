#include "Level_MapTool.h"
#include "MapTool_Cam.h"
#include "SkyBox.h"
#include "StaticProp.h"
CLevel_MapTool::CLevel_MapTool(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
    :CLevel{ pDevice,pContext }
{
}

HRESULT CLevel_MapTool::Initialize()
{
    if (FAILED(__super::Initialize()))
        return E_FAIL;

    SetWindowText(g_hWnd, L"MapTool_Level");

    if (FAILED(Ready_Layer_BackGround(TEXT("Layer_BackGround"))))
        return E_FAIL;
    if (FAILED(Ready_Layer_GameObject(TEXT("Layer_GameObject"))))
        return E_FAIL;
    if (FAILED(Ready_Layer_Map(TEXT("Layer_Map"))))
        return E_FAIL;

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
    // 원형
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
    
    // 사본
    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::MAPTOOL), Proto::Obj_SkyBox,
        ETOUI(LEVEL::MAPTOOL), Layer::BackGround, GO::SkyBox)))
        return E_FAIL;

    return S_OK;
}

HRESULT CLevel_MapTool::Ready_Layer_GameObject(const tchar_t* pLayerTag)
{
    // 카메라 원형
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::MAPTOOL), Proto::Obj_MapToolCam,
        CMapTool_Cam::Create(m_pDevice, m_pContext))))
        return E_FAIL;

    // 카메라 사본
    CMapTool_Cam::CAMERA_MAPTOOL_CAM_DESC         CameraDesc{};
    CameraDesc.fDegreeRotPerSec = 180.f;
    CameraDesc.fSpeedPerSec = 20.f;
    CameraDesc.vEye = float4_t(0.f, 0.f, -1.f, 1.f);
    CameraDesc.vAt = float4_t(0.f, 0.f, 0.f, 1.f);
    CameraDesc.fFovy = 60.f;
    CameraDesc.fNear = 0.1f;
    CameraDesc.fFar = 1000.f;
    CameraDesc.fSensor = 0.05f;

    if (FAILED(CGameInstance::Get().Add_GameObject(ETOUI(LEVEL::MAPTOOL), Proto::Obj_MapToolCam,
        ETOUI(LEVEL::MAPTOOL), pLayerTag, GO::MapToolCam, &CameraDesc)))
        return E_FAIL;

    auto pMapToolCam = dynamic_pointer_cast<CMapTool_Cam>(CGameInstance::Get().Find_GameObject(ETOUI(LEVEL::MAPTOOL), pLayerTag, GO::MapToolCam));
    CGameInstance::Get().Add_Camera(CAMERA::FREE, pMapToolCam);
    CGameInstance::Get().Set_MainCamera(CAMERA::FREE);

    return S_OK;
}

HRESULT CLevel_MapTool::Ready_Layer_Map(const tchar_t* pLayerTag)
{
// 원본
    // 픽셀 셰이더 (VS_VTXTEX는 Ready_Layer_BackGround에서 이미 등록됨)
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::MAPTOOL), Proto::PS_VTXTEX_NOLIGHT,
        CPixelShader::Create(m_pDevice, m_pContext, L"../Bin/Shader/Shader_VtxTex.hlsl", "PS_MAIN_NOLIGHT"))))
        return E_FAIL;

    // Obj_StaticProp 객체 원본
    if (FAILED(CGameInstance::Get().Add_Prototype(ETOUI(LEVEL::MAPTOOL), Proto::Obj_StaticProp,
        CStaticProp::Create(m_pDevice, m_pContext))))
        return E_FAIL;   
    return S_OK;
}

shared_ptr<CLevel_MapTool> CLevel_MapTool::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
    auto pInstance = shared_ptr<CLevel_MapTool>(new CLevel_MapTool(pDevice, pContext));
    if (FAILED(pInstance->Initialize()))
        pInstance.reset();

    return pInstance;
}