#pragma once

#define WINCX	800
#define WINCY	600

#define PI		3.141592f

#define PURE	= 0
template<typename T>
void SafeDelete(T& p)
{
	if (p)
	{
		delete p;
		p = nullptr;
	}
}
//
// 픽메세지는 메세지 큐가 비어있으면 false임
// 
// 윈도우 핸들을 definde.h에서 exturn을 사용해서 전역으로 사용할 수 있도록 함
//