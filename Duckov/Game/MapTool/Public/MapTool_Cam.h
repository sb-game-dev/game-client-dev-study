#pragma once
#include "Camera.h"
#include "MapTool_Defines.h"
NS_BEGIN(MapTool)
class CMapTool_Cam :
    public CCamera
{
private:
    CMapTool_Cam(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
    virtual ~CMapTool_Cam() = default;

public:
    virtual HRESULT     Initialize() override;
    virtual void        Update(f32_t fDeltaTime) override;
    virtual void        Late_Update(f32_t fDeltaTime) override;

    virtual void        Set_SceneClicked(bool_t bClicked) { m_bSceneClicked = bClicked; }

private:
    f32_t       m_fMoveSpeed    = { 10.f };
    bool_t      m_bSceneClicked = { false };

private:
    void        KeyInput(const f32_t fDeltaTime);
    void        Mouse_Move(); 

public:
    static shared_ptr<CMapTool_Cam> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);

};

NS_END