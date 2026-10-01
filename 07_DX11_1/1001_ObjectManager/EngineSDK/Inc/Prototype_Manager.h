#pragma once

#include "Engine_Defines.h"

/* 1. 레벨별로 원형객체들을 모아서 관리한다.  */
/* 2.원형객체를 복제하여 사본객체를 생성해준다. */

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
	shared_ptr<map<const wstring_t, shared_ptr<CPrototype>>[]>	m_pPrototypes = {nullptr};
	typedef map<const wstring_t, shared_ptr<CPrototype>>			PROTOTYPES;

private:
	shared_ptr<CPrototype> Find_Prototype(uint32_t iLevelIndex, const wstring_t& strPrototypeTag);

public:
	static unique_ptr<CPrototype_Manager> Create(uint32_t iNumLevels);

};

NS_END