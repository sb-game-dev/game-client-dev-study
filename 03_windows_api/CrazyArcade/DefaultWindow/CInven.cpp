#include "pch.h"
#include "CInven.h"

CInven* CInven::m_pInstance = nullptr;
CInven::CInven():m_iGold(10000)
{
}

CInven::~CInven()
{
}
