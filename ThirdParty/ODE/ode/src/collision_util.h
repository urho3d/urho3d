/*************************************************************************
 *                                                                       *
 * Open Dynamics Engine, Copyright (C) 2001,2002 Russell L. Smith.       *
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

some useful collision utility stuff.

*/

#ifndef _ODE_COLLISION_UTIL_H_
#define _ODE_COLLISION_UTIL_H_

#include <ode/common.h>
#include <ode/contact.h>
#include <ode/odemath.h>
#include <ode/rotation.h>


// given a pointer `p' to a dContactGeom, return the dContactGeom at
// p + skip bytes.
#define CONTACT(p,skip) ((dContactGeom*) (((char*)p) + (skip)))

#if 1
#include "collision_kernel.h"
// Fetches a contact
static inline dContactGeom* SAFECONTACT(int Flags, dContactGeom* Contacts, int Index, int Stride){
	dIASSERT(Index >= 0 && Index < (Flags & NUMC_MASK));
	return ((dContactGeom*)(((char*)Contacts) + (Index * Stride)));
}
#endif


// if the spheres (p1,r1) and (p2,r2) collide, set the contact `c' and
// return 1, else return 0.

int dCollideSpheres (dVector3 p1, dReal r1,
		     dVector3 p2, dReal r2, dContactGeom *c);


// given two lines
//    qa = pa + alpha* ua
//    qb = pb + beta * ub
// where pa,pb are two points, ua,ub are two unit length vectors, and alpha,
// beta go from [-inf,inf], return alpha and beta such that qa and qb are
// as close as possible

void dLineClosestApproach (const dVector3 pa, const dVector3 ua,
			   const dVector3 pb, const dVector3 ub,
			   dReal *alpha, dReal *beta);


// given a line segment p1-p2 and a box (center 'c', rotation 'R', side length
// vector 'side'), compute the points of closest approach between the box
// and the line. return these points in 'lret' (the point on the line) and
// 'bret' (the point on the box). if the line actually penetrates the box
// then the solution is not unique, but only one solution will be returned.
// in this case the solution points will coincide.

void dClosestLineBoxPoints (const dVector3 p1, const dVector3 p2,
			    const dVector3 c, const dMatrix3 R,
			    const dVector3 side,
			    dVector3 lret, dVector3 bret);

// 20 Apr 2004
// Start code by Nguyen Binh
int dClipEdgeToPlane(dVector3 &vEpnt0, dVector3 &vEpnt1, const dVector4& plPlane);
// clip polygon with plane and generate new polygon points
void dClipPolyToPlane(const dVector3 avArrayIn[], const int ctIn, dVector3 avArrayOut[], int &ctOut, const dVector4 &plPlane );

void dClipPolyToCircle(const dVector3 avArrayIn[], const int ctIn, dVector3 avArrayOut[], int &ctOut, const dVector4 &plPlane ,dReal fRadius);

// Some vector math
static inline void dVector3Subtract(const dVector3& a,const dVector3& b,dVector3& c)
{
  dSubtractVectors3(c, a, b);
}

static inline void dVector3Scale(dVector3& a,dReal nScale)
{
  dScaleVector3(a, nScale);
}

static inline void dVector3Add(const dVector3& a,const dVector3& b,dVector3& c)
{
  dAddVectors3(c, a, b);
}

static inline void dVector3Copy(const dVector3& a,dVector3& c)
{
  dCopyVector3(c, a);
}

static inline void dVector4Copy(const dVector4& a,dVector4& c)
{
  dCopyVector4(c, a);
}

static inline void dVector3Cross(const dVector3& a,const dVector3& b,dVector3& c)
{
	dCalcVectorCross3(c, a, b);
}

static inline dReal dVector3Length(const dVector3& a)
{
	return dCalcVectorLength3(a);
}

static inline dReal dVector3LengthSquare(const dVector3& a)
{
  return dCalcVectorLengthSquare3(a);
}

static inline dReal dVector3Dot(const dVector3& a,const dVector3& b)
{
	return dCalcVectorDot3(a, b);
}

static inline void dVector3Inv(dVector3& a)
{
  dNegateVector3(a);
}

static inline void dMat3GetCol(const dMatrix3& m,const int col, dVector3& v)
{
  dGetMatrixColumn3(v, m, col);
}

static inline void dVector3CrossMat3Col(const dMatrix3& m,const int col,const dVector3& v,dVector3& r)
{
  dCalcVectorCross3_114(r, v, m + col);
}

static inline void dMat3ColCrossVector3(const dMatrix3& m,const int col,const dVector3& v,dVector3& r)
{
  dCalcVectorCross3_141(r, m + col, v);
}

static inline void dMultiplyMat3Vec3(const dMatrix3& m,const dVector3& v, dVector3& r)
{
	dMultiply0_331(r, m, v);
}

static inline dReal dPointPlaneDistance(const dVector3& point,const dVector4& plane)
{
	return (plane[0]*point[0] + plane[1]*point[1] + plane[2]*point[2] + plane[3]);
}

static inline void dConstructPlane(const dVector3& normal,const dReal& distance, dVector4& plane)
{
	plane[0] = normal[0];
	plane[1] = normal[1];
	plane[2] = normal[2];
	plane[3] = distance;
}

static inline void dMatrix3Copy(const dReal* source,dMatrix3& dest)
{
  dCopyMatrix4x3(dest, source);
}

static inline dReal dMatrix3Det( const dMatrix3& mat )
{
	dReal det;

	det = mat[0] * ( mat[5]*mat[10] - mat[9]*mat[6] )
		- mat[1] * ( mat[4]*mat[10] - mat[8]*mat[6] )
		+ mat[2] * ( mat[4]*mat[9]  - mat[8]*mat[5] );

	return( det );
}


inline void dMatrix3Inv( const dMatrix3& ma, dMatrix3& dst )
{
	dReal det = dMatrix3Det( ma );

	if ( dFabs( det ) < REAL(0.0005) )
	{
		dRSetIdentity( dst );
		return;
	}

	dst[0] =    ma[5]*ma[10] - ma[6]*ma[9]   / det;
	dst[1] = -( ma[1]*ma[10] - ma[9]*ma[2] ) / det;
	dst[2] =    ma[1]*ma[6]  - ma[5]*ma[2]   / det;

	dst[4] = -( ma[4]*ma[10] - ma[6]*ma[8] ) / det;
	dst[5] =    ma[0]*ma[10] - ma[8]*ma[2]   / det;
	dst[6] = -( ma[0]*ma[6] - ma[4]*ma[2] ) / det;

	dst[8] =    ma[4]*ma[9] - ma[8]*ma[5]   / det;
	dst[9] = -( ma[0]*ma[9] - ma[8]*ma[1] ) / det;
	dst[10] =    ma[0]*ma[5] - ma[1]*ma[4]   / det;
}

inline void dQuatTransform(const dQuaternion& quat,const dVector3& source,dVector3& dest)
{

	// Nguyen Binh : this code seem to be the fastest.
	dReal x0 = 	source[0] * quat[0] + source[2] * quat[2] - source[1] * quat[3];
	dReal x1 = 	source[1] * quat[0] + source[0] * quat[3] - source[2] * quat[1];
	dReal x2 = 	source[2] * quat[0] + source[1] * quat[1] - source[0] * quat[2];
	dReal x3 = 	source[0] * quat[1] + source[1] * quat[2] + source[2] * quat[3];

	dest[0]  = 	quat[0] * x0 + quat[1] * x3 + quat[2] * x2 - quat[3] * x1;
	dest[1]  = 	quat[0] * x1 + quat[2] * x3 + quat[3] * x0 - quat[1] * x2;
	dest[2]  = 	quat[0] * x2 + quat[3] * x3 + quat[1] * x1 - quat[2] * x0;

	/*
	// nVidia SDK implementation
	dVector3 uv, uuv; 
	dVector3 qvec;
	qvec[0] = quat[1];
	qvec[1] = quat[2];
	qvec[2] = quat[3];

	dVector3Cross(qvec,source,uv);
	dVector3Cross(qvec,uv,uuv);

	dVector3Scale(uv,REAL(2.0)*quat[0]);
	dVector3Scale(uuv,REAL(2.0));

	dest[0] = source[0] + uv[0] + uuv[0];
	dest[1] = source[1] + uv[1] + uuv[1];
	dest[2] = source[2] + uv[2] + uuv[2];   
	*/
}

inline void dQuatInvTransform(const dQuaternion& quat,const dVector3& source,dVector3& dest)
{

	dReal norm = quat[0]*quat[0] + quat[1]*quat[1] + quat[2]*quat[2] + quat[3]*quat[3];

	if (norm > REAL(0.0))
	{
		dQuaternion invQuat;
		invQuat[0] =  quat[0] / norm;
		invQuat[1] = -quat[1] / norm;
		invQuat[2] = -quat[2] / norm;
		invQuat[3] = -quat[3] / norm;	
		
		dQuatTransform(invQuat,source,dest);

	}
	else
	{
		// Singular -> return identity
		dVector3Copy(source,dest);
	}
}

inline void dGetEulerAngleFromRot(const dMatrix3& mRot,dReal& rX,dReal& rY,dReal& rZ)
{
	rY = asin(mRot[0 * 4 + 2]);
	if (rY < M_PI /2)
	{
		if (rY > -M_PI /2)
		{
			rX = atan2(-mRot[1*4 + 2], mRot[2*4 + 2]);
			rZ = atan2(-mRot[0*4 + 1], mRot[0*4 + 0]);
		}
		else
		{
			// not unique
			rX = -atan2(mRot[1*4 + 0], mRot[1*4 + 1]);
			rZ = REAL(0.0);
		}
	}
	else
	{
		// not unique
		rX = atan2(mRot[1*4 + 0], mRot[1*4 + 1]);
		rZ = REAL(0.0);
	}
}

inline void dQuatInv(const dQuaternion& source, dQuaternion& dest)
{
	dReal norm = source[0]*source[0] + source[1]*source[1] + source[2]*source[2] + source[3]*source[3];

	if (norm > 0.0f)
	{
		dest[0] = source[0] / norm;
		dest[1] = -source[1] / norm;
		dest[2] = -source[2] / norm;
		dest[3] = -source[3] / norm;	
	}
	else
	{
		// Singular -> return identity
		dest[0] = REAL(1.0);
		dest[1] = REAL(0.0);
		dest[2] = REAL(0.0);
		dest[3] = REAL(0.0);
	}
}


#endif
