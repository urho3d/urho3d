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
#include "plane2d.h"
#include "joint_internal.h"



//****************************************************************************
// Plane2D
/*
    This code is part of the Plane2D ODE joint
    by psero@gmx.de
    Wed Apr 23 18:53:43 CEST 2003
*/


# define        VoXYZ(v1, o1, x, y, z) \
    ( \
      (v1)[0] o1 (x), \
      (v1)[1] o1 (y), \
      (v1)[2] o1 (z)  \
    )

static const dReal   Midentity[3][3] =
{
    {   1,  0,  0   },
    {   0,  1,  0   },
    {   0,  0,  1,  }
};


dxJointPlane2D::dxJointPlane2D( dxWorld *w ) :
        dxJoint( w )
{
    motor_x.init( world );
    motor_y.init( world );
    motor_angle.init( world );
}


void 
dxJointPlane2D::getSureMaxInfo( SureMaxInfo* info )
{
    info->max_m = 6;
}


void
dxJointPlane2D::getInfo1( dxJoint::Info1 *info )
{
    info->nub = 3;
    info->m = 3;

    if ( motor_x.fmax > 0 )
        row_motor_x = info->m ++;
    if ( motor_y.fmax > 0 )
        row_motor_y = info->m ++;
    if ( motor_angle.fmax > 0 )
        row_motor_angle = info->m ++;
}



void
dxJointPlane2D::getInfo2( dxJoint::Info2 *info )
{
    int         r0 = 0,
                     r1 = info->rowskip,
                          r2 = 2 * r1;
    dReal       eps = info->fps * info->erp;

    /*
        v = v1, w = omega1
        (v2, omega2 not important (== static environment))

        constraint equations:
            xz = 0
            wx = 0
            wy = 0

        <=> ( 0 0 1 ) (vx)   ( 0 0 0 ) (wx)   ( 0 )
            ( 0 0 0 ) (vy) + ( 1 0 0 ) (wy) = ( 0 )
            ( 0 0 0 ) (vz)   ( 0 1 0 ) (wz)   ( 0 )
            J1/J1l           Omega1/J1a
    */

    // fill in linear and angular coeff. for left hand side:

    VoXYZ( &info->J1l[r0], = , 0, 0, 1 );
    VoXYZ( &info->J1l[r1], = , 0, 0, 0 );
    VoXYZ( &info->J1l[r2], = , 0, 0, 0 );

    VoXYZ( &info->J1a[r0], = , 0, 0, 0 );
    VoXYZ( &info->J1a[r1], = , 1, 0, 0 );
    VoXYZ( &info->J1a[r2], = , 0, 1, 0 );

    // error correction (against drift):

    // a) linear vz, so that z (== pos[2]) == 0
    info->c[0] = eps * -node[0].body->posr.pos[2];

# if 0
    // b) angular correction? -> left to application !!!
    dReal       *body_z_axis = &node[0].body->R[8];
    info->c[1] = eps * + atan2( body_z_axis[1], body_z_axis[2] );  // wx error
    info->c[2] = eps * -atan2( body_z_axis[0], body_z_axis[2] );  // wy error
# endif

    // if the slider is powered, or has joint limits, add in the extra row:

    if ( row_motor_x > 0 )
        motor_x.addLimot( this, info, row_motor_x, Midentity[0], 0 );

    if ( row_motor_y > 0 )
        motor_y.addLimot( this, info, row_motor_y, Midentity[1], 0 );

    if ( row_motor_angle > 0 )
        motor_angle.addLimot( this, info, row_motor_angle, Midentity[2], 1 );
}


dJointType
dxJointPlane2D::type() const
{
    return dJointTypePlane2D;
};


size_t
dxJointPlane2D::size() const
{
    return sizeof( *this );
}



void dJointSetPlane2DXParam( dxJoint *joint,
                             int parameter, dReal value )
{
    dUASSERT( joint, "bad joint argument" );
    checktype( joint, Plane2D );
    dxJointPlane2D* joint2d = ( dxJointPlane2D* )( joint );
    joint2d->motor_x.set( parameter, value );
}


void dJointSetPlane2DYParam( dxJoint *joint,
                             int parameter, dReal value )
{
    dUASSERT( joint, "bad joint argument" );
    checktype( joint, Plane2D );
    dxJointPlane2D* joint2d = ( dxJointPlane2D* )( joint );
    joint2d->motor_y.set( parameter, value );
}



void dJointSetPlane2DAngleParam( dxJoint *joint,
                                 int parameter, dReal value )
{
    dUASSERT( joint, "bad joint argument" );
    checktype( joint, Plane2D );
    dxJointPlane2D* joint2d = ( dxJointPlane2D* )( joint );
    joint2d->motor_angle.set( parameter, value );
}

