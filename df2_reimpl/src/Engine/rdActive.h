#ifndef _RDACTIVE_H
#define _RDACTIVE_H

#define rdActive_Startup_ADDR (0x0044BBC0)
#define rdActive_AdvanceFrame_ADDR (0x0044BBD0)
#define rdActive_ClearFrameCounters_ADDR (0x0044BC70)
#define rdActive_DrawScene_ADDR (0x0044BC80)
#define rdActive_BuildSpans_ADDR (0x0044BE00)
#define rdActive_AddNewEdges_ADDR (0x0044C640)
#define rdActive_BuildEdges_ADDR (0x0044C690)
#define rdActive_AddActiveFace_ADDR (0x0044C7E0)

static int (*rdActive_Startup)(void) = (void*)rdActive_Startup_ADDR;
static void (*rdActive_ClearFrameCounters)(void) = (void*)rdActive_ClearFrameCounters_ADDR;

#endif // _RDACTIVE_H
