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
#include "hinge2.h"
#include "joint_internal.h"




//****************************************************************************
// hinge 2. note that this joint must be attached to two bodies for it to work

dReal
dxJointHinge2::measureAngle() const
{
    dVector3 a1, a2;
    dMultiply0_331( a1, node[1].body->posr.R, axis2 );
    dMultiply1_331( a2, node[0].body->posr.R, a1 );
    dReal x = dCalcVectorDot3( v1, a2 );
    dReal y = dCalcVectorDot3( v2, a2 );
    return -dAtan2( y, x );
}


dxJointHinge2::dxJointHinge2( dxWorld *w ) :
        dxJoint( w )
{
    dSetZero( anchor1, 4 );
    dSetZero( anchor2, 4 );
    dSetZero( axis1, 4 );
    axis1[0] = 1;
    dSetZero( axis2, 4 );
    axis2[1] = 1;
    c0 = 0;
    s0 = 0;

    dSetZero( v1, 4 );
    v1[0] = 1;
    dSetZero( v2, 4 );
    v2[1] = 1;

    limot1.init( world );
    limot2.init( world );

    susp_erp = world->global_erp;
    susp_cfm = world->global_cfm;

    flags |= dJOINT_TWOBODIES;
}


void 
dxJointHinge2::getSureMaxInfo( SureMaxInfo* info )
{
    info->max_m = 6;
}


void
dxJointHinge2::getInfo1( dxJoint::Info1 *info )
{
    info->m = 4;
    info->nub = 4;

    // see if we're powered or at a joint limit for axis 1
    limot1.limit = 0;
    if (( limot1.lostop >= -M_PI || limot1.histop <= M_PI ) &&
            limot1.lostop <= limot1.histop )
    {
        dReal angle = measureAngle();
        limot1.testRotationalLimit( angle );
    }
    if ( limot1.limit || limot1.fmax > 0 ) info->m++;

    // see if we're powering axis 2 (we currently never limit this axis)
    limot2.limit = 0;
    if ( limot2.fmax > 0 ) info->m++;
}


////////////////////////////////////////////////////////////////////////////////
/// Function that computes ax1,ax2 = axis 1 and 2 in global coordinates (they are
/// relative to body 1 and 2 initially) and then computes the constrained
/// rotational axis as the cross product of ax1 and ax2.
/// the sin and cos of the angle between axis 1 and 2 is computed, this comes
/// from dot and cross product rules.
///
/// @param ax1 Will contain the joint axis1 in world frame
/// @param ax2 Will contain the joint axis2 in world frame
/// @param axis Will contain the cross product of ax1 x ax2
/// @param sin_angle
/// @param cos_angle
////////////////////////////////////////////////////////////////////////////////
void
dxJointHinge2::getAxisInfo(dVector3 ax1, dVector3 ax2, dVector3 axCross,
                           dReal &sin_angle, dReal &cos_angle) const
{
    dMultiply0_331 (ax1, node[0].body->posr.R, axis1);
    dMultiply0_331 (ax2, node[1].body->posr.R, axis2);
    dCalcVectorCross3(axCross,ax1,ax2);
    sin_angle = dSqrt (axCross[0]*axCross[0] + axCross[1]*axCross[1] + axCross[2]*axCross[2]);
    cos_angle = dCalcVectorDot3 (ax1,ax2);
}


void
dxJointHinge2::getInfo2( dxJoint::Info2 *info )
{
    // get information we need to set the hinge row
    dReal s, c;
    dVector3 q;
    const dxJointHinge2 *joint = this;

    dVector3 ax1, ax2;
    joint->getAxisInfo( ax1, ax2, q, s, c );
    dNormalize3( q );   // @@@ quicker: divide q by s ?

    // set the three ball-and-socket rows (aligned to the suspension axis ax1)
    setBall2( this, info, anchor1, anchor2, ax1, susp_erp );

    // set the hinge row
    int s3 = 3 * info->rowskip;
    info->J1a[s3+0] = q[0];
    info->J1a[s3+1] = q[1];
    info->J1a[s3+2] = q[2];
    if ( joint->node[1].body )
    {
        info->J2a[s3+0] = -q[0];
        info->J2a[s3+1] = -q[1];
        info->J2a[s3+2] = -q[2];
    }

    // compute the right hand side for the constrained rotational DOF.
    // axis 1 and axis 2 are separated by an angle `theta'. the desired
    // separation angle is theta0. sin(theta0) and cos(theta0) are recorded
    // in the joint structure. the correcting angular velocity is:
    //   |angular_velocity| = angle/time = erp*(theta0-theta) / stepsize
    //                      = (erp*fps) * (theta0-theta)
    // (theta0-theta) can be computed using the following small-angle-difference
    // approximation:
    //   theta0-theta ~= tan(theta0-theta)
    //                 = sin(theta0-theta)/cos(theta0-theta)
    //                 = (c*s0 - s*c0) / (c*c0 + s*s0)
    //                 = c*s0 - s*c0         assuming c*c0 + s*s0 ~= 1
    // where c = cos(theta), s = sin(theta)
    //       c0 = cos(theta0), s0 = sin(theta0)

    dReal k = info->fps * info->erp;
    info->c[3] = k * ( c0 * s - joint->s0 * c );

    // if the axis1 hinge is powered, or has joint limits, add in more stuff
    int row = 4 + limot1.addLimot( this, info, 4, ax1, 1 );

    // if the axis2 hinge is powered, add in more stuff
    limot2.addLimot( this, info, row, ax2, 1 );

    // set parameter for the suspension
    info->cfm[0] = susp_cfm;
}


// compute vectors v1 and v2 (embedded in body1), used to measure angle
// between body 1 and body 2

void
dxJointHinge2::makeV1andV2()
{
    if ( node[0].body )
    {
        // get axis 1 and 2 in global coords
        dVector3 ax1, ax2, v;
        dMultiply0_331( ax1, node[0].body->posr.R, axis1 );
        dMultiply0_331( ax2, node[1].body->posr.R, axis2 );

        // don't do anything if the axis1 or axis2 vectors are zero or the same
        if (( ax1[0] == 0 && ax1[1] == 0 && ax1[2] == 0 ) ||
                ( ax2[0] == 0 && ax2[1] == 0 && ax2[2] == 0 ) ||
                ( ax1[0] == ax2[0] && ax1[1] == ax2[1] && ax1[2] == ax2[2] ) ) return;

        // modify axis 2 so it's perpendicular to axis 1
        dReal k = dCalcVectorDot3( ax1, ax2 );
        for ( int i = 0; i < 3; i++ ) ax2[i] -= k * ax1[i];
        dNormalize3( ax2 );

        // make v1 = modified axis2, v2 = axis1 x (modified axis2)
        dCalcVectorCross3( v, ax1, ax2 );
        dMultiply1_331( v1, node[0].body->posr.R, ax2 );
        dMultiply1_331( v2, node[0].body->posr.R, v );
    }
}


void dJointSetHinge2Anchor( dJointID j, dReal x, dReal y, dReal z )
{
    dxJointHinge2* joint = ( dxJointHinge2* )j;
    dUASSERT( joint, "bad joint argument" );
    checktype( joint, Hinge2 );
    setAnchors( joint, x, y, z, joint->anchor1, joint->anchor2 );
    joint->makeV1andV2();
}


void dJointSetHinge2Axis1( dJointID j, dReal x, dReal y, dReal z )
{
    dxJointHinge2* joint = ( dxJointHinge2* )j;
    dUASSERT( joint, "bad joint argument" );
    checktype( joint, Hinge2 );
    if ( joint->node[0].body )
    {
        setAxes(joint, x, y, z, joint->axis1, NULL);

        // compute the sin and cos of the angle between axis 1 and axis 2
        dVector3 ax1, ax2, ax;
        joint->getAxisInfo( ax1, ax2, ax, joint->s0, joint->c0 );
    }
    joint->makeV1andV2();
}


void dJointSetHinge2Axis2( dJointID j, dReal x, dReal y, dReal z )
{
    dxJointHinge2* joint = ( dxJointHinge2* )j;
    dUASSERT( joint, "bad joint argument" );
    checktype( joint, Hinge2 );
    if ( joint->node[1].body )
    {
        setAxes(joint, x, y, z, NULL, joint->axis2);


        // compute the sin and cos of the angle between axis 1 and axis 2
        dVector3 ax1, ax2, ax;;
        joint->getAxisInfo( ax1, ax2, ax, joint->s0, joint->c0 );
    }
    joint->makeV1andV2();
}


void dJointSetHinge2Param( dJointID j, int parameter, dReal value )
{
    dxJointHinge2* joint = ( dxJointHinge2* )j;
    dUASSERT( joint, "bad joint argument" );
    checktype( joint, Hinge2 );
    if (( parameter & 0xff00 ) == 0x100 )
    {
        joint->limot2.set( parameter & 0xff, value );
    }
    else
    {
        if ( parameter == dParamSuspensionERP ) joint->susp_erp = value;
        else if ( parameter == dParamSuspensionCFM ) joint->susp_cfm = value;
        else joint->limot1.set( parameter, value );
    }
}


void dJointGetHinge2Anchor( dJointID j, dVector3 result )
{
    dxJointHinge2* joint = ( dxJointHinge2* )j;
    dUASSERT( joint, "bad joint argument" );
    dUASSERT( result, "bad result argument" );
    checktype( joint, Hinge2 );
    if ( joint->flags & dJOINT_REVERSE )
        getAnchor2( joint, result, joint->anchor2 );
    else
        getAnchor( joint, result, joint->anchor1 );
}


void dJointGetHinge2Anchor2( dJointID j, dVector3 result )
{
    dxJointHinge2* joint = ( dxJointHinge2* )j;
    dUASSERT( joint, "bad joint argument" );
    dUASSERT( result, "bad result argument" );
    checktype( joint, Hinge2 );
    if ( joint->flags & dJOINT_REVERSE )
        getAnchor( joint, result, joint->anchor1 );
    else
        getAnchor2( joint, result, joint->anchor2 );
}


void dJointGetHinge2Axis1( dJointID j, dVector3 result )
{
    dxJointHinge2* joint = ( dxJointHinge2* )j;
    dUASSERT( joint, "bad joint argument" );
    dUASSERT( result, "bad result argument" );
    checktype( joint, Hinge2 );
    if ( joint->node[0].body )
    {
        dMultiply0_331( result, joint->node[0].body->posr.R, joint->axis1 );
    }
}


void dJointGetHinge2Axis2( dJointID j, dVector3 result )
{
    dxJointHinge2* joint = ( dxJointHinge2* )j;
    dUASSERT( joint, "bad joint argument" );
    dUASSERT( result, "bad result argument" );
    checktype( joint, Hinge2 );
    if ( joint->node[1].body )
    {
        dMultiply0_331( result, joint->node[1].body->posr.R, joint->axis2 );
    }
}


dReal dJointGetHinge2Param( dJointID j, int parameter )
{
    dxJointHinge2* joint = ( dxJointHinge2* )j;
    dUASSERT( joint, "bad joint argument" );
    checktype( joint, Hinge2 );
    if (( parameter & 0xff00 ) == 0x100 )
    {
        return joint->limot2.get( parameter & 0xff );
    }
    else
    {
        if ( parameter == dParamSuspensionERP ) return joint->susp_erp;
        else if ( parameter == dParamSuspensionCFM ) return joint->susp_cfm;
        else return joint->limot1.get( parameter );
    }
}


dReal dJointGetHinge2Angle1( dJointID j )
{
    dxJointHinge2* joint = ( dxJointHinge2* )j;
    dUASSERT( joint, "bad joint argument" );
    checktype( joint, Hinge2 );
    if ( joint->node[0].body ) return joint->measureAngle();
    else return 0;
}


dReal dJointGetHinge2Angle1Rate( dJointID j )
{
    dxJointHinge2* joint = ( dxJointHinge2* )j;
    dUASSERT( joint, "bad joint argument" );
    checktype( joint, Hinge2 );
    if ( joint->node[0].body )
    {
        dVector3 axis;
        dMultiply0_331( axis, joint->node[0].body->posr.R, joint->axis1 );
        dReal rate = dCalcVectorDot3( axis, joint->node[0].body->avel );
        if ( joint->node[1].body )
            rate -= dCalcVectorDot3( axis, joint->node[1].body->avel );
        return rate;
    }
    else return 0;
}


dReal dJointGetHinge2Angle2Rate( dJointID j )
{
    dxJointHinge2* joint = ( dxJointHinge2* )j;
    dUASSERT( joint, "bad joint argument" );
    checktype( joint, Hinge2 );
    if ( joint->node[0].body && joint->node[1].body )
    {
        dVector3 axis;
        dMultiply0_331( axis, joint->node[1].body->posr.R, joint->axis2 );
        dReal rate = dCalcVectorDot3( axis, joint->node[0].body->avel );
        if ( joint->node[1].body )
            rate -= dCalcVectorDot3( axis, joint->node[1].body->avel );
        return rate;
    }
    else return 0;
}


void dJointAddHinge2Torques( dJointID j, dReal torque1, dReal torque2 )
{
    dxJointHinge2* joint = ( dxJointHinge2* )j;
    dVector3 axis1, axis2;
    dUASSERT( joint, "bad joint argument" );
    checktype( joint, Hinge2 );

    if ( joint->node[0].body && joint->node[1].body )
    {
        dMultiply0_331( axis1, joint->node[0].body->posr.R, joint->axis1 );
        dMultiply0_331( axis2, joint->node[1].body->posr.R, joint->axis2 );
        axis1[0] = axis1[0] * torque1 + axis2[0] * torque2;
        axis1[1] = axis1[1] * torque1 + axis2[1] * torque2;
        axis1[2] = axis1[2] * torque1 + axis2[2] * torque2;
        dBodyAddTorque( joint->node[0].body, axis1[0], axis1[1], axis1[2] );
        dBodyAddTorque( joint->node[1].body, -axis1[0], -axis1[1], -axis1[2] );
    }
}


dJointType
dxJointHinge2::type() const
{
    return dJointTypeHinge2;
}


size_t
dxJointHinge2::size() const
{
    return sizeof( *this );
}


void
dxJointHinge2::setRelativeValues()
{
    dVector3 anchor;
    dJointGetHinge2Anchor(this, anchor);
    setAnchors( this, anchor[0], anchor[1], anchor[2], anchor1, anchor2 );

    dVector3 axis;

    if ( node[0].body )
    {
        dJointGetHinge2Axis1(this, axis);
        setAxes( this, axis[0],axis[1],axis[2], axis1, NULL );
    }

    if ( node[0].body )
    {
        dJointGetHinge2Axis2(this, axis);
        setAxes( this, axis[0],axis[1],axis[2], NULL, axis2 );
    }

    dVector3 ax1, ax2;
    getAxisInfo( ax1, ax2, axis, s0, c0 );

    makeV1andV2();
}
