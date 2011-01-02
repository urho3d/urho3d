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
#include "hinge.h"
#include "joint_internal.h"


//****************************************************************************
// hinge

dxJointHinge::dxJointHinge( dxWorld *w ) :
        dxJoint( w )
{
    dSetZero( anchor1, 4 );
    dSetZero( anchor2, 4 );
    dSetZero( axis1, 4 );
    axis1[0] = 1;
    dSetZero( axis2, 4 );
    axis2[0] = 1;
    dSetZero( qrel, 4 );
    limot.init( world );
}


void 
dxJointHinge::getSureMaxInfo( SureMaxInfo* info )
{
    info->max_m = 6;
}


void
dxJointHinge::getInfo1( dxJoint::Info1 *info )
{
    info->nub = 5;

    // see if joint is powered
    if ( limot.fmax > 0 )
        info->m = 6; // powered hinge needs an extra constraint row
    else info->m = 5;

    // see if we're at a joint limit.
    if (( limot.lostop >= -M_PI || limot.histop <= M_PI ) &&
            limot.lostop <= limot.histop )
    {
        dReal angle = getHingeAngle( node[0].body,
                                     node[1].body,
                                     axis1, qrel );
        if ( limot.testRotationalLimit( angle ) )
            info->m = 6;
    }
}


void
dxJointHinge::getInfo2( dxJoint::Info2 *info )
{
    // set the three ball-and-socket rows
    setBall( this, info, anchor1, anchor2 );

    // set the two hinge rows. the hinge axis should be the only unconstrained
    // rotational axis, the angular velocity of the two bodies perpendicular to
    // the hinge axis should be equal. thus the constraint equations are
    //    p*w1 - p*w2 = 0
    //    q*w1 - q*w2 = 0
    // where p and q are unit vectors normal to the hinge axis, and w1 and w2
    // are the angular velocity vectors of the two bodies.

    dVector3 ax1;  // length 1 joint axis in global coordinates, from 1st body
    dVector3 p, q; // plane space vectors for ax1
    dMultiply0_331( ax1, node[0].body->posr.R, axis1 );
    dPlaneSpace( ax1, p, q );

    int s3 = 3 * info->rowskip;
    int s4 = 4 * info->rowskip;

    info->J1a[s3+0] = p[0];
    info->J1a[s3+1] = p[1];
    info->J1a[s3+2] = p[2];
    info->J1a[s4+0] = q[0];
    info->J1a[s4+1] = q[1];
    info->J1a[s4+2] = q[2];

    if ( node[1].body )
    {
        info->J2a[s3+0] = -p[0];
        info->J2a[s3+1] = -p[1];
        info->J2a[s3+2] = -p[2];
        info->J2a[s4+0] = -q[0];
        info->J2a[s4+1] = -q[1];
        info->J2a[s4+2] = -q[2];
    }

    // compute the right hand side of the constraint equation. set relative
    // body velocities along p and q to bring the hinge back into alignment.
    // if ax1,ax2 are the unit length hinge axes as computed from body1 and
    // body2, we need to rotate both bodies along the axis u = (ax1 x ax2).
    // if `theta' is the angle between ax1 and ax2, we need an angular velocity
    // along u to cover angle erp*theta in one step :
    //   |angular_velocity| = angle/time = erp*theta / stepsize
    //                      = (erp*fps) * theta
    //    angular_velocity  = |angular_velocity| * (ax1 x ax2) / |ax1 x ax2|
    //                      = (erp*fps) * theta * (ax1 x ax2) / sin(theta)
    // ...as ax1 and ax2 are unit length. if theta is smallish,
    // theta ~= sin(theta), so
    //    angular_velocity  = (erp*fps) * (ax1 x ax2)
    // ax1 x ax2 is in the plane space of ax1, so we project the angular
    // velocity to p and q to find the right hand side.

    dVector3 ax2, b;
    if ( node[1].body )
    {
        dMultiply0_331( ax2, node[1].body->posr.R, axis2 );
    }
    else
    {
        ax2[0] = axis2[0];
        ax2[1] = axis2[1];
        ax2[2] = axis2[2];
    }
    dCalcVectorCross3( b, ax1, ax2 );
    dReal k = info->fps * info->erp;
    info->c[3] = k * dCalcVectorDot3( b, p );
    info->c[4] = k * dCalcVectorDot3( b, q );

    // if the hinge is powered, or has joint limits, add in the stuff
    limot.addLimot( this, info, 5, ax1, 1 );
}



void dJointSetHingeAnchor( dJointID j, dReal x, dReal y, dReal z )
{
    dxJointHinge* joint = ( dxJointHinge* )j;
    dUASSERT( joint, "bad joint argument" );
    checktype( joint, Hinge );
    setAnchors( joint, x, y, z, joint->anchor1, joint->anchor2 );
    joint->computeInitialRelativeRotation();
}


void dJointSetHingeAnchorDelta( dJointID j, dReal x, dReal y, dReal z, dReal dx, dReal dy, dReal dz )
{
    dxJointHinge* joint = ( dxJointHinge* )j;
    dUASSERT( joint, "bad joint argument" );
    checktype( joint, Hinge );

    if ( joint->node[0].body )
    {
        dReal q[4];
        q[0] = x - joint->node[0].body->posr.pos[0];
        q[1] = y - joint->node[0].body->posr.pos[1];
        q[2] = z - joint->node[0].body->posr.pos[2];
        q[3] = 0;
        dMultiply1_331( joint->anchor1, joint->node[0].body->posr.R, q );

        if ( joint->node[1].body )
        {
            q[0] = x - joint->node[1].body->posr.pos[0];
            q[1] = y - joint->node[1].body->posr.pos[1];
            q[2] = z - joint->node[1].body->posr.pos[2];
            q[3] = 0;
            dMultiply1_331( joint->anchor2, joint->node[1].body->posr.R, q );
        }
        else
        {
            // Move the relative displacement between the passive body and the
            //  anchor in the same direction as the passive body has just moved
            joint->anchor2[0] = x + dx;
            joint->anchor2[1] = y + dy;
            joint->anchor2[2] = z + dz;
        }
    }
    joint->anchor1[3] = 0;
    joint->anchor2[3] = 0;

    joint->computeInitialRelativeRotation();
}



void dJointSetHingeAxis( dJointID j, dReal x, dReal y, dReal z )
{
    dxJointHinge* joint = ( dxJointHinge* )j;
    dUASSERT( joint, "bad joint argument" );
    checktype( joint, Hinge );
    setAxes( joint, x, y, z, joint->axis1, joint->axis2 );
    joint->computeInitialRelativeRotation();
}


void dJointSetHingeAxisOffset( dJointID j, dReal x, dReal y, dReal z, dReal dangle )
{
    dxJointHinge* joint = ( dxJointHinge* )j;
    dUASSERT( joint, "bad joint argument" );
    checktype( joint, Hinge );
    setAxes( joint, x, y, z, joint->axis1, joint->axis2 );
    joint->computeInitialRelativeRotation();

    if ( joint->flags & dJOINT_REVERSE ) dangle = -dangle;

    dQuaternion qAngle, qOffset;
    dQFromAxisAndAngle(qAngle, x, y, z, dangle);
    dQMultiply3(qOffset, qAngle, joint->qrel);
    joint->qrel[0] = qOffset[0];
    joint->qrel[1] = qOffset[1];
    joint->qrel[2] = qOffset[2];
    joint->qrel[3] = qOffset[3];
}



void dJointGetHingeAnchor( dJointID j, dVector3 result )
{
    dxJointHinge* joint = ( dxJointHinge* )j;
    dUASSERT( joint, "bad joint argument" );
    dUASSERT( result, "bad result argument" );
    checktype( joint, Hinge );
    if ( joint->flags & dJOINT_REVERSE )
        getAnchor2( joint, result, joint->anchor2 );
    else
        getAnchor( joint, result, joint->anchor1 );
}


void dJointGetHingeAnchor2( dJointID j, dVector3 result )
{
    dxJointHinge* joint = ( dxJointHinge* )j;
    dUASSERT( joint, "bad joint argument" );
    dUASSERT( result, "bad result argument" );
    checktype( joint, Hinge );
    if ( joint->flags & dJOINT_REVERSE )
        getAnchor( joint, result, joint->anchor1 );
    else
        getAnchor2( joint, result, joint->anchor2 );
}


void dJointGetHingeAxis( dJointID j, dVector3 result )
{
    dxJointHinge* joint = ( dxJointHinge* )j;
    dUASSERT( joint, "bad joint argument" );
    dUASSERT( result, "bad result argument" );
    checktype( joint, Hinge );
    getAxis( joint, result, joint->axis1 );
}


void dJointSetHingeParam( dJointID j, int parameter, dReal value )
{
    dxJointHinge* joint = ( dxJointHinge* )j;
    dUASSERT( joint, "bad joint argument" );
    checktype( joint, Hinge );
    joint->limot.set( parameter, value );
}


dReal dJointGetHingeParam( dJointID j, int parameter )
{
    dxJointHinge* joint = ( dxJointHinge* )j;
    dUASSERT( joint, "bad joint argument" );
    checktype( joint, Hinge );
    return joint->limot.get( parameter );
}


dReal dJointGetHingeAngle( dJointID j )
{
    dxJointHinge* joint = ( dxJointHinge* )j;
    dAASSERT( joint );
    checktype( joint, Hinge );
    if ( joint->node[0].body )
    {
        dReal ang = getHingeAngle( joint->node[0].body,
                                   joint->node[1].body,
                                   joint->axis1,
                                   joint->qrel );
        if ( joint->flags & dJOINT_REVERSE )
            return -ang;
        else
            return ang;
    }
    else return 0;
}


dReal dJointGetHingeAngleRate( dJointID j )
{
    dxJointHinge* joint = ( dxJointHinge* )j;
    dAASSERT( joint );
    checktype( joint, Hinge );
    if ( joint->node[0].body )
    {
        dVector3 axis;
        dMultiply0_331( axis, joint->node[0].body->posr.R, joint->axis1 );
        dReal rate = dCalcVectorDot3( axis, joint->node[0].body->avel );
        if ( joint->node[1].body ) rate -= dCalcVectorDot3( axis, joint->node[1].body->avel );
        if ( joint->flags & dJOINT_REVERSE ) rate = - rate;
        return rate;
    }
    else return 0;
}


void dJointAddHingeTorque( dJointID j, dReal torque )
{
    dxJointHinge* joint = ( dxJointHinge* )j;
    dVector3 axis;
    dAASSERT( joint );
    checktype( joint, Hinge );

    if ( joint->flags & dJOINT_REVERSE )
        torque = -torque;

    getAxis( joint, axis, joint->axis1 );
    axis[0] *= torque;
    axis[1] *= torque;
    axis[2] *= torque;

    if ( joint->node[0].body != 0 )
        dBodyAddTorque( joint->node[0].body, axis[0], axis[1], axis[2] );
    if ( joint->node[1].body != 0 )
        dBodyAddTorque( joint->node[1].body, -axis[0], -axis[1], -axis[2] );
}


dJointType
dxJointHinge::type() const
{
    return dJointTypeHinge;
}



size_t
dxJointHinge::size() const
{
    return sizeof( *this );
}


void
dxJointHinge::setRelativeValues()
{
    dVector3 vec;
    dJointGetHingeAnchor(this, vec);
    setAnchors( this, vec[0], vec[1], vec[2], anchor1, anchor2 );

    dJointGetHingeAxis(this, vec);
    setAxes( this,  vec[0], vec[1], vec[2], axis1, axis2 );
    computeInitialRelativeRotation();
}


/// Compute initial relative rotation body1 -> body2, or env -> body1
void
dxJointHinge::computeInitialRelativeRotation()
{
    if ( node[0].body )
    {
        if ( node[1].body )
        {
            dQMultiply1( qrel, node[0].body->q, node[1].body->q );
        }
        else
        {
            // set qrel to the transpose of the first body q
            qrel[0] =  node[0].body->q[0];
            qrel[1] = -node[0].body->q[1];
            qrel[2] = -node[0].body->q[2];
            qrel[3] = -node[0].body->q[3];
        }
    }
}

