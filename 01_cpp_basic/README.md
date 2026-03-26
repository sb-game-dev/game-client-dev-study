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

### 7일차 (2600326) 함수 기본 문법 및 포인터

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
