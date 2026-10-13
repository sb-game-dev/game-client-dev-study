#pragma once
#include "Client_Defines.h"
NS_BEGIN(Client)

class CSkyBox : public CGameObject
{
public:
	typedef struct tagSkyBoxDesc : public GAMEOBJECT_DESC
	{

	}SKYBOX_DESC;
private:
	CSkyBox(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	virtual ~CSkyBox() = default;

public:
	virtual		HRESULT		Initialize_Prototype() override;
	virtual		HRESULT		Initialize(void* pArg) override;
	virtual		void		Priority_Update(f32_t fTimeDelta)override;
	virtual		void		Update(f32_t fTimeDelta)override;
	virtual		void		Late_Update(f32_t fTimeDelta)override;
	virtual		HRESULT		Render() override;

public:
	static shared_ptr<CSkyBox> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
	virtual shared_ptr<CPrototype> Clone(void* pArg) override;

};

NS_END