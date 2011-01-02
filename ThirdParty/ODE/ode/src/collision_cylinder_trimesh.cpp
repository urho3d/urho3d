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
 *	Cylinder-trimesh collider by Alen Ladavac
 *   Ported to ODE by Nguyen Binh
 */


#include <ode/collision.h>
#include <ode/matrix.h>
#include <ode/rotation.h>
#include <ode/odemath.h>
#include "config.h"
#include "collision_util.h"
#include "collision_trimesh_internal.h"
#include "util.h"

#if dTRIMESH_ENABLED

#define MAX_REAL	dInfinity
static const int	nCYLINDER_AXIS				= 2;
static const int    nCYLINDER_CIRCLE_SEGMENTS	= 8;
static const int    nMAX_CYLINDER_TRIANGLE_CLIP_POINTS	= 12;

#define OPTIMIZE_CONTACTS 1

// Local contacts data
typedef struct _sLocalContactData
{
	dVector3	vPos;
	dVector3	vNormal;
	dReal		fDepth;
	int			triIndex;
	int			nFlags; // 0 = filtered out, 1 = OK
}sLocalContactData;

struct sCylinderTrimeshColliderData
{
	sCylinderTrimeshColliderData(int flags, int skip): m_iFlags(flags), m_iSkip(skip), m_nContacts(0), m_gLocalContacts(NULL) {}

#ifdef OPTIMIZE_CONTACTS
	void _OptimizeLocalContacts();
#endif
	void _InitCylinderTrimeshData(dxGeom *Cylinder, dxTriMesh *Trimesh);
	int	_ProcessLocalContacts(dContactGeom *contact, dxGeom *Cylinder, dxTriMesh *Trimesh);

	bool _cldTestAxis(const dVector3 &v0, const dVector3 &v1, const dVector3 &v2, 
		dVector3& vAxis, int iAxis, bool bNoFlip = false);
	bool _cldTestCircleToEdgeAxis(
		const dVector3 &v0, const dVector3 &v1, const dVector3 &v2,
		const dVector3 &vCenterPoint, const dVector3 &vCylinderAxis1,
		const dVector3 &vVx0, const dVector3 &vVx1, int iAxis);
	bool _cldTestSeparatingAxes(const dVector3 &v0, const dVector3 &v1, const dVector3 &v2);
	bool _cldClipCylinderEdgeToTriangle(const dVector3 &v0, const dVector3 &v1, const dVector3 &v2);
	void _cldClipCylinderToTriangle(const dVector3 &v0, const dVector3 &v1, const dVector3 &v2);
	void TestOneTriangleVsCylinder(const dVector3 &v0, const dVector3 &v1, const dVector3 &v2, 
		const bool bDoubleSided);
	int TestCollisionForSingleTriangle(int ctContacts0, int Triint, dVector3 dv[3], 
		bool &bOutFinishSearching);

	// cylinder data
	dMatrix3	m_mCylinderRot;
	dQuaternion	m_qCylinderRot;
	dQuaternion	m_qInvCylinderRot;
	dVector3	m_vCylinderPos;
	dVector3	m_vCylinderAxis;
	dReal		m_fCylinderRadius;
	dReal		m_fCylinderSize;
	dVector3	m_avCylinderNormals[nCYLINDER_CIRCLE_SEGMENTS];

	// mesh data
	dQuaternion	m_qTrimeshRot;
	dQuaternion	m_qInvTrimeshRot;
	dMatrix3	m_mTrimeshRot;
	dVector3	m_vTrimeshPos;

	// global collider data
	dVector3	m_vBestPoint;
	dReal		m_fBestDepth;
	dReal		m_fBestCenter;
	dReal		m_fBestrt;
	int			m_iBestAxis;
	dVector3	m_vContactNormal;
	dVector3	m_vNormal;
	dVector3	m_vE0;
	dVector3	m_vE1;
	dVector3	m_vE2;

	// ODE stuff
	int					m_iFlags;
	int					m_iSkip;
	int					m_nContacts;// = 0;
	sLocalContactData*	m_gLocalContacts;
};


#ifdef OPTIMIZE_CONTACTS

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
	dVector3Subtract(c1.vPos,c2.vPos,vDiff);
	if (  (dFabs(vDiff[0]) < fSameContactPositionEpsilon)
		&&(dFabs(vDiff[1]) < fSameContactPositionEpsilon)
		&&(dFabs(vDiff[2]) < fSameContactPositionEpsilon))
	{
		bPosNear = 1;
	}

	// Second check if they are "near" in normal direction
	dVector3Subtract(c1.vNormal,c2.vNormal,vDiff);
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
void sCylinderTrimeshColliderData::_OptimizeLocalContacts()
{
	int nContacts = m_nContacts;

	for (int i = 0; i < nContacts-1; i++)
	{
		for (int j = i+1; j < nContacts; j++)
		{
			if (_IsNearContacts(m_gLocalContacts[i],m_gLocalContacts[j]))
			{
				// If they are seem to be the same then filtered 
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

int	sCylinderTrimeshColliderData::_ProcessLocalContacts(dContactGeom *contact, 
	dxGeom *Cylinder, dxTriMesh *Trimesh)
{
#ifdef OPTIMIZE_CONTACTS
	if (m_nContacts > 1 && !(m_iFlags & CONTACTS_UNIMPORTANT))
	{
		// Can be optimized...
		_OptimizeLocalContacts();
	}
#endif		

	int iContact = 0;
	dContactGeom* Contact = 0;

	int nFinalContact = 0;

	for (iContact = 0; iContact < m_nContacts; iContact ++)
	{
		if (1 == m_gLocalContacts[iContact].nFlags)
		{
			Contact = SAFECONTACT(m_iFlags, contact, nFinalContact, m_iSkip);
			Contact->depth = m_gLocalContacts[iContact].fDepth;
			dVector3Copy(m_gLocalContacts[iContact].vNormal,Contact->normal);
			dVector3Copy(m_gLocalContacts[iContact].vPos,Contact->pos);
			Contact->g1 = Cylinder;
			Contact->g2 = Trimesh;
			Contact->side1 = -1;
			Contact->side2 = m_gLocalContacts[iContact].triIndex;
			dVector3Inv(Contact->normal);

			nFinalContact++;
		}
	}
	// debug
	//if (nFinalContact != m_nContacts)
	//{
	//	printf("[Info] %d contacts generated,%d  filtered.\n",m_nContacts,m_nContacts-nFinalContact);
	//}

	return nFinalContact;
}


bool sCylinderTrimeshColliderData::_cldTestAxis(
				  const dVector3 &v0,
				  const dVector3 &v1,
				  const dVector3 &v2, 
                  dVector3& vAxis, 
				  int iAxis,
				  bool bNoFlip/* = false*/)
{
  
	// calculate length of separating axis vector
	dReal fL = dVector3Length(vAxis);
	// if not long enough
	if ( fL < REAL(1e-5) )
	{
		// do nothing
		return true;
	}

	// otherwise normalize it
	vAxis[0] /= fL;
	vAxis[1] /= fL;
	vAxis[2] /= fL;

	dReal fdot1 = dVector3Dot(m_vCylinderAxis,vAxis);
	// project capsule on vAxis
	dReal frc;

	if (dFabs(fdot1) > REAL(1.0) ) 
	{
//		fdot1 = REAL(1.0);
		frc = dFabs(m_fCylinderSize* REAL(0.5));
	}
	else
	{
		frc = dFabs((m_fCylinderSize* REAL(0.5)) * fdot1)
			+ m_fCylinderRadius * dSqrt(REAL(1.0)-(fdot1*fdot1));
	}
  
	dVector3 vV0;
	dVector3Subtract(v0,m_vCylinderPos,vV0);
	dVector3 vV1;
	dVector3Subtract(v1,m_vCylinderPos,vV1);
	dVector3 vV2;
	dVector3Subtract(v2,m_vCylinderPos,vV2);

	// project triangle on vAxis
	dReal afv[3];
	afv[0] = dVector3Dot( vV0 , vAxis );
	afv[1] = dVector3Dot( vV1 , vAxis );
	afv[2] = dVector3Dot( vV2 , vAxis );

	dReal fMin = MAX_REAL;
	dReal fMax = -MAX_REAL;

	// for each vertex 
	for(int i = 0; i < 3; i++) 
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

	// find capsule's center of interval on axis
	dReal fCenter = (fMin+fMax)* REAL(0.5);
	// calculate triangles halfinterval 
	dReal fTriangleRadius = (fMax-fMin)*REAL(0.5);

	// if they do not overlap, 
	if( dFabs(fCenter) > (frc+fTriangleRadius) ) 
	{ 
		// exit, we have no intersection
		return false; 
	}

	// calculate depth 
	dReal fDepth = -(dFabs(fCenter) - (frc + fTriangleRadius ) );

	// if greater then best found so far
	if ( fDepth < m_fBestDepth ) 
	{
		// remember depth
		m_fBestDepth			= fDepth;
		m_fBestCenter		    = fCenter;
		m_fBestrt				= frc;
		dVector3Copy(vAxis,m_vContactNormal);
		m_iBestAxis				= iAxis;
	  
		// flip normal if interval is wrong faced
		if ( fCenter< REAL(0.0) && !bNoFlip) 
		{ 
			dVector3Inv(m_vContactNormal);
			m_fBestCenter = -fCenter;
		}
	}
  
	return true;
}

// intersection test between edge and circle
bool sCylinderTrimeshColliderData::_cldTestCircleToEdgeAxis(
	const dVector3 &v0, const dVector3 &v1, const dVector3 &v2,
	const dVector3 &vCenterPoint, const dVector3 &vCylinderAxis1,
	const dVector3 &vVx0, const dVector3 &vVx1, int iAxis) 
{
	// calculate direction of edge
	dVector3 vkl;
	dVector3Subtract( vVx1 , vVx0 , vkl);
	dNormalize3(vkl);
	// starting point of edge 
	dVector3 vol;
	dVector3Copy(vVx0,vol);

	// calculate angle cosine between cylinder axis and edge
	dReal fdot2 = dVector3Dot(vkl , vCylinderAxis1);

	// if edge is perpendicular to cylinder axis
	if(dFabs(fdot2)<REAL(1e-5))
	{
		// this can't be separating axis, because edge is parallel to circle plane
		return true;
	}
    
	// find point of intersection between edge line and circle plane
	dVector3 vTemp;
	dVector3Subtract(vCenterPoint,vol,vTemp);
	dReal fdot1 = dVector3Dot(vTemp,vCylinderAxis1);
	dVector3 vpnt;// = vol + vkl * (fdot1/fdot2);
	vpnt[0] = vol[0] + vkl[0] * fdot1/fdot2;
	vpnt[1] = vol[1] + vkl[1] * fdot1/fdot2;
	vpnt[2] = vol[2] + vkl[2] * fdot1/fdot2;

	// find tangent vector on circle with same center (vCenterPoint) that touches point of intersection (vpnt)
	dVector3 vTangent;
	dVector3Subtract(vCenterPoint,vpnt,vTemp);
	dVector3Cross(vTemp,vCylinderAxis1,vTangent);
  
	// find vector orthogonal both to tangent and edge direction
	dVector3 vAxis;
	dVector3Cross(vTangent,vkl,vAxis);

	// use that vector as separating axis
	return _cldTestAxis( v0, v1, v2, vAxis, iAxis );
}

// helper for less key strokes
// r = ( (v1 - v2) cross v3 ) cross v3
inline void _CalculateAxis(const dVector3& v1,
						   const dVector3& v2,
						   const dVector3& v3,
						   dVector3& r)
{
	dVector3 t1;
	dVector3 t2;

	dVector3Subtract(v1,v2,t1);
	dVector3Cross(t1,v3,t2);
	dVector3Cross(t2,v3,r);
}

bool sCylinderTrimeshColliderData::_cldTestSeparatingAxes(
							const dVector3 &v0,
							const dVector3 &v1,
							const dVector3 &v2) 
{

	// calculate edge vectors
	dVector3Subtract(v1 ,v0 , m_vE0);
	// m_vE1 has been calculated before -> so save some cycles here
	dVector3Subtract(v0 ,v2 , m_vE2);

	// calculate caps centers in absolute space
	dVector3 vCp0;
	vCp0[0] = m_vCylinderPos[0] + m_vCylinderAxis[0]*(m_fCylinderSize* REAL(0.5));
	vCp0[1] = m_vCylinderPos[1] + m_vCylinderAxis[1]*(m_fCylinderSize* REAL(0.5));
	vCp0[2] = m_vCylinderPos[2] + m_vCylinderAxis[2]*(m_fCylinderSize* REAL(0.5));

	dVector3 vCp1;
	vCp1[0] = m_vCylinderPos[0] - m_vCylinderAxis[0]*(m_fCylinderSize* REAL(0.5));
	vCp1[1] = m_vCylinderPos[1] - m_vCylinderAxis[1]*(m_fCylinderSize* REAL(0.5));
	vCp1[2] = m_vCylinderPos[2] - m_vCylinderAxis[2]*(m_fCylinderSize* REAL(0.5));

	// reset best axis
	m_iBestAxis = 0;
	dVector3 vAxis;

	// axis m_vNormal
	//vAxis = -m_vNormal;
	vAxis[0] = -m_vNormal[0];
	vAxis[1] = -m_vNormal[1];
	vAxis[2] = -m_vNormal[2];
	if (!_cldTestAxis(v0, v1, v2, vAxis, 1, true)) 
	{ 
		return false; 
	}

	// axis CxE0
	// vAxis = ( m_vCylinderAxis cross m_vE0 );
	dVector3Cross(m_vCylinderAxis, m_vE0,vAxis);
	if (!_cldTestAxis(v0, v1, v2, vAxis, 2)) 
	{ 
		return false; 
	}

	// axis CxE1
	// vAxis = ( m_vCylinderAxis cross m_vE1 );
	dVector3Cross(m_vCylinderAxis, m_vE1,vAxis);
	if (!_cldTestAxis(v0, v1, v2, vAxis, 3)) 
	{ 
		return false; 
	}

	// axis CxE2
	// vAxis = ( m_vCylinderAxis cross m_vE2 );
	dVector3Cross(m_vCylinderAxis, m_vE2,vAxis);
	if (!_cldTestAxis(v0, v1, v2, vAxis, 4)) 
	{ 
		return false; 
	}

	// first vertex on triangle
	// axis ((V0-Cp0) x C) x C
	//vAxis = ( ( v0-vCp0 ) cross m_vCylinderAxis ) cross m_vCylinderAxis;
	_CalculateAxis(v0 , vCp0 , m_vCylinderAxis , vAxis);
	if (!_cldTestAxis(v0, v1, v2, vAxis, 11)) 
	{ 
		return false; 
	}

	// second vertex on triangle
	// axis ((V1-Cp0) x C) x C
	// vAxis = ( ( v1-vCp0 ) cross m_vCylinderAxis ) cross m_vCylinderAxis;
	_CalculateAxis(v1 , vCp0 , m_vCylinderAxis , vAxis);
	if (!_cldTestAxis(v0, v1, v2, vAxis, 12)) 
	{ 
		return false; 
	}

	// third vertex on triangle
	// axis ((V2-Cp0) x C) x C
	//vAxis = ( ( v2-vCp0 ) cross m_vCylinderAxis ) cross m_vCylinderAxis;
	_CalculateAxis(v2 , vCp0 , m_vCylinderAxis , vAxis);
	if (!_cldTestAxis(v0, v1, v2, vAxis, 13))
	{ 
		return false; 
	}

	// test cylinder axis
	// vAxis = m_vCylinderAxis;
	dVector3Copy(m_vCylinderAxis , vAxis);
	if (!_cldTestAxis(v0, v1, v2, vAxis, 14)) 
	{ 
		return false; 
	}

	// Test top and bottom circle ring of cylinder for separation
	dVector3 vccATop;
	vccATop[0] = m_vCylinderPos[0] + m_vCylinderAxis[0]*(m_fCylinderSize * REAL(0.5));
	vccATop[1] = m_vCylinderPos[1] + m_vCylinderAxis[1]*(m_fCylinderSize * REAL(0.5));
	vccATop[2] = m_vCylinderPos[2] + m_vCylinderAxis[2]*(m_fCylinderSize * REAL(0.5));

	dVector3 vccABottom;
	vccABottom[0] = m_vCylinderPos[0] - m_vCylinderAxis[0]*(m_fCylinderSize * REAL(0.5));
	vccABottom[1] = m_vCylinderPos[1] - m_vCylinderAxis[1]*(m_fCylinderSize * REAL(0.5));
	vccABottom[2] = m_vCylinderPos[2] - m_vCylinderAxis[2]*(m_fCylinderSize * REAL(0.5));


  if (!_cldTestCircleToEdgeAxis(v0, v1, v2, vccATop, m_vCylinderAxis, v0, v1, 15)) 
  {
    return false;
  }

  if (!_cldTestCircleToEdgeAxis(v0, v1, v2, vccATop, m_vCylinderAxis, v1, v2, 16)) 
  {
    return false;
  }

  if (!_cldTestCircleToEdgeAxis(v0, v1, v2, vccATop, m_vCylinderAxis, v0, v2, 17)) 
  {
    return false;
  }

  if (!_cldTestCircleToEdgeAxis(v0, v1, v2, vccABottom, m_vCylinderAxis, v0, v1, 18)) 
  {
    return false;
  }

  if (!_cldTestCircleToEdgeAxis(v0, v1, v2, vccABottom, m_vCylinderAxis, v1, v2, 19)) 
  {
    return false;
  }

  if (!_cldTestCircleToEdgeAxis(v0, v1, v2, vccABottom, m_vCylinderAxis, v0, v2, 20)) 
  {
    return false;
  }

  return true;
}

bool sCylinderTrimeshColliderData::_cldClipCylinderEdgeToTriangle(
	const dVector3 &v0, const dVector3 &v1, const dVector3 &v2)
{
	// translate cylinder
	dReal fTemp = dVector3Dot(m_vCylinderAxis , m_vContactNormal);
	dVector3 vN2;
	vN2[0] = m_vContactNormal[0] - m_vCylinderAxis[0]*fTemp;
	vN2[1] = m_vContactNormal[1] - m_vCylinderAxis[1]*fTemp;
	vN2[2] = m_vContactNormal[2] - m_vCylinderAxis[2]*fTemp;

	fTemp = dVector3Length(vN2);
	if (fTemp < REAL(1e-5))
	{
		return false;
	}

	// Normalize it
	vN2[0] /= fTemp;
	vN2[1] /= fTemp;
	vN2[2] /= fTemp;

	// calculate caps centers in absolute space
	dVector3 vCposTrans;
	vCposTrans[0] = m_vCylinderPos[0] + vN2[0]*m_fCylinderRadius;
	vCposTrans[1] = m_vCylinderPos[1] + vN2[1]*m_fCylinderRadius;
	vCposTrans[2] = m_vCylinderPos[2] + vN2[2]*m_fCylinderRadius;
	  
	dVector3 vCEdgePoint0;
	vCEdgePoint0[0]  = vCposTrans[0] + m_vCylinderAxis[0] * (m_fCylinderSize* REAL(0.5));
	vCEdgePoint0[1]  = vCposTrans[1] + m_vCylinderAxis[1] * (m_fCylinderSize* REAL(0.5));
	vCEdgePoint0[2]  = vCposTrans[2] + m_vCylinderAxis[2] * (m_fCylinderSize* REAL(0.5));

	dVector3 vCEdgePoint1;
	vCEdgePoint1[0]  = vCposTrans[0] - m_vCylinderAxis[0] * (m_fCylinderSize* REAL(0.5));
	vCEdgePoint1[1]  = vCposTrans[1] - m_vCylinderAxis[1] * (m_fCylinderSize* REAL(0.5));
	vCEdgePoint1[2]  = vCposTrans[2] - m_vCylinderAxis[2] * (m_fCylinderSize* REAL(0.5));

	// transform cylinder edge points into triangle space
	vCEdgePoint0[0] -= v0[0];
	vCEdgePoint0[1] -= v0[1];
	vCEdgePoint0[2] -= v0[2];

	vCEdgePoint1[0] -= v0[0];
	vCEdgePoint1[1] -= v0[1];
	vCEdgePoint1[2] -= v0[2];

	dVector4 plPlane;
	dVector3 vPlaneNormal;

	// triangle plane
	//plPlane = Plane4f( -m_vNormal, 0);
	vPlaneNormal[0] = -m_vNormal[0];
	vPlaneNormal[1] = -m_vNormal[1];
	vPlaneNormal[2] = -m_vNormal[2];
	dConstructPlane(vPlaneNormal,REAL(0.0),plPlane);
	if(!dClipEdgeToPlane( vCEdgePoint0, vCEdgePoint1, plPlane )) 
	{ 
		return false; 
	}

	// plane with edge 0
	//plPlane = Plane4f( ( m_vNormal cross m_vE0 ), REAL(1e-5));
	dVector3Cross(m_vNormal,m_vE0,vPlaneNormal);
	dConstructPlane(vPlaneNormal,REAL(1e-5),plPlane);
	if(!dClipEdgeToPlane( vCEdgePoint0, vCEdgePoint1, plPlane )) 
	{ 
		return false; 
	}
  
	// plane with edge 1
	//dVector3 vTemp = ( m_vNormal cross m_vE1 );
	dVector3Cross(m_vNormal,m_vE1,vPlaneNormal);
	fTemp = dVector3Dot(m_vE0 , vPlaneNormal) - REAL(1e-5);
	//plPlane = Plane4f( vTemp, -(( m_vE0 dot vTemp )-REAL(1e-5)));
	dConstructPlane(vPlaneNormal,-fTemp,plPlane);
	if(!dClipEdgeToPlane( vCEdgePoint0, vCEdgePoint1, plPlane )) 
	{
		return false;
	}

	// plane with edge 2
	// plPlane = Plane4f( ( m_vNormal cross m_vE2 ), REAL(1e-5));
	dVector3Cross(m_vNormal,m_vE2,vPlaneNormal);
	dConstructPlane(vPlaneNormal,REAL(1e-5),plPlane);
	if(!dClipEdgeToPlane( vCEdgePoint0, vCEdgePoint1, plPlane )) 
	{ 
		return false; 
	}

	// return capsule edge points into absolute space
	vCEdgePoint0[0] += v0[0];
	vCEdgePoint0[1] += v0[1];
	vCEdgePoint0[2] += v0[2];

	vCEdgePoint1[0] += v0[0];
	vCEdgePoint1[1] += v0[1];
	vCEdgePoint1[2] += v0[2];

	// calculate depths for both contact points
	dVector3 vTemp;
	dVector3Subtract(vCEdgePoint0,m_vCylinderPos, vTemp);
	dReal fRestDepth0 = -dVector3Dot(vTemp,m_vContactNormal) + m_fBestrt;
	dVector3Subtract(vCEdgePoint1,m_vCylinderPos, vTemp);
	dReal fRestDepth1 = -dVector3Dot(vTemp,m_vContactNormal) + m_fBestrt;
	
	dReal fDepth0 = m_fBestDepth - (fRestDepth0);
	dReal fDepth1 = m_fBestDepth - (fRestDepth1);
		  
	// clamp depths to zero
	if(fDepth0 < REAL(0.0) ) 
	{
		fDepth0 = REAL(0.0);
	}

	if(fDepth1<REAL(0.0)) 
	{
		fDepth1 = REAL(0.0);
	}

	// Generate contact 0
	{
		m_gLocalContacts[m_nContacts].fDepth = fDepth0;
		dVector3Copy(m_vContactNormal,m_gLocalContacts[m_nContacts].vNormal);
		dVector3Copy(vCEdgePoint0,m_gLocalContacts[m_nContacts].vPos);
		m_gLocalContacts[m_nContacts].nFlags = 1;
		m_nContacts++;
		if(m_nContacts >= (m_iFlags & NUMC_MASK)) 
			return true;
	}

	// Generate contact 1
	{
		// generate contacts
		m_gLocalContacts[m_nContacts].fDepth = fDepth1;
		dVector3Copy(m_vContactNormal,m_gLocalContacts[m_nContacts].vNormal);
		dVector3Copy(vCEdgePoint1,m_gLocalContacts[m_nContacts].vPos);
		m_gLocalContacts[m_nContacts].nFlags = 1;
		m_nContacts++;		
	}

	return true;
}

void sCylinderTrimeshColliderData::_cldClipCylinderToTriangle(
	const dVector3 &v0, const dVector3 &v1, const dVector3 &v2)
{
	int i = 0;
	dVector3 avPoints[3];
	dVector3 avTempArray1[nMAX_CYLINDER_TRIANGLE_CLIP_POINTS];
	dVector3 avTempArray2[nMAX_CYLINDER_TRIANGLE_CLIP_POINTS];

	dSetZero(&avTempArray1[0][0],nMAX_CYLINDER_TRIANGLE_CLIP_POINTS * 4);
	dSetZero(&avTempArray2[0][0],nMAX_CYLINDER_TRIANGLE_CLIP_POINTS * 4);

	// setup array of triangle vertices
	dVector3Copy(v0,avPoints[0]);
	dVector3Copy(v1,avPoints[1]);
	dVector3Copy(v2,avPoints[2]);

	dVector3 vCylinderCirclePos, vCylinderCircleNormal_Rel;
	dSetZero(vCylinderCircleNormal_Rel,4);
	// check which circle from cylinder we take for clipping
	if ( dVector3Dot(m_vCylinderAxis , m_vContactNormal) > REAL(0.0)) 
	{
		// get top circle
		vCylinderCirclePos[0] = m_vCylinderPos[0] + m_vCylinderAxis[0]*(m_fCylinderSize*REAL(0.5));
		vCylinderCirclePos[1] = m_vCylinderPos[1] + m_vCylinderAxis[1]*(m_fCylinderSize*REAL(0.5));
		vCylinderCirclePos[2] = m_vCylinderPos[2] + m_vCylinderAxis[2]*(m_fCylinderSize*REAL(0.5));

		vCylinderCircleNormal_Rel[nCYLINDER_AXIS] = REAL(-1.0);
	} 
	else 
	{
		// get bottom circle
		vCylinderCirclePos[0] = m_vCylinderPos[0] - m_vCylinderAxis[0]*(m_fCylinderSize*REAL(0.5));
		vCylinderCirclePos[1] = m_vCylinderPos[1] - m_vCylinderAxis[1]*(m_fCylinderSize*REAL(0.5));
		vCylinderCirclePos[2] = m_vCylinderPos[2] - m_vCylinderAxis[2]*(m_fCylinderSize*REAL(0.5));

		vCylinderCircleNormal_Rel[nCYLINDER_AXIS] = REAL(1.0);
	}

	dVector3 vTemp;
	dQuatInv(m_qCylinderRot , m_qInvCylinderRot);
	// transform triangle points to space of cylinder circle
	for(i=0; i<3; i++) 
	{
		dVector3Subtract(avPoints[i] , vCylinderCirclePos , vTemp);
		dQuatTransform(m_qInvCylinderRot,vTemp,avPoints[i]);
	}

	int iTmpCounter1 = 0;
	int iTmpCounter2 = 0;
	dVector4 plPlane;

	// plane of cylinder that contains circle for intersection
	//plPlane = Plane4f( vCylinderCircleNormal_Rel, 0.0f );
	dConstructPlane(vCylinderCircleNormal_Rel,REAL(0.0),plPlane);
	dClipPolyToPlane(avPoints, 3, avTempArray1, iTmpCounter1, plPlane);

	// Body of base circle of Cylinder
	int nCircleSegment = 0;
	for (nCircleSegment = 0; nCircleSegment < nCYLINDER_CIRCLE_SEGMENTS; nCircleSegment++)
	{
		dConstructPlane(m_avCylinderNormals[nCircleSegment],m_fCylinderRadius,plPlane);

		if (0 == (nCircleSegment % 2))
		{
			dClipPolyToPlane( avTempArray1 , iTmpCounter1 , avTempArray2, iTmpCounter2, plPlane);
		}
		else
		{
			dClipPolyToPlane( avTempArray2, iTmpCounter2, avTempArray1 , iTmpCounter1 , plPlane );
		}

		dIASSERT( iTmpCounter1 >= 0 && iTmpCounter1 <= nMAX_CYLINDER_TRIANGLE_CLIP_POINTS );
		dIASSERT( iTmpCounter2 >= 0 && iTmpCounter2 <= nMAX_CYLINDER_TRIANGLE_CLIP_POINTS );
	}

	// back transform clipped points to absolute space
	dReal ftmpdot;	
	dReal fTempDepth;
	dVector3 vPoint;

	if (nCircleSegment %2)
	{
		for( i=0; i<iTmpCounter2; i++)
		{
			dQuatTransform(m_qCylinderRot,avTempArray2[i], vPoint);
			vPoint[0] += vCylinderCirclePos[0];
			vPoint[1] += vCylinderCirclePos[1];
			vPoint[2] += vCylinderCirclePos[2];

			dVector3Subtract(vPoint,m_vCylinderPos,vTemp);
			ftmpdot	 = dFabs(dVector3Dot(vTemp, m_vContactNormal));
			fTempDepth = m_fBestrt - ftmpdot;
			// Depth must be positive
			if (fTempDepth > REAL(0.0))
			{
				m_gLocalContacts[m_nContacts].fDepth = fTempDepth;
				dVector3Copy(m_vContactNormal,m_gLocalContacts[m_nContacts].vNormal);
				dVector3Copy(vPoint,m_gLocalContacts[m_nContacts].vPos);
				m_gLocalContacts[m_nContacts].nFlags = 1;
				m_nContacts++;
				if(m_nContacts >= (m_iFlags & NUMC_MASK)) 
					return;;
			}
		}
	}
	else
	{
		for( i=0; i<iTmpCounter1; i++)
		{
			dQuatTransform(m_qCylinderRot,avTempArray1[i], vPoint);
			vPoint[0] += vCylinderCirclePos[0];
			vPoint[1] += vCylinderCirclePos[1];
			vPoint[2] += vCylinderCirclePos[2];

			dVector3Subtract(vPoint,m_vCylinderPos,vTemp);
			ftmpdot	 = dFabs(dVector3Dot(vTemp, m_vContactNormal));
			fTempDepth = m_fBestrt - ftmpdot;
			// Depth must be positive
			if (fTempDepth > REAL(0.0))
			{
				m_gLocalContacts[m_nContacts].fDepth = fTempDepth;
				dVector3Copy(m_vContactNormal,m_gLocalContacts[m_nContacts].vNormal);
				dVector3Copy(vPoint,m_gLocalContacts[m_nContacts].vPos);
				m_gLocalContacts[m_nContacts].nFlags = 1;
				m_nContacts++;
				if(m_nContacts >= (m_iFlags & NUMC_MASK)) 
					return;;
			}
		}
	}
}

void sCylinderTrimeshColliderData::TestOneTriangleVsCylinder(
								  const dVector3 &v0, 
                                  const dVector3 &v1, 
                                  const dVector3 &v2, 
                                  const bool bDoubleSided)
{
	// calculate triangle normal
	dVector3Subtract( v2 , v1 , m_vE1);
	dVector3 vTemp;
	dVector3Subtract( v0 , v1 ,vTemp);
	dVector3Cross(m_vE1 , vTemp , m_vNormal );

	// Even though all triangles might be initially valid, 
	// a triangle may degenerate into a segment after applying 
	// space transformation.
	if (!dSafeNormalize3( m_vNormal))
	{
		return;
	}

	// create plane from triangle
	//Plane4f plTrianglePlane = Plane4f( vPolyNormal, v0 ); 
	dReal plDistance = -dVector3Dot(v0, m_vNormal);
	dVector4 plTrianglePlane;
	dConstructPlane( m_vNormal,plDistance,plTrianglePlane);

	 // calculate sphere distance to plane
	dReal fDistanceCylinderCenterToPlane = dPointPlaneDistance(m_vCylinderPos , plTrianglePlane);

	// Sphere must be over positive side of triangle
	if(fDistanceCylinderCenterToPlane < 0 && !bDoubleSided) 
	{
		// if not don't generate contacts
		return;
	 }

	dVector3 vPnt0;
	dVector3 vPnt1;
	dVector3 vPnt2;

	if (fDistanceCylinderCenterToPlane < REAL(0.0) )
	{
		// flip it
		dVector3Copy(v0 , vPnt0);
		dVector3Copy(v1 , vPnt2);
		dVector3Copy(v2 , vPnt1);
	}
	else
	{
		dVector3Copy(v0 , vPnt0);
		dVector3Copy(v1 , vPnt1);
		dVector3Copy(v2 , vPnt2);
	}

	m_fBestDepth = MAX_REAL;

	// do intersection test and find best separating axis
	if(!_cldTestSeparatingAxes(vPnt0, vPnt1, vPnt2) ) 
	{
		// if not found do nothing
		return;
	}

	// if best separation axis is not found
	if ( m_iBestAxis == 0 ) 
	{
		// this should not happen (we should already exit in that case)
		dIASSERT(false);
		// do nothing
		return;
	}

	dReal fdot = dVector3Dot( m_vContactNormal , m_vCylinderAxis );

	// choose which clipping method are we going to apply
	if (dFabs(fdot) < REAL(0.9) ) 
	{
		if (!_cldClipCylinderEdgeToTriangle(vPnt0, vPnt1, vPnt2)) 
		{
			return;
		}
	}
	else 
	{
		_cldClipCylinderToTriangle(vPnt0, vPnt1, vPnt2);
	}
}

void sCylinderTrimeshColliderData::_InitCylinderTrimeshData(dxGeom *Cylinder, dxTriMesh *Trimesh)
{
	// get cylinder information
	// Rotation
	const dReal* pRotCyc = dGeomGetRotation(Cylinder); 
	dMatrix3Copy(pRotCyc,m_mCylinderRot);
	dGeomGetQuaternion(Cylinder,m_qCylinderRot);
	
	// Position
	const dVector3* pPosCyc = (const dVector3*)dGeomGetPosition(Cylinder);
	dVector3Copy(*pPosCyc,m_vCylinderPos);
	// Cylinder axis
	dMat3GetCol(m_mCylinderRot,nCYLINDER_AXIS,m_vCylinderAxis);
	// get cylinder radius and size
	dGeomCylinderGetParams(Cylinder,&m_fCylinderRadius,&m_fCylinderSize);
	
	// get trimesh position and orientation
	const dReal* pRotTris = dGeomGetRotation(Trimesh); 
	dMatrix3Copy(pRotTris,m_mTrimeshRot);
	dGeomGetQuaternion(Trimesh,m_qTrimeshRot);
	
	// Position
	const dVector3* pPosTris = (const dVector3*)dGeomGetPosition(Trimesh);
	dVector3Copy(*pPosTris,m_vTrimeshPos);


	// calculate basic angle for 8-gon
	dReal fAngle = (dReal) (M_PI / nCYLINDER_CIRCLE_SEGMENTS);
	// calculate angle increment
	dReal fAngleIncrement = fAngle*REAL(2.0); 

	// calculate plane normals
	// axis dependant code
	for(int i=0; i<nCYLINDER_CIRCLE_SEGMENTS; i++) 
	{
		m_avCylinderNormals[i][0] = -dCos(fAngle);
		m_avCylinderNormals[i][1] = -dSin(fAngle);
		m_avCylinderNormals[i][2] = REAL(0.0);

		fAngle += fAngleIncrement;
	}

	dSetZero(m_vBestPoint,4);
	// reset best depth
	m_fBestCenter = REAL(0.0);	
}

int sCylinderTrimeshColliderData::TestCollisionForSingleTriangle(int ctContacts0, 
	int Triint, dVector3 dv[3], bool &bOutFinishSearching)
{
	// test this triangle
	TestOneTriangleVsCylinder(dv[0],dv[1],dv[2], false);

	// fill-in tri index for generated contacts
	for (; ctContacts0<m_nContacts; ctContacts0++)
		m_gLocalContacts[ctContacts0].triIndex = Triint;

	// Putting "break" at the end of loop prevents unnecessary checks on first pass and "continue"
	bOutFinishSearching = (m_nContacts >= (m_iFlags & NUMC_MASK));

	return ctContacts0;
}

// OPCODE version of cylinder to mesh collider
#if dTRIMESH_OPCODE
static void dQueryCTLPotentialCollisionTriangles(OBBCollider &Collider, 
	sCylinderTrimeshColliderData &cData, dxGeom *Cylinder, dxTriMesh *Trimesh,
	OBBCache &BoxCache)
{
	const dVector3 &vCylinderPos = cData.m_vCylinderPos;

	Point cCenter(vCylinderPos[0],vCylinderPos[1],vCylinderPos[2]);

	Point cExtents(cData.m_fCylinderRadius,cData.m_fCylinderRadius,cData.m_fCylinderRadius);
	cExtents[nCYLINDER_AXIS] = cData.m_fCylinderSize * REAL(0.5);

	Matrix3x3 obbRot;

	const dMatrix3 &mCylinderRot = cData.m_mCylinderRot;

	// It is a potential issue to explicitly cast to float 
	// if custom width floating point type is introduced in OPCODE.
	// It is necessary to make a typedef and cast to it
	// (e.g. typedef float opc_float;)
	// However I'm not sure in what header it should be added.

	obbRot[0][0] = /*(float)*/mCylinderRot[0];
	obbRot[1][0] = /*(float)*/mCylinderRot[1];
	obbRot[2][0] = /*(float)*/mCylinderRot[2];

	obbRot[0][1] = /*(float)*/mCylinderRot[4];
	obbRot[1][1] = /*(float)*/mCylinderRot[5];
	obbRot[2][1] = /*(float)*/mCylinderRot[6];

	obbRot[0][2] = /*(float)*/mCylinderRot[8];
	obbRot[1][2] = /*(float)*/mCylinderRot[9];
	obbRot[2][2] = /*(float)*/mCylinderRot[10];

	OBB obbCapsule(cCenter,cExtents,obbRot);

	Matrix4x4 CapsuleMatrix;
	MakeMatrix(vCylinderPos, mCylinderRot, CapsuleMatrix);

	Matrix4x4 MeshMatrix;
	MakeMatrix(cData.m_vTrimeshPos, cData.m_mTrimeshRot, MeshMatrix);

	// TC results
	if (Trimesh->doBoxTC) 
	{
		dxTriMesh::BoxTC* BoxTC = 0;
		for (int i = 0; i < Trimesh->BoxTCCache.size(); i++)
		{
			if (Trimesh->BoxTCCache[i].Geom == Cylinder)
			{
				BoxTC = &Trimesh->BoxTCCache[i];
				break;
			}
		}
		if (!BoxTC)
		{
			Trimesh->BoxTCCache.push(dxTriMesh::BoxTC());

			BoxTC = &Trimesh->BoxTCCache[Trimesh->BoxTCCache.size() - 1];
			BoxTC->Geom = Cylinder;
			BoxTC->FatCoeff = REAL(1.0);
		}

		// Intersect
		Collider.SetTemporalCoherence(true);
		Collider.Collide(*BoxTC, obbCapsule, Trimesh->Data->BVTree, null, &MeshMatrix);
	}
	else 
	{
		Collider.SetTemporalCoherence(false);
		Collider.Collide(BoxCache, obbCapsule, Trimesh->Data->BVTree, null,&MeshMatrix);
	}
}

int dCollideCylinderTrimesh(dxGeom *o1, dxGeom *o2, int flags, dContactGeom *contact, int skip)
{
	dIASSERT( skip >= (int)sizeof( dContactGeom ) );
	dIASSERT( o1->type == dCylinderClass );
	dIASSERT( o2->type == dTriMeshClass );
	dIASSERT ((flags & NUMC_MASK) >= 1);

	int nContactCount = 0;

	dxGeom *Cylinder = o1;
	dxTriMesh *Trimesh = (dxTriMesh *)o2;

	// Main data holder
	sCylinderTrimeshColliderData cData(flags, skip);
	cData._InitCylinderTrimeshData(Cylinder, Trimesh);

	const unsigned uiTLSKind = Trimesh->getParentSpaceTLSKind();
	dIASSERT(uiTLSKind == Cylinder->getParentSpaceTLSKind()); // The colliding spaces must use matching cleanup method
	TrimeshCollidersCache *pccColliderCache = GetTrimeshCollidersCache(uiTLSKind);
	OBBCollider& Collider = pccColliderCache->_OBBCollider;

	dQueryCTLPotentialCollisionTriangles(Collider, cData, Cylinder, Trimesh, pccColliderCache->defaultBoxCache);

	// Retrieve data
	int TriCount = Collider.GetNbTouchedPrimitives();

	if (TriCount != 0)
	{
		const int* Triangles = (const int*)Collider.GetTouchedPrimitives();

		if (Trimesh->ArrayCallback != null)
		{
			Trimesh->ArrayCallback(Trimesh, Cylinder, Triangles, TriCount);
		}

		// allocate buffer for local contacts on stack
		cData.m_gLocalContacts = (sLocalContactData*)dALLOCA16(sizeof(sLocalContactData)*(cData.m_iFlags & NUMC_MASK));

	    int ctContacts0 = 0;

		// loop through all intersecting triangles
		for (int i = 0; i < TriCount; i++)
		{
			const int Triint = Triangles[i];
			if (!Callback(Trimesh, Cylinder, Triint)) continue;


			dVector3 dv[3];
			FetchTriangle(Trimesh, Triint, cData.m_vTrimeshPos, cData.m_mTrimeshRot, dv);

			bool bFinishSearching;
			ctContacts0 = cData.TestCollisionForSingleTriangle(ctContacts0, Triint, dv, bFinishSearching);

			if (bFinishSearching) 
			{
				break;
			}
		}

		if (cData.m_nContacts != 0)
		{
			nContactCount = cData._ProcessLocalContacts(contact, Cylinder, Trimesh);
		}
	}

	return nContactCount;
}
#endif

// GIMPACT version of cylinder to mesh collider
#if dTRIMESH_GIMPACT
int dCollideCylinderTrimesh(dxGeom *o1, dxGeom *o2, int flags, dContactGeom *contact, int skip)
{
	dIASSERT( skip >= (int)sizeof( dContactGeom ) );
	dIASSERT( o1->type == dCylinderClass );
	dIASSERT( o2->type == dTriMeshClass );
	dIASSERT ((flags & NUMC_MASK) >= 1);
	
	int nContactCount = 0;

	dxGeom *Cylinder = o1;
	dxTriMesh *Trimesh = (dxTriMesh *)o2;

	// Main data holder
	sCylinderTrimeshColliderData cData(flags, skip);
	cData._InitCylinderTrimeshData(Cylinder, Trimesh);

//*****at first , collide box aabb******//

	aabb3f test_aabb;

	test_aabb.minX = o1->aabb[0];
	test_aabb.maxX = o1->aabb[1];
	test_aabb.minY = o1->aabb[2];
	test_aabb.maxY = o1->aabb[3];
	test_aabb.minZ = o1->aabb[4];
	test_aabb.maxZ = o1->aabb[5];


	GDYNAMIC_ARRAY collision_result;
	GIM_CREATE_BOXQUERY_LIST(collision_result);

	gim_aabbset_box_collision(&test_aabb, &Trimesh->m_collision_trimesh.m_aabbset , &collision_result);

	if (collision_result.m_size != 0)
	{
//*****Set globals for box collision******//

		int ctContacts0 = 0;
		cData.m_gLocalContacts = (sLocalContactData*)dALLOCA16(sizeof(sLocalContactData)*(cData.m_iFlags & NUMC_MASK));

		GUINT32 * boxesresult = GIM_DYNARRAY_POINTER(GUINT32,collision_result);
		GIM_TRIMESH * ptrimesh = &Trimesh->m_collision_trimesh;

		gim_trimesh_locks_work_data(ptrimesh);

		for(unsigned int i=0;i<collision_result.m_size;i++)
		{
			const int Triint = boxesresult[i];
			
			dVector3 dv[3];
			gim_trimesh_get_triangle_vertices(ptrimesh, Triint, dv[0], dv[1], dv[2]);
			
			bool bFinishSearching;
			ctContacts0 = cData.TestCollisionForSingleTriangle(ctContacts0, Triint, dv, bFinishSearching);

			if (bFinishSearching) 
			{
				break;
			}
		}

		gim_trimesh_unlocks_work_data(ptrimesh);

		if (cData.m_nContacts != 0)
		{
			nContactCount = cData._ProcessLocalContacts(contact, Cylinder, Trimesh);
		}
	}

	GIM_DYNARRAY_DESTROY(collision_result);

	return nContactCount;
}
#endif

#endif // dTRIMESH_ENABLED


