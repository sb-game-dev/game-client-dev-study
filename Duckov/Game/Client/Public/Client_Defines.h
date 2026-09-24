#pragma once

// 클라이언트에서 제작하는 클래스들이 이용할 공통적인 것들
#include <Windows.h>
#include <memory>
#include "Engine_Defines.h"
#include "GameInstance.h"
namespace Client
{
	static constexpr uint32_t g_iWinSizeX = 1280;
	static constexpr uint32_t g_iWinSizeY = 720;
};

using namespace std;
using namespace Client;
using namespace Engine;

extern HWND	g_hWnd;

enum class ITEM_TYPE { GUN, MELEE, BULLET, ARMOR, ATTACH, BACKPACK, TOTEM, MEDICAL, FOOD, MISC, END };
typedef struct Item
{
	ITEM_TYPE			eItemType;		    // 아이템 타입
	wstring_t		    strItemName;		// 이름
	wstring_t           strDesc;            // 아이템 설명
	bool				bStackable;		    // 중첩 가능 여부
	int					iCount;			    // 개수
	f32_t				fWeight;			// 무게
	int                 iPrice;             // 가격
}ITEM;

enum class CALIBER { S, AR, L, END };
typedef struct Gun : ITEM
{
	CALIBER	eCaliber;                       // 탄환 종류

	f32_t   fDamage;                        // 공격력

	f32_t   fFireRate;                      // 발사 속도
	int     iMagazineSize;                  // 탄창 용량
	f32_t   fReloadTime;                    // 재장전 시간

	f32_t   fAimTime;                       // 조준 시간

	f32_t   fHipFireSpread;                 // 조준 없이 발사시 탄퍼짐 정도
	f32_t   fAimSpread;                     // 조준 탄퍼짐 정도
	f32_t   fRecoilVertical;                // 수직 반동
	f32_t   fRecoilHorizontal;              // 수평 반동
}GUN;

typedef struct Melee : ITEM
{
	f32_t   fDamage;                        // 공격력
	f32_t   fAttackSpeed;                   // 공격 속도
}MELEE;

enum class ARMOR_SLOT { HEAD, BODY, END };
typedef struct Armor : ITEM
{
	ARMOR_SLOT eSlot;                       // 머리 방어구 / 신체 방어구
	f32_t      fArmorLevel;                 // 방어구 수치 
}ARMOR;

typedef struct Backpack : ITEM
{
	f32_t   fMaxWeightBonus;                // 최대 소지 중량
	int     iSlotBonus;                     // 가방 공간     
}BACKPACK;


enum class EQUIP_SLOT
{
	GUN_1, GUN_2,       // 총기 ×2
	MELEE,              // 근접 무기
	HEAD, BODY,         // 머리, 신체
	FACE, HEADSET,      // 얼굴, 헤드폰
	BACKPACK,           // 가방
	TOTEM_1, TOTEM_2,   // 토템 ×2
	END
};


