#include "pch.h"
class CObj
{
public:
	CObj(int iA) : m_iA(iA) {}
	CObj(const CObj& rhs)
	{

	}

private:
	int m_iA;
};
int main()
{



	return 0;
}


// 복사 생성자
// 1. 일반 생성하는 것과 복사 생성하는 것의 차이
// 2. default 복사 생성자
// 3. CObj   Copy(Dest) -> Copy가 복사 생성자를 호출함
// 
// 4. 복사 생성자 만들기
// CObj(const CObj& rhs) //rhs -> right hands side 복사 생성자를 지칭하는 것 + 대입연산자의 오른쪽에 오는 것
// 복사 생성자를 만들면서 이니셜라이저로 초기화 가능
// 
// 함수의 매개변수로 객체타입을 설정하면 복사생성자로 생성함
// 
// 함수의 반환값이 객체타입인 경우 복사 생성자로 생성해서 반환함
// 
// 거의 3번만 사용함
// 
// 
// 
// friend
// 
//