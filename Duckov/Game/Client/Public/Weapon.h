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

	HRESULT	Change_Model(const wstring_t& strMeshPath);
	void	Play_FireAnim(const f32_t fDeltaTime);
	vector<shared_ptr<class CBullet>>&		Get_Bullets() { return m_Bullets; }

	void	Update_MeleeAttack();
	void	Set_ColliderActive(bool_t bActive) { m_bActive = bActive; }
	void	TriggerEnter(shared_ptr<class CCollider> pOtherCollider) override;
	void	Clear_Hit_Targets();

private:
	shared_ptr<CVertexShader>				m_pVSCom = { nullptr };
	shared_ptr<CPixelShader>				m_pPSCom = { nullptr };
	shared_ptr<CModel>						m_pModelCom = { nullptr };
	shared_ptr<CCube_Collider>				m_pCubeCollider = { nullptr };

	weak_ptr<class CInven>					m_pInven;
	weak_ptr<class CPlayer>					m_pPlayer;

private:
	const float4x4_t* m_pSocketMatrix = { nullptr };

private:
	f32_t m_fFireTimer = { 0.f };
	f32_t m_fFireinterval = { 0.1f };

private:
	f32_t m_fRecoilOffset = { 0.f };
	f32_t m_fRecoilSpeed = { 2.f };
	
	f32_t m_fAimBlend = { 1.f };
	f32_t m_fAimBlendDuration = { 0.2f };

private:
	vector<shared_ptr<class CBullet>>	m_Bullets;
	uint32_t							m_iNumBullet = { 32 };
private:
	vector<weak_ptr<CGameObject>>		m_Hit_Targets;
	DAMAGE_DESC							m_tDamageDesc = {};

private:
	HRESULT Ready_Components();
	HRESULT Bind_Shader();
	HRESULT Bind_ShaderResources(const matrix_t& matWorld);
	HRESULT Ready_Bullets();
private:
	void	Update_CanFire(const f32_t& fDeltaTime);
	void	Fire(const float3_t vPos, const float3_t& vDir, f32_t fSpeed);
public:
	static shared_ptr<CWeapon> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
	virtual shared_ptr<CPrototype> Clone(void* pArg) override;
};

NS_END