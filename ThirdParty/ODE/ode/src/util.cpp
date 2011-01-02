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

#include <ode/ode.h>
#include "config.h"
#include "objects.h"
#include "joints/joint.h"
#include "util.h"

static void InternalFreeWorldProcessContext (dxWorldProcessContext *context);

//****************************************************************************
// Malloc based world stepping memory manager

/*extern */dxWorldProcessMemoryManager g_WorldProcessMallocMemoryManager(dAlloc, dRealloc, dFree);
/*extern */dxWorldProcessMemoryReserveInfo g_WorldProcessDefaultReserveInfo(dWORLDSTEP_RESERVEFACTOR_DEFAULT, dWORLDSTEP_RESERVESIZE_DEFAULT);


//****************************************************************************
// dxWorldProcessContext implementation

void dxWorldProcessContext::CleanupContext()
{
  ResetState();
  ClearPreallocations();
  FreePreallocationsContext();
}

void dxWorldProcessContext::SavePreallocations(int islandcount, int const *islandsizes, dxBody *const *bodies, dxJoint *const *joints)
{
  m_IslandCount = islandcount;
  m_pIslandSizes = islandsizes;
  m_pBodies = bodies;
  m_pJoints = joints;
}

void dxWorldProcessContext::RetrievePreallocations(int &islandcount, int const *&islandsizes, dxBody *const *&bodies, dxJoint *const *&joints)
{
  islandcount = m_IslandCount;
  islandsizes = m_pIslandSizes;
  bodies = m_pBodies;
  joints = m_pJoints;
}

void dxWorldProcessContext::OffsetPreallocations(size_t stOffset)
{
  // m_IslandCount = -- no offset for count
  m_pIslandSizes = m_pIslandSizes ? (int const *)((size_t)m_pIslandSizes + stOffset) : NULL;
  m_pBodies = m_pBodies ? (dxBody *const *)((size_t)m_pBodies + stOffset) : NULL;
  m_pJoints = m_pJoints ? (dxJoint *const *)((size_t)m_pJoints + stOffset) : NULL;
}

void dxWorldProcessContext::CopyPreallocations(const dxWorldProcessContext *othercontext)
{
  m_IslandCount = othercontext->m_IslandCount;
  m_pIslandSizes = othercontext->m_pIslandSizes;
  m_pBodies = othercontext->m_pBodies;
  m_pJoints = othercontext->m_pJoints;
}

void dxWorldProcessContext::ClearPreallocations()
{
  m_IslandCount = 0;
  m_pIslandSizes = NULL;
  m_pBodies = NULL;
  m_pJoints = NULL;
}

void dxWorldProcessContext::FreePreallocationsContext()
{
  if (m_pPreallocationcContext) {
    InternalFreeWorldProcessContext(m_pPreallocationcContext);
    m_pPreallocationcContext = NULL;
  }
}


//****************************************************************************
// Auto disabling

void dInternalHandleAutoDisabling (dxWorld *world, dReal stepsize)
{
	dxBody *bb;
	for ( bb=world->firstbody; bb; bb=(dxBody*)bb->next )
	{
		// don't freeze objects mid-air (patch 1586738)
		if ( bb->firstjoint == NULL ) continue;

		// nothing to do unless this body is currently enabled and has
		// the auto-disable flag set
		if ( (bb->flags & (dxBodyAutoDisable|dxBodyDisabled)) != dxBodyAutoDisable ) continue;

		// if sampling / threshold testing is disabled, we can never sleep.
		if ( bb->adis.average_samples == 0 ) continue;

		//
		// see if the body is idle
		//
		
#ifndef dNODEBUG
		// sanity check
		if ( bb->average_counter >= bb->adis.average_samples )
		{
			dUASSERT( bb->average_counter < bb->adis.average_samples, "buffer overflow" );

			// something is going wrong, reset the average-calculations
			bb->average_ready = 0; // not ready for average calculation
			bb->average_counter = 0; // reset the buffer index
		}
#endif // dNODEBUG

		// sample the linear and angular velocity
		bb->average_lvel_buffer[bb->average_counter][0] = bb->lvel[0];
		bb->average_lvel_buffer[bb->average_counter][1] = bb->lvel[1];
		bb->average_lvel_buffer[bb->average_counter][2] = bb->lvel[2];
		bb->average_avel_buffer[bb->average_counter][0] = bb->avel[0];
		bb->average_avel_buffer[bb->average_counter][1] = bb->avel[1];
		bb->average_avel_buffer[bb->average_counter][2] = bb->avel[2];
		bb->average_counter++;

		// buffer ready test
		if ( bb->average_counter >= bb->adis.average_samples )
		{
			bb->average_counter = 0; // fill the buffer from the beginning
			bb->average_ready = 1; // this body is ready now for average calculation
		}

		int idle = 0; // Assume it's in motion unless we have samples to disprove it.

		// enough samples?
		if ( bb->average_ready )
		{
			idle = 1; // Initial assumption: IDLE

			// the sample buffers are filled and ready for calculation
			dVector3 average_lvel, average_avel;

			// Store first velocity samples
			average_lvel[0] = bb->average_lvel_buffer[0][0];
			average_avel[0] = bb->average_avel_buffer[0][0];
			average_lvel[1] = bb->average_lvel_buffer[0][1];
			average_avel[1] = bb->average_avel_buffer[0][1];
			average_lvel[2] = bb->average_lvel_buffer[0][2];
			average_avel[2] = bb->average_avel_buffer[0][2];
			
			// If we're not in "instantaneous mode"
			if ( bb->adis.average_samples > 1 )
			{
				// add remaining velocities together
				for ( unsigned int i = 1; i < bb->adis.average_samples; ++i )
				{
					average_lvel[0] += bb->average_lvel_buffer[i][0];
					average_avel[0] += bb->average_avel_buffer[i][0];
					average_lvel[1] += bb->average_lvel_buffer[i][1];
					average_avel[1] += bb->average_avel_buffer[i][1];
					average_lvel[2] += bb->average_lvel_buffer[i][2];
					average_avel[2] += bb->average_avel_buffer[i][2];
				}

				// make average
				dReal r1 = dReal( 1.0 ) / dReal( bb->adis.average_samples );

				average_lvel[0] *= r1;
				average_avel[0] *= r1;
				average_lvel[1] *= r1;
				average_avel[1] *= r1;
				average_lvel[2] *= r1;
				average_avel[2] *= r1;
			}

			// threshold test
			dReal av_lspeed, av_aspeed;
			av_lspeed = dCalcVectorDot3( average_lvel, average_lvel );
			if ( av_lspeed > bb->adis.linear_average_threshold )
			{
				idle = 0; // average linear velocity is too high for idle
			}
			else
			{
				av_aspeed = dCalcVectorDot3( average_avel, average_avel );
				if ( av_aspeed > bb->adis.angular_average_threshold )
				{
					idle = 0; // average angular velocity is too high for idle
				}
			}
		}

		// if it's idle, accumulate steps and time.
		// these counters won't overflow because this code doesn't run for disabled bodies.
		if (idle) {
			bb->adis_stepsleft--;
			bb->adis_timeleft -= stepsize;
		}
		else {
			// Reset countdowns
			bb->adis_stepsleft = bb->adis.idle_steps;
			bb->adis_timeleft = bb->adis.idle_time;
		}

		// disable the body if it's idle for a long enough time
		if ( bb->adis_stepsleft <= 0 && bb->adis_timeleft <= 0 )
		{
			bb->flags |= dxBodyDisabled; // set the disable flag

			// disabling bodies should also include resetting the velocity
			// should prevent jittering in big "islands"
			bb->lvel[0] = 0;
			bb->lvel[1] = 0;
			bb->lvel[2] = 0;
			bb->avel[0] = 0;
			bb->avel[1] = 0;
			bb->avel[2] = 0;
		}
	}
}


//****************************************************************************
// body rotation

// return sin(x)/x. this has a singularity at 0 so special handling is needed
// for small arguments.

static inline dReal sinc (dReal x)
{
  // if |x| < 1e-4 then use a taylor series expansion. this two term expansion
  // is actually accurate to one LS bit within this range if double precision
  // is being used - so don't worry!
  if (dFabs(x) < 1.0e-4) return REAL(1.0) - x*x*REAL(0.166666666666666666667);
  else return dSin(x)/x;
}


// given a body b, apply its linear and angular rotation over the time
// interval h, thereby adjusting its position and orientation.

void dxStepBody (dxBody *b, dReal h)
{
  // cap the angular velocity
  if (b->flags & dxBodyMaxAngularSpeed) {
    const dReal max_ang_speed = b->max_angular_speed;
    const dReal aspeed = dCalcVectorDot3( b->avel, b->avel );
    if (aspeed > max_ang_speed*max_ang_speed) {
      const dReal coef = max_ang_speed/dSqrt(aspeed);
      dScaleVector3(b->avel, coef);
    }
  }
  // end of angular velocity cap


  // handle linear velocity
  for (int j=0; j<3; j++) b->posr.pos[j] += h * b->lvel[j];

  if (b->flags & dxBodyFlagFiniteRotation) {
    dVector3 irv;	// infitesimal rotation vector
    dQuaternion q;	// quaternion for finite rotation

    if (b->flags & dxBodyFlagFiniteRotationAxis) {
      // split the angular velocity vector into a component along the finite
      // rotation axis, and a component orthogonal to it.
      dVector3 frv;		// finite rotation vector
      dReal k = dCalcVectorDot3 (b->finite_rot_axis,b->avel);
      frv[0] = b->finite_rot_axis[0] * k;
      frv[1] = b->finite_rot_axis[1] * k;
      frv[2] = b->finite_rot_axis[2] * k;
      irv[0] = b->avel[0] - frv[0];
      irv[1] = b->avel[1] - frv[1];
      irv[2] = b->avel[2] - frv[2];

      // make a rotation quaternion q that corresponds to frv * h.
      // compare this with the full-finite-rotation case below.
      h *= REAL(0.5);
      dReal theta = k * h;
      q[0] = dCos(theta);
      dReal s = sinc(theta) * h;
      q[1] = frv[0] * s;
      q[2] = frv[1] * s;
      q[3] = frv[2] * s;
    }
    else {
      // make a rotation quaternion q that corresponds to w * h
      dReal wlen = dSqrt (b->avel[0]*b->avel[0] + b->avel[1]*b->avel[1] +
        b->avel[2]*b->avel[2]);
      h *= REAL(0.5);
      dReal theta = wlen * h;
      q[0] = dCos(theta);
      dReal s = sinc(theta) * h;
      q[1] = b->avel[0] * s;
      q[2] = b->avel[1] * s;
      q[3] = b->avel[2] * s;
    }

    // do the finite rotation
    dQuaternion q2;
    dQMultiply0 (q2,q,b->q);
    for (int j=0; j<4; j++) b->q[j] = q2[j];

    // do the infitesimal rotation if required
    if (b->flags & dxBodyFlagFiniteRotationAxis) {
      dReal dq[4];
      dWtoDQ (irv,b->q,dq);
      for (int j=0; j<4; j++) b->q[j] += h * dq[j];
    }
  }
  else {
    // the normal way - do an infitesimal rotation
    dReal dq[4];
    dWtoDQ (b->avel,b->q,dq);
    for (int j=0; j<4; j++) b->q[j] += h * dq[j];
  }

  // normalize the quaternion and convert it to a rotation matrix
  dNormalize4 (b->q);
  dQtoR (b->q,b->posr.R);

  // notify all attached geoms that this body has moved
  for (dxGeom *geom = b->geom; geom; geom = dGeomGetBodyNext (geom))
    dGeomMoved (geom);

  // notify the user
  if (b->moved_callback)
    b->moved_callback(b);


  // damping
  if (b->flags & dxBodyLinearDamping) {
    const dReal lin_threshold = b->dampingp.linear_threshold;
    const dReal lin_speed = dCalcVectorDot3( b->lvel, b->lvel );
    if ( lin_speed > lin_threshold) {
      const dReal k = 1 - b->dampingp.linear_scale;
      dScaleVector3(b->lvel, k);
    }
  }
  if (b->flags & dxBodyAngularDamping) {
    const dReal ang_threshold = b->dampingp.angular_threshold;
    const dReal ang_speed = dCalcVectorDot3( b->avel, b->avel );
    if ( ang_speed > ang_threshold) {
      const dReal k = 1 - b->dampingp.angular_scale;
      dScaleVector3(b->avel, k);
    }
  }
}


//****************************************************************************
// island processing

// This estimates dynamic memory requirements for dxProcessIslands
static size_t EstimateIslandsProcessingMemoryRequirements(dxWorld *world, size_t &sesize)
{
  size_t res = 0;

  size_t islandcounts = dEFFICIENT_SIZE(world->nb * 2 * sizeof(int));
  res += islandcounts;

  size_t bodiessize = dEFFICIENT_SIZE(world->nb * sizeof(dxBody*));
  size_t jointssize = dEFFICIENT_SIZE(world->nj * sizeof(dxJoint*));
  res += bodiessize + jointssize;

  sesize = (bodiessize < jointssize) ? bodiessize : jointssize;
  return res;
}

static size_t BuildIslandsAndEstimateStepperMemoryRequirements(dxWorldProcessContext *context, 
  dxWorld *world, dReal stepsize, dmemestimate_fn_t stepperestimate)
{
  const int sizeelements = 2;
  size_t maxreq = 0;

  // handle auto-disabling of bodies
  dInternalHandleAutoDisabling (world,stepsize);

  int nb = world->nb, nj = world->nj;
  // Make array for island body/joint counts
  int *islandsizes = context->AllocateArray<int>(2 * nb);
  int *sizescurr;

  // make arrays for body and joint lists (for a single island) to go into
  dxBody **body = context->AllocateArray<dxBody *>(nb);
  dxJoint **joint = context->AllocateArray<dxJoint *>(nj);

  BEGIN_STATE_SAVE(context, stackstate) {
    // allocate a stack of unvisited bodies in the island. the maximum size of
    // the stack can be the lesser of the number of bodies or joints, because
    // new bodies are only ever added to the stack by going through untagged
    // joints. all the bodies in the stack must be tagged!
    int stackalloc = (nj < nb) ? nj : nb;
    dxBody **stack = context->AllocateArray<dxBody *>(stackalloc);

    {
      // set all body/joint tags to 0
      for (dxBody *b=world->firstbody; b; b=(dxBody*)b->next) b->tag = 0;
      for (dxJoint *j=world->firstjoint; j; j=(dxJoint*)j->next) j->tag = 0;
    }

    sizescurr = islandsizes;
    dxBody **bodystart = body;
    dxJoint **jointstart = joint;
    for (dxBody *bb=world->firstbody; bb; bb=(dxBody*)bb->next) {
      // get bb = the next enabled, untagged body, and tag it
      if (!bb->tag) {
        if (!(bb->flags & dxBodyDisabled)) {
          bb->tag = 1;

          dxBody **bodycurr = bodystart;
          dxJoint **jointcurr = jointstart;

          // tag all bodies and joints starting from bb.
          *bodycurr++ = bb;

          int stacksize = 0;
          dxBody *b = bb;

          while (true) {
            // traverse and tag all body's joints, add untagged connected bodies
            // to stack
            for (dxJointNode *n=b->firstjoint; n; n=n->next) {
              dxJoint *njoint = n->joint;
              if (!njoint->tag) {
                if (njoint->isEnabled()) {
                  njoint->tag = 1;
                  *jointcurr++ = njoint;

                  dxBody *nbody = n->body;
                  // Body disabled flag is not checked here. This is how auto-enable works.
                  if (nbody && nbody->tag <= 0) {
                    nbody->tag = 1;
                    // Make sure all bodies are in the enabled state.
                    nbody->flags &= ~dxBodyDisabled;
                    stack[stacksize++] = nbody;
                  }
                } else {
                  njoint->tag = -1; // Used in Step to prevent search over disabled joints (not needed for QuickStep so far)
                }
              }
            }
            dIASSERT(stacksize <= world->nb);
            dIASSERT(stacksize <= world->nj);

            if (stacksize == 0) {
              break;
            }

            b = stack[--stacksize];	// pop body off stack
            *bodycurr++ = b;	// put body on body list
          }

          int bcount = bodycurr - bodystart;
          int jcount = jointcurr - jointstart;
          sizescurr[0] = bcount;
          sizescurr[1] = jcount;
          sizescurr += sizeelements;

          size_t islandreq = stepperestimate(bodystart, bcount, jointstart, jcount);
          maxreq = (maxreq > islandreq) ? maxreq : islandreq;

          bodystart = bodycurr;
          jointstart = jointcurr;
        } else {
          bb->tag = -1; // Not used so far (assigned to retain consistency with joints)
        }
      }
    }
  } END_STATE_SAVE(context, stackstate);

# ifndef dNODEBUG
  // if debugging, check that all objects (except for disabled bodies,
  // unconnected joints, and joints that are connected to disabled bodies)
  // were tagged.
  {
    for (dxBody *b=world->firstbody; b; b=(dxBody*)b->next) {
      if (b->flags & dxBodyDisabled) {
        if (b->tag > 0) dDebug (0,"disabled body tagged");
      }
      else {
        if (b->tag <= 0) dDebug (0,"enabled body not tagged");
      }
    }
    for (dxJoint *j=world->firstjoint; j; j=(dxJoint*)j->next) {
      if ( (( j->node[0].body && (j->node[0].body->flags & dxBodyDisabled)==0 ) ||
        (j->node[1].body && (j->node[1].body->flags & dxBodyDisabled)==0) )
        && 
        j->isEnabled() ) {
          if (j->tag <= 0) dDebug (0,"attached enabled joint not tagged");
      }
      else {
        if (j->tag > 0) dDebug (0,"unattached or disabled joint tagged");
      }
    }
  }
# endif

  int islandcount = (sizescurr - islandsizes) / sizeelements;
  context->SavePreallocations(islandcount, islandsizes, body, joint);

  return maxreq;
}

// this groups all joints and bodies in a world into islands. all objects
// in an island are reachable by going through connected bodies and joints.
// each island can be simulated separately.
// note that joints that are not attached to anything will not be included
// in any island, an so they do not affect the simulation.
//
// this function starts new island from unvisited bodies. however, it will
// never start a new islands from a disabled body. thus islands of disabled
// bodies will not be included in the simulation. disabled bodies are
// re-enabled if they are found to be part of an active island.

void dxProcessIslands (dxWorld *world, dReal stepsize, dstepper_fn_t stepper)
{
  const int sizeelements = 2;

  dxStepWorkingMemory *wmem = world->wmem;
  dIASSERT(wmem != NULL);

  dxWorldProcessContext *context = wmem->GetWorldProcessingContext(); 

  int islandcount;
  int const *islandsizes;
  dxBody *const *body;
  dxJoint *const *joint;
  context->RetrievePreallocations(islandcount, islandsizes, body, joint);

  dxBody *const *bodystart = body;
  dxJoint *const *jointstart = joint;

  int const *const sizesend = islandsizes + islandcount * sizeelements;
  for (int const *sizescurr = islandsizes; sizescurr != sizesend; sizescurr += sizeelements) {
    int bcount = sizescurr[0];
    int jcount = sizescurr[1];

    BEGIN_STATE_SAVE(context, stepperstate) {
      // now do something with body and joint lists
      stepper (context,world,bodystart,bcount,jointstart,jcount,stepsize);
    } END_STATE_SAVE(context, stepperstate);

    bodystart += bcount;
    jointstart += jcount;
  }

  context->CleanupContext();
  dIASSERT(context->IsStructureValid());
}

//****************************************************************************
// World processing context management

static size_t AdjustArenaSizeForReserveRequirements(size_t arenareq, float rsrvfactor, unsigned rsrvminimum)
{
  float scaledarena = arenareq * rsrvfactor;
  size_t adjustedarena = (scaledarena < SIZE_MAX) ? (size_t)scaledarena : SIZE_MAX;
  size_t boundedarena = (adjustedarena > rsrvminimum) ? adjustedarena : (size_t)rsrvminimum;
  return dEFFICIENT_SIZE(boundedarena);
}

static dxWorldProcessContext *InternalReallocateWorldProcessContext (
  dxWorldProcessContext *oldcontext, size_t memreq, 
  const dxWorldProcessMemoryManager *memmgr, float rsrvfactor, unsigned rsrvminimum)
{
  dxWorldProcessContext *context = oldcontext;
  bool allocsuccess = false;

  size_t oldarenasize; 
  void *pOldArena;

  do {
    size_t oldmemsize = oldcontext ? oldcontext->GetMemorySize() : 0;
    if (!oldcontext || oldmemsize < memreq) {
      oldarenasize = oldcontext ? dxWorldProcessContext::MakeArenaSize(oldmemsize) : 0;
      pOldArena = oldcontext ? oldcontext->m_pArenaBegin : NULL;

      if (!dxWorldProcessContext::IsArenaPossible(memreq)) {
        break;
      }

      size_t arenareq = dxWorldProcessContext::MakeArenaSize(memreq);
      size_t arenareq_with_reserve = AdjustArenaSizeForReserveRequirements(arenareq, rsrvfactor, rsrvminimum);
      size_t memreq_with_reserve = memreq + (arenareq_with_reserve - arenareq);

      if (oldcontext) {

        if (oldcontext->m_pAllocCurrent != oldcontext->m_pAllocBegin) {

          // Save old efficient offset and meaningful data size for the case if 
          // reallocation throws the block at different efficient offset
          size_t oldcontextofs = (size_t)oldcontext - (size_t)pOldArena;
          size_t datasize = (size_t)oldcontext->m_pAllocCurrent - (size_t)oldcontext;
          
          // Extra EFFICIENT_ALIGNMENT bytes might be needed after re-allocation with different alignment
          size_t shrunkarenasize = dEFFICIENT_SIZE(datasize + oldcontextofs) + EFFICIENT_ALIGNMENT;
          if (shrunkarenasize < oldarenasize) {

            void *pShrunkOldArena = oldcontext->m_pArenaMemMgr->m_fnShrink(pOldArena, oldarenasize, shrunkarenasize);
            if (!pShrunkOldArena) {
              break;
            }

            // In case if shrinking is not supported and memory manager had to allocate-copy-free
            if (pShrunkOldArena != pOldArena) {
              dxWorldProcessContext *shrunkcontext = (dxWorldProcessContext *)dEFFICIENT_PTR(pShrunkOldArena);

              // Preform data shift in case if efficient alignment of new block
              // does not match that of old block
              size_t shrunkcontextofs = (size_t)shrunkcontext - (size_t)pShrunkOldArena;
              size_t offsetdiff = oldcontextofs - shrunkcontextofs;
              if (offsetdiff != 0) {
                memmove(shrunkcontext, (void *)((size_t)shrunkcontext + offsetdiff), datasize);
              }

              // Make sure allocation pointers are valid - that is necessary to
              // be able to calculate size and free old arena later
              size_t shrunkdatasize = dxWorldProcessContext::MakeBufferSize(shrunkarenasize);
              void *blockbegin = dEFFICIENT_PTR(shrunkcontext + 1);
              void *blockend = dOFFSET_EFFICIENTLY(blockbegin, shrunkdatasize);
              shrunkcontext->m_pAllocBegin = blockbegin;
              shrunkcontext->m_pAllocEnd = blockend;
              shrunkcontext->m_pAllocCurrent = blockend; // -- set to end to prevent possibility of further allocation
              shrunkcontext->m_pArenaBegin = pShrunkOldArena;

              size_t stOffset = ((size_t)pShrunkOldArena - (size_t)pOldArena) - offsetdiff;
              shrunkcontext->OffsetPreallocations(stOffset);

              oldcontext = shrunkcontext;

              // Reassign to old arena variables for potential freeing at exit
              pOldArena = pShrunkOldArena;
            }

            // Reassign to old arena variables for potential freeing at exit
            oldarenasize = shrunkarenasize;
          }

        } else {
          oldcontext->m_pArenaMemMgr->m_fnFree(pOldArena, oldarenasize);
          oldcontext = NULL;
          
          // Zero variables to avoid another freeing on exit
          pOldArena = NULL;
          oldarenasize = 0;
        }
      }

      // Allocate new arena
      void *pNewArena = memmgr->m_fnAlloc(arenareq_with_reserve);
      if (!pNewArena) {
        break;
      }

      context = (dxWorldProcessContext *)dEFFICIENT_PTR(pNewArena);

      void *blockbegin = dEFFICIENT_PTR(context + 1);
      void *blockend = dOFFSET_EFFICIENTLY(blockbegin, memreq_with_reserve);

      context->m_pAllocBegin = blockbegin;
      context->m_pAllocEnd = blockend;
      context->m_pArenaBegin = pNewArena;
      context->m_pAllocCurrent = blockbegin;

      if (oldcontext) {
        context->CopyPreallocations(oldcontext);
      } else {
        context->ClearPreallocations();
      }

      context->m_pArenaMemMgr = memmgr;
      context->m_pPreallocationcContext = oldcontext;
    }

    allocsuccess = true;
  } while (false);

  if (!allocsuccess) {
    if (pOldArena) {
      dIASSERT(oldcontext);
      oldcontext->m_pArenaMemMgr->m_fnFree(pOldArena, oldarenasize);
    }
    context = NULL;
  }

  return context;
}

static void InternalFreeWorldProcessContext (dxWorldProcessContext *context)
{
  size_t memsize = context->GetMemorySize();
  size_t arenasize = dxWorldProcessContext::MakeArenaSize(memsize);

  void *pArenaBegin = context->m_pArenaBegin;
  context->m_pArenaMemMgr->m_fnFree(pArenaBegin, arenasize);
}


bool dxReallocateWorldProcessContext (dxWorld *world, 
  dReal stepsize, dmemestimate_fn_t stepperestimate)
{
  dxStepWorkingMemory *wmem = AllocateOnDemand(world->wmem);
  if (!wmem) return false;

  dxWorldProcessContext *oldcontext = wmem->GetWorldProcessingContext();
  dIASSERT (!oldcontext || oldcontext->IsStructureValid());

  const dxWorldProcessMemoryReserveInfo *reserveinfo = wmem->SureGetMemoryReserveInfo();
  const dxWorldProcessMemoryManager *memmgr = wmem->SureGetMemoryManager();

  dxWorldProcessContext *context = oldcontext;

  size_t sesize;
  size_t islandsreq = EstimateIslandsProcessingMemoryRequirements(world, sesize);
  dIASSERT(islandsreq == dEFFICIENT_SIZE(islandsreq));
  dIASSERT(sesize == dEFFICIENT_SIZE(sesize));

  size_t stepperestimatereq = islandsreq + sesize;
  context = InternalReallocateWorldProcessContext(context, stepperestimatereq, memmgr, 1.0f, reserveinfo->m_uiReserveMinimum);
  
  if (context)
  {
    size_t stepperreq = BuildIslandsAndEstimateStepperMemoryRequirements(context, world, stepsize, stepperestimate);
    dIASSERT(stepperreq == dEFFICIENT_SIZE(stepperreq));

    size_t memreq = stepperreq + islandsreq;
    context = InternalReallocateWorldProcessContext(context, memreq, memmgr, reserveinfo->m_fReserveFactor, reserveinfo->m_uiReserveMinimum);
  }

  wmem->SetWorldProcessingContext(context);
  return context != NULL;
}

dxWorldProcessContext *dxReallocateTemporayWorldProcessContext(dxWorldProcessContext *oldcontext, 
  size_t memreq, const dxWorldProcessMemoryManager *memmgr/*=NULL*/, const dxWorldProcessMemoryReserveInfo *reserveinfo/*=NULL*/)
{
  dxWorldProcessContext *context = oldcontext;

  if (context && context->GetMemorySize() < memreq) {
    dIASSERT(!context->IsPreallocationsContextAssigned());

    InternalFreeWorldProcessContext(context);
    context = NULL;
  }

  if (context == NULL) {
    const dxWorldProcessMemoryManager *surememmgr = memmgr ? memmgr : &g_WorldProcessMallocMemoryManager;
    const dxWorldProcessMemoryReserveInfo *surereserveinfo = reserveinfo ? reserveinfo : &g_WorldProcessDefaultReserveInfo;
    context = InternalReallocateWorldProcessContext(context, memreq, surememmgr, surereserveinfo->m_fReserveFactor, surereserveinfo->m_uiReserveMinimum);
  }

  return context;
}

void dxFreeWorldProcessContext (dxWorldProcessContext *context)
{
  // Free old arena for the case if context is freed after reallocation without
  // a call to world stepping function
  context->FreePreallocationsContext();

  // Assert validity after old arena is freed as validation includes checking for
  // old arena to be absent
  dUASSERT (context->IsStructureValid(), "invalid context structure");

  InternalFreeWorldProcessContext(context);
}



