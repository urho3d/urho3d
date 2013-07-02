/*
** Lua binding: Core
** Generated automatically by tolua++-1.0.92 on 07/02/13 20:27:48.
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
TOLUA_API int  tolua_Core_open (lua_State* tolua_S);

#define TOLUA_RELEASE
#include "CoreLuaAPI.h"
#include "ProcessUtils.h"
#include "StringUtils.h"
#include "Variant.h"
#include "Timer.h"
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

static int tolua_collect_IntRect (lua_State* tolua_S)
{
 IntRect* self = (IntRect*) tolua_tousertype(tolua_S,1,0);
  Mtolua_delete(self);
  return 0;
}

static int tolua_collect_Vector4 (lua_State* tolua_S)
{
 Vector4* self = (Vector4*) tolua_tousertype(tolua_S,1,0);
  Mtolua_delete(self);
  return 0;
}

static int tolua_collect_Color (lua_State* tolua_S)
{
 Color* self = (Color*) tolua_tousertype(tolua_S,1,0);
  Mtolua_delete(self);
  return 0;
}

static int tolua_collect_Variant (lua_State* tolua_S)
{
 Variant* self = (Variant*) tolua_tousertype(tolua_S,1,0);
  Mtolua_delete(self);
  return 0;
}

static int tolua_collect_ShortStringHash (lua_State* tolua_S)
{
 ShortStringHash* self = (ShortStringHash*) tolua_tousertype(tolua_S,1,0);
  Mtolua_delete(self);
  return 0;
}

static int tolua_collect_StringHash (lua_State* tolua_S)
{
 StringHash* self = (StringHash*) tolua_tousertype(tolua_S,1,0);
  Mtolua_delete(self);
  return 0;
}

static int tolua_collect_ResourceRef (lua_State* tolua_S)
{
 ResourceRef* self = (ResourceRef*) tolua_tousertype(tolua_S,1,0);
  Mtolua_delete(self);
  return 0;
}

static int tolua_collect_Rect (lua_State* tolua_S)
{
 Rect* self = (Rect*) tolua_tousertype(tolua_S,1,0);
  Mtolua_delete(self);
  return 0;
}

static int tolua_collect_ResourceRefList (lua_State* tolua_S)
{
 ResourceRefList* self = (ResourceRefList*) tolua_tousertype(tolua_S,1,0);
  Mtolua_delete(self);
  return 0;
}

static int tolua_collect_Vector2 (lua_State* tolua_S)
{
 Vector2* self = (Vector2*) tolua_tousertype(tolua_S,1,0);
  Mtolua_delete(self);
  return 0;
}

static int tolua_collect_Timer (lua_State* tolua_S)
{
 Timer* self = (Timer*) tolua_tousertype(tolua_S,1,0);
  Mtolua_delete(self);
  return 0;
}

static int tolua_collect_Vector3 (lua_State* tolua_S)
{
 Vector3* self = (Vector3*) tolua_tousertype(tolua_S,1,0);
  Mtolua_delete(self);
  return 0;
}

static int tolua_collect_String (lua_State* tolua_S)
{
 String* self = (String*) tolua_tousertype(tolua_S,1,0);
  Mtolua_delete(self);
  return 0;
}

static int tolua_collect_IntVector2 (lua_State* tolua_S)
{
 IntVector2* self = (IntVector2*) tolua_tousertype(tolua_S,1,0);
  Mtolua_delete(self);
  return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"VariantMap");
 tolua_usertype(tolua_S,"String");
 tolua_usertype(tolua_S,"Color");
 tolua_usertype(tolua_S,"Vector<String>");
 tolua_usertype(tolua_S,"Time");
 tolua_usertype(tolua_S,"Variant");
 tolua_usertype(tolua_S,"Vector3");
 tolua_usertype(tolua_S,"IntRect");
 tolua_usertype(tolua_S,"Object");
 tolua_usertype(tolua_S,"ResourceRef");
 tolua_usertype(tolua_S,"StringHash");
 tolua_usertype(tolua_S,"Quaternion");
 tolua_usertype(tolua_S,"Rect");
 tolua_usertype(tolua_S,"ResourceRefList");
 tolua_usertype(tolua_S,"Vector2");
 tolua_usertype(tolua_S,"Timer");
 tolua_usertype(tolua_S,"ShortStringHash");
 tolua_usertype(tolua_S,"Vector4");
 tolua_usertype(tolua_S,"IntVector2");
}

/* function: InitFPU */
#ifndef TOLUA_DISABLE_tolua_Core_InitFPU00
static int tolua_Core_InitFPU00(lua_State* tolua_S)
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
   InitFPU();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'InitFPU'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: ErrorDialog */
#ifndef TOLUA_DISABLE_tolua_Core_ErrorDialog00
static int tolua_Core_ErrorDialog00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* title = ((const char*)  tolua_tostring(tolua_S,1,0));
  const char* message = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   ErrorDialog(title,message);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ErrorDialog'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: ErrorExit */
#ifndef TOLUA_DISABLE_tolua_Core_ErrorExit00
static int tolua_Core_ErrorExit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* message = ((const char*)  tolua_tostring(tolua_S,1,0));
  int exitCode = ((int)  tolua_tonumber(tolua_S,2,EXIT_FAILURE));
  {
   ErrorExit(message,exitCode);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ErrorExit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: OpenConsoleWindow */
#ifndef TOLUA_DISABLE_tolua_Core_OpenConsoleWindow00
static int tolua_Core_OpenConsoleWindow00(lua_State* tolua_S)
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
   OpenConsoleWindow();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OpenConsoleWindow'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: PrintLine */
#ifndef TOLUA_DISABLE_tolua_Core_PrintLine00
static int tolua_Core_PrintLine00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* str = ((const char*)  tolua_tostring(tolua_S,1,0));
  bool error = ((bool)  tolua_toboolean(tolua_S,2,false));
  {
   PrintLine(str,error);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'PrintLine'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GetArguments */
#ifndef TOLUA_DISABLE_tolua_Core_GetArguments00
static int tolua_Core_GetArguments00(lua_State* tolua_S)
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
   const Vector<String>& tolua_ret = (const Vector<String>&)  GetArguments();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Vector<String>");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetArguments'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GetConsoleInput */
#ifndef TOLUA_DISABLE_tolua_Core_GetConsoleInput00
static int tolua_Core_GetConsoleInput00(lua_State* tolua_S)
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
   String tolua_ret = (String)  GetConsoleInput();
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
 tolua_error(tolua_S,"#ferror in function 'GetConsoleInput'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GetPlatform */
#ifndef TOLUA_DISABLE_tolua_Core_GetPlatform00
static int tolua_Core_GetPlatform00(lua_State* tolua_S)
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
   String tolua_ret = (String)  GetPlatform();
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
 tolua_error(tolua_S,"#ferror in function 'GetPlatform'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GetNumPhysicalCPUs */
#ifndef TOLUA_DISABLE_tolua_Core_GetNumPhysicalCPUs00
static int tolua_Core_GetNumPhysicalCPUs00(lua_State* tolua_S)
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
   unsigned tolua_ret = (unsigned)  GetNumPhysicalCPUs();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNumPhysicalCPUs'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GetNumLogicalCPUs */
#ifndef TOLUA_DISABLE_tolua_Core_GetNumLogicalCPUs00
static int tolua_Core_GetNumLogicalCPUs00(lua_State* tolua_S)
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
   unsigned tolua_ret = (unsigned)  GetNumLogicalCPUs();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNumLogicalCPUs'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: ToBool */
#ifndef TOLUA_DISABLE_tolua_Core_ToBool00
static int tolua_Core_ToBool00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const String* source = ((const String*)  tolua_tousertype(tolua_S,1,0));
  {
   bool tolua_ret = (bool)  ToBool(*source);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ToBool'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: ToBool */
#ifndef TOLUA_DISABLE_tolua_Core_ToBool01
static int tolua_Core_ToBool01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* source = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   bool tolua_ret = (bool)  ToBool(source);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_ToBool00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: ToFloat */
#ifndef TOLUA_DISABLE_tolua_Core_ToFloat00
static int tolua_Core_ToFloat00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const String* source = ((const String*)  tolua_tousertype(tolua_S,1,0));
  {
   float tolua_ret = (float)  ToFloat(*source);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ToFloat'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: ToFloat */
#ifndef TOLUA_DISABLE_tolua_Core_ToFloat01
static int tolua_Core_ToFloat01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* source = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   float tolua_ret = (float)  ToFloat(source);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_ToFloat00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: ToInt */
#ifndef TOLUA_DISABLE_tolua_Core_ToInt00
static int tolua_Core_ToInt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const String* source = ((const String*)  tolua_tousertype(tolua_S,1,0));
  {
   int tolua_ret = (int)  ToInt(*source);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ToInt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: ToInt */
#ifndef TOLUA_DISABLE_tolua_Core_ToInt01
static int tolua_Core_ToInt01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* source = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   int tolua_ret = (int)  ToInt(source);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_ToInt00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: ToUInt */
#ifndef TOLUA_DISABLE_tolua_Core_ToUInt00
static int tolua_Core_ToUInt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const String* source = ((const String*)  tolua_tousertype(tolua_S,1,0));
  {
   unsigned tolua_ret = (unsigned)  ToUInt(*source);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ToUInt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: ToUInt */
#ifndef TOLUA_DISABLE_tolua_Core_ToUInt01
static int tolua_Core_ToUInt01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* source = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   unsigned tolua_ret = (unsigned)  ToUInt(source);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_ToUInt00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: ToColor */
#ifndef TOLUA_DISABLE_tolua_Core_ToColor00
static int tolua_Core_ToColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const String* source = ((const String*)  tolua_tousertype(tolua_S,1,0));
  {
   Color tolua_ret = (Color)  ToColor(*source);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((Color)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"Color");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Color));
     tolua_pushusertype(tolua_S,tolua_obj,"Color");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ToColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: ToColor */
#ifndef TOLUA_DISABLE_tolua_Core_ToColor01
static int tolua_Core_ToColor01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* source = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   Color tolua_ret = (Color)  ToColor(source);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((Color)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"Color");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Color));
     tolua_pushusertype(tolua_S,tolua_obj,"Color");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_ToColor00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: ToIntRect */
#ifndef TOLUA_DISABLE_tolua_Core_ToIntRect00
static int tolua_Core_ToIntRect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const String* source = ((const String*)  tolua_tousertype(tolua_S,1,0));
  {
   IntRect tolua_ret = (IntRect)  ToIntRect(*source);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((IntRect)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"IntRect");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(IntRect));
     tolua_pushusertype(tolua_S,tolua_obj,"IntRect");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ToIntRect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: ToIntRect */
#ifndef TOLUA_DISABLE_tolua_Core_ToIntRect01
static int tolua_Core_ToIntRect01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* source = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   IntRect tolua_ret = (IntRect)  ToIntRect(source);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((IntRect)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"IntRect");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(IntRect));
     tolua_pushusertype(tolua_S,tolua_obj,"IntRect");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_ToIntRect00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: ToIntVector2 */
#ifndef TOLUA_DISABLE_tolua_Core_ToIntVector200
static int tolua_Core_ToIntVector200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const String* source = ((const String*)  tolua_tousertype(tolua_S,1,0));
  {
   IntVector2 tolua_ret = (IntVector2)  ToIntVector2(*source);
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
 tolua_error(tolua_S,"#ferror in function 'ToIntVector2'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: ToIntVector2 */
#ifndef TOLUA_DISABLE_tolua_Core_ToIntVector201
static int tolua_Core_ToIntVector201(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* source = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   IntVector2 tolua_ret = (IntVector2)  ToIntVector2(source);
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
tolua_lerror:
 return tolua_Core_ToIntVector200(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: ToQuaternion */
#ifndef TOLUA_DISABLE_tolua_Core_ToQuaternion00
static int tolua_Core_ToQuaternion00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const String* source = ((const String*)  tolua_tousertype(tolua_S,1,0));
  {
   Quaternion tolua_ret = (Quaternion)  ToQuaternion(*source);
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
 tolua_error(tolua_S,"#ferror in function 'ToQuaternion'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: ToQuaternion */
#ifndef TOLUA_DISABLE_tolua_Core_ToQuaternion01
static int tolua_Core_ToQuaternion01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* source = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   Quaternion tolua_ret = (Quaternion)  ToQuaternion(source);
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
tolua_lerror:
 return tolua_Core_ToQuaternion00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: ToRect */
#ifndef TOLUA_DISABLE_tolua_Core_ToRect00
static int tolua_Core_ToRect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const String* source = ((const String*)  tolua_tousertype(tolua_S,1,0));
  {
   Rect tolua_ret = (Rect)  ToRect(*source);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((Rect)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"Rect");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Rect));
     tolua_pushusertype(tolua_S,tolua_obj,"Rect");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ToRect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: ToRect */
#ifndef TOLUA_DISABLE_tolua_Core_ToRect01
static int tolua_Core_ToRect01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* source = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   Rect tolua_ret = (Rect)  ToRect(source);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((Rect)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"Rect");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Rect));
     tolua_pushusertype(tolua_S,tolua_obj,"Rect");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_ToRect00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: ToVector2 */
#ifndef TOLUA_DISABLE_tolua_Core_ToVector200
static int tolua_Core_ToVector200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const String* source = ((const String*)  tolua_tousertype(tolua_S,1,0));
  {
   Vector2 tolua_ret = (Vector2)  ToVector2(*source);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((Vector2)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"Vector2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Vector2));
     tolua_pushusertype(tolua_S,tolua_obj,"Vector2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ToVector2'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: ToVector2 */
#ifndef TOLUA_DISABLE_tolua_Core_ToVector201
static int tolua_Core_ToVector201(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* source = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   Vector2 tolua_ret = (Vector2)  ToVector2(source);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((Vector2)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"Vector2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Vector2));
     tolua_pushusertype(tolua_S,tolua_obj,"Vector2");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_ToVector200(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: ToVector3 */
#ifndef TOLUA_DISABLE_tolua_Core_ToVector300
static int tolua_Core_ToVector300(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const String* source = ((const String*)  tolua_tousertype(tolua_S,1,0));
  {
   Vector3 tolua_ret = (Vector3)  ToVector3(*source);
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
 tolua_error(tolua_S,"#ferror in function 'ToVector3'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: ToVector3 */
#ifndef TOLUA_DISABLE_tolua_Core_ToVector301
static int tolua_Core_ToVector301(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* source = ((const char*)  tolua_tostring(tolua_S,1,0));
  {
   Vector3 tolua_ret = (Vector3)  ToVector3(source);
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
 return tolua_Core_ToVector300(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: ToVector4 */
#ifndef TOLUA_DISABLE_tolua_Core_ToVector400
static int tolua_Core_ToVector400(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"const String",0,&tolua_err)) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const String* source = ((const String*)  tolua_tousertype(tolua_S,1,0));
  bool allowMissingCoords = ((bool)  tolua_toboolean(tolua_S,2,false));
  {
   Vector4 tolua_ret = (Vector4)  ToVector4(*source,allowMissingCoords);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((Vector4)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"Vector4");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Vector4));
     tolua_pushusertype(tolua_S,tolua_obj,"Vector4");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ToVector4'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: ToVector4 */
#ifndef TOLUA_DISABLE_tolua_Core_ToVector401
static int tolua_Core_ToVector401(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isstring(tolua_S,1,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* source = ((const char*)  tolua_tostring(tolua_S,1,0));
  bool allowMissingCoords = ((bool)  tolua_toboolean(tolua_S,2,false));
  {
   Vector4 tolua_ret = (Vector4)  ToVector4(source,allowMissingCoords);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((Vector4)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"Vector4");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Vector4));
     tolua_pushusertype(tolua_S,tolua_obj,"Vector4");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_ToVector400(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* function: ToString */
#ifndef TOLUA_DISABLE_tolua_Core_ToString00
static int tolua_Core_ToString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isuserdata(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  void* value = ((void*)  tolua_touserdata(tolua_S,1,0));
  {
   String tolua_ret = (String)  ToString(value);
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
 tolua_error(tolua_S,"#ferror in function 'ToString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: ToStringHex */
#ifndef TOLUA_DISABLE_tolua_Core_ToStringHex00
static int tolua_Core_ToStringHex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned value = ((unsigned)  tolua_tonumber(tolua_S,1,0));
  {
   String tolua_ret = (String)  ToStringHex(value);
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
 tolua_error(tolua_S,"#ferror in function 'ToStringHex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: IsAlpha */
#ifndef TOLUA_DISABLE_tolua_Core_IsAlpha00
static int tolua_Core_IsAlpha00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned ch = ((unsigned)  tolua_tonumber(tolua_S,1,0));
  {
   bool tolua_ret = (bool)  IsAlpha(ch);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsAlpha'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: IsDigit */
#ifndef TOLUA_DISABLE_tolua_Core_IsDigit00
static int tolua_Core_IsDigit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isnumber(tolua_S,1,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  unsigned ch = ((unsigned)  tolua_tonumber(tolua_S,1,0));
  {
   bool tolua_ret = (bool)  IsDigit(ch);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsDigit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  ResourceRef */
#ifndef TOLUA_DISABLE_tolua_Core_ResourceRef_new00
static int tolua_Core_ResourceRef_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ResourceRef",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ResourceRef* tolua_ret = (ResourceRef*)  Mtolua_new((ResourceRef)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ResourceRef");
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

/* method: new_local of class  ResourceRef */
#ifndef TOLUA_DISABLE_tolua_Core_ResourceRef_new00_local
static int tolua_Core_ResourceRef_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ResourceRef",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ResourceRef* tolua_ret = (ResourceRef*)  Mtolua_new((ResourceRef)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ResourceRef");
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

/* method: new of class  ResourceRef */
#ifndef TOLUA_DISABLE_tolua_Core_ResourceRef_new01
static int tolua_Core_ResourceRef_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ResourceRef",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"ShortStringHash",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  ShortStringHash type = *((ShortStringHash*)  tolua_tousertype(tolua_S,2,0));
  {
   ResourceRef* tolua_ret = (ResourceRef*)  Mtolua_new((ResourceRef)(type));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ResourceRef");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_ResourceRef_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  ResourceRef */
#ifndef TOLUA_DISABLE_tolua_Core_ResourceRef_new01_local
static int tolua_Core_ResourceRef_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ResourceRef",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"ShortStringHash",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  ShortStringHash type = *((ShortStringHash*)  tolua_tousertype(tolua_S,2,0));
  {
   ResourceRef* tolua_ret = (ResourceRef*)  Mtolua_new((ResourceRef)(type));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ResourceRef");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_ResourceRef_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  ResourceRef */
#ifndef TOLUA_DISABLE_tolua_Core_ResourceRef_new02
static int tolua_Core_ResourceRef_new02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ResourceRef",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"ShortStringHash",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"StringHash",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  ShortStringHash type = *((ShortStringHash*)  tolua_tousertype(tolua_S,2,0));
  StringHash id = *((StringHash*)  tolua_tousertype(tolua_S,3,0));
  {
   ResourceRef* tolua_ret = (ResourceRef*)  Mtolua_new((ResourceRef)(type,id));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ResourceRef");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_ResourceRef_new01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  ResourceRef */
#ifndef TOLUA_DISABLE_tolua_Core_ResourceRef_new02_local
static int tolua_Core_ResourceRef_new02_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ResourceRef",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"ShortStringHash",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"StringHash",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  ShortStringHash type = *((ShortStringHash*)  tolua_tousertype(tolua_S,2,0));
  StringHash id = *((StringHash*)  tolua_tousertype(tolua_S,3,0));
  {
   ResourceRef* tolua_ret = (ResourceRef*)  Mtolua_new((ResourceRef)(type,id));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ResourceRef");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_ResourceRef_new01_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  ResourceRef */
#ifndef TOLUA_DISABLE_tolua_Core_ResourceRef_new03
static int tolua_Core_ResourceRef_new03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ResourceRef",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ResourceRef",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const ResourceRef* rhs = ((const ResourceRef*)  tolua_tousertype(tolua_S,2,0));
  {
   ResourceRef* tolua_ret = (ResourceRef*)  Mtolua_new((ResourceRef)(*rhs));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ResourceRef");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_ResourceRef_new02(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  ResourceRef */
#ifndef TOLUA_DISABLE_tolua_Core_ResourceRef_new03_local
static int tolua_Core_ResourceRef_new03_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ResourceRef",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ResourceRef",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const ResourceRef* rhs = ((const ResourceRef*)  tolua_tousertype(tolua_S,2,0));
  {
   ResourceRef* tolua_ret = (ResourceRef*)  Mtolua_new((ResourceRef)(*rhs));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ResourceRef");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_ResourceRef_new02_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* get function: type_ of class  ResourceRef */
#ifndef TOLUA_DISABLE_tolua_get_ResourceRef_type
static int tolua_get_ResourceRef_type(lua_State* tolua_S)
{
  ResourceRef* self = (ResourceRef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'type_'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->type_,"ShortStringHash");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: type_ of class  ResourceRef */
#ifndef TOLUA_DISABLE_tolua_set_ResourceRef_type
static int tolua_set_ResourceRef_type(lua_State* tolua_S)
{
  ResourceRef* self = (ResourceRef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'type_'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"ShortStringHash",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->type_ = *((ShortStringHash*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: id_ of class  ResourceRef */
#ifndef TOLUA_DISABLE_tolua_get_ResourceRef_id
static int tolua_get_ResourceRef_id(lua_State* tolua_S)
{
  ResourceRef* self = (ResourceRef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'id_'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->id_,"StringHash");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: id_ of class  ResourceRef */
#ifndef TOLUA_DISABLE_tolua_set_ResourceRef_id
static int tolua_set_ResourceRef_id(lua_State* tolua_S)
{
  ResourceRef* self = (ResourceRef*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'id_'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"StringHash",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->id_ = *((StringHash*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  ResourceRef */
#ifndef TOLUA_DISABLE_tolua_Core_ResourceRef__eq00
static int tolua_Core_ResourceRef__eq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ResourceRef",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ResourceRef",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ResourceRef* self = (const ResourceRef*)  tolua_tousertype(tolua_S,1,0);
  const ResourceRef* rhs = ((const ResourceRef*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator=='", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator==(*rhs);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.eq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  ResourceRefList */
#ifndef TOLUA_DISABLE_tolua_Core_ResourceRefList_new00
static int tolua_Core_ResourceRefList_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ResourceRefList",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ResourceRefList* tolua_ret = (ResourceRefList*)  Mtolua_new((ResourceRefList)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ResourceRefList");
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

/* method: new_local of class  ResourceRefList */
#ifndef TOLUA_DISABLE_tolua_Core_ResourceRefList_new00_local
static int tolua_Core_ResourceRefList_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ResourceRefList",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ResourceRefList* tolua_ret = (ResourceRefList*)  Mtolua_new((ResourceRefList)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ResourceRefList");
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

/* method: new of class  ResourceRefList */
#ifndef TOLUA_DISABLE_tolua_Core_ResourceRefList_new01
static int tolua_Core_ResourceRefList_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ResourceRefList",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"ShortStringHash",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  ShortStringHash type = *((ShortStringHash*)  tolua_tousertype(tolua_S,2,0));
  {
   ResourceRefList* tolua_ret = (ResourceRefList*)  Mtolua_new((ResourceRefList)(type));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ResourceRefList");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_ResourceRefList_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  ResourceRefList */
#ifndef TOLUA_DISABLE_tolua_Core_ResourceRefList_new01_local
static int tolua_Core_ResourceRefList_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ResourceRefList",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"ShortStringHash",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  ShortStringHash type = *((ShortStringHash*)  tolua_tousertype(tolua_S,2,0));
  {
   ResourceRefList* tolua_ret = (ResourceRefList*)  Mtolua_new((ResourceRefList)(type));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ResourceRefList");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_ResourceRefList_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* get function: type_ of class  ResourceRefList */
#ifndef TOLUA_DISABLE_tolua_get_ResourceRefList_type
static int tolua_get_ResourceRefList_type(lua_State* tolua_S)
{
  ResourceRefList* self = (ResourceRefList*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'type_'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->type_,"ShortStringHash");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: type_ of class  ResourceRefList */
#ifndef TOLUA_DISABLE_tolua_set_ResourceRefList_type
static int tolua_set_ResourceRefList_type(lua_State* tolua_S)
{
  ResourceRefList* self = (ResourceRefList*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'type_'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"ShortStringHash",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->type_ = *((ShortStringHash*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  ResourceRefList */
#ifndef TOLUA_DISABLE_tolua_Core_ResourceRefList__eq00
static int tolua_Core_ResourceRefList__eq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ResourceRefList",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ResourceRefList",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ResourceRefList* self = (const ResourceRefList*)  tolua_tousertype(tolua_S,1,0);
  const ResourceRefList* rhs = ((const ResourceRefList*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator=='", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator==(*rhs);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.eq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_new00
static int tolua_Core_Variant_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Variant",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Variant* tolua_ret = (Variant*)  Mtolua_new((Variant)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Variant");
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

/* method: new_local of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_new00_local
static int tolua_Core_Variant_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Variant",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Variant* tolua_ret = (Variant*)  Mtolua_new((Variant)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Variant");
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

/* method: new of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_new01
static int tolua_Core_Variant_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Variant",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  int value = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   Variant* tolua_ret = (Variant*)  Mtolua_new((Variant)(value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Variant");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_new01_local
static int tolua_Core_Variant_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Variant",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  int value = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   Variant* tolua_ret = (Variant*)  Mtolua_new((Variant)(value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Variant");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_new02
static int tolua_Core_Variant_new02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Variant",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  unsigned value = ((unsigned)  tolua_tonumber(tolua_S,2,0));
  {
   Variant* tolua_ret = (Variant*)  Mtolua_new((Variant)(value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Variant");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant_new01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_new02_local
static int tolua_Core_Variant_new02_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Variant",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  unsigned value = ((unsigned)  tolua_tonumber(tolua_S,2,0));
  {
   Variant* tolua_ret = (Variant*)  Mtolua_new((Variant)(value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Variant");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant_new01_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_new03
static int tolua_Core_Variant_new03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Variant",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const StringHash",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const StringHash* value = ((const StringHash*)  tolua_tousertype(tolua_S,2,0));
  {
   Variant* tolua_ret = (Variant*)  Mtolua_new((Variant)(*value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Variant");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant_new02(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_new03_local
static int tolua_Core_Variant_new03_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Variant",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const StringHash",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const StringHash* value = ((const StringHash*)  tolua_tousertype(tolua_S,2,0));
  {
   Variant* tolua_ret = (Variant*)  Mtolua_new((Variant)(*value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Variant");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant_new02_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_new04
static int tolua_Core_Variant_new04(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Variant",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ShortStringHash",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const ShortStringHash* value = ((const ShortStringHash*)  tolua_tousertype(tolua_S,2,0));
  {
   Variant* tolua_ret = (Variant*)  Mtolua_new((Variant)(*value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Variant");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant_new03(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_new04_local
static int tolua_Core_Variant_new04_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Variant",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ShortStringHash",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const ShortStringHash* value = ((const ShortStringHash*)  tolua_tousertype(tolua_S,2,0));
  {
   Variant* tolua_ret = (Variant*)  Mtolua_new((Variant)(*value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Variant");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant_new03_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_new05
static int tolua_Core_Variant_new05(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Variant",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  bool value = ((bool)  tolua_toboolean(tolua_S,2,0));
  {
   Variant* tolua_ret = (Variant*)  Mtolua_new((Variant)(value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Variant");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant_new04(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_new05_local
static int tolua_Core_Variant_new05_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Variant",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  bool value = ((bool)  tolua_toboolean(tolua_S,2,0));
  {
   Variant* tolua_ret = (Variant*)  Mtolua_new((Variant)(value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Variant");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant_new04_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_new06
static int tolua_Core_Variant_new06(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Variant",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float value = ((float)  tolua_tonumber(tolua_S,2,0));
  {
   Variant* tolua_ret = (Variant*)  Mtolua_new((Variant)(value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Variant");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant_new05(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_new06_local
static int tolua_Core_Variant_new06_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Variant",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float value = ((float)  tolua_tonumber(tolua_S,2,0));
  {
   Variant* tolua_ret = (Variant*)  Mtolua_new((Variant)(value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Variant");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant_new05_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_new07
static int tolua_Core_Variant_new07(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Variant",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const Vector2* value = ((const Vector2*)  tolua_tousertype(tolua_S,2,0));
  {
   Variant* tolua_ret = (Variant*)  Mtolua_new((Variant)(*value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Variant");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant_new06(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_new07_local
static int tolua_Core_Variant_new07_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Variant",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const Vector2* value = ((const Vector2*)  tolua_tousertype(tolua_S,2,0));
  {
   Variant* tolua_ret = (Variant*)  Mtolua_new((Variant)(*value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Variant");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant_new06_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_new08
static int tolua_Core_Variant_new08(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Variant",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const Vector3* value = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
  {
   Variant* tolua_ret = (Variant*)  Mtolua_new((Variant)(*value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Variant");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant_new07(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_new08_local
static int tolua_Core_Variant_new08_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Variant",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const Vector3* value = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
  {
   Variant* tolua_ret = (Variant*)  Mtolua_new((Variant)(*value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Variant");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant_new07_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_new09
static int tolua_Core_Variant_new09(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Variant",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector4",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const Vector4* value = ((const Vector4*)  tolua_tousertype(tolua_S,2,0));
  {
   Variant* tolua_ret = (Variant*)  Mtolua_new((Variant)(*value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Variant");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant_new08(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_new09_local
static int tolua_Core_Variant_new09_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Variant",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector4",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const Vector4* value = ((const Vector4*)  tolua_tousertype(tolua_S,2,0));
  {
   Variant* tolua_ret = (Variant*)  Mtolua_new((Variant)(*value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Variant");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant_new08_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_new10
static int tolua_Core_Variant_new10(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Variant",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Quaternion",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const Quaternion* value = ((const Quaternion*)  tolua_tousertype(tolua_S,2,0));
  {
   Variant* tolua_ret = (Variant*)  Mtolua_new((Variant)(*value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Variant");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant_new09(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_new10_local
static int tolua_Core_Variant_new10_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Variant",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Quaternion",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const Quaternion* value = ((const Quaternion*)  tolua_tousertype(tolua_S,2,0));
  {
   Variant* tolua_ret = (Variant*)  Mtolua_new((Variant)(*value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Variant");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant_new09_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_new11
static int tolua_Core_Variant_new11(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Variant",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Color",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const Color* value = ((const Color*)  tolua_tousertype(tolua_S,2,0));
  {
   Variant* tolua_ret = (Variant*)  Mtolua_new((Variant)(*value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Variant");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant_new10(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_new11_local
static int tolua_Core_Variant_new11_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Variant",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Color",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const Color* value = ((const Color*)  tolua_tousertype(tolua_S,2,0));
  {
   Variant* tolua_ret = (Variant*)  Mtolua_new((Variant)(*value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Variant");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant_new10_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_new12
static int tolua_Core_Variant_new12(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Variant",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const String* value = ((const String*)  tolua_tousertype(tolua_S,2,0));
  {
   Variant* tolua_ret = (Variant*)  Mtolua_new((Variant)(*value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Variant");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant_new11(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_new12_local
static int tolua_Core_Variant_new12_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Variant",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const String* value = ((const String*)  tolua_tousertype(tolua_S,2,0));
  {
   Variant* tolua_ret = (Variant*)  Mtolua_new((Variant)(*value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Variant");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant_new11_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_new13
static int tolua_Core_Variant_new13(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Variant",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* value = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   Variant* tolua_ret = (Variant*)  Mtolua_new((Variant)(value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Variant");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant_new12(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_new13_local
static int tolua_Core_Variant_new13_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Variant",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* value = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   Variant* tolua_ret = (Variant*)  Mtolua_new((Variant)(value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Variant");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant_new12_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_new14
static int tolua_Core_Variant_new14(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Variant",0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  void* value = ((void*)  tolua_touserdata(tolua_S,2,0));
  {
   Variant* tolua_ret = (Variant*)  Mtolua_new((Variant)(value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Variant");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant_new13(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_new14_local
static int tolua_Core_Variant_new14_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Variant",0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  void* value = ((void*)  tolua_touserdata(tolua_S,2,0));
  {
   Variant* tolua_ret = (Variant*)  Mtolua_new((Variant)(value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Variant");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant_new13_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_new15
static int tolua_Core_Variant_new15(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Variant",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ResourceRef",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const ResourceRef* value = ((const ResourceRef*)  tolua_tousertype(tolua_S,2,0));
  {
   Variant* tolua_ret = (Variant*)  Mtolua_new((Variant)(*value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Variant");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant_new14(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_new15_local
static int tolua_Core_Variant_new15_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Variant",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ResourceRef",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const ResourceRef* value = ((const ResourceRef*)  tolua_tousertype(tolua_S,2,0));
  {
   Variant* tolua_ret = (Variant*)  Mtolua_new((Variant)(*value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Variant");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant_new14_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_new16
static int tolua_Core_Variant_new16(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Variant",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ResourceRefList",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const ResourceRefList* value = ((const ResourceRefList*)  tolua_tousertype(tolua_S,2,0));
  {
   Variant* tolua_ret = (Variant*)  Mtolua_new((Variant)(*value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Variant");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant_new15(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_new16_local
static int tolua_Core_Variant_new16_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Variant",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ResourceRefList",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const ResourceRefList* value = ((const ResourceRefList*)  tolua_tousertype(tolua_S,2,0));
  {
   Variant* tolua_ret = (Variant*)  Mtolua_new((Variant)(*value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Variant");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant_new15_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_new17
static int tolua_Core_Variant_new17(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Variant",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const IntRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const IntRect* value = ((const IntRect*)  tolua_tousertype(tolua_S,2,0));
  {
   Variant* tolua_ret = (Variant*)  Mtolua_new((Variant)(*value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Variant");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant_new16(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_new17_local
static int tolua_Core_Variant_new17_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Variant",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const IntRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const IntRect* value = ((const IntRect*)  tolua_tousertype(tolua_S,2,0));
  {
   Variant* tolua_ret = (Variant*)  Mtolua_new((Variant)(*value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Variant");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant_new16_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_new18
static int tolua_Core_Variant_new18(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Variant",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const IntVector2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const IntVector2* value = ((const IntVector2*)  tolua_tousertype(tolua_S,2,0));
  {
   Variant* tolua_ret = (Variant*)  Mtolua_new((Variant)(*value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Variant");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant_new17(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_new18_local
static int tolua_Core_Variant_new18_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Variant",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const IntVector2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const IntVector2* value = ((const IntVector2*)  tolua_tousertype(tolua_S,2,0));
  {
   Variant* tolua_ret = (Variant*)  Mtolua_new((Variant)(*value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Variant");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant_new17_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_new19
static int tolua_Core_Variant_new19(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Variant",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const String* type = ((const String*)  tolua_tousertype(tolua_S,2,0));
  const String* value = ((const String*)  tolua_tousertype(tolua_S,3,0));
  {
   Variant* tolua_ret = (Variant*)  Mtolua_new((Variant)(*type,*value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Variant");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant_new18(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_new19_local
static int tolua_Core_Variant_new19_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Variant",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const String* type = ((const String*)  tolua_tousertype(tolua_S,2,0));
  const String* value = ((const String*)  tolua_tousertype(tolua_S,3,0));
  {
   Variant* tolua_ret = (Variant*)  Mtolua_new((Variant)(*type,*value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Variant");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant_new18_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_new20
static int tolua_Core_Variant_new20(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Variant",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  VariantType type = ((VariantType) (int)  tolua_tonumber(tolua_S,2,0));
  const String* value = ((const String*)  tolua_tousertype(tolua_S,3,0));
  {
   Variant* tolua_ret = (Variant*)  Mtolua_new((Variant)(type,*value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Variant");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant_new19(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_new20_local
static int tolua_Core_Variant_new20_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Variant",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  VariantType type = ((VariantType) (int)  tolua_tonumber(tolua_S,2,0));
  const String* value = ((const String*)  tolua_tousertype(tolua_S,3,0));
  {
   Variant* tolua_ret = (Variant*)  Mtolua_new((Variant)(type,*value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Variant");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant_new19_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_new21
static int tolua_Core_Variant_new21(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Variant",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  VariantType type = ((VariantType) (int)  tolua_tonumber(tolua_S,2,0));
  const char* value = ((const char*)  tolua_tostring(tolua_S,3,0));
  {
   Variant* tolua_ret = (Variant*)  Mtolua_new((Variant)(type,value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Variant");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant_new20(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_new21_local
static int tolua_Core_Variant_new21_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Variant",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  VariantType type = ((VariantType) (int)  tolua_tonumber(tolua_S,2,0));
  const char* value = ((const char*)  tolua_tostring(tolua_S,3,0));
  {
   Variant* tolua_ret = (Variant*)  Mtolua_new((Variant)(type,value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Variant");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant_new20_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_new22
static int tolua_Core_Variant_new22(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Variant",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Variant",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const Variant* value = ((const Variant*)  tolua_tousertype(tolua_S,2,0));
  {
   Variant* tolua_ret = (Variant*)  Mtolua_new((Variant)(*value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Variant");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant_new21(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_new22_local
static int tolua_Core_Variant_new22_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Variant",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Variant",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const Variant* value = ((const Variant*)  tolua_tousertype(tolua_S,2,0));
  {
   Variant* tolua_ret = (Variant*)  Mtolua_new((Variant)(*value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Variant");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant_new21_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_delete00
static int tolua_Core_Variant_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Variant",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Variant* self = (Variant*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'", NULL);
#endif
  Mtolua_delete(self);
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Clear of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_Clear00
static int tolua_Core_Variant_Clear00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Variant",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Variant* self = (Variant*)  tolua_tousertype(tolua_S,1,0);
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

/* method: operator== of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant__eq00
static int tolua_Core_Variant__eq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Variant",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Variant",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Variant* self = (const Variant*)  tolua_tousertype(tolua_S,1,0);
  const Variant* rhs = ((const Variant*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator=='", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator==(*rhs);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.eq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant__eq01
static int tolua_Core_Variant__eq01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Variant",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const Variant* self = (const Variant*)  tolua_tousertype(tolua_S,1,0);
  int rhs = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator=='", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator==(rhs);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant__eq00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant__eq02
static int tolua_Core_Variant__eq02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Variant",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const Variant* self = (const Variant*)  tolua_tousertype(tolua_S,1,0);
  unsigned rhs = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator=='", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator==(rhs);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant__eq01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant__eq03
static int tolua_Core_Variant__eq03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Variant",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const Variant* self = (const Variant*)  tolua_tousertype(tolua_S,1,0);
  bool rhs = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator=='", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator==(rhs);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant__eq02(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant__eq04
static int tolua_Core_Variant__eq04(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Variant",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const Variant* self = (const Variant*)  tolua_tousertype(tolua_S,1,0);
  float rhs = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator=='", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator==(rhs);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant__eq03(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant__eq05
static int tolua_Core_Variant__eq05(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Variant",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Variant* self = (Variant*)  tolua_tousertype(tolua_S,1,0);
  const Vector2* rhs = ((const Vector2*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator=='", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator==(*rhs);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant__eq04(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant__eq06
static int tolua_Core_Variant__eq06(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Variant",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const Variant* self = (const Variant*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* rhs = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator=='", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator==(*rhs);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant__eq05(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant__eq07
static int tolua_Core_Variant__eq07(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Variant",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector4",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const Variant* self = (const Variant*)  tolua_tousertype(tolua_S,1,0);
  const Vector4* rhs = ((const Vector4*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator=='", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator==(*rhs);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant__eq06(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant__eq08
static int tolua_Core_Variant__eq08(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Variant",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Quaternion",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const Variant* self = (const Variant*)  tolua_tousertype(tolua_S,1,0);
  const Quaternion* rhs = ((const Quaternion*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator=='", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator==(*rhs);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant__eq07(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant__eq09
static int tolua_Core_Variant__eq09(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Variant",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Color",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const Variant* self = (const Variant*)  tolua_tousertype(tolua_S,1,0);
  const Color* rhs = ((const Color*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator=='", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator==(*rhs);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant__eq08(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant__eq10
static int tolua_Core_Variant__eq10(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Variant",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const Variant* self = (const Variant*)  tolua_tousertype(tolua_S,1,0);
  const String* rhs = ((const String*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator=='", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator==(*rhs);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant__eq09(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant__eq11
static int tolua_Core_Variant__eq11(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Variant",0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const Variant* self = (const Variant*)  tolua_tousertype(tolua_S,1,0);
  void* rhs = ((void*)  tolua_touserdata(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator=='", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator==(rhs);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant__eq10(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant__eq12
static int tolua_Core_Variant__eq12(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Variant",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ResourceRef",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const Variant* self = (const Variant*)  tolua_tousertype(tolua_S,1,0);
  const ResourceRef* rhs = ((const ResourceRef*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator=='", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator==(*rhs);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant__eq11(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant__eq13
static int tolua_Core_Variant__eq13(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Variant",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ResourceRefList",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const Variant* self = (const Variant*)  tolua_tousertype(tolua_S,1,0);
  const ResourceRefList* rhs = ((const ResourceRefList*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator=='", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator==(*rhs);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant__eq12(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant__eq14
static int tolua_Core_Variant__eq14(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Variant",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const IntRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const Variant* self = (const Variant*)  tolua_tousertype(tolua_S,1,0);
  const IntRect* rhs = ((const IntRect*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator=='", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator==(*rhs);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant__eq13(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant__eq15
static int tolua_Core_Variant__eq15(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Variant",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const IntVector2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const Variant* self = (const Variant*)  tolua_tousertype(tolua_S,1,0);
  const IntVector2* rhs = ((const IntVector2*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator=='", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator==(*rhs);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant__eq14(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant__eq16
static int tolua_Core_Variant__eq16(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Variant",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const StringHash",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const Variant* self = (const Variant*)  tolua_tousertype(tolua_S,1,0);
  const StringHash* rhs = ((const StringHash*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator=='", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator==(*rhs);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant__eq15(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant__eq17
static int tolua_Core_Variant__eq17(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Variant",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ShortStringHash",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const Variant* self = (const Variant*)  tolua_tousertype(tolua_S,1,0);
  const ShortStringHash* rhs = ((const ShortStringHash*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator=='", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator==(*rhs);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_Core_Variant__eq16(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetInt of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_GetInt00
static int tolua_Core_Variant_GetInt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Variant",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Variant* self = (const Variant*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetInt'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetInt();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetInt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetUInt of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_GetUInt00
static int tolua_Core_Variant_GetUInt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Variant",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Variant* self = (const Variant*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetUInt'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetUInt();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetUInt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetStringHash of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_GetStringHash00
static int tolua_Core_Variant_GetStringHash00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Variant",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Variant* self = (Variant*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetStringHash'", NULL);
#endif
  {
   StringHash tolua_ret = (StringHash)  self->GetStringHash();
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
 tolua_error(tolua_S,"#ferror in function 'GetStringHash'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetShortStringHash of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_GetShortStringHash00
static int tolua_Core_Variant_GetShortStringHash00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Variant",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Variant* self = (Variant*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetShortStringHash'", NULL);
#endif
  {
   ShortStringHash tolua_ret = (ShortStringHash)  self->GetShortStringHash();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((ShortStringHash)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"ShortStringHash");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(ShortStringHash));
     tolua_pushusertype(tolua_S,tolua_obj,"ShortStringHash");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetShortStringHash'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetBool of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_GetBool00
static int tolua_Core_Variant_GetBool00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Variant",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Variant* self = (const Variant*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetBool'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetBool();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetBool'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFloat of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_GetFloat00
static int tolua_Core_Variant_GetFloat00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Variant",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Variant* self = (const Variant*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFloat'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetFloat();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFloat'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetVector2 of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_GetVector200
static int tolua_Core_Variant_GetVector200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Variant",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Variant* self = (const Variant*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetVector2'", NULL);
#endif
  {
   const Vector2& tolua_ret = (const Vector2&)  self->GetVector2();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Vector2");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetVector2'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetVector3 of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_GetVector300
static int tolua_Core_Variant_GetVector300(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Variant",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Variant* self = (const Variant*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetVector3'", NULL);
#endif
  {
   const Vector3& tolua_ret = (const Vector3&)  self->GetVector3();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Vector3");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetVector3'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetVector4 of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_GetVector400
static int tolua_Core_Variant_GetVector400(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Variant",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Variant* self = (const Variant*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetVector4'", NULL);
#endif
  {
   const Vector4& tolua_ret = (const Vector4&)  self->GetVector4();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Vector4");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetVector4'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetQuaternion of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_GetQuaternion00
static int tolua_Core_Variant_GetQuaternion00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Variant",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Variant* self = (const Variant*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetQuaternion'", NULL);
#endif
  {
   const Quaternion& tolua_ret = (const Quaternion&)  self->GetQuaternion();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Quaternion");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetQuaternion'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetColor of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_GetColor00
static int tolua_Core_Variant_GetColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Variant",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Variant* self = (const Variant*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetColor'", NULL);
#endif
  {
   const Color& tolua_ret = (const Color&)  self->GetColor();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Color");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetString of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_GetString00
static int tolua_Core_Variant_GetString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Variant",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Variant* self = (const Variant*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetString'", NULL);
#endif
  {
   const String& tolua_ret = (const String&)  self->GetString();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const String");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetPtr of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_GetPtr00
static int tolua_Core_Variant_GetPtr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Variant",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Variant* self = (const Variant*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPtr'", NULL);
#endif
  {
   void* tolua_ret = (void*)  self->GetPtr();
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPtr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetResourceRef of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_GetResourceRef00
static int tolua_Core_Variant_GetResourceRef00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Variant",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Variant* self = (const Variant*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetResourceRef'", NULL);
#endif
  {
   const ResourceRef& tolua_ret = (const ResourceRef&)  self->GetResourceRef();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const ResourceRef");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetResourceRef'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetResourceRefList of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_GetResourceRefList00
static int tolua_Core_Variant_GetResourceRefList00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Variant",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Variant* self = (const Variant*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetResourceRefList'", NULL);
#endif
  {
   const ResourceRefList& tolua_ret = (const ResourceRefList&)  self->GetResourceRefList();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const ResourceRefList");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetResourceRefList'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetIntRect of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_GetIntRect00
static int tolua_Core_Variant_GetIntRect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Variant",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Variant* self = (const Variant*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetIntRect'", NULL);
#endif
  {
   const IntRect& tolua_ret = (const IntRect&)  self->GetIntRect();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const IntRect");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetIntRect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetIntVector2 of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_GetIntVector200
static int tolua_Core_Variant_GetIntVector200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Variant",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Variant* self = (const Variant*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetIntVector2'", NULL);
#endif
  {
   const IntVector2& tolua_ret = (const IntVector2&)  self->GetIntVector2();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const IntVector2");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetIntVector2'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetType of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_GetType00
static int tolua_Core_Variant_GetType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Variant",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Variant* self = (const Variant*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetType'", NULL);
#endif
  {
   VariantType tolua_ret = (VariantType)  self->GetType();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTypeName of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_GetTypeName00
static int tolua_Core_Variant_GetTypeName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Variant",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Variant* self = (const Variant*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTypeName'", NULL);
#endif
  {
   String tolua_ret = (String)  self->GetTypeName();
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
 tolua_error(tolua_S,"#ferror in function 'GetTypeName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ToString of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_ToString00
static int tolua_Core_Variant_ToString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Variant",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Variant* self = (const Variant*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ToString'", NULL);
#endif
  {
   String tolua_ret = (String)  self->ToString();
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
 tolua_error(tolua_S,"#ferror in function 'ToString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsZero of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_IsZero00
static int tolua_Core_Variant_IsZero00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Variant",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Variant* self = (const Variant*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsZero'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsZero();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsZero'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsEmpty of class  Variant */
#ifndef TOLUA_DISABLE_tolua_Core_Variant_IsEmpty00
static int tolua_Core_Variant_IsEmpty00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Variant",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Variant* self = (const Variant*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsEmpty'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsEmpty();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsEmpty'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: VariantMapGetInt of class  VariantMap */
#ifndef TOLUA_DISABLE_tolua_Core_VariantMap_GetInt00
static int tolua_Core_VariantMap_GetInt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VariantMap",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  VariantMap* self = (VariantMap*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'VariantMapGetInt'", NULL);
#endif
  {
   tolua_outside int tolua_ret = (tolua_outside int)  VariantMapGetInt(self,key);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetInt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: VariantMapGetBool of class  VariantMap */
#ifndef TOLUA_DISABLE_tolua_Core_VariantMap_GetBool00
static int tolua_Core_VariantMap_GetBool00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VariantMap",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  VariantMap* self = (VariantMap*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'VariantMapGetBool'", NULL);
#endif
  {
   tolua_outside bool tolua_ret = (tolua_outside bool)  VariantMapGetBool(self,key);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetBool'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: VariantMapGetFloat of class  VariantMap */
#ifndef TOLUA_DISABLE_tolua_Core_VariantMap_GetFloat00
static int tolua_Core_VariantMap_GetFloat00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VariantMap",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  VariantMap* self = (VariantMap*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'VariantMapGetFloat'", NULL);
#endif
  {
   tolua_outside float tolua_ret = (tolua_outside float)  VariantMapGetFloat(self,key);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFloat'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: VariantMapGetVector2 of class  VariantMap */
#ifndef TOLUA_DISABLE_tolua_Core_VariantMap_GetVector200
static int tolua_Core_VariantMap_GetVector200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VariantMap",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  VariantMap* self = (VariantMap*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'VariantMapGetVector2'", NULL);
#endif
  {
   tolua_outside  const Vector2& tolua_ret = (tolua_outside  const Vector2&)  VariantMapGetVector2(self,key);
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Vector2");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetVector2'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: VariantMapGetVector3 of class  VariantMap */
#ifndef TOLUA_DISABLE_tolua_Core_VariantMap_GetVector300
static int tolua_Core_VariantMap_GetVector300(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VariantMap",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  VariantMap* self = (VariantMap*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'VariantMapGetVector3'", NULL);
#endif
  {
   tolua_outside  const Vector3& tolua_ret = (tolua_outside  const Vector3&)  VariantMapGetVector3(self,key);
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Vector3");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetVector3'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: VariantMapGetVector4 of class  VariantMap */
#ifndef TOLUA_DISABLE_tolua_Core_VariantMap_GetVector400
static int tolua_Core_VariantMap_GetVector400(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VariantMap",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  VariantMap* self = (VariantMap*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'VariantMapGetVector4'", NULL);
#endif
  {
   tolua_outside  const Vector4& tolua_ret = (tolua_outside  const Vector4&)  VariantMapGetVector4(self,key);
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Vector4");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetVector4'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: VariantMapGetQuaternion of class  VariantMap */
#ifndef TOLUA_DISABLE_tolua_Core_VariantMap_GetQuaternion00
static int tolua_Core_VariantMap_GetQuaternion00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VariantMap",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  VariantMap* self = (VariantMap*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'VariantMapGetQuaternion'", NULL);
#endif
  {
   tolua_outside  const Quaternion& tolua_ret = (tolua_outside  const Quaternion&)  VariantMapGetQuaternion(self,key);
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Quaternion");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetQuaternion'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: VariantMapGetColor of class  VariantMap */
#ifndef TOLUA_DISABLE_tolua_Core_VariantMap_GetColor00
static int tolua_Core_VariantMap_GetColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VariantMap",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  VariantMap* self = (VariantMap*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'VariantMapGetColor'", NULL);
#endif
  {
   tolua_outside  const Color& tolua_ret = (tolua_outside  const Color&)  VariantMapGetColor(self,key);
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Color");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: VariantMapGetString of class  VariantMap */
#ifndef TOLUA_DISABLE_tolua_Core_VariantMap_GetString00
static int tolua_Core_VariantMap_GetString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VariantMap",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  VariantMap* self = (VariantMap*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'VariantMapGetString'", NULL);
#endif
  {
   tolua_outside  const String& tolua_ret = (tolua_outside  const String&)  VariantMapGetString(self,key);
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const String");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: VariantMapGetPtr of class  VariantMap */
#ifndef TOLUA_DISABLE_tolua_Core_VariantMap_GetPtr00
static int tolua_Core_VariantMap_GetPtr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VariantMap",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  VariantMap* self = (VariantMap*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'VariantMapGetPtr'", NULL);
#endif
  {
   tolua_outside  const void* tolua_ret = (tolua_outside  const void*)  VariantMapGetPtr(self,key);
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPtr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: VariantMapGetResourceRef of class  VariantMap */
#ifndef TOLUA_DISABLE_tolua_Core_VariantMap_GetResourceRef00
static int tolua_Core_VariantMap_GetResourceRef00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VariantMap",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  VariantMap* self = (VariantMap*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'VariantMapGetResourceRef'", NULL);
#endif
  {
   tolua_outside  const ResourceRef& tolua_ret = (tolua_outside  const ResourceRef&)  VariantMapGetResourceRef(self,key);
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const ResourceRef");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetResourceRef'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: VariantMapGetResourceRefList of class  VariantMap */
#ifndef TOLUA_DISABLE_tolua_Core_VariantMap_GetResourceRefList00
static int tolua_Core_VariantMap_GetResourceRefList00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VariantMap",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  VariantMap* self = (VariantMap*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'VariantMapGetResourceRefList'", NULL);
#endif
  {
   tolua_outside  const ResourceRefList& tolua_ret = (tolua_outside  const ResourceRefList&)  VariantMapGetResourceRefList(self,key);
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const ResourceRefList");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetResourceRefList'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: VariantMapGetIntRect of class  VariantMap */
#ifndef TOLUA_DISABLE_tolua_Core_VariantMap_GetIntRect00
static int tolua_Core_VariantMap_GetIntRect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VariantMap",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  VariantMap* self = (VariantMap*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'VariantMapGetIntRect'", NULL);
#endif
  {
   tolua_outside  const IntRect& tolua_ret = (tolua_outside  const IntRect&)  VariantMapGetIntRect(self,key);
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const IntRect");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetIntRect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: VariantMapGetIntVector2 of class  VariantMap */
#ifndef TOLUA_DISABLE_tolua_Core_VariantMap_GetIntVector200
static int tolua_Core_VariantMap_GetIntVector200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VariantMap",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  VariantMap* self = (VariantMap*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'VariantMapGetIntVector2'", NULL);
#endif
  {
   tolua_outside  const IntVector2& tolua_ret = (tolua_outside  const IntVector2&)  VariantMapGetIntVector2(self,key);
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const IntVector2");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetIntVector2'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: VariantMapSetInt of class  VariantMap */
#ifndef TOLUA_DISABLE_tolua_Core_VariantMap_SetInt00
static int tolua_Core_VariantMap_SetInt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VariantMap",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  VariantMap* self = (VariantMap*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
  int value = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'VariantMapSetInt'", NULL);
#endif
  {
   VariantMapSetInt(self,key,value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetInt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: VariantMapSetBool of class  VariantMap */
#ifndef TOLUA_DISABLE_tolua_Core_VariantMap_SetBool00
static int tolua_Core_VariantMap_SetBool00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VariantMap",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  VariantMap* self = (VariantMap*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
  bool value = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'VariantMapSetBool'", NULL);
#endif
  {
   VariantMapSetBool(self,key,value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetBool'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: VariantMapSetFloat of class  VariantMap */
#ifndef TOLUA_DISABLE_tolua_Core_VariantMap_SetFloat00
static int tolua_Core_VariantMap_SetFloat00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VariantMap",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  VariantMap* self = (VariantMap*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
  float value = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'VariantMapSetFloat'", NULL);
#endif
  {
   VariantMapSetFloat(self,key,value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFloat'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: VariantMapSetVector2 of class  VariantMap */
#ifndef TOLUA_DISABLE_tolua_Core_VariantMap_SetVector200
static int tolua_Core_VariantMap_SetVector200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VariantMap",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const Vector2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  VariantMap* self = (VariantMap*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
  const Vector2* value = ((const Vector2*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'VariantMapSetVector2'", NULL);
#endif
  {
   VariantMapSetVector2(self,key,*value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetVector2'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: VariantMapSetVector3 of class  VariantMap */
#ifndef TOLUA_DISABLE_tolua_Core_VariantMap_SetVector300
static int tolua_Core_VariantMap_SetVector300(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VariantMap",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  VariantMap* self = (VariantMap*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
  const Vector3* value = ((const Vector3*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'VariantMapSetVector3'", NULL);
#endif
  {
   VariantMapSetVector3(self,key,*value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetVector3'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: VariantMapSetVector4 of class  VariantMap */
#ifndef TOLUA_DISABLE_tolua_Core_VariantMap_SetVector400
static int tolua_Core_VariantMap_SetVector400(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VariantMap",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const Vector4",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  VariantMap* self = (VariantMap*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
  const Vector4* value = ((const Vector4*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'VariantMapSetVector4'", NULL);
#endif
  {
   VariantMapSetVector4(self,key,*value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetVector4'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: VariantMapSetQuaternion of class  VariantMap */
#ifndef TOLUA_DISABLE_tolua_Core_VariantMap_SetQuaternion00
static int tolua_Core_VariantMap_SetQuaternion00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VariantMap",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const Quaternion",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  VariantMap* self = (VariantMap*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
  const Quaternion* value = ((const Quaternion*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'VariantMapSetQuaternion'", NULL);
#endif
  {
   VariantMapSetQuaternion(self,key,*value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetQuaternion'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: VariantMapSetColor of class  VariantMap */
#ifndef TOLUA_DISABLE_tolua_Core_VariantMap_SetColor00
static int tolua_Core_VariantMap_SetColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VariantMap",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const Color",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  VariantMap* self = (VariantMap*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
  const Color* value = ((const Color*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'VariantMapSetColor'", NULL);
#endif
  {
   VariantMapSetColor(self,key,*value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: VariantMapSetString of class  VariantMap */
#ifndef TOLUA_DISABLE_tolua_Core_VariantMap_SetString00
static int tolua_Core_VariantMap_SetString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VariantMap",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  VariantMap* self = (VariantMap*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
  const String* value = ((const String*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'VariantMapSetString'", NULL);
#endif
  {
   VariantMapSetString(self,key,*value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: VariantMapSetPtr of class  VariantMap */
#ifndef TOLUA_DISABLE_tolua_Core_VariantMap_SetPtr00
static int tolua_Core_VariantMap_SetPtr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VariantMap",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  VariantMap* self = (VariantMap*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
  void* value = ((void*)  tolua_touserdata(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'VariantMapSetPtr'", NULL);
#endif
  {
   VariantMapSetPtr(self,key,value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetPtr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: VariantMapSetResourceRef of class  VariantMap */
#ifndef TOLUA_DISABLE_tolua_Core_VariantMap_SetResourceRef00
static int tolua_Core_VariantMap_SetResourceRef00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VariantMap",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const ResourceRef",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  VariantMap* self = (VariantMap*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
  const ResourceRef* value = ((const ResourceRef*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'VariantMapSetResourceRef'", NULL);
#endif
  {
   VariantMapSetResourceRef(self,key,*value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetResourceRef'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: VariantMapSetResourceRefList of class  VariantMap */
#ifndef TOLUA_DISABLE_tolua_Core_VariantMap_SetResourceRefList00
static int tolua_Core_VariantMap_SetResourceRefList00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VariantMap",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const ResourceRefList",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  VariantMap* self = (VariantMap*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
  const ResourceRefList* value = ((const ResourceRefList*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'VariantMapSetResourceRefList'", NULL);
#endif
  {
   VariantMapSetResourceRefList(self,key,*value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetResourceRefList'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: VariantMapSetIntRect of class  VariantMap */
#ifndef TOLUA_DISABLE_tolua_Core_VariantMap_SetIntRect00
static int tolua_Core_VariantMap_SetIntRect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VariantMap",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const IntRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  VariantMap* self = (VariantMap*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
  const IntRect* value = ((const IntRect*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'VariantMapSetIntRect'", NULL);
#endif
  {
   VariantMapSetIntRect(self,key,*value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetIntRect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: VariantMapSetIntVector2 of class  VariantMap */
#ifndef TOLUA_DISABLE_tolua_Core_VariantMap_SetIntVector200
static int tolua_Core_VariantMap_SetIntVector200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"VariantMap",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const IntVector2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  VariantMap* self = (VariantMap*)  tolua_tousertype(tolua_S,1,0);
  const char* key = ((const char*)  tolua_tostring(tolua_S,2,0));
  const IntVector2* value = ((const IntVector2*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'VariantMapSetIntVector2'", NULL);
#endif
  {
   VariantMapSetIntVector2(self,key,*value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetIntVector2'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Timer */
#ifndef TOLUA_DISABLE_tolua_Core_Timer_new00
static int tolua_Core_Timer_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Timer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Timer* tolua_ret = (Timer*)  Mtolua_new((Timer)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Timer");
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

/* method: new_local of class  Timer */
#ifndef TOLUA_DISABLE_tolua_Core_Timer_new00_local
static int tolua_Core_Timer_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Timer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Timer* tolua_ret = (Timer*)  Mtolua_new((Timer)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Timer");
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

/* method: GetMSec of class  Timer */
#ifndef TOLUA_DISABLE_tolua_Core_Timer_GetMSec00
static int tolua_Core_Timer_GetMSec00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Timer",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Timer* self = (Timer*)  tolua_tousertype(tolua_S,1,0);
  bool reset = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMSec'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetMSec(reset);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMSec'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Reset of class  Timer */
#ifndef TOLUA_DISABLE_tolua_Core_Timer_Reset00
static int tolua_Core_Timer_Reset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Timer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Timer* self = (Timer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Reset'", NULL);
#endif
  {
   self->Reset();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Reset'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFrameNumber of class  Time */
#ifndef TOLUA_DISABLE_tolua_Core_Time_GetFrameNumber00
static int tolua_Core_Time_GetFrameNumber00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Time",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Time* self = (const Time*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFrameNumber'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetFrameNumber();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFrameNumber'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTimeStep of class  Time */
#ifndef TOLUA_DISABLE_tolua_Core_Time_GetTimeStep00
static int tolua_Core_Time_GetTimeStep00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Time",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Time* self = (const Time*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTimeStep'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetTimeStep();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTimeStep'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTimerPeriod of class  Time */
#ifndef TOLUA_DISABLE_tolua_Core_Time_GetTimerPeriod00
static int tolua_Core_Time_GetTimerPeriod00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Time",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Time* self = (Time*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTimerPeriod'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetTimerPeriod();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTimerPeriod'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetElapsedTime of class  Time */
#ifndef TOLUA_DISABLE_tolua_Core_Time_GetElapsedTime00
static int tolua_Core_Time_GetElapsedTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Time",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Time* self = (Time*)  tolua_tousertype(tolua_S,1,0);
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

/* function: GetTime */
#ifndef TOLUA_DISABLE_tolua_Core_GetTime00
static int tolua_Core_GetTime00(lua_State* tolua_S)
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
   Time* tolua_ret = (Time*)  GetTime();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Time");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_Core_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_function(tolua_S,"InitFPU",tolua_Core_InitFPU00);
  tolua_function(tolua_S,"ErrorDialog",tolua_Core_ErrorDialog00);
  tolua_function(tolua_S,"ErrorExit",tolua_Core_ErrorExit00);
  tolua_function(tolua_S,"OpenConsoleWindow",tolua_Core_OpenConsoleWindow00);
  tolua_function(tolua_S,"PrintLine",tolua_Core_PrintLine00);
  tolua_function(tolua_S,"GetArguments",tolua_Core_GetArguments00);
  tolua_function(tolua_S,"GetConsoleInput",tolua_Core_GetConsoleInput00);
  tolua_function(tolua_S,"GetPlatform",tolua_Core_GetPlatform00);
  tolua_function(tolua_S,"GetNumPhysicalCPUs",tolua_Core_GetNumPhysicalCPUs00);
  tolua_function(tolua_S,"GetNumLogicalCPUs",tolua_Core_GetNumLogicalCPUs00);
  tolua_function(tolua_S,"ToBool",tolua_Core_ToBool00);
  tolua_function(tolua_S,"ToBool",tolua_Core_ToBool01);
  tolua_function(tolua_S,"ToFloat",tolua_Core_ToFloat00);
  tolua_function(tolua_S,"ToFloat",tolua_Core_ToFloat01);
  tolua_function(tolua_S,"ToInt",tolua_Core_ToInt00);
  tolua_function(tolua_S,"ToInt",tolua_Core_ToInt01);
  tolua_function(tolua_S,"ToUInt",tolua_Core_ToUInt00);
  tolua_function(tolua_S,"ToUInt",tolua_Core_ToUInt01);
  tolua_function(tolua_S,"ToColor",tolua_Core_ToColor00);
  tolua_function(tolua_S,"ToColor",tolua_Core_ToColor01);
  tolua_function(tolua_S,"ToIntRect",tolua_Core_ToIntRect00);
  tolua_function(tolua_S,"ToIntRect",tolua_Core_ToIntRect01);
  tolua_function(tolua_S,"ToIntVector2",tolua_Core_ToIntVector200);
  tolua_function(tolua_S,"ToIntVector2",tolua_Core_ToIntVector201);
  tolua_function(tolua_S,"ToQuaternion",tolua_Core_ToQuaternion00);
  tolua_function(tolua_S,"ToQuaternion",tolua_Core_ToQuaternion01);
  tolua_function(tolua_S,"ToRect",tolua_Core_ToRect00);
  tolua_function(tolua_S,"ToRect",tolua_Core_ToRect01);
  tolua_function(tolua_S,"ToVector2",tolua_Core_ToVector200);
  tolua_function(tolua_S,"ToVector2",tolua_Core_ToVector201);
  tolua_function(tolua_S,"ToVector3",tolua_Core_ToVector300);
  tolua_function(tolua_S,"ToVector3",tolua_Core_ToVector301);
  tolua_function(tolua_S,"ToVector4",tolua_Core_ToVector400);
  tolua_function(tolua_S,"ToVector4",tolua_Core_ToVector401);
  tolua_function(tolua_S,"ToString",tolua_Core_ToString00);
  tolua_function(tolua_S,"ToStringHex",tolua_Core_ToStringHex00);
  tolua_function(tolua_S,"IsAlpha",tolua_Core_IsAlpha00);
  tolua_function(tolua_S,"IsDigit",tolua_Core_IsDigit00);
  tolua_constant(tolua_S,"VAR_NONE",VAR_NONE);
  tolua_constant(tolua_S,"VAR_INT",VAR_INT);
  tolua_constant(tolua_S,"VAR_BOOL",VAR_BOOL);
  tolua_constant(tolua_S,"VAR_FLOAT",VAR_FLOAT);
  tolua_constant(tolua_S,"VAR_VECTOR2",VAR_VECTOR2);
  tolua_constant(tolua_S,"VAR_VECTOR3",VAR_VECTOR3);
  tolua_constant(tolua_S,"VAR_VECTOR4",VAR_VECTOR4);
  tolua_constant(tolua_S,"VAR_QUATERNION",VAR_QUATERNION);
  tolua_constant(tolua_S,"VAR_COLOR",VAR_COLOR);
  tolua_constant(tolua_S,"VAR_STRING",VAR_STRING);
  tolua_constant(tolua_S,"VAR_BUFFER",VAR_BUFFER);
  tolua_constant(tolua_S,"VAR_PTR",VAR_PTR);
  tolua_constant(tolua_S,"VAR_RESOURCEREF",VAR_RESOURCEREF);
  tolua_constant(tolua_S,"VAR_RESOURCEREFLIST",VAR_RESOURCEREFLIST);
  tolua_constant(tolua_S,"VAR_VARIANTVECTOR",VAR_VARIANTVECTOR);
  tolua_constant(tolua_S,"VAR_VARIANTMAP",VAR_VARIANTMAP);
  tolua_constant(tolua_S,"VAR_INTRECT",VAR_INTRECT);
  tolua_constant(tolua_S,"VAR_INTVECTOR2",VAR_INTVECTOR2);
  tolua_constant(tolua_S,"MAX_VAR_TYPES",MAX_VAR_TYPES);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"ResourceRef","ResourceRef","",tolua_collect_ResourceRef);
  #else
  tolua_cclass(tolua_S,"ResourceRef","ResourceRef","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"ResourceRef");
   tolua_function(tolua_S,"new",tolua_Core_ResourceRef_new00);
   tolua_function(tolua_S,"new_local",tolua_Core_ResourceRef_new00_local);
   tolua_function(tolua_S,".call",tolua_Core_ResourceRef_new00_local);
   tolua_function(tolua_S,"new",tolua_Core_ResourceRef_new01);
   tolua_function(tolua_S,"new_local",tolua_Core_ResourceRef_new01_local);
   tolua_function(tolua_S,".call",tolua_Core_ResourceRef_new01_local);
   tolua_function(tolua_S,"new",tolua_Core_ResourceRef_new02);
   tolua_function(tolua_S,"new_local",tolua_Core_ResourceRef_new02_local);
   tolua_function(tolua_S,".call",tolua_Core_ResourceRef_new02_local);
   tolua_function(tolua_S,"new",tolua_Core_ResourceRef_new03);
   tolua_function(tolua_S,"new_local",tolua_Core_ResourceRef_new03_local);
   tolua_function(tolua_S,".call",tolua_Core_ResourceRef_new03_local);
   tolua_variable(tolua_S,"type",tolua_get_ResourceRef_type,tolua_set_ResourceRef_type);
   tolua_variable(tolua_S,"id",tolua_get_ResourceRef_id,tolua_set_ResourceRef_id);
   tolua_function(tolua_S,".eq",tolua_Core_ResourceRef__eq00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"ResourceRefList","ResourceRefList","",tolua_collect_ResourceRefList);
  #else
  tolua_cclass(tolua_S,"ResourceRefList","ResourceRefList","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"ResourceRefList");
   tolua_function(tolua_S,"new",tolua_Core_ResourceRefList_new00);
   tolua_function(tolua_S,"new_local",tolua_Core_ResourceRefList_new00_local);
   tolua_function(tolua_S,".call",tolua_Core_ResourceRefList_new00_local);
   tolua_function(tolua_S,"new",tolua_Core_ResourceRefList_new01);
   tolua_function(tolua_S,"new_local",tolua_Core_ResourceRefList_new01_local);
   tolua_function(tolua_S,".call",tolua_Core_ResourceRefList_new01_local);
   tolua_variable(tolua_S,"type",tolua_get_ResourceRefList_type,tolua_set_ResourceRefList_type);
   tolua_function(tolua_S,".eq",tolua_Core_ResourceRefList__eq00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"Variant","Variant","",tolua_collect_Variant);
  #else
  tolua_cclass(tolua_S,"Variant","Variant","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"Variant");
   tolua_function(tolua_S,"new",tolua_Core_Variant_new00);
   tolua_function(tolua_S,"new_local",tolua_Core_Variant_new00_local);
   tolua_function(tolua_S,".call",tolua_Core_Variant_new00_local);
   tolua_function(tolua_S,"new",tolua_Core_Variant_new01);
   tolua_function(tolua_S,"new_local",tolua_Core_Variant_new01_local);
   tolua_function(tolua_S,".call",tolua_Core_Variant_new01_local);
   tolua_function(tolua_S,"new",tolua_Core_Variant_new02);
   tolua_function(tolua_S,"new_local",tolua_Core_Variant_new02_local);
   tolua_function(tolua_S,".call",tolua_Core_Variant_new02_local);
   tolua_function(tolua_S,"new",tolua_Core_Variant_new03);
   tolua_function(tolua_S,"new_local",tolua_Core_Variant_new03_local);
   tolua_function(tolua_S,".call",tolua_Core_Variant_new03_local);
   tolua_function(tolua_S,"new",tolua_Core_Variant_new04);
   tolua_function(tolua_S,"new_local",tolua_Core_Variant_new04_local);
   tolua_function(tolua_S,".call",tolua_Core_Variant_new04_local);
   tolua_function(tolua_S,"new",tolua_Core_Variant_new05);
   tolua_function(tolua_S,"new_local",tolua_Core_Variant_new05_local);
   tolua_function(tolua_S,".call",tolua_Core_Variant_new05_local);
   tolua_function(tolua_S,"new",tolua_Core_Variant_new06);
   tolua_function(tolua_S,"new_local",tolua_Core_Variant_new06_local);
   tolua_function(tolua_S,".call",tolua_Core_Variant_new06_local);
   tolua_function(tolua_S,"new",tolua_Core_Variant_new07);
   tolua_function(tolua_S,"new_local",tolua_Core_Variant_new07_local);
   tolua_function(tolua_S,".call",tolua_Core_Variant_new07_local);
   tolua_function(tolua_S,"new",tolua_Core_Variant_new08);
   tolua_function(tolua_S,"new_local",tolua_Core_Variant_new08_local);
   tolua_function(tolua_S,".call",tolua_Core_Variant_new08_local);
   tolua_function(tolua_S,"new",tolua_Core_Variant_new09);
   tolua_function(tolua_S,"new_local",tolua_Core_Variant_new09_local);
   tolua_function(tolua_S,".call",tolua_Core_Variant_new09_local);
   tolua_function(tolua_S,"new",tolua_Core_Variant_new10);
   tolua_function(tolua_S,"new_local",tolua_Core_Variant_new10_local);
   tolua_function(tolua_S,".call",tolua_Core_Variant_new10_local);
   tolua_function(tolua_S,"new",tolua_Core_Variant_new11);
   tolua_function(tolua_S,"new_local",tolua_Core_Variant_new11_local);
   tolua_function(tolua_S,".call",tolua_Core_Variant_new11_local);
   tolua_function(tolua_S,"new",tolua_Core_Variant_new12);
   tolua_function(tolua_S,"new_local",tolua_Core_Variant_new12_local);
   tolua_function(tolua_S,".call",tolua_Core_Variant_new12_local);
   tolua_function(tolua_S,"new",tolua_Core_Variant_new13);
   tolua_function(tolua_S,"new_local",tolua_Core_Variant_new13_local);
   tolua_function(tolua_S,".call",tolua_Core_Variant_new13_local);
   tolua_function(tolua_S,"new",tolua_Core_Variant_new14);
   tolua_function(tolua_S,"new_local",tolua_Core_Variant_new14_local);
   tolua_function(tolua_S,".call",tolua_Core_Variant_new14_local);
   tolua_function(tolua_S,"new",tolua_Core_Variant_new15);
   tolua_function(tolua_S,"new_local",tolua_Core_Variant_new15_local);
   tolua_function(tolua_S,".call",tolua_Core_Variant_new15_local);
   tolua_function(tolua_S,"new",tolua_Core_Variant_new16);
   tolua_function(tolua_S,"new_local",tolua_Core_Variant_new16_local);
   tolua_function(tolua_S,".call",tolua_Core_Variant_new16_local);
   tolua_function(tolua_S,"new",tolua_Core_Variant_new17);
   tolua_function(tolua_S,"new_local",tolua_Core_Variant_new17_local);
   tolua_function(tolua_S,".call",tolua_Core_Variant_new17_local);
   tolua_function(tolua_S,"new",tolua_Core_Variant_new18);
   tolua_function(tolua_S,"new_local",tolua_Core_Variant_new18_local);
   tolua_function(tolua_S,".call",tolua_Core_Variant_new18_local);
   tolua_function(tolua_S,"new",tolua_Core_Variant_new19);
   tolua_function(tolua_S,"new_local",tolua_Core_Variant_new19_local);
   tolua_function(tolua_S,".call",tolua_Core_Variant_new19_local);
   tolua_function(tolua_S,"new",tolua_Core_Variant_new20);
   tolua_function(tolua_S,"new_local",tolua_Core_Variant_new20_local);
   tolua_function(tolua_S,".call",tolua_Core_Variant_new20_local);
   tolua_function(tolua_S,"new",tolua_Core_Variant_new21);
   tolua_function(tolua_S,"new_local",tolua_Core_Variant_new21_local);
   tolua_function(tolua_S,".call",tolua_Core_Variant_new21_local);
   tolua_function(tolua_S,"new",tolua_Core_Variant_new22);
   tolua_function(tolua_S,"new_local",tolua_Core_Variant_new22_local);
   tolua_function(tolua_S,".call",tolua_Core_Variant_new22_local);
   tolua_function(tolua_S,"delete",tolua_Core_Variant_delete00);
   tolua_function(tolua_S,"Clear",tolua_Core_Variant_Clear00);
   tolua_function(tolua_S,".eq",tolua_Core_Variant__eq00);
   tolua_function(tolua_S,".eq",tolua_Core_Variant__eq01);
   tolua_function(tolua_S,".eq",tolua_Core_Variant__eq02);
   tolua_function(tolua_S,".eq",tolua_Core_Variant__eq03);
   tolua_function(tolua_S,".eq",tolua_Core_Variant__eq04);
   tolua_function(tolua_S,".eq",tolua_Core_Variant__eq05);
   tolua_function(tolua_S,".eq",tolua_Core_Variant__eq06);
   tolua_function(tolua_S,".eq",tolua_Core_Variant__eq07);
   tolua_function(tolua_S,".eq",tolua_Core_Variant__eq08);
   tolua_function(tolua_S,".eq",tolua_Core_Variant__eq09);
   tolua_function(tolua_S,".eq",tolua_Core_Variant__eq10);
   tolua_function(tolua_S,".eq",tolua_Core_Variant__eq11);
   tolua_function(tolua_S,".eq",tolua_Core_Variant__eq12);
   tolua_function(tolua_S,".eq",tolua_Core_Variant__eq13);
   tolua_function(tolua_S,".eq",tolua_Core_Variant__eq14);
   tolua_function(tolua_S,".eq",tolua_Core_Variant__eq15);
   tolua_function(tolua_S,".eq",tolua_Core_Variant__eq16);
   tolua_function(tolua_S,".eq",tolua_Core_Variant__eq17);
   tolua_function(tolua_S,"GetInt",tolua_Core_Variant_GetInt00);
   tolua_function(tolua_S,"GetUInt",tolua_Core_Variant_GetUInt00);
   tolua_function(tolua_S,"GetStringHash",tolua_Core_Variant_GetStringHash00);
   tolua_function(tolua_S,"GetShortStringHash",tolua_Core_Variant_GetShortStringHash00);
   tolua_function(tolua_S,"GetBool",tolua_Core_Variant_GetBool00);
   tolua_function(tolua_S,"GetFloat",tolua_Core_Variant_GetFloat00);
   tolua_function(tolua_S,"GetVector2",tolua_Core_Variant_GetVector200);
   tolua_function(tolua_S,"GetVector3",tolua_Core_Variant_GetVector300);
   tolua_function(tolua_S,"GetVector4",tolua_Core_Variant_GetVector400);
   tolua_function(tolua_S,"GetQuaternion",tolua_Core_Variant_GetQuaternion00);
   tolua_function(tolua_S,"GetColor",tolua_Core_Variant_GetColor00);
   tolua_function(tolua_S,"GetString",tolua_Core_Variant_GetString00);
   tolua_function(tolua_S,"GetPtr",tolua_Core_Variant_GetPtr00);
   tolua_function(tolua_S,"GetResourceRef",tolua_Core_Variant_GetResourceRef00);
   tolua_function(tolua_S,"GetResourceRefList",tolua_Core_Variant_GetResourceRefList00);
   tolua_function(tolua_S,"GetIntRect",tolua_Core_Variant_GetIntRect00);
   tolua_function(tolua_S,"GetIntVector2",tolua_Core_Variant_GetIntVector200);
   tolua_function(tolua_S,"GetType",tolua_Core_Variant_GetType00);
   tolua_function(tolua_S,"GetTypeName",tolua_Core_Variant_GetTypeName00);
   tolua_function(tolua_S,"ToString",tolua_Core_Variant_ToString00);
   tolua_function(tolua_S,"IsZero",tolua_Core_Variant_IsZero00);
   tolua_function(tolua_S,"IsEmpty",tolua_Core_Variant_IsEmpty00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"VariantMap","VariantMap","",NULL);
  tolua_beginmodule(tolua_S,"VariantMap");
   tolua_function(tolua_S,"GetInt",tolua_Core_VariantMap_GetInt00);
   tolua_function(tolua_S,"GetBool",tolua_Core_VariantMap_GetBool00);
   tolua_function(tolua_S,"GetFloat",tolua_Core_VariantMap_GetFloat00);
   tolua_function(tolua_S,"GetVector2",tolua_Core_VariantMap_GetVector200);
   tolua_function(tolua_S,"GetVector3",tolua_Core_VariantMap_GetVector300);
   tolua_function(tolua_S,"GetVector4",tolua_Core_VariantMap_GetVector400);
   tolua_function(tolua_S,"GetQuaternion",tolua_Core_VariantMap_GetQuaternion00);
   tolua_function(tolua_S,"GetColor",tolua_Core_VariantMap_GetColor00);
   tolua_function(tolua_S,"GetString",tolua_Core_VariantMap_GetString00);
   tolua_function(tolua_S,"GetPtr",tolua_Core_VariantMap_GetPtr00);
   tolua_function(tolua_S,"GetResourceRef",tolua_Core_VariantMap_GetResourceRef00);
   tolua_function(tolua_S,"GetResourceRefList",tolua_Core_VariantMap_GetResourceRefList00);
   tolua_function(tolua_S,"GetIntRect",tolua_Core_VariantMap_GetIntRect00);
   tolua_function(tolua_S,"GetIntVector2",tolua_Core_VariantMap_GetIntVector200);
   tolua_function(tolua_S,"SetInt",tolua_Core_VariantMap_SetInt00);
   tolua_function(tolua_S,"SetBool",tolua_Core_VariantMap_SetBool00);
   tolua_function(tolua_S,"SetFloat",tolua_Core_VariantMap_SetFloat00);
   tolua_function(tolua_S,"SetVector2",tolua_Core_VariantMap_SetVector200);
   tolua_function(tolua_S,"SetVector3",tolua_Core_VariantMap_SetVector300);
   tolua_function(tolua_S,"SetVector4",tolua_Core_VariantMap_SetVector400);
   tolua_function(tolua_S,"SetQuaternion",tolua_Core_VariantMap_SetQuaternion00);
   tolua_function(tolua_S,"SetColor",tolua_Core_VariantMap_SetColor00);
   tolua_function(tolua_S,"SetString",tolua_Core_VariantMap_SetString00);
   tolua_function(tolua_S,"SetPtr",tolua_Core_VariantMap_SetPtr00);
   tolua_function(tolua_S,"SetResourceRef",tolua_Core_VariantMap_SetResourceRef00);
   tolua_function(tolua_S,"SetResourceRefList",tolua_Core_VariantMap_SetResourceRefList00);
   tolua_function(tolua_S,"SetIntRect",tolua_Core_VariantMap_SetIntRect00);
   tolua_function(tolua_S,"SetIntVector2",tolua_Core_VariantMap_SetIntVector200);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"Timer","Timer","",tolua_collect_Timer);
  #else
  tolua_cclass(tolua_S,"Timer","Timer","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"Timer");
   tolua_function(tolua_S,"new",tolua_Core_Timer_new00);
   tolua_function(tolua_S,"new_local",tolua_Core_Timer_new00_local);
   tolua_function(tolua_S,".call",tolua_Core_Timer_new00_local);
   tolua_function(tolua_S,"GetMSec",tolua_Core_Timer_GetMSec00);
   tolua_function(tolua_S,"Reset",tolua_Core_Timer_Reset00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Time","Time","Object",NULL);
  tolua_beginmodule(tolua_S,"Time");
   tolua_function(tolua_S,"GetFrameNumber",tolua_Core_Time_GetFrameNumber00);
   tolua_function(tolua_S,"GetTimeStep",tolua_Core_Time_GetTimeStep00);
   tolua_function(tolua_S,"GetTimerPeriod",tolua_Core_Time_GetTimerPeriod00);
   tolua_function(tolua_S,"GetElapsedTime",tolua_Core_Time_GetElapsedTime00);
  tolua_endmodule(tolua_S);
  tolua_function(tolua_S,"GetTime",tolua_Core_GetTime00);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_Core (lua_State* tolua_S) {
 return tolua_Core_open(tolua_S);
};
#endif

