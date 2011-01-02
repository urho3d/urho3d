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
#include "piston.h"
#include "joint_internal.h"



//****************************************************************************
// Piston
//

dxJointPiston::dxJointPiston ( dxWorld *w ) :
        dxJoint ( w )
{
    dSetZero ( axis1, 4 );
    dSetZero ( axis2, 4 );

    axis1[0] = 1;
    axis2[0] = 1;

    dSetZero ( qrel, 4 );

    dSetZero ( anchor1, 4 );
    dSetZero ( anchor2, 4 );

    limotP.init ( world );

    limotR.init ( world );
}


dReal dJointGetPistonPosition ( dJointID j )
{
    dxJointPiston* joint = ( dxJointPiston* ) j;
    dUASSERT ( joint, "bad joint argument" );
    checktype ( joint, Piston );

    if ( joint->node[0].body )
    {
        dVector3 q;
        // get the anchor (or offset) in global coordinates
        dMultiply0_331 ( q, joint->node[0].body->posr.R, joint->anchor1 );

        if ( joint->node[1].body )
        {
            dVector3 anchor2;
            // get the anchor2 in global coordinates
            dMultiply0_331 ( anchor2, joint->node[1].body->posr.R, joint->anchor2 );

            q[0] = ( ( joint->node[0].body->posr.pos[0] + q[0] ) -
                     ( joint->node[1].body->posr.pos[0] + anchor2[0] ) );
            q[1] = ( ( joint->node[0].body->posr.pos[1] + q[1] ) -
                     ( joint->node[1].body->posr.pos[1] + anchor2[1] ) );
            q[2] = ( ( joint->node[0].body->posr.pos[2] + q[2] ) -
                     ( joint->node[1].body->posr.pos[2] + anchor2[2] ) );
        }
        else
        {
            // N.B. When there is no body 2 the joint->anchor2 is already in
            //      global coordinates
            q[0] = ( ( joint->node[0].body->posr.pos[0] + q[0] ) -
                     ( joint->anchor2[0] ) );
            q[1] = ( ( joint->node[0].body->posr.pos[1] + q[1] ) -
                     ( joint->anchor2[1] ) );
            q[2] = ( ( joint->node[0].body->posr.pos[2] + q[2] ) -
                     ( joint->anchor2[2] ) );

            if ( joint->flags & dJOINT_REVERSE )
            {
                q[0] = -q[0];
                q[1] = -q[1];
                q[2] = -q[2];
            }
        }

        // get axis in global coordinates
        dVector3 ax;
        dMultiply0_331 ( ax, joint->node[0].body->posr.R, joint->axis1 );

        return dCalcVectorDot3 ( ax, q );
    }

    dDEBUGMSG ( "The function always return 0 since no body are attached" );
    return 0;
}


dReal dJointGetPistonPositionRate ( dJointID j )
{
    dxJointPiston* joint = ( dxJointPiston* ) j;
    dUASSERT ( joint, "bad joint argument" );
    checktype ( joint, Piston );

    // get axis in global coordinates
    dVector3 ax;
    dMultiply0_331 ( ax, joint->node[0].body->posr.R, joint->axis1 );

    // The linear velocity created by the rotation can be discarded since
    // the rotation is along the prismatic axis and this rotation don't create
    // linear velocity in the direction of the prismatic axis.
    if ( joint->node[1].body )
    {
        return ( dCalcVectorDot3 ( ax, joint->node[0].body->lvel ) -
                 dCalcVectorDot3 ( ax, joint->node[1].body->lvel ) );
    }
    else
    {
        dReal rate = dCalcVectorDot3 ( ax, joint->node[0].body->lvel );
        return ( (joint->flags & dJOINT_REVERSE) ? -rate : rate);
    }
}


dReal dJointGetPistonAngle ( dJointID j )
{
    dxJointPiston* joint = ( dxJointPiston * ) j;
    dAASSERT ( joint );
    checktype ( joint, Piston );

    if ( joint->node[0].body )
    {
        dReal ang = getHingeAngle ( joint->node[0].body, joint->node[1].body, joint->axis1,
                                    joint->qrel );
        if ( joint->flags & dJOINT_REVERSE )
            return -ang;
        else
            return ang;
    }
    else return 0;
}


dReal dJointGetPistonAngleRate ( dJointID j )
{
    dxJointPiston* joint = ( dxJointPiston* ) j;
    dAASSERT ( joint );
    checktype ( joint, Piston );

    if ( joint->node[0].body )
    {
        dVector3 axis;
        dMultiply0_331 ( axis, joint->node[0].body->posr.R, joint->axis1 );
        dReal rate = dCalcVectorDot3 ( axis, joint->node[0].body->avel );
        if ( joint->node[1].body ) rate -= dCalcVectorDot3 ( axis, joint->node[1].body->avel );
        if ( joint->flags & dJOINT_REVERSE ) rate = - rate;
        return rate;
    }
    else return 0;
}


void 
dxJointPiston::getSureMaxInfo( SureMaxInfo* info )
{
  info->max_m = 6;
}


void
dxJointPiston::getInfo1 ( dxJoint::Info1 *info )
{
    info->nub = 4; // Number of unbound variables
    // The only bound variable is one linear displacement

    info->m = 4; // Default number of constraint row

    // see if we're at a joint limit.
    limotP.limit = 0;
    if ( ( limotP.lostop > -dInfinity || limotP.histop < dInfinity ) &&
            limotP.lostop <= limotP.histop )
    {
        // measure joint position
        dReal pos = dJointGetPistonPosition ( this );
        limotP.testRotationalLimit ( pos );     // N.B. The fucntion is ill named
    }

    // powered Piston or at limits needs an extra constraint row
    if ( limotP.limit || limotP.fmax > 0 ) info->m++;


    // see if we're at a joint limit.
    limotR.limit = 0;
    if ( ( limotR.lostop > -dInfinity || limotR.histop < dInfinity ) &&
            limotR.lostop <= limotR.histop )
    {
        // measure joint position
        dReal angle = getHingeAngle ( node[0].body, node[1].body, axis1,
                                      qrel );
        limotR.testRotationalLimit ( angle );
    }

    // powered Piston or at limits needs an extra constraint row
    if ( limotR.limit || limotR.fmax > 0 ) info->m++;

}


void
dxJointPiston::getInfo2 ( dxJoint::Info2 *info )
{
    const int s0 = 0;
    const int s1 = info->rowskip;
    const int s2 = 2 * s1, s3 = 3 * s1 /*, s4=4*s1*/;

    const dReal k = info->fps * info->erp;


    // Pull out pos and R for both bodies. also get the `connection'
    // vector pos2-pos1.

    dReal *pos1, *pos2, *R1, *R2=0;
    dVector3 dist; // Current position of body_1  w.r.t "anchor"
    // 2 bodies anchor is center of body 2
    // 1 bodies anchor is origin
    dVector3 lanchor2=
    {
        0,0,0
    };

    pos1 = node[0].body->posr.pos;
    R1   = node[0].body->posr.R;

    if ( node[1].body )
    {
        pos2 = node[1].body->posr.pos;
        R2   = node[1].body->posr.R;

        dMultiply0_331 ( lanchor2, R2, anchor2 );
        dist[0] = lanchor2[0] + pos2[0] - pos1[0];
        dist[1] = lanchor2[1] + pos2[1] - pos1[1];
        dist[2] = lanchor2[2] + pos2[2] - pos1[2];
    }
    else
    {
        // pos2 = 0; // N.B. We can do that to be safe but it is no necessary
        // R2 = 0;   // N.B. We can do that to be safe but it is no necessary
        if (flags & dJOINT_REVERSE )
        {
            dist[0] = pos1[0] - anchor2[0]; // Invert the value
            dist[1] = pos1[1] - anchor2[1];
            dist[2] = pos1[2] - anchor2[2];
        }
        else
        {
            dist[0] = anchor2[0] - pos1[0];
            dist[1] = anchor2[1] - pos1[1];
            dist[2] = anchor2[2] - pos1[2];
        }
    }

    // ======================================================================
    // Work on the angular part (i.e. row 0, 1)
    // Set the two orientation rows. The rotoide axis should be the only
    // unconstrained rotational axis, the angular velocity of the two bodies
    // perpendicular to the rotoide axis should be equal.
    // Thus the constraint equations are:
    //    p*w1 - p*w2 = 0
    //    q*w1 - q*w2 = 0
    // where p and q are unit vectors normal to the rotoide axis, and w1 and w2
    // are the angular velocity vectors of the two bodies.
    // Since the rotoide axis is the same as the prismatic axis.
    //
    //
    // Also, compute the right hand side (RHS) of the rotation constraint equation set.
    // The first 2 element will result in the relative angular velocity of the two
    // bodies along axis p and q. This is set to bring the rotoide back into alignment.
    // if `theta' is the angle between ax1 and ax2, we need an angular velocity
    // along u to cover angle erp*theta in one step :
    //   |angular_velocity| = angle/time = erp*theta / stepsize
    //                      = (erp*fps) * theta
    //    angular_velocity  = |angular_velocity| * u
    //                      = (erp*fps) * theta * u
    // where rotation along unit length axis u by theta brings body 2's frame
    //
    // if theta is smallish, sin(theta) ~= theta and cos(theta) ~= 1
    // where the quaternion of the relative rotation between the two bodies is
    //    quat = [cos(theta/2) sin(theta/2)*u]
    //    quat = [1 theta/2*u]
    //         => q[0] ~= 1
    //            2 * q[1+i] = theta * u[i]
    //
    // Since there is no constraint along the rotoide axis
    // only along p and q that we want the same angular velocity and need to reduce
    // the error
    dVector3 ax1, p, q;
    dMultiply0_331 ( ax1, node[0].body->posr.R, axis1 );

    // Find the 2 axis perpendicular to the rotoide axis.
    dPlaneSpace ( ax1, p, q );

    // LHS
    dCopyVector3 ( ( info->J1a ) + s0, p );
    dCopyVector3 ( ( info->J1a ) + s1, q );

    dVector3 b;
    if ( node[1].body )
    {
        // LHS
        //  info->J2a[s0+i] = -p[i]
        dCopyNegatedVector3 ( ( info->J2a ) + s0, p );
        dCopyNegatedVector3 ( ( info->J2a ) + s1, q );


        // Some math for the RHS
        dVector3 ax2;
        dMultiply0_331 ( ax2, R2, axis2 );
        dCalcVectorCross3( b, ax1, ax2 );
    }
    else
    {
        // Some math for the RHS
        dCalcVectorCross3( b, ax1, axis2 );
    }

    // RHS
    info->c[0] = k * dCalcVectorDot3 ( p, b );
    info->c[1] = k * dCalcVectorDot3 ( q, b );


    // ======================================================================
    // Work on the linear part (i.e row 2,3)
    // p2 + R2 anchor2' = p1 + R1 dist'
    // v2 + w2 R2 anchor2' + R2 d(anchor2')/dt  = v1 + w1 R1 dist' + R1 d(dist')/dt
    // v2 + w2 x anchor2 = v1 + w1 x dist + v_p
    // v_p is speed of prismatic joint (i.e. elongation rate)
    // Since the constraints are perpendicular to v_p we have:
    // p . v_p = 0 and q . v_p = 0
    // Along p and q we have (since sliding along the prismatic axis is disregarded):
    // u . ( v2 + w2 x anchor2 = v1 + w1 x dist + v_p) ( where u is p or q )
    // Simplify
    // u . v2 + u. w2 x anchor2 = u . v1 + u . w1 x dist
    // or
    // u . v1 - u . v2 + u . w1 x dist - u2 . w2 x anchor2 = 0
    // using the fact that (a x b = - b x a)
    // u . v1 - u . v2 - u . dist x w1  + u . anchor2 x w2 = 0
    // With the help of the triple product:
    //   i.e.  a . b x c = b . c x a = c . a x b  or  a . b x c = a x b . c
    //   Ref: http://mathworld.wolfram.com/ScalarTripleProduct.html
    // u . v1 - u . v2 - u x dist . w1 + u x anchor2 . w2 = 0
    // u . v1 - u . v2 + dist x u . w1 - u x anchor2 . w2 = 0
    //
    // Coeff for 1er line of: J1l => p, J2l => -p
    // Coeff for 2er line of: J1l => q, J2l => -q
    // Coeff for 1er line of: J1a => dist x p, J2a => p x anchor2
    // Coeff for 2er line of: J1a => dist x q, J2a => q x anchor2

    dCalcVectorCross3( ( info->J1a ) + s2, dist, p );

    dCalcVectorCross3( ( info->J1a ) + s3, dist, q );

    dCopyVector3 ( ( info->J1l ) + s2, p );
    dCopyVector3 ( ( info->J1l ) + s3, q );

    if ( node[1].body )
    {
        // q x anchor2 instead of anchor2 x q since we want the negative value
        dCalcVectorCross3( ( info->J2a ) + s2, p, lanchor2 );

        // The cross product is in reverse order since we want the negative value
        dCalcVectorCross3( ( info->J2a ) + s3, q, lanchor2 );

        // info->J2l[s2+i] = -p[i];
        dCopyNegatedVector3 ( ( info->J2l ) + s2, p );
        dCopyNegatedVector3 ( ( info->J2l ) + s3, q );
    }


    // We want to make correction for motion not in the line of the axis
    // We calculate the displacement w.r.t. the "anchor" pt.
    // i.e. Find the difference between the current position and the initial
    //      position along the constrained axies (i.e. axis p and q).
    // The bodies can move w.r.t each other only along the prismatic axis
    //
    // Compute the RHS of rows 2 and 3
    dVector3 err;
    dMultiply0_331 ( err, R1, anchor1 );
    dSubtractVectors3( err, dist, err );

    info->c[2] = k * dCalcVectorDot3 ( p, err );
    info->c[3] = k * dCalcVectorDot3 ( q, err );


    int row = 4;
    if (  node[1].body )
    {
        row += limotP.addLimot ( this, info, 4, ax1, 0 );
    }
    else if (flags & dJOINT_REVERSE )
    {
        dVector3 rAx1;
        rAx1[0] = -ax1[0];
        rAx1[1] = -ax1[1];
        rAx1[2] = -ax1[2];
        row += limotP.addLimot ( this, info, 4, rAx1, 0 );
    }
    else
        row += limotP.addLimot ( this, info, 4, ax1, 0 );

    limotR.addLimot ( this, info, row, ax1, 1 );
}

void dJointSetPistonAnchor ( dJointID j, dReal x, dReal y, dReal z )
{
    dxJointPiston* joint = ( dxJointPiston* ) j;
    dUASSERT ( joint, "bad joint argument" );
    checktype ( joint, Piston );
    setAnchors ( joint, x, y, z, joint->anchor1, joint->anchor2 );
    joint->computeInitialRelativeRotation();

}

void dJointSetPistonAnchorOffset (dJointID j, dReal x, dReal y, dReal z,
                                  dReal dx, dReal dy, dReal dz)
{
    dxJointPiston* joint = (dxJointPiston*) j;
    dUASSERT (joint,"bad joint argument");
    checktype ( joint, Piston );

    if (joint->flags & dJOINT_REVERSE)
    {
        dx = -dx;
        dy = -dy;
        dz = -dz;
    }

    if (joint->node[0].body)
    {
        joint->node[0].body->posr.pos[0] -= dx;
        joint->node[0].body->posr.pos[1] -= dy;
        joint->node[0].body->posr.pos[2] -= dz;
    }

    setAnchors (joint,x ,y, z, joint->anchor1, joint->anchor2);

    if (joint->node[0].body)
    {
        joint->node[0].body->posr.pos[0] += dx;
        joint->node[0].body->posr.pos[1] += dy;
        joint->node[0].body->posr.pos[2] += dz;
    }

    joint->computeInitialRelativeRotation();
}



void dJointGetPistonAnchor ( dJointID j, dVector3 result )
{
    dxJointPiston* joint = ( dxJointPiston* ) j;
    dUASSERT ( joint, "bad joint argument" );
    dUASSERT ( result, "bad result argument" );
    checktype ( joint, Piston );
    if ( joint->flags & dJOINT_REVERSE )
        getAnchor2 ( joint, result, joint->anchor2 );
    else
        getAnchor ( joint, result, joint->anchor1 );
}


void dJointGetPistonAnchor2 ( dJointID j, dVector3 result )
{
    dxJointPiston* joint = ( dxJointPiston* ) j;
    dUASSERT ( joint, "bad joint argument" );
    dUASSERT ( result, "bad result argument" );
    checktype ( joint, Piston );
    if ( joint->flags & dJOINT_REVERSE )
        getAnchor ( joint, result, joint->anchor1 );
    else
        getAnchor2 ( joint, result, joint->anchor2 );
}



void dJointSetPistonAxis ( dJointID j, dReal x, dReal y, dReal z )
{
    dxJointPiston* joint = ( dxJointPiston* ) j;
    dUASSERT ( joint, "bad joint argument" );
    checktype ( joint, Piston );

    setAxes ( joint, x, y, z, joint->axis1, joint->axis2 );

    joint->computeInitialRelativeRotation();
}


void dJointSetPistonAxisDelta ( dJointID j, dReal x, dReal y, dReal z,
                                dReal dx, dReal dy, dReal dz )
{
    dxJointPiston* joint = ( dxJointPiston* ) j;
    dUASSERT ( joint, "bad joint argument" );
    checktype ( joint, Piston );

    setAxes ( joint, x, y, z, joint->axis1, joint->axis2 );

    joint->computeInitialRelativeRotation();

    dVector3 c = {0,0,0};
    if ( joint->node[1].body )
    {
        c[0] = ( joint->node[0].body->posr.pos[0] -
                 joint->node[1].body->posr.pos[0] - dx );
        c[1] = ( joint->node[0].body->posr.pos[1] -
                 joint->node[1].body->posr.pos[1] - dy );
        c[2] = ( joint->node[0].body->posr.pos[2] -
                 joint->node[1].body->posr.pos[2] - dz );
    }
    else if ( joint->node[0].body )
    {
        c[0] = joint->node[0].body->posr.pos[0] - dx;
        c[1] = joint->node[0].body->posr.pos[1] - dy;
        c[2] = joint->node[0].body->posr.pos[2] - dz;
    }

    // Convert into frame of body 1
    dMultiply1_331 ( joint->anchor1, joint->node[0].body->posr.R, c );
}



void dJointGetPistonAxis ( dJointID j, dVector3 result )
{
    dxJointPiston* joint = ( dxJointPiston* ) j;
    dUASSERT ( joint, "bad joint argument" );
    dUASSERT ( result, "bad result argument" );
    checktype ( joint, Piston );

    getAxis ( joint, result, joint->axis1 );
}

void dJointSetPistonParam ( dJointID j, int parameter, dReal value )
{
    dxJointPiston* joint = ( dxJointPiston* ) j;
    dUASSERT ( joint, "bad joint argument" );
    checktype ( joint, Piston );

    if ( ( parameter & 0xff00 ) == 0x100 )
    {
        joint->limotR.set ( parameter & 0xff, value );
    }
    else
    {
        joint->limotP.set ( parameter, value );
    }
}


dReal dJointGetPistonParam ( dJointID j, int parameter )
{
    dxJointPiston* joint = ( dxJointPiston* ) j;
    dUASSERT ( joint, "bad joint argument" );
    checktype ( joint, Piston );

    if ( ( parameter & 0xff00 ) == 0x100 )
    {
        return joint->limotR.get ( parameter & 0xff );
    }
    else
    {
        return joint->limotP.get ( parameter );
    }
}


void dJointAddPistonForce ( dJointID j, dReal force )
{
    dxJointPiston* joint = ( dxJointPiston* ) j;
    dUASSERT ( joint, "bad joint argument" );
    checktype ( joint, Piston );

    if ( joint->flags & dJOINT_REVERSE )
        force -= force;

    dVector3 axis;
    getAxis ( joint, axis, joint->axis1 );
    // axis[i] *= force
    dScaleVector3( axis, force );


    if ( joint->node[0].body != 0 )
        dBodyAddForce ( joint->node[0].body, axis[0], axis[1], axis[2] );
    if ( joint->node[1].body != 0 )
        dBodyAddForce ( joint->node[1].body, -axis[0], -axis[1], -axis[2] );

    if ( joint->node[0].body != 0 && joint->node[1].body != 0 )
    {
        // Case where we don't need ltd since center of mass of both bodies
        // pass by the anchor point '*' when travelling along the prismatic axis.
        //                                     Body_2
        //   Body_1                             -----
        //    ---                |--           |     |
        //   |   |---------------*-------------|     |     ---> prismatic axis
        //    ---                |--           |     |
        //                                      -----
        //                                      Body_2
        // Case where we need ltd
        //   Body_1
        //    ---
        //   |   |---------
        //    ---          |
        //                 |     |--
        //                  -----*-----                    ---> prismatic axis
        //                       |--   |
        //                             |
        //                             |
        //                             |        -----
        //                             |       |     |
        //                              -------|     |
        //                                     |     |
        //                                      -----
        //                                      Body_2
        //
        // In real life force apply at the '*' point
        // But in ODE the force are applied on the center of mass of Body_1 and Body_2
        // So we have to add torques on both bodies to compensate for that when there
        // is an offset between the anchor point and the center of mass of both bodies.
        //
        // We need to add to each body T = r x F
        // Where r is the distance between the cm and '*'

        dVector3 ltd; // Linear Torque Decoupling vector (a torque)
        dVector3 c;   // Distance of the body w.r.t the anchor
        // N.B. The distance along the prismatic axis might not
        //      not be included in this variable since it won't add
        //      anything to the ltd.

        // Calculate the distance of the body w.r.t the anchor

        // The anchor1 of body1 can be used since:
        // Real anchor = Position of body 1 + anchor + d* axis1 = anchor in world frame
        // d is the position of the prismatic joint (i.e. elongation)
        // Since axis1 x axis1 == 0
        // We can do the following.
        dMultiply0_331 ( c, joint->node[0].body->posr.R, joint->anchor1 );
        dCalcVectorCross3( ltd, c, axis );
        dBodyAddTorque ( joint->node[0].body, ltd[0], ltd[1], ltd[2] );


        dMultiply0_331 ( c, joint->node[1].body->posr.R, joint->anchor2 );
        dCalcVectorCross3( ltd, c, axis );
        dBodyAddTorque ( joint->node[1].body, ltd[0], ltd[1], ltd[2] );
    }
}


dJointType
dxJointPiston::type() const
{
    return dJointTypePiston;
}


size_t
dxJointPiston::size() const
{
    return sizeof ( *this );
}



void
dxJointPiston::setRelativeValues()
{
    dVector3 vec;
    dJointGetPistonAnchor(this, vec);
    setAnchors( this, vec[0], vec[1], vec[2], anchor1, anchor2 );

    dJointGetPistonAxis(this, vec);
    setAxes( this,  vec[0], vec[1], vec[2], axis1, axis2 );

    computeInitialRelativeRotation();
}




void
dxJointPiston::computeInitialRelativeRotation()
{
    if ( node[0].body )
    {
        if ( node[1].body )
        {
            dQMultiply1 ( qrel, node[0].body->q, node[1].body->q );
        }
        else
        {
            // set joint->qrel to the transpose of the first body q
            qrel[0] = node[0].body->q[0];
            for ( int i = 1; i < 4; i++ )
                qrel[i] = -node[0].body->q[i];
            // WARNING do we need the - in -joint->node[0].body->q[i]; or not
        }
    }
}
