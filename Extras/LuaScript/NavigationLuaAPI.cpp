/*
** Lua binding: Navigation
** Generated automatically by tolua++-1.0.92 on 06/29/13 19:40:27.
*/

//
// Copyright (c) 2008-2013 the Urho3D project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include "Precompiled.h"

#include "tolua++.h"

/* Exported function */
TOLUA_API int  tolua_Navigation_open (lua_State* tolua_S);

#define TOLUA_RELEASE
#include "NavigationLuaAPI.h"
#include "Navigable.h"
#include "NavigationMesh.h"
#include "OffMeshConnection.h"
using namespace Urho3D;
#pragma warning(disable:4800)

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_IntVector2 (lua_State* tolua_S)
{
 IntVector2* self = (IntVector2*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_BoundingBox (lua_State* tolua_S)
{
 BoundingBox* self = (BoundingBox*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_Vector3 (lua_State* tolua_S)
{
 Vector3* self = (Vector3*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"Matrix3x4");
 tolua_usertype(tolua_S,"BoundingBox");
 tolua_usertype(tolua_S,"OffMeshConnection");
 tolua_usertype(tolua_S,"Component");
 tolua_usertype(tolua_S,"NavigationGeometryInfo");
 tolua_usertype(tolua_S,"IntVector2");
 tolua_usertype(tolua_S,"NavigationMesh");
 tolua_usertype(tolua_S,"PODVector<Vector3>");
 tolua_usertype(tolua_S,"Vector3");
 tolua_usertype(tolua_S,"Node");
 tolua_usertype(tolua_S,"Navigable");
}

/* method: SetRecursive of class  Navigable */
#ifndef TOLUA_DISABLE_tolua_Navigation_Navigable_SetRecursive00
static int tolua_Navigation_Navigable_SetRecursive00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Navigable",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Navigable* self = (Navigable*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetRecursive'", NULL);
#endif
  {
   self->SetRecursive(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetRecursive'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsRecursive of class  Navigable */
#ifndef TOLUA_DISABLE_tolua_Navigation_Navigable_IsRecursive00
static int tolua_Navigation_Navigable_IsRecursive00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Navigable",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Navigable* self = (const Navigable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsRecursive'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsRecursive();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsRecursive'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: component_ of class  NavigationGeometryInfo */
#ifndef TOLUA_DISABLE_tolua_get_NavigationGeometryInfo_component__ptr
static int tolua_get_NavigationGeometryInfo_component__ptr(lua_State* tolua_S)
{
  NavigationGeometryInfo* self = (NavigationGeometryInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'component_'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->component_,"Component");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: component_ of class  NavigationGeometryInfo */
#ifndef TOLUA_DISABLE_tolua_set_NavigationGeometryInfo_component__ptr
static int tolua_set_NavigationGeometryInfo_component__ptr(lua_State* tolua_S)
{
  NavigationGeometryInfo* self = (NavigationGeometryInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'component_'",NULL);
  if (!tolua_isusertype(tolua_S,2,"Component",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->component_ = ((Component*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: lodLevel_ of class  NavigationGeometryInfo */
#ifndef TOLUA_DISABLE_tolua_get_NavigationGeometryInfo_lodLevel_
static int tolua_get_NavigationGeometryInfo_lodLevel_(lua_State* tolua_S)
{
  NavigationGeometryInfo* self = (NavigationGeometryInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'lodLevel_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->lodLevel_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: lodLevel_ of class  NavigationGeometryInfo */
#ifndef TOLUA_DISABLE_tolua_set_NavigationGeometryInfo_lodLevel_
static int tolua_set_NavigationGeometryInfo_lodLevel_(lua_State* tolua_S)
{
  NavigationGeometryInfo* self = (NavigationGeometryInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'lodLevel_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->lodLevel_ = ((unsigned)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: transform_ of class  NavigationGeometryInfo */
#ifndef TOLUA_DISABLE_tolua_get_NavigationGeometryInfo_transform_
static int tolua_get_NavigationGeometryInfo_transform_(lua_State* tolua_S)
{
  NavigationGeometryInfo* self = (NavigationGeometryInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'transform_'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->transform_,"Matrix3x4");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: transform_ of class  NavigationGeometryInfo */
#ifndef TOLUA_DISABLE_tolua_set_NavigationGeometryInfo_transform_
static int tolua_set_NavigationGeometryInfo_transform_(lua_State* tolua_S)
{
  NavigationGeometryInfo* self = (NavigationGeometryInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'transform_'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"Matrix3x4",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->transform_ = *((Matrix3x4*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: boundingBox_ of class  NavigationGeometryInfo */
#ifndef TOLUA_DISABLE_tolua_get_NavigationGeometryInfo_boundingBox_
static int tolua_get_NavigationGeometryInfo_boundingBox_(lua_State* tolua_S)
{
  NavigationGeometryInfo* self = (NavigationGeometryInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'boundingBox_'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->boundingBox_,"BoundingBox");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: boundingBox_ of class  NavigationGeometryInfo */
#ifndef TOLUA_DISABLE_tolua_set_NavigationGeometryInfo_boundingBox_
static int tolua_set_NavigationGeometryInfo_boundingBox_(lua_State* tolua_S)
{
  NavigationGeometryInfo* self = (NavigationGeometryInfo*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'boundingBox_'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"BoundingBox",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->boundingBox_ = *((BoundingBox*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetTileSize of class  NavigationMesh */
#ifndef TOLUA_DISABLE_tolua_Navigation_NavigationMesh_SetTileSize00
static int tolua_Navigation_NavigationMesh_SetTileSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NavigationMesh",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NavigationMesh* self = (NavigationMesh*)  tolua_tousertype(tolua_S,1,0);
  int size = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetTileSize'", NULL);
#endif
  {
   self->SetTileSize(size);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetTileSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetCellSize of class  NavigationMesh */
#ifndef TOLUA_DISABLE_tolua_Navigation_NavigationMesh_SetCellSize00
static int tolua_Navigation_NavigationMesh_SetCellSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NavigationMesh",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NavigationMesh* self = (NavigationMesh*)  tolua_tousertype(tolua_S,1,0);
  float size = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetCellSize'", NULL);
#endif
  {
   self->SetCellSize(size);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetCellSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetCellHeight of class  NavigationMesh */
#ifndef TOLUA_DISABLE_tolua_Navigation_NavigationMesh_SetCellHeight00
static int tolua_Navigation_NavigationMesh_SetCellHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NavigationMesh",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NavigationMesh* self = (NavigationMesh*)  tolua_tousertype(tolua_S,1,0);
  float height = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetCellHeight'", NULL);
#endif
  {
   self->SetCellHeight(height);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetCellHeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetAgentHeight of class  NavigationMesh */
#ifndef TOLUA_DISABLE_tolua_Navigation_NavigationMesh_SetAgentHeight00
static int tolua_Navigation_NavigationMesh_SetAgentHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NavigationMesh",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NavigationMesh* self = (NavigationMesh*)  tolua_tousertype(tolua_S,1,0);
  float height = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetAgentHeight'", NULL);
#endif
  {
   self->SetAgentHeight(height);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetAgentHeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetAgentRadius of class  NavigationMesh */
#ifndef TOLUA_DISABLE_tolua_Navigation_NavigationMesh_SetAgentRadius00
static int tolua_Navigation_NavigationMesh_SetAgentRadius00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NavigationMesh",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NavigationMesh* self = (NavigationMesh*)  tolua_tousertype(tolua_S,1,0);
  float radius = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetAgentRadius'", NULL);
#endif
  {
   self->SetAgentRadius(radius);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetAgentRadius'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetAgentMaxClimb of class  NavigationMesh */
#ifndef TOLUA_DISABLE_tolua_Navigation_NavigationMesh_SetAgentMaxClimb00
static int tolua_Navigation_NavigationMesh_SetAgentMaxClimb00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NavigationMesh",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NavigationMesh* self = (NavigationMesh*)  tolua_tousertype(tolua_S,1,0);
  float maxClimb = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetAgentMaxClimb'", NULL);
#endif
  {
   self->SetAgentMaxClimb(maxClimb);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetAgentMaxClimb'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetAgentMaxSlope of class  NavigationMesh */
#ifndef TOLUA_DISABLE_tolua_Navigation_NavigationMesh_SetAgentMaxSlope00
static int tolua_Navigation_NavigationMesh_SetAgentMaxSlope00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NavigationMesh",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NavigationMesh* self = (NavigationMesh*)  tolua_tousertype(tolua_S,1,0);
  float maxSlope = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetAgentMaxSlope'", NULL);
#endif
  {
   self->SetAgentMaxSlope(maxSlope);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetAgentMaxSlope'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetRegionMinSize of class  NavigationMesh */
#ifndef TOLUA_DISABLE_tolua_Navigation_NavigationMesh_SetRegionMinSize00
static int tolua_Navigation_NavigationMesh_SetRegionMinSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NavigationMesh",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NavigationMesh* self = (NavigationMesh*)  tolua_tousertype(tolua_S,1,0);
  float size = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetRegionMinSize'", NULL);
#endif
  {
   self->SetRegionMinSize(size);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetRegionMinSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetRegionMergeSize of class  NavigationMesh */
#ifndef TOLUA_DISABLE_tolua_Navigation_NavigationMesh_SetRegionMergeSize00
static int tolua_Navigation_NavigationMesh_SetRegionMergeSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NavigationMesh",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NavigationMesh* self = (NavigationMesh*)  tolua_tousertype(tolua_S,1,0);
  float size = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetRegionMergeSize'", NULL);
#endif
  {
   self->SetRegionMergeSize(size);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetRegionMergeSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetEdgeMaxLength of class  NavigationMesh */
#ifndef TOLUA_DISABLE_tolua_Navigation_NavigationMesh_SetEdgeMaxLength00
static int tolua_Navigation_NavigationMesh_SetEdgeMaxLength00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NavigationMesh",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NavigationMesh* self = (NavigationMesh*)  tolua_tousertype(tolua_S,1,0);
  float length = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetEdgeMaxLength'", NULL);
#endif
  {
   self->SetEdgeMaxLength(length);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetEdgeMaxLength'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetEdgeMaxError of class  NavigationMesh */
#ifndef TOLUA_DISABLE_tolua_Navigation_NavigationMesh_SetEdgeMaxError00
static int tolua_Navigation_NavigationMesh_SetEdgeMaxError00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NavigationMesh",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NavigationMesh* self = (NavigationMesh*)  tolua_tousertype(tolua_S,1,0);
  float error = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetEdgeMaxError'", NULL);
#endif
  {
   self->SetEdgeMaxError(error);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetEdgeMaxError'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetDetailSampleDistance of class  NavigationMesh */
#ifndef TOLUA_DISABLE_tolua_Navigation_NavigationMesh_SetDetailSampleDistance00
static int tolua_Navigation_NavigationMesh_SetDetailSampleDistance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NavigationMesh",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NavigationMesh* self = (NavigationMesh*)  tolua_tousertype(tolua_S,1,0);
  float distance = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetDetailSampleDistance'", NULL);
#endif
  {
   self->SetDetailSampleDistance(distance);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetDetailSampleDistance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetDetailSampleMaxError of class  NavigationMesh */
#ifndef TOLUA_DISABLE_tolua_Navigation_NavigationMesh_SetDetailSampleMaxError00
static int tolua_Navigation_NavigationMesh_SetDetailSampleMaxError00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NavigationMesh",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NavigationMesh* self = (NavigationMesh*)  tolua_tousertype(tolua_S,1,0);
  float error = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetDetailSampleMaxError'", NULL);
#endif
  {
   self->SetDetailSampleMaxError(error);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetDetailSampleMaxError'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetPadding of class  NavigationMesh */
#ifndef TOLUA_DISABLE_tolua_Navigation_NavigationMesh_SetPadding00
static int tolua_Navigation_NavigationMesh_SetPadding00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NavigationMesh",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NavigationMesh* self = (NavigationMesh*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* padding = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetPadding'", NULL);
#endif
  {
   self->SetPadding(*padding);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetPadding'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Build of class  NavigationMesh */
#ifndef TOLUA_DISABLE_tolua_Navigation_NavigationMesh_Build00
static int tolua_Navigation_NavigationMesh_Build00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NavigationMesh",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NavigationMesh* self = (NavigationMesh*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Build'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Build();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Build'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Build of class  NavigationMesh */
#ifndef TOLUA_DISABLE_tolua_Navigation_NavigationMesh_Build01
static int tolua_Navigation_NavigationMesh_Build01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NavigationMesh",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const BoundingBox",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  NavigationMesh* self = (NavigationMesh*)  tolua_tousertype(tolua_S,1,0);
  const BoundingBox* boundingBox = ((const BoundingBox*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Build'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Build(*boundingBox);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_Navigation_NavigationMesh_Build00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: FindPath of class  NavigationMesh */
#ifndef TOLUA_DISABLE_tolua_Navigation_NavigationMesh_FindPath00
static int tolua_Navigation_NavigationMesh_FindPath00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NavigationMesh",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"PODVector<Vector3>",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const Vector3",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NavigationMesh* self = (NavigationMesh*)  tolua_tousertype(tolua_S,1,0);
  PODVector<Vector3>* dest = ((PODVector<Vector3>*)  tolua_tousertype(tolua_S,2,0));
  const Vector3* start = ((const Vector3*)  tolua_tousertype(tolua_S,3,0));
  const Vector3* end = ((const Vector3*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FindPath'", NULL);
#endif
  {
   self->FindPath(*dest,*start,*end);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FindPath'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: FindPath of class  NavigationMesh */
#ifndef TOLUA_DISABLE_tolua_Navigation_NavigationMesh_FindPath01
static int tolua_Navigation_NavigationMesh_FindPath01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NavigationMesh",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"PODVector<Vector3>",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const Vector3",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"const Vector3",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  NavigationMesh* self = (NavigationMesh*)  tolua_tousertype(tolua_S,1,0);
  PODVector<Vector3>* dest = ((PODVector<Vector3>*)  tolua_tousertype(tolua_S,2,0));
  const Vector3* start = ((const Vector3*)  tolua_tousertype(tolua_S,3,0));
  const Vector3* end = ((const Vector3*)  tolua_tousertype(tolua_S,4,0));
  const Vector3* extents = ((const Vector3*)  tolua_tousertype(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FindPath'", NULL);
#endif
  {
   self->FindPath(*dest,*start,*end,*extents);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Navigation_NavigationMesh_FindPath00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRandomPoint of class  NavigationMesh */
#ifndef TOLUA_DISABLE_tolua_Navigation_NavigationMesh_GetRandomPoint00
static int tolua_Navigation_NavigationMesh_GetRandomPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NavigationMesh",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NavigationMesh* self = (NavigationMesh*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRandomPoint'", NULL);
#endif
  {
   Vector3 tolua_ret = (Vector3)  self->GetRandomPoint();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((Vector3)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"Vector3");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Vector3));
     tolua_pushusertype(tolua_S,tolua_obj,"Vector3");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRandomPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRandomPointInCircle of class  NavigationMesh */
#ifndef TOLUA_DISABLE_tolua_Navigation_NavigationMesh_GetRandomPointInCircle00
static int tolua_Navigation_NavigationMesh_GetRandomPointInCircle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NavigationMesh",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NavigationMesh* self = (NavigationMesh*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* center = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
  float radius = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRandomPointInCircle'", NULL);
#endif
  {
   Vector3 tolua_ret = (Vector3)  self->GetRandomPointInCircle(*center,radius);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((Vector3)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"Vector3");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Vector3));
     tolua_pushusertype(tolua_S,tolua_obj,"Vector3");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRandomPointInCircle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRandomPointInCircle of class  NavigationMesh */
#ifndef TOLUA_DISABLE_tolua_Navigation_NavigationMesh_GetRandomPointInCircle01
static int tolua_Navigation_NavigationMesh_GetRandomPointInCircle01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NavigationMesh",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  NavigationMesh* self = (NavigationMesh*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* center = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
  float radius = ((float)  tolua_tonumber(tolua_S,3,0));
  const Vector3* extents = ((const Vector3*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRandomPointInCircle'", NULL);
#endif
  {
   Vector3 tolua_ret = (Vector3)  self->GetRandomPointInCircle(*center,radius,*extents);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((Vector3)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"Vector3");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Vector3));
     tolua_pushusertype(tolua_S,tolua_obj,"Vector3");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_Navigation_NavigationMesh_GetRandomPointInCircle00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetDistanceToWall of class  NavigationMesh */
#ifndef TOLUA_DISABLE_tolua_Navigation_NavigationMesh_GetDistanceToWall00
static int tolua_Navigation_NavigationMesh_GetDistanceToWall00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NavigationMesh",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NavigationMesh* self = (NavigationMesh*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* point = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
  float radius = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetDistanceToWall'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetDistanceToWall(*point,radius);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDistanceToWall'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetDistanceToWall of class  NavigationMesh */
#ifndef TOLUA_DISABLE_tolua_Navigation_NavigationMesh_GetDistanceToWall01
static int tolua_Navigation_NavigationMesh_GetDistanceToWall01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NavigationMesh",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  NavigationMesh* self = (NavigationMesh*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* point = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
  float radius = ((float)  tolua_tonumber(tolua_S,3,0));
  const Vector3* extents = ((const Vector3*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetDistanceToWall'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetDistanceToWall(*point,radius,*extents);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_Navigation_NavigationMesh_GetDistanceToWall00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: Raycast of class  NavigationMesh */
#ifndef TOLUA_DISABLE_tolua_Navigation_NavigationMesh_Raycast00
static int tolua_Navigation_NavigationMesh_Raycast00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NavigationMesh",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NavigationMesh* self = (NavigationMesh*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* start = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
  const Vector3* end = ((const Vector3*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Raycast'", NULL);
#endif
  {
   Vector3 tolua_ret = (Vector3)  self->Raycast(*start,*end);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((Vector3)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"Vector3");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Vector3));
     tolua_pushusertype(tolua_S,tolua_obj,"Vector3");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Raycast'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Raycast of class  NavigationMesh */
#ifndef TOLUA_DISABLE_tolua_Navigation_NavigationMesh_Raycast01
static int tolua_Navigation_NavigationMesh_Raycast01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NavigationMesh",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const Vector3",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  NavigationMesh* self = (NavigationMesh*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* start = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
  const Vector3* end = ((const Vector3*)  tolua_tousertype(tolua_S,3,0));
  const Vector3* extents = ((const Vector3*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Raycast'", NULL);
#endif
  {
   Vector3 tolua_ret = (Vector3)  self->Raycast(*start,*end,*extents);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((Vector3)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"Vector3");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Vector3));
     tolua_pushusertype(tolua_S,tolua_obj,"Vector3");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_Navigation_NavigationMesh_Raycast00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTileSize of class  NavigationMesh */
#ifndef TOLUA_DISABLE_tolua_Navigation_NavigationMesh_GetTileSize00
static int tolua_Navigation_NavigationMesh_GetTileSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const NavigationMesh",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const NavigationMesh* self = (const NavigationMesh*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTileSize'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetTileSize();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTileSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCellSize of class  NavigationMesh */
#ifndef TOLUA_DISABLE_tolua_Navigation_NavigationMesh_GetCellSize00
static int tolua_Navigation_NavigationMesh_GetCellSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const NavigationMesh",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const NavigationMesh* self = (const NavigationMesh*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCellSize'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetCellSize();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCellSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCellHeight of class  NavigationMesh */
#ifndef TOLUA_DISABLE_tolua_Navigation_NavigationMesh_GetCellHeight00
static int tolua_Navigation_NavigationMesh_GetCellHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const NavigationMesh",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const NavigationMesh* self = (const NavigationMesh*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCellHeight'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetCellHeight();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCellHeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAgentHeight of class  NavigationMesh */
#ifndef TOLUA_DISABLE_tolua_Navigation_NavigationMesh_GetAgentHeight00
static int tolua_Navigation_NavigationMesh_GetAgentHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const NavigationMesh",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const NavigationMesh* self = (const NavigationMesh*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAgentHeight'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetAgentHeight();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAgentHeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAgentRadius of class  NavigationMesh */
#ifndef TOLUA_DISABLE_tolua_Navigation_NavigationMesh_GetAgentRadius00
static int tolua_Navigation_NavigationMesh_GetAgentRadius00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const NavigationMesh",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const NavigationMesh* self = (const NavigationMesh*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAgentRadius'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetAgentRadius();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAgentRadius'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAgentMaxClimb of class  NavigationMesh */
#ifndef TOLUA_DISABLE_tolua_Navigation_NavigationMesh_GetAgentMaxClimb00
static int tolua_Navigation_NavigationMesh_GetAgentMaxClimb00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const NavigationMesh",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const NavigationMesh* self = (const NavigationMesh*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAgentMaxClimb'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetAgentMaxClimb();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAgentMaxClimb'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAgentMaxSlope of class  NavigationMesh */
#ifndef TOLUA_DISABLE_tolua_Navigation_NavigationMesh_GetAgentMaxSlope00
static int tolua_Navigation_NavigationMesh_GetAgentMaxSlope00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const NavigationMesh",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const NavigationMesh* self = (const NavigationMesh*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAgentMaxSlope'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetAgentMaxSlope();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAgentMaxSlope'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRegionMinSize of class  NavigationMesh */
#ifndef TOLUA_DISABLE_tolua_Navigation_NavigationMesh_GetRegionMinSize00
static int tolua_Navigation_NavigationMesh_GetRegionMinSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const NavigationMesh",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const NavigationMesh* self = (const NavigationMesh*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRegionMinSize'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetRegionMinSize();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRegionMinSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRegionMergeSize of class  NavigationMesh */
#ifndef TOLUA_DISABLE_tolua_Navigation_NavigationMesh_GetRegionMergeSize00
static int tolua_Navigation_NavigationMesh_GetRegionMergeSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const NavigationMesh",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const NavigationMesh* self = (const NavigationMesh*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRegionMergeSize'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetRegionMergeSize();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRegionMergeSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetEdgeMaxLength of class  NavigationMesh */
#ifndef TOLUA_DISABLE_tolua_Navigation_NavigationMesh_GetEdgeMaxLength00
static int tolua_Navigation_NavigationMesh_GetEdgeMaxLength00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const NavigationMesh",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const NavigationMesh* self = (const NavigationMesh*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetEdgeMaxLength'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetEdgeMaxLength();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetEdgeMaxLength'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetEdgeMaxError of class  NavigationMesh */
#ifndef TOLUA_DISABLE_tolua_Navigation_NavigationMesh_GetEdgeMaxError00
static int tolua_Navigation_NavigationMesh_GetEdgeMaxError00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const NavigationMesh",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const NavigationMesh* self = (const NavigationMesh*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetEdgeMaxError'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetEdgeMaxError();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetEdgeMaxError'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetDetailSampleDistance of class  NavigationMesh */
#ifndef TOLUA_DISABLE_tolua_Navigation_NavigationMesh_GetDetailSampleDistance00
static int tolua_Navigation_NavigationMesh_GetDetailSampleDistance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const NavigationMesh",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const NavigationMesh* self = (const NavigationMesh*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetDetailSampleDistance'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetDetailSampleDistance();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDetailSampleDistance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetDetailSampleMaxError of class  NavigationMesh */
#ifndef TOLUA_DISABLE_tolua_Navigation_NavigationMesh_GetDetailSampleMaxError00
static int tolua_Navigation_NavigationMesh_GetDetailSampleMaxError00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const NavigationMesh",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const NavigationMesh* self = (const NavigationMesh*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetDetailSampleMaxError'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetDetailSampleMaxError();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDetailSampleMaxError'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetPadding of class  NavigationMesh */
#ifndef TOLUA_DISABLE_tolua_Navigation_NavigationMesh_GetPadding00
static int tolua_Navigation_NavigationMesh_GetPadding00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const NavigationMesh",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const NavigationMesh* self = (const NavigationMesh*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPadding'", NULL);
#endif
  {
   const Vector3& tolua_ret = (const Vector3&)  self->GetPadding();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Vector3");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPadding'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsInitialized of class  NavigationMesh */
#ifndef TOLUA_DISABLE_tolua_Navigation_NavigationMesh_IsInitialized00
static int tolua_Navigation_NavigationMesh_IsInitialized00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const NavigationMesh",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const NavigationMesh* self = (const NavigationMesh*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsInitialized'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsInitialized();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsInitialized'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetBoundingBox of class  NavigationMesh */
#ifndef TOLUA_DISABLE_tolua_Navigation_NavigationMesh_GetBoundingBox00
static int tolua_Navigation_NavigationMesh_GetBoundingBox00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const NavigationMesh",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const NavigationMesh* self = (const NavigationMesh*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetBoundingBox'", NULL);
#endif
  {
   const BoundingBox& tolua_ret = (const BoundingBox&)  self->GetBoundingBox();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const BoundingBox");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetBoundingBox'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetWorldBoundingBox of class  NavigationMesh */
#ifndef TOLUA_DISABLE_tolua_Navigation_NavigationMesh_GetWorldBoundingBox00
static int tolua_Navigation_NavigationMesh_GetWorldBoundingBox00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const NavigationMesh",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const NavigationMesh* self = (const NavigationMesh*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetWorldBoundingBox'", NULL);
#endif
  {
   BoundingBox tolua_ret = (BoundingBox)  self->GetWorldBoundingBox();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((BoundingBox)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"BoundingBox");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(BoundingBox));
     tolua_pushusertype(tolua_S,tolua_obj,"BoundingBox");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetWorldBoundingBox'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNumTiles of class  NavigationMesh */
#ifndef TOLUA_DISABLE_tolua_Navigation_NavigationMesh_GetNumTiles00
static int tolua_Navigation_NavigationMesh_GetNumTiles00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const NavigationMesh",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const NavigationMesh* self = (const NavigationMesh*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNumTiles'", NULL);
#endif
  {
   IntVector2 tolua_ret = (IntVector2)  self->GetNumTiles();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((IntVector2)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"IntVector2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(IntVector2));
     tolua_pushusertype(tolua_S,tolua_obj,"IntVector2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNumTiles'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetEndPoint of class  OffMeshConnection */
#ifndef TOLUA_DISABLE_tolua_Navigation_OffMeshConnection_SetEndPoint00
static int tolua_Navigation_OffMeshConnection_SetEndPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"OffMeshConnection",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Node",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  OffMeshConnection* self = (OffMeshConnection*)  tolua_tousertype(tolua_S,1,0);
  Node* node = ((Node*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetEndPoint'", NULL);
#endif
  {
   self->SetEndPoint(node);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetEndPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetRadius of class  OffMeshConnection */
#ifndef TOLUA_DISABLE_tolua_Navigation_OffMeshConnection_SetRadius00
static int tolua_Navigation_OffMeshConnection_SetRadius00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"OffMeshConnection",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  OffMeshConnection* self = (OffMeshConnection*)  tolua_tousertype(tolua_S,1,0);
  float radius = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetRadius'", NULL);
#endif
  {
   self->SetRadius(radius);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetRadius'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetBidirectional of class  OffMeshConnection */
#ifndef TOLUA_DISABLE_tolua_Navigation_OffMeshConnection_SetBidirectional00
static int tolua_Navigation_OffMeshConnection_SetBidirectional00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"OffMeshConnection",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  OffMeshConnection* self = (OffMeshConnection*)  tolua_tousertype(tolua_S,1,0);
  bool enabled = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetBidirectional'", NULL);
#endif
  {
   self->SetBidirectional(enabled);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetBidirectional'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetEndPoint of class  OffMeshConnection */
#ifndef TOLUA_DISABLE_tolua_Navigation_OffMeshConnection_GetEndPoint00
static int tolua_Navigation_OffMeshConnection_GetEndPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const OffMeshConnection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const OffMeshConnection* self = (const OffMeshConnection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetEndPoint'", NULL);
#endif
  {
   Node* tolua_ret = (Node*)  self->GetEndPoint();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Node");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetEndPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRadius of class  OffMeshConnection */
#ifndef TOLUA_DISABLE_tolua_Navigation_OffMeshConnection_GetRadius00
static int tolua_Navigation_OffMeshConnection_GetRadius00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const OffMeshConnection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const OffMeshConnection* self = (const OffMeshConnection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRadius'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetRadius();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRadius'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsBidirectional of class  OffMeshConnection */
#ifndef TOLUA_DISABLE_tolua_Navigation_OffMeshConnection_IsBidirectional00
static int tolua_Navigation_OffMeshConnection_IsBidirectional00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const OffMeshConnection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const OffMeshConnection* self = (const OffMeshConnection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsBidirectional'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsBidirectional();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsBidirectional'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_Navigation_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_cclass(tolua_S,"Navigable","Navigable","Component",NULL);
  tolua_beginmodule(tolua_S,"Navigable");
   tolua_function(tolua_S,"SetRecursive",tolua_Navigation_Navigable_SetRecursive00);
   tolua_function(tolua_S,"IsRecursive",tolua_Navigation_Navigable_IsRecursive00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"NavigationGeometryInfo","NavigationGeometryInfo","",NULL);
  tolua_beginmodule(tolua_S,"NavigationGeometryInfo");
   tolua_variable(tolua_S,"component_",tolua_get_NavigationGeometryInfo_component__ptr,tolua_set_NavigationGeometryInfo_component__ptr);
   tolua_variable(tolua_S,"lodLevel_",tolua_get_NavigationGeometryInfo_lodLevel_,tolua_set_NavigationGeometryInfo_lodLevel_);
   tolua_variable(tolua_S,"transform_",tolua_get_NavigationGeometryInfo_transform_,tolua_set_NavigationGeometryInfo_transform_);
   tolua_variable(tolua_S,"boundingBox_",tolua_get_NavigationGeometryInfo_boundingBox_,tolua_set_NavigationGeometryInfo_boundingBox_);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"NavigationMesh","NavigationMesh","Component",NULL);
  tolua_beginmodule(tolua_S,"NavigationMesh");
   tolua_function(tolua_S,"SetTileSize",tolua_Navigation_NavigationMesh_SetTileSize00);
   tolua_function(tolua_S,"SetCellSize",tolua_Navigation_NavigationMesh_SetCellSize00);
   tolua_function(tolua_S,"SetCellHeight",tolua_Navigation_NavigationMesh_SetCellHeight00);
   tolua_function(tolua_S,"SetAgentHeight",tolua_Navigation_NavigationMesh_SetAgentHeight00);
   tolua_function(tolua_S,"SetAgentRadius",tolua_Navigation_NavigationMesh_SetAgentRadius00);
   tolua_function(tolua_S,"SetAgentMaxClimb",tolua_Navigation_NavigationMesh_SetAgentMaxClimb00);
   tolua_function(tolua_S,"SetAgentMaxSlope",tolua_Navigation_NavigationMesh_SetAgentMaxSlope00);
   tolua_function(tolua_S,"SetRegionMinSize",tolua_Navigation_NavigationMesh_SetRegionMinSize00);
   tolua_function(tolua_S,"SetRegionMergeSize",tolua_Navigation_NavigationMesh_SetRegionMergeSize00);
   tolua_function(tolua_S,"SetEdgeMaxLength",tolua_Navigation_NavigationMesh_SetEdgeMaxLength00);
   tolua_function(tolua_S,"SetEdgeMaxError",tolua_Navigation_NavigationMesh_SetEdgeMaxError00);
   tolua_function(tolua_S,"SetDetailSampleDistance",tolua_Navigation_NavigationMesh_SetDetailSampleDistance00);
   tolua_function(tolua_S,"SetDetailSampleMaxError",tolua_Navigation_NavigationMesh_SetDetailSampleMaxError00);
   tolua_function(tolua_S,"SetPadding",tolua_Navigation_NavigationMesh_SetPadding00);
   tolua_function(tolua_S,"Build",tolua_Navigation_NavigationMesh_Build00);
   tolua_function(tolua_S,"Build",tolua_Navigation_NavigationMesh_Build01);
   tolua_function(tolua_S,"FindPath",tolua_Navigation_NavigationMesh_FindPath00);
   tolua_function(tolua_S,"FindPath",tolua_Navigation_NavigationMesh_FindPath01);
   tolua_function(tolua_S,"GetRandomPoint",tolua_Navigation_NavigationMesh_GetRandomPoint00);
   tolua_function(tolua_S,"GetRandomPointInCircle",tolua_Navigation_NavigationMesh_GetRandomPointInCircle00);
   tolua_function(tolua_S,"GetRandomPointInCircle",tolua_Navigation_NavigationMesh_GetRandomPointInCircle01);
   tolua_function(tolua_S,"GetDistanceToWall",tolua_Navigation_NavigationMesh_GetDistanceToWall00);
   tolua_function(tolua_S,"GetDistanceToWall",tolua_Navigation_NavigationMesh_GetDistanceToWall01);
   tolua_function(tolua_S,"Raycast",tolua_Navigation_NavigationMesh_Raycast00);
   tolua_function(tolua_S,"Raycast",tolua_Navigation_NavigationMesh_Raycast01);
   tolua_function(tolua_S,"GetTileSize",tolua_Navigation_NavigationMesh_GetTileSize00);
   tolua_function(tolua_S,"GetCellSize",tolua_Navigation_NavigationMesh_GetCellSize00);
   tolua_function(tolua_S,"GetCellHeight",tolua_Navigation_NavigationMesh_GetCellHeight00);
   tolua_function(tolua_S,"GetAgentHeight",tolua_Navigation_NavigationMesh_GetAgentHeight00);
   tolua_function(tolua_S,"GetAgentRadius",tolua_Navigation_NavigationMesh_GetAgentRadius00);
   tolua_function(tolua_S,"GetAgentMaxClimb",tolua_Navigation_NavigationMesh_GetAgentMaxClimb00);
   tolua_function(tolua_S,"GetAgentMaxSlope",tolua_Navigation_NavigationMesh_GetAgentMaxSlope00);
   tolua_function(tolua_S,"GetRegionMinSize",tolua_Navigation_NavigationMesh_GetRegionMinSize00);
   tolua_function(tolua_S,"GetRegionMergeSize",tolua_Navigation_NavigationMesh_GetRegionMergeSize00);
   tolua_function(tolua_S,"GetEdgeMaxLength",tolua_Navigation_NavigationMesh_GetEdgeMaxLength00);
   tolua_function(tolua_S,"GetEdgeMaxError",tolua_Navigation_NavigationMesh_GetEdgeMaxError00);
   tolua_function(tolua_S,"GetDetailSampleDistance",tolua_Navigation_NavigationMesh_GetDetailSampleDistance00);
   tolua_function(tolua_S,"GetDetailSampleMaxError",tolua_Navigation_NavigationMesh_GetDetailSampleMaxError00);
   tolua_function(tolua_S,"GetPadding",tolua_Navigation_NavigationMesh_GetPadding00);
   tolua_function(tolua_S,"IsInitialized",tolua_Navigation_NavigationMesh_IsInitialized00);
   tolua_function(tolua_S,"GetBoundingBox",tolua_Navigation_NavigationMesh_GetBoundingBox00);
   tolua_function(tolua_S,"GetWorldBoundingBox",tolua_Navigation_NavigationMesh_GetWorldBoundingBox00);
   tolua_function(tolua_S,"GetNumTiles",tolua_Navigation_NavigationMesh_GetNumTiles00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"OffMeshConnection","OffMeshConnection","Component",NULL);
  tolua_beginmodule(tolua_S,"OffMeshConnection");
   tolua_function(tolua_S,"SetEndPoint",tolua_Navigation_OffMeshConnection_SetEndPoint00);
   tolua_function(tolua_S,"SetRadius",tolua_Navigation_OffMeshConnection_SetRadius00);
   tolua_function(tolua_S,"SetBidirectional",tolua_Navigation_OffMeshConnection_SetBidirectional00);
   tolua_function(tolua_S,"GetEndPoint",tolua_Navigation_OffMeshConnection_GetEndPoint00);
   tolua_function(tolua_S,"GetRadius",tolua_Navigation_OffMeshConnection_GetRadius00);
   tolua_function(tolua_S,"IsBidirectional",tolua_Navigation_OffMeshConnection_IsBidirectional00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_Navigation (lua_State* tolua_S) {
 return tolua_Navigation_open(tolua_S);
};
#endif

