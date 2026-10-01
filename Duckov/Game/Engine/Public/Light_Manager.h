#pragma once
#include "Engine_Defines.h"
NS_BEGIN(Engine)
class CLight;
class CLight_Manager
{
private:
	CLight_Manager();
public:
	~CLight_Manager() = default;

public:
	void	Priority_Update(f32_t fDeltaTime) ;
	void	Update(f32_t fDeltaTime) ;
	void	Late_Update(f32_t fDeltaTime) ;

	void	AddLight(const wstring_t& strLightTag, shared_ptr<CLight> pLight);
	shared_ptr<CLight> Find_Light(const wstring_t& strLightTag);
private:
	map<const wstring_t, shared_ptr<CLight>> m_Lights;

public:
	static unique_ptr<CLight_Manager> Create();
};

NS_END