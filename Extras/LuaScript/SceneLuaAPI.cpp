/*
** Lua binding: Scene
** Generated automatically by tolua++-1.0.92 on 06/29/13 19:40:28.
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
TOLUA_API int  tolua_Scene_open (lua_State* tolua_S);

#define TOLUA_RELEASE
#include "SceneLuaAPI.h"
#include "Component.h"
#include "Node.h"
#include "Scene.h"
using namespace Urho3D;
#pragma warning(disable:4800)

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_Matrix3x4 (lua_State* tolua_S)
{
 Matrix3x4* self = (Matrix3x4*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_String (lua_State* tolua_S)
{
 String* self = (String*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_Quaternion (lua_State* tolua_S)
{
 Quaternion* self = (Quaternion*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_Vector3 (lua_State* tolua_S)
{
 Vector3* self = (Vector3*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}

static int tolua_collect_StringHash (lua_State* tolua_S)
{
 StringHash* self = (StringHash*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"Connection");
 tolua_usertype(tolua_S,"Quaternion");
 tolua_usertype(tolua_S,"Scene");
 tolua_usertype(tolua_S,"ShortStringHash");
 tolua_usertype(tolua_S,"StringHash");
 tolua_usertype(tolua_S,"Component");
 tolua_usertype(tolua_S,"Vector4");
 tolua_usertype(tolua_S,"Matrix3x4");
 tolua_usertype(tolua_S,"Variant");
 tolua_usertype(tolua_S,"String");
 tolua_usertype(tolua_S,"File");
 tolua_usertype(tolua_S,"Node");
 tolua_usertype(tolua_S,"Vector3");
}

/* method: SetEnabled of class  Component */
#ifndef TOLUA_DISABLE_tolua_Scene_Component_SetEnabled00
static int tolua_Scene_Component_SetEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Component",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Component* self = (Component*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetEnabled'", NULL);
#endif
  {
   self->SetEnabled(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Remove of class  Component */
#ifndef TOLUA_DISABLE_tolua_Scene_Component_Remove00
static int tolua_Scene_Component_Remove00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Component",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Component* self = (Component*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Remove'", NULL);
#endif
  {
   self->Remove();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Remove'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetID of class  Component */
#ifndef TOLUA_DISABLE_tolua_Scene_Component_GetID00
static int tolua_Scene_Component_GetID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Component",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Component* self = (const Component*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetID'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetID();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNode of class  Component */
#ifndef TOLUA_DISABLE_tolua_Scene_Component_GetNode00
static int tolua_Scene_Component_GetNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Component",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Component* self = (const Component*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNode'", NULL);
#endif
  {
   Node* tolua_ret = (Node*)  self->GetNode();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Node");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetScene of class  Component */
#ifndef TOLUA_DISABLE_tolua_Scene_Component_GetScene00
static int tolua_Scene_Component_GetScene00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Component",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Component* self = (const Component*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetScene'", NULL);
#endif
  {
   Scene* tolua_ret = (Scene*)  self->GetScene();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Scene");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetScene'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsEnabled of class  Component */
#ifndef TOLUA_DISABLE_tolua_Scene_Component_IsEnabled00
static int tolua_Scene_Component_IsEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Component",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Component* self = (const Component*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsEnabled'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsEnabled();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetName of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_SetName00
static int tolua_Scene_Node_SetName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
  const String* name = ((const String*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetName'", NULL);
#endif
  {
   self->SetName(*name);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetPosition of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_SetPosition00
static int tolua_Scene_Node_SetPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
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

/* method: SetRotation of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_SetRotation00
static int tolua_Scene_Node_SetRotation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Quaternion",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
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

/* method: SetDirection of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_SetDirection00
static int tolua_Scene_Node_SetDirection00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* direction = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetDirection'", NULL);
#endif
  {
   self->SetDirection(*direction);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetDirection'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetScale of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_SetScale00
static int tolua_Scene_Node_SetScale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
  float scale = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetScale'", NULL);
#endif
  {
   self->SetScale(scale);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetScale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetScale of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_SetScale01
static int tolua_Scene_Node_SetScale01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* scale = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetScale'", NULL);
#endif
  {
   self->SetScale(*scale);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Scene_Node_SetScale00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetTransform of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_SetTransform00
static int tolua_Scene_Node_SetTransform00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const Quaternion",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
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

/* method: SetTransform of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_SetTransform01
static int tolua_Scene_Node_SetTransform01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const Quaternion",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* position = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
  const Quaternion* rotation = ((const Quaternion*)  tolua_tousertype(tolua_S,3,0));
  float scale = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetTransform'", NULL);
#endif
  {
   self->SetTransform(*position,*rotation,scale);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Scene_Node_SetTransform00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetTransform of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_SetTransform02
static int tolua_Scene_Node_SetTransform02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const Quaternion",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* position = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
  const Quaternion* rotation = ((const Quaternion*)  tolua_tousertype(tolua_S,3,0));
  const Vector3* scale = ((const Vector3*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetTransform'", NULL);
#endif
  {
   self->SetTransform(*position,*rotation,*scale);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Scene_Node_SetTransform01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetWorldPosition of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_SetWorldPosition00
static int tolua_Scene_Node_SetWorldPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
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

/* method: SetWorldRotation of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_SetWorldRotation00
static int tolua_Scene_Node_SetWorldRotation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Quaternion",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
  const Quaternion* rotation = ((const Quaternion*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetWorldRotation'", NULL);
#endif
  {
   self->SetWorldRotation(*rotation);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetWorldRotation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetWorldDirection of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_SetWorldDirection00
static int tolua_Scene_Node_SetWorldDirection00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* direction = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetWorldDirection'", NULL);
#endif
  {
   self->SetWorldDirection(*direction);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetWorldDirection'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetWorldScale of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_SetWorldScale00
static int tolua_Scene_Node_SetWorldScale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
  float scale = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetWorldScale'", NULL);
#endif
  {
   self->SetWorldScale(scale);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetWorldScale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetWorldScale of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_SetWorldScale01
static int tolua_Scene_Node_SetWorldScale01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* scale = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetWorldScale'", NULL);
#endif
  {
   self->SetWorldScale(*scale);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Scene_Node_SetWorldScale00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetWorldTransform of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_SetWorldTransform00
static int tolua_Scene_Node_SetWorldTransform00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const Quaternion",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* position = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
  const Quaternion* rotation = ((const Quaternion*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetWorldTransform'", NULL);
#endif
  {
   self->SetWorldTransform(*position,*rotation);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetWorldTransform'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetWorldTransform of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_SetWorldTransform01
static int tolua_Scene_Node_SetWorldTransform01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const Quaternion",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* position = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
  const Quaternion* rotation = ((const Quaternion*)  tolua_tousertype(tolua_S,3,0));
  float scale = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetWorldTransform'", NULL);
#endif
  {
   self->SetWorldTransform(*position,*rotation,scale);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Scene_Node_SetWorldTransform00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetWorldTransform of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_SetWorldTransform02
static int tolua_Scene_Node_SetWorldTransform02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const Quaternion",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* position = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
  const Quaternion* rotation = ((const Quaternion*)  tolua_tousertype(tolua_S,3,0));
  const Vector3* scale = ((const Vector3*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetWorldTransform'", NULL);
#endif
  {
   self->SetWorldTransform(*position,*rotation,*scale);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Scene_Node_SetWorldTransform01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: Translate of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_Translate00
static int tolua_Scene_Node_Translate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* delta = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Translate'", NULL);
#endif
  {
   self->Translate(*delta);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Translate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: TranslateRelative of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_TranslateRelative00
static int tolua_Scene_Node_TranslateRelative00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* delta = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'TranslateRelative'", NULL);
#endif
  {
   self->TranslateRelative(*delta);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'TranslateRelative'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Rotate of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_Rotate00
static int tolua_Scene_Node_Rotate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Quaternion",0,&tolua_err)) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
  const Quaternion* delta = ((const Quaternion*)  tolua_tousertype(tolua_S,2,0));
  bool fixedAxis = ((bool)  tolua_toboolean(tolua_S,3,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Rotate'", NULL);
#endif
  {
   self->Rotate(*delta,fixedAxis);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Rotate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Pitch of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_Pitch00
static int tolua_Scene_Node_Pitch00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
  float angle = ((float)  tolua_tonumber(tolua_S,2,0));
  bool fixedAxis = ((bool)  tolua_toboolean(tolua_S,3,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Pitch'", NULL);
#endif
  {
   self->Pitch(angle,fixedAxis);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Pitch'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Yaw of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_Yaw00
static int tolua_Scene_Node_Yaw00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
  float angle = ((float)  tolua_tonumber(tolua_S,2,0));
  bool fixedAxis = ((bool)  tolua_toboolean(tolua_S,3,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Yaw'", NULL);
#endif
  {
   self->Yaw(angle,fixedAxis);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Yaw'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Roll of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_Roll00
static int tolua_Scene_Node_Roll00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
  float angle = ((float)  tolua_tonumber(tolua_S,2,0));
  bool fixedAxis = ((bool)  tolua_toboolean(tolua_S,3,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Roll'", NULL);
#endif
  {
   self->Roll(angle,fixedAxis);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Roll'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LookAt of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_LookAt00
static int tolua_Scene_Node_LookAt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* target = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LookAt'", NULL);
#endif
  {
   self->LookAt(*target);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LookAt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LookAt of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_LookAt01
static int tolua_Scene_Node_LookAt01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* target = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
  const Vector3* upAxis = ((const Vector3*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LookAt'", NULL);
#endif
  {
   self->LookAt(*target,*upAxis);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Scene_Node_LookAt00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: Scale of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_Scale00
static int tolua_Scene_Node_Scale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
  float scale = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Scale'", NULL);
#endif
  {
   self->Scale(scale);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Scale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Scale of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_Scale01
static int tolua_Scene_Node_Scale01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* scale = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Scale'", NULL);
#endif
  {
   self->Scale(*scale);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Scene_Node_Scale00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetEnabled of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_SetEnabled00
static int tolua_Scene_Node_SetEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetEnabled'", NULL);
#endif
  {
   self->SetEnabled(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetEnabled of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_SetEnabled01
static int tolua_Scene_Node_SetEnabled01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
  bool recursive = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetEnabled'", NULL);
#endif
  {
   self->SetEnabled(enable,recursive);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Scene_Node_SetEnabled00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetOwner of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_SetOwner00
static int tolua_Scene_Node_SetOwner00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Connection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
  Connection* owner = ((Connection*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetOwner'", NULL);
#endif
  {
   self->SetOwner(owner);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetOwner'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: MarkDirty of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_MarkDirty00
static int tolua_Scene_Node_MarkDirty00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'MarkDirty'", NULL);
#endif
  {
   self->MarkDirty();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MarkDirty'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CreateChild of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_CreateChild00
static int tolua_Scene_Node_CreateChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CreateChild'", NULL);
#endif
  {
   Node* tolua_ret = (Node*)  self->CreateChild();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Node");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CreateChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CreateChild of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_CreateChild01
static int tolua_Scene_Node_CreateChild01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
  const String* name = ((const String*)  tolua_tousertype(tolua_S,2,0));
  CreateMode mode = ((CreateMode) (int)  tolua_tonumber(tolua_S,3,REPLICATED));
  unsigned id = ((unsigned)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CreateChild'", NULL);
#endif
  {
   Node* tolua_ret = (Node*)  self->CreateChild(*name,mode,id);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Node");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Scene_Node_CreateChild00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddChild of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_AddChild00
static int tolua_Scene_Node_AddChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Node",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
  Node* node = ((Node*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddChild'", NULL);
#endif
  {
   self->AddChild(node);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveChild of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_RemoveChild00
static int tolua_Scene_Node_RemoveChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Node",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
  Node* node = ((Node*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveChild'", NULL);
#endif
  {
   self->RemoveChild(node);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemoveChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveAllChildren of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_RemoveAllChildren00
static int tolua_Scene_Node_RemoveAllChildren00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveAllChildren'", NULL);
#endif
  {
   self->RemoveAllChildren();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemoveAllChildren'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CreateComponent of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_CreateComponent00
static int tolua_Scene_Node_CreateComponent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"ShortStringHash",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
  ShortStringHash type = *((ShortStringHash*)  tolua_tousertype(tolua_S,2,0));
  CreateMode mode = ((CreateMode) (int)  tolua_tonumber(tolua_S,3,REPLICATED));
  unsigned id = ((unsigned)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CreateComponent'", NULL);
#endif
  {
   Component* tolua_ret = (Component*)  self->CreateComponent(type,mode,id);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Component");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CreateComponent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetOrCreateComponent of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_GetOrCreateComponent00
static int tolua_Scene_Node_GetOrCreateComponent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"ShortStringHash",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
  ShortStringHash type = *((ShortStringHash*)  tolua_tousertype(tolua_S,2,0));
  CreateMode mode = ((CreateMode) (int)  tolua_tonumber(tolua_S,3,REPLICATED));
  unsigned id = ((unsigned)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetOrCreateComponent'", NULL);
#endif
  {
   Component* tolua_ret = (Component*)  self->GetOrCreateComponent(type,mode,id);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Component");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetOrCreateComponent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveComponent of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_RemoveComponent00
static int tolua_Scene_Node_RemoveComponent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Component",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
  Component* component = ((Component*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveComponent'", NULL);
#endif
  {
   self->RemoveComponent(component);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemoveComponent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveComponent of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_RemoveComponent01
static int tolua_Scene_Node_RemoveComponent01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"ShortStringHash",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
  ShortStringHash type = *((ShortStringHash*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveComponent'", NULL);
#endif
  {
   self->RemoveComponent(type);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Scene_Node_RemoveComponent00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveAllComponents of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_RemoveAllComponents00
static int tolua_Scene_Node_RemoveAllComponents00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveAllComponents'", NULL);
#endif
  {
   self->RemoveAllComponents();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemoveAllComponents'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Clone of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_Clone00
static int tolua_Scene_Node_Clone00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
  CreateMode mode = ((CreateMode) (int)  tolua_tonumber(tolua_S,2,REPLICATED));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Clone'", NULL);
#endif
  {
   Node* tolua_ret = (Node*)  self->Clone(mode);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Node");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Clone'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Remove of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_Remove00
static int tolua_Scene_Node_Remove00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Remove'", NULL);
#endif
  {
   self->Remove();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Remove'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetParent of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_SetParent00
static int tolua_Scene_Node_SetParent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Node",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
  Node* parent = ((Node*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetParent'", NULL);
#endif
  {
   self->SetParent(parent);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetParent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetVar of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_SetVar00
static int tolua_Scene_Node_SetVar00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"ShortStringHash",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const Variant",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
  ShortStringHash key = *((ShortStringHash*)  tolua_tousertype(tolua_S,2,0));
  const Variant* value = ((const Variant*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetVar'", NULL);
#endif
  {
   self->SetVar(key,*value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetVar'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddListener of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_AddListener00
static int tolua_Scene_Node_AddListener00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Component",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
  Component* component = ((Component*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddListener'", NULL);
#endif
  {
   self->AddListener(component);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddListener'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveListener of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_RemoveListener00
static int tolua_Scene_Node_RemoveListener00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Node",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Component",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Node* self = (Node*)  tolua_tousertype(tolua_S,1,0);
  Component* component = ((Component*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveListener'", NULL);
#endif
  {
   self->RemoveListener(component);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemoveListener'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetID of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_GetID00
static int tolua_Scene_Node_GetID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Node",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Node* self = (const Node*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetID'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetID();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetName of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_GetName00
static int tolua_Scene_Node_GetName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Node",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Node* self = (const Node*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetName'", NULL);
#endif
  {
   const String& tolua_ret = (const String&)  self->GetName();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const String");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNameHash of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_GetNameHash00
static int tolua_Scene_Node_GetNameHash00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Node",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Node* self = (const Node*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNameHash'", NULL);
#endif
  {
   StringHash tolua_ret = (StringHash)  self->GetNameHash();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((StringHash)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"StringHash");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(StringHash));
     tolua_pushusertype(tolua_S,tolua_obj,"StringHash");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNameHash'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetParent of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_GetParent00
static int tolua_Scene_Node_GetParent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Node",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Node* self = (const Node*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetParent'", NULL);
#endif
  {
   Node* tolua_ret = (Node*)  self->GetParent();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Node");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetParent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetScene of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_GetScene00
static int tolua_Scene_Node_GetScene00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Node",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Node* self = (const Node*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetScene'", NULL);
#endif
  {
   Scene* tolua_ret = (Scene*)  self->GetScene();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Scene");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetScene'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsEnabled of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_IsEnabled00
static int tolua_Scene_Node_IsEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Node",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Node* self = (const Node*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsEnabled'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsEnabled();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetOwner of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_GetOwner00
static int tolua_Scene_Node_GetOwner00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Node",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Node* self = (const Node*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetOwner'", NULL);
#endif
  {
   Connection* tolua_ret = (Connection*)  self->GetOwner();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Connection");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetOwner'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetPosition of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_GetPosition00
static int tolua_Scene_Node_GetPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Node",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Node* self = (const Node*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetRotation of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_GetRotation00
static int tolua_Scene_Node_GetRotation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Node",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Node* self = (const Node*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetDirection of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_GetDirection00
static int tolua_Scene_Node_GetDirection00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Node",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Node* self = (const Node*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetDirection'", NULL);
#endif
  {
   Vector3 tolua_ret = (Vector3)  self->GetDirection();
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
 tolua_error(tolua_S,"#ferror in function 'GetDirection'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetScale of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_GetScale00
static int tolua_Scene_Node_GetScale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Node",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Node* self = (const Node*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetScale'", NULL);
#endif
  {
   const Vector3& tolua_ret = (const Vector3&)  self->GetScale();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Vector3");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetScale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTransform of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_GetTransform00
static int tolua_Scene_Node_GetTransform00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Node",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Node* self = (const Node*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTransform'", NULL);
#endif
  {
   Matrix3x4 tolua_ret = (Matrix3x4)  self->GetTransform();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((Matrix3x4)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"Matrix3x4");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Matrix3x4));
     tolua_pushusertype(tolua_S,tolua_obj,"Matrix3x4");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTransform'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetWorldPosition of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_GetWorldPosition00
static int tolua_Scene_Node_GetWorldPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Node",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Node* self = (const Node*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetWorldRotation of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_GetWorldRotation00
static int tolua_Scene_Node_GetWorldRotation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Node",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Node* self = (const Node*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetWorldRotation'", NULL);
#endif
  {
   Quaternion tolua_ret = (Quaternion)  self->GetWorldRotation();
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
 tolua_error(tolua_S,"#ferror in function 'GetWorldRotation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetWorldDirection of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_GetWorldDirection00
static int tolua_Scene_Node_GetWorldDirection00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Node",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Node* self = (const Node*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetWorldDirection'", NULL);
#endif
  {
   Vector3 tolua_ret = (Vector3)  self->GetWorldDirection();
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
 tolua_error(tolua_S,"#ferror in function 'GetWorldDirection'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetWorldScale of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_GetWorldScale00
static int tolua_Scene_Node_GetWorldScale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Node",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Node* self = (const Node*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetWorldScale'", NULL);
#endif
  {
   Vector3 tolua_ret = (Vector3)  self->GetWorldScale();
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
 tolua_error(tolua_S,"#ferror in function 'GetWorldScale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetWorldTransform of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_GetWorldTransform00
static int tolua_Scene_Node_GetWorldTransform00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Node",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Node* self = (const Node*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetWorldTransform'", NULL);
#endif
  {
   const Matrix3x4& tolua_ret = (const Matrix3x4&)  self->GetWorldTransform();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Matrix3x4");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetWorldTransform'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LocalToWorld of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_LocalToWorld00
static int tolua_Scene_Node_LocalToWorld00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Node",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Node* self = (const Node*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* position = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LocalToWorld'", NULL);
#endif
  {
   Vector3 tolua_ret = (Vector3)  self->LocalToWorld(*position);
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
 tolua_error(tolua_S,"#ferror in function 'LocalToWorld'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LocalToWorld of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_LocalToWorld01
static int tolua_Scene_Node_LocalToWorld01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Node",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector4",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const Node* self = (const Node*)  tolua_tousertype(tolua_S,1,0);
  const Vector4* vector = ((const Vector4*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LocalToWorld'", NULL);
#endif
  {
   Vector3 tolua_ret = (Vector3)  self->LocalToWorld(*vector);
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
 return tolua_Scene_Node_LocalToWorld00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: WorldToLocal of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_WorldToLocal00
static int tolua_Scene_Node_WorldToLocal00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Node",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Node* self = (const Node*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* position = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'WorldToLocal'", NULL);
#endif
  {
   Vector3 tolua_ret = (Vector3)  self->WorldToLocal(*position);
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
 tolua_error(tolua_S,"#ferror in function 'WorldToLocal'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: WorldToLocal of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_WorldToLocal01
static int tolua_Scene_Node_WorldToLocal01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Node",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector4",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const Node* self = (const Node*)  tolua_tousertype(tolua_S,1,0);
  const Vector4* vector = ((const Vector4*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'WorldToLocal'", NULL);
#endif
  {
   Vector3 tolua_ret = (Vector3)  self->WorldToLocal(*vector);
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
 return tolua_Scene_Node_WorldToLocal00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsDirty of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_IsDirty00
static int tolua_Scene_Node_IsDirty00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Node",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Node* self = (const Node*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsDirty'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsDirty();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsDirty'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNumChildren of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_GetNumChildren00
static int tolua_Scene_Node_GetNumChildren00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Node",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Node* self = (const Node*)  tolua_tousertype(tolua_S,1,0);
  bool recursive = ((bool)  tolua_toboolean(tolua_S,2,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNumChildren'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetNumChildren(recursive);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNumChildren'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetChild of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_GetChild00
static int tolua_Scene_Node_GetChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Node",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Node* self = (const Node*)  tolua_tousertype(tolua_S,1,0);
  unsigned index = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetChild'", NULL);
#endif
  {
   Node* tolua_ret = (Node*)  self->GetChild(index);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Node");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetChild of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_GetChild01
static int tolua_Scene_Node_GetChild01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Node",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const Node* self = (const Node*)  tolua_tousertype(tolua_S,1,0);
  const String* name = ((const String*)  tolua_tousertype(tolua_S,2,0));
  bool recursive = ((bool)  tolua_toboolean(tolua_S,3,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetChild'", NULL);
#endif
  {
   Node* tolua_ret = (Node*)  self->GetChild(*name,recursive);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Node");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Scene_Node_GetChild00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetChild of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_GetChild02
static int tolua_Scene_Node_GetChild02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Node",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const Node* self = (const Node*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
  bool recursive = ((bool)  tolua_toboolean(tolua_S,3,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetChild'", NULL);
#endif
  {
   Node* tolua_ret = (Node*)  self->GetChild(name,recursive);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Node");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Scene_Node_GetChild01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetChild of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_GetChild03
static int tolua_Scene_Node_GetChild03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Node",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"StringHash",0,&tolua_err)) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const Node* self = (const Node*)  tolua_tousertype(tolua_S,1,0);
  StringHash nameHash = *((StringHash*)  tolua_tousertype(tolua_S,2,0));
  bool recursive = ((bool)  tolua_toboolean(tolua_S,3,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetChild'", NULL);
#endif
  {
   Node* tolua_ret = (Node*)  self->GetChild(nameHash,recursive);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Node");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Scene_Node_GetChild02(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNumComponents of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_GetNumComponents00
static int tolua_Scene_Node_GetNumComponents00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Node",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Node* self = (const Node*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNumComponents'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetNumComponents();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNumComponents'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNumNetworkComponents of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_GetNumNetworkComponents00
static int tolua_Scene_Node_GetNumNetworkComponents00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Node",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Node* self = (const Node*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNumNetworkComponents'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetNumNetworkComponents();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNumNetworkComponents'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetComponent of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_GetComponent00
static int tolua_Scene_Node_GetComponent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Node",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"ShortStringHash",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Node* self = (const Node*)  tolua_tousertype(tolua_S,1,0);
  ShortStringHash type = *((ShortStringHash*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetComponent'", NULL);
#endif
  {
   Component* tolua_ret = (Component*)  self->GetComponent(type);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Component");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetComponent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: HasComponent of class  Node */
#ifndef TOLUA_DISABLE_tolua_Scene_Node_HasComponent00
static int tolua_Scene_Node_HasComponent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Node",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"ShortStringHash",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Node* self = (const Node*)  tolua_tousertype(tolua_S,1,0);
  ShortStringHash type = *((ShortStringHash*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'HasComponent'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->HasComponent(type);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'HasComponent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: FIRST_REPLICATED_ID */
#ifndef TOLUA_DISABLE_tolua_get_FIRST_REPLICATED_ID
static int tolua_get_FIRST_REPLICATED_ID(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)FIRST_REPLICATED_ID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: LAST_REPLICATED_ID */
#ifndef TOLUA_DISABLE_tolua_get_LAST_REPLICATED_ID
static int tolua_get_LAST_REPLICATED_ID(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)LAST_REPLICATED_ID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: FIRST_LOCAL_ID */
#ifndef TOLUA_DISABLE_tolua_get_FIRST_LOCAL_ID
static int tolua_get_FIRST_LOCAL_ID(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)FIRST_LOCAL_ID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: LAST_LOCAL_ID */
#ifndef TOLUA_DISABLE_tolua_get_LAST_LOCAL_ID
static int tolua_get_LAST_LOCAL_ID(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)LAST_LOCAL_ID);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: LoadAsync of class  Scene */
#ifndef TOLUA_DISABLE_tolua_Scene_Scene_LoadAsync00
static int tolua_Scene_Scene_LoadAsync00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Scene",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"File",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Scene* self = (Scene*)  tolua_tousertype(tolua_S,1,0);
  File* file = ((File*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LoadAsync'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->LoadAsync(file);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LoadAsync'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LoadAsyncXML of class  Scene */
#ifndef TOLUA_DISABLE_tolua_Scene_Scene_LoadAsyncXML00
static int tolua_Scene_Scene_LoadAsyncXML00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Scene",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"File",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Scene* self = (Scene*)  tolua_tousertype(tolua_S,1,0);
  File* file = ((File*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LoadAsyncXML'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->LoadAsyncXML(file);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LoadAsyncXML'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: StopAsyncLoading of class  Scene */
#ifndef TOLUA_DISABLE_tolua_Scene_Scene_StopAsyncLoading00
static int tolua_Scene_Scene_StopAsyncLoading00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Scene",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Scene* self = (Scene*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'StopAsyncLoading'", NULL);
#endif
  {
   self->StopAsyncLoading();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'StopAsyncLoading'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Clear of class  Scene */
#ifndef TOLUA_DISABLE_tolua_Scene_Scene_Clear00
static int tolua_Scene_Scene_Clear00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Scene",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Scene* self = (Scene*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Clear'", NULL);
#endif
  {
   self->Clear();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Clear'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetUpdateEnabled of class  Scene */
#ifndef TOLUA_DISABLE_tolua_Scene_Scene_SetUpdateEnabled00
static int tolua_Scene_Scene_SetUpdateEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Scene",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Scene* self = (Scene*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetUpdateEnabled'", NULL);
#endif
  {
   self->SetUpdateEnabled(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetUpdateEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetTimeScale of class  Scene */
#ifndef TOLUA_DISABLE_tolua_Scene_Scene_SetTimeScale00
static int tolua_Scene_Scene_SetTimeScale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Scene",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Scene* self = (Scene*)  tolua_tousertype(tolua_S,1,0);
  float scale = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetTimeScale'", NULL);
#endif
  {
   self->SetTimeScale(scale);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetTimeScale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetElapsedTime of class  Scene */
#ifndef TOLUA_DISABLE_tolua_Scene_Scene_SetElapsedTime00
static int tolua_Scene_Scene_SetElapsedTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Scene",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Scene* self = (Scene*)  tolua_tousertype(tolua_S,1,0);
  float time = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetElapsedTime'", NULL);
#endif
  {
   self->SetElapsedTime(time);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetElapsedTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetSmoothingConstant of class  Scene */
#ifndef TOLUA_DISABLE_tolua_Scene_Scene_SetSmoothingConstant00
static int tolua_Scene_Scene_SetSmoothingConstant00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Scene",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Scene* self = (Scene*)  tolua_tousertype(tolua_S,1,0);
  float constant = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetSmoothingConstant'", NULL);
#endif
  {
   self->SetSmoothingConstant(constant);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetSmoothingConstant'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetSnapThreshold of class  Scene */
#ifndef TOLUA_DISABLE_tolua_Scene_Scene_SetSnapThreshold00
static int tolua_Scene_Scene_SetSnapThreshold00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Scene",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Scene* self = (Scene*)  tolua_tousertype(tolua_S,1,0);
  float threshold = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetSnapThreshold'", NULL);
#endif
  {
   self->SetSnapThreshold(threshold);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetSnapThreshold'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNode of class  Scene */
#ifndef TOLUA_DISABLE_tolua_Scene_Scene_GetNode00
static int tolua_Scene_Scene_GetNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Scene",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Scene* self = (const Scene*)  tolua_tousertype(tolua_S,1,0);
  unsigned id = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNode'", NULL);
#endif
  {
   Node* tolua_ret = (Node*)  self->GetNode(id);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Node");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetComponent of class  Scene */
#ifndef TOLUA_DISABLE_tolua_Scene_Scene_GetComponent00
static int tolua_Scene_Scene_GetComponent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Scene",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Scene* self = (const Scene*)  tolua_tousertype(tolua_S,1,0);
  unsigned id = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetComponent'", NULL);
#endif
  {
   Component* tolua_ret = (Component*)  self->GetComponent(id);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Component");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetComponent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsUpdateEnabled of class  Scene */
#ifndef TOLUA_DISABLE_tolua_Scene_Scene_IsUpdateEnabled00
static int tolua_Scene_Scene_IsUpdateEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Scene",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Scene* self = (const Scene*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsUpdateEnabled'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsUpdateEnabled();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsUpdateEnabled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsAsyncLoading of class  Scene */
#ifndef TOLUA_DISABLE_tolua_Scene_Scene_IsAsyncLoading00
static int tolua_Scene_Scene_IsAsyncLoading00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Scene",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Scene* self = (const Scene*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsAsyncLoading'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsAsyncLoading();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsAsyncLoading'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAsyncProgress of class  Scene */
#ifndef TOLUA_DISABLE_tolua_Scene_Scene_GetAsyncProgress00
static int tolua_Scene_Scene_GetAsyncProgress00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Scene",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Scene* self = (const Scene*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAsyncProgress'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetAsyncProgress();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAsyncProgress'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFileName of class  Scene */
#ifndef TOLUA_DISABLE_tolua_Scene_Scene_GetFileName00
static int tolua_Scene_Scene_GetFileName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Scene",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Scene* self = (const Scene*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFileName'", NULL);
#endif
  {
   const String& tolua_ret = (const String&)  self->GetFileName();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const String");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFileName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetChecksum of class  Scene */
#ifndef TOLUA_DISABLE_tolua_Scene_Scene_GetChecksum00
static int tolua_Scene_Scene_GetChecksum00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Scene",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Scene* self = (const Scene*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetChecksum'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetChecksum();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetChecksum'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTimeScale of class  Scene */
#ifndef TOLUA_DISABLE_tolua_Scene_Scene_GetTimeScale00
static int tolua_Scene_Scene_GetTimeScale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Scene",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Scene* self = (const Scene*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTimeScale'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetTimeScale();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTimeScale'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetElapsedTime of class  Scene */
#ifndef TOLUA_DISABLE_tolua_Scene_Scene_GetElapsedTime00
static int tolua_Scene_Scene_GetElapsedTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Scene",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Scene* self = (const Scene*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetElapsedTime'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetElapsedTime();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetElapsedTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSmoothingConstant of class  Scene */
#ifndef TOLUA_DISABLE_tolua_Scene_Scene_GetSmoothingConstant00
static int tolua_Scene_Scene_GetSmoothingConstant00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Scene",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Scene* self = (const Scene*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSmoothingConstant'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetSmoothingConstant();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSmoothingConstant'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSnapThreshold of class  Scene */
#ifndef TOLUA_DISABLE_tolua_Scene_Scene_GetSnapThreshold00
static int tolua_Scene_Scene_GetSnapThreshold00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Scene",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Scene* self = (const Scene*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSnapThreshold'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetSnapThreshold();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSnapThreshold'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetVarName of class  Scene */
#ifndef TOLUA_DISABLE_tolua_Scene_Scene_GetVarName00
static int tolua_Scene_Scene_GetVarName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Scene",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"ShortStringHash",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Scene* self = (const Scene*)  tolua_tousertype(tolua_S,1,0);
  ShortStringHash hash = *((ShortStringHash*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetVarName'", NULL);
#endif
  {
   const String& tolua_ret = (const String&)  self->GetVarName(hash);
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const String");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetVarName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Update of class  Scene */
#ifndef TOLUA_DISABLE_tolua_Scene_Scene_Update00
static int tolua_Scene_Scene_Update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Scene",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Scene* self = (Scene*)  tolua_tousertype(tolua_S,1,0);
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

/* method: BeginThreadedUpdate of class  Scene */
#ifndef TOLUA_DISABLE_tolua_Scene_Scene_BeginThreadedUpdate00
static int tolua_Scene_Scene_BeginThreadedUpdate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Scene",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Scene* self = (Scene*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'BeginThreadedUpdate'", NULL);
#endif
  {
   self->BeginThreadedUpdate();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'BeginThreadedUpdate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: EndThreadedUpdate of class  Scene */
#ifndef TOLUA_DISABLE_tolua_Scene_Scene_EndThreadedUpdate00
static int tolua_Scene_Scene_EndThreadedUpdate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Scene",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Scene* self = (Scene*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'EndThreadedUpdate'", NULL);
#endif
  {
   self->EndThreadedUpdate();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'EndThreadedUpdate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DelayedMarkedDirty of class  Scene */
#ifndef TOLUA_DISABLE_tolua_Scene_Scene_DelayedMarkedDirty00
static int tolua_Scene_Scene_DelayedMarkedDirty00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Scene",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Component",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Scene* self = (Scene*)  tolua_tousertype(tolua_S,1,0);
  Component* component = ((Component*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DelayedMarkedDirty'", NULL);
#endif
  {
   self->DelayedMarkedDirty(component);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DelayedMarkedDirty'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsThreadedUpdate of class  Scene */
#ifndef TOLUA_DISABLE_tolua_Scene_Scene_IsThreadedUpdate00
static int tolua_Scene_Scene_IsThreadedUpdate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Scene",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Scene* self = (const Scene*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsThreadedUpdate'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsThreadedUpdate();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsThreadedUpdate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFreeNodeID of class  Scene */
#ifndef TOLUA_DISABLE_tolua_Scene_Scene_GetFreeNodeID00
static int tolua_Scene_Scene_GetFreeNodeID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Scene",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Scene* self = (Scene*)  tolua_tousertype(tolua_S,1,0);
  CreateMode mode = ((CreateMode) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFreeNodeID'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetFreeNodeID(mode);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFreeNodeID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFreeComponentID of class  Scene */
#ifndef TOLUA_DISABLE_tolua_Scene_Scene_GetFreeComponentID00
static int tolua_Scene_Scene_GetFreeComponentID00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Scene",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Scene* self = (Scene*)  tolua_tousertype(tolua_S,1,0);
  CreateMode mode = ((CreateMode) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFreeComponentID'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetFreeComponentID(mode);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFreeComponentID'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: NodeAdded of class  Scene */
#ifndef TOLUA_DISABLE_tolua_Scene_Scene_NodeAdded00
static int tolua_Scene_Scene_NodeAdded00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Scene",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Node",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Scene* self = (Scene*)  tolua_tousertype(tolua_S,1,0);
  Node* node = ((Node*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'NodeAdded'", NULL);
#endif
  {
   self->NodeAdded(node);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NodeAdded'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: NodeRemoved of class  Scene */
#ifndef TOLUA_DISABLE_tolua_Scene_Scene_NodeRemoved00
static int tolua_Scene_Scene_NodeRemoved00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Scene",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Node",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Scene* self = (Scene*)  tolua_tousertype(tolua_S,1,0);
  Node* node = ((Node*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'NodeRemoved'", NULL);
#endif
  {
   self->NodeRemoved(node);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NodeRemoved'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ComponentAdded of class  Scene */
#ifndef TOLUA_DISABLE_tolua_Scene_Scene_ComponentAdded00
static int tolua_Scene_Scene_ComponentAdded00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Scene",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Component",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Scene* self = (Scene*)  tolua_tousertype(tolua_S,1,0);
  Component* component = ((Component*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ComponentAdded'", NULL);
#endif
  {
   self->ComponentAdded(component);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ComponentAdded'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ComponentRemoved of class  Scene */
#ifndef TOLUA_DISABLE_tolua_Scene_Scene_ComponentRemoved00
static int tolua_Scene_Scene_ComponentRemoved00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Scene",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Component",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Scene* self = (Scene*)  tolua_tousertype(tolua_S,1,0);
  Component* component = ((Component*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ComponentRemoved'", NULL);
#endif
  {
   self->ComponentRemoved(component);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ComponentRemoved'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetVarNamesAttr of class  Scene */
#ifndef TOLUA_DISABLE_tolua_Scene_Scene_SetVarNamesAttr00
static int tolua_Scene_Scene_SetVarNamesAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Scene",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Scene* self = (Scene*)  tolua_tousertype(tolua_S,1,0);
  String value = *((String*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetVarNamesAttr'", NULL);
#endif
  {
   self->SetVarNamesAttr(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetVarNamesAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetVarNamesAttr of class  Scene */
#ifndef TOLUA_DISABLE_tolua_Scene_Scene_GetVarNamesAttr00
static int tolua_Scene_Scene_GetVarNamesAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Scene",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Scene* self = (const Scene*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetVarNamesAttr'", NULL);
#endif
  {
   String tolua_ret = (String)  self->GetVarNamesAttr();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((String)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"String");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(String));
     tolua_pushusertype(tolua_S,tolua_obj,"String");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetVarNamesAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: PrepareNetworkUpdate of class  Scene */
#ifndef TOLUA_DISABLE_tolua_Scene_Scene_PrepareNetworkUpdate00
static int tolua_Scene_Scene_PrepareNetworkUpdate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Scene",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Scene* self = (Scene*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'PrepareNetworkUpdate'", NULL);
#endif
  {
   self->PrepareNetworkUpdate();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'PrepareNetworkUpdate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CleanupConnection of class  Scene */
#ifndef TOLUA_DISABLE_tolua_Scene_Scene_CleanupConnection00
static int tolua_Scene_Scene_CleanupConnection00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Scene",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Connection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Scene* self = (Scene*)  tolua_tousertype(tolua_S,1,0);
  Connection* connection = ((Connection*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CleanupConnection'", NULL);
#endif
  {
   self->CleanupConnection(connection);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CleanupConnection'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: MarkNetworkUpdate of class  Scene */
#ifndef TOLUA_DISABLE_tolua_Scene_Scene_MarkNetworkUpdate00
static int tolua_Scene_Scene_MarkNetworkUpdate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Scene",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Node",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Scene* self = (Scene*)  tolua_tousertype(tolua_S,1,0);
  Node* node = ((Node*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'MarkNetworkUpdate'", NULL);
#endif
  {
   self->MarkNetworkUpdate(node);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MarkNetworkUpdate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: MarkNetworkUpdate of class  Scene */
#ifndef TOLUA_DISABLE_tolua_Scene_Scene_MarkNetworkUpdate01
static int tolua_Scene_Scene_MarkNetworkUpdate01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Scene",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Component",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Scene* self = (Scene*)  tolua_tousertype(tolua_S,1,0);
  Component* component = ((Component*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'MarkNetworkUpdate'", NULL);
#endif
  {
   self->MarkNetworkUpdate(component);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Scene_Scene_MarkNetworkUpdate00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: MarkReplicationDirty of class  Scene */
#ifndef TOLUA_DISABLE_tolua_Scene_Scene_MarkReplicationDirty00
static int tolua_Scene_Scene_MarkReplicationDirty00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Scene",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Node",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Scene* self = (Scene*)  tolua_tousertype(tolua_S,1,0);
  Node* node = ((Node*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'MarkReplicationDirty'", NULL);
#endif
  {
   self->MarkReplicationDirty(node);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MarkReplicationDirty'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GetScene */
#ifndef TOLUA_DISABLE_tolua_Scene_GetScene00
static int tolua_Scene_GetScene00(lua_State* tolua_S)
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
   Scene* tolua_ret = (Scene*)  GetScene();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Scene");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetScene'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_Scene_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,1);
 tolua_beginmodule(tolua_S,NULL);
  tolua_cclass(tolua_S,"Component","Component","",NULL);
  tolua_beginmodule(tolua_S,"Component");
   tolua_function(tolua_S,"SetEnabled",tolua_Scene_Component_SetEnabled00);
   tolua_function(tolua_S,"Remove",tolua_Scene_Component_Remove00);
   tolua_function(tolua_S,"GetID",tolua_Scene_Component_GetID00);
   tolua_function(tolua_S,"GetNode",tolua_Scene_Component_GetNode00);
   tolua_function(tolua_S,"GetScene",tolua_Scene_Component_GetScene00);
   tolua_function(tolua_S,"IsEnabled",tolua_Scene_Component_IsEnabled00);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"REPLICATED",REPLICATED);
  tolua_constant(tolua_S,"LOCAL",LOCAL);
  tolua_cclass(tolua_S,"Node","Node","",NULL);
  tolua_beginmodule(tolua_S,"Node");
   tolua_function(tolua_S,"SetName",tolua_Scene_Node_SetName00);
   tolua_function(tolua_S,"SetPosition",tolua_Scene_Node_SetPosition00);
   tolua_function(tolua_S,"SetRotation",tolua_Scene_Node_SetRotation00);
   tolua_function(tolua_S,"SetDirection",tolua_Scene_Node_SetDirection00);
   tolua_function(tolua_S,"SetScale",tolua_Scene_Node_SetScale00);
   tolua_function(tolua_S,"SetScale",tolua_Scene_Node_SetScale01);
   tolua_function(tolua_S,"SetTransform",tolua_Scene_Node_SetTransform00);
   tolua_function(tolua_S,"SetTransform",tolua_Scene_Node_SetTransform01);
   tolua_function(tolua_S,"SetTransform",tolua_Scene_Node_SetTransform02);
   tolua_function(tolua_S,"SetWorldPosition",tolua_Scene_Node_SetWorldPosition00);
   tolua_function(tolua_S,"SetWorldRotation",tolua_Scene_Node_SetWorldRotation00);
   tolua_function(tolua_S,"SetWorldDirection",tolua_Scene_Node_SetWorldDirection00);
   tolua_function(tolua_S,"SetWorldScale",tolua_Scene_Node_SetWorldScale00);
   tolua_function(tolua_S,"SetWorldScale",tolua_Scene_Node_SetWorldScale01);
   tolua_function(tolua_S,"SetWorldTransform",tolua_Scene_Node_SetWorldTransform00);
   tolua_function(tolua_S,"SetWorldTransform",tolua_Scene_Node_SetWorldTransform01);
   tolua_function(tolua_S,"SetWorldTransform",tolua_Scene_Node_SetWorldTransform02);
   tolua_function(tolua_S,"Translate",tolua_Scene_Node_Translate00);
   tolua_function(tolua_S,"TranslateRelative",tolua_Scene_Node_TranslateRelative00);
   tolua_function(tolua_S,"Rotate",tolua_Scene_Node_Rotate00);
   tolua_function(tolua_S,"Pitch",tolua_Scene_Node_Pitch00);
   tolua_function(tolua_S,"Yaw",tolua_Scene_Node_Yaw00);
   tolua_function(tolua_S,"Roll",tolua_Scene_Node_Roll00);
   tolua_function(tolua_S,"LookAt",tolua_Scene_Node_LookAt00);
   tolua_function(tolua_S,"LookAt",tolua_Scene_Node_LookAt01);
   tolua_function(tolua_S,"Scale",tolua_Scene_Node_Scale00);
   tolua_function(tolua_S,"Scale",tolua_Scene_Node_Scale01);
   tolua_function(tolua_S,"SetEnabled",tolua_Scene_Node_SetEnabled00);
   tolua_function(tolua_S,"SetEnabled",tolua_Scene_Node_SetEnabled01);
   tolua_function(tolua_S,"SetOwner",tolua_Scene_Node_SetOwner00);
   tolua_function(tolua_S,"MarkDirty",tolua_Scene_Node_MarkDirty00);
   tolua_function(tolua_S,"CreateChild",tolua_Scene_Node_CreateChild00);
   tolua_function(tolua_S,"CreateChild",tolua_Scene_Node_CreateChild01);
   tolua_function(tolua_S,"AddChild",tolua_Scene_Node_AddChild00);
   tolua_function(tolua_S,"RemoveChild",tolua_Scene_Node_RemoveChild00);
   tolua_function(tolua_S,"RemoveAllChildren",tolua_Scene_Node_RemoveAllChildren00);
   tolua_function(tolua_S,"CreateComponent",tolua_Scene_Node_CreateComponent00);
   tolua_function(tolua_S,"GetOrCreateComponent",tolua_Scene_Node_GetOrCreateComponent00);
   tolua_function(tolua_S,"RemoveComponent",tolua_Scene_Node_RemoveComponent00);
   tolua_function(tolua_S,"RemoveComponent",tolua_Scene_Node_RemoveComponent01);
   tolua_function(tolua_S,"RemoveAllComponents",tolua_Scene_Node_RemoveAllComponents00);
   tolua_function(tolua_S,"Clone",tolua_Scene_Node_Clone00);
   tolua_function(tolua_S,"Remove",tolua_Scene_Node_Remove00);
   tolua_function(tolua_S,"SetParent",tolua_Scene_Node_SetParent00);
   tolua_function(tolua_S,"SetVar",tolua_Scene_Node_SetVar00);
   tolua_function(tolua_S,"AddListener",tolua_Scene_Node_AddListener00);
   tolua_function(tolua_S,"RemoveListener",tolua_Scene_Node_RemoveListener00);
   tolua_function(tolua_S,"GetID",tolua_Scene_Node_GetID00);
   tolua_function(tolua_S,"GetName",tolua_Scene_Node_GetName00);
   tolua_function(tolua_S,"GetNameHash",tolua_Scene_Node_GetNameHash00);
   tolua_function(tolua_S,"GetParent",tolua_Scene_Node_GetParent00);
   tolua_function(tolua_S,"GetScene",tolua_Scene_Node_GetScene00);
   tolua_function(tolua_S,"IsEnabled",tolua_Scene_Node_IsEnabled00);
   tolua_function(tolua_S,"GetOwner",tolua_Scene_Node_GetOwner00);
   tolua_function(tolua_S,"GetPosition",tolua_Scene_Node_GetPosition00);
   tolua_function(tolua_S,"GetRotation",tolua_Scene_Node_GetRotation00);
   tolua_function(tolua_S,"GetDirection",tolua_Scene_Node_GetDirection00);
   tolua_function(tolua_S,"GetScale",tolua_Scene_Node_GetScale00);
   tolua_function(tolua_S,"GetTransform",tolua_Scene_Node_GetTransform00);
   tolua_function(tolua_S,"GetWorldPosition",tolua_Scene_Node_GetWorldPosition00);
   tolua_function(tolua_S,"GetWorldRotation",tolua_Scene_Node_GetWorldRotation00);
   tolua_function(tolua_S,"GetWorldDirection",tolua_Scene_Node_GetWorldDirection00);
   tolua_function(tolua_S,"GetWorldScale",tolua_Scene_Node_GetWorldScale00);
   tolua_function(tolua_S,"GetWorldTransform",tolua_Scene_Node_GetWorldTransform00);
   tolua_function(tolua_S,"LocalToWorld",tolua_Scene_Node_LocalToWorld00);
   tolua_function(tolua_S,"LocalToWorld",tolua_Scene_Node_LocalToWorld01);
   tolua_function(tolua_S,"WorldToLocal",tolua_Scene_Node_WorldToLocal00);
   tolua_function(tolua_S,"WorldToLocal",tolua_Scene_Node_WorldToLocal01);
   tolua_function(tolua_S,"IsDirty",tolua_Scene_Node_IsDirty00);
   tolua_function(tolua_S,"GetNumChildren",tolua_Scene_Node_GetNumChildren00);
   tolua_function(tolua_S,"GetChild",tolua_Scene_Node_GetChild00);
   tolua_function(tolua_S,"GetChild",tolua_Scene_Node_GetChild01);
   tolua_function(tolua_S,"GetChild",tolua_Scene_Node_GetChild02);
   tolua_function(tolua_S,"GetChild",tolua_Scene_Node_GetChild03);
   tolua_function(tolua_S,"GetNumComponents",tolua_Scene_Node_GetNumComponents00);
   tolua_function(tolua_S,"GetNumNetworkComponents",tolua_Scene_Node_GetNumNetworkComponents00);
   tolua_function(tolua_S,"GetComponent",tolua_Scene_Node_GetComponent00);
   tolua_function(tolua_S,"HasComponent",tolua_Scene_Node_HasComponent00);
  tolua_endmodule(tolua_S);
  tolua_variable(tolua_S,"FIRST_REPLICATED_ID",tolua_get_FIRST_REPLICATED_ID,NULL);
  tolua_variable(tolua_S,"LAST_REPLICATED_ID",tolua_get_LAST_REPLICATED_ID,NULL);
  tolua_variable(tolua_S,"FIRST_LOCAL_ID",tolua_get_FIRST_LOCAL_ID,NULL);
  tolua_variable(tolua_S,"LAST_LOCAL_ID",tolua_get_LAST_LOCAL_ID,NULL);
  tolua_cclass(tolua_S,"Scene","Scene","Node",NULL);
  tolua_beginmodule(tolua_S,"Scene");
   tolua_function(tolua_S,"LoadAsync",tolua_Scene_Scene_LoadAsync00);
   tolua_function(tolua_S,"LoadAsyncXML",tolua_Scene_Scene_LoadAsyncXML00);
   tolua_function(tolua_S,"StopAsyncLoading",tolua_Scene_Scene_StopAsyncLoading00);
   tolua_function(tolua_S,"Clear",tolua_Scene_Scene_Clear00);
   tolua_function(tolua_S,"SetUpdateEnabled",tolua_Scene_Scene_SetUpdateEnabled00);
   tolua_function(tolua_S,"SetTimeScale",tolua_Scene_Scene_SetTimeScale00);
   tolua_function(tolua_S,"SetElapsedTime",tolua_Scene_Scene_SetElapsedTime00);
   tolua_function(tolua_S,"SetSmoothingConstant",tolua_Scene_Scene_SetSmoothingConstant00);
   tolua_function(tolua_S,"SetSnapThreshold",tolua_Scene_Scene_SetSnapThreshold00);
   tolua_function(tolua_S,"GetNode",tolua_Scene_Scene_GetNode00);
   tolua_function(tolua_S,"GetComponent",tolua_Scene_Scene_GetComponent00);
   tolua_function(tolua_S,"IsUpdateEnabled",tolua_Scene_Scene_IsUpdateEnabled00);
   tolua_function(tolua_S,"IsAsyncLoading",tolua_Scene_Scene_IsAsyncLoading00);
   tolua_function(tolua_S,"GetAsyncProgress",tolua_Scene_Scene_GetAsyncProgress00);
   tolua_function(tolua_S,"GetFileName",tolua_Scene_Scene_GetFileName00);
   tolua_function(tolua_S,"GetChecksum",tolua_Scene_Scene_GetChecksum00);
   tolua_function(tolua_S,"GetTimeScale",tolua_Scene_Scene_GetTimeScale00);
   tolua_function(tolua_S,"GetElapsedTime",tolua_Scene_Scene_GetElapsedTime00);
   tolua_function(tolua_S,"GetSmoothingConstant",tolua_Scene_Scene_GetSmoothingConstant00);
   tolua_function(tolua_S,"GetSnapThreshold",tolua_Scene_Scene_GetSnapThreshold00);
   tolua_function(tolua_S,"GetVarName",tolua_Scene_Scene_GetVarName00);
   tolua_function(tolua_S,"Update",tolua_Scene_Scene_Update00);
   tolua_function(tolua_S,"BeginThreadedUpdate",tolua_Scene_Scene_BeginThreadedUpdate00);
   tolua_function(tolua_S,"EndThreadedUpdate",tolua_Scene_Scene_EndThreadedUpdate00);
   tolua_function(tolua_S,"DelayedMarkedDirty",tolua_Scene_Scene_DelayedMarkedDirty00);
   tolua_function(tolua_S,"IsThreadedUpdate",tolua_Scene_Scene_IsThreadedUpdate00);
   tolua_function(tolua_S,"GetFreeNodeID",tolua_Scene_Scene_GetFreeNodeID00);
   tolua_function(tolua_S,"GetFreeComponentID",tolua_Scene_Scene_GetFreeComponentID00);
   tolua_function(tolua_S,"NodeAdded",tolua_Scene_Scene_NodeAdded00);
   tolua_function(tolua_S,"NodeRemoved",tolua_Scene_Scene_NodeRemoved00);
   tolua_function(tolua_S,"ComponentAdded",tolua_Scene_Scene_ComponentAdded00);
   tolua_function(tolua_S,"ComponentRemoved",tolua_Scene_Scene_ComponentRemoved00);
   tolua_function(tolua_S,"SetVarNamesAttr",tolua_Scene_Scene_SetVarNamesAttr00);
   tolua_function(tolua_S,"GetVarNamesAttr",tolua_Scene_Scene_GetVarNamesAttr00);
   tolua_function(tolua_S,"PrepareNetworkUpdate",tolua_Scene_Scene_PrepareNetworkUpdate00);
   tolua_function(tolua_S,"CleanupConnection",tolua_Scene_Scene_CleanupConnection00);
   tolua_function(tolua_S,"MarkNetworkUpdate",tolua_Scene_Scene_MarkNetworkUpdate00);
   tolua_function(tolua_S,"MarkNetworkUpdate",tolua_Scene_Scene_MarkNetworkUpdate01);
   tolua_function(tolua_S,"MarkReplicationDirty",tolua_Scene_Scene_MarkReplicationDirty00);
  tolua_endmodule(tolua_S);
  tolua_function(tolua_S,"GetScene",tolua_Scene_GetScene00);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_Scene (lua_State* tolua_S) {
 return tolua_Scene_open(tolua_S);
};
#endif

