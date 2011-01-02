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


/*******************************************************************
 *                                                                 *
 * cylinder-sphere collider by Christoph Beyer (boernerb@web.de)   *
 *                                                                 *
 * In Cylinder/Sphere-collisions, there are three possibilies:     *
 * 1. collision with the cylinder's nappe                          *
 * 2. collision with one of the cylinder's disc                    *
 * 3. collision with one of the disc's border                      *
 *                                                                 *
 * This collider computes two distances (s, t) and based on them,  *
 * it decides, which collision we have.                            *
 * This collider always generates 1 (or 0, if we have no collison) *
 * contacts.                                                       *
 * It is able to "separate" cylinder and sphere in all             *
 * configurations, but it never pays attention to velocity.        *
 * So, in extrem situations, "tunneling-effect" is possible.       *
 *                                                                 *
 *******************************************************************/

#include <ode/collision.h>
#include <ode/matrix.h>
#include <ode/rotation.h>
#include <ode/odemath.h>
#include <ode/objects.h>

#include "config.h"
#include "collision_kernel.h"	// for dxGeom
#include "collision_util.h"

int dCollideCylinderSphere(dxGeom* Cylinder, dxGeom* Sphere, 
                           int flags, dContactGeom *contact, int skip)
{
	dIASSERT (skip >= (int)sizeof(dContactGeom));
	dIASSERT (Cylinder->type == dCylinderClass);
	dIASSERT (Sphere->type == dSphereClass);
	dIASSERT ((flags & NUMC_MASK) >= 1);

	//unsigned char* pContactData = (unsigned char*)contact;
	int GeomCount = 0; // count of used contacts

#ifdef dSINGLE
	const dReal toleranz = REAL(0.0001);
#endif
#ifdef dDOUBLE
	const dReal toleranz = REAL(0.0000001);
#endif

	// get the data from the geoms
	dReal radius, length;
	dGeomCylinderGetParams(Cylinder, &radius, &length);
    dVector3 &cylpos = Cylinder->final_posr->pos;
	//const dReal* pfRot1 = dGeomGetRotation(Cylinder);

	dReal radius2;
	radius2 = dGeomSphereGetRadius(Sphere);
	const dReal* SpherePos = dGeomGetPosition(Sphere);

	// G1Pos1 is the middle of the first disc
	// G1Pos2 is the middle of the second disc
	// vDir1 is the unit direction of the cylinderaxis
	dVector3 G1Pos1, G1Pos2, vDir1;
	vDir1[0] = Cylinder->final_posr->R[2];
	vDir1[1] = Cylinder->final_posr->R[6];
	vDir1[2] = Cylinder->final_posr->R[10];

	dReal s;
	s = length * REAL(0.5); // just a precomputed factor
	G1Pos2[0] = vDir1[0] * s + cylpos[0];
	G1Pos2[1] = vDir1[1] * s + cylpos[1];
	G1Pos2[2] = vDir1[2] * s + cylpos[2];

	G1Pos1[0] = vDir1[0] * -s + cylpos[0];
	G1Pos1[1] = vDir1[1] * -s + cylpos[1];
	G1Pos1[2] = vDir1[2] * -s + cylpos[2];

	dVector3 C;
	dReal t;
	// Step 1: compute the two distances 's' and 't'
	// 's' is the distance from the first disc (in vDir1-/Zylinderaxis-direction), the disc with G1Pos1 in the middle
	s = (SpherePos[0] - G1Pos1[0]) * vDir1[0] - (G1Pos1[1] - SpherePos[1]) * vDir1[1] - (G1Pos1[2] - SpherePos[2]) * vDir1[2];
	if(s < (-radius2) || s > (length + radius2) )
	{
		// Sphere is too far away from the discs
		// no collision
		return 0;
	}

	// C is the direction from Sphere-middle to the cylinder-axis (vDir1); C is orthogonal to the cylinder-axis
	C[0] = s * vDir1[0] + G1Pos1[0] - SpherePos[0];
	C[1] = s * vDir1[1] + G1Pos1[1] - SpherePos[1];
	C[2] = s * vDir1[2] + G1Pos1[2] - SpherePos[2];
	// t is the distance from the Sphere-middle to the cylinder-axis!
	t = dVector3Length(C);
	if(t > (radius + radius2) )
	{
		// Sphere is too far away from the cylinder axis!
		// no collision
		return 0;
	}

	// decide which kind of collision we have:
	if(t > radius && (s < 0 || s > length) )
	{
		// 3. collision
		if(s <= 0)
		{
			contact->depth = radius2 - dSqrt( (s) * (s) + (t - radius) * (t - radius) );
			if(contact->depth < 0)
			{
				// no collision!
				return 0;
			}
			contact->pos[0] = C[0] / t * -radius + G1Pos1[0];
			contact->pos[1] = C[1] / t * -radius + G1Pos1[1];
			contact->pos[2] = C[2] / t * -radius + G1Pos1[2];
			contact->normal[0] = (contact->pos[0] - SpherePos[0]) / (radius2 - contact->depth);
			contact->normal[1] = (contact->pos[1] - SpherePos[1]) / (radius2 - contact->depth);
			contact->normal[2] = (contact->pos[2] - SpherePos[2]) / (radius2 - contact->depth);
			contact->g1 = Cylinder;
			contact->g2 = Sphere;
			contact->side1 = -1;
			contact->side2 = -1;
			GeomCount++;
			return GeomCount;
		}
		else
		{
			// now s is bigger than length here!
			contact->depth = radius2 - dSqrt( (s - length) * (s - length) + (t - radius) * (t - radius) );
			if(contact->depth < 0)
			{
				// no collision!
				return 0;
			}
			contact->pos[0] = C[0] / t * -radius + G1Pos2[0];
			contact->pos[1] = C[1] / t * -radius + G1Pos2[1];
			contact->pos[2] = C[2] / t * -radius + G1Pos2[2];
			contact->normal[0] = (contact->pos[0] - SpherePos[0]) / (radius2 - contact->depth);
			contact->normal[1] = (contact->pos[1] - SpherePos[1]) / (radius2 - contact->depth);
			contact->normal[2] = (contact->pos[2] - SpherePos[2]) / (radius2 - contact->depth);
			contact->g1 = Cylinder;
			contact->g2 = Sphere;
			contact->side1 = -1;
			contact->side2 = -1;
			GeomCount++;
			return GeomCount;
		}
	}
	else if( (radius - t) <= s && (radius - t) <= (length - s) )
	{
		// 1. collsision
		if(t > (radius2 + toleranz))
		{
			// cylinder-axis is outside the sphere
			contact->depth = (radius2 + radius) - t;
			if(contact->depth < 0)
			{
				// should never happen, but just for safeness
				return 0;
			}
			else
			{
				C[0] /= t;
				C[1] /= t;
				C[2] /= t;
				contact->pos[0] = C[0] * radius2 + SpherePos[0];
				contact->pos[1] = C[1] * radius2 + SpherePos[1];
				contact->pos[2] = C[2] * radius2 + SpherePos[2];
				contact->normal[0] = C[0];
				contact->normal[1] = C[1];
				contact->normal[2] = C[2];
				contact->g1 = Cylinder;
				contact->g2 = Sphere;
				contact->side1 = -1;
				contact->side2 = -1;
				GeomCount++;
				return GeomCount;
			}
		}
		else
		{
			// cylinder-axis is outside of the sphere
			contact->depth = (radius2 + radius) - t;
			if(contact->depth < 0)
			{
				// should never happen, but just for safeness
				return 0;
			}
			else
			{
				contact->pos[0] = C[0] + SpherePos[0];
				contact->pos[1] = C[1] + SpherePos[1];
				contact->pos[2] = C[2] + SpherePos[2];
				contact->normal[0] = C[0] / t;
				contact->normal[1] = C[1] / t;
				contact->normal[2] = C[2] / t;
				contact->g1 = Cylinder;
				contact->g2 = Sphere;
				contact->side1 = -1;
				contact->side2 = -1;
				GeomCount++;
				return GeomCount;
			}
		}
	}
	else
	{
		// 2. collision
		if(s <= (length * REAL(0.5)) )
		{
			// collsision with the first disc
			contact->depth = s + radius2;
			if(contact->depth < 0)
			{
				// should never happen, but just for safeness
				return 0;
			}
			contact->pos[0] = radius2 * vDir1[0] + SpherePos[0];
			contact->pos[1] = radius2 * vDir1[1] + SpherePos[1];
			contact->pos[2] = radius2 * vDir1[2] + SpherePos[2];
			contact->normal[0] = vDir1[0];
			contact->normal[1] = vDir1[1];
			contact->normal[2] = vDir1[2];
			contact->g1 = Cylinder;
			contact->g2 = Sphere;
			contact->side1 = -1;
			contact->side2 = -1;
			GeomCount++;
			return GeomCount;
		}
		else
		{
			// collsision with the second disc
			contact->depth = (radius2 + length - s);
			if(contact->depth < 0)
			{
				// should never happen, but just for safeness
				return 0;
			}
			contact->pos[0] = radius2 * -vDir1[0] + SpherePos[0];
			contact->pos[1] = radius2 * -vDir1[1] + SpherePos[1];
			contact->pos[2] = radius2 * -vDir1[2] + SpherePos[2];
			contact->normal[0] = -vDir1[0];
			contact->normal[1] = -vDir1[1];
			contact->normal[2] = -vDir1[2];
			contact->g1 = Cylinder;
			contact->g2 = Sphere;
			contact->side1 = -1;
			contact->side2 = -1;
			GeomCount++;
			return GeomCount;
		}
	}
	return GeomCount;
}
