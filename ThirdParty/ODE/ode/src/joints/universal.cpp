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
#include "universal.h"
#include "joint_internal.h"



//****************************************************************************
// universal

// I just realized that the universal joint is equivalent to a hinge 2 joint with
// perfectly stiff suspension.  By comparing the hinge 2 implementation to
// the universal implementation, you may be able to improve this
// implementation (or, less likely, the hinge2 implementation).

dxJointUniversal::dxJointUniversal( dxWorld *w ) :
        dxJoint( w )
{
    dSetZero( anchor1, 4 );
    dSetZero( anchor2, 4 );
    dSetZero( axis1, 4 );
    axis1[0] = 1;
    dSetZero( axis2, 4 );
    axis2[1] = 1;
    dSetZero( qrel1, 4 );
    dSetZero( qrel2, 4 );
    limot1.init( world );
    limot2.init( world );
}


void
dxJointUniversal::getAxes( dVector3 ax1, dVector3 ax2 )
{
    // This says "ax1 = joint->node[0].body->posr.R * joint->axis1"
    dMultiply0_331( ax1, node[0].body->posr.R, axis1 );

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
}

void
dxJointUniversal::getAngles( dReal *angle1, dReal *angle2 )
{
    if ( node[0].body )
    {
        // length 1 joint axis in global coordinates, from each body
        dVector3 ax1, ax2;
        dMatrix3 R;
        dQuaternion qcross, qq, qrel;

        getAxes( ax1, ax2 );

        // It should be possible to get both angles without explicitly
        // constructing the rotation matrix of the cross.  Basically,
        // orientation of the cross about axis1 comes from body 2,
        // about axis 2 comes from body 1, and the perpendicular
        // axis can come from the two bodies somehow.  (We don't really
        // want to assume it's 90 degrees, because in general the
        // constraints won't be perfectly satisfied, or even very well
        // satisfied.)
        //
        // However, we'd need a version of getHingeAngleFromRElativeQuat()
        // that CAN handle when its relative quat is rotated along a direction
        // other than the given axis.  What I have here works,
        // although it's probably much slower than need be.

        dRFrom2Axes( R, ax1[0], ax1[1], ax1[2], ax2[0], ax2[1], ax2[2] );

        dRtoQ( R, qcross );


        // This code is essentialy the same as getHingeAngle(), see the comments
        // there for details.

        // get qrel = relative rotation between node[0] and the cross
        dQMultiply1( qq, node[0].body->q, qcross );
        dQMultiply2( qrel, qq, qrel1 );

        *angle1 = getHingeAngleFromRelativeQuat( qrel, axis1 );

        // This is equivalent to
        // dRFrom2Axes(R, ax2[0], ax2[1], ax2[2], ax1[0], ax1[1], ax1[2]);
        // You see that the R is constructed from the same 2 axis as for angle1
        // but the first and second axis are swapped.
        // So we can take the first R and rapply a rotation to it.
        // The rotation is around the axis between the 2 axes (ax1 and ax2).
        // We do a rotation of 180deg.

        dQuaternion qcross2;
        // Find the vector between ax1 and ax2 (i.e. in the middle)
        // We need to turn around this vector by 180deg

        // The 2 axes should be normalize so to find the vector between the 2.
        // Add and devide by 2 then normalize or simply normalize
        //    ax2
        //    ^
        //    |
        //    |
        ///   *------------> ax1
        //    We want the vector a 45deg
        //
        // N.B. We don't need to normalize the ax1 and ax2 since there are
        //      normalized when we set them.

        // We set the quaternion q = [cos(theta), dir*sin(theta)] = [w, x, y, Z]
        qrel[0] = 0;                // equivalent to cos(Pi/2)
        qrel[1] = ax1[0] + ax2[0];  // equivalent to x*sin(Pi/2); since sin(Pi/2) = 1
        qrel[2] = ax1[1] + ax2[1];
        qrel[3] = ax1[2] + ax2[2];

        dReal l = dRecip( sqrt( qrel[1] * qrel[1] + qrel[2] * qrel[2] + qrel[3] * qrel[3] ) );
        qrel[1] *= l;
        qrel[2] *= l;
        qrel[3] *= l;

        dQMultiply0( qcross2, qrel, qcross );

        if ( node[1].body )
        {
            dQMultiply1( qq, node[1].body->q, qcross2 );
            dQMultiply2( qrel, qq, qrel2 );
        }
        else
        {
            // pretend joint->node[1].body->q is the identity
            dQMultiply2( qrel, qcross2, qrel2 );
        }

        *angle2 = - getHingeAngleFromRelativeQuat( qrel, axis2 );
    }
    else
    {
        *angle1 = 0;
        *angle2 = 0;
    }
}

dReal
dxJointUniversal::getAngle1()
{
    if ( node[0].body )
    {
        // length 1 joint axis in global coordinates, from each body
        dVector3 ax1, ax2;
        dMatrix3 R;
        dQuaternion qcross, qq, qrel;

        getAxes( ax1, ax2 );

        // It should be possible to get both angles without explicitly
        // constructing the rotation matrix of the cross.  Basically,
        // orientation of the cross about axis1 comes from body 2,
        // about axis 2 comes from body 1, and the perpendicular
        // axis can come from the two bodies somehow.  (We don't really
        // want to assume it's 90 degrees, because in general the
        // constraints won't be perfectly satisfied, or even very well
        // satisfied.)
        //
        // However, we'd need a version of getHingeAngleFromRElativeQuat()
        // that CAN handle when its relative quat is rotated along a direction
        // other than the given axis.  What I have here works,
        // although it's probably much slower than need be.

        dRFrom2Axes( R, ax1[0], ax1[1], ax1[2], ax2[0], ax2[1], ax2[2] );
        dRtoQ( R, qcross );

        // This code is essential the same as getHingeAngle(), see the comments
        // there for details.

        // get qrel = relative rotation between node[0] and the cross
        dQMultiply1( qq, node[0].body->q, qcross );
        dQMultiply2( qrel, qq, qrel1 );

        return getHingeAngleFromRelativeQuat( qrel, axis1 );
    }
    return 0;
}


dReal
dxJointUniversal::getAngle2()
{
    if ( node[0].body )
    {
        // length 1 joint axis in global coordinates, from each body
        dVector3 ax1, ax2;
        dMatrix3 R;
        dQuaternion qcross, qq, qrel;

        getAxes( ax1, ax2 );

        // It should be possible to get both angles without explicitly
        // constructing the rotation matrix of the cross.  Basically,
        // orientation of the cross about axis1 comes from body 2,
        // about axis 2 comes from body 1, and the perpendicular
        // axis can come from the two bodies somehow.  (We don't really
        // want to assume it's 90 degrees, because in general the
        // constraints won't be perfectly satisfied, or even very well
        // satisfied.)
        //
        // However, we'd need a version of getHingeAngleFromRElativeQuat()
        // that CAN handle when its relative quat is rotated along a direction
        // other than the given axis.  What I have here works,
        // although it's probably much slower than need be.

        dRFrom2Axes( R, ax2[0], ax2[1], ax2[2], ax1[0], ax1[1], ax1[2] );
        dRtoQ( R, qcross );

        if ( node[1].body )
        {
            dQMultiply1( qq, node[1].body->q, qcross );
            dQMultiply2( qrel, qq, qrel2 );
        }
        else
        {
            // pretend joint->node[1].body->q is the identity
            dQMultiply2( qrel, qcross, qrel2 );
        }

        return - getHingeAngleFromRelativeQuat( qrel, axis2 );
    }
    return 0;
}


void 
dxJointUniversal::getSureMaxInfo( SureMaxInfo* info )
{
  info->max_m = 6;
}


void
dxJointUniversal::getInfo1( dxJoint::Info1 *info )
{
    info->nub = 4;
    info->m = 4;

    bool limiting1 = ( limot1.lostop >= -M_PI || limot1.histop <= M_PI ) &&
                     limot1.lostop <= limot1.histop;
    bool limiting2 = ( limot2.lostop >= -M_PI || limot2.histop <= M_PI ) &&
                     limot2.lostop <= limot2.histop;

    // We need to call testRotationLimit() even if we're motored, since it
    // records the result.
    limot1.limit = 0;
    limot2.limit = 0;

    if ( limiting1 || limiting2 )
    {
        dReal angle1, angle2;
        getAngles( &angle1, &angle2 );
        if ( limiting1 )
            limot1.testRotationalLimit( angle1 );
        if ( limiting2 )
            limot2.testRotationalLimit( angle2 );
    }

    if ( limot1.limit || limot1.fmax > 0 ) info->m++;
    if ( limot2.limit || limot2.fmax > 0 ) info->m++;
}


void
dxJointUniversal::getInfo2( dxJoint::Info2 *info )
{
    // set the three ball-and-socket rows
    setBall( this, info, anchor1, anchor2 );

    // set the universal joint row. the angular velocity about an axis
    // perpendicular to both joint axes should be equal. thus the constraint
    // equation is
    //    p*w1 - p*w2 = 0
    // where p is a vector normal to both joint axes, and w1 and w2
    // are the angular velocity vectors of the two bodies.

    // length 1 joint axis in global coordinates, from each body
    dVector3 ax1, ax2;
    dVector3 ax2_temp;
    // length 1 vector perpendicular to ax1 and ax2. Neither body can rotate
    // about this.
    dVector3 p;
    dReal k;

    // Since axis1 and axis2 may not be perpendicular
    // we find a axis2_tmp which is really perpendicular to axis1
    // and in the plane of axis1 and axis2
    getAxes( ax1, ax2 );
    k = dCalcVectorDot3( ax1, ax2 );
    ax2_temp[0] = ax2[0] - k * ax1[0];
    ax2_temp[1] = ax2[1] - k * ax1[1];
    ax2_temp[2] = ax2[2] - k * ax1[2];
    dCalcVectorCross3( p, ax1, ax2_temp );
    dNormalize3( p );

    int s3 = 3 * info->rowskip;

    info->J1a[s3+0] = p[0];
    info->J1a[s3+1] = p[1];
    info->J1a[s3+2] = p[2];

    if ( node[1].body )
    {
        info->J2a[s3+0] = -p[0];
        info->J2a[s3+1] = -p[1];
        info->J2a[s3+2] = -p[2];
    }

    // compute the right hand side of the constraint equation. set relative
    // body velocities along p to bring the axes back to perpendicular.
    // If ax1, ax2 are unit length joint axes as computed from body1 and
    // body2, we need to rotate both bodies along the axis p.  If theta
    // is the angle between ax1 and ax2, we need an angular velocity
    // along p to cover the angle erp * (theta - Pi/2) in one step:
    //
    //   |angular_velocity| = angle/time = erp*(theta - Pi/2) / stepsize
    //                      = (erp*fps) * (theta - Pi/2)
    //
    // if theta is close to Pi/2,
    // theta - Pi/2 ~= cos(theta), so
    //    |angular_velocity|  ~= (erp*fps) * (ax1 dot ax2)

    info->c[3] = info->fps * info->erp * - k;

    // if the first angle is powered, or has joint limits, add in the stuff
    int row = 4 + limot1.addLimot( this, info, 4, ax1, 1 );

    // if the second angle is powered, or has joint limits, add in more stuff
    limot2.addLimot( this, info, row, ax2, 1 );
}


void
dxJointUniversal::computeInitialRelativeRotations()
{
    if ( node[0].body )
    {
        dVector3 ax1, ax2;
        dMatrix3 R;
        dQuaternion qcross;

        getAxes( ax1, ax2 );

        // Axis 1.
        dRFrom2Axes( R, ax1[0], ax1[1], ax1[2], ax2[0], ax2[1], ax2[2] );
        dRtoQ( R, qcross );
        dQMultiply1( qrel1, node[0].body->q, qcross );

        // Axis 2.
        dRFrom2Axes( R, ax2[0], ax2[1], ax2[2], ax1[0], ax1[1], ax1[2] );
        dRtoQ( R, qcross );
        if ( node[1].body )
        {
            dQMultiply1( qrel2, node[1].body->q, qcross );
        }
        else
        {
            // set joint->qrel to qcross
            for ( int i = 0; i < 4; i++ ) qrel2[i] = qcross[i];
        }
    }
}


void dJointSetUniversalAnchor( dJointID j, dReal x, dReal y, dReal z )
{
    dxJointUniversal* joint = ( dxJointUniversal* )j;
    dUASSERT( joint, "bad joint argument" );
    checktype( joint, Universal );
    setAnchors( joint, x, y, z, joint->anchor1, joint->anchor2 );
    joint->computeInitialRelativeRotations();
}


void dJointSetUniversalAxis1( dJointID j, dReal x, dReal y, dReal z )
{
    dxJointUniversal* joint = ( dxJointUniversal* )j;
    dUASSERT( joint, "bad joint argument" );
    checktype( joint, Universal );
    if ( joint->flags & dJOINT_REVERSE )
        setAxes( joint, x, y, z, NULL, joint->axis2 );
    else
        setAxes( joint, x, y, z, joint->axis1, NULL );
    joint->computeInitialRelativeRotations();
}

void dJointSetUniversalAxis1Offset( dJointID j, dReal x, dReal y, dReal z,
                                    dReal offset1, dReal offset2 )
{
    dxJointUniversal* joint = ( dxJointUniversal* )j;
    dUASSERT( joint, "bad joint argument" );
    checktype( joint, Universal );
    if ( joint->flags & dJOINT_REVERSE )
    {
        setAxes( joint, x, y, z, NULL, joint->axis2 );
        offset1 = -offset1;
        offset2 = -offset2;
    }
    else
        setAxes( joint, x, y, z, joint->axis1, NULL );

    joint->computeInitialRelativeRotations();


    dVector3 ax2;
    getAxis2( joint, ax2, joint->axis2 );

    {
        dVector3 ax1;
        joint->getAxes(ax1, ax2);
    }



    dQuaternion qAngle;
    dQFromAxisAndAngle(qAngle, x, y, z, offset1);

    dMatrix3 R;
    dRFrom2Axes( R, x, y, z, ax2[0], ax2[1], ax2[2] );

    dQuaternion qcross;
    dRtoQ( R, qcross );

    dQuaternion qOffset;
    dQMultiply0(qOffset, qAngle, qcross);

    dQMultiply1( joint->qrel1, joint->node[0].body->q, qOffset );

    // Calculating the second offset
    dQFromAxisAndAngle(qAngle, ax2[0], ax2[1], ax2[2], offset2);

    dRFrom2Axes( R, ax2[0], ax2[1], ax2[2], x, y, z );
    dRtoQ( R, qcross );

    dQMultiply1(qOffset, qAngle, qcross);
    if ( joint->node[1].body )
    {
        dQMultiply1( joint->qrel2, joint->node[1].body->q, qOffset );
    }
    else
    {
        joint->qrel2[0] = qcross[0];
        joint->qrel2[1] = qcross[1];
        joint->qrel2[2] = qcross[2];
        joint->qrel2[3] = qcross[3];
    }
}


void dJointSetUniversalAxis2( dJointID j, dReal x, dReal y, dReal z )
{
    dxJointUniversal* joint = ( dxJointUniversal* )j;
    dUASSERT( joint, "bad joint argument" );
    checktype( joint, Universal );
    if ( joint->flags & dJOINT_REVERSE )
        setAxes( joint, x, y, z, joint->axis1, NULL );
    else
        setAxes( joint, x, y, z, NULL, joint->axis2 );
    joint->computeInitialRelativeRotations();
}

void dJointSetUniversalAxis2Offset( dJointID j, dReal x, dReal y, dReal z,
                                    dReal offset1, dReal offset2 )
{
    dxJointUniversal* joint = ( dxJointUniversal* )j;
    dUASSERT( joint, "bad joint argument" );
    checktype( joint, Universal );

    if ( joint->flags & dJOINT_REVERSE )
    {
        setAxes( joint, x, y, z, joint->axis1, NULL );
        offset1 = -offset2;
        offset2 = -offset1;
    }
    else
        setAxes( joint, x, y, z, NULL, joint->axis2 );


    joint->computeInitialRelativeRotations();

    // It is easier to retreive the 2 axes here since
    // when there is only one body B2 (the axes switch position)
    // Doing this way eliminate the need to write the code differently
    // for both case.
    dVector3 ax1, ax2;
    joint->getAxes(ax1, ax2 );



    dQuaternion qAngle;
    dQFromAxisAndAngle(qAngle, ax1[0], ax1[1], ax1[2], offset1);

    dMatrix3 R;
    dRFrom2Axes( R, ax1[0], ax1[1], ax1[2], ax2[0], ax2[1], ax2[2]);

    dQuaternion qcross;
    dRtoQ( R, qcross );

    dQuaternion qOffset;
    dQMultiply0(qOffset, qAngle, qcross);



    dQMultiply1( joint->qrel1, joint->node[0].body->q, qOffset );


    // Calculating the second offset
    dQFromAxisAndAngle(qAngle, ax2[0], ax2[1], ax2[2], offset2);

    dRFrom2Axes( R, ax2[0], ax2[1], ax2[2], ax1[0], ax1[1], ax1[2]);
    dRtoQ( R, qcross );

    dQMultiply1(qOffset, qAngle, qcross);
    if ( joint->node[1].body )
    {
        dQMultiply1( joint->qrel2, joint->node[1].body->q, qOffset );
    }
    else
    {
        joint->qrel2[0] = qcross[0];
        joint->qrel2[1] = qcross[1];
        joint->qrel2[2] = qcross[2];
        joint->qrel2[3] = qcross[3];
    }
}


void dJointGetUniversalAnchor( dJointID j, dVector3 result )
{
    dxJointUniversal* joint = ( dxJointUniversal* )j;
    dUASSERT( joint, "bad joint argument" );
    dUASSERT( result, "bad result argument" );
    checktype( joint, Universal );
    if ( joint->flags & dJOINT_REVERSE )
        getAnchor2( joint, result, joint->anchor2 );
    else
        getAnchor( joint, result, joint->anchor1 );
}


void dJointGetUniversalAnchor2( dJointID j, dVector3 result )
{
    dxJointUniversal* joint = ( dxJointUniversal* )j;
    dUASSERT( joint, "bad joint argument" );
    dUASSERT( result, "bad result argument" );
    checktype( joint, Universal );
    if ( joint->flags & dJOINT_REVERSE )
        getAnchor( joint, result, joint->anchor1 );
    else
        getAnchor2( joint, result, joint->anchor2 );
}


void dJointGetUniversalAxis1( dJointID j, dVector3 result )
{
    dxJointUniversal* joint = ( dxJointUniversal* )j;
    dUASSERT( joint, "bad joint argument" );
    dUASSERT( result, "bad result argument" );
    checktype( joint, Universal );
    if ( joint->flags & dJOINT_REVERSE )
        getAxis2( joint, result, joint->axis2 );
    else
        getAxis( joint, result, joint->axis1 );
}


void dJointGetUniversalAxis2( dJointID j, dVector3 result )
{
    dxJointUniversal* joint = ( dxJointUniversal* )j;
    dUASSERT( joint, "bad joint argument" );
    dUASSERT( result, "bad result argument" );
    checktype( joint, Universal );
    if ( joint->flags & dJOINT_REVERSE )
        getAxis( joint, result, joint->axis1 );
    else
        getAxis2( joint, result, joint->axis2 );
}


void dJointSetUniversalParam( dJointID j, int parameter, dReal value )
{
    dxJointUniversal* joint = ( dxJointUniversal* )j;
    dUASSERT( joint, "bad joint argument" );
    checktype( joint, Universal );
    if (( parameter & 0xff00 ) == 0x100 )
    {
        joint->limot2.set( parameter & 0xff, value );
    }
    else
    {
        joint->limot1.set( parameter, value );
    }
}


dReal dJointGetUniversalParam( dJointID j, int parameter )
{
    dxJointUniversal* joint = ( dxJointUniversal* )j;
    dUASSERT( joint, "bad joint argument" );
    checktype( joint, Universal );
    if (( parameter & 0xff00 ) == 0x100 )
    {
        return joint->limot2.get( parameter & 0xff );
    }
    else
    {
        return joint->limot1.get( parameter );
    }
}

void dJointGetUniversalAngles( dJointID j, dReal *angle1, dReal *angle2 )
{
    dxJointUniversal* joint = ( dxJointUniversal* )j;
    dUASSERT( joint, "bad joint argument" );
    checktype( joint, Universal );
    if ( joint->flags & dJOINT_REVERSE )
    {
        joint->getAngles( angle2, angle1 );
        *angle2 = -(*angle2);
        return;
    }
    else
        return joint->getAngles( angle1, angle2 );
}


dReal dJointGetUniversalAngle1( dJointID j )
{
    dxJointUniversal* joint = ( dxJointUniversal* )j;
    dUASSERT( joint, "bad joint argument" );
    checktype( joint, Universal );
    if ( joint->flags & dJOINT_REVERSE )
        return joint->getAngle2();
    else
        return joint->getAngle1();
}


dReal dJointGetUniversalAngle2( dJointID j )
{
    dxJointUniversal* joint = ( dxJointUniversal* )j;
    dUASSERT( joint, "bad joint argument" );
    checktype( joint, Universal );
    if ( joint->flags & dJOINT_REVERSE )
        return -joint->getAngle1();
    else
        return joint->getAngle2();
}


dReal dJointGetUniversalAngle1Rate( dJointID j )
{
    dxJointUniversal* joint = ( dxJointUniversal* )j;
    dUASSERT( joint, "bad joint argument" );
    checktype( joint, Universal );

    if ( joint->node[0].body )
    {
        dVector3 axis;

        if ( joint->flags & dJOINT_REVERSE )
            getAxis2( joint, axis, joint->axis2 );
        else
            getAxis( joint, axis, joint->axis1 );

        dReal rate = dCalcVectorDot3( axis, joint->node[0].body->avel );
        if ( joint->node[1].body )
            rate -= dCalcVectorDot3( axis, joint->node[1].body->avel );
        return rate;
    }
    return 0;
}


dReal dJointGetUniversalAngle2Rate( dJointID j )
{
    dxJointUniversal* joint = ( dxJointUniversal* )j;
    dUASSERT( joint, "bad joint argument" );
    checktype( joint, Universal );

    if ( joint->node[0].body )
    {
        dVector3 axis;

        if ( joint->flags & dJOINT_REVERSE )
            getAxis( joint, axis, joint->axis1 );
        else
            getAxis2( joint, axis, joint->axis2 );

        dReal rate = dCalcVectorDot3( axis, joint->node[0].body->avel );
        if ( joint->node[1].body ) rate -= dCalcVectorDot3( axis, joint->node[1].body->avel );
        return rate;
    }
    return 0;
}


void dJointAddUniversalTorques( dJointID j, dReal torque1, dReal torque2 )
{
    dxJointUniversal* joint = ( dxJointUniversal* )j;
    dVector3 axis1, axis2;
    dAASSERT( joint );
    checktype( joint, Universal );

    if ( joint->flags & dJOINT_REVERSE )
    {
        dReal temp = torque1;
        torque1 = - torque2;
        torque2 = - temp;
    }

    getAxis( joint, axis1, joint->axis1 );
    getAxis2( joint, axis2, joint->axis2 );
    axis1[0] = axis1[0] * torque1 + axis2[0] * torque2;
    axis1[1] = axis1[1] * torque1 + axis2[1] * torque2;
    axis1[2] = axis1[2] * torque1 + axis2[2] * torque2;

    if ( joint->node[0].body != 0 )
        dBodyAddTorque( joint->node[0].body, axis1[0], axis1[1], axis1[2] );
    if ( joint->node[1].body != 0 )
        dBodyAddTorque( joint->node[1].body, -axis1[0], -axis1[1], -axis1[2] );
}


dJointType
dxJointUniversal::type() const
{
    return dJointTypeUniversal;
}


size_t
dxJointUniversal::size() const
{
    return sizeof( *this );
}



void
dxJointUniversal::setRelativeValues()
{
    dVector3 anchor;
    dJointGetUniversalAnchor(this, anchor);
    setAnchors( this, anchor[0], anchor[1], anchor[2], anchor1, anchor2 );

    dVector3 ax1,ax2;
    dJointGetUniversalAxis1(this, ax1);
    dJointGetUniversalAxis2(this, ax2);

    if ( flags & dJOINT_REVERSE )
    {
        setAxes( this, ax1[0],ax1[1],ax1[2], NULL, axis2 );
        setAxes( this, ax2[0],ax2[1],ax2[2], axis1, NULL );
    }
    else
    {
        setAxes( this, ax1[0],ax1[1],ax1[2], axis1, NULL );
        setAxes( this, ax2[0],ax2[1],ax2[2], NULL, axis2 );
    }

    computeInitialRelativeRotations();
}

