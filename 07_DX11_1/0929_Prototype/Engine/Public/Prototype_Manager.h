#pragma once
#include "Engine_Defines.h"


// 1 레벨별로 원형객체들을 모아서 관리 - addprototype
// 2 원형 객체를 복제하여 사본객체를 생성 - cloneprototype

NS_BEGIN(Engine)
class CPrototype;
class CPrototype_Manager
{
private:
   CPrototype_Manager();
public:
   ~CPrototype_Manager() = default;

public:
   HRESULT Initialize(uint32_t iNumLevels);
   HRESULT Add_Prototype(uint32_t iLevelIndex, const wstring_t& strPrototypeTag, shared_ptr<CPrototype> pPrototype); //레벨넘버, 이름, 객체 를 가져옴
   shared_ptr<CPrototype> Clone_Prototype(uint32_t iLevelIndex, const wstring_t& strPrototypeTag, void* pArg);
   void   Clear(uint32_t iClearLevelIndex);

private:
   uint32_t      m_iNumLevels = {};

private:
   shared_ptr<CPrototype> Find_Prototype(uint32_t iLevelIndex, const wstring_t& strPrototypeTag);

private:
   typedef map<const wstring_t, shared_ptr<CPrototype>>         PROTOTYPES;

   //원본을 모아두는 컨테이너
   shared_ptr<PROTOTYPES[]>      m_pPrototypes = { nullptr };

   // 1. 배열의 크기를 클라이언트의 m_iNumLevels(Level개수)로 정하고 싶다
   // 2. 배열을 선언할 때 크기에 변수를 넣지 못함
   // 3. 배열의 크기를 동적으로 설정할 수 있는 동적배열
   // 4. 동적 배열은 포인터로 선언해야 동적할당을 할 수 있음
   // 5. 포인터로 동적할당하면 메모리 해제를 해야하는데 메모리 해제를 스마트포인터에서 맡기고 싶어서 shared_ptr로 선언

public:
   static unique_ptr<CPrototype_Manager>Create(uint32_t iNumLevels);

};

NS_END