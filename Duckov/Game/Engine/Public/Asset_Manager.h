#pragma once
#include "Engine_Defines.h"

NS_BEGIN(Engine)
class CPrototype;
class CAsset_Manager final
{
private:
	CAsset_Manager(ComPtr<ID3D11Device>pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	~CAsset_Manager() = default;

public:
	HRESULT	Get_Or_Load_Texture(uint32_t iLevelIndex, const wstring_t& strPath, _Out_ wstring_t& strTag);
	HRESULT	Get_or_Load_Mesh(uint32_t iLevelIndex, const wstring_t& strPath, _Out_ wstring_t& strTag);
private:
	shared_ptr<CPrototype> Create_BuiltinMesh(const wstring_t& strTag);

private:
	ComPtr<ID3D11Device>				m_pDevice;
	ComPtr<ID3D11DeviceContext>			m_pContext;
	unordered_set<wstring_t>            m_FailedTags;		// 실패한 경로는 다시 시도하지 않기 위해 실패한 경로를 저장

public:
	static unique_ptr<CAsset_Manager> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
};

NS_END