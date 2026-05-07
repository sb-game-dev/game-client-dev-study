#include "pch.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);


	return 0;
}

// 
// 
// vector<int>		vecInt(5);
// 
// vecInt[0] =100;
// 
// vecInt.front() = 100;
// 
// vecInt.Resize(7);
// 
// vecInt.reserve(5) -> capacity 5 예약 -> 재할당을 줄일 수 있다. 최적화에 정말 중요
// 
// vecInt.assign(vecInt.front(),vecInt.back()) -> 오버로딩이 세가지 버전이 있음
// 
// vecInt.at(0) -> [] 연산자 기능을 함
// []보다 더 빠름 ([]는 operator된거라)
// 
// vecInt.emplace
// 
// vecInt.data
// 
// &vecInt[0] != &vecInt 
// 
// &vecInt[0] == vecInt.data 근데 많이 안씀 
// 
// 
// 
// 
// 
// 