/*************************************************************************
 *                                                                       *
 * Open Dynamics Engine, Copyright (C) 2001-2003 Russell L. Smith.       *
 * All rights reserved.  Email: russ@q12.org   Web: www.q12.org          *
 *                                                                       *
 * This library is free software; you can redistribute it and/or         *
 * modify it under the terms of EITHER:                                  *
 *   (1) The GNU Lesser General Public License as published by the Free  *
 *       Software Foundation; either version 2.1 of the License, or (at  *
 *       your option) any later version. The text of the GNU Lesser      *
 *       General Public License is included with this library in the     *
 *       file LICENSE.TXT.                                               *
 *   (2) The BSD-style license that is included with this library in     *
 *       the file LICENSE-BSD.TXT.                                       *
 *                                                                       *
 * This library is distributed in the hope that it will be useful,       *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the files    *
 * LICENSE.TXT and LICENSE-BSD.TXT for more details.                     *
 *                                                                       *
 *************************************************************************/

#include <ode/collision.h>
#include <ode/matrix.h>
#include "config.h"

#if !dTRIMESH_ENABLED

#include "collision_util.h"
#include "collision_trimesh_internal.h"

dxTriMesh::dxTriMesh(dSpaceID Space, dTriMeshDataID Data) : dxGeom(Space, 1) { type = dTriMeshClass; }
dxTriMesh::~dxTriMesh(){}

bool dxTriMesh::controlGeometry(int controlClass, int controlCode, void *dataValue, int *dataSize)
{
	return dxGeom::controlGeometry(controlClass, controlCode, dataValue, dataSize);
}

int dxTriMesh::AABBTest(dxGeom* g, dReal aabb[6]) { return 0; }
void dxTriMesh::computeAABB() { dSetZero (aabb,6); }

static dMatrix4 identity = {
	REAL( 0.0 ), REAL( 0.0 ), REAL( 0.0 ), REAL( 0.0 ),
	REAL( 0.0 ), REAL( 0.0 ), REAL( 0.0 ), REAL( 0.0 ),
	REAL( 0.0 ), REAL( 0.0 ), REAL( 0.0 ), REAL( 0.0 ),
	REAL( 0.0 ), REAL( 0.0 ), REAL( 0.0 ), REAL( 0.0 ) };

// Stub functions for trimesh calls

dTriMeshDataID dGeomTriMeshDataCreate(void) { return 0; }
void dGeomTriMeshDataDestroy(dTriMeshDataID g) {}

void dGeomTriMeshDataSet(dTriMeshDataID g, int data_id, void* in_data) {}
void* dGeomTriMeshDataGet(dTriMeshDataID g, int data_id) { return 0; }

ODE_API void dGeomTriMeshSetLastTransform( dGeomID g, dMatrix4 last_trans ) {}
ODE_API dReal* dGeomTriMeshGetLastTransform( dGeomID g ) { return identity; }

dGeomID dCreateTriMesh(dSpaceID space, 
		       dTriMeshDataID Data,
		       dTriCallback* Callback,
		       dTriArrayCallback* ArrayCallback,
		       dTriRayCallback* RayCallback)
{
    dxTriMesh* Geom = new dxTriMesh(space, Data);
    Geom->Callback = Callback;
    Geom->ArrayCallback = ArrayCallback;
    Geom->RayCallback = RayCallback;

    return Geom;
}

void dGeomTriMeshSetData(dGeomID g, dTriMeshDataID Data) {}
dTriMeshDataID dGeomTriMeshGetData(dGeomID g) { return 0; }


void dGeomTriMeshDataBuildSingle(dTriMeshDataID g,
                                 const void* Vertices, int VertexStride, int VertexCount, 
                                 const void* Indices, int IndexCount, int TriStride) { }

void dGeomTriMeshDataBuildSingle1(dTriMeshDataID g,
                                  const void* Vertices, int VertexStride, int VertexCount, 
                                  const void* Indices, int IndexCount, int TriStride,
                                  const void* Normals) { }

void dGeomTriMeshDataBuildDouble(dTriMeshDataID g, 
                                 const void* Vertices,  int VertexStride, int VertexCount, 
                                 const void* Indices, int IndexCount, int TriStride) { }

void dGeomTriMeshDataBuildDouble1(dTriMeshDataID g, 
                                  const void* Vertices,  int VertexStride, int VertexCount, 
                                  const void* Indices, int IndexCount, int TriStride,
								  const void* Normals) { }

void dGeomTriMeshDataBuildSimple(dTriMeshDataID g,
                                 const dReal* Vertices, int VertexCount,
                                 const dTriIndex* Indices, int IndexCount) { }

void dGeomTriMeshDataBuildSimple1(dTriMeshDataID g,
                                  const dReal* Vertices, int VertexCount,
                                  const dTriIndex* Indices, int IndexCount,
                                  const int* Normals) { }

void dGeomTriMeshDataPreprocess(dTriMeshDataID g) { }

void dGeomTriMeshDataGetBuffer(dTriMeshDataID g, unsigned char** buf, int* bufLen) { *buf = NULL; *bufLen=0; }
void dGeomTriMeshDataSetBuffer(dTriMeshDataID g, unsigned char* buf) {}

void dGeomTriMeshSetCallback(dGeomID g, dTriCallback* Callback) { }
dTriCallback* dGeomTriMeshGetCallback(dGeomID g) { return 0; }

void dGeomTriMeshSetArrayCallback(dGeomID g, dTriArrayCallback* ArrayCallback) { }
dTriArrayCallback* dGeomTriMeshGetArrayCallback(dGeomID g) { return 0; }

void dGeomTriMeshSetRayCallback(dGeomID g, dTriRayCallback* Callback) { }
dTriRayCallback* dGeomTriMeshGetRayCallback(dGeomID g) { return 0; }

void dGeomTriMeshSetTriMergeCallback(dGeomID g, dTriTriMergeCallback* Callback) { }
dTriTriMergeCallback* dGeomTriMeshGetTriMergeCallback(dGeomID g) { return 0; }

void dGeomTriMeshEnableTC(dGeomID g, int geomClass, int enable) {}
int dGeomTriMeshIsTCEnabled(dGeomID g, int geomClass) { return 0; }
void dGeomTriMeshClearTCCache(dGeomID g) {}

dTriMeshDataID dGeomTriMeshGetTriMeshDataID(dGeomID g) { return 0; }

int dGeomTriMeshGetTriangleCount (dGeomID g) { return 0; }
void dGeomTriMeshDataUpdate(dTriMeshDataID g) {}

#endif // !dTRIMESH_ENABLED


