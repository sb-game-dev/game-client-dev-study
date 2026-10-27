#pragma once
#include "Client_Defines.h"
#include "GameObject.h"

NS_BEGIN(Client)

class CScope : public CGameObject
{
public:
	typedef struct tagScopeDesc : public CGameObject::GAMEOBJECT_DESC
	{

	}Scope_DESC;
private:
	CScope(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	virtual ~CScope() = default;

public:
	virtual		HRESULT		Initialize_Prototype() override;
	virtual		HRESULT		Initialize(void* pArg) override;
	virtual		void		Priority_Update(f32_t fTimeDelta)override;
	virtual		void		Update(f32_t fTimeDelta)override;
	virtual		void		Late_Update(f32_t fTimeDelta)override;
	virtual		HRESULT		Render() override;

private:
	shared_ptr<CVIBuffer_Rect>		m_pBufferCom = { nullptr };
	shared_ptr<CVertexShader>		m_pVS = { nullptr };
	shared_ptr<CPixelShader>		m_pPS = { nullptr };
	shared_ptr<CConstantBuffer>		m_pCB = { nullptr };
	shared_ptr<CConstantBuffer> 	m_pCBMouse = { nullptr };

	CB_PER_OBJECT					m_tCBData = {};
	CB_MOUSEINFO					m_tCBMouseData = {};
private:
	HRESULT			Ready_Components();
	HRESULT			Ready_ConstantBuffer();
	HRESULT			Update_ConstantBuffer();

	virtual			HRESULT Bind_Shader(shared_ptr<CVertexShader> pVS = nullptr, shared_ptr<CPixelShader> pPS = nullptr);
	virtual			HRESULT Bind_ShaderResources(const matrix_t& matWorld = XMMatrixIdentity());

public:
	static shared_ptr<CScope> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
	virtual shared_ptr<CPrototype> Clone(void* pArg) override;

};

NS_END