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
// capped cylinder public API

dxCapsule::dxCapsule (dSpaceID space, dReal _radius, dReal _length) :
  dxGeom (space,1)
{
  dAASSERT (_radius >= 0 && _length >= 0);
  type = dCapsuleClass;
  radius = _radius;
  lz = _length;
  updateZeroSizedFlag(!_radius/* || !_length -- zero length capsule is not a zero sized capsule*/);
}


void dxCapsule::computeAABB()
{
  const dMatrix3& R = final_posr->R;
  const dVector3& pos = final_posr->pos;
  
  dReal xrange = dFabs(R[2]  * lz) * REAL(0.5) + radius;
  dReal yrange = dFabs(R[6]  * lz) * REAL(0.5) + radius;
  dReal zrange = dFabs(R[10] * lz) * REAL(0.5) + radius;
  aabb[0] = pos[0] - xrange;
  aabb[1] = pos[0] + xrange;
  aabb[2] = pos[1] - yrange;
  aabb[3] = pos[1] + yrange;
  aabb[4] = pos[2] - zrange;
  aabb[5] = pos[2] + zrange;
}


dGeomID dCreateCapsule (dSpaceID space, dReal radius, dReal length)
{
  return new dxCapsule (space,radius,length);
}


void dGeomCapsuleSetParams (dGeomID g, dReal radius, dReal length)
{
  dUASSERT (g && g->type == dCapsuleClass,"argument not a ccylinder");
  dAASSERT (radius >= 0 && length >= 0);
  dxCapsule *c = (dxCapsule*) g;
  c->radius = radius;
  c->lz = length;
  c->updateZeroSizedFlag(!radius/* || !length -- zero length capsule is not a zero sized capsule*/);
  dGeomMoved (g);
}


void dGeomCapsuleGetParams (dGeomID g, dReal *radius, dReal *length)
{
  dUASSERT (g && g->type == dCapsuleClass,"argument not a ccylinder");
  dxCapsule *c = (dxCapsule*) g;
  *radius = c->radius;
  *length = c->lz;
}


dReal dGeomCapsulePointDepth (dGeomID g, dReal x, dReal y, dReal z)
{
  dUASSERT (g && g->type == dCapsuleClass,"argument not a ccylinder");
  g->recomputePosr();
  dxCapsule *c = (dxCapsule*) g;

  const dReal* R = g->final_posr->R;
  const dReal* pos = g->final_posr->pos;
  
  dVector3 a;
  a[0] = x - pos[0];
  a[1] = y - pos[1];
  a[2] = z - pos[2];
  dReal beta = dCalcVectorDot3_14(a,R+2);
  dReal lz2 = c->lz*REAL(0.5);
  if (beta < -lz2) beta = -lz2;
  else if (beta > lz2) beta = lz2;
  a[0] = c->final_posr->pos[0] + beta*R[0*4+2];
  a[1] = c->final_posr->pos[1] + beta*R[1*4+2];
  a[2] = c->final_posr->pos[2] + beta*R[2*4+2];
  return c->radius -
    dSqrt ((x-a[0])*(x-a[0]) + (y-a[1])*(y-a[1]) + (z-a[2])*(z-a[2]));
}



int dCollideCapsuleSphere (dxGeom *o1, dxGeom *o2, int flags,
			     dContactGeom *contact, int skip)
{
  dIASSERT (skip >= (int)sizeof(dContactGeom));
  dIASSERT (o1->type == dCapsuleClass);
  dIASSERT (o2->type == dSphereClass);
  dIASSERT ((flags & NUMC_MASK) >= 1);
  
  dxCapsule *ccyl = (dxCapsule*) o1;
  dxSphere *sphere = (dxSphere*) o2;

  contact->g1 = o1;
  contact->g2 = o2;
  contact->side1 = -1;
  contact->side2 = -1;

  // find the point on the cylinder axis that is closest to the sphere
  dReal alpha = 
    o1->final_posr->R[2]  * (o2->final_posr->pos[0] - o1->final_posr->pos[0]) +
    o1->final_posr->R[6]  * (o2->final_posr->pos[1] - o1->final_posr->pos[1]) +
    o1->final_posr->R[10] * (o2->final_posr->pos[2] - o1->final_posr->pos[2]);
  dReal lz2 = ccyl->lz * REAL(0.5);
  if (alpha > lz2) alpha = lz2;
  if (alpha < -lz2) alpha = -lz2;

  // collide the spheres
  dVector3 p;
  p[0] = o1->final_posr->pos[0] + alpha * o1->final_posr->R[2];
  p[1] = o1->final_posr->pos[1] + alpha * o1->final_posr->R[6];
  p[2] = o1->final_posr->pos[2] + alpha * o1->final_posr->R[10];
  return dCollideSpheres (p,ccyl->radius,o2->final_posr->pos,sphere->radius,contact);
}

// use this instead of dCollideSpheres if the spheres are at the same point, 
//  but the normal is known (e.g. in capsule-box collision)
int dCollideSpheresZeroDist (dVector3 p1, dReal r1, dVector3 p2, dReal r2, 
                             dVector3 normal, dContactGeom *c) {
  c->normal[0] = normal[0];
  c->normal[1] = normal[1];
  c->normal[2] = normal[2];
  c->depth  = r1 + r2;
  dReal k = REAL(0.5) * (r2 - r1);
  c->pos[0] = p1[0] + c->normal[0]*k;
  c->pos[1] = p1[1] + c->normal[1]*k;
  c->pos[2] = p1[2] + c->normal[2]*k;
  return 1;
}

int dCollideCapsuleBox (dxGeom *o1, dxGeom *o2, int flags,
			  dContactGeom *contact, int skip)
{
  dIASSERT (skip >= (int)sizeof(dContactGeom));
  dIASSERT (o1->type == dCapsuleClass);
  dIASSERT (o2->type == dBoxClass);
  dIASSERT ((flags & NUMC_MASK) >= 1);

  dxCapsule *cyl = (dxCapsule*) o1;
  dxBox *box = (dxBox*) o2;

  contact->g1 = o1;
  contact->g2 = o2;
  contact->side1 = -1;
  contact->side2 = -1;

  // get p1,p2 = cylinder axis endpoints, get radius
  dVector3 p1,p2;
  dReal clen = cyl->lz * REAL(0.5);
  p1[0] = o1->final_posr->pos[0] + clen * o1->final_posr->R[2];
  p1[1] = o1->final_posr->pos[1] + clen * o1->final_posr->R[6];
  p1[2] = o1->final_posr->pos[2] + clen * o1->final_posr->R[10];
  p2[0] = o1->final_posr->pos[0] - clen * o1->final_posr->R[2];
  p2[1] = o1->final_posr->pos[1] - clen * o1->final_posr->R[6];
  p2[2] = o1->final_posr->pos[2] - clen * o1->final_posr->R[10];
  dReal radius = cyl->radius;

  // copy out box center, rotation matrix, and side array
  dReal *c = o2->final_posr->pos;
  dReal *R = o2->final_posr->R;
  const dReal *side = box->side;

  // get the closest point between the cylinder axis and the box
  dVector3 pl,pb;
  dClosestLineBoxPoints (p1,p2,c,R,side,pl,pb);

  // if the capsule is penetrated further than radius 
  //  than pl and pb are equal -> unknown normal
  // use vector to center of box as normal
#ifdef dSINGLE
  dReal mindist = REAL(1e-9);
#else
  dReal mindist = REAL(1e-18);
#endif
  if (dCalcPointsDistance3(pl, pb)<mindist) {
    dVector3 normal; // pb-c (vector from center of box to pb)
    for (int i=0; i<3; i++) normal[i] = pb[i]-c[i];
    dSafeNormalize3(normal);
    return dCollideSpheresZeroDist (pl,radius,pb,0,normal,contact);
  } else {
    // generate contact point
    return dCollideSpheres (pl,radius,pb,0,contact);
  }
}


int dCollideCapsuleCapsule (dxGeom *o1, dxGeom *o2,
				int flags, dContactGeom *contact, int skip)
{
  dIASSERT (skip >= (int)sizeof(dContactGeom));
  dIASSERT (o1->type == dCapsuleClass);
  dIASSERT (o2->type == dCapsuleClass);
  dIASSERT ((flags & NUMC_MASK) >= 1);

  int i;
  const dReal tolerance = REAL(1e-5);

  dxCapsule *cyl1 = (dxCapsule*) o1;
  dxCapsule *cyl2 = (dxCapsule*) o2;

  contact->g1 = o1;
  contact->g2 = o2;
  contact->side1 = -1;
  contact->side2 = -1;

  // copy out some variables, for convenience
  dReal lz1 = cyl1->lz * REAL(0.5);
  dReal lz2 = cyl2->lz * REAL(0.5);
  dReal *pos1 = o1->final_posr->pos;
  dReal *pos2 = o2->final_posr->pos;
  dReal axis1[3],axis2[3];
  axis1[0] = o1->final_posr->R[2];
  axis1[1] = o1->final_posr->R[6];
  axis1[2] = o1->final_posr->R[10];
  axis2[0] = o2->final_posr->R[2];
  axis2[1] = o2->final_posr->R[6];
  axis2[2] = o2->final_posr->R[10];

  // if the cylinder axes are close to parallel, we'll try to detect up to
  // two contact points along the body of the cylinder. if we can't find any
  // points then we'll fall back to the closest-points algorithm. note that
  // we are not treating this special case for reasons of degeneracy, but
  // because we want two contact points in some situations. the closet-points
  // algorithm is robust in all casts, but it can return only one contact.

  dVector3 sphere1,sphere2;
  dReal a1a2 = dCalcVectorDot3 (axis1,axis2);
  dReal det = REAL(1.0)-a1a2*a1a2;
  if (det < tolerance) {
    // the cylinder axes (almost) parallel, so we will generate up to two
    // contacts. alpha1 and alpha2 (line position parameters) are related by:
    //       alpha2 =   alpha1 + (pos1-pos2)'*axis1   (if axis1==axis2)
    //    or alpha2 = -(alpha1 + (pos1-pos2)'*axis1)  (if axis1==-axis2)
    // first compute where the two cylinders overlap in alpha1 space:
    if (a1a2 < 0) {
      axis2[0] = -axis2[0];
      axis2[1] = -axis2[1];
      axis2[2] = -axis2[2];
    }
    dReal q[3];
    for (i=0; i<3; i++) q[i] = pos1[i]-pos2[i];
    dReal k = dCalcVectorDot3 (axis1,q);
    dReal a1lo = -lz1;
    dReal a1hi = lz1;
    dReal a2lo = -lz2 - k;
    dReal a2hi = lz2 - k;
    dReal lo = (a1lo > a2lo) ? a1lo : a2lo;
    dReal hi = (a1hi < a2hi) ? a1hi : a2hi;
    if (lo <= hi) {
      int num_contacts = flags & NUMC_MASK;
      if (num_contacts >= 2 && lo < hi) {
	// generate up to two contacts. if one of those contacts is
	// not made, fall back on the one-contact strategy.
	for (i=0; i<3; i++) sphere1[i] = pos1[i] + lo*axis1[i];
	for (i=0; i<3; i++) sphere2[i] = pos2[i] + (lo+k)*axis2[i];
	int n1 = dCollideSpheres (sphere1,cyl1->radius,
				  sphere2,cyl2->radius,contact);
	if (n1) {
	  for (i=0; i<3; i++) sphere1[i] = pos1[i] + hi*axis1[i];
	  for (i=0; i<3; i++) sphere2[i] = pos2[i] + (hi+k)*axis2[i];
	  dContactGeom *c2 = CONTACT(contact,skip);
	  int n2 = dCollideSpheres (sphere1,cyl1->radius,
				    sphere2,cyl2->radius, c2);
	  if (n2) {
	    c2->g1 = o1;
	    c2->g2 = o2;
		c2->side1 = -1;
		c2->side2 = -1;
	    return 2;
	  }
	}
      }

      // just one contact to generate, so put it in the middle of
      // the range
      dReal alpha1 = (lo + hi) * REAL(0.5);
      dReal alpha2 = alpha1 + k;
      for (i=0; i<3; i++) sphere1[i] = pos1[i] + alpha1*axis1[i];
      for (i=0; i<3; i++) sphere2[i] = pos2[i] + alpha2*axis2[i];
      return dCollideSpheres (sphere1,cyl1->radius,
			      sphere2,cyl2->radius,contact);
    }
  }
	  
  // use the closest point algorithm
  dVector3 a1,a2,b1,b2;
  a1[0] = o1->final_posr->pos[0] + axis1[0]*lz1;
  a1[1] = o1->final_posr->pos[1] + axis1[1]*lz1;
  a1[2] = o1->final_posr->pos[2] + axis1[2]*lz1;
  a2[0] = o1->final_posr->pos[0] - axis1[0]*lz1;
  a2[1] = o1->final_posr->pos[1] - axis1[1]*lz1;
  a2[2] = o1->final_posr->pos[2] - axis1[2]*lz1;
  b1[0] = o2->final_posr->pos[0] + axis2[0]*lz2;
  b1[1] = o2->final_posr->pos[1] + axis2[1]*lz2;
  b1[2] = o2->final_posr->pos[2] + axis2[2]*lz2;
  b2[0] = o2->final_posr->pos[0] - axis2[0]*lz2;
  b2[1] = o2->final_posr->pos[1] - axis2[1]*lz2;
  b2[2] = o2->final_posr->pos[2] - axis2[2]*lz2;

  dClosestLineSegmentPoints (a1,a2,b1,b2,sphere1,sphere2);
  return dCollideSpheres (sphere1,cyl1->radius,sphere2,cyl2->radius,contact);
}


int dCollideCapsulePlane (dxGeom *o1, dxGeom *o2, int flags,
			    dContactGeom *contact, int skip)
{
  dIASSERT (skip >= (int)sizeof(dContactGeom));
  dIASSERT (o1->type == dCapsuleClass);
  dIASSERT (o2->type == dPlaneClass);
  dIASSERT ((flags & NUMC_MASK) >= 1);

  dxCapsule *ccyl = (dxCapsule*) o1;
  dxPlane *plane = (dxPlane*) o2;

  // collide the deepest capping sphere with the plane
  dReal sign = (dCalcVectorDot3_14 (plane->p,o1->final_posr->R+2) > 0) ? REAL(-1.0) : REAL(1.0);
  dVector3 p;
  p[0] = o1->final_posr->pos[0] + o1->final_posr->R[2]  * ccyl->lz * REAL(0.5) * sign;
  p[1] = o1->final_posr->pos[1] + o1->final_posr->R[6]  * ccyl->lz * REAL(0.5) * sign;
  p[2] = o1->final_posr->pos[2] + o1->final_posr->R[10] * ccyl->lz * REAL(0.5) * sign;

  dReal k = dCalcVectorDot3 (p,plane->p);
  dReal depth = plane->p[3] - k + ccyl->radius;
  if (depth < 0) return 0;
  contact->normal[0] = plane->p[0];
  contact->normal[1] = plane->p[1];
  contact->normal[2] = plane->p[2];
  contact->pos[0] = p[0] - plane->p[0] * ccyl->radius;
  contact->pos[1] = p[1] - plane->p[1] * ccyl->radius;
  contact->pos[2] = p[2] - plane->p[2] * ccyl->radius;
  contact->depth = depth;

  int ncontacts = 1;
  if ((flags & NUMC_MASK) >= 2) {
    // collide the other capping sphere with the plane
    p[0] = o1->final_posr->pos[0] - o1->final_posr->R[2]  * ccyl->lz * REAL(0.5) * sign;
    p[1] = o1->final_posr->pos[1] - o1->final_posr->R[6]  * ccyl->lz * REAL(0.5) * sign;
    p[2] = o1->final_posr->pos[2] - o1->final_posr->R[10] * ccyl->lz * REAL(0.5) * sign;

    k = dCalcVectorDot3 (p,plane->p);
    depth = plane->p[3] - k + ccyl->radius;
    if (depth >= 0) {
      dContactGeom *c2 = CONTACT(contact,skip);
      c2->normal[0] = plane->p[0];
      c2->normal[1] = plane->p[1];
      c2->normal[2] = plane->p[2];
      c2->pos[0] = p[0] - plane->p[0] * ccyl->radius;
      c2->pos[1] = p[1] - plane->p[1] * ccyl->radius;
      c2->pos[2] = p[2] - plane->p[2] * ccyl->radius;
      c2->depth = depth;
      ncontacts = 2;
    }
  }

  for (int i=0; i < ncontacts; i++) {
    dContactGeom *currContact = CONTACT(contact,i*skip);
    currContact->g1 = o1;
    currContact->g2 = o2;
	currContact->side1 = -1;
    currContact->side2 = -1;
  }
  return ncontacts;
}

