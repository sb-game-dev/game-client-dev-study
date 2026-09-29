#pragma once
#include "Engine_Defines.h"
NS_BEGIN(Engine)
class CPrototype;
class CPrototype_Manager final
{
private:
	CPrototype_Manager();
public:
	~CPrototype_Manager() = default;

public:
	HRESULT Initialize(uint32_t iNumLevels);
	HRESULT Add_Prototype(uint32_t iLevelIndex, const wstring_t& strPrototypeTag, shared_ptr<CPrototype> pPrototype);
	shared_ptr<CPrototype> Clone_Prototype(uint32_t iLevelIndex, const wstring_t& strPrototypeTag, void* pArg);
	void Clear(uint32_t iClearLevelIndex);

private:
	uint32_t	m_iNumLevels = {};

private:
	typedef map<const wstring_t, shared_ptr<CPrototype>>	PROTOTYPES;
	shared_ptr<PROTOTYPES[]> m_pPrototypes = { nullptr };
	// 동적 배열을 스마트 포인터로 선언
private:
	shared_ptr<CPrototype> Find_Prototype(uint32_t iLevelIndex, const wstring_t& strPrototypeTag);
public:
	static unique_ptr<CPrototype_Manager> Create(uint32_t iNumLevels);
};

NS_END
