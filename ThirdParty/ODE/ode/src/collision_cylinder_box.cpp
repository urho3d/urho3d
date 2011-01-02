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
 *	Cylinder-box collider by Alen Ladavac
 *  Ported to ODE by Nguyen Binh
 */

#include <ode/collision.h>
#include <ode/matrix.h>
#include <ode/rotation.h>
#include <ode/odemath.h>
#include "config.h"
#include "collision_util.h"

static const int MAX_CYLBOX_CLIP_POINTS  = 16;
static const int nCYLINDER_AXIS			 = 2;
// Number of segment of cylinder base circle.
// Must be divisible by 4.
static const int nCYLINDER_SEGMENT		 = 8;

#define MAX_FLOAT	dInfinity

// Data that passed through the collider's functions
struct sCylinderBoxData
{
	sCylinderBoxData(dxGeom *Cylinder, dxGeom *Box, int flags, dContactGeom *contact, int skip):
		m_gBox(Box), m_gCylinder(Cylinder), m_gContact(contact), m_iFlags(flags), m_iSkip(skip), m_nContacts(0)
	{
	}

	void _cldInitCylinderBox();
	int _cldTestAxis( dVector3& vInputNormal, int iAxis );
	int _cldTestEdgeCircleAxis( const dVector3 &vCenterPoint, 
		const dVector3 &vVx0, const dVector3 &vVx1, int iAxis );
	int _cldTestSeparatingAxes();
	int _cldClipCylinderToBox();
	void _cldClipBoxToCylinder();
	int PerformCollisionChecking();

	// cylinder parameters
	dMatrix3			m_mCylinderRot;
	dVector3			m_vCylinderPos;
	dVector3			m_vCylinderAxis;
	dReal				m_fCylinderRadius;
	dReal				m_fCylinderSize;
	dVector3			m_avCylinderNormals[nCYLINDER_SEGMENT];
	
	// box parameters

	dMatrix3			m_mBoxRot;
	dVector3			m_vBoxPos;
	dVector3			m_vBoxHalfSize;
	// box vertices array : 8 vertices
	dVector3			m_avBoxVertices[8];

	// global collider data
	dVector3			m_vDiff;			
	dVector3			m_vNormal;
	dReal				m_fBestDepth;
	dReal				m_fBestrb;
	dReal				m_fBestrc;
	int					m_iBestAxis;

	// contact data
	dVector3			m_vEp0, m_vEp1;
	dReal				m_fDepth0, m_fDepth1;

	// ODE stuff
	dGeomID				m_gBox;
	dGeomID				m_gCylinder;
	dContactGeom*		m_gContact;
	int					m_iFlags;
	int					m_iSkip;
	int					m_nContacts;
	
};


// initialize collision data
void sCylinderBoxData::_cldInitCylinderBox() 
{
	// get cylinder position, orientation
	const dReal* pRotCyc = dGeomGetRotation(m_gCylinder); 
	dMatrix3Copy(pRotCyc,m_mCylinderRot);

	const dVector3* pPosCyc = (const dVector3*)dGeomGetPosition(m_gCylinder);
	dVector3Copy(*pPosCyc,m_vCylinderPos);

	dMat3GetCol(m_mCylinderRot,nCYLINDER_AXIS,m_vCylinderAxis);
	
	// get cylinder radius and size
	dGeomCylinderGetParams(m_gCylinder,&m_fCylinderRadius,&m_fCylinderSize);

	// get box position, orientation, size
	const dReal* pRotBox = dGeomGetRotation(m_gBox);
	dMatrix3Copy(pRotBox,m_mBoxRot);
	const dVector3* pPosBox  = (const dVector3*)dGeomGetPosition(m_gBox);
	dVector3Copy(*pPosBox,m_vBoxPos);

	dGeomBoxGetLengths(m_gBox, m_vBoxHalfSize);
	m_vBoxHalfSize[0] *= REAL(0.5);
	m_vBoxHalfSize[1] *= REAL(0.5);
	m_vBoxHalfSize[2] *= REAL(0.5);

	// vertex 0
	m_avBoxVertices[0][0] = -m_vBoxHalfSize[0];
	m_avBoxVertices[0][1] =  m_vBoxHalfSize[1];
	m_avBoxVertices[0][2] = -m_vBoxHalfSize[2];

	// vertex 1
	m_avBoxVertices[1][0] =  m_vBoxHalfSize[0];
	m_avBoxVertices[1][1] =  m_vBoxHalfSize[1];
	m_avBoxVertices[1][2] = -m_vBoxHalfSize[2];

	// vertex 2
	m_avBoxVertices[2][0] = -m_vBoxHalfSize[0];
	m_avBoxVertices[2][1] = -m_vBoxHalfSize[1];
	m_avBoxVertices[2][2] = -m_vBoxHalfSize[2];

	// vertex 3
	m_avBoxVertices[3][0] =  m_vBoxHalfSize[0];
	m_avBoxVertices[3][1] = -m_vBoxHalfSize[1];
	m_avBoxVertices[3][2] = -m_vBoxHalfSize[2];

	// vertex 4
	m_avBoxVertices[4][0] =  m_vBoxHalfSize[0];
	m_avBoxVertices[4][1] =  m_vBoxHalfSize[1];
	m_avBoxVertices[4][2] =  m_vBoxHalfSize[2];

	// vertex 5
	m_avBoxVertices[5][0] =  m_vBoxHalfSize[0];
	m_avBoxVertices[5][1] = -m_vBoxHalfSize[1];
	m_avBoxVertices[5][2] =  m_vBoxHalfSize[2];

	// vertex 6
	m_avBoxVertices[6][0] = -m_vBoxHalfSize[0];
	m_avBoxVertices[6][1] = -m_vBoxHalfSize[1];
	m_avBoxVertices[6][2] =  m_vBoxHalfSize[2];

	// vertex 7
	m_avBoxVertices[7][0] = -m_vBoxHalfSize[0];
	m_avBoxVertices[7][1] =  m_vBoxHalfSize[1];
	m_avBoxVertices[7][2] =  m_vBoxHalfSize[2];

	// temp index
	int i = 0;
	dVector3	vTempBoxVertices[8];
	// transform vertices in absolute space
	for(i=0; i < 8; i++) 
	{
		dMultiplyMat3Vec3(m_mBoxRot,m_avBoxVertices[i], vTempBoxVertices[i]);
		dVector3Add(vTempBoxVertices[i], m_vBoxPos, m_avBoxVertices[i]);
	}

	// find relative position
	dVector3Subtract(m_vCylinderPos,m_vBoxPos,m_vDiff);
	m_fBestDepth = MAX_FLOAT;
	m_vNormal[0] = REAL(0.0);
	m_vNormal[1] = REAL(0.0);
	m_vNormal[2] = REAL(0.0);

	// calculate basic angle for nCYLINDER_SEGMENT-gon
	dReal fAngle = (dReal) (M_PI/nCYLINDER_SEGMENT);

	// calculate angle increment
	dReal fAngleIncrement = fAngle * REAL(2.0); 

	// calculate nCYLINDER_SEGMENT-gon points
	for(i = 0; i < nCYLINDER_SEGMENT; i++) 
	{
		m_avCylinderNormals[i][0] = -dCos(fAngle);
		m_avCylinderNormals[i][1] = -dSin(fAngle);
		m_avCylinderNormals[i][2] = 0;

		fAngle += fAngleIncrement;
	}

	m_fBestrb		= 0;
	m_fBestrc		= 0;
	m_iBestAxis		= 0;
	m_nContacts		= 0;

}

// test for given separating axis
int sCylinderBoxData::_cldTestAxis( dVector3& vInputNormal, int iAxis ) 
{
	// check length of input normal
	dReal fL = dVector3Length(vInputNormal);
	// if not long enough
	if ( fL < REAL(1e-5) ) 
	{
		// do nothing
		return 1;
	}

	// otherwise make it unit for sure
	dNormalize3(vInputNormal);

	// project box and Cylinder on mAxis
	dReal fdot1 = dVector3Dot(m_vCylinderAxis, vInputNormal);

	dReal frc;

	if (fdot1 > REAL(1.0)) 
	{
		// assume fdot1 = 1
		frc = m_fCylinderSize*REAL(0.5);
	}
	else if (fdot1 < REAL(-1.0))
	{
		// assume fdot1 = -1
		frc = m_fCylinderSize*REAL(0.5);
	}
	else
	{
    	// project box and capsule on iAxis
    	frc = dFabs( fdot1 * (m_fCylinderSize*REAL(0.5))) + m_fCylinderRadius * dSqrt(REAL(1.0)-(fdot1*fdot1));
    }
    
	dVector3	vTemp1;

	dMat3GetCol(m_mBoxRot,0,vTemp1);
	dReal frb = dFabs(dVector3Dot(vTemp1,vInputNormal))*m_vBoxHalfSize[0];

	dMat3GetCol(m_mBoxRot,1,vTemp1);
	frb += dFabs(dVector3Dot(vTemp1,vInputNormal))*m_vBoxHalfSize[1];

	dMat3GetCol(m_mBoxRot,2,vTemp1);
	frb += dFabs(dVector3Dot(vTemp1,vInputNormal))*m_vBoxHalfSize[2];
	
	// project their distance on separating axis
	dReal fd  = dVector3Dot(m_vDiff,vInputNormal);

	// get depth 

	dReal fDepth = frc + frb;  // Calculate partial depth

	// if they do not overlap exit, we have no intersection
	if ( dFabs(fd) > fDepth )
	{ 
		return 0; 
	} 

	// Finalyze the depth calculation
	fDepth -= dFabs(fd);

	// get maximum depth
	if ( fDepth < m_fBestDepth ) 
	{
		m_fBestDepth = fDepth;
		dVector3Copy(vInputNormal,m_vNormal);
		m_iBestAxis  = iAxis;
		m_fBestrb    = frb;
		m_fBestrc    = frc;

		// flip normal if interval is wrong faced
		if (fd > 0) 
		{ 
			dVector3Inv(m_vNormal);
		}
	}

	return 1;
}


// check for separation between box edge and cylinder circle edge
int sCylinderBoxData::_cldTestEdgeCircleAxis( 
							const dVector3 &vCenterPoint, 
							const dVector3 &vVx0, const dVector3 &vVx1, 
							int iAxis ) 
{
	// calculate direction of edge
	dVector3 vDirEdge;
	dVector3Subtract(vVx1,vVx0,vDirEdge);
	dNormalize3(vDirEdge);
	// starting point of edge 
	dVector3 vEStart;
	dVector3Copy(vVx0,vEStart);;

	// calculate angle cosine between cylinder axis and edge
	dReal fdot2 = dVector3Dot (vDirEdge,m_vCylinderAxis);

	// if edge is perpendicular to cylinder axis
	if(dFabs(fdot2) < REAL(1e-5)) 
	{
		// this can't be separating axis, because edge is parallel to circle plane
		return 1;
	}

	// find point of intersection between edge line and circle plane
	dVector3 vTemp1;
	dVector3Subtract(vCenterPoint,vEStart,vTemp1);
	dReal fdot1 = dVector3Dot(vTemp1,m_vCylinderAxis);
	dVector3 vpnt;
	vpnt[0]= vEStart[0] + vDirEdge[0] * (fdot1/fdot2);
	vpnt[1]= vEStart[1] + vDirEdge[1] * (fdot1/fdot2);
	vpnt[2]= vEStart[2] + vDirEdge[2] * (fdot1/fdot2);

	// find tangent vector on circle with same center (vCenterPoint) that
	// touches point of intersection (vpnt)
	dVector3 vTangent;
	dVector3Subtract(vCenterPoint,vpnt,vTemp1);
	dVector3Cross(vTemp1,m_vCylinderAxis,vTangent);
	
	// find vector orthogonal both to tangent and edge direction
	dVector3 vAxis;
	dVector3Cross(vTangent,vDirEdge,vAxis);

	// use that vector as separating axis
	return _cldTestAxis( vAxis, iAxis );
}

// Test separating axis for collision
int sCylinderBoxData::_cldTestSeparatingAxes() 
{
	// reset best axis
	m_fBestDepth = MAX_FLOAT;
	m_iBestAxis = 0;
	m_fBestrb = 0;
	m_fBestrc = 0;
	m_nContacts = 0;

	dVector3  vAxis = {REAL(0.0),REAL(0.0),REAL(0.0),REAL(0.0)};

	// Epsilon value for checking axis vector length 
	const dReal fEpsilon = REAL(1e-6);

	// axis A0
	dMat3GetCol(m_mBoxRot, 0 , vAxis);
	if (!_cldTestAxis( vAxis, 1 )) 
	{
		return 0;
	}

	// axis A1
	dMat3GetCol(m_mBoxRot, 1 , vAxis);
	if (!_cldTestAxis( vAxis, 2 )) 
	{
		return 0;
	}

	// axis A2
	dMat3GetCol(m_mBoxRot, 2 , vAxis);
	if (!_cldTestAxis( vAxis, 3 )) 
	{
		return 0;
	}

	// axis C - Cylinder Axis
	//vAxis = vCylinderAxis;
	dVector3Copy(m_vCylinderAxis , vAxis);
	if (!_cldTestAxis( vAxis, 4 )) 
	{
		return 0;
	}

	// axis CxA0
	//vAxis = ( vCylinderAxis cross mthGetColM33f( mBoxRot, 0 ));
	dVector3CrossMat3Col(m_mBoxRot, 0 ,m_vCylinderAxis, vAxis);
	if(dVector3LengthSquare( vAxis ) > fEpsilon ) 
	{
		if (!_cldTestAxis( vAxis, 5 ))
		{
			return 0;
		}
	}

	// axis CxA1
	//vAxis = ( vCylinderAxis cross mthGetColM33f( mBoxRot, 1 ));
	dVector3CrossMat3Col(m_mBoxRot, 1 ,m_vCylinderAxis, vAxis);
	if(dVector3LengthSquare( vAxis ) > fEpsilon ) 
	{
		if (!_cldTestAxis( vAxis, 6 )) 
		{
			return 0;
		}
	}

	// axis CxA2
	//vAxis = ( vCylinderAxis cross mthGetColM33f( mBoxRot, 2 ));
	dVector3CrossMat3Col(m_mBoxRot, 2 ,m_vCylinderAxis, vAxis);
	if(dVector3LengthSquare( vAxis ) > fEpsilon ) 
	{
		if (!_cldTestAxis( vAxis, 7 ))
		{
			return 0;
		}
	}

	int i = 0;
	dVector3	vTemp1;
	dVector3	vTemp2;
	// here we check box's vertices axis
	for(i=0; i< 8; i++) 
	{
		//vAxis = ( vCylinderAxis cross (m_avBoxVertices[i] - vCylinderPos));
		dVector3Subtract(m_avBoxVertices[i],m_vCylinderPos,vTemp1);
		dVector3Cross(m_vCylinderAxis,vTemp1,vTemp2);
		//vAxis = ( vCylinderAxis cross vAxis );
		dVector3Cross(m_vCylinderAxis,vTemp2,vAxis);
		if(dVector3LengthSquare( vAxis ) > fEpsilon ) 
		{
			if (!_cldTestAxis( vAxis, 8 + i ))
			{
				return 0;
			}
		}
	}

	// ************************************
	// this is defined for first 12 axes
	// normal of plane that contains top circle of cylinder
	// center of top circle of cylinder
	dVector3 vcc;
	vcc[0] = (m_vCylinderPos)[0] + m_vCylinderAxis[0]*(m_fCylinderSize*REAL(0.5));
	vcc[1] = (m_vCylinderPos)[1] + m_vCylinderAxis[1]*(m_fCylinderSize*REAL(0.5));
	vcc[2] = (m_vCylinderPos)[2] + m_vCylinderAxis[2]*(m_fCylinderSize*REAL(0.5));
	// ************************************

	if (!_cldTestEdgeCircleAxis( vcc, m_avBoxVertices[1], m_avBoxVertices[0], 16)) 
	{
		return 0;
	}

	if (!_cldTestEdgeCircleAxis( vcc, m_avBoxVertices[1], m_avBoxVertices[3], 17)) 
	{
		return 0;
	}

	if (!_cldTestEdgeCircleAxis( vcc, m_avBoxVertices[2], m_avBoxVertices[3], 18))
	{
		return 0;
	}

	if (!_cldTestEdgeCircleAxis( vcc, m_avBoxVertices[2], m_avBoxVertices[0], 19)) 
	{
		return 0;
	}


	if (!_cldTestEdgeCircleAxis( vcc, m_avBoxVertices[4], m_avBoxVertices[1], 20))
	{
		return 0;
	}

	if (!_cldTestEdgeCircleAxis( vcc, m_avBoxVertices[4], m_avBoxVertices[7], 21))
	{
		return 0;
	}

	if (!_cldTestEdgeCircleAxis( vcc, m_avBoxVertices[0], m_avBoxVertices[7], 22)) 
	{
		return 0;
	}

	if (!_cldTestEdgeCircleAxis( vcc, m_avBoxVertices[5], m_avBoxVertices[3], 23)) 
	{
		return 0;
	}

	if (!_cldTestEdgeCircleAxis( vcc, m_avBoxVertices[5], m_avBoxVertices[6], 24)) 
	{
		return 0;
	}

	if (!_cldTestEdgeCircleAxis( vcc, m_avBoxVertices[2], m_avBoxVertices[6], 25)) 
	{
		return 0;
	}

	if (!_cldTestEdgeCircleAxis( vcc, m_avBoxVertices[4], m_avBoxVertices[5], 26)) 
	{
		return 0;
	}

	if (!_cldTestEdgeCircleAxis( vcc, m_avBoxVertices[6], m_avBoxVertices[7], 27)) 
	{
		return 0;
	}

	// ************************************
	// this is defined for second 12 axes
	// normal of plane that contains bottom circle of cylinder
	// center of bottom circle of cylinder
	//	vcc = vCylinderPos - vCylinderAxis*(fCylinderSize*REAL(0.5));
	vcc[0] = (m_vCylinderPos)[0] - m_vCylinderAxis[0]*(m_fCylinderSize*REAL(0.5));
	vcc[1] = (m_vCylinderPos)[1] - m_vCylinderAxis[1]*(m_fCylinderSize*REAL(0.5));
	vcc[2] = (m_vCylinderPos)[2] - m_vCylinderAxis[2]*(m_fCylinderSize*REAL(0.5));
	// ************************************

	if (!_cldTestEdgeCircleAxis( vcc, m_avBoxVertices[1], m_avBoxVertices[0], 28)) 
	{
		return 0;
	}

	if (!_cldTestEdgeCircleAxis( vcc, m_avBoxVertices[1], m_avBoxVertices[3], 29)) 
	{
		return 0;
	}

	if (!_cldTestEdgeCircleAxis( vcc, m_avBoxVertices[2], m_avBoxVertices[3], 30)) 
	{
		return 0;
	}

	if (!_cldTestEdgeCircleAxis( vcc, m_avBoxVertices[2], m_avBoxVertices[0], 31)) 
	{
		return 0;
	}

	if (!_cldTestEdgeCircleAxis( vcc, m_avBoxVertices[4], m_avBoxVertices[1], 32)) 
	{
		return 0;
	}

	if (!_cldTestEdgeCircleAxis( vcc, m_avBoxVertices[4], m_avBoxVertices[7], 33)) 
	{
		return 0;
	}

	if (!_cldTestEdgeCircleAxis( vcc, m_avBoxVertices[0], m_avBoxVertices[7], 34)) 
	{
		return 0;
	}

	if (!_cldTestEdgeCircleAxis( vcc, m_avBoxVertices[5], m_avBoxVertices[3], 35)) 
	{
		return 0;
	}

	if (!_cldTestEdgeCircleAxis( vcc, m_avBoxVertices[5], m_avBoxVertices[6], 36)) 
	{
		return 0;
	}

	if (!_cldTestEdgeCircleAxis( vcc, m_avBoxVertices[2], m_avBoxVertices[6], 37)) 
	{
		return 0;
	}

	if (!_cldTestEdgeCircleAxis( vcc, m_avBoxVertices[4], m_avBoxVertices[5], 38)) 
	{
		return 0;
	}

	if (!_cldTestEdgeCircleAxis( vcc, m_avBoxVertices[6], m_avBoxVertices[7], 39)) 
	{
		return 0;
	}

	return 1;
}

int sCylinderBoxData::_cldClipCylinderToBox()
{
	dIASSERT(m_nContacts != (m_iFlags & NUMC_MASK));

	// calculate that vector perpendicular to cylinder axis which closes lowest angle with collision normal
	dVector3 vN;
	dReal fTemp1 = dVector3Dot(m_vCylinderAxis,m_vNormal);
	vN[0]	=	m_vNormal[0] - m_vCylinderAxis[0]*fTemp1;
	vN[1]	=	m_vNormal[1] - m_vCylinderAxis[1]*fTemp1;
	vN[2]	=	m_vNormal[2] - m_vCylinderAxis[2]*fTemp1;

	// normalize that vector
	dNormalize3(vN);

	// translate cylinder end points by the vector
	dVector3 vCposTrans;
	vCposTrans[0] = m_vCylinderPos[0] + vN[0] * m_fCylinderRadius;
	vCposTrans[1] = m_vCylinderPos[1] + vN[1] * m_fCylinderRadius;
	vCposTrans[2] = m_vCylinderPos[2] + vN[2] * m_fCylinderRadius;

	m_vEp0[0]  = vCposTrans[0] + m_vCylinderAxis[0]*(m_fCylinderSize*REAL(0.5));
	m_vEp0[1]  = vCposTrans[1] + m_vCylinderAxis[1]*(m_fCylinderSize*REAL(0.5));
	m_vEp0[2]  = vCposTrans[2] + m_vCylinderAxis[2]*(m_fCylinderSize*REAL(0.5));

	m_vEp1[0]  = vCposTrans[0] - m_vCylinderAxis[0]*(m_fCylinderSize*REAL(0.5));
	m_vEp1[1]  = vCposTrans[1] - m_vCylinderAxis[1]*(m_fCylinderSize*REAL(0.5));
	m_vEp1[2]  = vCposTrans[2] - m_vCylinderAxis[2]*(m_fCylinderSize*REAL(0.5));

	// transform edge points in box space
	m_vEp0[0] -= m_vBoxPos[0];
	m_vEp0[1] -= m_vBoxPos[1];
	m_vEp0[2] -= m_vBoxPos[2];

	m_vEp1[0] -= m_vBoxPos[0];
	m_vEp1[1] -= m_vBoxPos[1];
	m_vEp1[2] -= m_vBoxPos[2];

	dVector3 vTemp1;
	// clip the edge to box 
	dVector4 plPlane;
	// plane 0 +x
	dMat3GetCol(m_mBoxRot,0,vTemp1);
	dConstructPlane(vTemp1,m_vBoxHalfSize[0],plPlane);
	if(!dClipEdgeToPlane( m_vEp0, m_vEp1, plPlane )) 
	{ 
		return 0; 
	}

	// plane 1 +y
	dMat3GetCol(m_mBoxRot,1,vTemp1);
	dConstructPlane(vTemp1,m_vBoxHalfSize[1],plPlane);
	if(!dClipEdgeToPlane( m_vEp0, m_vEp1, plPlane )) 
	{ 
		return 0; 
	}

	// plane 2 +z
	dMat3GetCol(m_mBoxRot,2,vTemp1);
	dConstructPlane(vTemp1,m_vBoxHalfSize[2],plPlane);
	if(!dClipEdgeToPlane( m_vEp0, m_vEp1, plPlane )) 
	{ 
		return 0; 
	}

	// plane 3 -x
	dMat3GetCol(m_mBoxRot,0,vTemp1);
	dVector3Inv(vTemp1);
	dConstructPlane(vTemp1,m_vBoxHalfSize[0],plPlane);
	if(!dClipEdgeToPlane( m_vEp0, m_vEp1, plPlane )) 
	{ 
		return 0; 
	}

	// plane 4 -y
	dMat3GetCol(m_mBoxRot,1,vTemp1);
	dVector3Inv(vTemp1);
	dConstructPlane(vTemp1,m_vBoxHalfSize[1],plPlane);
	if(!dClipEdgeToPlane( m_vEp0, m_vEp1, plPlane )) 
	{ 
		return 0; 
	}

	// plane 5 -z
	dMat3GetCol(m_mBoxRot,2,vTemp1);
	dVector3Inv(vTemp1);
	dConstructPlane(vTemp1,m_vBoxHalfSize[2],plPlane);
	if(!dClipEdgeToPlane( m_vEp0, m_vEp1, plPlane )) 
	{ 
		return 0; 
	}

	// calculate depths for both contact points
	m_fDepth0 = m_fBestrb + dVector3Dot(m_vEp0, m_vNormal);
	m_fDepth1 = m_fBestrb + dVector3Dot(m_vEp1, m_vNormal);

	// clamp depths to 0
	if(m_fDepth0<0) 
	{
		m_fDepth0 = REAL(0.0);
	}

	if(m_fDepth1<0) 
	{
		m_fDepth1 = REAL(0.0);
	}

	// back transform edge points from box to absolute space
	m_vEp0[0] += m_vBoxPos[0];
	m_vEp0[1] += m_vBoxPos[1];
	m_vEp0[2] += m_vBoxPos[2];

	m_vEp1[0] += m_vBoxPos[0];
	m_vEp1[1] += m_vBoxPos[1];
	m_vEp1[2] += m_vBoxPos[2];

	dContactGeom* Contact0 = SAFECONTACT(m_iFlags, m_gContact, m_nContacts, m_iSkip);
	Contact0->depth = m_fDepth0;
	dVector3Copy(m_vNormal,Contact0->normal);
	dVector3Copy(m_vEp0,Contact0->pos);
	Contact0->g1 = m_gCylinder;
	Contact0->g2 = m_gBox;
	Contact0->side1 = -1;
	Contact0->side2 = -1;
	dVector3Inv(Contact0->normal);
	m_nContacts++;
	
	if (m_nContacts != (m_iFlags & NUMC_MASK))
	{
		dContactGeom* Contact1 = SAFECONTACT(m_iFlags, m_gContact, m_nContacts, m_iSkip);
		Contact1->depth = m_fDepth1;
		dVector3Copy(m_vNormal,Contact1->normal);
		dVector3Copy(m_vEp1,Contact1->pos);
		Contact1->g1 = m_gCylinder;
		Contact1->g2 = m_gBox;
		Contact1->side1 = -1;
		Contact1->side2 = -1;
		dVector3Inv(Contact1->normal);
		m_nContacts++;
	}

	return 1;
}


void sCylinderBoxData::_cldClipBoxToCylinder() 
{
	dIASSERT(m_nContacts != (m_iFlags & NUMC_MASK));
	
	dVector3 vCylinderCirclePos, vCylinderCircleNormal_Rel;
	// check which circle from cylinder we take for clipping
	if ( dVector3Dot(m_vCylinderAxis, m_vNormal) > REAL(0.0) ) 
	{
		// get top circle
		vCylinderCirclePos[0] = m_vCylinderPos[0] + m_vCylinderAxis[0]*(m_fCylinderSize*REAL(0.5));
		vCylinderCirclePos[1] = m_vCylinderPos[1] + m_vCylinderAxis[1]*(m_fCylinderSize*REAL(0.5));
		vCylinderCirclePos[2] = m_vCylinderPos[2] + m_vCylinderAxis[2]*(m_fCylinderSize*REAL(0.5));

		vCylinderCircleNormal_Rel[0] = REAL(0.0);
		vCylinderCircleNormal_Rel[1] = REAL(0.0);
		vCylinderCircleNormal_Rel[2] = REAL(0.0);
		vCylinderCircleNormal_Rel[nCYLINDER_AXIS] = REAL(-1.0);
	}
	else 
	{
		// get bottom circle
		vCylinderCirclePos[0] = m_vCylinderPos[0] - m_vCylinderAxis[0]*(m_fCylinderSize*REAL(0.5));
		vCylinderCirclePos[1] = m_vCylinderPos[1] - m_vCylinderAxis[1]*(m_fCylinderSize*REAL(0.5));
		vCylinderCirclePos[2] = m_vCylinderPos[2] - m_vCylinderAxis[2]*(m_fCylinderSize*REAL(0.5));

		vCylinderCircleNormal_Rel[0] = REAL(0.0);
		vCylinderCircleNormal_Rel[1] = REAL(0.0);
		vCylinderCircleNormal_Rel[2] = REAL(0.0);
		vCylinderCircleNormal_Rel[nCYLINDER_AXIS] = REAL(1.0);
	}

	// vNr is normal in Box frame, pointing from Cylinder to Box
	dVector3 vNr;
	dMatrix3 mBoxInv;

	// Find a way to use quaternion
	dMatrix3Inv(m_mBoxRot,mBoxInv);
	dMultiplyMat3Vec3(mBoxInv,m_vNormal,vNr);

	dVector3 vAbsNormal;

	vAbsNormal[0] = dFabs( vNr[0] );
	vAbsNormal[1] = dFabs( vNr[1] );
	vAbsNormal[2] = dFabs( vNr[2] );

	// find which face in box is closest to cylinder
	int iB0, iB1, iB2;

	// Different from Croteam's code
	if (vAbsNormal[1] > vAbsNormal[0]) 
	{
		// 1 > 0
		if (vAbsNormal[0]> vAbsNormal[2]) 
		{
			// 0 > 2 -> 1 > 0 >2
			iB0 = 1; iB1 = 0; iB2 = 2;
		} 
		else 
		{
			// 2 > 0-> Must compare 1 and 2
			if (vAbsNormal[1] > vAbsNormal[2])
			{
				// 1 > 2 -> 1 > 2 > 0
				iB0 = 1; iB1 = 2; iB2 = 0;
			}
			else
			{
				// 2 > 1 -> 2 > 1 > 0;
				iB0 = 2; iB1 = 1; iB2 = 0;
			}			
		}
	} 
	else 
	{
		// 0 > 1
		if (vAbsNormal[1] > vAbsNormal[2]) 
		{
			// 1 > 2 -> 0 > 1 > 2
			iB0 = 0; iB1 = 1; iB2 = 2;
		}
		else 
		{
			// 2 > 1 -> Must compare 0 and 2
			if (vAbsNormal[0] > vAbsNormal[2])
			{
				// 0 > 2 -> 0 > 2 > 1;
				iB0 = 0; iB1 = 2; iB2 = 1;
			}
			else
			{
				// 2 > 0 -> 2 > 0 > 1;
				iB0 = 2; iB1 = 0; iB2 = 1;
			}		
		}
	}

	dVector3 vCenter;
	// find center of box polygon
	dVector3 vTemp;
	if (vNr[iB0] > 0) 
	{
		dMat3GetCol(m_mBoxRot,iB0,vTemp);
		vCenter[0] = m_vBoxPos[0] - m_vBoxHalfSize[iB0]*vTemp[0];
		vCenter[1] = m_vBoxPos[1] - m_vBoxHalfSize[iB0]*vTemp[1];
		vCenter[2] = m_vBoxPos[2] - m_vBoxHalfSize[iB0]*vTemp[2];
	}
	else 
	{
		dMat3GetCol(m_mBoxRot,iB0,vTemp);
		vCenter[0] = m_vBoxPos[0] + m_vBoxHalfSize[iB0]*vTemp[0];
		vCenter[1] = m_vBoxPos[1] + m_vBoxHalfSize[iB0]*vTemp[1];
		vCenter[2] = m_vBoxPos[2] + m_vBoxHalfSize[iB0]*vTemp[2];
	}

	// find the vertices of box polygon
	dVector3 avPoints[4];
	dVector3 avTempArray1[MAX_CYLBOX_CLIP_POINTS];
	dVector3 avTempArray2[MAX_CYLBOX_CLIP_POINTS];

	int i=0;
	for(i=0; i<MAX_CYLBOX_CLIP_POINTS; i++) 
	{
		avTempArray1[i][0] = REAL(0.0);
		avTempArray1[i][1] = REAL(0.0);
		avTempArray1[i][2] = REAL(0.0);

		avTempArray2[i][0] = REAL(0.0);
		avTempArray2[i][1] = REAL(0.0);
		avTempArray2[i][2] = REAL(0.0);
	}

	dVector3 vAxis1, vAxis2;

	dMat3GetCol(m_mBoxRot,iB1,vAxis1);
	dMat3GetCol(m_mBoxRot,iB2,vAxis2);

	avPoints[0][0] = vCenter[0] + m_vBoxHalfSize[iB1] * vAxis1[0] - m_vBoxHalfSize[iB2] * vAxis2[0];
	avPoints[0][1] = vCenter[1] + m_vBoxHalfSize[iB1] * vAxis1[1] - m_vBoxHalfSize[iB2] * vAxis2[1];
	avPoints[0][2] = vCenter[2] + m_vBoxHalfSize[iB1] * vAxis1[2] - m_vBoxHalfSize[iB2] * vAxis2[2];

	avPoints[1][0] = vCenter[0] - m_vBoxHalfSize[iB1] * vAxis1[0] - m_vBoxHalfSize[iB2] * vAxis2[0];
	avPoints[1][1] = vCenter[1] - m_vBoxHalfSize[iB1] * vAxis1[1] - m_vBoxHalfSize[iB2] * vAxis2[1];
	avPoints[1][2] = vCenter[2] - m_vBoxHalfSize[iB1] * vAxis1[2] - m_vBoxHalfSize[iB2] * vAxis2[2];

	avPoints[2][0] = vCenter[0] - m_vBoxHalfSize[iB1] * vAxis1[0] + m_vBoxHalfSize[iB2] * vAxis2[0];
	avPoints[2][1] = vCenter[1] - m_vBoxHalfSize[iB1] * vAxis1[1] + m_vBoxHalfSize[iB2] * vAxis2[1];
	avPoints[2][2] = vCenter[2] - m_vBoxHalfSize[iB1] * vAxis1[2] + m_vBoxHalfSize[iB2] * vAxis2[2];

	avPoints[3][0] = vCenter[0] + m_vBoxHalfSize[iB1] * vAxis1[0] + m_vBoxHalfSize[iB2] * vAxis2[0];
	avPoints[3][1] = vCenter[1] + m_vBoxHalfSize[iB1] * vAxis1[1] + m_vBoxHalfSize[iB2] * vAxis2[1];
	avPoints[3][2] = vCenter[2] + m_vBoxHalfSize[iB1] * vAxis1[2] + m_vBoxHalfSize[iB2] * vAxis2[2];

	// transform box points to space of cylinder circle
	dMatrix3 mCylinderInv;
	dMatrix3Inv(m_mCylinderRot,mCylinderInv);

	for(i=0; i<4; i++) 
	{
		dVector3Subtract(avPoints[i],vCylinderCirclePos,vTemp);
		dMultiplyMat3Vec3(mCylinderInv,vTemp,avPoints[i]);
	}

	int iTmpCounter1 = 0;
	int iTmpCounter2 = 0;
	dVector4 plPlane;

	// plane of cylinder that contains circle for intersection
	dConstructPlane(vCylinderCircleNormal_Rel,REAL(0.0),plPlane);
	dClipPolyToPlane(avPoints, 4, avTempArray1, iTmpCounter1, plPlane);


	// Body of base circle of Cylinder
	int nCircleSegment = 0;
	for (nCircleSegment = 0; nCircleSegment < nCYLINDER_SEGMENT; nCircleSegment++)
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

		dIASSERT( iTmpCounter1 >= 0 && iTmpCounter1 <= MAX_CYLBOX_CLIP_POINTS );
		dIASSERT( iTmpCounter2 >= 0 && iTmpCounter2 <= MAX_CYLBOX_CLIP_POINTS );
	}
	
	// back transform clipped points to absolute space
	dReal ftmpdot;	
	dReal fTempDepth;
	dVector3 vPoint;

	if (nCircleSegment % 2)
	{
		for( i=0; i<iTmpCounter2; i++)
		{
			dMultiply0_331(vPoint,m_mCylinderRot,avTempArray2[i]);
			vPoint[0] += vCylinderCirclePos[0];
			vPoint[1] += vCylinderCirclePos[1];
			vPoint[2] += vCylinderCirclePos[2];

			dVector3Subtract(vPoint,m_vCylinderPos,vTemp);
			ftmpdot	 = dVector3Dot(vTemp, m_vNormal);
			fTempDepth = m_fBestrc - ftmpdot;
			// Depth must be positive
			if (fTempDepth > REAL(0.0))
			{
				// generate contacts
				dContactGeom* Contact0 = SAFECONTACT(m_iFlags, m_gContact, m_nContacts, m_iSkip);
				Contact0->depth = fTempDepth;
				dVector3Copy(m_vNormal,Contact0->normal);
				dVector3Copy(vPoint,Contact0->pos);
				Contact0->g1 = m_gCylinder;
				Contact0->g2 = m_gBox;
				Contact0->side1 = -1;
				Contact0->side2 = -1;
				dVector3Inv(Contact0->normal);
				m_nContacts++;
				
				if (m_nContacts == (m_iFlags & NUMC_MASK))
				{
					break;
				}
			}
		}
	}
	else
	{
		for( i=0; i<iTmpCounter1; i++)
		{
			dMultiply0_331(vPoint,m_mCylinderRot,avTempArray1[i]);
			vPoint[0] += vCylinderCirclePos[0];
			vPoint[1] += vCylinderCirclePos[1];
			vPoint[2] += vCylinderCirclePos[2];

			dVector3Subtract(vPoint,m_vCylinderPos,vTemp);
			ftmpdot	 = dVector3Dot(vTemp, m_vNormal);
			fTempDepth = m_fBestrc - ftmpdot;
			// Depth must be positive
			if (fTempDepth > REAL(0.0))
			{
				// generate contacts
				dContactGeom* Contact0 = SAFECONTACT(m_iFlags, m_gContact, m_nContacts, m_iSkip);
				Contact0->depth = fTempDepth;
				dVector3Copy(m_vNormal,Contact0->normal);
				dVector3Copy(vPoint,Contact0->pos);
				Contact0->g1 = m_gCylinder;
				Contact0->g2 = m_gBox;
				Contact0->side1 = -1;
				Contact0->side2 = -1;
				dVector3Inv(Contact0->normal);
				m_nContacts++;
				
				if (m_nContacts == (m_iFlags & NUMC_MASK))
				{
					break;
				}
			}
		}
	}
}

int sCylinderBoxData::PerformCollisionChecking()
{
	// initialize collider
	_cldInitCylinderBox();

	// do intersection test and find best separating axis
	if ( !_cldTestSeparatingAxes() ) 
	{
		// if not found do nothing
		return 0;
	}

	// if best separation axis is not found
	if ( m_iBestAxis == 0 ) 
	{
		// this should not happen (we should already exit in that case)
		dIASSERT(0);
		// do nothing
		return 0;
	}

	dReal fdot = dVector3Dot(m_vNormal,m_vCylinderAxis);
	// choose which clipping method are we going to apply
	if (dFabs(fdot) < REAL(0.9) ) 
	{
		// clip cylinder over box
		if(!_cldClipCylinderToBox()) 
		{
			return 0;
		}
	} 
	else 
	{
		_cldClipBoxToCylinder();  
	}

	return m_nContacts;
}

// Cylinder - Box by CroTeam
// Ported by Nguyen Binh
int dCollideCylinderBox(dxGeom *o1, dxGeom *o2, int flags, dContactGeom *contact, int skip)
{
	dIASSERT (skip >= (int)sizeof(dContactGeom));
	dIASSERT (o1->type == dCylinderClass);
	dIASSERT (o2->type == dBoxClass);
	dIASSERT ((flags & NUMC_MASK) >= 1);

	sCylinderBoxData cData(o1, o2, flags, contact, skip);

	return cData.PerformCollisionChecking();
}


