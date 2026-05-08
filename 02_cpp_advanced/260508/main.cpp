#include "pch.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);


	return 0;
}

// ** 알고리즘
// #include<algorithm>
// 
// 1. sort(vecInt.begin(),vecInt.end());
// 조건자로 함수포인터 Less
// 
// #include<functional>
// less<int>()
// 
// 배열기반 컨테이너만 가능함
// 
// 
// 리스트는 sort가 있음
// 
// 
// 2. count_if()
// 
// 3. for_each()
// 
// ** 리스트
// push_back()
// pop_back()
// 
// push_front()
// pop_front()
// 
// .merge();
// .remove(); //값 다 지움
// .remove_if(); // (중요!)
// .reverse(); //리스트 노드의 배치 순서를 역순으로 재배치함
// .sort(less<int>())
// .splice(iter ,tempList ) // 잘라내기 + 붙여넣기
// 
// 
// .unique() // 연속적으로 같은 값이 있다면 하나만 남기고 다 지움
// 
// 
// forward_list
// 
// push_front()
// pop_front()
// 
// 빠름, 용량이 적음
// 
// ** 맵
// #include <map>
// 
// map<int, int> mapInt;
// 
// 이미지나 리소스 탐색용으로 사용
// 
// map만 [] 연산자가 오버로딩 되어있음
// 
// 원소 추가
// insert(pair< , >)
// 
// mapInt[] = ; ->operator [] 오버로딩 해야 해서 느림 + 대입 연산을 사용해서 좋지 않음
// 
// 순회
// iterator로 순회해야 함
// first, second를 사용해서 key와 value로 접근 해야 함
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