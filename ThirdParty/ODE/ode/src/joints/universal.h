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

#ifndef _ODE_JOINT_UNIVERSAL_H_
#define _ODE_JOINT_UNIVERSAL_H_

#include "joint.h"

// universal

struct dxJointUniversal : public dxJoint
{
    dVector3 anchor1;   // anchor w.r.t first body
    dVector3 anchor2;   // anchor w.r.t second body
    dVector3 axis1;     // axis w.r.t first body
    dVector3 axis2;     // axis w.r.t second body
    dQuaternion qrel1;  // initial relative rotation body1 -> virtual cross piece
    dQuaternion qrel2;  // initial relative rotation virtual cross piece -> body2
    dxJointLimitMotor limot1; // limit and motor information for axis1
    dxJointLimitMotor limot2; // limit and motor information for axis2


    void getAxes( dVector3 ax1, dVector3 ax2 );
    void getAngles( dReal *angle1, dReal *angle2 );
    dReal getAngle1();
    dReal getAngle2();
    void computeInitialRelativeRotations();


    dxJointUniversal( dxWorld *w );
    virtual void getSureMaxInfo( SureMaxInfo* info );
    virtual void getInfo1( Info1* info );
    virtual void getInfo2( Info2* info );
    virtual dJointType type() const;
    virtual size_t size() const;

    virtual void setRelativeValues();
};


#endif

