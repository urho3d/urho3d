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
 * Cylinder-Plane collider by Christoph Beyer ( boernerb@web.de )
 *
 * This testing basically comes down to testing the intersection
 * of the cylinder caps (discs) with the plane.
 * 
 */

#include <ode/collision.h>
#include <ode/matrix.h>
#include <ode/rotation.h>
#include <ode/odemath.h>
#include <ode/objects.h>

#include "config.h"
#include "collision_kernel.h"	// for dxGeom
#include "collision_util.h"


int dCollideCylinderPlane(dxGeom *Cylinder, dxGeom *Plane, int flags, dContactGeom *contact, int skip)
{
	dIASSERT (skip >= (int)sizeof(dContactGeom));
	dIASSERT (Cylinder->type == dCylinderClass);
	dIASSERT (Plane->type == dPlaneClass);
	dIASSERT ((flags & NUMC_MASK) >= 1);

	int GeomCount = 0; // count of used contactgeoms

#ifdef dSINGLE
	const dReal toleranz = REAL(0.0001);
#endif
#ifdef dDOUBLE
	const dReal toleranz = REAL(0.0000001);
#endif

	// Get the properties of the cylinder (length+radius)
	dReal radius, length;
	dGeomCylinderGetParams(Cylinder, &radius, &length);
	dVector3 &cylpos = Cylinder->final_posr->pos;
	// and the plane
	dVector4 planevec;
	dGeomPlaneGetParams(Plane, planevec);
	dVector3 PlaneNormal = {planevec[0],planevec[1],planevec[2]};
	//dVector3 PlanePos = {planevec[0] * planevec[3],planevec[1] * planevec[3],planevec[2] * planevec[3]};

	dVector3 G1Pos1, G1Pos2, vDir1;
	vDir1[0] = Cylinder->final_posr->R[2];
	vDir1[1] = Cylinder->final_posr->R[6];
	vDir1[2] = Cylinder->final_posr->R[10];

	dReal s;
	s = length * REAL(0.5);
	G1Pos2[0] = vDir1[0] * s + cylpos[0];
	G1Pos2[1] = vDir1[1] * s + cylpos[1];
	G1Pos2[2] = vDir1[2] * s + cylpos[2];

	G1Pos1[0] = vDir1[0] * -s + cylpos[0];
	G1Pos1[1] = vDir1[1] * -s + cylpos[1];
	G1Pos1[2] = vDir1[2] * -s + cylpos[2];

	dVector3 C;

	// parallel-check
	s = vDir1[0] * PlaneNormal[0] + vDir1[1] * PlaneNormal[1] + vDir1[2] * PlaneNormal[2];
	if(s < 0)
		s += REAL(1.0); // is ca. 0, if vDir1 and PlaneNormal are parallel
	else
		s -= REAL(1.0); // is ca. 0, if vDir1 and PlaneNormal are parallel
	if(s < toleranz && s > (-toleranz))
	{
		// discs are parallel to the plane

		// 1.compute if, and where contacts are
		dVector3 P;
		s = planevec[3] - dVector3Dot(planevec, G1Pos1);
		dReal t;
		t = planevec[3] - dVector3Dot(planevec, G1Pos2);
		if(s >= t) // s == t does never happen, 
		{
			if(s >= 0)
			{
				// 1. Disc
				dVector3Copy(G1Pos1, P);
			}
			else
				return GeomCount; // no contacts
		}
		else
		{
			if(t >= 0)
			{
				// 2. Disc
				dVector3Copy(G1Pos2, P);
			}
			else
				return GeomCount; // no contacts
		}

		// 2. generate a coordinate-system on the disc
		dVector3 V1, V2;
		if(vDir1[0] < toleranz && vDir1[0] > (-toleranz))
		{
			// not x-axis
			V1[0] = vDir1[0] + REAL(1.0); // random value
			V1[1] = vDir1[1];
			V1[2] = vDir1[2];
		}
		else
		{
			// maybe x-axis
			V1[0] = vDir1[0];
			V1[1] = vDir1[1] + REAL(1.0); // random value
			V1[2] = vDir1[2];
		}
		// V1 is now another direction than vDir1
		// Cross-product
	    dVector3Cross(V1, vDir1, V2);
		// make unit V2
		t = dVector3Length(V2);
		t = radius / t;
		dVector3Scale(V2, t);
		// cross again
		dVector3Cross(V2, vDir1, V1);
		// |V2| is 'radius' and vDir1 unit, so |V1| is 'radius'
		// V1 = first axis
		// V2 = second axis

		// 3. generate contactpoints

		// Potential contact 1
		dVector3Add(P, V1, contact->pos);
		contact->depth = planevec[3] - dVector3Dot(planevec, contact->pos);
		if(contact->depth > 0)
		{
			dVector3Copy(PlaneNormal, contact->normal);
			contact->g1 = Cylinder;
			contact->g2 = Plane;
			contact->side1 = -1;
			contact->side2 = -1;
			GeomCount++;
			if( GeomCount >= (flags & NUMC_MASK))
				return GeomCount; // enough contactgeoms
			contact = (dContactGeom *)((char *)contact + skip);
		}

		// Potential contact 2
		dVector3Subtract(P, V1, contact->pos);
		contact->depth = planevec[3] - dVector3Dot(planevec, contact->pos);
		if(contact->depth > 0)
		{
			dVector3Copy(PlaneNormal, contact->normal);
			contact->g1 = Cylinder;
			contact->g2 = Plane;
			contact->side1 = -1;
			contact->side2 = -1;
			GeomCount++;
			if( GeomCount >= (flags & NUMC_MASK))
				return GeomCount; // enough contactgeoms
			contact = (dContactGeom *)((char *)contact + skip);
		}

		// Potential contact 3
		dVector3Add(P, V2, contact->pos);
		contact->depth = planevec[3] - dVector3Dot(planevec, contact->pos);
		if(contact->depth > 0)
		{
			dVector3Copy(PlaneNormal, contact->normal);
			contact->g1 = Cylinder;
			contact->g2 = Plane;
			contact->side1 = -1;
			contact->side2 = -1;
			GeomCount++;
			if( GeomCount >= (flags & NUMC_MASK))
				return GeomCount; // enough contactgeoms
			contact = (dContactGeom *)((char *)contact + skip);
		}

		// Potential contact 4
		dVector3Subtract(P, V2, contact->pos);
		contact->depth = planevec[3] - dVector3Dot(planevec, contact->pos);
		if(contact->depth > 0)
		{
			dVector3Copy(PlaneNormal, contact->normal);
			contact->g1 = Cylinder;
			contact->g2 = Plane;
			contact->side1 = -1;
			contact->side2 = -1;
			GeomCount++;
			if( GeomCount >= (flags & NUMC_MASK))
				return GeomCount; // enough contactgeoms
			contact = (dContactGeom *)((char *)contact + skip);
		}
	}
	else
	{
		dReal t = dVector3Dot(PlaneNormal, vDir1);
		C[0] = vDir1[0] * t - PlaneNormal[0];
		C[1] = vDir1[1] * t - PlaneNormal[1];
		C[2] = vDir1[2] * t - PlaneNormal[2];
		s = dVector3Length(C);
		// move C onto the circle
		s = radius / s;
		dVector3Scale(C, s);

		// deepest point of disc 1
		dVector3Add(C, G1Pos1, contact->pos);

		// depth of the deepest point
		contact->depth = planevec[3] - dVector3Dot(planevec, contact->pos);
		if(contact->depth >= 0)
		{
			dVector3Copy(PlaneNormal, contact->normal);
			contact->g1 = Cylinder;
			contact->g2 = Plane;
			contact->side1 = -1;
			contact->side2 = -1;
			GeomCount++;
			if( GeomCount >= (flags & NUMC_MASK))
				return GeomCount; // enough contactgeoms
			contact = (dContactGeom *)((char *)contact + skip);
		}

		// C is still computed

		// deepest point of disc 2
		dVector3Add(C, G1Pos2, contact->pos);

		// depth of the deepest point
		contact->depth = planevec[3] - planevec[0] * contact->pos[0] - planevec[1] * contact->pos[1] - planevec[2] * contact->pos[2];
		if(contact->depth >= 0)
		{
			dVector3Copy(PlaneNormal, contact->normal);
			contact->g1 = Cylinder;
			contact->g2 = Plane;
			contact->side1 = -1;
			contact->side2 = -1;
			GeomCount++;
			if( GeomCount >= (flags & NUMC_MASK))
				return GeomCount; // enough contactgeoms
			contact = (dContactGeom *)((char *)contact + skip);
		}
	}
	return GeomCount;
}
