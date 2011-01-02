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

#ifndef _ODE_JOINT_PR_H_
#define _ODE_JOINT_PR_H_

#include "joint.h"



/**
 * The axisP must be perpendicular to axis2
 * <PRE>
 *                                        +-------------+
 *                                        |      x      |
 *                                        +------------\+
 * Prismatic articulation                   ..     ..
 *                       |                ..     ..
 *                      \/              ..      ..
 * +--------------+    --|        __..      ..  anchor2
 * |      x       | .....|.......(__)     ..
 * +--------------+    --|         ^     <
 *        |----------------------->|
 *            Offset               |--- Rotoide articulation
 * </PRE>
 */
struct dxJointPR : public dxJoint
{

    /// @brief Position of the rotoide articulation w.r.t second body.
    /// @note Position of body 2 in world frame + anchor2 in world frame give
    /// the position of the rotoide articulation
    dVector3 anchor2;


    /// axis of the rotoide articulation w.r.t first body.
    /// @note This is considered as axis1 from the parameter view.
    dVector3 axisR1;

    /// axis of the rotoide articulation w.r.t second body.
    /// @note This is considered also as axis1 from the parameter view
    dVector3 axisR2;

    /// axis for the prismatic articulation w.r.t first body.
    /// @note This is considered as axis2 in from the parameter view
    dVector3 axisP1;


    dQuaternion qrel;   ///< initial relative rotation body1 -> body2.


    /// @brief vector between the body1 and the rotoide articulation.
    ///
    /// Going from the first to the second in the frame of body1.
    /// That should be aligned with body1 center along axisP.
    /// This is calculated when the axis are set.
    dVector3 offset;
    dxJointLimitMotor limotR; ///< limit and motor information for the rotoide articulation.
    dxJointLimitMotor limotP; ///< limit and motor information for the prismatic articulation.


    void computeInitialRelativeRotation();


    dxJointPR( dxWorld *w );
    virtual void getSureMaxInfo( SureMaxInfo* info );
    virtual void getInfo1( Info1* info );
    virtual void getInfo2( Info2* info );
    virtual dJointType type() const;
    virtual size_t size() const;

    virtual void setRelativeValues();
};



#endif

