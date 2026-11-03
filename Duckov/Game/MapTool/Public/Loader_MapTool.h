#pragma once
#include "MapTool_Defines.h"

NS_BEGIN(MapTool)
class CLoader_MapTool
{
private:
	CLoader_MapTool(ComPtr<ID3D11Device>pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	~CLoader_MapTool();

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
	HRESULT Loading_For_MapToolLV();

public:
	static shared_ptr<CLoader_MapTool> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext, LEVEL eNextLevelID);
	void Free();
};
NS_END