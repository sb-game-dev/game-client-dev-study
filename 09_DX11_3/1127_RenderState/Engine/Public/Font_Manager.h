#pragma once

#include "Engine_Defines.h"

NS_BEGIN(Engine)

class CFont_Manager final 
{
private:
	CFont_Manager(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	~CFont_Manager() = default;

public:
	HRESULT Add_Font(const wstring_t& strFontTag, const tchar_t* pFontFilePath);

private:
	ComPtr<ID3D11Device>				m_pDevice = { nullptr };
	ComPtr<ID3D11DeviceContext>			m_pContext = { nullptr };

private:
	map<const wstring_t, shared_ptr<class CCustomFont>>			m_Fonts;

private:
	shared_ptr<class CCustomFont> Find_Font(const wstring_t& strFontTag);

public:
	static unique_ptr<CFont_Manager> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);

};

NS_END