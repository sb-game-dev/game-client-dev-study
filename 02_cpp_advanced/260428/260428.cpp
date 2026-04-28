#include "pch.h"

int main()
{

}


// 모든 컨테이너에는 allocator가 있기 때문에 단항 컨테이너는 없다.
// 
// ** vector
// - 동적 배열 기반
// - 탐색에 용이하고 추가, 삽입, 삭제에는 용이하지 않음
// - push_back, pop_back
// - 추가할 때는 메모리 재할당, 삭제할 때는 재할당 하지 않음
// 
// ** array
// - 추가 삭제X 대입만 가능
// 
// ** dequeue
// 리스트 4개짜리 노드들의 연결, 왜 4개지 앞 뒤 요소 (인덱스?)
// 벡터보다 느림
// 잘 안씀
// 
// ** 리스트
// value, link로 이루어진 노드
// single linked list	vs		double linked list
// forward list			vs		list
// 
// push_back (X)
// pop_back(X)
// 용량이 더 적음(링크가 1개)
// 역방향으로 탐색하는 경우 드뭄
// 
// 1945 -> 총알 
// 과거 : list로 만들고 최적화로 vector(오브젝트 풀링)
// 
// 현재 : list(컴파일러가 좋아져서 탐색 속도가 빨라짐)
// 
// 모드 전환 때문에 vector(오브젝트 풀링)로 처리하는게 좋을 수 있음
// 
// 
// 
// 
// 
// 