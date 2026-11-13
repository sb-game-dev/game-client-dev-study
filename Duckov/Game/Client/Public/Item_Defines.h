#pragma once

#include "Client_Defines.h"
#include "ItemIconTable.h"

enum class ITEM_TYPE { GUN, MELEE, BULLET, ARMOR, ATTACH, BACKPACK, TOTEM, MEDICAL, FOOD, MISC, END };
typedef struct Item
{
	virtual ~Item() = default;
	ITEM_TYPE			eItemType;		    // 아이템 타입
	wstring_t		    strItemName;		// 이름
	wstring_t           strDesc;            // 아이템 설명
	bool_t				bStackable;		    // 중첩 가능 여부
	int32_t				iCount;			    // 개수
	f32_t				fWeight;			// 무게
	int32_t             iPrice;             // 가격


	int32_t				iTypeID;			// 같은 아이템인지 판단 (스택 합치기) / 아이콘 텍스처 배열 슬라이스
	int32_t				iMaxStack;			// 최대 겹침 수
	int32_t				iQuality;			// 1~6
	
	f32_t				fMaxDurability = 0.f;   // 0 = 내구도 없는 아이템(탄약/음식/키 등) -> 바 자체를 안 그림
	f32_t				fDurability = 0.f;
}ITEM;

enum class ATTACH_SLOT { SCOPE, MUZZLE, GRIP, STOCK, MAGAZINE, END };
typedef struct Attachment : ITEM
{
	ATTACH_SLOT eSlot;              // 부착물 종류

	// 부착물 능력치(총 능력치에 더하거나 곱함)
	f32_t   fSpreadMod;             // 탄퍼짐
	f32_t   fRecoilMod;             // 반동
	f32_t   fAimTimeMod;            // 조준 시간
	int32_t iMagazineBonus;         // 탄창 용량 증가
	f32_t   fZoom;                  // 조준경 배율
}ATTACHMENT;

enum class CALIBER { S, AR, L, END };
typedef struct Gun : ITEM
{
	CALIBER		eCaliber;                       // 탄환 종류

	f32_t		fDamage;                        // 공격력

	f32_t		fFireRate;                      // 발사 속도
	int32_t		iMagazineSize;                  // 탄창 용량
	f32_t		fReloadTime;                    // 재장전 시간

	f32_t		fAimTime;                       // 조준 시간

	f32_t		fHipFireSpread;                 // 조준 없이 발사시 탄퍼짐 정도
	f32_t		fAimSpread;                     // 조준 탄퍼짐 정도
	f32_t		fRecoilVertical;                // 수직 반동
	f32_t		fRecoilHorizontal;              // 수평 반동

	uint32_t                   iAllowedSlots;							// 총이 지원하는 칸 (비트마스크)
	shared_ptr<ATTACHMENT>     pAttachments[ETOUI(ATTACH_SLOT::END)];	// 끼운 부착물 (없으면 nullptr)
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
