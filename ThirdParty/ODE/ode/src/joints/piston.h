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

#ifndef _ODE_JOINT_PISTON_H_
#define _ODE_JOINT_PISTON_H_

#include "joint.h"


////////////////////////////////////////////////////////////////////////////////
/// Component of a Piston joint
/// <PRE>
///                              |- Anchor point
///      Body_1                  |                       Body_2
///      +---------------+       V                       +------------------+
///     /               /|                             /                  /|
///    /               / +       |--      ______      /                  / +
///   /      x        /./........x.......(_____()..../         x        /.......> axis
///  +---------------+ /         |--                +------------------+ /
///  |               |/                             |                  |/
///  +---------------+                              +------------------+
///          |                                                 |
///          |                                                 |
///          |------------------> <----------------------------|
///              anchor1                  anchor2
///
///
/// </PRE>
///
/// When the prismatic joint as been elongated (i.e. dJointGetPistonPosition)
/// return a value >  0
/// <PRE>
///                                   |- Anchor point
///      Body_1                       |                       Body_2
///      +---------------+            V                       +------------------+
///     /               /|                                  /                  /|
///    /               / +            |--      ______      /                  / +
///   /      x        /./........_____x.......(_____()..../         x        /.......> axis
///  +---------------+ /              |--                +------------------+ /
///  |               |/                                  |                  |/
///  +---------------+                                   +------------------+
///          |                                                      |
///          |                                                      |
///          |------------------>      <----------------------------|
///              anchor1         |----|         anchor2
///                                ^
///                                |-- This is what dJointGetPistonPosition will
///                                    return
/// </PRE>
////////////////////////////////////////////////////////////////////////////////
struct dxJointPiston : public dxJoint
{
    dVector3 axis1;          ///< Axis of the prismatic and rotoide w.r.t first body
    dVector3 axis2;          ///< Axis of the prismatic and rotoide w.r.t second body


    dQuaternion qrel;        ///< Initial relative rotation body1 -> body2

    /// Anchor w.r.t first body.
    /// This is the same as the offset for the Slider joint
    /// @note To find the position of the anchor when the body 1 has moved
    ///       you must add the position of the prismatic joint
    ///       i.e anchor = R1 * anchor1 + dJointGetPistonPosition() * (R1 * axis1)
    dVector3 anchor1;
    dVector3 anchor2;        //< anchor w.r.t second body

    /// limit and motor information for the prismatic
    /// part of the joint
    dxJointLimitMotor limotP;

    /// limit and motor information for the rotoide
    /// part of the joint
    dxJointLimitMotor limotR;

    dxJointPiston( dxWorld *w );
    virtual void getSureMaxInfo( SureMaxInfo* info );
    virtual void getInfo1( Info1* info );
    virtual void getInfo2( Info2* info );
    virtual dJointType type() const;
    virtual size_t size() const;

    virtual void setRelativeValues();

    void computeInitialRelativeRotation();
};



#endif

