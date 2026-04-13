#pragma once
#include <iostream>
using namespace std;
class C_B;

class C_A
{
public:
	C_A(int iTemp);
	~C_A();
	void Initialize();
	void Update();
	void Release();
private:
	int m_iApple;
private:
	C_B* m_pB;
public:
	void Render_B();
};

