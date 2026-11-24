#pragma once
#include "Client_Defines.h"
#include "GameObject.h"
NS_BEGIN(Client)
class CBullet : public CGameObject
{
public:
	typedef struct tagBulletDesc : public CGameObject::GAMEOBJECT_DESC
	{

	}BULLET_DESC;

private:
	CBullet(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	~CBullet() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Update(f32_t fDeltaTime) override;
	virtual void Update(f32_t fDeltaTime) override;
	virtual void Late_Update(f32_t fDeltaTime) override;
	virtual HRESULT Render() override;

public:
	void	Bullet_Active(const float3_t vPos, const float3_t& vDir, f32_t fSpeed);

public:
	void	TriggerEnter(shared_ptr<class CCollider> pOtherCollider)override;

private:
	shared_ptr<CVertexShader>				m_pVSCom = { nullptr };
	shared_ptr<CPixelShader>				m_pPSCom = { nullptr };
	shared_ptr<CVIBuffer_Rect>				m_pBufferCom = { nullptr };
	shared_ptr<CCube_Collider>				m_pCube_Collider = { nullptr };
	
private:
	f32_t				m_fMoveDistance = { 0.f };
	f32_t				m_fWidth = { 0.25f };

private:
	HRESULT Ready_Components();
	HRESULT	Ready_ConstantBuffer();
	HRESULT Bind_Shader();
	HRESULT Bind_ShaderResources();

public:
	static shared_ptr<CBullet> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
	virtual shared_ptr<CPrototype> Clone(void* pArg) override;
};

NS_END