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

// TriMesh code by Erwin de Vries.

#include <ode/collision.h>
#include <ode/matrix.h>
#include <ode/rotation.h>
#include <ode/odemath.h>
#include "config.h"
#include "collision_util.h"
#include "collision_trimesh_internal.h"

#if dTRIMESH_ENABLED
#if dTRIMESH_OPCODE


void TrimeshCollidersCache::InitOPCODECaches()
{
	_RayCollider.SetDestination(&Faces);

/* -- not used
	_PlanesCollider.SetTemporalCoherence(true);
*/

	_SphereCollider.SetTemporalCoherence(true);
	_SphereCollider.SetPrimitiveTests(false);

	_OBBCollider.SetTemporalCoherence(true);

	// no first-contact test (i.e. return full contact info)
	_AABBTreeCollider.SetFirstContact( false );     
	// temporal coherence only works with "first contact" tests
	_AABBTreeCollider.SetTemporalCoherence(false);
	// Perform full BV-BV tests (true) or SAT-lite tests (false)
	_AABBTreeCollider.SetFullBoxBoxTest( true );
	// Perform full Primitive-BV tests (true) or SAT-lite tests (false)
	_AABBTreeCollider.SetFullPrimBoxTest( true );
	const char* msg;
	if ((msg =_AABBTreeCollider.ValidateSettings()))
		dDebug (d_ERR_UASSERT, msg, " (%s:%d)", __FILE__,__LINE__);

/* -- not used
	_LSSCollider.SetTemporalCoherence(false);
	_LSSCollider.SetPrimitiveTests(false);
	_LSSCollider.SetFirstContact(false);
*/
}



// Trimesh data
dxTriMeshData::dxTriMeshData() : UseFlags( NULL )
{
#if !dTRIMESH_ENABLED
  dUASSERT(false, "dTRIMESH_ENABLED is not defined. Trimesh geoms will not work");
#endif
}

dxTriMeshData::~dxTriMeshData()
{
	if ( UseFlags )
		delete [] UseFlags;
}

void 
dxTriMeshData::Build(const void* Vertices, int VertexStide, int VertexCount,
		     const void* Indices, int IndexCount, int TriStride,
		     const void* in_Normals,
		     bool Single)
{
#if dTRIMESH_ENABLED

    Mesh.SetNbTriangles(IndexCount / 3);
    Mesh.SetNbVertices(VertexCount);
    Mesh.SetPointers((IndexedTriangle*)Indices, (Point*)Vertices);
    Mesh.SetStrides(TriStride, VertexStide);
    Mesh.SetSingle(Single);
    
    // Build tree
    BuildSettings Settings;
    // recommended in Opcode User Manual
    //Settings.mRules = SPLIT_COMPLETE | SPLIT_SPLATTERPOINTS | SPLIT_GEOMCENTER;
    // used in ODE, why?
    //Settings.mRules = SPLIT_BEST_AXIS;

    // best compromise?
    Settings.mRules = SPLIT_BEST_AXIS | SPLIT_SPLATTER_POINTS | SPLIT_GEOM_CENTER;


    OPCODECREATE TreeBuilder;
    TreeBuilder.mIMesh = &Mesh;

    TreeBuilder.mSettings = Settings;
    TreeBuilder.mNoLeaf = true;
    TreeBuilder.mQuantized = false;

    TreeBuilder.mKeepOriginal = false;
    TreeBuilder.mCanRemap = false;



    BVTree.Build(TreeBuilder);

    // compute model space AABB
    dVector3 AABBMax, AABBMin;
    AABBMax[0] = AABBMax[1] = AABBMax[2] = (dReal) -dInfinity;
    AABBMin[0] = AABBMin[1] = AABBMin[2] = (dReal) dInfinity;
    if( Single ) {
        const char* verts = (const char*)Vertices;
        for( int i = 0; i < VertexCount; ++i ) {
        const float* v = (const float*)verts;
        if( v[0] > AABBMax[0] ) AABBMax[0] = v[0];
        if( v[1] > AABBMax[1] ) AABBMax[1] = v[1];
        if( v[2] > AABBMax[2] ) AABBMax[2] = v[2];
        if( v[0] < AABBMin[0] ) AABBMin[0] = v[0];
        if( v[1] < AABBMin[1] ) AABBMin[1] = v[1];
        if( v[2] < AABBMin[2] ) AABBMin[2] = v[2];
        verts += VertexStide;
        }
    } else {
        const char* verts = (const char*)Vertices;
        for( int i = 0; i < VertexCount; ++i ) {
        const double* v = (const double*)verts;
        if( v[0] > AABBMax[0] ) AABBMax[0] = (dReal) v[0];
        if( v[1] > AABBMax[1] ) AABBMax[1] = (dReal) v[1];
        if( v[2] > AABBMax[2] ) AABBMax[2] = (dReal) v[2];
        if( v[0] < AABBMin[0] ) AABBMin[0] = (dReal) v[0];
        if( v[1] < AABBMin[1] ) AABBMin[1] = (dReal) v[1];
        if( v[2] < AABBMin[2] ) AABBMin[2] = (dReal) v[2];
        verts += VertexStide;
        }
    }
    AABBCenter[0] = (AABBMin[0] + AABBMax[0]) * REAL(0.5);
    AABBCenter[1] = (AABBMin[1] + AABBMax[1]) * REAL(0.5);
    AABBCenter[2] = (AABBMin[2] + AABBMax[2]) * REAL(0.5);
    AABBExtents[0] = AABBMax[0] - AABBCenter[0];
    AABBExtents[1] = AABBMax[1] - AABBCenter[1];
    AABBExtents[2] = AABBMax[2] - AABBCenter[2];

    // user data (not used by OPCODE)
    Normals = (dReal *) in_Normals;

	UseFlags = 0;

#endif // dTRIMESH_ENABLED
}

struct EdgeRecord
{
	int VertIdx1;	// Index into vertex array for this edges vertices
	int VertIdx2;
	int TriIdx;		// Index into triangle array for triangle this edge belongs to

	uint8 EdgeFlags;	
	uint8 Vert1Flags;
	uint8 Vert2Flags;
	bool Concave;
};

// Edge comparison function for qsort
static int EdgeCompare(const void* edge1, const void* edge2)
{
	EdgeRecord* e1 = (EdgeRecord*)edge1;
	EdgeRecord* e2 = (EdgeRecord*)edge2;

	if (e1->VertIdx1 == e2->VertIdx1)
		return e1->VertIdx2 - e2->VertIdx2;
	else
		return e1->VertIdx1 - e2->VertIdx1;
}

void SetupEdge(EdgeRecord* edge, int edgeIdx, int triIdx, const dTriIndex* vertIdxs)
{
	if (edgeIdx == 0)
	{
		edge->EdgeFlags  = dxTriMeshData::kEdge0;
		edge->Vert1Flags = dxTriMeshData::kVert0;
		edge->Vert2Flags = dxTriMeshData::kVert1;
		edge->VertIdx1 = vertIdxs[0];
		edge->VertIdx2 = vertIdxs[1];
	}
	else if (edgeIdx == 1)
	{
		edge->EdgeFlags  = dxTriMeshData::kEdge1;
		edge->Vert1Flags = dxTriMeshData::kVert1;
		edge->Vert2Flags = dxTriMeshData::kVert2;
		edge->VertIdx1 = vertIdxs[1];
		edge->VertIdx2 = vertIdxs[2];
	}
	else if (edgeIdx == 2)
	{
		edge->EdgeFlags  = dxTriMeshData::kEdge2;
		edge->Vert1Flags = dxTriMeshData::kVert2;
		edge->Vert2Flags = dxTriMeshData::kVert0;
		edge->VertIdx1 = vertIdxs[2];
		edge->VertIdx2 = vertIdxs[0];
	}

	// Make sure vert index 1 is less than index 2 (for easier sorting)
	if (edge->VertIdx1 > edge->VertIdx2)
	{
		unsigned int tempIdx = edge->VertIdx1;
		edge->VertIdx1 = edge->VertIdx2;
		edge->VertIdx2 = tempIdx;

		uint8 tempFlags = edge->Vert1Flags;
		edge->Vert1Flags = edge->Vert2Flags;
		edge->Vert2Flags = tempFlags;
	}

	edge->TriIdx = triIdx;
	edge->Concave = false;
}

#if dTRIMESH_ENABLED

// Get the vertex opposite this edge in the triangle
inline Point GetOppositeVert(EdgeRecord* edge, const Point* vertices[])
{
	if ((edge->Vert1Flags == dxTriMeshData::kVert0 && edge->Vert2Flags == dxTriMeshData::kVert1) ||
		(edge->Vert1Flags == dxTriMeshData::kVert1 && edge->Vert2Flags == dxTriMeshData::kVert0))
	{
		return *vertices[2];
	}
	else if ((edge->Vert1Flags == dxTriMeshData::kVert1 && edge->Vert2Flags == dxTriMeshData::kVert2) ||
		(edge->Vert1Flags == dxTriMeshData::kVert2 && edge->Vert2Flags == dxTriMeshData::kVert1))
	{
		return *vertices[0];
	}
	else
		return *vertices[1];
}

#endif // dTRIMESH_ENABLED

void dxTriMeshData::Preprocess()
{

#if dTRIMESH_ENABLED

	// If this mesh has already been preprocessed, exit
	if (UseFlags)
		return;

	udword numTris = Mesh.GetNbTriangles();
	udword numEdges = numTris * 3;

	UseFlags = new uint8[numTris];
	memset(UseFlags, 0, sizeof(uint8) * numTris);

	EdgeRecord* records = new EdgeRecord[numEdges];

	// Make a list of every edge in the mesh
	const IndexedTriangle* tris = Mesh.GetTris();
	const unsigned tristride = Mesh.GetTriStride();
	for (unsigned int i = 0; i < numTris; i++)
	{
		SetupEdge(&records[i*3],   0, i, tris->mVRef);
		SetupEdge(&records[i*3+1], 1, i, tris->mVRef);
		SetupEdge(&records[i*3+2], 2, i, tris->mVRef);

		tris = (const IndexedTriangle*)(((uint8*)tris) + tristride);
	}

	// Sort the edges, so the ones sharing the same verts are beside each other
	qsort(records, numEdges, sizeof(EdgeRecord), EdgeCompare);

	// Go through the sorted list of edges and flag all the edges and vertices that we need to use
	for (unsigned int i = 0; i < numEdges; i++)
	{
		EdgeRecord* rec1 = &records[i];
		EdgeRecord* rec2 = 0;
		if (i < numEdges - 1)
			rec2 = &records[i+1];

		if (rec2 &&
			rec1->VertIdx1 == rec2->VertIdx1 &&
			rec1->VertIdx2 == rec2->VertIdx2)
		{
			VertexPointers vp;
			ConversionArea vc;
			Mesh.GetTriangle(vp, rec1->TriIdx, vc);

			// Get the normal of the first triangle
			Point triNorm = (*vp.Vertex[2] - *vp.Vertex[1]) ^ (*vp.Vertex[0] - *vp.Vertex[1]);
			triNorm.Normalize();

			// Get the vert opposite this edge in the first triangle
			Point oppositeVert1 = GetOppositeVert(rec1, vp.Vertex);

			// Get the vert opposite this edge in the second triangle
			Mesh.GetTriangle(vp, rec2->TriIdx, vc);
			Point oppositeVert2 = GetOppositeVert(rec2, vp.Vertex);

			float dot = triNorm.Dot((oppositeVert2 - oppositeVert1).Normalize());

			// We let the dot threshold for concavity get slightly negative to allow for rounding errors
			static const float kConcaveThresh = -0.000001f;

			// This is a concave edge, leave it for the next pass
			if (dot >= kConcaveThresh)
				rec1->Concave = true;
			// If this is a convex edge, mark its vertices and edge as used
			else
				UseFlags[rec1->TriIdx] |= rec1->Vert1Flags | rec1->Vert2Flags | rec1->EdgeFlags;

			// Skip the second edge
			i++;
		}
		// This is a boundary edge
		else
		{
			UseFlags[rec1->TriIdx] |= rec1->Vert1Flags | rec1->Vert2Flags | rec1->EdgeFlags;
		}
	}

	// Go through the list once more, and take any edge we marked as concave and
	// clear it's vertices flags in any triangles they're used in
	for (unsigned int i = 0; i < numEdges; i++)
	{
		EdgeRecord& er = records[i];

		if (er.Concave)
		{
			for (unsigned int j = 0; j < numEdges; j++)
			{
				EdgeRecord& curER = records[j];

				if (curER.VertIdx1 == er.VertIdx1 ||
					curER.VertIdx1 == er.VertIdx2)
					UseFlags[curER.TriIdx] &= ~curER.Vert1Flags;

				if (curER.VertIdx2 == er.VertIdx1 ||
					curER.VertIdx2 == er.VertIdx2)
					UseFlags[curER.TriIdx] &= ~curER.Vert2Flags;
			}
		}
	}

	delete [] records;

#endif // dTRIMESH_ENABLED

}

dTriMeshDataID dGeomTriMeshDataCreate(){
    return new dxTriMeshData();
}

void dGeomTriMeshDataDestroy(dTriMeshDataID g){
    delete g;
}




void dGeomTriMeshSetLastTransform( dxGeom* g, dMatrix4 last_trans )
{
	dAASSERT(g)
    dUASSERT(g->type == dTriMeshClass, "geom not trimesh");

    for (int i=0; i<16; i++)
        (((dxTriMesh*)g)->last_trans)[ i ] = last_trans[ i ];

    return;
}


dReal* dGeomTriMeshGetLastTransform( dxGeom* g )
{
	dAASSERT(g)
    dUASSERT(g->type == dTriMeshClass, "geom not trimesh");

    return (dReal*)(((dxTriMesh*)g)->last_trans);
}




void dGeomTriMeshDataSet(dTriMeshDataID g, int data_id, void* in_data)
{
    dUASSERT(g, "argument not trimesh data");

    switch (data_id)
	{
    case TRIMESH_FACE_NORMALS:
		g->Normals = (dReal *) in_data;
		break;

    default:
		dUASSERT(data_id, "invalid data type");
		break;
    }

    return;
}



void*  dGeomTriMeshDataGet(dTriMeshDataID g, int data_id)
{
    dUASSERT(g, "argument not trimesh data");

    switch (data_id)
	{
    case TRIMESH_FACE_NORMALS:
        return (void *) g->Normals;
        break;

	default:
        dUASSERT(data_id, "invalid data type");
        break;
    }
    
    return NULL;
}


void dGeomTriMeshDataBuildSingle1(dTriMeshDataID g,
                                  const void* Vertices, int VertexStride, int VertexCount, 
                                  const void* Indices, int IndexCount, int TriStride,
                                  const void* Normals)
{
    dUASSERT(g, "argument not trimesh data");
    
    g->Build(Vertices, VertexStride, VertexCount, 
             Indices, IndexCount, TriStride, 
             Normals, 
             true);
}


void dGeomTriMeshDataBuildSingle(dTriMeshDataID g,
                                 const void* Vertices, int VertexStride, int VertexCount, 
                                 const void* Indices, int IndexCount, int TriStride)
{
    dGeomTriMeshDataBuildSingle1(g, Vertices, VertexStride, VertexCount,
                                 Indices, IndexCount, TriStride, (void*)NULL);
}


void dGeomTriMeshDataBuildDouble1(dTriMeshDataID g,
                                  const void* Vertices, int VertexStride, int VertexCount, 
                                 const void* Indices, int IndexCount, int TriStride,
				 const void* Normals)
{
    dUASSERT(g, "argument not trimesh data");
    
    g->Build(Vertices, VertexStride, VertexCount, 
             Indices, IndexCount, TriStride, 
             Normals, 
             false);
}


void dGeomTriMeshDataBuildDouble(dTriMeshDataID g,
				 const void* Vertices, int VertexStride, int VertexCount, 
                                 const void* Indices, int IndexCount, int TriStride) {
    dGeomTriMeshDataBuildDouble1(g, Vertices, VertexStride, VertexCount,
                                 Indices, IndexCount, TriStride, NULL);
}


void dGeomTriMeshDataBuildSimple1(dTriMeshDataID g,
                                  const dReal* Vertices, int VertexCount, 
                                 const dTriIndex* Indices, int IndexCount,
                                 const int* Normals){
#ifdef dSINGLE
    dGeomTriMeshDataBuildSingle1(g,
				Vertices, 4 * sizeof(dReal), VertexCount, 
				Indices, IndexCount, 3 * sizeof(dTriIndex),
				Normals);
#else
    dGeomTriMeshDataBuildDouble1(g, Vertices, 4 * sizeof(dReal), VertexCount, 
				Indices, IndexCount, 3 * sizeof(dTriIndex),
				Normals);
#endif
}


void dGeomTriMeshDataBuildSimple(dTriMeshDataID g,
                                 const dReal* Vertices, int VertexCount, 
                                 const dTriIndex* Indices, int IndexCount) {
    dGeomTriMeshDataBuildSimple1(g,
                                 Vertices, VertexCount, Indices, IndexCount,
                                 (const int*)NULL);
}

void dGeomTriMeshDataPreprocess(dTriMeshDataID g)
{
    dUASSERT(g, "argument not trimesh data");
	g->Preprocess();
}

void dGeomTriMeshDataGetBuffer(dTriMeshDataID g, unsigned char** buf, int* bufLen)
{
    dUASSERT(g, "argument not trimesh data");
#if dTRIMESH_ENABLED
	*buf = g->UseFlags;
	*bufLen = g->Mesh.GetNbTriangles();
#endif // dTRIMESH_ENABLED
}

void dGeomTriMeshDataSetBuffer(dTriMeshDataID g, unsigned char* buf)
{
    dUASSERT(g, "argument not trimesh data");
	g->UseFlags = buf;
}


dxTriMesh::dxTriMesh(dSpaceID Space, dTriMeshDataID Data) : dxGeom(Space, 1)
{
    type = dTriMeshClass;

    Callback = NULL;
    ArrayCallback = NULL;
    RayCallback = NULL;
    TriMergeCallback = NULL; // Not initialized in dCreateTriMesh

    this->Data = Data;

	/* TC has speed/space 'issues' that don't make it a clear
	   win by default on spheres/boxes. */
	this->doSphereTC = false;
	this->doBoxTC = false;
	this->doCapsuleTC = false;

	SphereContactsMergeOption = (dxContactMergeOptions)MERGE_NORMALS__SPHERE_DEFAULT;

    for (int i=0; i<16; i++)
        last_trans[i] = REAL( 0.0 );
}

dxTriMesh::~dxTriMesh(){
    //
}

// Cleanup for allocations when shutting down ODE
/*extern */void opcode_collider_cleanup()
{
#if !dTLS_ENABLED
#if dTRIMESH_ENABLED

	// Clear TC caches
	TrimeshCollidersCache *pccColliderCache = GetTrimeshCollidersCache(0);
	pccColliderCache->Faces.Empty();
	pccColliderCache->defaultSphereCache.TouchedPrimitives.Empty();
	pccColliderCache->defaultBoxCache.TouchedPrimitives.Empty();
	pccColliderCache->defaultCapsuleCache.TouchedPrimitives.Empty();

#endif // dTRIMESH_ENABLED
#endif // dTLS_ENABLED
}



void dxTriMesh::ClearTCCache()
{
#if dTRIMESH_ENABLED
  /* dxTriMesh::ClearTCCache uses dArray's setSize(0) to clear the caches -
     but the destructor isn't called when doing this, so we would leak.
     So, call the previous caches' containers' destructors by hand first. */
    int i, n;
    n = SphereTCCache.size();
    for( i = 0; i < n; ++i ) {
        SphereTCCache[i].~SphereTC();
    }
    SphereTCCache.setSize(0);
    n = BoxTCCache.size();
    for( i = 0; i < n; ++i ) {
        BoxTCCache[i].~BoxTC();
    }
    BoxTCCache.setSize(0);
	n = CapsuleTCCache.size();
	for( i = 0; i < n; ++i ) {
	  CapsuleTCCache[i].~CapsuleTC();
	}
	CapsuleTCCache.setSize(0);
#endif // dTRIMESH_ENABLED
}


bool dxTriMesh::controlGeometry(int controlClass, int controlCode, void *dataValue, int *dataSize)
{
	if (controlClass == dGeomColliderControlClass) {
		if (controlCode == dGeomCommonAnyControlCode) {
			return checkControlValueSizeValidity(dataValue, dataSize, 0);
		}
		else if (controlCode == dGeomColliderSetMergeSphereContactsControlCode) {
			return checkControlValueSizeValidity(dataValue, dataSize, sizeof(int)) 
				&& controlGeometry_SetMergeSphereContacts(*(int *)dataValue);
		}
		else if (controlCode == dGeomColliderGetMergeSphereContactsControlCode) {
			return checkControlValueSizeValidity(dataValue, dataSize, sizeof(int)) 
				&& controlGeometry_GetMergeSphereContacts(*(int *)dataValue);
		}
	}

	return dxGeom::controlGeometry(controlClass, controlCode, dataValue, dataSize);
}

bool dxTriMesh::controlGeometry_SetMergeSphereContacts(int dataValue)
{
	if (dataValue == dGeomColliderMergeContactsValue__Default) {
		SphereContactsMergeOption = (dxContactMergeOptions)MERGE_NORMALS__SPHERE_DEFAULT;
	}
	else if (dataValue == dGeomColliderMergeContactsValue_None) {
		SphereContactsMergeOption = DONT_MERGE_CONTACTS;
	}
	else if (dataValue == dGeomColliderMergeContactsValue_Normals) {
		SphereContactsMergeOption = MERGE_CONTACT_NORMALS;
	}
	else if (dataValue == dGeomColliderMergeContactsValue_Full) {
		SphereContactsMergeOption = MERGE_CONTACTS_FULLY;
	}
	else {
		dAASSERT(false && "Invalid contact merge control value");
		return false;
	}

	return true;
}

bool dxTriMesh::controlGeometry_GetMergeSphereContacts(int &returnValue)
{
	if (SphereContactsMergeOption = DONT_MERGE_CONTACTS) {
		returnValue = dGeomColliderMergeContactsValue_None;
	}
	else if (SphereContactsMergeOption = MERGE_CONTACT_NORMALS) {
		returnValue = dGeomColliderMergeContactsValue_Normals;
	}
	else if (SphereContactsMergeOption = MERGE_CONTACTS_FULLY) {
		returnValue = dGeomColliderMergeContactsValue_Full;
	}
	else {
		dIASSERT(false && "Internal error: unexpected contact merge option field value");
		return false;
	}

	return true;
}

int dxTriMesh::AABBTest(dxGeom* g, dReal aabb[6]){
    return 1;
}


void dxTriMesh::computeAABB() {
    const dxTriMeshData* d = Data;
    dVector3 c;
    const dMatrix3& R = final_posr->R;
    const dVector3& pos = final_posr->pos;
    
    dMultiply0_331( c, R, d->AABBCenter );
    
    dReal xrange = dFabs(R[0] * Data->AABBExtents[0]) +
        dFabs(R[1] * Data->AABBExtents[1]) + 
        dFabs(R[2] * Data->AABBExtents[2]);
    dReal yrange = dFabs(R[4] * Data->AABBExtents[0]) +
        dFabs(R[5] * Data->AABBExtents[1]) + 
        dFabs(R[6] * Data->AABBExtents[2]);
    dReal zrange = dFabs(R[8] * Data->AABBExtents[0]) +
        dFabs(R[9] * Data->AABBExtents[1]) + 
        dFabs(R[10] * Data->AABBExtents[2]);

    aabb[0] = c[0] + pos[0] - xrange;
    aabb[1] = c[0] + pos[0] + xrange;
    aabb[2] = c[1] + pos[1] - yrange;
    aabb[3] = c[1] + pos[1] + yrange;
    aabb[4] = c[2] + pos[2] - zrange;
    aabb[5] = c[2] + pos[2] + zrange;
}


void dxTriMeshData::UpdateData()
{
#if  dTRIMESH_ENABLED
	BVTree.Refit();
#endif // dTRIMESH_ENABLED
}


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

void dGeomTriMeshSetCallback(dGeomID g, dTriCallback* Callback)
{
	dUASSERT(g && g->type == dTriMeshClass, "argument not a trimesh");
	((dxTriMesh*)g)->Callback = Callback;
}

dTriCallback* dGeomTriMeshGetCallback(dGeomID g)
{
	dUASSERT(g && g->type == dTriMeshClass, "argument not a trimesh");
	return ((dxTriMesh*)g)->Callback;
}

void dGeomTriMeshSetArrayCallback(dGeomID g, dTriArrayCallback* ArrayCallback)
{
	dUASSERT(g && g->type == dTriMeshClass, "argument not a trimesh");
	((dxTriMesh*)g)->ArrayCallback = ArrayCallback;
}

dTriArrayCallback* dGeomTriMeshGetArrayCallback(dGeomID g)
{
	dUASSERT(g && g->type == dTriMeshClass, "argument not a trimesh");
	return ((dxTriMesh*)g)->ArrayCallback;
}

void dGeomTriMeshSetRayCallback(dGeomID g, dTriRayCallback* Callback)
{
	dUASSERT(g && g->type == dTriMeshClass, "argument not a trimesh");
	((dxTriMesh*)g)->RayCallback = Callback;
}

dTriRayCallback* dGeomTriMeshGetRayCallback(dGeomID g)
{
	dUASSERT(g && g->type == dTriMeshClass, "argument not a trimesh");	
	return ((dxTriMesh*)g)->RayCallback;
}

void dGeomTriMeshSetTriMergeCallback(dGeomID g, dTriTriMergeCallback* Callback)
{
    dUASSERT(g && g->type == dTriMeshClass, "argument not a trimesh");
    ((dxTriMesh*)g)->TriMergeCallback = Callback;
}

dTriTriMergeCallback* dGeomTriMeshGetTriMergeCallback(dGeomID g)
{
    dUASSERT(g && g->type == dTriMeshClass, "argument not a trimesh");	
    return ((dxTriMesh*)g)->TriMergeCallback;
}

void dGeomTriMeshSetData(dGeomID g, dTriMeshDataID Data)
{
	dUASSERT(g && g->type == dTriMeshClass, "argument not a trimesh");
	((dxTriMesh*)g)->Data = Data;
	// I changed my data -- I know nothing about my own AABB anymore.
	((dxTriMesh*)g)->gflags |= (GEOM_DIRTY|GEOM_AABB_BAD);
}

dTriMeshDataID dGeomTriMeshGetData(dGeomID g)
{
  dUASSERT(g && g->type == dTriMeshClass, "argument not a trimesh");
  return ((dxTriMesh*)g)->Data;
}



void dGeomTriMeshEnableTC(dGeomID g, int geomClass, int enable)
{
	dUASSERT(g && g->type == dTriMeshClass, "argument not a trimesh");
  
	switch (geomClass)
	{
		case dSphereClass: 
			((dxTriMesh*)g)->doSphereTC = (1 == enable);
			break;
		case dBoxClass:
			((dxTriMesh*)g)->doBoxTC = (1 == enable);
			break;
		case dCapsuleClass:
			((dxTriMesh*)g)->doCapsuleTC = (1 == enable);
			break;
	}
}

int dGeomTriMeshIsTCEnabled(dGeomID g, int geomClass)
{
	dUASSERT(g && g->type == dTriMeshClass, "argument not a trimesh");
  
	switch (geomClass)
	{
		case dSphereClass:
			if (((dxTriMesh*)g)->doSphereTC)
				return 1;
			break;
		case dBoxClass:
			if (((dxTriMesh*)g)->doBoxTC)
				return 1;
			break;
		case dCapsuleClass:
			if (((dxTriMesh*)g)->doCapsuleTC)
				return 1;
			break;
	}
	return 0;
}

void dGeomTriMeshClearTCCache(dGeomID g){
    dUASSERT(g && g->type == dTriMeshClass, "argument not a trimesh");

    dxTriMesh* Geom = (dxTriMesh*)g;
    Geom->ClearTCCache();
}

/*
 * returns the TriMeshDataID
 */
dTriMeshDataID
dGeomTriMeshGetTriMeshDataID(dGeomID g)
{
    dxTriMesh* Geom = (dxTriMesh*) g;
    return Geom->Data;
}

// Getting data
void dGeomTriMeshGetTriangle(dGeomID g, int Index, dVector3* v0, dVector3* v1, dVector3* v2){
    dUASSERT(g && g->type == dTriMeshClass, "argument not a trimesh");

    dxTriMesh* Geom = (dxTriMesh*)g;

    const dVector3& Position = *(const dVector3*)dGeomGetPosition(g);
    const dMatrix3& Rotation = *(const dMatrix3*)dGeomGetRotation(g);

    dVector3 v[3];
	FetchTriangle(Geom, Index, Position, Rotation, v);

    if (v0){
        (*v0)[0] = v[0][0];
        (*v0)[1] = v[0][1];
        (*v0)[2] = v[0][2];
        (*v0)[3] = v[0][3];
    }
    if (v1){
        (*v1)[0] = v[1][0];
        (*v1)[1] = v[1][1];
        (*v1)[2] = v[1][2];
        (*v1)[3] = v[1][3];
    }
    if (v2){
        (*v2)[0] = v[2][0];
        (*v2)[1] = v[2][1];
        (*v2)[2] = v[2][2];
        (*v2)[3] = v[2][3];
    }
}

void dGeomTriMeshGetPoint(dGeomID g, int Index, dReal u, dReal v, dVector3 Out){
    dUASSERT(g && g->type == dTriMeshClass, "argument not a trimesh");

    dxTriMesh* Geom = (dxTriMesh*)g;

    const dVector3& Position = *(const dVector3*)dGeomGetPosition(g);
    const dMatrix3& Rotation = *(const dMatrix3*)dGeomGetRotation(g);

    dVector3 dv[3];
    FetchTriangle(Geom, Index, Position, Rotation, dv);

    GetPointFromBarycentric(dv, u, v, Out);
}

int dGeomTriMeshGetTriangleCount (dGeomID g)
{
    dxTriMesh* Geom = (dxTriMesh*)g;
    return FetchTriangleCount(Geom);
}

void dGeomTriMeshDataUpdate(dTriMeshDataID g) {
    dUASSERT(g, "argument not trimesh data");
    g->UpdateData();
}

#endif // dTRIMESH_OPCODE
#endif // dTRIMESH_ENABLED
