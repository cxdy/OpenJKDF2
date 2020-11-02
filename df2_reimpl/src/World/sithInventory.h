#ifndef _SITHINVENTORY_H
#define _SITHINVENTORY_H

#include <stdint.h>

#define sithInventory_NewEntry_ADDR (0x004D1120)
#define sithInventory_GetNumBinsWithFlag_ADDR (0x004D1180)
#define sithInventory_GetNumBinsWithFlagRev_ADDR (0x004D1220)
#define sithInventory_GetNumItemsPriorToIdx_ADDR (0x004D12C0)
#define sithInventory_GetNumItemsFollowingIdx_ADDR (0x004D1380)
#define sithInventory_SelectItem_ADDR (0x004D1440)
#define sithInventory_SelectItemPrior_ADDR (0x004D1540)
#define sithInventory_SelectItemFollowing_ADDR (0x004D15F0)
#define sithInventory_HasWeaponByIdx_ADDR (0x004D16A0)
#define sithInventory_GetBinByIdx_ADDR (0x004D16D0)
#define sithInventory_GetCurWeapon_ADDR (0x004D16F0)
#define sithInventory_SetCurWeapon_ADDR (0x004D1710)
#define sithInventory_GetCurItem_ADDR (0x004D1730)
#define sithInventory_SetCurItem_ADDR (0x004D1750)
#define sithInventory_GetCurPower_ADDR (0x004D1770)
#define sithInventory_SetCurPower_ADDR (0x004D1790)
#define sithInventory_GetWeaponPrior_ADDR (0x004D17B0)
#define sithInventory_GetWeaponFollowing_ADDR (0x004D1850)
#define sithInventory_GetPowerPrior_ADDR (0x004D18F0)
#define sithInventory_GetPowerFollowing_ADDR (0x004D1990)
#define sithInventory_SelectPowerPrior_ADDR (0x004D1A30)
#define sithInventory_SelectPowerFollowing_ADDR (0x004D1B90)
#define sithInventory_ActivateBin_ADDR (0x004D1CE0)
#define sithInventory_DeactivateBin_ADDR (0x004D1DA0)
#define sithInventory_BinSendActivate_ADDR (0x004D1E10)
#define sithInventory_BinSendDeactivate_ADDR (0x004D1E90)
#define sithInventory_ChangeInv_ADDR (0x004D1EF0)
#define sithInventory_GetBinAmount_ADDR (0x004D1FC0)
#define sithInventory_SetBinAmount_ADDR (0x004D2000)
#define sithInventory_SetActivate_ADDR (0x004D20C0)
#define sithInventory_GetActivate_ADDR (0x004D2110)
#define sithInventory_SetAvailable_ADDR (0x004D2150)
#define sithInventory_GetAvailable_ADDR (0x004D21A0)
#define sithInventory_SetCarries_ADDR (0x004D21E0)
#define sithInventory_GetCarries_ADDR (0x004D2230)
#define sithInventory_IsBackpackable_ADDR (0x004D2270)
#define sithInventory_SerializedWrite_ADDR (0x004D22A0)
#define sithInventory_GetMin_ADDR (0x004D2300)
#define sithInventory_GetMax_ADDR (0x004D2320)
#define sithInventory_SetFlags_ADDR (0x004D2340)
#define sithInventory_GetFlags_ADDR (0x004D2370)
#define sithInventory_UnsetFlags_ADDR (0x004D2390)
#define sithInventory_SendMessageToAllWithState_ADDR (0x004D23C0)
#define sithInventory_SendMessageToAllWithFlag_ADDR (0x004D24A0)
#define sithInventory_Reset_ADDR (0x004D2560)
#define sithInventory_ClearUncarried_ADDR (0x004D2700)
#define sithInventory_CreateBackpack_ADDR (0x004D2740)
#define sithInventory_PickupBackpack_ADDR (0x004D2860)
#define sithInventory_NthBackpackBin_ADDR (0x004D28C0)
#define sithInventory_NthBackpackValue_ADDR (0x004D28E0)
#define sithInventory_NumBackpackItems_ADDR (0x004D2910)
#define sithInventory_HandleInvSkillKeys_ADDR (0x004D2920)
#define sithInventory_sendfiremsg_ADDR (0x004D3020)
#define sithInventory_GetBin_ADDR (0x004D30B0)
#define sithInventory_GetItemDesc_ADDR (0x004D30F0)
#define sithInventory_items_init_related_ADDR (0x004D3120)
#define sithInventory_SetPowerKeybind_ADDR (0x004D3190)
#define sithInventory_GetPowerKeybind_ADDR (0x004D31C0)
#define sithInventory_ClearInventory_ADDR (0x004D31E0)
#define sithInventory_SendKilledMessageToAll_ADDR (0x004D3280)
#define sithInventory_SetBinWait_ADDR (0x004D32F0)
#define sithInventory_SelectPower_ADDR (0x004D3330)

enum ITEMINFO_FLAGS
{
    ITEMINFO_VALID   = 1,
    ITEMINFO_ITEM    = 2,
    ITEMINFO_WEAPON  = 4,
    ITEMINFO_POWER   = 8,
    ITEMINFO_ARMORED = 0x10,
    ITEMINFO_DEFAULT = 0x20,
    ITEMINFO_NOTCARRIED = 0x40,
    ITEMINFO_MP_BACKPACK = 0x80,
    ITEMINFO_HOTKEYABLE = 0x100
};

enum ITEMSTATE
{
    ITEMSTATE_1  = 1,
    ITEMSTATE_ACTIVATE  = 2,
    ITEMSTATE_AVAILABLE  = 4,
    ITEMSTATE_CARRIES = 8
};

typedef struct sithCog sithCog;
typedef struct sithThing sithThing;

typedef struct sithItemDescriptor
{
    uint32_t flags;
    char fpath[128];
    float ammoMin;
    float ammoMax;
    sithCog* cog;
    uint32_t field_90;
    uint32_t field_94;
    uint32_t used_in_render;
} sithItemDescriptor;

typedef struct sithItemInfo
{
    float ammoAmt;
    int field_4;
    int state;
    float activatedTimeSecs;
    float activationDelaySecs;
    float binWait;
} sithItemInfo;

#define sithInventory_aDescriptors ((sithItemDescriptor*)0x008BD1C0)
#define sithInventory_bUnk (*(int*)0x008339E4)
#define sithInventory_bUnkPower (*(int*)0x008339E8)

void sithInventory_NewEntry(int binIdx, sithCog *cog, char *name, float min, float max, int flags);
int sithInventory_GetNumBinsWithFlag(sithThing *thing, int binNum, int flags);
int sithInventory_GetNumBinsWithFlagRev(sithThing *thing, int binNum, int flags);
int sithInventory_GetNumItemsPriorToIdx(sithThing *thing, signed int binNumStart);
int sithInventory_GetNumItemsFollowingIdx(sithThing *thing, signed int binNumStart);
void sithInventory_SelectItem(sithThing *thing, int binIdx);
void sithInventory_SelectItemPrior(sithThing *thing);
void sithInventory_SelectItemFollowing(sithThing *thing);
int sithInventory_HasWeaponByIdx(int idx);
sithItemDescriptor* sithInventory_GetBinByIdx(int idx);
int sithInventory_GetCurWeapon(sithThing *player);
void sithInventory_SetCurWeapon(sithThing *player, int idx);
int sithInventory_GetCurItem(sithThing *player);
void sithInventory_SetCurItem(sithThing *player, int idx);
int sithInventory_GetCurPower(sithThing *player);
void sithInventory_SetCurPower(sithThing *player, int idx);
int sithInventory_GetWeaponPrior(sithThing *thing, int binNum);
int sithInventory_GetWeaponFollowing(sithThing *thing, int binNum);
int sithInventory_GetPowerPrior(sithThing *thing, int binNum);
int sithInventory_GetPowerFollowing(sithThing *thing, int binNum);
void sithInventory_SelectPower(sithThing *player, int binNum);
void sithInventory_SelectPowerPrior(sithThing *player);
void sithInventory_SelectPowerFollowing(sithThing *player);
int sithInventory_ActivateBin(sithThing *player, sithCog *cog, float delay, int binNum);
float sithInventory_DeactivateBin(sithThing *player, sithCog *unused, int binNum);
int sithInventory_BinSendActivate(sithThing *player, int binIdx);
void sithInventory_BinSendDeactivate(sithThing *player, int senderIndex);
float sithInventory_ChangeInv(sithThing *player, int binIdx, float amt);
float sithInventory_GetBinAmount(sithThing *player, int binIdx);
float sithInventory_SetBinAmount(sithThing *player, int binIdx, float amt);
void sithInventory_SetActivate(sithThing *player, int binIdx, int bActivate);
int sithInventory_GetActivate(sithThing *player, int binIdx);
void sithInventory_SetAvailable(sithThing *player, int binIdx, int bAvailable);
int sithInventory_GetAvailable(sithThing *player, int binIdx);
void sithInventory_SetCarries(sithThing *player, int binIdx, int bCarries);
int sithInventory_GetCarries(sithThing *player, int binIdx);
int sithInventory_IsBackpackable(sithThing *player, int binIdx);

float sithInventory_GetMin(sithThing *player, int binIdx);
float sithInventory_GetMax(sithThing *player, int binIdx);
void sithInventory_SetFlags(sithThing *player, int binIdx, int flags);
int sithInventory_GetFlags(sithThing *player, int binIdx);
void sithInventory_UnsetFlags(sithThing *player, int binIdx, int flags);
float sithInventory_SendMessageToAllWithState(sithThing *player, int sourceType, int sourceIdx, int msgid, int stateFlags, float param0, float param1, float param2, float param3);
float sithInventory_SendMessageToAllWithFlag(sithThing *player, int sourceType, int sourceIdx, int msgid, int flags, float param0, float param1, float param2, float param3);
void sithInventory_ClearUncarried(sithThing *player);

void sithInventory_ClearInventory(sithThing *player);
void sithInventory_SendKilledMessageToAll(sithThing *player, sithThing *sender);
void sithInventory_SetBinWait(sithThing *player, int binIdx, float wait);

#endif // _SITHINVENTORY_H
