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

#ifdef _MSC_VER
#pragma warning(disable:4291)  // for VC++, no complaints about "no matching operator delete found"
#endif

// this source file is mostly concerned with the data structures, not the
// numerics.

#include <ode/ode.h>
#include <ode/odemath.h>
#include <ode/matrix.h>
#include <ode/memory.h>
#include <ode/error.h>
#include "config.h"
#include "objects.h"
#include "joints/joints.h"
#include "step.h"
#include "quickstep.h"
#include "util.h"
#include "odetls.h"

// misc defines
#define ALLOCA dALLOCA16

//****************************************************************************
// utility


dObject::dObject(dxWorld *w)
{
    world = w;
    next = 0;
    tome = 0;
    userdata = 0;
    tag = 0;
}


// add an object `obj' to the list who's head pointer is pointed to by `first'.

void addObjectToList (dObject *obj, dObject **first)
{
  obj->next = *first;
  obj->tome = first;
  if (*first) (*first)->tome = &obj->next;
  (*first) = obj;
}


// remove the object from the linked list

static inline void removeObjectFromList (dObject *obj)
{
  if (obj->next) obj->next->tome = obj->tome;
  *(obj->tome) = obj->next;
  // safeguard
  obj->next = 0;
  obj->tome = 0;
}


// remove the joint from neighbour lists of all connected bodies

static void removeJointReferencesFromAttachedBodies (dxJoint *j)
{
  for (int i=0; i<2; i++) {
    dxBody *body = j->node[i].body;
    if (body) {
      dxJointNode *n = body->firstjoint;
      dxJointNode *last = 0;
      while (n) {
	if (n->joint == j) {
	  if (last) last->next = n->next;
	  else body->firstjoint = n->next;
	  break;
	}
	last = n;
	n = n->next;
      }
    }
  }
  j->node[0].body = 0;
  j->node[0].next = 0;
  j->node[1].body = 0;
  j->node[1].next = 0;
}

//****************************************************************************
// debugging

// see if an object list loops on itself (if so, it's bad).

static int listHasLoops (dObject *first)
{
  if (first==0 || first->next==0) return 0;
  dObject *a=first,*b=first->next;
  int skip=0;
  while (b) {
    if (a==b) return 1;
    b = b->next;
    if (skip) a = a->next;
    skip ^= 1;
  }
  return 0;
}


// check the validity of the world data structures

static int g_world_check_tag_generator = 0;

static inline int generateWorldCheckTag()
{
	// Atomicity is not necessary here
	return ++g_world_check_tag_generator;
}

static void checkWorld (dxWorld *w)
{
  dxBody *b;
  dxJoint *j;

  // check there are no loops
  if (listHasLoops (w->firstbody)) dDebug (0,"body list has loops");
  if (listHasLoops (w->firstjoint)) dDebug (0,"joint list has loops");

  // check lists are well formed (check `tome' pointers)
  for (b=w->firstbody; b; b=(dxBody*)b->next) {
    if (b->next && b->next->tome != &b->next)
      dDebug (0,"bad tome pointer in body list");
  }
  for (j=w->firstjoint; j; j=(dxJoint*)j->next) {
    if (j->next && j->next->tome != &j->next)
      dDebug (0,"bad tome pointer in joint list");
  }

  // check counts
  int n = 0;
  for (b=w->firstbody; b; b=(dxBody*)b->next) n++;
  if (w->nb != n) dDebug (0,"body count incorrect");
  n = 0;
  for (j=w->firstjoint; j; j=(dxJoint*)j->next) n++;
  if (w->nj != n) dDebug (0,"joint count incorrect");

  // set all tag values to a known value
  int count = generateWorldCheckTag();
  for (b=w->firstbody; b; b=(dxBody*)b->next) b->tag = count;
  for (j=w->firstjoint; j; j=(dxJoint*)j->next) j->tag = count;

  // check all body/joint world pointers are ok
  for (b=w->firstbody; b; b=(dxBody*)b->next) if (b->world != w)
    dDebug (0,"bad world pointer in body list");
  for (j=w->firstjoint; j; j=(dxJoint*)j->next) if (j->world != w)
    dDebug (0,"bad world pointer in joint list");

  /*
  // check for half-connected joints - actually now these are valid
  for (j=w->firstjoint; j; j=(dxJoint*)j->next) {
    if (j->node[0].body || j->node[1].body) {
      if (!(j->node[0].body && j->node[1].body))
	dDebug (0,"half connected joint found");
    }
  }
  */

  // check that every joint node appears in the joint lists of both bodies it
  // attaches
  for (j=w->firstjoint; j; j=(dxJoint*)j->next) {
    for (int i=0; i<2; i++) {
      if (j->node[i].body) {
	int ok = 0;
	for (dxJointNode *n=j->node[i].body->firstjoint; n; n=n->next) {
	  if (n->joint == j) ok = 1;
	}
	if (ok==0) dDebug (0,"joint not in joint list of attached body");
      }
    }
  }

  // check all body joint lists (correct body ptrs)
  for (b=w->firstbody; b; b=(dxBody*)b->next) {
    for (dxJointNode *n=b->firstjoint; n; n=n->next) {
      if (&n->joint->node[0] == n) {
	if (n->joint->node[1].body != b)
	  dDebug (0,"bad body pointer in joint node of body list (1)");
      }
      else {
	if (n->joint->node[0].body != b)
	  dDebug (0,"bad body pointer in joint node of body list (2)");
      }
      if (n->joint->tag != count) dDebug (0,"bad joint node pointer in body");
    }
  }

  // check all body pointers in joints, check they are distinct
  for (j=w->firstjoint; j; j=(dxJoint*)j->next) {
    if (j->node[0].body && (j->node[0].body == j->node[1].body))
      dDebug (0,"non-distinct body pointers in joint");
    if ((j->node[0].body && j->node[0].body->tag != count) ||
	(j->node[1].body && j->node[1].body->tag != count))
      dDebug (0,"bad body pointer in joint");
  }
}


void dWorldCheck (dxWorld *w)
{
  checkWorld (w);
}

//****************************************************************************
// body

dxBody::dxBody(dxWorld *w) :
    dObject(w)
{
    
}


dxWorld* dBodyGetWorld (dxBody * b)
{
  dAASSERT (b);
  return b->world;
}

dxBody *dBodyCreate (dxWorld *w)
{
  dAASSERT (w);
  dxBody *b = new dxBody(w);
  b->firstjoint = 0;
  b->flags = 0;
  b->geom = 0;
  b->average_lvel_buffer = 0;
  b->average_avel_buffer = 0;
  dMassSetParameters (&b->mass,1,0,0,0,1,1,1,0,0,0);
  dSetZero (b->invI,4*3);
  b->invI[0] = 1;
  b->invI[5] = 1;
  b->invI[10] = 1;
  b->invMass = 1;
  dSetZero (b->posr.pos,4);
  dSetZero (b->q,4);
  b->q[0] = 1;
  dRSetIdentity (b->posr.R);
  dSetZero (b->lvel,4);
  dSetZero (b->avel,4);
  dSetZero (b->facc,4);
  dSetZero (b->tacc,4);
  dSetZero (b->finite_rot_axis,4);
  addObjectToList (b,(dObject **) &w->firstbody);
  w->nb++;

  // set auto-disable parameters
  b->average_avel_buffer = b->average_lvel_buffer = 0; // no buffer at beginning
  dBodySetAutoDisableDefaults (b);	// must do this after adding to world
  b->adis_stepsleft = b->adis.idle_steps;
  b->adis_timeleft = b->adis.idle_time;
  b->average_counter = 0;
  b->average_ready = 0; // average buffer not filled on the beginning
  dBodySetAutoDisableAverageSamplesCount(b, b->adis.average_samples);

  b->moved_callback = 0;

  dBodySetDampingDefaults(b);	// must do this after adding to world

  b->flags |= w->body_flags & dxBodyMaxAngularSpeed;
  b->max_angular_speed = w->max_angular_speed;

  b->flags |= dxBodyGyroscopic;

  return b;
}


void dBodyDestroy (dxBody *b)
{
  dAASSERT (b);

  // all geoms that link to this body must be notified that the body is about
  // to disappear. note that the call to dGeomSetBody(geom,0) will result in
  // dGeomGetBodyNext() returning 0 for the body, so we must get the next body
  // before setting the body to 0.
  dxGeom *next_geom = 0;
  for (dxGeom *geom = b->geom; geom; geom = next_geom) {
    next_geom = dGeomGetBodyNext (geom);
    dGeomSetBody (geom,0);
  }

  // detach all neighbouring joints, then delete this body.
  dxJointNode *n = b->firstjoint;
  while (n) {
    // sneaky trick to speed up removal of joint references (black magic)
    n->joint->node[(n == n->joint->node)].body = 0;

    dxJointNode *next = n->next;
    n->next = 0;
    removeJointReferencesFromAttachedBodies (n->joint);
    n = next;
  }
  removeObjectFromList (b);
  b->world->nb--;

  // delete the average buffers
  if(b->average_lvel_buffer)
  {
	  delete[] (b->average_lvel_buffer);
	  b->average_lvel_buffer = 0;
  }
  if(b->average_avel_buffer)
  {
	  delete[] (b->average_avel_buffer);
	  b->average_avel_buffer = 0;
  }

  delete b;
}


void dBodySetData (dBodyID b, void *data)
{
  dAASSERT (b);
  b->userdata = data;
}


void *dBodyGetData (dBodyID b)
{
  dAASSERT (b);
  return b->userdata;
}


void dBodySetPosition (dBodyID b, dReal x, dReal y, dReal z)
{
  dAASSERT (b);
  b->posr.pos[0] = x;
  b->posr.pos[1] = y;
  b->posr.pos[2] = z;

  // notify all attached geoms that this body has moved
  for (dxGeom *geom = b->geom; geom; geom = dGeomGetBodyNext (geom))
    dGeomMoved (geom);
}


void dBodySetRotation (dBodyID b, const dMatrix3 R)
{
  dAASSERT (b && R);

  memcpy(b->posr.R, R, sizeof(dMatrix3));
  dOrthogonalizeR(b->posr.R);
  dRtoQ (R, b->q);
  dNormalize4 (b->q);

  // notify all attached geoms that this body has moved
  for (dxGeom *geom = b->geom; geom; geom = dGeomGetBodyNext (geom))
    dGeomMoved (geom);
}


void dBodySetQuaternion (dBodyID b, const dQuaternion q)
{
  dAASSERT (b && q);
  b->q[0] = q[0];
  b->q[1] = q[1];
  b->q[2] = q[2];
  b->q[3] = q[3];
  dNormalize4 (b->q);
  dQtoR (b->q,b->posr.R);

  // notify all attached geoms that this body has moved
  for (dxGeom *geom = b->geom; geom; geom = dGeomGetBodyNext (geom))
    dGeomMoved (geom);
}


void dBodySetLinearVel  (dBodyID b, dReal x, dReal y, dReal z)
{
  dAASSERT (b);
  b->lvel[0] = x;
  b->lvel[1] = y;
  b->lvel[2] = z;
}


void dBodySetAngularVel (dBodyID b, dReal x, dReal y, dReal z)
{
  dAASSERT (b);
  b->avel[0] = x;
  b->avel[1] = y;
  b->avel[2] = z;
}


const dReal * dBodyGetPosition (dBodyID b)
{
  dAASSERT (b);
  return b->posr.pos;
}


void dBodyCopyPosition (dBodyID b, dVector3 pos)
{
	dAASSERT (b);
	dReal* src = b->posr.pos;
	pos[0] = src[0];
	pos[1] = src[1];
	pos[2] = src[2];
}


const dReal * dBodyGetRotation (dBodyID b)
{
  dAASSERT (b);
  return b->posr.R;
}


void dBodyCopyRotation (dBodyID b, dMatrix3 R)
{
	dAASSERT (b);
	const dReal* src = b->posr.R;
	R[0] = src[0];
	R[1] = src[1];
	R[2] = src[2];
	R[3] = src[3];
	R[4] = src[4];
	R[5] = src[5];
	R[6] = src[6];
	R[7] = src[7];
	R[8] = src[8];
	R[9] = src[9];
	R[10] = src[10];
	R[11] = src[11];
}


const dReal * dBodyGetQuaternion (dBodyID b)
{
  dAASSERT (b);
  return b->q;
}


void dBodyCopyQuaternion (dBodyID b, dQuaternion quat)
{
	dAASSERT (b);
	dReal* src = b->q;
	quat[0] = src[0];
	quat[1] = src[1];
	quat[2] = src[2];
	quat[3] = src[3];
}


const dReal * dBodyGetLinearVel (dBodyID b)
{
  dAASSERT (b);
  return b->lvel;
}


const dReal * dBodyGetAngularVel (dBodyID b)
{
  dAASSERT (b);
  return b->avel;
}


void dBodySetMass (dBodyID b, const dMass *mass)
{
  dAASSERT (b && mass );
  dIASSERT(dMassCheck(mass));

  // The centre of mass must be at the origin.
  // Use dMassTranslate( mass, -mass->c[0], -mass->c[1], -mass->c[2] ) to correct it.
  dUASSERT( fabs( mass->c[0] ) <= dEpsilon &&
			fabs( mass->c[1] ) <= dEpsilon &&
			fabs( mass->c[2] ) <= dEpsilon, "The centre of mass must be at the origin." )

  memcpy (&b->mass,mass,sizeof(dMass));
  if (dInvertPDMatrix (b->mass.I,b->invI,3,NULL)==0) {
    dDEBUGMSG ("inertia must be positive definite!");
    dRSetIdentity (b->invI);
  }
  b->invMass = dRecip(b->mass.mass);
}


void dBodyGetMass (dBodyID b, dMass *mass)
{
  dAASSERT (b && mass);
  memcpy (mass,&b->mass,sizeof(dMass));
}


void dBodyAddForce (dBodyID b, dReal fx, dReal fy, dReal fz)
{
  dAASSERT (b);
  b->facc[0] += fx;
  b->facc[1] += fy;
  b->facc[2] += fz;
}


void dBodyAddTorque (dBodyID b, dReal fx, dReal fy, dReal fz)
{
  dAASSERT (b);
  b->tacc[0] += fx;
  b->tacc[1] += fy;
  b->tacc[2] += fz;
}


void dBodyAddRelForce (dBodyID b, dReal fx, dReal fy, dReal fz)
{
  dAASSERT (b);
  dVector3 t1,t2;
  t1[0] = fx;
  t1[1] = fy;
  t1[2] = fz;
  t1[3] = 0;
  dMultiply0_331 (t2,b->posr.R,t1);
  b->facc[0] += t2[0];
  b->facc[1] += t2[1];
  b->facc[2] += t2[2];
}


void dBodyAddRelTorque (dBodyID b, dReal fx, dReal fy, dReal fz)
{
  dAASSERT (b);
  dVector3 t1,t2;
  t1[0] = fx;
  t1[1] = fy;
  t1[2] = fz;
  t1[3] = 0;
  dMultiply0_331 (t2,b->posr.R,t1);
  b->tacc[0] += t2[0];
  b->tacc[1] += t2[1];
  b->tacc[2] += t2[2];
}


void dBodyAddForceAtPos (dBodyID b, dReal fx, dReal fy, dReal fz,
			 dReal px, dReal py, dReal pz)
{
  dAASSERT (b);
  b->facc[0] += fx;
  b->facc[1] += fy;
  b->facc[2] += fz;
  dVector3 f,q;
  f[0] = fx;
  f[1] = fy;
  f[2] = fz;
  q[0] = px - b->posr.pos[0];
  q[1] = py - b->posr.pos[1];
  q[2] = pz - b->posr.pos[2];
  dAddVectorCross3(b->tacc,q,f);
}


void dBodyAddForceAtRelPos (dBodyID b, dReal fx, dReal fy, dReal fz,
			    dReal px, dReal py, dReal pz)
{
  dAASSERT (b);
  dVector3 prel,f,p;
  f[0] = fx;
  f[1] = fy;
  f[2] = fz;
  f[3] = 0;
  prel[0] = px;
  prel[1] = py;
  prel[2] = pz;
  prel[3] = 0;
  dMultiply0_331 (p,b->posr.R,prel);
  b->facc[0] += f[0];
  b->facc[1] += f[1];
  b->facc[2] += f[2];
  dAddVectorCross3(b->tacc,p,f);
}


void dBodyAddRelForceAtPos (dBodyID b, dReal fx, dReal fy, dReal fz,
			    dReal px, dReal py, dReal pz)
{
  dAASSERT (b);
  dVector3 frel,f;
  frel[0] = fx;
  frel[1] = fy;
  frel[2] = fz;
  frel[3] = 0;
  dMultiply0_331 (f,b->posr.R,frel);
  b->facc[0] += f[0];
  b->facc[1] += f[1];
  b->facc[2] += f[2];
  dVector3 q;
  q[0] = px - b->posr.pos[0];
  q[1] = py - b->posr.pos[1];
  q[2] = pz - b->posr.pos[2];
  dAddVectorCross3(b->tacc,q,f);
}


void dBodyAddRelForceAtRelPos (dBodyID b, dReal fx, dReal fy, dReal fz,
			       dReal px, dReal py, dReal pz)
{
  dAASSERT (b);
  dVector3 frel,prel,f,p;
  frel[0] = fx;
  frel[1] = fy;
  frel[2] = fz;
  frel[3] = 0;
  prel[0] = px;
  prel[1] = py;
  prel[2] = pz;
  prel[3] = 0;
  dMultiply0_331 (f,b->posr.R,frel);
  dMultiply0_331 (p,b->posr.R,prel);
  b->facc[0] += f[0];
  b->facc[1] += f[1];
  b->facc[2] += f[2];
  dAddVectorCross3(b->tacc,p,f);
}


const dReal * dBodyGetForce (dBodyID b)
{
  dAASSERT (b);
  return b->facc;
}


const dReal * dBodyGetTorque (dBodyID b)
{
  dAASSERT (b);
  return b->tacc;
}


void dBodySetForce (dBodyID b, dReal x, dReal y, dReal z)
{
  dAASSERT (b);
  b->facc[0] = x;
  b->facc[1] = y;
  b->facc[2] = z;
}


void dBodySetTorque (dBodyID b, dReal x, dReal y, dReal z)
{
  dAASSERT (b);
  b->tacc[0] = x;
  b->tacc[1] = y;
  b->tacc[2] = z;
}


void dBodyGetRelPointPos (dBodyID b, dReal px, dReal py, dReal pz,
			  dVector3 result)
{
  dAASSERT (b);
  dVector3 prel,p;
  prel[0] = px;
  prel[1] = py;
  prel[2] = pz;
  prel[3] = 0;
  dMultiply0_331 (p,b->posr.R,prel);
  result[0] = p[0] + b->posr.pos[0];
  result[1] = p[1] + b->posr.pos[1];
  result[2] = p[2] + b->posr.pos[2];
}


void dBodyGetRelPointVel (dBodyID b, dReal px, dReal py, dReal pz,
			  dVector3 result)
{
  dAASSERT (b);
  dVector3 prel,p;
  prel[0] = px;
  prel[1] = py;
  prel[2] = pz;
  prel[3] = 0;
  dMultiply0_331 (p,b->posr.R,prel);
  result[0] = b->lvel[0];
  result[1] = b->lvel[1];
  result[2] = b->lvel[2];
  dAddVectorCross3(result,b->avel,p);
}


void dBodyGetPointVel (dBodyID b, dReal px, dReal py, dReal pz,
		       dVector3 result)
{
  dAASSERT (b);
  dVector3 p;
  p[0] = px - b->posr.pos[0];
  p[1] = py - b->posr.pos[1];
  p[2] = pz - b->posr.pos[2];
  p[3] = 0;
  result[0] = b->lvel[0];
  result[1] = b->lvel[1];
  result[2] = b->lvel[2];
  dAddVectorCross3(result,b->avel,p);
}


void dBodyGetPosRelPoint (dBodyID b, dReal px, dReal py, dReal pz,
			  dVector3 result)
{
  dAASSERT (b);
  dVector3 prel;
  prel[0] = px - b->posr.pos[0];
  prel[1] = py - b->posr.pos[1];
  prel[2] = pz - b->posr.pos[2];
  prel[3] = 0;
  dMultiply1_331 (result,b->posr.R,prel);
}


void dBodyVectorToWorld (dBodyID b, dReal px, dReal py, dReal pz,
			 dVector3 result)
{
  dAASSERT (b);
  dVector3 p;
  p[0] = px;
  p[1] = py;
  p[2] = pz;
  p[3] = 0;
  dMultiply0_331 (result,b->posr.R,p);
}


void dBodyVectorFromWorld (dBodyID b, dReal px, dReal py, dReal pz,
			   dVector3 result)
{
  dAASSERT (b);
  dVector3 p;
  p[0] = px;
  p[1] = py;
  p[2] = pz;
  p[3] = 0;
  dMultiply1_331 (result,b->posr.R,p);
}


void dBodySetFiniteRotationMode (dBodyID b, int mode)
{
  dAASSERT (b);
  b->flags &= ~(dxBodyFlagFiniteRotation | dxBodyFlagFiniteRotationAxis);
  if (mode) {
    b->flags |= dxBodyFlagFiniteRotation;
    if (b->finite_rot_axis[0] != 0 || b->finite_rot_axis[1] != 0 ||
	b->finite_rot_axis[2] != 0) {
      b->flags |= dxBodyFlagFiniteRotationAxis;
    }
  }
}


void dBodySetFiniteRotationAxis (dBodyID b, dReal x, dReal y, dReal z)
{
  dAASSERT (b);
  b->finite_rot_axis[0] = x;
  b->finite_rot_axis[1] = y;
  b->finite_rot_axis[2] = z;
  if (x != 0 || y != 0 || z != 0) {
    dNormalize3 (b->finite_rot_axis);
    b->flags |= dxBodyFlagFiniteRotationAxis;
  }
  else {
    b->flags &= ~dxBodyFlagFiniteRotationAxis;
  }
}


int dBodyGetFiniteRotationMode (dBodyID b)
{
  dAASSERT (b);
  return ((b->flags & dxBodyFlagFiniteRotation) != 0);
}


void dBodyGetFiniteRotationAxis (dBodyID b, dVector3 result)
{
  dAASSERT (b);
  result[0] = b->finite_rot_axis[0];
  result[1] = b->finite_rot_axis[1];
  result[2] = b->finite_rot_axis[2];
}


int dBodyGetNumJoints (dBodyID b)
{
  dAASSERT (b);
  int count=0;
  for (dxJointNode *n=b->firstjoint; n; n=n->next, count++);
  return count;
}


dJointID dBodyGetJoint (dBodyID b, int index)
{
  dAASSERT (b);
  int i=0;
  for (dxJointNode *n=b->firstjoint; n; n=n->next, i++) {
    if (i == index) return n->joint;
  }
  return 0;
}

void dBodySetDynamic (dBodyID b)
{
  dAASSERT (b);
  
  dBodySetMass(b,&b->mass);
}

void dBodySetKinematic (dBodyID b)
{
  dAASSERT (b);
  dSetZero (b->invI,4*3);
  b->invMass = 0; 
}

int dBodyIsKinematic (dBodyID b)
{
  dAASSERT (b);
  return b->invMass == 0;
}

void dBodyEnable (dBodyID b)
{
  dAASSERT (b);
  b->flags &= ~dxBodyDisabled;
  b->adis_stepsleft = b->adis.idle_steps;
  b->adis_timeleft = b->adis.idle_time;
  // no code for average-processing needed here
}


void dBodyDisable (dBodyID b)
{
  dAASSERT (b);
  b->flags |= dxBodyDisabled;
}


int dBodyIsEnabled (dBodyID b)
{
  dAASSERT (b);
  return ((b->flags & dxBodyDisabled) == 0);
}


void dBodySetGravityMode (dBodyID b, int mode)
{
  dAASSERT (b);
  if (mode) b->flags &= ~dxBodyNoGravity;
  else b->flags |= dxBodyNoGravity;
}


int dBodyGetGravityMode (dBodyID b)
{
  dAASSERT (b);
  return ((b->flags & dxBodyNoGravity) == 0);
}


// body auto-disable functions

dReal dBodyGetAutoDisableLinearThreshold (dBodyID b)
{
	dAASSERT(b);
	return dSqrt (b->adis.linear_average_threshold);
}


void dBodySetAutoDisableLinearThreshold (dBodyID b, dReal linear_average_threshold)
{
	dAASSERT(b);
	b->adis.linear_average_threshold = linear_average_threshold * linear_average_threshold;
}


dReal dBodyGetAutoDisableAngularThreshold (dBodyID b)
{
	dAASSERT(b);
	return dSqrt (b->adis.angular_average_threshold);
}


void dBodySetAutoDisableAngularThreshold (dBodyID b, dReal angular_average_threshold)
{
	dAASSERT(b);
	b->adis.angular_average_threshold = angular_average_threshold * angular_average_threshold;
}


int dBodyGetAutoDisableAverageSamplesCount (dBodyID b)
{
	dAASSERT(b);
	return b->adis.average_samples;
}


void dBodySetAutoDisableAverageSamplesCount (dBodyID b, unsigned int average_samples_count)
{
	dAASSERT(b);
	b->adis.average_samples = average_samples_count;
	// update the average buffers
	if(b->average_lvel_buffer)
	{
		delete[] b->average_lvel_buffer;
		b->average_lvel_buffer = 0;
	}
	if(b->average_avel_buffer)
	{
		delete[] b->average_avel_buffer;
		b->average_avel_buffer = 0;
	}
	if(b->adis.average_samples > 0)
	{
		b->average_lvel_buffer = new dVector3[b->adis.average_samples];
		b->average_avel_buffer = new dVector3[b->adis.average_samples];
	}
	else
	{
		b->average_lvel_buffer = 0;
		b->average_avel_buffer = 0;
	}
	// new buffer is empty
	b->average_counter = 0;
	b->average_ready = 0;
}


int dBodyGetAutoDisableSteps (dBodyID b)
{
	dAASSERT(b);
	return b->adis.idle_steps;
}


void dBodySetAutoDisableSteps (dBodyID b, int steps)
{
	dAASSERT(b);
	b->adis.idle_steps = steps;
}


dReal dBodyGetAutoDisableTime (dBodyID b)
{
	dAASSERT(b);
	return b->adis.idle_time;
}


void dBodySetAutoDisableTime (dBodyID b, dReal time)
{
	dAASSERT(b);
	b->adis.idle_time = time;
}


int dBodyGetAutoDisableFlag (dBodyID b)
{
	dAASSERT(b);
	return ((b->flags & dxBodyAutoDisable) != 0);
}


void dBodySetAutoDisableFlag (dBodyID b, int do_auto_disable)
{
	dAASSERT(b);
	if (!do_auto_disable)
	{
		b->flags &= ~dxBodyAutoDisable;
		// (mg) we should also reset the IsDisabled state to correspond to the DoDisabling flag
		b->flags &= ~dxBodyDisabled;
		b->adis.idle_steps = dWorldGetAutoDisableSteps(b->world);
		b->adis.idle_time = dWorldGetAutoDisableTime(b->world);
		// resetting the average calculations too
		dBodySetAutoDisableAverageSamplesCount(b, dWorldGetAutoDisableAverageSamplesCount(b->world) );
	}
	else
	{
		b->flags |= dxBodyAutoDisable;
	}
}


void dBodySetAutoDisableDefaults (dBodyID b)
{
	dAASSERT(b);
	dWorldID w = b->world;
	dAASSERT(w);
	b->adis = w->adis;
	dBodySetAutoDisableFlag (b, w->body_flags & dxBodyAutoDisable);
}


// body damping functions

dReal dBodyGetLinearDamping(dBodyID b)
{
        dAASSERT(b);
        return b->dampingp.linear_scale;
}

void dBodySetLinearDamping(dBodyID b, dReal scale)
{
        dAASSERT(b);
        if (scale)
                b->flags |= dxBodyLinearDamping;
        else
                b->flags &= ~dxBodyLinearDamping;
        b->dampingp.linear_scale = scale;
}

dReal dBodyGetAngularDamping(dBodyID b)
{
        dAASSERT(b);
        return b->dampingp.angular_scale;
}

void dBodySetAngularDamping(dBodyID b, dReal scale)
{
        dAASSERT(b);
        if (scale)
                b->flags |= dxBodyAngularDamping;
        else
                b->flags &= ~dxBodyAngularDamping;
        b->dampingp.angular_scale = scale;
}

void dBodySetDamping(dBodyID b, dReal linear_scale, dReal angular_scale)
{
        dAASSERT(b);
        dBodySetLinearDamping(b, linear_scale);
        dBodySetAngularDamping(b, angular_scale);
}

dReal dBodyGetLinearDampingThreshold(dBodyID b)
{
        dAASSERT(b);
        return dSqrt(b->dampingp.linear_threshold);
}

void dBodySetLinearDampingThreshold(dBodyID b, dReal threshold)
{
        dAASSERT(b);
        b->dampingp.linear_threshold = threshold*threshold;
}


dReal dBodyGetAngularDampingThreshold(dBodyID b)
{
        dAASSERT(b);
        return dSqrt(b->dampingp.angular_threshold);
}

void dBodySetAngularDampingThreshold(dBodyID b, dReal threshold)
{
        dAASSERT(b);
        b->dampingp.angular_threshold = threshold*threshold;
}

void dBodySetDampingDefaults(dBodyID b)
{
        dAASSERT(b);
        dWorldID w = b->world;
        dAASSERT(w);
        b->dampingp = w->dampingp;
        const unsigned mask = dxBodyLinearDamping | dxBodyAngularDamping;
        b->flags &= ~mask; // zero them
        b->flags |= w->body_flags & mask;
}

dReal dBodyGetMaxAngularSpeed(dBodyID b)
{
        dAASSERT(b);
        return b->max_angular_speed;
}

void dBodySetMaxAngularSpeed(dBodyID b, dReal max_speed)
{
        dAASSERT(b);
        if (max_speed < dInfinity)
                b->flags |= dxBodyMaxAngularSpeed;
        else
                b->flags &= ~dxBodyMaxAngularSpeed;
        b->max_angular_speed = max_speed;
}

void dBodySetMovedCallback(dBodyID b, void (*callback)(dBodyID))
{
        dAASSERT(b);
        b->moved_callback = callback;
}


dGeomID dBodyGetFirstGeom(dBodyID b)
{
        dAASSERT(b);
        return b->geom;
}


dGeomID dBodyGetNextGeom(dGeomID geom)
{
        dAASSERT(geom);
        return dGeomGetBodyNext(geom);
}


int dBodyGetGyroscopicMode(dBodyID b)
{
        dAASSERT(b);
        return b->flags & dxBodyGyroscopic;
}

void dBodySetGyroscopicMode(dBodyID b, int enabled)
{
        dAASSERT(b);
        if (enabled)
                b->flags |= dxBodyGyroscopic;
        else
                b->flags &= ~dxBodyGyroscopic;
}



//****************************************************************************
// joints



template<class T>
dxJoint* createJoint(dWorldID w, dJointGroupID group)
{
    dxJoint *j;
    if (group) {
        j = (dxJoint*) group->stack.alloc(sizeof(T));
        group->num++;
    } else
        j = (dxJoint*) dAlloc(sizeof(T));
    
    new(j) T(w);
    if (group)
        j->flags |= dJOINT_INGROUP;
    
    return j;
}


dxJoint * dJointCreateBall (dWorldID w, dJointGroupID group)
{
    dAASSERT (w);
    return createJoint<dxJointBall>(w,group);
}


dxJoint * dJointCreateHinge (dWorldID w, dJointGroupID group)
{
    dAASSERT (w);
    return createJoint<dxJointHinge>(w,group);
}


dxJoint * dJointCreateSlider (dWorldID w, dJointGroupID group)
{
    dAASSERT (w);
    return createJoint<dxJointSlider>(w,group);
}


dxJoint * dJointCreateContact (dWorldID w, dJointGroupID group,
			       const dContact *c)
{
    dAASSERT (w && c);
    dxJointContact *j = (dxJointContact *)
        createJoint<dxJointContact> (w,group);
    j->contact = *c;
    return j;
}


dxJoint * dJointCreateHinge2 (dWorldID w, dJointGroupID group)
{
    dAASSERT (w);
    return createJoint<dxJointHinge2> (w,group);
}


dxJoint * dJointCreateUniversal (dWorldID w, dJointGroupID group)
{
    dAASSERT (w);
    return createJoint<dxJointUniversal> (w,group);
}

dxJoint * dJointCreatePR (dWorldID w, dJointGroupID group)
{
    dAASSERT (w);
    return createJoint<dxJointPR> (w,group);
}

dxJoint * dJointCreatePU (dWorldID w, dJointGroupID group)
{
    dAASSERT (w);
    return createJoint<dxJointPU> (w,group);
}

dxJoint * dJointCreatePiston (dWorldID w, dJointGroupID group)
{
    dAASSERT (w);
    return createJoint<dxJointPiston> (w,group);
}

dxJoint * dJointCreateFixed (dWorldID w, dJointGroupID group)
{
    dAASSERT (w);
    return createJoint<dxJointFixed> (w,group);
}


dxJoint * dJointCreateNull (dWorldID w, dJointGroupID group)
{
    dAASSERT (w);
    return createJoint<dxJointNull> (w,group);
}


dxJoint * dJointCreateAMotor (dWorldID w, dJointGroupID group)
{
    dAASSERT (w);
    return createJoint<dxJointAMotor> (w,group);
}

dxJoint * dJointCreateLMotor (dWorldID w, dJointGroupID group)
{
    dAASSERT (w);
    return createJoint<dxJointLMotor> (w,group);
}

dxJoint * dJointCreatePlane2D (dWorldID w, dJointGroupID group)
{
    dAASSERT (w);
    return createJoint<dxJointPlane2D> (w,group);
}

void dJointDestroy (dxJoint *j)
{
    dAASSERT (j);
    size_t sz = j->size();
    if (j->flags & dJOINT_INGROUP) return;
    removeJointReferencesFromAttachedBodies (j);
    removeObjectFromList (j);
    j->world->nj--;
    j->~dxJoint();
    dFree (j, sz);
}


dJointGroupID dJointGroupCreate (int max_size)
{
    // not any more ... dUASSERT (max_size > 0,"max size must be > 0");
    dxJointGroup *group = new dxJointGroup;
    group->num = 0;
    return group;
}


void dJointGroupDestroy (dJointGroupID group)
{
    dAASSERT (group);
    dJointGroupEmpty (group);
    delete group;
}


void dJointGroupEmpty (dJointGroupID group)
{
    // the joints in this group are detached starting from the most recently
    // added (at the top of the stack). this helps ensure that the various
    // linked lists are not traversed too much, as the joints will hopefully
    // be at the start of those lists.
    // if any group joints have their world pointer set to 0, their world was
    // previously destroyed. no special handling is required for these joints.
    
    dAASSERT (group);
    int i;
    dxJoint **jlist = (dxJoint**) ALLOCA (group->num * sizeof(dxJoint*));
    dxJoint *j = (dxJoint*) group->stack.rewind();
    for (i=0; i < group->num; i++) {
        jlist[i] = j;
        j = (dxJoint*) (group->stack.next (j->size()));
    }
    for (i=group->num-1; i >= 0; i--) {
        if (jlist[i]->world) {
            removeJointReferencesFromAttachedBodies (jlist[i]);
            removeObjectFromList (jlist[i]);
            jlist[i]->world->nj--;
            jlist[i]->~dxJoint();
        }
    }
    group->num = 0;
    group->stack.freeAll();
}

int dJointGetNumBodies(dxJoint *joint)
{
    // check arguments
    dUASSERT (joint,"bad joint argument");

    if ( !joint->node[0].body )
        return 0;
    else if ( !joint->node[1].body )
        return 1;
    else
        return 2;
}


void dJointAttach (dxJoint *joint, dxBody *body1, dxBody *body2)
{
  // check arguments
  dUASSERT (joint,"bad joint argument");
  dUASSERT (body1 == 0 || body1 != body2,"can't have body1==body2");
  dxWorld *world = joint->world;
  dUASSERT ( (!body1 || body1->world == world) &&
	     (!body2 || body2->world == world),
	     "joint and bodies must be in same world");

  // check if the joint can not be attached to just one body
  dUASSERT (!((joint->flags & dJOINT_TWOBODIES) &&
	      ((body1 != 0) ^ (body2 != 0))),
	    "joint can not be attached to just one body");

  // remove any existing body attachments
  if (joint->node[0].body || joint->node[1].body) {
    removeJointReferencesFromAttachedBodies (joint);
  }

  // if a body is zero, make sure that it is body2, so 0 --> node[1].body
  if (body1==0) {
    body1 = body2;
    body2 = 0;
    joint->flags |= dJOINT_REVERSE;
  }
  else {
    joint->flags &= (~dJOINT_REVERSE);
  }

  // attach to new bodies
  joint->node[0].body = body1;
  joint->node[1].body = body2;
  if (body1) {
    joint->node[1].next = body1->firstjoint;
    body1->firstjoint = &joint->node[1];
  }
  else joint->node[1].next = 0;
  if (body2) {
    joint->node[0].next = body2->firstjoint;
    body2->firstjoint = &joint->node[0];
  }
  else {
    joint->node[0].next = 0;
  }

  // Since the bodies are now set.
  // Calculate the values depending on the bodies.
  // Only need to calculate relative value if a body exist
  if (body1 || body2)
    joint->setRelativeValues();
}

void dJointEnable (dxJoint *joint)
{
  dAASSERT (joint);
  joint->flags &= ~dJOINT_DISABLED;
}

void dJointDisable (dxJoint *joint)
{
  dAASSERT (joint);
  joint->flags |= dJOINT_DISABLED;
}

int dJointIsEnabled (dxJoint *joint)
{
  dAASSERT (joint);
  return (joint->flags & dJOINT_DISABLED) == 0;
}

void dJointSetData (dxJoint *joint, void *data)
{
  dAASSERT (joint);
  joint->userdata = data;
}


void *dJointGetData (dxJoint *joint)
{
  dAASSERT (joint);
  return joint->userdata;
}


dJointType dJointGetType (dxJoint *joint)
{
  dAASSERT (joint);
  return joint->type();
}


dBodyID dJointGetBody (dxJoint *joint, int index)
{
  dAASSERT (joint);
  if (index == 0 || index == 1) {
    if (joint->flags & dJOINT_REVERSE) return joint->node[1-index].body;
    else return joint->node[index].body;
  }
  else return 0;
}


void dJointSetFeedback (dxJoint *joint, dJointFeedback *f)
{
  dAASSERT (joint);
  joint->feedback = f;
}


dJointFeedback *dJointGetFeedback (dxJoint *joint)
{
  dAASSERT (joint);
  return joint->feedback;
}



dJointID dConnectingJoint (dBodyID in_b1, dBodyID in_b2)
{
    dAASSERT (in_b1 || in_b2);

	dBodyID b1, b2;

	if (in_b1 == 0) {
		b1 = in_b2;
		b2 = in_b1;
	}
	else {
		b1 = in_b1;
		b2 = in_b2;
	}

    // look through b1's neighbour list for b2
    for (dxJointNode *n=b1->firstjoint; n; n=n->next) {
        if (n->body == b2) return n->joint;
    }

    return 0;
}



int dConnectingJointList (dBodyID in_b1, dBodyID in_b2, dJointID* out_list)
{
    dAASSERT (in_b1 || in_b2);


	dBodyID b1, b2;

	if (in_b1 == 0) {
		b1 = in_b2;
		b2 = in_b1;
	}
	else {
		b1 = in_b1;
		b2 = in_b2;
	}

    // look through b1's neighbour list for b2
    int numConnectingJoints = 0;
    for (dxJointNode *n=b1->firstjoint; n; n=n->next) {
        if (n->body == b2)
            out_list[numConnectingJoints++] = n->joint;
    }

    return numConnectingJoints;
}


int dAreConnected (dBodyID b1, dBodyID b2)
{
  dAASSERT (b1/* && b2*/); // b2 can be NULL to test for connection to environment
  // look through b1's neighbour list for b2
  for (dxJointNode *n=b1->firstjoint; n; n=n->next) {
    if (n->body == b2) return 1;
  }
  return 0;
}


int dAreConnectedExcluding (dBodyID b1, dBodyID b2, int joint_type)
{
  dAASSERT (b1/* && b2*/); // b2 can be NULL to test for connection to environment
  // look through b1's neighbour list for b2
  for (dxJointNode *n=b1->firstjoint; n; n=n->next) {
    if (dJointGetType (n->joint) != joint_type && n->body == b2) return 1;
  }
  return 0;
}

//****************************************************************************
// world

dxWorld * dWorldCreate()
{
  dxWorld *w = new dxWorld;
  w->firstbody = 0;
  w->firstjoint = 0;
  w->nb = 0;
  w->nj = 0;
  dSetZero (w->gravity,4);
  w->global_erp = REAL(0.2);
#if defined(dSINGLE)
  w->global_cfm = 1e-5f;
#elif defined(dDOUBLE)
  w->global_cfm = 1e-10;
#else
  #error dSINGLE or dDOUBLE must be defined
#endif

  w->body_flags = 0; // everything disabled

  w->wmem = 0;

  w->adis.idle_steps = 10;
  w->adis.idle_time = 0;
  w->adis.average_samples = 1;		// Default is 1 sample => Instantaneous velocity
  w->adis.angular_average_threshold = REAL(0.01)*REAL(0.01);	// (magnitude squared)
  w->adis.linear_average_threshold = REAL(0.01)*REAL(0.01);		// (magnitude squared)

  w->qs.num_iterations = 20;
  w->qs.w = REAL(1.3);

  w->contactp.max_vel = dInfinity;
  w->contactp.min_depth = 0;

  w->dampingp.linear_scale = 0;
  w->dampingp.angular_scale = 0;
  w->dampingp.linear_threshold = REAL(0.01) * REAL(0.01);
  w->dampingp.angular_threshold = REAL(0.01) * REAL(0.01);  
  w->max_angular_speed = dInfinity;

  return w;
}


void dWorldDestroy (dxWorld *w)
{
  // delete all bodies and joints
  dAASSERT (w);
  dxBody *nextb, *b = w->firstbody;
  while (b) {
    nextb = (dxBody*) b->next;
    dBodyDestroy(b); // calling here dBodyDestroy for correct destroying! (i.e. the average buffers)
    b = nextb;
  }
  dxJoint *nextj, *j = w->firstjoint;
  while (j) {
    nextj = (dxJoint*)j->next;
    if (j->flags & dJOINT_INGROUP) {
      // the joint is part of a group, so "deactivate" it instead
      j->world = 0;
      j->node[0].body = 0;
      j->node[0].next = 0;
      j->node[1].body = 0;
      j->node[1].next = 0;
      dMessage (0,"warning: destroying world containing grouped joints");
    }
    else {
        // TODO: shouldn't we call dJointDestroy()?
        size_t sz = j->size();
        j->~dxJoint();
        dFree (j,sz);
    }
    j = nextj;
  }

  if (w->wmem) {
    w->wmem->Release();
  }

  delete w;
}


void dWorldSetGravity (dWorldID w, dReal x, dReal y, dReal z)
{
  dAASSERT (w);
  w->gravity[0] = x;
  w->gravity[1] = y;
  w->gravity[2] = z;
}


void dWorldGetGravity (dWorldID w, dVector3 g)
{
  dAASSERT (w);
  g[0] = w->gravity[0];
  g[1] = w->gravity[1];
  g[2] = w->gravity[2];
}


void dWorldSetERP (dWorldID w, dReal erp)
{
  dAASSERT (w);
  w->global_erp = erp;
}


dReal dWorldGetERP (dWorldID w)
{
  dAASSERT (w);
  return w->global_erp;
}


void dWorldSetCFM (dWorldID w, dReal cfm)
{
  dAASSERT (w);
  w->global_cfm = cfm;
}


dReal dWorldGetCFM (dWorldID w)
{
  dAASSERT (w);
  return w->global_cfm;
}


int dWorldUseSharedWorkingMemory(dWorldID w, dWorldID from_world)
{
  dUASSERT (w,"bad world argument");

  bool result = false;

  if (from_world)
  {
    dUASSERT (!w->wmem, "world does already have working memory allocated"); // Prevent replacement of one memory object with another to avoid cases when smaller buffer replaces a larger one or memory manager changes.

    dxStepWorkingMemory *wmem = AllocateOnDemand(from_world->wmem);

    if (wmem)
    {
      // Even though there is an assertion check on entry still release existing
      // memory object for extra safety.
      if (w->wmem)
      {
        w->wmem->Release();
        w->wmem = NULL;
      }

      wmem->Addref();
      w->wmem = wmem;

      result = true;
    }
  }
  else
  {
    dxStepWorkingMemory *wmem = w->wmem;

    if (wmem)
    {
      wmem->Release();
      w->wmem = NULL;
    }

    result = true;
  }

  return result;
}

void dWorldCleanupWorkingMemory(dWorldID w)
{
  dUASSERT (w,"bad world argument");

  dxStepWorkingMemory *wmem = w->wmem;
  
  if (wmem)
  {
    wmem->CleanupMemory();
  }
}

int dWorldSetStepMemoryReservationPolicy(dWorldID w, const dWorldStepReserveInfo *policyinfo)
{
  dUASSERT (w,"bad world argument");
  dUASSERT (!policyinfo || (policyinfo->struct_size >= sizeof(*policyinfo) && policyinfo->reserve_factor >= 1.0f), "Bad policy info");

  bool result = false;

  dxStepWorkingMemory *wmem = policyinfo ? AllocateOnDemand(w->wmem) : w->wmem;

  if (wmem)
  {
    if (policyinfo)
    {
      wmem->SetMemoryReserveInfo(policyinfo->reserve_factor, policyinfo->reserve_minimum);
      result = wmem->GetMemoryReserveInfo() != NULL;
    }
    else
    {
      wmem->ResetMemoryReserveInfoToDefault();
      result = true;
    }
  }
  else if (!policyinfo)
  {
    result = true;
  }

  return result;
}

int dWorldSetStepMemoryManager(dWorldID w, const dWorldStepMemoryFunctionsInfo *memfuncs)
{
  dUASSERT (w,"bad world argument");
  dUASSERT (!memfuncs || memfuncs->struct_size >= sizeof(*memfuncs), "Bad functions info");

  bool result = false;

  dxStepWorkingMemory *wmem = memfuncs ? AllocateOnDemand(w->wmem) : w->wmem;

  if (wmem)
  {
    if (memfuncs)
    {
      wmem->SetMemoryManager(memfuncs->alloc_block, memfuncs->shrink_block, memfuncs->free_block);
      result = wmem->GetMemoryManager() != NULL;
    }
    else
    {
      wmem->ResetMemoryManagerToDefault();
      result = true;
    }
  }
  else if (!memfuncs)
  {
    result = true;
  }

  return result;
}


int dWorldStep (dWorldID w, dReal stepsize)
{
  dUASSERT (w,"bad world argument");
  dUASSERT (stepsize > 0,"stepsize must be > 0");

  bool result = false;

  if (dxReallocateWorldProcessContext (w, stepsize, &dxEstimateStepMemoryRequirements))
  {
    dxProcessIslands (w, stepsize, &dInternalStepIsland);
    
    result = true;
  }

  return result;
}

int dWorldQuickStep (dWorldID w, dReal stepsize)
{
  dUASSERT (w,"bad world argument");
  dUASSERT (stepsize > 0,"stepsize must be > 0");

  bool result = false;

  if (dxReallocateWorldProcessContext (w, stepsize, &dxEstimateQuickStepMemoryRequirements))
  {
    dxProcessIslands (w, stepsize, &dxQuickStepper);
    
    result = true;
  }

  return result;
}


void dWorldImpulseToForce (dWorldID w, dReal stepsize,
			   dReal ix, dReal iy, dReal iz,
			   dVector3 force)
{
  dAASSERT (w);
  stepsize = dRecip(stepsize);
  force[0] = stepsize * ix;
  force[1] = stepsize * iy;
  force[2] = stepsize * iz;
  // @@@ force[3] = 0;
}


// world auto-disable functions

dReal dWorldGetAutoDisableLinearThreshold (dWorldID w)
{
	dAASSERT(w);
	return dSqrt (w->adis.linear_average_threshold);
}


void dWorldSetAutoDisableLinearThreshold (dWorldID w, dReal linear_average_threshold)
{
	dAASSERT(w);
	w->adis.linear_average_threshold = linear_average_threshold * linear_average_threshold;
}


dReal dWorldGetAutoDisableAngularThreshold (dWorldID w)
{
	dAASSERT(w);
	return dSqrt (w->adis.angular_average_threshold);
}


void dWorldSetAutoDisableAngularThreshold (dWorldID w, dReal angular_average_threshold)
{
	dAASSERT(w);
	w->adis.angular_average_threshold = angular_average_threshold * angular_average_threshold;
}


int dWorldGetAutoDisableAverageSamplesCount (dWorldID w)
{
	dAASSERT(w);
	return w->adis.average_samples;
}


void dWorldSetAutoDisableAverageSamplesCount (dWorldID w, unsigned int average_samples_count)
{
	dAASSERT(w);
	w->adis.average_samples = average_samples_count;
}


int dWorldGetAutoDisableSteps (dWorldID w)
{
	dAASSERT(w);
	return w->adis.idle_steps;
}


void dWorldSetAutoDisableSteps (dWorldID w, int steps)
{
	dAASSERT(w);
	w->adis.idle_steps = steps;
}


dReal dWorldGetAutoDisableTime (dWorldID w)
{
	dAASSERT(w);
	return w->adis.idle_time;
}


void dWorldSetAutoDisableTime (dWorldID w, dReal time)
{
	dAASSERT(w);
	w->adis.idle_time = time;
}


int dWorldGetAutoDisableFlag (dWorldID w)
{
	dAASSERT(w);
	return w->body_flags & dxBodyAutoDisable;
}


void dWorldSetAutoDisableFlag (dWorldID w, int do_auto_disable)
{
	dAASSERT(w);
	if (do_auto_disable)
        	w->body_flags |= dxBodyAutoDisable;
	else
	        w->body_flags &= ~dxBodyAutoDisable;
}


// world damping functions

dReal dWorldGetLinearDampingThreshold(dWorldID w)
{
        dAASSERT(w);
        return dSqrt(w->dampingp.linear_threshold);
}

void dWorldSetLinearDampingThreshold(dWorldID w, dReal threshold)
{
        dAASSERT(w);
        w->dampingp.linear_threshold = threshold*threshold;
}

dReal dWorldGetAngularDampingThreshold(dWorldID w)
{
        dAASSERT(w);
        return dSqrt(w->dampingp.angular_threshold);
}

void dWorldSetAngularDampingThreshold(dWorldID w, dReal threshold)
{
        dAASSERT(w);
        w->dampingp.angular_threshold = threshold*threshold;
}

dReal dWorldGetLinearDamping(dWorldID w)
{
        dAASSERT(w);
        return w->dampingp.linear_scale;
}

void dWorldSetLinearDamping(dWorldID w, dReal scale)
{
        dAASSERT(w);
        if (scale)
                w->body_flags |= dxBodyLinearDamping;
        else
                w->body_flags &= ~dxBodyLinearDamping;
        w->dampingp.linear_scale = scale;
}

dReal dWorldGetAngularDamping(dWorldID w)
{
        dAASSERT(w);
        return w->dampingp.angular_scale;
}

void dWorldSetAngularDamping(dWorldID w, dReal scale)
{
        dAASSERT(w);
        if (scale)
                w->body_flags |= dxBodyAngularDamping;
        else
                w->body_flags &= ~dxBodyAngularDamping;
        w->dampingp.angular_scale = scale;
}

void dWorldSetDamping(dWorldID w, dReal linear_scale, dReal angular_scale)
{
        dAASSERT(w);
        dWorldSetLinearDamping(w, linear_scale);
        dWorldSetAngularDamping(w, angular_scale);
}

dReal dWorldGetMaxAngularSpeed(dWorldID w)
{
        dAASSERT(w);
        return w->max_angular_speed;
}

void dWorldSetMaxAngularSpeed(dWorldID w, dReal max_speed)
{
        dAASSERT(w);
        if (max_speed < dInfinity)
                w->body_flags |= dxBodyMaxAngularSpeed;
        else
                w->body_flags &= ~dxBodyMaxAngularSpeed;
        w->max_angular_speed = max_speed;
}


void dWorldSetQuickStepNumIterations (dWorldID w, int num)
{
	dAASSERT(w);
	w->qs.num_iterations = num;
}


int dWorldGetQuickStepNumIterations (dWorldID w)
{
	dAASSERT(w);
	return w->qs.num_iterations;
}


void dWorldSetQuickStepW (dWorldID w, dReal param)
{
	dAASSERT(w);
	w->qs.w = param;
}


dReal dWorldGetQuickStepW (dWorldID w)
{
	dAASSERT(w);
	return w->qs.w;
}


void dWorldSetContactMaxCorrectingVel (dWorldID w, dReal vel)
{
	dAASSERT(w);
	w->contactp.max_vel = vel;
}


dReal dWorldGetContactMaxCorrectingVel (dWorldID w)
{
	dAASSERT(w);
	return w->contactp.max_vel;
}


void dWorldSetContactSurfaceLayer (dWorldID w, dReal depth)
{
	dAASSERT(w);
	w->contactp.min_depth = depth;
}


dReal dWorldGetContactSurfaceLayer (dWorldID w)
{
	dAASSERT(w);
	return w->contactp.min_depth;
}

//****************************************************************************
// testing

#define NUM 100

#define DO(x)


extern "C" void dTestDataStructures()
{
  int i;
  DO(printf ("testDynamicsStuff()\n"));

  dBodyID body [NUM];
  int nb = 0;
  dJointID joint [NUM];
  int nj = 0;

  for (i=0; i<NUM; i++) body[i] = 0;
  for (i=0; i<NUM; i++) joint[i] = 0;

  DO(printf ("creating world\n"));
  dWorldID w = dWorldCreate();
  checkWorld (w);

  for (;;) {
    if (nb < NUM && dRandReal() > 0.5) {
      DO(printf ("creating body\n"));
      body[nb] = dBodyCreate (w);
      DO(printf ("\t--> %p\n",body[nb]));
      nb++;
      checkWorld (w);
      DO(printf ("%d BODIES, %d JOINTS\n",nb,nj));
    }
    if (nj < NUM && nb > 2 && dRandReal() > 0.5) {
      dBodyID b1 = body [dRand() % nb];
      dBodyID b2 = body [dRand() % nb];
      if (b1 != b2) {
	DO(printf ("creating joint, attaching to %p,%p\n",b1,b2));
	joint[nj] = dJointCreateBall (w,0);
	DO(printf ("\t-->%p\n",joint[nj]));
	checkWorld (w);
	dJointAttach (joint[nj],b1,b2);
	nj++;
	checkWorld (w);
	DO(printf ("%d BODIES, %d JOINTS\n",nb,nj));
      }
    }
    if (nj > 0 && nb > 2 && dRandReal() > 0.5) {
      dBodyID b1 = body [dRand() % nb];
      dBodyID b2 = body [dRand() % nb];
      if (b1 != b2) {
	int k = dRand() % nj;
	DO(printf ("reattaching joint %p\n",joint[k]));
	dJointAttach (joint[k],b1,b2);
	checkWorld (w);
	DO(printf ("%d BODIES, %d JOINTS\n",nb,nj));
      }
    }
    if (nb > 0 && dRandReal() > 0.5) {
      int k = dRand() % nb;
      DO(printf ("destroying body %p\n",body[k]));
      dBodyDestroy (body[k]);
      checkWorld (w);
      for (; k < (NUM-1); k++) body[k] = body[k+1];
      nb--;
      DO(printf ("%d BODIES, %d JOINTS\n",nb,nj));
    }
    if (nj > 0 && dRandReal() > 0.5) {
      int k = dRand() % nj;
      DO(printf ("destroying joint %p\n",joint[k]));
      dJointDestroy (joint[k]);
      checkWorld (w);
      for (; k < (NUM-1); k++) joint[k] = joint[k+1];
      nj--;
      DO(printf ("%d BODIES, %d JOINTS\n",nb,nj));
    }
  }

  /*
  printf ("creating world\n");
  dWorldID w = dWorldCreate();
  checkWorld (w);
  printf ("creating body\n");
  dBodyID b1 = dBodyCreate (w);
  checkWorld (w);
  printf ("creating body\n");
  dBodyID b2 = dBodyCreate (w);
  checkWorld (w);
  printf ("creating joint\n");
  dJointID j = dJointCreateBall (w);
  checkWorld (w);
  printf ("attaching joint\n");
  dJointAttach (j,b1,b2);
  checkWorld (w);
  printf ("destroying joint\n");
  dJointDestroy (j);
  checkWorld (w);
  printf ("destroying body\n");
  dBodyDestroy (b1);
  checkWorld (w);
  printf ("destroying body\n");
  dBodyDestroy (b2);
  checkWorld (w);
  printf ("destroying world\n");
  dWorldDestroy (w);
  */
}

//****************************************************************************
// configuration
#if 1
#define REGISTER_EXTENSION( __a )  #__a " "
#else
#define REGISTER_EXTENSION( __a )  "__a "
#endif
static const char ode_configuration[] = "ODE "

// EXTENSION LIST BEGIN
//**********************************

#ifdef dNODEBUG
REGISTER_EXTENSION( ODE_EXT_no_debug )
#endif // dNODEBUG

#if dTRIMESH_ENABLED
REGISTER_EXTENSION( ODE_EXT_trimesh )

	// tri-mesh extensions
	#if dTRIMESH_OPCODE
	REGISTER_EXTENSION( ODE_EXT_opcode )

		// opcode extensions
		#if dTRIMESH_16BIT_INDICES
		REGISTER_EXTENSION( ODE_OPC_16bit_indices )
		#endif

		#if !dTRIMESH_OPCODE_USE_OLD_TRIMESH_TRIMESH_COLLIDER
		REGISTER_EXTENSION( ODE_OPC_new_collider )
		#endif

	#endif // dTRIMESH_OPCODE

	#if dTRIMESH_GIMPACT
	REGISTER_EXTENSION( ODE_EXT_gimpact )

		// gimpact extensions
	#endif

#endif // dTRIMESH_ENABLED

#if dTLS_ENABLED
REGISTER_EXTENSION( ODE_EXT_mt_collisions )
#endif // dTLS_ENABLED

//**********************************
// EXTENSION LIST END

// These tokens are mutually exclusive, and always present
#ifdef dSINGLE
"ODE_single_precision"
#else
"ODE_double_precision"
#endif // dDOUBLE

; // END

const char* dGetConfiguration (void)
{
	return ode_configuration;
}


// Helper to check for a feature of ODE
int dCheckConfiguration( const char* extension )
{
	const char *start;
	char *where, *terminator;

	/* Feature names should not have spaces. */
	where = (char*)strchr(extension, ' ');
	if ( where || *extension == '\0')
		return 1;

	const char* config = dGetConfiguration();

	const size_t ext_length = strlen(extension);

	/* It takes a bit of care to be fool-proof. Don't be fooled by sub-strings, etc. */
	start = config;
	for (  ; ;  )
	{
		where = (char*)strstr((const char *) start, extension);
		if (!where)
			break;

		terminator = where + ext_length;
	
		if ( (where == start || *(where - 1) == ' ') && 
			 (*terminator == ' ' || *terminator == '\0') )
		{
			return 1;
		}
		
		start = terminator;
	}

	return 0;
}


// Local Variables:
// c-basic-offset:4
// End:
