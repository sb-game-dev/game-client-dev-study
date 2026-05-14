#include "pch.h"

class CObj
{
public:
	CObj(int iSize) :m_iSize(iSize) { m_pArray = new int[iSize]; }
	CObj(CObj&& Move)
	{
		m_pArray = Move.m_pArray;
		m_iSize = Move.m_iSize;

		Move.m_pArray = nullptr;
	}
	~CObj()
	{
		if (m_pArray)
		{
			delete[] m_pArray;
			m_pArray = nullptr;
		}
	}
private:
	int m_iSize;
	int* m_pArray;
};
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	CObj Obj(1000000);

	CObj Temp(move(Obj));

	return 0;
}

//
// **r-value레퍼런스
// 
// 임시객체 사용할 때 주의해야 함
// emplace 사용할 때 주의
// 
// ** 이동 생성자
// 
// 프로그래머가 직접 생성해야 작동함
// 면접 질문으로 나온 적이 있다고 함 -> 원본의 소유권을 사본에 이전을 한다
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
//