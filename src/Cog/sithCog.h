#ifndef _SITHCOG_H
#define _SITHCOG_H

#include "types.h"
#include "globals.h"
#include "sithCogVm.h"
#include "sithCogScript.h"

#define jkCog_RegisterVerbs_ADDR (0x40A110)
#define jkCog_Initialize_ADDR (0x40A0C0)
#define sithCogFunction_Initialize_ADDR (0x00505400)
#define sithCogFunctionThing_Initialize_ADDR (0x005014E0)
#define sithCogFunctionAI_Initialize_ADDR (0x00500B00)
#define sithCogFunctionSound_Initialize_ADDR (0x004FF060)
#define sithCogFunctionPlayer_Initialize_ADDR (0x004E0780)
#define sithCogFunctionSector_Initialize_ADDR (0x004FE680)
#define sithCogFunctionSurface_Initialize_ADDR (0x004FFB50)

#define sithCog_Startup_ADDR (0x004DE070)
#define sithCog_Shutdown_ADDR (0x004DE590)
#define sithCog_Open_ADDR (0x004DE5D0)
#define sithCog_Close_ADDR (0x004DE7E0)
#define sithCog_Free_ADDR (0x004DE820)
#define sithCog_FreeEntry_ADDR (0x004DE9B0)
#define sithCog_Free2_ADDR (0x004DEA20)
#define sithCog_HandleThingTimerPulse_ADDR (0x004DEA60)
#define sithCog_SendSimpleMessageToAll_ADDR (0x004DEAD0)
#define sithCog_SendMessageToAll_ADDR (0x004DEB00)
#define sithCog_SendMessage_ADDR (0x004DEBE0)
#define sithCog_SendMessageEx_ADDR (0x004DEDC0)
#define sithCog_InitScripts_ADDR (0x004DEFF0)
#define sithCog_InitCogs_ADDR (0x004DF080)
#define sithCog_Load_ADDR (0x004DF110)
#define sithCog_LoadEntry_ADDR (0x004DF410)
#define sithCog_ThingsSectorsRegSymbolIdk_ADDR (0x004DF610)
#define sithCog_LoadCogscript_ADDR (0x004DF7D0)
#define sithCog_GetByIdx_ADDR (0x004DF930)
#define sithCog_ThingFromSymbolidk_ADDR (0x004DF980)
#define sithCog_Thingidk_ADDR (0x004DFA00)
#define sithCog_Sectoridk_ADDR (0x004DFA60)
#define sithCog_SendMessageFromThing_ADDR (0x004DFAC0)
#define sithCog_SendMessageFromThingEx_ADDR (0x004DFAF0)
#define sithCog_SendMessageFromSector_ADDR (0x004DFD60)
#define sithCog_SendMessageFromSectorEx_ADDR (0x004DFD90)
#define sithCog_SendMessageFromSurface_ADDR (0x004DFED0)
#define sithCog_SendMessageFromSurfaceEx_ADDR (0x004DFF00)
#define sithCogScript_Load_ADDR (0x004E0040)
#define sithCogScript_LoadEntry_ADDR (0x004E0240)
#define sithCogScript_Tick_ADDR (0x004E0300)
#define sithCogScript_TickAll_ADDR (0x004E0400)
#define sithCogScript_DevCmdCogStatus_ADDR (0x004E0480)
#define sithCogScript_RegisterMessageSymbol_ADDR (0x004E0600)
#define sithCogScript_TimerTick_ADDR (0x004E0640)
#define sithCogScript_RegisterGlobalMessage_ADDR (0x004E06C0)
#define sithCogScript_RegisterVerb_ADDR (0x004E0700)

#define NETMSG_START intptr_t craftingPacket = (intptr_t)&sithCogVm_netMsgTmp.pktData[0];
#define NETMSG_PUSHU8(x) {*(uint8_t*)craftingPacket = x; craftingPacket += sizeof(uint8_t);};
#define NETMSG_PUSHU16(x) {*(uint16_t*)craftingPacket = x; craftingPacket += sizeof(uint16_t);};
#define NETMSG_PUSHS16(x) {*(int16_t*)craftingPacket = x; craftingPacket += sizeof(int16_t);};
#define NETMSG_PUSHU32(x) {*(uint32_t*)craftingPacket = x; craftingPacket += sizeof(uint32_t);};
#define NETMSG_PUSHS32(x) {*(int32_t*)craftingPacket = x; craftingPacket += sizeof(int32_t);};
#define NETMSG_PUSHF32(x) {*(float*)craftingPacket = x; craftingPacket += sizeof(float);};
#define NETMSG_PUSHVEC2(x) {*(rdVector2*)craftingPacket = x; craftingPacket += sizeof(rdVector2);};
#define NETMSG_PUSHVEC3(x) {*(rdVector3*)craftingPacket = x; craftingPacket += sizeof(rdVector3);};
#define NETMSG_PUSHVEC3I(x) {*(rdVector3i*)craftingPacket = x; craftingPacket += sizeof(rdVector3i);};
#define NETMSG_PUSHMAT34(x) {*(rdMatrix34*)craftingPacket = x; craftingPacket += sizeof(rdMatrix34);};
#define NETMSG_PUSHSTR(x,l) {_strncpy((char*)craftingPacket, x, (l)-1); ((char*)craftingPacket)[(l)-1] = 0; craftingPacket += (l);};
#define NETMSG_END(msgid) { size_t len = (intptr_t)craftingPacket - (intptr_t)&sithCogVm_netMsgTmp.pktData[0]; \
                            sithCogVm_netMsgTmp.netMsg.flag_maybe = 0; \
                            sithCogVm_netMsgTmp.netMsg.cogMsgId = msgid; \
                            sithCogVm_netMsgTmp.netMsg.msg_size = len; \
                          };

#define NETMSG_IN_START(x) intptr_t _readingPacket = (intptr_t)&x->pktData[0]; uint8_t _readingOutU8; \
uint16_t _readingOutU16; int16_t _readingOutS16; uint32_t _readingOutU32; \
int32_t _readingOutS32; float _readingOutFloat; rdVector2 _readingOutV2; \
rdVector3 _readingOutV3; rdVector3i _readingOutV3i; rdMatrix34 _readingOutM34;

#define NETMSG_POPU8() (_readingOutU8 = *(uint8_t*)_readingPacket, _readingPacket += sizeof(uint8_t), _readingOutU8)
#define NETMSG_POPU16() (_readingOutU16 = *(uint16_t*)_readingPacket, _readingPacket += sizeof(uint16_t), _readingOutU16)
#define NETMSG_POPS16() (_readingOutS16 = *(int16_t*)_readingPacket, _readingPacket += sizeof(int16_t), _readingOutS16)
#define NETMSG_POPU32() (_readingOutU32 = *(uint32_t*)_readingPacket, _readingPacket += sizeof(uint32_t), _readingOutU32)
#define NETMSG_POPS32() (_readingOutS32 = *(int32_t*)_readingPacket, _readingPacket += sizeof(int32_t), _readingOutS32)
#define NETMSG_POPF32() (_readingOutFloat = *(float*)_readingPacket, _readingPacket += sizeof(float), _readingOutFloat)
#define NETMSG_POPVEC2() (_readingOutV2 = *(rdVector2*)_readingPacket, _readingPacket += sizeof(rdVector2), _readingOutV2)
#define NETMSG_POPVEC3() (_readingOutV3 = *(rdVector3*)_readingPacket, _readingPacket += sizeof(rdVector3), _readingOutV3)
#define NETMSG_POPVEC3I() (_readingOutV3i = *(rdVector3i*)_readingPacket, _readingPacket += sizeof(rdVector3i), _readingOutV3i)
#define NETMSG_POPMAT34() (_readingOutM34 = *(rdMatrix34*)_readingPacket, _readingPacket += sizeof(rdMatrix34), _readingOutM34)
#define NETMSG_POPSTR(x,l) { _strncpy((x), (char*)_readingPacket, (l)-1); (x)[(l)-1] = 0; _readingPacket += (l); }
#define NETMSG_IN_END {}

typedef int SITH_MESSAGE;

enum SITH_MESSAGE_E
{
    SITH_MESSAGE_0   = 0,
    SITH_MESSAGE_ACTIVATE  = 1,
    SITH_MESSAGE_REMOVED  = 2,
    SITH_MESSAGE_STARTUP  = 3,
    SITH_MESSAGE_TIMER  = 4,
    SITH_MESSAGE_BLOCKED  = 5,
    SITH_MESSAGE_ENTERED  = 6,
    SITH_MESSAGE_EXITED  = 7,
    SITH_MESSAGE_CROSSED  = 8,
    SITH_MESSAGE_SIGHTED  = 9,
    SITH_MESSAGE_DAMAGED  = 10,
    SITH_MESSAGE_ARRIVED  = 11,
    SITH_MESSAGE_KILLED  = 12,
    SITH_MESSAGE_PULSE  = 13,
    SITH_MESSAGE_TOUCHED  = 14,
    SITH_MESSAGE_CREATED  = 15,
    SITH_MESSAGE_LOADING  = 16,
    SITH_MESSAGE_SELECTED  = 17,
    SITH_MESSAGE_DESELECTED  = 18,
    SITH_MESSAGE_AUTOSELECT  = 19,
    SITH_MESSAGE_CHANGED  = 20,
    SITH_MESSAGE_DEACTIVATED  = 21,
    SITH_MESSAGE_SHUTDOWN  = 22,
    SITH_MESSAGE_RESPAWN  = 23,
    SITH_MESSAGE_AIEVENT  = 24,
    SITH_MESSAGE_SKILL  = 25,
    SITH_MESSAGE_TAKEN  = 26,
    SITH_MESSAGE_USER0  = 27,
    SITH_MESSAGE_USER1  = 28,
    SITH_MESSAGE_USER2  = 29,
    SITH_MESSAGE_USER3  = 30,
    SITH_MESSAGE_USER4  = 31,
    SITH_MESSAGE_USER5  = 32,
    SITH_MESSAGE_USER6  = 33,
    SITH_MESSAGE_USER7  = 34,
    SITH_MESSAGE_NEWPLAYER  = 35,
    SITH_MESSAGE_FIRE  = 36,
    SITH_MESSAGE_JOIN  = 37,
    SITH_MESSAGE_LEAVE  = 38,
    SITH_MESSAGE_SPLASH  = 39,
    SITH_MESSAGE_TRIGGER  = 40,
};

static int (*_sithCog_Load)(sithWorld *world, int a2) = (void*)sithCog_Load_ADDR;
//static int (*sithCogScript_Load)(sithWorld *world, int a2) = (void*)sithCogScript_Load_ADDR;
//static void (*sithCogScript_RegisterVerb)(void* a, intptr_t func, char* cmd) = (void*)0x4E0700;
//static void (__cdecl *sithCog_SendMessage)(sithCog *a1, int msgid, int senderType, int senderIndex, int sourceType, int sourceIndex, int linkId) = (void*)0x4DEBE0;
//static float (__cdecl *sithCog_SendMessageEx)(sithCog *a1, SITH_MESSAGE message, int senderType, int senderIndex, int sourceType, int sourceIndex, int linkId, float param0, float param1, float param2, float param3) = (void*)0x4DEDC0;
//static void (*sithCog_HandleThingTimerPulse)(sithThing *a1) = (void*)sithCog_HandleThingTimerPulse_ADDR;
//static int (*sithCog_ThingsSectorsRegSymbolIdk)(sithCog *a1, sithCogReference *a2, sithCogSymbol *a3) = (void*)sithCog_ThingsSectorsRegSymbolIdk_ADDR;
static sithCog* (*_sithCog_LoadCogscript)(const char *fpath) = (void*)sithCog_LoadCogscript_ADDR;

int sithCog_Startup();
void sithCog_Shutdown();
int sithCog_Open();
void sithCog_Close();
int sithCog_Load(sithWorld *world, int a2);
sithCog* sithCog_LoadCogscript(const char *fpath);
int sithCog_LoadEntry(sithCogSymbol *cogSymbol, sithCogReference *cogIdk, char *val);
int sithCog_ThingsSectorsRegSymbolIdk(sithCog *cog, sithCogReference *idk, sithCogSymbol *symbol);
void sithCog_HandleThingTimerPulse(sithThing *thing);

void sithCogFunction_Initialize(void* a1);
void sithCogThing_Initialize(void* a1);
void sithCogFunctionSound_Initialize(void* a1);
void sithCogFunctionSector_Initialize(void* a1);
void sithCogSurface_Initialize(void* a1);

void sithCog_SendMessageFromThing(sithThing *a1, sithThing *a2, int msg);
float sithCog_SendMessageFromThingEx(sithThing *sender, sithThing *receiver, SITH_MESSAGE message, float param0, float param1, float param2, float param3);
void sithCog_SendMessageFromSurface(sithSurface *surface, sithThing *thing, int msg);
double sithCog_SendMessageFromSurfaceEx(sithSurface *sender, sithThing *thing, SITH_MESSAGE msg, float a4, float a5, float a6, float a7);
void sithCog_SendMessageFromSector(sithSector *sector, sithThing *thing, int message);
float sithCog_SendMessageFromSectorEx(sithSector *a1, sithThing *sourceType, SITH_MESSAGE message, float param0, float param1, float param2, float param3);
void sithCog_SendSimpleMessageToAll(int a1, int a2, int a3, int a4, int a5);
void sithCog_SendMessageToAll(int cmdid, int senderType, int senderIdx, int sourceType, int sourceIdx, float arg0, float arg1, float arg2, float arg3);
void sithCog_SendMessage(sithCog *cog, int msgid, int senderType, int senderIndex, int sourceType, int sourceIndex, int linkId);
float sithCog_SendMessageEx(sithCog *cog, int message, int senderType, int senderIndex, int sourceType, int sourceIndex, int linkId, float param0, float param1, float param2, float param3);
void sithCog_Free(sithWorld *world);

static int (*_sithCog_Open)() = (void*)sithCog_Open_ADDR;
//static double (*sithCog_SendMessageFromSurfaceEx)(sithSurface *a1, sithThing *a2, int a3, float a4, float a5, float a6, float a7) = (void*)sithCog_SendMessageFromSurfaceEx_ADDR;
static float (*_sithCog_SendMessageFromThingEx)(sithThing *sender, sithThing *receiver, SITH_MESSAGE message, float param0, float param1, float param2, float param3) = (void*)sithCog_SendMessageFromThingEx_ADDR;
//static void (*sithCog_SendMessageFromSectorEx)(sithSector *a1, sithThing *sourceType, SITH_MESSAGE message, float param0, float param1, float param2, float param3) = (void*)sithCog_SendMessageFromSectorEx_ADDR;
//static void (*sithCog_SendMessageToAll)(int cmdid, int senderType, int senderIdx, int sourceType, int sourceIdx, float arg0, float arg1, float arg2, float arg3) = (void*)sithCog_SendMessageToAll_ADDR;
//static void (*sithCog_Free)(sithWorld* world) = (void*)sithCog_Free_ADDR;
//static void (*sithCogScript_Tick)(sithCog* cog) = (void*)sithCogScript_Tick_ADDR;

int sithCogScript_Load(sithWorld *lvl, int a2);
void sithCogScript_RegisterVerb(sithCogSymboltable *a1, cogSymbolFunc_t a2, char *a3);
void sithCogScript_RegisterMessageSymbol(sithCogSymboltable *a1, int a2, const char *a3);
void sithCogScript_RegisterGlobalMessage(sithCogSymboltable *a1, const char *a2, int a3);
void sithCogScript_TickAll();
void sithCogScript_Tick(sithCog *cog);
int sithCogScript_TimerTick(int deltaMs, sithEventInfo *info);
void sithCogScript_DevCmdCogStatus(stdDebugConsoleCmd *cmd, char *extra);
sithCog* sithCog_GetByIdx(int idx);

#endif // _SITHCOG_H
