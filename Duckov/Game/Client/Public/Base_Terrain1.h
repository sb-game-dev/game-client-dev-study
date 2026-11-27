#pragma once
#include "Client_Defines.h"
#include "GameObject.h"
NS_BEGIN(Client)
class CBase_Terrain1 : public CGameObject
{
private:
	CBase_Terrain1(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	~CBase_Terrain1() = default;

public:
	virtual HRESULT		Initialize_Prototype() override;
	virtual HRESULT		Initialize(void* pArg) override;
	virtual	void		Priority_Update(f32_t fDeltaTime) override;
	virtual	void		Update(f32_t fDeltaTime) override;
	virtual	void		Late_Update(f32_t fDeltaTime) override;
	virtual HRESULT		Render() override;

private:
	shared_ptr<CModel>				m_pModelCom = { nullptr };
	shared_ptr<CVertexShader>		m_pVSCom = { nullptr };
	shared_ptr<CPixelShader>		m_pPSCom = { nullptr };

private:
	HRESULT Ready_Components();
	HRESULT	Ready_ConstantBuffer();

	HRESULT Bind_Shader();
	HRESULT Bind_ShaderResources();

public:
	static shared_ptr<CBase_Terrain1> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
	shared_ptr<CPrototype> Clone(void* pArg) override;
};

NS_END