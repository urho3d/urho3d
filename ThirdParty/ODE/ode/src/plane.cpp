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

//****************************************************************************
// plane public API

static void make_sure_plane_normal_has_unit_length (dxPlane *g)
{
  dReal l = g->p[0]*g->p[0] + g->p[1]*g->p[1] + g->p[2]*g->p[2];
  if (l > 0) {
    l = dRecipSqrt(l);
    g->p[0] *= l;
    g->p[1] *= l;
    g->p[2] *= l;
    g->p[3] *= l;
  }
  else {
    g->p[0] = 1;
    g->p[1] = 0;
    g->p[2] = 0;
    g->p[3] = 0;
  }
}


dxPlane::dxPlane (dSpaceID space, dReal a, dReal b, dReal c, dReal d) :
  dxGeom (space,0)
{
  type = dPlaneClass;
  p[0] = a;
  p[1] = b;
  p[2] = c;
  p[3] = d;
  make_sure_plane_normal_has_unit_length (this);
}


void dxPlane::computeAABB()
{
	aabb[0] = -dInfinity;
	aabb[1] = dInfinity;
	aabb[2] = -dInfinity;
	aabb[3] = dInfinity;
	aabb[4] = -dInfinity;
	aabb[5] = dInfinity;

	// Planes that have normal vectors aligned along an axis can use a
	// less comprehensive (half space) bounding box.

	if ( p[1] == 0.0f && p[2] == 0.0f ) {
		// normal aligned with x-axis
		aabb[0] = (p[0] > 0) ? -dInfinity : -p[3];
		aabb[1] = (p[0] > 0) ? p[3] : dInfinity;
	} else
	if ( p[0] == 0.0f && p[2] == 0.0f ) {
		// normal aligned with y-axis
		aabb[2] = (p[1] > 0) ? -dInfinity : -p[3];
		aabb[3] = (p[1] > 0) ? p[3] : dInfinity;
	} else
	if ( p[0] == 0.0f && p[1] == 0.0f ) {
		// normal aligned with z-axis
		aabb[4] = (p[2] > 0) ? -dInfinity : -p[3];
		aabb[5] = (p[2] > 0) ? p[3] : dInfinity;
	}
}


dGeomID dCreatePlane (dSpaceID space,
		      dReal a, dReal b, dReal c, dReal d)
{
  return new dxPlane (space,a,b,c,d);
}


void dGeomPlaneSetParams (dGeomID g, dReal a, dReal b, dReal c, dReal d)
{
  dUASSERT (g && g->type == dPlaneClass,"argument not a plane");
  dxPlane *p = (dxPlane*) g;
  p->p[0] = a;
  p->p[1] = b;
  p->p[2] = c;
  p->p[3] = d;
  make_sure_plane_normal_has_unit_length (p);
  dGeomMoved (g);
}


void dGeomPlaneGetParams (dGeomID g, dVector4 result)
{
  dUASSERT (g && g->type == dPlaneClass,"argument not a plane");
  dxPlane *p = (dxPlane*) g;
  result[0] = p->p[0];
  result[1] = p->p[1];
  result[2] = p->p[2];
  result[3] = p->p[3];
}


dReal dGeomPlanePointDepth (dGeomID g, dReal x, dReal y, dReal z)
{
  dUASSERT (g && g->type == dPlaneClass,"argument not a plane");
  dxPlane *p = (dxPlane*) g;
  return p->p[3] - p->p[0]*x - p->p[1]*y - p->p[2]*z;
}
