/*
** Lua binding: IO
** Generated automatically by tolua++-1.0.92 on 06/30/13 11:31:50.
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
TOLUA_API int  tolua_IO_open (lua_State* tolua_S);

#define TOLUA_RELEASE
#include "IOLuaAPI.h"
#include "File.h"
#include "FileSystem.h"
#include "Log.h"
#include "PackageFile.h"
using namespace Urho3D;
#pragma warning(disable:4800)

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_StringHash (lua_State* tolua_S)
{
 StringHash* self = (StringHash*) tolua_tousertype(tolua_S,1,0);
  Mtolua_delete(self);
  return 0;
}

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
 tolua_usertype(tolua_S,"Log");
 tolua_usertype(tolua_S,"PackageEntry");
 tolua_usertype(tolua_S,"StringHash");
 tolua_usertype(tolua_S,"FileSystem");
 tolua_usertype(tolua_S,"Object");
 tolua_usertype(tolua_S,"Deserializer");
 tolua_usertype(tolua_S,"File");
 tolua_usertype(tolua_S,"String");
 tolua_usertype(tolua_S,"PackageFile");
}

/* method: Read of class  File */
#ifndef TOLUA_DISABLE_tolua_IO_File_Read00
static int tolua_IO_File_Read00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"File",0,&tolua_err) ||
     !tolua_isuserdata(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  File* self = (File*)  tolua_tousertype(tolua_S,1,0);
  void* dest = ((void*)  tolua_touserdata(tolua_S,2,0));
  unsigned size = ((unsigned)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Read'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->Read(dest,size);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Read'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Seek of class  File */
#ifndef TOLUA_DISABLE_tolua_IO_File_Seek00
static int tolua_IO_File_Seek00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"File",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  File* self = (File*)  tolua_tousertype(tolua_S,1,0);
  unsigned position = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Seek'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->Seek(position);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Seek'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetName of class  File */
#ifndef TOLUA_DISABLE_tolua_IO_File_GetName00
static int tolua_IO_File_GetName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const File",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const File* self = (const File*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetChecksum of class  File */
#ifndef TOLUA_DISABLE_tolua_IO_File_GetChecksum00
static int tolua_IO_File_GetChecksum00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"File",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  File* self = (File*)  tolua_tousertype(tolua_S,1,0);
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

/* method: Open of class  File */
#ifndef TOLUA_DISABLE_tolua_IO_File_Open00
static int tolua_IO_File_Open00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"File",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  File* self = (File*)  tolua_tousertype(tolua_S,1,0);
  const String* fileName = ((const String*)  tolua_tousertype(tolua_S,2,0));
  FileMode mode = ((FileMode) (int)  tolua_tonumber(tolua_S,3,FILE_READ));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Open'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Open(*fileName,mode);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Open'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Open of class  File */
#ifndef TOLUA_DISABLE_tolua_IO_File_Open01
static int tolua_IO_File_Open01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"File",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"PackageFile",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  File* self = (File*)  tolua_tousertype(tolua_S,1,0);
  PackageFile* package = ((PackageFile*)  tolua_tousertype(tolua_S,2,0));
  const String* fileName = ((const String*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Open'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Open(package,*fileName);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_IO_File_Open00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: Close of class  File */
#ifndef TOLUA_DISABLE_tolua_IO_File_Close00
static int tolua_IO_File_Close00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"File",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  File* self = (File*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Close'", NULL);
#endif
  {
   self->Close();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Close'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Flush of class  File */
#ifndef TOLUA_DISABLE_tolua_IO_File_Flush00
static int tolua_IO_File_Flush00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"File",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  File* self = (File*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Flush'", NULL);
#endif
  {
   self->Flush();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Flush'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetName of class  File */
#ifndef TOLUA_DISABLE_tolua_IO_File_SetName00
static int tolua_IO_File_SetName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"File",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  File* self = (File*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetMode of class  File */
#ifndef TOLUA_DISABLE_tolua_IO_File_GetMode00
static int tolua_IO_File_GetMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const File",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const File* self = (const File*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMode'", NULL);
#endif
  {
   FileMode tolua_ret = (FileMode)  self->GetMode();
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

/* method: IsOpen of class  File */
#ifndef TOLUA_DISABLE_tolua_IO_File_IsOpen00
static int tolua_IO_File_IsOpen00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const File",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const File* self = (const File*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsOpen'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsOpen();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsOpen'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetHandle of class  File */
#ifndef TOLUA_DISABLE_tolua_IO_File_GetHandle00
static int tolua_IO_File_GetHandle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const File",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const File* self = (const File*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetHandle'", NULL);
#endif
  {
   void* tolua_ret = (void*)  self->GetHandle();
   tolua_pushuserdata(tolua_S,(void*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetHandle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsPackaged of class  File */
#ifndef TOLUA_DISABLE_tolua_IO_File_IsPackaged00
static int tolua_IO_File_IsPackaged00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const File",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const File* self = (const File*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsPackaged'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsPackaged();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsPackaged'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: SCAN_FILES */
#ifndef TOLUA_DISABLE_tolua_get_SCAN_FILES
static int tolua_get_SCAN_FILES(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)SCAN_FILES);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: SCAN_DIRS */
#ifndef TOLUA_DISABLE_tolua_get_SCAN_DIRS
static int tolua_get_SCAN_DIRS(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)SCAN_DIRS);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: SCAN_HIDDEN */
#ifndef TOLUA_DISABLE_tolua_get_SCAN_HIDDEN
static int tolua_get_SCAN_HIDDEN(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)SCAN_HIDDEN);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetCurrentDir of class  FileSystem */
#ifndef TOLUA_DISABLE_tolua_IO_FileSystem_SetCurrentDir00
static int tolua_IO_FileSystem_SetCurrentDir00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"FileSystem",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  FileSystem* self = (FileSystem*)  tolua_tousertype(tolua_S,1,0);
  const String* pathName = ((const String*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetCurrentDir'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SetCurrentDir(*pathName);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetCurrentDir'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CreateDir of class  FileSystem */
#ifndef TOLUA_DISABLE_tolua_IO_FileSystem_CreateDir00
static int tolua_IO_FileSystem_CreateDir00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"FileSystem",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  FileSystem* self = (FileSystem*)  tolua_tousertype(tolua_S,1,0);
  const String* pathName = ((const String*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CreateDir'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->CreateDir(*pathName);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CreateDir'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SystemCommand of class  FileSystem */
#ifndef TOLUA_DISABLE_tolua_IO_FileSystem_SystemCommand00
static int tolua_IO_FileSystem_SystemCommand00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"FileSystem",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  FileSystem* self = (FileSystem*)  tolua_tousertype(tolua_S,1,0);
  const String* commandLine = ((const String*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SystemCommand'", NULL);
#endif
  {
   int tolua_ret = (int)  self->SystemCommand(*commandLine);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SystemCommand'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SystemOpen of class  FileSystem */
#ifndef TOLUA_DISABLE_tolua_IO_FileSystem_SystemOpen00
static int tolua_IO_FileSystem_SystemOpen00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"FileSystem",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  FileSystem* self = (FileSystem*)  tolua_tousertype(tolua_S,1,0);
  const String* fileName = ((const String*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SystemOpen'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SystemOpen(*fileName);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SystemOpen'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SystemOpen of class  FileSystem */
#ifndef TOLUA_DISABLE_tolua_IO_FileSystem_SystemOpen01
static int tolua_IO_FileSystem_SystemOpen01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"FileSystem",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  FileSystem* self = (FileSystem*)  tolua_tousertype(tolua_S,1,0);
  const String* fileName = ((const String*)  tolua_tousertype(tolua_S,2,0));
  const String* mode = ((const String*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SystemOpen'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SystemOpen(*fileName,*mode);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_IO_FileSystem_SystemOpen00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: Copy of class  FileSystem */
#ifndef TOLUA_DISABLE_tolua_IO_FileSystem_Copy00
static int tolua_IO_FileSystem_Copy00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"FileSystem",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  FileSystem* self = (FileSystem*)  tolua_tousertype(tolua_S,1,0);
  const String* srcFileName = ((const String*)  tolua_tousertype(tolua_S,2,0));
  const String* destFileName = ((const String*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Copy'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Copy(*srcFileName,*destFileName);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Copy'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Rename of class  FileSystem */
#ifndef TOLUA_DISABLE_tolua_IO_FileSystem_Rename00
static int tolua_IO_FileSystem_Rename00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"FileSystem",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  FileSystem* self = (FileSystem*)  tolua_tousertype(tolua_S,1,0);
  const String* srcFileName = ((const String*)  tolua_tousertype(tolua_S,2,0));
  const String* destFileName = ((const String*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Rename'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Rename(*srcFileName,*destFileName);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Rename'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Delete of class  FileSystem */
#ifndef TOLUA_DISABLE_tolua_IO_FileSystem_Delete00
static int tolua_IO_FileSystem_Delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"FileSystem",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  FileSystem* self = (FileSystem*)  tolua_tousertype(tolua_S,1,0);
  const String* fileName = ((const String*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Delete'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Delete(*fileName);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Delete'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RegisterPath of class  FileSystem */
#ifndef TOLUA_DISABLE_tolua_IO_FileSystem_RegisterPath00
static int tolua_IO_FileSystem_RegisterPath00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"FileSystem",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  FileSystem* self = (FileSystem*)  tolua_tousertype(tolua_S,1,0);
  const String* pathName = ((const String*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RegisterPath'", NULL);
#endif
  {
   self->RegisterPath(*pathName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RegisterPath'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCurrentDir of class  FileSystem */
#ifndef TOLUA_DISABLE_tolua_IO_FileSystem_GetCurrentDir00
static int tolua_IO_FileSystem_GetCurrentDir00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const FileSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const FileSystem* self = (const FileSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCurrentDir'", NULL);
#endif
  {
   String tolua_ret = (String)  self->GetCurrentDir();
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
 tolua_error(tolua_S,"#ferror in function 'GetCurrentDir'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: HasRegisteredPaths of class  FileSystem */
#ifndef TOLUA_DISABLE_tolua_IO_FileSystem_HasRegisteredPaths00
static int tolua_IO_FileSystem_HasRegisteredPaths00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const FileSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const FileSystem* self = (const FileSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'HasRegisteredPaths'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->HasRegisteredPaths();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'HasRegisteredPaths'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CheckAccess of class  FileSystem */
#ifndef TOLUA_DISABLE_tolua_IO_FileSystem_CheckAccess00
static int tolua_IO_FileSystem_CheckAccess00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const FileSystem",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const FileSystem* self = (const FileSystem*)  tolua_tousertype(tolua_S,1,0);
  const String* pathName = ((const String*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CheckAccess'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->CheckAccess(*pathName);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CheckAccess'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLastModifiedTime of class  FileSystem */
#ifndef TOLUA_DISABLE_tolua_IO_FileSystem_GetLastModifiedTime00
static int tolua_IO_FileSystem_GetLastModifiedTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const FileSystem",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const FileSystem* self = (const FileSystem*)  tolua_tousertype(tolua_S,1,0);
  const String* fileName = ((const String*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLastModifiedTime'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetLastModifiedTime(*fileName);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLastModifiedTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: FileExists of class  FileSystem */
#ifndef TOLUA_DISABLE_tolua_IO_FileSystem_FileExists00
static int tolua_IO_FileSystem_FileExists00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const FileSystem",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const FileSystem* self = (const FileSystem*)  tolua_tousertype(tolua_S,1,0);
  const String* fileName = ((const String*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FileExists'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->FileExists(*fileName);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FileExists'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DirExists of class  FileSystem */
#ifndef TOLUA_DISABLE_tolua_IO_FileSystem_DirExists00
static int tolua_IO_FileSystem_DirExists00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const FileSystem",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const FileSystem* self = (const FileSystem*)  tolua_tousertype(tolua_S,1,0);
  const String* pathName = ((const String*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DirExists'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->DirExists(*pathName);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DirExists'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetProgramDir of class  FileSystem */
#ifndef TOLUA_DISABLE_tolua_IO_FileSystem_GetProgramDir00
static int tolua_IO_FileSystem_GetProgramDir00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const FileSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const FileSystem* self = (const FileSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetProgramDir'", NULL);
#endif
  {
   String tolua_ret = (String)  self->GetProgramDir();
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
 tolua_error(tolua_S,"#ferror in function 'GetProgramDir'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetUserDocumentsDir of class  FileSystem */
#ifndef TOLUA_DISABLE_tolua_IO_FileSystem_GetUserDocumentsDir00
static int tolua_IO_FileSystem_GetUserDocumentsDir00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const FileSystem",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const FileSystem* self = (const FileSystem*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetUserDocumentsDir'", NULL);
#endif
  {
   String tolua_ret = (String)  self->GetUserDocumentsDir();
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
 tolua_error(tolua_S,"#ferror in function 'GetUserDocumentsDir'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GetFileSystem */
#ifndef TOLUA_DISABLE_tolua_IO_GetFileSystem00
static int tolua_IO_GetFileSystem00(lua_State* tolua_S)
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
   FileSystem* tolua_ret = (FileSystem*)  GetFileSystem();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"FileSystem");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFileSystem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: SplitPath */
#ifndef TOLUA_DISABLE_tolua_IO_SplitPath00
static int tolua_IO_SplitPath00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"const String",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"String",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"String",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const String* fullPath = ((const String*)  tolua_tousertype(tolua_S,1,0));
  String* pathName = ((String*)  tolua_tousertype(tolua_S,2,0));
  String* fileName = ((String*)  tolua_tousertype(tolua_S,3,0));
  String* extension = ((String*)  tolua_tousertype(tolua_S,4,0));
  {
   SplitPath(*fullPath,*pathName,*fileName,*extension);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SplitPath'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GetPath */
#ifndef TOLUA_DISABLE_tolua_IO_GetPath00
static int tolua_IO_GetPath00(lua_State* tolua_S)
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
  const String* fullPath = ((const String*)  tolua_tousertype(tolua_S,1,0));
  {
   String tolua_ret = (String)  GetPath(*fullPath);
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
 tolua_error(tolua_S,"#ferror in function 'GetPath'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GetFileName */
#ifndef TOLUA_DISABLE_tolua_IO_GetFileName00
static int tolua_IO_GetFileName00(lua_State* tolua_S)
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
  const String* fullPath = ((const String*)  tolua_tousertype(tolua_S,1,0));
  {
   String tolua_ret = (String)  GetFileName(*fullPath);
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
 tolua_error(tolua_S,"#ferror in function 'GetFileName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GetExtension */
#ifndef TOLUA_DISABLE_tolua_IO_GetExtension00
static int tolua_IO_GetExtension00(lua_State* tolua_S)
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
  const String* fullPath = ((const String*)  tolua_tousertype(tolua_S,1,0));
  {
   String tolua_ret = (String)  GetExtension(*fullPath);
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
 tolua_error(tolua_S,"#ferror in function 'GetExtension'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GetFileNameAndExtension */
#ifndef TOLUA_DISABLE_tolua_IO_GetFileNameAndExtension00
static int tolua_IO_GetFileNameAndExtension00(lua_State* tolua_S)
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
  const String* fullPath = ((const String*)  tolua_tousertype(tolua_S,1,0));
  {
   String tolua_ret = (String)  GetFileNameAndExtension(*fullPath);
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
 tolua_error(tolua_S,"#ferror in function 'GetFileNameAndExtension'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: ReplaceExtension */
#ifndef TOLUA_DISABLE_tolua_IO_ReplaceExtension00
static int tolua_IO_ReplaceExtension00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     (tolua_isvaluenil(tolua_S,1,&tolua_err) || !tolua_isusertype(tolua_S,1,"const String",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const String* fullPath = ((const String*)  tolua_tousertype(tolua_S,1,0));
  const String* newExtension = ((const String*)  tolua_tousertype(tolua_S,2,0));
  {
   String tolua_ret = (String)  ReplaceExtension(*fullPath,*newExtension);
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
 tolua_error(tolua_S,"#ferror in function 'ReplaceExtension'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: AddTrailingSlash */
#ifndef TOLUA_DISABLE_tolua_IO_AddTrailingSlash00
static int tolua_IO_AddTrailingSlash00(lua_State* tolua_S)
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
  const String* pathName = ((const String*)  tolua_tousertype(tolua_S,1,0));
  {
   String tolua_ret = (String)  AddTrailingSlash(*pathName);
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
 tolua_error(tolua_S,"#ferror in function 'AddTrailingSlash'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: RemoveTrailingSlash */
#ifndef TOLUA_DISABLE_tolua_IO_RemoveTrailingSlash00
static int tolua_IO_RemoveTrailingSlash00(lua_State* tolua_S)
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
  const String* pathName = ((const String*)  tolua_tousertype(tolua_S,1,0));
  {
   String tolua_ret = (String)  RemoveTrailingSlash(*pathName);
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
 tolua_error(tolua_S,"#ferror in function 'RemoveTrailingSlash'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GetParentPath */
#ifndef TOLUA_DISABLE_tolua_IO_GetParentPath00
static int tolua_IO_GetParentPath00(lua_State* tolua_S)
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
  const String* pathName = ((const String*)  tolua_tousertype(tolua_S,1,0));
  {
   String tolua_ret = (String)  GetParentPath(*pathName);
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
 tolua_error(tolua_S,"#ferror in function 'GetParentPath'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GetInternalPath */
#ifndef TOLUA_DISABLE_tolua_IO_GetInternalPath00
static int tolua_IO_GetInternalPath00(lua_State* tolua_S)
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
  const String* pathName = ((const String*)  tolua_tousertype(tolua_S,1,0));
  {
   String tolua_ret = (String)  GetInternalPath(*pathName);
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
 tolua_error(tolua_S,"#ferror in function 'GetInternalPath'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GetNativePath */
#ifndef TOLUA_DISABLE_tolua_IO_GetNativePath00
static int tolua_IO_GetNativePath00(lua_State* tolua_S)
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
  const String* pathName = ((const String*)  tolua_tousertype(tolua_S,1,0));
  {
   String tolua_ret = (String)  GetNativePath(*pathName);
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
 tolua_error(tolua_S,"#ferror in function 'GetNativePath'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: LOG_DEBUG */
#ifndef TOLUA_DISABLE_tolua_get_LOG_DEBUG
static int tolua_get_LOG_DEBUG(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)LOG_DEBUG);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: LOG_INFO */
#ifndef TOLUA_DISABLE_tolua_get_LOG_INFO
static int tolua_get_LOG_INFO(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)LOG_INFO);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: LOG_WARNING */
#ifndef TOLUA_DISABLE_tolua_get_LOG_WARNING
static int tolua_get_LOG_WARNING(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)LOG_WARNING);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: LOG_ERROR */
#ifndef TOLUA_DISABLE_tolua_get_LOG_ERROR
static int tolua_get_LOG_ERROR(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)LOG_ERROR);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: LOG_NONE */
#ifndef TOLUA_DISABLE_tolua_get_LOG_NONE
static int tolua_get_LOG_NONE(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)LOG_NONE);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetLevel of class  Log */
#ifndef TOLUA_DISABLE_tolua_IO_Log_SetLevel00
static int tolua_IO_Log_SetLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Log",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Log* self = (Log*)  tolua_tousertype(tolua_S,1,0);
  int level = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLevel'", NULL);
#endif
  {
   self->SetLevel(level);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetTimeStamp of class  Log */
#ifndef TOLUA_DISABLE_tolua_IO_Log_SetTimeStamp00
static int tolua_IO_Log_SetTimeStamp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Log",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Log* self = (Log*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetTimeStamp'", NULL);
#endif
  {
   self->SetTimeStamp(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetTimeStamp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetQuiet of class  Log */
#ifndef TOLUA_DISABLE_tolua_IO_Log_SetQuiet00
static int tolua_IO_Log_SetQuiet00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Log",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Log* self = (Log*)  tolua_tousertype(tolua_S,1,0);
  bool quiet = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetQuiet'", NULL);
#endif
  {
   self->SetQuiet(quiet);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetQuiet'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLevel of class  Log */
#ifndef TOLUA_DISABLE_tolua_IO_Log_GetLevel00
static int tolua_IO_Log_GetLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Log",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Log* self = (const Log*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLevel'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetLevel();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTimeStamp of class  Log */
#ifndef TOLUA_DISABLE_tolua_IO_Log_GetTimeStamp00
static int tolua_IO_Log_GetTimeStamp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Log",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Log* self = (const Log*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTimeStamp'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetTimeStamp();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTimeStamp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsQuiet of class  Log */
#ifndef TOLUA_DISABLE_tolua_IO_Log_IsQuiet00
static int tolua_IO_Log_IsQuiet00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Log",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Log* self = (const Log*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsQuiet'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsQuiet();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsQuiet'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Write of class  Log */
#ifndef TOLUA_DISABLE_tolua_IO_Log_Write00
static int tolua_IO_Log_Write00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Log",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  int level = ((int)  tolua_tonumber(tolua_S,2,0));
  const char* message = ((const char*)  tolua_tostring(tolua_S,3,0));
  {
   Log::Write(level,message);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Write'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: WriteRaw of class  Log */
#ifndef TOLUA_DISABLE_tolua_IO_Log_WriteRaw00
static int tolua_IO_Log_WriteRaw00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Log",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* message = ((const char*)  tolua_tostring(tolua_S,2,0));
  bool error = ((bool)  tolua_toboolean(tolua_S,3,false));
  {
   Log::WriteRaw(message,error);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'WriteRaw'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GetLog */
#ifndef TOLUA_DISABLE_tolua_IO_GetLog00
static int tolua_IO_GetLog00(lua_State* tolua_S)
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
   Log* tolua_ret = (Log*)  GetLog();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Log");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLog'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: offset_ of class  PackageEntry */
#ifndef TOLUA_DISABLE_tolua_get_PackageEntry_offset_
static int tolua_get_PackageEntry_offset_(lua_State* tolua_S)
{
  PackageEntry* self = (PackageEntry*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'offset_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->offset_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: offset_ of class  PackageEntry */
#ifndef TOLUA_DISABLE_tolua_set_PackageEntry_offset_
static int tolua_set_PackageEntry_offset_(lua_State* tolua_S)
{
  PackageEntry* self = (PackageEntry*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'offset_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->offset_ = ((unsigned)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: size_ of class  PackageEntry */
#ifndef TOLUA_DISABLE_tolua_get_PackageEntry_size_
static int tolua_get_PackageEntry_size_(lua_State* tolua_S)
{
  PackageEntry* self = (PackageEntry*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'size_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->size_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: size_ of class  PackageEntry */
#ifndef TOLUA_DISABLE_tolua_set_PackageEntry_size_
static int tolua_set_PackageEntry_size_(lua_State* tolua_S)
{
  PackageEntry* self = (PackageEntry*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'size_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->size_ = ((unsigned)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: checksum_ of class  PackageEntry */
#ifndef TOLUA_DISABLE_tolua_get_PackageEntry_checksum_
static int tolua_get_PackageEntry_checksum_(lua_State* tolua_S)
{
  PackageEntry* self = (PackageEntry*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'checksum_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->checksum_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: checksum_ of class  PackageEntry */
#ifndef TOLUA_DISABLE_tolua_set_PackageEntry_checksum_
static int tolua_set_PackageEntry_checksum_(lua_State* tolua_S)
{
  PackageEntry* self = (PackageEntry*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'checksum_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->checksum_ = ((unsigned)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: Open of class  PackageFile */
#ifndef TOLUA_DISABLE_tolua_IO_PackageFile_Open00
static int tolua_IO_PackageFile_Open00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PackageFile",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PackageFile* self = (PackageFile*)  tolua_tousertype(tolua_S,1,0);
  const String* fileName = ((const String*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Open'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Open(*fileName);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Open'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Exists of class  PackageFile */
#ifndef TOLUA_DISABLE_tolua_IO_PackageFile_Exists00
static int tolua_IO_PackageFile_Exists00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const PackageFile",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const PackageFile* self = (const PackageFile*)  tolua_tousertype(tolua_S,1,0);
  const String* fileName = ((const String*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Exists'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Exists(*fileName);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Exists'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetEntry of class  PackageFile */
#ifndef TOLUA_DISABLE_tolua_IO_PackageFile_GetEntry00
static int tolua_IO_PackageFile_GetEntry00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const PackageFile",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const PackageFile* self = (const PackageFile*)  tolua_tousertype(tolua_S,1,0);
  const String* fileName = ((const String*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetEntry'", NULL);
#endif
  {
   const PackageEntry* tolua_ret = (const PackageEntry*)  self->GetEntry(*fileName);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"const PackageEntry");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetEntry'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetName of class  PackageFile */
#ifndef TOLUA_DISABLE_tolua_IO_PackageFile_GetName00
static int tolua_IO_PackageFile_GetName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const PackageFile",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const PackageFile* self = (const PackageFile*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetNameHash of class  PackageFile */
#ifndef TOLUA_DISABLE_tolua_IO_PackageFile_GetNameHash00
static int tolua_IO_PackageFile_GetNameHash00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const PackageFile",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const PackageFile* self = (const PackageFile*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetNumFiles of class  PackageFile */
#ifndef TOLUA_DISABLE_tolua_IO_PackageFile_GetNumFiles00
static int tolua_IO_PackageFile_GetNumFiles00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const PackageFile",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const PackageFile* self = (const PackageFile*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNumFiles'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetNumFiles();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNumFiles'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTotalSize of class  PackageFile */
#ifndef TOLUA_DISABLE_tolua_IO_PackageFile_GetTotalSize00
static int tolua_IO_PackageFile_GetTotalSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const PackageFile",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const PackageFile* self = (const PackageFile*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTotalSize'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetTotalSize();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTotalSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetChecksum of class  PackageFile */
#ifndef TOLUA_DISABLE_tolua_IO_PackageFile_GetChecksum00
static int tolua_IO_PackageFile_GetChecksum00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const PackageFile",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const PackageFile* self = (const PackageFile*)  tolua_tousertype(tolua_S,1,0);
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

/* Open function */
TOLUA_API int tolua_IO_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,1);
 tolua_beginmodule(tolua_S,NULL);
  tolua_constant(tolua_S,"FILE_READ",FILE_READ);
  tolua_constant(tolua_S,"FILE_WRITE",FILE_WRITE);
  tolua_constant(tolua_S,"FILE_READWRITE",FILE_READWRITE);
  tolua_cclass(tolua_S,"File","File","Deserializer",NULL);
  tolua_beginmodule(tolua_S,"File");
   tolua_function(tolua_S,"Read",tolua_IO_File_Read00);
   tolua_function(tolua_S,"Seek",tolua_IO_File_Seek00);
   tolua_function(tolua_S,"GetName",tolua_IO_File_GetName00);
   tolua_function(tolua_S,"GetChecksum",tolua_IO_File_GetChecksum00);
   tolua_function(tolua_S,"Open",tolua_IO_File_Open00);
   tolua_function(tolua_S,"Open",tolua_IO_File_Open01);
   tolua_function(tolua_S,"Close",tolua_IO_File_Close00);
   tolua_function(tolua_S,"Flush",tolua_IO_File_Flush00);
   tolua_function(tolua_S,"SetName",tolua_IO_File_SetName00);
   tolua_function(tolua_S,"GetMode",tolua_IO_File_GetMode00);
   tolua_function(tolua_S,"IsOpen",tolua_IO_File_IsOpen00);
   tolua_function(tolua_S,"GetHandle",tolua_IO_File_GetHandle00);
   tolua_function(tolua_S,"IsPackaged",tolua_IO_File_IsPackaged00);
  tolua_endmodule(tolua_S);
  tolua_variable(tolua_S,"SCAN_FILES",tolua_get_SCAN_FILES,NULL);
  tolua_variable(tolua_S,"SCAN_DIRS",tolua_get_SCAN_DIRS,NULL);
  tolua_variable(tolua_S,"SCAN_HIDDEN",tolua_get_SCAN_HIDDEN,NULL);
  tolua_cclass(tolua_S,"FileSystem","FileSystem","Object",NULL);
  tolua_beginmodule(tolua_S,"FileSystem");
   tolua_function(tolua_S,"SetCurrentDir",tolua_IO_FileSystem_SetCurrentDir00);
   tolua_function(tolua_S,"CreateDir",tolua_IO_FileSystem_CreateDir00);
   tolua_function(tolua_S,"SystemCommand",tolua_IO_FileSystem_SystemCommand00);
   tolua_function(tolua_S,"SystemOpen",tolua_IO_FileSystem_SystemOpen00);
   tolua_function(tolua_S,"SystemOpen",tolua_IO_FileSystem_SystemOpen01);
   tolua_function(tolua_S,"Copy",tolua_IO_FileSystem_Copy00);
   tolua_function(tolua_S,"Rename",tolua_IO_FileSystem_Rename00);
   tolua_function(tolua_S,"Delete",tolua_IO_FileSystem_Delete00);
   tolua_function(tolua_S,"RegisterPath",tolua_IO_FileSystem_RegisterPath00);
   tolua_function(tolua_S,"GetCurrentDir",tolua_IO_FileSystem_GetCurrentDir00);
   tolua_function(tolua_S,"HasRegisteredPaths",tolua_IO_FileSystem_HasRegisteredPaths00);
   tolua_function(tolua_S,"CheckAccess",tolua_IO_FileSystem_CheckAccess00);
   tolua_function(tolua_S,"GetLastModifiedTime",tolua_IO_FileSystem_GetLastModifiedTime00);
   tolua_function(tolua_S,"FileExists",tolua_IO_FileSystem_FileExists00);
   tolua_function(tolua_S,"DirExists",tolua_IO_FileSystem_DirExists00);
   tolua_function(tolua_S,"GetProgramDir",tolua_IO_FileSystem_GetProgramDir00);
   tolua_function(tolua_S,"GetUserDocumentsDir",tolua_IO_FileSystem_GetUserDocumentsDir00);
  tolua_endmodule(tolua_S);
  tolua_function(tolua_S,"GetFileSystem",tolua_IO_GetFileSystem00);
  tolua_function(tolua_S,"SplitPath",tolua_IO_SplitPath00);
  tolua_function(tolua_S,"GetPath",tolua_IO_GetPath00);
  tolua_function(tolua_S,"GetFileName",tolua_IO_GetFileName00);
  tolua_function(tolua_S,"GetExtension",tolua_IO_GetExtension00);
  tolua_function(tolua_S,"GetFileNameAndExtension",tolua_IO_GetFileNameAndExtension00);
  tolua_function(tolua_S,"ReplaceExtension",tolua_IO_ReplaceExtension00);
  tolua_function(tolua_S,"AddTrailingSlash",tolua_IO_AddTrailingSlash00);
  tolua_function(tolua_S,"RemoveTrailingSlash",tolua_IO_RemoveTrailingSlash00);
  tolua_function(tolua_S,"GetParentPath",tolua_IO_GetParentPath00);
  tolua_function(tolua_S,"GetInternalPath",tolua_IO_GetInternalPath00);
  tolua_function(tolua_S,"GetNativePath",tolua_IO_GetNativePath00);
  tolua_variable(tolua_S,"LOG_DEBUG",tolua_get_LOG_DEBUG,NULL);
  tolua_variable(tolua_S,"LOG_INFO",tolua_get_LOG_INFO,NULL);
  tolua_variable(tolua_S,"LOG_WARNING",tolua_get_LOG_WARNING,NULL);
  tolua_variable(tolua_S,"LOG_ERROR",tolua_get_LOG_ERROR,NULL);
  tolua_variable(tolua_S,"LOG_NONE",tolua_get_LOG_NONE,NULL);
  tolua_cclass(tolua_S,"Log","Log","Object",NULL);
  tolua_beginmodule(tolua_S,"Log");
   tolua_function(tolua_S,"SetLevel",tolua_IO_Log_SetLevel00);
   tolua_function(tolua_S,"SetTimeStamp",tolua_IO_Log_SetTimeStamp00);
   tolua_function(tolua_S,"SetQuiet",tolua_IO_Log_SetQuiet00);
   tolua_function(tolua_S,"GetLevel",tolua_IO_Log_GetLevel00);
   tolua_function(tolua_S,"GetTimeStamp",tolua_IO_Log_GetTimeStamp00);
   tolua_function(tolua_S,"IsQuiet",tolua_IO_Log_IsQuiet00);
   tolua_function(tolua_S,"Write",tolua_IO_Log_Write00);
   tolua_function(tolua_S,"WriteRaw",tolua_IO_Log_WriteRaw00);
  tolua_endmodule(tolua_S);
  tolua_function(tolua_S,"GetLog",tolua_IO_GetLog00);
  tolua_cclass(tolua_S,"PackageEntry","PackageEntry","",NULL);
  tolua_beginmodule(tolua_S,"PackageEntry");
   tolua_variable(tolua_S,"offset_",tolua_get_PackageEntry_offset_,tolua_set_PackageEntry_offset_);
   tolua_variable(tolua_S,"size_",tolua_get_PackageEntry_size_,tolua_set_PackageEntry_size_);
   tolua_variable(tolua_S,"checksum_",tolua_get_PackageEntry_checksum_,tolua_set_PackageEntry_checksum_);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"PackageFile","PackageFile","Object",NULL);
  tolua_beginmodule(tolua_S,"PackageFile");
   tolua_function(tolua_S,"Open",tolua_IO_PackageFile_Open00);
   tolua_function(tolua_S,"Exists",tolua_IO_PackageFile_Exists00);
   tolua_function(tolua_S,"GetEntry",tolua_IO_PackageFile_GetEntry00);
   tolua_function(tolua_S,"GetName",tolua_IO_PackageFile_GetName00);
   tolua_function(tolua_S,"GetNameHash",tolua_IO_PackageFile_GetNameHash00);
   tolua_function(tolua_S,"GetNumFiles",tolua_IO_PackageFile_GetNumFiles00);
   tolua_function(tolua_S,"GetTotalSize",tolua_IO_PackageFile_GetTotalSize00);
   tolua_function(tolua_S,"GetChecksum",tolua_IO_PackageFile_GetChecksum00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_IO (lua_State* tolua_S) {
 return tolua_IO_open(tolua_S);
};
#endif

