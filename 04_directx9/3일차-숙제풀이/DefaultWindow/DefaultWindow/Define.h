#pragma once

#define WINCX	800
#define WINCY	600

#define PI		3.141592f

#define PURE	= 0

extern HWND g_hWnd;

typedef struct tagInfo
{
	D3DXVECTOR3		vPos;		// 위치 벡터
	D3DXVECTOR3		vDir;		// 방향 벡터
	D3DXVECTOR3		vLook;		// 방향 벡터

	D3DXVECTOR3		vNormal;	// 방향 벡터(법선 벡터)

	D3DXMATRIX		matWorld;

}INFO;

// 벡터의 상등 : 방향과 크기가 일치하는 벡터는 완전히 같은 벡터
 
// 단위 벡터 : 벡터의 크기가 1인 상태를 말함
// 벡터의 정규화 : 벡터의 크기가 1이 되도록 만드는 과정

// 벡터의 곱셈은 본래 없으나 벡터의 곱셈이라 불리는 두 과정이 있다.

// 내적 : x * x` + y * y` + z * z`, 상수(스칼라) 곱, 두 방향 벡터 사이의 끼인 각을 구하는 용도로 자주 사용(절대 벡터의 내적의 결과가 끼인 각이라는 말은 아니다!!!!)
// A ? B

// - 두 방향 벡터의 크기가 단위 벡터로 정규화가 되어 있고, 두 방향 벡터의 내적의 결과를
// 역함수를 이용하여 각도를 추출하는 용도로 사용 할 수 있다.


// 외적 : 벡터 곱, 3D 공간이 아닌 곳에서는 외적은 사용 불가, 두 방향 벡터와 모두 직각을 이루는 방향 벡터를 구하는 용도로 사용
// A X B

// x	y	z
// 
// x`  y`   z`
// 
// (y * z` - z * y`, x * z` - z * x`, x * y` - y * x`)


// 행렬 : 다수의 데이터를 행과 열의 상태로 표현해 놓은 것
// - 사용 이유 : 객체의 여러 상태(크기, 회전, 위치)를 표현하기 위함

// 월드 변환
// Local.Vtx  * World.Matrix	-> World.Vtx
// 
// 로컬 -> 월드(우리가 만드는 게임 공간)

/*
_11, _12, _13, _14
_21, _22, _23, _24
_31, _32, _33, _34
_41, _42, _43, _44
*/

// 크기 : _11, _22, _33(X, Y, Z 배율)
// 위치 : _41, _42, _43(X, Y, Z 좌표)
// 
// x 회전 : _22(cos), _23(sin), _32(-sin), _33(cos)
// y 회전 : _11(cos), _13(-sin), _31(sin), _33(cos)
// z 회전 : _11(cos), _12(sin), _21(-sin), _22(cos)

//- 4(행) * 4(열)
//- 정방 행렬 : 행과 열의 수가 일치하는 상태, 연산의 편의성 때문
//- 항등 행렬 : 항상 연산의 결과가 같은 값을 가지는 형태, 기호로 I, 행렬의 초기화 상태
//
//1 0
//0 1
//
//1 0 0
//0 1 0
//0 0 1
//
//
//1 0 0 0	->	right(dir)
//0 1 0 0	->  up	(dir)
//0 0 1 0	->  look(dir)
//0 0 0 1	->  pos	(pos)


// 행렬의 곱셈 법칙

//1. 두 행렬을 곱셈하려면 앞의 행렬의 열의 값과 뒤의 행렬의 행의 값이 일치해야 한다.
//2. 두 행렬의 곱셈의 결과는 앞의 행렬의 행과 뒤의 행렬의 열의 조합으로 발생한다.
//3. 행렬의 곱셈은 교환 법칙이 항상 성립하지는 않는다.
//// A * B /= B * A
//4. 항등 행렬과 곱셈 시에는 교환 법칙이 성립한다.
//// A * I == I * A
//5. A 행렬과 그 행렬의 역행렬을 곱셈하게 되면 항등 행렬이 결과로 발생한다.
//// A * A^-1 == I	-> A / A == I

// 월드 행렬을 구성하는 순서

// - 필요에 의해 존재해야 하는 행렬들이 있다면 반드시 곱셈 순서는 지켜야 한다.
// - 모두 있어야 하는 필수 요소는 아니다.

// 월드 행렬 = 크 * 자 * 이 * 공 * 부
// 
// 월드 행렬 = 크기 행렬 * 자전 행렬 * 이동 행렬 * (공전 행렬 * 부모(위치) 행렬)
// 
// 크기 * (x * y * z)

// 크기 변환 행렬을 만들어주는 함수
//D3DXMatrixScaling(결과를 저장할 행렬의 주소, x배율, y배율, z배율)
//
//// x축 회전 행렬을 만들어주는 함수
//D3DXMatrixRotationX(결과를 저장할 행렬의 주소, 회전 각도(라디안))
//D3DXMatrixRotationY(결과를 저장할 행렬의 주소, 회전 각도(라디안))
//D3DXMatrixRotationZ(결과를 저장할 행렬의 주소, 회전 각도(라디안))
//
//// 이동 변환 행렬을 만들어주는 함수
//D3DXMatrixTranslation(결과를 저장할 행렬의 주소, x좌표,y좌표, z좌표)

// 항등 행렬을 만들어주는 함수
// D3DXMatrixIdentity(&matWorld);

// 각종 행렬을 구성하는 함수가 가장 먼저 수행하는 동작 과정은
// 결과를 저장할 행렬을 항등 행렬로 만드는 작업부터 한다.

//D3DXMATRIX	matScale, matRotZ, matTrans;
//
//D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
//D3DXMatrixRotationZ(&matRotZ, D3DXToRadian(45.f));
//D3DXMatrixTranslation(&matTrans, 400.f, 300.f, 0.f);
//
//matWorld = matScale * matRotZ * matTrans;

// 벡터와 행렬의 곱셈을 수행시키는 함수
// D3DXVec3TransformCoord(결과 값(위치)을 저장할 벡터의 주소, 행렬과 곱셈을 수행할 위치 벡터의 주소, 곱셈을 수행할 행렬의 주소)
// D3DXVec3TransformNormal(결과 값(방향)을 저장할 벡터의 주소, 행렬과 곱셈을 수행할 방향 벡터의 주소, 곱셈을 수행할 행렬의 주소)




template<typename T>
void Safe_Delete(T& p)
{
	if (p)
	{
		delete p;
		p = nullptr;
	}
}

struct tagDelete
{
	template<typename T>
	void operator()(T& p)
	{
		if (p)
		{
			delete p;
			p = nullptr;
		}
	}
};
struct tagDeleteMap
{
	template<typename T>
	void operator()(T& pair)
	{
		if (pair.second)
		{
			delete pair.second;
			pair.second = nullptr;
		}
	}
};

struct tagFinder
{
	tagFinder(const TCHAR* pTag) : m_pTag(pTag) {}

	template<typename T>
	bool operator()(T& Pair)
	{
		return !lstrcmp(Pair.first, m_pTag);
	}

	const TCHAR* m_pTag;
};

static D3DXVECTOR3	GetMouse()
{
	POINT		pt{};

	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	return D3DXVECTOR3((float)pt.x, (float)pt.y, 0.f);
}
