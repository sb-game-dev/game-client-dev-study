#pragma once
class C_A;
class C_B
{
public:
	C_B(int iTemp);
	~C_B();
	void Initialize();
	int GetBanana();
private:
	int Banana;
public:
	void Render_A();
private:
	C_A* m_pA;
};

