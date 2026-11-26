#pragma once
#include "Client_Defines.h"
#include "ContainerObject.h"

NS_BEGIN(Client)
class CTargetDummy : public CContainerObject
{
public:
	typedef struct tagTargetDummyDesc : public CONTAINEROBJECT_DESC
	{

	}TARGETDUMMY_DESC;
private:
	CTargetDummy(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	~CTargetDummy() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual	void	Priority_Update(f32_t fDeltaTime) override;
	virtual	void	Update(f32_t fDeltaTime) override;
	virtual	void	Late_Update(f32_t fDeltaTime) override;
	virtual HRESULT	Render() override;

public:
	
	virtual void	TriggerEnter(shared_ptr<class CCollider> pOtherCollider)override;
	virtual void	Take_Damage(const DAMAGE_DESC& Desc)override;


private:
	float4_t						m_vGroundPlane = { 0.f, 1.f, 0.f, 0.f };	// 발밑 평면 (a,b,c,d)
	weak_ptr<class CHill>			m_pHill;

private:
	shared_ptr<class CUI_HpBar>			m_pHpBar = { nullptr };
	f32_t								m_fHitTimeRemaining = { 0.f };	// 남은 시간
	f32_t								m_fHitDuration = { 0.15f };		// 전체 애니메이션 길이
	shared_ptr<CConstantBuffer>			m_pCBHitRatio = { nullptr };
	float4_t							m_vHitRatio = {};

	shared_ptr<CCube_Collider>			m_pCube_Collider = { nullptr };
	shared_ptr<class CBody_TargetDummy> m_pBodyTargetDummy = { nullptr };


private:
	HRESULT			Ready_Components();
	HRESULT			Ready_PartObjects();
;
public:
	static shared_ptr<CTargetDummy> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
	virtual shared_ptr<CPrototype> Clone(void* pArg) override;
};

NS_END