/*
** Lua binding: Input
** Generated automatically by tolua++-1.0.92 on 07/02/13 20:27:49.
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
TOLUA_API int  tolua_Input_open (lua_State* tolua_S);

#define TOLUA_RELEASE
#include "InputLuaAPI.h"
#include "Input.h"
#include "InputEvents.h"
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
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"String");
 tolua_usertype(tolua_S,"Object");
 tolua_usertype(tolua_S,"JoystickState");
 tolua_usertype(tolua_S,"Input");
 tolua_usertype(tolua_S,"IntVector2");
 tolua_usertype(tolua_S,"TouchState");
}

/* get function: touchID_ of class  TouchState */
#ifndef TOLUA_DISABLE_tolua_get_TouchState_touchID
static int tolua_get_TouchState_touchID(lua_State* tolua_S)
{
  TouchState* self = (TouchState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'touchID_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->touchID_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: touchID_ of class  TouchState */
#ifndef TOLUA_DISABLE_tolua_set_TouchState_touchID
static int tolua_set_TouchState_touchID(lua_State* tolua_S)
{
  TouchState* self = (TouchState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'touchID_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->touchID_ = ((int)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: position_ of class  TouchState */
#ifndef TOLUA_DISABLE_tolua_get_TouchState_position
static int tolua_get_TouchState_position(lua_State* tolua_S)
{
  TouchState* self = (TouchState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'position_'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->position_,"IntVector2");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: position_ of class  TouchState */
#ifndef TOLUA_DISABLE_tolua_set_TouchState_position
static int tolua_set_TouchState_position(lua_State* tolua_S)
{
  TouchState* self = (TouchState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'position_'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"IntVector2",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->position_ = *((IntVector2*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: lastPosition_ of class  TouchState */
#ifndef TOLUA_DISABLE_tolua_get_TouchState_lastPosition
static int tolua_get_TouchState_lastPosition(lua_State* tolua_S)
{
  TouchState* self = (TouchState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'lastPosition_'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->lastPosition_,"IntVector2");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: lastPosition_ of class  TouchState */
#ifndef TOLUA_DISABLE_tolua_set_TouchState_lastPosition
static int tolua_set_TouchState_lastPosition(lua_State* tolua_S)
{
  TouchState* self = (TouchState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'lastPosition_'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"IntVector2",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->lastPosition_ = *((IntVector2*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: delta_ of class  TouchState */
#ifndef TOLUA_DISABLE_tolua_get_TouchState_delta
static int tolua_get_TouchState_delta(lua_State* tolua_S)
{
  TouchState* self = (TouchState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'delta_'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->delta_,"IntVector2");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: delta_ of class  TouchState */
#ifndef TOLUA_DISABLE_tolua_set_TouchState_delta
static int tolua_set_TouchState_delta(lua_State* tolua_S)
{
  TouchState* self = (TouchState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'delta_'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"IntVector2",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->delta_ = *((IntVector2*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: pressure_ of class  TouchState */
#ifndef TOLUA_DISABLE_tolua_get_TouchState_pressure
static int tolua_get_TouchState_pressure(lua_State* tolua_S)
{
  TouchState* self = (TouchState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'pressure_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->pressure_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: pressure_ of class  TouchState */
#ifndef TOLUA_DISABLE_tolua_set_TouchState_pressure
static int tolua_set_TouchState_pressure(lua_State* tolua_S)
{
  TouchState* self = (TouchState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'pressure_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->pressure_ = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNumButtons of class  JoystickState */
#ifndef TOLUA_DISABLE_tolua_Input_JoystickState_GetNumButtons00
static int tolua_Input_JoystickState_GetNumButtons00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const JoystickState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const JoystickState* self = (const JoystickState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNumButtons'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetNumButtons();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNumButtons'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNumAxes of class  JoystickState */
#ifndef TOLUA_DISABLE_tolua_Input_JoystickState_GetNumAxes00
static int tolua_Input_JoystickState_GetNumAxes00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const JoystickState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const JoystickState* self = (const JoystickState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNumAxes'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetNumAxes();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNumAxes'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNumHats of class  JoystickState */
#ifndef TOLUA_DISABLE_tolua_Input_JoystickState_GetNumHats00
static int tolua_Input_JoystickState_GetNumHats00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const JoystickState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const JoystickState* self = (const JoystickState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNumHats'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetNumHats();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNumHats'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetButtonDown of class  JoystickState */
#ifndef TOLUA_DISABLE_tolua_Input_JoystickState_GetButtonDown00
static int tolua_Input_JoystickState_GetButtonDown00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const JoystickState",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const JoystickState* self = (const JoystickState*)  tolua_tousertype(tolua_S,1,0);
  unsigned index = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetButtonDown'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetButtonDown(index);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetButtonDown'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetButtonPress of class  JoystickState */
#ifndef TOLUA_DISABLE_tolua_Input_JoystickState_GetButtonPress00
static int tolua_Input_JoystickState_GetButtonPress00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const JoystickState",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const JoystickState* self = (const JoystickState*)  tolua_tousertype(tolua_S,1,0);
  unsigned index = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetButtonPress'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetButtonPress(index);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetButtonPress'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAxisPosition of class  JoystickState */
#ifndef TOLUA_DISABLE_tolua_Input_JoystickState_GetAxisPosition00
static int tolua_Input_JoystickState_GetAxisPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const JoystickState",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const JoystickState* self = (const JoystickState*)  tolua_tousertype(tolua_S,1,0);
  unsigned index = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAxisPosition'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetAxisPosition(index);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAxisPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetHatPosition of class  JoystickState */
#ifndef TOLUA_DISABLE_tolua_Input_JoystickState_GetHatPosition00
static int tolua_Input_JoystickState_GetHatPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const JoystickState",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const JoystickState* self = (const JoystickState*)  tolua_tousertype(tolua_S,1,0);
  unsigned index = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetHatPosition'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetHatPosition(index);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetHatPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMouseVisible of class  Input */
#ifndef TOLUA_DISABLE_tolua_Input_Input_SetMouseVisible00
static int tolua_Input_Input_SetMouseVisible00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Input",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Input* self = (Input*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMouseVisible'", NULL);
#endif
  {
   self->SetMouseVisible(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMouseVisible'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: OpenJoystick of class  Input */
#ifndef TOLUA_DISABLE_tolua_Input_Input_OpenJoystick00
static int tolua_Input_Input_OpenJoystick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Input",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Input* self = (Input*)  tolua_tousertype(tolua_S,1,0);
  unsigned index = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'OpenJoystick'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->OpenJoystick(index);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'OpenJoystick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CloseJoystick of class  Input */
#ifndef TOLUA_DISABLE_tolua_Input_Input_CloseJoystick00
static int tolua_Input_Input_CloseJoystick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Input",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Input* self = (Input*)  tolua_tousertype(tolua_S,1,0);
  unsigned index = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CloseJoystick'", NULL);
#endif
  {
   self->CloseJoystick(index);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CloseJoystick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DetectJoysticks of class  Input */
#ifndef TOLUA_DISABLE_tolua_Input_Input_DetectJoysticks00
static int tolua_Input_Input_DetectJoysticks00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Input",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Input* self = (Input*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DetectJoysticks'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->DetectJoysticks();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DetectJoysticks'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetKeyDown of class  Input */
#ifndef TOLUA_DISABLE_tolua_Input_Input_GetKeyDown00
static int tolua_Input_Input_GetKeyDown00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Input",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Input* self = (const Input*)  tolua_tousertype(tolua_S,1,0);
  int key = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetKeyDown'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetKeyDown(key);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetKeyDown'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetKeyPress of class  Input */
#ifndef TOLUA_DISABLE_tolua_Input_Input_GetKeyPress00
static int tolua_Input_Input_GetKeyPress00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Input",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Input* self = (const Input*)  tolua_tousertype(tolua_S,1,0);
  int key = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetKeyPress'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetKeyPress(key);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetKeyPress'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMouseButtonDown of class  Input */
#ifndef TOLUA_DISABLE_tolua_Input_Input_GetMouseButtonDown00
static int tolua_Input_Input_GetMouseButtonDown00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Input",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Input* self = (const Input*)  tolua_tousertype(tolua_S,1,0);
  int button = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMouseButtonDown'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetMouseButtonDown(button);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMouseButtonDown'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMouseButtonPress of class  Input */
#ifndef TOLUA_DISABLE_tolua_Input_Input_GetMouseButtonPress00
static int tolua_Input_Input_GetMouseButtonPress00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Input",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Input* self = (const Input*)  tolua_tousertype(tolua_S,1,0);
  int button = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMouseButtonPress'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetMouseButtonPress(button);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMouseButtonPress'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetQualifierDown of class  Input */
#ifndef TOLUA_DISABLE_tolua_Input_Input_GetQualifierDown00
static int tolua_Input_Input_GetQualifierDown00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Input",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Input* self = (const Input*)  tolua_tousertype(tolua_S,1,0);
  int qualifier = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetQualifierDown'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetQualifierDown(qualifier);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetQualifierDown'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetQualifierPress of class  Input */
#ifndef TOLUA_DISABLE_tolua_Input_Input_GetQualifierPress00
static int tolua_Input_Input_GetQualifierPress00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Input",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Input* self = (const Input*)  tolua_tousertype(tolua_S,1,0);
  int qualifier = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetQualifierPress'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetQualifierPress(qualifier);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetQualifierPress'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetQualifiers of class  Input */
#ifndef TOLUA_DISABLE_tolua_Input_Input_GetQualifiers00
static int tolua_Input_Input_GetQualifiers00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Input",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Input* self = (const Input*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetQualifiers'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetQualifiers();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetQualifiers'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMousePosition of class  Input */
#ifndef TOLUA_DISABLE_tolua_Input_Input_GetMousePosition00
static int tolua_Input_Input_GetMousePosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Input",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Input* self = (const Input*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMousePosition'", NULL);
#endif
  {
   IntVector2 tolua_ret = (IntVector2)  self->GetMousePosition();
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
 tolua_error(tolua_S,"#ferror in function 'GetMousePosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMouseMove of class  Input */
#ifndef TOLUA_DISABLE_tolua_Input_Input_GetMouseMove00
static int tolua_Input_Input_GetMouseMove00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Input",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Input* self = (const Input*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMouseMove'", NULL);
#endif
  {
   const IntVector2& tolua_ret = (const IntVector2&)  self->GetMouseMove();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const IntVector2");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMouseMove'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMouseMoveX of class  Input */
#ifndef TOLUA_DISABLE_tolua_Input_Input_GetMouseMoveX00
static int tolua_Input_Input_GetMouseMoveX00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Input",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Input* self = (const Input*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMouseMoveX'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetMouseMoveX();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMouseMoveX'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMouseMoveY of class  Input */
#ifndef TOLUA_DISABLE_tolua_Input_Input_GetMouseMoveY00
static int tolua_Input_Input_GetMouseMoveY00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Input",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Input* self = (const Input*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMouseMoveY'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetMouseMoveY();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMouseMoveY'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMouseMoveWheel of class  Input */
#ifndef TOLUA_DISABLE_tolua_Input_Input_GetMouseMoveWheel00
static int tolua_Input_Input_GetMouseMoveWheel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Input",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Input* self = (const Input*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMouseMoveWheel'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetMouseMoveWheel();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMouseMoveWheel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNumTouches of class  Input */
#ifndef TOLUA_DISABLE_tolua_Input_Input_GetNumTouches00
static int tolua_Input_Input_GetNumTouches00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Input",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Input* self = (const Input*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNumTouches'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetNumTouches();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNumTouches'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTouch of class  Input */
#ifndef TOLUA_DISABLE_tolua_Input_Input_GetTouch00
static int tolua_Input_Input_GetTouch00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Input",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Input* self = (const Input*)  tolua_tousertype(tolua_S,1,0);
  unsigned index = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTouch'", NULL);
#endif
  {
   TouchState* tolua_ret = (TouchState*)  self->GetTouch(index);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"TouchState");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTouch'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNumJoysticks of class  Input */
#ifndef TOLUA_DISABLE_tolua_Input_Input_GetNumJoysticks00
static int tolua_Input_Input_GetNumJoysticks00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Input",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Input* self = (const Input*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNumJoysticks'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetNumJoysticks();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNumJoysticks'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetJoystickName of class  Input */
#ifndef TOLUA_DISABLE_tolua_Input_Input_GetJoystickName00
static int tolua_Input_Input_GetJoystickName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Input",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Input* self = (const Input*)  tolua_tousertype(tolua_S,1,0);
  unsigned index = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetJoystickName'", NULL);
#endif
  {
   const String& tolua_ret = (const String&)  self->GetJoystickName(index);
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const String");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetJoystickName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetJoystick of class  Input */
#ifndef TOLUA_DISABLE_tolua_Input_Input_GetJoystick00
static int tolua_Input_Input_GetJoystick00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Input",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Input* self = (Input*)  tolua_tousertype(tolua_S,1,0);
  unsigned index = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetJoystick'", NULL);
#endif
  {
   JoystickState* tolua_ret = (JoystickState*)  self->GetJoystick(index);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"JoystickState");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetJoystick'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetToggleFullscreen of class  Input */
#ifndef TOLUA_DISABLE_tolua_Input_Input_GetToggleFullscreen00
static int tolua_Input_Input_GetToggleFullscreen00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Input",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Input* self = (const Input*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetToggleFullscreen'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetToggleFullscreen();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetToggleFullscreen'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsMouseVisible of class  Input */
#ifndef TOLUA_DISABLE_tolua_Input_Input_IsMouseVisible00
static int tolua_Input_Input_IsMouseVisible00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Input",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Input* self = (const Input*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsMouseVisible'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsMouseVisible();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsMouseVisible'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: HasFocus of class  Input */
#ifndef TOLUA_DISABLE_tolua_Input_Input_HasFocus00
static int tolua_Input_Input_HasFocus00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Input",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Input* self = (Input*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'HasFocus'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->HasFocus();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'HasFocus'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsMinimized of class  Input */
#ifndef TOLUA_DISABLE_tolua_Input_Input_IsMinimized00
static int tolua_Input_Input_IsMinimized00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Input",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Input* self = (const Input*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsMinimized'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsMinimized();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsMinimized'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GetInput */
#ifndef TOLUA_DISABLE_tolua_Input_GetInput00
static int tolua_Input_GetInput00(lua_State* tolua_S)
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
   Input* tolua_ret = (Input*)  GetInput();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Input");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetInput'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: MOUSEB_LEFT */
#ifndef TOLUA_DISABLE_tolua_get_MOUSEB_LEFT
static int tolua_get_MOUSEB_LEFT(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)MOUSEB_LEFT);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: MOUSEB_MIDDLE */
#ifndef TOLUA_DISABLE_tolua_get_MOUSEB_MIDDLE
static int tolua_get_MOUSEB_MIDDLE(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)MOUSEB_MIDDLE);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: MOUSEB_RIGHT */
#ifndef TOLUA_DISABLE_tolua_get_MOUSEB_RIGHT
static int tolua_get_MOUSEB_RIGHT(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)MOUSEB_RIGHT);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: QUAL_SHIFT */
#ifndef TOLUA_DISABLE_tolua_get_QUAL_SHIFT
static int tolua_get_QUAL_SHIFT(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)QUAL_SHIFT);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: QUAL_CTRL */
#ifndef TOLUA_DISABLE_tolua_get_QUAL_CTRL
static int tolua_get_QUAL_CTRL(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)QUAL_CTRL);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: QUAL_ALT */
#ifndef TOLUA_DISABLE_tolua_get_QUAL_ALT
static int tolua_get_QUAL_ALT(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)QUAL_ALT);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: QUAL_ANY */
#ifndef TOLUA_DISABLE_tolua_get_QUAL_ANY
static int tolua_get_QUAL_ANY(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)QUAL_ANY);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_A */
#ifndef TOLUA_DISABLE_tolua_get_KEY_A
static int tolua_get_KEY_A(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_A);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_B */
#ifndef TOLUA_DISABLE_tolua_get_KEY_B
static int tolua_get_KEY_B(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_B);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_C */
#ifndef TOLUA_DISABLE_tolua_get_KEY_C
static int tolua_get_KEY_C(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_C);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_D */
#ifndef TOLUA_DISABLE_tolua_get_KEY_D
static int tolua_get_KEY_D(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_D);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_E */
#ifndef TOLUA_DISABLE_tolua_get_KEY_E
static int tolua_get_KEY_E(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_E);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_F */
#ifndef TOLUA_DISABLE_tolua_get_KEY_F
static int tolua_get_KEY_F(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_F);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_G */
#ifndef TOLUA_DISABLE_tolua_get_KEY_G
static int tolua_get_KEY_G(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_G);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_H */
#ifndef TOLUA_DISABLE_tolua_get_KEY_H
static int tolua_get_KEY_H(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_H);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_I */
#ifndef TOLUA_DISABLE_tolua_get_KEY_I
static int tolua_get_KEY_I(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_I);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_J */
#ifndef TOLUA_DISABLE_tolua_get_KEY_J
static int tolua_get_KEY_J(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_J);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_K */
#ifndef TOLUA_DISABLE_tolua_get_KEY_K
static int tolua_get_KEY_K(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_K);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_L */
#ifndef TOLUA_DISABLE_tolua_get_KEY_L
static int tolua_get_KEY_L(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_L);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_M */
#ifndef TOLUA_DISABLE_tolua_get_KEY_M
static int tolua_get_KEY_M(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_M);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_N */
#ifndef TOLUA_DISABLE_tolua_get_KEY_N
static int tolua_get_KEY_N(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_N);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_O */
#ifndef TOLUA_DISABLE_tolua_get_KEY_O
static int tolua_get_KEY_O(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_O);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_P */
#ifndef TOLUA_DISABLE_tolua_get_KEY_P
static int tolua_get_KEY_P(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_P);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_Q */
#ifndef TOLUA_DISABLE_tolua_get_KEY_Q
static int tolua_get_KEY_Q(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_Q);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_R */
#ifndef TOLUA_DISABLE_tolua_get_KEY_R
static int tolua_get_KEY_R(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_R);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_S */
#ifndef TOLUA_DISABLE_tolua_get_KEY_S
static int tolua_get_KEY_S(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_S);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_T */
#ifndef TOLUA_DISABLE_tolua_get_KEY_T
static int tolua_get_KEY_T(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_T);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_U */
#ifndef TOLUA_DISABLE_tolua_get_KEY_U
static int tolua_get_KEY_U(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_U);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_V */
#ifndef TOLUA_DISABLE_tolua_get_KEY_V
static int tolua_get_KEY_V(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_V);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_W */
#ifndef TOLUA_DISABLE_tolua_get_KEY_W
static int tolua_get_KEY_W(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_W);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_X */
#ifndef TOLUA_DISABLE_tolua_get_KEY_X
static int tolua_get_KEY_X(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_X);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_Y */
#ifndef TOLUA_DISABLE_tolua_get_KEY_Y
static int tolua_get_KEY_Y(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_Y);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_Z */
#ifndef TOLUA_DISABLE_tolua_get_KEY_Z
static int tolua_get_KEY_Z(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_Z);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_BACKSPACE */
#ifndef TOLUA_DISABLE_tolua_get_KEY_BACKSPACE
static int tolua_get_KEY_BACKSPACE(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_BACKSPACE);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_TAB */
#ifndef TOLUA_DISABLE_tolua_get_KEY_TAB
static int tolua_get_KEY_TAB(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_TAB);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_RETURN */
#ifndef TOLUA_DISABLE_tolua_get_KEY_RETURN
static int tolua_get_KEY_RETURN(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_RETURN);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_RETURN2 */
#ifndef TOLUA_DISABLE_tolua_get_KEY_RETURN2
static int tolua_get_KEY_RETURN2(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_RETURN2);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_KP_ENTER */
#ifndef TOLUA_DISABLE_tolua_get_KEY_KP_ENTER
static int tolua_get_KEY_KP_ENTER(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_KP_ENTER);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_SHIFT */
#ifndef TOLUA_DISABLE_tolua_get_KEY_SHIFT
static int tolua_get_KEY_SHIFT(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_SHIFT);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_CTRL */
#ifndef TOLUA_DISABLE_tolua_get_KEY_CTRL
static int tolua_get_KEY_CTRL(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_CTRL);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_ALT */
#ifndef TOLUA_DISABLE_tolua_get_KEY_ALT
static int tolua_get_KEY_ALT(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_ALT);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_PAUSE */
#ifndef TOLUA_DISABLE_tolua_get_KEY_PAUSE
static int tolua_get_KEY_PAUSE(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_PAUSE);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_CAPSLOCK */
#ifndef TOLUA_DISABLE_tolua_get_KEY_CAPSLOCK
static int tolua_get_KEY_CAPSLOCK(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_CAPSLOCK);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_ESC */
#ifndef TOLUA_DISABLE_tolua_get_KEY_ESC
static int tolua_get_KEY_ESC(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_ESC);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_SPACE */
#ifndef TOLUA_DISABLE_tolua_get_KEY_SPACE
static int tolua_get_KEY_SPACE(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_SPACE);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_PAGEUP */
#ifndef TOLUA_DISABLE_tolua_get_KEY_PAGEUP
static int tolua_get_KEY_PAGEUP(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_PAGEUP);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_PAGEDOWN */
#ifndef TOLUA_DISABLE_tolua_get_KEY_PAGEDOWN
static int tolua_get_KEY_PAGEDOWN(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_PAGEDOWN);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_END */
#ifndef TOLUA_DISABLE_tolua_get_KEY_END
static int tolua_get_KEY_END(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_END);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_HOME */
#ifndef TOLUA_DISABLE_tolua_get_KEY_HOME
static int tolua_get_KEY_HOME(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_HOME);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_LEFT */
#ifndef TOLUA_DISABLE_tolua_get_KEY_LEFT
static int tolua_get_KEY_LEFT(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_LEFT);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_UP */
#ifndef TOLUA_DISABLE_tolua_get_KEY_UP
static int tolua_get_KEY_UP(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_UP);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_RIGHT */
#ifndef TOLUA_DISABLE_tolua_get_KEY_RIGHT
static int tolua_get_KEY_RIGHT(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_RIGHT);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_DOWN */
#ifndef TOLUA_DISABLE_tolua_get_KEY_DOWN
static int tolua_get_KEY_DOWN(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_DOWN);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_SELECT */
#ifndef TOLUA_DISABLE_tolua_get_KEY_SELECT
static int tolua_get_KEY_SELECT(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_SELECT);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_PRINTSCREEN */
#ifndef TOLUA_DISABLE_tolua_get_KEY_PRINTSCREEN
static int tolua_get_KEY_PRINTSCREEN(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_PRINTSCREEN);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_INSERT */
#ifndef TOLUA_DISABLE_tolua_get_KEY_INSERT
static int tolua_get_KEY_INSERT(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_INSERT);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_DELETE */
#ifndef TOLUA_DISABLE_tolua_get_KEY_DELETE
static int tolua_get_KEY_DELETE(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_DELETE);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_LWIN */
#ifndef TOLUA_DISABLE_tolua_get_KEY_LWIN
static int tolua_get_KEY_LWIN(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_LWIN);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_RWIN */
#ifndef TOLUA_DISABLE_tolua_get_KEY_RWIN
static int tolua_get_KEY_RWIN(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_RWIN);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_APPS */
#ifndef TOLUA_DISABLE_tolua_get_KEY_APPS
static int tolua_get_KEY_APPS(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_APPS);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_NUMPAD0 */
#ifndef TOLUA_DISABLE_tolua_get_KEY_NUMPAD0
static int tolua_get_KEY_NUMPAD0(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_NUMPAD0);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_NUMPAD1 */
#ifndef TOLUA_DISABLE_tolua_get_KEY_NUMPAD1
static int tolua_get_KEY_NUMPAD1(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_NUMPAD1);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_NUMPAD2 */
#ifndef TOLUA_DISABLE_tolua_get_KEY_NUMPAD2
static int tolua_get_KEY_NUMPAD2(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_NUMPAD2);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_NUMPAD3 */
#ifndef TOLUA_DISABLE_tolua_get_KEY_NUMPAD3
static int tolua_get_KEY_NUMPAD3(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_NUMPAD3);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_NUMPAD4 */
#ifndef TOLUA_DISABLE_tolua_get_KEY_NUMPAD4
static int tolua_get_KEY_NUMPAD4(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_NUMPAD4);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_NUMPAD5 */
#ifndef TOLUA_DISABLE_tolua_get_KEY_NUMPAD5
static int tolua_get_KEY_NUMPAD5(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_NUMPAD5);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_NUMPAD6 */
#ifndef TOLUA_DISABLE_tolua_get_KEY_NUMPAD6
static int tolua_get_KEY_NUMPAD6(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_NUMPAD6);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_NUMPAD7 */
#ifndef TOLUA_DISABLE_tolua_get_KEY_NUMPAD7
static int tolua_get_KEY_NUMPAD7(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_NUMPAD7);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_NUMPAD8 */
#ifndef TOLUA_DISABLE_tolua_get_KEY_NUMPAD8
static int tolua_get_KEY_NUMPAD8(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_NUMPAD8);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_NUMPAD9 */
#ifndef TOLUA_DISABLE_tolua_get_KEY_NUMPAD9
static int tolua_get_KEY_NUMPAD9(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_NUMPAD9);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_MULTIPLY */
#ifndef TOLUA_DISABLE_tolua_get_KEY_MULTIPLY
static int tolua_get_KEY_MULTIPLY(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_MULTIPLY);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_ADD */
#ifndef TOLUA_DISABLE_tolua_get_KEY_ADD
static int tolua_get_KEY_ADD(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_ADD);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_SUBTRACT */
#ifndef TOLUA_DISABLE_tolua_get_KEY_SUBTRACT
static int tolua_get_KEY_SUBTRACT(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_SUBTRACT);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_DECIMAL */
#ifndef TOLUA_DISABLE_tolua_get_KEY_DECIMAL
static int tolua_get_KEY_DECIMAL(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_DECIMAL);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_DIVIDE */
#ifndef TOLUA_DISABLE_tolua_get_KEY_DIVIDE
static int tolua_get_KEY_DIVIDE(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_DIVIDE);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_F1 */
#ifndef TOLUA_DISABLE_tolua_get_KEY_F1
static int tolua_get_KEY_F1(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_F1);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_F2 */
#ifndef TOLUA_DISABLE_tolua_get_KEY_F2
static int tolua_get_KEY_F2(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_F2);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_F3 */
#ifndef TOLUA_DISABLE_tolua_get_KEY_F3
static int tolua_get_KEY_F3(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_F3);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_F4 */
#ifndef TOLUA_DISABLE_tolua_get_KEY_F4
static int tolua_get_KEY_F4(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_F4);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_F5 */
#ifndef TOLUA_DISABLE_tolua_get_KEY_F5
static int tolua_get_KEY_F5(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_F5);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_F6 */
#ifndef TOLUA_DISABLE_tolua_get_KEY_F6
static int tolua_get_KEY_F6(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_F6);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_F7 */
#ifndef TOLUA_DISABLE_tolua_get_KEY_F7
static int tolua_get_KEY_F7(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_F7);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_F8 */
#ifndef TOLUA_DISABLE_tolua_get_KEY_F8
static int tolua_get_KEY_F8(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_F8);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_F9 */
#ifndef TOLUA_DISABLE_tolua_get_KEY_F9
static int tolua_get_KEY_F9(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_F9);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_F10 */
#ifndef TOLUA_DISABLE_tolua_get_KEY_F10
static int tolua_get_KEY_F10(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_F10);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_F11 */
#ifndef TOLUA_DISABLE_tolua_get_KEY_F11
static int tolua_get_KEY_F11(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_F11);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_F12 */
#ifndef TOLUA_DISABLE_tolua_get_KEY_F12
static int tolua_get_KEY_F12(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_F12);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_F13 */
#ifndef TOLUA_DISABLE_tolua_get_KEY_F13
static int tolua_get_KEY_F13(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_F13);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_F14 */
#ifndef TOLUA_DISABLE_tolua_get_KEY_F14
static int tolua_get_KEY_F14(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_F14);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_F15 */
#ifndef TOLUA_DISABLE_tolua_get_KEY_F15
static int tolua_get_KEY_F15(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_F15);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_F16 */
#ifndef TOLUA_DISABLE_tolua_get_KEY_F16
static int tolua_get_KEY_F16(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_F16);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_F17 */
#ifndef TOLUA_DISABLE_tolua_get_KEY_F17
static int tolua_get_KEY_F17(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_F17);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_F18 */
#ifndef TOLUA_DISABLE_tolua_get_KEY_F18
static int tolua_get_KEY_F18(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_F18);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_F19 */
#ifndef TOLUA_DISABLE_tolua_get_KEY_F19
static int tolua_get_KEY_F19(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_F19);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_F20 */
#ifndef TOLUA_DISABLE_tolua_get_KEY_F20
static int tolua_get_KEY_F20(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_F20);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_F21 */
#ifndef TOLUA_DISABLE_tolua_get_KEY_F21
static int tolua_get_KEY_F21(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_F21);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_F22 */
#ifndef TOLUA_DISABLE_tolua_get_KEY_F22
static int tolua_get_KEY_F22(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_F22);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_F23 */
#ifndef TOLUA_DISABLE_tolua_get_KEY_F23
static int tolua_get_KEY_F23(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_F23);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_F24 */
#ifndef TOLUA_DISABLE_tolua_get_KEY_F24
static int tolua_get_KEY_F24(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_F24);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_NUMLOCK */
#ifndef TOLUA_DISABLE_tolua_get_KEY_NUMLOCK
static int tolua_get_KEY_NUMLOCK(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_NUMLOCK);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_SCROLLLOCK */
#ifndef TOLUA_DISABLE_tolua_get_KEY_SCROLLLOCK
static int tolua_get_KEY_SCROLLLOCK(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_SCROLLLOCK);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_LSHIFT */
#ifndef TOLUA_DISABLE_tolua_get_KEY_LSHIFT
static int tolua_get_KEY_LSHIFT(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_LSHIFT);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_RSHIFT */
#ifndef TOLUA_DISABLE_tolua_get_KEY_RSHIFT
static int tolua_get_KEY_RSHIFT(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_RSHIFT);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_LCTRL */
#ifndef TOLUA_DISABLE_tolua_get_KEY_LCTRL
static int tolua_get_KEY_LCTRL(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_LCTRL);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_RCTRL */
#ifndef TOLUA_DISABLE_tolua_get_KEY_RCTRL
static int tolua_get_KEY_RCTRL(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_RCTRL);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_LALT */
#ifndef TOLUA_DISABLE_tolua_get_KEY_LALT
static int tolua_get_KEY_LALT(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_LALT);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: KEY_RALT */
#ifndef TOLUA_DISABLE_tolua_get_KEY_RALT
static int tolua_get_KEY_RALT(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)KEY_RALT);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: HAT_CENTER */
#ifndef TOLUA_DISABLE_tolua_get_HAT_CENTER
static int tolua_get_HAT_CENTER(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)HAT_CENTER);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: HAT_UP */
#ifndef TOLUA_DISABLE_tolua_get_HAT_UP
static int tolua_get_HAT_UP(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)HAT_UP);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: HAT_RIGHT */
#ifndef TOLUA_DISABLE_tolua_get_HAT_RIGHT
static int tolua_get_HAT_RIGHT(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)HAT_RIGHT);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: HAT_DOWN */
#ifndef TOLUA_DISABLE_tolua_get_HAT_DOWN
static int tolua_get_HAT_DOWN(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)HAT_DOWN);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: HAT_LEFT */
#ifndef TOLUA_DISABLE_tolua_get_HAT_LEFT
static int tolua_get_HAT_LEFT(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)HAT_LEFT);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_Input_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,1);
 tolua_beginmodule(tolua_S,NULL);
  tolua_cclass(tolua_S,"TouchState","TouchState","",NULL);
  tolua_beginmodule(tolua_S,"TouchState");
   tolua_variable(tolua_S,"touchID",tolua_get_TouchState_touchID,tolua_set_TouchState_touchID);
   tolua_variable(tolua_S,"position",tolua_get_TouchState_position,tolua_set_TouchState_position);
   tolua_variable(tolua_S,"lastPosition",tolua_get_TouchState_lastPosition,tolua_set_TouchState_lastPosition);
   tolua_variable(tolua_S,"delta",tolua_get_TouchState_delta,tolua_set_TouchState_delta);
   tolua_variable(tolua_S,"pressure",tolua_get_TouchState_pressure,tolua_set_TouchState_pressure);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"JoystickState","JoystickState","",NULL);
  tolua_beginmodule(tolua_S,"JoystickState");
   tolua_function(tolua_S,"GetNumButtons",tolua_Input_JoystickState_GetNumButtons00);
   tolua_function(tolua_S,"GetNumAxes",tolua_Input_JoystickState_GetNumAxes00);
   tolua_function(tolua_S,"GetNumHats",tolua_Input_JoystickState_GetNumHats00);
   tolua_function(tolua_S,"GetButtonDown",tolua_Input_JoystickState_GetButtonDown00);
   tolua_function(tolua_S,"GetButtonPress",tolua_Input_JoystickState_GetButtonPress00);
   tolua_function(tolua_S,"GetAxisPosition",tolua_Input_JoystickState_GetAxisPosition00);
   tolua_function(tolua_S,"GetHatPosition",tolua_Input_JoystickState_GetHatPosition00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Input","Input","Object",NULL);
  tolua_beginmodule(tolua_S,"Input");
   tolua_function(tolua_S,"SetMouseVisible",tolua_Input_Input_SetMouseVisible00);
   tolua_function(tolua_S,"OpenJoystick",tolua_Input_Input_OpenJoystick00);
   tolua_function(tolua_S,"CloseJoystick",tolua_Input_Input_CloseJoystick00);
   tolua_function(tolua_S,"DetectJoysticks",tolua_Input_Input_DetectJoysticks00);
   tolua_function(tolua_S,"GetKeyDown",tolua_Input_Input_GetKeyDown00);
   tolua_function(tolua_S,"GetKeyPress",tolua_Input_Input_GetKeyPress00);
   tolua_function(tolua_S,"GetMouseButtonDown",tolua_Input_Input_GetMouseButtonDown00);
   tolua_function(tolua_S,"GetMouseButtonPress",tolua_Input_Input_GetMouseButtonPress00);
   tolua_function(tolua_S,"GetQualifierDown",tolua_Input_Input_GetQualifierDown00);
   tolua_function(tolua_S,"GetQualifierPress",tolua_Input_Input_GetQualifierPress00);
   tolua_function(tolua_S,"GetQualifiers",tolua_Input_Input_GetQualifiers00);
   tolua_function(tolua_S,"GetMousePosition",tolua_Input_Input_GetMousePosition00);
   tolua_function(tolua_S,"GetMouseMove",tolua_Input_Input_GetMouseMove00);
   tolua_function(tolua_S,"GetMouseMoveX",tolua_Input_Input_GetMouseMoveX00);
   tolua_function(tolua_S,"GetMouseMoveY",tolua_Input_Input_GetMouseMoveY00);
   tolua_function(tolua_S,"GetMouseMoveWheel",tolua_Input_Input_GetMouseMoveWheel00);
   tolua_function(tolua_S,"GetNumTouches",tolua_Input_Input_GetNumTouches00);
   tolua_function(tolua_S,"GetTouch",tolua_Input_Input_GetTouch00);
   tolua_function(tolua_S,"GetNumJoysticks",tolua_Input_Input_GetNumJoysticks00);
   tolua_function(tolua_S,"GetJoystickName",tolua_Input_Input_GetJoystickName00);
   tolua_function(tolua_S,"GetJoystick",tolua_Input_Input_GetJoystick00);
   tolua_function(tolua_S,"GetToggleFullscreen",tolua_Input_Input_GetToggleFullscreen00);
   tolua_function(tolua_S,"IsMouseVisible",tolua_Input_Input_IsMouseVisible00);
   tolua_function(tolua_S,"HasFocus",tolua_Input_Input_HasFocus00);
   tolua_function(tolua_S,"IsMinimized",tolua_Input_Input_IsMinimized00);
  tolua_endmodule(tolua_S);
  tolua_function(tolua_S,"GetInput",tolua_Input_GetInput00);
  tolua_variable(tolua_S,"MOUSEB_LEFT",tolua_get_MOUSEB_LEFT,NULL);
  tolua_variable(tolua_S,"MOUSEB_MIDDLE",tolua_get_MOUSEB_MIDDLE,NULL);
  tolua_variable(tolua_S,"MOUSEB_RIGHT",tolua_get_MOUSEB_RIGHT,NULL);
  tolua_variable(tolua_S,"QUAL_SHIFT",tolua_get_QUAL_SHIFT,NULL);
  tolua_variable(tolua_S,"QUAL_CTRL",tolua_get_QUAL_CTRL,NULL);
  tolua_variable(tolua_S,"QUAL_ALT",tolua_get_QUAL_ALT,NULL);
  tolua_variable(tolua_S,"QUAL_ANY",tolua_get_QUAL_ANY,NULL);
  tolua_variable(tolua_S,"KEY_A",tolua_get_KEY_A,NULL);
  tolua_variable(tolua_S,"KEY_B",tolua_get_KEY_B,NULL);
  tolua_variable(tolua_S,"KEY_C",tolua_get_KEY_C,NULL);
  tolua_variable(tolua_S,"KEY_D",tolua_get_KEY_D,NULL);
  tolua_variable(tolua_S,"KEY_E",tolua_get_KEY_E,NULL);
  tolua_variable(tolua_S,"KEY_F",tolua_get_KEY_F,NULL);
  tolua_variable(tolua_S,"KEY_G",tolua_get_KEY_G,NULL);
  tolua_variable(tolua_S,"KEY_H",tolua_get_KEY_H,NULL);
  tolua_variable(tolua_S,"KEY_I",tolua_get_KEY_I,NULL);
  tolua_variable(tolua_S,"KEY_J",tolua_get_KEY_J,NULL);
  tolua_variable(tolua_S,"KEY_K",tolua_get_KEY_K,NULL);
  tolua_variable(tolua_S,"KEY_L",tolua_get_KEY_L,NULL);
  tolua_variable(tolua_S,"KEY_M",tolua_get_KEY_M,NULL);
  tolua_variable(tolua_S,"KEY_N",tolua_get_KEY_N,NULL);
  tolua_variable(tolua_S,"KEY_O",tolua_get_KEY_O,NULL);
  tolua_variable(tolua_S,"KEY_P",tolua_get_KEY_P,NULL);
  tolua_variable(tolua_S,"KEY_Q",tolua_get_KEY_Q,NULL);
  tolua_variable(tolua_S,"KEY_R",tolua_get_KEY_R,NULL);
  tolua_variable(tolua_S,"KEY_S",tolua_get_KEY_S,NULL);
  tolua_variable(tolua_S,"KEY_T",tolua_get_KEY_T,NULL);
  tolua_variable(tolua_S,"KEY_U",tolua_get_KEY_U,NULL);
  tolua_variable(tolua_S,"KEY_V",tolua_get_KEY_V,NULL);
  tolua_variable(tolua_S,"KEY_W",tolua_get_KEY_W,NULL);
  tolua_variable(tolua_S,"KEY_X",tolua_get_KEY_X,NULL);
  tolua_variable(tolua_S,"KEY_Y",tolua_get_KEY_Y,NULL);
  tolua_variable(tolua_S,"KEY_Z",tolua_get_KEY_Z,NULL);
  tolua_variable(tolua_S,"KEY_BACKSPACE",tolua_get_KEY_BACKSPACE,NULL);
  tolua_variable(tolua_S,"KEY_TAB",tolua_get_KEY_TAB,NULL);
  tolua_variable(tolua_S,"KEY_RETURN",tolua_get_KEY_RETURN,NULL);
  tolua_variable(tolua_S,"KEY_RETURN2",tolua_get_KEY_RETURN2,NULL);
  tolua_variable(tolua_S,"KEY_KP_ENTER",tolua_get_KEY_KP_ENTER,NULL);
  tolua_variable(tolua_S,"KEY_SHIFT",tolua_get_KEY_SHIFT,NULL);
  tolua_variable(tolua_S,"KEY_CTRL",tolua_get_KEY_CTRL,NULL);
  tolua_variable(tolua_S,"KEY_ALT",tolua_get_KEY_ALT,NULL);
  tolua_variable(tolua_S,"KEY_PAUSE",tolua_get_KEY_PAUSE,NULL);
  tolua_variable(tolua_S,"KEY_CAPSLOCK",tolua_get_KEY_CAPSLOCK,NULL);
  tolua_variable(tolua_S,"KEY_ESC",tolua_get_KEY_ESC,NULL);
  tolua_variable(tolua_S,"KEY_SPACE",tolua_get_KEY_SPACE,NULL);
  tolua_variable(tolua_S,"KEY_PAGEUP",tolua_get_KEY_PAGEUP,NULL);
  tolua_variable(tolua_S,"KEY_PAGEDOWN",tolua_get_KEY_PAGEDOWN,NULL);
  tolua_variable(tolua_S,"KEY_END",tolua_get_KEY_END,NULL);
  tolua_variable(tolua_S,"KEY_HOME",tolua_get_KEY_HOME,NULL);
  tolua_variable(tolua_S,"KEY_LEFT",tolua_get_KEY_LEFT,NULL);
  tolua_variable(tolua_S,"KEY_UP",tolua_get_KEY_UP,NULL);
  tolua_variable(tolua_S,"KEY_RIGHT",tolua_get_KEY_RIGHT,NULL);
  tolua_variable(tolua_S,"KEY_DOWN",tolua_get_KEY_DOWN,NULL);
  tolua_variable(tolua_S,"KEY_SELECT",tolua_get_KEY_SELECT,NULL);
  tolua_variable(tolua_S,"KEY_PRINTSCREEN",tolua_get_KEY_PRINTSCREEN,NULL);
  tolua_variable(tolua_S,"KEY_INSERT",tolua_get_KEY_INSERT,NULL);
  tolua_variable(tolua_S,"KEY_DELETE",tolua_get_KEY_DELETE,NULL);
  tolua_variable(tolua_S,"KEY_LWIN",tolua_get_KEY_LWIN,NULL);
  tolua_variable(tolua_S,"KEY_RWIN",tolua_get_KEY_RWIN,NULL);
  tolua_variable(tolua_S,"KEY_APPS",tolua_get_KEY_APPS,NULL);
  tolua_variable(tolua_S,"KEY_NUMPAD0",tolua_get_KEY_NUMPAD0,NULL);
  tolua_variable(tolua_S,"KEY_NUMPAD1",tolua_get_KEY_NUMPAD1,NULL);
  tolua_variable(tolua_S,"KEY_NUMPAD2",tolua_get_KEY_NUMPAD2,NULL);
  tolua_variable(tolua_S,"KEY_NUMPAD3",tolua_get_KEY_NUMPAD3,NULL);
  tolua_variable(tolua_S,"KEY_NUMPAD4",tolua_get_KEY_NUMPAD4,NULL);
  tolua_variable(tolua_S,"KEY_NUMPAD5",tolua_get_KEY_NUMPAD5,NULL);
  tolua_variable(tolua_S,"KEY_NUMPAD6",tolua_get_KEY_NUMPAD6,NULL);
  tolua_variable(tolua_S,"KEY_NUMPAD7",tolua_get_KEY_NUMPAD7,NULL);
  tolua_variable(tolua_S,"KEY_NUMPAD8",tolua_get_KEY_NUMPAD8,NULL);
  tolua_variable(tolua_S,"KEY_NUMPAD9",tolua_get_KEY_NUMPAD9,NULL);
  tolua_variable(tolua_S,"KEY_MULTIPLY",tolua_get_KEY_MULTIPLY,NULL);
  tolua_variable(tolua_S,"KEY_ADD",tolua_get_KEY_ADD,NULL);
  tolua_variable(tolua_S,"KEY_SUBTRACT",tolua_get_KEY_SUBTRACT,NULL);
  tolua_variable(tolua_S,"KEY_DECIMAL",tolua_get_KEY_DECIMAL,NULL);
  tolua_variable(tolua_S,"KEY_DIVIDE",tolua_get_KEY_DIVIDE,NULL);
  tolua_variable(tolua_S,"KEY_F1",tolua_get_KEY_F1,NULL);
  tolua_variable(tolua_S,"KEY_F2",tolua_get_KEY_F2,NULL);
  tolua_variable(tolua_S,"KEY_F3",tolua_get_KEY_F3,NULL);
  tolua_variable(tolua_S,"KEY_F4",tolua_get_KEY_F4,NULL);
  tolua_variable(tolua_S,"KEY_F5",tolua_get_KEY_F5,NULL);
  tolua_variable(tolua_S,"KEY_F6",tolua_get_KEY_F6,NULL);
  tolua_variable(tolua_S,"KEY_F7",tolua_get_KEY_F7,NULL);
  tolua_variable(tolua_S,"KEY_F8",tolua_get_KEY_F8,NULL);
  tolua_variable(tolua_S,"KEY_F9",tolua_get_KEY_F9,NULL);
  tolua_variable(tolua_S,"KEY_F10",tolua_get_KEY_F10,NULL);
  tolua_variable(tolua_S,"KEY_F11",tolua_get_KEY_F11,NULL);
  tolua_variable(tolua_S,"KEY_F12",tolua_get_KEY_F12,NULL);
  tolua_variable(tolua_S,"KEY_F13",tolua_get_KEY_F13,NULL);
  tolua_variable(tolua_S,"KEY_F14",tolua_get_KEY_F14,NULL);
  tolua_variable(tolua_S,"KEY_F15",tolua_get_KEY_F15,NULL);
  tolua_variable(tolua_S,"KEY_F16",tolua_get_KEY_F16,NULL);
  tolua_variable(tolua_S,"KEY_F17",tolua_get_KEY_F17,NULL);
  tolua_variable(tolua_S,"KEY_F18",tolua_get_KEY_F18,NULL);
  tolua_variable(tolua_S,"KEY_F19",tolua_get_KEY_F19,NULL);
  tolua_variable(tolua_S,"KEY_F20",tolua_get_KEY_F20,NULL);
  tolua_variable(tolua_S,"KEY_F21",tolua_get_KEY_F21,NULL);
  tolua_variable(tolua_S,"KEY_F22",tolua_get_KEY_F22,NULL);
  tolua_variable(tolua_S,"KEY_F23",tolua_get_KEY_F23,NULL);
  tolua_variable(tolua_S,"KEY_F24",tolua_get_KEY_F24,NULL);
  tolua_variable(tolua_S,"KEY_NUMLOCK",tolua_get_KEY_NUMLOCK,NULL);
  tolua_variable(tolua_S,"KEY_SCROLLLOCK",tolua_get_KEY_SCROLLLOCK,NULL);
  tolua_variable(tolua_S,"KEY_LSHIFT",tolua_get_KEY_LSHIFT,NULL);
  tolua_variable(tolua_S,"KEY_RSHIFT",tolua_get_KEY_RSHIFT,NULL);
  tolua_variable(tolua_S,"KEY_LCTRL",tolua_get_KEY_LCTRL,NULL);
  tolua_variable(tolua_S,"KEY_RCTRL",tolua_get_KEY_RCTRL,NULL);
  tolua_variable(tolua_S,"KEY_LALT",tolua_get_KEY_LALT,NULL);
  tolua_variable(tolua_S,"KEY_RALT",tolua_get_KEY_RALT,NULL);
  tolua_variable(tolua_S,"HAT_CENTER",tolua_get_HAT_CENTER,NULL);
  tolua_variable(tolua_S,"HAT_UP",tolua_get_HAT_UP,NULL);
  tolua_variable(tolua_S,"HAT_RIGHT",tolua_get_HAT_RIGHT,NULL);
  tolua_variable(tolua_S,"HAT_DOWN",tolua_get_HAT_DOWN,NULL);
  tolua_variable(tolua_S,"HAT_LEFT",tolua_get_HAT_LEFT,NULL);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_Input (lua_State* tolua_S) {
 return tolua_Input_open(tolua_S);
};
#endif

