#pragma once
#include "Client_Defines.h"
#include "MapObject.h"
#include "Hill.h"

NS_BEGIN(Client)
class CPlayer : public CMapObject
{
public:
	typedef struct tagPlayerDesc : public MAPOBJECT_DESC
	{

	}PLAYER_DESC;
private:
	CPlayer(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	~CPlayer() = default;

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual	void	Priority_Update(f32_t fDeltaTime) override;
	virtual	void	Update(f32_t fDeltaTime) override;
	virtual	void	Late_Update(f32_t fDeltaTime) override;

	virtual HRESULT	Render() override;
	virtual HRESULT	Render_Reflection(const matrix_t& matReflect) override;
	virtual HRESULT	Render_Shadow() override;
	virtual HRESULT	Render_Occluded() override;

	void	AdjustPosY();

	bool_t	Is_Aiming()			const { return m_bAiming; }
	bool_t	Is_Firing()			const { return m_bFiring; }

	f32_t	Get_HP()			const { return m_fHP; }
	f32_t	Get_MaxHP()			const { return m_fMaxHP; }

	f32_t	Get_Stamina()		const { return m_fStamina; }
	f32_t	Get_MaxStamina()	const { return m_fMaxStamina; }
	bool_t	Is_StaminaLock()	const { return m_bStaminaLock; }

	f32_t	Get_Hunger()		const { return m_fHunger; }
	f32_t	Get_MaxHunger()		const { return m_fMaxHunger; }

	f32_t	Get_Thirst()		const { return m_fThirst; }
	f32_t	Get_MaxThirst()		const { return m_fMaxThirst; }

private:
	float4_t						m_vGroundPlane = { 0.f, 1.f, 0.f, 0.f };	// 발밑 평면 (a,b,c,d)

	shared_ptr<CModel>				m_pModel = { nullptr };
	shared_ptr<CVertexShader>		m_pVS = { nullptr };
	shared_ptr<CPixelShader>		m_pPS = { nullptr };
	shared_ptr<CPixelShader>		m_pPS_Shadow = { nullptr };
	shared_ptr<CPixelShader>		m_pPS_Occluded = { nullptr };

	shared_ptr<CConstantBuffer>		m_pCB = { nullptr };
	CB_PER_OBJECT					m_tCBData = {};

	ComPtr<ID3D11RasterizerState>	m_pRS_Reflect = { nullptr };

	weak_ptr<class CInven>			m_pInven;
	bool_t							m_bAiming = { false };
	bool_t							m_bFiring = { false };

	enum class MOVESTATE {
		IDLE, 
		WALK_FORWARD, WALK_BACKWARD, WALK_LEFT, WALK_RIGHT, TPOS,
		IDLE_RH,
		WALK_FORWARD_RH, WALK_BACKWRD_RH, WALK_LEFT_RH, WALK_RIGHT_RH,
		ROLL, ATTACK, ATTACK_L2R, END 
	};

	MOVESTATE						m_eMoveState = { MOVESTATE::END };

	f32_t							m_fInputX = { 0.f };
	f32_t							m_fInputZ = { 0.f };
	bool_t							m_bSlowTrun = { false };

	// 플레이어 스텟값
	f32_t							m_fHP = { 100.f };
	f32_t							m_fMaxHP = { 100.f };

	f32_t							m_fStamina = {100.f};
	f32_t							m_fMaxStamina = {100.f};
	f32_t							m_fStaminaRegenRate = { 15.f };
	f32_t							m_fStaminaDecayRate = { 10.f };
	f32_t							m_fRollStamina = { 20.f };
	bool_t							m_bStaminaLock = { false };

	f32_t							m_fHunger = { 100.f };
	f32_t							m_fMaxHunger = { 100.f };
	f32_t							m_fHungerDecayRate = { 10.5f };

	f32_t							m_fThirst = { 100.f };
	f32_t							m_fMaxThirst = { 100.f };
	f32_t							m_fThirstDecayRate = { 10.5f };

private:
	HRESULT			Ready_Components();
	HRESULT			Ready_ConstantBuffer();
	HRESULT			Update_ConstantBuffer(const matrix_t& matWorld);
	HRESULT			Render_Mesh(const matrix_t& matWorld, ID3D11RasterizerState* pRS, shared_ptr<CPixelShader> pPS);

	virtual			HRESULT Bind_Shader(shared_ptr<CVertexShader> pVS = nullptr, shared_ptr<CPixelShader> pPS = nullptr);
	virtual			HRESULT Bind_ShaderResources(const matrix_t& matWorld);

	void			KeyInput(f32_t fDeltaTime);
	void			LookAtMouse(f32_t fDeltaTime);
	void			Change_Animation(MOVESTATE eMoveState);
	void			Update_Hunger(f32_t fDeltaTime);
	void			Update_Thirst(f32_t fDeltaTime);
public:
	static shared_ptr<CPlayer> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
	virtual shared_ptr<CPrototype> Clone(void* pArg) override;
};

NS_END