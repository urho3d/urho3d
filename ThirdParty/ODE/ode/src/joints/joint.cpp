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

/*

design note: the general principle for giving a joint the option of connecting
to the static environment (i.e. the absolute frame) is to check the second
body (joint->node[1].body), and if it is zero then behave as if its body
transform is the identity.

*/

#include <ode/ode.h>
#include <ode/odemath.h>
#include <ode/rotation.h>
#include <ode/matrix.h>
#include "config.h"
#include "joint.h"
#include "joint_internal.h"

extern void addObjectToList( dObject *obj, dObject **first );

dxJoint::dxJoint( dxWorld *w ) :
        dObject( w )
{
    //printf("constructing %p\n", this);
    dIASSERT( w );
    flags = 0;
    node[0].joint = this;
    node[0].body = 0;
    node[0].next = 0;
    node[1].joint = this;
    node[1].body = 0;
    node[1].next = 0;
    dSetZero( lambda, 6 );

    addObjectToList( this, ( dObject ** ) &w->firstjoint );

    w->nj++;
    feedback = 0;
}

dxJoint::~dxJoint()
{ }


bool dxJoint::isEnabled() const
{
    return ( (flags & dJOINT_DISABLED) == 0 &&
             (node[0].body->invMass > 0 ||
             (node[1].body && node[1].body->invMass > 0)) );
}

//****************************************************************************
// externs

// extern "C" void dBodyAddTorque (dBodyID, dReal fx, dReal fy, dReal fz);
// extern "C" void dBodyAddForce (dBodyID, dReal fx, dReal fy, dReal fz);

//****************************************************************************
// utility

// set three "ball-and-socket" rows in the constraint equation, and the
// corresponding right hand side.

void setBall( dxJoint *joint, dxJoint::Info2 *info,
              dVector3 anchor1, dVector3 anchor2 )
{
    // anchor points in global coordinates with respect to body PORs.
    dVector3 a1, a2;

    int s = info->rowskip;

    // set jacobian
    info->J1l[0] = 1;
    info->J1l[s+1] = 1;
    info->J1l[2*s+2] = 1;
    dMultiply0_331( a1, joint->node[0].body->posr.R, anchor1 );
    dSetCrossMatrixMinus( info->J1a, a1, s );
    if ( joint->node[1].body )
    {
        info->J2l[0] = -1;
        info->J2l[s+1] = -1;
        info->J2l[2*s+2] = -1;
        dMultiply0_331( a2, joint->node[1].body->posr.R, anchor2 );
        dSetCrossMatrixPlus( info->J2a, a2, s );
    }

    // set right hand side
    dReal k = info->fps * info->erp;
    if ( joint->node[1].body )
    {
        for ( int j = 0; j < 3; j++ )
        {
            info->c[j] = k * ( a2[j] + joint->node[1].body->posr.pos[j] -
                               a1[j] - joint->node[0].body->posr.pos[j] );
        }
    }
    else
    {
        for ( int j = 0; j < 3; j++ )
        {
            info->c[j] = k * ( anchor2[j] - a1[j] -
                               joint->node[0].body->posr.pos[j] );
        }
    }
}


// this is like setBall(), except that `axis' is a unit length vector
// (in global coordinates) that should be used for the first jacobian
// position row (the other two row vectors will be derived from this).
// `erp1' is the erp value to use along the axis.

void setBall2( dxJoint *joint, dxJoint::Info2 *info,
               dVector3 anchor1, dVector3 anchor2,
               dVector3 axis, dReal erp1 )
{
    // anchor points in global coordinates with respect to body PORs.
    dVector3 a1, a2;

    int i, s = info->rowskip;

    // get vectors normal to the axis. in setBall() axis,q1,q2 is [1 0 0],
    // [0 1 0] and [0 0 1], which makes everything much easier.
    dVector3 q1, q2;
    dPlaneSpace( axis, q1, q2 );

    // set jacobian
    for ( i = 0; i < 3; i++ ) info->J1l[i] = axis[i];
    for ( i = 0; i < 3; i++ ) info->J1l[s+i] = q1[i];
    for ( i = 0; i < 3; i++ ) info->J1l[2*s+i] = q2[i];
    dMultiply0_331( a1, joint->node[0].body->posr.R, anchor1 );
    dCalcVectorCross3( info->J1a, a1, axis );
    dCalcVectorCross3( info->J1a + s, a1, q1 );
    dCalcVectorCross3( info->J1a + 2*s, a1, q2 );
    if ( joint->node[1].body )
    {
        for ( i = 0; i < 3; i++ ) info->J2l[i] = -axis[i];
        for ( i = 0; i < 3; i++ ) info->J2l[s+i] = -q1[i];
        for ( i = 0; i < 3; i++ ) info->J2l[2*s+i] = -q2[i];
        dMultiply0_331( a2, joint->node[1].body->posr.R, anchor2 );
        dReal *J2a = info->J2a;
        dCalcVectorCross3( J2a, a2, axis );
        dNegateVector3( J2a );
        dReal *J2a_plus_s = J2a + s;
        dCalcVectorCross3( J2a_plus_s, a2, q1 );
        dNegateVector3( J2a_plus_s );
        dReal *J2a_plus_2s = J2a_plus_s + s;
        dCalcVectorCross3( J2a_plus_2s, a2, q2 );
        dNegateVector3( J2a_plus_2s );
    }

    // set right hand side - measure error along (axis,q1,q2)
    dReal k1 = info->fps * erp1;
    dReal k = info->fps * info->erp;

    for ( i = 0; i < 3; i++ ) a1[i] += joint->node[0].body->posr.pos[i];
    if ( joint->node[1].body )
    {
        for ( i = 0; i < 3; i++ ) a2[i] += joint->node[1].body->posr.pos[i];
        
        dVector3 a2_minus_a1;
        dSubtractVectors3(a2_minus_a1, a2, a1);
        info->c[0] = k1 * dCalcVectorDot3( axis, a2_minus_a1 );
        info->c[1] = k * dCalcVectorDot3( q1, a2_minus_a1 );
        info->c[2] = k * dCalcVectorDot3( q2, a2_minus_a1 );
    }
    else
    {
        dVector3 anchor2_minus_a1;
        dSubtractVectors3(anchor2_minus_a1, anchor2, a1);
        info->c[0] = k1 * dCalcVectorDot3( axis, anchor2_minus_a1 );
        info->c[1] = k * dCalcVectorDot3( q1, anchor2_minus_a1 );
        info->c[2] = k * dCalcVectorDot3( q2, anchor2_minus_a1 );
    }
}


// set three orientation rows in the constraint equation, and the
// corresponding right hand side.

void setFixedOrientation( dxJoint *joint, dxJoint::Info2 *info, dQuaternion qrel, int start_row )
{
    int s = info->rowskip;
    int start_index = start_row * s;

    // 3 rows to make body rotations equal
    info->J1a[start_index] = 1;
    info->J1a[start_index + s + 1] = 1;
    info->J1a[start_index + s*2+2] = 1;
    if ( joint->node[1].body )
    {
        info->J2a[start_index] = -1;
        info->J2a[start_index + s+1] = -1;
        info->J2a[start_index + s*2+2] = -1;
    }

    // compute the right hand side. the first three elements will result in
    // relative angular velocity of the two bodies - this is set to bring them
    // back into alignment. the correcting angular velocity is
    //   |angular_velocity| = angle/time = erp*theta / stepsize
    //                      = (erp*fps) * theta
    //    angular_velocity  = |angular_velocity| * u
    //                      = (erp*fps) * theta * u
    // where rotation along unit length axis u by theta brings body 2's frame
    // to qrel with respect to body 1's frame. using a small angle approximation
    // for sin(), this gives
    //    angular_velocity  = (erp*fps) * 2 * v
    // where the quaternion of the relative rotation between the two bodies is
    //    q = [cos(theta/2) sin(theta/2)*u] = [s v]

    // get qerr = relative rotation (rotation error) between two bodies
    dQuaternion qerr, e;
    if ( joint->node[1].body )
    {
        dQuaternion qq;
        dQMultiply1( qq, joint->node[0].body->q, joint->node[1].body->q );
        dQMultiply2( qerr, qq, qrel );
    }
    else
    {
        dQMultiply3( qerr, joint->node[0].body->q, qrel );
    }
    if ( qerr[0] < 0 )
    {
        qerr[1] = -qerr[1];  // adjust sign of qerr to make theta small
        qerr[2] = -qerr[2];
        qerr[3] = -qerr[3];
    }
    dMultiply0_331( e, joint->node[0].body->posr.R, qerr + 1 );  // @@@ bad SIMD padding!
    dReal k = info->fps * info->erp;
    info->c[start_row] = 2 * k * e[0];
    info->c[start_row+1] = 2 * k * e[1];
    info->c[start_row+2] = 2 * k * e[2];
}


// compute anchor points relative to bodies

void setAnchors( dxJoint *j, dReal x, dReal y, dReal z,
                 dVector3 anchor1, dVector3 anchor2 )
{
    if ( j->node[0].body )
    {
        dReal q[4];
        q[0] = x - j->node[0].body->posr.pos[0];
        q[1] = y - j->node[0].body->posr.pos[1];
        q[2] = z - j->node[0].body->posr.pos[2];
        q[3] = 0;
        dMultiply1_331( anchor1, j->node[0].body->posr.R, q );
        if ( j->node[1].body )
        {
            q[0] = x - j->node[1].body->posr.pos[0];
            q[1] = y - j->node[1].body->posr.pos[1];
            q[2] = z - j->node[1].body->posr.pos[2];
            q[3] = 0;
            dMultiply1_331( anchor2, j->node[1].body->posr.R, q );
        }
        else
        {
            anchor2[0] = x;
            anchor2[1] = y;
            anchor2[2] = z;
        }
    }
    anchor1[3] = 0;
    anchor2[3] = 0;
}


// compute axes relative to bodies. either axis1 or axis2 can be 0.

void setAxes( dxJoint *j, dReal x, dReal y, dReal z,
              dVector3 axis1, dVector3 axis2 )
{
    if ( j->node[0].body )
    {
        dReal q[4];
        q[0] = x;
        q[1] = y;
        q[2] = z;
        q[3] = 0;
        dNormalize3( q );
        if ( axis1 )
        {
            dMultiply1_331( axis1, j->node[0].body->posr.R, q );
            axis1[3] = 0;
        }
        if ( axis2 )
        {
            if ( j->node[1].body )
            {
                dMultiply1_331( axis2, j->node[1].body->posr.R, q );
            }
            else
            {
                axis2[0] = x;
                axis2[1] = y;
                axis2[2] = z;
            }
            axis2[3] = 0;
        }
    }
}


void getAnchor( dxJoint *j, dVector3 result, dVector3 anchor1 )
{
    if ( j->node[0].body )
    {
        dMultiply0_331( result, j->node[0].body->posr.R, anchor1 );
        result[0] += j->node[0].body->posr.pos[0];
        result[1] += j->node[0].body->posr.pos[1];
        result[2] += j->node[0].body->posr.pos[2];
    }
}


void getAnchor2( dxJoint *j, dVector3 result, dVector3 anchor2 )
{
    if ( j->node[1].body )
    {
        dMultiply0_331( result, j->node[1].body->posr.R, anchor2 );
        result[0] += j->node[1].body->posr.pos[0];
        result[1] += j->node[1].body->posr.pos[1];
        result[2] += j->node[1].body->posr.pos[2];
    }
    else
    {
        result[0] = anchor2[0];
        result[1] = anchor2[1];
        result[2] = anchor2[2];
    }
}


void getAxis( dxJoint *j, dVector3 result, dVector3 axis1 )
{
    if ( j->node[0].body )
    {
        dMultiply0_331( result, j->node[0].body->posr.R, axis1 );
    }
}


void getAxis2( dxJoint *j, dVector3 result, dVector3 axis2 )
{
    if ( j->node[1].body )
    {
        dMultiply0_331( result, j->node[1].body->posr.R, axis2 );
    }
    else
    {
        result[0] = axis2[0];
        result[1] = axis2[1];
        result[2] = axis2[2];
    }
}


dReal getHingeAngleFromRelativeQuat( dQuaternion qrel, dVector3 axis )
{
    // the angle between the two bodies is extracted from the quaternion that
    // represents the relative rotation between them. recall that a quaternion
    // q is:
    //    [s,v] = [ cos(theta/2) , sin(theta/2) * u ]
    // where s is a scalar and v is a 3-vector. u is a unit length axis and
    // theta is a rotation along that axis. we can get theta/2 by:
    //    theta/2 = atan2 ( sin(theta/2) , cos(theta/2) )
    // but we can't get sin(theta/2) directly, only its absolute value, i.e.:
    //    |v| = |sin(theta/2)| * |u|
    //        = |sin(theta/2)|
    // using this value will have a strange effect. recall that there are two
    // quaternion representations of a given rotation, q and -q. typically as
    // a body rotates along the axis it will go through a complete cycle using
    // one representation and then the next cycle will use the other
    // representation. this corresponds to u pointing in the direction of the
    // hinge axis and then in the opposite direction. the result is that theta
    // will appear to go "backwards" every other cycle. here is a fix: if u
    // points "away" from the direction of the hinge (motor) axis (i.e. more
    // than 90 degrees) then use -q instead of q. this represents the same
    // rotation, but results in the cos(theta/2) value being sign inverted.

    // extract the angle from the quaternion. cost2 = cos(theta/2),
    // sint2 = |sin(theta/2)|
    dReal cost2 = qrel[0];
    dReal sint2 = dSqrt( qrel[1] * qrel[1] + qrel[2] * qrel[2] + qrel[3] * qrel[3] );
    dReal theta = ( dCalcVectorDot3( qrel + 1, axis ) >= 0 ) ? // @@@ padding assumptions
                  ( 2 * dAtan2( sint2, cost2 ) ) :  // if u points in direction of axis
                  ( 2 * dAtan2( sint2, -cost2 ) );  // if u points in opposite direction

    // the angle we get will be between 0..2*pi, but we want to return angles
    // between -pi..pi
    if ( theta > M_PI ) theta -= ( dReal )( 2 * M_PI );

    // the angle we've just extracted has the wrong sign
    theta = -theta;

    return theta;
}


// given two bodies (body1,body2), the hinge axis that they are connected by
// w.r.t. body1 (axis), and the initial relative orientation between them
// (q_initial), return the relative rotation angle. the initial relative
// orientation corresponds to an angle of zero. if body2 is 0 then measure the
// angle between body1 and the static frame.
//
// this will not return the correct angle if the bodies rotate along any axis
// other than the given hinge axis.

dReal getHingeAngle( dxBody *body1, dxBody *body2, dVector3 axis,
                     dQuaternion q_initial )
{
    // get qrel = relative rotation between the two bodies
    dQuaternion qrel;
    if ( body2 )
    {
        dQuaternion qq;
        dQMultiply1( qq, body1->q, body2->q );
        dQMultiply2( qrel, qq, q_initial );
    }
    else
    {
        // pretend body2->q is the identity
        dQMultiply3( qrel, body1->q, q_initial );
    }

    return getHingeAngleFromRelativeQuat( qrel, axis );
}

//****************************************************************************
// dxJointLimitMotor

void dxJointLimitMotor::init( dxWorld *world )
{
    vel = 0;
    fmax = 0;
    lostop = -dInfinity;
    histop = dInfinity;
    fudge_factor = 1;
    normal_cfm = world->global_cfm;
    stop_erp = world->global_erp;
    stop_cfm = world->global_cfm;
    bounce = 0;
    limit = 0;
    limit_err = 0;
}


void dxJointLimitMotor::set( int num, dReal value )
{
    switch ( num )
    {
    case dParamLoStop:
        lostop = value;
        break;
    case dParamHiStop:
        histop = value;
        break;
    case dParamVel:
        vel = value;
        break;
    case dParamFMax:
        if ( value >= 0 ) fmax = value;
        break;
    case dParamFudgeFactor:
        if ( value >= 0 && value <= 1 ) fudge_factor = value;
        break;
    case dParamBounce:
        bounce = value;
        break;
    case dParamCFM:
        normal_cfm = value;
        break;
    case dParamStopERP:
        stop_erp = value;
        break;
    case dParamStopCFM:
        stop_cfm = value;
        break;
    }
}


dReal dxJointLimitMotor::get( int num )
{
    switch ( num )
    {
    case dParamLoStop:
        return lostop;
    case dParamHiStop:
        return histop;
    case dParamVel:
        return vel;
    case dParamFMax:
        return fmax;
    case dParamFudgeFactor:
        return fudge_factor;
    case dParamBounce:
        return bounce;
    case dParamCFM:
        return normal_cfm;
    case dParamStopERP:
        return stop_erp;
    case dParamStopCFM:
        return stop_cfm;
    default:
        return 0;
    }
}


int dxJointLimitMotor::testRotationalLimit( dReal angle )
{
    if ( angle <= lostop )
    {
        limit = 1;
        limit_err = angle - lostop;
        return 1;
    }
    else if ( angle >= histop )
    {
        limit = 2;
        limit_err = angle - histop;
        return 1;
    }
    else
    {
        limit = 0;
        return 0;
    }
}


int dxJointLimitMotor::addLimot( dxJoint *joint,
                                 dxJoint::Info2 *info, int row,
                                 const dVector3 ax1, int rotational )
{
    int srow = row * info->rowskip;

    // if the joint is powered, or has joint limits, add in the extra row
    int powered = fmax > 0;
    if ( powered || limit )
    {
        dReal *J1 = rotational ? info->J1a : info->J1l;
        dReal *J2 = rotational ? info->J2a : info->J2l;

        J1[srow+0] = ax1[0];
        J1[srow+1] = ax1[1];
        J1[srow+2] = ax1[2];
        if ( joint->node[1].body )
        {
            J2[srow+0] = -ax1[0];
            J2[srow+1] = -ax1[1];
            J2[srow+2] = -ax1[2];
        }

        // linear limot torque decoupling step:
        //
        // if this is a linear limot (e.g. from a slider), we have to be careful
        // that the linear constraint forces (+/- ax1) applied to the two bodies
        // do not create a torque couple. in other words, the points that the
        // constraint force is applied at must lie along the same ax1 axis.
        // a torque couple will result in powered or limited slider-jointed free
        // bodies from gaining angular momentum.
        // the solution used here is to apply the constraint forces at the point
        // halfway between the body centers. there is no penalty (other than an
        // extra tiny bit of computation) in doing this adjustment. note that we
        // only need to do this if the constraint connects two bodies.

        dVector3 ltd = {0,0,0}; // Linear Torque Decoupling vector (a torque)
        if ( !rotational && joint->node[1].body )
        {
            dVector3 c;
            c[0] = REAL( 0.5 ) * ( joint->node[1].body->posr.pos[0] - joint->node[0].body->posr.pos[0] );
            c[1] = REAL( 0.5 ) * ( joint->node[1].body->posr.pos[1] - joint->node[0].body->posr.pos[1] );
            c[2] = REAL( 0.5 ) * ( joint->node[1].body->posr.pos[2] - joint->node[0].body->posr.pos[2] );
            dCalcVectorCross3( ltd, c, ax1 );
            info->J1a[srow+0] = ltd[0];
            info->J1a[srow+1] = ltd[1];
            info->J1a[srow+2] = ltd[2];
            info->J2a[srow+0] = ltd[0];
            info->J2a[srow+1] = ltd[1];
            info->J2a[srow+2] = ltd[2];
        }

        // if we're limited low and high simultaneously, the joint motor is
        // ineffective
        if ( limit && ( lostop == histop ) ) powered = 0;

        if ( powered )
        {
            info->cfm[row] = normal_cfm;
            if ( ! limit )
            {
                info->c[row] = vel;
                info->lo[row] = -fmax;
                info->hi[row] = fmax;
            }
            else
            {
                // the joint is at a limit, AND is being powered. if the joint is
                // being powered into the limit then we apply the maximum motor force
                // in that direction, because the motor is working against the
                // immovable limit. if the joint is being powered away from the limit
                // then we have problems because actually we need *two* lcp
                // constraints to handle this case. so we fake it and apply some
                // fraction of the maximum force. the fraction to use can be set as
                // a fudge factor.

                dReal fm = fmax;
                if (( vel > 0 ) || ( vel == 0 && limit == 2 ) ) fm = -fm;

                // if we're powering away from the limit, apply the fudge factor
                if (( limit == 1 && vel > 0 ) || ( limit == 2 && vel < 0 ) ) fm *= fudge_factor;

                if ( rotational )
                {
                    dBodyAddTorque( joint->node[0].body, -fm*ax1[0], -fm*ax1[1],
                                    -fm*ax1[2] );
                    if ( joint->node[1].body )
                        dBodyAddTorque( joint->node[1].body, fm*ax1[0], fm*ax1[1], fm*ax1[2] );
                }
                else
                {
                    dBodyAddForce( joint->node[0].body, -fm*ax1[0], -fm*ax1[1], -fm*ax1[2] );
                    if ( joint->node[1].body )
                    {
                        dBodyAddForce( joint->node[1].body, fm*ax1[0], fm*ax1[1], fm*ax1[2] );

                        // linear limot torque decoupling step: refer to above discussion
                        dBodyAddTorque( joint->node[0].body, -fm*ltd[0], -fm*ltd[1],
                                        -fm*ltd[2] );
                        dBodyAddTorque( joint->node[1].body, -fm*ltd[0], -fm*ltd[1],
                                        -fm*ltd[2] );
                    }
                }
            }
        }

        if ( limit )
        {
            dReal k = info->fps * stop_erp;
            info->c[row] = -k * limit_err;
            info->cfm[row] = stop_cfm;

            if ( lostop == histop )
            {
                // limited low and high simultaneously
                info->lo[row] = -dInfinity;
                info->hi[row] = dInfinity;
            }
            else
            {
                if ( limit == 1 )
                {
                    // low limit
                    info->lo[row] = 0;
                    info->hi[row] = dInfinity;
                }
                else
                {
                    // high limit
                    info->lo[row] = -dInfinity;
                    info->hi[row] = 0;
                }

                // deal with bounce
                if ( bounce > 0 )
                {
                    // calculate joint velocity
                    dReal vel;
                    if ( rotational )
                    {
                        vel = dCalcVectorDot3( joint->node[0].body->avel, ax1 );
                        if ( joint->node[1].body )
                            vel -= dCalcVectorDot3( joint->node[1].body->avel, ax1 );
                    }
                    else
                    {
                        vel = dCalcVectorDot3( joint->node[0].body->lvel, ax1 );
                        if ( joint->node[1].body )
                            vel -= dCalcVectorDot3( joint->node[1].body->lvel, ax1 );
                    }

                    // only apply bounce if the velocity is incoming, and if the
                    // resulting c[] exceeds what we already have.
                    if ( limit == 1 )
                    {
                        // low limit
                        if ( vel < 0 )
                        {
                            dReal newc = -bounce * vel;
                            if ( newc > info->c[row] ) info->c[row] = newc;
                        }
                    }
                    else
                    {
                        // high limit - all those computations are reversed
                        if ( vel > 0 )
                        {
                            dReal newc = -bounce * vel;
                            if ( newc < info->c[row] ) info->c[row] = newc;
                        }
                    }
                }
            }
        }
        return 1;
    }
    else return 0;
}



// Local Variables:
// mode:c++
// c-basic-offset:4
// End:
