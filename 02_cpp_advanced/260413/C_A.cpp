#include "C_A.h"
#include "C_B.h"
C_A::C_A(int iTemp) 
{
	m_iApple = iTemp; 
	m_pB = nullptr;
}
C_A::~C_A()
{

}
void C_A::Initialize()
{
	cout << "m_pB에 50 할당함" << endl;
	m_pB = new C_B(50);
}
void C_A::Render_B()
{
	cout << m_pB->GetBanana() << endl;
}
