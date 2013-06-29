/*
** Lua binding: Engine
** Generated automatically by tolua++-1.0.92 on 06/29/13 19:40:25.
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
TOLUA_API int  tolua_Engine_open (lua_State* tolua_S);

#define TOLUA_RELEASE
#include "EngineLuaAPI.h"
#include "Console.h"
#include "DebugHud.h"
#include "Engine.h"
using namespace Urho3D;
#pragma warning(disable:4800)

/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"DebugHud");
 tolua_usertype(tolua_S,"XMLFile");
 tolua_usertype(tolua_S,"Text");
 tolua_usertype(tolua_S,"Engine");
 tolua_usertype(tolua_S,"Object");
 tolua_usertype(tolua_S,"Variant");
 tolua_usertype(tolua_S,"Console");
 tolua_usertype(tolua_S,"LineEdit");
 tolua_usertype(tolua_S,"String");
 tolua_usertype(tolua_S,"BorderImage");
}

/* method: SetDefaultStyle of class  Console */
#ifndef TOLUA_DISABLE_tolua_Engine_Console_SetDefaultStyle00
static int tolua_Engine_Console_SetDefaultStyle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Console",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"XMLFile",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Console* self = (Console*)  tolua_tousertype(tolua_S,1,0);
  XMLFile* style = ((XMLFile*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetDefaultStyle'", NULL);
#endif
  {
   self->SetDefaultStyle(style);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetDefaultStyle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetVisible of class  Console */
#ifndef TOLUA_DISABLE_tolua_Engine_Console_SetVisible00
static int tolua_Engine_Console_SetVisible00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Console",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Console* self = (Console*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetVisible'", NULL);
#endif
  {
   self->SetVisible(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetVisible'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Toggle of class  Console */
#ifndef TOLUA_DISABLE_tolua_Engine_Console_Toggle00
static int tolua_Engine_Console_Toggle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Console",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Console* self = (Console*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Toggle'", NULL);
#endif
  {
   self->Toggle();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Toggle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetNumRows of class  Console */
#ifndef TOLUA_DISABLE_tolua_Engine_Console_SetNumRows00
static int tolua_Engine_Console_SetNumRows00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Console",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Console* self = (Console*)  tolua_tousertype(tolua_S,1,0);
  unsigned rows = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetNumRows'", NULL);
#endif
  {
   self->SetNumRows(rows);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetNumRows'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetNumHistoryRows of class  Console */
#ifndef TOLUA_DISABLE_tolua_Engine_Console_SetNumHistoryRows00
static int tolua_Engine_Console_SetNumHistoryRows00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Console",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Console* self = (Console*)  tolua_tousertype(tolua_S,1,0);
  unsigned rows = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetNumHistoryRows'", NULL);
#endif
  {
   self->SetNumHistoryRows(rows);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetNumHistoryRows'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: UpdateElements of class  Console */
#ifndef TOLUA_DISABLE_tolua_Engine_Console_UpdateElements00
static int tolua_Engine_Console_UpdateElements00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Console",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Console* self = (Console*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'UpdateElements'", NULL);
#endif
  {
   self->UpdateElements();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'UpdateElements'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetDefaultStyle of class  Console */
#ifndef TOLUA_DISABLE_tolua_Engine_Console_GetDefaultStyle00
static int tolua_Engine_Console_GetDefaultStyle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Console",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Console* self = (const Console*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetDefaultStyle'", NULL);
#endif
  {
   XMLFile* tolua_ret = (XMLFile*)  self->GetDefaultStyle();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"XMLFile");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDefaultStyle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetBackground of class  Console */
#ifndef TOLUA_DISABLE_tolua_Engine_Console_GetBackground00
static int tolua_Engine_Console_GetBackground00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Console",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Console* self = (const Console*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetBackground'", NULL);
#endif
  {
   BorderImage* tolua_ret = (BorderImage*)  self->GetBackground();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BorderImage");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetBackground'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLineEdit of class  Console */
#ifndef TOLUA_DISABLE_tolua_Engine_Console_GetLineEdit00
static int tolua_Engine_Console_GetLineEdit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Console",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Console* self = (const Console*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLineEdit'", NULL);
#endif
  {
   LineEdit* tolua_ret = (LineEdit*)  self->GetLineEdit();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"LineEdit");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLineEdit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsVisible of class  Console */
#ifndef TOLUA_DISABLE_tolua_Engine_Console_IsVisible00
static int tolua_Engine_Console_IsVisible00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Console",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Console* self = (const Console*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsVisible'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsVisible();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsVisible'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNumRows of class  Console */
#ifndef TOLUA_DISABLE_tolua_Engine_Console_GetNumRows00
static int tolua_Engine_Console_GetNumRows00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Console",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Console* self = (const Console*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNumRows'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetNumRows();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNumRows'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNumHistoryRows of class  Console */
#ifndef TOLUA_DISABLE_tolua_Engine_Console_GetNumHistoryRows00
static int tolua_Engine_Console_GetNumHistoryRows00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Console",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Console* self = (const Console*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNumHistoryRows'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetNumHistoryRows();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNumHistoryRows'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetHistoryPosition of class  Console */
#ifndef TOLUA_DISABLE_tolua_Engine_Console_GetHistoryPosition00
static int tolua_Engine_Console_GetHistoryPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Console",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Console* self = (const Console*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetHistoryPosition'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetHistoryPosition();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetHistoryPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetHistoryRow of class  Console */
#ifndef TOLUA_DISABLE_tolua_Engine_Console_GetHistoryRow00
static int tolua_Engine_Console_GetHistoryRow00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Console",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Console* self = (const Console*)  tolua_tousertype(tolua_S,1,0);
  unsigned index = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetHistoryRow'", NULL);
#endif
  {
   const String& tolua_ret = (const String&)  self->GetHistoryRow(index);
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const String");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetHistoryRow'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GetConsole */
#ifndef TOLUA_DISABLE_tolua_Engine_GetConsole00
static int tolua_Engine_GetConsole00(lua_State* tolua_S)
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
   Console* tolua_ret = (Console*)  GetConsole();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Console");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetConsole'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: DEBUGHUD_SHOW_NONE */
#ifndef TOLUA_DISABLE_tolua_get_DEBUGHUD_SHOW_NONE
static int tolua_get_DEBUGHUD_SHOW_NONE(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)DEBUGHUD_SHOW_NONE);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: DEBUGHUD_SHOW_STATS */
#ifndef TOLUA_DISABLE_tolua_get_DEBUGHUD_SHOW_STATS
static int tolua_get_DEBUGHUD_SHOW_STATS(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)DEBUGHUD_SHOW_STATS);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: DEBUGHUD_SHOW_MODE */
#ifndef TOLUA_DISABLE_tolua_get_DEBUGHUD_SHOW_MODE
static int tolua_get_DEBUGHUD_SHOW_MODE(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)DEBUGHUD_SHOW_MODE);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: DEBUGHUD_SHOW_PROFILER */
#ifndef TOLUA_DISABLE_tolua_get_DEBUGHUD_SHOW_PROFILER
static int tolua_get_DEBUGHUD_SHOW_PROFILER(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)DEBUGHUD_SHOW_PROFILER);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: DEBUGHUD_SHOW_ALL */
#ifndef TOLUA_DISABLE_tolua_get_DEBUGHUD_SHOW_ALL
static int tolua_get_DEBUGHUD_SHOW_ALL(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)DEBUGHUD_SHOW_ALL);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: Update of class  DebugHud */
#ifndef TOLUA_DISABLE_tolua_Engine_DebugHud_Update00
static int tolua_Engine_DebugHud_Update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DebugHud",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DebugHud* self = (DebugHud*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Update'", NULL);
#endif
  {
   self->Update();
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

/* method: SetDefaultStyle of class  DebugHud */
#ifndef TOLUA_DISABLE_tolua_Engine_DebugHud_SetDefaultStyle00
static int tolua_Engine_DebugHud_SetDefaultStyle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DebugHud",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"XMLFile",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DebugHud* self = (DebugHud*)  tolua_tousertype(tolua_S,1,0);
  XMLFile* style = ((XMLFile*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetDefaultStyle'", NULL);
#endif
  {
   self->SetDefaultStyle(style);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetDefaultStyle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMode of class  DebugHud */
#ifndef TOLUA_DISABLE_tolua_Engine_DebugHud_SetMode00
static int tolua_Engine_DebugHud_SetMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DebugHud",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DebugHud* self = (DebugHud*)  tolua_tousertype(tolua_S,1,0);
  unsigned mode = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMode'", NULL);
#endif
  {
   self->SetMode(mode);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetProfilerMaxDepth of class  DebugHud */
#ifndef TOLUA_DISABLE_tolua_Engine_DebugHud_SetProfilerMaxDepth00
static int tolua_Engine_DebugHud_SetProfilerMaxDepth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DebugHud",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DebugHud* self = (DebugHud*)  tolua_tousertype(tolua_S,1,0);
  unsigned depth = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetProfilerMaxDepth'", NULL);
#endif
  {
   self->SetProfilerMaxDepth(depth);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetProfilerMaxDepth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetProfilerInterval of class  DebugHud */
#ifndef TOLUA_DISABLE_tolua_Engine_DebugHud_SetProfilerInterval00
static int tolua_Engine_DebugHud_SetProfilerInterval00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DebugHud",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DebugHud* self = (DebugHud*)  tolua_tousertype(tolua_S,1,0);
  float interval = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetProfilerInterval'", NULL);
#endif
  {
   self->SetProfilerInterval(interval);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetProfilerInterval'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetUseRendererStats of class  DebugHud */
#ifndef TOLUA_DISABLE_tolua_Engine_DebugHud_SetUseRendererStats00
static int tolua_Engine_DebugHud_SetUseRendererStats00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DebugHud",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DebugHud* self = (DebugHud*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetUseRendererStats'", NULL);
#endif
  {
   self->SetUseRendererStats(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetUseRendererStats'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Toggle of class  DebugHud */
#ifndef TOLUA_DISABLE_tolua_Engine_DebugHud_Toggle00
static int tolua_Engine_DebugHud_Toggle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DebugHud",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DebugHud* self = (DebugHud*)  tolua_tousertype(tolua_S,1,0);
  unsigned mode = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Toggle'", NULL);
#endif
  {
   self->Toggle(mode);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Toggle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ToggleAll of class  DebugHud */
#ifndef TOLUA_DISABLE_tolua_Engine_DebugHud_ToggleAll00
static int tolua_Engine_DebugHud_ToggleAll00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DebugHud",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DebugHud* self = (DebugHud*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ToggleAll'", NULL);
#endif
  {
   self->ToggleAll();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ToggleAll'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetDefaultStyle of class  DebugHud */
#ifndef TOLUA_DISABLE_tolua_Engine_DebugHud_GetDefaultStyle00
static int tolua_Engine_DebugHud_GetDefaultStyle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const DebugHud",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const DebugHud* self = (const DebugHud*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetDefaultStyle'", NULL);
#endif
  {
   XMLFile* tolua_ret = (XMLFile*)  self->GetDefaultStyle();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"XMLFile");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDefaultStyle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetStatsText of class  DebugHud */
#ifndef TOLUA_DISABLE_tolua_Engine_DebugHud_GetStatsText00
static int tolua_Engine_DebugHud_GetStatsText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const DebugHud",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const DebugHud* self = (const DebugHud*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetStatsText'", NULL);
#endif
  {
   Text* tolua_ret = (Text*)  self->GetStatsText();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Text");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetStatsText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetModeText of class  DebugHud */
#ifndef TOLUA_DISABLE_tolua_Engine_DebugHud_GetModeText00
static int tolua_Engine_DebugHud_GetModeText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const DebugHud",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const DebugHud* self = (const DebugHud*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetModeText'", NULL);
#endif
  {
   Text* tolua_ret = (Text*)  self->GetModeText();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Text");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetModeText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetProfilerText of class  DebugHud */
#ifndef TOLUA_DISABLE_tolua_Engine_DebugHud_GetProfilerText00
static int tolua_Engine_DebugHud_GetProfilerText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const DebugHud",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const DebugHud* self = (const DebugHud*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetProfilerText'", NULL);
#endif
  {
   Text* tolua_ret = (Text*)  self->GetProfilerText();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Text");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetProfilerText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMode of class  DebugHud */
#ifndef TOLUA_DISABLE_tolua_Engine_DebugHud_GetMode00
static int tolua_Engine_DebugHud_GetMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const DebugHud",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const DebugHud* self = (const DebugHud*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMode'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetMode();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetProfilerMaxDepth of class  DebugHud */
#ifndef TOLUA_DISABLE_tolua_Engine_DebugHud_GetProfilerMaxDepth00
static int tolua_Engine_DebugHud_GetProfilerMaxDepth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const DebugHud",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const DebugHud* self = (const DebugHud*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetProfilerMaxDepth'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetProfilerMaxDepth();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetProfilerMaxDepth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetProfilerInterval of class  DebugHud */
#ifndef TOLUA_DISABLE_tolua_Engine_DebugHud_GetProfilerInterval00
static int tolua_Engine_DebugHud_GetProfilerInterval00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const DebugHud",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const DebugHud* self = (const DebugHud*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetProfilerInterval'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetProfilerInterval();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetProfilerInterval'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetUseRendererStats of class  DebugHud */
#ifndef TOLUA_DISABLE_tolua_Engine_DebugHud_GetUseRendererStats00
static int tolua_Engine_DebugHud_GetUseRendererStats00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const DebugHud",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const DebugHud* self = (const DebugHud*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetUseRendererStats'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetUseRendererStats();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetUseRendererStats'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetAppStats of class  DebugHud */
#ifndef TOLUA_DISABLE_tolua_Engine_DebugHud_SetAppStats00
static int tolua_Engine_DebugHud_SetAppStats00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DebugHud",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const Variant",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DebugHud* self = (DebugHud*)  tolua_tousertype(tolua_S,1,0);
  const String* label = ((const String*)  tolua_tousertype(tolua_S,2,0));
  const Variant* stats = ((const Variant*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetAppStats'", NULL);
#endif
  {
   self->SetAppStats(*label,*stats);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetAppStats'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetAppStats of class  DebugHud */
#ifndef TOLUA_DISABLE_tolua_Engine_DebugHud_SetAppStats01
static int tolua_Engine_DebugHud_SetAppStats01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DebugHud",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  DebugHud* self = (DebugHud*)  tolua_tousertype(tolua_S,1,0);
  const String* label = ((const String*)  tolua_tousertype(tolua_S,2,0));
  const String* stats = ((const String*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetAppStats'", NULL);
#endif
  {
   self->SetAppStats(*label,*stats);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Engine_DebugHud_SetAppStats00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: ResetAppStats of class  DebugHud */
#ifndef TOLUA_DISABLE_tolua_Engine_DebugHud_ResetAppStats00
static int tolua_Engine_DebugHud_ResetAppStats00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DebugHud",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DebugHud* self = (DebugHud*)  tolua_tousertype(tolua_S,1,0);
  const String* label = ((const String*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ResetAppStats'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->ResetAppStats(*label);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ResetAppStats'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ClearAppStats of class  DebugHud */
#ifndef TOLUA_DISABLE_tolua_Engine_DebugHud_ClearAppStats00
static int tolua_Engine_DebugHud_ClearAppStats00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DebugHud",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DebugHud* self = (DebugHud*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ClearAppStats'", NULL);
#endif
  {
   self->ClearAppStats();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ClearAppStats'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GetDebugHud */
#ifndef TOLUA_DISABLE_tolua_Engine_GetDebugHud00
static int tolua_Engine_GetDebugHud00(lua_State* tolua_S)
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
   DebugHud* tolua_ret = (DebugHud*)  GetDebugHud();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DebugHud");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDebugHud'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RunFrame of class  Engine */
#ifndef TOLUA_DISABLE_tolua_Engine_Engine_RunFrame00
static int tolua_Engine_Engine_RunFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Engine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Engine* self = (Engine*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RunFrame'", NULL);
#endif
  {
   self->RunFrame();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RunFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CreateConsole of class  Engine */
#ifndef TOLUA_DISABLE_tolua_Engine_Engine_CreateConsole00
static int tolua_Engine_Engine_CreateConsole00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Engine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Engine* self = (Engine*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CreateConsole'", NULL);
#endif
  {
   Console* tolua_ret = (Console*)  self->CreateConsole();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Console");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CreateConsole'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CreateDebugHud of class  Engine */
#ifndef TOLUA_DISABLE_tolua_Engine_Engine_CreateDebugHud00
static int tolua_Engine_Engine_CreateDebugHud00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Engine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Engine* self = (Engine*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CreateDebugHud'", NULL);
#endif
  {
   DebugHud* tolua_ret = (DebugHud*)  self->CreateDebugHud();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DebugHud");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CreateDebugHud'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMinFps of class  Engine */
#ifndef TOLUA_DISABLE_tolua_Engine_Engine_SetMinFps00
static int tolua_Engine_Engine_SetMinFps00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Engine",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Engine* self = (Engine*)  tolua_tousertype(tolua_S,1,0);
  int fps = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMinFps'", NULL);
#endif
  {
   self->SetMinFps(fps);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMinFps'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMaxFps of class  Engine */
#ifndef TOLUA_DISABLE_tolua_Engine_Engine_SetMaxFps00
static int tolua_Engine_Engine_SetMaxFps00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Engine",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Engine* self = (Engine*)  tolua_tousertype(tolua_S,1,0);
  int fps = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMaxFps'", NULL);
#endif
  {
   self->SetMaxFps(fps);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMaxFps'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMaxInactiveFps of class  Engine */
#ifndef TOLUA_DISABLE_tolua_Engine_Engine_SetMaxInactiveFps00
static int tolua_Engine_Engine_SetMaxInactiveFps00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Engine",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Engine* self = (Engine*)  tolua_tousertype(tolua_S,1,0);
  int fps = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMaxInactiveFps'", NULL);
#endif
  {
   self->SetMaxInactiveFps(fps);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMaxInactiveFps'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetPauseMinimized of class  Engine */
#ifndef TOLUA_DISABLE_tolua_Engine_Engine_SetPauseMinimized00
static int tolua_Engine_Engine_SetPauseMinimized00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Engine",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Engine* self = (Engine*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetPauseMinimized'", NULL);
#endif
  {
   self->SetPauseMinimized(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetPauseMinimized'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Exit of class  Engine */
#ifndef TOLUA_DISABLE_tolua_Engine_Engine_Exit00
static int tolua_Engine_Engine_Exit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Engine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Engine* self = (Engine*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Exit'", NULL);
#endif
  {
   self->Exit();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Exit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DumpProfiler of class  Engine */
#ifndef TOLUA_DISABLE_tolua_Engine_Engine_DumpProfiler00
static int tolua_Engine_Engine_DumpProfiler00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Engine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Engine* self = (Engine*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DumpProfiler'", NULL);
#endif
  {
   self->DumpProfiler();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DumpProfiler'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DumpResources of class  Engine */
#ifndef TOLUA_DISABLE_tolua_Engine_Engine_DumpResources00
static int tolua_Engine_Engine_DumpResources00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Engine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Engine* self = (Engine*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DumpResources'", NULL);
#endif
  {
   self->DumpResources();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DumpResources'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DumpMemory of class  Engine */
#ifndef TOLUA_DISABLE_tolua_Engine_Engine_DumpMemory00
static int tolua_Engine_Engine_DumpMemory00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Engine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Engine* self = (Engine*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DumpMemory'", NULL);
#endif
  {
   self->DumpMemory();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DumpMemory'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMinFps of class  Engine */
#ifndef TOLUA_DISABLE_tolua_Engine_Engine_GetMinFps00
static int tolua_Engine_Engine_GetMinFps00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Engine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Engine* self = (const Engine*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMinFps'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetMinFps();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMinFps'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMaxFps of class  Engine */
#ifndef TOLUA_DISABLE_tolua_Engine_Engine_GetMaxFps00
static int tolua_Engine_Engine_GetMaxFps00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Engine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Engine* self = (const Engine*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMaxFps'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetMaxFps();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMaxFps'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMaxInactiveFps of class  Engine */
#ifndef TOLUA_DISABLE_tolua_Engine_Engine_GetMaxInactiveFps00
static int tolua_Engine_Engine_GetMaxInactiveFps00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Engine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Engine* self = (const Engine*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMaxInactiveFps'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetMaxInactiveFps();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMaxInactiveFps'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetPauseMinimized of class  Engine */
#ifndef TOLUA_DISABLE_tolua_Engine_Engine_GetPauseMinimized00
static int tolua_Engine_Engine_GetPauseMinimized00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Engine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Engine* self = (const Engine*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPauseMinimized'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetPauseMinimized();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPauseMinimized'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsInitialized of class  Engine */
#ifndef TOLUA_DISABLE_tolua_Engine_Engine_IsInitialized00
static int tolua_Engine_Engine_IsInitialized00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Engine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Engine* self = (const Engine*)  tolua_tousertype(tolua_S,1,0);
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

/* method: IsExiting of class  Engine */
#ifndef TOLUA_DISABLE_tolua_Engine_Engine_IsExiting00
static int tolua_Engine_Engine_IsExiting00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Engine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Engine* self = (const Engine*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsExiting'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsExiting();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsExiting'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsHeadless of class  Engine */
#ifndef TOLUA_DISABLE_tolua_Engine_Engine_IsHeadless00
static int tolua_Engine_Engine_IsHeadless00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Engine",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Engine* self = (const Engine*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsHeadless'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsHeadless();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsHeadless'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GetEngine */
#ifndef TOLUA_DISABLE_tolua_Engine_GetEngine00
static int tolua_Engine_GetEngine00(lua_State* tolua_S)
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
   Engine* tolua_ret = (Engine*)  GetEngine();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Engine");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetEngine'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_Engine_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,1);
 tolua_beginmodule(tolua_S,NULL);
  tolua_cclass(tolua_S,"Console","Console","Object",NULL);
  tolua_beginmodule(tolua_S,"Console");
   tolua_function(tolua_S,"SetDefaultStyle",tolua_Engine_Console_SetDefaultStyle00);
   tolua_function(tolua_S,"SetVisible",tolua_Engine_Console_SetVisible00);
   tolua_function(tolua_S,"Toggle",tolua_Engine_Console_Toggle00);
   tolua_function(tolua_S,"SetNumRows",tolua_Engine_Console_SetNumRows00);
   tolua_function(tolua_S,"SetNumHistoryRows",tolua_Engine_Console_SetNumHistoryRows00);
   tolua_function(tolua_S,"UpdateElements",tolua_Engine_Console_UpdateElements00);
   tolua_function(tolua_S,"GetDefaultStyle",tolua_Engine_Console_GetDefaultStyle00);
   tolua_function(tolua_S,"GetBackground",tolua_Engine_Console_GetBackground00);
   tolua_function(tolua_S,"GetLineEdit",tolua_Engine_Console_GetLineEdit00);
   tolua_function(tolua_S,"IsVisible",tolua_Engine_Console_IsVisible00);
   tolua_function(tolua_S,"GetNumRows",tolua_Engine_Console_GetNumRows00);
   tolua_function(tolua_S,"GetNumHistoryRows",tolua_Engine_Console_GetNumHistoryRows00);
   tolua_function(tolua_S,"GetHistoryPosition",tolua_Engine_Console_GetHistoryPosition00);
   tolua_function(tolua_S,"GetHistoryRow",tolua_Engine_Console_GetHistoryRow00);
  tolua_endmodule(tolua_S);
  tolua_function(tolua_S,"GetConsole",tolua_Engine_GetConsole00);
  tolua_variable(tolua_S,"DEBUGHUD_SHOW_NONE",tolua_get_DEBUGHUD_SHOW_NONE,NULL);
  tolua_variable(tolua_S,"DEBUGHUD_SHOW_STATS",tolua_get_DEBUGHUD_SHOW_STATS,NULL);
  tolua_variable(tolua_S,"DEBUGHUD_SHOW_MODE",tolua_get_DEBUGHUD_SHOW_MODE,NULL);
  tolua_variable(tolua_S,"DEBUGHUD_SHOW_PROFILER",tolua_get_DEBUGHUD_SHOW_PROFILER,NULL);
  tolua_variable(tolua_S,"DEBUGHUD_SHOW_ALL",tolua_get_DEBUGHUD_SHOW_ALL,NULL);
  tolua_cclass(tolua_S,"DebugHud","DebugHud","Object",NULL);
  tolua_beginmodule(tolua_S,"DebugHud");
   tolua_function(tolua_S,"Update",tolua_Engine_DebugHud_Update00);
   tolua_function(tolua_S,"SetDefaultStyle",tolua_Engine_DebugHud_SetDefaultStyle00);
   tolua_function(tolua_S,"SetMode",tolua_Engine_DebugHud_SetMode00);
   tolua_function(tolua_S,"SetProfilerMaxDepth",tolua_Engine_DebugHud_SetProfilerMaxDepth00);
   tolua_function(tolua_S,"SetProfilerInterval",tolua_Engine_DebugHud_SetProfilerInterval00);
   tolua_function(tolua_S,"SetUseRendererStats",tolua_Engine_DebugHud_SetUseRendererStats00);
   tolua_function(tolua_S,"Toggle",tolua_Engine_DebugHud_Toggle00);
   tolua_function(tolua_S,"ToggleAll",tolua_Engine_DebugHud_ToggleAll00);
   tolua_function(tolua_S,"GetDefaultStyle",tolua_Engine_DebugHud_GetDefaultStyle00);
   tolua_function(tolua_S,"GetStatsText",tolua_Engine_DebugHud_GetStatsText00);
   tolua_function(tolua_S,"GetModeText",tolua_Engine_DebugHud_GetModeText00);
   tolua_function(tolua_S,"GetProfilerText",tolua_Engine_DebugHud_GetProfilerText00);
   tolua_function(tolua_S,"GetMode",tolua_Engine_DebugHud_GetMode00);
   tolua_function(tolua_S,"GetProfilerMaxDepth",tolua_Engine_DebugHud_GetProfilerMaxDepth00);
   tolua_function(tolua_S,"GetProfilerInterval",tolua_Engine_DebugHud_GetProfilerInterval00);
   tolua_function(tolua_S,"GetUseRendererStats",tolua_Engine_DebugHud_GetUseRendererStats00);
   tolua_function(tolua_S,"SetAppStats",tolua_Engine_DebugHud_SetAppStats00);
   tolua_function(tolua_S,"SetAppStats",tolua_Engine_DebugHud_SetAppStats01);
   tolua_function(tolua_S,"ResetAppStats",tolua_Engine_DebugHud_ResetAppStats00);
   tolua_function(tolua_S,"ClearAppStats",tolua_Engine_DebugHud_ClearAppStats00);
  tolua_endmodule(tolua_S);
  tolua_function(tolua_S,"GetDebugHud",tolua_Engine_GetDebugHud00);
  tolua_cclass(tolua_S,"Engine","Engine","Object",NULL);
  tolua_beginmodule(tolua_S,"Engine");
   tolua_function(tolua_S,"RunFrame",tolua_Engine_Engine_RunFrame00);
   tolua_function(tolua_S,"CreateConsole",tolua_Engine_Engine_CreateConsole00);
   tolua_function(tolua_S,"CreateDebugHud",tolua_Engine_Engine_CreateDebugHud00);
   tolua_function(tolua_S,"SetMinFps",tolua_Engine_Engine_SetMinFps00);
   tolua_function(tolua_S,"SetMaxFps",tolua_Engine_Engine_SetMaxFps00);
   tolua_function(tolua_S,"SetMaxInactiveFps",tolua_Engine_Engine_SetMaxInactiveFps00);
   tolua_function(tolua_S,"SetPauseMinimized",tolua_Engine_Engine_SetPauseMinimized00);
   tolua_function(tolua_S,"Exit",tolua_Engine_Engine_Exit00);
   tolua_function(tolua_S,"DumpProfiler",tolua_Engine_Engine_DumpProfiler00);
   tolua_function(tolua_S,"DumpResources",tolua_Engine_Engine_DumpResources00);
   tolua_function(tolua_S,"DumpMemory",tolua_Engine_Engine_DumpMemory00);
   tolua_function(tolua_S,"GetMinFps",tolua_Engine_Engine_GetMinFps00);
   tolua_function(tolua_S,"GetMaxFps",tolua_Engine_Engine_GetMaxFps00);
   tolua_function(tolua_S,"GetMaxInactiveFps",tolua_Engine_Engine_GetMaxInactiveFps00);
   tolua_function(tolua_S,"GetPauseMinimized",tolua_Engine_Engine_GetPauseMinimized00);
   tolua_function(tolua_S,"IsInitialized",tolua_Engine_Engine_IsInitialized00);
   tolua_function(tolua_S,"IsExiting",tolua_Engine_Engine_IsExiting00);
   tolua_function(tolua_S,"IsHeadless",tolua_Engine_Engine_IsHeadless00);
  tolua_endmodule(tolua_S);
  tolua_function(tolua_S,"GetEngine",tolua_Engine_GetEngine00);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_Engine (lua_State* tolua_S) {
 return tolua_Engine_open(tolua_S);
};
#endif

