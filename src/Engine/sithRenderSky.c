#include "sithRenderSky.h"

#include "General/stdMath.h"
#include "Engine/sithCamera.h"
#include "Engine/sithIntersect.h"
#include "World/sithSector.h"
#include "jk.h"

int sithRenderSky_Open(float horizontalPixelsPerRev, float horizontalDist, float ceilingSky)
{
    sithSector_horizontalPixelsPerRev_idk = horizontalPixelsPerRev * 0.0027777778;
    sithSector_horizontalDist = horizontalDist;
    sithSector_ceilingSky = ceilingSky;
    sithSector_zMaxVec.x = 0.0;
    sithSector_zMaxVec.y = 0.0;
    sithSector_zMaxVec.z = ceilingSky;
    sithSector_horizontalPixelsPerRev = horizontalPixelsPerRev;
    sithSector_zMinVec.x = 0.0;
    sithSector_zMinVec.y = 0.0;
    sithSector_zMinVec.z = -ceilingSky;
    return 1;
}

void sithRenderSky_Close()
{
}

void sithRenderSky_Update()
{
    double v0; // st7
    float v1; // [esp-Ch] [ebp-Ch]

    v1 = sithCamera_currentCamera->vec3_2.z;
    sithSector_flt_8553C0 = sithSector_horizontalDist / rdCamera_pCurCamera->fov_y;
    stdMath_SinCos(v1, &sithSector_flt_8553F4, &sithSector_flt_8553C8);
    v0 = -(sithCamera_currentCamera->vec3_2.x * sithSector_horizontalPixelsPerRev_idk);
    sithSector_flt_8553B8 = -(sithCamera_currentCamera->vec3_2.y * sithSector_horizontalPixelsPerRev_idk);
    sithSector_flt_8553C4 = v0;
}

void sithRenderSky_TransformHorizontal(rdProcEntry *a1, sithSurfaceInfo *a2, int num_vertices)
{
    int v3; // eax
    int v4; // eax
    sithWorld *v5; // edi
    rdCanvas *v6; // esi
    rdVector2 *v7; // eax
    rdVector3 *v8; // edx
    float *v9; // ecx
    double v10; // st7
    double v12; // st5
    double v13; // st6
    double v14; // st7
    rdClipFrustum *v15; // [esp+10h] [ebp-4h]
    float a1a; // [esp+18h] [ebp+4h]

    v3 = sithRender_geoMode;
    if ( sithRender_geoMode > 4 )
        v3 = 4;
    a1->geometryMode = v3;
    v4 = sithRender_texMode;
    a1->lightingMode = sithRender_lightMode > 0 ? 0 : sithRender_lightMode;
    a1->textureMode = v4 > 0 ? 0 : v4;
    if ( num_vertices )
    {
        v5 = sithWorld_pCurrentWorld;
        v6 = rdCamera_pCurCamera->canvas;
        v7 = a1->vertexUVs;
        v15 = rdCamera_pCurCamera->cameraClipFrustum;
        v8 = a1->vertices;
        do
        {
            ++v8;
            v9 = &v7->y;
            v8[-1].z = v15->field_0.z;
            v10 = (v8[-1].x - v6->screen_height_half) * sithSector_flt_8553C0;
            ++v7;
            v12 = (v8[-1].y - v6->screen_width_half) * sithSector_flt_8553C0;
            a1a = v12;
            --num_vertices;
            v13 = v10 * sithSector_flt_8553C8 - v12 * sithSector_flt_8553F4 + sithSector_flt_8553B8;
            v14 = a1a * sithSector_flt_8553C8 + v10 * sithSector_flt_8553F4 + sithSector_flt_8553C4;
            v7[-1].x = v13;
            *v9 = v14;
            v7[-1].x = v7[-1].x + v5->horizontalSkyOffs.x;
            *v9 = *v9 + v5->horizontalSkyOffs.y;
            v7[-1].x = v7[-1].x + a2->face.clipIdk.x;
            *v9 = *v9 + a2->face.clipIdk.y;
        }
        while (num_vertices != 0);
    }
}

void sithRenderSky_TransformVertical(rdProcEntry *a1, sithSurfaceInfo *a2, rdVector3 *a3, unsigned int a4)
{
    int v4; // eax
    rdProcEntry *v5; // ebx
    unsigned int v6; // edi
    int v8; // esi
    rdVector2 *v9; // eax
    rdVector2 *v10; // eax
    double v11; // st7
    sithWorld *v12; // ecx
    double v13; // st5
    double v14; // st6
    sithSurfaceInfo *v15; // ecx
    unsigned int v16; // eax
    rdMatrix34 *v17; // [esp-4h] [ebp-38h]
    rdVector3 a1a; // [esp+10h] [ebp-24h] BYREF
    rdVector3 a2a; // [esp+1Ch] [ebp-18h] BYREF
    rdVector3 vertex_out; // [esp+28h] [ebp-Ch] BYREF

    v4 = sithRender_geoMode;
    if ( sithRender_geoMode > 4 )
        v4 = 4;
    v5 = a1;
    a1->geometryMode = v4;
    v6 = 0;
    v5->lightingMode = sithRender_lightMode > 0 ? 0 : sithRender_lightMode;
    if ( a4 != 0 )
    {
        v8 = 0;
        do
        {
            rdMatrix_TransformPoint34(&a2a, &a3[v8], &rdCamera_camMatrix);
            a2a.x = a2a.x - sithCamera_currentCamera->vec3_1.x;
            a2a.y = a2a.y - sithCamera_currentCamera->vec3_1.y;
            a2a.z = a2a.z - sithCamera_currentCamera->vec3_1.z;
            rdVector_Normalize3(&a1a, &a2a);
            
            float tmp = 0.0;
            if ( !sithIntersect_sub_508BE0(&sithCamera_currentCamera->vec3_1, &a1a, 1000.0, 0.0, &sithSector_surfaceNormal, &sithSector_zMaxVec, &tmp, 0) )
                tmp = 1000.0;
            v9 = v5->vertexUVs;
            a1a.x = tmp * a1a.x;
            a1a.y = tmp * a1a.y;
            a1a.z = tmp * a1a.z;
            v10 = &v9[v6];
            v17 = &sithCamera_currentCamera->rdCam.view_matrix;
            v11 = a2->face.clipIdk.x;
            a1a.x = sithCamera_currentCamera->vec3_1.x + a1a.x;
            a1a.y = sithCamera_currentCamera->vec3_1.y + a1a.y;
            v12 = sithWorld_pCurrentWorld;
            a1a.z = sithCamera_currentCamera->vec3_1.z + a1a.z;
            v10->x = a1a.x * 16.0;
            v13 = v12->ceilingSkyOffs.x;
            v14 = v12->ceilingSkyOffs.y;
            v10->y = a1a.y * 16.0;
            v15 = a2;
            v10->x = v13 + v10->x;
            v10->y = v14 + v10->y;
            v10->x = v11 + v10->x;
            v10->y = v10->y + v15->face.clipIdk.y;
            rdMatrix_TransformPoint34(&vertex_out, &a1a, v17);
            v16 = a4;
            ++v6;
            v5->vertices[v8++].z = vertex_out.y;
        }
        while ( v6 < v16 );
    }
}