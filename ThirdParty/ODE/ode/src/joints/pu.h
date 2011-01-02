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

#ifndef _ODE_JOINT_PU_H_
#define _ODE_JOINT_PU_H_

#include "universal.h"



/**
 * Component of a Prismatic -- Universal joint.
 * The axisP must be perpendicular to axis1.
 * The second axis of the universal joint is perpendicular to axis1.
 *
 * Since the PU joint is derived from the Universal joint. Some variable
 * are reused.
 *
 * anchor1: Vector from body1 to the anchor point
 *          This vector is calculated when the body are attached or
 *          when the anchor point is set. It is like the offset of the Slider
 *          joint. Since their is a prismatic between the anchor and the body1
 *          the distance might change as the simulation goes on.
 * anchor2: Vector from body2 to the anchor point.
 * <PRE>
 *                                                 Body 2
 *                                                 +-------------+
 *                                                 |      x      |
 *                                                 +------------\+
 *          Prismatic articulation                   ..     ..
 *                                |                ..     ..
 *          Body 1                v             ..      ..
 *          +--------------+    --|        __..      ..  anchor2
 * <--------|      x       | .....|.......(__)     ..
 * axisP    +--------------+    --|         ^     <
 *                 |----------------------->|
 *                     anchor1              |--- Universal articulation
 *                                               axis1 going out of the plane
 *                                               axis2 is perpendicular to axis1
 *                                               (i.e. 2 rotoides)
 * </PRE>
 */
struct dxJointPU : public dxJointUniversal
{

    /// @brief Axis for the prismatic articulation w.r.t first body.
    /// @note This is considered as axis2 from the parameter view
    dVector3 axisP1;

    dxJointLimitMotor limotP; ///< limit and motor information for the prismatic articulation.


    dxJointPU( dxWorld *w );
    virtual void getSureMaxInfo( SureMaxInfo* info );
    virtual void getInfo1( Info1* info );
    virtual void getInfo2( Info2* info );
    virtual dJointType type() const;
    virtual size_t size() const;


    virtual void setRelativeValues();
};


#endif

