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


#ifndef _ODE_JOINT_NTERNAL_H_
#define _ODE_JOINT_INTERNAL_H_


#include <ode/matrix.h>
#include <ode/odemath.h>
#include <ode/rotation.h>
#include <ode/objects.h>

#define checktype(j,t) dUASSERT(j->type() == dJointType##t, \
                                "joint type is not " #t)


void setBall( dxJoint *joint, dxJoint::Info2 *info,
              dVector3 anchor1, dVector3 anchor2 );
void setBall2( dxJoint *joint, dxJoint::Info2 *info,
               dVector3 anchor1, dVector3 anchor2,
               dVector3 axis, dReal erp1 );


void setAnchors( dxJoint *j, dReal x, dReal y, dReal z,
                 dVector3 anchor1, dVector3 anchor2 );

void getAnchor( dxJoint *j, dVector3 result, dVector3 anchor1 );
void getAnchor2( dxJoint *j, dVector3 result, dVector3 anchor2 );

void setAxes( dxJoint *j, dReal x, dReal y, dReal z,
              dVector3 axis1, dVector3 axis2 );
void getAxis( dxJoint *j, dVector3 result, dVector3 axis1 );
void getAxis2( dxJoint *j, dVector3 result, dVector3 axis2 );


dReal getHingeAngle( dxBody *body1, dxBody *body2, dVector3 axis, dQuaternion q_initial );
dReal getHingeAngleFromRelativeQuat( dQuaternion qrel, dVector3 axis );

void setFixedOrientation( dxJoint *joint, dxJoint::Info2 *info, dQuaternion qrel, int start_row );

#endif

