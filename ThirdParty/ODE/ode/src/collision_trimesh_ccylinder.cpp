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

/*
 *	Triangle-Capsule(Capsule) collider by Alen Ladavac
 *  Ported to ODE by Nguyen Binh
 */

// NOTES from Nguyen Binh
//	14 Apr : Seem to be robust
//       There is a problem when you use original Step and set contact friction
//		surface.mu = dInfinity;
//		More description : 
//			When I dropped Capsule over the bunny ears, it seems to stuck
//			there for a while. I think the cause is when you set surface.mu = dInfinity;
//			the friction force is too high so it just hang the capsule there.
//			So the good cure for this is to set mu = around 1.5 (in my case)
//		For StepFast1, this become as solid as rock : StepFast1 just approximate 
//		friction force.

// NOTES from Croteam's Alen
//As a side note... there are some extra contacts that can be generated
//on the edge between two triangles, and if the capsule penetrates deeply into
//the triangle (usually happens with large mass or low FPS), some such
//contacts can in some cases push the capsule away from the edge instead of
//away from the two triangles. This shows up as capsule slowing down a bit
//when hitting an edge while sliding along a flat tesselated grid of
//triangles. This is only if capsule is standing upwards.

//Same thing can appear whenever a smooth object (e.g sphere) hits such an
//edge, and it needs to be solved as a special case probably. This is a
//problem we are looking forward to address soon.

#include <ode/collision.h>
#include <ode/matrix.h>
#include <ode/rotation.h>
#include <ode/odemath.h>
#include "config.h"
#include "collision_util.h"
#include "collision_trimesh_internal.h"
#include "util.h"

#if dTRIMESH_ENABLED

// OPCODE version
#if dTRIMESH_OPCODE
// largest number, double or float
#if defined(dSINGLE)
#define MAX_REAL	FLT_MAX
#define MIN_REAL	(-FLT_MAX)
#else
#define MAX_REAL	DBL_MAX
#define MIN_REAL	(-DBL_MAX)
#endif

// To optimize before send contacts to dynamic part
#define OPTIMIZE_CONTACTS 1

// dVector3
// r=a-b
#define SUBTRACT(a,b,r) dSubtractVectors3(r, a, b)


// dVector3
// a=b
#define SET(a,b) dCopyVector3(a, b)


// dMatrix3
// a=b
#define SETM(a,b) dCopyMatrix4x4(a, b)


// dVector3
// r=a+b
#define ADD(a,b,r) dAddVectors3(r, a, b)


// dMatrix3, int, dVector3
// v=column a from m
#define GETCOL(m,a,v) dGetMatrixColumn3(v, m, a)


// dVector4, dVector3
// distance between plane p and point v
#define POINTDISTANCE(p,v) dPointPlaneDistance(v, p)


// dVector4, dVector3, dReal
// construct plane from normal and d
#define CONSTRUCTPLANE(plane,normal,d) dConstructPlane(normal, d, plane)


// dVector3
// length of vector a
#define LENGTHOF(a) dCalcVectorLength3(a)


static inline dReal _length2OfVector3(dVector3 v)
{
	return dCalcVectorLengthSquare3(v);
}


// Local contacts data
typedef struct _sLocalContactData
{
	dVector3	vPos;
	dVector3	vNormal;
	dReal		fDepth;
	int			triIndex;
	int			nFlags; // 0 = filtered out, 1 = OK
}sLocalContactData;

struct sTrimeshCapsuleColliderData
{
	sTrimeshCapsuleColliderData(): m_gLocalContacts(NULL), m_ctContacts(0) { memset(m_vN, 0, sizeof(dVector3)); }

	void SetupInitialContext(dxTriMesh *TriMesh, dxGeom *Capsule, int flags, int skip);
	int TestCollisionForSingleTriangle(int ctContacts0, int Triint, dVector3 dv[3], 
		uint8 flags, bool &bOutFinishSearching);

#if OPTIMIZE_CONTACTS
	void _OptimizeLocalContacts();
#endif
	int	_ProcessLocalContacts(dContactGeom *contact, dxTriMesh *TriMesh, dxGeom *Capsule);

	static BOOL _cldClipEdgeToPlane(dVector3 &vEpnt0, dVector3 &vEpnt1, const dVector4& plPlane);
	BOOL _cldTestAxis(const dVector3 &v0, const dVector3 &v1, const dVector3 &v2, 
		dVector3 vAxis, int iAxis, BOOL bNoFlip = FALSE);
	BOOL _cldTestSeparatingAxesOfCapsule(const dVector3 &v0, const dVector3 &v1, 
		const dVector3 &v2, uint8 flags);
	void _cldTestOneTriangleVSCapsule(const dVector3 &v0, const dVector3 &v1, 
		const dVector3 &v2, uint8 flags);

	sLocalContactData   *m_gLocalContacts;
	unsigned int		m_ctContacts;

	// capsule data
	// real time data
	dMatrix3  m_mCapsuleRotation;
	dVector3   m_vCapsulePosition;
	dVector3   m_vCapsuleAxis;
	// static data
	dReal      m_vCapsuleRadius;
	dReal      m_fCapsuleSize;

	// mesh data
	// dMatrix4  mHullDstPl;
	dMatrix3   m_mTriMeshRot;
	dVector3   m_mTriMeshPos;
	dVector3   m_vE0, m_vE1, m_vE2;

	// global collider data
	dVector3 m_vNormal;
	dReal    m_fBestDepth;
	dReal    m_fBestCenter;
	dReal    m_fBestrt;
	int		m_iBestAxis;
	dVector3 m_vN;

	dVector3 m_vV0; 
	dVector3 m_vV1;
	dVector3 m_vV2;

	// ODE contact's specific
	unsigned int m_iFlags;
	int m_iStride;
};

// Capsule lie on axis number 3 = (Z axis)
static const int nCAPSULE_AXIS = 2;


#if OPTIMIZE_CONTACTS

// Use to classify contacts to be "near" in position
static const dReal fSameContactPositionEpsilon = REAL(0.0001); // 1e-4
// Use to classify contacts to be "near" in normal direction
static const dReal fSameContactNormalEpsilon = REAL(0.0001); // 1e-4

// If this two contact can be classified as "near"
inline int _IsNearContacts(sLocalContactData& c1,sLocalContactData& c2)
{
	int bPosNear = 0;
	int bSameDir = 0;
	dVector3	vDiff;

	// First check if they are "near" in position
	SUBTRACT(c1.vPos,c2.vPos,vDiff);
	if (  (dFabs(vDiff[0]) < fSameContactPositionEpsilon)
		&&(dFabs(vDiff[1]) < fSameContactPositionEpsilon)
		&&(dFabs(vDiff[2]) < fSameContactPositionEpsilon))
	{
		bPosNear = 1;
	}

	// Second check if they are "near" in normal direction
	SUBTRACT(c1.vNormal,c2.vNormal,vDiff);
	if (  (dFabs(vDiff[0]) < fSameContactNormalEpsilon)
		&&(dFabs(vDiff[1]) < fSameContactNormalEpsilon)
		&&(dFabs(vDiff[2]) < fSameContactNormalEpsilon) )
	{
		bSameDir = 1;
	}

	// Will be "near" if position and normal direction are "near"
	return (bPosNear && bSameDir);
}

inline int _IsBetter(sLocalContactData& c1,sLocalContactData& c2)
{
	// The not better will be throw away
	// You can change the selection criteria here
	return (c1.fDepth > c2.fDepth);
}

// iterate through gLocalContacts and filtered out "near contact"
void sTrimeshCapsuleColliderData::_OptimizeLocalContacts()
{
	int nContacts = m_ctContacts;
		
	for (int i = 0; i < nContacts-1; i++)
	{
		for (int j = i+1; j < nContacts; j++)
		{
			if (_IsNearContacts(m_gLocalContacts[i],m_gLocalContacts[j]))
			{
				// If they are seem to be the samed then filtered 
				// out the least penetrate one
				if (_IsBetter(m_gLocalContacts[j],m_gLocalContacts[i]))
				{
					m_gLocalContacts[i].nFlags = 0; // filtered 1st contact
				}
				else
				{
					m_gLocalContacts[j].nFlags = 0; // filtered 2nd contact
				}

				// NOTE
				// There is other way is to add two depth together but
				// it not work so well. Why???
			}
		}
	}
}
#endif // OPTIMIZE_CONTACTS

int	sTrimeshCapsuleColliderData::_ProcessLocalContacts(dContactGeom *contact,
	dxTriMesh *TriMesh, dxGeom *Capsule)
{
#if OPTIMIZE_CONTACTS
	if (m_ctContacts > 1 && !(m_iFlags & CONTACTS_UNIMPORTANT))
	{
		// Can be optimized...
		_OptimizeLocalContacts();
	}
#endif		

	unsigned int iContact = 0;
	dContactGeom* Contact = 0;

	unsigned int nFinalContact = 0;

	for (iContact = 0; iContact < m_ctContacts; iContact ++)
	{
        // Ensure that we haven't created too many contacts
        if( nFinalContact >= (m_iFlags & NUMC_MASK)) 
		{
            break;
        }

		if (1 == m_gLocalContacts[iContact].nFlags)
		{
				Contact =  SAFECONTACT(m_iFlags, contact, nFinalContact, m_iStride);
				Contact->depth = m_gLocalContacts[iContact].fDepth;
				SET(Contact->normal,m_gLocalContacts[iContact].vNormal);
				SET(Contact->pos,m_gLocalContacts[iContact].vPos);
				Contact->g1 = TriMesh;
				Contact->g2 = Capsule;
				Contact->side1 = m_gLocalContacts[iContact].triIndex;
				Contact->side2 = -1;

				nFinalContact++;
		}
	}
	// debug
	//if (nFinalContact != m_ctContacts)
	//{
	//	printf("[Info] %d contacts generated,%d  filtered.\n",m_ctContacts,m_ctContacts-nFinalContact);
	//}

	return nFinalContact;
}

BOOL sTrimeshCapsuleColliderData::_cldClipEdgeToPlane( 
	dVector3 &vEpnt0, dVector3 &vEpnt1, const dVector4& plPlane)
{
	// calculate distance of edge points to plane
	dReal fDistance0 = POINTDISTANCE( plPlane, vEpnt0 );
	dReal fDistance1 = POINTDISTANCE( plPlane, vEpnt1 );

	// if both points are behind the plane
	if ( fDistance0 < 0 && fDistance1 < 0 ) 
	{
		// do nothing
		return FALSE;
		// if both points in front of the plane
	} else if ( fDistance0 > 0 && fDistance1 > 0 ) 
	{
		// accept them
		return TRUE;
		// if we have edge/plane intersection
	} else if ((fDistance0 > 0 && fDistance1 < 0) || ( fDistance0 < 0 && fDistance1 > 0)) 
	{
			// find intersection point of edge and plane
			dVector3 vIntersectionPoint;
			vIntersectionPoint[0]= vEpnt0[0]-(vEpnt0[0]-vEpnt1[0])*fDistance0/(fDistance0-fDistance1);
			vIntersectionPoint[1]= vEpnt0[1]-(vEpnt0[1]-vEpnt1[1])*fDistance0/(fDistance0-fDistance1);
			vIntersectionPoint[2]= vEpnt0[2]-(vEpnt0[2]-vEpnt1[2])*fDistance0/(fDistance0-fDistance1);

			// clamp correct edge to intersection point
			if ( fDistance0 < 0 ) 
			{
				SET(vEpnt0,vIntersectionPoint);
			} else 
			{
				SET(vEpnt1,vIntersectionPoint);
			}
			return TRUE;
		}
		return TRUE;
}

BOOL sTrimeshCapsuleColliderData::_cldTestAxis(
						 const dVector3 &v0,
						 const dVector3 &v1,
						 const dVector3 &v2, 
						 dVector3 vAxis, 
						 int iAxis,
						 BOOL bNoFlip/* = FALSE*/) 
{

	// calculate length of separating axis vector
	dReal fL = LENGTHOF(vAxis);
	// if not long enough
	// TODO : dReal epsilon please
	if ( fL < REAL(1e-5) ) 
	{
		// do nothing
		//iLastOutAxis = 0;
		return TRUE;
	}

	// otherwise normalize it
	dNormalize3(vAxis);

	// project capsule on vAxis
	dReal frc = dFabs(dCalcVectorDot3(m_vCapsuleAxis,vAxis))*(m_fCapsuleSize*REAL(0.5)-m_vCapsuleRadius) + m_vCapsuleRadius;

	// project triangle on vAxis
	dReal afv[3];
	afv[0] = dCalcVectorDot3(m_vV0, vAxis);
	afv[1] = dCalcVectorDot3(m_vV1, vAxis);
	afv[2] = dCalcVectorDot3(m_vV2, vAxis);

	dReal fMin = MAX_REAL;
	dReal fMax = MIN_REAL;

	// for each vertex 
	for(int i=0; i<3; i++) 
	{
		// find minimum
		if (afv[i]<fMin) 
		{
			fMin = afv[i];
		}
		// find maximum
		if (afv[i]>fMax) 
		{
			fMax = afv[i];
		}
	}

	// find triangle's center of interval on axis
	dReal fCenter = (fMin+fMax)*REAL(0.5);
	// calculate triangles half interval 
	dReal fTriangleRadius = (fMax-fMin)*REAL(0.5);

	// if they do not overlap, 
	if (dFabs(fCenter) > ( frc + fTriangleRadius ))
	{ 
		// exit, we have no intersection
		return FALSE; 
	}

	// calculate depth 
	dReal fDepth = dFabs(fCenter) - (frc+fTriangleRadius);

	// if greater then best found so far
	if ( fDepth > m_fBestDepth ) 
	{
		// remember depth
		m_fBestDepth  = fDepth;
		m_fBestCenter = fCenter;
		m_fBestrt     = fTriangleRadius;

		m_vNormal[0]     = vAxis[0];
		m_vNormal[1]     = vAxis[1];
		m_vNormal[2]     = vAxis[2];

		m_iBestAxis   = iAxis;

		// flip normal if interval is wrong faced
		if (fCenter<0 && !bNoFlip) 
		{ 
			m_vNormal[0] = -m_vNormal[0];
			m_vNormal[1] = -m_vNormal[1];
			m_vNormal[2] = -m_vNormal[2];

			m_fBestCenter = -fCenter;
		}
	}

	return TRUE;
}

// helper for less key strokes
inline void _CalculateAxis(const dVector3& v1,
						   const dVector3& v2,
						   const dVector3& v3,
						   const dVector3& v4,
						   dVector3& r)
{
	dVector3 t1;
	dVector3 t2;

	SUBTRACT(v1,v2,t1);
	dCalcVectorCross3(t2,t1,v3);
	dCalcVectorCross3(r,t2,v4);
}

BOOL sTrimeshCapsuleColliderData::_cldTestSeparatingAxesOfCapsule(
											const dVector3 &v0,
											const dVector3 &v1,
											const dVector3 &v2,
											uint8 flags) 
{
	// calculate caps centers in absolute space
	dVector3 vCp0;
	vCp0[0] = m_vCapsulePosition[0] + m_vCapsuleAxis[0]*(m_fCapsuleSize*REAL(0.5)-m_vCapsuleRadius);
	vCp0[1] = m_vCapsulePosition[1] + m_vCapsuleAxis[1]*(m_fCapsuleSize*REAL(0.5)-m_vCapsuleRadius);
	vCp0[2] = m_vCapsulePosition[2] + m_vCapsuleAxis[2]*(m_fCapsuleSize*REAL(0.5)-m_vCapsuleRadius);

	dVector3 vCp1;
	vCp1[0] = m_vCapsulePosition[0] - m_vCapsuleAxis[0]*(m_fCapsuleSize*REAL(0.5)-m_vCapsuleRadius);
	vCp1[1] = m_vCapsulePosition[1] - m_vCapsuleAxis[1]*(m_fCapsuleSize*REAL(0.5)-m_vCapsuleRadius);
	vCp1[2] = m_vCapsulePosition[2] - m_vCapsuleAxis[2]*(m_fCapsuleSize*REAL(0.5)-m_vCapsuleRadius);

	// reset best axis
	m_iBestAxis = 0;
	// reset best depth
	m_fBestDepth  = -MAX_REAL;
	// reset separating axis vector
	dVector3 vAxis = {REAL(0.0),REAL(0.0),REAL(0.0),REAL(0.0)};

	// Epsilon value for checking axis vector length 
	const dReal fEpsilon = 1e-6f;

	// Translate triangle to Cc cord.
	SUBTRACT(v0, m_vCapsulePosition, m_vV0);
	SUBTRACT(v1, m_vCapsulePosition, m_vV1);
	SUBTRACT(v2, m_vCapsulePosition, m_vV2);

	// We begin to test for 19 separating axis now
	// I wonder does it help if we employ the method like ISA-GJK???
	// Or at least we should do experiment and find what axis will
	// be most likely to be separating axis to check it first.

	// Original
	// axis m_vN
	//vAxis = -m_vN;
	vAxis[0] = - m_vN[0];
	vAxis[1] = - m_vN[1];
	vAxis[2] = - m_vN[2];
	if (!_cldTestAxis(v0, v1, v2, vAxis, 1, TRUE)) 
	{ 
		return FALSE; 
	}

	if (flags & dxTriMeshData::kEdge0)
	{
		// axis CxE0 - Edge 0
		dCalcVectorCross3(vAxis,m_vCapsuleAxis,m_vE0);
		//vAxis = dCalcVectorCross3( m_vCapsuleAxis cross vE0 );
		if (_length2OfVector3( vAxis ) > fEpsilon) {
			if (!_cldTestAxis(v0, v1, v2, vAxis, 2)) { 
				return FALSE;
			}
		}
	}

	if (flags & dxTriMeshData::kEdge1)
	{
		// axis CxE1 - Edge 1
		dCalcVectorCross3(vAxis,m_vCapsuleAxis,m_vE1);
		//vAxis = ( m_vCapsuleAxis cross m_vE1 );
		if (_length2OfVector3( vAxis ) > fEpsilon) {
			if (!_cldTestAxis(v0, v1, v2, vAxis, 3)) {
				return FALSE;
			}
		}
	}

	if (flags & dxTriMeshData::kEdge2)
	{
		// axis CxE2 - Edge 2
		//vAxis = ( m_vCapsuleAxis cross m_vE2 );
		dCalcVectorCross3(vAxis,m_vCapsuleAxis,m_vE2);
		if (_length2OfVector3( vAxis ) > fEpsilon) {
			if (!_cldTestAxis(v0, v1, v2, vAxis, 4)) {
				return FALSE;
			}
		}
	}

	if (flags & dxTriMeshData::kEdge0)
	{
		// first capsule point
		// axis ((Cp0-V0) x E0) x E0
		_CalculateAxis(vCp0,v0,m_vE0,m_vE0,vAxis);
	//	vAxis = ( ( vCp0-v0) cross vE0 ) cross vE0;
		if (_length2OfVector3( vAxis ) > fEpsilon) {
			if (!_cldTestAxis(v0, v1, v2, vAxis, 5)) {
				return FALSE;
			}
		}
	}

	if (flags & dxTriMeshData::kEdge1)
	{
		// axis ((Cp0-V1) x E1) x E1
		_CalculateAxis(vCp0,v1,m_vE1,m_vE1,vAxis);
		//vAxis = ( ( vCp0-v1) cross vE1 ) cross vE1;
		if (_length2OfVector3( vAxis ) > fEpsilon) {
			if (!_cldTestAxis(v0, v1, v2, vAxis, 6)) {
				return FALSE;
			}
		}
	}

	if (flags & dxTriMeshData::kEdge2)
	{
		// axis ((Cp0-V2) x E2) x E2
		_CalculateAxis(vCp0,v2,m_vE2,m_vE2,vAxis);
		//vAxis = ( ( vCp0-v2) cross vE2 ) cross vE2;
		if (_length2OfVector3( vAxis ) > fEpsilon) {
			if (!_cldTestAxis(v0, v1, v2, vAxis, 7)) {
				return FALSE;
			}
		}
	}

	if (flags & dxTriMeshData::kEdge0)
	{
		// second capsule point
		// axis ((Cp1-V0) x E0) x E0
		_CalculateAxis(vCp1,v0,m_vE0,m_vE0,vAxis);
		//vAxis = ( ( vCp1-v0 ) cross vE0 ) cross vE0;
		if (_length2OfVector3( vAxis ) > fEpsilon) {
			if (!_cldTestAxis(v0, v1, v2, vAxis, 8)) {
				return FALSE;
			}
		}
	}

	if (flags & dxTriMeshData::kEdge1)
	{
		// axis ((Cp1-V1) x E1) x E1
		_CalculateAxis(vCp1,v1,m_vE1,m_vE1,vAxis);
		//vAxis = ( ( vCp1-v1 ) cross vE1 ) cross vE1;
		if (_length2OfVector3( vAxis ) > fEpsilon) {
			if (!_cldTestAxis(v0, v1, v2, vAxis, 9)) {
				return FALSE;
			}
		}
	}

	if (flags & dxTriMeshData::kEdge2)
	{
		// axis ((Cp1-V2) x E2) x E2
		_CalculateAxis(vCp1,v2,m_vE2,m_vE2,vAxis);
		//vAxis = ( ( vCp1-v2 ) cross vE2 ) cross vE2;
		if (_length2OfVector3( vAxis ) > fEpsilon) {
			if (!_cldTestAxis(v0, v1, v2, vAxis, 10)) {
				return FALSE;
			}
		}
	}

	if (flags & dxTriMeshData::kVert0)
	{
		// first vertex on triangle
		// axis ((V0-Cp0) x C) x C
		_CalculateAxis(v0,vCp0,m_vCapsuleAxis,m_vCapsuleAxis,vAxis);
		//vAxis = ( ( v0-vCp0 ) cross m_vCapsuleAxis ) cross m_vCapsuleAxis;
		if (_length2OfVector3( vAxis ) > fEpsilon) {
			if (!_cldTestAxis(v0, v1, v2, vAxis, 11)) {
				return FALSE;
			}
		}
	}

	if (flags & dxTriMeshData::kVert1)
	{
		// second vertex on triangle
		// axis ((V1-Cp0) x C) x C
		_CalculateAxis(v1,vCp0,m_vCapsuleAxis,m_vCapsuleAxis,vAxis);	
		//vAxis = ( ( v1-vCp0 ) cross vCapsuleAxis ) cross vCapsuleAxis;
		if (_length2OfVector3( vAxis ) > fEpsilon) {
			if (!_cldTestAxis(v0, v1, v2, vAxis, 12)) {
				return FALSE;
			}
		}
	}

	if (flags & dxTriMeshData::kVert2)
	{
		// third vertex on triangle
		// axis ((V2-Cp0) x C) x C
		_CalculateAxis(v2,vCp0,m_vCapsuleAxis,m_vCapsuleAxis,vAxis);
		//vAxis = ( ( v2-vCp0 ) cross vCapsuleAxis ) cross vCapsuleAxis;
		if (_length2OfVector3( vAxis ) > fEpsilon) {
			if (!_cldTestAxis(v0, v1, v2, vAxis, 13)) {
				return FALSE;
			}
		}
	}

	// Test as separating axes direction vectors between each triangle
	// edge and each capsule's cap center

	if (flags & dxTriMeshData::kVert0)
	{
		// first triangle vertex and first capsule point
		//vAxis = v0 - vCp0;
		SUBTRACT(v0,vCp0,vAxis);
		if (_length2OfVector3( vAxis ) > fEpsilon) {
			if (!_cldTestAxis(v0, v1, v2, vAxis, 14)) {
				return FALSE;
			}
		}
	}

	if (flags & dxTriMeshData::kVert1)
	{
		// second triangle vertex and first capsule point
		//vAxis = v1 - vCp0;
		SUBTRACT(v1,vCp0,vAxis);
		if (_length2OfVector3( vAxis ) > fEpsilon) {
			if (!_cldTestAxis(v0, v1, v2, vAxis, 15)) {
				return FALSE;
			}
		}
	}

	if (flags & dxTriMeshData::kVert2)
	{
		// third triangle vertex and first capsule point
		//vAxis = v2 - vCp0;
		SUBTRACT(v2,vCp0,vAxis);
		if (_length2OfVector3( vAxis ) > fEpsilon) {
			if (!_cldTestAxis(v0, v1, v2, vAxis, 16)) {
				return FALSE;
			}
		}
	}

	if (flags & dxTriMeshData::kVert0)
	{
		// first triangle vertex and second capsule point
		//vAxis = v0 - vCp1;
		SUBTRACT(v0,vCp1,vAxis);
		if (_length2OfVector3( vAxis ) > fEpsilon) {
			if (!_cldTestAxis(v0, v1, v2, vAxis, 17)) {
				return FALSE;
			}
		}
	}

	if (flags & dxTriMeshData::kVert1)
	{
		// second triangle vertex and second capsule point
		//vAxis = v1 - vCp1;
		SUBTRACT(v1,vCp1,vAxis);
		if (_length2OfVector3( vAxis ) > fEpsilon) {
			if (!_cldTestAxis(v0, v1, v2, vAxis, 18)) {
				return FALSE;
			}
		}
	}

	if (flags & dxTriMeshData::kVert2)
	{
		// third triangle vertex and second capsule point
		//vAxis = v2 - vCp1;
		SUBTRACT(v2,vCp1,vAxis);
		if (_length2OfVector3( vAxis ) > fEpsilon) {
			if (!_cldTestAxis(v0, v1, v2, vAxis, 19)) {
				return FALSE;
			}
		}
	}

	return TRUE;
}

// test one mesh triangle on intersection with capsule
void sTrimeshCapsuleColliderData::_cldTestOneTriangleVSCapsule(
	const dVector3 &v0, const dVector3 &v1, const dVector3 &v2,
	uint8 flags)
{
	// calculate edges
	SUBTRACT(v1,v0,m_vE0);
	SUBTRACT(v2,v1,m_vE1);
	SUBTRACT(v0,v2,m_vE2);

	dVector3	_minus_vE0;
	SUBTRACT(v0,v1,_minus_vE0);

	// calculate poly normal
	dCalcVectorCross3(m_vN,m_vE1,_minus_vE0);

	// Even though all triangles might be initially valid, 
	// a triangle may degenerate into a segment after applying 
	// space transformation.
	if (!dSafeNormalize3(m_vN))
	{
		return;
	}

	// create plane from triangle
	dReal plDistance = -dCalcVectorDot3(v0,m_vN);
	dVector4 plTrianglePlane;
	CONSTRUCTPLANE(plTrianglePlane,m_vN,plDistance);

	// calculate capsule distance to plane
	dReal fDistanceCapsuleCenterToPlane = POINTDISTANCE(plTrianglePlane,m_vCapsulePosition);

	// Capsule must be over positive side of triangle
	if (fDistanceCapsuleCenterToPlane < 0 /* && !bDoubleSided*/) 
	{
		// if not don't generate contacts
		return;
	}

	dVector3 vPnt0;
	SET	(vPnt0,v0);
	dVector3 vPnt1;
	SET	(vPnt1,v1);
	dVector3 vPnt2;
	SET	(vPnt2,v2);

	if (fDistanceCapsuleCenterToPlane < 0 )
	{
		SET	(vPnt0,v0);
		SET	(vPnt1,v2);
		SET	(vPnt2,v1);
	}

	// do intersection test and find best separating axis
	if (!_cldTestSeparatingAxesOfCapsule(vPnt0, vPnt1, vPnt2, flags))
	{
		// if not found do nothing
		return;
	}

	// if best separation axis is not found
	if (m_iBestAxis == 0 ) 
	{
		// this should not happen (we should already exit in that case)
		dIASSERT(FALSE);
		// do nothing
		return;
	}

	// calculate caps centers in absolute space
	dVector3 vCposTrans;
	vCposTrans[0] = m_vCapsulePosition[0] + m_vNormal[0]*m_vCapsuleRadius;
	vCposTrans[1] = m_vCapsulePosition[1] + m_vNormal[1]*m_vCapsuleRadius;
	vCposTrans[2] = m_vCapsulePosition[2] + m_vNormal[2]*m_vCapsuleRadius;

	dVector3 vCEdgePoint0;
	vCEdgePoint0[0]  = vCposTrans[0] + m_vCapsuleAxis[0]*(m_fCapsuleSize*REAL(0.5)-m_vCapsuleRadius);
	vCEdgePoint0[1]  = vCposTrans[1] + m_vCapsuleAxis[1]*(m_fCapsuleSize*REAL(0.5)-m_vCapsuleRadius);
	vCEdgePoint0[2]  = vCposTrans[2] + m_vCapsuleAxis[2]*(m_fCapsuleSize*REAL(0.5)-m_vCapsuleRadius);
    
	dVector3 vCEdgePoint1;
	vCEdgePoint1[0] = vCposTrans[0] - m_vCapsuleAxis[0]*(m_fCapsuleSize*REAL(0.5)-m_vCapsuleRadius);
	vCEdgePoint1[1] = vCposTrans[1] - m_vCapsuleAxis[1]*(m_fCapsuleSize*REAL(0.5)-m_vCapsuleRadius);
	vCEdgePoint1[2] = vCposTrans[2] - m_vCapsuleAxis[2]*(m_fCapsuleSize*REAL(0.5)-m_vCapsuleRadius);

	// transform capsule edge points into triangle space
	vCEdgePoint0[0] -= vPnt0[0];
	vCEdgePoint0[1] -= vPnt0[1];
	vCEdgePoint0[2] -= vPnt0[2];

	vCEdgePoint1[0] -= vPnt0[0];
	vCEdgePoint1[1] -= vPnt0[1];
	vCEdgePoint1[2] -= vPnt0[2];

	dVector4 plPlane;
	dVector3 _minus_vN;
	_minus_vN[0] = -m_vN[0];
	_minus_vN[1] = -m_vN[1];
	_minus_vN[2] = -m_vN[2];
	// triangle plane
	CONSTRUCTPLANE(plPlane,_minus_vN,0);
	//plPlane = Plane4f( -m_vN, 0);

	if (!_cldClipEdgeToPlane( vCEdgePoint0, vCEdgePoint1, plPlane )) 
	{ 
		return; 
	}

	// plane with edge 0
	dVector3 vTemp;
	dCalcVectorCross3(vTemp,m_vN,m_vE0);
	CONSTRUCTPLANE(plPlane, vTemp, REAL(1e-5));
	if (!_cldClipEdgeToPlane( vCEdgePoint0, vCEdgePoint1, plPlane ))
	{ 
		return; 
	}

	dCalcVectorCross3(vTemp,m_vN,m_vE1);
	CONSTRUCTPLANE(plPlane, vTemp, -(dCalcVectorDot3(m_vE0,vTemp)-REAL(1e-5)));
	if (!_cldClipEdgeToPlane( vCEdgePoint0, vCEdgePoint1, plPlane )) 
	{ 
		return; 
	}

	dCalcVectorCross3(vTemp,m_vN,m_vE2);
	CONSTRUCTPLANE(plPlane, vTemp, REAL(1e-5));
	if (!_cldClipEdgeToPlane( vCEdgePoint0, vCEdgePoint1, plPlane )) { 
		return; 
	}

	// return capsule edge points into absolute space
	vCEdgePoint0[0] += vPnt0[0];
	vCEdgePoint0[1] += vPnt0[1];
	vCEdgePoint0[2] += vPnt0[2];

	vCEdgePoint1[0] += vPnt0[0];
	vCEdgePoint1[1] += vPnt0[1];
	vCEdgePoint1[2] += vPnt0[2];

	// calculate depths for both contact points
	SUBTRACT(vCEdgePoint0,m_vCapsulePosition,vTemp);
	dReal fDepth0 = dCalcVectorDot3(vTemp,m_vNormal) - (m_fBestCenter-m_fBestrt);
	SUBTRACT(vCEdgePoint1,m_vCapsulePosition,vTemp);
	dReal fDepth1 = dCalcVectorDot3(vTemp,m_vNormal) - (m_fBestCenter-m_fBestrt);

	// clamp depths to zero
	if (fDepth0 < 0) 
	{
		fDepth0 = 0.0f;
	}

	if (fDepth1 < 0 ) 
	{
		fDepth1 = 0.0f;
	}

	// Cached contacts's data
	// contact 0
    dIASSERT(m_ctContacts < (m_iFlags & NUMC_MASK)); // Do not call function if there is no room to store result
	m_gLocalContacts[m_ctContacts].fDepth = fDepth0;
	SET(m_gLocalContacts[m_ctContacts].vNormal,m_vNormal);
	SET(m_gLocalContacts[m_ctContacts].vPos,vCEdgePoint0);
	m_gLocalContacts[m_ctContacts].nFlags = 1;
	m_ctContacts++;

	if (m_ctContacts < (m_iFlags & NUMC_MASK)) {
		// contact 1
		m_gLocalContacts[m_ctContacts].fDepth = fDepth1;
		SET(m_gLocalContacts[m_ctContacts].vNormal,m_vNormal);
		SET(m_gLocalContacts[m_ctContacts].vPos,vCEdgePoint1);
		m_gLocalContacts[m_ctContacts].nFlags = 1;
		m_ctContacts++;
    }
}

void sTrimeshCapsuleColliderData::SetupInitialContext(dxTriMesh *TriMesh, dxGeom *Capsule, 
	int flags, int skip)
{
	const dMatrix3* pRot = (const dMatrix3*)dGeomGetRotation(Capsule);
	memcpy(m_mCapsuleRotation, pRot, sizeof(dMatrix3));

	const dVector3* pDst = (const dVector3*)dGeomGetPosition(Capsule);
	memcpy(m_vCapsulePosition, pDst, sizeof(dVector3));

	m_vCapsuleAxis[0] = m_mCapsuleRotation[0*4 + nCAPSULE_AXIS];
	m_vCapsuleAxis[1] = m_mCapsuleRotation[1*4 + nCAPSULE_AXIS];
	m_vCapsuleAxis[2] = m_mCapsuleRotation[2*4 + nCAPSULE_AXIS];

	// Get size of Capsule
	dGeomCapsuleGetParams(Capsule, &m_vCapsuleRadius, &m_fCapsuleSize);
	m_fCapsuleSize += 2*m_vCapsuleRadius;

	const dMatrix3* pTriRot = (const dMatrix3*)dGeomGetRotation(TriMesh);
	memcpy(m_mTriMeshRot, pTriRot, sizeof(dMatrix3));

	const dVector3* pTriPos = (const dVector3*)dGeomGetPosition(TriMesh);
	memcpy(m_mTriMeshPos, pTriPos, sizeof(dVector3));

	// global info for contact creation
	m_iStride			=skip;
	m_iFlags			=flags;

	// reset contact counter
	m_ctContacts = 0;	

	// reset best depth
	m_fBestDepth  = - MAX_REAL;
	m_fBestCenter = 0;
	m_fBestrt     = 0;

	// reset collision normal
	m_vNormal[0] = REAL(0.0);
	m_vNormal[1] = REAL(0.0);
	m_vNormal[2] = REAL(0.0);
}

int sTrimeshCapsuleColliderData::TestCollisionForSingleTriangle(int ctContacts0, 
	int Triint, dVector3 dv[3], uint8 flags, bool &bOutFinishSearching)
{
	// test this triangle
	_cldTestOneTriangleVSCapsule(dv[0],dv[1],dv[2], flags);

	// fill-in tri index for generated contacts
	for (; ctContacts0 < (int)m_ctContacts; ctContacts0++)
		m_gLocalContacts[ctContacts0].triIndex = Triint;

	// Putting "break" at the end of loop prevents unnecessary checks on first pass and "continue"
	bOutFinishSearching = (m_ctContacts >= (m_iFlags & NUMC_MASK));

	return ctContacts0;
}


static void dQueryCCTLPotentialCollisionTriangles(OBBCollider &Collider, 
	const sTrimeshCapsuleColliderData &cData, dxTriMesh *TriMesh, dxGeom *Capsule,
	OBBCache &BoxCache)
{
	// It is a potential issue to explicitly cast to float 
	// if custom width floating point type is introduced in OPCODE.
	// It is necessary to make a typedef and cast to it
	// (e.g. typedef float opc_float;)
	// However I'm not sure in what header it should be added.

	const dVector3 &vCapsulePosition = cData.m_vCapsulePosition;

	Point cCenter(/*(float)*/ vCapsulePosition[0], /*(float)*/ vCapsulePosition[1], /*(float)*/ vCapsulePosition[2]);
	Point cExtents(/*(float)*/ cData.m_vCapsuleRadius, /*(float)*/ cData.m_vCapsuleRadius,/*(float)*/ cData.m_fCapsuleSize/2);

	Matrix3x3 obbRot;

	const dMatrix3 &mCapsuleRotation = cData.m_mCapsuleRotation;

	obbRot[0][0] = /*(float)*/ mCapsuleRotation[0];
	obbRot[1][0] = /*(float)*/ mCapsuleRotation[1];
	obbRot[2][0] = /*(float)*/ mCapsuleRotation[2];

	obbRot[0][1] = /*(float)*/ mCapsuleRotation[4];
	obbRot[1][1] = /*(float)*/ mCapsuleRotation[5];
	obbRot[2][1] = /*(float)*/ mCapsuleRotation[6];

	obbRot[0][2] = /*(float)*/ mCapsuleRotation[8];
	obbRot[1][2] = /*(float)*/ mCapsuleRotation[9];
	obbRot[2][2] = /*(float)*/ mCapsuleRotation[10];

	OBB obbCapsule(cCenter,cExtents,obbRot);

	Matrix4x4 CapsuleMatrix;
	MakeMatrix(vCapsulePosition, mCapsuleRotation, CapsuleMatrix);

	Matrix4x4 MeshMatrix;
	MakeMatrix(cData.m_mTriMeshPos, cData.m_mTriMeshRot, MeshMatrix);

	// TC results
	if (TriMesh->doBoxTC) {
		dxTriMesh::BoxTC* BoxTC = 0;
		for (int i = 0; i < TriMesh->BoxTCCache.size(); i++){
			if (TriMesh->BoxTCCache[i].Geom == Capsule){
				BoxTC = &TriMesh->BoxTCCache[i];
				break;
			}
		}
		if (!BoxTC){
			TriMesh->BoxTCCache.push(dxTriMesh::BoxTC());

			BoxTC = &TriMesh->BoxTCCache[TriMesh->BoxTCCache.size() - 1];
			BoxTC->Geom = Capsule;
			BoxTC->FatCoeff = 1.0f;
		}

		// Intersect
		Collider.SetTemporalCoherence(true);
		Collider.Collide(*BoxTC, obbCapsule, TriMesh->Data->BVTree, null, &MeshMatrix);
	}
	else {
		Collider.SetTemporalCoherence(false);
		Collider.Collide(BoxCache, obbCapsule, TriMesh->Data->BVTree, null,&MeshMatrix);
	}
}

// capsule - trimesh by CroTeam
// Ported by Nguyem Binh
int dCollideCCTL(dxGeom *o1, dxGeom *o2, int flags, dContactGeom *contact, int skip)
{
	dIASSERT (skip >= (int)sizeof(dContactGeom));
	dIASSERT (o1->type == dTriMeshClass);
	dIASSERT (o2->type == dCapsuleClass);
	dIASSERT ((flags & NUMC_MASK) >= 1);
	
	int nContactCount = 0;

	dxTriMesh *TriMesh = (dxTriMesh*)o1;
	dxGeom *Capsule = o2;

	sTrimeshCapsuleColliderData cData;
	cData.SetupInitialContext(TriMesh, Capsule, flags, skip);

	const unsigned uiTLSKind = TriMesh->getParentSpaceTLSKind();
	dIASSERT(uiTLSKind == Capsule->getParentSpaceTLSKind()); // The colliding spaces must use matching cleanup method
	TrimeshCollidersCache *pccColliderCache = GetTrimeshCollidersCache(uiTLSKind);
	OBBCollider& Collider = pccColliderCache->_OBBCollider;

	// Will it better to use LSS here? -> confirm Pierre.
	dQueryCCTLPotentialCollisionTriangles(Collider, cData, 
		TriMesh, Capsule, pccColliderCache->defaultBoxCache);

	 if (Collider.GetContactStatus()) 
	 {
		 // Retrieve data
		 int TriCount = Collider.GetNbTouchedPrimitives();

		 if (TriCount != 0)
		 {
			 const int* Triangles = (const int*)Collider.GetTouchedPrimitives();

			 if (TriMesh->ArrayCallback != null)
			 {
				 TriMesh->ArrayCallback(TriMesh, Capsule, Triangles, TriCount);
			 }

			// allocate buffer for local contacts on stack
			cData.m_gLocalContacts = (sLocalContactData*)dALLOCA16(sizeof(sLocalContactData)*(cData.m_iFlags & NUMC_MASK));

			unsigned int ctContacts0 = cData.m_ctContacts;

			uint8* UseFlags = TriMesh->Data->UseFlags;

			// loop through all intersecting triangles
			for (int i = 0; i < TriCount; i++)
			{
				const int Triint = Triangles[i];
				if (!Callback(TriMesh, Capsule, Triint)) continue;

				dVector3 dv[3];
				FetchTriangle(TriMesh, Triint, cData.m_mTriMeshPos, cData.m_mTriMeshRot, dv);

				uint8 flags = UseFlags ? UseFlags[Triint] : dxTriMeshData::kUseAll;

				bool bFinishSearching;
				ctContacts0 = cData.TestCollisionForSingleTriangle(ctContacts0, Triint, dv, flags, bFinishSearching);

				if (bFinishSearching) 
				{
					break;
				}
			}

			if (cData.m_ctContacts != 0)
			{
				nContactCount = cData._ProcessLocalContacts(contact, TriMesh, Capsule);
			}
		 }
	 }

	return nContactCount;
}
#endif

// GIMPACT version
#if dTRIMESH_GIMPACT
#define nCAPSULE_AXIS 2
// capsule - trimesh  By francisco leon
int dCollideCCTL(dxGeom *o1, dxGeom *o2, int flags, dContactGeom *contact, int skip)
{
	dIASSERT (skip >= (int)sizeof(dContactGeom));
	dIASSERT (o1->type == dTriMeshClass);
	dIASSERT (o2->type == dCapsuleClass);
	dIASSERT ((flags & NUMC_MASK) >= 1);
	
	dxTriMesh* TriMesh = (dxTriMesh*)o1;
	dxGeom*	   gCylinder = o2;

    //Get capsule params
    dMatrix3  mCapsuleRotation;
    dVector3   vCapsulePosition;
    dVector3   vCapsuleAxis;
    dReal      vCapsuleRadius;
    dReal      fCapsuleSize;
    dMatrix3* pRot = (dMatrix3*) dGeomGetRotation(gCylinder);
	memcpy(mCapsuleRotation,pRot,sizeof(dMatrix3));
	dVector3* pDst = (dVector3*)dGeomGetPosition(gCylinder);
	memcpy(vCapsulePosition,pDst,sizeof(dVector3));
	//Axis
	vCapsuleAxis[0] = mCapsuleRotation[0*4 + nCAPSULE_AXIS];
	vCapsuleAxis[1] = mCapsuleRotation[1*4 + nCAPSULE_AXIS];
	vCapsuleAxis[2] = mCapsuleRotation[2*4 + nCAPSULE_AXIS];
	// Get size of CCylinder
	dGeomCCylinderGetParams(gCylinder,&vCapsuleRadius,&fCapsuleSize);
	fCapsuleSize*=0.5f;
	//Set Capsule params
	GIM_CAPSULE_DATA capsule;

	capsule.m_radius = vCapsuleRadius;
	VEC_SCALE(capsule.m_point1,fCapsuleSize,vCapsuleAxis);
	VEC_SUM(capsule.m_point1,vCapsulePosition,capsule.m_point1);
	VEC_SCALE(capsule.m_point2,-fCapsuleSize,vCapsuleAxis);
	VEC_SUM(capsule.m_point2,vCapsulePosition,capsule.m_point2);


//Create contact list
    GDYNAMIC_ARRAY trimeshcontacts;
    GIM_CREATE_CONTACT_LIST(trimeshcontacts);

    //Collide trimeshe vs capsule
    gim_trimesh_capsule_collision(&TriMesh->m_collision_trimesh,&capsule,&trimeshcontacts);


    if(trimeshcontacts.m_size == 0)
    {
        GIM_DYNARRAY_DESTROY(trimeshcontacts);
        return 0;
    }

    GIM_CONTACT * ptrimeshcontacts = GIM_DYNARRAY_POINTER(GIM_CONTACT,trimeshcontacts);

	unsigned contactcount = trimeshcontacts.m_size;
	unsigned contactmax = (unsigned)(flags & NUMC_MASK);
	if (contactcount > contactmax)
	{
		contactcount = contactmax;
	}

    dContactGeom* pcontact;
	unsigned i;

	for (i=0;i<contactcount;i++)
	{
        pcontact = SAFECONTACT(flags, contact, i, skip);

        pcontact->pos[0] = ptrimeshcontacts->m_point[0];
        pcontact->pos[1] = ptrimeshcontacts->m_point[1];
        pcontact->pos[2] = ptrimeshcontacts->m_point[2];
        pcontact->pos[3] = 1.0f;

        pcontact->normal[0] = ptrimeshcontacts->m_normal[0];
        pcontact->normal[1] = ptrimeshcontacts->m_normal[1];
        pcontact->normal[2] = ptrimeshcontacts->m_normal[2];
        pcontact->normal[3] = 0;

        pcontact->depth = ptrimeshcontacts->m_depth;
        pcontact->g1 = TriMesh;
        pcontact->g2 = gCylinder;
        pcontact->side1 = ptrimeshcontacts->m_feature1;
        pcontact->side2 = -1;
        
        ptrimeshcontacts++;
	}

	GIM_DYNARRAY_DESTROY(trimeshcontacts);

    return (int)contactcount;
}
#endif

#endif // dTRIMESH_ENABLED
