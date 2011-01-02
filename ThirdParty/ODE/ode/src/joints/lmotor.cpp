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
#include "lmotor.h"
#include "joint_internal.h"


//****************************************************************************
// lmotor joint
dxJointLMotor::dxJointLMotor( dxWorld *w ) :
        dxJoint( w )
{
    int i;
    num = 0;
    for ( i = 0;i < 3;i++ )
    {
        dSetZero( axis[i], 4 );
        limot[i].init( world );
    }
}

void
dxJointLMotor::computeGlobalAxes( dVector3 ax[3] )
{
    for ( int i = 0; i < num; i++ )
    {
        if ( rel[i] == 1 )
        {
            dMultiply0_331( ax[i], node[0].body->posr.R, axis[i] );
        }
        else if ( rel[i] == 2 )
        {
            if ( node[1].body )   // jds: don't assert, just ignore
            {
                dMultiply0_331( ax[i], node[1].body->posr.R, axis[i] );
            }
        }
        else
        {
            ax[i][0] = axis[i][0];
            ax[i][1] = axis[i][1];
            ax[i][2] = axis[i][2];
        }
    }
}

void 
dxJointLMotor::getSureMaxInfo( SureMaxInfo* info )
{
    info->max_m = num;
}

void
dxJointLMotor::getInfo1( dxJoint::Info1 *info )
{
    info->m = 0;
    info->nub = 0;
    for ( int i = 0; i < num; i++ )
    {
        if ( limot[i].fmax > 0 )
        {
            info->m++;
        }
    }
}

void
dxJointLMotor::getInfo2( dxJoint::Info2 *info )
{
    int row = 0;
    dVector3 ax[3];
    computeGlobalAxes( ax );

    for ( int i = 0;i < num;i++ )
    {
        row += limot[i].addLimot( this, info, row, ax[i], 0 );
    }
}

void dJointSetLMotorAxis( dJointID j, int anum, int rel, dReal x, dReal y, dReal z )
{
    dxJointLMotor* joint = ( dxJointLMotor* )j;
//for now we are ignoring rel!
    dAASSERT( joint && anum >= 0 && anum <= 2 && rel >= 0 && rel <= 2 );
    checktype( joint, LMotor );

    if ( anum < 0 ) anum = 0;
    if ( anum > 2 ) anum = 2;

    if ( !joint->node[1].body && rel == 2 ) rel = 1; //ref 1

    joint->rel[anum] = rel;

    dVector3 r;
    r[0] = x;
    r[1] = y;
    r[2] = z;
    r[3] = 0;
    if ( rel > 0 )
    {
        if ( rel == 1 )
        {
            dMultiply1_331( joint->axis[anum], joint->node[0].body->posr.R, r );
        }
        else
        {
            //second body has to exists thanks to ref 1 line
            dMultiply1_331( joint->axis[anum], joint->node[1].body->posr.R, r );
        }
    }
    else
    {
        joint->axis[anum][0] = r[0];
        joint->axis[anum][1] = r[1];
        joint->axis[anum][2] = r[2];
    }

    dNormalize3( joint->axis[anum] );
}

void dJointSetLMotorNumAxes( dJointID j, int num )
{
    dxJointLMotor* joint = ( dxJointLMotor* )j;
    dAASSERT( joint && num >= 0 && num <= 3 );
    checktype( joint, LMotor );
    if ( num < 0 ) num = 0;
    if ( num > 3 ) num = 3;
    joint->num = num;
}

void dJointSetLMotorParam( dJointID j, int parameter, dReal value )
{
    dxJointLMotor* joint = ( dxJointLMotor* )j;
    dAASSERT( joint );
    checktype( joint, LMotor );
    int anum = parameter >> 8;
    if ( anum < 0 ) anum = 0;
    if ( anum > 2 ) anum = 2;
    parameter &= 0xff;
    joint->limot[anum].set( parameter, value );
}

int dJointGetLMotorNumAxes( dJointID j )
{
    dxJointLMotor* joint = ( dxJointLMotor* )j;
    dAASSERT( joint );
    checktype( joint, LMotor );
    return joint->num;
}


void dJointGetLMotorAxis( dJointID j, int anum, dVector3 result )
{
    dxJointLMotor* joint = ( dxJointLMotor* )j;
    dAASSERT( joint && anum >= 0 && anum < 3 );
    checktype( joint, LMotor );
    if ( anum < 0 ) anum = 0;
    if ( anum > 2 ) anum = 2;
    result[0] = joint->axis[anum][0];
    result[1] = joint->axis[anum][1];
    result[2] = joint->axis[anum][2];
}

dReal dJointGetLMotorParam( dJointID j, int parameter )
{
    dxJointLMotor* joint = ( dxJointLMotor* )j;
    dAASSERT( joint );
    checktype( joint, LMotor );
    int anum = parameter >> 8;
    if ( anum < 0 ) anum = 0;
    if ( anum > 2 ) anum = 2;
    parameter &= 0xff;
    return joint->limot[anum].get( parameter );
}

dJointType
dxJointLMotor::type() const
{
    return dJointTypeLMotor;
}


size_t
dxJointLMotor::size() const
{
    return sizeof( *this );
}

