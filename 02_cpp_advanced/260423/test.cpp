#include "pch.h"
class CObj
{
public:
	CObj(int iA, int iB) : m_iA(iA), m_iB(iB) {}
	virtual ~CObj() {}
private:
	int m_iA;
	int m_iB;
public:
	void	Render() { cout << m_iA << "\t" << m_iB << endl; }

	CObj operator+(CObj& Temp)
	{
		CObj Result(m_iA + Temp.m_iA, m_iB + Temp.m_iB);
		return Result;
	}
	CObj operator+(int iData)
	{
		CObj Result(m_iA + iData, m_iB + iData);
		return Result;
	}
	CObj& operator++()
	{
		++m_iA;
		++m_iB;
		return *this;
	}
	//CObj operator++()
	//{
	//	++m_iA;
	//	++m_iB;
	//	CObj Result(*this);
	//	return Result;
	//}
	CObj operator++(int)
	{
		CObj Result(*this);

		++(*this);
		return Result;
	}
};
CObj operator+(int iData, CObj& Temp)
{
	CObj Result = Temp + iData;
	return Result;
}
int main()
{
	CObj Dst(10, 20);
	CObj Src(30, 40);
	CObj Tmp = ++Dst + 10;
	Tmp.Render();
	//++Tmp; // 실제로는 Tmp.operator++(); 처럼 작동함
}