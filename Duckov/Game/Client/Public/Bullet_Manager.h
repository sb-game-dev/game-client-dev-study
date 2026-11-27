#pragma once
#include "Client_Defines.h"
#include "GameObject.h"

NS_BEGIN(Client)
class CBullet_Manager : public CGameObject
{
private:
	CBullet_Manager(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	~CBullet_Manager() = default;
public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Priority_Update(f32_t fDeltaTime) override;
	virtual void Update(f32_t fDeltaTime) override;
	virtual void Late_Update(f32_t fDeltaTime) override;
	virtual HRESULT Render() override;

public:
	void	Bullet_Active(const float3_t vPos, const float3_t& vDir, f32_t fSpeed);
	void	Check_Collision(const vector<shared_ptr<class CGameObject>>& vecObjects);
	vector<shared_ptr<class CBullet>>& Get_Bullets() { return m_Bullets; }

private:
	vector<shared_ptr<class CBullet>>	m_Bullets;
	uint32_t							m_iNumBullet = { 32 };

private:
	HRESULT Ready_Bullets();

public:
	static shared_ptr<CBullet_Manager> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
	shared_ptr<CPrototype> Clone(void* pArg) override;
};

NS_END