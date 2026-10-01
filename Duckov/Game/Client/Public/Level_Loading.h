#pragma once
#include "Client_Defines.h"
#include "Level.h"
/* 1. 로딩 레벨에 필요한 객체(로딩 바, 배경, 글자)들을 생성해준다. (메인 스레드)*/
/* 2. 다음 레벨에 필요한 자원 준비를 한다(서브 스레드)*/
/* 2_1. 로딩레벨에서 담당하지 않고 로더클래스가 로딩 작업을 수행해 준다. */
/* 2_2. 물론 로더는 로딩레벨 안에서 생성해준다. */

NS_BEGIN(Client)
class CLevel_Loading final : public CLevel
{
private:
	CLevel_Loading(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	~CLevel_Loading() = default;

public:
	virtual HRESULT	Initialize(LEVEL eNextLevel);
	virtual void	Update(f32_t fDeltaTime) override;
	virtual HRESULT	Render() override;

private:
	LEVEL							m_eNextLevelID = { LEVEL::END };
	shared_ptr<class CLoader>		m_pLoader = { nullptr };
private:
	HRESULT	Ready_Layer_BackGround();
	HRESULT	Ready_Layer_UI();
public:
	static shared_ptr<CLevel_Loading> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, LEVEL eNextLevel);
};

NS_END
