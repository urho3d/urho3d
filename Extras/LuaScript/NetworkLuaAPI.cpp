/*
** Lua binding: Network
** Generated automatically by tolua++-1.0.92 on 06/30/13 11:31:51.
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
TOLUA_API int  tolua_Network_open (lua_State* tolua_S);

#define TOLUA_RELEASE
#include "NetworkLuaAPI.h"
#include "Connection.h"
#include "Controls.h"
#include "Network.h"
#include "NetworkPriority.h"
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
 tolua_usertype(tolua_S,"VariantMap");
 tolua_usertype(tolua_S,"RemoteEvent");
 tolua_usertype(tolua_S,"Scene");
 tolua_usertype(tolua_S,"Network");
 tolua_usertype(tolua_S,"NetworkPriority");
 tolua_usertype(tolua_S,"MemoryBuffer");
 tolua_usertype(tolua_S,"StringHash");
 tolua_usertype(tolua_S,"Component");
 tolua_usertype(tolua_S,"Controls");
 tolua_usertype(tolua_S,"Object");
 tolua_usertype(tolua_S,"String");
 tolua_usertype(tolua_S,"Node");
 tolua_usertype(tolua_S,"Connection");
 tolua_usertype(tolua_S,"VectorBuffer");
 tolua_usertype(tolua_S,"Vector3");
}

/* get function: senderID_ of class  RemoteEvent */
#ifndef TOLUA_DISABLE_tolua_get_RemoteEvent_senderID
static int tolua_get_RemoteEvent_senderID(lua_State* tolua_S)
{
  RemoteEvent* self = (RemoteEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'senderID_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->senderID_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: senderID_ of class  RemoteEvent */
#ifndef TOLUA_DISABLE_tolua_set_RemoteEvent_senderID
static int tolua_set_RemoteEvent_senderID(lua_State* tolua_S)
{
  RemoteEvent* self = (RemoteEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'senderID_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->senderID_ = ((unsigned)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: eventType_ of class  RemoteEvent */
#ifndef TOLUA_DISABLE_tolua_get_RemoteEvent_eventType
static int tolua_get_RemoteEvent_eventType(lua_State* tolua_S)
{
  RemoteEvent* self = (RemoteEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'eventType_'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->eventType_,"StringHash");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: eventType_ of class  RemoteEvent */
#ifndef TOLUA_DISABLE_tolua_set_RemoteEvent_eventType
static int tolua_set_RemoteEvent_eventType(lua_State* tolua_S)
{
  RemoteEvent* self = (RemoteEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'eventType_'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"StringHash",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->eventType_ = *((StringHash*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: eventData_ of class  RemoteEvent */
#ifndef TOLUA_DISABLE_tolua_get_RemoteEvent_eventData
static int tolua_get_RemoteEvent_eventData(lua_State* tolua_S)
{
  RemoteEvent* self = (RemoteEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'eventData_'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->eventData_,"VariantMap");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: eventData_ of class  RemoteEvent */
#ifndef TOLUA_DISABLE_tolua_set_RemoteEvent_eventData
static int tolua_set_RemoteEvent_eventData(lua_State* tolua_S)
{
  RemoteEvent* self = (RemoteEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'eventData_'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"VariantMap",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->eventData_ = *((VariantMap*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: inOrder_ of class  RemoteEvent */
#ifndef TOLUA_DISABLE_tolua_get_RemoteEvent_inOrder
static int tolua_get_RemoteEvent_inOrder(lua_State* tolua_S)
{
  RemoteEvent* self = (RemoteEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'inOrder_'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->inOrder_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: inOrder_ of class  RemoteEvent */
#ifndef TOLUA_DISABLE_tolua_set_RemoteEvent_inOrder
static int tolua_set_RemoteEvent_inOrder(lua_State* tolua_S)
{
  RemoteEvent* self = (RemoteEvent*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'inOrder_'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->inOrder_ = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: SendMessage of class  Connection */
#ifndef TOLUA_DISABLE_tolua_Network_Connection_SendMessage00
static int tolua_Network_Connection_SendMessage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Connection",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"const VectorBuffer",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,6,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Connection* self = (Connection*)  tolua_tousertype(tolua_S,1,0);
  int msgID = ((int)  tolua_tonumber(tolua_S,2,0));
  bool reliable = ((bool)  tolua_toboolean(tolua_S,3,0));
  bool inOrder = ((bool)  tolua_toboolean(tolua_S,4,0));
  const VectorBuffer* msg = ((const VectorBuffer*)  tolua_tousertype(tolua_S,5,0));
  unsigned contentID = ((unsigned)  tolua_tonumber(tolua_S,6,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SendMessage'", NULL);
#endif
  {
   self->SendMessage(msgID,reliable,inOrder,*msg,contentID);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SendMessage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SendMessage of class  Connection */
#ifndef TOLUA_DISABLE_tolua_Network_Connection_SendMessage01
static int tolua_Network_Connection_SendMessage01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Connection",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     !tolua_isstring(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Connection* self = (Connection*)  tolua_tousertype(tolua_S,1,0);
  int msgID = ((int)  tolua_tonumber(tolua_S,2,0));
  bool reliable = ((bool)  tolua_toboolean(tolua_S,3,0));
  bool inOrder = ((bool)  tolua_toboolean(tolua_S,4,0));
  unsigned const char* data = ((unsigned const char*)  tolua_tostring(tolua_S,5,0));
  unsigned numBytes = ((unsigned)  tolua_tonumber(tolua_S,6,0));
  unsigned contentID = ((unsigned)  tolua_tonumber(tolua_S,7,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SendMessage'", NULL);
#endif
  {
   self->SendMessage(msgID,reliable,inOrder,data,numBytes,contentID);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Network_Connection_SendMessage00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SendRemoteEvent of class  Connection */
#ifndef TOLUA_DISABLE_tolua_Network_Connection_SendRemoteEvent00
static int tolua_Network_Connection_SendRemoteEvent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Connection",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"StringHash",0,&tolua_err)) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Connection* self = (Connection*)  tolua_tousertype(tolua_S,1,0);
  StringHash eventType = *((StringHash*)  tolua_tousertype(tolua_S,2,0));
  bool inOrder = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SendRemoteEvent'", NULL);
#endif
  {
   self->SendRemoteEvent(eventType,inOrder);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SendRemoteEvent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SendRemoteEvent of class  Connection */
#ifndef TOLUA_DISABLE_tolua_Network_Connection_SendRemoteEvent01
static int tolua_Network_Connection_SendRemoteEvent01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Connection",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"StringHash",0,&tolua_err)) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"const VariantMap",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Connection* self = (Connection*)  tolua_tousertype(tolua_S,1,0);
  StringHash eventType = *((StringHash*)  tolua_tousertype(tolua_S,2,0));
  bool inOrder = ((bool)  tolua_toboolean(tolua_S,3,0));
  const VariantMap* eventData = ((const VariantMap*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SendRemoteEvent'", NULL);
#endif
  {
   self->SendRemoteEvent(eventType,inOrder,*eventData);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Network_Connection_SendRemoteEvent00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SendRemoteEvent of class  Connection */
#ifndef TOLUA_DISABLE_tolua_Network_Connection_SendRemoteEvent02
static int tolua_Network_Connection_SendRemoteEvent02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Connection",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Node",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"StringHash",0,&tolua_err)) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Connection* self = (Connection*)  tolua_tousertype(tolua_S,1,0);
  Node* node = ((Node*)  tolua_tousertype(tolua_S,2,0));
  StringHash eventType = *((StringHash*)  tolua_tousertype(tolua_S,3,0));
  bool inOrder = ((bool)  tolua_toboolean(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SendRemoteEvent'", NULL);
#endif
  {
   self->SendRemoteEvent(node,eventType,inOrder);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Network_Connection_SendRemoteEvent01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SendRemoteEvent of class  Connection */
#ifndef TOLUA_DISABLE_tolua_Network_Connection_SendRemoteEvent03
static int tolua_Network_Connection_SendRemoteEvent03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Connection",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Node",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"StringHash",0,&tolua_err)) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"const VariantMap",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Connection* self = (Connection*)  tolua_tousertype(tolua_S,1,0);
  Node* node = ((Node*)  tolua_tousertype(tolua_S,2,0));
  StringHash eventType = *((StringHash*)  tolua_tousertype(tolua_S,3,0));
  bool inOrder = ((bool)  tolua_toboolean(tolua_S,4,0));
  const VariantMap* eventData = ((const VariantMap*)  tolua_tousertype(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SendRemoteEvent'", NULL);
#endif
  {
   self->SendRemoteEvent(node,eventType,inOrder,*eventData);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Network_Connection_SendRemoteEvent02(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetScene of class  Connection */
#ifndef TOLUA_DISABLE_tolua_Network_Connection_SetScene00
static int tolua_Network_Connection_SetScene00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Connection",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Scene",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Connection* self = (Connection*)  tolua_tousertype(tolua_S,1,0);
  Scene* newScene = ((Scene*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetScene'", NULL);
#endif
  {
   self->SetScene(newScene);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetScene'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetIdentity of class  Connection */
#ifndef TOLUA_DISABLE_tolua_Network_Connection_SetIdentity00
static int tolua_Network_Connection_SetIdentity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Connection",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const VariantMap",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Connection* self = (Connection*)  tolua_tousertype(tolua_S,1,0);
  const VariantMap* identity = ((const VariantMap*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetIdentity'", NULL);
#endif
  {
   self->SetIdentity(*identity);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetIdentity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetControls of class  Connection */
#ifndef TOLUA_DISABLE_tolua_Network_Connection_SetControls00
static int tolua_Network_Connection_SetControls00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Connection",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Controls",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Connection* self = (Connection*)  tolua_tousertype(tolua_S,1,0);
  const Controls* newControls = ((const Controls*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetControls'", NULL);
#endif
  {
   self->SetControls(*newControls);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetControls'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetPosition of class  Connection */
#ifndef TOLUA_DISABLE_tolua_Network_Connection_SetPosition00
static int tolua_Network_Connection_SetPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Connection",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Connection* self = (Connection*)  tolua_tousertype(tolua_S,1,0);
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

/* method: SetConnectPending of class  Connection */
#ifndef TOLUA_DISABLE_tolua_Network_Connection_SetConnectPending00
static int tolua_Network_Connection_SetConnectPending00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Connection",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Connection* self = (Connection*)  tolua_tousertype(tolua_S,1,0);
  bool connectPending = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetConnectPending'", NULL);
#endif
  {
   self->SetConnectPending(connectPending);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetConnectPending'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetLogStatistics of class  Connection */
#ifndef TOLUA_DISABLE_tolua_Network_Connection_SetLogStatistics00
static int tolua_Network_Connection_SetLogStatistics00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Connection",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Connection* self = (Connection*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLogStatistics'", NULL);
#endif
  {
   self->SetLogStatistics(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLogStatistics'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Disconnect of class  Connection */
#ifndef TOLUA_DISABLE_tolua_Network_Connection_Disconnect00
static int tolua_Network_Connection_Disconnect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Connection",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Connection* self = (Connection*)  tolua_tousertype(tolua_S,1,0);
  int waitMSec = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Disconnect'", NULL);
#endif
  {
   self->Disconnect(waitMSec);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Disconnect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SendServerUpdate of class  Connection */
#ifndef TOLUA_DISABLE_tolua_Network_Connection_SendServerUpdate00
static int tolua_Network_Connection_SendServerUpdate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Connection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Connection* self = (Connection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SendServerUpdate'", NULL);
#endif
  {
   self->SendServerUpdate();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SendServerUpdate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SendClientUpdate of class  Connection */
#ifndef TOLUA_DISABLE_tolua_Network_Connection_SendClientUpdate00
static int tolua_Network_Connection_SendClientUpdate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Connection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Connection* self = (Connection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SendClientUpdate'", NULL);
#endif
  {
   self->SendClientUpdate();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SendClientUpdate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SendRemoteEvents of class  Connection */
#ifndef TOLUA_DISABLE_tolua_Network_Connection_SendRemoteEvents00
static int tolua_Network_Connection_SendRemoteEvents00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Connection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Connection* self = (Connection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SendRemoteEvents'", NULL);
#endif
  {
   self->SendRemoteEvents();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SendRemoteEvents'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SendPackages of class  Connection */
#ifndef TOLUA_DISABLE_tolua_Network_Connection_SendPackages00
static int tolua_Network_Connection_SendPackages00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Connection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Connection* self = (Connection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SendPackages'", NULL);
#endif
  {
   self->SendPackages();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SendPackages'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ProcessPendingLatestData of class  Connection */
#ifndef TOLUA_DISABLE_tolua_Network_Connection_ProcessPendingLatestData00
static int tolua_Network_Connection_ProcessPendingLatestData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Connection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Connection* self = (Connection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ProcessPendingLatestData'", NULL);
#endif
  {
   self->ProcessPendingLatestData();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ProcessPendingLatestData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ProcessMessage of class  Connection */
#ifndef TOLUA_DISABLE_tolua_Network_Connection_ProcessMessage00
static int tolua_Network_Connection_ProcessMessage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Connection",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"MemoryBuffer",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Connection* self = (Connection*)  tolua_tousertype(tolua_S,1,0);
  int msgID = ((int)  tolua_tonumber(tolua_S,2,0));
  MemoryBuffer* msg = ((MemoryBuffer*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ProcessMessage'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->ProcessMessage(msgID,*msg);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ProcessMessage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetIdentity of class  Connection */
#ifndef TOLUA_DISABLE_tolua_Network_Connection_GetIdentity00
static int tolua_Network_Connection_GetIdentity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Connection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Connection* self = (const Connection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetIdentity'", NULL);
#endif
  {
   const VariantMap& tolua_ret = (const VariantMap&)  self->GetIdentity();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const VariantMap");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetIdentity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetScene of class  Connection */
#ifndef TOLUA_DISABLE_tolua_Network_Connection_GetScene00
static int tolua_Network_Connection_GetScene00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Connection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Connection* self = (const Connection*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetControls of class  Connection */
#ifndef TOLUA_DISABLE_tolua_Network_Connection_GetControls00
static int tolua_Network_Connection_GetControls00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Connection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Connection* self = (const Connection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetControls'", NULL);
#endif
  {
   const Controls& tolua_ret = (const Controls&)  self->GetControls();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Controls");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetControls'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetPosition of class  Connection */
#ifndef TOLUA_DISABLE_tolua_Network_Connection_GetPosition00
static int tolua_Network_Connection_GetPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Connection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Connection* self = (const Connection*)  tolua_tousertype(tolua_S,1,0);
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

/* method: IsClient of class  Connection */
#ifndef TOLUA_DISABLE_tolua_Network_Connection_IsClient00
static int tolua_Network_Connection_IsClient00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Connection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Connection* self = (const Connection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsClient'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsClient();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsClient'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsConnected of class  Connection */
#ifndef TOLUA_DISABLE_tolua_Network_Connection_IsConnected00
static int tolua_Network_Connection_IsConnected00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Connection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Connection* self = (const Connection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsConnected'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsConnected();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsConnected'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsConnectPending of class  Connection */
#ifndef TOLUA_DISABLE_tolua_Network_Connection_IsConnectPending00
static int tolua_Network_Connection_IsConnectPending00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Connection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Connection* self = (const Connection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsConnectPending'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsConnectPending();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsConnectPending'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsSceneLoaded of class  Connection */
#ifndef TOLUA_DISABLE_tolua_Network_Connection_IsSceneLoaded00
static int tolua_Network_Connection_IsSceneLoaded00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Connection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Connection* self = (const Connection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsSceneLoaded'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsSceneLoaded();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsSceneLoaded'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLogStatistics of class  Connection */
#ifndef TOLUA_DISABLE_tolua_Network_Connection_GetLogStatistics00
static int tolua_Network_Connection_GetLogStatistics00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Connection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Connection* self = (const Connection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLogStatistics'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetLogStatistics();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLogStatistics'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAddress of class  Connection */
#ifndef TOLUA_DISABLE_tolua_Network_Connection_GetAddress00
static int tolua_Network_Connection_GetAddress00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Connection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Connection* self = (const Connection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAddress'", NULL);
#endif
  {
   String tolua_ret = (String)  self->GetAddress();
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
 tolua_error(tolua_S,"#ferror in function 'GetAddress'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetPort of class  Connection */
#ifndef TOLUA_DISABLE_tolua_Network_Connection_GetPort00
static int tolua_Network_Connection_GetPort00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Connection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Connection* self = (const Connection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPort'", NULL);
#endif
  {
   unsigned short tolua_ret = (unsigned short)  self->GetPort();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPort'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ToString of class  Connection */
#ifndef TOLUA_DISABLE_tolua_Network_Connection_ToString00
static int tolua_Network_Connection_ToString00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Connection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Connection* self = (const Connection*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetNumDownloads of class  Connection */
#ifndef TOLUA_DISABLE_tolua_Network_Connection_GetNumDownloads00
static int tolua_Network_Connection_GetNumDownloads00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Connection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Connection* self = (const Connection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNumDownloads'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetNumDownloads();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNumDownloads'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetDownloadName of class  Connection */
#ifndef TOLUA_DISABLE_tolua_Network_Connection_GetDownloadName00
static int tolua_Network_Connection_GetDownloadName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Connection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Connection* self = (const Connection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetDownloadName'", NULL);
#endif
  {
   const String& tolua_ret = (const String&)  self->GetDownloadName();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const String");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDownloadName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetDownloadProgress of class  Connection */
#ifndef TOLUA_DISABLE_tolua_Network_Connection_GetDownloadProgress00
static int tolua_Network_Connection_GetDownloadProgress00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Connection",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Connection* self = (const Connection*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetDownloadProgress'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetDownloadProgress();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDownloadProgress'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Reset of class  Controls */
#ifndef TOLUA_DISABLE_tolua_Network_Controls_Reset00
static int tolua_Network_Controls_Reset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Controls",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Controls* self = (Controls*)  tolua_tousertype(tolua_S,1,0);
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

/* method: Set of class  Controls */
#ifndef TOLUA_DISABLE_tolua_Network_Controls_Set00
static int tolua_Network_Controls_Set00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Controls",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Controls* self = (Controls*)  tolua_tousertype(tolua_S,1,0);
  unsigned buttons = ((unsigned)  tolua_tonumber(tolua_S,2,0));
  bool down = ((bool)  tolua_toboolean(tolua_S,3,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Set'", NULL);
#endif
  {
   self->Set(buttons,down);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Set'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsDown of class  Controls */
#ifndef TOLUA_DISABLE_tolua_Network_Controls_IsDown00
static int tolua_Network_Controls_IsDown00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Controls",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Controls* self = (const Controls*)  tolua_tousertype(tolua_S,1,0);
  unsigned button = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsDown'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsDown(button);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsDown'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsPressed of class  Controls */
#ifndef TOLUA_DISABLE_tolua_Network_Controls_IsPressed00
static int tolua_Network_Controls_IsPressed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Controls",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const Controls",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Controls* self = (const Controls*)  tolua_tousertype(tolua_S,1,0);
  unsigned button = ((unsigned)  tolua_tonumber(tolua_S,2,0));
  const Controls* previousControls = ((const Controls*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsPressed'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsPressed(button,*previousControls);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsPressed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: buttons_ of class  Controls */
#ifndef TOLUA_DISABLE_tolua_get_Controls_buttons
static int tolua_get_Controls_buttons(lua_State* tolua_S)
{
  Controls* self = (Controls*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'buttons_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->buttons_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: buttons_ of class  Controls */
#ifndef TOLUA_DISABLE_tolua_set_Controls_buttons
static int tolua_set_Controls_buttons(lua_State* tolua_S)
{
  Controls* self = (Controls*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'buttons_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->buttons_ = ((unsigned)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: yaw_ of class  Controls */
#ifndef TOLUA_DISABLE_tolua_get_Controls_yaw
static int tolua_get_Controls_yaw(lua_State* tolua_S)
{
  Controls* self = (Controls*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'yaw_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->yaw_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: yaw_ of class  Controls */
#ifndef TOLUA_DISABLE_tolua_set_Controls_yaw
static int tolua_set_Controls_yaw(lua_State* tolua_S)
{
  Controls* self = (Controls*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'yaw_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->yaw_ = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: pitch_ of class  Controls */
#ifndef TOLUA_DISABLE_tolua_get_Controls_pitch
static int tolua_get_Controls_pitch(lua_State* tolua_S)
{
  Controls* self = (Controls*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'pitch_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->pitch_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: pitch_ of class  Controls */
#ifndef TOLUA_DISABLE_tolua_set_Controls_pitch
static int tolua_set_Controls_pitch(lua_State* tolua_S)
{
  Controls* self = (Controls*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'pitch_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->pitch_ = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: extraData_ of class  Controls */
#ifndef TOLUA_DISABLE_tolua_get_Controls_extraData
static int tolua_get_Controls_extraData(lua_State* tolua_S)
{
  Controls* self = (Controls*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'extraData_'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->extraData_,"VariantMap");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: extraData_ of class  Controls */
#ifndef TOLUA_DISABLE_tolua_set_Controls_extraData
static int tolua_set_Controls_extraData(lua_State* tolua_S)
{
  Controls* self = (Controls*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'extraData_'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"VariantMap",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->extraData_ = *((VariantMap*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: Connect of class  Network */
#ifndef TOLUA_DISABLE_tolua_Network_Network_Connect00
static int tolua_Network_Network_Connect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Network",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"Scene",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Network* self = (Network*)  tolua_tousertype(tolua_S,1,0);
  const String* address = ((const String*)  tolua_tousertype(tolua_S,2,0));
  unsigned short port = ((unsigned short)  tolua_tonumber(tolua_S,3,0));
  Scene* scene = ((Scene*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Connect'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Connect(*address,port,scene);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Connect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Connect of class  Network */
#ifndef TOLUA_DISABLE_tolua_Network_Network_Connect01
static int tolua_Network_Network_Connect01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Network",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"Scene",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"const VariantMap",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Network* self = (Network*)  tolua_tousertype(tolua_S,1,0);
  const String* address = ((const String*)  tolua_tousertype(tolua_S,2,0));
  unsigned short port = ((unsigned short)  tolua_tonumber(tolua_S,3,0));
  Scene* scene = ((Scene*)  tolua_tousertype(tolua_S,4,0));
  const VariantMap* identity = ((const VariantMap*)  tolua_tousertype(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Connect'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Connect(*address,port,scene,*identity);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_Network_Network_Connect00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: Disconnect of class  Network */
#ifndef TOLUA_DISABLE_tolua_Network_Network_Disconnect00
static int tolua_Network_Network_Disconnect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Network",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Network* self = (Network*)  tolua_tousertype(tolua_S,1,0);
  int waitMSec = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Disconnect'", NULL);
#endif
  {
   self->Disconnect(waitMSec);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Disconnect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: StartServer of class  Network */
#ifndef TOLUA_DISABLE_tolua_Network_Network_StartServer00
static int tolua_Network_Network_StartServer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Network",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Network* self = (Network*)  tolua_tousertype(tolua_S,1,0);
  unsigned short port = ((unsigned short)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'StartServer'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->StartServer(port);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'StartServer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: StopServer of class  Network */
#ifndef TOLUA_DISABLE_tolua_Network_Network_StopServer00
static int tolua_Network_Network_StopServer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Network",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Network* self = (Network*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'StopServer'", NULL);
#endif
  {
   self->StopServer();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'StopServer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: BroadcastMessage of class  Network */
#ifndef TOLUA_DISABLE_tolua_Network_Network_BroadcastMessage00
static int tolua_Network_Network_BroadcastMessage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Network",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"const VectorBuffer",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,6,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Network* self = (Network*)  tolua_tousertype(tolua_S,1,0);
  int msgID = ((int)  tolua_tonumber(tolua_S,2,0));
  bool reliable = ((bool)  tolua_toboolean(tolua_S,3,0));
  bool inOrder = ((bool)  tolua_toboolean(tolua_S,4,0));
  const VectorBuffer* msg = ((const VectorBuffer*)  tolua_tousertype(tolua_S,5,0));
  unsigned contentID = ((unsigned)  tolua_tonumber(tolua_S,6,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'BroadcastMessage'", NULL);
#endif
  {
   self->BroadcastMessage(msgID,reliable,inOrder,*msg,contentID);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'BroadcastMessage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: BroadcastMessage of class  Network */
#ifndef TOLUA_DISABLE_tolua_Network_Network_BroadcastMessage01
static int tolua_Network_Network_BroadcastMessage01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Network",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     !tolua_isstring(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Network* self = (Network*)  tolua_tousertype(tolua_S,1,0);
  int msgID = ((int)  tolua_tonumber(tolua_S,2,0));
  bool reliable = ((bool)  tolua_toboolean(tolua_S,3,0));
  bool inOrder = ((bool)  tolua_toboolean(tolua_S,4,0));
  unsigned const char* data = ((unsigned const char*)  tolua_tostring(tolua_S,5,0));
  unsigned numBytes = ((unsigned)  tolua_tonumber(tolua_S,6,0));
  unsigned contentID = ((unsigned)  tolua_tonumber(tolua_S,7,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'BroadcastMessage'", NULL);
#endif
  {
   self->BroadcastMessage(msgID,reliable,inOrder,data,numBytes,contentID);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Network_Network_BroadcastMessage00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: BroadcastRemoteEvent of class  Network */
#ifndef TOLUA_DISABLE_tolua_Network_Network_BroadcastRemoteEvent00
static int tolua_Network_Network_BroadcastRemoteEvent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Network",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"StringHash",0,&tolua_err)) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Network* self = (Network*)  tolua_tousertype(tolua_S,1,0);
  StringHash eventType = *((StringHash*)  tolua_tousertype(tolua_S,2,0));
  bool inOrder = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'BroadcastRemoteEvent'", NULL);
#endif
  {
   self->BroadcastRemoteEvent(eventType,inOrder);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'BroadcastRemoteEvent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: BroadcastRemoteEvent of class  Network */
#ifndef TOLUA_DISABLE_tolua_Network_Network_BroadcastRemoteEvent01
static int tolua_Network_Network_BroadcastRemoteEvent01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Network",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"StringHash",0,&tolua_err)) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"const VariantMap",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Network* self = (Network*)  tolua_tousertype(tolua_S,1,0);
  StringHash eventType = *((StringHash*)  tolua_tousertype(tolua_S,2,0));
  bool inOrder = ((bool)  tolua_toboolean(tolua_S,3,0));
  const VariantMap* eventData = ((const VariantMap*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'BroadcastRemoteEvent'", NULL);
#endif
  {
   self->BroadcastRemoteEvent(eventType,inOrder,*eventData);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Network_Network_BroadcastRemoteEvent00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: BroadcastRemoteEvent of class  Network */
#ifndef TOLUA_DISABLE_tolua_Network_Network_BroadcastRemoteEvent02
static int tolua_Network_Network_BroadcastRemoteEvent02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Network",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Scene",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"StringHash",0,&tolua_err)) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Network* self = (Network*)  tolua_tousertype(tolua_S,1,0);
  Scene* scene = ((Scene*)  tolua_tousertype(tolua_S,2,0));
  StringHash eventType = *((StringHash*)  tolua_tousertype(tolua_S,3,0));
  bool inOrder = ((bool)  tolua_toboolean(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'BroadcastRemoteEvent'", NULL);
#endif
  {
   self->BroadcastRemoteEvent(scene,eventType,inOrder);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Network_Network_BroadcastRemoteEvent01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: BroadcastRemoteEvent of class  Network */
#ifndef TOLUA_DISABLE_tolua_Network_Network_BroadcastRemoteEvent03
static int tolua_Network_Network_BroadcastRemoteEvent03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Network",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Scene",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"StringHash",0,&tolua_err)) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"const VariantMap",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Network* self = (Network*)  tolua_tousertype(tolua_S,1,0);
  Scene* scene = ((Scene*)  tolua_tousertype(tolua_S,2,0));
  StringHash eventType = *((StringHash*)  tolua_tousertype(tolua_S,3,0));
  bool inOrder = ((bool)  tolua_toboolean(tolua_S,4,0));
  const VariantMap* eventData = ((const VariantMap*)  tolua_tousertype(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'BroadcastRemoteEvent'", NULL);
#endif
  {
   self->BroadcastRemoteEvent(scene,eventType,inOrder,*eventData);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Network_Network_BroadcastRemoteEvent02(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: BroadcastRemoteEvent of class  Network */
#ifndef TOLUA_DISABLE_tolua_Network_Network_BroadcastRemoteEvent04
static int tolua_Network_Network_BroadcastRemoteEvent04(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Network",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Node",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"StringHash",0,&tolua_err)) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Network* self = (Network*)  tolua_tousertype(tolua_S,1,0);
  Node* node = ((Node*)  tolua_tousertype(tolua_S,2,0));
  StringHash eventType = *((StringHash*)  tolua_tousertype(tolua_S,3,0));
  bool inOrder = ((bool)  tolua_toboolean(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'BroadcastRemoteEvent'", NULL);
#endif
  {
   self->BroadcastRemoteEvent(node,eventType,inOrder);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Network_Network_BroadcastRemoteEvent03(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: BroadcastRemoteEvent of class  Network */
#ifndef TOLUA_DISABLE_tolua_Network_Network_BroadcastRemoteEvent05
static int tolua_Network_Network_BroadcastRemoteEvent05(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Network",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Node",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"StringHash",0,&tolua_err)) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"const VariantMap",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Network* self = (Network*)  tolua_tousertype(tolua_S,1,0);
  Node* node = ((Node*)  tolua_tousertype(tolua_S,2,0));
  StringHash eventType = *((StringHash*)  tolua_tousertype(tolua_S,3,0));
  bool inOrder = ((bool)  tolua_toboolean(tolua_S,4,0));
  const VariantMap* eventData = ((const VariantMap*)  tolua_tousertype(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'BroadcastRemoteEvent'", NULL);
#endif
  {
   self->BroadcastRemoteEvent(node,eventType,inOrder,*eventData);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Network_Network_BroadcastRemoteEvent04(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetUpdateFps of class  Network */
#ifndef TOLUA_DISABLE_tolua_Network_Network_SetUpdateFps00
static int tolua_Network_Network_SetUpdateFps00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Network",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Network* self = (Network*)  tolua_tousertype(tolua_S,1,0);
  int fps = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetUpdateFps'", NULL);
#endif
  {
   self->SetUpdateFps(fps);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetUpdateFps'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RegisterRemoteEvent of class  Network */
#ifndef TOLUA_DISABLE_tolua_Network_Network_RegisterRemoteEvent00
static int tolua_Network_Network_RegisterRemoteEvent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Network",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"StringHash",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Network* self = (Network*)  tolua_tousertype(tolua_S,1,0);
  StringHash eventType = *((StringHash*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RegisterRemoteEvent'", NULL);
#endif
  {
   self->RegisterRemoteEvent(eventType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RegisterRemoteEvent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: UnregisterRemoteEvent of class  Network */
#ifndef TOLUA_DISABLE_tolua_Network_Network_UnregisterRemoteEvent00
static int tolua_Network_Network_UnregisterRemoteEvent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Network",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"StringHash",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Network* self = (Network*)  tolua_tousertype(tolua_S,1,0);
  StringHash eventType = *((StringHash*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'UnregisterRemoteEvent'", NULL);
#endif
  {
   self->UnregisterRemoteEvent(eventType);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'UnregisterRemoteEvent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: UnregisterAllRemoteEvents of class  Network */
#ifndef TOLUA_DISABLE_tolua_Network_Network_UnregisterAllRemoteEvents00
static int tolua_Network_Network_UnregisterAllRemoteEvents00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Network",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Network* self = (Network*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'UnregisterAllRemoteEvents'", NULL);
#endif
  {
   self->UnregisterAllRemoteEvents();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'UnregisterAllRemoteEvents'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetPackageCacheDir of class  Network */
#ifndef TOLUA_DISABLE_tolua_Network_Network_SetPackageCacheDir00
static int tolua_Network_Network_SetPackageCacheDir00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Network",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Network* self = (Network*)  tolua_tousertype(tolua_S,1,0);
  const String* path = ((const String*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetPackageCacheDir'", NULL);
#endif
  {
   self->SetPackageCacheDir(*path);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetPackageCacheDir'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetUpdateFps of class  Network */
#ifndef TOLUA_DISABLE_tolua_Network_Network_GetUpdateFps00
static int tolua_Network_Network_GetUpdateFps00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Network",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Network* self = (const Network*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetUpdateFps'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetUpdateFps();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetUpdateFps'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetServerConnection of class  Network */
#ifndef TOLUA_DISABLE_tolua_Network_Network_GetServerConnection00
static int tolua_Network_Network_GetServerConnection00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Network",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Network* self = (const Network*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetServerConnection'", NULL);
#endif
  {
   Connection* tolua_ret = (Connection*)  self->GetServerConnection();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Connection");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetServerConnection'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsServerRunning of class  Network */
#ifndef TOLUA_DISABLE_tolua_Network_Network_IsServerRunning00
static int tolua_Network_Network_IsServerRunning00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Network",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Network* self = (const Network*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsServerRunning'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsServerRunning();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsServerRunning'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CheckRemoteEvent of class  Network */
#ifndef TOLUA_DISABLE_tolua_Network_Network_CheckRemoteEvent00
static int tolua_Network_Network_CheckRemoteEvent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Network",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"StringHash",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Network* self = (const Network*)  tolua_tousertype(tolua_S,1,0);
  StringHash eventType = *((StringHash*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CheckRemoteEvent'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->CheckRemoteEvent(eventType);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CheckRemoteEvent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetPackageCacheDir of class  Network */
#ifndef TOLUA_DISABLE_tolua_Network_Network_GetPackageCacheDir00
static int tolua_Network_Network_GetPackageCacheDir00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Network",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Network* self = (const Network*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPackageCacheDir'", NULL);
#endif
  {
   const String& tolua_ret = (const String&)  self->GetPackageCacheDir();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const String");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPackageCacheDir'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GetNetwork */
#ifndef TOLUA_DISABLE_tolua_Network_GetNetwork00
static int tolua_Network_GetNetwork00(lua_State* tolua_S)
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
   Network* tolua_ret = (Network*)  GetNetwork();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Network");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNetwork'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetBasePriority of class  NetworkPriority */
#ifndef TOLUA_DISABLE_tolua_Network_NetworkPriority_SetBasePriority00
static int tolua_Network_NetworkPriority_SetBasePriority00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NetworkPriority",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NetworkPriority* self = (NetworkPriority*)  tolua_tousertype(tolua_S,1,0);
  float priority = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetBasePriority'", NULL);
#endif
  {
   self->SetBasePriority(priority);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetBasePriority'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetDistanceFactor of class  NetworkPriority */
#ifndef TOLUA_DISABLE_tolua_Network_NetworkPriority_SetDistanceFactor00
static int tolua_Network_NetworkPriority_SetDistanceFactor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NetworkPriority",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NetworkPriority* self = (NetworkPriority*)  tolua_tousertype(tolua_S,1,0);
  float factor = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetDistanceFactor'", NULL);
#endif
  {
   self->SetDistanceFactor(factor);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetDistanceFactor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMinPriority of class  NetworkPriority */
#ifndef TOLUA_DISABLE_tolua_Network_NetworkPriority_SetMinPriority00
static int tolua_Network_NetworkPriority_SetMinPriority00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NetworkPriority",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NetworkPriority* self = (NetworkPriority*)  tolua_tousertype(tolua_S,1,0);
  float priority = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMinPriority'", NULL);
#endif
  {
   self->SetMinPriority(priority);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMinPriority'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetAlwaysUpdateOwner of class  NetworkPriority */
#ifndef TOLUA_DISABLE_tolua_Network_NetworkPriority_SetAlwaysUpdateOwner00
static int tolua_Network_NetworkPriority_SetAlwaysUpdateOwner00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NetworkPriority",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NetworkPriority* self = (NetworkPriority*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetAlwaysUpdateOwner'", NULL);
#endif
  {
   self->SetAlwaysUpdateOwner(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetAlwaysUpdateOwner'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetBasePriority of class  NetworkPriority */
#ifndef TOLUA_DISABLE_tolua_Network_NetworkPriority_GetBasePriority00
static int tolua_Network_NetworkPriority_GetBasePriority00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const NetworkPriority",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const NetworkPriority* self = (const NetworkPriority*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetBasePriority'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetBasePriority();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetBasePriority'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetDistanceFactor of class  NetworkPriority */
#ifndef TOLUA_DISABLE_tolua_Network_NetworkPriority_GetDistanceFactor00
static int tolua_Network_NetworkPriority_GetDistanceFactor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const NetworkPriority",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const NetworkPriority* self = (const NetworkPriority*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetDistanceFactor'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetDistanceFactor();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDistanceFactor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMinPriority of class  NetworkPriority */
#ifndef TOLUA_DISABLE_tolua_Network_NetworkPriority_GetMinPriority00
static int tolua_Network_NetworkPriority_GetMinPriority00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const NetworkPriority",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const NetworkPriority* self = (const NetworkPriority*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMinPriority'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetMinPriority();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMinPriority'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAlwaysUpdateOwner of class  NetworkPriority */
#ifndef TOLUA_DISABLE_tolua_Network_NetworkPriority_GetAlwaysUpdateOwner00
static int tolua_Network_NetworkPriority_GetAlwaysUpdateOwner00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const NetworkPriority",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const NetworkPriority* self = (const NetworkPriority*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAlwaysUpdateOwner'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetAlwaysUpdateOwner();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAlwaysUpdateOwner'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CheckUpdate of class  NetworkPriority */
#ifndef TOLUA_DISABLE_tolua_Network_NetworkPriority_CheckUpdate00
static int tolua_Network_NetworkPriority_CheckUpdate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"NetworkPriority",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  NetworkPriority* self = (NetworkPriority*)  tolua_tousertype(tolua_S,1,0);
  float distance = ((float)  tolua_tonumber(tolua_S,2,0));
  float accumulator = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CheckUpdate'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->CheckUpdate(distance,accumulator);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
   tolua_pushnumber(tolua_S,(lua_Number)accumulator);
  }
 }
 return 2;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CheckUpdate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_Network_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_cclass(tolua_S,"RemoteEvent","RemoteEvent","",NULL);
  tolua_beginmodule(tolua_S,"RemoteEvent");
   tolua_variable(tolua_S,"senderID",tolua_get_RemoteEvent_senderID,tolua_set_RemoteEvent_senderID);
   tolua_variable(tolua_S,"eventType",tolua_get_RemoteEvent_eventType,tolua_set_RemoteEvent_eventType);
   tolua_variable(tolua_S,"eventData",tolua_get_RemoteEvent_eventData,tolua_set_RemoteEvent_eventData);
   tolua_variable(tolua_S,"inOrder",tolua_get_RemoteEvent_inOrder,tolua_set_RemoteEvent_inOrder);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Connection","Connection","Object",NULL);
  tolua_beginmodule(tolua_S,"Connection");
   tolua_function(tolua_S,"SendMessage",tolua_Network_Connection_SendMessage00);
   tolua_function(tolua_S,"SendMessage",tolua_Network_Connection_SendMessage01);
   tolua_function(tolua_S,"SendRemoteEvent",tolua_Network_Connection_SendRemoteEvent00);
   tolua_function(tolua_S,"SendRemoteEvent",tolua_Network_Connection_SendRemoteEvent01);
   tolua_function(tolua_S,"SendRemoteEvent",tolua_Network_Connection_SendRemoteEvent02);
   tolua_function(tolua_S,"SendRemoteEvent",tolua_Network_Connection_SendRemoteEvent03);
   tolua_function(tolua_S,"SetScene",tolua_Network_Connection_SetScene00);
   tolua_function(tolua_S,"SetIdentity",tolua_Network_Connection_SetIdentity00);
   tolua_function(tolua_S,"SetControls",tolua_Network_Connection_SetControls00);
   tolua_function(tolua_S,"SetPosition",tolua_Network_Connection_SetPosition00);
   tolua_function(tolua_S,"SetConnectPending",tolua_Network_Connection_SetConnectPending00);
   tolua_function(tolua_S,"SetLogStatistics",tolua_Network_Connection_SetLogStatistics00);
   tolua_function(tolua_S,"Disconnect",tolua_Network_Connection_Disconnect00);
   tolua_function(tolua_S,"SendServerUpdate",tolua_Network_Connection_SendServerUpdate00);
   tolua_function(tolua_S,"SendClientUpdate",tolua_Network_Connection_SendClientUpdate00);
   tolua_function(tolua_S,"SendRemoteEvents",tolua_Network_Connection_SendRemoteEvents00);
   tolua_function(tolua_S,"SendPackages",tolua_Network_Connection_SendPackages00);
   tolua_function(tolua_S,"ProcessPendingLatestData",tolua_Network_Connection_ProcessPendingLatestData00);
   tolua_function(tolua_S,"ProcessMessage",tolua_Network_Connection_ProcessMessage00);
   tolua_function(tolua_S,"GetIdentity",tolua_Network_Connection_GetIdentity00);
   tolua_function(tolua_S,"GetScene",tolua_Network_Connection_GetScene00);
   tolua_function(tolua_S,"GetControls",tolua_Network_Connection_GetControls00);
   tolua_function(tolua_S,"GetPosition",tolua_Network_Connection_GetPosition00);
   tolua_function(tolua_S,"IsClient",tolua_Network_Connection_IsClient00);
   tolua_function(tolua_S,"IsConnected",tolua_Network_Connection_IsConnected00);
   tolua_function(tolua_S,"IsConnectPending",tolua_Network_Connection_IsConnectPending00);
   tolua_function(tolua_S,"IsSceneLoaded",tolua_Network_Connection_IsSceneLoaded00);
   tolua_function(tolua_S,"GetLogStatistics",tolua_Network_Connection_GetLogStatistics00);
   tolua_function(tolua_S,"GetAddress",tolua_Network_Connection_GetAddress00);
   tolua_function(tolua_S,"GetPort",tolua_Network_Connection_GetPort00);
   tolua_function(tolua_S,"ToString",tolua_Network_Connection_ToString00);
   tolua_function(tolua_S,"GetNumDownloads",tolua_Network_Connection_GetNumDownloads00);
   tolua_function(tolua_S,"GetDownloadName",tolua_Network_Connection_GetDownloadName00);
   tolua_function(tolua_S,"GetDownloadProgress",tolua_Network_Connection_GetDownloadProgress00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Controls","Controls","",NULL);
  tolua_beginmodule(tolua_S,"Controls");
   tolua_function(tolua_S,"Reset",tolua_Network_Controls_Reset00);
   tolua_function(tolua_S,"Set",tolua_Network_Controls_Set00);
   tolua_function(tolua_S,"IsDown",tolua_Network_Controls_IsDown00);
   tolua_function(tolua_S,"IsPressed",tolua_Network_Controls_IsPressed00);
   tolua_variable(tolua_S,"buttons",tolua_get_Controls_buttons,tolua_set_Controls_buttons);
   tolua_variable(tolua_S,"yaw",tolua_get_Controls_yaw,tolua_set_Controls_yaw);
   tolua_variable(tolua_S,"pitch",tolua_get_Controls_pitch,tolua_set_Controls_pitch);
   tolua_variable(tolua_S,"extraData",tolua_get_Controls_extraData,tolua_set_Controls_extraData);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Network","Network","",NULL);
  tolua_beginmodule(tolua_S,"Network");
   tolua_function(tolua_S,"Connect",tolua_Network_Network_Connect00);
   tolua_function(tolua_S,"Connect",tolua_Network_Network_Connect01);
   tolua_function(tolua_S,"Disconnect",tolua_Network_Network_Disconnect00);
   tolua_function(tolua_S,"StartServer",tolua_Network_Network_StartServer00);
   tolua_function(tolua_S,"StopServer",tolua_Network_Network_StopServer00);
   tolua_function(tolua_S,"BroadcastMessage",tolua_Network_Network_BroadcastMessage00);
   tolua_function(tolua_S,"BroadcastMessage",tolua_Network_Network_BroadcastMessage01);
   tolua_function(tolua_S,"BroadcastRemoteEvent",tolua_Network_Network_BroadcastRemoteEvent00);
   tolua_function(tolua_S,"BroadcastRemoteEvent",tolua_Network_Network_BroadcastRemoteEvent01);
   tolua_function(tolua_S,"BroadcastRemoteEvent",tolua_Network_Network_BroadcastRemoteEvent02);
   tolua_function(tolua_S,"BroadcastRemoteEvent",tolua_Network_Network_BroadcastRemoteEvent03);
   tolua_function(tolua_S,"BroadcastRemoteEvent",tolua_Network_Network_BroadcastRemoteEvent04);
   tolua_function(tolua_S,"BroadcastRemoteEvent",tolua_Network_Network_BroadcastRemoteEvent05);
   tolua_function(tolua_S,"SetUpdateFps",tolua_Network_Network_SetUpdateFps00);
   tolua_function(tolua_S,"RegisterRemoteEvent",tolua_Network_Network_RegisterRemoteEvent00);
   tolua_function(tolua_S,"UnregisterRemoteEvent",tolua_Network_Network_UnregisterRemoteEvent00);
   tolua_function(tolua_S,"UnregisterAllRemoteEvents",tolua_Network_Network_UnregisterAllRemoteEvents00);
   tolua_function(tolua_S,"SetPackageCacheDir",tolua_Network_Network_SetPackageCacheDir00);
   tolua_function(tolua_S,"GetUpdateFps",tolua_Network_Network_GetUpdateFps00);
   tolua_function(tolua_S,"GetServerConnection",tolua_Network_Network_GetServerConnection00);
   tolua_function(tolua_S,"IsServerRunning",tolua_Network_Network_IsServerRunning00);
   tolua_function(tolua_S,"CheckRemoteEvent",tolua_Network_Network_CheckRemoteEvent00);
   tolua_function(tolua_S,"GetPackageCacheDir",tolua_Network_Network_GetPackageCacheDir00);
  tolua_endmodule(tolua_S);
  tolua_function(tolua_S,"GetNetwork",tolua_Network_GetNetwork00);
  tolua_cclass(tolua_S,"NetworkPriority","NetworkPriority","Component",NULL);
  tolua_beginmodule(tolua_S,"NetworkPriority");
   tolua_function(tolua_S,"SetBasePriority",tolua_Network_NetworkPriority_SetBasePriority00);
   tolua_function(tolua_S,"SetDistanceFactor",tolua_Network_NetworkPriority_SetDistanceFactor00);
   tolua_function(tolua_S,"SetMinPriority",tolua_Network_NetworkPriority_SetMinPriority00);
   tolua_function(tolua_S,"SetAlwaysUpdateOwner",tolua_Network_NetworkPriority_SetAlwaysUpdateOwner00);
   tolua_function(tolua_S,"GetBasePriority",tolua_Network_NetworkPriority_GetBasePriority00);
   tolua_function(tolua_S,"GetDistanceFactor",tolua_Network_NetworkPriority_GetDistanceFactor00);
   tolua_function(tolua_S,"GetMinPriority",tolua_Network_NetworkPriority_GetMinPriority00);
   tolua_function(tolua_S,"GetAlwaysUpdateOwner",tolua_Network_NetworkPriority_GetAlwaysUpdateOwner00);
   tolua_function(tolua_S,"CheckUpdate",tolua_Network_NetworkPriority_CheckUpdate00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_Network (lua_State* tolua_S) {
 return tolua_Network_open(tolua_S);
};
#endif

