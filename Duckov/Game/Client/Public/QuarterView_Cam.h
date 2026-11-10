#pragma once
#include "Camera.h"
#include "Client_Defines.h"
NS_BEGIN(Client)
class CQuarterView_Cam :
    public CCamera
{
public:
    typedef struct tagCameraQuaterDesc : public CCamera::CAMERA_DESC
    {
    }CAMERA_QUATER_DESC;
private:
    CQuarterView_Cam(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
    virtual ~CQuarterView_Cam();

public:
    virtual HRESULT Initialize_Prototype() override;
    virtual HRESULT Initialize(void* pArg) override;
    virtual void Priority_Update(f32_t fTimeDelta);
    virtual void Update(f32_t fTimeDelta);
    virtual void Late_Update(f32_t fTimeDelta);
    virtual HRESULT Render();

    void                AddShakeTime(f32_t fDeltaTime) { m_fShakeTime += fDeltaTime; }
private:
    weak_ptr<class CPlayer>         m_pPlayer;
    weak_ptr<class CClient_Mouse>   m_pClientMouse;
    f32_t                           m_fShakeTime = {};
    f32_t                           m_fShakeDistance = { 1.f };
    float3_t                        m_vShakeOffset = {};
    float4_t                        m_vAt = {}; 
    float4_t                        m_vOffset = { 12.9f, 36.9f, -22.4f, 0.f };

private:
    void                Shake(f32_t fDeltaTime);
public:
    static shared_ptr<CQuarterView_Cam> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
    shared_ptr<CPrototype> Clone(void* pArg) override;

};

NS_END