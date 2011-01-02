/*************************************************************************
*                                                                       *
* Open Dynamics Engine, Copyright (C) 2001-2003 Russell L. Smith.       *
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

#ifndef _ODE_COLLISION_TRIMESH_COLLIDERS_H_
#define _ODE_COLLISION_TRIMESH_COLLIDERS_H_


int dCollideCylinderTrimesh(dxGeom *o1, dxGeom *o2, int flags, dContactGeom *contact, int skip);
int dCollideTrimeshPlane(dxGeom *o1, dxGeom *o2, int flags, dContactGeom *contact, int skip);

int dCollideSTL(dxGeom *o1, dxGeom *o2, int flags, dContactGeom *contact, int skip);
int dCollideBTL(dxGeom *o1, dxGeom *o2, int flags, dContactGeom *contact, int skip);
int dCollideRTL(dxGeom *o1, dxGeom *o2, int flags, dContactGeom *contact, int skip);
int dCollideTTL(dxGeom *o1, dxGeom *o2, int flags, dContactGeom *contact, int skip);
int dCollideCCTL(dxGeom *o1, dxGeom *o2, int flags, dContactGeom *contact, int skip);

PURE_INLINE int dCollideRayTrimesh( dxGeom *ray, dxGeom *trimesh, int flags,
								   dContactGeom *contact, int skip )
{
	// Swapped case, for code that needs it (heightfield initially)
	// The other ray-geom colliders take geoms in a swapped order to the
	// dCollideRTL function which is annoying when using function pointers.
	return dCollideRTL( trimesh, ray, flags, contact, skip );
}


#endif // _ODE_COLLISION_TRIMESH_COLLIDERS_H_
