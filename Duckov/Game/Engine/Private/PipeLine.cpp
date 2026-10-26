#include "PipeLine.h"

CPipeLine::CPipeLine(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
}

unique_ptr<CPipeLine> CPipeLine::Create(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
{
	return unique_ptr<CPipeLine>();
}
