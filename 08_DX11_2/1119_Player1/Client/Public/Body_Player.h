#pragma once

#include "Client_Defines.h"
#include "PartObject.h"

NS_BEGIN(Engine)
class CShader;
class CModel;
NS_END


NS_BEGIN(Client)

class CBody_Player final : public CPartObject
{
public:
	typedef struct tagBodyDesc : public CPartObject::PARTOBJECT_DESC
	{
		
	}BODY_DESC;
private:
	CBody_Player(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	virtual ~CBody_Player() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Update(f32_t fTimeDelta) override;
	virtual void Update(f32_t fTimeDelta) override;
	virtual void Late_Update(f32_t fTimeDelta) override;
	virtual HRESULT Render() override;

private:
	
	shared_ptr<CShader>				m_pVSCom = { nullptr };
	shared_ptr<CShader>				m_pPSCom = { nullptr };
	shared_ptr<CModel>				m_pModelCom = { nullptr };

private:
	HRESULT Ready_Components();
	HRESULT Bind_Shader();
	HRESULT Bind_ShaderResources();



public:
	static shared_ptr<CBody_Player> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
	virtual shared_ptr<CPrototype> Clone(void* pArg) override;
};

NS_END