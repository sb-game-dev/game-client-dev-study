#pragma once
#include "Camera.h"
#include "Client_Defines.h"
NS_BEGIN(Client)
class COrthographic_Cam :
    public CCamera
{
private:
    COrthographic_Cam(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
    virtual ~COrthographic_Cam();

public:
    virtual HRESULT     Initialize() override;
    virtual void        Update(f32_t fDeltaTime) override;
    virtual void        Late_Update(f32_t fDeltaTime) override;

public:
    static shared_ptr<COrthographic_Cam> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);

};

NS_END