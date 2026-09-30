#pragma once
#include "Client_Defines.h"

NS_BEGIN(Client)
class CLoader
{
private:
	CLoader(ComPtr<ID3D11Device>pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	~CLoader();

public:
	HRESULT	Initialize(LEVEL eNextLevelID);
	HRESULT	Loading();
	bool_t	isFinished() const { return m_isFinished; }

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
	ComPtr<ID3D11DeviceContext> m_pContext = { nullptr };

private:
	HRESULT Loading_For_LogoLV();
	HRESULT Loading_For_GamePlayLV();

public:
	static shared_ptr<CLoader> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, LEVEL eNextLevelID);
	void Free();

};
NS_END
