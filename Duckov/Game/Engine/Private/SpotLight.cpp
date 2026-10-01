#include "SpotLight.h"

CSpotLight::CSpotLight(ComPtr<ID3D11Device> pDevice, ComPtr<ID3D11DeviceContext> pContext)
	: CLight{ pDevice,pContext }
{
}