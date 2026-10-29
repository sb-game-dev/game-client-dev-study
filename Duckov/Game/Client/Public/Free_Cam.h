#pragma once
#include "Camera.h"
#include "Client_Defines.h"
NS_BEGIN(Client)
class CFree_Cam :
    public CCamera
{
private:
    CFree_Cam(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
    virtual ~CFree_Cam() = default;

public:
    virtual HRESULT     Initialize() override;
    virtual void        Update(f32_t fDeltaTime) override;
    virtual void        Late_Update(f32_t fDeltaTime) override;

private:
    bool_t  m_bFix = { true };
    f32_t   m_fMoveSpeed = { 10.f };
private:
    void    KeyInput(const f32_t fDeltaTime);
    void    Mouse_Move();
    void    Mouse_Fix();

public:
    static shared_ptr<CFree_Cam> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);

};

NS_END