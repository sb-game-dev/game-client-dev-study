#pragma once

#include "Client_Defines.h"
#include "Engine_Defines.h"

/* 2. 다음 레벨에 대한 자원 준비를 한다.(서브스레드) */
/* 2_1. 로딩레벨에서 담당하기보다는 로더클래스가 로딩작업을 수행해준다. */
/* 2_2. 물론 로더는 로딩레벨안에서 생성해준다. */

NS_BEGIN(Client)

class CLoader final 
{
private:
	CLoader(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	~CLoader();

public:
	HRESULT Initialize(LEVEL eNextLevelID);
	HRESULT Loading();
	bool_t isFinished() const {
		return m_isFinished;
	}

#ifdef _DEBUG
public:
	HRESULT Draw_Debug();

#endif


private:
	LEVEL				m_eNextLevelID = {};
	HANDLE				m_hThread = {};
	CRITICAL_SECTION	m_CriticalSection = {};
	tchar_t				m_szLoadingText[MAX_PATH] = {};
	bool_t				m_isFinished = { false };

private:
	ComPtr<ID3D11Device>		m_pDevice = { nullptr };
	ComPtr<ID3D11DeviceContext>	m_pContext = { nullptr };

private:
	HRESULT Loading_For_LogoLV();
	HRESULT Loading_For_GamePlayLV();

public:
	static shared_ptr<CLoader> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, LEVEL eNextLevelID);
	void Free();

};

NS_END