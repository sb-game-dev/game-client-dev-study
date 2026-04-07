#include "pch.h"

#define NUMBER 7
#if NUMBER > 7
void Render() { cout << "7보다 크다" << endl; }
#elif NUMBER < 7
void Render() { cout << "7보다 작다" << endl; }
#else
void Render() { cout << "7이다" << endl; }
#endif

//int main()
//{
//
//	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//
//	//FILE* pWrite = nullptr;
//	//
//	//errno_t err = fopen_s(&pWrite, "./test.txt", "wb");
//	//
//	//if (err == 0)
//	//{
//	//	fputs("hello world", pWrite);
//	//	cout << "파일 출력 성공" << endl;
//	//
//	//	fclose(pWrite);
//	//}
//
//	//FILE* pRead = nullptr;
//	//
//	//errno_t err = fopen_s(&pRead, "./test.txt", "rb");
//	//char szName[32] = "";
//	//if (err == 0)
//	//{
//	//	fgets(szName, sizeof(szName), pRead);
//	//	fputs(szName,stdout);
//	//	fclose(pRead);
//	//}
//}

// 문자열 입출력 함수
// 
// text모드 binary모드
// 
// 파일 입출력
// 
// ./ -> 현재 프로젝트 위치의 경로
// ../ -> 현재 프로젝트 위치의 경로 이전 경로로 이동하세요
// 
// 바이너리모드 파일 쓰기시 파일을 못열도록 .dat 확장자로 생성함 
// 
// <레퍼런스 자료형 (자료형&) >
// 1. 주소값 직접 참조
// 2. 별명을 붙혀주는 것과 같음 그래서 주소가 참조하는 대상의 주소와 같다.
// 3. 선언과 동시에 초기화 해야 함.
// 4. 크기는 의미가 없음(용량을 갖지 않음)
// 5. 동작 속도가 굉장히 빠르다.
// 6. 불필요한 연산자를 기입할 필요가 없음.
// 
// 7. 레퍼런스는 오직 하나의 데이터만 참조가 가능하다. (초기화한 변수만 참조, 참조 대상 변경 못함)
// 8. 레퍼런스는 L-Value만 참조 가능 (단,  const 사용시 가능)
// 9. 동적 할당은 못함.
// 10. 재귀함수를 사용할 때는 못함.
// 
// 그럼 레퍼런스를 쓰는 경우는 언제?
// swap?
// 
// 
// ===================================
// 0. 어제꺼 다시 정리
// 
// 1. 자동 개행 여부도 정리
// 
// 2. 파일 입력 코드를 한 번 더 하면 덮어쓰기가 되나 아님 오류가 나나 아님 이어쓰기가 되나
// 
// 3. 파일 스트림 생성시 nullptr이 아니라 NULL로 초기화 하는 이유
// 
// 4. 파일 입출력으로 구조체 읽고 써보기
// 
// ====과제====
// 1. 파일 입출력 함수를 이용하여 이미지 파일 복사
// 2. textRPG 저장 / 불러오기 기능 추가
// - 불러오기는 SelectJob 함수 안에서 하기
// 
// 
