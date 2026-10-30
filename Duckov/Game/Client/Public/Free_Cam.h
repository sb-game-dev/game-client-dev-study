#pragma once
#include "Camera.h"
#include "Client_Defines.h"
NS_BEGIN(Client)
class CFree_Cam :
    public CCamera
{
public:
    typedef struct tagCameraFreeDesc : public CCamera::CAMERA_DESC
    {
        f32_t			fSensor = {};
    }CAMERA_FREE_DESC;
private:
    CFree_Cam(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
    virtual ~CFree_Cam() = default;

public:
    virtual HRESULT Initialize_Prototype() override;
    virtual HRESULT Initialize(void* pArg) override;
    virtual void Priority_Update(f32_t fTimeDelta);
    virtual void Update(f32_t fTimeDelta);
    virtual void Late_Update(f32_t fTimeDelta);
    virtual HRESULT Render();

private:
    bool_t  m_bFix = { true };
    f32_t	m_fMouseSensor = {};
private:
    void    KeyInput(const f32_t fDeltaTime);
    void    Mouse_Move();
    void    Mouse_Fix();

public:
    static shared_ptr<CFree_Cam> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
    shared_ptr<CPrototype> Clone(void* pArg) override;

};

NS_END