# C++ 기초 정리

### 1일차 (260316) 
<details>
  <summary>c++ 동작 순서</summary>

  전처리기(#) - 컴파일 - 어셈블러 - 링크 - exe파일
</details>

<details>
  <summary>이스케이프 시퀀스</summary>

  > null문자  
  - '\0' -> null 문자, 문자열의 끝을 나타냄, 1byte 크기, 문자열은 null 문자로 끝나야 함. 그 이유는 문자열의 길이를 알 수 있기 때문  

  > 줄바꿈 문자 
  - endl -> end line, 줄바꿈을 하는 것, 버퍼를 비우는 역할도 함   
 - '\n'과의 차이점은 버퍼를 비우는 역할이 있다는 것, 버퍼는 일시적으로 데이터를 저장하는 공간  
 - 버퍼를 비우는 것은 데이터를 즉시 출력하는 것  
 - '\n'은 줄바꿈만 하는 것
</details>

<details>
  <summary>디버그 vs 디버그 없이 실행</summary>
  
  - 디버그는 프로그램을실행하면서 중간중간 변수의 값이나 함수의 호출 등을 확인할 수 있는 모드
</details>

### 2일차 (260317) 변수, 상수, 자료형
<details>
  <summary>자료형</summary>

  - 정수형 자료형 : short(2byte), int(4byte), long(4byte), long long(8byte)
  - 실수형 자료형 : float(4byte), double(8byte), long double(16byte)
  - 문자열 자료형 : char(1byte), wchar_t(2byte)
  - 논리형 자료형 : bool(1byte)  
</details>
<details>
  <summary>변수 표기법</summary>

  - 헝가리안 표기법: iData, fPi, cName, bIsTrue  
  - 파스칼 표기법 : PlayerHp  
  - 카멜 표기법: playerHp  
  - 스네이크 표기법 : is_true  
</details>
<details>
  <summary>bit와 byte</summary>

  - bit: 연산의 최소 단위  
  - byte: 저장의 최소 단위  
  - 1byte = 8bit  
</details>
<details>
  <summary>signed 와 unsigned</summary>

  - signed: - 부호가 있음  
  - unsigned: -부호가 없음  
  - 1byte = 8bit  
</details>
<details>
  <summary>고정 소수점과 부동 소수점</summary>

  - 고정 소수점 방식: 소수점의 위치가 고정 되어있는 방식 주로 사용자가 직접 구현함  
    (실제)1/3 + 1/3 + 1/3 = 1  
    (컴터)0.33 + 0.33 + 0.33 = 0.99 로 계산할 수 있음(오차 발생하지만 예측 가능함)  
    
  - 부동 소수점의 방식: 소수점의 위치가 고정되어있지 않음, 실제 소수값으로 저장되지 않고 유사 값으로 저장.(컴퓨터는 이진수 연산하기 때문)  
    (실제) 0.1 + 0.2 = 0.3  
    (컴터) 0.1 + 0.2 = 0.30000000000000004  
  
</details>

### 3일차 260319. 연산자
<details>
  <summary>sizeof</summary>

  - sizeof 연산자: 자료형의 크기를 계산해주는 연산자  
    ``cout<< sizeof(char)<<endl; //1``
</details>

<details>
  <summary>L-value와 R-value</summary>

  - R-Value : 대입 연산자(=)를 기준으로 오른쪽에만 위치할 수 있는 데이터 형식  
    ```cpp
    int iTest = 100; //100이 R-Value, 리터럴 상수들이 R-Value에 해당
    ```  
    
  - L-Value: 대입 연산자(=)를 기준으로 왼쪽 오른쪽 모두 위치 가능한 데이터 형식  
    ```cpp
    int iSrc = iTest; //iSrc와 iTest 모두 L-Value에 해당
    
    const int iConst = 100;
    iSrc = iConst; //const 변수도 L-Value에 해당
    ```
</details>

<details>
  <summary>비트 연산자</summary>

  - 비트 연산자 : 2진수 형태에서 연산을 수행시켜주는 연산자. 정수만 사용 가능. 방향키 입력으로 캐릭터 이동시킬 때 사용
  - &(and): 비교하는 두 비트의 값이 모두 1인 경우 1  
  - |(or) : 비교하는 두 비트의 값중 하나가 1인 경우 1  
  - ~(not) : 비트 값을 반대로  
  - ^(XOR): 비교하는 두 비트의 값이 다른 경우 1
  ```cpp
  // LEFT			0001
  // RIGHT		0010
  // UP			  0100
  // DOWN			1000
  // 
  // LEFT | UP   ->  0101
  // 0101 & LEFT ->  0001
  // LEFT ^ LEFT ->  0000
  ```
</details>

<details>
  <summary>삼항 연산자</summary>

  > 삼항 연산자 : 연산의 항목이 세 개이며, 짧은 코드로 분기를 하고자 할 때 사용  
   - 주로 최대, 최소 값을 표현하는 용도로 사용  
   - 긴 코드를 작성하기 까다롭고, 가독성이 떨어진다.  
   - 1항(조건식) ? 2항(조건이 참인 경우) : 3항(조건이 거짓인 경우)  

  ```cpp
  for(int i=0;i<n;i++)
  {
    iMax = (arr[i]>iMax) ? arr[i] : iMax;
  }
  ```  
</details>

### 4일차 (260320) 분기문, while
<details>
  <summary>goto</summary>
  
  - goto: 선언한 레이블을 기준으로 이전, 이후 코드로 분기하는 문법  
  ```cpp
  goto Jump;
  int iTemp = 100;
  cout << iTemp;

  Jump;
  cout<<2<<endl;
  cout<<iTemp<<endl;
  ```
</details>
<details>
  <summary>switch</summary>
  
  - switch: 상수(조건)분기문, 조건식에 무조건 정수만 올 수 있음.
  ```cpp
switch(num)
{
case 1:
  break;
case 2:
  break;
case 3:
  break;
default:
  break;
}
  ```
</details>

### 5일차 (260323) do-while, for
<details>
  <summary>do-while</summary>
  
  - do-while: 무조건 한 번은 실행하고 조건을 확인하여 반복을 결정
```cpp
do
{
  //코드 몸체;
}while();
```
</details>

### 6일차 (260324) 메모리 및 기본 함수
<details>
  <summary>메모리</summary>
  
  - 메모리 계층 구성요소: data(data,bss) // heap // stack    
  - 메모리 계층을 넘나드는 것은 좋지 않음.  
  - 변수 및 상수 사용시 가상 메모리 할당 후 사용 가능  
  - 상수는 가상 메모리에 할당 후 다음 줄로 넘어가면 할당 해제  
  - 변수는 가상 메모리에 할당 후 접근 범위를 벗어나면 할당 해제

  |메모리 이름|변수|
  |:----:|:----:|
  |**data**|전역변수,static 변수 |
  |**heap**|포인터 |
  |**stack**|지역변수 |


  |static|dynamic|
  |:------:|:-------:|
  |정적|동적|
  |컴파일타임|런타임|
  |data에 저장|stack에 저장|

  | 구분 | 메모리 | 접근 범위 |
  |:--------:|:----------:|:----------:|
  |지역변수|stack|함수 내부|
  |static 지역변수|data|함수 내부|
  |전역변수|data|모든 파일|
  |static 전역변수|data|현재 파일만|
  
  
</details>

### 7일차 (2600326) 함수 기본 문법 및 포인터 기초

<details>
  <summary>함수 오버로딩</summary>
  
  - 이름이 같은 함수를 사용할 때 어떤 함수를 호출할 지 결정  
  - 매개변수의 종류와 갯수가 같은 것들을 먼저 사용
  - 반환값의 종류와는 상관 없음.
```cpp
void Render();
void Render(int iA, int iB);
int main()
{
  int iDst = 10, iSrc = 20;
  Render(iDst,iSrc); // 30 출력됨
}
void Render()
{
  cout<< "hello world"<<endl;
}
void Render(int _iDst, int _Src)
{
  cout<<_iDst+_iSrc;
}
```
</details>

<details>
  <summary>default 매개변수</summary>
  
  - 매개변수를 선언할 때 매개변수에 값을 할당하는 방법.  
  - 매개변수가 거의 고정인 경우 사용.  
  - 반드시 뒤에있는 매개변수부터 순차적으로 할당해야 함.  
  - 함수 오버로딩과 혼용할 경우 모호해지는 경우가 있음.   
```cpp
void Render(int iA,int iB = 100);
int main()
{
  Render(10);// 매개변수를 하나만 넣었지만 실행 가능.
}
void Render(int iA,int iB)
{
  cout<<iA+iB<<endl;
}

```
</details>

<details>
  <summary>재귀함수</summary>

  - 관습적으로 점점 줄어드는 재귀를 사용함.   
  - 재귀함수를 사용할 때 매 번 스텍 프레임을 생성하기 때문에 메모리 효율이 좋지 못함.  
  - 프로그램 완성 후 반복문으로 바꿀 수 있으면 바꾸는게 좋음.  
  - 다만 retrun Fact(n-1) 과 같은 꼬리 재귀함수의 경우 스텍 프레임을 생성하지 않음.  
```cpp
//일반 재귀
int sum(int n)
{
  if(n<=0) return 0;
  return n+sum(n-1);
}
```
```cpp
//꼬리 재귀
int sum(int n,int res)
{
  if(n<=0) return res;
  return sum(n-1, res + n);
}
```
</details>

<details>
  <summary>포인터</summary>

  - 포인터는 주소값을 저장하는 변수  
  - int* p;로 선언 또는 선언과 동시에 초기화도 가능  
  - 포인터 변수는 64bit 기반 프로그램에서는 8byte 크기  
  - 64bit 기반에서는 0x0 ~ 0xffff ffff ffff ffff까지 가능함(f -> 15 -> 1111, 즉 f 하나가 4비트이고 f는 총 16개, 그냥 1byte = 8bit라서 8로 나누면 됨)
```cpp
//포인터 변수 선언 및 초기화
int main()
{
  int iA = 100;
  int* p = &iA; //포인터 변수 p 선언과 동시에 초기화

  cout<<iA<<endl; // iA의 변수값 출력  
  cout<<*p<<endl; // 포인터 변수 p가 가르키는 iA의 주소에있는 값 출력 (=iA의 변수값)

  cout<<&iA<<endl; // iA의 주소값 출력
  cout<<p <<endl;  // 포인터 변수 p가 가르키는 iA의 주소 출력(=iA의 주소)

  *p = 20; // 포인터 변수 p가 가르키는 iA의 주소에 있는 값을 20으로 변경(간접 참조)

  cout<<iA<<endl; // 윗 줄의 간접 참조로 인해 iA값은20으로 변경됨. 
}
```
```cpp
//Swap함수 call by value를 보완하기 위해 call by reference 사용
void Swap(int* pDst,int* pSrc)
{
  int iTemp = *pDst;
  *pDst = *pSrc;
  *pSrc = iTemp;
}
int main()
{
  int iA = 20, iB = 30;
  Swap(iA,iB);
  cout<<iA <<" "<< iB<<endl;
}
```
</details>

### 8일차 (2600327) 포인터2, 배열

<details>
  <summary>const와 포인터</summary>

  > 읽기 전용 포인터: 참조하는 대상의 변수값을 변경할 수 없음 읽기만 가능함. 
```cpp
int iData = 10;
const int* p = &iData;
```
  > 상수 포인터: 참조하는 대상을 바꿀 수 없음. 주소를 바꿀수 없음. 다만 값은 변경 가능함. 배열이 여기에 해당.
```cpp
int iData = 10;
int* const p = &iData;
```
  > 읽기 전용 상수 포인터: 참조하는 대상을 바꿀 수 없고 값도 변경 불가능함.
```cpp
int iData = 10;
const int* const p = &iData;
```
</details>

<details>
  <summary>이중포인터</summary>

  - 이중 포인터: 포인터의 주소를 참조하는 포인터  
  - 이중 포인터도 크기는 8byte
```cpp
int iData = 10;
int* p = &iData;
int** pp = &p;
```
</details>

<details>
  <summary>포인터 연산</summary>

  - 포인터 연산: 참조하는 대상의 자료형 크기만큼 메모리를 이동하여 참조의 대상을 변경하는 연산
```cpp
int iData = 10;
int* p = &iData;
++p; //iData 의 주소가 0x0001이었다면 ++p 이후 p를 출력했을 때는 0x0005가 됨.
```
</details>

### 9일차 (2600330) 시간 복잡도, 2차원 배열

<details>
  <summary>시간 복잡도</summary>

  > 빅오 표기법(Big-O) : 코드가 얼마나 느려질 수 있는지 확인(최악 기준)

  - O(1) : 항상 일정함 (입력 크기와 상관 없음)  
  - O(log n) : 이진 탐색(가장 이상적임)
```cpp
for(int i=0;i<n;i*=2)
{
  cout<<i;
}
```
  - O(n) : 입력 크기만큼 증가  
  - O(nlog n) : merge sort  
  - O(n^2) : 이중 반복문  
```cpp
for(int i=0;i<n;i++)
{
  for(int j=0;j<n;j++)
  {
    cout<<i*n + j;
  }
}
```
  - O(2^n) : 완전 탐색  
  - O(n!) : 순열, 완전 탐색  

</details>

<details>
  <summary>2차원 배열</summary>

  - 2차원 배열도 1차원 배열과 마찬가지로 연속된 메모리 공간에 저장됨.  
  - 2차원 배열 포인터: 2차원 배열의 이름을 저장하는 포인터가 따로 존재함.
```cpp
void Render(int(*pArr)[3]);
int main()
{
  int Arr[2][3] = {};
  Render(Arr);
}
```
</details>

### 10일차 (2600330) 디버깅, 함수포인터, 문자배열, 문자열 포인터

<details>
  <summary>디버깅</summary>

  - F5: 디버깅 시작 또는 중단점까지 계속 실행  
  - Shift + F5 : 디버깅 중지  
  - F9 : 현재 줄에 중단점(Breakpoint) 설정 / 해제  
  - Ctrl + Shift + F9 : 모든 중단점 삭제  
  - F10 : 프로시저 단위 실행(Step Over - 함수 내부로 들어가지 않음)  
  - F11 : 한 단계씩 코드 실행(Step Into - 함수 내부로 진입)
  - 조건식 화면에서 변수 또는 배열의 값과 주소 확인 가능
  - 조건을 추가하여 반복문의 경우 특정 i값으로 중단점 조건을 설정하여 디버깅 시작 가능
  - 디버깅 하는 도중 "직접 실행창"을 통해 변수의 값을 직접 할당하여 실행할 수 있음  
</details>

<details>
  <summary>함수 포인터</summary>

  - 함수 포인터: 함수의 이름을 저장하는 용도의 포인터  
  - 코드의 가독성을 높이고 배열에 저장하여 인덱스 번호를 이용하여 함수를 호출 가능함(배열에 함수 저장)
```cpp
int		Plus(int dst, int src);
int		Min(int dst, int src);
int		Mul(int dst, int src);
int		Div(int dst, int src);
int main()
{
  int iDst(10), iSrc(20);
  int iInput(0), iResult(0);
  int (*pCalc[4])(int, int) = {Plus, Min, Mul, Div}; // 배열에 함수를 저장함

  cout << "1. 덧셈 2. 뺄셈 3. 곱셈 4. 나눗셈 : ";
  cin >> iInput;

  cout << pCalc[iInput - 1](iDst, iSrc) << endl;
}
```
</details>

<details>
  <summary>문자 배열과 문자열 포인터</summary>

  - 문자 배열: 읽기와 쓰기를 모두 허용하는 저장 방식  
  - 마지막에 NULL문자 포함해야 함.
  - 크기는 넉넉하게 해야 함. 
```cpp
char sName[6] ="jusin";
```
  - 문자열 포인터: 읽기만 허용하는 저장 방식
  - 문자열을 복사하지 않고 첫 문자의 주소를 전달하기 때문에 성능이 좋음  
  - 수정을 할 수 없지만 성능이 중요한 경우 std::string대신 사용함.  
```cpp
const char* pName = "helloworld"; //pName은 'h'의 주소만 들고 있음 함수에 매개변수로 전달할 때 사용될 수 있음
cout << pName << endl;
```

|방식|	전달되는 것|
|:---:|:---:|
|const char*|	주소 1개|
|std::string|	문자열 전체|
</details>

### 11일차 (2600402) 문자열함수, 사용자 정의 자료형, 구조체, 공용체
<details>
  <summary>문자열 함수</summary>

  > 문자열 복사 함수: strcpy_s(복사 **받을** 메모리 공간의 주소, 복사 **받을** 메모리 공간의 크기, 복사할 문자열의 주소)
```cpp
char szName[32] = "hello";
char szTemp[32] = "";

cout<<szTemp<<endl;
strcpy_s(szTemp,sizeof(szTemp),szName);
coyt<<szTemp<<endl;
```
  > 문자열 결합 함수: strcat_s(결합할 결과물을 저장하는 배열의 주소, 결합한 결과물을 저장할 메모리 공간의 크기, 결합 문자열);
```cpp
char szName[32] = "hello";
char szTemp[32] = "world";
strcat_s(szName,sizeof(szName),szTemp);
cout<<szName<<endl; // helloworld 출력
strcat_s(szTemp,sizeof(szTemp),szName);
cout<<szTemp<<endl; // worldhelloworld 출력
```

  > 문자열 길이 계산 함수: strlen(문자열)
```cpp
char szName[32] = "hello";
int iLength = strlen(szName);
cout<<iLength<<endl;
```
  > 문자열 비교 함수: strcmp(비교할 문자열1의 주소, 비교할 문자열2의 주소), 같으면 0 반환, 다르면 -1반환, !를 붙히고 사용
```cpp
char szName[32] = "hello";
if(!strcmp(szName,"hello")) cout<<"두 문자열은 같습니다."<<endl;
else cout<<"두 문자열은 다릅니다."<<endl;
```
</details>

<details>
  <summary>문자열 함수(string 버전)</summary>

  > 문자열 복사
```cpp
string szName = "hello";
string szTemp = szName;
cout<< szTemp;
```
  > 문자열 결합
```cpp
string szName = "hello";
string szTemp = "world";
szName = szName+szTemp; // += 가능
cout<<szName<<endl; // helloworld 출력
szTemp = szTemp+szName;
cout<<szTemp<<endl; // worldhelloworld 출력
```

  > 문자열 길이 계산: .size()
```cpp
string szName = "hello";
int iLength = szName.size();
cout<<iLength<<endl;
```
  > 문자열 비교: ==, !=
```cpp
string szName = "hello";
if(szName!="hello") cout<<"두 문자열은 같습니다."<<endl;
else cout<<"두 문자열은 다릅니다."<<endl;
```
</details>

<details>
  <summary>사용자 정의 자료형</summary>
  
  - 사용자 정의 자료형이란? : 프로그래머의 필요에 따라 직접 만들어서 사용하는 자료형  
  - 반드시 용도에 따른 키워드를 삽입해야 함  
  - struct(구조체): 다른 타입의 자료형을 하나의 자료형으로 묶어서 사용하기 위한 자료형  
  - union(공용체): 여러 데이터들을 하나의 메모리를 공유하여 사용하게 하는 문법  
  - enum(열거체): 상수를 여러 개 만드는 문법
  - class도 추가
</details>

<details>
  <summary>구조체</summary>

  - 포인터사용이 가능하다
```cpp
tagSt st = {};
tagSt* pst = st;

cout<< *pst->iKor <<endl; // -> 이 키워드를 아래 문법 보다 더 많이 사용함
cout<< *pst.iKor <<endl;
```
  - 구조체도 상속 가능하고 부모 자식 둘 다 가능, class와도 상속이 가능  
  - 데이터 집합체(멤버 변수만 사용)로도 사용 가능하고 객체로도 사용 가능함.
</details>

<details>
  <summary>구조체의 메모리 할당 정책 </summary>
  
  - 멤버변수 중 가장 큰 자료형의 크기만큼 메모리 블럭을 할당함.  
  - 작은 크기의 자료형 먼저 선언해야 메모리를 절약할 수 있다.  
  - 배열이 있더라도 배열의 크기가 아니라 배열의 자료형으로 계산.  
  - 멤버 변수가 없다면 디폴트 1byte로 계산함.
  - 멤버 함수는 데이터로 취급하지 않고 오로지 멤버 변수로만 크기를 계산함.(클래스도 동일)
  - 가장 큰 자료형의 크기는 기본 자료형으로만 계산.
```cpp
struct tagInfo // 정렬 기준: 8(double 때문에)
{
	int		iKor;		// 4+4(padding)
	double	dAver;		// 8
};
struct tagTemp // 정렬 기준: 8(tagInfo 때문에)
{
	tagInfo		tInfo;		// 16 

	short		sName; //2
	float		fPi;  //4+2(2는 padding)
};

int main()
{
  cout<<sizeof(tagTemp)<<endl; // 24
}
```
</details>

<details>
  <summary>공용체</summary>

  - 거의 안씀 c#에는 없음.  
  - 다른 자료형을 사용한다면 정상적으로 저장이 안됨.
</details>






















