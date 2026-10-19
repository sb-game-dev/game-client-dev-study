#pragma once
#include "Client_Defines.h"
#include "Mouse.h"
NS_BEGIN(Engine)
class CTexture;
NS_END

NS_BEGIN(Client)

class CClient_Mouse : public CMouse
{
public:
	typedef struct tagMouseDesc : public CMouse::MOUSE_DESC
	{

	}CLIENT_MOUSE_DESC;
	enum class MOUSESTATE { CURSOR, DOT, BAR, ARROW, END };

private:
	CClient_Mouse(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	virtual ~CClient_Mouse() = default;

public:
	virtual		HRESULT		Initialize_Prototype() override;
	virtual		HRESULT		Initialize(void* pArg) override;
	virtual		void		Priority_Update(f32_t fTimeDelta)override;
	virtual		void		Update(f32_t fTimeDelta)override;
	virtual		void		Late_Update(f32_t fTimeDelta)override;
	virtual		HRESULT		Render() override;
	virtual		HRESULT		Render_Mesh(const XMMATRIX& matWorld, ID3D11RasterizerState* pRS)override;

	MOUSESTATE				GetMouseState() { return m_eMouseState; }
	void					SetMouseState(MOUSESTATE eMouseState) { m_eMouseState = eMouseState; }

private:
	shared_ptr<CTexture>			m_pTextureCom = { nullptr };
	MOUSESTATE						m_eMouseState = {};
	float3_t						m_vPosVP = {0.f,0.f,2.f};

	static constexpr uint32_t		m_iNumInstance = 4;
	ComPtr<ID3D11Buffer>			m_pInstanceVB = { nullptr };
	float4x4_t						m_WorldMats[m_iNumInstance] = {};
	
	f32_t							m_fRange = { 25.f };
	f32_t							m_fTimer = { 0.f };

private:
	HRESULT					Ready_Components();
	HRESULT					Ready_InstanceBuffers();
	HRESULT					Render_Mesh(ID3D11Buffer* pInstanceVB, ID3D11PixelShader* pPS, uint32_t iInstanceCnt);

public:
	static shared_ptr<CClient_Mouse> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
	virtual shared_ptr<CPrototype> Clone(void* pArg) override;
};

NS_END