#pragma once

#include "Client_Defines.h"

// CMainApp

// 객체 == 인스턴스


/*
class C이름
{
private: or protected:
	생성자	// Create에서 new
public: // 스마트 포인터
	소멸자
	
public:
	함수
protected:
	변수
protected:
	함수
private:
	변수
private:
	함수

public:
	생성관련된 함수.
	필요에 따라 소멸관련된 함수.
};
*/
namespace Client
{
	class CMainApp final// 자식 클래스
	{
	private:
		CMainApp();
	public:
		~CMainApp() = default; // 스마트 포인터를 사용하기 때문에 default로 설정. = default -> {}한 것과 같음. 가독성이 높음

	public:
		HRESULT		Initialize();
		void		Update();
		HRESULT		Render();

	public:
		static		unique_ptr<CMainApp>		Create();


	};
}
