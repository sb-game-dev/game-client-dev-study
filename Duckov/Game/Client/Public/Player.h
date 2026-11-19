#pragma once
#include "Client_Defines.h"
#include "ContainerObject.h"

NS_BEGIN(Client)
class CPlayer : public CContainerObject
{
public:
	typedef struct tagPlayerDesc : public CONTAINEROBJECT_DESC
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

	bool_t	Is_Aiming()				{ return m_bAiming && Has_Weapon();	}
	bool_t	Is_Firing()				{ return m_bFiring && Has_Weapon(); }

	f32_t	Get_HP()				const { return m_fHP; }
	f32_t	Get_MaxHP()				const { return m_fMaxHP; }

	f32_t	Get_Stamina()			const { return m_fStamina; }
	f32_t	Get_MaxStamina()		const { return m_fMaxStamina; }
	bool_t	Is_StaminaLock()		const { return m_bStaminaLock; }

	f32_t	Get_Hunger()			const { return m_fHunger; }
	f32_t	Get_MaxHunger()			const { return m_fMaxHunger; }

	f32_t	Get_Thirst()			const { return m_fThirst; }
	f32_t	Get_MaxThirst()			const { return m_fMaxThirst; }

private:
	float4_t						m_vGroundPlane = { 0.f, 1.f, 0.f, 0.f };	// 발밑 평면 (a,b,c,d)

	shared_ptr<CModel>				m_pModelCom = { nullptr };
	shared_ptr<CVertexShader>		m_pVSCom = { nullptr };
	shared_ptr<CPixelShader>		m_pPSCom = { nullptr };
	shared_ptr<CPixelShader>		m_pPS_Shadow = { nullptr };
	shared_ptr<CPixelShader>		m_pPS_Occluded = { nullptr };
	ComPtr<ID3D11RasterizerState>	m_pRS_Reflect = { nullptr };

	shared_ptr<CConstantBuffer>		m_pCB = { nullptr };
	CB_PER_OBJECT					m_tCBData = {};

	weak_ptr<class CInven>			m_pInven;
	weak_ptr<class CHill>			m_pHill;
	bool_t							m_bAiming = { false };
	bool_t							m_bFiring = { false };
	
	bool_t							m_bSlowTrun = { false };
	float4_t						m_vRollStartMoveDir = {};

private:
	typedef struct tagPlayerInput
	{
		f32_t   fMoveX = 0.f, fMoveZ = 0.f;   // WASD 결과
		bool_t  bSprint = false;              // LShift 누르는 중
		bool_t  bRoll = false;                // Space 이번 프레임에 눌림
		bool_t  bAim = false;                 // RB
		bool_t  bFire = false;                // LB
		bool_t  bSlot1 = false, bSlot2 = false, bSlotMelee = false;
	}PLAYER_INPUT;

	PLAYER_INPUT    m_tInput = {};


private:
	enum class PLAYER_STATE { IDLE, WALK, SPRINT, ROLL, ATTACK, END };
	PLAYER_STATE    m_eState = { PLAYER_STATE::IDLE };

	enum class PLAYER_ANIM {
		IDLE, 
		WALK_FORWARD, WALK_BACKWARD, TPOS,
		IDLE_RH,
		WALK_FORWARD_RH, WALK_BACKWARD_RH,
		ROLL, ATTACK, ATTACK_L2R, 
		WALK_LEFT,WALK_RIGHT,WALK_LEFT_RH_OUT,WALK_RIGHT_RH_OUT,
		RIDING,
		END 
	};

	PLAYER_ANIM						m_eLowerMoveState = { PLAYER_ANIM::END };
	PLAYER_ANIM						m_eUpperMoveState = { PLAYER_ANIM::END };


private:
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

	void			Key_Input();
	void			Update_State(f32_t fDeltaTime);
	void			Initialize_State(PLAYER_STATE eNext);

	void			Update_State_Idle(f32_t fDeltaTime);
	void			Update_State_Walk(f32_t fDeltaTime);
	void			Update_State_Sprint(f32_t fDeltaTime);
	void			Update_State_Roll(f32_t fDeltaTime);
	void			Update_State_Attack(f32_t fDeltaTime);
	void			Handle_SlotInput();

	bool_t			Can_Roll() const { return !m_bStaminaLock && m_fStamina > m_fRollStamina; }
	bool_t			Can_Sprint() const { return !m_bStaminaLock && m_fStamina > 0.f; }
	bool_t			Has_MoveInput() const { return 0.f != m_tInput.fMoveX || 0.f != m_tInput.fMoveZ; }
	bool_t			Has_Weapon();	
	bool_t          Is_MeleeSlot();	
	vector_t		Calc_MoveDir();
	void			Turn_Toward(vector_t vMoveDir, f32_t fDeltaTime);

	void			LookAtMouse(f32_t fDeltaTime);
	void			Change_Animation(PLAYER_ANIM eMoveState, bool_t bUpper = false, f32_t fAnimPlaySpeed = 1.f, f32_t fBlendDuration = 0.2f);
	
	void			Update_Stamina(f32_t fDeltaTime);
	void			Update_Hunger(f32_t fDeltaTime);
	void			Update_Thirst(f32_t fDeltaTime);
public:
	static shared_ptr<CPlayer> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
	virtual shared_ptr<CPrototype> Clone(void* pArg) override;
};

NS_END