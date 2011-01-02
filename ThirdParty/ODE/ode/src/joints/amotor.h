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

#ifndef _ODE_JOINT_AMOTOR_H_
#define _ODE_JOINT_AMOTOR_H_

#include "joint.h"


// angular motor

struct dxJointAMotor : public dxJoint
{
    int num;                // number of axes (0..3)
    int mode;               // a dAMotorXXX constant
    int rel[3];             // what the axes are relative to (global,b1,b2)
    dVector3 axis[3];       // three axes
    dxJointLimitMotor limot[3]; // limit+motor info for axes
    dReal angle[3];         // user-supplied angles for axes
    // these vectors are used for calculating euler angles
    dVector3 reference1;    // original axis[2], relative to body 1
    dVector3 reference2;    // original axis[0], relative to body 2


    void computeGlobalAxes( dVector3 ax[3] );
    void computeEulerAngles( dVector3 ax[3] );
    void setEulerReferenceVectors();


    dxJointAMotor( dxWorld *w );
    virtual void getSureMaxInfo( SureMaxInfo* info );
    virtual void getInfo1( Info1* info );
    virtual void getInfo2( Info2* info );
    virtual dJointType type() const;
    virtual size_t size() const;
};


#endif

