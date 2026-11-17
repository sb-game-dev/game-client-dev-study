#pragma once

#include "Engine_Defines.h"

/* 클라이언트 개발자가 생성한 레벨클래스들의 부모가 되는 클래스. */

/* 엔진의 레벨매니져가 클라클래슬르 객체화한 레벨을 보관한다라는 개념이 가능 */
/* 엔진에서 클라에 정의한 레벨클래스의 함수(오버라이딩에 의하여)를 호출하는 것이 가능해졌다. */

NS_BEGIN(Engine)

class ENGINE_DLL CLevel abstract
{
protected:
	CLevel(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);

public:
	virtual ~CLevel() = default;

public:
	virtual HRESULT Initialize();
	virtual void Update(f32_t fTimeDelta);
	virtual HRESULT Render();

protected:
	ComPtr<ID3D11Device>			m_pDevice = { nullptr };
	ComPtr<ID3D11DeviceContext>		m_pContext = { nullptr };

};

NS_END