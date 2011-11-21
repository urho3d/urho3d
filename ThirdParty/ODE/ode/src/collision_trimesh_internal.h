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
// Modified for FreeSOLID Compatibility by Rodrigo Hernandez
// Trimesh caches separation by Oleh Derevenko


#ifndef _ODE_COLLISION_TRIMESH_INTERNAL_H_
#define _ODE_COLLISION_TRIMESH_INTERNAL_H_

//****************************************************************************
// dxTriMesh class


#include "collision_kernel.h"
#include "collision_trimesh_colliders.h"
#include <ode/collision_trimesh.h>

#if dTRIMESH_OPCODE
#define BAN_OPCODE_AUTOLINK
#include "Opcode.h"
using namespace Opcode;
#endif // dTRIMESH_OPCODE

#if dTRIMESH_GIMPACT
#include <GIMPACT/gimpact.h>
#endif

#if dTLS_ENABLED
#include "odetls.h"
#endif




#if dTRIMESH_OPCODE
#if !dTRIMESH_OPCODE_USE_OLD_TRIMESH_TRIMESH_COLLIDER

// New trimesh collider hash table types
enum
{
	MAXCONTACT_X_NODE = 4,
	CONTACTS_HASHSIZE = 256,
};

struct CONTACT_KEY
{
	dContactGeom * m_contact;
	unsigned int m_key;
};

struct CONTACT_KEY_HASH_NODE
{
	CONTACT_KEY m_keyarray[MAXCONTACT_X_NODE];
	int m_keycount;
};

struct CONTACT_KEY_HASH_TABLE
{
public:
	CONTACT_KEY_HASH_NODE &operator[](unsigned int index) { return m_storage[index]; }

private:
	CONTACT_KEY_HASH_NODE m_storage[CONTACTS_HASHSIZE];
};

#endif // !dTRIMESH_OPCODE_USE_OLD_TRIMESH_TRIMESH_COLLIDER
#endif // dTRIMESH_OPCODE

struct VertexUseCache
{
public:
	VertexUseCache(): m_VertexUseBits(NULL), m_VertexUseElements(0) {}
	~VertexUseCache() { FreeVertexUSEDFlags();  }

	bool ResizeAndResetVertexUSEDFlags(unsigned VertexCount)
	{
		bool Result = false;
		size_t VertexNewElements = (VertexCount + 7) / 8;
		if (VertexNewElements <= m_VertexUseElements || ReallocVertexUSEDFlags(VertexNewElements)) {
			memset(m_VertexUseBits, 0, VertexNewElements);
			Result = true;
		}
		return Result;
	}
	
	bool GetVertexUSEDFlag(unsigned VertexIndex) const { return (m_VertexUseBits[VertexIndex / 8] & (1 << (VertexIndex % 8))) != 0; }
	void SetVertexUSEDFlag(unsigned VertexIndex) { m_VertexUseBits[VertexIndex / 8] |= (1 << (VertexIndex % 8)); }

private:
	bool ReallocVertexUSEDFlags(size_t VertexNewElements)
	{
		bool Result = false;
		uint8 *VertexNewBits = (uint8 *)dRealloc(m_VertexUseBits, m_VertexUseElements * sizeof(m_VertexUseBits[0]), VertexNewElements * sizeof(m_VertexUseBits[0]));
		if (VertexNewBits) {
			m_VertexUseBits = VertexNewBits;
			m_VertexUseElements = VertexNewElements;
			Result = true;
		}
		return Result;
	}

	void FreeVertexUSEDFlags()
	{
		dFree(m_VertexUseBits, m_VertexUseElements * sizeof(m_VertexUseBits[0]));
		m_VertexUseBits = NULL;
		m_VertexUseElements = 0;
	}

private:
	uint8 *m_VertexUseBits;
	size_t m_VertexUseElements;
};


struct TrimeshCollidersCache
{
	TrimeshCollidersCache()
	{
#if dTRIMESH_OPCODE
		InitOPCODECaches();
#endif // dTRIMESH_OPCODE
	}

#if dTRIMESH_OPCODE

	void InitOPCODECaches();


	// Collider caches
	BVTCache ColCache;

#if !dTRIMESH_OPCODE_USE_OLD_TRIMESH_TRIMESH_COLLIDER
	CONTACT_KEY_HASH_TABLE _hashcontactset;
#endif

	// Colliders
/* -- not used -- also uncomment in InitOPCODECaches()
	PlanesCollider _PlanesCollider; -- not used 
*/
	SphereCollider _SphereCollider;
	OBBCollider _OBBCollider;
	RayCollider _RayCollider;
	AABBTreeCollider _AABBTreeCollider;
/* -- not used -- also uncomment in InitOPCODECaches()
	LSSCollider _LSSCollider;
*/
	// Trimesh caches
	CollisionFaces Faces;
	SphereCache defaultSphereCache;
	OBBCache defaultBoxCache;
	LSSCache defaultCapsuleCache;

	// Trimesh-plane collision vertex use cache
	VertexUseCache VertexUses;

#endif // dTRIMESH_OPCODE
};

#if dTLS_ENABLED

inline TrimeshCollidersCache *GetTrimeshCollidersCache(unsigned uiTLSKind)
{
	EODETLSKIND tkTLSKind = (EODETLSKIND)uiTLSKind;
	return COdeTls::GetTrimeshCollidersCache(tkTLSKind);
}


#else // dTLS_ENABLED

inline TrimeshCollidersCache *GetTrimeshCollidersCache(unsigned uiTLSKind)
{
	extern TrimeshCollidersCache g_ccTrimeshCollidersCache;

	return &g_ccTrimeshCollidersCache;
}


#endif // dTLS_ENABLED





struct dxTriMeshData  : public dBase 
{
    /* Array of flags for which edges and verts should be used on each triangle */
    enum UseFlags
    {
        kEdge0 = 0x1,
        kEdge1 = 0x2,
        kEdge2 = 0x4,
        kVert0 = 0x8,
        kVert1 = 0x10,
        kVert2 = 0x20,

        kUseAll = 0xFF,
    };

    /* Setup the UseFlags array */
    void Preprocess();
    /* For when app changes the vertices */
    void UpdateData();
    
#if dTRIMESH_OPCODE
	Model BVTree;
	MeshInterface Mesh;

    dxTriMeshData();
    ~dxTriMeshData();
    
	void Build(const void* Vertices, int VertexStide, int VertexCount, 
		const void* Indices, int IndexCount, int TriStride, 
		const void* Normals, 
		bool Single);

	/* aabb in model space */
	dVector3 AABBCenter;
	dVector3 AABBExtents;

	// data for use in collision resolution
	const void* Normals;
	uint8* UseFlags;
#endif  // dTRIMESH_OPCODE

#if dTRIMESH_GIMPACT
	const char* m_Vertices;
	int m_VertexStride;
	int m_VertexCount;
	const char* m_Indices;
	int m_TriangleCount;
	int m_TriStride;
	bool m_single;

   dxTriMeshData()
	{
		m_Vertices=NULL;
		m_VertexStride = 12;
		m_VertexCount = 0;
		m_Indices = 0;
		m_TriangleCount = 0;
		m_TriStride = 12;
		m_single = true;
	}

    void Build(const void* Vertices, int VertexStride, int VertexCount,
	       const void* Indices, int IndexCount, int TriStride,
	       const void* Normals,
	      bool Single)
	{
		dIASSERT(Vertices);
		dIASSERT(Indices);
 		dIASSERT(VertexStride);
 		dIASSERT(TriStride);
 		dIASSERT(IndexCount);
		m_Vertices=(const char *)Vertices;
		m_VertexStride = VertexStride;
		m_VertexCount = VertexCount;
		m_Indices = (const char *)Indices;
		m_TriangleCount = IndexCount/3;
		m_TriStride = TriStride;
		m_single = Single;
	}

	inline void GetVertex(unsigned int i, dVector3 Out)
	{
		if(m_single)
		{
			const float * fverts = (const float * )(m_Vertices + m_VertexStride*i);
			Out[0] = fverts[0];
			Out[1] = fverts[1];
			Out[2] = fverts[2];
			Out[3] = 1.0f;
		}
		else
		{
			const double * dverts = (const double * )(m_Vertices + m_VertexStride*i);
			Out[0] = (float)dverts[0];
			Out[1] = (float)dverts[1];
			Out[2] = (float)dverts[2];
			Out[3] = 1.0f;

		}
	}

	inline void GetTriIndices(unsigned int itriangle, unsigned int triindices[3])
	{
		const unsigned int * ind = (const unsigned int * )(m_Indices + m_TriStride*itriangle);
		triindices[0] = ind[0];
		triindices[1] = ind[1];
		triindices[2] = ind[2];
	}
#endif  // dTRIMESH_GIMPACT
};

struct dxTriMesh : public dxGeom{
	// Callbacks
	dTriCallback* Callback;
	dTriArrayCallback* ArrayCallback;
	dTriRayCallback* RayCallback;
    dTriTriMergeCallback* TriMergeCallback;

	// Data types
	dxTriMeshData* Data;

	bool doSphereTC;
	bool doBoxTC;
	bool doCapsuleTC;

	// Functions
	dxTriMesh(dSpaceID Space, dTriMeshDataID Data);
	~dxTriMesh();

	void ClearTCCache();

	bool controlGeometry(int controlClass, int controlCode, void *dataValue, int *dataSize);

	int AABBTest(dxGeom* g, dReal aabb[6]);
	void computeAABB();

#if dTRIMESH_OPCODE

	enum {
		MERGE_NORMALS__SPHERE_DEFAULT = DONT_MERGE_CONTACTS,
	};
	bool controlGeometry_SetMergeSphereContacts(int dataValue);
	bool controlGeometry_GetMergeSphereContacts(int &returnValue);

	// Contact merging option
	dxContactMergeOptions SphereContactsMergeOption;
	// Instance data for last transform.
    dMatrix4 last_trans;

	// Some constants
	// Temporal coherence
	struct SphereTC : public SphereCache{
		dxGeom* Geom;
	};
	dArray<SphereTC> SphereTCCache;

	struct BoxTC : public OBBCache{
		dxGeom* Geom;
	};
	dArray<BoxTC> BoxTCCache;
	
	struct CapsuleTC : public LSSCache{
		dxGeom* Geom;
	};
	dArray<CapsuleTC> CapsuleTCCache;
#endif // dTRIMESH_OPCODE

#if dTRIMESH_GIMPACT
    GIM_TRIMESH  m_collision_trimesh;
	GBUFFER_MANAGER_DATA m_buffer_managers[G_BUFFER_MANAGER__MAX];
#endif  // dTRIMESH_GIMPACT
};

#if 0
#include "collision_kernel.h"
// Fetches a contact
inline dContactGeom* SAFECONTACT(int Flags, dContactGeom* Contacts, int Index, int Stride){
	dIASSERT(Index >= 0 && Index < (Flags & NUMC_MASK));
	return ((dContactGeom*)(((char*)Contacts) + (Index * Stride)));
}
#endif

#if dTRIMESH_OPCODE

inline unsigned FetchTriangleCount(dxTriMesh* TriMesh)
{
	return TriMesh->Data->Mesh.GetNbTriangles();
}

inline void FetchTriangle(dxTriMesh* TriMesh, int Index, const dVector3 Position, const dMatrix3 Rotation, dVector3 Out[3]){
	VertexPointers VP;
	ConversionArea VC;
	TriMesh->Data->Mesh.GetTriangle(VP, Index, VC);
	for (int i = 0; i < 3; i++){
		dVector3 v;
		v[0] = VP.Vertex[i]->x;
		v[1] = VP.Vertex[i]->y;
		v[2] = VP.Vertex[i]->z;
		v[3] = 0;

		dMultiply0_331(Out[i], Rotation, v);
		Out[i][0] += Position[0];
		Out[i][1] += Position[1];
		Out[i][2] += Position[2];
		Out[i][3] = 0;
	}
}

inline void FetchTransformedTriangle(dxTriMesh* TriMesh, int Index, dVector3 Out[3]){
	const dVector3& Position = *(const dVector3*)dGeomGetPosition(TriMesh);
	const dMatrix3& Rotation = *(const dMatrix3*)dGeomGetRotation(TriMesh);
	FetchTriangle(TriMesh, Index, Position, Rotation, Out);
}

inline Matrix4x4& MakeMatrix(const dVector3 Position, const dMatrix3 Rotation, Matrix4x4& Out){
	Out.m[0][0] = (float) Rotation[0];
	Out.m[1][0] = (float) Rotation[1];
	Out.m[2][0] = (float) Rotation[2];

	Out.m[0][1] = (float) Rotation[4];
	Out.m[1][1] = (float) Rotation[5];
	Out.m[2][1] = (float) Rotation[6];

	Out.m[0][2] = (float) Rotation[8];
	Out.m[1][2] = (float) Rotation[9];
	Out.m[2][2] = (float) Rotation[10];

	Out.m[3][0] = (float) Position[0];
	Out.m[3][1] = (float) Position[1];
	Out.m[3][2] = (float) Position[2];

	Out.m[0][3] = 0.0f;
	Out.m[1][3] = 0.0f;
	Out.m[2][3] = 0.0f;
	Out.m[3][3] = 1.0f;

	return Out;
}

inline Matrix4x4& MakeMatrix(dxGeom* g, Matrix4x4& Out){
	const dVector3& Position = *(const dVector3*)dGeomGetPosition(g);
	const dMatrix3& Rotation = *(const dMatrix3*)dGeomGetRotation(g);
	return MakeMatrix(Position, Rotation, Out);
}
#endif // dTRIMESH_OPCODE

#if dTRIMESH_GIMPACT

	#ifdef dDOUBLE
		// To use GIMPACT with doubles, we need to patch a couple of the GIMPACT functions to 
		// convert arguments to floats before sending them in


		/// Convert an gimpact vec3f to a ODE dVector3d:   dVector3[i] = vec3f[i]
		#define dVECTOR3_VEC3F_COPY(b,a) { 			\
			(b)[0] = (a)[0];              \
			(b)[1] = (a)[1];              \
			(b)[2] = (a)[2];              \
			(b)[3] = 0;                   \
		}

		inline void gim_trimesh_get_triangle_verticesODE(GIM_TRIMESH * trimesh, GUINT32 triangle_index, dVector3 v1, dVector3 v2, dVector3 v3) {   
			vec3f src1, src2, src3;
			gim_trimesh_get_triangle_vertices(trimesh, triangle_index, src1, src2, src3);

			dVECTOR3_VEC3F_COPY(v1, src1);
			dVECTOR3_VEC3F_COPY(v2, src2);
			dVECTOR3_VEC3F_COPY(v3, src3);
		}

		// Anything calling gim_trimesh_get_triangle_vertices from within ODE 
		// should be patched through to the dDOUBLE version above

		#define gim_trimesh_get_triangle_vertices gim_trimesh_get_triangle_verticesODE

		inline int gim_trimesh_ray_closest_collisionODE( GIM_TRIMESH *mesh, dVector3 origin, dVector3 dir, GREAL tmax, GIM_TRIANGLE_RAY_CONTACT_DATA *contact ) {
			vec3f dir_vec3f    = { dir[ 0 ],       dir[ 1 ],    dir[ 2 ] };
			vec3f origin_vec3f = { origin[ 0 ], origin[ 1 ], origin[ 2 ] };

			return gim_trimesh_ray_closest_collision( mesh, origin_vec3f, dir_vec3f, tmax, contact );
		}

		inline int gim_trimesh_ray_collisionODE( GIM_TRIMESH *mesh, dVector3 origin, dVector3 dir, GREAL tmax, GIM_TRIANGLE_RAY_CONTACT_DATA *contact ) {
			vec3f dir_vec3f    = { dir[ 0 ],       dir[ 1 ],    dir[ 2 ] };
			vec3f origin_vec3f = { origin[ 0 ], origin[ 1 ], origin[ 2 ] };

			return gim_trimesh_ray_collision( mesh, origin_vec3f, dir_vec3f, tmax, contact );
		}

		#define gim_trimesh_sphere_collisionODE( mesh, Position, Radius, contact ) {	\
			vec3f pos_vec3f = { Position[ 0 ], Position[ 1 ], Position[ 2 ] };			\
			gim_trimesh_sphere_collision( mesh, pos_vec3f, Radius, contact );			\
		}

		#define gim_trimesh_plane_collisionODE( mesh, plane, contact ) { 			\
			vec4f plane_vec4f = { plane[ 0 ], plane[ 1 ], plane[ 2 ], plane[ 3 ] }; \
			gim_trimesh_plane_collision( mesh, plane_vec4f, contact );				\
		}

		#define GIM_AABB_COPY( src, dst ) {		\
			dst[ 0 ]= (src) -> minX;			\
			dst[ 1 ]= (src) -> maxX;			\
			dst[ 2 ]= (src) -> minY;			\
			dst[ 3 ]= (src) -> maxY;			\
			dst[ 4 ]= (src) -> minZ;			\
			dst[ 5 ]= (src) -> maxZ;			\
		}

	#else 
		// With single precision, we can pass native ODE vectors directly to GIMPACT

		#define gim_trimesh_ray_closest_collisionODE 	gim_trimesh_ray_closest_collision
		#define gim_trimesh_ray_collisionODE 			gim_trimesh_ray_collision
		#define gim_trimesh_sphere_collisionODE 		gim_trimesh_sphere_collision
		#define gim_trimesh_plane_collisionODE 			gim_trimesh_plane_collision

		#define GIM_AABB_COPY( src, dst ) 	memcpy( dst, src, 6 * sizeof( GREAL ) )

	#endif // dDouble

inline unsigned FetchTriangleCount(dxTriMesh* TriMesh)
{
	return gim_trimesh_get_triangle_count(&TriMesh->m_collision_trimesh);
}

inline void FetchTransformedTriangle(dxTriMesh* TriMesh, int Index, dVector3 Out[3]){
	gim_trimesh_locks_work_data(&TriMesh->m_collision_trimesh);	
	gim_trimesh_get_triangle_vertices(&TriMesh->m_collision_trimesh, (GUINT32)Index, Out[0], Out[1], Out[2]);
	gim_trimesh_unlocks_work_data(&TriMesh->m_collision_trimesh);
}

inline void MakeMatrix(const dVector3 Position, const dMatrix3 Rotation, mat4f m)
{
	m[0][0] = (float) Rotation[0];
	m[0][1] = (float) Rotation[1];
	m[0][2] = (float) Rotation[2];

	m[1][0] = (float) Rotation[4];
	m[1][1] = (float) Rotation[5];
	m[1][2] = (float) Rotation[6];

	m[2][0] = (float) Rotation[8];
	m[2][1] = (float) Rotation[9];
	m[2][2] = (float) Rotation[10];

	m[0][3] = (float) Position[0];
	m[1][3] = (float) Position[1];
	m[2][3] = (float) Position[2];

}

inline void MakeMatrix(dxGeom* g, mat4f Out){
	const dVector3& Position = *(const dVector3*)dGeomGetPosition(g);
	const dMatrix3& Rotation = *(const dMatrix3*)dGeomGetRotation(g);
	MakeMatrix(Position, Rotation, Out);
}
#endif // dTRIMESH_GIMPACT

// Outputs a matrix to 3 vectors
inline void Decompose(const dMatrix3 Matrix, dVector3 Right, dVector3 Up, dVector3 Direction){
	Right[0] = Matrix[0 * 4 + 0];
	Right[1] = Matrix[1 * 4 + 0];
	Right[2] = Matrix[2 * 4 + 0];
	Right[3] = REAL(0.0);
	Up[0] = Matrix[0 * 4 + 1];
	Up[1] = Matrix[1 * 4 + 1];
	Up[2] = Matrix[2 * 4 + 1];
	Up[3] = REAL(0.0);
	Direction[0] = Matrix[0 * 4 + 2];
	Direction[1] = Matrix[1 * 4 + 2];
	Direction[2] = Matrix[2 * 4 + 2];
	Direction[3] = REAL(0.0);
}

// Outputs a matrix to 3 vectors
inline void Decompose(const dMatrix3 Matrix, dVector3 Vectors[3]){
	Decompose(Matrix, Vectors[0], Vectors[1], Vectors[2]);
}

// Finds barycentric
inline void GetPointFromBarycentric(const dVector3 dv[3], dReal u, dReal v, dVector3 Out){
	dReal w = REAL(1.0) - u - v;

	Out[0] = (dv[0][0] * w) + (dv[1][0] * u) + (dv[2][0] * v);
	Out[1] = (dv[0][1] * w) + (dv[1][1] * u) + (dv[2][1] * v);
	Out[2] = (dv[0][2] * w) + (dv[1][2] * u) + (dv[2][2] * v);
	Out[3] = (dv[0][3] * w) + (dv[1][3] * u) + (dv[2][3] * v);
}

// Performs a callback
inline bool Callback(dxTriMesh* TriMesh, dxGeom* Object, int TriIndex){
	if (TriMesh->Callback != NULL){
		return (TriMesh->Callback(TriMesh, Object, TriIndex)!=0);
	}
	else return true;
}

// Some utilities
template<class T> const T& dcMAX(const T& x, const T& y){
	return x > y ? x : y;
}

template<class T> const T& dcMIN(const T& x, const T& y){
	return x < y ? x : y;
}

dReal SqrDistancePointTri( const dVector3 p, const dVector3 triOrigin, 
                           const dVector3 triEdge1, const dVector3 triEdge2,
                           dReal* pfSParam = 0, dReal* pfTParam = 0 );

dReal SqrDistanceSegments( const dVector3 seg1Origin, const dVector3 seg1Direction, 
                           const dVector3 seg2Origin, const dVector3 seg2Direction,
                           dReal* pfSegP0 = 0, dReal* pfSegP1 = 0 );

dReal SqrDistanceSegTri( const dVector3 segOrigin, const dVector3 segEnd, 
                         const dVector3 triOrigin, 
                         const dVector3 triEdge1, const dVector3 triEdge2,
                         dReal* t = 0, dReal* u = 0, dReal* v = 0 );

inline
void Vector3Subtract( const dVector3 left, const dVector3 right, dVector3 result )
{
    result[0] = left[0] - right[0];
    result[1] = left[1] - right[1];
    result[2] = left[2] - right[2];
    result[3] = REAL(0.0);
}

inline
void Vector3Add( const dVector3 left, const dVector3 right, dVector3 result )
{
    result[0] = left[0] + right[0];
    result[1] = left[1] + right[1];
    result[2] = left[2] + right[2];
    result[3] = REAL(0.0);
}

inline
void Vector3Negate( const dVector3 in, dVector3 out )
{
    out[0] = -in[0];
    out[1] = -in[1];
    out[2] = -in[2];
    out[3] = REAL(0.0);
}

inline
void Vector3Copy( const dVector3 in, dVector3 out )
{
    out[0] = in[0];
    out[1] = in[1];
    out[2] = in[2];
    out[3] = REAL(0.0);
}

inline
void Vector3Multiply( const dVector3 in, dReal scalar, dVector3 out )
{
    out[0] = in[0] * scalar;
    out[1] = in[1] * scalar;
    out[2] = in[2] * scalar;
    out[3] = REAL(0.0);
}

inline
void TransformVector3( const dVector3 in, 
                       const dMatrix3 orientation, const dVector3 position, 
                       dVector3 out )
{
    dMultiply0_331( out, orientation, in );
    out[0] += position[0];
    out[1] += position[1];
    out[2] += position[2];
}

//------------------------------------------------------------------------------
/**
  @brief Check for intersection between triangle and capsule.
  
  @param dist [out] Shortest distance squared between the triangle and 
                    the capsule segment (central axis).
  @param t    [out] t value of point on segment that's the shortest distance 
                    away from the triangle, the coordinates of this point 
                    can be found by (cap.seg.end - cap.seg.start) * t,
                    or cap.seg.ipol(t).
  @param u    [out] Barycentric coord on triangle.
  @param v    [out] Barycentric coord on triangle.
  @return True if intersection exists.
  
  The third Barycentric coord is implicit, ie. w = 1.0 - u - v
  The Barycentric coords give the location of the point on the triangle
  closest to the capsule (where the distance between the two shapes
  is the shortest).
*/
inline
bool IntersectCapsuleTri( const dVector3 segOrigin, const dVector3 segEnd, 
                          const dReal radius, const dVector3 triOrigin, 
                          const dVector3 triEdge0, const dVector3 triEdge1,
                          dReal* dist, dReal* t, dReal* u, dReal* v )
{
    dReal sqrDist = SqrDistanceSegTri( segOrigin, segEnd, triOrigin, triEdge0, triEdge1, 
                                       t, u, v );
  
    if ( dist )
      *dist = sqrDist;
    
    return ( sqrDist <= (radius * radius) );
}


#endif	//_ODE_COLLISION_TRIMESH_INTERNAL_H_
