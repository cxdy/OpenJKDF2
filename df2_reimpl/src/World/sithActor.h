#ifndef _SITHACTOR_H
#define _SITHACTOR_H

#define sithActor_Tick_ADDR (0x004ECBE0)
#define sithActor_Remove_ADDR (0x004ED760)
#define sithActor_cogMsg_OpenDoor_ADDR (0x004FC0A0)
#define sithActor_JumpWithVel_ADDR (0x004FC270)
#define sithActor_cogMsg_WarpThingToCheckpoint_ADDR (0x004FC450)

static void (*sithActor_Tick)(sithThing *thing, int deltaMs) = (void*)sithActor_Tick_ADDR;
static void (*sithActor_Remove)(sithThing *thing) = (void*)sithActor_Remove_ADDR;

#endif // _SITHACTOR_H