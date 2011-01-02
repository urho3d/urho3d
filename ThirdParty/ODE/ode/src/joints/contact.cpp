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


#include "config.h"
#include "contact.h"
#include "joint_internal.h"



//****************************************************************************
// contact

dxJointContact::dxJointContact( dxWorld *w ) :
        dxJoint( w )
{
}


void 
dxJointContact::getSureMaxInfo( SureMaxInfo* info )
{
    info->max_m = 3; // ...as the actual m is very likely to hit the maximum
}


void
dxJointContact::getInfo1( dxJoint::Info1 *info )
{
    // make sure mu's >= 0, then calculate number of constraint rows and number
    // of unbounded rows.
    int m = 1, nub = 0;
    if ( contact.surface.mu < 0 ) contact.surface.mu = 0;
    if ( contact.surface.mode & dContactMu2 )
    {
        if ( contact.surface.mu > 0 ) m++;
        if ( contact.surface.mu2 < 0 ) contact.surface.mu2 = 0;
        if ( contact.surface.mu2 > 0 ) m++;
        if ( contact.surface.mu  == dInfinity ) nub ++;
        if ( contact.surface.mu2 == dInfinity ) nub ++;
    }
    else
    {
        if ( contact.surface.mu > 0 ) m += 2;
        if ( contact.surface.mu == dInfinity ) nub += 2;
    }

    the_m = m;
    info->m = m;
    info->nub = nub;
}


void
dxJointContact::getInfo2( dxJoint::Info2 *info )
{
    int s = info->rowskip;
    int s2 = 2 * s;

    // get normal, with sign adjusted for body1/body2 polarity
    dVector3 normal;
    if ( flags & dJOINT_REVERSE )
    {
        normal[0] = - contact.geom.normal[0];
        normal[1] = - contact.geom.normal[1];
        normal[2] = - contact.geom.normal[2];
    }
    else
    {
        normal[0] = contact.geom.normal[0];
        normal[1] = contact.geom.normal[1];
        normal[2] = contact.geom.normal[2];
    }
    normal[3] = 0; // @@@ hmmm

    // c1,c2 = contact points with respect to body PORs
    dVector3 c1, c2 = {0,0,0};
    c1[0] = contact.geom.pos[0] - node[0].body->posr.pos[0];
    c1[1] = contact.geom.pos[1] - node[0].body->posr.pos[1];
    c1[2] = contact.geom.pos[2] - node[0].body->posr.pos[2];

    // set jacobian for normal
    info->J1l[0] = normal[0];
    info->J1l[1] = normal[1];
    info->J1l[2] = normal[2];
    dCalcVectorCross3( info->J1a, c1, normal );
    if ( node[1].body )
    {
        c2[0] = contact.geom.pos[0] - node[1].body->posr.pos[0];
        c2[1] = contact.geom.pos[1] - node[1].body->posr.pos[1];
        c2[2] = contact.geom.pos[2] - node[1].body->posr.pos[2];
        info->J2l[0] = -normal[0];
        info->J2l[1] = -normal[1];
        info->J2l[2] = -normal[2];
        dCalcVectorCross3( info->J2a, c2, normal );
        dNegateVector3( info->J2a );
    }

    // set right hand side and cfm value for normal
    dReal erp = info->erp;
    if ( contact.surface.mode & dContactSoftERP )
        erp = contact.surface.soft_erp;
    dReal k = info->fps * erp;
    dReal depth = contact.geom.depth - world->contactp.min_depth;
    if ( depth < 0 ) depth = 0;

    if ( contact.surface.mode & dContactSoftCFM )
        info->cfm[0] = contact.surface.soft_cfm;


    dReal motionN = 0;
    if ( contact.surface.mode & dContactMotionN )
        motionN = contact.surface.motionN;

    const dReal pushout = k * depth + motionN;
    info->c[0] = pushout;

    // note: this cap should not limit bounce velocity
    const dReal maxvel = world->contactp.max_vel;
    if ( info->c[0] > maxvel )
        info->c[0] = maxvel;

    // deal with bounce
    if ( contact.surface.mode & dContactBounce )
    {
        // calculate outgoing velocity (-ve for incoming contact)
        dReal outgoing = dCalcVectorDot3( info->J1l, node[0].body->lvel )
                         + dCalcVectorDot3( info->J1a, node[0].body->avel );
        if ( node[1].body )
        {
            outgoing += dCalcVectorDot3( info->J2l, node[1].body->lvel )
                        + dCalcVectorDot3( info->J2a, node[1].body->avel );
        }
        outgoing -= motionN;
        // only apply bounce if the outgoing velocity is greater than the
        // threshold, and if the resulting c[0] exceeds what we already have.
        if ( contact.surface.bounce_vel >= 0 &&
                ( -outgoing ) > contact.surface.bounce_vel )
        {
            dReal newc = - contact.surface.bounce * outgoing + motionN;
            if ( newc > info->c[0] ) info->c[0] = newc;
        }
    }

    // set LCP limits for normal
    info->lo[0] = 0;
    info->hi[0] = dInfinity;

    // now do jacobian for tangential forces
    dVector3 t1, t2; // two vectors tangential to normal

    // first friction direction
    if ( the_m >= 2 )
    {
        if ( contact.surface.mode & dContactFDir1 )   // use fdir1 ?
        {
            t1[0] = contact.fdir1[0];
            t1[1] = contact.fdir1[1];
            t1[2] = contact.fdir1[2];
            dCalcVectorCross3( t2, normal, t1 );
        }
        else
        {
            dPlaneSpace( normal, t1, t2 );
        }
        info->J1l[s+0] = t1[0];
        info->J1l[s+1] = t1[1];
        info->J1l[s+2] = t1[2];
        dCalcVectorCross3( info->J1a + s, c1, t1 );
        if ( node[1].body )
        {
            info->J2l[s+0] = -t1[0];
            info->J2l[s+1] = -t1[1];
            info->J2l[s+2] = -t1[2];
            dReal *J2a_plus_s = info->J2a + s;
            dCalcVectorCross3( J2a_plus_s, c2, t1 );
            dNegateVector3( J2a_plus_s );
        }
        // set right hand side
        if ( contact.surface.mode & dContactMotion1 )
        {
            info->c[1] = contact.surface.motion1;
        }
        // set LCP bounds and friction index. this depends on the approximation
        // mode
        info->lo[1] = -contact.surface.mu;
        info->hi[1] = contact.surface.mu;
        if ( contact.surface.mode & dContactApprox1_1 )
            info->findex[1] = 0;

        // set slip (constraint force mixing)
        if ( contact.surface.mode & dContactSlip1 )
            info->cfm[1] = contact.surface.slip1;
    }

    // second friction direction
    if ( the_m >= 3 )
    {
        info->J1l[s2+0] = t2[0];
        info->J1l[s2+1] = t2[1];
        info->J1l[s2+2] = t2[2];
        dCalcVectorCross3( info->J1a + s2, c1, t2 );
        if ( node[1].body )
        {
            info->J2l[s2+0] = -t2[0];
            info->J2l[s2+1] = -t2[1];
            info->J2l[s2+2] = -t2[2];
            dReal *J2a_plus_s2 = info->J2a + s2;
            dCalcVectorCross3( J2a_plus_s2, c2, t2 );
            dNegateVector3( J2a_plus_s2 );
        }
        // set right hand side
        if ( contact.surface.mode & dContactMotion2 )
        {
            info->c[2] = contact.surface.motion2;
        }
        // set LCP bounds and friction index. this depends on the approximation
        // mode
        if ( contact.surface.mode & dContactMu2 )
        {
            info->lo[2] = -contact.surface.mu2;
            info->hi[2] = contact.surface.mu2;
        }
        else
        {
            info->lo[2] = -contact.surface.mu;
            info->hi[2] = contact.surface.mu;
        }
        if ( contact.surface.mode & dContactApprox1_2 )
            info->findex[2] = 0;

        // set slip (constraint force mixing)
        if ( contact.surface.mode & dContactSlip2 )
            info->cfm[2] = contact.surface.slip2;
    }
}

dJointType
dxJointContact::type() const
{
    return dJointTypeContact;
}


size_t
dxJointContact::size() const
{
    return sizeof( *this );
}

