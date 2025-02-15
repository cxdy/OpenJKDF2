#include "sithTrackThing.h"

#include "General/stdConffile.h"
#include "General/stdMath.h"
#include "Engine/sithSoundClass.h"
#include "Engine/sithCollision.h"
#include "World/jkPlayer.h"
#include "Cog/sithCog.h"
#include "jk.h"

void sithTrackThing_MoveToFrame(sithThing *thing, int goalFrame, float a3)
{
    if ( goalFrame < thing->trackParams.loadedFrames )
    {
        thing->trackParams.field_C |= 4u;
        thing->trackParams.field_20 = a3;
        thing->goalframe = goalFrame;
        sithSoundClass_ThingPlaySoundclass4(thing, SITH_SC_STARTMOVE);
        sithSoundClass_ThingPlaySoundclass4(thing, SITH_SC_MOVING);
        sithTrackThing_Arrivedidk(thing);
    }
}

void sithTrackThing_Arrivedidk(sithThing *thing)
{
    int v2; // eax
    int v3; // edi
    sithThingFrame *v4; // edx
    int v5; // eax
    long double v8; // st7
    long double v9; // st6
    sithThingFrame *v12; // eax
    double v13; // st7
    sithThingFrame *v14; // eax
    long double v15; // st7
    long double v16; // st6
    float thinga; // [esp+10h] [ebp+4h]

    v2 = thing->curframe;
    v3 = thing->goalframe;
    if ( v2 == v3 )
    {
        v4 = thing->trackParams.frames;
        v5 = v2;
        thing->trackParams.vel.x = v4[v5].pos.x - thing->position.x;
        thing->trackParams.vel.y = v4[v5].pos.y - thing->position.y;
        thing->trackParams.vel.z = v4[v5].pos.z - thing->position.z;
        v8 = rdVector_Normalize3Acc(&thing->trackParams.vel);
        if ( v8 != 0.0 )
        {
            v9 = v8 / thing->trackParams.field_20;
            thing->field_250 = 0;
            thing->trackParams.field_C |= 1;
            thing->trackParams.field_1C = v9;
        }
        thinga = thing->trackParams.field_1C;
        if ( thing->trackParams.field_1C == 0.0 )
        {
            thing->trackParams.field_C &= 0xE8;
            thing->trackParams.field_20 = 0.0;
            thing->goalframe = 0;
            thing->field_258 = 0;
            thing->field_250 = 0;
            sithSoundClass_ThingPauseSoundclass(thing, SITH_SC_MOVING);
            sithSoundClass_ThingPlaySoundclass4(thing, SITH_SC_STOPMOVE);
            if ( (thing->thingflags & SITH_TF_CAPTURED) != 0 && (thing->thingflags & SITH_TF_INVULN) == 0 )
                sithCog_SendMessageFromThing(thing, 0, SITH_MESSAGE_ARRIVED);
            return;
        }
        v3 = thing->goalframe;
    }
    else
    {
        if ( v2 >= 0 )
            v3 = v2 + (v3 - thing->curframe >= 0 ? 1 : -1);

        // Added
        //if (v3 < 0)
        //    v3 = 0;
        //if (v3 >= thing->trackParams.numFrames)
        //    v3 = 0;//thing->trackParams.numFrames - 1;

        v12 = thing->trackParams.frames;
        thing->field_258 = v3;
        v13 = v12[v3].pos.x - thing->position.x;
        v14 = &v12[v3];
        thing->trackParams.vel.x = v13;
        thing->trackParams.vel.y = v14->pos.y - thing->position.y;
        thing->trackParams.vel.z = v14->pos.z - thing->position.z;
        v15 = rdVector_Normalize3Acc(&thing->trackParams.vel);
        if ( v15 != 0.0 )
        {
            v16 = v15 / thing->trackParams.field_20;
            thing->field_250 = 0;
            thing->trackParams.field_C |= 1;
            thing->trackParams.field_1C = v16;
        }
        thinga = thing->trackParams.field_1C;
    }
    if ( thinga < 1.0 )
        thinga = 1.0;
    sithTrackThing_sub_4FAD50(thing, &thing->trackParams.frames[v3].rot, thinga);
}

void sithTrackThing_Tick(sithThing *thing, float deltaSeconds)
{
    int v3; // eax
    double v4; // st7
    double v5; // st7
    double v6; // st7
    double v7; // st6
    double v8; // st7
    double v9; // st6
    double v10; // rt1
    double v11; // st6
    double v12; // st7
    double v16; // st7
    double v18; // st7
    double v19; // st6
    double v20; // st7
    double v22; // st7
    double v24; // st6
    double v26; // st7
    double v28; // st7
    double v30; // st7
    double v31; // st7
    double v33; // st6
    int v37; // eax
    int v38; // ecx
    sithThing *v39; // [esp-14h] [ebp-64h]
    float a6; // [esp+0h] [ebp-50h]
    float v41; // [esp+4h] [ebp-4Ch]
    float v42; // [esp+4h] [ebp-4Ch]
    rdVector3 rot; // [esp+8h] [ebp-48h] BYREF
    rdVector3 a1a; // [esp+14h] [ebp-3Ch] BYREF
    rdMatrix34 a; // [esp+20h] [ebp-30h] BYREF
    float a3; // [esp+54h] [ebp+4h]
    float a3a; // [esp+54h] [ebp+4h]
    float deltaSecondsa; // [esp+58h] [ebp+8h]

    if ( deltaSeconds != 0.0 )
    {
        v3 = thing->trackParams.field_C;
        if ( v3 )
        {
            if ( (v3 & 0x80u) == 0 )
            {
                if ( (v3 & 2) != 0 )
                {
                    v4 = thing->trackParams.field_54 * deltaSeconds;
                    v41 = v4;
                    v5 = v4 + thing->field_24C;
                    a3 = v5;
                    if ( v5 > 1.0 )
                    {
                        a3 = 1.0;
                        v41 = 1.0 - thing->field_24C;
                    }
                    v6 = thing->trackParams.field_64.y * a3;
                    v7 = thing->trackParams.field_64.z * a3;
                    rot.x = thing->trackParams.field_64.x * a3;
                    rot.y = v6;
                    rot.z = v7;
                    _memcpy(&a, &thing->trackParams.field_24, sizeof(a));
                    rdMatrix_PostRotate34(&a, &rot);
                    if ( (thing->trackParams.field_C & 0x10) != 0 )
                    {
                        v8 = thing->trackParams.field_58.y + a.scale.y;
                        v9 = thing->trackParams.field_58.z + a.scale.z;
                        a1a.x = thing->trackParams.field_58.x + a.scale.x - thing->position.x;
                        v10 = v9;
                        v11 = v8 - thing->position.y;
                        v12 = v10 - thing->position.z;
                        a1a.y = v11;
                        a1a.z = v12;
                        if ( a1a.x != 0.0 || a1a.y != 0.0 || a1a.z != 0.0 )
                        {
                            a6 = rdVector_Normalize3Acc(&a1a);
                            v16 = a6;
                            if ( v16 < 0.0 )
                                v16 = -v16;
                            if ( v16 <= 0.0000099999997 )
                                a6 = 0.0;
                            if ( a6 != 0.0 )
                            {
                                v18 = sithCollision_UpdateThingCollision(thing, &a1a, a6, 0x44);
                                if ( v18 < a6 )
                                {
                                    _memcpy(&a, &thing->trackParams.field_24, sizeof(a));
                                    a3 = v18 / a6 * v41 + thing->field_24C;
                                    v19 = thing->trackParams.field_64.y * a3;
                                    v20 = thing->trackParams.field_64.z * a3;
                                    rot.x = thing->trackParams.field_64.x * a3;
                                    rot.y = v19;
                                    rot.z = v20;
                                    rdMatrix_PreRotate34(&a, &rot);
                                }
                            }
                        }
                    }
                    thing->field_24C = a3;
                    thing->lookOrientation.scale.x = 0.0;
                    thing->lookOrientation.scale.y = 0.0;
                    thing->lookOrientation.scale.z = 0.0;
                    sithCollision_sub_4E77A0(thing, &a);
                    if ( thing->field_24C >= 1.0 )
                    {
                        if ( (thing->trackParams.field_C & 0x10) == 0 )
                        {
                            rdMatrix_BuildRotate34(&a, &thing->trackParams.orientation);
                            thing->lookOrientation.scale.x = 0.0;
                            thing->lookOrientation.scale.y = 0.0;
                            thing->lookOrientation.scale.z = 0.0;
                            sithCollision_sub_4E77A0(thing, &a);
                        }
                        thing->trackParams.field_C &= ~0x12;
                    }
                }
                if ( (thing->trackParams.field_C & 1) != 0 )
                {
                    if ( thing->trackParams.field_1C <= (double)deltaSeconds )
                        v22 = thing->trackParams.field_1C;
                    else
                        v22 = deltaSeconds;
                    v42 = v22;
                    deltaSecondsa = thing->trackParams.field_20 * v22;
                    v24 = deltaSecondsa;
                    if ( v24 < 0.0 )
                        v24 = -v24;
                    if ( v24 <= 0.0000099999997 )
                        deltaSecondsa = 0.0;
                    if ( deltaSecondsa != 0.0 )
                    {
                        v26 = sithCollision_UpdateThingCollision(thing, &thing->trackParams.vel, deltaSecondsa, 68);
                        a3a = v26;
                        if ( v26 >= deltaSecondsa )
                        {
                            v22 = v42;
                        }
                        else
                        {
                            v28 = a3a;
                            if ( v28 < 0.0 )
                                v28 = -v28;
                            if ( v28 <= 0.0000099999997 )
                                v30 = 0.0;
                            else
                                v30 = a3a;
                            if ( v30 <= 0.0 )
                            {
                                v22 = 0.0;
                                ++thing->field_250;
                            }
                            else
                            {
                                ++thing->field_250;
                                v22 = a3a / deltaSecondsa * v42;
                            }
                        }
                    }
                    v31 = thing->trackParams.field_1C - v22;
                    thing->trackParams.field_1C = v31;
                    v33 = v31;
                    if ( v33 < 0.0 )
                        v33 = -v31;
                    if ( v33 <= 0.0000099999997 )
                        v31 = 0.0;
                    if ( v31 == 0.0 )
                    {
                        thing->trackParams.field_C &= ~1;
                    }
                    else if ( thing->field_250 > 2u && (thing->thingflags & SITH_TF_CAPTURED) != 0 && (thing->thingflags & SITH_TF_INVULN) == 0 )
                    {
                        sithCog_SendMessageFromThing(thing, 0, SITH_MESSAGE_BLOCKED);
                    }
                }
                if ( (thing->trackParams.field_C & 3) == 0 )
                {
                    if ( (thing->trackParams.field_C & 4) != 0 )
                    {
                        v37 = thing->field_258;
                        v38 = thing->goalframe;
                        thing->curframe = v37;
                        v39 = thing;
                        if ( v37 != v38 )
                        {
                            sithTrackThing_Arrivedidk(thing);
                            return;
                        }
                    }
                    else
                    {
                        v39 = thing;
                        thing->curframe = thing->field_258;
                    }
                    sithTrackThing_Stop(v39);
                }
            }
        }
    }
}

void sithTrackThing_sub_4FAD50(sithThing *thing, rdVector3 *a2, float a3)
{
    double v4; // st7
    double v7; // st7
    double v10; // st7
    float v12; // eax
    float v13; // edx
    float v15; // [esp+0h] [ebp-2Ch]
    float v16; // [esp+14h] [ebp-18h]
    float v17; // [esp+18h] [ebp-14h]
    float v18; // [esp+18h] [ebp-14h]
    float v18_hi;
    float v19; // [esp+1Ch] [ebp-10h]
    rdVector3 out; // [esp+20h] [ebp-Ch] BYREF

    rdMatrix_ExtractAngles34(&thing->lookOrientation, &out);
    v17 = a2->y - out.y;
    v19 = a2->z - out.z;
    v15 = a2->x - out.x;
    v16 = stdMath_NormalizeAngleAcute(v15);
    v18 = stdMath_NormalizeAngleAcute(v17);
    v18_hi = stdMath_NormalizeAngleAcute(v19);
    v4 = v16;
    if ( v4 < 0.0 )
        v4 = -v4;
    if ( v4 < 2.5 )
        v16 = 0.0;
    v7 = v18;
    if ( v7 < 0.0 )
        v7 = -v7;
    if ( v7 < 2.5 )
        v18 = 0.0;
    v10 = v18_hi;
    if ( v10 < 0.0 )
        v10 = -v10;
    if ( v10 < 2.5 )
        v18_hi = 0.0;
    if ( v16 != 0.0 || v18 != 0.0 || v18_hi != 0.0 )
    {
        _memcpy(&thing->trackParams.field_24, &thing->lookOrientation, 0x30u);
        thing->trackParams.field_54 = 1.0 / a3;
        rdVector_Zero3(&thing->trackParams.field_24.scale);
        thing->trackParams.field_64.x = v16;
        thing->field_24C = 0.0;
        thing->trackParams.field_64.y = v18;
        thing->trackParams.field_64.z = v18_hi;
        v12 = a2->y;
        thing->trackParams.orientation.x = a2->x;
        v13 = a2->z;
        thing->trackParams.orientation.y = v12;
        thing->trackParams.orientation.z = v13;
        thing->trackParams.field_C &= ~0x10;
        thing->trackParams.field_C |= 2;
    }
}

int sithTrackThing_LoadPathParams(stdConffileArg *arg, sithThing *thing, int param)
{
    sithThing *v4; // ebp
    int v5; // eax
    int v6; // ebx
    unsigned int v7; // esi
    sithThing *v8; // edi
    unsigned int v9; // esi
    sithThingFrame *v10; // eax
    rdVector3 v12; // [esp+10h] [ebp-Ch] BYREF
    rdVector3 v13;

    if ( param == THINGPARAM_FRAME )
    {
        v8 = thing;
        v9 = thing->trackParams.loadedFrames;
        if ( v9 < thing->trackParams.numFrames )
        {
            if ( _sscanf(arg->value, "(%f/%f/%f:%f/%f/%f)", &v12.x, &v12.y, &v12.z, &v13.x, &v13.y, &v13.z) != 6 )
                return 0;
            v10 = &v8->trackParams.frames[v9];
            v8->trackParams.loadedFrames = v9 + 1;
            rdVector_Copy3(&v10->pos, &v12);
            rdVector_Copy3(&v10->rot, &v13);
        }
        return 1;
    }
    if ( param != THINGPARAM_NUMFRAMES )
        return 0;
    v4 = thing;
    if ( thing->trackParams.numFrames )
        return 0;
    v5 = _atoi(arg->value);
    v6 = v5;
    if ( v5 < 1 )
        return 0;
    v7 = sizeof(sithThingFrame) * v5;
    v4->trackParams.frames = pSithHS->alloc(sizeof(sithThingFrame) * v5);
    if ( v4->trackParams.frames )
    {
        _memset(v4->trackParams.frames, 0, v7);
        v4->trackParams.numFrames = v6;
        v4->trackParams.loadedFrames = 0;
        return 1;
    }
    return 0;
}

void sithTrackThing_Stop(sithThing *thing)
{
    thing->trackParams.field_C &= ~0x17u;
    thing->trackParams.field_20 = 0.0;
    thing->goalframe = 0;
    thing->field_258 = 0;
    thing->field_250 = 0;
    sithSoundClass_ThingPauseSoundclass(thing, SITH_SC_MOVING);
    sithSoundClass_ThingPlaySoundclass4(thing, SITH_SC_STOPMOVE);
    if ( (thing->thingflags & SITH_TF_CAPTURED) != 0 && (thing->thingflags & SITH_TF_INVULN) == 0 )
        sithCog_SendMessageFromThing(thing, 0, SITH_MESSAGE_ARRIVED);
}

void sithTrackThing_idkpathmove(sithThing *thing, sithThing *thing2, rdVector3 *a3)
{
    sithThingFrame *v3; // eax
    sithThingFrame *v4; // esi
    uint32_t v5; // ecx
    uint32_t v6; // ebp
    uint32_t v7; // edi
    int v8; // ebp
    sithThingFrame *v9; // esi
    uint32_t v10; // eax
    rdVector3 a1a; // [esp+10h] [ebp-Ch] BYREF

    v3 = (sithThingFrame *)pSithHS->alloc(sizeof(sithThingFrame) * thing2->trackParams.numFrames);
    v4 = thing2->trackParams.frames;
    v5 = 3 * thing2->trackParams.numFrames;
    thing->trackParams.frames = v3;
    _memcpy(v3, v4, 8 * v5);
    v6 = thing2->trackParams.loadedFrames;
    v7 = 0;
    thing->trackParams.numFrames = thing2->trackParams.numFrames;
    thing->trackParams.loadedFrames = v6;
    if ( v6 )
    {
        v8 = 0;
        do
        {
            v9 = &thing->trackParams.frames[v8];
            rdVector_Rotate3(&a1a, a3, &v9->rot);
            v10 = thing->trackParams.loadedFrames;
            ++v7;
            ++v8;
            v9->pos.x = a1a.x + v9->pos.x;
            v9->pos.y = a1a.y + v9->pos.y;
            v9->pos.z = a1a.z + v9->pos.z;
        }
        while ( v7 < v10 );
    }
}

void sithTrackThing_RotatePivot(sithThing *thing, rdVector3 *a2, rdVector3 *a3, float a4)
{
    double v4; // st7
    float v5; // esi
    float v6; // ecx
    double v7; // st7

    thing->trackParams.field_C |= 0x12u;
    sithSoundClass_ThingPlaySoundclass4(thing, 3u);
    sithSoundClass_ThingPlaySoundclass4(thing, 5u);
    v4 = thing->position.x;
    thing->trackParams.field_58.x = a2->x;
    v5 = a2->y;
    thing->curframe = -1;
    v6 = a2->z;
    thing->trackParams.field_58.y = v5;
    thing->trackParams.field_58.z = v6;
    v7 = v4 - thing->trackParams.field_58.x;
    _memcpy(&thing->trackParams.field_24, &thing->lookOrientation, sizeof(thing->trackParams.field_24));
    thing->trackParams.field_24.scale.x = v7;
    thing->trackParams.field_24.scale.y = thing->position.y - thing->trackParams.field_58.y;
    thing->trackParams.field_24.scale.z = thing->position.z - thing->trackParams.field_58.z;
    thing->trackParams.field_64 = *a3;
    thing->field_24C = 0.0;
    thing->field_250 = 0;
    thing->trackParams.field_54 = 1.0 / a4;
}

void sithTrackThing_Rotate(sithThing *trackThing, rdVector3 *rot)
{
    double v2; // st7
    double v4; // st6
    double v5; // st6
    double v6; // st6
    double v7; // st4
    double v8; // st5
    float v9; // [esp+14h] [ebp+4h]
    float v10; // [esp+14h] [ebp+4h]
    float v11; // [esp+14h] [ebp+4h]

    v2 = 0.0;
    if ( rot->x != 0.0 )
    {
        v4 = 360.0 / rot->x;
        if ( v4 > 0.0 )
        {
            v9 = v4;
            v2 = v9;
        }
    }
    if ( rot->y != 0.0 )
    {
        v5 = 360.0 / rot->y;
        if ( v5 > v2 )
        {
            v10 = v5;
            v2 = v10;
        }
    }
    if ( rot->z != 0.0 )
    {
        v6 = 360.0 / rot->z;
        if ( v6 > v2 )
        {
            v11 = v6;
            v2 = v11;
        }
    }
    if ( v2 != 0.0 )
    {
        trackThing->trackParams.field_C |= 0x42u;
        _memcpy(&trackThing->trackParams.field_24, &trackThing->lookOrientation, sizeof(trackThing->trackParams.field_24));
        v7 = rot->y * v2;
        v8 = rot->z * v2;
        trackThing->trackParams.field_64.x = v2 * rot->x;
        trackThing->trackParams.field_64.y = v7;
        trackThing->trackParams.field_64.z = v8;
        trackThing->trackParams.field_54 = 1.0 / v2;
        trackThing->trackParams.field_24.scale.x = 0.0;
        trackThing->trackParams.field_24.scale.y = 0.0;
        trackThing->trackParams.field_24.scale.z = 0.0;
        trackThing->field_24C = 0.0;
        trackThing->field_250 = 0;
        trackThing->curframe = -1;
    }
}

void sithTrackThing_SkipToFrame(sithThing *trackThing, uint32_t goalframeNum, float a3)
{
    sithThingFrame *goalFrame; // eax
    float v5; // st7

    if ( goalframeNum < trackThing->trackParams.loadedFrames )
    {
        trackThing->goalframe = goalframeNum;
        trackThing->trackParams.field_C &= ~0x4;
        trackThing->trackParams.field_20 = a3;
        sithSoundClass_ThingPlaySoundclass4(trackThing, SITH_SC_STARTMOVE);
        sithSoundClass_ThingPlaySoundclass4(trackThing, SITH_SC_MOVING);

        goalFrame = &trackThing->trackParams.frames[trackThing->goalframe];

        trackThing->trackParams.vel.x = goalFrame->pos.x - trackThing->position.x;
        trackThing->trackParams.vel.y = goalFrame->pos.y - trackThing->position.y;
        trackThing->trackParams.vel.z = goalFrame->pos.z - trackThing->position.z;
        
        v5 = rdVector_Normalize3Acc(&trackThing->trackParams.vel);
        if ( v5 != 0.0 )
        {
            trackThing->field_250 = 0;
            trackThing->trackParams.field_C |= 1;
            trackThing->trackParams.field_1C = v5 / trackThing->trackParams.field_20;
        }
    }
}

int sithTrackThing_PathMovePause(sithThing *trackThing)
{
    if ( (trackThing->trackParams.field_C & 3) == 0 )
        return 0;

    sithSoundClass_ThingPauseSoundclass(trackThing, SITH_SC_MOVING);

    trackThing->trackParams.field_C |= 0x80;
    return 1;
}

int sithTrackThing_PathMoveResume(sithThing *trackThing)
{
    if (!(trackThing->trackParams.field_C & 0x80))
        return 0;

    sithSoundClass_ThingPlaySoundclass4(trackThing, SITH_SC_MOVING);

    trackThing->trackParams.field_C &= ~0x80;
    return 1;
}
