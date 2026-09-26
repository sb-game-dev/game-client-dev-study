#pragma once
#include "Camera.h"
#include "Client_Defines.h"
NS_BEGIN(Client)
class CQuarterView_Cam :
    public CCamera
{
private:
    CQuarterView_Cam(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
    virtual ~CQuarterView_Cam();

public:
    virtual HRESULT     Initialize() override;
    virtual void        Update(f32_t fDeltaTime) override;
    virtual void        LateUpdate(f32_t fDeltaTime) override;
    virtual HRESULT     Render() override;

    void                SetPlayer(shared_ptr<CGameObject> pPlayer) { m_pPlayer = pPlayer; }
private:
    shared_ptr<CGameObject>     m_pPlayer = {nullptr};

public:
    static shared_ptr<CQuarterView_Cam> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);

};

NS_END