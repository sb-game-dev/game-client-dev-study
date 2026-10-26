#pragma once
#include "Engine_Defines.h"

NS_BEGIN(Engine)
class CPipeLine final
{
private:
	CPipeLine(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	~CPipeLine() = default;

private:
	ComPtr<ID3D11Device> m_pDevice;
	ComPtr<ID3D11DeviceContext> m_pContext;

private:
	//float4x4_t		

public:
	static unique_ptr<CPipeLine> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
};

NS_END