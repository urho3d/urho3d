/*
** Lua binding: Container
** Generated automatically by tolua++-1.0.92 on 06/30/13 11:31:48.
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
TOLUA_API int  tolua_Container_open (lua_State* tolua_S);

#define TOLUA_RELEASE
#include "ContainerLuaAPI.h"
#include "Str.h"
using namespace Urho3D;
#pragma warning(disable:4800)

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_String (lua_State* tolua_S)
{
 String* self = (String*) tolua_tousertype(tolua_S,1,0);
  Mtolua_delete(self);
  return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"String");
}

/* method: new of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_new00
static int tolua_Container_String_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"String",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   String* tolua_ret = (String*)  Mtolua_new((String)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"String");
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

/* method: new_local of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_new00_local
static int tolua_Container_String_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"String",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   String* tolua_ret = (String*)  Mtolua_new((String)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"String");
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

/* method: new of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_new01
static int tolua_Container_String_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"String",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const String* str = ((const String*)  tolua_tousertype(tolua_S,2,0));
  {
   String* tolua_ret = (String*)  Mtolua_new((String)(*str));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"String");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Container_String_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_new01_local
static int tolua_Container_String_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"String",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const String* str = ((const String*)  tolua_tousertype(tolua_S,2,0));
  {
   String* tolua_ret = (String*)  Mtolua_new((String)(*str));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"String");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_Container_String_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_new02
static int tolua_Container_String_new02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"String",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* str = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   String* tolua_ret = (String*)  Mtolua_new((String)(str));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"String");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Container_String_new01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_new02_local
static int tolua_Container_String_new02_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"String",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* str = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   String* tolua_ret = (String*)  Mtolua_new((String)(str));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"String");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_Container_String_new01_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_new03
static int tolua_Container_String_new03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"String",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* str = ((const char*)  tolua_tostring(tolua_S,2,0));
  unsigned length = ((unsigned)  tolua_tonumber(tolua_S,3,0));
  {
   String* tolua_ret = (String*)  Mtolua_new((String)(str,length));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"String");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Container_String_new02(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_new03_local
static int tolua_Container_String_new03_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"String",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* str = ((const char*)  tolua_tostring(tolua_S,2,0));
  unsigned length = ((unsigned)  tolua_tonumber(tolua_S,3,0));
  {
   String* tolua_ret = (String*)  Mtolua_new((String)(str,length));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"String");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_Container_String_new02_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_new04
static int tolua_Container_String_new04(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"String",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  int value = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   String* tolua_ret = (String*)  Mtolua_new((String)(value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"String");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Container_String_new03(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_new04_local
static int tolua_Container_String_new04_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"String",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  int value = ((int)  tolua_tonumber(tolua_S,2,0));
  {
   String* tolua_ret = (String*)  Mtolua_new((String)(value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"String");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_Container_String_new03_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_new05
static int tolua_Container_String_new05(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"String",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  short value = ((short)  tolua_tonumber(tolua_S,2,0));
  {
   String* tolua_ret = (String*)  Mtolua_new((String)(value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"String");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Container_String_new04(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_new05_local
static int tolua_Container_String_new05_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"String",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  short value = ((short)  tolua_tonumber(tolua_S,2,0));
  {
   String* tolua_ret = (String*)  Mtolua_new((String)(value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"String");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_Container_String_new04_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_new06
static int tolua_Container_String_new06(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"String",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  long value = ((long)  tolua_tonumber(tolua_S,2,0));
  {
   String* tolua_ret = (String*)  Mtolua_new((String)(value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"String");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Container_String_new05(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_new06_local
static int tolua_Container_String_new06_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"String",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  long value = ((long)  tolua_tonumber(tolua_S,2,0));
  {
   String* tolua_ret = (String*)  Mtolua_new((String)(value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"String");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_Container_String_new05_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_new07
static int tolua_Container_String_new07(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"String",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  long long value = ((long long)  tolua_tonumber(tolua_S,2,0));
  {
   String* tolua_ret = (String*)  Mtolua_new((String)(value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"String");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Container_String_new06(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_new07_local
static int tolua_Container_String_new07_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"String",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  long long value = ((long long)  tolua_tonumber(tolua_S,2,0));
  {
   String* tolua_ret = (String*)  Mtolua_new((String)(value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"String");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_Container_String_new06_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_new08
static int tolua_Container_String_new08(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"String",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  unsigned value = ((unsigned)  tolua_tonumber(tolua_S,2,0));
  {
   String* tolua_ret = (String*)  Mtolua_new((String)(value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"String");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Container_String_new07(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_new08_local
static int tolua_Container_String_new08_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"String",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  unsigned value = ((unsigned)  tolua_tonumber(tolua_S,2,0));
  {
   String* tolua_ret = (String*)  Mtolua_new((String)(value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"String");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_Container_String_new07_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_new09
static int tolua_Container_String_new09(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"String",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  unsigned short value = ((unsigned short)  tolua_tonumber(tolua_S,2,0));
  {
   String* tolua_ret = (String*)  Mtolua_new((String)(value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"String");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Container_String_new08(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_new09_local
static int tolua_Container_String_new09_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"String",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  unsigned short value = ((unsigned short)  tolua_tonumber(tolua_S,2,0));
  {
   String* tolua_ret = (String*)  Mtolua_new((String)(value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"String");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_Container_String_new08_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_new10
static int tolua_Container_String_new10(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"String",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  unsigned long value = ((unsigned long)  tolua_tonumber(tolua_S,2,0));
  {
   String* tolua_ret = (String*)  Mtolua_new((String)(value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"String");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Container_String_new09(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_new10_local
static int tolua_Container_String_new10_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"String",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  unsigned long value = ((unsigned long)  tolua_tonumber(tolua_S,2,0));
  {
   String* tolua_ret = (String*)  Mtolua_new((String)(value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"String");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_Container_String_new09_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_new11
static int tolua_Container_String_new11(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"String",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  unsigned long long value = ((unsigned long long)  tolua_tonumber(tolua_S,2,0));
  {
   String* tolua_ret = (String*)  Mtolua_new((String)(value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"String");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Container_String_new10(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_new11_local
static int tolua_Container_String_new11_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"String",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  unsigned long long value = ((unsigned long long)  tolua_tonumber(tolua_S,2,0));
  {
   String* tolua_ret = (String*)  Mtolua_new((String)(value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"String");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_Container_String_new10_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_new12
static int tolua_Container_String_new12(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"String",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float value = ((float)  tolua_tonumber(tolua_S,2,0));
  {
   String* tolua_ret = (String*)  Mtolua_new((String)(value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"String");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Container_String_new11(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_new12_local
static int tolua_Container_String_new12_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"String",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  float value = ((float)  tolua_tonumber(tolua_S,2,0));
  {
   String* tolua_ret = (String*)  Mtolua_new((String)(value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"String");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_Container_String_new11_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_new13
static int tolua_Container_String_new13(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"String",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  double value = ((double)  tolua_tonumber(tolua_S,2,0));
  {
   String* tolua_ret = (String*)  Mtolua_new((String)(value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"String");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Container_String_new12(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_new13_local
static int tolua_Container_String_new13_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"String",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  double value = ((double)  tolua_tonumber(tolua_S,2,0));
  {
   String* tolua_ret = (String*)  Mtolua_new((String)(value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"String");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_Container_String_new12_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_new14
static int tolua_Container_String_new14(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"String",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  bool value = ((bool)  tolua_toboolean(tolua_S,2,0));
  {
   String* tolua_ret = (String*)  Mtolua_new((String)(value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"String");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Container_String_new13(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_new14_local
static int tolua_Container_String_new14_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"String",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  bool value = ((bool)  tolua_toboolean(tolua_S,2,0));
  {
   String* tolua_ret = (String*)  Mtolua_new((String)(value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"String");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_Container_String_new13_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_new15
static int tolua_Container_String_new15(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"String",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  char value = ((char)  tolua_tonumber(tolua_S,2,0));
  {
   String* tolua_ret = (String*)  Mtolua_new((String)(value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"String");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Container_String_new14(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_new15_local
static int tolua_Container_String_new15_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"String",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  char value = ((char)  tolua_tonumber(tolua_S,2,0));
  {
   String* tolua_ret = (String*)  Mtolua_new((String)(value));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"String");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_Container_String_new14_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_new16
static int tolua_Container_String_new16(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"String",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  char value = ((char)  tolua_tonumber(tolua_S,2,0));
  unsigned length = ((unsigned)  tolua_tonumber(tolua_S,3,0));
  {
   String* tolua_ret = (String*)  Mtolua_new((String)(value,length));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"String");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Container_String_new15(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_new16_local
static int tolua_Container_String_new16_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"String",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  char value = ((char)  tolua_tonumber(tolua_S,2,0));
  unsigned length = ((unsigned)  tolua_tonumber(tolua_S,3,0));
  {
   String* tolua_ret = (String*)  Mtolua_new((String)(value,length));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"String");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_Container_String_new15_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_delete00
static int tolua_Container_String_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"String",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  String* self = (String*)  tolua_tousertype(tolua_S,1,0);
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

/* method: operator+ of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String__add00
static int tolua_Container_String__add00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const String",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const String* self = (const String*)  tolua_tousertype(tolua_S,1,0);
  const String* rhs = ((const String*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator+'", NULL);
#endif
  {
   String tolua_ret = (String)  self->operator+(*rhs);
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
 tolua_error(tolua_S,"#ferror in function '.add'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator+ of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String__add01
static int tolua_Container_String__add01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const String",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const String* self = (const String*)  tolua_tousertype(tolua_S,1,0);
  const char* rhs = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator+'", NULL);
#endif
  {
   String tolua_ret = (String)  self->operator+(rhs);
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
tolua_lerror:
 return tolua_Container_String__add00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator+ of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String__add02
static int tolua_Container_String__add02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const String",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const String* self = (const String*)  tolua_tousertype(tolua_S,1,0);
  char rhs = ((char)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator+'", NULL);
#endif
  {
   String tolua_ret = (String)  self->operator+(rhs);
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
tolua_lerror:
 return tolua_Container_String__add01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String__eq00
static int tolua_Container_String__eq00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const String",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const String* self = (const String*)  tolua_tousertype(tolua_S,1,0);
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
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.eq'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator< of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String__lt00
static int tolua_Container_String__lt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const String",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const String* self = (const String*)  tolua_tousertype(tolua_S,1,0);
  const String* rhs = ((const String*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator<'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator<(*rhs);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.lt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator== of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String__eq01
static int tolua_Container_String__eq01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const String",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const String* self = (const String*)  tolua_tousertype(tolua_S,1,0);
  const char* rhs = ((const char*)  tolua_tostring(tolua_S,2,0));
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
 return tolua_Container_String__eq00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: operator< of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String__lt01
static int tolua_Container_String__lt01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const String",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const String* self = (const String*)  tolua_tousertype(tolua_S,1,0);
  const char* rhs = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operator<'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator<(rhs);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_Container_String__lt00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: At of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_At00
static int tolua_Container_String_At00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"String",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  String* self = (String*)  tolua_tousertype(tolua_S,1,0);
  unsigned index = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'At'", NULL);
#endif
  {
   char tolua_ret = (char)  self->At(index);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'At'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: At of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_At01
static int tolua_Container_String_At01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const String",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const String* self = (const String*)  tolua_tousertype(tolua_S,1,0);
  unsigned index = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'At'", NULL);
#endif
  {
   const char tolua_ret = (const char)  self->At(index);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_Container_String_At00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: Replace of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_Replace00
static int tolua_Container_String_Replace00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"String",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  String* self = (String*)  tolua_tousertype(tolua_S,1,0);
  char replaceThis = ((char)  tolua_tonumber(tolua_S,2,0));
  char replaceWith = ((char)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Replace'", NULL);
#endif
  {
   self->Replace(replaceThis,replaceWith);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Replace'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Replace of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_Replace01
static int tolua_Container_String_Replace01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"String",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  String* self = (String*)  tolua_tousertype(tolua_S,1,0);
  const String* replaceThis = ((const String*)  tolua_tousertype(tolua_S,2,0));
  const String* replaceWith = ((const String*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Replace'", NULL);
#endif
  {
   self->Replace(*replaceThis,*replaceWith);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Container_String_Replace00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: Replace of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_Replace02
static int tolua_Container_String_Replace02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"String",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  String* self = (String*)  tolua_tousertype(tolua_S,1,0);
  unsigned pos = ((unsigned)  tolua_tonumber(tolua_S,2,0));
  unsigned length = ((unsigned)  tolua_tonumber(tolua_S,3,0));
  const String* replaceWith = ((const String*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Replace'", NULL);
#endif
  {
   self->Replace(pos,length,*replaceWith);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Container_String_Replace01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: Replaced of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_Replaced00
static int tolua_Container_String_Replaced00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const String",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const String* self = (const String*)  tolua_tousertype(tolua_S,1,0);
  char replaceThis = ((char)  tolua_tonumber(tolua_S,2,0));
  char replaceWith = ((char)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Replaced'", NULL);
#endif
  {
   String tolua_ret = (String)  self->Replaced(replaceThis,replaceWith);
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
 tolua_error(tolua_S,"#ferror in function 'Replaced'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Replaced of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_Replaced01
static int tolua_Container_String_Replaced01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const String",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const String* self = (const String*)  tolua_tousertype(tolua_S,1,0);
  const String* replaceThis = ((const String*)  tolua_tousertype(tolua_S,2,0));
  const String* replaceWith = ((const String*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Replaced'", NULL);
#endif
  {
   String tolua_ret = (String)  self->Replaced(*replaceThis,*replaceWith);
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
tolua_lerror:
 return tolua_Container_String_Replaced00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: Append of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_Append00
static int tolua_Container_String_Append00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"String",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  String* self = (String*)  tolua_tousertype(tolua_S,1,0);
  const String* str = ((const String*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Append'", NULL);
#endif
  {
   String& tolua_ret = (String&)  self->Append(*str);
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"String");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Append'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Append of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_Append01
static int tolua_Container_String_Append01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"String",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  String* self = (String*)  tolua_tousertype(tolua_S,1,0);
  const char* str = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Append'", NULL);
#endif
  {
   String& tolua_ret = (String&)  self->Append(str);
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"String");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Container_String_Append00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: Append of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_Append02
static int tolua_Container_String_Append02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"String",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  String* self = (String*)  tolua_tousertype(tolua_S,1,0);
  char c = ((char)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Append'", NULL);
#endif
  {
   String& tolua_ret = (String&)  self->Append(c);
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"String");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Container_String_Append01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: Append of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_Append03
static int tolua_Container_String_Append03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"String",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  String* self = (String*)  tolua_tousertype(tolua_S,1,0);
  const char* str = ((const char*)  tolua_tostring(tolua_S,2,0));
  unsigned length = ((unsigned)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Append'", NULL);
#endif
  {
   String& tolua_ret = (String&)  self->Append(str,length);
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"String");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Container_String_Append02(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: Insert of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_Insert00
static int tolua_Container_String_Insert00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"String",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  String* self = (String*)  tolua_tousertype(tolua_S,1,0);
  unsigned pos = ((unsigned)  tolua_tonumber(tolua_S,2,0));
  const String* str = ((const String*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Insert'", NULL);
#endif
  {
   self->Insert(pos,*str);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Insert'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Insert of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_Insert01
static int tolua_Container_String_Insert01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"String",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  String* self = (String*)  tolua_tousertype(tolua_S,1,0);
  unsigned pos = ((unsigned)  tolua_tonumber(tolua_S,2,0));
  char c = ((char)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Insert'", NULL);
#endif
  {
   self->Insert(pos,c);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Container_String_Insert00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: Erase of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_Erase00
static int tolua_Container_String_Erase00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"String",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  String* self = (String*)  tolua_tousertype(tolua_S,1,0);
  unsigned pos = ((unsigned)  tolua_tonumber(tolua_S,2,0));
  unsigned length = ((unsigned)  tolua_tonumber(tolua_S,3,1));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Erase'", NULL);
#endif
  {
   self->Erase(pos,length);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Erase'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Resize of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_Resize00
static int tolua_Container_String_Resize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"String",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  String* self = (String*)  tolua_tousertype(tolua_S,1,0);
  unsigned newLength = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Resize'", NULL);
#endif
  {
   self->Resize(newLength);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Resize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Reserve of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_Reserve00
static int tolua_Container_String_Reserve00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"String",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  String* self = (String*)  tolua_tousertype(tolua_S,1,0);
  unsigned newCapacity = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Reserve'", NULL);
#endif
  {
   self->Reserve(newCapacity);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Reserve'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Compact of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_Compact00
static int tolua_Container_String_Compact00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"String",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  String* self = (String*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Compact'", NULL);
#endif
  {
   self->Compact();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Compact'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Clear of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_Clear00
static int tolua_Container_String_Clear00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"String",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  String* self = (String*)  tolua_tousertype(tolua_S,1,0);
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

/* method: Swap of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_Swap00
static int tolua_Container_String_Swap00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"String",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  String* self = (String*)  tolua_tousertype(tolua_S,1,0);
  String* str = ((String*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Swap'", NULL);
#endif
  {
   self->Swap(*str);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Swap'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Front of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_Front00
static int tolua_Container_String_Front00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const String",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const String* self = (const String*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Front'", NULL);
#endif
  {
   char tolua_ret = (char)  self->Front();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Front'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Back of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_Back00
static int tolua_Container_String_Back00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const String",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const String* self = (const String*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Back'", NULL);
#endif
  {
   char tolua_ret = (char)  self->Back();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Back'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Substring of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_Substring00
static int tolua_Container_String_Substring00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const String",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const String* self = (const String*)  tolua_tousertype(tolua_S,1,0);
  unsigned pos = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Substring'", NULL);
#endif
  {
   String tolua_ret = (String)  self->Substring(pos);
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
 tolua_error(tolua_S,"#ferror in function 'Substring'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Substring of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_Substring01
static int tolua_Container_String_Substring01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const String",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const String* self = (const String*)  tolua_tousertype(tolua_S,1,0);
  unsigned pos = ((unsigned)  tolua_tonumber(tolua_S,2,0));
  unsigned length = ((unsigned)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Substring'", NULL);
#endif
  {
   String tolua_ret = (String)  self->Substring(pos,length);
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
tolua_lerror:
 return tolua_Container_String_Substring00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: Trimmed of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_Trimmed00
static int tolua_Container_String_Trimmed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const String",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const String* self = (const String*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Trimmed'", NULL);
#endif
  {
   String tolua_ret = (String)  self->Trimmed();
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
 tolua_error(tolua_S,"#ferror in function 'Trimmed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ToUpper of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_ToUpper00
static int tolua_Container_String_ToUpper00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const String",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const String* self = (const String*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ToUpper'", NULL);
#endif
  {
   String tolua_ret = (String)  self->ToUpper();
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
 tolua_error(tolua_S,"#ferror in function 'ToUpper'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ToLower of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_ToLower00
static int tolua_Container_String_ToLower00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const String",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const String* self = (const String*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ToLower'", NULL);
#endif
  {
   String tolua_ret = (String)  self->ToLower();
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
 tolua_error(tolua_S,"#ferror in function 'ToLower'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Find of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_Find00
static int tolua_Container_String_Find00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const String",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const String* self = (const String*)  tolua_tousertype(tolua_S,1,0);
  const String* str = ((const String*)  tolua_tousertype(tolua_S,2,0));
  unsigned startPos = ((unsigned)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Find'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->Find(*str,startPos);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Find'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Find of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_Find01
static int tolua_Container_String_Find01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const String",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const String* self = (const String*)  tolua_tousertype(tolua_S,1,0);
  char c = ((char)  tolua_tonumber(tolua_S,2,0));
  unsigned startPos = ((unsigned)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Find'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->Find(c,startPos);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_Container_String_Find00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: FindLast of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_FindLast00
static int tolua_Container_String_FindLast00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const String",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const String* self = (const String*)  tolua_tousertype(tolua_S,1,0);
  const String* str = ((const String*)  tolua_tousertype(tolua_S,2,0));
  unsigned startPos = ((unsigned)  tolua_tonumber(tolua_S,3,String::NPOS));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FindLast'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->FindLast(*str,startPos);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FindLast'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: FindLast of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_FindLast01
static int tolua_Container_String_FindLast01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const String",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const String* self = (const String*)  tolua_tousertype(tolua_S,1,0);
  char c = ((char)  tolua_tonumber(tolua_S,2,0));
  unsigned startPos = ((unsigned)  tolua_tonumber(tolua_S,3,String::NPOS));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FindLast'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->FindLast(c,startPos);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_Container_String_FindLast00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: StartsWith of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_StartsWith00
static int tolua_Container_String_StartsWith00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const String",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const String* self = (const String*)  tolua_tousertype(tolua_S,1,0);
  const String* str = ((const String*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'StartsWith'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->StartsWith(*str);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'StartsWith'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: EndsWith of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_EndsWith00
static int tolua_Container_String_EndsWith00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const String",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const String* self = (const String*)  tolua_tousertype(tolua_S,1,0);
  const String* str = ((const String*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'EndsWith'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->EndsWith(*str);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'EndsWith'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CString of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_CString00
static int tolua_Container_String_CString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const String",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const String* self = (const String*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CString'", NULL);
#endif
  {
   const char* tolua_ret = (const char*)  self->CString();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CString'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Length of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_Length00
static int tolua_Container_String_Length00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const String",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const String* self = (const String*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Length'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->Length();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Length'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Capacity of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_Capacity00
static int tolua_Container_String_Capacity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const String",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const String* self = (const String*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Capacity'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->Capacity();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Capacity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Empty of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_Empty00
static int tolua_Container_String_Empty00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const String",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const String* self = (const String*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Empty'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Empty();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Empty'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Compare of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_Compare00
static int tolua_Container_String_Compare00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const String",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const String* self = (const String*)  tolua_tousertype(tolua_S,1,0);
  const String* str = ((const String*)  tolua_tousertype(tolua_S,2,0));
  bool caseSensitive = ((bool)  tolua_toboolean(tolua_S,3,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Compare'", NULL);
#endif
  {
   int tolua_ret = (int)  self->Compare(*str,caseSensitive);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Compare'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Compare of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_Compare01
static int tolua_Container_String_Compare01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const String",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const String* self = (const String*)  tolua_tousertype(tolua_S,1,0);
  const char* str = ((const char*)  tolua_tostring(tolua_S,2,0));
  bool caseSensitive = ((bool)  tolua_toboolean(tolua_S,3,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Compare'", NULL);
#endif
  {
   int tolua_ret = (int)  self->Compare(str,caseSensitive);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_Container_String_Compare00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: Contains of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_Contains00
static int tolua_Container_String_Contains00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const String",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const String* self = (const String*)  tolua_tousertype(tolua_S,1,0);
  const String* str = ((const String*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Contains'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Contains(*str);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Contains'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Contains of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_Contains01
static int tolua_Container_String_Contains01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const String",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const String* self = (const String*)  tolua_tousertype(tolua_S,1,0);
  char c = ((char)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Contains'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Contains(c);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_Container_String_Contains00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: ToHash of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_ToHash00
static int tolua_Container_String_ToHash00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const String",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const String* self = (const String*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ToHash'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->ToHash();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ToHash'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CStringLength of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_CStringLength00
static int tolua_Container_String_CStringLength00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"String",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* str = ((const char*)  tolua_tostring(tolua_S,2,0));
  {
   unsigned tolua_ret = (unsigned)  String::CStringLength(str);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CStringLength'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Compare of class  String */
#ifndef TOLUA_DISABLE_tolua_Container_String_Compare02
static int tolua_Container_String_Compare02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"String",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* str1 = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* str2 = ((const char*)  tolua_tostring(tolua_S,3,0));
  bool caseSensitive = ((bool)  tolua_toboolean(tolua_S,4,0));
  {
   int tolua_ret = (int)  String::Compare(str1,str2,caseSensitive);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_Container_String_Compare01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* get function: EMPTY of class  String */
#ifndef TOLUA_DISABLE_tolua_get_String_EMPTY
static int tolua_get_String_EMPTY(lua_State* tolua_S)
{
   tolua_pushusertype(tolua_S,(void*)&String::EMPTY,"const String");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_Container_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"String","String","",tolua_collect_String);
  #else
  tolua_cclass(tolua_S,"String","String","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"String");
   tolua_function(tolua_S,"new",tolua_Container_String_new00);
   tolua_function(tolua_S,"new_local",tolua_Container_String_new00_local);
   tolua_function(tolua_S,".call",tolua_Container_String_new00_local);
   tolua_function(tolua_S,"new",tolua_Container_String_new01);
   tolua_function(tolua_S,"new_local",tolua_Container_String_new01_local);
   tolua_function(tolua_S,".call",tolua_Container_String_new01_local);
   tolua_function(tolua_S,"new",tolua_Container_String_new02);
   tolua_function(tolua_S,"new_local",tolua_Container_String_new02_local);
   tolua_function(tolua_S,".call",tolua_Container_String_new02_local);
   tolua_function(tolua_S,"new",tolua_Container_String_new03);
   tolua_function(tolua_S,"new_local",tolua_Container_String_new03_local);
   tolua_function(tolua_S,".call",tolua_Container_String_new03_local);
   tolua_function(tolua_S,"new",tolua_Container_String_new04);
   tolua_function(tolua_S,"new_local",tolua_Container_String_new04_local);
   tolua_function(tolua_S,".call",tolua_Container_String_new04_local);
   tolua_function(tolua_S,"new",tolua_Container_String_new05);
   tolua_function(tolua_S,"new_local",tolua_Container_String_new05_local);
   tolua_function(tolua_S,".call",tolua_Container_String_new05_local);
   tolua_function(tolua_S,"new",tolua_Container_String_new06);
   tolua_function(tolua_S,"new_local",tolua_Container_String_new06_local);
   tolua_function(tolua_S,".call",tolua_Container_String_new06_local);
   tolua_function(tolua_S,"new",tolua_Container_String_new07);
   tolua_function(tolua_S,"new_local",tolua_Container_String_new07_local);
   tolua_function(tolua_S,".call",tolua_Container_String_new07_local);
   tolua_function(tolua_S,"new",tolua_Container_String_new08);
   tolua_function(tolua_S,"new_local",tolua_Container_String_new08_local);
   tolua_function(tolua_S,".call",tolua_Container_String_new08_local);
   tolua_function(tolua_S,"new",tolua_Container_String_new09);
   tolua_function(tolua_S,"new_local",tolua_Container_String_new09_local);
   tolua_function(tolua_S,".call",tolua_Container_String_new09_local);
   tolua_function(tolua_S,"new",tolua_Container_String_new10);
   tolua_function(tolua_S,"new_local",tolua_Container_String_new10_local);
   tolua_function(tolua_S,".call",tolua_Container_String_new10_local);
   tolua_function(tolua_S,"new",tolua_Container_String_new11);
   tolua_function(tolua_S,"new_local",tolua_Container_String_new11_local);
   tolua_function(tolua_S,".call",tolua_Container_String_new11_local);
   tolua_function(tolua_S,"new",tolua_Container_String_new12);
   tolua_function(tolua_S,"new_local",tolua_Container_String_new12_local);
   tolua_function(tolua_S,".call",tolua_Container_String_new12_local);
   tolua_function(tolua_S,"new",tolua_Container_String_new13);
   tolua_function(tolua_S,"new_local",tolua_Container_String_new13_local);
   tolua_function(tolua_S,".call",tolua_Container_String_new13_local);
   tolua_function(tolua_S,"new",tolua_Container_String_new14);
   tolua_function(tolua_S,"new_local",tolua_Container_String_new14_local);
   tolua_function(tolua_S,".call",tolua_Container_String_new14_local);
   tolua_function(tolua_S,"new",tolua_Container_String_new15);
   tolua_function(tolua_S,"new_local",tolua_Container_String_new15_local);
   tolua_function(tolua_S,".call",tolua_Container_String_new15_local);
   tolua_function(tolua_S,"new",tolua_Container_String_new16);
   tolua_function(tolua_S,"new_local",tolua_Container_String_new16_local);
   tolua_function(tolua_S,".call",tolua_Container_String_new16_local);
   tolua_function(tolua_S,"delete",tolua_Container_String_delete00);
   tolua_function(tolua_S,".add",tolua_Container_String__add00);
   tolua_function(tolua_S,".add",tolua_Container_String__add01);
   tolua_function(tolua_S,".add",tolua_Container_String__add02);
   tolua_function(tolua_S,".eq",tolua_Container_String__eq00);
   tolua_function(tolua_S,".lt",tolua_Container_String__lt00);
   tolua_function(tolua_S,".eq",tolua_Container_String__eq01);
   tolua_function(tolua_S,".lt",tolua_Container_String__lt01);
   tolua_function(tolua_S,"At",tolua_Container_String_At00);
   tolua_function(tolua_S,"At",tolua_Container_String_At01);
   tolua_function(tolua_S,"Replace",tolua_Container_String_Replace00);
   tolua_function(tolua_S,"Replace",tolua_Container_String_Replace01);
   tolua_function(tolua_S,"Replace",tolua_Container_String_Replace02);
   tolua_function(tolua_S,"Replaced",tolua_Container_String_Replaced00);
   tolua_function(tolua_S,"Replaced",tolua_Container_String_Replaced01);
   tolua_function(tolua_S,"Append",tolua_Container_String_Append00);
   tolua_function(tolua_S,"Append",tolua_Container_String_Append01);
   tolua_function(tolua_S,"Append",tolua_Container_String_Append02);
   tolua_function(tolua_S,"Append",tolua_Container_String_Append03);
   tolua_function(tolua_S,"Insert",tolua_Container_String_Insert00);
   tolua_function(tolua_S,"Insert",tolua_Container_String_Insert01);
   tolua_function(tolua_S,"Erase",tolua_Container_String_Erase00);
   tolua_function(tolua_S,"Resize",tolua_Container_String_Resize00);
   tolua_function(tolua_S,"Reserve",tolua_Container_String_Reserve00);
   tolua_function(tolua_S,"Compact",tolua_Container_String_Compact00);
   tolua_function(tolua_S,"Clear",tolua_Container_String_Clear00);
   tolua_function(tolua_S,"Swap",tolua_Container_String_Swap00);
   tolua_function(tolua_S,"Front",tolua_Container_String_Front00);
   tolua_function(tolua_S,"Back",tolua_Container_String_Back00);
   tolua_function(tolua_S,"Substring",tolua_Container_String_Substring00);
   tolua_function(tolua_S,"Substring",tolua_Container_String_Substring01);
   tolua_function(tolua_S,"Trimmed",tolua_Container_String_Trimmed00);
   tolua_function(tolua_S,"ToUpper",tolua_Container_String_ToUpper00);
   tolua_function(tolua_S,"ToLower",tolua_Container_String_ToLower00);
   tolua_function(tolua_S,"Find",tolua_Container_String_Find00);
   tolua_function(tolua_S,"Find",tolua_Container_String_Find01);
   tolua_function(tolua_S,"FindLast",tolua_Container_String_FindLast00);
   tolua_function(tolua_S,"FindLast",tolua_Container_String_FindLast01);
   tolua_function(tolua_S,"StartsWith",tolua_Container_String_StartsWith00);
   tolua_function(tolua_S,"EndsWith",tolua_Container_String_EndsWith00);
   tolua_function(tolua_S,"CString",tolua_Container_String_CString00);
   tolua_function(tolua_S,"Length",tolua_Container_String_Length00);
   tolua_function(tolua_S,"Capacity",tolua_Container_String_Capacity00);
   tolua_function(tolua_S,"Empty",tolua_Container_String_Empty00);
   tolua_function(tolua_S,"Compare",tolua_Container_String_Compare00);
   tolua_function(tolua_S,"Compare",tolua_Container_String_Compare01);
   tolua_function(tolua_S,"Contains",tolua_Container_String_Contains00);
   tolua_function(tolua_S,"Contains",tolua_Container_String_Contains01);
   tolua_function(tolua_S,"ToHash",tolua_Container_String_ToHash00);
   tolua_function(tolua_S,"CStringLength",tolua_Container_String_CStringLength00);
   tolua_function(tolua_S,"Compare",tolua_Container_String_Compare02);
   tolua_variable(tolua_S,"EMPTY",tolua_get_String_EMPTY,NULL);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_Container (lua_State* tolua_S) {
 return tolua_Container_open(tolua_S);
};
#endif

