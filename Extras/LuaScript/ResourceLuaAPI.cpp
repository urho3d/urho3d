/*
** Lua binding: Resource
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
TOLUA_API int  tolua_Resource_open (lua_State* tolua_S);

#define TOLUA_RELEASE
#include "ResourceLuaAPI.h"
#include "Image.h"
#include "Resource.h"
#include "ResourceCache.h"
#include "XMLElement.h"
#include "XMLFile.h"
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

static int tolua_collect_IntRect (lua_State* tolua_S)
{
 IntRect* self = (IntRect*) tolua_tousertype(tolua_S,1,0);
  Mtolua_delete(self);
  return 0;
}

static int tolua_collect_Color (lua_State* tolua_S)
{
 Color* self = (Color*) tolua_tousertype(tolua_S,1,0);
  Mtolua_delete(self);
  return 0;
}

static int tolua_collect_Vector4 (lua_State* tolua_S)
{
 Vector4* self = (Vector4*) tolua_tousertype(tolua_S,1,0);
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

static int tolua_collect_Quaternion (lua_State* tolua_S)
{
 Quaternion* self = (Quaternion*) tolua_tousertype(tolua_S,1,0);
  Mtolua_delete(self);
  return 0;
}

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

static int tolua_collect_XMLElement (lua_State* tolua_S)
{
 XMLElement* self = (XMLElement*) tolua_tousertype(tolua_S,1,0);
  Mtolua_delete(self);
  return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"String");
 tolua_usertype(tolua_S,"Resource");
 tolua_usertype(tolua_S,"Color");
 tolua_usertype(tolua_S,"XMLFile");
 tolua_usertype(tolua_S,"Image");
 tolua_usertype(tolua_S,"Vector4");
 tolua_usertype(tolua_S,"Vector3");
 tolua_usertype(tolua_S,"Vector2");
 tolua_usertype(tolua_S,"Material");
 tolua_usertype(tolua_S,"Sound");
 tolua_usertype(tolua_S,"BoundingBox");
 tolua_usertype(tolua_S,"XMLElement");
 tolua_usertype(tolua_S,"ResourceRef");
 tolua_usertype(tolua_S,"ResourceCache");
 tolua_usertype(tolua_S,"Animation");
 tolua_usertype(tolua_S,"Quaternion");
 tolua_usertype(tolua_S,"Rect");
 tolua_usertype(tolua_S,"IntVector2");
 tolua_usertype(tolua_S,"StringHash");
 tolua_usertype(tolua_S,"IntRect");
 tolua_usertype(tolua_S,"Font");
 tolua_usertype(tolua_S,"ResourceRefList");
 tolua_usertype(tolua_S,"Model");
 tolua_usertype(tolua_S,"Technique");
 tolua_usertype(tolua_S,"TextureCube");
 tolua_usertype(tolua_S,"Texture2D");
 tolua_usertype(tolua_S,"ShortStringHash");
}

/* method: FlipVertical of class  Image */
#ifndef TOLUA_DISABLE_tolua_Resource_Image_FlipVertical00
static int tolua_Resource_Image_FlipVertical00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Image",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Image* self = (Image*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FlipVertical'", NULL);
#endif
  {
   self->FlipVertical();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FlipVertical'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SaveBMP of class  Image */
#ifndef TOLUA_DISABLE_tolua_Resource_Image_SaveBMP00
static int tolua_Resource_Image_SaveBMP00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Image",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Image* self = (Image*)  tolua_tousertype(tolua_S,1,0);
  const char* fileName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SaveBMP'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SaveBMP(fileName);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SaveBMP'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SavePNG of class  Image */
#ifndef TOLUA_DISABLE_tolua_Resource_Image_SavePNG00
static int tolua_Resource_Image_SavePNG00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Image",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Image* self = (Image*)  tolua_tousertype(tolua_S,1,0);
  const char* fileName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SavePNG'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SavePNG(fileName);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SavePNG'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SaveTGA of class  Image */
#ifndef TOLUA_DISABLE_tolua_Resource_Image_SaveTGA00
static int tolua_Resource_Image_SaveTGA00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Image",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Image* self = (Image*)  tolua_tousertype(tolua_S,1,0);
  const char* fileName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SaveTGA'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SaveTGA(fileName);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SaveTGA'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SaveJPG of class  Image */
#ifndef TOLUA_DISABLE_tolua_Resource_Image_SaveJPG00
static int tolua_Resource_Image_SaveJPG00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Image",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Image* self = (Image*)  tolua_tousertype(tolua_S,1,0);
  const char* fileName = ((const char*)  tolua_tostring(tolua_S,2,0));
  int quality = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SaveJPG'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SaveJPG(fileName,quality);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SaveJPG'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetWidth of class  Image */
#ifndef TOLUA_DISABLE_tolua_Resource_Image_GetWidth00
static int tolua_Resource_Image_GetWidth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Image",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Image* self = (const Image*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetWidth'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetWidth();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetWidth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetHeight of class  Image */
#ifndef TOLUA_DISABLE_tolua_Resource_Image_GetHeight00
static int tolua_Resource_Image_GetHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Image",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Image* self = (const Image*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetHeight'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetHeight();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetHeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetComponents of class  Image */
#ifndef TOLUA_DISABLE_tolua_Resource_Image_GetComponents00
static int tolua_Resource_Image_GetComponents00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Image",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Image* self = (const Image*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetComponents'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetComponents();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetComponents'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsCompressed of class  Image */
#ifndef TOLUA_DISABLE_tolua_Resource_Image_IsCompressed00
static int tolua_Resource_Image_IsCompressed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Image",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Image* self = (const Image*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsCompressed'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsCompressed();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsCompressed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCompressedFormat of class  Image */
#ifndef TOLUA_DISABLE_tolua_Resource_Image_GetCompressedFormat00
static int tolua_Resource_Image_GetCompressedFormat00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Image",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Image* self = (const Image*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCompressedFormat'", NULL);
#endif
  {
   CompressedFormat tolua_ret = (CompressedFormat)  self->GetCompressedFormat();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCompressedFormat'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetName of class  Resource */
#ifndef TOLUA_DISABLE_tolua_Resource_Resource_SetName00
static int tolua_Resource_Resource_SetName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Resource",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Resource* self = (Resource*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetName of class  Resource */
#ifndef TOLUA_DISABLE_tolua_Resource_Resource_GetName00
static int tolua_Resource_Resource_GetName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Resource",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Resource* self = (const Resource*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetNameHash of class  Resource */
#ifndef TOLUA_DISABLE_tolua_Resource_Resource_GetNameHash00
static int tolua_Resource_Resource_GetNameHash00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Resource",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Resource* self = (const Resource*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetMemoryUse of class  Resource */
#ifndef TOLUA_DISABLE_tolua_Resource_Resource_GetMemoryUse00
static int tolua_Resource_Resource_GetMemoryUse00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Resource",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Resource* self = (const Resource*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMemoryUse'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetMemoryUse();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMemoryUse'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ReleaseAllResources of class  ResourceCache */
#ifndef TOLUA_DISABLE_tolua_Resource_ResourceCache_ReleaseAllResources00
static int tolua_Resource_ResourceCache_ReleaseAllResources00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ResourceCache",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ResourceCache* self = (ResourceCache*)  tolua_tousertype(tolua_S,1,0);
  bool force = ((bool)  tolua_toboolean(tolua_S,2,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ReleaseAllResources'", NULL);
#endif
  {
   self->ReleaseAllResources(force);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ReleaseAllResources'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ReloadResource of class  ResourceCache */
#ifndef TOLUA_DISABLE_tolua_Resource_ResourceCache_ReloadResource00
static int tolua_Resource_ResourceCache_ReloadResource00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ResourceCache",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Resource",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ResourceCache* self = (ResourceCache*)  tolua_tousertype(tolua_S,1,0);
  Resource* resource = ((Resource*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ReloadResource'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->ReloadResource(resource);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ReloadResource'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMemoryBudget of class  ResourceCache */
#ifndef TOLUA_DISABLE_tolua_Resource_ResourceCache_SetMemoryBudget00
static int tolua_Resource_ResourceCache_SetMemoryBudget00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ResourceCache",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"ShortStringHash",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ResourceCache* self = (ResourceCache*)  tolua_tousertype(tolua_S,1,0);
  ShortStringHash type = *((ShortStringHash*)  tolua_tousertype(tolua_S,2,0));
  unsigned budget = ((unsigned)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMemoryBudget'", NULL);
#endif
  {
   self->SetMemoryBudget(type,budget);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMemoryBudget'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetAutoReloadResources of class  ResourceCache */
#ifndef TOLUA_DISABLE_tolua_Resource_ResourceCache_SetAutoReloadResources00
static int tolua_Resource_ResourceCache_SetAutoReloadResources00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ResourceCache",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ResourceCache* self = (ResourceCache*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetAutoReloadResources'", NULL);
#endif
  {
   self->SetAutoReloadResources(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetAutoReloadResources'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Exists of class  ResourceCache */
#ifndef TOLUA_DISABLE_tolua_Resource_ResourceCache_Exists00
static int tolua_Resource_ResourceCache_Exists00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ResourceCache",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ResourceCache* self = (const ResourceCache*)  tolua_tousertype(tolua_S,1,0);
  const String* name = ((const String*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Exists'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Exists(*name);
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

/* method: Exists of class  ResourceCache */
#ifndef TOLUA_DISABLE_tolua_Resource_ResourceCache_Exists01
static int tolua_Resource_ResourceCache_Exists01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ResourceCache",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"StringHash",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const ResourceCache* self = (const ResourceCache*)  tolua_tousertype(tolua_S,1,0);
  StringHash nameHash = *((StringHash*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Exists'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Exists(nameHash);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_Resource_ResourceCache_Exists00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMemoryBudget of class  ResourceCache */
#ifndef TOLUA_DISABLE_tolua_Resource_ResourceCache_GetMemoryBudget00
static int tolua_Resource_ResourceCache_GetMemoryBudget00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ResourceCache",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"ShortStringHash",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ResourceCache* self = (const ResourceCache*)  tolua_tousertype(tolua_S,1,0);
  ShortStringHash type = *((ShortStringHash*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMemoryBudget'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetMemoryBudget(type);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMemoryBudget'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMemoryUse of class  ResourceCache */
#ifndef TOLUA_DISABLE_tolua_Resource_ResourceCache_GetMemoryUse00
static int tolua_Resource_ResourceCache_GetMemoryUse00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ResourceCache",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"ShortStringHash",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ResourceCache* self = (const ResourceCache*)  tolua_tousertype(tolua_S,1,0);
  ShortStringHash type = *((ShortStringHash*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMemoryUse'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetMemoryUse(type);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMemoryUse'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTotalMemoryUse of class  ResourceCache */
#ifndef TOLUA_DISABLE_tolua_Resource_ResourceCache_GetTotalMemoryUse00
static int tolua_Resource_ResourceCache_GetTotalMemoryUse00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ResourceCache",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ResourceCache* self = (const ResourceCache*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTotalMemoryUse'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetTotalMemoryUse();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTotalMemoryUse'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetResourceName of class  ResourceCache */
#ifndef TOLUA_DISABLE_tolua_Resource_ResourceCache_GetResourceName00
static int tolua_Resource_ResourceCache_GetResourceName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ResourceCache",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"StringHash",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ResourceCache* self = (const ResourceCache*)  tolua_tousertype(tolua_S,1,0);
  StringHash nameHash = *((StringHash*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetResourceName'", NULL);
#endif
  {
   const String& tolua_ret = (const String&)  self->GetResourceName(nameHash);
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const String");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetResourceName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetResourceFileName of class  ResourceCache */
#ifndef TOLUA_DISABLE_tolua_Resource_ResourceCache_GetResourceFileName00
static int tolua_Resource_ResourceCache_GetResourceFileName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ResourceCache",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ResourceCache* self = (const ResourceCache*)  tolua_tousertype(tolua_S,1,0);
  const String* name = ((const String*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetResourceFileName'", NULL);
#endif
  {
   String tolua_ret = (String)  self->GetResourceFileName(*name);
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
 tolua_error(tolua_S,"#ferror in function 'GetResourceFileName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAutoReloadResources of class  ResourceCache */
#ifndef TOLUA_DISABLE_tolua_Resource_ResourceCache_GetAutoReloadResources00
static int tolua_Resource_ResourceCache_GetAutoReloadResources00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ResourceCache",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ResourceCache* self = (const ResourceCache*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAutoReloadResources'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetAutoReloadResources();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAutoReloadResources'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ResourceCacheGetAnimation of class  ResourceCache */
#ifndef TOLUA_DISABLE_tolua_Resource_ResourceCache_GetAnimation00
static int tolua_Resource_ResourceCache_GetAnimation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ResourceCache",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ResourceCache* self = (ResourceCache*)  tolua_tousertype(tolua_S,1,0);
  const char* fileName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ResourceCacheGetAnimation'", NULL);
#endif
  {
   tolua_outside Animation* tolua_ret = (tolua_outside Animation*)  ResourceCacheGetAnimation(self,fileName);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Animation");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAnimation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ResourceCacheGetFont of class  ResourceCache */
#ifndef TOLUA_DISABLE_tolua_Resource_ResourceCache_GetFont00
static int tolua_Resource_ResourceCache_GetFont00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ResourceCache",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ResourceCache* self = (ResourceCache*)  tolua_tousertype(tolua_S,1,0);
  const char* fileName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ResourceCacheGetFont'", NULL);
#endif
  {
   tolua_outside Font* tolua_ret = (tolua_outside Font*)  ResourceCacheGetFont(self,fileName);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Font");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFont'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ResourceCacheGetImage of class  ResourceCache */
#ifndef TOLUA_DISABLE_tolua_Resource_ResourceCache_GetImage00
static int tolua_Resource_ResourceCache_GetImage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ResourceCache",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ResourceCache* self = (ResourceCache*)  tolua_tousertype(tolua_S,1,0);
  const char* fileName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ResourceCacheGetImage'", NULL);
#endif
  {
   tolua_outside Image* tolua_ret = (tolua_outside Image*)  ResourceCacheGetImage(self,fileName);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Image");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetImage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ResourceCacheGetMaterial of class  ResourceCache */
#ifndef TOLUA_DISABLE_tolua_Resource_ResourceCache_GetMaterial00
static int tolua_Resource_ResourceCache_GetMaterial00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ResourceCache",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ResourceCache* self = (ResourceCache*)  tolua_tousertype(tolua_S,1,0);
  const char* fileName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ResourceCacheGetMaterial'", NULL);
#endif
  {
   tolua_outside Material* tolua_ret = (tolua_outside Material*)  ResourceCacheGetMaterial(self,fileName);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Material");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMaterial'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ResourceCacheGetModel of class  ResourceCache */
#ifndef TOLUA_DISABLE_tolua_Resource_ResourceCache_GetModel00
static int tolua_Resource_ResourceCache_GetModel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ResourceCache",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ResourceCache* self = (ResourceCache*)  tolua_tousertype(tolua_S,1,0);
  const char* fileName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ResourceCacheGetModel'", NULL);
#endif
  {
   tolua_outside Model* tolua_ret = (tolua_outside Model*)  ResourceCacheGetModel(self,fileName);
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

/* method: ResourceCacheGetSound of class  ResourceCache */
#ifndef TOLUA_DISABLE_tolua_Resource_ResourceCache_GetSound00
static int tolua_Resource_ResourceCache_GetSound00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ResourceCache",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ResourceCache* self = (ResourceCache*)  tolua_tousertype(tolua_S,1,0);
  const char* fileName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ResourceCacheGetSound'", NULL);
#endif
  {
   tolua_outside Sound* tolua_ret = (tolua_outside Sound*)  ResourceCacheGetSound(self,fileName);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Sound");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSound'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ResourceCacheGetTechnique of class  ResourceCache */
#ifndef TOLUA_DISABLE_tolua_Resource_ResourceCache_GetTechnique00
static int tolua_Resource_ResourceCache_GetTechnique00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ResourceCache",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ResourceCache* self = (ResourceCache*)  tolua_tousertype(tolua_S,1,0);
  const char* fileName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ResourceCacheGetTechnique'", NULL);
#endif
  {
   tolua_outside Technique* tolua_ret = (tolua_outside Technique*)  ResourceCacheGetTechnique(self,fileName);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Technique");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTechnique'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ResourceCacheGetTexture2D of class  ResourceCache */
#ifndef TOLUA_DISABLE_tolua_Resource_ResourceCache_GetTexture2D00
static int tolua_Resource_ResourceCache_GetTexture2D00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ResourceCache",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ResourceCache* self = (ResourceCache*)  tolua_tousertype(tolua_S,1,0);
  const char* fileName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ResourceCacheGetTexture2D'", NULL);
#endif
  {
   tolua_outside Texture2D* tolua_ret = (tolua_outside Texture2D*)  ResourceCacheGetTexture2D(self,fileName);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Texture2D");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTexture2D'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ResourceCacheGetTextureCube of class  ResourceCache */
#ifndef TOLUA_DISABLE_tolua_Resource_ResourceCache_GetTextureCube00
static int tolua_Resource_ResourceCache_GetTextureCube00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ResourceCache",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ResourceCache* self = (ResourceCache*)  tolua_tousertype(tolua_S,1,0);
  const char* fileName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ResourceCacheGetTextureCube'", NULL);
#endif
  {
   tolua_outside TextureCube* tolua_ret = (tolua_outside TextureCube*)  ResourceCacheGetTextureCube(self,fileName);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"TextureCube");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTextureCube'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ResourceCacheGetXMLFile of class  ResourceCache */
#ifndef TOLUA_DISABLE_tolua_Resource_ResourceCache_GetXMLFile00
static int tolua_Resource_ResourceCache_GetXMLFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ResourceCache",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ResourceCache* self = (ResourceCache*)  tolua_tousertype(tolua_S,1,0);
  const char* fileName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ResourceCacheGetXMLFile'", NULL);
#endif
  {
   tolua_outside XMLFile* tolua_ret = (tolua_outside XMLFile*)  ResourceCacheGetXMLFile(self,fileName);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"XMLFile");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetXMLFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GetCache */
#ifndef TOLUA_DISABLE_tolua_Resource_GetCache00
static int tolua_Resource_GetCache00(lua_State* tolua_S)
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
   ResourceCache* tolua_ret = (ResourceCache*)  GetCache();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ResourceCache");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCache'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsNull of class  XMLElement */
#ifndef TOLUA_DISABLE_tolua_Resource_XMLElement_IsNull00
static int tolua_Resource_XMLElement_IsNull00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const XMLElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const XMLElement* self = (const XMLElement*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsNull'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsNull();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsNull'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: NotNull of class  XMLElement */
#ifndef TOLUA_DISABLE_tolua_Resource_XMLElement_NotNull00
static int tolua_Resource_XMLElement_NotNull00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const XMLElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const XMLElement* self = (const XMLElement*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'NotNull'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->NotNull();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'NotNull'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: operatorbool of class  XMLElement */
#ifndef TOLUA_DISABLE_tolua_Resource_XMLElement__bool00
static int tolua_Resource_XMLElement__bool00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const XMLElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const XMLElement* self = (const XMLElement*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'operatorbool'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->operator  bool();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function '.bool'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetName of class  XMLElement */
#ifndef TOLUA_DISABLE_tolua_Resource_XMLElement_GetName00
static int tolua_Resource_XMLElement_GetName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const XMLElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const XMLElement* self = (const XMLElement*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetName'", NULL);
#endif
  {
   String tolua_ret = (String)  self->GetName();
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
 tolua_error(tolua_S,"#ferror in function 'GetName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: HasChild of class  XMLElement */
#ifndef TOLUA_DISABLE_tolua_Resource_XMLElement_HasChild00
static int tolua_Resource_XMLElement_HasChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const XMLElement",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const XMLElement* self = (const XMLElement*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'HasChild'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->HasChild(name);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'HasChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: HasChild of class  XMLElement */
#ifndef TOLUA_DISABLE_tolua_Resource_XMLElement_HasChild01
static int tolua_Resource_XMLElement_HasChild01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const XMLElement",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const XMLElement* self = (const XMLElement*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'HasChild'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->HasChild(name);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_Resource_XMLElement_HasChild00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetChild of class  XMLElement */
#ifndef TOLUA_DISABLE_tolua_Resource_XMLElement_GetChild00
static int tolua_Resource_XMLElement_GetChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const XMLElement",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const XMLElement* self = (const XMLElement*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetChild'", NULL);
#endif
  {
   XMLElement tolua_ret = (XMLElement)  self->GetChild(name);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((XMLElement)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"XMLElement");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(XMLElement));
     tolua_pushusertype(tolua_S,tolua_obj,"XMLElement");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
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

/* method: GetChild of class  XMLElement */
#ifndef TOLUA_DISABLE_tolua_Resource_XMLElement_GetChild01
static int tolua_Resource_XMLElement_GetChild01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const XMLElement",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const XMLElement* self = (const XMLElement*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetChild'", NULL);
#endif
  {
   XMLElement tolua_ret = (XMLElement)  self->GetChild(name);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((XMLElement)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"XMLElement");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(XMLElement));
     tolua_pushusertype(tolua_S,tolua_obj,"XMLElement");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_Resource_XMLElement_GetChild00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNext of class  XMLElement */
#ifndef TOLUA_DISABLE_tolua_Resource_XMLElement_GetNext00
static int tolua_Resource_XMLElement_GetNext00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const XMLElement",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const XMLElement* self = (const XMLElement*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNext'", NULL);
#endif
  {
   XMLElement tolua_ret = (XMLElement)  self->GetNext(name);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((XMLElement)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"XMLElement");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(XMLElement));
     tolua_pushusertype(tolua_S,tolua_obj,"XMLElement");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNext'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNext of class  XMLElement */
#ifndef TOLUA_DISABLE_tolua_Resource_XMLElement_GetNext01
static int tolua_Resource_XMLElement_GetNext01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const XMLElement",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const XMLElement* self = (const XMLElement*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNext'", NULL);
#endif
  {
   XMLElement tolua_ret = (XMLElement)  self->GetNext(name);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((XMLElement)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"XMLElement");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(XMLElement));
     tolua_pushusertype(tolua_S,tolua_obj,"XMLElement");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_Resource_XMLElement_GetNext00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetParent of class  XMLElement */
#ifndef TOLUA_DISABLE_tolua_Resource_XMLElement_GetParent00
static int tolua_Resource_XMLElement_GetParent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const XMLElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const XMLElement* self = (const XMLElement*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetParent'", NULL);
#endif
  {
   XMLElement tolua_ret = (XMLElement)  self->GetParent();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((XMLElement)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"XMLElement");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(XMLElement));
     tolua_pushusertype(tolua_S,tolua_obj,"XMLElement");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
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

/* method: GetNumAttributes of class  XMLElement */
#ifndef TOLUA_DISABLE_tolua_Resource_XMLElement_GetNumAttributes00
static int tolua_Resource_XMLElement_GetNumAttributes00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const XMLElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const XMLElement* self = (const XMLElement*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNumAttributes'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetNumAttributes();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNumAttributes'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: HasAttribute of class  XMLElement */
#ifndef TOLUA_DISABLE_tolua_Resource_XMLElement_HasAttribute00
static int tolua_Resource_XMLElement_HasAttribute00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const XMLElement",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const XMLElement* self = (const XMLElement*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'HasAttribute'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->HasAttribute(name);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'HasAttribute'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: HasAttribute of class  XMLElement */
#ifndef TOLUA_DISABLE_tolua_Resource_XMLElement_HasAttribute01
static int tolua_Resource_XMLElement_HasAttribute01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const XMLElement",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const XMLElement* self = (const XMLElement*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'HasAttribute'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->HasAttribute(name);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_Resource_XMLElement_HasAttribute00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetBool of class  XMLElement */
#ifndef TOLUA_DISABLE_tolua_Resource_XMLElement_GetBool00
static int tolua_Resource_XMLElement_GetBool00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const XMLElement",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const XMLElement* self = (const XMLElement*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetBool'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetBool(name);
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

/* method: GetBoundingBox of class  XMLElement */
#ifndef TOLUA_DISABLE_tolua_Resource_XMLElement_GetBoundingBox00
static int tolua_Resource_XMLElement_GetBoundingBox00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const XMLElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const XMLElement* self = (const XMLElement*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetBoundingBox'", NULL);
#endif
  {
   BoundingBox tolua_ret = (BoundingBox)  self->GetBoundingBox();
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
 tolua_error(tolua_S,"#ferror in function 'GetBoundingBox'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetColor of class  XMLElement */
#ifndef TOLUA_DISABLE_tolua_Resource_XMLElement_GetColor00
static int tolua_Resource_XMLElement_GetColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const XMLElement",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const XMLElement* self = (const XMLElement*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetColor'", NULL);
#endif
  {
   Color tolua_ret = (Color)  self->GetColor(name);
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
 tolua_error(tolua_S,"#ferror in function 'GetColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFloat of class  XMLElement */
#ifndef TOLUA_DISABLE_tolua_Resource_XMLElement_GetFloat00
static int tolua_Resource_XMLElement_GetFloat00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const XMLElement",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const XMLElement* self = (const XMLElement*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFloat'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetFloat(name);
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

/* method: GetUInt of class  XMLElement */
#ifndef TOLUA_DISABLE_tolua_Resource_XMLElement_GetUInt00
static int tolua_Resource_XMLElement_GetUInt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const XMLElement",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const XMLElement* self = (const XMLElement*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetUInt'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetUInt(name);
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

/* method: GetInt of class  XMLElement */
#ifndef TOLUA_DISABLE_tolua_Resource_XMLElement_GetInt00
static int tolua_Resource_XMLElement_GetInt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const XMLElement",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const XMLElement* self = (const XMLElement*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetInt'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetInt(name);
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

/* method: GetIntRect of class  XMLElement */
#ifndef TOLUA_DISABLE_tolua_Resource_XMLElement_GetIntRect00
static int tolua_Resource_XMLElement_GetIntRect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const XMLElement",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const XMLElement* self = (const XMLElement*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetIntRect'", NULL);
#endif
  {
   IntRect tolua_ret = (IntRect)  self->GetIntRect(name);
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
 tolua_error(tolua_S,"#ferror in function 'GetIntRect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetIntVector2 of class  XMLElement */
#ifndef TOLUA_DISABLE_tolua_Resource_XMLElement_GetIntVector200
static int tolua_Resource_XMLElement_GetIntVector200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const XMLElement",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const XMLElement* self = (const XMLElement*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetIntVector2'", NULL);
#endif
  {
   IntVector2 tolua_ret = (IntVector2)  self->GetIntVector2(name);
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
 tolua_error(tolua_S,"#ferror in function 'GetIntVector2'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRect of class  XMLElement */
#ifndef TOLUA_DISABLE_tolua_Resource_XMLElement_GetRect00
static int tolua_Resource_XMLElement_GetRect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const XMLElement",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const XMLElement* self = (const XMLElement*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRect'", NULL);
#endif
  {
   Rect tolua_ret = (Rect)  self->GetRect(name);
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
 tolua_error(tolua_S,"#ferror in function 'GetRect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetQuaternion of class  XMLElement */
#ifndef TOLUA_DISABLE_tolua_Resource_XMLElement_GetQuaternion00
static int tolua_Resource_XMLElement_GetQuaternion00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const XMLElement",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const XMLElement* self = (const XMLElement*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetQuaternion'", NULL);
#endif
  {
   Quaternion tolua_ret = (Quaternion)  self->GetQuaternion(name);
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
 tolua_error(tolua_S,"#ferror in function 'GetQuaternion'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetResourceRef of class  XMLElement */
#ifndef TOLUA_DISABLE_tolua_Resource_XMLElement_GetResourceRef00
static int tolua_Resource_XMLElement_GetResourceRef00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const XMLElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const XMLElement* self = (const XMLElement*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetResourceRef'", NULL);
#endif
  {
   ResourceRef tolua_ret = (ResourceRef)  self->GetResourceRef();
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
 tolua_error(tolua_S,"#ferror in function 'GetResourceRef'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetResourceRefList of class  XMLElement */
#ifndef TOLUA_DISABLE_tolua_Resource_XMLElement_GetResourceRefList00
static int tolua_Resource_XMLElement_GetResourceRefList00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const XMLElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const XMLElement* self = (const XMLElement*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetResourceRefList'", NULL);
#endif
  {
   ResourceRefList tolua_ret = (ResourceRefList)  self->GetResourceRefList();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((ResourceRefList)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"ResourceRefList");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(ResourceRefList));
     tolua_pushusertype(tolua_S,tolua_obj,"ResourceRefList");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
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

/* method: GetVector2 of class  XMLElement */
#ifndef TOLUA_DISABLE_tolua_Resource_XMLElement_GetVector200
static int tolua_Resource_XMLElement_GetVector200(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const XMLElement",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const XMLElement* self = (const XMLElement*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetVector2'", NULL);
#endif
  {
   Vector2 tolua_ret = (Vector2)  self->GetVector2(name);
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
 tolua_error(tolua_S,"#ferror in function 'GetVector2'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetVector3 of class  XMLElement */
#ifndef TOLUA_DISABLE_tolua_Resource_XMLElement_GetVector300
static int tolua_Resource_XMLElement_GetVector300(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const XMLElement",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const XMLElement* self = (const XMLElement*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetVector3'", NULL);
#endif
  {
   Vector3 tolua_ret = (Vector3)  self->GetVector3(name);
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
 tolua_error(tolua_S,"#ferror in function 'GetVector3'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetVector4 of class  XMLElement */
#ifndef TOLUA_DISABLE_tolua_Resource_XMLElement_GetVector400
static int tolua_Resource_XMLElement_GetVector400(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const XMLElement",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const XMLElement* self = (const XMLElement*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetVector4'", NULL);
#endif
  {
   Vector4 tolua_ret = (Vector4)  self->GetVector4(name);
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
 tolua_error(tolua_S,"#ferror in function 'GetVector4'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetVector of class  XMLElement */
#ifndef TOLUA_DISABLE_tolua_Resource_XMLElement_GetVector00
static int tolua_Resource_XMLElement_GetVector00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const XMLElement",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const XMLElement* self = (const XMLElement*)  tolua_tousertype(tolua_S,1,0);
  const char* name = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetVector'", NULL);
#endif
  {
   Vector4 tolua_ret = (Vector4)  self->GetVector(name);
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
 tolua_error(tolua_S,"#ferror in function 'GetVector'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFile of class  XMLElement */
#ifndef TOLUA_DISABLE_tolua_Resource_XMLElement_GetFile00
static int tolua_Resource_XMLElement_GetFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const XMLElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const XMLElement* self = (const XMLElement*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFile'", NULL);
#endif
  {
   XMLFile* tolua_ret = (XMLFile*)  self->GetFile();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"XMLFile");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: EMPTY of class  XMLElement */
#ifndef TOLUA_DISABLE_tolua_get_XMLElement_EMPTY
static int tolua_get_XMLElement_EMPTY(lua_State* tolua_S)
{
   tolua_pushusertype(tolua_S,(void*)&XMLElement::EMPTY,"const XMLElement");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRoot of class  XMLFile */
#ifndef TOLUA_DISABLE_tolua_Resource_XMLFile_GetRoot00
static int tolua_Resource_XMLFile_GetRoot00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"XMLFile",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  XMLFile* self = (XMLFile*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRoot'", NULL);
#endif
  {
   XMLElement tolua_ret = (XMLElement)  self->GetRoot();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((XMLElement)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"XMLElement");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(XMLElement));
     tolua_pushusertype(tolua_S,tolua_obj,"XMLElement");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRoot'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRoot of class  XMLFile */
#ifndef TOLUA_DISABLE_tolua_Resource_XMLFile_GetRoot01
static int tolua_Resource_XMLFile_GetRoot01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"XMLFile",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  XMLFile* self = (XMLFile*)  tolua_tousertype(tolua_S,1,0);
  const String* name = ((const String*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRoot'", NULL);
#endif
  {
   XMLElement tolua_ret = (XMLElement)  self->GetRoot(*name);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((XMLElement)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"XMLElement");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(XMLElement));
     tolua_pushusertype(tolua_S,tolua_obj,"XMLElement");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_Resource_XMLFile_GetRoot00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_Resource_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_constant(tolua_S,"CF_NONE",CF_NONE);
  tolua_constant(tolua_S,"CF_DXT1",CF_DXT1);
  tolua_constant(tolua_S,"CF_DXT3",CF_DXT3);
  tolua_constant(tolua_S,"CF_DXT5",CF_DXT5);
  tolua_constant(tolua_S,"CF_ETC1",CF_ETC1);
  tolua_constant(tolua_S,"CF_PVRTC_RGB_2BPP",CF_PVRTC_RGB_2BPP);
  tolua_constant(tolua_S,"CF_PVRTC_RGBA_2BPP",CF_PVRTC_RGBA_2BPP);
  tolua_constant(tolua_S,"CF_PVRTC_RGB_4BPP",CF_PVRTC_RGB_4BPP);
  tolua_constant(tolua_S,"CF_PVRTC_RGBA_4BPP",CF_PVRTC_RGBA_4BPP);
  tolua_cclass(tolua_S,"Image","Image","Resource",NULL);
  tolua_beginmodule(tolua_S,"Image");
   tolua_function(tolua_S,"FlipVertical",tolua_Resource_Image_FlipVertical00);
   tolua_function(tolua_S,"SaveBMP",tolua_Resource_Image_SaveBMP00);
   tolua_function(tolua_S,"SavePNG",tolua_Resource_Image_SavePNG00);
   tolua_function(tolua_S,"SaveTGA",tolua_Resource_Image_SaveTGA00);
   tolua_function(tolua_S,"SaveJPG",tolua_Resource_Image_SaveJPG00);
   tolua_function(tolua_S,"GetWidth",tolua_Resource_Image_GetWidth00);
   tolua_function(tolua_S,"GetHeight",tolua_Resource_Image_GetHeight00);
   tolua_function(tolua_S,"GetComponents",tolua_Resource_Image_GetComponents00);
   tolua_function(tolua_S,"IsCompressed",tolua_Resource_Image_IsCompressed00);
   tolua_function(tolua_S,"GetCompressedFormat",tolua_Resource_Image_GetCompressedFormat00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Resource","Resource","",NULL);
  tolua_beginmodule(tolua_S,"Resource");
   tolua_function(tolua_S,"SetName",tolua_Resource_Resource_SetName00);
   tolua_function(tolua_S,"GetName",tolua_Resource_Resource_GetName00);
   tolua_function(tolua_S,"GetNameHash",tolua_Resource_Resource_GetNameHash00);
   tolua_function(tolua_S,"GetMemoryUse",tolua_Resource_Resource_GetMemoryUse00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"ResourceCache","ResourceCache","",NULL);
  tolua_beginmodule(tolua_S,"ResourceCache");
   tolua_function(tolua_S,"ReleaseAllResources",tolua_Resource_ResourceCache_ReleaseAllResources00);
   tolua_function(tolua_S,"ReloadResource",tolua_Resource_ResourceCache_ReloadResource00);
   tolua_function(tolua_S,"SetMemoryBudget",tolua_Resource_ResourceCache_SetMemoryBudget00);
   tolua_function(tolua_S,"SetAutoReloadResources",tolua_Resource_ResourceCache_SetAutoReloadResources00);
   tolua_function(tolua_S,"Exists",tolua_Resource_ResourceCache_Exists00);
   tolua_function(tolua_S,"Exists",tolua_Resource_ResourceCache_Exists01);
   tolua_function(tolua_S,"GetMemoryBudget",tolua_Resource_ResourceCache_GetMemoryBudget00);
   tolua_function(tolua_S,"GetMemoryUse",tolua_Resource_ResourceCache_GetMemoryUse00);
   tolua_function(tolua_S,"GetTotalMemoryUse",tolua_Resource_ResourceCache_GetTotalMemoryUse00);
   tolua_function(tolua_S,"GetResourceName",tolua_Resource_ResourceCache_GetResourceName00);
   tolua_function(tolua_S,"GetResourceFileName",tolua_Resource_ResourceCache_GetResourceFileName00);
   tolua_function(tolua_S,"GetAutoReloadResources",tolua_Resource_ResourceCache_GetAutoReloadResources00);
   tolua_function(tolua_S,"GetAnimation",tolua_Resource_ResourceCache_GetAnimation00);
   tolua_function(tolua_S,"GetFont",tolua_Resource_ResourceCache_GetFont00);
   tolua_function(tolua_S,"GetImage",tolua_Resource_ResourceCache_GetImage00);
   tolua_function(tolua_S,"GetMaterial",tolua_Resource_ResourceCache_GetMaterial00);
   tolua_function(tolua_S,"GetModel",tolua_Resource_ResourceCache_GetModel00);
   tolua_function(tolua_S,"GetSound",tolua_Resource_ResourceCache_GetSound00);
   tolua_function(tolua_S,"GetTechnique",tolua_Resource_ResourceCache_GetTechnique00);
   tolua_function(tolua_S,"GetTexture2D",tolua_Resource_ResourceCache_GetTexture2D00);
   tolua_function(tolua_S,"GetTextureCube",tolua_Resource_ResourceCache_GetTextureCube00);
   tolua_function(tolua_S,"GetXMLFile",tolua_Resource_ResourceCache_GetXMLFile00);
  tolua_endmodule(tolua_S);
  tolua_function(tolua_S,"GetCache",tolua_Resource_GetCache00);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"XMLElement","XMLElement","",tolua_collect_XMLElement);
  #else
  tolua_cclass(tolua_S,"XMLElement","XMLElement","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"XMLElement");
   tolua_function(tolua_S,"IsNull",tolua_Resource_XMLElement_IsNull00);
   tolua_function(tolua_S,"NotNull",tolua_Resource_XMLElement_NotNull00);
   tolua_function(tolua_S,".bool",tolua_Resource_XMLElement__bool00);
   tolua_function(tolua_S,"GetName",tolua_Resource_XMLElement_GetName00);
   tolua_function(tolua_S,"HasChild",tolua_Resource_XMLElement_HasChild00);
   tolua_function(tolua_S,"HasChild",tolua_Resource_XMLElement_HasChild01);
   tolua_function(tolua_S,"GetChild",tolua_Resource_XMLElement_GetChild00);
   tolua_function(tolua_S,"GetChild",tolua_Resource_XMLElement_GetChild01);
   tolua_function(tolua_S,"GetNext",tolua_Resource_XMLElement_GetNext00);
   tolua_function(tolua_S,"GetNext",tolua_Resource_XMLElement_GetNext01);
   tolua_function(tolua_S,"GetParent",tolua_Resource_XMLElement_GetParent00);
   tolua_function(tolua_S,"GetNumAttributes",tolua_Resource_XMLElement_GetNumAttributes00);
   tolua_function(tolua_S,"HasAttribute",tolua_Resource_XMLElement_HasAttribute00);
   tolua_function(tolua_S,"HasAttribute",tolua_Resource_XMLElement_HasAttribute01);
   tolua_function(tolua_S,"GetBool",tolua_Resource_XMLElement_GetBool00);
   tolua_function(tolua_S,"GetBoundingBox",tolua_Resource_XMLElement_GetBoundingBox00);
   tolua_function(tolua_S,"GetColor",tolua_Resource_XMLElement_GetColor00);
   tolua_function(tolua_S,"GetFloat",tolua_Resource_XMLElement_GetFloat00);
   tolua_function(tolua_S,"GetUInt",tolua_Resource_XMLElement_GetUInt00);
   tolua_function(tolua_S,"GetInt",tolua_Resource_XMLElement_GetInt00);
   tolua_function(tolua_S,"GetIntRect",tolua_Resource_XMLElement_GetIntRect00);
   tolua_function(tolua_S,"GetIntVector2",tolua_Resource_XMLElement_GetIntVector200);
   tolua_function(tolua_S,"GetRect",tolua_Resource_XMLElement_GetRect00);
   tolua_function(tolua_S,"GetQuaternion",tolua_Resource_XMLElement_GetQuaternion00);
   tolua_function(tolua_S,"GetResourceRef",tolua_Resource_XMLElement_GetResourceRef00);
   tolua_function(tolua_S,"GetResourceRefList",tolua_Resource_XMLElement_GetResourceRefList00);
   tolua_function(tolua_S,"GetVector2",tolua_Resource_XMLElement_GetVector200);
   tolua_function(tolua_S,"GetVector3",tolua_Resource_XMLElement_GetVector300);
   tolua_function(tolua_S,"GetVector4",tolua_Resource_XMLElement_GetVector400);
   tolua_function(tolua_S,"GetVector",tolua_Resource_XMLElement_GetVector00);
   tolua_function(tolua_S,"GetFile",tolua_Resource_XMLElement_GetFile00);
   tolua_variable(tolua_S,"EMPTY",tolua_get_XMLElement_EMPTY,NULL);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"XMLFile","XMLFile","Resource",NULL);
  tolua_beginmodule(tolua_S,"XMLFile");
   tolua_function(tolua_S,"GetRoot",tolua_Resource_XMLFile_GetRoot00);
   tolua_function(tolua_S,"GetRoot",tolua_Resource_XMLFile_GetRoot01);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_Resource (lua_State* tolua_S) {
 return tolua_Resource_open(tolua_S);
};
#endif

