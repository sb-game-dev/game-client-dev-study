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
    virtual void        Late_Update(f32_t fDeltaTime) override;

    void                SetPlayer(shared_ptr<CGameObject> pPlayer) { m_pPlayer = pPlayer; }
    void                AddShakeTime(f32_t fDeltaTime) { m_fShakeTime += fDeltaTime; }
private:
    shared_ptr<CGameObject>     m_pPlayer = {nullptr};
    f32_t                       m_fShakeTime = {};
    f32_t                       m_fShakeDistance = { 1.f };
    float3_t                    m_vShakeOffset = {};
private:
    void                Shake(f32_t fDeltaTime);
public:
    static shared_ptr<CQuarterView_Cam> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);

};

NS_END