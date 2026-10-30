#pragma once
#include "Camera.h"
#include "Client_Defines.h"
NS_BEGIN(Client)
class CMapTool_Cam :
    public CCamera
{
public:
    typedef struct tagMapToolCamDesc : public CCamera::CAMERA_DESC
    {
        f32_t			fSensor = {};
    }CAMERA_MAPTOOL_CAM_DESC;
private:
    CMapTool_Cam(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
    virtual ~CMapTool_Cam() = default;

public:
    virtual HRESULT Initialize_Prototype() override;
    virtual HRESULT Initialize(void* pArg) override;
    virtual void Priority_Update(f32_t fTimeDelta);
    virtual void Update(f32_t fTimeDelta);
    virtual void Late_Update(f32_t fTimeDelta);
    virtual HRESULT Render();

    virtual void        Set_SceneClicked(bool_t bClicked) { m_bSceneClicked = bClicked; }
private:
    bool_t      m_bSceneClicked = { false };
    f32_t	    m_fMouseSensor = {};
private:
    void        KeyInput(const f32_t fDeltaTime);

public:
    static shared_ptr<CMapTool_Cam> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
    shared_ptr<CPrototype> Clone(void* pArg) override;

};

NS_END