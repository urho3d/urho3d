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

/*

the standard ODE geometry primitives.

*/

#ifndef _ODE_COLLISION_STD_H_
#define _ODE_COLLISION_STD_H_

#include <ode/common.h>
#include "collision_kernel.h"


// primitive collision functions - these have the dColliderFn interface, i.e.
// the same interface as dCollide(). the first and second geom arguments must
// have the specified types.

int dCollideSphereSphere (dxGeom *o1, dxGeom *o2, int flags,
			  dContactGeom *contact, int skip);
int dCollideSphereBox (dxGeom *o1, dxGeom *o2, int flags,
		       dContactGeom *contact, int skip);
int dCollideSpherePlane (dxGeom *o1, dxGeom *o2, int flags,
			 dContactGeom *contact, int skip);
int dCollideBoxBox (dxGeom *o1, dxGeom *o2, int flags,
		    dContactGeom *contact, int skip);
int dCollideBoxPlane (dxGeom *o1, dxGeom *o2,
		      int flags, dContactGeom *contact, int skip);
int dCollideCapsuleSphere (dxGeom *o1, dxGeom *o2, int flags,
			     dContactGeom *contact, int skip);
int dCollideCapsuleBox (dxGeom *o1, dxGeom *o2, int flags,
			  dContactGeom *contact, int skip);
int dCollideCapsuleCapsule (dxGeom *o1, dxGeom *o2,
				int flags, dContactGeom *contact, int skip);
int dCollideCapsulePlane (dxGeom *o1, dxGeom *o2, int flags,
			    dContactGeom *contact, int skip);
int dCollideRaySphere (dxGeom *o1, dxGeom *o2, int flags,
		       dContactGeom *contact, int skip);
int dCollideRayBox (dxGeom *o1, dxGeom *o2, int flags,
		    dContactGeom *contact, int skip);
int dCollideRayCapsule (dxGeom *o1, dxGeom *o2,
			  int flags, dContactGeom *contact, int skip);
int dCollideRayPlane (dxGeom *o1, dxGeom *o2, int flags,
		      dContactGeom *contact, int skip);
int dCollideRayCylinder (dxGeom *o1, dxGeom *o2, int flags,
		      dContactGeom *contact, int skip);

// Cylinder - Box/Sphere by (C) CroTeam
// Ported by Nguyen Binh
int dCollideCylinderBox(dxGeom *o1, dxGeom *o2, 
                        int flags, dContactGeom *contact, int skip);
int dCollideCylinderSphere(dxGeom *gCylinder, dxGeom *gSphere, 
                           int flags, dContactGeom *contact, int skip); 
int dCollideCylinderPlane(dxGeom *gCylinder, dxGeom *gPlane, 
                           int flags, dContactGeom *contact, int skip); 

//--> Convex Collision
int dCollideConvexPlane (dxGeom *o1, dxGeom *o2, int flags,
			 dContactGeom *contact, int skip);
int dCollideSphereConvex (dxGeom *o1, dxGeom *o2, int flags,
			  dContactGeom *contact, int skip);
int dCollideConvexBox (dxGeom *o1, dxGeom *o2, int flags,
		       dContactGeom *contact, int skip);
int dCollideConvexCapsule (dxGeom *o1, dxGeom *o2,
			   int flags, dContactGeom *contact, int skip);
int dCollideConvexConvex (dxGeom *o1, dxGeom *o2, int flags, 
			  dContactGeom *contact, int skip);
int dCollideRayConvex (dxGeom *o1, dxGeom *o2, int flags, 
		       dContactGeom *contact, int skip);
//<-- Convex Collision

// dHeightfield
int dCollideHeightfield( dxGeom *o1, dxGeom *o2, 
						 int flags, dContactGeom *contact, int skip );

//****************************************************************************
// the basic geometry objects

struct dxSphere : public dxGeom {
  dReal radius;		// sphere radius
  dxSphere (dSpaceID space, dReal _radius);
  void computeAABB();
};


struct dxBox : public dxGeom {
  dVector3 side;	// side lengths (x,y,z)
  dxBox (dSpaceID space, dReal lx, dReal ly, dReal lz);
  void computeAABB();
};


struct dxCapsule : public dxGeom {
  dReal radius,lz;	// radius, length along z axis
  dxCapsule (dSpaceID space, dReal _radius, dReal _length);
  void computeAABB();
};


struct dxCylinder : public dxGeom {
        dReal radius,lz;        // radius, length along z axis
        dxCylinder (dSpaceID space, dReal _radius, dReal _length);
        void computeAABB();
};


struct dxPlane : public dxGeom {
  dReal p[4];
  dxPlane (dSpaceID space, dReal a, dReal b, dReal c, dReal d);
  void computeAABB();
};


struct dxRay : public dxGeom {
  dReal length;
  dxRay (dSpaceID space, dReal _length);
  void computeAABB();
};

struct dxConvex : public dxGeom 
{  
  dReal *planes; /*!< An array of planes in the form:
		   normal X, normal Y, normal Z,Distance
		 */
  dReal *points; /*!< An array of points X,Y,Z */  
  unsigned int *polygons; /*! An array of indices to the points of each polygon, it should be the number of vertices followed by that amount of indices to "points" in counter clockwise order*/
  unsigned int planecount; /*!< Amount of planes in planes */
  unsigned int pointcount;/*!< Amount of points in points */
  unsigned int edgecount;/*!< Amount of edges in convex */
  dReal saabb[6];/*!< Static AABB */
  dxConvex(dSpaceID space,
	   dReal *planes,
	   unsigned int planecount,
	   dReal *points,
	   unsigned int pointcount,
	   unsigned int *polygons);
  ~dxConvex()
  {
	  if((edgecount!=0)&&(edges!=NULL)) delete[] edges;
  }
  void computeAABB();
  struct edge
  {
	unsigned int first;
	unsigned int second;
  };
  edge* edges;

  /*! \brief A Support mapping function for convex shapes
  \param dir [IN] direction to find the Support Point for
  \return the index of the support vertex.
 */
	inline unsigned int SupportIndex(dVector3 dir)
	{
		dVector3 rdir;
		unsigned int index=0;
		dMultiply1_331 (rdir,final_posr->R,dir);
		dReal max = dCalcVectorDot3(points,rdir);
		dReal tmp;
		for (unsigned int i = 1; i < pointcount; ++i) 
		{
			tmp = dCalcVectorDot3(points+(i*3),rdir);
			if (tmp > max) 
			{
				index=i;
				max = tmp; 
			}
		}
		return index;
	}

 private:
  // For Internal Use Only
/*! \brief Fills the edges dynamic array based on points and polygons.
 */
  void FillEdges();
#if 0
  /*
  What this does is the same as the Support function by doing some preprocessing
  for optimization. Not complete yet.
  */
  // Based on Eberly's Game Physics Book page 307
  struct Arc
  {
	  // indices of polyhedron normals that form the spherical arc
	  int normals[2];
	  // index of edge shared by polyhedron faces
	  int edge;
  };
  struct Polygon
  {
	  // indices of polyhedron normals that form the spherical polygon
	  std::vector<int> normals;
	  // index of extreme vertex corresponding to this polygon
	  int vertex;
  };
  // This is for extrem feature query and not the usual level BSP structure (that comes later)
  struct BSPNode
  {
	// Normal index (interior node), vertex index (leaf node)
	int normal;
	// if Dot (E,D)>=0, D gets propagated to this child
	BSPNode* right;
	// if Dot (E,D)<0, D gets propagated to this child
	BSPNode* left;
  };
  void CreateTree();
  BSPNode* CreateNode(std::vector<Arc> Arcs,std::vector<Polygon> Polygons);
  void GetFacesSharedByVertex(int i, std::vector<int> f);
  void GetFacesSharedByEdge(int i, int* f);
  void GetFaceNormal(int i, dVector3 normal);
  BSPNode* tree;
#endif
};


#endif
