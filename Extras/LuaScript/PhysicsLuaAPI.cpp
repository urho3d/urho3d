/*
** Lua binding: Physics
** Generated automatically by tolua++-1.0.92 on 07/02/13 20:27:50.
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
TOLUA_API int  tolua_Physics_open (lua_State* tolua_S);

#define TOLUA_RELEASE
#include "PhysicsLuaAPI.h"
#include "CollisionShape.h"
#include "Constraint.h"
#include "PhysicsWorld.h"
#include "RigidBody.h"
using namespace Urho3D;
#pragma warning(disable:4800)

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_Quaternion (lua_State* tolua_S)
{
 Quaternion* self = (Quaternion*) tolua_tousertype(tolua_S,1,0);
  Mtolua_delete(self);
  return 0;
}

static int tolua_collect_PhysicsRaycastResult (lua_State* tolua_S)
{
 PhysicsRaycastResult* self = (PhysicsRaycastResult*) tolua_tousertype(tolua_S,1,0);
  Mtolua_delete(self);
  return 0;
}

static int tolua_collect_ResourceRef (lua_State* tolua_S)
{
 ResourceRef* self = (ResourceRef*) tolua_tousertype(tolua_S,1,0);
  Mtolua_delete(self);
  return 0;
}

static int tolua_collect_Vector3 (lua_State* tolua_S)
{
 Vector3* self = (Vector3*) tolua_tousertype(tolua_S,1,0);
  Mtolua_delete(self);
  return 0;
}

static int tolua_collect_BoundingBox (lua_State* tolua_S)
{
 BoundingBox* self = (BoundingBox*) tolua_tousertype(tolua_S,1,0);
  Mtolua_delete(self);
  return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"Quaternion");
 tolua_usertype(tolua_S,"RigidBody");
 tolua_usertype(tolua_S,"ResourceRef");
 tolua_usertype(tolua_S,"Ray");
 tolua_usertype(tolua_S,"PhysicsWorld");
 tolua_usertype(tolua_S,"BoundingBox");
 tolua_usertype(tolua_S,"Vector2");
 tolua_usertype(tolua_S,"Component");
 tolua_usertype(tolua_S,"CollisionShape");
 tolua_usertype(tolua_S,"PhysicsRaycastResult");
 tolua_usertype(tolua_S,"Model");
 tolua_usertype(tolua_S,"DebugRenderer");
 tolua_usertype(tolua_S,"DelayedWorldTransform");
 tolua_usertype(tolua_S,"Constraint");
 tolua_usertype(tolua_S,"Vector3");
}

/* method: SetBox of class  CollisionShape */
#ifndef TOLUA_DISABLE_tolua_Physics_CollisionShape_SetBox00
static int tolua_Physics_CollisionShape_SetBox00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CollisionShape",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CollisionShape* self = (CollisionShape*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* size = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetBox'", NULL);
#endif
  {
   self->SetBox(*size);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetBox'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetBox of class  CollisionShape */
#ifndef TOLUA_DISABLE_tolua_Physics_CollisionShape_SetBox01
static int tolua_Physics_CollisionShape_SetBox01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CollisionShape",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CollisionShape* self = (CollisionShape*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* size = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
  const Vector3* position = ((const Vector3*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetBox'", NULL);
#endif
  {
   self->SetBox(*size,*position);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Physics_CollisionShape_SetBox00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetBox of class  CollisionShape */
#ifndef TOLUA_DISABLE_tolua_Physics_CollisionShape_SetBox02
static int tolua_Physics_CollisionShape_SetBox02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CollisionShape",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const Vector3",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"const Quaternion",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CollisionShape* self = (CollisionShape*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* size = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
  const Vector3* position = ((const Vector3*)  tolua_tousertype(tolua_S,3,0));
  const Quaternion* rotation = ((const Quaternion*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetBox'", NULL);
#endif
  {
   self->SetBox(*size,*position,*rotation);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Physics_CollisionShape_SetBox01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetSphere of class  CollisionShape */
#ifndef TOLUA_DISABLE_tolua_Physics_CollisionShape_SetSphere00
static int tolua_Physics_CollisionShape_SetSphere00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CollisionShape",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CollisionShape* self = (CollisionShape*)  tolua_tousertype(tolua_S,1,0);
  float diameter = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetSphere'", NULL);
#endif
  {
   self->SetSphere(diameter);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetSphere'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetSphere of class  CollisionShape */
#ifndef TOLUA_DISABLE_tolua_Physics_CollisionShape_SetSphere01
static int tolua_Physics_CollisionShape_SetSphere01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CollisionShape",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CollisionShape* self = (CollisionShape*)  tolua_tousertype(tolua_S,1,0);
  float diameter = ((float)  tolua_tonumber(tolua_S,2,0));
  const Vector3* position = ((const Vector3*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetSphere'", NULL);
#endif
  {
   self->SetSphere(diameter,*position);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Physics_CollisionShape_SetSphere00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetSphere of class  CollisionShape */
#ifndef TOLUA_DISABLE_tolua_Physics_CollisionShape_SetSphere02
static int tolua_Physics_CollisionShape_SetSphere02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CollisionShape",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const Vector3",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"const Quaternion",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CollisionShape* self = (CollisionShape*)  tolua_tousertype(tolua_S,1,0);
  float diameter = ((float)  tolua_tonumber(tolua_S,2,0));
  const Vector3* position = ((const Vector3*)  tolua_tousertype(tolua_S,3,0));
  const Quaternion* rotation = ((const Quaternion*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetSphere'", NULL);
#endif
  {
   self->SetSphere(diameter,*position,*rotation);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Physics_CollisionShape_SetSphere01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetStaticPlane of class  CollisionShape */
#ifndef TOLUA_DISABLE_tolua_Physics_CollisionShape_SetStaticPlane00
static int tolua_Physics_CollisionShape_SetStaticPlane00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CollisionShape",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CollisionShape* self = (CollisionShape*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetStaticPlane'", NULL);
#endif
  {
   self->SetStaticPlane();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetStaticPlane'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetStaticPlane of class  CollisionShape */
#ifndef TOLUA_DISABLE_tolua_Physics_CollisionShape_SetStaticPlane01
static int tolua_Physics_CollisionShape_SetStaticPlane01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CollisionShape",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CollisionShape* self = (CollisionShape*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* position = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetStaticPlane'", NULL);
#endif
  {
   self->SetStaticPlane(*position);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Physics_CollisionShape_SetStaticPlane00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetStaticPlane of class  CollisionShape */
#ifndef TOLUA_DISABLE_tolua_Physics_CollisionShape_SetStaticPlane02
static int tolua_Physics_CollisionShape_SetStaticPlane02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CollisionShape",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const Quaternion",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CollisionShape* self = (CollisionShape*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* position = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
  const Quaternion* rotation = ((const Quaternion*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetStaticPlane'", NULL);
#endif
  {
   self->SetStaticPlane(*position,*rotation);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Physics_CollisionShape_SetStaticPlane01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetCylinder of class  CollisionShape */
#ifndef TOLUA_DISABLE_tolua_Physics_CollisionShape_SetCylinder00
static int tolua_Physics_CollisionShape_SetCylinder00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CollisionShape",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CollisionShape* self = (CollisionShape*)  tolua_tousertype(tolua_S,1,0);
  float diameter = ((float)  tolua_tonumber(tolua_S,2,0));
  float height = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetCylinder'", NULL);
#endif
  {
   self->SetCylinder(diameter,height);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetCylinder'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetCylinder of class  CollisionShape */
#ifndef TOLUA_DISABLE_tolua_Physics_CollisionShape_SetCylinder01
static int tolua_Physics_CollisionShape_SetCylinder01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CollisionShape",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CollisionShape* self = (CollisionShape*)  tolua_tousertype(tolua_S,1,0);
  float diameter = ((float)  tolua_tonumber(tolua_S,2,0));
  float height = ((float)  tolua_tonumber(tolua_S,3,0));
  const Vector3* position = ((const Vector3*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetCylinder'", NULL);
#endif
  {
   self->SetCylinder(diameter,height,*position);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Physics_CollisionShape_SetCylinder00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetCylinder of class  CollisionShape */
#ifndef TOLUA_DISABLE_tolua_Physics_CollisionShape_SetCylinder02
static int tolua_Physics_CollisionShape_SetCylinder02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CollisionShape",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"const Vector3",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"const Quaternion",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CollisionShape* self = (CollisionShape*)  tolua_tousertype(tolua_S,1,0);
  float diameter = ((float)  tolua_tonumber(tolua_S,2,0));
  float height = ((float)  tolua_tonumber(tolua_S,3,0));
  const Vector3* position = ((const Vector3*)  tolua_tousertype(tolua_S,4,0));
  const Quaternion* rotation = ((const Quaternion*)  tolua_tousertype(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetCylinder'", NULL);
#endif
  {
   self->SetCylinder(diameter,height,*position,*rotation);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Physics_CollisionShape_SetCylinder01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetCapsule of class  CollisionShape */
#ifndef TOLUA_DISABLE_tolua_Physics_CollisionShape_SetCapsule00
static int tolua_Physics_CollisionShape_SetCapsule00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CollisionShape",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CollisionShape* self = (CollisionShape*)  tolua_tousertype(tolua_S,1,0);
  float diameter = ((float)  tolua_tonumber(tolua_S,2,0));
  float height = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetCapsule'", NULL);
#endif
  {
   self->SetCapsule(diameter,height);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetCapsule'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetCapsule of class  CollisionShape */
#ifndef TOLUA_DISABLE_tolua_Physics_CollisionShape_SetCapsule01
static int tolua_Physics_CollisionShape_SetCapsule01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CollisionShape",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CollisionShape* self = (CollisionShape*)  tolua_tousertype(tolua_S,1,0);
  float diameter = ((float)  tolua_tonumber(tolua_S,2,0));
  float height = ((float)  tolua_tonumber(tolua_S,3,0));
  const Vector3* position = ((const Vector3*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetCapsule'", NULL);
#endif
  {
   self->SetCapsule(diameter,height,*position);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Physics_CollisionShape_SetCapsule00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetCapsule of class  CollisionShape */
#ifndef TOLUA_DISABLE_tolua_Physics_CollisionShape_SetCapsule02
static int tolua_Physics_CollisionShape_SetCapsule02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CollisionShape",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"const Vector3",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"const Quaternion",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CollisionShape* self = (CollisionShape*)  tolua_tousertype(tolua_S,1,0);
  float diameter = ((float)  tolua_tonumber(tolua_S,2,0));
  float height = ((float)  tolua_tonumber(tolua_S,3,0));
  const Vector3* position = ((const Vector3*)  tolua_tousertype(tolua_S,4,0));
  const Quaternion* rotation = ((const Quaternion*)  tolua_tousertype(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetCapsule'", NULL);
#endif
  {
   self->SetCapsule(diameter,height,*position,*rotation);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Physics_CollisionShape_SetCapsule01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetCone of class  CollisionShape */
#ifndef TOLUA_DISABLE_tolua_Physics_CollisionShape_SetCone00
static int tolua_Physics_CollisionShape_SetCone00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CollisionShape",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CollisionShape* self = (CollisionShape*)  tolua_tousertype(tolua_S,1,0);
  float diameter = ((float)  tolua_tonumber(tolua_S,2,0));
  float height = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetCone'", NULL);
#endif
  {
   self->SetCone(diameter,height);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetCone'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetCone of class  CollisionShape */
#ifndef TOLUA_DISABLE_tolua_Physics_CollisionShape_SetCone01
static int tolua_Physics_CollisionShape_SetCone01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CollisionShape",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CollisionShape* self = (CollisionShape*)  tolua_tousertype(tolua_S,1,0);
  float diameter = ((float)  tolua_tonumber(tolua_S,2,0));
  float height = ((float)  tolua_tonumber(tolua_S,3,0));
  const Vector3* position = ((const Vector3*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetCone'", NULL);
#endif
  {
   self->SetCone(diameter,height,*position);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Physics_CollisionShape_SetCone00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetCone of class  CollisionShape */
#ifndef TOLUA_DISABLE_tolua_Physics_CollisionShape_SetCone02
static int tolua_Physics_CollisionShape_SetCone02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CollisionShape",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"const Vector3",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"const Quaternion",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CollisionShape* self = (CollisionShape*)  tolua_tousertype(tolua_S,1,0);
  float diameter = ((float)  tolua_tonumber(tolua_S,2,0));
  float height = ((float)  tolua_tonumber(tolua_S,3,0));
  const Vector3* position = ((const Vector3*)  tolua_tousertype(tolua_S,4,0));
  const Quaternion* rotation = ((const Quaternion*)  tolua_tousertype(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetCone'", NULL);
#endif
  {
   self->SetCone(diameter,height,*position,*rotation);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Physics_CollisionShape_SetCone01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetTriangleMesh of class  CollisionShape */
#ifndef TOLUA_DISABLE_tolua_Physics_CollisionShape_SetTriangleMesh00
static int tolua_Physics_CollisionShape_SetTriangleMesh00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CollisionShape",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Model",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CollisionShape* self = (CollisionShape*)  tolua_tousertype(tolua_S,1,0);
  Model* model = ((Model*)  tolua_tousertype(tolua_S,2,0));
  unsigned lodLevel = ((unsigned)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetTriangleMesh'", NULL);
#endif
  {
   self->SetTriangleMesh(model,lodLevel);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetTriangleMesh'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetTriangleMesh of class  CollisionShape */
#ifndef TOLUA_DISABLE_tolua_Physics_CollisionShape_SetTriangleMesh01
static int tolua_Physics_CollisionShape_SetTriangleMesh01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CollisionShape",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Model",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CollisionShape* self = (CollisionShape*)  tolua_tousertype(tolua_S,1,0);
  Model* model = ((Model*)  tolua_tousertype(tolua_S,2,0));
  unsigned lodLevel = ((unsigned)  tolua_tonumber(tolua_S,3,0));
  const Vector3* scale = ((const Vector3*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetTriangleMesh'", NULL);
#endif
  {
   self->SetTriangleMesh(model,lodLevel,*scale);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Physics_CollisionShape_SetTriangleMesh00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetTriangleMesh of class  CollisionShape */
#ifndef TOLUA_DISABLE_tolua_Physics_CollisionShape_SetTriangleMesh02
static int tolua_Physics_CollisionShape_SetTriangleMesh02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CollisionShape",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Model",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"const Vector3",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CollisionShape* self = (CollisionShape*)  tolua_tousertype(tolua_S,1,0);
  Model* model = ((Model*)  tolua_tousertype(tolua_S,2,0));
  unsigned lodLevel = ((unsigned)  tolua_tonumber(tolua_S,3,0));
  const Vector3* scale = ((const Vector3*)  tolua_tousertype(tolua_S,4,0));
  const Vector3* position = ((const Vector3*)  tolua_tousertype(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetTriangleMesh'", NULL);
#endif
  {
   self->SetTriangleMesh(model,lodLevel,*scale,*position);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Physics_CollisionShape_SetTriangleMesh01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetTriangleMesh of class  CollisionShape */
#ifndef TOLUA_DISABLE_tolua_Physics_CollisionShape_SetTriangleMesh03
static int tolua_Physics_CollisionShape_SetTriangleMesh03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CollisionShape",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Model",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"const Vector3",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"const Vector3",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,6,&tolua_err) || !tolua_isusertype(tolua_S,6,"const Quaternion",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CollisionShape* self = (CollisionShape*)  tolua_tousertype(tolua_S,1,0);
  Model* model = ((Model*)  tolua_tousertype(tolua_S,2,0));
  unsigned lodLevel = ((unsigned)  tolua_tonumber(tolua_S,3,0));
  const Vector3* scale = ((const Vector3*)  tolua_tousertype(tolua_S,4,0));
  const Vector3* position = ((const Vector3*)  tolua_tousertype(tolua_S,5,0));
  const Quaternion* rotation = ((const Quaternion*)  tolua_tousertype(tolua_S,6,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetTriangleMesh'", NULL);
#endif
  {
   self->SetTriangleMesh(model,lodLevel,*scale,*position,*rotation);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Physics_CollisionShape_SetTriangleMesh02(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetConvexHull of class  CollisionShape */
#ifndef TOLUA_DISABLE_tolua_Physics_CollisionShape_SetConvexHull00
static int tolua_Physics_CollisionShape_SetConvexHull00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CollisionShape",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Model",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CollisionShape* self = (CollisionShape*)  tolua_tousertype(tolua_S,1,0);
  Model* model = ((Model*)  tolua_tousertype(tolua_S,2,0));
  unsigned lodLevel = ((unsigned)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetConvexHull'", NULL);
#endif
  {
   self->SetConvexHull(model,lodLevel);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetConvexHull'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetConvexHull of class  CollisionShape */
#ifndef TOLUA_DISABLE_tolua_Physics_CollisionShape_SetConvexHull01
static int tolua_Physics_CollisionShape_SetConvexHull01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CollisionShape",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Model",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CollisionShape* self = (CollisionShape*)  tolua_tousertype(tolua_S,1,0);
  Model* model = ((Model*)  tolua_tousertype(tolua_S,2,0));
  unsigned lodLevel = ((unsigned)  tolua_tonumber(tolua_S,3,0));
  const Vector3* scale = ((const Vector3*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetConvexHull'", NULL);
#endif
  {
   self->SetConvexHull(model,lodLevel,*scale);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Physics_CollisionShape_SetConvexHull00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetConvexHull of class  CollisionShape */
#ifndef TOLUA_DISABLE_tolua_Physics_CollisionShape_SetConvexHull02
static int tolua_Physics_CollisionShape_SetConvexHull02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CollisionShape",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Model",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"const Vector3",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CollisionShape* self = (CollisionShape*)  tolua_tousertype(tolua_S,1,0);
  Model* model = ((Model*)  tolua_tousertype(tolua_S,2,0));
  unsigned lodLevel = ((unsigned)  tolua_tonumber(tolua_S,3,0));
  const Vector3* scale = ((const Vector3*)  tolua_tousertype(tolua_S,4,0));
  const Vector3* position = ((const Vector3*)  tolua_tousertype(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetConvexHull'", NULL);
#endif
  {
   self->SetConvexHull(model,lodLevel,*scale,*position);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Physics_CollisionShape_SetConvexHull01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetConvexHull of class  CollisionShape */
#ifndef TOLUA_DISABLE_tolua_Physics_CollisionShape_SetConvexHull03
static int tolua_Physics_CollisionShape_SetConvexHull03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CollisionShape",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Model",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"const Vector3",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"const Vector3",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,6,&tolua_err) || !tolua_isusertype(tolua_S,6,"const Quaternion",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CollisionShape* self = (CollisionShape*)  tolua_tousertype(tolua_S,1,0);
  Model* model = ((Model*)  tolua_tousertype(tolua_S,2,0));
  unsigned lodLevel = ((unsigned)  tolua_tonumber(tolua_S,3,0));
  const Vector3* scale = ((const Vector3*)  tolua_tousertype(tolua_S,4,0));
  const Vector3* position = ((const Vector3*)  tolua_tousertype(tolua_S,5,0));
  const Quaternion* rotation = ((const Quaternion*)  tolua_tousertype(tolua_S,6,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetConvexHull'", NULL);
#endif
  {
   self->SetConvexHull(model,lodLevel,*scale,*position,*rotation);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Physics_CollisionShape_SetConvexHull02(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetTerrain of class  CollisionShape */
#ifndef TOLUA_DISABLE_tolua_Physics_CollisionShape_SetTerrain00
static int tolua_Physics_CollisionShape_SetTerrain00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CollisionShape",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CollisionShape* self = (CollisionShape*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetTerrain'", NULL);
#endif
  {
   self->SetTerrain();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetTerrain'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetShapeType of class  CollisionShape */
#ifndef TOLUA_DISABLE_tolua_Physics_CollisionShape_SetShapeType00
static int tolua_Physics_CollisionShape_SetShapeType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CollisionShape",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CollisionShape* self = (CollisionShape*)  tolua_tousertype(tolua_S,1,0);
  ShapeType type = ((ShapeType) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetShapeType'", NULL);
#endif
  {
   self->SetShapeType(type);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetShapeType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetSize of class  CollisionShape */
#ifndef TOLUA_DISABLE_tolua_Physics_CollisionShape_SetSize00
static int tolua_Physics_CollisionShape_SetSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CollisionShape",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CollisionShape* self = (CollisionShape*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* size = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetSize'", NULL);
#endif
  {
   self->SetSize(*size);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetPosition of class  CollisionShape */
#ifndef TOLUA_DISABLE_tolua_Physics_CollisionShape_SetPosition00
static int tolua_Physics_CollisionShape_SetPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CollisionShape",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CollisionShape* self = (CollisionShape*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* position = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetPosition'", NULL);
#endif
  {
   self->SetPosition(*position);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetRotation of class  CollisionShape */
#ifndef TOLUA_DISABLE_tolua_Physics_CollisionShape_SetRotation00
static int tolua_Physics_CollisionShape_SetRotation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CollisionShape",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Quaternion",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CollisionShape* self = (CollisionShape*)  tolua_tousertype(tolua_S,1,0);
  const Quaternion* rotation = ((const Quaternion*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetRotation'", NULL);
#endif
  {
   self->SetRotation(*rotation);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetRotation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetTransform of class  CollisionShape */
#ifndef TOLUA_DISABLE_tolua_Physics_CollisionShape_SetTransform00
static int tolua_Physics_CollisionShape_SetTransform00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CollisionShape",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const Quaternion",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CollisionShape* self = (CollisionShape*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* position = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
  const Quaternion* rotation = ((const Quaternion*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetTransform'", NULL);
#endif
  {
   self->SetTransform(*position,*rotation);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetTransform'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMargin of class  CollisionShape */
#ifndef TOLUA_DISABLE_tolua_Physics_CollisionShape_SetMargin00
static int tolua_Physics_CollisionShape_SetMargin00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CollisionShape",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CollisionShape* self = (CollisionShape*)  tolua_tousertype(tolua_S,1,0);
  float margin = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMargin'", NULL);
#endif
  {
   self->SetMargin(margin);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMargin'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetModel of class  CollisionShape */
#ifndef TOLUA_DISABLE_tolua_Physics_CollisionShape_SetModel00
static int tolua_Physics_CollisionShape_SetModel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CollisionShape",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Model",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CollisionShape* self = (CollisionShape*)  tolua_tousertype(tolua_S,1,0);
  Model* model = ((Model*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetModel'", NULL);
#endif
  {
   self->SetModel(model);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetModel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetLodLevel of class  CollisionShape */
#ifndef TOLUA_DISABLE_tolua_Physics_CollisionShape_SetLodLevel00
static int tolua_Physics_CollisionShape_SetLodLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CollisionShape",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CollisionShape* self = (CollisionShape*)  tolua_tousertype(tolua_S,1,0);
  unsigned lodLevel = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLodLevel'", NULL);
#endif
  {
   self->SetLodLevel(lodLevel);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLodLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetPhysicsWorld of class  CollisionShape */
#ifndef TOLUA_DISABLE_tolua_Physics_CollisionShape_GetPhysicsWorld00
static int tolua_Physics_CollisionShape_GetPhysicsWorld00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CollisionShape",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CollisionShape* self = (const CollisionShape*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPhysicsWorld'", NULL);
#endif
  {
   PhysicsWorld* tolua_ret = (PhysicsWorld*)  self->GetPhysicsWorld();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"PhysicsWorld");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPhysicsWorld'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetShapeType of class  CollisionShape */
#ifndef TOLUA_DISABLE_tolua_Physics_CollisionShape_GetShapeType00
static int tolua_Physics_CollisionShape_GetShapeType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CollisionShape",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CollisionShape* self = (const CollisionShape*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetShapeType'", NULL);
#endif
  {
   ShapeType tolua_ret = (ShapeType)  self->GetShapeType();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetShapeType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSize of class  CollisionShape */
#ifndef TOLUA_DISABLE_tolua_Physics_CollisionShape_GetSize00
static int tolua_Physics_CollisionShape_GetSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CollisionShape",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CollisionShape* self = (const CollisionShape*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSize'", NULL);
#endif
  {
   const Vector3& tolua_ret = (const Vector3&)  self->GetSize();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Vector3");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetPosition of class  CollisionShape */
#ifndef TOLUA_DISABLE_tolua_Physics_CollisionShape_GetPosition00
static int tolua_Physics_CollisionShape_GetPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CollisionShape",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CollisionShape* self = (const CollisionShape*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPosition'", NULL);
#endif
  {
   const Vector3& tolua_ret = (const Vector3&)  self->GetPosition();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Vector3");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRotation of class  CollisionShape */
#ifndef TOLUA_DISABLE_tolua_Physics_CollisionShape_GetRotation00
static int tolua_Physics_CollisionShape_GetRotation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CollisionShape",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CollisionShape* self = (const CollisionShape*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRotation'", NULL);
#endif
  {
   const Quaternion& tolua_ret = (const Quaternion&)  self->GetRotation();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Quaternion");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRotation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMargin of class  CollisionShape */
#ifndef TOLUA_DISABLE_tolua_Physics_CollisionShape_GetMargin00
static int tolua_Physics_CollisionShape_GetMargin00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CollisionShape",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CollisionShape* self = (const CollisionShape*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMargin'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetMargin();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMargin'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetModel of class  CollisionShape */
#ifndef TOLUA_DISABLE_tolua_Physics_CollisionShape_GetModel00
static int tolua_Physics_CollisionShape_GetModel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CollisionShape",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CollisionShape* self = (const CollisionShape*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetModel'", NULL);
#endif
  {
   Model* tolua_ret = (Model*)  self->GetModel();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Model");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetModel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLodLevel of class  CollisionShape */
#ifndef TOLUA_DISABLE_tolua_Physics_CollisionShape_GetLodLevel00
static int tolua_Physics_CollisionShape_GetLodLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CollisionShape",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CollisionShape* self = (const CollisionShape*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLodLevel'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetLodLevel();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLodLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetWorldBoundingBox of class  CollisionShape */
#ifndef TOLUA_DISABLE_tolua_Physics_CollisionShape_GetWorldBoundingBox00
static int tolua_Physics_CollisionShape_GetWorldBoundingBox00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CollisionShape",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CollisionShape* self = (const CollisionShape*)  tolua_tousertype(tolua_S,1,0);
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

/* method: NotifyRigidBody of class  CollisionShape */
#ifndef TOLUA_DISABLE_tolua_Physics_CollisionShape_NotifyRigidBody00
static int tolua_Physics_CollisionShape_NotifyRigidBody00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CollisionShape",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CollisionShape* self = (CollisionShape*)  tolua_tousertype(tolua_S,1,0);
  bool updateMass = ((bool)  tolua_toboolean(tolua_S,2,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'NotifyRigidBody'", NULL);
#endif
  {
   self->NotifyRigidBody(updateMass);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NotifyRigidBody'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetModelAttr of class  CollisionShape */
#ifndef TOLUA_DISABLE_tolua_Physics_CollisionShape_SetModelAttr00
static int tolua_Physics_CollisionShape_SetModelAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CollisionShape",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"ResourceRef",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CollisionShape* self = (CollisionShape*)  tolua_tousertype(tolua_S,1,0);
  ResourceRef value = *((ResourceRef*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetModelAttr'", NULL);
#endif
  {
   self->SetModelAttr(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetModelAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetModelAttr of class  CollisionShape */
#ifndef TOLUA_DISABLE_tolua_Physics_CollisionShape_GetModelAttr00
static int tolua_Physics_CollisionShape_GetModelAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CollisionShape",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CollisionShape* self = (const CollisionShape*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetModelAttr'", NULL);
#endif
  {
   ResourceRef tolua_ret = (ResourceRef)  self->GetModelAttr();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((ResourceRef)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"ResourceRef");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(ResourceRef));
     tolua_pushusertype(tolua_S,tolua_obj,"ResourceRef");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetModelAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ReleaseShape of class  CollisionShape */
#ifndef TOLUA_DISABLE_tolua_Physics_CollisionShape_ReleaseShape00
static int tolua_Physics_CollisionShape_ReleaseShape00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CollisionShape",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CollisionShape* self = (CollisionShape*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ReleaseShape'", NULL);
#endif
  {
   self->ReleaseShape();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ReleaseShape'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetConstraintType of class  Constraint */
#ifndef TOLUA_DISABLE_tolua_Physics_Constraint_SetConstraintType00
static int tolua_Physics_Constraint_SetConstraintType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Constraint",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Constraint* self = (Constraint*)  tolua_tousertype(tolua_S,1,0);
  ConstraintType type = ((ConstraintType) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetConstraintType'", NULL);
#endif
  {
   self->SetConstraintType(type);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetConstraintType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetOtherBody of class  Constraint */
#ifndef TOLUA_DISABLE_tolua_Physics_Constraint_SetOtherBody00
static int tolua_Physics_Constraint_SetOtherBody00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Constraint",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"RigidBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Constraint* self = (Constraint*)  tolua_tousertype(tolua_S,1,0);
  RigidBody* body = ((RigidBody*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetOtherBody'", NULL);
#endif
  {
   self->SetOtherBody(body);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetOtherBody'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetPosition of class  Constraint */
#ifndef TOLUA_DISABLE_tolua_Physics_Constraint_SetPosition00
static int tolua_Physics_Constraint_SetPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Constraint",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Constraint* self = (Constraint*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* position = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetPosition'", NULL);
#endif
  {
   self->SetPosition(*position);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetRotation of class  Constraint */
#ifndef TOLUA_DISABLE_tolua_Physics_Constraint_SetRotation00
static int tolua_Physics_Constraint_SetRotation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Constraint",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Quaternion",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Constraint* self = (Constraint*)  tolua_tousertype(tolua_S,1,0);
  const Quaternion* rotation = ((const Quaternion*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetRotation'", NULL);
#endif
  {
   self->SetRotation(*rotation);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetRotation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetAxis of class  Constraint */
#ifndef TOLUA_DISABLE_tolua_Physics_Constraint_SetAxis00
static int tolua_Physics_Constraint_SetAxis00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Constraint",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Constraint* self = (Constraint*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* axis = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetAxis'", NULL);
#endif
  {
   self->SetAxis(*axis);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetAxis'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetOtherPosition of class  Constraint */
#ifndef TOLUA_DISABLE_tolua_Physics_Constraint_SetOtherPosition00
static int tolua_Physics_Constraint_SetOtherPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Constraint",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Constraint* self = (Constraint*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* position = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetOtherPosition'", NULL);
#endif
  {
   self->SetOtherPosition(*position);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetOtherPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetOtherRotation of class  Constraint */
#ifndef TOLUA_DISABLE_tolua_Physics_Constraint_SetOtherRotation00
static int tolua_Physics_Constraint_SetOtherRotation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Constraint",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Quaternion",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Constraint* self = (Constraint*)  tolua_tousertype(tolua_S,1,0);
  const Quaternion* rotation = ((const Quaternion*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetOtherRotation'", NULL);
#endif
  {
   self->SetOtherRotation(*rotation);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetOtherRotation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetOtherAxis of class  Constraint */
#ifndef TOLUA_DISABLE_tolua_Physics_Constraint_SetOtherAxis00
static int tolua_Physics_Constraint_SetOtherAxis00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Constraint",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Constraint* self = (Constraint*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* axis = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetOtherAxis'", NULL);
#endif
  {
   self->SetOtherAxis(*axis);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetOtherAxis'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetWorldPosition of class  Constraint */
#ifndef TOLUA_DISABLE_tolua_Physics_Constraint_SetWorldPosition00
static int tolua_Physics_Constraint_SetWorldPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Constraint",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Constraint* self = (Constraint*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* position = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetWorldPosition'", NULL);
#endif
  {
   self->SetWorldPosition(*position);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetWorldPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetHighLimit of class  Constraint */
#ifndef TOLUA_DISABLE_tolua_Physics_Constraint_SetHighLimit00
static int tolua_Physics_Constraint_SetHighLimit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Constraint",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Constraint* self = (Constraint*)  tolua_tousertype(tolua_S,1,0);
  const Vector2* limit = ((const Vector2*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetHighLimit'", NULL);
#endif
  {
   self->SetHighLimit(*limit);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetHighLimit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetLowLimit of class  Constraint */
#ifndef TOLUA_DISABLE_tolua_Physics_Constraint_SetLowLimit00
static int tolua_Physics_Constraint_SetLowLimit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Constraint",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Constraint* self = (Constraint*)  tolua_tousertype(tolua_S,1,0);
  const Vector2* limit = ((const Vector2*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLowLimit'", NULL);
#endif
  {
   self->SetLowLimit(*limit);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLowLimit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetERP of class  Constraint */
#ifndef TOLUA_DISABLE_tolua_Physics_Constraint_SetERP00
static int tolua_Physics_Constraint_SetERP00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Constraint",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Constraint* self = (Constraint*)  tolua_tousertype(tolua_S,1,0);
  float erp = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetERP'", NULL);
#endif
  {
   self->SetERP(erp);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetERP'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetCFM of class  Constraint */
#ifndef TOLUA_DISABLE_tolua_Physics_Constraint_SetCFM00
static int tolua_Physics_Constraint_SetCFM00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Constraint",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Constraint* self = (Constraint*)  tolua_tousertype(tolua_S,1,0);
  float cfm = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetCFM'", NULL);
#endif
  {
   self->SetCFM(cfm);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetCFM'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetDisableCollision of class  Constraint */
#ifndef TOLUA_DISABLE_tolua_Physics_Constraint_SetDisableCollision00
static int tolua_Physics_Constraint_SetDisableCollision00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Constraint",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Constraint* self = (Constraint*)  tolua_tousertype(tolua_S,1,0);
  bool disable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetDisableCollision'", NULL);
#endif
  {
   self->SetDisableCollision(disable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetDisableCollision'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetPhysicsWorld of class  Constraint */
#ifndef TOLUA_DISABLE_tolua_Physics_Constraint_GetPhysicsWorld00
static int tolua_Physics_Constraint_GetPhysicsWorld00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Constraint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Constraint* self = (const Constraint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPhysicsWorld'", NULL);
#endif
  {
   PhysicsWorld* tolua_ret = (PhysicsWorld*)  self->GetPhysicsWorld();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"PhysicsWorld");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPhysicsWorld'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetConstraintType of class  Constraint */
#ifndef TOLUA_DISABLE_tolua_Physics_Constraint_GetConstraintType00
static int tolua_Physics_Constraint_GetConstraintType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Constraint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Constraint* self = (const Constraint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetConstraintType'", NULL);
#endif
  {
   ConstraintType tolua_ret = (ConstraintType)  self->GetConstraintType();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetConstraintType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetOwnBody of class  Constraint */
#ifndef TOLUA_DISABLE_tolua_Physics_Constraint_GetOwnBody00
static int tolua_Physics_Constraint_GetOwnBody00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Constraint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Constraint* self = (const Constraint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetOwnBody'", NULL);
#endif
  {
   RigidBody* tolua_ret = (RigidBody*)  self->GetOwnBody();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"RigidBody");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetOwnBody'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetOtherBody of class  Constraint */
#ifndef TOLUA_DISABLE_tolua_Physics_Constraint_GetOtherBody00
static int tolua_Physics_Constraint_GetOtherBody00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Constraint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Constraint* self = (const Constraint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetOtherBody'", NULL);
#endif
  {
   RigidBody* tolua_ret = (RigidBody*)  self->GetOtherBody();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"RigidBody");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetOtherBody'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetPosition of class  Constraint */
#ifndef TOLUA_DISABLE_tolua_Physics_Constraint_GetPosition00
static int tolua_Physics_Constraint_GetPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Constraint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Constraint* self = (const Constraint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPosition'", NULL);
#endif
  {
   const Vector3& tolua_ret = (const Vector3&)  self->GetPosition();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Vector3");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRotation of class  Constraint */
#ifndef TOLUA_DISABLE_tolua_Physics_Constraint_GetRotation00
static int tolua_Physics_Constraint_GetRotation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Constraint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Constraint* self = (const Constraint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRotation'", NULL);
#endif
  {
   const Quaternion& tolua_ret = (const Quaternion&)  self->GetRotation();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Quaternion");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRotation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetOtherPosition of class  Constraint */
#ifndef TOLUA_DISABLE_tolua_Physics_Constraint_GetOtherPosition00
static int tolua_Physics_Constraint_GetOtherPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Constraint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Constraint* self = (const Constraint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetOtherPosition'", NULL);
#endif
  {
   const Vector3& tolua_ret = (const Vector3&)  self->GetOtherPosition();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Vector3");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetOtherPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetOtherRotation of class  Constraint */
#ifndef TOLUA_DISABLE_tolua_Physics_Constraint_GetOtherRotation00
static int tolua_Physics_Constraint_GetOtherRotation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Constraint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Constraint* self = (const Constraint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetOtherRotation'", NULL);
#endif
  {
   const Quaternion& tolua_ret = (const Quaternion&)  self->GetOtherRotation();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Quaternion");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetOtherRotation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetWorldPosition of class  Constraint */
#ifndef TOLUA_DISABLE_tolua_Physics_Constraint_GetWorldPosition00
static int tolua_Physics_Constraint_GetWorldPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Constraint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Constraint* self = (const Constraint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetWorldPosition'", NULL);
#endif
  {
   Vector3 tolua_ret = (Vector3)  self->GetWorldPosition();
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
 tolua_error(tolua_S,"#ferror in function 'GetWorldPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetHighLimit of class  Constraint */
#ifndef TOLUA_DISABLE_tolua_Physics_Constraint_GetHighLimit00
static int tolua_Physics_Constraint_GetHighLimit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Constraint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Constraint* self = (const Constraint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetHighLimit'", NULL);
#endif
  {
   const Vector2& tolua_ret = (const Vector2&)  self->GetHighLimit();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Vector2");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetHighLimit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLowLimit of class  Constraint */
#ifndef TOLUA_DISABLE_tolua_Physics_Constraint_GetLowLimit00
static int tolua_Physics_Constraint_GetLowLimit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Constraint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Constraint* self = (const Constraint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLowLimit'", NULL);
#endif
  {
   const Vector2& tolua_ret = (const Vector2&)  self->GetLowLimit();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Vector2");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLowLimit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetERP of class  Constraint */
#ifndef TOLUA_DISABLE_tolua_Physics_Constraint_GetERP00
static int tolua_Physics_Constraint_GetERP00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Constraint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Constraint* self = (const Constraint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetERP'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetERP();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetERP'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCFM of class  Constraint */
#ifndef TOLUA_DISABLE_tolua_Physics_Constraint_GetCFM00
static int tolua_Physics_Constraint_GetCFM00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Constraint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Constraint* self = (const Constraint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCFM'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetCFM();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCFM'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetDisableCollision of class  Constraint */
#ifndef TOLUA_DISABLE_tolua_Physics_Constraint_GetDisableCollision00
static int tolua_Physics_Constraint_GetDisableCollision00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Constraint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Constraint* self = (const Constraint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetDisableCollision'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetDisableCollision();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDisableCollision'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ReleaseConstraint of class  Constraint */
#ifndef TOLUA_DISABLE_tolua_Physics_Constraint_ReleaseConstraint00
static int tolua_Physics_Constraint_ReleaseConstraint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Constraint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Constraint* self = (Constraint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ReleaseConstraint'", NULL);
#endif
  {
   self->ReleaseConstraint();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ReleaseConstraint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ApplyFrames of class  Constraint */
#ifndef TOLUA_DISABLE_tolua_Physics_Constraint_ApplyFrames00
static int tolua_Physics_Constraint_ApplyFrames00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Constraint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Constraint* self = (Constraint*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ApplyFrames'", NULL);
#endif
  {
   self->ApplyFrames();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ApplyFrames'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  PhysicsRaycastResult */
#ifndef TOLUA_DISABLE_tolua_Physics_PhysicsRaycastResult_new00
static int tolua_Physics_PhysicsRaycastResult_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"PhysicsRaycastResult",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   PhysicsRaycastResult* tolua_ret = (PhysicsRaycastResult*)  Mtolua_new((PhysicsRaycastResult)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"PhysicsRaycastResult");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  PhysicsRaycastResult */
#ifndef TOLUA_DISABLE_tolua_Physics_PhysicsRaycastResult_new00_local
static int tolua_Physics_PhysicsRaycastResult_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"PhysicsRaycastResult",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   PhysicsRaycastResult* tolua_ret = (PhysicsRaycastResult*)  Mtolua_new((PhysicsRaycastResult)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"PhysicsRaycastResult");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: position_ of class  PhysicsRaycastResult */
#ifndef TOLUA_DISABLE_tolua_get_PhysicsRaycastResult_position
static int tolua_get_PhysicsRaycastResult_position(lua_State* tolua_S)
{
  PhysicsRaycastResult* self = (PhysicsRaycastResult*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'position_'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->position_,"Vector3");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: position_ of class  PhysicsRaycastResult */
#ifndef TOLUA_DISABLE_tolua_set_PhysicsRaycastResult_position
static int tolua_set_PhysicsRaycastResult_position(lua_State* tolua_S)
{
  PhysicsRaycastResult* self = (PhysicsRaycastResult*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'position_'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"Vector3",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->position_ = *((Vector3*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: normal_ of class  PhysicsRaycastResult */
#ifndef TOLUA_DISABLE_tolua_get_PhysicsRaycastResult_normal
static int tolua_get_PhysicsRaycastResult_normal(lua_State* tolua_S)
{
  PhysicsRaycastResult* self = (PhysicsRaycastResult*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'normal_'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->normal_,"Vector3");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: normal_ of class  PhysicsRaycastResult */
#ifndef TOLUA_DISABLE_tolua_set_PhysicsRaycastResult_normal
static int tolua_set_PhysicsRaycastResult_normal(lua_State* tolua_S)
{
  PhysicsRaycastResult* self = (PhysicsRaycastResult*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'normal_'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"Vector3",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->normal_ = *((Vector3*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: distance_ of class  PhysicsRaycastResult */
#ifndef TOLUA_DISABLE_tolua_get_PhysicsRaycastResult_distance
static int tolua_get_PhysicsRaycastResult_distance(lua_State* tolua_S)
{
  PhysicsRaycastResult* self = (PhysicsRaycastResult*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'distance_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->distance_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: distance_ of class  PhysicsRaycastResult */
#ifndef TOLUA_DISABLE_tolua_set_PhysicsRaycastResult_distance
static int tolua_set_PhysicsRaycastResult_distance(lua_State* tolua_S)
{
  PhysicsRaycastResult* self = (PhysicsRaycastResult*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'distance_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->distance_ = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: body_ of class  PhysicsRaycastResult */
#ifndef TOLUA_DISABLE_tolua_get_PhysicsRaycastResult_body_ptr
static int tolua_get_PhysicsRaycastResult_body_ptr(lua_State* tolua_S)
{
  PhysicsRaycastResult* self = (PhysicsRaycastResult*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'body_'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->body_,"RigidBody");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: body_ of class  PhysicsRaycastResult */
#ifndef TOLUA_DISABLE_tolua_set_PhysicsRaycastResult_body_ptr
static int tolua_set_PhysicsRaycastResult_body_ptr(lua_State* tolua_S)
{
  PhysicsRaycastResult* self = (PhysicsRaycastResult*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'body_'",NULL);
  if (!tolua_isusertype(tolua_S,2,"RigidBody",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->body_ = ((RigidBody*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: rigidBody_ of class  DelayedWorldTransform */
#ifndef TOLUA_DISABLE_tolua_get_DelayedWorldTransform_rigidBody_ptr
static int tolua_get_DelayedWorldTransform_rigidBody_ptr(lua_State* tolua_S)
{
  DelayedWorldTransform* self = (DelayedWorldTransform*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'rigidBody_'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->rigidBody_,"RigidBody");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: rigidBody_ of class  DelayedWorldTransform */
#ifndef TOLUA_DISABLE_tolua_set_DelayedWorldTransform_rigidBody_ptr
static int tolua_set_DelayedWorldTransform_rigidBody_ptr(lua_State* tolua_S)
{
  DelayedWorldTransform* self = (DelayedWorldTransform*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'rigidBody_'",NULL);
  if (!tolua_isusertype(tolua_S,2,"RigidBody",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->rigidBody_ = ((RigidBody*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: parentRigidBody_ of class  DelayedWorldTransform */
#ifndef TOLUA_DISABLE_tolua_get_DelayedWorldTransform_parentRigidBody_ptr
static int tolua_get_DelayedWorldTransform_parentRigidBody_ptr(lua_State* tolua_S)
{
  DelayedWorldTransform* self = (DelayedWorldTransform*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'parentRigidBody_'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->parentRigidBody_,"RigidBody");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: parentRigidBody_ of class  DelayedWorldTransform */
#ifndef TOLUA_DISABLE_tolua_set_DelayedWorldTransform_parentRigidBody_ptr
static int tolua_set_DelayedWorldTransform_parentRigidBody_ptr(lua_State* tolua_S)
{
  DelayedWorldTransform* self = (DelayedWorldTransform*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'parentRigidBody_'",NULL);
  if (!tolua_isusertype(tolua_S,2,"RigidBody",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->parentRigidBody_ = ((RigidBody*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: worldPosition_ of class  DelayedWorldTransform */
#ifndef TOLUA_DISABLE_tolua_get_DelayedWorldTransform_worldPosition
static int tolua_get_DelayedWorldTransform_worldPosition(lua_State* tolua_S)
{
  DelayedWorldTransform* self = (DelayedWorldTransform*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'worldPosition_'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->worldPosition_,"Vector3");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: worldPosition_ of class  DelayedWorldTransform */
#ifndef TOLUA_DISABLE_tolua_set_DelayedWorldTransform_worldPosition
static int tolua_set_DelayedWorldTransform_worldPosition(lua_State* tolua_S)
{
  DelayedWorldTransform* self = (DelayedWorldTransform*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'worldPosition_'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"Vector3",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->worldPosition_ = *((Vector3*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: worldRotation_ of class  DelayedWorldTransform */
#ifndef TOLUA_DISABLE_tolua_get_DelayedWorldTransform_worldRotation
static int tolua_get_DelayedWorldTransform_worldRotation(lua_State* tolua_S)
{
  DelayedWorldTransform* self = (DelayedWorldTransform*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'worldRotation_'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->worldRotation_,"Quaternion");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: worldRotation_ of class  DelayedWorldTransform */
#ifndef TOLUA_DISABLE_tolua_set_DelayedWorldTransform_worldRotation
static int tolua_set_DelayedWorldTransform_worldRotation(lua_State* tolua_S)
{
  DelayedWorldTransform* self = (DelayedWorldTransform*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'worldRotation_'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"Quaternion",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->worldRotation_ = *((Quaternion*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: Update of class  PhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_Physics_PhysicsWorld_Update00
static int tolua_Physics_PhysicsWorld_Update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PhysicsWorld",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PhysicsWorld* self = (PhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  float timeStep = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Update'", NULL);
#endif
  {
   self->Update(timeStep);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Update'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: UpdateCollisions of class  PhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_Physics_PhysicsWorld_UpdateCollisions00
static int tolua_Physics_PhysicsWorld_UpdateCollisions00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PhysicsWorld",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PhysicsWorld* self = (PhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'UpdateCollisions'", NULL);
#endif
  {
   self->UpdateCollisions();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'UpdateCollisions'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFps of class  PhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_Physics_PhysicsWorld_SetFps00
static int tolua_Physics_PhysicsWorld_SetFps00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PhysicsWorld",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PhysicsWorld* self = (PhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  int fps = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFps'", NULL);
#endif
  {
   self->SetFps(fps);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFps'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetGravity of class  PhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_Physics_PhysicsWorld_SetGravity00
static int tolua_Physics_PhysicsWorld_SetGravity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PhysicsWorld",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PhysicsWorld* self = (PhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  Vector3 gravity = *((Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetGravity'", NULL);
#endif
  {
   self->SetGravity(gravity);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetGravity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetNumIterations of class  PhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_Physics_PhysicsWorld_SetNumIterations00
static int tolua_Physics_PhysicsWorld_SetNumIterations00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PhysicsWorld",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PhysicsWorld* self = (PhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  int num = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetNumIterations'", NULL);
#endif
  {
   self->SetNumIterations(num);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetNumIterations'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetInterpolation of class  PhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_Physics_PhysicsWorld_SetInterpolation00
static int tolua_Physics_PhysicsWorld_SetInterpolation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PhysicsWorld",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PhysicsWorld* self = (PhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetInterpolation'", NULL);
#endif
  {
   self->SetInterpolation(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetInterpolation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetInternalEdge of class  PhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_Physics_PhysicsWorld_SetInternalEdge00
static int tolua_Physics_PhysicsWorld_SetInternalEdge00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PhysicsWorld",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PhysicsWorld* self = (PhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetInternalEdge'", NULL);
#endif
  {
   self->SetInternalEdge(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetInternalEdge'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetSplitImpulse of class  PhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_Physics_PhysicsWorld_SetSplitImpulse00
static int tolua_Physics_PhysicsWorld_SetSplitImpulse00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PhysicsWorld",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PhysicsWorld* self = (PhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetSplitImpulse'", NULL);
#endif
  {
   self->SetSplitImpulse(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetSplitImpulse'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMaxNetworkAngularVelocity of class  PhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_Physics_PhysicsWorld_SetMaxNetworkAngularVelocity00
static int tolua_Physics_PhysicsWorld_SetMaxNetworkAngularVelocity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PhysicsWorld",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PhysicsWorld* self = (PhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  float velocity = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMaxNetworkAngularVelocity'", NULL);
#endif
  {
   self->SetMaxNetworkAngularVelocity(velocity);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMaxNetworkAngularVelocity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RaycastSingle of class  PhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_Physics_PhysicsWorld_RaycastSingle00
static int tolua_Physics_PhysicsWorld_RaycastSingle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PhysicsWorld",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"PhysicsRaycastResult",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const Ray",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PhysicsWorld* self = (PhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  PhysicsRaycastResult* result = ((PhysicsRaycastResult*)  tolua_tousertype(tolua_S,2,0));
  const Ray* ray = ((const Ray*)  tolua_tousertype(tolua_S,3,0));
  float maxDistance = ((float)  tolua_tonumber(tolua_S,4,0));
  unsigned collisionMask = ((unsigned)  tolua_tonumber(tolua_S,5,M_MAX_UNSIGNED));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RaycastSingle'", NULL);
#endif
  {
   self->RaycastSingle(*result,*ray,maxDistance,collisionMask);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RaycastSingle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SphereCast of class  PhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_Physics_PhysicsWorld_SphereCast00
static int tolua_Physics_PhysicsWorld_SphereCast00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PhysicsWorld",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"PhysicsRaycastResult",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const Ray",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PhysicsWorld* self = (PhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  PhysicsRaycastResult* result = ((PhysicsRaycastResult*)  tolua_tousertype(tolua_S,2,0));
  const Ray* ray = ((const Ray*)  tolua_tousertype(tolua_S,3,0));
  float radius = ((float)  tolua_tonumber(tolua_S,4,0));
  float maxDistance = ((float)  tolua_tonumber(tolua_S,5,0));
  unsigned collisionMask = ((unsigned)  tolua_tonumber(tolua_S,6,M_MAX_UNSIGNED));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SphereCast'", NULL);
#endif
  {
   self->SphereCast(*result,*ray,radius,maxDistance,collisionMask);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SphereCast'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetGravity of class  PhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_Physics_PhysicsWorld_GetGravity00
static int tolua_Physics_PhysicsWorld_GetGravity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const PhysicsWorld",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const PhysicsWorld* self = (const PhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetGravity'", NULL);
#endif
  {
   Vector3 tolua_ret = (Vector3)  self->GetGravity();
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
 tolua_error(tolua_S,"#ferror in function 'GetGravity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNumIterations of class  PhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_Physics_PhysicsWorld_GetNumIterations00
static int tolua_Physics_PhysicsWorld_GetNumIterations00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const PhysicsWorld",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const PhysicsWorld* self = (const PhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNumIterations'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetNumIterations();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNumIterations'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetInterpolation of class  PhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_Physics_PhysicsWorld_GetInterpolation00
static int tolua_Physics_PhysicsWorld_GetInterpolation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const PhysicsWorld",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const PhysicsWorld* self = (const PhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetInterpolation'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetInterpolation();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetInterpolation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetInternalEdge of class  PhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_Physics_PhysicsWorld_GetInternalEdge00
static int tolua_Physics_PhysicsWorld_GetInternalEdge00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const PhysicsWorld",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const PhysicsWorld* self = (const PhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetInternalEdge'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetInternalEdge();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetInternalEdge'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSplitImpulse of class  PhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_Physics_PhysicsWorld_GetSplitImpulse00
static int tolua_Physics_PhysicsWorld_GetSplitImpulse00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const PhysicsWorld",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const PhysicsWorld* self = (const PhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSplitImpulse'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetSplitImpulse();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSplitImpulse'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFps of class  PhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_Physics_PhysicsWorld_GetFps00
static int tolua_Physics_PhysicsWorld_GetFps00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const PhysicsWorld",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const PhysicsWorld* self = (const PhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFps'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetFps();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFps'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMaxNetworkAngularVelocity of class  PhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_Physics_PhysicsWorld_GetMaxNetworkAngularVelocity00
static int tolua_Physics_PhysicsWorld_GetMaxNetworkAngularVelocity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const PhysicsWorld",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const PhysicsWorld* self = (const PhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMaxNetworkAngularVelocity'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetMaxNetworkAngularVelocity();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMaxNetworkAngularVelocity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddRigidBody of class  PhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_Physics_PhysicsWorld_AddRigidBody00
static int tolua_Physics_PhysicsWorld_AddRigidBody00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PhysicsWorld",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"RigidBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PhysicsWorld* self = (PhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  RigidBody* body = ((RigidBody*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddRigidBody'", NULL);
#endif
  {
   self->AddRigidBody(body);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddRigidBody'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveRigidBody of class  PhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_Physics_PhysicsWorld_RemoveRigidBody00
static int tolua_Physics_PhysicsWorld_RemoveRigidBody00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PhysicsWorld",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"RigidBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PhysicsWorld* self = (PhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  RigidBody* body = ((RigidBody*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveRigidBody'", NULL);
#endif
  {
   self->RemoveRigidBody(body);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemoveRigidBody'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddCollisionShape of class  PhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_Physics_PhysicsWorld_AddCollisionShape00
static int tolua_Physics_PhysicsWorld_AddCollisionShape00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PhysicsWorld",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CollisionShape",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PhysicsWorld* self = (PhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  CollisionShape* shape = ((CollisionShape*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddCollisionShape'", NULL);
#endif
  {
   self->AddCollisionShape(shape);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddCollisionShape'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveCollisionShape of class  PhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_Physics_PhysicsWorld_RemoveCollisionShape00
static int tolua_Physics_PhysicsWorld_RemoveCollisionShape00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PhysicsWorld",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"CollisionShape",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PhysicsWorld* self = (PhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  CollisionShape* shape = ((CollisionShape*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveCollisionShape'", NULL);
#endif
  {
   self->RemoveCollisionShape(shape);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemoveCollisionShape'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddConstraint of class  PhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_Physics_PhysicsWorld_AddConstraint00
static int tolua_Physics_PhysicsWorld_AddConstraint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PhysicsWorld",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Constraint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PhysicsWorld* self = (PhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  Constraint* joint = ((Constraint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddConstraint'", NULL);
#endif
  {
   self->AddConstraint(joint);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddConstraint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveConstraint of class  PhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_Physics_PhysicsWorld_RemoveConstraint00
static int tolua_Physics_PhysicsWorld_RemoveConstraint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PhysicsWorld",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Constraint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PhysicsWorld* self = (PhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  Constraint* joint = ((Constraint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveConstraint'", NULL);
#endif
  {
   self->RemoveConstraint(joint);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemoveConstraint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddDelayedWorldTransform of class  PhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_Physics_PhysicsWorld_AddDelayedWorldTransform00
static int tolua_Physics_PhysicsWorld_AddDelayedWorldTransform00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PhysicsWorld",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const DelayedWorldTransform",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PhysicsWorld* self = (PhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  const DelayedWorldTransform* transform = ((const DelayedWorldTransform*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddDelayedWorldTransform'", NULL);
#endif
  {
   self->AddDelayedWorldTransform(*transform);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddDelayedWorldTransform'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DrawDebugGeometry of class  PhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_Physics_PhysicsWorld_DrawDebugGeometry00
static int tolua_Physics_PhysicsWorld_DrawDebugGeometry00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PhysicsWorld",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PhysicsWorld* self = (PhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  bool depthTest = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DrawDebugGeometry'", NULL);
#endif
  {
   self->DrawDebugGeometry(depthTest);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DrawDebugGeometry'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetDebugRenderer of class  PhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_Physics_PhysicsWorld_SetDebugRenderer00
static int tolua_Physics_PhysicsWorld_SetDebugRenderer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PhysicsWorld",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"DebugRenderer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PhysicsWorld* self = (PhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  DebugRenderer* debug = ((DebugRenderer*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetDebugRenderer'", NULL);
#endif
  {
   self->SetDebugRenderer(debug);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetDebugRenderer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetDebugDepthTest of class  PhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_Physics_PhysicsWorld_SetDebugDepthTest00
static int tolua_Physics_PhysicsWorld_SetDebugDepthTest00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PhysicsWorld",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PhysicsWorld* self = (PhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetDebugDepthTest'", NULL);
#endif
  {
   self->SetDebugDepthTest(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetDebugDepthTest'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CleanupGeometryCache of class  PhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_Physics_PhysicsWorld_CleanupGeometryCache00
static int tolua_Physics_PhysicsWorld_CleanupGeometryCache00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PhysicsWorld",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PhysicsWorld* self = (PhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CleanupGeometryCache'", NULL);
#endif
  {
   self->CleanupGeometryCache();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CleanupGeometryCache'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetApplyingTransforms of class  PhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_Physics_PhysicsWorld_SetApplyingTransforms00
static int tolua_Physics_PhysicsWorld_SetApplyingTransforms00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PhysicsWorld",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PhysicsWorld* self = (PhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetApplyingTransforms'", NULL);
#endif
  {
   self->SetApplyingTransforms(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetApplyingTransforms'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsApplyingTransforms of class  PhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_Physics_PhysicsWorld_IsApplyingTransforms00
static int tolua_Physics_PhysicsWorld_IsApplyingTransforms00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const PhysicsWorld",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const PhysicsWorld* self = (const PhysicsWorld*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsApplyingTransforms'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsApplyingTransforms();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsApplyingTransforms'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GetPhysicsWorld */
#ifndef TOLUA_DISABLE_tolua_Physics_GetPhysicsWorld00
static int tolua_Physics_GetPhysicsWorld00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnoobj(tolua_S,1,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   PhysicsWorld* tolua_ret = (PhysicsWorld*)  GetPhysicsWorld();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"PhysicsWorld");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPhysicsWorld'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMass of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_SetMass00
static int tolua_Physics_RigidBody_SetMass00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RigidBody",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RigidBody* self = (RigidBody*)  tolua_tousertype(tolua_S,1,0);
  float mass = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMass'", NULL);
#endif
  {
   self->SetMass(mass);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMass'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetPosition of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_SetPosition00
static int tolua_Physics_RigidBody_SetPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RigidBody",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RigidBody* self = (RigidBody*)  tolua_tousertype(tolua_S,1,0);
  Vector3 position = *((Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetPosition'", NULL);
#endif
  {
   self->SetPosition(position);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetRotation of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_SetRotation00
static int tolua_Physics_RigidBody_SetRotation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RigidBody",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"Quaternion",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RigidBody* self = (RigidBody*)  tolua_tousertype(tolua_S,1,0);
  Quaternion rotation = *((Quaternion*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetRotation'", NULL);
#endif
  {
   self->SetRotation(rotation);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetRotation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetTransform of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_SetTransform00
static int tolua_Physics_RigidBody_SetTransform00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RigidBody",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const Quaternion",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RigidBody* self = (RigidBody*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* position = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
  const Quaternion* rotation = ((const Quaternion*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetTransform'", NULL);
#endif
  {
   self->SetTransform(*position,*rotation);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetTransform'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetLinearVelocity of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_SetLinearVelocity00
static int tolua_Physics_RigidBody_SetLinearVelocity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RigidBody",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RigidBody* self = (RigidBody*)  tolua_tousertype(tolua_S,1,0);
  Vector3 velocity = *((Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLinearVelocity'", NULL);
#endif
  {
   self->SetLinearVelocity(velocity);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLinearVelocity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetLinearFactor of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_SetLinearFactor00
static int tolua_Physics_RigidBody_SetLinearFactor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RigidBody",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RigidBody* self = (RigidBody*)  tolua_tousertype(tolua_S,1,0);
  Vector3 factor = *((Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLinearFactor'", NULL);
#endif
  {
   self->SetLinearFactor(factor);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLinearFactor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetLinearRestThreshold of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_SetLinearRestThreshold00
static int tolua_Physics_RigidBody_SetLinearRestThreshold00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RigidBody",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RigidBody* self = (RigidBody*)  tolua_tousertype(tolua_S,1,0);
  float threshold = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLinearRestThreshold'", NULL);
#endif
  {
   self->SetLinearRestThreshold(threshold);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLinearRestThreshold'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetLinearDamping of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_SetLinearDamping00
static int tolua_Physics_RigidBody_SetLinearDamping00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RigidBody",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RigidBody* self = (RigidBody*)  tolua_tousertype(tolua_S,1,0);
  float damping = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLinearDamping'", NULL);
#endif
  {
   self->SetLinearDamping(damping);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLinearDamping'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetAngularVelocity of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_SetAngularVelocity00
static int tolua_Physics_RigidBody_SetAngularVelocity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RigidBody",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RigidBody* self = (RigidBody*)  tolua_tousertype(tolua_S,1,0);
  Vector3 angularVelocity = *((Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetAngularVelocity'", NULL);
#endif
  {
   self->SetAngularVelocity(angularVelocity);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetAngularVelocity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetAngularFactor of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_SetAngularFactor00
static int tolua_Physics_RigidBody_SetAngularFactor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RigidBody",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RigidBody* self = (RigidBody*)  tolua_tousertype(tolua_S,1,0);
  Vector3 factor = *((Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetAngularFactor'", NULL);
#endif
  {
   self->SetAngularFactor(factor);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetAngularFactor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetAngularRestThreshold of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_SetAngularRestThreshold00
static int tolua_Physics_RigidBody_SetAngularRestThreshold00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RigidBody",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RigidBody* self = (RigidBody*)  tolua_tousertype(tolua_S,1,0);
  float threshold = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetAngularRestThreshold'", NULL);
#endif
  {
   self->SetAngularRestThreshold(threshold);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetAngularRestThreshold'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetAngularDamping of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_SetAngularDamping00
static int tolua_Physics_RigidBody_SetAngularDamping00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RigidBody",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RigidBody* self = (RigidBody*)  tolua_tousertype(tolua_S,1,0);
  float factor = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetAngularDamping'", NULL);
#endif
  {
   self->SetAngularDamping(factor);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetAngularDamping'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFriction of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_SetFriction00
static int tolua_Physics_RigidBody_SetFriction00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RigidBody",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RigidBody* self = (RigidBody*)  tolua_tousertype(tolua_S,1,0);
  float friction = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFriction'", NULL);
#endif
  {
   self->SetFriction(friction);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFriction'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetRestitution of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_SetRestitution00
static int tolua_Physics_RigidBody_SetRestitution00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RigidBody",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RigidBody* self = (RigidBody*)  tolua_tousertype(tolua_S,1,0);
  float restitution = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetRestitution'", NULL);
#endif
  {
   self->SetRestitution(restitution);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetRestitution'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetContactProcessingThreshold of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_SetContactProcessingThreshold00
static int tolua_Physics_RigidBody_SetContactProcessingThreshold00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RigidBody",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RigidBody* self = (RigidBody*)  tolua_tousertype(tolua_S,1,0);
  float threshold = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetContactProcessingThreshold'", NULL);
#endif
  {
   self->SetContactProcessingThreshold(threshold);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetContactProcessingThreshold'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetCcdRadius of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_SetCcdRadius00
static int tolua_Physics_RigidBody_SetCcdRadius00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RigidBody",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RigidBody* self = (RigidBody*)  tolua_tousertype(tolua_S,1,0);
  float radius = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetCcdRadius'", NULL);
#endif
  {
   self->SetCcdRadius(radius);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetCcdRadius'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetCcdMotionThreshold of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_SetCcdMotionThreshold00
static int tolua_Physics_RigidBody_SetCcdMotionThreshold00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RigidBody",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RigidBody* self = (RigidBody*)  tolua_tousertype(tolua_S,1,0);
  float threshold = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetCcdMotionThreshold'", NULL);
#endif
  {
   self->SetCcdMotionThreshold(threshold);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetCcdMotionThreshold'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetUseGravity of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_SetUseGravity00
static int tolua_Physics_RigidBody_SetUseGravity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RigidBody",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RigidBody* self = (RigidBody*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetUseGravity'", NULL);
#endif
  {
   self->SetUseGravity(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetUseGravity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetGravityOverride of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_SetGravityOverride00
static int tolua_Physics_RigidBody_SetGravityOverride00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RigidBody",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RigidBody* self = (RigidBody*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* gravity = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetGravityOverride'", NULL);
#endif
  {
   self->SetGravityOverride(*gravity);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetGravityOverride'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetKinematic of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_SetKinematic00
static int tolua_Physics_RigidBody_SetKinematic00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RigidBody",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RigidBody* self = (RigidBody*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetKinematic'", NULL);
#endif
  {
   self->SetKinematic(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetKinematic'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetPhantom of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_SetPhantom00
static int tolua_Physics_RigidBody_SetPhantom00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RigidBody",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RigidBody* self = (RigidBody*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetPhantom'", NULL);
#endif
  {
   self->SetPhantom(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetPhantom'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetCollisionLayer of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_SetCollisionLayer00
static int tolua_Physics_RigidBody_SetCollisionLayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RigidBody",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RigidBody* self = (RigidBody*)  tolua_tousertype(tolua_S,1,0);
  unsigned layer = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetCollisionLayer'", NULL);
#endif
  {
   self->SetCollisionLayer(layer);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetCollisionLayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetCollisionMask of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_SetCollisionMask00
static int tolua_Physics_RigidBody_SetCollisionMask00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RigidBody",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RigidBody* self = (RigidBody*)  tolua_tousertype(tolua_S,1,0);
  unsigned mask = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetCollisionMask'", NULL);
#endif
  {
   self->SetCollisionMask(mask);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetCollisionMask'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetCollisionLayerAndMask of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_SetCollisionLayerAndMask00
static int tolua_Physics_RigidBody_SetCollisionLayerAndMask00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RigidBody",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RigidBody* self = (RigidBody*)  tolua_tousertype(tolua_S,1,0);
  unsigned layer = ((unsigned)  tolua_tonumber(tolua_S,2,0));
  unsigned mask = ((unsigned)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetCollisionLayerAndMask'", NULL);
#endif
  {
   self->SetCollisionLayerAndMask(layer,mask);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetCollisionLayerAndMask'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetCollisionEventMode of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_SetCollisionEventMode00
static int tolua_Physics_RigidBody_SetCollisionEventMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RigidBody",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RigidBody* self = (RigidBody*)  tolua_tousertype(tolua_S,1,0);
  CollisionEventMode mode = ((CollisionEventMode) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetCollisionEventMode'", NULL);
#endif
  {
   self->SetCollisionEventMode(mode);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetCollisionEventMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ApplyForce of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_ApplyForce00
static int tolua_Physics_RigidBody_ApplyForce00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RigidBody",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RigidBody* self = (RigidBody*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* force = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ApplyForce'", NULL);
#endif
  {
   self->ApplyForce(*force);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ApplyForce'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ApplyForce of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_ApplyForce01
static int tolua_Physics_RigidBody_ApplyForce01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RigidBody",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  RigidBody* self = (RigidBody*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* force = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
  const Vector3* position = ((const Vector3*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ApplyForce'", NULL);
#endif
  {
   self->ApplyForce(*force,*position);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Physics_RigidBody_ApplyForce00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: ApplyTorque of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_ApplyTorque00
static int tolua_Physics_RigidBody_ApplyTorque00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RigidBody",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RigidBody* self = (RigidBody*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* torque = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ApplyTorque'", NULL);
#endif
  {
   self->ApplyTorque(*torque);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ApplyTorque'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ApplyImpulse of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_ApplyImpulse00
static int tolua_Physics_RigidBody_ApplyImpulse00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RigidBody",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RigidBody* self = (RigidBody*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* impulse = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ApplyImpulse'", NULL);
#endif
  {
   self->ApplyImpulse(*impulse);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ApplyImpulse'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ApplyImpulse of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_ApplyImpulse01
static int tolua_Physics_RigidBody_ApplyImpulse01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RigidBody",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  RigidBody* self = (RigidBody*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* impulse = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
  const Vector3* position = ((const Vector3*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ApplyImpulse'", NULL);
#endif
  {
   self->ApplyImpulse(*impulse,*position);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Physics_RigidBody_ApplyImpulse00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: ApplyTorqueImpulse of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_ApplyTorqueImpulse00
static int tolua_Physics_RigidBody_ApplyTorqueImpulse00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RigidBody",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RigidBody* self = (RigidBody*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* torque = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ApplyTorqueImpulse'", NULL);
#endif
  {
   self->ApplyTorqueImpulse(*torque);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ApplyTorqueImpulse'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ResetForces of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_ResetForces00
static int tolua_Physics_RigidBody_ResetForces00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RigidBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RigidBody* self = (RigidBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ResetForces'", NULL);
#endif
  {
   self->ResetForces();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ResetForces'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Activate of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_Activate00
static int tolua_Physics_RigidBody_Activate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RigidBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RigidBody* self = (RigidBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Activate'", NULL);
#endif
  {
   self->Activate();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Activate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ReAddBodyToWorld of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_ReAddBodyToWorld00
static int tolua_Physics_RigidBody_ReAddBodyToWorld00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RigidBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RigidBody* self = (RigidBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ReAddBodyToWorld'", NULL);
#endif
  {
   self->ReAddBodyToWorld();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ReAddBodyToWorld'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetPhysicsWorld of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_GetPhysicsWorld00
static int tolua_Physics_RigidBody_GetPhysicsWorld00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const RigidBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const RigidBody* self = (const RigidBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPhysicsWorld'", NULL);
#endif
  {
   PhysicsWorld* tolua_ret = (PhysicsWorld*)  self->GetPhysicsWorld();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"PhysicsWorld");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPhysicsWorld'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMass of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_GetMass00
static int tolua_Physics_RigidBody_GetMass00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const RigidBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const RigidBody* self = (const RigidBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMass'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetMass();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMass'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetPosition of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_GetPosition00
static int tolua_Physics_RigidBody_GetPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const RigidBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const RigidBody* self = (const RigidBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPosition'", NULL);
#endif
  {
   Vector3 tolua_ret = (Vector3)  self->GetPosition();
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
 tolua_error(tolua_S,"#ferror in function 'GetPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRotation of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_GetRotation00
static int tolua_Physics_RigidBody_GetRotation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const RigidBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const RigidBody* self = (const RigidBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRotation'", NULL);
#endif
  {
   Quaternion tolua_ret = (Quaternion)  self->GetRotation();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((Quaternion)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"Quaternion");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Quaternion));
     tolua_pushusertype(tolua_S,tolua_obj,"Quaternion");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRotation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLinearVelocity of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_GetLinearVelocity00
static int tolua_Physics_RigidBody_GetLinearVelocity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const RigidBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const RigidBody* self = (const RigidBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLinearVelocity'", NULL);
#endif
  {
   Vector3 tolua_ret = (Vector3)  self->GetLinearVelocity();
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
 tolua_error(tolua_S,"#ferror in function 'GetLinearVelocity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLinearFactor of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_GetLinearFactor00
static int tolua_Physics_RigidBody_GetLinearFactor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const RigidBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const RigidBody* self = (const RigidBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLinearFactor'", NULL);
#endif
  {
   Vector3 tolua_ret = (Vector3)  self->GetLinearFactor();
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
 tolua_error(tolua_S,"#ferror in function 'GetLinearFactor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetVelocityAtPoint of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_GetVelocityAtPoint00
static int tolua_Physics_RigidBody_GetVelocityAtPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const RigidBody",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const RigidBody* self = (const RigidBody*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* position = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetVelocityAtPoint'", NULL);
#endif
  {
   Vector3 tolua_ret = (Vector3)  self->GetVelocityAtPoint(*position);
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
 tolua_error(tolua_S,"#ferror in function 'GetVelocityAtPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLinearRestThreshold of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_GetLinearRestThreshold00
static int tolua_Physics_RigidBody_GetLinearRestThreshold00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const RigidBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const RigidBody* self = (const RigidBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLinearRestThreshold'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetLinearRestThreshold();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLinearRestThreshold'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLinearDamping of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_GetLinearDamping00
static int tolua_Physics_RigidBody_GetLinearDamping00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const RigidBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const RigidBody* self = (const RigidBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLinearDamping'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetLinearDamping();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLinearDamping'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAngularVelocity of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_GetAngularVelocity00
static int tolua_Physics_RigidBody_GetAngularVelocity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const RigidBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const RigidBody* self = (const RigidBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAngularVelocity'", NULL);
#endif
  {
   Vector3 tolua_ret = (Vector3)  self->GetAngularVelocity();
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
 tolua_error(tolua_S,"#ferror in function 'GetAngularVelocity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAngularFactor of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_GetAngularFactor00
static int tolua_Physics_RigidBody_GetAngularFactor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const RigidBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const RigidBody* self = (const RigidBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAngularFactor'", NULL);
#endif
  {
   Vector3 tolua_ret = (Vector3)  self->GetAngularFactor();
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
 tolua_error(tolua_S,"#ferror in function 'GetAngularFactor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAngularRestThreshold of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_GetAngularRestThreshold00
static int tolua_Physics_RigidBody_GetAngularRestThreshold00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const RigidBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const RigidBody* self = (const RigidBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAngularRestThreshold'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetAngularRestThreshold();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAngularRestThreshold'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAngularDamping of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_GetAngularDamping00
static int tolua_Physics_RigidBody_GetAngularDamping00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const RigidBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const RigidBody* self = (const RigidBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAngularDamping'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetAngularDamping();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAngularDamping'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFriction of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_GetFriction00
static int tolua_Physics_RigidBody_GetFriction00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const RigidBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const RigidBody* self = (const RigidBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFriction'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetFriction();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFriction'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRestitution of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_GetRestitution00
static int tolua_Physics_RigidBody_GetRestitution00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const RigidBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const RigidBody* self = (const RigidBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRestitution'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetRestitution();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRestitution'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetContactProcessingThreshold of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_GetContactProcessingThreshold00
static int tolua_Physics_RigidBody_GetContactProcessingThreshold00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const RigidBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const RigidBody* self = (const RigidBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetContactProcessingThreshold'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetContactProcessingThreshold();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetContactProcessingThreshold'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCcdRadius of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_GetCcdRadius00
static int tolua_Physics_RigidBody_GetCcdRadius00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const RigidBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const RigidBody* self = (const RigidBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCcdRadius'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetCcdRadius();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCcdRadius'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCcdMotionThreshold of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_GetCcdMotionThreshold00
static int tolua_Physics_RigidBody_GetCcdMotionThreshold00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const RigidBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const RigidBody* self = (const RigidBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCcdMotionThreshold'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetCcdMotionThreshold();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCcdMotionThreshold'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetUseGravity of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_GetUseGravity00
static int tolua_Physics_RigidBody_GetUseGravity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const RigidBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const RigidBody* self = (const RigidBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetUseGravity'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetUseGravity();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetUseGravity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetGravityOverride of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_GetGravityOverride00
static int tolua_Physics_RigidBody_GetGravityOverride00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const RigidBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const RigidBody* self = (const RigidBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetGravityOverride'", NULL);
#endif
  {
   const Vector3& tolua_ret = (const Vector3&)  self->GetGravityOverride();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Vector3");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetGravityOverride'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCenterOfMass of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_GetCenterOfMass00
static int tolua_Physics_RigidBody_GetCenterOfMass00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const RigidBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const RigidBody* self = (const RigidBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCenterOfMass'", NULL);
#endif
  {
   const Vector3& tolua_ret = (const Vector3&)  self->GetCenterOfMass();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Vector3");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCenterOfMass'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsKinematic of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_IsKinematic00
static int tolua_Physics_RigidBody_IsKinematic00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const RigidBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const RigidBody* self = (const RigidBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsKinematic'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsKinematic();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsKinematic'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsPhantom of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_IsPhantom00
static int tolua_Physics_RigidBody_IsPhantom00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const RigidBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const RigidBody* self = (const RigidBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsPhantom'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsPhantom();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsPhantom'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsActive of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_IsActive00
static int tolua_Physics_RigidBody_IsActive00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const RigidBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const RigidBody* self = (const RigidBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsActive'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsActive();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsActive'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCollisionLayer of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_GetCollisionLayer00
static int tolua_Physics_RigidBody_GetCollisionLayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const RigidBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const RigidBody* self = (const RigidBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCollisionLayer'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetCollisionLayer();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCollisionLayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCollisionMask of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_GetCollisionMask00
static int tolua_Physics_RigidBody_GetCollisionMask00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const RigidBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const RigidBody* self = (const RigidBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCollisionMask'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetCollisionMask();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCollisionMask'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCollisionEventMode of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_GetCollisionEventMode00
static int tolua_Physics_RigidBody_GetCollisionEventMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const RigidBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const RigidBody* self = (const RigidBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCollisionEventMode'", NULL);
#endif
  {
   CollisionEventMode tolua_ret = (CollisionEventMode)  self->GetCollisionEventMode();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCollisionEventMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ApplyWorldTransform of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_ApplyWorldTransform00
static int tolua_Physics_RigidBody_ApplyWorldTransform00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RigidBody",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const Quaternion",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RigidBody* self = (RigidBody*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* newWorldPosition = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
  const Quaternion* newWorldRotation = ((const Quaternion*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ApplyWorldTransform'", NULL);
#endif
  {
   self->ApplyWorldTransform(*newWorldPosition,*newWorldRotation);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ApplyWorldTransform'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: UpdateMass of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_UpdateMass00
static int tolua_Physics_RigidBody_UpdateMass00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RigidBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RigidBody* self = (RigidBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'UpdateMass'", NULL);
#endif
  {
   self->UpdateMass();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'UpdateMass'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: UpdateGravity of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_UpdateGravity00
static int tolua_Physics_RigidBody_UpdateGravity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RigidBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RigidBody* self = (RigidBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'UpdateGravity'", NULL);
#endif
  {
   self->UpdateGravity();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'UpdateGravity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddConstraint of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_AddConstraint00
static int tolua_Physics_RigidBody_AddConstraint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RigidBody",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Constraint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RigidBody* self = (RigidBody*)  tolua_tousertype(tolua_S,1,0);
  Constraint* constraint = ((Constraint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddConstraint'", NULL);
#endif
  {
   self->AddConstraint(constraint);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddConstraint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveConstraint of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_RemoveConstraint00
static int tolua_Physics_RigidBody_RemoveConstraint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RigidBody",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Constraint",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RigidBody* self = (RigidBody*)  tolua_tousertype(tolua_S,1,0);
  Constraint* constraint = ((Constraint*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveConstraint'", NULL);
#endif
  {
   self->RemoveConstraint(constraint);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemoveConstraint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ReleaseBody of class  RigidBody */
#ifndef TOLUA_DISABLE_tolua_Physics_RigidBody_ReleaseBody00
static int tolua_Physics_RigidBody_ReleaseBody00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RigidBody",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RigidBody* self = (RigidBody*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ReleaseBody'", NULL);
#endif
  {
   self->ReleaseBody();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ReleaseBody'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_Physics_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_constant(tolua_S,"SHAPE_BOX",SHAPE_BOX);
  tolua_constant(tolua_S,"SHAPE_SPHERE",SHAPE_SPHERE);
  tolua_constant(tolua_S,"SHAPE_STATICPLANE",SHAPE_STATICPLANE);
  tolua_constant(tolua_S,"SHAPE_CYLINDER",SHAPE_CYLINDER);
  tolua_constant(tolua_S,"SHAPE_CAPSULE",SHAPE_CAPSULE);
  tolua_constant(tolua_S,"SHAPE_CONE",SHAPE_CONE);
  tolua_constant(tolua_S,"SHAPE_TRIANGLEMESH",SHAPE_TRIANGLEMESH);
  tolua_constant(tolua_S,"SHAPE_CONVEXHULL",SHAPE_CONVEXHULL);
  tolua_constant(tolua_S,"SHAPE_TERRAIN",SHAPE_TERRAIN);
  tolua_cclass(tolua_S,"CollisionShape","CollisionShape","Component",NULL);
  tolua_beginmodule(tolua_S,"CollisionShape");
   tolua_function(tolua_S,"SetBox",tolua_Physics_CollisionShape_SetBox00);
   tolua_function(tolua_S,"SetBox",tolua_Physics_CollisionShape_SetBox01);
   tolua_function(tolua_S,"SetBox",tolua_Physics_CollisionShape_SetBox02);
   tolua_function(tolua_S,"SetSphere",tolua_Physics_CollisionShape_SetSphere00);
   tolua_function(tolua_S,"SetSphere",tolua_Physics_CollisionShape_SetSphere01);
   tolua_function(tolua_S,"SetSphere",tolua_Physics_CollisionShape_SetSphere02);
   tolua_function(tolua_S,"SetStaticPlane",tolua_Physics_CollisionShape_SetStaticPlane00);
   tolua_function(tolua_S,"SetStaticPlane",tolua_Physics_CollisionShape_SetStaticPlane01);
   tolua_function(tolua_S,"SetStaticPlane",tolua_Physics_CollisionShape_SetStaticPlane02);
   tolua_function(tolua_S,"SetCylinder",tolua_Physics_CollisionShape_SetCylinder00);
   tolua_function(tolua_S,"SetCylinder",tolua_Physics_CollisionShape_SetCylinder01);
   tolua_function(tolua_S,"SetCylinder",tolua_Physics_CollisionShape_SetCylinder02);
   tolua_function(tolua_S,"SetCapsule",tolua_Physics_CollisionShape_SetCapsule00);
   tolua_function(tolua_S,"SetCapsule",tolua_Physics_CollisionShape_SetCapsule01);
   tolua_function(tolua_S,"SetCapsule",tolua_Physics_CollisionShape_SetCapsule02);
   tolua_function(tolua_S,"SetCone",tolua_Physics_CollisionShape_SetCone00);
   tolua_function(tolua_S,"SetCone",tolua_Physics_CollisionShape_SetCone01);
   tolua_function(tolua_S,"SetCone",tolua_Physics_CollisionShape_SetCone02);
   tolua_function(tolua_S,"SetTriangleMesh",tolua_Physics_CollisionShape_SetTriangleMesh00);
   tolua_function(tolua_S,"SetTriangleMesh",tolua_Physics_CollisionShape_SetTriangleMesh01);
   tolua_function(tolua_S,"SetTriangleMesh",tolua_Physics_CollisionShape_SetTriangleMesh02);
   tolua_function(tolua_S,"SetTriangleMesh",tolua_Physics_CollisionShape_SetTriangleMesh03);
   tolua_function(tolua_S,"SetConvexHull",tolua_Physics_CollisionShape_SetConvexHull00);
   tolua_function(tolua_S,"SetConvexHull",tolua_Physics_CollisionShape_SetConvexHull01);
   tolua_function(tolua_S,"SetConvexHull",tolua_Physics_CollisionShape_SetConvexHull02);
   tolua_function(tolua_S,"SetConvexHull",tolua_Physics_CollisionShape_SetConvexHull03);
   tolua_function(tolua_S,"SetTerrain",tolua_Physics_CollisionShape_SetTerrain00);
   tolua_function(tolua_S,"SetShapeType",tolua_Physics_CollisionShape_SetShapeType00);
   tolua_function(tolua_S,"SetSize",tolua_Physics_CollisionShape_SetSize00);
   tolua_function(tolua_S,"SetPosition",tolua_Physics_CollisionShape_SetPosition00);
   tolua_function(tolua_S,"SetRotation",tolua_Physics_CollisionShape_SetRotation00);
   tolua_function(tolua_S,"SetTransform",tolua_Physics_CollisionShape_SetTransform00);
   tolua_function(tolua_S,"SetMargin",tolua_Physics_CollisionShape_SetMargin00);
   tolua_function(tolua_S,"SetModel",tolua_Physics_CollisionShape_SetModel00);
   tolua_function(tolua_S,"SetLodLevel",tolua_Physics_CollisionShape_SetLodLevel00);
   tolua_function(tolua_S,"GetPhysicsWorld",tolua_Physics_CollisionShape_GetPhysicsWorld00);
   tolua_function(tolua_S,"GetShapeType",tolua_Physics_CollisionShape_GetShapeType00);
   tolua_function(tolua_S,"GetSize",tolua_Physics_CollisionShape_GetSize00);
   tolua_function(tolua_S,"GetPosition",tolua_Physics_CollisionShape_GetPosition00);
   tolua_function(tolua_S,"GetRotation",tolua_Physics_CollisionShape_GetRotation00);
   tolua_function(tolua_S,"GetMargin",tolua_Physics_CollisionShape_GetMargin00);
   tolua_function(tolua_S,"GetModel",tolua_Physics_CollisionShape_GetModel00);
   tolua_function(tolua_S,"GetLodLevel",tolua_Physics_CollisionShape_GetLodLevel00);
   tolua_function(tolua_S,"GetWorldBoundingBox",tolua_Physics_CollisionShape_GetWorldBoundingBox00);
   tolua_function(tolua_S,"NotifyRigidBody",tolua_Physics_CollisionShape_NotifyRigidBody00);
   tolua_function(tolua_S,"SetModelAttr",tolua_Physics_CollisionShape_SetModelAttr00);
   tolua_function(tolua_S,"GetModelAttr",tolua_Physics_CollisionShape_GetModelAttr00);
   tolua_function(tolua_S,"ReleaseShape",tolua_Physics_CollisionShape_ReleaseShape00);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"CONSTRAINT_POINT",CONSTRAINT_POINT);
  tolua_constant(tolua_S,"CONSTRAINT_HINGE",CONSTRAINT_HINGE);
  tolua_constant(tolua_S,"CONSTRAINT_SLIDER",CONSTRAINT_SLIDER);
  tolua_constant(tolua_S,"CONSTRAINT_CONETWIST",CONSTRAINT_CONETWIST);
  tolua_cclass(tolua_S,"Constraint","Constraint","Component",NULL);
  tolua_beginmodule(tolua_S,"Constraint");
   tolua_function(tolua_S,"SetConstraintType",tolua_Physics_Constraint_SetConstraintType00);
   tolua_function(tolua_S,"SetOtherBody",tolua_Physics_Constraint_SetOtherBody00);
   tolua_function(tolua_S,"SetPosition",tolua_Physics_Constraint_SetPosition00);
   tolua_function(tolua_S,"SetRotation",tolua_Physics_Constraint_SetRotation00);
   tolua_function(tolua_S,"SetAxis",tolua_Physics_Constraint_SetAxis00);
   tolua_function(tolua_S,"SetOtherPosition",tolua_Physics_Constraint_SetOtherPosition00);
   tolua_function(tolua_S,"SetOtherRotation",tolua_Physics_Constraint_SetOtherRotation00);
   tolua_function(tolua_S,"SetOtherAxis",tolua_Physics_Constraint_SetOtherAxis00);
   tolua_function(tolua_S,"SetWorldPosition",tolua_Physics_Constraint_SetWorldPosition00);
   tolua_function(tolua_S,"SetHighLimit",tolua_Physics_Constraint_SetHighLimit00);
   tolua_function(tolua_S,"SetLowLimit",tolua_Physics_Constraint_SetLowLimit00);
   tolua_function(tolua_S,"SetERP",tolua_Physics_Constraint_SetERP00);
   tolua_function(tolua_S,"SetCFM",tolua_Physics_Constraint_SetCFM00);
   tolua_function(tolua_S,"SetDisableCollision",tolua_Physics_Constraint_SetDisableCollision00);
   tolua_function(tolua_S,"GetPhysicsWorld",tolua_Physics_Constraint_GetPhysicsWorld00);
   tolua_function(tolua_S,"GetConstraintType",tolua_Physics_Constraint_GetConstraintType00);
   tolua_function(tolua_S,"GetOwnBody",tolua_Physics_Constraint_GetOwnBody00);
   tolua_function(tolua_S,"GetOtherBody",tolua_Physics_Constraint_GetOtherBody00);
   tolua_function(tolua_S,"GetPosition",tolua_Physics_Constraint_GetPosition00);
   tolua_function(tolua_S,"GetRotation",tolua_Physics_Constraint_GetRotation00);
   tolua_function(tolua_S,"GetOtherPosition",tolua_Physics_Constraint_GetOtherPosition00);
   tolua_function(tolua_S,"GetOtherRotation",tolua_Physics_Constraint_GetOtherRotation00);
   tolua_function(tolua_S,"GetWorldPosition",tolua_Physics_Constraint_GetWorldPosition00);
   tolua_function(tolua_S,"GetHighLimit",tolua_Physics_Constraint_GetHighLimit00);
   tolua_function(tolua_S,"GetLowLimit",tolua_Physics_Constraint_GetLowLimit00);
   tolua_function(tolua_S,"GetERP",tolua_Physics_Constraint_GetERP00);
   tolua_function(tolua_S,"GetCFM",tolua_Physics_Constraint_GetCFM00);
   tolua_function(tolua_S,"GetDisableCollision",tolua_Physics_Constraint_GetDisableCollision00);
   tolua_function(tolua_S,"ReleaseConstraint",tolua_Physics_Constraint_ReleaseConstraint00);
   tolua_function(tolua_S,"ApplyFrames",tolua_Physics_Constraint_ApplyFrames00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"PhysicsRaycastResult","PhysicsRaycastResult","",tolua_collect_PhysicsRaycastResult);
  #else
  tolua_cclass(tolua_S,"PhysicsRaycastResult","PhysicsRaycastResult","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"PhysicsRaycastResult");
   tolua_function(tolua_S,"new",tolua_Physics_PhysicsRaycastResult_new00);
   tolua_function(tolua_S,"new_local",tolua_Physics_PhysicsRaycastResult_new00_local);
   tolua_function(tolua_S,".call",tolua_Physics_PhysicsRaycastResult_new00_local);
   tolua_variable(tolua_S,"position",tolua_get_PhysicsRaycastResult_position,tolua_set_PhysicsRaycastResult_position);
   tolua_variable(tolua_S,"normal",tolua_get_PhysicsRaycastResult_normal,tolua_set_PhysicsRaycastResult_normal);
   tolua_variable(tolua_S,"distance",tolua_get_PhysicsRaycastResult_distance,tolua_set_PhysicsRaycastResult_distance);
   tolua_variable(tolua_S,"body",tolua_get_PhysicsRaycastResult_body_ptr,tolua_set_PhysicsRaycastResult_body_ptr);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"DelayedWorldTransform","DelayedWorldTransform","",NULL);
  tolua_beginmodule(tolua_S,"DelayedWorldTransform");
   tolua_variable(tolua_S,"rigidBody",tolua_get_DelayedWorldTransform_rigidBody_ptr,tolua_set_DelayedWorldTransform_rigidBody_ptr);
   tolua_variable(tolua_S,"parentRigidBody",tolua_get_DelayedWorldTransform_parentRigidBody_ptr,tolua_set_DelayedWorldTransform_parentRigidBody_ptr);
   tolua_variable(tolua_S,"worldPosition",tolua_get_DelayedWorldTransform_worldPosition,tolua_set_DelayedWorldTransform_worldPosition);
   tolua_variable(tolua_S,"worldRotation",tolua_get_DelayedWorldTransform_worldRotation,tolua_set_DelayedWorldTransform_worldRotation);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"PhysicsWorld","PhysicsWorld","Component",NULL);
  tolua_beginmodule(tolua_S,"PhysicsWorld");
   tolua_function(tolua_S,"Update",tolua_Physics_PhysicsWorld_Update00);
   tolua_function(tolua_S,"UpdateCollisions",tolua_Physics_PhysicsWorld_UpdateCollisions00);
   tolua_function(tolua_S,"SetFps",tolua_Physics_PhysicsWorld_SetFps00);
   tolua_function(tolua_S,"SetGravity",tolua_Physics_PhysicsWorld_SetGravity00);
   tolua_function(tolua_S,"SetNumIterations",tolua_Physics_PhysicsWorld_SetNumIterations00);
   tolua_function(tolua_S,"SetInterpolation",tolua_Physics_PhysicsWorld_SetInterpolation00);
   tolua_function(tolua_S,"SetInternalEdge",tolua_Physics_PhysicsWorld_SetInternalEdge00);
   tolua_function(tolua_S,"SetSplitImpulse",tolua_Physics_PhysicsWorld_SetSplitImpulse00);
   tolua_function(tolua_S,"SetMaxNetworkAngularVelocity",tolua_Physics_PhysicsWorld_SetMaxNetworkAngularVelocity00);
   tolua_function(tolua_S,"RaycastSingle",tolua_Physics_PhysicsWorld_RaycastSingle00);
   tolua_function(tolua_S,"SphereCast",tolua_Physics_PhysicsWorld_SphereCast00);
   tolua_function(tolua_S,"GetGravity",tolua_Physics_PhysicsWorld_GetGravity00);
   tolua_function(tolua_S,"GetNumIterations",tolua_Physics_PhysicsWorld_GetNumIterations00);
   tolua_function(tolua_S,"GetInterpolation",tolua_Physics_PhysicsWorld_GetInterpolation00);
   tolua_function(tolua_S,"GetInternalEdge",tolua_Physics_PhysicsWorld_GetInternalEdge00);
   tolua_function(tolua_S,"GetSplitImpulse",tolua_Physics_PhysicsWorld_GetSplitImpulse00);
   tolua_function(tolua_S,"GetFps",tolua_Physics_PhysicsWorld_GetFps00);
   tolua_function(tolua_S,"GetMaxNetworkAngularVelocity",tolua_Physics_PhysicsWorld_GetMaxNetworkAngularVelocity00);
   tolua_function(tolua_S,"AddRigidBody",tolua_Physics_PhysicsWorld_AddRigidBody00);
   tolua_function(tolua_S,"RemoveRigidBody",tolua_Physics_PhysicsWorld_RemoveRigidBody00);
   tolua_function(tolua_S,"AddCollisionShape",tolua_Physics_PhysicsWorld_AddCollisionShape00);
   tolua_function(tolua_S,"RemoveCollisionShape",tolua_Physics_PhysicsWorld_RemoveCollisionShape00);
   tolua_function(tolua_S,"AddConstraint",tolua_Physics_PhysicsWorld_AddConstraint00);
   tolua_function(tolua_S,"RemoveConstraint",tolua_Physics_PhysicsWorld_RemoveConstraint00);
   tolua_function(tolua_S,"AddDelayedWorldTransform",tolua_Physics_PhysicsWorld_AddDelayedWorldTransform00);
   tolua_function(tolua_S,"DrawDebugGeometry",tolua_Physics_PhysicsWorld_DrawDebugGeometry00);
   tolua_function(tolua_S,"SetDebugRenderer",tolua_Physics_PhysicsWorld_SetDebugRenderer00);
   tolua_function(tolua_S,"SetDebugDepthTest",tolua_Physics_PhysicsWorld_SetDebugDepthTest00);
   tolua_function(tolua_S,"CleanupGeometryCache",tolua_Physics_PhysicsWorld_CleanupGeometryCache00);
   tolua_function(tolua_S,"SetApplyingTransforms",tolua_Physics_PhysicsWorld_SetApplyingTransforms00);
   tolua_function(tolua_S,"IsApplyingTransforms",tolua_Physics_PhysicsWorld_IsApplyingTransforms00);
  tolua_endmodule(tolua_S);
  tolua_function(tolua_S,"GetPhysicsWorld",tolua_Physics_GetPhysicsWorld00);
  tolua_constant(tolua_S,"COLLISION_NEVER",COLLISION_NEVER);
  tolua_constant(tolua_S,"COLLISION_ACTIVE",COLLISION_ACTIVE);
  tolua_constant(tolua_S,"COLLISION_ALWAYS",COLLISION_ALWAYS);
  tolua_cclass(tolua_S,"RigidBody","RigidBody","Component",NULL);
  tolua_beginmodule(tolua_S,"RigidBody");
   tolua_function(tolua_S,"SetMass",tolua_Physics_RigidBody_SetMass00);
   tolua_function(tolua_S,"SetPosition",tolua_Physics_RigidBody_SetPosition00);
   tolua_function(tolua_S,"SetRotation",tolua_Physics_RigidBody_SetRotation00);
   tolua_function(tolua_S,"SetTransform",tolua_Physics_RigidBody_SetTransform00);
   tolua_function(tolua_S,"SetLinearVelocity",tolua_Physics_RigidBody_SetLinearVelocity00);
   tolua_function(tolua_S,"SetLinearFactor",tolua_Physics_RigidBody_SetLinearFactor00);
   tolua_function(tolua_S,"SetLinearRestThreshold",tolua_Physics_RigidBody_SetLinearRestThreshold00);
   tolua_function(tolua_S,"SetLinearDamping",tolua_Physics_RigidBody_SetLinearDamping00);
   tolua_function(tolua_S,"SetAngularVelocity",tolua_Physics_RigidBody_SetAngularVelocity00);
   tolua_function(tolua_S,"SetAngularFactor",tolua_Physics_RigidBody_SetAngularFactor00);
   tolua_function(tolua_S,"SetAngularRestThreshold",tolua_Physics_RigidBody_SetAngularRestThreshold00);
   tolua_function(tolua_S,"SetAngularDamping",tolua_Physics_RigidBody_SetAngularDamping00);
   tolua_function(tolua_S,"SetFriction",tolua_Physics_RigidBody_SetFriction00);
   tolua_function(tolua_S,"SetRestitution",tolua_Physics_RigidBody_SetRestitution00);
   tolua_function(tolua_S,"SetContactProcessingThreshold",tolua_Physics_RigidBody_SetContactProcessingThreshold00);
   tolua_function(tolua_S,"SetCcdRadius",tolua_Physics_RigidBody_SetCcdRadius00);
   tolua_function(tolua_S,"SetCcdMotionThreshold",tolua_Physics_RigidBody_SetCcdMotionThreshold00);
   tolua_function(tolua_S,"SetUseGravity",tolua_Physics_RigidBody_SetUseGravity00);
   tolua_function(tolua_S,"SetGravityOverride",tolua_Physics_RigidBody_SetGravityOverride00);
   tolua_function(tolua_S,"SetKinematic",tolua_Physics_RigidBody_SetKinematic00);
   tolua_function(tolua_S,"SetPhantom",tolua_Physics_RigidBody_SetPhantom00);
   tolua_function(tolua_S,"SetCollisionLayer",tolua_Physics_RigidBody_SetCollisionLayer00);
   tolua_function(tolua_S,"SetCollisionMask",tolua_Physics_RigidBody_SetCollisionMask00);
   tolua_function(tolua_S,"SetCollisionLayerAndMask",tolua_Physics_RigidBody_SetCollisionLayerAndMask00);
   tolua_function(tolua_S,"SetCollisionEventMode",tolua_Physics_RigidBody_SetCollisionEventMode00);
   tolua_function(tolua_S,"ApplyForce",tolua_Physics_RigidBody_ApplyForce00);
   tolua_function(tolua_S,"ApplyForce",tolua_Physics_RigidBody_ApplyForce01);
   tolua_function(tolua_S,"ApplyTorque",tolua_Physics_RigidBody_ApplyTorque00);
   tolua_function(tolua_S,"ApplyImpulse",tolua_Physics_RigidBody_ApplyImpulse00);
   tolua_function(tolua_S,"ApplyImpulse",tolua_Physics_RigidBody_ApplyImpulse01);
   tolua_function(tolua_S,"ApplyTorqueImpulse",tolua_Physics_RigidBody_ApplyTorqueImpulse00);
   tolua_function(tolua_S,"ResetForces",tolua_Physics_RigidBody_ResetForces00);
   tolua_function(tolua_S,"Activate",tolua_Physics_RigidBody_Activate00);
   tolua_function(tolua_S,"ReAddBodyToWorld",tolua_Physics_RigidBody_ReAddBodyToWorld00);
   tolua_function(tolua_S,"GetPhysicsWorld",tolua_Physics_RigidBody_GetPhysicsWorld00);
   tolua_function(tolua_S,"GetMass",tolua_Physics_RigidBody_GetMass00);
   tolua_function(tolua_S,"GetPosition",tolua_Physics_RigidBody_GetPosition00);
   tolua_function(tolua_S,"GetRotation",tolua_Physics_RigidBody_GetRotation00);
   tolua_function(tolua_S,"GetLinearVelocity",tolua_Physics_RigidBody_GetLinearVelocity00);
   tolua_function(tolua_S,"GetLinearFactor",tolua_Physics_RigidBody_GetLinearFactor00);
   tolua_function(tolua_S,"GetVelocityAtPoint",tolua_Physics_RigidBody_GetVelocityAtPoint00);
   tolua_function(tolua_S,"GetLinearRestThreshold",tolua_Physics_RigidBody_GetLinearRestThreshold00);
   tolua_function(tolua_S,"GetLinearDamping",tolua_Physics_RigidBody_GetLinearDamping00);
   tolua_function(tolua_S,"GetAngularVelocity",tolua_Physics_RigidBody_GetAngularVelocity00);
   tolua_function(tolua_S,"GetAngularFactor",tolua_Physics_RigidBody_GetAngularFactor00);
   tolua_function(tolua_S,"GetAngularRestThreshold",tolua_Physics_RigidBody_GetAngularRestThreshold00);
   tolua_function(tolua_S,"GetAngularDamping",tolua_Physics_RigidBody_GetAngularDamping00);
   tolua_function(tolua_S,"GetFriction",tolua_Physics_RigidBody_GetFriction00);
   tolua_function(tolua_S,"GetRestitution",tolua_Physics_RigidBody_GetRestitution00);
   tolua_function(tolua_S,"GetContactProcessingThreshold",tolua_Physics_RigidBody_GetContactProcessingThreshold00);
   tolua_function(tolua_S,"GetCcdRadius",tolua_Physics_RigidBody_GetCcdRadius00);
   tolua_function(tolua_S,"GetCcdMotionThreshold",tolua_Physics_RigidBody_GetCcdMotionThreshold00);
   tolua_function(tolua_S,"GetUseGravity",tolua_Physics_RigidBody_GetUseGravity00);
   tolua_function(tolua_S,"GetGravityOverride",tolua_Physics_RigidBody_GetGravityOverride00);
   tolua_function(tolua_S,"GetCenterOfMass",tolua_Physics_RigidBody_GetCenterOfMass00);
   tolua_function(tolua_S,"IsKinematic",tolua_Physics_RigidBody_IsKinematic00);
   tolua_function(tolua_S,"IsPhantom",tolua_Physics_RigidBody_IsPhantom00);
   tolua_function(tolua_S,"IsActive",tolua_Physics_RigidBody_IsActive00);
   tolua_function(tolua_S,"GetCollisionLayer",tolua_Physics_RigidBody_GetCollisionLayer00);
   tolua_function(tolua_S,"GetCollisionMask",tolua_Physics_RigidBody_GetCollisionMask00);
   tolua_function(tolua_S,"GetCollisionEventMode",tolua_Physics_RigidBody_GetCollisionEventMode00);
   tolua_function(tolua_S,"ApplyWorldTransform",tolua_Physics_RigidBody_ApplyWorldTransform00);
   tolua_function(tolua_S,"UpdateMass",tolua_Physics_RigidBody_UpdateMass00);
   tolua_function(tolua_S,"UpdateGravity",tolua_Physics_RigidBody_UpdateGravity00);
   tolua_function(tolua_S,"AddConstraint",tolua_Physics_RigidBody_AddConstraint00);
   tolua_function(tolua_S,"RemoveConstraint",tolua_Physics_RigidBody_RemoveConstraint00);
   tolua_function(tolua_S,"ReleaseBody",tolua_Physics_RigidBody_ReleaseBody00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_Physics (lua_State* tolua_S) {
 return tolua_Physics_open(tolua_S);
};
#endif

