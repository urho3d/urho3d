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

core collision functions and data structures, plus part of the public API
for geometry objects

*/

#include <ode/common.h>
#include <ode/matrix.h>
#include <ode/rotation.h>
#include <ode/objects.h>
#include <ode/odemath.h>
#include "config.h"
#include "collision_kernel.h"
#include "collision_util.h"
#include "collision_std.h"
#include "collision_transform.h"
#include "collision_trimesh_internal.h"
#include "collision_space_internal.h"
#include "odeou.h"

#ifdef dLIBCCD_ENABLED
# include "collision_libccd.h"
#endif /* dLIBCCD_ENABLED */


#ifdef _MSC_VER
#pragma warning(disable:4291)  // for VC++, no complaints about "no matching operator delete found"
#endif

//****************************************************************************
// helper functions for dCollide()ing a space with another geom

// this struct records the parameters passed to dCollideSpaceGeom()

#if dATOMICS_ENABLED 
static volatile atomicptr s_cachedPosR = 0; // dxPosR *
#endif // dATOMICS_ENABLED

static inline dxPosR* dAllocPosr()
{
	dxPosR *retPosR;

#if dATOMICS_ENABLED
	retPosR = (dxPosR *)AtomicExchangePointer(&s_cachedPosR, NULL);

	if (!retPosR)
#endif
	{
		retPosR = (dxPosR*) dAlloc (sizeof(dxPosR));
	}

	return retPosR;
}

static inline void dFreePosr(dxPosR *oldPosR)
{
#if dATOMICS_ENABLED
	if (!AtomicCompareExchangePointer(&s_cachedPosR, NULL, (atomicptr)oldPosR))
#endif
	{
		dFree(oldPosR, sizeof(dxPosR));
	}
}

/*extern */void dClearPosrCache(void)
{
#if dATOMICS_ENABLED
	// No threads should be accessing ODE at this time already,
	// hence variable may be read directly.
	dxPosR *existingPosR = (dxPosR *)s_cachedPosR;

	if (existingPosR)
	{
		dFree(existingPosR, sizeof(dxPosR));

		s_cachedPosR = 0;
	}
#endif
}

struct SpaceGeomColliderData {
  int flags;			// space left in contacts array
  dContactGeom *contact;
  int skip;
};


static void space_geom_collider (void *data, dxGeom *o1, dxGeom *o2)
{
  SpaceGeomColliderData *d = (SpaceGeomColliderData*) data;
  if (d->flags & NUMC_MASK) {
    int n = dCollide (o1,o2,d->flags,d->contact,d->skip);
    d->contact = CONTACT (d->contact,d->skip*n);
    d->flags -= n;
  }
}


static int dCollideSpaceGeom (dxGeom *o1, dxGeom *o2, int flags,
			      dContactGeom *contact, int skip)
{
  SpaceGeomColliderData data;
  data.flags = flags;
  data.contact = contact;
  data.skip = skip;
  dSpaceCollide2 (o1,o2,&data,&space_geom_collider);
  return (flags & NUMC_MASK) - (data.flags & NUMC_MASK);
}

//****************************************************************************
// dispatcher for the N^2 collider functions

// function pointers and modes for n^2 class collider functions

struct dColliderEntry {
  dColliderFn *fn;	// collider function, 0 = no function available
  int reverse;		// 1 = reverse o1 and o2
};
static dColliderEntry colliders[dGeomNumClasses][dGeomNumClasses];
static int colliders_initialized = 0;


// setCollider() will refuse to write over a collider entry once it has
// been written.

static void setCollider (int i, int j, dColliderFn *fn)
{
  if (colliders[i][j].fn == 0) {
    colliders[i][j].fn = fn;
    colliders[i][j].reverse = 0;
  }
  if (colliders[j][i].fn == 0) {
    colliders[j][i].fn = fn;
    colliders[j][i].reverse = 1;
  }
}


static void setAllColliders (int i, dColliderFn *fn)
{
  for (int j=0; j<dGeomNumClasses; j++) setCollider (i,j,fn);
}

/*extern */void dInitColliders()
{
  dIASSERT(!colliders_initialized);
  colliders_initialized = 1;

  memset (colliders,0,sizeof(colliders));

  int i,j;

  // setup space colliders
  for (i=dFirstSpaceClass; i <= dLastSpaceClass; i++) {
    for (j=0; j < dGeomNumClasses; j++) {
      setCollider (i,j,&dCollideSpaceGeom);
    }
  }

  setCollider (dSphereClass,dSphereClass,&dCollideSphereSphere);
  setCollider (dSphereClass,dBoxClass,&dCollideSphereBox);
  setCollider (dSphereClass,dPlaneClass,&dCollideSpherePlane);
  setCollider (dBoxClass,dBoxClass,&dCollideBoxBox);
  setCollider (dBoxClass,dPlaneClass,&dCollideBoxPlane);
  setCollider (dCapsuleClass,dSphereClass,&dCollideCapsuleSphere);
  setCollider (dCapsuleClass,dBoxClass,&dCollideCapsuleBox);
  setCollider (dCapsuleClass,dCapsuleClass,&dCollideCapsuleCapsule);
  setCollider (dCapsuleClass,dPlaneClass,&dCollideCapsulePlane);
  setCollider (dRayClass,dSphereClass,&dCollideRaySphere);
  setCollider (dRayClass,dBoxClass,&dCollideRayBox);
  setCollider (dRayClass,dCapsuleClass,&dCollideRayCapsule);
  setCollider (dRayClass,dPlaneClass,&dCollideRayPlane);
  setCollider (dRayClass,dCylinderClass,&dCollideRayCylinder);
#if dTRIMESH_ENABLED
  setCollider (dTriMeshClass,dSphereClass,&dCollideSTL);
  setCollider (dTriMeshClass,dBoxClass,&dCollideBTL);
  setCollider (dTriMeshClass,dRayClass,&dCollideRTL);
  setCollider (dTriMeshClass,dTriMeshClass,&dCollideTTL);
  setCollider (dTriMeshClass,dCapsuleClass,&dCollideCCTL);
  setCollider (dTriMeshClass,dPlaneClass,&dCollideTrimeshPlane);
  setCollider (dCylinderClass,dTriMeshClass,&dCollideCylinderTrimesh);
#endif

#ifdef dLIBCCD_BOX_CYL
  setCollider (dBoxClass,dCylinderClass,&dCollideBoxCylinderCCD);
#else
  setCollider (dCylinderClass,dBoxClass,&dCollideCylinderBox);
#endif
  setCollider (dCylinderClass,dSphereClass,&dCollideCylinderSphere);
  setCollider (dCylinderClass,dPlaneClass,&dCollideCylinderPlane);

#ifdef dLIBCCD_CYL_CYL
  setCollider (dCylinderClass, dCylinderClass, &dCollideCylinderCylinder);
#endif
#ifdef dLIBCCD_CAP_CYL
  setCollider (dCapsuleClass, dCylinderClass, &dCollideCapsuleCylinder);
#endif

//--> Convex Collision
#ifdef dLIBCCD_CONVEX_BOX
  setCollider (dConvexClass, dBoxClass, &dCollideConvexBoxCCD);
#else
  setCollider (dConvexClass,dBoxClass,&dCollideConvexBox);
#endif

#ifdef dLIBCCD_CONVEX_CAP
  setCollider (dConvexClass,dCapsuleClass,&dCollideConvexCapsuleCCD);
#else
  setCollider (dConvexClass,dCapsuleClass,&dCollideConvexCapsule);
#endif

#ifdef dLIBCCD_CONVEX_CYL
  setCollider (dConvexClass,dCylinderClass,&dCollideConvexCylinderCCD);
#endif

#ifdef dLIBCCD_CONVEX_SPHERE
  setCollider (dConvexClass,dSphereClass,&dCollideConvexSphereCCD);
#else
  setCollider (dSphereClass,dConvexClass,&dCollideSphereConvex);
#endif

#ifdef dLIBCCD_CONVEX_CONVEX
  setCollider (dConvexClass,dConvexClass,&dCollideConvexConvexCCD);
#else
  setCollider (dConvexClass,dConvexClass,&dCollideConvexConvex);
#endif

  setCollider (dConvexClass,dPlaneClass,&dCollideConvexPlane);
  setCollider (dRayClass,dConvexClass,&dCollideRayConvex);
//<-- Convex Collision

//--> dHeightfield Collision
  setCollider (dHeightfieldClass,dRayClass,&dCollideHeightfield);
  setCollider (dHeightfieldClass,dSphereClass,&dCollideHeightfield);
  setCollider (dHeightfieldClass,dBoxClass,&dCollideHeightfield);
  setCollider (dHeightfieldClass,dCapsuleClass,&dCollideHeightfield);
  setCollider (dHeightfieldClass,dCylinderClass,&dCollideHeightfield);
  setCollider (dHeightfieldClass,dConvexClass,&dCollideHeightfield);
#if dTRIMESH_ENABLED
  setCollider (dHeightfieldClass,dTriMeshClass,&dCollideHeightfield);
#endif
//<-- dHeightfield Collision

  setAllColliders (dGeomTransformClass,&dCollideTransform);
}

/*extern */void dFinitColliders()
{
	colliders_initialized = 0;
}

void dSetColliderOverride (int i, int j, dColliderFn *fn)
{
	dIASSERT( colliders_initialized );
	dAASSERT( i < dGeomNumClasses );
	dAASSERT( j < dGeomNumClasses );

	colliders[i][j].fn = fn;
	colliders[i][j].reverse = 0;
	colliders[j][i].fn = fn;
	colliders[j][i].reverse = 1;
}

/*
 *	NOTE!
 *	If it is necessary to add special processing mode without contact generation
 *	use NULL contact parameter value as indicator, not zero in flags.
 */
int dCollide (dxGeom *o1, dxGeom *o2, int flags, dContactGeom *contact,
	      int skip)
{
  dAASSERT(o1 && o2 && contact);
  dUASSERT(colliders_initialized,"Please call ODE initialization (dInitODE() or similar) before using the library");
  dUASSERT(o1->type >= 0 && o1->type < dGeomNumClasses,"bad o1 class number");
  dUASSERT(o2->type >= 0 && o2->type < dGeomNumClasses,"bad o2 class number");
  // Even though comparison for greater or equal to one is used in all the 
  // other places, here it is more logical to check for greater than zero
  // because function does not require any specific number of contact slots - 
  // it must be just a positive.
  dUASSERT((flags & NUMC_MASK) > 0, "no contacts requested"); 

  // Extra precaution for zero contact count in parameters
  if ((flags & NUMC_MASK) == 0) return 0;
  // no contacts if both geoms are the same
  if (o1 == o2) return 0;

  // no contacts if both geoms on the same body, and the body is not 0
  if (o1->body == o2->body && o1->body) return 0;

  o1->recomputePosr();
  o2->recomputePosr();

  dColliderEntry *ce = &colliders[o1->type][o2->type];
  int count = 0;
  if (ce->fn) {
    if (ce->reverse) {
      count = (*ce->fn) (o2,o1,flags,contact,skip);
      for (int i=0; i<count; i++) {
	dContactGeom *c = CONTACT(contact,skip*i);
	c->normal[0] = -c->normal[0];
	c->normal[1] = -c->normal[1];
	c->normal[2] = -c->normal[2];
	dxGeom *tmp = c->g1;
	c->g1 = c->g2;
	c->g2 = tmp;
	int tmpint = c->side1;
	c->side1 = c->side2;
	c->side2 = tmpint;
      }
    }
    else {
      count = (*ce->fn) (o1,o2,flags,contact,skip);
    }
  }
  return count;
}

//****************************************************************************
// dxGeom

dxGeom::dxGeom (dSpaceID _space, int is_placeable)
{
  // setup body vars. invalid type of -1 must be changed by the constructor.
  type = -1;
  gflags = GEOM_DIRTY | GEOM_AABB_BAD | GEOM_ENABLED;
  if (is_placeable) gflags |= GEOM_PLACEABLE;
  data = 0;
  body = 0;
  body_next = 0;
  if (is_placeable) {
	final_posr = dAllocPosr();
    dSetZero (final_posr->pos,4);
    dRSetIdentity (final_posr->R);
  }
  else {
    final_posr = 0;
  }
  offset_posr = 0;

  // setup space vars
  next = 0;
  tome = 0;
  parent_space = 0;
  dSetZero (aabb,6);
  category_bits = ~0;
  collide_bits = ~0;

  // put this geom in a space if required
  if (_space) dSpaceAdd (_space,this);
}


dxGeom::~dxGeom()
{
   if (parent_space) dSpaceRemove (parent_space,this);
   if ((gflags & GEOM_PLACEABLE) && (!body || (body && offset_posr)))
     dFreePosr(final_posr);
   if (offset_posr) dFreePosr(offset_posr);
   bodyRemove();
}

unsigned dxGeom::getParentSpaceTLSKind() const
{
  return parent_space ? parent_space->tls_kind : dSPACE_TLS_KIND_INIT_VALUE;
}

int dxGeom::AABBTest (dxGeom *o, dReal aabb[6])
{
  return 1;
}


void dxGeom::bodyRemove()
{
  if (body) {
    // delete this geom from body list
    dxGeom **last = &body->geom, *g = body->geom;
    while (g) {
      if (g == this) {
        *last = g->body_next;
        break;
      }
      last = &g->body_next;
      g = g->body_next;
    }
    body = 0;
    body_next = 0;
  }
}

inline void myswap(dReal& a, dReal& b) { dReal t=b; b=a; a=t; }


inline void matrixInvert(const dMatrix3& inMat, dMatrix3& outMat)
{
	memcpy(outMat, inMat, sizeof(dMatrix3));
	// swap _12 and _21
	myswap(outMat[0 + 4*1], outMat[1 + 4*0]);
	// swap _31 and _13
	myswap(outMat[2 + 4*0], outMat[0 + 4*2]);
	// swap _23 and _32
	myswap(outMat[1 + 4*2], outMat[2 + 4*1]);
}

void getBodyPosr(const dxPosR& offset_posr, const dxPosR& final_posr, dxPosR& body_posr)
{
	dMatrix3 inv_offset;
	matrixInvert(offset_posr.R, inv_offset);

	dMultiply0_333(body_posr.R, final_posr.R, inv_offset);
	dVector3 world_offset;
	dMultiply0_331(world_offset, body_posr.R, offset_posr.pos);
	body_posr.pos[0] = final_posr.pos[0] - world_offset[0];
	body_posr.pos[1] = final_posr.pos[1] - world_offset[1];
	body_posr.pos[2] = final_posr.pos[2] - world_offset[2];
}

void getWorldOffsetPosr(const dxPosR& body_posr, const dxPosR& world_posr, dxPosR& offset_posr)
{
	dMatrix3 inv_body;
	matrixInvert(body_posr.R, inv_body);

	dMultiply0_333(offset_posr.R, inv_body, world_posr.R);
	dVector3 world_offset;
	world_offset[0] = world_posr.pos[0] - body_posr.pos[0];
	world_offset[1] = world_posr.pos[1] - body_posr.pos[1];
	world_offset[2] = world_posr.pos[2] - body_posr.pos[2];
	dMultiply0_331(offset_posr.pos, inv_body, world_offset);
}

void dxGeom::computePosr()
{
  // should only be recalced if we need to - ie offset from a body
  dIASSERT(offset_posr);  
  dIASSERT(body);
  
  dMultiply0_331 (final_posr->pos,body->posr.R,offset_posr->pos);
  final_posr->pos[0] += body->posr.pos[0];
  final_posr->pos[1] += body->posr.pos[1];
  final_posr->pos[2] += body->posr.pos[2];
  dMultiply0_333 (final_posr->R,body->posr.R,offset_posr->R);
}

 bool dxGeom::controlGeometry(int controlClass, int controlCode, void *dataValue, int *dataSize)
 {
   dAASSERT(false && "Control class/code is not supported for current geom");

   *dataSize = 0;
   return false;
 }

//****************************************************************************
// misc

dxGeom *dGeomGetBodyNext (dxGeom *geom)
{
  return geom->body_next;
}

//****************************************************************************
// public API for geometry objects

void dGeomDestroy (dxGeom *g)
{
  dAASSERT (g);
  delete g;
}


void dGeomSetData (dxGeom *g, void *data)
{
  dAASSERT (g);
  g->data = data;
}


void *dGeomGetData (dxGeom *g)
{
  dAASSERT (g);
  return g->data;
}


void dGeomSetBody (dxGeom *g, dxBody *b)
{
  dAASSERT (g);
  dUASSERT (b == NULL || (g->gflags & GEOM_PLACEABLE),"geom must be placeable");
  CHECK_NOT_LOCKED (g->parent_space);

  if (b) {
    if (!g->body) dFreePosr(g->final_posr);
    if (g->body != b) {
      if (g->offset_posr) {
        dFreePosr(g->offset_posr);
        g->offset_posr = 0;
      }
      g->final_posr = &b->posr;
      g->bodyRemove();
      g->bodyAdd (b);
    }
    dGeomMoved (g);
  }
  else {
    if (g->body) {
      if (g->offset_posr)
      {
        // if we're offset, we already have our own final position, make sure its updated
        g->recomputePosr();
        dFreePosr(g->offset_posr);
        g->offset_posr = 0;
      }
      else
      {
        g->final_posr = dAllocPosr();
        memcpy (g->final_posr->pos,g->body->posr.pos,sizeof(dVector3));
        memcpy (g->final_posr->R,g->body->posr.R,sizeof(dMatrix3));
      }
      g->bodyRemove();
    }
    // dGeomMoved() should not be called if the body is being set to 0, as the
    // new position of the geom is set to the old position of the body, so the
    // effective position of the geom remains unchanged.
  }
}


dBodyID dGeomGetBody (dxGeom *g)
{
  dAASSERT (g);
  return g->body;
}


void dGeomSetPosition (dxGeom *g, dReal x, dReal y, dReal z)
{
  dAASSERT (g);
  dUASSERT (g->gflags & GEOM_PLACEABLE,"geom must be placeable");
  CHECK_NOT_LOCKED (g->parent_space);
  if (g->offset_posr) {
    // move body such that body+offset = position
	dVector3 world_offset;
	dMultiply0_331(world_offset, g->body->posr.R, g->offset_posr->pos);
	dBodySetPosition(g->body,
	    x - world_offset[0],
	    y - world_offset[1],
	    z - world_offset[2]);
  }
  else if (g->body) {
    // this will call dGeomMoved (g), so we don't have to
    dBodySetPosition (g->body,x,y,z);
  }
  else {
    g->final_posr->pos[0] = x;
    g->final_posr->pos[1] = y;
    g->final_posr->pos[2] = z;
    dGeomMoved (g);
  }
}


void dGeomSetRotation (dxGeom *g, const dMatrix3 R)
{
  dAASSERT (g && R);
  dUASSERT (g->gflags & GEOM_PLACEABLE,"geom must be placeable");
  CHECK_NOT_LOCKED (g->parent_space);
  if (g->offset_posr) {
    g->recomputePosr();
    // move body such that body+offset = rotation
    dxPosR new_final_posr;
    dxPosR new_body_posr;
    memcpy(new_final_posr.pos, g->final_posr->pos, sizeof(dVector3));
    memcpy(new_final_posr.R, R, sizeof(dMatrix3));
    getBodyPosr(*g->offset_posr, new_final_posr, new_body_posr);
    dBodySetRotation(g->body, new_body_posr.R);
    dBodySetPosition(g->body, new_body_posr.pos[0], new_body_posr.pos[1], new_body_posr.pos[2]);
  }
  else if (g->body) {
    // this will call dGeomMoved (g), so we don't have to
    dBodySetRotation (g->body,R);
  }
  else {
    memcpy (g->final_posr->R,R,sizeof(dMatrix3));
    dGeomMoved (g);
  }
}


void dGeomSetQuaternion (dxGeom *g, const dQuaternion quat)
{
  dAASSERT (g && quat);
  dUASSERT (g->gflags & GEOM_PLACEABLE,"geom must be placeable");
  CHECK_NOT_LOCKED (g->parent_space);
  if (g->offset_posr) {
    g->recomputePosr();
    // move body such that body+offset = rotation
    dxPosR new_final_posr;
    dxPosR new_body_posr;
    dQtoR (quat, new_final_posr.R);
    memcpy(new_final_posr.pos, g->final_posr->pos, sizeof(dVector3));
    
    getBodyPosr(*g->offset_posr, new_final_posr, new_body_posr);
    dBodySetRotation(g->body, new_body_posr.R);
    dBodySetPosition(g->body, new_body_posr.pos[0], new_body_posr.pos[1], new_body_posr.pos[2]);
  }
  if (g->body) {
    // this will call dGeomMoved (g), so we don't have to
    dBodySetQuaternion (g->body,quat);
  }
  else {
    dQtoR (quat, g->final_posr->R);
    dGeomMoved (g);
  }
}


const dReal * dGeomGetPosition (dxGeom *g)
{
  dAASSERT (g);
  dUASSERT (g->gflags & GEOM_PLACEABLE,"geom must be placeable");
  g->recomputePosr();
  return g->final_posr->pos;
}


void dGeomCopyPosition(dxGeom *g, dVector3 pos)
{
  dAASSERT (g);
  dUASSERT (g->gflags & GEOM_PLACEABLE,"geom must be placeable");
  g->recomputePosr();
  const dReal* src = g->final_posr->pos;
  pos[0] = src[0];
  pos[1] = src[1];
  pos[2] = src[2];
}


const dReal * dGeomGetRotation (dxGeom *g)
{
  dAASSERT (g);
  dUASSERT (g->gflags & GEOM_PLACEABLE,"geom must be placeable");
  g->recomputePosr();
  return g->final_posr->R;
}


void dGeomCopyRotation(dxGeom *g, dMatrix3 R)
{
  dAASSERT (g);
  dUASSERT (g->gflags & GEOM_PLACEABLE,"geom must be placeable");
  g->recomputePosr();
  const dReal* src = g->final_posr->R;
  R[0]  = src[0];
  R[1]  = src[1];
  R[2]  = src[2];
  R[4]  = src[4];
  R[5]  = src[5];
  R[6]  = src[6];
  R[8]  = src[8];
  R[9]  = src[9];
  R[10] = src[10];
}


void dGeomGetQuaternion (dxGeom *g, dQuaternion quat)
{
  dAASSERT (g);
  dUASSERT (g->gflags & GEOM_PLACEABLE,"geom must be placeable");
  if (g->body && !g->offset_posr) {
    const dReal * body_quat = dBodyGetQuaternion (g->body);
    quat[0] = body_quat[0];
    quat[1] = body_quat[1];
    quat[2] = body_quat[2];
    quat[3] = body_quat[3];
  }
  else {
    g->recomputePosr();
    dRtoQ (g->final_posr->R, quat);
  }
}


void dGeomGetAABB (dxGeom *g, dReal aabb[6])
{
  dAASSERT (g);
  dAASSERT (aabb);
  g->recomputeAABB();
  memcpy (aabb,g->aabb,6 * sizeof(dReal));
}


int dGeomIsSpace (dxGeom *g)
{
  dAASSERT (g);
  return IS_SPACE(g);
}


dSpaceID dGeomGetSpace (dxGeom *g)
{
  dAASSERT (g);
  return g->parent_space;
}


int dGeomGetClass (dxGeom *g)
{
  dAASSERT (g);
  return g->type;
}


void dGeomSetCategoryBits (dxGeom *g, unsigned long bits)
{
  dAASSERT (g);
  CHECK_NOT_LOCKED (g->parent_space);
  g->category_bits = bits;
}


void dGeomSetCollideBits (dxGeom *g, unsigned long bits)
{
  dAASSERT (g);
  CHECK_NOT_LOCKED (g->parent_space);
  g->collide_bits = bits;
}


unsigned long dGeomGetCategoryBits (dxGeom *g)
{
  dAASSERT (g);
  return g->category_bits;
}


unsigned long dGeomGetCollideBits (dxGeom *g)
{
  dAASSERT (g);
  return g->collide_bits;
}


void dGeomEnable (dxGeom *g)
{
	dAASSERT (g);
	g->gflags |= GEOM_ENABLED;
}

void dGeomDisable (dxGeom *g)
{
	dAASSERT (g);
	g->gflags &= ~GEOM_ENABLED;
}

int dGeomIsEnabled (dxGeom *g)
{
	dAASSERT (g);
	return (g->gflags & GEOM_ENABLED) != 0;
}


void dGeomGetRelPointPos (dGeomID g, dReal px, dReal py, dReal pz,
                          dVector3 result)
{
  dAASSERT (g);

  if ((g->gflags & GEOM_PLACEABLE) == 0) {
    result[0] = px;
    result[1] = py;
    result[2] = pz;
    return;
  }
  
  g->recomputePosr();
  
  dVector3 prel,p;
  prel[0] = px;
  prel[1] = py;
  prel[2] = pz;
  prel[3] = 0;
  dMultiply0_331 (p,g->final_posr->R,prel);
  result[0] = p[0] + g->final_posr->pos[0];
  result[1] = p[1] + g->final_posr->pos[1];
  result[2] = p[2] + g->final_posr->pos[2];
}


void dGeomGetPosRelPoint (dGeomID g, dReal px, dReal py, dReal pz,
			  dVector3 result)
{
  dAASSERT (g);
  if ((g->gflags & GEOM_PLACEABLE) == 0) {
    result[0] = px;
    result[1] = py;
    result[2] = pz;
    return;
  }

  g->recomputePosr();
  
  dVector3 prel;
  prel[0] = px - g->final_posr->pos[0];
  prel[1] = py - g->final_posr->pos[1];
  prel[2] = pz - g->final_posr->pos[2];
  prel[3] = 0;
  dMultiply1_331 (result,g->final_posr->R,prel);
}


void dGeomVectorToWorld (dGeomID g, dReal px, dReal py, dReal pz,
			 dVector3 result)
{
  dAASSERT (g);
  if ((g->gflags & GEOM_PLACEABLE) == 0) {
    result[0] = px;
    result[1] = py;
    result[2] = pz;
    return;
  }

  g->recomputePosr();
  
  dVector3 p;
  p[0] = px;
  p[1] = py;
  p[2] = pz;
  p[3] = 0;
  dMultiply0_331 (result,g->final_posr->R,p);
}


void dGeomVectorFromWorld (dGeomID g, dReal px, dReal py, dReal pz,
			   dVector3 result)
{
  dAASSERT (g);
  if ((g->gflags & GEOM_PLACEABLE) == 0) {
    result[0] = px;
    result[1] = py;
    result[2] = pz;
    return;
  }

  g->recomputePosr();
  
  dVector3 p;
  p[0] = px;
  p[1] = py;
  p[2] = pz;
  p[3] = 0;
  dMultiply1_331 (result,g->final_posr->R,p);
}



int dGeomLowLevelControl (dxGeom *g, int controlClass, int controlCode, void *dataValue, int *dataSize)
{
	dAASSERT (g);
	dAASSERT (dataSize);

	if (!dataSize) {
		return false;
	}

	bool result = g->controlGeometry(controlClass, controlCode, dataValue, dataSize);
	return result;
}

//****************************************************************************
// C interface that lets the user make new classes. this interface is a lot
// more cumbersome than C++ subclassing, which is what is used internally
// in ODE. this API is mainly to support legacy code.

static int num_user_classes = 0;
static dGeomClass user_classes [dMaxUserClasses];


struct dxUserGeom : public dxGeom {
  void *user_data;

  dxUserGeom (int class_num);
  ~dxUserGeom();
  void computeAABB();
  int AABBTest (dxGeom *o, dReal aabb[6]);
};


dxUserGeom::dxUserGeom (int class_num) : dxGeom (0,1)
{
  type = class_num;
  int size = user_classes[type-dFirstUserClass].bytes;
  user_data = dAlloc (size);
  memset (user_data,0,size);
}


dxUserGeom::~dxUserGeom()
{
  dGeomClass *c = &user_classes[type-dFirstUserClass];
  if (c->dtor) c->dtor (this);
  dFree (user_data,c->bytes);
}


void dxUserGeom::computeAABB()
{
  user_classes[type-dFirstUserClass].aabb (this,aabb);
}


int dxUserGeom::AABBTest (dxGeom *o, dReal aabb[6])
{
  dGeomClass *c = &user_classes[type-dFirstUserClass];
  if (c->aabb_test) return c->aabb_test (this,o,aabb);
  else return 1;
}


static int dCollideUserGeomWithGeom (dxGeom *o1, dxGeom *o2, int flags,
				     dContactGeom *contact, int skip)
{
  // this generic collider function is called the first time that a user class
  // tries to collide against something. it will find out the correct collider
  // function and then set the colliders array so that the correct function is
  // called directly the next time around.

  int t1 = o1->type;	// note that o1 is a user geom
  int t2 = o2->type;	// o2 *may* be a user geom

  // find the collider function to use. if o1 does not know how to collide with
  // o2, then o2 might know how to collide with o1 (provided that it is a user
  // geom).
  dColliderFn *fn = user_classes[t1-dFirstUserClass].collider (t2);
  int reverse = 0;
  if (!fn && t2 >= dFirstUserClass && t2 <= dLastUserClass) {
    fn = user_classes[t2-dFirstUserClass].collider (t1);
    reverse = 1;
  }

  // set the colliders array so that the correct function is called directly
  // the next time around. note that fn can be 0 here if no collider was found,
  // which means that dCollide() will always return 0 for this case.
  colliders[t1][t2].fn = fn;
  colliders[t1][t2].reverse = reverse;
  colliders[t2][t1].fn = fn;
  colliders[t2][t1].reverse = !reverse;

  // now call the collider function indirectly through dCollide(), so that
  // contact reversing is properly handled.
  return dCollide (o1,o2,flags,contact,skip);
}


int dCreateGeomClass (const dGeomClass *c)
{
  dUASSERT(c && c->bytes >= 0 && c->collider && c->aabb,"bad geom class");

  if (num_user_classes >= dMaxUserClasses) {
    dDebug (0,"too many user classes, you must increase the limit and "
	      "recompile ODE");
  }
  user_classes[num_user_classes] = *c;
  int class_number = num_user_classes + dFirstUserClass;
  setAllColliders (class_number,&dCollideUserGeomWithGeom);

  num_user_classes++;
  return class_number;
}

/*extern */void dFinitUserClasses()
{
  num_user_classes = 0;
}

void * dGeomGetClassData (dxGeom *g)
{
  dUASSERT (g && g->type >= dFirstUserClass &&
	    g->type <= dLastUserClass,"not a custom class");
  dxUserGeom *user = (dxUserGeom*) g;
  return user->user_data;
}


dGeomID dCreateGeom (int classnum)
{
  dUASSERT (classnum >= dFirstUserClass &&
	    classnum <= dLastUserClass,"not a custom class");
  return new dxUserGeom (classnum);
}



/* ************************************************************************ */
/* geom offset from body */

void dGeomCreateOffset (dxGeom *g)
{
  dAASSERT (g);
  dUASSERT (g->gflags & GEOM_PLACEABLE,"geom must be placeable");
  dUASSERT (g->body, "geom must be on a body");  
  if (g->offset_posr)
  {
	return; // already created
  }
  dIASSERT (g->final_posr == &g->body->posr);
  
  g->final_posr = dAllocPosr();
  g->offset_posr = dAllocPosr();
  dSetZero (g->offset_posr->pos,4);
  dRSetIdentity (g->offset_posr->R);
  
  g->gflags |= GEOM_POSR_BAD;
}

void dGeomSetOffsetPosition (dxGeom *g, dReal x, dReal y, dReal z)
{
  dAASSERT (g);
  dUASSERT (g->gflags & GEOM_PLACEABLE,"geom must be placeable");
  dUASSERT (g->body, "geom must be on a body");  
  CHECK_NOT_LOCKED (g->parent_space);
  if (!g->offset_posr) 
  {
	dGeomCreateOffset(g);
  }
  g->offset_posr->pos[0] = x;
  g->offset_posr->pos[1] = y;
  g->offset_posr->pos[2] = z;
  dGeomMoved (g);
}

void dGeomSetOffsetRotation (dxGeom *g, const dMatrix3 R)
{
  dAASSERT (g && R);
  dUASSERT (g->gflags & GEOM_PLACEABLE,"geom must be placeable");
  dUASSERT (g->body, "geom must be on a body");  
  CHECK_NOT_LOCKED (g->parent_space);
  if (!g->offset_posr) 
  {
	dGeomCreateOffset (g);
  }
  memcpy (g->offset_posr->R,R,sizeof(dMatrix3));
  dGeomMoved (g);
}

void dGeomSetOffsetQuaternion (dxGeom *g, const dQuaternion quat)
{
  dAASSERT (g && quat);
  dUASSERT (g->gflags & GEOM_PLACEABLE,"geom must be placeable");
  dUASSERT (g->body, "geom must be on a body");  
  CHECK_NOT_LOCKED (g->parent_space);
  if (!g->offset_posr) 
  {
	dGeomCreateOffset (g);
  }
  dQtoR (quat, g->offset_posr->R);
  dGeomMoved (g);
}

void dGeomSetOffsetWorldPosition (dxGeom *g, dReal x, dReal y, dReal z)
{
  dAASSERT (g);
  dUASSERT (g->gflags & GEOM_PLACEABLE,"geom must be placeable");
  dUASSERT (g->body, "geom must be on a body");  
  CHECK_NOT_LOCKED (g->parent_space);
  if (!g->offset_posr) 
  {
	dGeomCreateOffset(g);
  }
  dBodyGetPosRelPoint(g->body, x, y, z, g->offset_posr->pos);
  dGeomMoved (g);
}

void dGeomSetOffsetWorldRotation (dxGeom *g, const dMatrix3 R)
{
  dAASSERT (g && R);
  dUASSERT (g->gflags & GEOM_PLACEABLE,"geom must be placeable");
  dUASSERT (g->body, "geom must be on a body");  
  CHECK_NOT_LOCKED (g->parent_space);
  if (!g->offset_posr) 
  {
	dGeomCreateOffset (g);
  }
  g->recomputePosr();
  
  dxPosR new_final_posr;
  memcpy(new_final_posr.pos, g->final_posr->pos, sizeof(dVector3));
  memcpy(new_final_posr.R, R, sizeof(dMatrix3));
  
  getWorldOffsetPosr(g->body->posr, new_final_posr, *g->offset_posr);
  dGeomMoved (g);
}

void dGeomSetOffsetWorldQuaternion (dxGeom *g, const dQuaternion quat)
{
  dAASSERT (g && quat);
  dUASSERT (g->gflags & GEOM_PLACEABLE,"geom must be placeable");
  dUASSERT (g->body, "geom must be on a body");  
  CHECK_NOT_LOCKED (g->parent_space);
  if (!g->offset_posr) 
  {
	dGeomCreateOffset (g);
  }

  g->recomputePosr();
  
  dxPosR new_final_posr;
  memcpy(new_final_posr.pos, g->final_posr->pos, sizeof(dVector3));
  dQtoR (quat, new_final_posr.R);
  
  getWorldOffsetPosr(g->body->posr, new_final_posr, *g->offset_posr);
  dGeomMoved (g);
}

void dGeomClearOffset(dxGeom *g)
{
  dAASSERT (g);
  dUASSERT (g->gflags & GEOM_PLACEABLE,"geom must be placeable");
  if (g->offset_posr)
  {
    dIASSERT(g->body);
    // no longer need an offset posr
	dFreePosr(g->offset_posr);
	g->offset_posr = 0;
    // the geom will now share the position of the body
    dFreePosr(g->final_posr);
    g->final_posr = &g->body->posr;
    // geom has moved
    g->gflags &= ~GEOM_POSR_BAD;
    dGeomMoved (g);
  }
}

int dGeomIsOffset(dxGeom *g)
{
  dAASSERT (g);
  return ((0 != g->offset_posr) ? 1 : 0);
}

static const dVector3 OFFSET_POSITION_ZERO = { 0.0f, 0.0f, 0.0f, 0.0f };

const dReal * dGeomGetOffsetPosition (dxGeom *g)
{
  dAASSERT (g);
  if (g->offset_posr)
  {
    return g->offset_posr->pos;
  }
  return OFFSET_POSITION_ZERO;
}

void dGeomCopyOffsetPosition (dxGeom *g, dVector3 pos)
{
  dAASSERT (g);
  if (g->offset_posr)
  {
    const dReal* src = g->offset_posr->pos;
    pos[0] = src[0];
	 pos[1] = src[1];
	 pos[2] = src[2];
  }
  else
  {
    pos[0] = 0;
	 pos[1] = 0;
	 pos[2] = 0;
  }
}

static const dMatrix3 OFFSET_ROTATION_ZERO = 
{ 
	1.0f, 0.0f, 0.0f, 0.0f, 
	0.0f, 1.0f, 0.0f, 0.0f, 
	0.0f, 0.0f, 1.0f, 0.0f, 
};

const dReal * dGeomGetOffsetRotation (dxGeom *g)
{
  dAASSERT (g);
  if (g->offset_posr)
  {
    return g->offset_posr->R;
  }
  return OFFSET_ROTATION_ZERO;
}

void dGeomCopyOffsetRotation (dxGeom *g, dMatrix3 R)
{
	dAASSERT (g);
	if (g->offset_posr)
	{
		const dReal* src = g->offset_posr->R;
		R[0]  = src[0];
		R[1]  = src[1];
		R[2]  = src[2];
		R[4]  = src[4];
		R[5]  = src[5];
		R[6]  = src[6];
		R[8]  = src[8];
		R[9]  = src[9];
		R[10] = src[10];
	}
	else
	{
		R[0]  = OFFSET_ROTATION_ZERO[0];
		R[1]  = OFFSET_ROTATION_ZERO[1];
		R[2]  = OFFSET_ROTATION_ZERO[2];
		R[4]  = OFFSET_ROTATION_ZERO[4];
		R[5]  = OFFSET_ROTATION_ZERO[5];
		R[6]  = OFFSET_ROTATION_ZERO[6];
		R[8]  = OFFSET_ROTATION_ZERO[8];
		R[9]  = OFFSET_ROTATION_ZERO[9];
		R[10] = OFFSET_ROTATION_ZERO[10];
	}
}

void dGeomGetOffsetQuaternion (dxGeom *g, dQuaternion result)
{
  dAASSERT (g);
  if (g->offset_posr)
  {
    dRtoQ (g->offset_posr->R, result);
  }
  else
  {
    dSetZero (result,4);
    result[0] = 1;
  }
}


