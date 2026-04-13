#include "C_B.h"

C_B::C_B(int iTemp)
{
	Banana = iTemp;
	m_pA = nullptr;
}

C_B::~C_B()
{
}

int C_B::GetBanana()
{
	return Banana;
}