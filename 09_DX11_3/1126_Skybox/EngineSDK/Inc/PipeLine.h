#pragma once

#include "Engine_Defines.h"

NS_BEGIN(Engine)

class CPipeLine final 
{
private:
	CPipeLine(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
public:
	~CPipeLine() = default;

public:
	void Set_Perspective_Transform(D3DTS eState, fmatrix_t TransformMatrix) {
		XMStoreFloat4x4(&m_PipeLineDesc.PerspectiveTransformMatrices[ETOUI(eState)], TransformMatrix);
	}
	void Set_Ortho_Transform(D3DTS eState, fmatrix_t TransformMatrix) {
		XMStoreFloat4x4(&m_PipeLineDesc.OrthoTransformMatrices[ETOUI(eState)], TransformMatrix);
	}

public:
	matrix_t Get_Perspective_Transform(D3DTS eState) const {
		return XMLoadFloat4x4(&m_PipeLineDesc.PerspectiveTransformMatrices[ETOUI(eState)]);
	}
	matrix_t Get_Ortho_Transform(D3DTS eState) const {
		return XMLoadFloat4x4(&m_PipeLineDesc.OrthoTransformMatrices[ETOUI(eState)]);
	}

	matrix_t Get_Perspective_Transform_Inverse(D3DTS eState) const {
		return XMLoadFloat4x4(&m_PipeLineDesc.PerspectiveTransformInverseMatrices[ETOUI(eState)]);
	}
	matrix_t Get_Ortho_Transform_Inverse(D3DTS eState) const {
		return XMLoadFloat4x4(&m_PipeLineDesc.OrthoTransformInverseMatrices[ETOUI(eState)]);
	}

	vector_t Get_CamPosition() const {
		return XMLoadFloat4(&m_PipeLineDesc.vCamPosition);
	}


public:
	HRESULT Initialize();
	void Update();
	
public:
	HRESULT Bind_Vertex_ShaderResource(uint32_t iSlot);
	HRESULT Bind_Pixel_ShaderResource(uint32_t iSlot);
	


private:
	ComPtr<ID3D11Device>			m_pDevice = { nullptr };
	ComPtr<ID3D11DeviceContext>		m_pContext = { nullptr };

private:
	PIPELINE_DESC							m_PipeLineDesc = {};
	shared_ptr<class CConstantBuffer>		m_pCB = { nullptr };

public:
	static unique_ptr<CPipeLine> Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext);
};

NS_END