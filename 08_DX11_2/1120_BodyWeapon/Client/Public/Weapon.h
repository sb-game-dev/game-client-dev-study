#pragma once

#include "Client_Defines.h"
#include "PartObject.h"

NS_BEGIN(Engine)
class CShader;
class CModel;
NS_END


NS_BEGIN(Client)

class CWeapon final : public CPartObject
{
public:
	typedef struct tagWeaponDesc : public CPartObject::PARTOBJECT_DESC
	{
		const float4x4_t* pSocketMatrix = { nullptr };
		const uint32_t* pParentState = { nullptr };
	}WEAPON_DESC;
private:
	CWeapon(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	virtual ~CWeapon() = default;

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
	const uint32_t* m_pParentState = { nullptr };
	const float4x4_t* m_pSocketMatrix = { nullptr };
	
private:
	HRESULT Ready_Components();
	HRESULT Bind_Shader();
	HRESULT Bind_ShaderResources();



public:
	static shared_ptr<CWeapon> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
	virtual shared_ptr<CPrototype> Clone(void* pArg) override;
};

NS_END