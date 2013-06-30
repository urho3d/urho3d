/*
** Lua binding: UI
** Generated automatically by tolua++-1.0.92 on 06/30/13 11:31:52.
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
TOLUA_API int  tolua_UI_open (lua_State* tolua_S);

#define TOLUA_RELEASE
#include "UILuaAPI.h"
#include "BorderImage.h"
#include "Button.h"
#include "CheckBox.h"
#include "Cursor.h"
#include "DropDownList.h"
#include "FileSelector.h"
#include "Font.h"
#include "LineEdit.h"
#include "ListView.h"
#include "Menu.h"
#include "ScrollBar.h"
#include "ScrollView.h"
#include "Slider.h"
#include "Sprite.h"
#include "Text.h"
#include "Text3D.h"
#include "UI.h"
#include "UIElement.h"
#include "Window.h"
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

static int tolua_collect_IntRect (lua_State* tolua_S)
{
 IntRect* self = (IntRect*) tolua_tousertype(tolua_S,1,0);
  Mtolua_delete(self);
  return 0;
}

static int tolua_collect_ResourceRef (lua_State* tolua_S)
{
 ResourceRef* self = (ResourceRef*) tolua_tousertype(tolua_S,1,0);
  Mtolua_delete(self);
  return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"Matrix3x4");
 tolua_usertype(tolua_S,"FileSelector");
 tolua_usertype(tolua_S,"Vector<String>");
 tolua_usertype(tolua_S,"FileSelectorEntry");
 tolua_usertype(tolua_S,"ListView");
 tolua_usertype(tolua_S,"Texture");
 tolua_usertype(tolua_S,"IntRect");
 tolua_usertype(tolua_S,"CheckBox");
 tolua_usertype(tolua_S,"Sprite");
 tolua_usertype(tolua_S,"Object");
 tolua_usertype(tolua_S,"ScrollBar");
 tolua_usertype(tolua_S,"IntVector2");
 tolua_usertype(tolua_S,"String");
 tolua_usertype(tolua_S,"Resource");
 tolua_usertype(tolua_S,"PODVector<float>");
 tolua_usertype(tolua_S,"Color");
 tolua_usertype(tolua_S,"Window");
 tolua_usertype(tolua_S,"Cursor");
 tolua_usertype(tolua_S,"PODVector<UIBatch>");
 tolua_usertype(tolua_S,"Variant");
 tolua_usertype(tolua_S,"Image");
 tolua_usertype(tolua_S,"Drawable");
 tolua_usertype(tolua_S,"ShortStringHash");
 tolua_usertype(tolua_S,"Button");
 tolua_usertype(tolua_S,"Material");
 tolua_usertype(tolua_S,"XMLElement");
 tolua_usertype(tolua_S,"ScrollView");
 tolua_usertype(tolua_S,"Slider");
 tolua_usertype(tolua_S,"UIElement");
 tolua_usertype(tolua_S,"Serializer");
 tolua_usertype(tolua_S,"UI");
 tolua_usertype(tolua_S,"PODVector<int>");
 tolua_usertype(tolua_S,"Text");
 tolua_usertype(tolua_S,"XMLFile");
 tolua_usertype(tolua_S,"Text3D");
 tolua_usertype(tolua_S,"ResourceRef");
 tolua_usertype(tolua_S,"Font");
 tolua_usertype(tolua_S,"Vector2");
 tolua_usertype(tolua_S,"DropDownList");
 tolua_usertype(tolua_S,"LineEdit");
 tolua_usertype(tolua_S,"Serializable");
 tolua_usertype(tolua_S,"Menu");
 tolua_usertype(tolua_S,"BorderImage");
}

/* method: SetTexture of class  BorderImage */
#ifndef TOLUA_DISABLE_tolua_UI_BorderImage_SetTexture00
static int tolua_UI_BorderImage_SetTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BorderImage",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Texture",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BorderImage* self = (BorderImage*)  tolua_tousertype(tolua_S,1,0);
  Texture* texture = ((Texture*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetTexture'", NULL);
#endif
  {
   self->SetTexture(texture);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetImageRect of class  BorderImage */
#ifndef TOLUA_DISABLE_tolua_UI_BorderImage_SetImageRect00
static int tolua_UI_BorderImage_SetImageRect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BorderImage",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const IntRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BorderImage* self = (BorderImage*)  tolua_tousertype(tolua_S,1,0);
  const IntRect* rect = ((const IntRect*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetImageRect'", NULL);
#endif
  {
   self->SetImageRect(*rect);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetImageRect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFullImageRect of class  BorderImage */
#ifndef TOLUA_DISABLE_tolua_UI_BorderImage_SetFullImageRect00
static int tolua_UI_BorderImage_SetFullImageRect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BorderImage",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BorderImage* self = (BorderImage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFullImageRect'", NULL);
#endif
  {
   self->SetFullImageRect();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFullImageRect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetBorder of class  BorderImage */
#ifndef TOLUA_DISABLE_tolua_UI_BorderImage_SetBorder00
static int tolua_UI_BorderImage_SetBorder00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BorderImage",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const IntRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BorderImage* self = (BorderImage*)  tolua_tousertype(tolua_S,1,0);
  const IntRect* rect = ((const IntRect*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetBorder'", NULL);
#endif
  {
   self->SetBorder(*rect);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetBorder'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetHoverOffset of class  BorderImage */
#ifndef TOLUA_DISABLE_tolua_UI_BorderImage_SetHoverOffset00
static int tolua_UI_BorderImage_SetHoverOffset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BorderImage",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const IntVector2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BorderImage* self = (BorderImage*)  tolua_tousertype(tolua_S,1,0);
  const IntVector2* offset = ((const IntVector2*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetHoverOffset'", NULL);
#endif
  {
   self->SetHoverOffset(*offset);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetHoverOffset'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetHoverOffset of class  BorderImage */
#ifndef TOLUA_DISABLE_tolua_UI_BorderImage_SetHoverOffset01
static int tolua_UI_BorderImage_SetHoverOffset01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BorderImage",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  BorderImage* self = (BorderImage*)  tolua_tousertype(tolua_S,1,0);
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetHoverOffset'", NULL);
#endif
  {
   self->SetHoverOffset(x,y);
  }
 }
 return 0;
tolua_lerror:
 return tolua_UI_BorderImage_SetHoverOffset00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetBlendMode of class  BorderImage */
#ifndef TOLUA_DISABLE_tolua_UI_BorderImage_SetBlendMode00
static int tolua_UI_BorderImage_SetBlendMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BorderImage",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BorderImage* self = (BorderImage*)  tolua_tousertype(tolua_S,1,0);
  BlendMode mode = ((BlendMode) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetBlendMode'", NULL);
#endif
  {
   self->SetBlendMode(mode);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetBlendMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetTiled of class  BorderImage */
#ifndef TOLUA_DISABLE_tolua_UI_BorderImage_SetTiled00
static int tolua_UI_BorderImage_SetTiled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BorderImage",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BorderImage* self = (BorderImage*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetTiled'", NULL);
#endif
  {
   self->SetTiled(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetTiled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTexture of class  BorderImage */
#ifndef TOLUA_DISABLE_tolua_UI_BorderImage_GetTexture00
static int tolua_UI_BorderImage_GetTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const BorderImage",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const BorderImage* self = (const BorderImage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTexture'", NULL);
#endif
  {
   Texture* tolua_ret = (Texture*)  self->GetTexture();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Texture");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetImageRect of class  BorderImage */
#ifndef TOLUA_DISABLE_tolua_UI_BorderImage_GetImageRect00
static int tolua_UI_BorderImage_GetImageRect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const BorderImage",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const BorderImage* self = (const BorderImage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetImageRect'", NULL);
#endif
  {
   const IntRect& tolua_ret = (const IntRect&)  self->GetImageRect();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const IntRect");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetImageRect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetBorder of class  BorderImage */
#ifndef TOLUA_DISABLE_tolua_UI_BorderImage_GetBorder00
static int tolua_UI_BorderImage_GetBorder00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const BorderImage",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const BorderImage* self = (const BorderImage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetBorder'", NULL);
#endif
  {
   const IntRect& tolua_ret = (const IntRect&)  self->GetBorder();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const IntRect");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetBorder'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetHoverOffset of class  BorderImage */
#ifndef TOLUA_DISABLE_tolua_UI_BorderImage_GetHoverOffset00
static int tolua_UI_BorderImage_GetHoverOffset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const BorderImage",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const BorderImage* self = (const BorderImage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetHoverOffset'", NULL);
#endif
  {
   const IntVector2& tolua_ret = (const IntVector2&)  self->GetHoverOffset();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const IntVector2");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetHoverOffset'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetBlendMode of class  BorderImage */
#ifndef TOLUA_DISABLE_tolua_UI_BorderImage_GetBlendMode00
static int tolua_UI_BorderImage_GetBlendMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const BorderImage",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const BorderImage* self = (const BorderImage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetBlendMode'", NULL);
#endif
  {
   BlendMode tolua_ret = (BlendMode)  self->GetBlendMode();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetBlendMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsTiled of class  BorderImage */
#ifndef TOLUA_DISABLE_tolua_UI_BorderImage_IsTiled00
static int tolua_UI_BorderImage_IsTiled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const BorderImage",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const BorderImage* self = (const BorderImage*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsTiled'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsTiled();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsTiled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetPressedOffset of class  Button */
#ifndef TOLUA_DISABLE_tolua_UI_Button_SetPressedOffset00
static int tolua_UI_Button_SetPressedOffset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Button",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const IntVector2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Button* self = (Button*)  tolua_tousertype(tolua_S,1,0);
  const IntVector2* offset = ((const IntVector2*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetPressedOffset'", NULL);
#endif
  {
   self->SetPressedOffset(*offset);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetPressedOffset'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetPressedOffset of class  Button */
#ifndef TOLUA_DISABLE_tolua_UI_Button_SetPressedOffset01
static int tolua_UI_Button_SetPressedOffset01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Button",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Button* self = (Button*)  tolua_tousertype(tolua_S,1,0);
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetPressedOffset'", NULL);
#endif
  {
   self->SetPressedOffset(x,y);
  }
 }
 return 0;
tolua_lerror:
 return tolua_UI_Button_SetPressedOffset00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetLabelOffset of class  Button */
#ifndef TOLUA_DISABLE_tolua_UI_Button_SetLabelOffset00
static int tolua_UI_Button_SetLabelOffset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Button",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const IntVector2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Button* self = (Button*)  tolua_tousertype(tolua_S,1,0);
  const IntVector2* offset = ((const IntVector2*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLabelOffset'", NULL);
#endif
  {
   self->SetLabelOffset(*offset);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLabelOffset'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetLabelOffset of class  Button */
#ifndef TOLUA_DISABLE_tolua_UI_Button_SetLabelOffset01
static int tolua_UI_Button_SetLabelOffset01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Button",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Button* self = (Button*)  tolua_tousertype(tolua_S,1,0);
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLabelOffset'", NULL);
#endif
  {
   self->SetLabelOffset(x,y);
  }
 }
 return 0;
tolua_lerror:
 return tolua_UI_Button_SetLabelOffset00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetRepeat of class  Button */
#ifndef TOLUA_DISABLE_tolua_UI_Button_SetRepeat00
static int tolua_UI_Button_SetRepeat00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Button",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Button* self = (Button*)  tolua_tousertype(tolua_S,1,0);
  float delay = ((float)  tolua_tonumber(tolua_S,2,0));
  float rate = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetRepeat'", NULL);
#endif
  {
   self->SetRepeat(delay,rate);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetRepeat'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetRepeatDelay of class  Button */
#ifndef TOLUA_DISABLE_tolua_UI_Button_SetRepeatDelay00
static int tolua_UI_Button_SetRepeatDelay00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Button",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Button* self = (Button*)  tolua_tousertype(tolua_S,1,0);
  float delay = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetRepeatDelay'", NULL);
#endif
  {
   self->SetRepeatDelay(delay);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetRepeatDelay'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetRepeatRate of class  Button */
#ifndef TOLUA_DISABLE_tolua_UI_Button_SetRepeatRate00
static int tolua_UI_Button_SetRepeatRate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Button",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Button* self = (Button*)  tolua_tousertype(tolua_S,1,0);
  float rate = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetRepeatRate'", NULL);
#endif
  {
   self->SetRepeatRate(rate);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetRepeatRate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetPressedOffset of class  Button */
#ifndef TOLUA_DISABLE_tolua_UI_Button_GetPressedOffset00
static int tolua_UI_Button_GetPressedOffset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Button",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Button* self = (const Button*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPressedOffset'", NULL);
#endif
  {
   const IntVector2& tolua_ret = (const IntVector2&)  self->GetPressedOffset();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const IntVector2");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPressedOffset'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLabelOffset of class  Button */
#ifndef TOLUA_DISABLE_tolua_UI_Button_GetLabelOffset00
static int tolua_UI_Button_GetLabelOffset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Button",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Button* self = (const Button*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLabelOffset'", NULL);
#endif
  {
   const IntVector2& tolua_ret = (const IntVector2&)  self->GetLabelOffset();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const IntVector2");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLabelOffset'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRepeatDelay of class  Button */
#ifndef TOLUA_DISABLE_tolua_UI_Button_GetRepeatDelay00
static int tolua_UI_Button_GetRepeatDelay00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Button",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Button* self = (const Button*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRepeatDelay'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetRepeatDelay();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRepeatDelay'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRepeatRate of class  Button */
#ifndef TOLUA_DISABLE_tolua_UI_Button_GetRepeatRate00
static int tolua_UI_Button_GetRepeatRate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Button",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Button* self = (const Button*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRepeatRate'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetRepeatRate();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRepeatRate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetChecked of class  CheckBox */
#ifndef TOLUA_DISABLE_tolua_UI_CheckBox_SetChecked00
static int tolua_UI_CheckBox_SetChecked00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CheckBox",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CheckBox* self = (CheckBox*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetChecked'", NULL);
#endif
  {
   self->SetChecked(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetChecked'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetCheckedOffset of class  CheckBox */
#ifndef TOLUA_DISABLE_tolua_UI_CheckBox_SetCheckedOffset00
static int tolua_UI_CheckBox_SetCheckedOffset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CheckBox",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const IntVector2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  CheckBox* self = (CheckBox*)  tolua_tousertype(tolua_S,1,0);
  const IntVector2* rect = ((const IntVector2*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetCheckedOffset'", NULL);
#endif
  {
   self->SetCheckedOffset(*rect);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetCheckedOffset'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetCheckedOffset of class  CheckBox */
#ifndef TOLUA_DISABLE_tolua_UI_CheckBox_SetCheckedOffset01
static int tolua_UI_CheckBox_SetCheckedOffset01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"CheckBox",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  CheckBox* self = (CheckBox*)  tolua_tousertype(tolua_S,1,0);
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetCheckedOffset'", NULL);
#endif
  {
   self->SetCheckedOffset(x,y);
  }
 }
 return 0;
tolua_lerror:
 return tolua_UI_CheckBox_SetCheckedOffset00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsChecked of class  CheckBox */
#ifndef TOLUA_DISABLE_tolua_UI_CheckBox_IsChecked00
static int tolua_UI_CheckBox_IsChecked00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CheckBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CheckBox* self = (const CheckBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsChecked'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsChecked();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsChecked'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCheckedOffset of class  CheckBox */
#ifndef TOLUA_DISABLE_tolua_UI_CheckBox_GetCheckedOffset00
static int tolua_UI_CheckBox_GetCheckedOffset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const CheckBox",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const CheckBox* self = (const CheckBox*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCheckedOffset'", NULL);
#endif
  {
   const IntVector2& tolua_ret = (const IntVector2&)  self->GetCheckedOffset();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const IntVector2");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCheckedOffset'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DefineShape of class  Cursor */
#ifndef TOLUA_DISABLE_tolua_UI_Cursor_DefineShape00
static int tolua_UI_Cursor_DefineShape00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Cursor",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"Image",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"const IntRect",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"const IntVector2",0,&tolua_err)) ||
     !tolua_isboolean(tolua_S,6,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,7,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Cursor* self = (Cursor*)  tolua_tousertype(tolua_S,1,0);
  CursorShape shape = ((CursorShape) (int)  tolua_tonumber(tolua_S,2,0));
  Image* image = ((Image*)  tolua_tousertype(tolua_S,3,0));
  const IntRect* imageRect = ((const IntRect*)  tolua_tousertype(tolua_S,4,0));
  const IntVector2* hotSpot = ((const IntVector2*)  tolua_tousertype(tolua_S,5,0));
  bool osMouseVisible = ((bool)  tolua_toboolean(tolua_S,6,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DefineShape'", NULL);
#endif
  {
   self->DefineShape(shape,image,*imageRect,*hotSpot,osMouseVisible);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DefineShape'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetShape of class  Cursor */
#ifndef TOLUA_DISABLE_tolua_UI_Cursor_SetShape00
static int tolua_UI_Cursor_SetShape00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Cursor",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Cursor* self = (Cursor*)  tolua_tousertype(tolua_S,1,0);
  CursorShape shape = ((CursorShape) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetShape'", NULL);
#endif
  {
   self->SetShape(shape);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetShape'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetShape of class  Cursor */
#ifndef TOLUA_DISABLE_tolua_UI_Cursor_GetShape00
static int tolua_UI_Cursor_GetShape00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Cursor",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Cursor* self = (const Cursor*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetShape'", NULL);
#endif
  {
   CursorShape tolua_ret = (CursorShape)  self->GetShape();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetShape'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: NewCursor */
#ifndef TOLUA_DISABLE_tolua_UI_Cursor00
static int tolua_UI_Cursor00(lua_State* tolua_S)
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
   Cursor* tolua_ret = (Cursor*)  NewCursor();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Cursor");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Cursor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddItem of class  DropDownList */
#ifndef TOLUA_DISABLE_tolua_UI_DropDownList_AddItem00
static int tolua_UI_DropDownList_AddItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DropDownList",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DropDownList* self = (DropDownList*)  tolua_tousertype(tolua_S,1,0);
  UIElement* item = ((UIElement*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddItem'", NULL);
#endif
  {
   self->AddItem(item);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: InsertItem of class  DropDownList */
#ifndef TOLUA_DISABLE_tolua_UI_DropDownList_InsertItem00
static int tolua_UI_DropDownList_InsertItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DropDownList",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DropDownList* self = (DropDownList*)  tolua_tousertype(tolua_S,1,0);
  unsigned index = ((unsigned)  tolua_tonumber(tolua_S,2,0));
  UIElement* item = ((UIElement*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'InsertItem'", NULL);
#endif
  {
   self->InsertItem(index,item);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'InsertItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveItem of class  DropDownList */
#ifndef TOLUA_DISABLE_tolua_UI_DropDownList_RemoveItem00
static int tolua_UI_DropDownList_RemoveItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DropDownList",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DropDownList* self = (DropDownList*)  tolua_tousertype(tolua_S,1,0);
  UIElement* item = ((UIElement*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveItem'", NULL);
#endif
  {
   self->RemoveItem(item);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemoveItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveItem of class  DropDownList */
#ifndef TOLUA_DISABLE_tolua_UI_DropDownList_RemoveItem01
static int tolua_UI_DropDownList_RemoveItem01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DropDownList",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  DropDownList* self = (DropDownList*)  tolua_tousertype(tolua_S,1,0);
  unsigned index = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveItem'", NULL);
#endif
  {
   self->RemoveItem(index);
  }
 }
 return 0;
tolua_lerror:
 return tolua_UI_DropDownList_RemoveItem00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveAllItems of class  DropDownList */
#ifndef TOLUA_DISABLE_tolua_UI_DropDownList_RemoveAllItems00
static int tolua_UI_DropDownList_RemoveAllItems00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DropDownList",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DropDownList* self = (DropDownList*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveAllItems'", NULL);
#endif
  {
   self->RemoveAllItems();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemoveAllItems'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetSelection of class  DropDownList */
#ifndef TOLUA_DISABLE_tolua_UI_DropDownList_SetSelection00
static int tolua_UI_DropDownList_SetSelection00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DropDownList",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DropDownList* self = (DropDownList*)  tolua_tousertype(tolua_S,1,0);
  unsigned index = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetSelection'", NULL);
#endif
  {
   self->SetSelection(index);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetSelection'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetPlaceholderText of class  DropDownList */
#ifndef TOLUA_DISABLE_tolua_UI_DropDownList_SetPlaceholderText00
static int tolua_UI_DropDownList_SetPlaceholderText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DropDownList",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DropDownList* self = (DropDownList*)  tolua_tousertype(tolua_S,1,0);
  const String* text = ((const String*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetPlaceholderText'", NULL);
#endif
  {
   self->SetPlaceholderText(*text);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetPlaceholderText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetResizePopup of class  DropDownList */
#ifndef TOLUA_DISABLE_tolua_UI_DropDownList_SetResizePopup00
static int tolua_UI_DropDownList_SetResizePopup00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DropDownList",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DropDownList* self = (DropDownList*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetResizePopup'", NULL);
#endif
  {
   self->SetResizePopup(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetResizePopup'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNumItems of class  DropDownList */
#ifndef TOLUA_DISABLE_tolua_UI_DropDownList_GetNumItems00
static int tolua_UI_DropDownList_GetNumItems00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const DropDownList",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const DropDownList* self = (const DropDownList*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNumItems'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetNumItems();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNumItems'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetItem of class  DropDownList */
#ifndef TOLUA_DISABLE_tolua_UI_DropDownList_GetItem00
static int tolua_UI_DropDownList_GetItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const DropDownList",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const DropDownList* self = (const DropDownList*)  tolua_tousertype(tolua_S,1,0);
  unsigned index = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetItem'", NULL);
#endif
  {
   UIElement* tolua_ret = (UIElement*)  self->GetItem(index);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIElement");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSelection of class  DropDownList */
#ifndef TOLUA_DISABLE_tolua_UI_DropDownList_GetSelection00
static int tolua_UI_DropDownList_GetSelection00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const DropDownList",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const DropDownList* self = (const DropDownList*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSelection'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetSelection();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSelection'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSelectedItem of class  DropDownList */
#ifndef TOLUA_DISABLE_tolua_UI_DropDownList_GetSelectedItem00
static int tolua_UI_DropDownList_GetSelectedItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const DropDownList",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const DropDownList* self = (const DropDownList*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSelectedItem'", NULL);
#endif
  {
   UIElement* tolua_ret = (UIElement*)  self->GetSelectedItem();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIElement");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSelectedItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetListView of class  DropDownList */
#ifndef TOLUA_DISABLE_tolua_UI_DropDownList_GetListView00
static int tolua_UI_DropDownList_GetListView00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const DropDownList",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const DropDownList* self = (const DropDownList*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetListView'", NULL);
#endif
  {
   ListView* tolua_ret = (ListView*)  self->GetListView();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ListView");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetListView'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetPlaceholder of class  DropDownList */
#ifndef TOLUA_DISABLE_tolua_UI_DropDownList_GetPlaceholder00
static int tolua_UI_DropDownList_GetPlaceholder00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const DropDownList",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const DropDownList* self = (const DropDownList*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPlaceholder'", NULL);
#endif
  {
   UIElement* tolua_ret = (UIElement*)  self->GetPlaceholder();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIElement");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPlaceholder'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetPlaceholderText of class  DropDownList */
#ifndef TOLUA_DISABLE_tolua_UI_DropDownList_GetPlaceholderText00
static int tolua_UI_DropDownList_GetPlaceholderText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const DropDownList",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const DropDownList* self = (const DropDownList*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPlaceholderText'", NULL);
#endif
  {
   const String& tolua_ret = (const String&)  self->GetPlaceholderText();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const String");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPlaceholderText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetResizePopup of class  DropDownList */
#ifndef TOLUA_DISABLE_tolua_UI_DropDownList_GetResizePopup00
static int tolua_UI_DropDownList_GetResizePopup00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const DropDownList",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const DropDownList* self = (const DropDownList*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetResizePopup'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetResizePopup();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetResizePopup'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: name_ of class  FileSelectorEntry */
#ifndef TOLUA_DISABLE_tolua_get_FileSelectorEntry_name_
static int tolua_get_FileSelectorEntry_name_(lua_State* tolua_S)
{
  FileSelectorEntry* self = (FileSelectorEntry*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'name_'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->name_,"String");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: name_ of class  FileSelectorEntry */
#ifndef TOLUA_DISABLE_tolua_set_FileSelectorEntry_name_
static int tolua_set_FileSelectorEntry_name_(lua_State* tolua_S)
{
  FileSelectorEntry* self = (FileSelectorEntry*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'name_'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"String",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->name_ = *((String*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: directory_ of class  FileSelectorEntry */
#ifndef TOLUA_DISABLE_tolua_get_FileSelectorEntry_directory_
static int tolua_get_FileSelectorEntry_directory_(lua_State* tolua_S)
{
  FileSelectorEntry* self = (FileSelectorEntry*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'directory_'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->directory_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: directory_ of class  FileSelectorEntry */
#ifndef TOLUA_DISABLE_tolua_set_FileSelectorEntry_directory_
static int tolua_set_FileSelectorEntry_directory_(lua_State* tolua_S)
{
  FileSelectorEntry* self = (FileSelectorEntry*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'directory_'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->directory_ = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetDefaultStyle of class  FileSelector */
#ifndef TOLUA_DISABLE_tolua_UI_FileSelector_SetDefaultStyle00
static int tolua_UI_FileSelector_SetDefaultStyle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"FileSelector",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"XMLFile",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  FileSelector* self = (FileSelector*)  tolua_tousertype(tolua_S,1,0);
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

/* method: SetTitle of class  FileSelector */
#ifndef TOLUA_DISABLE_tolua_UI_FileSelector_SetTitle00
static int tolua_UI_FileSelector_SetTitle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"FileSelector",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  FileSelector* self = (FileSelector*)  tolua_tousertype(tolua_S,1,0);
  const String* text = ((const String*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetTitle'", NULL);
#endif
  {
   self->SetTitle(*text);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetTitle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetButtonTexts of class  FileSelector */
#ifndef TOLUA_DISABLE_tolua_UI_FileSelector_SetButtonTexts00
static int tolua_UI_FileSelector_SetButtonTexts00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"FileSelector",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  FileSelector* self = (FileSelector*)  tolua_tousertype(tolua_S,1,0);
  const String* okText = ((const String*)  tolua_tousertype(tolua_S,2,0));
  const String* cancelText = ((const String*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetButtonTexts'", NULL);
#endif
  {
   self->SetButtonTexts(*okText,*cancelText);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetButtonTexts'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetPath of class  FileSelector */
#ifndef TOLUA_DISABLE_tolua_UI_FileSelector_SetPath00
static int tolua_UI_FileSelector_SetPath00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"FileSelector",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  FileSelector* self = (FileSelector*)  tolua_tousertype(tolua_S,1,0);
  const String* path = ((const String*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetPath'", NULL);
#endif
  {
   self->SetPath(*path);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetPath'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFileName of class  FileSelector */
#ifndef TOLUA_DISABLE_tolua_UI_FileSelector_SetFileName00
static int tolua_UI_FileSelector_SetFileName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"FileSelector",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  FileSelector* self = (FileSelector*)  tolua_tousertype(tolua_S,1,0);
  const String* fileName = ((const String*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFileName'", NULL);
#endif
  {
   self->SetFileName(*fileName);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFileName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFilters of class  FileSelector */
#ifndef TOLUA_DISABLE_tolua_UI_FileSelector_SetFilters00
static int tolua_UI_FileSelector_SetFilters00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"FileSelector",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector<String>",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  FileSelector* self = (FileSelector*)  tolua_tousertype(tolua_S,1,0);
  const Vector<String>* filters = ((const Vector<String>*)  tolua_tousertype(tolua_S,2,0));
  unsigned defaultIndex = ((unsigned)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFilters'", NULL);
#endif
  {
   self->SetFilters(*filters,defaultIndex);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFilters'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetDirectoryMode of class  FileSelector */
#ifndef TOLUA_DISABLE_tolua_UI_FileSelector_SetDirectoryMode00
static int tolua_UI_FileSelector_SetDirectoryMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"FileSelector",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  FileSelector* self = (FileSelector*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetDirectoryMode'", NULL);
#endif
  {
   self->SetDirectoryMode(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetDirectoryMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: UpdateElements of class  FileSelector */
#ifndef TOLUA_DISABLE_tolua_UI_FileSelector_UpdateElements00
static int tolua_UI_FileSelector_UpdateElements00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"FileSelector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  FileSelector* self = (FileSelector*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetDefaultStyle of class  FileSelector */
#ifndef TOLUA_DISABLE_tolua_UI_FileSelector_GetDefaultStyle00
static int tolua_UI_FileSelector_GetDefaultStyle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const FileSelector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const FileSelector* self = (const FileSelector*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetWindow of class  FileSelector */
#ifndef TOLUA_DISABLE_tolua_UI_FileSelector_GetWindow00
static int tolua_UI_FileSelector_GetWindow00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const FileSelector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const FileSelector* self = (const FileSelector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetWindow'", NULL);
#endif
  {
   Window* tolua_ret = (Window*)  self->GetWindow();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Window");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetWindow'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTitleText of class  FileSelector */
#ifndef TOLUA_DISABLE_tolua_UI_FileSelector_GetTitleText00
static int tolua_UI_FileSelector_GetTitleText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const FileSelector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const FileSelector* self = (const FileSelector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTitleText'", NULL);
#endif
  {
   Text* tolua_ret = (Text*)  self->GetTitleText();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Text");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTitleText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFileList of class  FileSelector */
#ifndef TOLUA_DISABLE_tolua_UI_FileSelector_GetFileList00
static int tolua_UI_FileSelector_GetFileList00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const FileSelector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const FileSelector* self = (const FileSelector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFileList'", NULL);
#endif
  {
   ListView* tolua_ret = (ListView*)  self->GetFileList();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ListView");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFileList'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetPathEdit of class  FileSelector */
#ifndef TOLUA_DISABLE_tolua_UI_FileSelector_GetPathEdit00
static int tolua_UI_FileSelector_GetPathEdit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const FileSelector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const FileSelector* self = (const FileSelector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPathEdit'", NULL);
#endif
  {
   LineEdit* tolua_ret = (LineEdit*)  self->GetPathEdit();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"LineEdit");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPathEdit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFileNameEdit of class  FileSelector */
#ifndef TOLUA_DISABLE_tolua_UI_FileSelector_GetFileNameEdit00
static int tolua_UI_FileSelector_GetFileNameEdit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const FileSelector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const FileSelector* self = (const FileSelector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFileNameEdit'", NULL);
#endif
  {
   LineEdit* tolua_ret = (LineEdit*)  self->GetFileNameEdit();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"LineEdit");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFileNameEdit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFilterList of class  FileSelector */
#ifndef TOLUA_DISABLE_tolua_UI_FileSelector_GetFilterList00
static int tolua_UI_FileSelector_GetFilterList00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const FileSelector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const FileSelector* self = (const FileSelector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFilterList'", NULL);
#endif
  {
   DropDownList* tolua_ret = (DropDownList*)  self->GetFilterList();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DropDownList");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFilterList'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetOKButton of class  FileSelector */
#ifndef TOLUA_DISABLE_tolua_UI_FileSelector_GetOKButton00
static int tolua_UI_FileSelector_GetOKButton00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const FileSelector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const FileSelector* self = (const FileSelector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetOKButton'", NULL);
#endif
  {
   Button* tolua_ret = (Button*)  self->GetOKButton();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Button");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetOKButton'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCancelButton of class  FileSelector */
#ifndef TOLUA_DISABLE_tolua_UI_FileSelector_GetCancelButton00
static int tolua_UI_FileSelector_GetCancelButton00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const FileSelector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const FileSelector* self = (const FileSelector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCancelButton'", NULL);
#endif
  {
   Button* tolua_ret = (Button*)  self->GetCancelButton();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Button");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCancelButton'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCloseButton of class  FileSelector */
#ifndef TOLUA_DISABLE_tolua_UI_FileSelector_GetCloseButton00
static int tolua_UI_FileSelector_GetCloseButton00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const FileSelector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const FileSelector* self = (const FileSelector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCloseButton'", NULL);
#endif
  {
   Button* tolua_ret = (Button*)  self->GetCloseButton();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Button");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCloseButton'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTitle of class  FileSelector */
#ifndef TOLUA_DISABLE_tolua_UI_FileSelector_GetTitle00
static int tolua_UI_FileSelector_GetTitle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const FileSelector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const FileSelector* self = (const FileSelector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTitle'", NULL);
#endif
  {
   const String& tolua_ret = (const String&)  self->GetTitle();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const String");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTitle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetPath of class  FileSelector */
#ifndef TOLUA_DISABLE_tolua_UI_FileSelector_GetPath00
static int tolua_UI_FileSelector_GetPath00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const FileSelector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const FileSelector* self = (const FileSelector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPath'", NULL);
#endif
  {
   const String& tolua_ret = (const String&)  self->GetPath();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const String");
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

/* method: GetFileName of class  FileSelector */
#ifndef TOLUA_DISABLE_tolua_UI_FileSelector_GetFileName00
static int tolua_UI_FileSelector_GetFileName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const FileSelector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const FileSelector* self = (const FileSelector*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetFilter of class  FileSelector */
#ifndef TOLUA_DISABLE_tolua_UI_FileSelector_GetFilter00
static int tolua_UI_FileSelector_GetFilter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const FileSelector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const FileSelector* self = (const FileSelector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFilter'", NULL);
#endif
  {
   const String& tolua_ret = (const String&)  self->GetFilter();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const String");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFilter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFilterIndex of class  FileSelector */
#ifndef TOLUA_DISABLE_tolua_UI_FileSelector_GetFilterIndex00
static int tolua_UI_FileSelector_GetFilterIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const FileSelector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const FileSelector* self = (const FileSelector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFilterIndex'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetFilterIndex();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFilterIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetDirectoryMode of class  FileSelector */
#ifndef TOLUA_DISABLE_tolua_UI_FileSelector_GetDirectoryMode00
static int tolua_UI_FileSelector_GetDirectoryMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const FileSelector",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const FileSelector* self = (const FileSelector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetDirectoryMode'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetDirectoryMode();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDirectoryMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetText of class  LineEdit */
#ifndef TOLUA_DISABLE_tolua_UI_LineEdit_SetText00
static int tolua_UI_LineEdit_SetText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LineEdit",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LineEdit* self = (LineEdit*)  tolua_tousertype(tolua_S,1,0);
  const String* text = ((const String*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetText'", NULL);
#endif
  {
   self->SetText(*text);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetCursorPosition of class  LineEdit */
#ifndef TOLUA_DISABLE_tolua_UI_LineEdit_SetCursorPosition00
static int tolua_UI_LineEdit_SetCursorPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LineEdit",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LineEdit* self = (LineEdit*)  tolua_tousertype(tolua_S,1,0);
  unsigned position = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetCursorPosition'", NULL);
#endif
  {
   self->SetCursorPosition(position);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetCursorPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetCursorBlinkRate of class  LineEdit */
#ifndef TOLUA_DISABLE_tolua_UI_LineEdit_SetCursorBlinkRate00
static int tolua_UI_LineEdit_SetCursorBlinkRate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LineEdit",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LineEdit* self = (LineEdit*)  tolua_tousertype(tolua_S,1,0);
  float rate = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetCursorBlinkRate'", NULL);
#endif
  {
   self->SetCursorBlinkRate(rate);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetCursorBlinkRate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMaxLength of class  LineEdit */
#ifndef TOLUA_DISABLE_tolua_UI_LineEdit_SetMaxLength00
static int tolua_UI_LineEdit_SetMaxLength00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LineEdit",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LineEdit* self = (LineEdit*)  tolua_tousertype(tolua_S,1,0);
  unsigned length = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMaxLength'", NULL);
#endif
  {
   self->SetMaxLength(length);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMaxLength'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetEchoCharacter of class  LineEdit */
#ifndef TOLUA_DISABLE_tolua_UI_LineEdit_SetEchoCharacter00
static int tolua_UI_LineEdit_SetEchoCharacter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LineEdit",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LineEdit* self = (LineEdit*)  tolua_tousertype(tolua_S,1,0);
  unsigned c = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetEchoCharacter'", NULL);
#endif
  {
   self->SetEchoCharacter(c);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetEchoCharacter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetCursorMovable of class  LineEdit */
#ifndef TOLUA_DISABLE_tolua_UI_LineEdit_SetCursorMovable00
static int tolua_UI_LineEdit_SetCursorMovable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LineEdit",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LineEdit* self = (LineEdit*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetCursorMovable'", NULL);
#endif
  {
   self->SetCursorMovable(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetCursorMovable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetTextSelectable of class  LineEdit */
#ifndef TOLUA_DISABLE_tolua_UI_LineEdit_SetTextSelectable00
static int tolua_UI_LineEdit_SetTextSelectable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LineEdit",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LineEdit* self = (LineEdit*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetTextSelectable'", NULL);
#endif
  {
   self->SetTextSelectable(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetTextSelectable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetTextCopyable of class  LineEdit */
#ifndef TOLUA_DISABLE_tolua_UI_LineEdit_SetTextCopyable00
static int tolua_UI_LineEdit_SetTextCopyable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LineEdit",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LineEdit* self = (LineEdit*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetTextCopyable'", NULL);
#endif
  {
   self->SetTextCopyable(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetTextCopyable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetDoubleClickInterval of class  LineEdit */
#ifndef TOLUA_DISABLE_tolua_UI_LineEdit_SetDoubleClickInterval00
static int tolua_UI_LineEdit_SetDoubleClickInterval00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"LineEdit",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  LineEdit* self = (LineEdit*)  tolua_tousertype(tolua_S,1,0);
  float interval = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetDoubleClickInterval'", NULL);
#endif
  {
   self->SetDoubleClickInterval(interval);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetDoubleClickInterval'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetText of class  LineEdit */
#ifndef TOLUA_DISABLE_tolua_UI_LineEdit_GetText00
static int tolua_UI_LineEdit_GetText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const LineEdit",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const LineEdit* self = (const LineEdit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetText'", NULL);
#endif
  {
   const String& tolua_ret = (const String&)  self->GetText();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const String");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCursorPosition of class  LineEdit */
#ifndef TOLUA_DISABLE_tolua_UI_LineEdit_GetCursorPosition00
static int tolua_UI_LineEdit_GetCursorPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const LineEdit",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const LineEdit* self = (const LineEdit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCursorPosition'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetCursorPosition();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCursorPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCursorBlinkRate of class  LineEdit */
#ifndef TOLUA_DISABLE_tolua_UI_LineEdit_GetCursorBlinkRate00
static int tolua_UI_LineEdit_GetCursorBlinkRate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const LineEdit",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const LineEdit* self = (const LineEdit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCursorBlinkRate'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetCursorBlinkRate();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCursorBlinkRate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMaxLength of class  LineEdit */
#ifndef TOLUA_DISABLE_tolua_UI_LineEdit_GetMaxLength00
static int tolua_UI_LineEdit_GetMaxLength00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const LineEdit",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const LineEdit* self = (const LineEdit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMaxLength'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetMaxLength();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMaxLength'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetEchoCharacter of class  LineEdit */
#ifndef TOLUA_DISABLE_tolua_UI_LineEdit_GetEchoCharacter00
static int tolua_UI_LineEdit_GetEchoCharacter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const LineEdit",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const LineEdit* self = (const LineEdit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetEchoCharacter'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetEchoCharacter();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetEchoCharacter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsCursorMovable of class  LineEdit */
#ifndef TOLUA_DISABLE_tolua_UI_LineEdit_IsCursorMovable00
static int tolua_UI_LineEdit_IsCursorMovable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const LineEdit",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const LineEdit* self = (const LineEdit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsCursorMovable'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsCursorMovable();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsCursorMovable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsTextSelectable of class  LineEdit */
#ifndef TOLUA_DISABLE_tolua_UI_LineEdit_IsTextSelectable00
static int tolua_UI_LineEdit_IsTextSelectable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const LineEdit",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const LineEdit* self = (const LineEdit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsTextSelectable'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsTextSelectable();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsTextSelectable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsTextCopyable of class  LineEdit */
#ifndef TOLUA_DISABLE_tolua_UI_LineEdit_IsTextCopyable00
static int tolua_UI_LineEdit_IsTextCopyable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const LineEdit",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const LineEdit* self = (const LineEdit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsTextCopyable'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsTextCopyable();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsTextCopyable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTextElement of class  LineEdit */
#ifndef TOLUA_DISABLE_tolua_UI_LineEdit_GetTextElement00
static int tolua_UI_LineEdit_GetTextElement00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const LineEdit",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const LineEdit* self = (const LineEdit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTextElement'", NULL);
#endif
  {
   Text* tolua_ret = (Text*)  self->GetTextElement();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Text");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTextElement'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCursor of class  LineEdit */
#ifndef TOLUA_DISABLE_tolua_UI_LineEdit_GetCursor00
static int tolua_UI_LineEdit_GetCursor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const LineEdit",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const LineEdit* self = (const LineEdit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCursor'", NULL);
#endif
  {
   BorderImage* tolua_ret = (BorderImage*)  self->GetCursor();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BorderImage");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCursor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetDoubleClickInterval of class  LineEdit */
#ifndef TOLUA_DISABLE_tolua_UI_LineEdit_GetDoubleClickInterval00
static int tolua_UI_LineEdit_GetDoubleClickInterval00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const LineEdit",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const LineEdit* self = (const LineEdit*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetDoubleClickInterval'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetDoubleClickInterval();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDoubleClickInterval'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddItem of class  ListView */
#ifndef TOLUA_DISABLE_tolua_UI_ListView_AddItem00
static int tolua_UI_ListView_AddItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ListView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ListView* self = (ListView*)  tolua_tousertype(tolua_S,1,0);
  UIElement* item = ((UIElement*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddItem'", NULL);
#endif
  {
   self->AddItem(item);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: InsertItem of class  ListView */
#ifndef TOLUA_DISABLE_tolua_UI_ListView_InsertItem00
static int tolua_UI_ListView_InsertItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ListView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"UIElement",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"UIElement",1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ListView* self = (ListView*)  tolua_tousertype(tolua_S,1,0);
  unsigned index = ((unsigned)  tolua_tonumber(tolua_S,2,0));
  UIElement* item = ((UIElement*)  tolua_tousertype(tolua_S,3,0));
  UIElement* parentItem = ((UIElement*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'InsertItem'", NULL);
#endif
  {
   self->InsertItem(index,item,parentItem);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'InsertItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveItem of class  ListView */
#ifndef TOLUA_DISABLE_tolua_UI_ListView_RemoveItem00
static int tolua_UI_ListView_RemoveItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ListView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UIElement",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ListView* self = (ListView*)  tolua_tousertype(tolua_S,1,0);
  UIElement* item = ((UIElement*)  tolua_tousertype(tolua_S,2,0));
  unsigned index = ((unsigned)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveItem'", NULL);
#endif
  {
   self->RemoveItem(item,index);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemoveItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveItem of class  ListView */
#ifndef TOLUA_DISABLE_tolua_UI_ListView_RemoveItem01
static int tolua_UI_ListView_RemoveItem01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ListView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  ListView* self = (ListView*)  tolua_tousertype(tolua_S,1,0);
  unsigned index = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveItem'", NULL);
#endif
  {
   self->RemoveItem(index);
  }
 }
 return 0;
tolua_lerror:
 return tolua_UI_ListView_RemoveItem00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveAllItems of class  ListView */
#ifndef TOLUA_DISABLE_tolua_UI_ListView_RemoveAllItems00
static int tolua_UI_ListView_RemoveAllItems00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ListView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ListView* self = (ListView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveAllItems'", NULL);
#endif
  {
   self->RemoveAllItems();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemoveAllItems'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetSelection of class  ListView */
#ifndef TOLUA_DISABLE_tolua_UI_ListView_SetSelection00
static int tolua_UI_ListView_SetSelection00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ListView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ListView* self = (ListView*)  tolua_tousertype(tolua_S,1,0);
  unsigned index = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetSelection'", NULL);
#endif
  {
   self->SetSelection(index);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetSelection'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddSelection of class  ListView */
#ifndef TOLUA_DISABLE_tolua_UI_ListView_AddSelection00
static int tolua_UI_ListView_AddSelection00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ListView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ListView* self = (ListView*)  tolua_tousertype(tolua_S,1,0);
  unsigned index = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddSelection'", NULL);
#endif
  {
   self->AddSelection(index);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddSelection'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveSelection of class  ListView */
#ifndef TOLUA_DISABLE_tolua_UI_ListView_RemoveSelection00
static int tolua_UI_ListView_RemoveSelection00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ListView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ListView* self = (ListView*)  tolua_tousertype(tolua_S,1,0);
  unsigned index = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveSelection'", NULL);
#endif
  {
   self->RemoveSelection(index);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemoveSelection'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ToggleSelection of class  ListView */
#ifndef TOLUA_DISABLE_tolua_UI_ListView_ToggleSelection00
static int tolua_UI_ListView_ToggleSelection00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ListView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ListView* self = (ListView*)  tolua_tousertype(tolua_S,1,0);
  unsigned index = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ToggleSelection'", NULL);
#endif
  {
   self->ToggleSelection(index);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ToggleSelection'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ChangeSelection of class  ListView */
#ifndef TOLUA_DISABLE_tolua_UI_ListView_ChangeSelection00
static int tolua_UI_ListView_ChangeSelection00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ListView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ListView* self = (ListView*)  tolua_tousertype(tolua_S,1,0);
  int delta = ((int)  tolua_tonumber(tolua_S,2,0));
  bool additive = ((bool)  tolua_toboolean(tolua_S,3,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ChangeSelection'", NULL);
#endif
  {
   self->ChangeSelection(delta,additive);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ChangeSelection'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ClearSelection of class  ListView */
#ifndef TOLUA_DISABLE_tolua_UI_ListView_ClearSelection00
static int tolua_UI_ListView_ClearSelection00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ListView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ListView* self = (ListView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ClearSelection'", NULL);
#endif
  {
   self->ClearSelection();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ClearSelection'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetHighlightMode of class  ListView */
#ifndef TOLUA_DISABLE_tolua_UI_ListView_SetHighlightMode00
static int tolua_UI_ListView_SetHighlightMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ListView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ListView* self = (ListView*)  tolua_tousertype(tolua_S,1,0);
  HighlightMode mode = ((HighlightMode) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetHighlightMode'", NULL);
#endif
  {
   self->SetHighlightMode(mode);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetHighlightMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMultiselect of class  ListView */
#ifndef TOLUA_DISABLE_tolua_UI_ListView_SetMultiselect00
static int tolua_UI_ListView_SetMultiselect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ListView",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ListView* self = (ListView*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMultiselect'", NULL);
#endif
  {
   self->SetMultiselect(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMultiselect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetHierarchyMode of class  ListView */
#ifndef TOLUA_DISABLE_tolua_UI_ListView_SetHierarchyMode00
static int tolua_UI_ListView_SetHierarchyMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ListView",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ListView* self = (ListView*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetHierarchyMode'", NULL);
#endif
  {
   self->SetHierarchyMode(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetHierarchyMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetBaseIndent of class  ListView */
#ifndef TOLUA_DISABLE_tolua_UI_ListView_SetBaseIndent00
static int tolua_UI_ListView_SetBaseIndent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ListView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ListView* self = (ListView*)  tolua_tousertype(tolua_S,1,0);
  int baseIndent = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetBaseIndent'", NULL);
#endif
  {
   self->SetBaseIndent(baseIndent);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetBaseIndent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetClearSelectionOnDefocus of class  ListView */
#ifndef TOLUA_DISABLE_tolua_UI_ListView_SetClearSelectionOnDefocus00
static int tolua_UI_ListView_SetClearSelectionOnDefocus00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ListView",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ListView* self = (ListView*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetClearSelectionOnDefocus'", NULL);
#endif
  {
   self->SetClearSelectionOnDefocus(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetClearSelectionOnDefocus'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetDoubleClickInterval of class  ListView */
#ifndef TOLUA_DISABLE_tolua_UI_ListView_SetDoubleClickInterval00
static int tolua_UI_ListView_SetDoubleClickInterval00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ListView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ListView* self = (ListView*)  tolua_tousertype(tolua_S,1,0);
  float interval = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetDoubleClickInterval'", NULL);
#endif
  {
   self->SetDoubleClickInterval(interval);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetDoubleClickInterval'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Expand of class  ListView */
#ifndef TOLUA_DISABLE_tolua_UI_ListView_Expand00
static int tolua_UI_ListView_Expand00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ListView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ListView* self = (ListView*)  tolua_tousertype(tolua_S,1,0);
  unsigned index = ((unsigned)  tolua_tonumber(tolua_S,2,0));
  bool enable = ((bool)  tolua_toboolean(tolua_S,3,0));
  bool recursive = ((bool)  tolua_toboolean(tolua_S,4,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Expand'", NULL);
#endif
  {
   self->Expand(index,enable,recursive);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Expand'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ToggleExpand of class  ListView */
#ifndef TOLUA_DISABLE_tolua_UI_ListView_ToggleExpand00
static int tolua_UI_ListView_ToggleExpand00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ListView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ListView* self = (ListView*)  tolua_tousertype(tolua_S,1,0);
  unsigned index = ((unsigned)  tolua_tonumber(tolua_S,2,0));
  bool recursive = ((bool)  tolua_toboolean(tolua_S,3,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ToggleExpand'", NULL);
#endif
  {
   self->ToggleExpand(index,recursive);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ToggleExpand'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNumItems of class  ListView */
#ifndef TOLUA_DISABLE_tolua_UI_ListView_GetNumItems00
static int tolua_UI_ListView_GetNumItems00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ListView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ListView* self = (const ListView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNumItems'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetNumItems();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNumItems'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetItem of class  ListView */
#ifndef TOLUA_DISABLE_tolua_UI_ListView_GetItem00
static int tolua_UI_ListView_GetItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ListView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ListView* self = (const ListView*)  tolua_tousertype(tolua_S,1,0);
  unsigned index = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetItem'", NULL);
#endif
  {
   UIElement* tolua_ret = (UIElement*)  self->GetItem(index);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIElement");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: FindItem of class  ListView */
#ifndef TOLUA_DISABLE_tolua_UI_ListView_FindItem00
static int tolua_UI_ListView_FindItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ListView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ListView* self = (const ListView*)  tolua_tousertype(tolua_S,1,0);
  UIElement* item = ((UIElement*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FindItem'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->FindItem(item);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FindItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSelection of class  ListView */
#ifndef TOLUA_DISABLE_tolua_UI_ListView_GetSelection00
static int tolua_UI_ListView_GetSelection00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ListView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ListView* self = (const ListView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSelection'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetSelection();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSelection'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSelectedItem of class  ListView */
#ifndef TOLUA_DISABLE_tolua_UI_ListView_GetSelectedItem00
static int tolua_UI_ListView_GetSelectedItem00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ListView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ListView* self = (const ListView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSelectedItem'", NULL);
#endif
  {
   UIElement* tolua_ret = (UIElement*)  self->GetSelectedItem();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIElement");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSelectedItem'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsSelected of class  ListView */
#ifndef TOLUA_DISABLE_tolua_UI_ListView_IsSelected00
static int tolua_UI_ListView_IsSelected00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ListView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ListView* self = (const ListView*)  tolua_tousertype(tolua_S,1,0);
  unsigned index = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsSelected'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsSelected(index);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsSelected'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsExpanded of class  ListView */
#ifndef TOLUA_DISABLE_tolua_UI_ListView_IsExpanded00
static int tolua_UI_ListView_IsExpanded00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ListView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ListView* self = (const ListView*)  tolua_tousertype(tolua_S,1,0);
  unsigned index = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsExpanded'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsExpanded(index);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsExpanded'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetHighlightMode of class  ListView */
#ifndef TOLUA_DISABLE_tolua_UI_ListView_GetHighlightMode00
static int tolua_UI_ListView_GetHighlightMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ListView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ListView* self = (const ListView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetHighlightMode'", NULL);
#endif
  {
   HighlightMode tolua_ret = (HighlightMode)  self->GetHighlightMode();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetHighlightMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMultiselect of class  ListView */
#ifndef TOLUA_DISABLE_tolua_UI_ListView_GetMultiselect00
static int tolua_UI_ListView_GetMultiselect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ListView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ListView* self = (const ListView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMultiselect'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetMultiselect();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMultiselect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetClearSelectionOnDefocus of class  ListView */
#ifndef TOLUA_DISABLE_tolua_UI_ListView_GetClearSelectionOnDefocus00
static int tolua_UI_ListView_GetClearSelectionOnDefocus00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ListView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ListView* self = (const ListView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetClearSelectionOnDefocus'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetClearSelectionOnDefocus();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetClearSelectionOnDefocus'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetHierarchyMode of class  ListView */
#ifndef TOLUA_DISABLE_tolua_UI_ListView_GetHierarchyMode00
static int tolua_UI_ListView_GetHierarchyMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ListView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ListView* self = (const ListView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetHierarchyMode'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetHierarchyMode();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetHierarchyMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetBaseIndent of class  ListView */
#ifndef TOLUA_DISABLE_tolua_UI_ListView_GetBaseIndent00
static int tolua_UI_ListView_GetBaseIndent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ListView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ListView* self = (const ListView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetBaseIndent'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetBaseIndent();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetBaseIndent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetDoubleClickInterval of class  ListView */
#ifndef TOLUA_DISABLE_tolua_UI_ListView_GetDoubleClickInterval00
static int tolua_UI_ListView_GetDoubleClickInterval00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ListView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ListView* self = (const ListView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetDoubleClickInterval'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetDoubleClickInterval();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDoubleClickInterval'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetPopup of class  Menu */
#ifndef TOLUA_DISABLE_tolua_UI_Menu_SetPopup00
static int tolua_UI_Menu_SetPopup00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Menu",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Menu* self = (Menu*)  tolua_tousertype(tolua_S,1,0);
  UIElement* element = ((UIElement*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetPopup'", NULL);
#endif
  {
   self->SetPopup(element);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetPopup'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetPopupOffset of class  Menu */
#ifndef TOLUA_DISABLE_tolua_UI_Menu_SetPopupOffset00
static int tolua_UI_Menu_SetPopupOffset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Menu",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const IntVector2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Menu* self = (Menu*)  tolua_tousertype(tolua_S,1,0);
  const IntVector2* offset = ((const IntVector2*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetPopupOffset'", NULL);
#endif
  {
   self->SetPopupOffset(*offset);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetPopupOffset'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetPopupOffset of class  Menu */
#ifndef TOLUA_DISABLE_tolua_UI_Menu_SetPopupOffset01
static int tolua_UI_Menu_SetPopupOffset01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Menu",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Menu* self = (Menu*)  tolua_tousertype(tolua_S,1,0);
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetPopupOffset'", NULL);
#endif
  {
   self->SetPopupOffset(x,y);
  }
 }
 return 0;
tolua_lerror:
 return tolua_UI_Menu_SetPopupOffset00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: ShowPopup of class  Menu */
#ifndef TOLUA_DISABLE_tolua_UI_Menu_ShowPopup00
static int tolua_UI_Menu_ShowPopup00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Menu",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Menu* self = (Menu*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ShowPopup'", NULL);
#endif
  {
   self->ShowPopup(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ShowPopup'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetAccelerator of class  Menu */
#ifndef TOLUA_DISABLE_tolua_UI_Menu_SetAccelerator00
static int tolua_UI_Menu_SetAccelerator00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Menu",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Menu* self = (Menu*)  tolua_tousertype(tolua_S,1,0);
  int key = ((int)  tolua_tonumber(tolua_S,2,0));
  int qualifiers = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetAccelerator'", NULL);
#endif
  {
   self->SetAccelerator(key,qualifiers);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetAccelerator'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetPopup of class  Menu */
#ifndef TOLUA_DISABLE_tolua_UI_Menu_GetPopup00
static int tolua_UI_Menu_GetPopup00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Menu",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Menu* self = (const Menu*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPopup'", NULL);
#endif
  {
   UIElement* tolua_ret = (UIElement*)  self->GetPopup();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIElement");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPopup'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetPopupOffset of class  Menu */
#ifndef TOLUA_DISABLE_tolua_UI_Menu_GetPopupOffset00
static int tolua_UI_Menu_GetPopupOffset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Menu",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Menu* self = (const Menu*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPopupOffset'", NULL);
#endif
  {
   const IntVector2& tolua_ret = (const IntVector2&)  self->GetPopupOffset();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const IntVector2");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPopupOffset'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetShowPopup of class  Menu */
#ifndef TOLUA_DISABLE_tolua_UI_Menu_GetShowPopup00
static int tolua_UI_Menu_GetShowPopup00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Menu",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Menu* self = (const Menu*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetShowPopup'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetShowPopup();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetShowPopup'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAcceleratorKey of class  Menu */
#ifndef TOLUA_DISABLE_tolua_UI_Menu_GetAcceleratorKey00
static int tolua_UI_Menu_GetAcceleratorKey00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Menu",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Menu* self = (const Menu*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAcceleratorKey'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetAcceleratorKey();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAcceleratorKey'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAcceleratorQualifiers of class  Menu */
#ifndef TOLUA_DISABLE_tolua_UI_Menu_GetAcceleratorQualifiers00
static int tolua_UI_Menu_GetAcceleratorQualifiers00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Menu",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Menu* self = (const Menu*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAcceleratorQualifiers'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetAcceleratorQualifiers();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAcceleratorQualifiers'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetOrientation of class  ScrollBar */
#ifndef TOLUA_DISABLE_tolua_UI_ScrollBar_SetOrientation00
static int tolua_UI_ScrollBar_SetOrientation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollBar",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScrollBar* self = (ScrollBar*)  tolua_tousertype(tolua_S,1,0);
  Orientation orientation = ((Orientation) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetOrientation'", NULL);
#endif
  {
   self->SetOrientation(orientation);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetOrientation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetRange of class  ScrollBar */
#ifndef TOLUA_DISABLE_tolua_UI_ScrollBar_SetRange00
static int tolua_UI_ScrollBar_SetRange00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollBar",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScrollBar* self = (ScrollBar*)  tolua_tousertype(tolua_S,1,0);
  float range = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetRange'", NULL);
#endif
  {
   self->SetRange(range);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetRange'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetValue of class  ScrollBar */
#ifndef TOLUA_DISABLE_tolua_UI_ScrollBar_SetValue00
static int tolua_UI_ScrollBar_SetValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollBar",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScrollBar* self = (ScrollBar*)  tolua_tousertype(tolua_S,1,0);
  float value = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetValue'", NULL);
#endif
  {
   self->SetValue(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ChangeValue of class  ScrollBar */
#ifndef TOLUA_DISABLE_tolua_UI_ScrollBar_ChangeValue00
static int tolua_UI_ScrollBar_ChangeValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollBar",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScrollBar* self = (ScrollBar*)  tolua_tousertype(tolua_S,1,0);
  float delta = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ChangeValue'", NULL);
#endif
  {
   self->ChangeValue(delta);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ChangeValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetScrollStep of class  ScrollBar */
#ifndef TOLUA_DISABLE_tolua_UI_ScrollBar_SetScrollStep00
static int tolua_UI_ScrollBar_SetScrollStep00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollBar",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScrollBar* self = (ScrollBar*)  tolua_tousertype(tolua_S,1,0);
  float step = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetScrollStep'", NULL);
#endif
  {
   self->SetScrollStep(step);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetScrollStep'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetStepFactor of class  ScrollBar */
#ifndef TOLUA_DISABLE_tolua_UI_ScrollBar_SetStepFactor00
static int tolua_UI_ScrollBar_SetStepFactor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollBar",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScrollBar* self = (ScrollBar*)  tolua_tousertype(tolua_S,1,0);
  float factor = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetStepFactor'", NULL);
#endif
  {
   self->SetStepFactor(factor);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetStepFactor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: StepBack of class  ScrollBar */
#ifndef TOLUA_DISABLE_tolua_UI_ScrollBar_StepBack00
static int tolua_UI_ScrollBar_StepBack00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScrollBar* self = (ScrollBar*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'StepBack'", NULL);
#endif
  {
   self->StepBack();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'StepBack'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: StepForward of class  ScrollBar */
#ifndef TOLUA_DISABLE_tolua_UI_ScrollBar_StepForward00
static int tolua_UI_ScrollBar_StepForward00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScrollBar* self = (ScrollBar*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'StepForward'", NULL);
#endif
  {
   self->StepForward();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'StepForward'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetOrientation of class  ScrollBar */
#ifndef TOLUA_DISABLE_tolua_UI_ScrollBar_GetOrientation00
static int tolua_UI_ScrollBar_GetOrientation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ScrollBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ScrollBar* self = (const ScrollBar*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetOrientation'", NULL);
#endif
  {
   Orientation tolua_ret = (Orientation)  self->GetOrientation();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetOrientation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRange of class  ScrollBar */
#ifndef TOLUA_DISABLE_tolua_UI_ScrollBar_GetRange00
static int tolua_UI_ScrollBar_GetRange00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ScrollBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ScrollBar* self = (const ScrollBar*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRange'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetRange();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRange'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetValue of class  ScrollBar */
#ifndef TOLUA_DISABLE_tolua_UI_ScrollBar_GetValue00
static int tolua_UI_ScrollBar_GetValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ScrollBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ScrollBar* self = (const ScrollBar*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetValue'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetValue();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetScrollStep of class  ScrollBar */
#ifndef TOLUA_DISABLE_tolua_UI_ScrollBar_GetScrollStep00
static int tolua_UI_ScrollBar_GetScrollStep00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ScrollBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ScrollBar* self = (const ScrollBar*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetScrollStep'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetScrollStep();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetScrollStep'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetStepFactor of class  ScrollBar */
#ifndef TOLUA_DISABLE_tolua_UI_ScrollBar_GetStepFactor00
static int tolua_UI_ScrollBar_GetStepFactor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ScrollBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ScrollBar* self = (const ScrollBar*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetStepFactor'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetStepFactor();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetStepFactor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetEffectiveScrollStep of class  ScrollBar */
#ifndef TOLUA_DISABLE_tolua_UI_ScrollBar_GetEffectiveScrollStep00
static int tolua_UI_ScrollBar_GetEffectiveScrollStep00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ScrollBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ScrollBar* self = (const ScrollBar*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetEffectiveScrollStep'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetEffectiveScrollStep();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetEffectiveScrollStep'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetBackButton of class  ScrollBar */
#ifndef TOLUA_DISABLE_tolua_UI_ScrollBar_GetBackButton00
static int tolua_UI_ScrollBar_GetBackButton00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ScrollBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ScrollBar* self = (const ScrollBar*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetBackButton'", NULL);
#endif
  {
   Button* tolua_ret = (Button*)  self->GetBackButton();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Button");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetBackButton'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetForwardButton of class  ScrollBar */
#ifndef TOLUA_DISABLE_tolua_UI_ScrollBar_GetForwardButton00
static int tolua_UI_ScrollBar_GetForwardButton00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ScrollBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ScrollBar* self = (const ScrollBar*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetForwardButton'", NULL);
#endif
  {
   Button* tolua_ret = (Button*)  self->GetForwardButton();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Button");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetForwardButton'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSlider of class  ScrollBar */
#ifndef TOLUA_DISABLE_tolua_UI_ScrollBar_GetSlider00
static int tolua_UI_ScrollBar_GetSlider00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ScrollBar",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ScrollBar* self = (const ScrollBar*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSlider'", NULL);
#endif
  {
   Slider* tolua_ret = (Slider*)  self->GetSlider();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Slider");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSlider'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetContentElement of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_UI_ScrollView_SetContentElement00
static int tolua_UI_ScrollView_SetContentElement00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScrollView* self = (ScrollView*)  tolua_tousertype(tolua_S,1,0);
  UIElement* element = ((UIElement*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetContentElement'", NULL);
#endif
  {
   self->SetContentElement(element);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetContentElement'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetViewPosition of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_UI_ScrollView_SetViewPosition00
static int tolua_UI_ScrollView_SetViewPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const IntVector2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScrollView* self = (ScrollView*)  tolua_tousertype(tolua_S,1,0);
  const IntVector2* position = ((const IntVector2*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetViewPosition'", NULL);
#endif
  {
   self->SetViewPosition(*position);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetViewPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetViewPosition of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_UI_ScrollView_SetViewPosition01
static int tolua_UI_ScrollView_SetViewPosition01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  ScrollView* self = (ScrollView*)  tolua_tousertype(tolua_S,1,0);
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetViewPosition'", NULL);
#endif
  {
   self->SetViewPosition(x,y);
  }
 }
 return 0;
tolua_lerror:
 return tolua_UI_ScrollView_SetViewPosition00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetScrollBarsVisible of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_UI_ScrollView_SetScrollBarsVisible00
static int tolua_UI_ScrollView_SetScrollBarsVisible00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScrollView* self = (ScrollView*)  tolua_tousertype(tolua_S,1,0);
  bool horizontal = ((bool)  tolua_toboolean(tolua_S,2,0));
  bool vertical = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetScrollBarsVisible'", NULL);
#endif
  {
   self->SetScrollBarsVisible(horizontal,vertical);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetScrollBarsVisible'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetScrollBarsAutoVisible of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_UI_ScrollView_SetScrollBarsAutoVisible00
static int tolua_UI_ScrollView_SetScrollBarsAutoVisible00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScrollView* self = (ScrollView*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetScrollBarsAutoVisible'", NULL);
#endif
  {
   self->SetScrollBarsAutoVisible(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetScrollBarsAutoVisible'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetScrollStep of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_UI_ScrollView_SetScrollStep00
static int tolua_UI_ScrollView_SetScrollStep00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScrollView* self = (ScrollView*)  tolua_tousertype(tolua_S,1,0);
  float step = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetScrollStep'", NULL);
#endif
  {
   self->SetScrollStep(step);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetScrollStep'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetPageStep of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_UI_ScrollView_SetPageStep00
static int tolua_UI_ScrollView_SetPageStep00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScrollView* self = (ScrollView*)  tolua_tousertype(tolua_S,1,0);
  float step = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetPageStep'", NULL);
#endif
  {
   self->SetPageStep(step);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetPageStep'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetViewPosition of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_UI_ScrollView_GetViewPosition00
static int tolua_UI_ScrollView_GetViewPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ScrollView* self = (const ScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetViewPosition'", NULL);
#endif
  {
   const IntVector2& tolua_ret = (const IntVector2&)  self->GetViewPosition();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const IntVector2");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetViewPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetContentElement of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_UI_ScrollView_GetContentElement00
static int tolua_UI_ScrollView_GetContentElement00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ScrollView* self = (const ScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetContentElement'", NULL);
#endif
  {
   UIElement* tolua_ret = (UIElement*)  self->GetContentElement();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIElement");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetContentElement'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetHorizontalScrollBar of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_UI_ScrollView_GetHorizontalScrollBar00
static int tolua_UI_ScrollView_GetHorizontalScrollBar00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ScrollView* self = (const ScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetHorizontalScrollBar'", NULL);
#endif
  {
   ScrollBar* tolua_ret = (ScrollBar*)  self->GetHorizontalScrollBar();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ScrollBar");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetHorizontalScrollBar'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetVerticalScrollBar of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_UI_ScrollView_GetVerticalScrollBar00
static int tolua_UI_ScrollView_GetVerticalScrollBar00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ScrollView* self = (const ScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetVerticalScrollBar'", NULL);
#endif
  {
   ScrollBar* tolua_ret = (ScrollBar*)  self->GetVerticalScrollBar();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ScrollBar");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetVerticalScrollBar'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetScrollPanel of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_UI_ScrollView_GetScrollPanel00
static int tolua_UI_ScrollView_GetScrollPanel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ScrollView* self = (const ScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetScrollPanel'", NULL);
#endif
  {
   BorderImage* tolua_ret = (BorderImage*)  self->GetScrollPanel();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BorderImage");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetScrollPanel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetScrollBarsAutoVisible of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_UI_ScrollView_GetScrollBarsAutoVisible00
static int tolua_UI_ScrollView_GetScrollBarsAutoVisible00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ScrollView* self = (const ScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetScrollBarsAutoVisible'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetScrollBarsAutoVisible();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetScrollBarsAutoVisible'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetScrollStep of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_UI_ScrollView_GetScrollStep00
static int tolua_UI_ScrollView_GetScrollStep00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ScrollView* self = (const ScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetScrollStep'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetScrollStep();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetScrollStep'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetPageStep of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_UI_ScrollView_GetPageStep00
static int tolua_UI_ScrollView_GetPageStep00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ScrollView",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ScrollView* self = (const ScrollView*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPageStep'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetPageStep();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPageStep'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetViewPositionAttr of class  ScrollView */
#ifndef TOLUA_DISABLE_tolua_UI_ScrollView_SetViewPositionAttr00
static int tolua_UI_ScrollView_SetViewPositionAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ScrollView",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const IntVector2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ScrollView* self = (ScrollView*)  tolua_tousertype(tolua_S,1,0);
  const IntVector2* value = ((const IntVector2*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetViewPositionAttr'", NULL);
#endif
  {
   self->SetViewPositionAttr(*value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetViewPositionAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetOrientation of class  Slider */
#ifndef TOLUA_DISABLE_tolua_UI_Slider_SetOrientation00
static int tolua_UI_Slider_SetOrientation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Slider",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Slider* self = (Slider*)  tolua_tousertype(tolua_S,1,0);
  Orientation orientation = ((Orientation) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetOrientation'", NULL);
#endif
  {
   self->SetOrientation(orientation);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetOrientation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetRange of class  Slider */
#ifndef TOLUA_DISABLE_tolua_UI_Slider_SetRange00
static int tolua_UI_Slider_SetRange00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Slider",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Slider* self = (Slider*)  tolua_tousertype(tolua_S,1,0);
  float range = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetRange'", NULL);
#endif
  {
   self->SetRange(range);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetRange'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetValue of class  Slider */
#ifndef TOLUA_DISABLE_tolua_UI_Slider_SetValue00
static int tolua_UI_Slider_SetValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Slider",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Slider* self = (Slider*)  tolua_tousertype(tolua_S,1,0);
  float value = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetValue'", NULL);
#endif
  {
   self->SetValue(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ChangeValue of class  Slider */
#ifndef TOLUA_DISABLE_tolua_UI_Slider_ChangeValue00
static int tolua_UI_Slider_ChangeValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Slider",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Slider* self = (Slider*)  tolua_tousertype(tolua_S,1,0);
  float delta = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ChangeValue'", NULL);
#endif
  {
   self->ChangeValue(delta);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ChangeValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetRepeatRate of class  Slider */
#ifndef TOLUA_DISABLE_tolua_UI_Slider_SetRepeatRate00
static int tolua_UI_Slider_SetRepeatRate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Slider",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Slider* self = (Slider*)  tolua_tousertype(tolua_S,1,0);
  float rate = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetRepeatRate'", NULL);
#endif
  {
   self->SetRepeatRate(rate);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetRepeatRate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetOrientation of class  Slider */
#ifndef TOLUA_DISABLE_tolua_UI_Slider_GetOrientation00
static int tolua_UI_Slider_GetOrientation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Slider",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Slider* self = (const Slider*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetOrientation'", NULL);
#endif
  {
   Orientation tolua_ret = (Orientation)  self->GetOrientation();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetOrientation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRange of class  Slider */
#ifndef TOLUA_DISABLE_tolua_UI_Slider_GetRange00
static int tolua_UI_Slider_GetRange00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Slider",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Slider* self = (const Slider*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRange'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetRange();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRange'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetValue of class  Slider */
#ifndef TOLUA_DISABLE_tolua_UI_Slider_GetValue00
static int tolua_UI_Slider_GetValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Slider",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Slider* self = (const Slider*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetValue'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetValue();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetKnob of class  Slider */
#ifndef TOLUA_DISABLE_tolua_UI_Slider_GetKnob00
static int tolua_UI_Slider_GetKnob00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Slider",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Slider* self = (const Slider*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetKnob'", NULL);
#endif
  {
   BorderImage* tolua_ret = (BorderImage*)  self->GetKnob();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"BorderImage");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetKnob'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRepeatRate of class  Slider */
#ifndef TOLUA_DISABLE_tolua_UI_Slider_GetRepeatRate00
static int tolua_UI_Slider_GetRepeatRate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Slider",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Slider* self = (const Slider*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRepeatRate'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetRepeatRate();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRepeatRate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetPosition of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_UI_Sprite_SetPosition00
static int tolua_UI_Sprite_SetPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sprite",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Sprite* self = (Sprite*)  tolua_tousertype(tolua_S,1,0);
  const Vector2* position = ((const Vector2*)  tolua_tousertype(tolua_S,2,0));
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

/* method: SetPosition of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_UI_Sprite_SetPosition01
static int tolua_UI_Sprite_SetPosition01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Sprite* self = (Sprite*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetPosition'", NULL);
#endif
  {
   self->SetPosition(x,y);
  }
 }
 return 0;
tolua_lerror:
 return tolua_UI_Sprite_SetPosition00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetHotSpot of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_UI_Sprite_SetHotSpot00
static int tolua_UI_Sprite_SetHotSpot00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sprite",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const IntVector2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Sprite* self = (Sprite*)  tolua_tousertype(tolua_S,1,0);
  const IntVector2* hotSpot = ((const IntVector2*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetHotSpot'", NULL);
#endif
  {
   self->SetHotSpot(*hotSpot);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetHotSpot'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetHotSpot of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_UI_Sprite_SetHotSpot01
static int tolua_UI_Sprite_SetHotSpot01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Sprite* self = (Sprite*)  tolua_tousertype(tolua_S,1,0);
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetHotSpot'", NULL);
#endif
  {
   self->SetHotSpot(x,y);
  }
 }
 return 0;
tolua_lerror:
 return tolua_UI_Sprite_SetHotSpot00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetScale of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_UI_Sprite_SetScale00
static int tolua_UI_Sprite_SetScale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sprite",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Sprite* self = (Sprite*)  tolua_tousertype(tolua_S,1,0);
  const Vector2* scale = ((const Vector2*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetScale'", NULL);
#endif
  {
   self->SetScale(*scale);
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

/* method: SetScale of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_UI_Sprite_SetScale01
static int tolua_UI_Sprite_SetScale01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Sprite* self = (Sprite*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetScale'", NULL);
#endif
  {
   self->SetScale(x,y);
  }
 }
 return 0;
tolua_lerror:
 return tolua_UI_Sprite_SetScale00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetScale of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_UI_Sprite_SetScale02
static int tolua_UI_Sprite_SetScale02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Sprite* self = (Sprite*)  tolua_tousertype(tolua_S,1,0);
  float scale = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetScale'", NULL);
#endif
  {
   self->SetScale(scale);
  }
 }
 return 0;
tolua_lerror:
 return tolua_UI_Sprite_SetScale01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetRotation of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_UI_Sprite_SetRotation00
static int tolua_UI_Sprite_SetRotation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Sprite* self = (Sprite*)  tolua_tousertype(tolua_S,1,0);
  float angle = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetRotation'", NULL);
#endif
  {
   self->SetRotation(angle);
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

/* method: SetTexture of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_UI_Sprite_SetTexture00
static int tolua_UI_Sprite_SetTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sprite",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Texture",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Sprite* self = (Sprite*)  tolua_tousertype(tolua_S,1,0);
  Texture* texture = ((Texture*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetTexture'", NULL);
#endif
  {
   self->SetTexture(texture);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetImageRect of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_UI_Sprite_SetImageRect00
static int tolua_UI_Sprite_SetImageRect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sprite",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const IntRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Sprite* self = (Sprite*)  tolua_tousertype(tolua_S,1,0);
  const IntRect* rect = ((const IntRect*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetImageRect'", NULL);
#endif
  {
   self->SetImageRect(*rect);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetImageRect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFullImageRect of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_UI_Sprite_SetFullImageRect00
static int tolua_UI_Sprite_SetFullImageRect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Sprite* self = (Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFullImageRect'", NULL);
#endif
  {
   self->SetFullImageRect();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFullImageRect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetBlendMode of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_UI_Sprite_SetBlendMode00
static int tolua_UI_Sprite_SetBlendMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sprite",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Sprite* self = (Sprite*)  tolua_tousertype(tolua_S,1,0);
  BlendMode mode = ((BlendMode) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetBlendMode'", NULL);
#endif
  {
   self->SetBlendMode(mode);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetBlendMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetPosition of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_UI_Sprite_GetPosition00
static int tolua_UI_Sprite_GetPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Sprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Sprite* self = (const Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPosition'", NULL);
#endif
  {
   const Vector2& tolua_ret = (const Vector2&)  self->GetPosition();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Vector2");
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

/* method: GetHotSpot of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_UI_Sprite_GetHotSpot00
static int tolua_UI_Sprite_GetHotSpot00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Sprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Sprite* self = (const Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetHotSpot'", NULL);
#endif
  {
   const IntVector2& tolua_ret = (const IntVector2&)  self->GetHotSpot();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const IntVector2");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetHotSpot'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetScale of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_UI_Sprite_GetScale00
static int tolua_UI_Sprite_GetScale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Sprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Sprite* self = (const Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetScale'", NULL);
#endif
  {
   const Vector2& tolua_ret = (const Vector2&)  self->GetScale();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Vector2");
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

/* method: GetRotation of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_UI_Sprite_GetRotation00
static int tolua_UI_Sprite_GetRotation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Sprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Sprite* self = (const Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRotation'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetRotation();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
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

/* method: GetTexture of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_UI_Sprite_GetTexture00
static int tolua_UI_Sprite_GetTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Sprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Sprite* self = (const Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTexture'", NULL);
#endif
  {
   Texture* tolua_ret = (Texture*)  self->GetTexture();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Texture");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetImageRect of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_UI_Sprite_GetImageRect00
static int tolua_UI_Sprite_GetImageRect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Sprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Sprite* self = (const Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetImageRect'", NULL);
#endif
  {
   const IntRect& tolua_ret = (const IntRect&)  self->GetImageRect();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const IntRect");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetImageRect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetBlendMode of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_UI_Sprite_GetBlendMode00
static int tolua_UI_Sprite_GetBlendMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Sprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Sprite* self = (const Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetBlendMode'", NULL);
#endif
  {
   BlendMode tolua_ret = (BlendMode)  self->GetBlendMode();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetBlendMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetTextureAttr of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_UI_Sprite_SetTextureAttr00
static int tolua_UI_Sprite_SetTextureAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sprite",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"ResourceRef",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Sprite* self = (Sprite*)  tolua_tousertype(tolua_S,1,0);
  ResourceRef value = *((ResourceRef*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetTextureAttr'", NULL);
#endif
  {
   self->SetTextureAttr(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetTextureAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTextureAttr of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_UI_Sprite_GetTextureAttr00
static int tolua_UI_Sprite_GetTextureAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Sprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Sprite* self = (const Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTextureAttr'", NULL);
#endif
  {
   ResourceRef tolua_ret = (ResourceRef)  self->GetTextureAttr();
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
 tolua_error(tolua_S,"#ferror in function 'GetTextureAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTransform of class  Sprite */
#ifndef TOLUA_DISABLE_tolua_UI_Sprite_GetTransform00
static int tolua_UI_Sprite_GetTransform00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Sprite",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Sprite* self = (const Sprite*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTransform'", NULL);
#endif
  {
   const Matrix3x4& tolua_ret = (const Matrix3x4&)  self->GetTransform();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Matrix3x4");
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

/* function: NewSprite */
#ifndef TOLUA_DISABLE_tolua_UI_Sprite00
static int tolua_UI_Sprite00(lua_State* tolua_S)
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
   Sprite* tolua_ret = (Sprite*)  NewSprite();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Sprite");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Sprite'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFont of class  Text */
#ifndef TOLUA_DISABLE_tolua_UI_Text_SetFont00
static int tolua_UI_Text_SetFont00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Text",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Text* self = (Text*)  tolua_tousertype(tolua_S,1,0);
  const String* fontName = ((const String*)  tolua_tousertype(tolua_S,2,0));
  int size = ((int)  tolua_tonumber(tolua_S,3,DEFAULT_FONT_SIZE));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFont'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SetFont(*fontName,size);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFont'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFont of class  Text */
#ifndef TOLUA_DISABLE_tolua_UI_Text_SetFont01
static int tolua_UI_Text_SetFont01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Text",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Font",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Text* self = (Text*)  tolua_tousertype(tolua_S,1,0);
  Font* font = ((Font*)  tolua_tousertype(tolua_S,2,0));
  int size = ((int)  tolua_tonumber(tolua_S,3,DEFAULT_FONT_SIZE));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFont'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SetFont(font,size);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_UI_Text_SetFont00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetText of class  Text */
#ifndef TOLUA_DISABLE_tolua_UI_Text_SetText00
static int tolua_UI_Text_SetText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Text",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Text* self = (Text*)  tolua_tousertype(tolua_S,1,0);
  const String* text = ((const String*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetText'", NULL);
#endif
  {
   self->SetText(*text);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetTextAlignment of class  Text */
#ifndef TOLUA_DISABLE_tolua_UI_Text_SetTextAlignment00
static int tolua_UI_Text_SetTextAlignment00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Text",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Text* self = (Text*)  tolua_tousertype(tolua_S,1,0);
  HorizontalAlignment align = ((HorizontalAlignment) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetTextAlignment'", NULL);
#endif
  {
   self->SetTextAlignment(align);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetTextAlignment'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetRowSpacing of class  Text */
#ifndef TOLUA_DISABLE_tolua_UI_Text_SetRowSpacing00
static int tolua_UI_Text_SetRowSpacing00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Text",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Text* self = (Text*)  tolua_tousertype(tolua_S,1,0);
  float spacing = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetRowSpacing'", NULL);
#endif
  {
   self->SetRowSpacing(spacing);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetRowSpacing'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetWordwrap of class  Text */
#ifndef TOLUA_DISABLE_tolua_UI_Text_SetWordwrap00
static int tolua_UI_Text_SetWordwrap00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Text",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Text* self = (Text*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetWordwrap'", NULL);
#endif
  {
   self->SetWordwrap(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetWordwrap'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetSelection of class  Text */
#ifndef TOLUA_DISABLE_tolua_UI_Text_SetSelection00
static int tolua_UI_Text_SetSelection00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Text",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Text* self = (Text*)  tolua_tousertype(tolua_S,1,0);
  unsigned start = ((unsigned)  tolua_tonumber(tolua_S,2,0));
  unsigned length = ((unsigned)  tolua_tonumber(tolua_S,3,M_MAX_UNSIGNED));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetSelection'", NULL);
#endif
  {
   self->SetSelection(start,length);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetSelection'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ClearSelection of class  Text */
#ifndef TOLUA_DISABLE_tolua_UI_Text_ClearSelection00
static int tolua_UI_Text_ClearSelection00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Text",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Text* self = (Text*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ClearSelection'", NULL);
#endif
  {
   self->ClearSelection();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ClearSelection'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetSelectionColor of class  Text */
#ifndef TOLUA_DISABLE_tolua_UI_Text_SetSelectionColor00
static int tolua_UI_Text_SetSelectionColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Text",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Color",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Text* self = (Text*)  tolua_tousertype(tolua_S,1,0);
  const Color* color = ((const Color*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetSelectionColor'", NULL);
#endif
  {
   self->SetSelectionColor(*color);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetSelectionColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetHoverColor of class  Text */
#ifndef TOLUA_DISABLE_tolua_UI_Text_SetHoverColor00
static int tolua_UI_Text_SetHoverColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Text",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Color",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Text* self = (Text*)  tolua_tousertype(tolua_S,1,0);
  const Color* color = ((const Color*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetHoverColor'", NULL);
#endif
  {
   self->SetHoverColor(*color);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetHoverColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFont of class  Text */
#ifndef TOLUA_DISABLE_tolua_UI_Text_GetFont00
static int tolua_UI_Text_GetFont00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Text",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Text* self = (const Text*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFont'", NULL);
#endif
  {
   Font* tolua_ret = (Font*)  self->GetFont();
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

/* method: GetFontSize of class  Text */
#ifndef TOLUA_DISABLE_tolua_UI_Text_GetFontSize00
static int tolua_UI_Text_GetFontSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Text",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Text* self = (const Text*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFontSize'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetFontSize();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFontSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetText of class  Text */
#ifndef TOLUA_DISABLE_tolua_UI_Text_GetText00
static int tolua_UI_Text_GetText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Text",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Text* self = (const Text*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetText'", NULL);
#endif
  {
   const String& tolua_ret = (const String&)  self->GetText();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const String");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTextAlignment of class  Text */
#ifndef TOLUA_DISABLE_tolua_UI_Text_GetTextAlignment00
static int tolua_UI_Text_GetTextAlignment00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Text",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Text* self = (const Text*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTextAlignment'", NULL);
#endif
  {
   HorizontalAlignment tolua_ret = (HorizontalAlignment)  self->GetTextAlignment();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTextAlignment'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRowSpacing of class  Text */
#ifndef TOLUA_DISABLE_tolua_UI_Text_GetRowSpacing00
static int tolua_UI_Text_GetRowSpacing00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Text",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Text* self = (const Text*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRowSpacing'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetRowSpacing();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRowSpacing'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetWordwrap of class  Text */
#ifndef TOLUA_DISABLE_tolua_UI_Text_GetWordwrap00
static int tolua_UI_Text_GetWordwrap00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Text",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Text* self = (const Text*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetWordwrap'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetWordwrap();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetWordwrap'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSelectionStart of class  Text */
#ifndef TOLUA_DISABLE_tolua_UI_Text_GetSelectionStart00
static int tolua_UI_Text_GetSelectionStart00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Text",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Text* self = (const Text*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSelectionStart'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetSelectionStart();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSelectionStart'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSelectionLength of class  Text */
#ifndef TOLUA_DISABLE_tolua_UI_Text_GetSelectionLength00
static int tolua_UI_Text_GetSelectionLength00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Text",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Text* self = (const Text*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSelectionLength'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetSelectionLength();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSelectionLength'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSelectionColor of class  Text */
#ifndef TOLUA_DISABLE_tolua_UI_Text_GetSelectionColor00
static int tolua_UI_Text_GetSelectionColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Text",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Text* self = (const Text*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSelectionColor'", NULL);
#endif
  {
   const Color& tolua_ret = (const Color&)  self->GetSelectionColor();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Color");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSelectionColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetHoverColor of class  Text */
#ifndef TOLUA_DISABLE_tolua_UI_Text_GetHoverColor00
static int tolua_UI_Text_GetHoverColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Text",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Text* self = (const Text*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetHoverColor'", NULL);
#endif
  {
   const Color& tolua_ret = (const Color&)  self->GetHoverColor();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Color");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetHoverColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRowHeight of class  Text */
#ifndef TOLUA_DISABLE_tolua_UI_Text_GetRowHeight00
static int tolua_UI_Text_GetRowHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Text",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Text* self = (const Text*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRowHeight'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetRowHeight();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRowHeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNumRows of class  Text */
#ifndef TOLUA_DISABLE_tolua_UI_Text_GetNumRows00
static int tolua_UI_Text_GetNumRows00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Text",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Text* self = (const Text*)  tolua_tousertype(tolua_S,1,0);
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

/* method: SetFont of class  Text3D */
#ifndef TOLUA_DISABLE_tolua_UI_Text3D_SetFont00
static int tolua_UI_Text3D_SetFont00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Text3D",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Text3D* self = (Text3D*)  tolua_tousertype(tolua_S,1,0);
  const String* fontName = ((const String*)  tolua_tousertype(tolua_S,2,0));
  int size = ((int)  tolua_tonumber(tolua_S,3,DEFAULT_FONT_SIZE));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFont'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SetFont(*fontName,size);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFont'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFont of class  Text3D */
#ifndef TOLUA_DISABLE_tolua_UI_Text3D_SetFont01
static int tolua_UI_Text3D_SetFont01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Text3D",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Font",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Text3D* self = (Text3D*)  tolua_tousertype(tolua_S,1,0);
  Font* font = ((Font*)  tolua_tousertype(tolua_S,2,0));
  int size = ((int)  tolua_tonumber(tolua_S,3,DEFAULT_FONT_SIZE));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFont'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SetFont(font,size);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_UI_Text3D_SetFont00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMaterial of class  Text3D */
#ifndef TOLUA_DISABLE_tolua_UI_Text3D_SetMaterial00
static int tolua_UI_Text3D_SetMaterial00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Text3D",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Material",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Text3D* self = (Text3D*)  tolua_tousertype(tolua_S,1,0);
  Material* material = ((Material*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMaterial'", NULL);
#endif
  {
   self->SetMaterial(material);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMaterial'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetText of class  Text3D */
#ifndef TOLUA_DISABLE_tolua_UI_Text3D_SetText00
static int tolua_UI_Text3D_SetText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Text3D",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Text3D* self = (Text3D*)  tolua_tousertype(tolua_S,1,0);
  const String* text = ((const String*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetText'", NULL);
#endif
  {
   self->SetText(*text);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetAlignment of class  Text3D */
#ifndef TOLUA_DISABLE_tolua_UI_Text3D_SetAlignment00
static int tolua_UI_Text3D_SetAlignment00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Text3D",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Text3D* self = (Text3D*)  tolua_tousertype(tolua_S,1,0);
  HorizontalAlignment hAlign = ((HorizontalAlignment) (int)  tolua_tonumber(tolua_S,2,0));
  VerticalAlignment vAlign = ((VerticalAlignment) (int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetAlignment'", NULL);
#endif
  {
   self->SetAlignment(hAlign,vAlign);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetAlignment'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetHorizontalAlignment of class  Text3D */
#ifndef TOLUA_DISABLE_tolua_UI_Text3D_SetHorizontalAlignment00
static int tolua_UI_Text3D_SetHorizontalAlignment00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Text3D",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Text3D* self = (Text3D*)  tolua_tousertype(tolua_S,1,0);
  HorizontalAlignment align = ((HorizontalAlignment) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetHorizontalAlignment'", NULL);
#endif
  {
   self->SetHorizontalAlignment(align);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetHorizontalAlignment'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetVerticalAlignment of class  Text3D */
#ifndef TOLUA_DISABLE_tolua_UI_Text3D_SetVerticalAlignment00
static int tolua_UI_Text3D_SetVerticalAlignment00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Text3D",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Text3D* self = (Text3D*)  tolua_tousertype(tolua_S,1,0);
  VerticalAlignment align = ((VerticalAlignment) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetVerticalAlignment'", NULL);
#endif
  {
   self->SetVerticalAlignment(align);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetVerticalAlignment'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetTextAlignment of class  Text3D */
#ifndef TOLUA_DISABLE_tolua_UI_Text3D_SetTextAlignment00
static int tolua_UI_Text3D_SetTextAlignment00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Text3D",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Text3D* self = (Text3D*)  tolua_tousertype(tolua_S,1,0);
  HorizontalAlignment align = ((HorizontalAlignment) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetTextAlignment'", NULL);
#endif
  {
   self->SetTextAlignment(align);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetTextAlignment'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetRowSpacing of class  Text3D */
#ifndef TOLUA_DISABLE_tolua_UI_Text3D_SetRowSpacing00
static int tolua_UI_Text3D_SetRowSpacing00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Text3D",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Text3D* self = (Text3D*)  tolua_tousertype(tolua_S,1,0);
  float spacing = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetRowSpacing'", NULL);
#endif
  {
   self->SetRowSpacing(spacing);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetRowSpacing'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetWordwrap of class  Text3D */
#ifndef TOLUA_DISABLE_tolua_UI_Text3D_SetWordwrap00
static int tolua_UI_Text3D_SetWordwrap00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Text3D",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Text3D* self = (Text3D*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetWordwrap'", NULL);
#endif
  {
   self->SetWordwrap(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetWordwrap'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetWidth of class  Text3D */
#ifndef TOLUA_DISABLE_tolua_UI_Text3D_SetWidth00
static int tolua_UI_Text3D_SetWidth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Text3D",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Text3D* self = (Text3D*)  tolua_tousertype(tolua_S,1,0);
  int width = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetWidth'", NULL);
#endif
  {
   self->SetWidth(width);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetWidth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetColor of class  Text3D */
#ifndef TOLUA_DISABLE_tolua_UI_Text3D_SetColor00
static int tolua_UI_Text3D_SetColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Text3D",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Color",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Text3D* self = (Text3D*)  tolua_tousertype(tolua_S,1,0);
  const Color* color = ((const Color*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetColor'", NULL);
#endif
  {
   self->SetColor(*color);
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

/* method: SetColor of class  Text3D */
#ifndef TOLUA_DISABLE_tolua_UI_Text3D_SetColor01
static int tolua_UI_Text3D_SetColor01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Text3D",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const Color",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Text3D* self = (Text3D*)  tolua_tousertype(tolua_S,1,0);
  Corner corner = ((Corner) (int)  tolua_tonumber(tolua_S,2,0));
  const Color* color = ((const Color*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetColor'", NULL);
#endif
  {
   self->SetColor(corner,*color);
  }
 }
 return 0;
tolua_lerror:
 return tolua_UI_Text3D_SetColor00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetOpacity of class  Text3D */
#ifndef TOLUA_DISABLE_tolua_UI_Text3D_SetOpacity00
static int tolua_UI_Text3D_SetOpacity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Text3D",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Text3D* self = (Text3D*)  tolua_tousertype(tolua_S,1,0);
  float opacity = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetOpacity'", NULL);
#endif
  {
   self->SetOpacity(opacity);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetOpacity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFaceCamera of class  Text3D */
#ifndef TOLUA_DISABLE_tolua_UI_Text3D_SetFaceCamera00
static int tolua_UI_Text3D_SetFaceCamera00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Text3D",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Text3D* self = (Text3D*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFaceCamera'", NULL);
#endif
  {
   self->SetFaceCamera(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFaceCamera'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFont of class  Text3D */
#ifndef TOLUA_DISABLE_tolua_UI_Text3D_GetFont00
static int tolua_UI_Text3D_GetFont00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Text3D",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Text3D* self = (const Text3D*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFont'", NULL);
#endif
  {
   Font* tolua_ret = (Font*)  self->GetFont();
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

/* method: GetMaterial of class  Text3D */
#ifndef TOLUA_DISABLE_tolua_UI_Text3D_GetMaterial00
static int tolua_UI_Text3D_GetMaterial00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Text3D",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Text3D* self = (const Text3D*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMaterial'", NULL);
#endif
  {
   Material* tolua_ret = (Material*)  self->GetMaterial();
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

/* method: GetFontSize of class  Text3D */
#ifndef TOLUA_DISABLE_tolua_UI_Text3D_GetFontSize00
static int tolua_UI_Text3D_GetFontSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Text3D",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Text3D* self = (const Text3D*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFontSize'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetFontSize();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFontSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetText of class  Text3D */
#ifndef TOLUA_DISABLE_tolua_UI_Text3D_GetText00
static int tolua_UI_Text3D_GetText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Text3D",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Text3D* self = (const Text3D*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetText'", NULL);
#endif
  {
   const String& tolua_ret = (const String&)  self->GetText();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const String");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTextAlignment of class  Text3D */
#ifndef TOLUA_DISABLE_tolua_UI_Text3D_GetTextAlignment00
static int tolua_UI_Text3D_GetTextAlignment00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Text3D",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Text3D* self = (const Text3D*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTextAlignment'", NULL);
#endif
  {
   HorizontalAlignment tolua_ret = (HorizontalAlignment)  self->GetTextAlignment();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTextAlignment'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetHorizontalAlignment of class  Text3D */
#ifndef TOLUA_DISABLE_tolua_UI_Text3D_GetHorizontalAlignment00
static int tolua_UI_Text3D_GetHorizontalAlignment00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Text3D",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Text3D* self = (const Text3D*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetHorizontalAlignment'", NULL);
#endif
  {
   HorizontalAlignment tolua_ret = (HorizontalAlignment)  self->GetHorizontalAlignment();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetHorizontalAlignment'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetVerticalAlignment of class  Text3D */
#ifndef TOLUA_DISABLE_tolua_UI_Text3D_GetVerticalAlignment00
static int tolua_UI_Text3D_GetVerticalAlignment00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Text3D",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Text3D* self = (const Text3D*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetVerticalAlignment'", NULL);
#endif
  {
   VerticalAlignment tolua_ret = (VerticalAlignment)  self->GetVerticalAlignment();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetVerticalAlignment'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRowSpacing of class  Text3D */
#ifndef TOLUA_DISABLE_tolua_UI_Text3D_GetRowSpacing00
static int tolua_UI_Text3D_GetRowSpacing00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Text3D",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Text3D* self = (const Text3D*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRowSpacing'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetRowSpacing();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRowSpacing'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetWordwrap of class  Text3D */
#ifndef TOLUA_DISABLE_tolua_UI_Text3D_GetWordwrap00
static int tolua_UI_Text3D_GetWordwrap00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Text3D",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Text3D* self = (const Text3D*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetWordwrap'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetWordwrap();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetWordwrap'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetWidth of class  Text3D */
#ifndef TOLUA_DISABLE_tolua_UI_Text3D_GetWidth00
static int tolua_UI_Text3D_GetWidth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Text3D",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Text3D* self = (const Text3D*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetRowHeight of class  Text3D */
#ifndef TOLUA_DISABLE_tolua_UI_Text3D_GetRowHeight00
static int tolua_UI_Text3D_GetRowHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Text3D",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Text3D* self = (const Text3D*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRowHeight'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetRowHeight();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRowHeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNumRows of class  Text3D */
#ifndef TOLUA_DISABLE_tolua_UI_Text3D_GetNumRows00
static int tolua_UI_Text3D_GetNumRows00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Text3D",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Text3D* self = (const Text3D*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetRowWidths of class  Text3D */
#ifndef TOLUA_DISABLE_tolua_UI_Text3D_GetRowWidths00
static int tolua_UI_Text3D_GetRowWidths00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Text3D",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Text3D* self = (const Text3D*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRowWidths'", NULL);
#endif
  {
   const PODVector<int>& tolua_ret = (const PODVector<int>&)  self->GetRowWidths();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const PODVector<int>");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRowWidths'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetColor of class  Text3D */
#ifndef TOLUA_DISABLE_tolua_UI_Text3D_GetColor00
static int tolua_UI_Text3D_GetColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Text3D",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Text3D* self = (const Text3D*)  tolua_tousertype(tolua_S,1,0);
  Corner corner = ((Corner) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetColor'", NULL);
#endif
  {
   const Color& tolua_ret = (const Color&)  self->GetColor(corner);
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

/* method: GetOpacity of class  Text3D */
#ifndef TOLUA_DISABLE_tolua_UI_Text3D_GetOpacity00
static int tolua_UI_Text3D_GetOpacity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Text3D",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Text3D* self = (const Text3D*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetOpacity'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetOpacity();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetOpacity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFaceCamera of class  Text3D */
#ifndef TOLUA_DISABLE_tolua_UI_Text3D_GetFaceCamera00
static int tolua_UI_Text3D_GetFaceCamera00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Text3D",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Text3D* self = (const Text3D*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFaceCamera'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetFaceCamera();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFaceCamera'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetCursor of class  UI */
#ifndef TOLUA_DISABLE_tolua_UI_UI_SetCursor00
static int tolua_UI_UI_SetCursor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UI",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Cursor",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UI* self = (UI*)  tolua_tousertype(tolua_S,1,0);
  Cursor* cursor = ((Cursor*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetCursor'", NULL);
#endif
  {
   self->SetCursor(cursor);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetCursor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFocusElement of class  UI */
#ifndef TOLUA_DISABLE_tolua_UI_UI_SetFocusElement00
static int tolua_UI_UI_SetFocusElement00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UI",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UI* self = (UI*)  tolua_tousertype(tolua_S,1,0);
  UIElement* element = ((UIElement*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFocusElement'", NULL);
#endif
  {
   self->SetFocusElement(element);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFocusElement'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetModalElement of class  UI */
#ifndef TOLUA_DISABLE_tolua_UI_UI_SetModalElement00
static int tolua_UI_UI_SetModalElement00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UI",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UIElement",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UI* self = (UI*)  tolua_tousertype(tolua_S,1,0);
  UIElement* modalElement = ((UIElement*)  tolua_tousertype(tolua_S,2,0));
  bool enable = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetModalElement'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SetModalElement(modalElement,enable);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetModalElement'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Clear of class  UI */
#ifndef TOLUA_DISABLE_tolua_UI_UI_Clear00
static int tolua_UI_UI_Clear00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UI",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UI* self = (UI*)  tolua_tousertype(tolua_S,1,0);
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

/* method: Update of class  UI */
#ifndef TOLUA_DISABLE_tolua_UI_UI_Update00
static int tolua_UI_UI_Update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UI",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UI* self = (UI*)  tolua_tousertype(tolua_S,1,0);
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

/* method: RenderUpdate of class  UI */
#ifndef TOLUA_DISABLE_tolua_UI_UI_RenderUpdate00
static int tolua_UI_UI_RenderUpdate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UI",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UI* self = (UI*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RenderUpdate'", NULL);
#endif
  {
   self->RenderUpdate();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RenderUpdate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Render of class  UI */
#ifndef TOLUA_DISABLE_tolua_UI_UI_Render00
static int tolua_UI_UI_Render00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UI",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UI* self = (UI*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Render'", NULL);
#endif
  {
   self->Render();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Render'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DebugDraw of class  UI */
#ifndef TOLUA_DISABLE_tolua_UI_UI_DebugDraw00
static int tolua_UI_UI_DebugDraw00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UI",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UI* self = (UI*)  tolua_tousertype(tolua_S,1,0);
  UIElement* element = ((UIElement*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DebugDraw'", NULL);
#endif
  {
   self->DebugDraw(element);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DebugDraw'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SaveLayout of class  UI */
#ifndef TOLUA_DISABLE_tolua_UI_UI_SaveLayout00
static int tolua_UI_UI_SaveLayout00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UI",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"Serializer",0,&tolua_err)) ||
     !tolua_isusertype(tolua_S,3,"UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UI* self = (UI*)  tolua_tousertype(tolua_S,1,0);
  Serializer* dest = ((Serializer*)  tolua_tousertype(tolua_S,2,0));
  UIElement* element = ((UIElement*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SaveLayout'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SaveLayout(*dest,element);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SaveLayout'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetClipBoardText of class  UI */
#ifndef TOLUA_DISABLE_tolua_UI_UI_SetClipBoardText00
static int tolua_UI_UI_SetClipBoardText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UI",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UI* self = (UI*)  tolua_tousertype(tolua_S,1,0);
  const String* text = ((const String*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetClipBoardText'", NULL);
#endif
  {
   self->SetClipBoardText(*text);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetClipBoardText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetNonFocusedMouseWheel of class  UI */
#ifndef TOLUA_DISABLE_tolua_UI_UI_SetNonFocusedMouseWheel00
static int tolua_UI_UI_SetNonFocusedMouseWheel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UI",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UI* self = (UI*)  tolua_tousertype(tolua_S,1,0);
  bool nonFocusedMouseWheel = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetNonFocusedMouseWheel'", NULL);
#endif
  {
   self->SetNonFocusedMouseWheel(nonFocusedMouseWheel);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetNonFocusedMouseWheel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRoot of class  UI */
#ifndef TOLUA_DISABLE_tolua_UI_UI_GetRoot00
static int tolua_UI_UI_GetRoot00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UI",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UI* self = (const UI*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRoot'", NULL);
#endif
  {
   UIElement* tolua_ret = (UIElement*)  self->GetRoot();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIElement");
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

/* method: GetRootModalElement of class  UI */
#ifndef TOLUA_DISABLE_tolua_UI_UI_GetRootModalElement00
static int tolua_UI_UI_GetRootModalElement00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UI",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UI* self = (const UI*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRootModalElement'", NULL);
#endif
  {
   UIElement* tolua_ret = (UIElement*)  self->GetRootModalElement();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIElement");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRootModalElement'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCursor of class  UI */
#ifndef TOLUA_DISABLE_tolua_UI_UI_GetCursor00
static int tolua_UI_UI_GetCursor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UI",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UI* self = (const UI*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCursor'", NULL);
#endif
  {
   Cursor* tolua_ret = (Cursor*)  self->GetCursor();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Cursor");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCursor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetElementAt of class  UI */
#ifndef TOLUA_DISABLE_tolua_UI_UI_GetElementAt00
static int tolua_UI_UI_GetElementAt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UI",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const IntVector2",0,&tolua_err)) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UI* self = (UI*)  tolua_tousertype(tolua_S,1,0);
  const IntVector2* position = ((const IntVector2*)  tolua_tousertype(tolua_S,2,0));
  bool enabledOnly = ((bool)  tolua_toboolean(tolua_S,3,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetElementAt'", NULL);
#endif
  {
   UIElement* tolua_ret = (UIElement*)  self->GetElementAt(*position,enabledOnly);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIElement");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetElementAt'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetElementAt of class  UI */
#ifndef TOLUA_DISABLE_tolua_UI_UI_GetElementAt01
static int tolua_UI_UI_GetElementAt01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UI",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  UI* self = (UI*)  tolua_tousertype(tolua_S,1,0);
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
  bool enabledOnly = ((bool)  tolua_toboolean(tolua_S,4,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetElementAt'", NULL);
#endif
  {
   UIElement* tolua_ret = (UIElement*)  self->GetElementAt(x,y,enabledOnly);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIElement");
  }
 }
 return 1;
tolua_lerror:
 return tolua_UI_UI_GetElementAt00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFocusElement of class  UI */
#ifndef TOLUA_DISABLE_tolua_UI_UI_GetFocusElement00
static int tolua_UI_UI_GetFocusElement00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UI",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UI* self = (const UI*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFocusElement'", NULL);
#endif
  {
   UIElement* tolua_ret = (UIElement*)  self->GetFocusElement();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIElement");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFocusElement'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFrontElement of class  UI */
#ifndef TOLUA_DISABLE_tolua_UI_UI_GetFrontElement00
static int tolua_UI_UI_GetFrontElement00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UI",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UI* self = (const UI*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFrontElement'", NULL);
#endif
  {
   UIElement* tolua_ret = (UIElement*)  self->GetFrontElement();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIElement");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFrontElement'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCursorPosition of class  UI */
#ifndef TOLUA_DISABLE_tolua_UI_UI_GetCursorPosition00
static int tolua_UI_UI_GetCursorPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UI",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UI* self = (const UI*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCursorPosition'", NULL);
#endif
  {
   IntVector2 tolua_ret = (IntVector2)  self->GetCursorPosition();
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
 tolua_error(tolua_S,"#ferror in function 'GetCursorPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetClipBoardText of class  UI */
#ifndef TOLUA_DISABLE_tolua_UI_UI_GetClipBoardText00
static int tolua_UI_UI_GetClipBoardText00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UI",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UI* self = (const UI*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetClipBoardText'", NULL);
#endif
  {
   const String& tolua_ret = (const String&)  self->GetClipBoardText();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const String");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetClipBoardText'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsNonFocusedMouseWheel of class  UI */
#ifndef TOLUA_DISABLE_tolua_UI_UI_IsNonFocusedMouseWheel00
static int tolua_UI_UI_IsNonFocusedMouseWheel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UI",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UI* self = (const UI*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsNonFocusedMouseWheel'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsNonFocusedMouseWheel();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsNonFocusedMouseWheel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: HasModalElement of class  UI */
#ifndef TOLUA_DISABLE_tolua_UI_UI_HasModalElement00
static int tolua_UI_UI_HasModalElement00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UI",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UI* self = (const UI*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'HasModalElement'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->HasModalElement();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'HasModalElement'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GetUI */
#ifndef TOLUA_DISABLE_tolua_UI_GetUI00
static int tolua_UI_GetUI00(lua_State* tolua_S)
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
   UI* tolua_ret = (UI*)  GetUI();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UI");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetUI'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: DD_DISABLED */
#ifndef TOLUA_DISABLE_tolua_get_DD_DISABLED
static int tolua_get_DD_DISABLED(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)DD_DISABLED);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: DD_SOURCE */
#ifndef TOLUA_DISABLE_tolua_get_DD_SOURCE
static int tolua_get_DD_SOURCE(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)DD_SOURCE);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: DD_TARGET */
#ifndef TOLUA_DISABLE_tolua_get_DD_TARGET
static int tolua_get_DD_TARGET(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)DD_TARGET);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: DD_SOURCE_AND_TARGET */
#ifndef TOLUA_DISABLE_tolua_get_DD_SOURCE_AND_TARGET
static int tolua_get_DD_SOURCE_AND_TARGET(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)DD_SOURCE_AND_TARGET);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetName of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_SetName00
static int tolua_UI_UIElement_SetName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
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

/* method: SetPosition of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_SetPosition00
static int tolua_UI_UIElement_SetPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const IntVector2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  const IntVector2* position = ((const IntVector2*)  tolua_tousertype(tolua_S,2,0));
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

/* method: SetPosition of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_SetPosition01
static int tolua_UI_UIElement_SetPosition01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int y = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetPosition'", NULL);
#endif
  {
   self->SetPosition(x,y);
  }
 }
 return 0;
tolua_lerror:
 return tolua_UI_UIElement_SetPosition00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetSize of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_SetSize00
static int tolua_UI_UIElement_SetSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const IntVector2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  const IntVector2* size = ((const IntVector2*)  tolua_tousertype(tolua_S,2,0));
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

/* method: SetSize of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_SetSize01
static int tolua_UI_UIElement_SetSize01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  int width = ((int)  tolua_tonumber(tolua_S,2,0));
  int height = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetSize'", NULL);
#endif
  {
   self->SetSize(width,height);
  }
 }
 return 0;
tolua_lerror:
 return tolua_UI_UIElement_SetSize00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetWidth of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_SetWidth00
static int tolua_UI_UIElement_SetWidth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  int width = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetWidth'", NULL);
#endif
  {
   self->SetWidth(width);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetWidth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetHeight of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_SetHeight00
static int tolua_UI_UIElement_SetHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  int height = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetHeight'", NULL);
#endif
  {
   self->SetHeight(height);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetHeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMinSize of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_SetMinSize00
static int tolua_UI_UIElement_SetMinSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const IntVector2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  const IntVector2* minSize = ((const IntVector2*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMinSize'", NULL);
#endif
  {
   self->SetMinSize(*minSize);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMinSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMinSize of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_SetMinSize01
static int tolua_UI_UIElement_SetMinSize01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  int width = ((int)  tolua_tonumber(tolua_S,2,0));
  int height = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMinSize'", NULL);
#endif
  {
   self->SetMinSize(width,height);
  }
 }
 return 0;
tolua_lerror:
 return tolua_UI_UIElement_SetMinSize00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMinWidth of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_SetMinWidth00
static int tolua_UI_UIElement_SetMinWidth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  int width = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMinWidth'", NULL);
#endif
  {
   self->SetMinWidth(width);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMinWidth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMinHeight of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_SetMinHeight00
static int tolua_UI_UIElement_SetMinHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  int height = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMinHeight'", NULL);
#endif
  {
   self->SetMinHeight(height);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMinHeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMaxSize of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_SetMaxSize00
static int tolua_UI_UIElement_SetMaxSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const IntVector2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  const IntVector2* maxSize = ((const IntVector2*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMaxSize'", NULL);
#endif
  {
   self->SetMaxSize(*maxSize);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMaxSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMaxSize of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_SetMaxSize01
static int tolua_UI_UIElement_SetMaxSize01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  int width = ((int)  tolua_tonumber(tolua_S,2,0));
  int height = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMaxSize'", NULL);
#endif
  {
   self->SetMaxSize(width,height);
  }
 }
 return 0;
tolua_lerror:
 return tolua_UI_UIElement_SetMaxSize00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMaxWidth of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_SetMaxWidth00
static int tolua_UI_UIElement_SetMaxWidth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  int width = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMaxWidth'", NULL);
#endif
  {
   self->SetMaxWidth(width);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMaxWidth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMaxHeight of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_SetMaxHeight00
static int tolua_UI_UIElement_SetMaxHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  int height = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMaxHeight'", NULL);
#endif
  {
   self->SetMaxHeight(height);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMaxHeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFixedSize of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_SetFixedSize00
static int tolua_UI_UIElement_SetFixedSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const IntVector2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  const IntVector2* size = ((const IntVector2*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFixedSize'", NULL);
#endif
  {
   self->SetFixedSize(*size);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFixedSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFixedSize of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_SetFixedSize01
static int tolua_UI_UIElement_SetFixedSize01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  int width = ((int)  tolua_tonumber(tolua_S,2,0));
  int height = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFixedSize'", NULL);
#endif
  {
   self->SetFixedSize(width,height);
  }
 }
 return 0;
tolua_lerror:
 return tolua_UI_UIElement_SetFixedSize00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFixedWidth of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_SetFixedWidth00
static int tolua_UI_UIElement_SetFixedWidth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  int width = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFixedWidth'", NULL);
#endif
  {
   self->SetFixedWidth(width);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFixedWidth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFixedHeight of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_SetFixedHeight00
static int tolua_UI_UIElement_SetFixedHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  int height = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFixedHeight'", NULL);
#endif
  {
   self->SetFixedHeight(height);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFixedHeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetAlignment of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_SetAlignment00
static int tolua_UI_UIElement_SetAlignment00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  HorizontalAlignment hAlign = ((HorizontalAlignment) (int)  tolua_tonumber(tolua_S,2,0));
  VerticalAlignment vAlign = ((VerticalAlignment) (int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetAlignment'", NULL);
#endif
  {
   self->SetAlignment(hAlign,vAlign);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetAlignment'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetHorizontalAlignment of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_SetHorizontalAlignment00
static int tolua_UI_UIElement_SetHorizontalAlignment00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  HorizontalAlignment align = ((HorizontalAlignment) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetHorizontalAlignment'", NULL);
#endif
  {
   self->SetHorizontalAlignment(align);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetHorizontalAlignment'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetVerticalAlignment of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_SetVerticalAlignment00
static int tolua_UI_UIElement_SetVerticalAlignment00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  VerticalAlignment align = ((VerticalAlignment) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetVerticalAlignment'", NULL);
#endif
  {
   self->SetVerticalAlignment(align);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetVerticalAlignment'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetClipBorder of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_SetClipBorder00
static int tolua_UI_UIElement_SetClipBorder00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const IntRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  const IntRect* rect = ((const IntRect*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetClipBorder'", NULL);
#endif
  {
   self->SetClipBorder(*rect);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetClipBorder'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetColor of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_SetColor00
static int tolua_UI_UIElement_SetColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Color",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  const Color* color = ((const Color*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetColor'", NULL);
#endif
  {
   self->SetColor(*color);
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

/* method: SetColor of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_SetColor01
static int tolua_UI_UIElement_SetColor01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const Color",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  Corner corner = ((Corner) (int)  tolua_tonumber(tolua_S,2,0));
  const Color* color = ((const Color*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetColor'", NULL);
#endif
  {
   self->SetColor(corner,*color);
  }
 }
 return 0;
tolua_lerror:
 return tolua_UI_UIElement_SetColor00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetPriority of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_SetPriority00
static int tolua_UI_UIElement_SetPriority00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  int priority = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetPriority'", NULL);
#endif
  {
   self->SetPriority(priority);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetPriority'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetOpacity of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_SetOpacity00
static int tolua_UI_UIElement_SetOpacity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  float opacity = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetOpacity'", NULL);
#endif
  {
   self->SetOpacity(opacity);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetOpacity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetBringToFront of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_SetBringToFront00
static int tolua_UI_UIElement_SetBringToFront00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetBringToFront'", NULL);
#endif
  {
   self->SetBringToFront(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetBringToFront'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetBringToBack of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_SetBringToBack00
static int tolua_UI_UIElement_SetBringToBack00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetBringToBack'", NULL);
#endif
  {
   self->SetBringToBack(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetBringToBack'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetClipChildren of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_SetClipChildren00
static int tolua_UI_UIElement_SetClipChildren00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetClipChildren'", NULL);
#endif
  {
   self->SetClipChildren(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetClipChildren'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetSortChildren of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_SetSortChildren00
static int tolua_UI_UIElement_SetSortChildren00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetSortChildren'", NULL);
#endif
  {
   self->SetSortChildren(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetSortChildren'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetUseDerivedOpacity of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_SetUseDerivedOpacity00
static int tolua_UI_UIElement_SetUseDerivedOpacity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetUseDerivedOpacity'", NULL);
#endif
  {
   self->SetUseDerivedOpacity(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetUseDerivedOpacity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetEnabled of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_SetEnabled00
static int tolua_UI_UIElement_SetEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
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

/* method: SetFocus of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_SetFocus00
static int tolua_UI_UIElement_SetFocus00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFocus'", NULL);
#endif
  {
   self->SetFocus(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFocus'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetSelected of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_SetSelected00
static int tolua_UI_UIElement_SetSelected00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetSelected'", NULL);
#endif
  {
   self->SetSelected(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetSelected'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetVisible of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_SetVisible00
static int tolua_UI_UIElement_SetVisible00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
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

/* method: SetFocusMode of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_SetFocusMode00
static int tolua_UI_UIElement_SetFocusMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  FocusMode mode = ((FocusMode) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFocusMode'", NULL);
#endif
  {
   self->SetFocusMode(mode);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFocusMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetDragDropMode of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_SetDragDropMode00
static int tolua_UI_UIElement_SetDragDropMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  unsigned mode = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetDragDropMode'", NULL);
#endif
  {
   self->SetDragDropMode(mode);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetDragDropMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetStyle of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_SetStyle00
static int tolua_UI_UIElement_SetStyle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isusertype(tolua_S,3,"XMLFile",1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  const String* styleName = ((const String*)  tolua_tousertype(tolua_S,2,0));
  XMLFile* file = ((XMLFile*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetStyle'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SetStyle(*styleName,file);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetStyle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetStyle of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_SetStyle01
static int tolua_UI_UIElement_SetStyle01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const XMLElement",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  const XMLElement* element = ((const XMLElement*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetStyle'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SetStyle(*element);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_UI_UIElement_SetStyle00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetStyleAuto of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_SetStyleAuto00
static int tolua_UI_UIElement_SetStyleAuto00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"XMLFile",1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  XMLFile* file = ((XMLFile*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetStyleAuto'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SetStyleAuto(file);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetStyleAuto'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetDefaultStyle of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_SetDefaultStyle00
static int tolua_UI_UIElement_SetDefaultStyle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"XMLFile",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
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

/* method: SetLayout of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_SetLayout00
static int tolua_UI_UIElement_SetLayout00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  LayoutMode mode = ((LayoutMode) (int)  tolua_tonumber(tolua_S,2,0));
  int spacing = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLayout'", NULL);
#endif
  {
   self->SetLayout(mode,spacing);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLayout'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetLayout of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_SetLayout01
static int tolua_UI_UIElement_SetLayout01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"const IntRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  LayoutMode mode = ((LayoutMode) (int)  tolua_tonumber(tolua_S,2,0));
  int spacing = ((int)  tolua_tonumber(tolua_S,3,0));
  const IntRect* border = ((const IntRect*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLayout'", NULL);
#endif
  {
   self->SetLayout(mode,spacing,*border);
  }
 }
 return 0;
tolua_lerror:
 return tolua_UI_UIElement_SetLayout00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetLayoutMode of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_SetLayoutMode00
static int tolua_UI_UIElement_SetLayoutMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  LayoutMode mode = ((LayoutMode) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLayoutMode'", NULL);
#endif
  {
   self->SetLayoutMode(mode);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLayoutMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetLayoutSpacing of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_SetLayoutSpacing00
static int tolua_UI_UIElement_SetLayoutSpacing00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  int spacing = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLayoutSpacing'", NULL);
#endif
  {
   self->SetLayoutSpacing(spacing);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLayoutSpacing'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetLayoutBorder of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_SetLayoutBorder00
static int tolua_UI_UIElement_SetLayoutBorder00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const IntRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  const IntRect* border = ((const IntRect*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLayoutBorder'", NULL);
#endif
  {
   self->SetLayoutBorder(*border);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLayoutBorder'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetIndent of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_SetIndent00
static int tolua_UI_UIElement_SetIndent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  int indent = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetIndent'", NULL);
#endif
  {
   self->SetIndent(indent);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetIndent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetIndentSpacing of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_SetIndentSpacing00
static int tolua_UI_UIElement_SetIndentSpacing00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  int indentSpacing = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetIndentSpacing'", NULL);
#endif
  {
   self->SetIndentSpacing(indentSpacing);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetIndentSpacing'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: UpdateLayout of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_UpdateLayout00
static int tolua_UI_UIElement_UpdateLayout00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'UpdateLayout'", NULL);
#endif
  {
   self->UpdateLayout();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'UpdateLayout'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DisableLayoutUpdate of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_DisableLayoutUpdate00
static int tolua_UI_UIElement_DisableLayoutUpdate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DisableLayoutUpdate'", NULL);
#endif
  {
   self->DisableLayoutUpdate();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DisableLayoutUpdate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: EnableLayoutUpdate of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_EnableLayoutUpdate00
static int tolua_UI_UIElement_EnableLayoutUpdate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'EnableLayoutUpdate'", NULL);
#endif
  {
   self->EnableLayoutUpdate();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'EnableLayoutUpdate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: BringToFront of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_BringToFront00
static int tolua_UI_UIElement_BringToFront00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'BringToFront'", NULL);
#endif
  {
   self->BringToFront();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'BringToFront'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CreateChild of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_CreateChild00
static int tolua_UI_UIElement_CreateChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"ShortStringHash",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  ShortStringHash type = *((ShortStringHash*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CreateChild'", NULL);
#endif
  {
   UIElement* tolua_ret = (UIElement*)  self->CreateChild(type);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIElement");
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

/* method: CreateChild of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_CreateChild01
static int tolua_UI_UIElement_CreateChild01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"ShortStringHash",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const String",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  ShortStringHash type = *((ShortStringHash*)  tolua_tousertype(tolua_S,2,0));
  const String* name = ((const String*)  tolua_tousertype(tolua_S,3,0));
  unsigned index = ((unsigned)  tolua_tonumber(tolua_S,4,M_MAX_UNSIGNED));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CreateChild'", NULL);
#endif
  {
   UIElement* tolua_ret = (UIElement*)  self->CreateChild(type,*name,index);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIElement");
  }
 }
 return 1;
tolua_lerror:
 return tolua_UI_UIElement_CreateChild00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddChild of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_AddChild00
static int tolua_UI_UIElement_AddChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  UIElement* element = ((UIElement*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddChild'", NULL);
#endif
  {
   self->AddChild(element);
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

/* method: InsertChild of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_InsertChild00
static int tolua_UI_UIElement_InsertChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  unsigned index = ((unsigned)  tolua_tonumber(tolua_S,2,0));
  UIElement* element = ((UIElement*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'InsertChild'", NULL);
#endif
  {
   self->InsertChild(index,element);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'InsertChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveChild of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_RemoveChild00
static int tolua_UI_UIElement_RemoveChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UIElement",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  UIElement* element = ((UIElement*)  tolua_tousertype(tolua_S,2,0));
  unsigned index = ((unsigned)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveChild'", NULL);
#endif
  {
   self->RemoveChild(element,index);
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

/* method: RemoveChildAtIndex of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_RemoveChildAtIndex00
static int tolua_UI_UIElement_RemoveChildAtIndex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  unsigned index = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveChildAtIndex'", NULL);
#endif
  {
   self->RemoveChildAtIndex(index);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemoveChildAtIndex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveAllChildren of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_RemoveAllChildren00
static int tolua_UI_UIElement_RemoveAllChildren00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
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

/* method: Remove of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_Remove00
static int tolua_UI_UIElement_Remove00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
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

/* method: FindChild of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_FindChild00
static int tolua_UI_UIElement_FindChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIElement",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIElement* self = (const UIElement*)  tolua_tousertype(tolua_S,1,0);
  UIElement* element = ((UIElement*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FindChild'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->FindChild(element);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FindChild'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetParent of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_SetParent00
static int tolua_UI_UIElement_SetParent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"UIElement",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  UIElement* parent = ((UIElement*)  tolua_tousertype(tolua_S,2,0));
  unsigned index = ((unsigned)  tolua_tonumber(tolua_S,3,M_MAX_UNSIGNED));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetParent'", NULL);
#endif
  {
   self->SetParent(parent,index);
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

/* method: SetVar of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_SetVar00
static int tolua_UI_UIElement_SetVar00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"ShortStringHash",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const Variant",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
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

/* method: SetInternal of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_SetInternal00
static int tolua_UI_UIElement_SetInternal00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetInternal'", NULL);
#endif
  {
   self->SetInternal(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetInternal'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetTraversalMode of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_SetTraversalMode00
static int tolua_UI_UIElement_SetTraversalMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  TraversalMode traversalMode = ((TraversalMode) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetTraversalMode'", NULL);
#endif
  {
   self->SetTraversalMode(traversalMode);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetTraversalMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetElementEventSender of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_SetElementEventSender00
static int tolua_UI_UIElement_SetElementEventSender00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  bool flag = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetElementEventSender'", NULL);
#endif
  {
   self->SetElementEventSender(flag);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetElementEventSender'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetName of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_GetName00
static int tolua_UI_UIElement_GetName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIElement* self = (const UIElement*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetPosition of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_GetPosition00
static int tolua_UI_UIElement_GetPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIElement* self = (const UIElement*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPosition'", NULL);
#endif
  {
   const IntVector2& tolua_ret = (const IntVector2&)  self->GetPosition();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const IntVector2");
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

/* method: GetSize of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_GetSize00
static int tolua_UI_UIElement_GetSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIElement* self = (const UIElement*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSize'", NULL);
#endif
  {
   const IntVector2& tolua_ret = (const IntVector2&)  self->GetSize();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const IntVector2");
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

/* method: GetWidth of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_GetWidth00
static int tolua_UI_UIElement_GetWidth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIElement* self = (const UIElement*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetHeight of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_GetHeight00
static int tolua_UI_UIElement_GetHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIElement* self = (const UIElement*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetMinSize of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_GetMinSize00
static int tolua_UI_UIElement_GetMinSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIElement* self = (const UIElement*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMinSize'", NULL);
#endif
  {
   const IntVector2& tolua_ret = (const IntVector2&)  self->GetMinSize();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const IntVector2");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMinSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMinWidth of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_GetMinWidth00
static int tolua_UI_UIElement_GetMinWidth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIElement* self = (const UIElement*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMinWidth'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetMinWidth();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMinWidth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMinHeight of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_GetMinHeight00
static int tolua_UI_UIElement_GetMinHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIElement* self = (const UIElement*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMinHeight'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetMinHeight();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMinHeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMaxSize of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_GetMaxSize00
static int tolua_UI_UIElement_GetMaxSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIElement* self = (const UIElement*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMaxSize'", NULL);
#endif
  {
   const IntVector2& tolua_ret = (const IntVector2&)  self->GetMaxSize();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const IntVector2");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMaxSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMaxWidth of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_GetMaxWidth00
static int tolua_UI_UIElement_GetMaxWidth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIElement* self = (const UIElement*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMaxWidth'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetMaxWidth();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMaxWidth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMaxHeight of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_GetMaxHeight00
static int tolua_UI_UIElement_GetMaxHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIElement* self = (const UIElement*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMaxHeight'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetMaxHeight();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMaxHeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsFixedSize of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_IsFixedSize00
static int tolua_UI_UIElement_IsFixedSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIElement* self = (const UIElement*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsFixedSize'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsFixedSize();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsFixedSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsFixedWidth of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_IsFixedWidth00
static int tolua_UI_UIElement_IsFixedWidth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIElement* self = (const UIElement*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsFixedWidth'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsFixedWidth();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsFixedWidth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsFixedHeight of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_IsFixedHeight00
static int tolua_UI_UIElement_IsFixedHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIElement* self = (const UIElement*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsFixedHeight'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsFixedHeight();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsFixedHeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetChildOffset of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_GetChildOffset00
static int tolua_UI_UIElement_GetChildOffset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIElement* self = (const UIElement*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetChildOffset'", NULL);
#endif
  {
   const IntVector2& tolua_ret = (const IntVector2&)  self->GetChildOffset();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const IntVector2");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetChildOffset'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetHorizontalAlignment of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_GetHorizontalAlignment00
static int tolua_UI_UIElement_GetHorizontalAlignment00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIElement* self = (const UIElement*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetHorizontalAlignment'", NULL);
#endif
  {
   HorizontalAlignment tolua_ret = (HorizontalAlignment)  self->GetHorizontalAlignment();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetHorizontalAlignment'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetVerticalAlignment of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_GetVerticalAlignment00
static int tolua_UI_UIElement_GetVerticalAlignment00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIElement* self = (const UIElement*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetVerticalAlignment'", NULL);
#endif
  {
   VerticalAlignment tolua_ret = (VerticalAlignment)  self->GetVerticalAlignment();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetVerticalAlignment'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetClipBorder of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_GetClipBorder00
static int tolua_UI_UIElement_GetClipBorder00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIElement* self = (const UIElement*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetClipBorder'", NULL);
#endif
  {
   const IntRect& tolua_ret = (const IntRect&)  self->GetClipBorder();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const IntRect");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetClipBorder'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetColor of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_GetColor00
static int tolua_UI_UIElement_GetColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIElement",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIElement* self = (const UIElement*)  tolua_tousertype(tolua_S,1,0);
  Corner corner = ((Corner) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetColor'", NULL);
#endif
  {
   const Color& tolua_ret = (const Color&)  self->GetColor(corner);
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

/* method: GetPriority of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_GetPriority00
static int tolua_UI_UIElement_GetPriority00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIElement* self = (const UIElement*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPriority'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetPriority();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPriority'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetOpacity of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_GetOpacity00
static int tolua_UI_UIElement_GetOpacity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIElement* self = (const UIElement*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetOpacity'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetOpacity();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetOpacity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetDerivedOpacity of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_GetDerivedOpacity00
static int tolua_UI_UIElement_GetDerivedOpacity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIElement* self = (const UIElement*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetDerivedOpacity'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetDerivedOpacity();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDerivedOpacity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetBringToFront of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_GetBringToFront00
static int tolua_UI_UIElement_GetBringToFront00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIElement* self = (const UIElement*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetBringToFront'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetBringToFront();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetBringToFront'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetBringToBack of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_GetBringToBack00
static int tolua_UI_UIElement_GetBringToBack00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIElement* self = (const UIElement*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetBringToBack'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetBringToBack();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetBringToBack'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetClipChildren of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_GetClipChildren00
static int tolua_UI_UIElement_GetClipChildren00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIElement* self = (const UIElement*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetClipChildren'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetClipChildren();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetClipChildren'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSortChildren of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_GetSortChildren00
static int tolua_UI_UIElement_GetSortChildren00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIElement* self = (const UIElement*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSortChildren'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetSortChildren();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSortChildren'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetUseDerivedOpacity of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_GetUseDerivedOpacity00
static int tolua_UI_UIElement_GetUseDerivedOpacity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIElement* self = (const UIElement*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetUseDerivedOpacity'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetUseDerivedOpacity();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetUseDerivedOpacity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: HasFocus of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_HasFocus00
static int tolua_UI_UIElement_HasFocus00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIElement* self = (const UIElement*)  tolua_tousertype(tolua_S,1,0);
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

/* method: IsEnabled of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_IsEnabled00
static int tolua_UI_UIElement_IsEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIElement* self = (const UIElement*)  tolua_tousertype(tolua_S,1,0);
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

/* method: IsSelected of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_IsSelected00
static int tolua_UI_UIElement_IsSelected00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIElement* self = (const UIElement*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsSelected'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsSelected();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsSelected'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsVisible of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_IsVisible00
static int tolua_UI_UIElement_IsVisible00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIElement* self = (const UIElement*)  tolua_tousertype(tolua_S,1,0);
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

/* method: IsHovering of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_IsHovering00
static int tolua_UI_UIElement_IsHovering00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIElement* self = (const UIElement*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsHovering'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsHovering();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsHovering'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsInternal of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_IsInternal00
static int tolua_UI_UIElement_IsInternal00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIElement* self = (const UIElement*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsInternal'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsInternal();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsInternal'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: HasColorGradient of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_HasColorGradient00
static int tolua_UI_UIElement_HasColorGradient00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIElement* self = (const UIElement*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'HasColorGradient'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->HasColorGradient();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'HasColorGradient'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFocusMode of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_GetFocusMode00
static int tolua_UI_UIElement_GetFocusMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIElement* self = (const UIElement*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFocusMode'", NULL);
#endif
  {
   FocusMode tolua_ret = (FocusMode)  self->GetFocusMode();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFocusMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetDragDropMode of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_GetDragDropMode00
static int tolua_UI_UIElement_GetDragDropMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIElement* self = (const UIElement*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetDragDropMode'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetDragDropMode();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDragDropMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAppliedStyle of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_GetAppliedStyle00
static int tolua_UI_UIElement_GetAppliedStyle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIElement* self = (const UIElement*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAppliedStyle'", NULL);
#endif
  {
   const String& tolua_ret = (const String&)  self->GetAppliedStyle();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const String");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAppliedStyle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetDefaultStyle of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_GetDefaultStyle00
static int tolua_UI_UIElement_GetDefaultStyle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIElement",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIElement* self = (const UIElement*)  tolua_tousertype(tolua_S,1,0);
  bool recursiveUp = ((bool)  tolua_toboolean(tolua_S,2,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetDefaultStyle'", NULL);
#endif
  {
   XMLFile* tolua_ret = (XMLFile*)  self->GetDefaultStyle(recursiveUp);
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

/* method: GetLayoutMode of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_GetLayoutMode00
static int tolua_UI_UIElement_GetLayoutMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIElement* self = (const UIElement*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLayoutMode'", NULL);
#endif
  {
   LayoutMode tolua_ret = (LayoutMode)  self->GetLayoutMode();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLayoutMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLayoutSpacing of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_GetLayoutSpacing00
static int tolua_UI_UIElement_GetLayoutSpacing00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIElement* self = (const UIElement*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLayoutSpacing'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetLayoutSpacing();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLayoutSpacing'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLayoutBorder of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_GetLayoutBorder00
static int tolua_UI_UIElement_GetLayoutBorder00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIElement* self = (const UIElement*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLayoutBorder'", NULL);
#endif
  {
   const IntRect& tolua_ret = (const IntRect&)  self->GetLayoutBorder();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const IntRect");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLayoutBorder'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNumChildren of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_GetNumChildren00
static int tolua_UI_UIElement_GetNumChildren00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIElement",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIElement* self = (const UIElement*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetChild of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_GetChild00
static int tolua_UI_UIElement_GetChild00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIElement",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIElement* self = (const UIElement*)  tolua_tousertype(tolua_S,1,0);
  unsigned index = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetChild'", NULL);
#endif
  {
   UIElement* tolua_ret = (UIElement*)  self->GetChild(index);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIElement");
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

/* method: GetChild of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_GetChild01
static int tolua_UI_UIElement_GetChild01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIElement",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const UIElement* self = (const UIElement*)  tolua_tousertype(tolua_S,1,0);
  const String* name = ((const String*)  tolua_tousertype(tolua_S,2,0));
  bool recursive = ((bool)  tolua_toboolean(tolua_S,3,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetChild'", NULL);
#endif
  {
   UIElement* tolua_ret = (UIElement*)  self->GetChild(*name,recursive);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIElement");
  }
 }
 return 1;
tolua_lerror:
 return tolua_UI_UIElement_GetChild00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetChild of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_GetChild02
static int tolua_UI_UIElement_GetChild02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIElement",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ShortStringHash",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const UIElement* self = (const UIElement*)  tolua_tousertype(tolua_S,1,0);
  const ShortStringHash* key = ((const ShortStringHash*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetChild'", NULL);
#endif
  {
   UIElement* tolua_ret = (UIElement*)  self->GetChild(*key);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIElement");
  }
 }
 return 1;
tolua_lerror:
 return tolua_UI_UIElement_GetChild01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetChild of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_GetChild03
static int tolua_UI_UIElement_GetChild03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIElement",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ShortStringHash",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const Variant",0,&tolua_err)) ||
     !tolua_isboolean(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const UIElement* self = (const UIElement*)  tolua_tousertype(tolua_S,1,0);
  const ShortStringHash* key = ((const ShortStringHash*)  tolua_tousertype(tolua_S,2,0));
  const Variant* value = ((const Variant*)  tolua_tousertype(tolua_S,3,0));
  bool recursive = ((bool)  tolua_toboolean(tolua_S,4,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetChild'", NULL);
#endif
  {
   UIElement* tolua_ret = (UIElement*)  self->GetChild(*key,*value,recursive);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIElement");
  }
 }
 return 1;
tolua_lerror:
 return tolua_UI_UIElement_GetChild02(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetParent of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_GetParent00
static int tolua_UI_UIElement_GetParent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIElement* self = (const UIElement*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetParent'", NULL);
#endif
  {
   UIElement* tolua_ret = (UIElement*)  self->GetParent();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIElement");
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

/* method: GetRoot of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_GetRoot00
static int tolua_UI_UIElement_GetRoot00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIElement* self = (const UIElement*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRoot'", NULL);
#endif
  {
   UIElement* tolua_ret = (UIElement*)  self->GetRoot();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIElement");
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

/* method: GetDerivedColor of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_GetDerivedColor00
static int tolua_UI_UIElement_GetDerivedColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIElement* self = (const UIElement*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetDerivedColor'", NULL);
#endif
  {
   const Color& tolua_ret = (const Color&)  self->GetDerivedColor();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Color");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDerivedColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ScreenToElement of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_ScreenToElement00
static int tolua_UI_UIElement_ScreenToElement00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const IntVector2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  const IntVector2* screenPosition = ((const IntVector2*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ScreenToElement'", NULL);
#endif
  {
   IntVector2 tolua_ret = (IntVector2)  self->ScreenToElement(*screenPosition);
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
 tolua_error(tolua_S,"#ferror in function 'ScreenToElement'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ElementToScreen of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_ElementToScreen00
static int tolua_UI_UIElement_ElementToScreen00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const IntVector2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  const IntVector2* position = ((const IntVector2*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ElementToScreen'", NULL);
#endif
  {
   IntVector2 tolua_ret = (IntVector2)  self->ElementToScreen(*position);
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
 tolua_error(tolua_S,"#ferror in function 'ElementToScreen'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsInside of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_IsInside00
static int tolua_UI_UIElement_IsInside00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"IntVector2",0,&tolua_err)) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  IntVector2 position = *((IntVector2*)  tolua_tousertype(tolua_S,2,0));
  bool isScreen = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsInside'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsInside(position,isScreen);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsInside'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsInsideCombined of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_IsInsideCombined00
static int tolua_UI_UIElement_IsInsideCombined00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"IntVector2",0,&tolua_err)) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  IntVector2 position = *((IntVector2*)  tolua_tousertype(tolua_S,2,0));
  bool isScreen = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsInsideCombined'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsInsideCombined(position,isScreen);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsInsideCombined'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCombinedScreenRect of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_GetCombinedScreenRect00
static int tolua_UI_UIElement_GetCombinedScreenRect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCombinedScreenRect'", NULL);
#endif
  {
   IntRect tolua_ret = (IntRect)  self->GetCombinedScreenRect();
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
 tolua_error(tolua_S,"#ferror in function 'GetCombinedScreenRect'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SortChildren of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_SortChildren00
static int tolua_UI_UIElement_SortChildren00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SortChildren'", NULL);
#endif
  {
   self->SortChildren();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SortChildren'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLayoutMinSize of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_GetLayoutMinSize00
static int tolua_UI_UIElement_GetLayoutMinSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIElement* self = (const UIElement*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLayoutMinSize'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetLayoutMinSize();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLayoutMinSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetIndent of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_GetIndent00
static int tolua_UI_UIElement_GetIndent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIElement* self = (const UIElement*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetIndent'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetIndent();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetIndent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetIndentSpacing of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_GetIndentSpacing00
static int tolua_UI_UIElement_GetIndentSpacing00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIElement* self = (const UIElement*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetIndentSpacing'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetIndentSpacing();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetIndentSpacing'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetIndentWidth of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_GetIndentWidth00
static int tolua_UI_UIElement_GetIndentWidth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIElement* self = (const UIElement*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetIndentWidth'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetIndentWidth();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetIndentWidth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetChildOffset of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_SetChildOffset00
static int tolua_UI_UIElement_SetChildOffset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const IntVector2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  const IntVector2* offset = ((const IntVector2*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetChildOffset'", NULL);
#endif
  {
   self->SetChildOffset(*offset);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetChildOffset'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetHovering of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_SetHovering00
static int tolua_UI_UIElement_SetHovering00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetHovering'", NULL);
#endif
  {
   self->SetHovering(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetHovering'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetTempVisible of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_SetTempVisible00
static int tolua_UI_UIElement_SetTempVisible00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetTempVisible'", NULL);
#endif
  {
   self->SetTempVisible(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetTempVisible'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AdjustScissor of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_AdjustScissor00
static int tolua_UI_UIElement_AdjustScissor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"IntRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  IntRect* currentScissor = ((IntRect*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AdjustScissor'", NULL);
#endif
  {
   self->AdjustScissor(*currentScissor);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AdjustScissor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetBatchesWithOffset of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_GetBatchesWithOffset00
static int tolua_UI_UIElement_GetBatchesWithOffset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"UIElement",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"IntVector2",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"PODVector<UIBatch>",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"PODVector<float>",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,5,&tolua_err) || !tolua_isusertype(tolua_S,5,"IntRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  UIElement* self = (UIElement*)  tolua_tousertype(tolua_S,1,0);
  IntVector2* offset = ((IntVector2*)  tolua_tousertype(tolua_S,2,0));
  PODVector<UIBatch>* batches = ((PODVector<UIBatch>*)  tolua_tousertype(tolua_S,3,0));
  PODVector<float>* vertexData = ((PODVector<float>*)  tolua_tousertype(tolua_S,4,0));
  IntRect currentScissor = *((IntRect*)  tolua_tousertype(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetBatchesWithOffset'", NULL);
#endif
  {
   self->GetBatchesWithOffset(*offset,*batches,*vertexData,currentScissor);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetBatchesWithOffset'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetColorAttr of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_GetColorAttr00
static int tolua_UI_UIElement_GetColorAttr00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIElement* self = (const UIElement*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetColorAttr'", NULL);
#endif
  {
   const Color& tolua_ret = (const Color&)  self->GetColorAttr();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Color");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetColorAttr'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTraversalMode of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_GetTraversalMode00
static int tolua_UI_UIElement_GetTraversalMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIElement* self = (const UIElement*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTraversalMode'", NULL);
#endif
  {
   TraversalMode tolua_ret = (TraversalMode)  self->GetTraversalMode();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTraversalMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsElementEventSender of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_IsElementEventSender00
static int tolua_UI_UIElement_IsElementEventSender00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIElement* self = (const UIElement*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsElementEventSender'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsElementEventSender();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsElementEventSender'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetElementEventSender of class  UIElement */
#ifndef TOLUA_DISABLE_tolua_UI_UIElement_GetElementEventSender00
static int tolua_UI_UIElement_GetElementEventSender00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const UIElement",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const UIElement* self = (const UIElement*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetElementEventSender'", NULL);
#endif
  {
   UIElement* tolua_ret = (UIElement*)  self->GetElementEventSender();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"UIElement");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetElementEventSender'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMovable of class  Window */
#ifndef TOLUA_DISABLE_tolua_UI_Window_SetMovable00
static int tolua_UI_Window_SetMovable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Window",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Window* self = (Window*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMovable'", NULL);
#endif
  {
   self->SetMovable(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMovable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetResizable of class  Window */
#ifndef TOLUA_DISABLE_tolua_UI_Window_SetResizable00
static int tolua_UI_Window_SetResizable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Window",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Window* self = (Window*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetResizable'", NULL);
#endif
  {
   self->SetResizable(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetResizable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetResizeBorder of class  Window */
#ifndef TOLUA_DISABLE_tolua_UI_Window_SetResizeBorder00
static int tolua_UI_Window_SetResizeBorder00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Window",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const IntRect",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Window* self = (Window*)  tolua_tousertype(tolua_S,1,0);
  const IntRect* rect = ((const IntRect*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetResizeBorder'", NULL);
#endif
  {
   self->SetResizeBorder(*rect);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetResizeBorder'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetModal of class  Window */
#ifndef TOLUA_DISABLE_tolua_UI_Window_SetModal00
static int tolua_UI_Window_SetModal00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Window",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Window* self = (Window*)  tolua_tousertype(tolua_S,1,0);
  bool modal = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetModal'", NULL);
#endif
  {
   self->SetModal(modal);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetModal'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetModalShadeColor of class  Window */
#ifndef TOLUA_DISABLE_tolua_UI_Window_SetModalShadeColor00
static int tolua_UI_Window_SetModalShadeColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Window",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Color",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Window* self = (Window*)  tolua_tousertype(tolua_S,1,0);
  const Color* color = ((const Color*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetModalShadeColor'", NULL);
#endif
  {
   self->SetModalShadeColor(*color);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetModalShadeColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetModalFrameColor of class  Window */
#ifndef TOLUA_DISABLE_tolua_UI_Window_SetModalFrameColor00
static int tolua_UI_Window_SetModalFrameColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Window",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Color",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Window* self = (Window*)  tolua_tousertype(tolua_S,1,0);
  const Color* color = ((const Color*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetModalFrameColor'", NULL);
#endif
  {
   self->SetModalFrameColor(*color);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetModalFrameColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetModalFrameSize of class  Window */
#ifndef TOLUA_DISABLE_tolua_UI_Window_SetModalFrameSize00
static int tolua_UI_Window_SetModalFrameSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Window",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const IntVector2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Window* self = (Window*)  tolua_tousertype(tolua_S,1,0);
  const IntVector2* size = ((const IntVector2*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetModalFrameSize'", NULL);
#endif
  {
   self->SetModalFrameSize(*size);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetModalFrameSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsMovable of class  Window */
#ifndef TOLUA_DISABLE_tolua_UI_Window_IsMovable00
static int tolua_UI_Window_IsMovable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Window",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Window* self = (const Window*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsMovable'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsMovable();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsMovable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsResizable of class  Window */
#ifndef TOLUA_DISABLE_tolua_UI_Window_IsResizable00
static int tolua_UI_Window_IsResizable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Window",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Window* self = (const Window*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsResizable'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsResizable();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsResizable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetResizeBorder of class  Window */
#ifndef TOLUA_DISABLE_tolua_UI_Window_GetResizeBorder00
static int tolua_UI_Window_GetResizeBorder00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Window",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Window* self = (const Window*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetResizeBorder'", NULL);
#endif
  {
   const IntRect& tolua_ret = (const IntRect&)  self->GetResizeBorder();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const IntRect");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetResizeBorder'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsModal of class  Window */
#ifndef TOLUA_DISABLE_tolua_UI_Window_IsModal00
static int tolua_UI_Window_IsModal00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Window",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Window* self = (const Window*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsModal'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsModal();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsModal'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetModalShadeColor of class  Window */
#ifndef TOLUA_DISABLE_tolua_UI_Window_GetModalShadeColor00
static int tolua_UI_Window_GetModalShadeColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Window",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Window* self = (const Window*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetModalShadeColor'", NULL);
#endif
  {
   const Color& tolua_ret = (const Color&)  self->GetModalShadeColor();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Color");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetModalShadeColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetModalFrameColor of class  Window */
#ifndef TOLUA_DISABLE_tolua_UI_Window_GetModalFrameColor00
static int tolua_UI_Window_GetModalFrameColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Window",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Window* self = (const Window*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetModalFrameColor'", NULL);
#endif
  {
   const Color& tolua_ret = (const Color&)  self->GetModalFrameColor();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Color");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetModalFrameColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetModalFrameSize of class  Window */
#ifndef TOLUA_DISABLE_tolua_UI_Window_GetModalFrameSize00
static int tolua_UI_Window_GetModalFrameSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Window",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Window* self = (const Window*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetModalFrameSize'", NULL);
#endif
  {
   const IntVector2& tolua_ret = (const IntVector2&)  self->GetModalFrameSize();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const IntVector2");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetModalFrameSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_UI_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,1);
 tolua_beginmodule(tolua_S,NULL);
  tolua_cclass(tolua_S,"BorderImage","BorderImage","UIElement",NULL);
  tolua_beginmodule(tolua_S,"BorderImage");
   tolua_function(tolua_S,"SetTexture",tolua_UI_BorderImage_SetTexture00);
   tolua_function(tolua_S,"SetImageRect",tolua_UI_BorderImage_SetImageRect00);
   tolua_function(tolua_S,"SetFullImageRect",tolua_UI_BorderImage_SetFullImageRect00);
   tolua_function(tolua_S,"SetBorder",tolua_UI_BorderImage_SetBorder00);
   tolua_function(tolua_S,"SetHoverOffset",tolua_UI_BorderImage_SetHoverOffset00);
   tolua_function(tolua_S,"SetHoverOffset",tolua_UI_BorderImage_SetHoverOffset01);
   tolua_function(tolua_S,"SetBlendMode",tolua_UI_BorderImage_SetBlendMode00);
   tolua_function(tolua_S,"SetTiled",tolua_UI_BorderImage_SetTiled00);
   tolua_function(tolua_S,"GetTexture",tolua_UI_BorderImage_GetTexture00);
   tolua_function(tolua_S,"GetImageRect",tolua_UI_BorderImage_GetImageRect00);
   tolua_function(tolua_S,"GetBorder",tolua_UI_BorderImage_GetBorder00);
   tolua_function(tolua_S,"GetHoverOffset",tolua_UI_BorderImage_GetHoverOffset00);
   tolua_function(tolua_S,"GetBlendMode",tolua_UI_BorderImage_GetBlendMode00);
   tolua_function(tolua_S,"IsTiled",tolua_UI_BorderImage_IsTiled00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Button","Button","BorderImage",NULL);
  tolua_beginmodule(tolua_S,"Button");
   tolua_function(tolua_S,"SetPressedOffset",tolua_UI_Button_SetPressedOffset00);
   tolua_function(tolua_S,"SetPressedOffset",tolua_UI_Button_SetPressedOffset01);
   tolua_function(tolua_S,"SetLabelOffset",tolua_UI_Button_SetLabelOffset00);
   tolua_function(tolua_S,"SetLabelOffset",tolua_UI_Button_SetLabelOffset01);
   tolua_function(tolua_S,"SetRepeat",tolua_UI_Button_SetRepeat00);
   tolua_function(tolua_S,"SetRepeatDelay",tolua_UI_Button_SetRepeatDelay00);
   tolua_function(tolua_S,"SetRepeatRate",tolua_UI_Button_SetRepeatRate00);
   tolua_function(tolua_S,"GetPressedOffset",tolua_UI_Button_GetPressedOffset00);
   tolua_function(tolua_S,"GetLabelOffset",tolua_UI_Button_GetLabelOffset00);
   tolua_function(tolua_S,"GetRepeatDelay",tolua_UI_Button_GetRepeatDelay00);
   tolua_function(tolua_S,"GetRepeatRate",tolua_UI_Button_GetRepeatRate00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"CheckBox","CheckBox","BorderImage",NULL);
  tolua_beginmodule(tolua_S,"CheckBox");
   tolua_function(tolua_S,"SetChecked",tolua_UI_CheckBox_SetChecked00);
   tolua_function(tolua_S,"SetCheckedOffset",tolua_UI_CheckBox_SetCheckedOffset00);
   tolua_function(tolua_S,"SetCheckedOffset",tolua_UI_CheckBox_SetCheckedOffset01);
   tolua_function(tolua_S,"IsChecked",tolua_UI_CheckBox_IsChecked00);
   tolua_function(tolua_S,"GetCheckedOffset",tolua_UI_CheckBox_GetCheckedOffset00);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"CS_NORMAL",CS_NORMAL);
  tolua_constant(tolua_S,"CS_RESIZEVERTICAL",CS_RESIZEVERTICAL);
  tolua_constant(tolua_S,"CS_RESIZEDIAGONAL_TOPRIGHT",CS_RESIZEDIAGONAL_TOPRIGHT);
  tolua_constant(tolua_S,"CS_RESIZEHORIZONTAL",CS_RESIZEHORIZONTAL);
  tolua_constant(tolua_S,"CS_RESIZEDIAGONAL_TOPLEFT",CS_RESIZEDIAGONAL_TOPLEFT);
  tolua_constant(tolua_S,"CS_ACCEPTDROP",CS_ACCEPTDROP);
  tolua_constant(tolua_S,"CS_REJECTDROP",CS_REJECTDROP);
  tolua_constant(tolua_S,"CS_BUSY",CS_BUSY);
  tolua_constant(tolua_S,"CS_MAX_SHAPES",CS_MAX_SHAPES);
  tolua_cclass(tolua_S,"Cursor","Cursor","BorderImage",NULL);
  tolua_beginmodule(tolua_S,"Cursor");
   tolua_function(tolua_S,"DefineShape",tolua_UI_Cursor_DefineShape00);
   tolua_function(tolua_S,"SetShape",tolua_UI_Cursor_SetShape00);
   tolua_function(tolua_S,"GetShape",tolua_UI_Cursor_GetShape00);
  tolua_endmodule(tolua_S);
  tolua_function(tolua_S,"Cursor",tolua_UI_Cursor00);
  tolua_cclass(tolua_S,"DropDownList","DropDownList","Menu",NULL);
  tolua_beginmodule(tolua_S,"DropDownList");
   tolua_function(tolua_S,"AddItem",tolua_UI_DropDownList_AddItem00);
   tolua_function(tolua_S,"InsertItem",tolua_UI_DropDownList_InsertItem00);
   tolua_function(tolua_S,"RemoveItem",tolua_UI_DropDownList_RemoveItem00);
   tolua_function(tolua_S,"RemoveItem",tolua_UI_DropDownList_RemoveItem01);
   tolua_function(tolua_S,"RemoveAllItems",tolua_UI_DropDownList_RemoveAllItems00);
   tolua_function(tolua_S,"SetSelection",tolua_UI_DropDownList_SetSelection00);
   tolua_function(tolua_S,"SetPlaceholderText",tolua_UI_DropDownList_SetPlaceholderText00);
   tolua_function(tolua_S,"SetResizePopup",tolua_UI_DropDownList_SetResizePopup00);
   tolua_function(tolua_S,"GetNumItems",tolua_UI_DropDownList_GetNumItems00);
   tolua_function(tolua_S,"GetItem",tolua_UI_DropDownList_GetItem00);
   tolua_function(tolua_S,"GetSelection",tolua_UI_DropDownList_GetSelection00);
   tolua_function(tolua_S,"GetSelectedItem",tolua_UI_DropDownList_GetSelectedItem00);
   tolua_function(tolua_S,"GetListView",tolua_UI_DropDownList_GetListView00);
   tolua_function(tolua_S,"GetPlaceholder",tolua_UI_DropDownList_GetPlaceholder00);
   tolua_function(tolua_S,"GetPlaceholderText",tolua_UI_DropDownList_GetPlaceholderText00);
   tolua_function(tolua_S,"GetResizePopup",tolua_UI_DropDownList_GetResizePopup00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"FileSelectorEntry","FileSelectorEntry","",NULL);
  tolua_beginmodule(tolua_S,"FileSelectorEntry");
   tolua_variable(tolua_S,"name_",tolua_get_FileSelectorEntry_name_,tolua_set_FileSelectorEntry_name_);
   tolua_variable(tolua_S,"directory_",tolua_get_FileSelectorEntry_directory_,tolua_set_FileSelectorEntry_directory_);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"FileSelector","FileSelector","Object",NULL);
  tolua_beginmodule(tolua_S,"FileSelector");
   tolua_function(tolua_S,"SetDefaultStyle",tolua_UI_FileSelector_SetDefaultStyle00);
   tolua_function(tolua_S,"SetTitle",tolua_UI_FileSelector_SetTitle00);
   tolua_function(tolua_S,"SetButtonTexts",tolua_UI_FileSelector_SetButtonTexts00);
   tolua_function(tolua_S,"SetPath",tolua_UI_FileSelector_SetPath00);
   tolua_function(tolua_S,"SetFileName",tolua_UI_FileSelector_SetFileName00);
   tolua_function(tolua_S,"SetFilters",tolua_UI_FileSelector_SetFilters00);
   tolua_function(tolua_S,"SetDirectoryMode",tolua_UI_FileSelector_SetDirectoryMode00);
   tolua_function(tolua_S,"UpdateElements",tolua_UI_FileSelector_UpdateElements00);
   tolua_function(tolua_S,"GetDefaultStyle",tolua_UI_FileSelector_GetDefaultStyle00);
   tolua_function(tolua_S,"GetWindow",tolua_UI_FileSelector_GetWindow00);
   tolua_function(tolua_S,"GetTitleText",tolua_UI_FileSelector_GetTitleText00);
   tolua_function(tolua_S,"GetFileList",tolua_UI_FileSelector_GetFileList00);
   tolua_function(tolua_S,"GetPathEdit",tolua_UI_FileSelector_GetPathEdit00);
   tolua_function(tolua_S,"GetFileNameEdit",tolua_UI_FileSelector_GetFileNameEdit00);
   tolua_function(tolua_S,"GetFilterList",tolua_UI_FileSelector_GetFilterList00);
   tolua_function(tolua_S,"GetOKButton",tolua_UI_FileSelector_GetOKButton00);
   tolua_function(tolua_S,"GetCancelButton",tolua_UI_FileSelector_GetCancelButton00);
   tolua_function(tolua_S,"GetCloseButton",tolua_UI_FileSelector_GetCloseButton00);
   tolua_function(tolua_S,"GetTitle",tolua_UI_FileSelector_GetTitle00);
   tolua_function(tolua_S,"GetPath",tolua_UI_FileSelector_GetPath00);
   tolua_function(tolua_S,"GetFileName",tolua_UI_FileSelector_GetFileName00);
   tolua_function(tolua_S,"GetFilter",tolua_UI_FileSelector_GetFilter00);
   tolua_function(tolua_S,"GetFilterIndex",tolua_UI_FileSelector_GetFilterIndex00);
   tolua_function(tolua_S,"GetDirectoryMode",tolua_UI_FileSelector_GetDirectoryMode00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Font","Font","Resource",NULL);
  tolua_beginmodule(tolua_S,"Font");
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"LineEdit","LineEdit","BorderImage",NULL);
  tolua_beginmodule(tolua_S,"LineEdit");
   tolua_function(tolua_S,"SetText",tolua_UI_LineEdit_SetText00);
   tolua_function(tolua_S,"SetCursorPosition",tolua_UI_LineEdit_SetCursorPosition00);
   tolua_function(tolua_S,"SetCursorBlinkRate",tolua_UI_LineEdit_SetCursorBlinkRate00);
   tolua_function(tolua_S,"SetMaxLength",tolua_UI_LineEdit_SetMaxLength00);
   tolua_function(tolua_S,"SetEchoCharacter",tolua_UI_LineEdit_SetEchoCharacter00);
   tolua_function(tolua_S,"SetCursorMovable",tolua_UI_LineEdit_SetCursorMovable00);
   tolua_function(tolua_S,"SetTextSelectable",tolua_UI_LineEdit_SetTextSelectable00);
   tolua_function(tolua_S,"SetTextCopyable",tolua_UI_LineEdit_SetTextCopyable00);
   tolua_function(tolua_S,"SetDoubleClickInterval",tolua_UI_LineEdit_SetDoubleClickInterval00);
   tolua_function(tolua_S,"GetText",tolua_UI_LineEdit_GetText00);
   tolua_function(tolua_S,"GetCursorPosition",tolua_UI_LineEdit_GetCursorPosition00);
   tolua_function(tolua_S,"GetCursorBlinkRate",tolua_UI_LineEdit_GetCursorBlinkRate00);
   tolua_function(tolua_S,"GetMaxLength",tolua_UI_LineEdit_GetMaxLength00);
   tolua_function(tolua_S,"GetEchoCharacter",tolua_UI_LineEdit_GetEchoCharacter00);
   tolua_function(tolua_S,"IsCursorMovable",tolua_UI_LineEdit_IsCursorMovable00);
   tolua_function(tolua_S,"IsTextSelectable",tolua_UI_LineEdit_IsTextSelectable00);
   tolua_function(tolua_S,"IsTextCopyable",tolua_UI_LineEdit_IsTextCopyable00);
   tolua_function(tolua_S,"GetTextElement",tolua_UI_LineEdit_GetTextElement00);
   tolua_function(tolua_S,"GetCursor",tolua_UI_LineEdit_GetCursor00);
   tolua_function(tolua_S,"GetDoubleClickInterval",tolua_UI_LineEdit_GetDoubleClickInterval00);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"HM_NEVER",HM_NEVER);
  tolua_constant(tolua_S,"HM_FOCUS",HM_FOCUS);
  tolua_constant(tolua_S,"HM_ALWAYS",HM_ALWAYS);
  tolua_cclass(tolua_S,"ListView","ListView","ScrollView",NULL);
  tolua_beginmodule(tolua_S,"ListView");
   tolua_function(tolua_S,"AddItem",tolua_UI_ListView_AddItem00);
   tolua_function(tolua_S,"InsertItem",tolua_UI_ListView_InsertItem00);
   tolua_function(tolua_S,"RemoveItem",tolua_UI_ListView_RemoveItem00);
   tolua_function(tolua_S,"RemoveItem",tolua_UI_ListView_RemoveItem01);
   tolua_function(tolua_S,"RemoveAllItems",tolua_UI_ListView_RemoveAllItems00);
   tolua_function(tolua_S,"SetSelection",tolua_UI_ListView_SetSelection00);
   tolua_function(tolua_S,"AddSelection",tolua_UI_ListView_AddSelection00);
   tolua_function(tolua_S,"RemoveSelection",tolua_UI_ListView_RemoveSelection00);
   tolua_function(tolua_S,"ToggleSelection",tolua_UI_ListView_ToggleSelection00);
   tolua_function(tolua_S,"ChangeSelection",tolua_UI_ListView_ChangeSelection00);
   tolua_function(tolua_S,"ClearSelection",tolua_UI_ListView_ClearSelection00);
   tolua_function(tolua_S,"SetHighlightMode",tolua_UI_ListView_SetHighlightMode00);
   tolua_function(tolua_S,"SetMultiselect",tolua_UI_ListView_SetMultiselect00);
   tolua_function(tolua_S,"SetHierarchyMode",tolua_UI_ListView_SetHierarchyMode00);
   tolua_function(tolua_S,"SetBaseIndent",tolua_UI_ListView_SetBaseIndent00);
   tolua_function(tolua_S,"SetClearSelectionOnDefocus",tolua_UI_ListView_SetClearSelectionOnDefocus00);
   tolua_function(tolua_S,"SetDoubleClickInterval",tolua_UI_ListView_SetDoubleClickInterval00);
   tolua_function(tolua_S,"Expand",tolua_UI_ListView_Expand00);
   tolua_function(tolua_S,"ToggleExpand",tolua_UI_ListView_ToggleExpand00);
   tolua_function(tolua_S,"GetNumItems",tolua_UI_ListView_GetNumItems00);
   tolua_function(tolua_S,"GetItem",tolua_UI_ListView_GetItem00);
   tolua_function(tolua_S,"FindItem",tolua_UI_ListView_FindItem00);
   tolua_function(tolua_S,"GetSelection",tolua_UI_ListView_GetSelection00);
   tolua_function(tolua_S,"GetSelectedItem",tolua_UI_ListView_GetSelectedItem00);
   tolua_function(tolua_S,"IsSelected",tolua_UI_ListView_IsSelected00);
   tolua_function(tolua_S,"IsExpanded",tolua_UI_ListView_IsExpanded00);
   tolua_function(tolua_S,"GetHighlightMode",tolua_UI_ListView_GetHighlightMode00);
   tolua_function(tolua_S,"GetMultiselect",tolua_UI_ListView_GetMultiselect00);
   tolua_function(tolua_S,"GetClearSelectionOnDefocus",tolua_UI_ListView_GetClearSelectionOnDefocus00);
   tolua_function(tolua_S,"GetHierarchyMode",tolua_UI_ListView_GetHierarchyMode00);
   tolua_function(tolua_S,"GetBaseIndent",tolua_UI_ListView_GetBaseIndent00);
   tolua_function(tolua_S,"GetDoubleClickInterval",tolua_UI_ListView_GetDoubleClickInterval00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Menu","Menu","Button",NULL);
  tolua_beginmodule(tolua_S,"Menu");
   tolua_function(tolua_S,"SetPopup",tolua_UI_Menu_SetPopup00);
   tolua_function(tolua_S,"SetPopupOffset",tolua_UI_Menu_SetPopupOffset00);
   tolua_function(tolua_S,"SetPopupOffset",tolua_UI_Menu_SetPopupOffset01);
   tolua_function(tolua_S,"ShowPopup",tolua_UI_Menu_ShowPopup00);
   tolua_function(tolua_S,"SetAccelerator",tolua_UI_Menu_SetAccelerator00);
   tolua_function(tolua_S,"GetPopup",tolua_UI_Menu_GetPopup00);
   tolua_function(tolua_S,"GetPopupOffset",tolua_UI_Menu_GetPopupOffset00);
   tolua_function(tolua_S,"GetShowPopup",tolua_UI_Menu_GetShowPopup00);
   tolua_function(tolua_S,"GetAcceleratorKey",tolua_UI_Menu_GetAcceleratorKey00);
   tolua_function(tolua_S,"GetAcceleratorQualifiers",tolua_UI_Menu_GetAcceleratorQualifiers00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"ScrollBar","ScrollBar","UIElement",NULL);
  tolua_beginmodule(tolua_S,"ScrollBar");
   tolua_function(tolua_S,"SetOrientation",tolua_UI_ScrollBar_SetOrientation00);
   tolua_function(tolua_S,"SetRange",tolua_UI_ScrollBar_SetRange00);
   tolua_function(tolua_S,"SetValue",tolua_UI_ScrollBar_SetValue00);
   tolua_function(tolua_S,"ChangeValue",tolua_UI_ScrollBar_ChangeValue00);
   tolua_function(tolua_S,"SetScrollStep",tolua_UI_ScrollBar_SetScrollStep00);
   tolua_function(tolua_S,"SetStepFactor",tolua_UI_ScrollBar_SetStepFactor00);
   tolua_function(tolua_S,"StepBack",tolua_UI_ScrollBar_StepBack00);
   tolua_function(tolua_S,"StepForward",tolua_UI_ScrollBar_StepForward00);
   tolua_function(tolua_S,"GetOrientation",tolua_UI_ScrollBar_GetOrientation00);
   tolua_function(tolua_S,"GetRange",tolua_UI_ScrollBar_GetRange00);
   tolua_function(tolua_S,"GetValue",tolua_UI_ScrollBar_GetValue00);
   tolua_function(tolua_S,"GetScrollStep",tolua_UI_ScrollBar_GetScrollStep00);
   tolua_function(tolua_S,"GetStepFactor",tolua_UI_ScrollBar_GetStepFactor00);
   tolua_function(tolua_S,"GetEffectiveScrollStep",tolua_UI_ScrollBar_GetEffectiveScrollStep00);
   tolua_function(tolua_S,"GetBackButton",tolua_UI_ScrollBar_GetBackButton00);
   tolua_function(tolua_S,"GetForwardButton",tolua_UI_ScrollBar_GetForwardButton00);
   tolua_function(tolua_S,"GetSlider",tolua_UI_ScrollBar_GetSlider00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"ScrollView","ScrollView","UIElement",NULL);
  tolua_beginmodule(tolua_S,"ScrollView");
   tolua_function(tolua_S,"SetContentElement",tolua_UI_ScrollView_SetContentElement00);
   tolua_function(tolua_S,"SetViewPosition",tolua_UI_ScrollView_SetViewPosition00);
   tolua_function(tolua_S,"SetViewPosition",tolua_UI_ScrollView_SetViewPosition01);
   tolua_function(tolua_S,"SetScrollBarsVisible",tolua_UI_ScrollView_SetScrollBarsVisible00);
   tolua_function(tolua_S,"SetScrollBarsAutoVisible",tolua_UI_ScrollView_SetScrollBarsAutoVisible00);
   tolua_function(tolua_S,"SetScrollStep",tolua_UI_ScrollView_SetScrollStep00);
   tolua_function(tolua_S,"SetPageStep",tolua_UI_ScrollView_SetPageStep00);
   tolua_function(tolua_S,"GetViewPosition",tolua_UI_ScrollView_GetViewPosition00);
   tolua_function(tolua_S,"GetContentElement",tolua_UI_ScrollView_GetContentElement00);
   tolua_function(tolua_S,"GetHorizontalScrollBar",tolua_UI_ScrollView_GetHorizontalScrollBar00);
   tolua_function(tolua_S,"GetVerticalScrollBar",tolua_UI_ScrollView_GetVerticalScrollBar00);
   tolua_function(tolua_S,"GetScrollPanel",tolua_UI_ScrollView_GetScrollPanel00);
   tolua_function(tolua_S,"GetScrollBarsAutoVisible",tolua_UI_ScrollView_GetScrollBarsAutoVisible00);
   tolua_function(tolua_S,"GetScrollStep",tolua_UI_ScrollView_GetScrollStep00);
   tolua_function(tolua_S,"GetPageStep",tolua_UI_ScrollView_GetPageStep00);
   tolua_function(tolua_S,"SetViewPositionAttr",tolua_UI_ScrollView_SetViewPositionAttr00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Slider","Slider","BorderImage",NULL);
  tolua_beginmodule(tolua_S,"Slider");
   tolua_function(tolua_S,"SetOrientation",tolua_UI_Slider_SetOrientation00);
   tolua_function(tolua_S,"SetRange",tolua_UI_Slider_SetRange00);
   tolua_function(tolua_S,"SetValue",tolua_UI_Slider_SetValue00);
   tolua_function(tolua_S,"ChangeValue",tolua_UI_Slider_ChangeValue00);
   tolua_function(tolua_S,"SetRepeatRate",tolua_UI_Slider_SetRepeatRate00);
   tolua_function(tolua_S,"GetOrientation",tolua_UI_Slider_GetOrientation00);
   tolua_function(tolua_S,"GetRange",tolua_UI_Slider_GetRange00);
   tolua_function(tolua_S,"GetValue",tolua_UI_Slider_GetValue00);
   tolua_function(tolua_S,"GetKnob",tolua_UI_Slider_GetKnob00);
   tolua_function(tolua_S,"GetRepeatRate",tolua_UI_Slider_GetRepeatRate00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Sprite","Sprite","UIElement",NULL);
  tolua_beginmodule(tolua_S,"Sprite");
   tolua_function(tolua_S,"SetPosition",tolua_UI_Sprite_SetPosition00);
   tolua_function(tolua_S,"SetPosition",tolua_UI_Sprite_SetPosition01);
   tolua_function(tolua_S,"SetHotSpot",tolua_UI_Sprite_SetHotSpot00);
   tolua_function(tolua_S,"SetHotSpot",tolua_UI_Sprite_SetHotSpot01);
   tolua_function(tolua_S,"SetScale",tolua_UI_Sprite_SetScale00);
   tolua_function(tolua_S,"SetScale",tolua_UI_Sprite_SetScale01);
   tolua_function(tolua_S,"SetScale",tolua_UI_Sprite_SetScale02);
   tolua_function(tolua_S,"SetRotation",tolua_UI_Sprite_SetRotation00);
   tolua_function(tolua_S,"SetTexture",tolua_UI_Sprite_SetTexture00);
   tolua_function(tolua_S,"SetImageRect",tolua_UI_Sprite_SetImageRect00);
   tolua_function(tolua_S,"SetFullImageRect",tolua_UI_Sprite_SetFullImageRect00);
   tolua_function(tolua_S,"SetBlendMode",tolua_UI_Sprite_SetBlendMode00);
   tolua_function(tolua_S,"GetPosition",tolua_UI_Sprite_GetPosition00);
   tolua_function(tolua_S,"GetHotSpot",tolua_UI_Sprite_GetHotSpot00);
   tolua_function(tolua_S,"GetScale",tolua_UI_Sprite_GetScale00);
   tolua_function(tolua_S,"GetRotation",tolua_UI_Sprite_GetRotation00);
   tolua_function(tolua_S,"GetTexture",tolua_UI_Sprite_GetTexture00);
   tolua_function(tolua_S,"GetImageRect",tolua_UI_Sprite_GetImageRect00);
   tolua_function(tolua_S,"GetBlendMode",tolua_UI_Sprite_GetBlendMode00);
   tolua_function(tolua_S,"SetTextureAttr",tolua_UI_Sprite_SetTextureAttr00);
   tolua_function(tolua_S,"GetTextureAttr",tolua_UI_Sprite_GetTextureAttr00);
   tolua_function(tolua_S,"GetTransform",tolua_UI_Sprite_GetTransform00);
  tolua_endmodule(tolua_S);
  tolua_function(tolua_S,"Sprite",tolua_UI_Sprite00);
  tolua_cclass(tolua_S,"Text","Text","UIElement",NULL);
  tolua_beginmodule(tolua_S,"Text");
   tolua_function(tolua_S,"SetFont",tolua_UI_Text_SetFont00);
   tolua_function(tolua_S,"SetFont",tolua_UI_Text_SetFont01);
   tolua_function(tolua_S,"SetText",tolua_UI_Text_SetText00);
   tolua_function(tolua_S,"SetTextAlignment",tolua_UI_Text_SetTextAlignment00);
   tolua_function(tolua_S,"SetRowSpacing",tolua_UI_Text_SetRowSpacing00);
   tolua_function(tolua_S,"SetWordwrap",tolua_UI_Text_SetWordwrap00);
   tolua_function(tolua_S,"SetSelection",tolua_UI_Text_SetSelection00);
   tolua_function(tolua_S,"ClearSelection",tolua_UI_Text_ClearSelection00);
   tolua_function(tolua_S,"SetSelectionColor",tolua_UI_Text_SetSelectionColor00);
   tolua_function(tolua_S,"SetHoverColor",tolua_UI_Text_SetHoverColor00);
   tolua_function(tolua_S,"GetFont",tolua_UI_Text_GetFont00);
   tolua_function(tolua_S,"GetFontSize",tolua_UI_Text_GetFontSize00);
   tolua_function(tolua_S,"GetText",tolua_UI_Text_GetText00);
   tolua_function(tolua_S,"GetTextAlignment",tolua_UI_Text_GetTextAlignment00);
   tolua_function(tolua_S,"GetRowSpacing",tolua_UI_Text_GetRowSpacing00);
   tolua_function(tolua_S,"GetWordwrap",tolua_UI_Text_GetWordwrap00);
   tolua_function(tolua_S,"GetSelectionStart",tolua_UI_Text_GetSelectionStart00);
   tolua_function(tolua_S,"GetSelectionLength",tolua_UI_Text_GetSelectionLength00);
   tolua_function(tolua_S,"GetSelectionColor",tolua_UI_Text_GetSelectionColor00);
   tolua_function(tolua_S,"GetHoverColor",tolua_UI_Text_GetHoverColor00);
   tolua_function(tolua_S,"GetRowHeight",tolua_UI_Text_GetRowHeight00);
   tolua_function(tolua_S,"GetNumRows",tolua_UI_Text_GetNumRows00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Text3D","Text3D","Drawable",NULL);
  tolua_beginmodule(tolua_S,"Text3D");
   tolua_function(tolua_S,"SetFont",tolua_UI_Text3D_SetFont00);
   tolua_function(tolua_S,"SetFont",tolua_UI_Text3D_SetFont01);
   tolua_function(tolua_S,"SetMaterial",tolua_UI_Text3D_SetMaterial00);
   tolua_function(tolua_S,"SetText",tolua_UI_Text3D_SetText00);
   tolua_function(tolua_S,"SetAlignment",tolua_UI_Text3D_SetAlignment00);
   tolua_function(tolua_S,"SetHorizontalAlignment",tolua_UI_Text3D_SetHorizontalAlignment00);
   tolua_function(tolua_S,"SetVerticalAlignment",tolua_UI_Text3D_SetVerticalAlignment00);
   tolua_function(tolua_S,"SetTextAlignment",tolua_UI_Text3D_SetTextAlignment00);
   tolua_function(tolua_S,"SetRowSpacing",tolua_UI_Text3D_SetRowSpacing00);
   tolua_function(tolua_S,"SetWordwrap",tolua_UI_Text3D_SetWordwrap00);
   tolua_function(tolua_S,"SetWidth",tolua_UI_Text3D_SetWidth00);
   tolua_function(tolua_S,"SetColor",tolua_UI_Text3D_SetColor00);
   tolua_function(tolua_S,"SetColor",tolua_UI_Text3D_SetColor01);
   tolua_function(tolua_S,"SetOpacity",tolua_UI_Text3D_SetOpacity00);
   tolua_function(tolua_S,"SetFaceCamera",tolua_UI_Text3D_SetFaceCamera00);
   tolua_function(tolua_S,"GetFont",tolua_UI_Text3D_GetFont00);
   tolua_function(tolua_S,"GetMaterial",tolua_UI_Text3D_GetMaterial00);
   tolua_function(tolua_S,"GetFontSize",tolua_UI_Text3D_GetFontSize00);
   tolua_function(tolua_S,"GetText",tolua_UI_Text3D_GetText00);
   tolua_function(tolua_S,"GetTextAlignment",tolua_UI_Text3D_GetTextAlignment00);
   tolua_function(tolua_S,"GetHorizontalAlignment",tolua_UI_Text3D_GetHorizontalAlignment00);
   tolua_function(tolua_S,"GetVerticalAlignment",tolua_UI_Text3D_GetVerticalAlignment00);
   tolua_function(tolua_S,"GetRowSpacing",tolua_UI_Text3D_GetRowSpacing00);
   tolua_function(tolua_S,"GetWordwrap",tolua_UI_Text3D_GetWordwrap00);
   tolua_function(tolua_S,"GetWidth",tolua_UI_Text3D_GetWidth00);
   tolua_function(tolua_S,"GetRowHeight",tolua_UI_Text3D_GetRowHeight00);
   tolua_function(tolua_S,"GetNumRows",tolua_UI_Text3D_GetNumRows00);
   tolua_function(tolua_S,"GetRowWidths",tolua_UI_Text3D_GetRowWidths00);
   tolua_function(tolua_S,"GetColor",tolua_UI_Text3D_GetColor00);
   tolua_function(tolua_S,"GetOpacity",tolua_UI_Text3D_GetOpacity00);
   tolua_function(tolua_S,"GetFaceCamera",tolua_UI_Text3D_GetFaceCamera00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"UI","UI","Object",NULL);
  tolua_beginmodule(tolua_S,"UI");
   tolua_function(tolua_S,"SetCursor",tolua_UI_UI_SetCursor00);
   tolua_function(tolua_S,"SetFocusElement",tolua_UI_UI_SetFocusElement00);
   tolua_function(tolua_S,"SetModalElement",tolua_UI_UI_SetModalElement00);
   tolua_function(tolua_S,"Clear",tolua_UI_UI_Clear00);
   tolua_function(tolua_S,"Update",tolua_UI_UI_Update00);
   tolua_function(tolua_S,"RenderUpdate",tolua_UI_UI_RenderUpdate00);
   tolua_function(tolua_S,"Render",tolua_UI_UI_Render00);
   tolua_function(tolua_S,"DebugDraw",tolua_UI_UI_DebugDraw00);
   tolua_function(tolua_S,"SaveLayout",tolua_UI_UI_SaveLayout00);
   tolua_function(tolua_S,"SetClipBoardText",tolua_UI_UI_SetClipBoardText00);
   tolua_function(tolua_S,"SetNonFocusedMouseWheel",tolua_UI_UI_SetNonFocusedMouseWheel00);
   tolua_function(tolua_S,"GetRoot",tolua_UI_UI_GetRoot00);
   tolua_function(tolua_S,"GetRootModalElement",tolua_UI_UI_GetRootModalElement00);
   tolua_function(tolua_S,"GetCursor",tolua_UI_UI_GetCursor00);
   tolua_function(tolua_S,"GetElementAt",tolua_UI_UI_GetElementAt00);
   tolua_function(tolua_S,"GetElementAt",tolua_UI_UI_GetElementAt01);
   tolua_function(tolua_S,"GetFocusElement",tolua_UI_UI_GetFocusElement00);
   tolua_function(tolua_S,"GetFrontElement",tolua_UI_UI_GetFrontElement00);
   tolua_function(tolua_S,"GetCursorPosition",tolua_UI_UI_GetCursorPosition00);
   tolua_function(tolua_S,"GetClipBoardText",tolua_UI_UI_GetClipBoardText00);
   tolua_function(tolua_S,"IsNonFocusedMouseWheel",tolua_UI_UI_IsNonFocusedMouseWheel00);
   tolua_function(tolua_S,"HasModalElement",tolua_UI_UI_HasModalElement00);
  tolua_endmodule(tolua_S);
  tolua_function(tolua_S,"GetUI",tolua_UI_GetUI00);
  tolua_constant(tolua_S,"HA_LEFT",HA_LEFT);
  tolua_constant(tolua_S,"HA_CENTER",HA_CENTER);
  tolua_constant(tolua_S,"HA_RIGHT",HA_RIGHT);
  tolua_constant(tolua_S,"VA_TOP",VA_TOP);
  tolua_constant(tolua_S,"VA_CENTER",VA_CENTER);
  tolua_constant(tolua_S,"VA_BOTTOM",VA_BOTTOM);
  tolua_constant(tolua_S,"C_TOPLEFT",C_TOPLEFT);
  tolua_constant(tolua_S,"C_TOPRIGHT",C_TOPRIGHT);
  tolua_constant(tolua_S,"C_BOTTOMLEFT",C_BOTTOMLEFT);
  tolua_constant(tolua_S,"C_BOTTOMRIGHT",C_BOTTOMRIGHT);
  tolua_constant(tolua_S,"MAX_UIELEMENT_CORNERS",MAX_UIELEMENT_CORNERS);
  tolua_constant(tolua_S,"O_HORIZONTAL",O_HORIZONTAL);
  tolua_constant(tolua_S,"O_VERTICAL",O_VERTICAL);
  tolua_constant(tolua_S,"FM_NOTFOCUSABLE",FM_NOTFOCUSABLE);
  tolua_constant(tolua_S,"FM_RESETFOCUS",FM_RESETFOCUS);
  tolua_constant(tolua_S,"FM_FOCUSABLE",FM_FOCUSABLE);
  tolua_constant(tolua_S,"FM_FOCUSABLE_DEFOCUSABLE",FM_FOCUSABLE_DEFOCUSABLE);
  tolua_constant(tolua_S,"LM_FREE",LM_FREE);
  tolua_constant(tolua_S,"LM_HORIZONTAL",LM_HORIZONTAL);
  tolua_constant(tolua_S,"LM_VERTICAL",LM_VERTICAL);
  tolua_constant(tolua_S,"TM_BREADTH_FIRST",TM_BREADTH_FIRST);
  tolua_constant(tolua_S,"TM_DEPTH_FIRST",TM_DEPTH_FIRST);
  tolua_variable(tolua_S,"DD_DISABLED",tolua_get_DD_DISABLED,NULL);
  tolua_variable(tolua_S,"DD_SOURCE",tolua_get_DD_SOURCE,NULL);
  tolua_variable(tolua_S,"DD_TARGET",tolua_get_DD_TARGET,NULL);
  tolua_variable(tolua_S,"DD_SOURCE_AND_TARGET",tolua_get_DD_SOURCE_AND_TARGET,NULL);
  tolua_cclass(tolua_S,"UIElement","UIElement","Serializable",NULL);
  tolua_beginmodule(tolua_S,"UIElement");
   tolua_function(tolua_S,"SetName",tolua_UI_UIElement_SetName00);
   tolua_function(tolua_S,"SetPosition",tolua_UI_UIElement_SetPosition00);
   tolua_function(tolua_S,"SetPosition",tolua_UI_UIElement_SetPosition01);
   tolua_function(tolua_S,"SetSize",tolua_UI_UIElement_SetSize00);
   tolua_function(tolua_S,"SetSize",tolua_UI_UIElement_SetSize01);
   tolua_function(tolua_S,"SetWidth",tolua_UI_UIElement_SetWidth00);
   tolua_function(tolua_S,"SetHeight",tolua_UI_UIElement_SetHeight00);
   tolua_function(tolua_S,"SetMinSize",tolua_UI_UIElement_SetMinSize00);
   tolua_function(tolua_S,"SetMinSize",tolua_UI_UIElement_SetMinSize01);
   tolua_function(tolua_S,"SetMinWidth",tolua_UI_UIElement_SetMinWidth00);
   tolua_function(tolua_S,"SetMinHeight",tolua_UI_UIElement_SetMinHeight00);
   tolua_function(tolua_S,"SetMaxSize",tolua_UI_UIElement_SetMaxSize00);
   tolua_function(tolua_S,"SetMaxSize",tolua_UI_UIElement_SetMaxSize01);
   tolua_function(tolua_S,"SetMaxWidth",tolua_UI_UIElement_SetMaxWidth00);
   tolua_function(tolua_S,"SetMaxHeight",tolua_UI_UIElement_SetMaxHeight00);
   tolua_function(tolua_S,"SetFixedSize",tolua_UI_UIElement_SetFixedSize00);
   tolua_function(tolua_S,"SetFixedSize",tolua_UI_UIElement_SetFixedSize01);
   tolua_function(tolua_S,"SetFixedWidth",tolua_UI_UIElement_SetFixedWidth00);
   tolua_function(tolua_S,"SetFixedHeight",tolua_UI_UIElement_SetFixedHeight00);
   tolua_function(tolua_S,"SetAlignment",tolua_UI_UIElement_SetAlignment00);
   tolua_function(tolua_S,"SetHorizontalAlignment",tolua_UI_UIElement_SetHorizontalAlignment00);
   tolua_function(tolua_S,"SetVerticalAlignment",tolua_UI_UIElement_SetVerticalAlignment00);
   tolua_function(tolua_S,"SetClipBorder",tolua_UI_UIElement_SetClipBorder00);
   tolua_function(tolua_S,"SetColor",tolua_UI_UIElement_SetColor00);
   tolua_function(tolua_S,"SetColor",tolua_UI_UIElement_SetColor01);
   tolua_function(tolua_S,"SetPriority",tolua_UI_UIElement_SetPriority00);
   tolua_function(tolua_S,"SetOpacity",tolua_UI_UIElement_SetOpacity00);
   tolua_function(tolua_S,"SetBringToFront",tolua_UI_UIElement_SetBringToFront00);
   tolua_function(tolua_S,"SetBringToBack",tolua_UI_UIElement_SetBringToBack00);
   tolua_function(tolua_S,"SetClipChildren",tolua_UI_UIElement_SetClipChildren00);
   tolua_function(tolua_S,"SetSortChildren",tolua_UI_UIElement_SetSortChildren00);
   tolua_function(tolua_S,"SetUseDerivedOpacity",tolua_UI_UIElement_SetUseDerivedOpacity00);
   tolua_function(tolua_S,"SetEnabled",tolua_UI_UIElement_SetEnabled00);
   tolua_function(tolua_S,"SetFocus",tolua_UI_UIElement_SetFocus00);
   tolua_function(tolua_S,"SetSelected",tolua_UI_UIElement_SetSelected00);
   tolua_function(tolua_S,"SetVisible",tolua_UI_UIElement_SetVisible00);
   tolua_function(tolua_S,"SetFocusMode",tolua_UI_UIElement_SetFocusMode00);
   tolua_function(tolua_S,"SetDragDropMode",tolua_UI_UIElement_SetDragDropMode00);
   tolua_function(tolua_S,"SetStyle",tolua_UI_UIElement_SetStyle00);
   tolua_function(tolua_S,"SetStyle",tolua_UI_UIElement_SetStyle01);
   tolua_function(tolua_S,"SetStyleAuto",tolua_UI_UIElement_SetStyleAuto00);
   tolua_function(tolua_S,"SetDefaultStyle",tolua_UI_UIElement_SetDefaultStyle00);
   tolua_function(tolua_S,"SetLayout",tolua_UI_UIElement_SetLayout00);
   tolua_function(tolua_S,"SetLayout",tolua_UI_UIElement_SetLayout01);
   tolua_function(tolua_S,"SetLayoutMode",tolua_UI_UIElement_SetLayoutMode00);
   tolua_function(tolua_S,"SetLayoutSpacing",tolua_UI_UIElement_SetLayoutSpacing00);
   tolua_function(tolua_S,"SetLayoutBorder",tolua_UI_UIElement_SetLayoutBorder00);
   tolua_function(tolua_S,"SetIndent",tolua_UI_UIElement_SetIndent00);
   tolua_function(tolua_S,"SetIndentSpacing",tolua_UI_UIElement_SetIndentSpacing00);
   tolua_function(tolua_S,"UpdateLayout",tolua_UI_UIElement_UpdateLayout00);
   tolua_function(tolua_S,"DisableLayoutUpdate",tolua_UI_UIElement_DisableLayoutUpdate00);
   tolua_function(tolua_S,"EnableLayoutUpdate",tolua_UI_UIElement_EnableLayoutUpdate00);
   tolua_function(tolua_S,"BringToFront",tolua_UI_UIElement_BringToFront00);
   tolua_function(tolua_S,"CreateChild",tolua_UI_UIElement_CreateChild00);
   tolua_function(tolua_S,"CreateChild",tolua_UI_UIElement_CreateChild01);
   tolua_function(tolua_S,"AddChild",tolua_UI_UIElement_AddChild00);
   tolua_function(tolua_S,"InsertChild",tolua_UI_UIElement_InsertChild00);
   tolua_function(tolua_S,"RemoveChild",tolua_UI_UIElement_RemoveChild00);
   tolua_function(tolua_S,"RemoveChildAtIndex",tolua_UI_UIElement_RemoveChildAtIndex00);
   tolua_function(tolua_S,"RemoveAllChildren",tolua_UI_UIElement_RemoveAllChildren00);
   tolua_function(tolua_S,"Remove",tolua_UI_UIElement_Remove00);
   tolua_function(tolua_S,"FindChild",tolua_UI_UIElement_FindChild00);
   tolua_function(tolua_S,"SetParent",tolua_UI_UIElement_SetParent00);
   tolua_function(tolua_S,"SetVar",tolua_UI_UIElement_SetVar00);
   tolua_function(tolua_S,"SetInternal",tolua_UI_UIElement_SetInternal00);
   tolua_function(tolua_S,"SetTraversalMode",tolua_UI_UIElement_SetTraversalMode00);
   tolua_function(tolua_S,"SetElementEventSender",tolua_UI_UIElement_SetElementEventSender00);
   tolua_function(tolua_S,"GetName",tolua_UI_UIElement_GetName00);
   tolua_function(tolua_S,"GetPosition",tolua_UI_UIElement_GetPosition00);
   tolua_function(tolua_S,"GetSize",tolua_UI_UIElement_GetSize00);
   tolua_function(tolua_S,"GetWidth",tolua_UI_UIElement_GetWidth00);
   tolua_function(tolua_S,"GetHeight",tolua_UI_UIElement_GetHeight00);
   tolua_function(tolua_S,"GetMinSize",tolua_UI_UIElement_GetMinSize00);
   tolua_function(tolua_S,"GetMinWidth",tolua_UI_UIElement_GetMinWidth00);
   tolua_function(tolua_S,"GetMinHeight",tolua_UI_UIElement_GetMinHeight00);
   tolua_function(tolua_S,"GetMaxSize",tolua_UI_UIElement_GetMaxSize00);
   tolua_function(tolua_S,"GetMaxWidth",tolua_UI_UIElement_GetMaxWidth00);
   tolua_function(tolua_S,"GetMaxHeight",tolua_UI_UIElement_GetMaxHeight00);
   tolua_function(tolua_S,"IsFixedSize",tolua_UI_UIElement_IsFixedSize00);
   tolua_function(tolua_S,"IsFixedWidth",tolua_UI_UIElement_IsFixedWidth00);
   tolua_function(tolua_S,"IsFixedHeight",tolua_UI_UIElement_IsFixedHeight00);
   tolua_function(tolua_S,"GetChildOffset",tolua_UI_UIElement_GetChildOffset00);
   tolua_function(tolua_S,"GetHorizontalAlignment",tolua_UI_UIElement_GetHorizontalAlignment00);
   tolua_function(tolua_S,"GetVerticalAlignment",tolua_UI_UIElement_GetVerticalAlignment00);
   tolua_function(tolua_S,"GetClipBorder",tolua_UI_UIElement_GetClipBorder00);
   tolua_function(tolua_S,"GetColor",tolua_UI_UIElement_GetColor00);
   tolua_function(tolua_S,"GetPriority",tolua_UI_UIElement_GetPriority00);
   tolua_function(tolua_S,"GetOpacity",tolua_UI_UIElement_GetOpacity00);
   tolua_function(tolua_S,"GetDerivedOpacity",tolua_UI_UIElement_GetDerivedOpacity00);
   tolua_function(tolua_S,"GetBringToFront",tolua_UI_UIElement_GetBringToFront00);
   tolua_function(tolua_S,"GetBringToBack",tolua_UI_UIElement_GetBringToBack00);
   tolua_function(tolua_S,"GetClipChildren",tolua_UI_UIElement_GetClipChildren00);
   tolua_function(tolua_S,"GetSortChildren",tolua_UI_UIElement_GetSortChildren00);
   tolua_function(tolua_S,"GetUseDerivedOpacity",tolua_UI_UIElement_GetUseDerivedOpacity00);
   tolua_function(tolua_S,"HasFocus",tolua_UI_UIElement_HasFocus00);
   tolua_function(tolua_S,"IsEnabled",tolua_UI_UIElement_IsEnabled00);
   tolua_function(tolua_S,"IsSelected",tolua_UI_UIElement_IsSelected00);
   tolua_function(tolua_S,"IsVisible",tolua_UI_UIElement_IsVisible00);
   tolua_function(tolua_S,"IsHovering",tolua_UI_UIElement_IsHovering00);
   tolua_function(tolua_S,"IsInternal",tolua_UI_UIElement_IsInternal00);
   tolua_function(tolua_S,"HasColorGradient",tolua_UI_UIElement_HasColorGradient00);
   tolua_function(tolua_S,"GetFocusMode",tolua_UI_UIElement_GetFocusMode00);
   tolua_function(tolua_S,"GetDragDropMode",tolua_UI_UIElement_GetDragDropMode00);
   tolua_function(tolua_S,"GetAppliedStyle",tolua_UI_UIElement_GetAppliedStyle00);
   tolua_function(tolua_S,"GetDefaultStyle",tolua_UI_UIElement_GetDefaultStyle00);
   tolua_function(tolua_S,"GetLayoutMode",tolua_UI_UIElement_GetLayoutMode00);
   tolua_function(tolua_S,"GetLayoutSpacing",tolua_UI_UIElement_GetLayoutSpacing00);
   tolua_function(tolua_S,"GetLayoutBorder",tolua_UI_UIElement_GetLayoutBorder00);
   tolua_function(tolua_S,"GetNumChildren",tolua_UI_UIElement_GetNumChildren00);
   tolua_function(tolua_S,"GetChild",tolua_UI_UIElement_GetChild00);
   tolua_function(tolua_S,"GetChild",tolua_UI_UIElement_GetChild01);
   tolua_function(tolua_S,"GetChild",tolua_UI_UIElement_GetChild02);
   tolua_function(tolua_S,"GetChild",tolua_UI_UIElement_GetChild03);
   tolua_function(tolua_S,"GetParent",tolua_UI_UIElement_GetParent00);
   tolua_function(tolua_S,"GetRoot",tolua_UI_UIElement_GetRoot00);
   tolua_function(tolua_S,"GetDerivedColor",tolua_UI_UIElement_GetDerivedColor00);
   tolua_function(tolua_S,"ScreenToElement",tolua_UI_UIElement_ScreenToElement00);
   tolua_function(tolua_S,"ElementToScreen",tolua_UI_UIElement_ElementToScreen00);
   tolua_function(tolua_S,"IsInside",tolua_UI_UIElement_IsInside00);
   tolua_function(tolua_S,"IsInsideCombined",tolua_UI_UIElement_IsInsideCombined00);
   tolua_function(tolua_S,"GetCombinedScreenRect",tolua_UI_UIElement_GetCombinedScreenRect00);
   tolua_function(tolua_S,"SortChildren",tolua_UI_UIElement_SortChildren00);
   tolua_function(tolua_S,"GetLayoutMinSize",tolua_UI_UIElement_GetLayoutMinSize00);
   tolua_function(tolua_S,"GetIndent",tolua_UI_UIElement_GetIndent00);
   tolua_function(tolua_S,"GetIndentSpacing",tolua_UI_UIElement_GetIndentSpacing00);
   tolua_function(tolua_S,"GetIndentWidth",tolua_UI_UIElement_GetIndentWidth00);
   tolua_function(tolua_S,"SetChildOffset",tolua_UI_UIElement_SetChildOffset00);
   tolua_function(tolua_S,"SetHovering",tolua_UI_UIElement_SetHovering00);
   tolua_function(tolua_S,"SetTempVisible",tolua_UI_UIElement_SetTempVisible00);
   tolua_function(tolua_S,"AdjustScissor",tolua_UI_UIElement_AdjustScissor00);
   tolua_function(tolua_S,"GetBatchesWithOffset",tolua_UI_UIElement_GetBatchesWithOffset00);
   tolua_function(tolua_S,"GetColorAttr",tolua_UI_UIElement_GetColorAttr00);
   tolua_function(tolua_S,"GetTraversalMode",tolua_UI_UIElement_GetTraversalMode00);
   tolua_function(tolua_S,"IsElementEventSender",tolua_UI_UIElement_IsElementEventSender00);
   tolua_function(tolua_S,"GetElementEventSender",tolua_UI_UIElement_GetElementEventSender00);
  tolua_endmodule(tolua_S);
  tolua_constant(tolua_S,"DRAG_NONE",DRAG_NONE);
  tolua_constant(tolua_S,"DRAG_MOVE",DRAG_MOVE);
  tolua_constant(tolua_S,"DRAG_RESIZE_TOPLEFT",DRAG_RESIZE_TOPLEFT);
  tolua_constant(tolua_S,"DRAG_RESIZE_TOP",DRAG_RESIZE_TOP);
  tolua_constant(tolua_S,"DRAG_RESIZE_TOPRIGHT",DRAG_RESIZE_TOPRIGHT);
  tolua_constant(tolua_S,"DRAG_RESIZE_RIGHT",DRAG_RESIZE_RIGHT);
  tolua_constant(tolua_S,"DRAG_RESIZE_BOTTOMRIGHT",DRAG_RESIZE_BOTTOMRIGHT);
  tolua_constant(tolua_S,"DRAG_RESIZE_BOTTOM",DRAG_RESIZE_BOTTOM);
  tolua_constant(tolua_S,"DRAG_RESIZE_BOTTOMLEFT",DRAG_RESIZE_BOTTOMLEFT);
  tolua_constant(tolua_S,"DRAG_RESIZE_LEFT",DRAG_RESIZE_LEFT);
  tolua_cclass(tolua_S,"Window","Window","BorderImage",NULL);
  tolua_beginmodule(tolua_S,"Window");
   tolua_function(tolua_S,"SetMovable",tolua_UI_Window_SetMovable00);
   tolua_function(tolua_S,"SetResizable",tolua_UI_Window_SetResizable00);
   tolua_function(tolua_S,"SetResizeBorder",tolua_UI_Window_SetResizeBorder00);
   tolua_function(tolua_S,"SetModal",tolua_UI_Window_SetModal00);
   tolua_function(tolua_S,"SetModalShadeColor",tolua_UI_Window_SetModalShadeColor00);
   tolua_function(tolua_S,"SetModalFrameColor",tolua_UI_Window_SetModalFrameColor00);
   tolua_function(tolua_S,"SetModalFrameSize",tolua_UI_Window_SetModalFrameSize00);
   tolua_function(tolua_S,"IsMovable",tolua_UI_Window_IsMovable00);
   tolua_function(tolua_S,"IsResizable",tolua_UI_Window_IsResizable00);
   tolua_function(tolua_S,"GetResizeBorder",tolua_UI_Window_GetResizeBorder00);
   tolua_function(tolua_S,"IsModal",tolua_UI_Window_IsModal00);
   tolua_function(tolua_S,"GetModalShadeColor",tolua_UI_Window_GetModalShadeColor00);
   tolua_function(tolua_S,"GetModalFrameColor",tolua_UI_Window_GetModalFrameColor00);
   tolua_function(tolua_S,"GetModalFrameSize",tolua_UI_Window_GetModalFrameSize00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_UI (lua_State* tolua_S) {
 return tolua_UI_open(tolua_S);
};
#endif

