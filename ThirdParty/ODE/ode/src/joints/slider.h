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

#ifndef _ODE_JOINT_SLIDER_H_
#define _ODE_JOINT_SLIDER_H_

#include "joint.h"


// slider. if body2 is 0 then qrel is the absolute rotation of body1 and
// offset is the position of body1 center along axis1.

struct dxJointSlider : public dxJoint
{
    dVector3 axis1;     // axis w.r.t first body
    dQuaternion qrel;   // initial relative rotation body1 -> body2
    dVector3 offset;    // point relative to body2 that should be
    // aligned with body1 center along axis1
    dxJointLimitMotor limot; // limit and motor information

    dxJointSlider ( dxWorld *w );
    virtual void getSureMaxInfo( SureMaxInfo* info );
    virtual void getInfo1 ( Info1* info );
    virtual void getInfo2 ( Info2* info );
    virtual dJointType type() const;
    virtual size_t size() const;

    virtual void setRelativeValues();

    void computeInitialRelativeRotation();

    void computeOffset();
};


#endif

