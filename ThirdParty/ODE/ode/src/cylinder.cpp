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

standard ODE geometry primitives: public API and pairwise collision functions.

the rule is that only the low level primitive collision functions should set
dContactGeom::g1 and dContactGeom::g2.

*/

#include <ode/common.h>
#include <ode/collision.h>
#include <ode/matrix.h>
#include <ode/rotation.h>
#include <ode/odemath.h>
#include "config.h"
#include "collision_kernel.h"
#include "collision_std.h"
#include "collision_util.h"

#ifdef _MSC_VER
#pragma warning(disable:4291)  // for VC++, no complaints about "no matching operator delete found"
#endif

// flat cylinder public API

dxCylinder::dxCylinder (dSpaceID space, dReal _radius, dReal _length) :
dxGeom (space,1)
{
	dAASSERT (_radius >= 0 && _length >= 0);
	type = dCylinderClass;
	radius = _radius;
	lz = _length;
	updateZeroSizedFlag(!_radius || !_length);
}


void dxCylinder::computeAABB()
{
    const dMatrix3& R = final_posr->R;
    const dVector3& pos = final_posr->pos;

	dReal xrange = dFabs (R[0] * radius) +	 dFabs (R[1] * radius) + REAL(0.5)* dFabs (R[2] * 
		lz);
	dReal yrange = dFabs (R[4] * radius) +   dFabs (R[5] * radius) + REAL(0.5)* dFabs (R[6] * 
		lz);
	dReal zrange = dFabs (R[8] * radius) +	 dFabs (R[9] * radius) + REAL(0.5)* dFabs (R[10] * 
		lz);
	aabb[0] = pos[0] - xrange;
	aabb[1] = pos[0] + xrange;
	aabb[2] = pos[1] - yrange;
	aabb[3] = pos[1] + yrange;
	aabb[4] = pos[2] - zrange;
	aabb[5] = pos[2] + zrange;
}


dGeomID dCreateCylinder (dSpaceID space, dReal radius, dReal length)
{
	return new dxCylinder (space,radius,length);
}

void dGeomCylinderSetParams (dGeomID cylinder, dReal radius, dReal length)
{
	dUASSERT (cylinder && cylinder->type == dCylinderClass,"argument not a ccylinder");
	dAASSERT (radius >= 0 && length >= 0);
	dxCylinder *c = (dxCylinder*) cylinder;
	c->radius = radius;
	c->lz = length;
	c->updateZeroSizedFlag(!radius || !length);
	dGeomMoved (cylinder);
}

void dGeomCylinderGetParams (dGeomID cylinder, dReal *radius, dReal *length)
{
	dUASSERT (cylinder && cylinder->type == dCylinderClass,"argument not a ccylinder");
	dxCylinder *c = (dxCylinder*) cylinder;
	*radius = c->radius;
	*length = c->lz;
}


