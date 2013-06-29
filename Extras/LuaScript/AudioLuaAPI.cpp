/*
** Lua binding: Audio
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
TOLUA_API int  tolua_Audio_open (lua_State* tolua_S);

#define TOLUA_RELEASE
#include "AudioLuaAPI.h"
#include "Audio.h"
#include "Sound.h"
#include "SoundListener.h"
#include "SoundSource.h"
#include "SoundSource3D.h"
using namespace Urho3D;
#pragma warning(disable:4800)

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_SoundType (lua_State* tolua_S)
{
 SoundType* self = (SoundType*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"Resource");
 tolua_usertype(tolua_S,"SoundListener");
 tolua_usertype(tolua_S,"SoundType");
 tolua_usertype(tolua_S,"Component");
 tolua_usertype(tolua_S,"Object");
 tolua_usertype(tolua_S,"SoundSource");
 tolua_usertype(tolua_S,"SoundSource3D");
 tolua_usertype(tolua_S,"Sound");
 tolua_usertype(tolua_S,"Audio");
}

/* method: SetMode of class  Audio */
#ifndef TOLUA_DISABLE_tolua_Audio_Audio_SetMode00
static int tolua_Audio_Audio_SetMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Audio",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Audio* self = (Audio*)  tolua_tousertype(tolua_S,1,0);
  int bufferLengthMSec = ((int)  tolua_tonumber(tolua_S,2,0));
  int mixRate = ((int)  tolua_tonumber(tolua_S,3,0));
  bool stereo = ((bool)  tolua_toboolean(tolua_S,4,0));
  bool interpolation = ((bool)  tolua_toboolean(tolua_S,5,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMode'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SetMode(bufferLengthMSec,mixRate,stereo,interpolation);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Update of class  Audio */
#ifndef TOLUA_DISABLE_tolua_Audio_Audio_Update00
static int tolua_Audio_Audio_Update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Audio",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Audio* self = (Audio*)  tolua_tousertype(tolua_S,1,0);
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

/* method: Play of class  Audio */
#ifndef TOLUA_DISABLE_tolua_Audio_Audio_Play00
static int tolua_Audio_Audio_Play00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Audio",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Audio* self = (Audio*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Play'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Play();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Play'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Stop of class  Audio */
#ifndef TOLUA_DISABLE_tolua_Audio_Audio_Stop00
static int tolua_Audio_Audio_Stop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Audio",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Audio* self = (Audio*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Stop'", NULL);
#endif
  {
   self->Stop();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Stop'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMasterGain of class  Audio */
#ifndef TOLUA_DISABLE_tolua_Audio_Audio_SetMasterGain00
static int tolua_Audio_Audio_SetMasterGain00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Audio",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"SoundType",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Audio* self = (Audio*)  tolua_tousertype(tolua_S,1,0);
  SoundType type = *((SoundType*)  tolua_tousertype(tolua_S,2,0));
  float gain = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMasterGain'", NULL);
#endif
  {
   self->SetMasterGain(type,gain);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMasterGain'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetListener of class  Audio */
#ifndef TOLUA_DISABLE_tolua_Audio_Audio_SetListener00
static int tolua_Audio_Audio_SetListener00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Audio",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"SoundListener",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Audio* self = (Audio*)  tolua_tousertype(tolua_S,1,0);
  SoundListener* listener = ((SoundListener*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetListener'", NULL);
#endif
  {
   self->SetListener(listener);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetListener'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: StopSound of class  Audio */
#ifndef TOLUA_DISABLE_tolua_Audio_Audio_StopSound00
static int tolua_Audio_Audio_StopSound00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Audio",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Sound",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Audio* self = (Audio*)  tolua_tousertype(tolua_S,1,0);
  Sound* sound = ((Sound*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'StopSound'", NULL);
#endif
  {
   self->StopSound(sound);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'StopSound'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSampleSize of class  Audio */
#ifndef TOLUA_DISABLE_tolua_Audio_Audio_GetSampleSize00
static int tolua_Audio_Audio_GetSampleSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Audio",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Audio* self = (const Audio*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSampleSize'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetSampleSize();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSampleSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMixRate of class  Audio */
#ifndef TOLUA_DISABLE_tolua_Audio_Audio_GetMixRate00
static int tolua_Audio_Audio_GetMixRate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Audio",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Audio* self = (const Audio*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMixRate'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetMixRate();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMixRate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetInterpolation of class  Audio */
#ifndef TOLUA_DISABLE_tolua_Audio_Audio_GetInterpolation00
static int tolua_Audio_Audio_GetInterpolation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Audio",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Audio* self = (const Audio*)  tolua_tousertype(tolua_S,1,0);
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

/* method: IsStereo of class  Audio */
#ifndef TOLUA_DISABLE_tolua_Audio_Audio_IsStereo00
static int tolua_Audio_Audio_IsStereo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Audio",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Audio* self = (const Audio*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsStereo'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsStereo();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsStereo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsPlaying of class  Audio */
#ifndef TOLUA_DISABLE_tolua_Audio_Audio_IsPlaying00
static int tolua_Audio_Audio_IsPlaying00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Audio",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Audio* self = (const Audio*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsPlaying'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsPlaying();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsPlaying'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsInitialized of class  Audio */
#ifndef TOLUA_DISABLE_tolua_Audio_Audio_IsInitialized00
static int tolua_Audio_Audio_IsInitialized00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Audio",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Audio* self = (const Audio*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetMasterGain of class  Audio */
#ifndef TOLUA_DISABLE_tolua_Audio_Audio_GetMasterGain00
static int tolua_Audio_Audio_GetMasterGain00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Audio",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"SoundType",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Audio* self = (const Audio*)  tolua_tousertype(tolua_S,1,0);
  SoundType type = *((SoundType*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMasterGain'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetMasterGain(type);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMasterGain'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetListener of class  Audio */
#ifndef TOLUA_DISABLE_tolua_Audio_Audio_GetListener00
static int tolua_Audio_Audio_GetListener00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Audio",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Audio* self = (const Audio*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetListener'", NULL);
#endif
  {
   SoundListener* tolua_ret = (SoundListener*)  self->GetListener();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SoundListener");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetListener'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddSoundSource of class  Audio */
#ifndef TOLUA_DISABLE_tolua_Audio_Audio_AddSoundSource00
static int tolua_Audio_Audio_AddSoundSource00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Audio",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"SoundSource",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Audio* self = (Audio*)  tolua_tousertype(tolua_S,1,0);
  SoundSource* soundSource = ((SoundSource*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddSoundSource'", NULL);
#endif
  {
   self->AddSoundSource(soundSource);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddSoundSource'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveSoundSource of class  Audio */
#ifndef TOLUA_DISABLE_tolua_Audio_Audio_RemoveSoundSource00
static int tolua_Audio_Audio_RemoveSoundSource00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Audio",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"SoundSource",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Audio* self = (Audio*)  tolua_tousertype(tolua_S,1,0);
  SoundSource* soundSource = ((SoundSource*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveSoundSource'", NULL);
#endif
  {
   self->RemoveSoundSource(soundSource);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemoveSoundSource'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSoundSourceMasterGain of class  Audio */
#ifndef TOLUA_DISABLE_tolua_Audio_Audio_GetSoundSourceMasterGain00
static int tolua_Audio_Audio_GetSoundSourceMasterGain00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Audio",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"SoundType",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Audio* self = (const Audio*)  tolua_tousertype(tolua_S,1,0);
  SoundType type = *((SoundType*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSoundSourceMasterGain'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetSoundSourceMasterGain(type);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSoundSourceMasterGain'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GetAudio */
#ifndef TOLUA_DISABLE_tolua_Audio_GetAudio00
static int tolua_Audio_GetAudio00(lua_State* tolua_S)
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
   Audio* tolua_ret = (Audio*)  GetAudio();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Audio");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAudio'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFormat of class  Sound */
#ifndef TOLUA_DISABLE_tolua_Audio_Sound_SetFormat00
static int tolua_Audio_Sound_SetFormat00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sound",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Sound* self = (Sound*)  tolua_tousertype(tolua_S,1,0);
  unsigned frequency = ((unsigned)  tolua_tonumber(tolua_S,2,0));
  bool sixteenBit = ((bool)  tolua_toboolean(tolua_S,3,0));
  bool stereo = ((bool)  tolua_toboolean(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFormat'", NULL);
#endif
  {
   self->SetFormat(frequency,sixteenBit,stereo);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFormat'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetLooped of class  Sound */
#ifndef TOLUA_DISABLE_tolua_Audio_Sound_SetLooped00
static int tolua_Audio_Sound_SetLooped00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sound",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Sound* self = (Sound*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLooped'", NULL);
#endif
  {
   self->SetLooped(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLooped'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetLoop of class  Sound */
#ifndef TOLUA_DISABLE_tolua_Audio_Sound_SetLoop00
static int tolua_Audio_Sound_SetLoop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sound",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Sound* self = (Sound*)  tolua_tousertype(tolua_S,1,0);
  unsigned repeatOffset = ((unsigned)  tolua_tonumber(tolua_S,2,0));
  unsigned endOffset = ((unsigned)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLoop'", NULL);
#endif
  {
   self->SetLoop(repeatOffset,endOffset);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLoop'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: FixInterpolation of class  Sound */
#ifndef TOLUA_DISABLE_tolua_Audio_Sound_FixInterpolation00
static int tolua_Audio_Sound_FixInterpolation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sound",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Sound* self = (Sound*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FixInterpolation'", NULL);
#endif
  {
   self->FixInterpolation();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FixInterpolation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLength of class  Sound */
#ifndef TOLUA_DISABLE_tolua_Audio_Sound_GetLength00
static int tolua_Audio_Sound_GetLength00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Sound",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Sound* self = (const Sound*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLength'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetLength();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLength'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetDataSize of class  Sound */
#ifndef TOLUA_DISABLE_tolua_Audio_Sound_GetDataSize00
static int tolua_Audio_Sound_GetDataSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Sound",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Sound* self = (const Sound*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetDataSize'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetDataSize();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDataSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSampleSize of class  Sound */
#ifndef TOLUA_DISABLE_tolua_Audio_Sound_GetSampleSize00
static int tolua_Audio_Sound_GetSampleSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Sound",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Sound* self = (const Sound*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSampleSize'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetSampleSize();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSampleSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFrequency of class  Sound */
#ifndef TOLUA_DISABLE_tolua_Audio_Sound_GetFrequency00
static int tolua_Audio_Sound_GetFrequency00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sound",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Sound* self = (Sound*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFrequency'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetFrequency();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFrequency'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetIntFrequency of class  Sound */
#ifndef TOLUA_DISABLE_tolua_Audio_Sound_GetIntFrequency00
static int tolua_Audio_Sound_GetIntFrequency00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Sound",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Sound* self = (Sound*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetIntFrequency'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetIntFrequency();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetIntFrequency'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsLooped of class  Sound */
#ifndef TOLUA_DISABLE_tolua_Audio_Sound_IsLooped00
static int tolua_Audio_Sound_IsLooped00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Sound",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Sound* self = (const Sound*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsLooped'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsLooped();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsLooped'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsSixteenBit of class  Sound */
#ifndef TOLUA_DISABLE_tolua_Audio_Sound_IsSixteenBit00
static int tolua_Audio_Sound_IsSixteenBit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Sound",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Sound* self = (const Sound*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsSixteenBit'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsSixteenBit();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsSixteenBit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsStereo of class  Sound */
#ifndef TOLUA_DISABLE_tolua_Audio_Sound_IsStereo00
static int tolua_Audio_Sound_IsStereo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Sound",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Sound* self = (const Sound*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsStereo'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsStereo();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsStereo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsCompressed of class  Sound */
#ifndef TOLUA_DISABLE_tolua_Audio_Sound_IsCompressed00
static int tolua_Audio_Sound_IsCompressed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Sound",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Sound* self = (const Sound*)  tolua_tousertype(tolua_S,1,0);
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

/* method: Play of class  SoundSource */
#ifndef TOLUA_DISABLE_tolua_Audio_SoundSource_Play00
static int tolua_Audio_SoundSource_Play00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SoundSource",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Sound",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SoundSource* self = (SoundSource*)  tolua_tousertype(tolua_S,1,0);
  Sound* sound = ((Sound*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Play'", NULL);
#endif
  {
   self->Play(sound);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Play'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Play of class  SoundSource */
#ifndef TOLUA_DISABLE_tolua_Audio_SoundSource_Play01
static int tolua_Audio_SoundSource_Play01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SoundSource",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Sound",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  SoundSource* self = (SoundSource*)  tolua_tousertype(tolua_S,1,0);
  Sound* sound = ((Sound*)  tolua_tousertype(tolua_S,2,0));
  float frequency = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Play'", NULL);
#endif
  {
   self->Play(sound,frequency);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Audio_SoundSource_Play00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: Play of class  SoundSource */
#ifndef TOLUA_DISABLE_tolua_Audio_SoundSource_Play02
static int tolua_Audio_SoundSource_Play02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SoundSource",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Sound",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  SoundSource* self = (SoundSource*)  tolua_tousertype(tolua_S,1,0);
  Sound* sound = ((Sound*)  tolua_tousertype(tolua_S,2,0));
  float frequency = ((float)  tolua_tonumber(tolua_S,3,0));
  float gain = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Play'", NULL);
#endif
  {
   self->Play(sound,frequency,gain);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Audio_SoundSource_Play01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: Play of class  SoundSource */
#ifndef TOLUA_DISABLE_tolua_Audio_SoundSource_Play03
static int tolua_Audio_SoundSource_Play03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SoundSource",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Sound",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  SoundSource* self = (SoundSource*)  tolua_tousertype(tolua_S,1,0);
  Sound* sound = ((Sound*)  tolua_tousertype(tolua_S,2,0));
  float frequency = ((float)  tolua_tonumber(tolua_S,3,0));
  float gain = ((float)  tolua_tonumber(tolua_S,4,0));
  float panning = ((float)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Play'", NULL);
#endif
  {
   self->Play(sound,frequency,gain,panning);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Audio_SoundSource_Play02(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: Stop of class  SoundSource */
#ifndef TOLUA_DISABLE_tolua_Audio_SoundSource_Stop00
static int tolua_Audio_SoundSource_Stop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SoundSource",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SoundSource* self = (SoundSource*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Stop'", NULL);
#endif
  {
   self->Stop();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Stop'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetSoundType of class  SoundSource */
#ifndef TOLUA_DISABLE_tolua_Audio_SoundSource_SetSoundType00
static int tolua_Audio_SoundSource_SetSoundType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SoundSource",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"SoundType",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SoundSource* self = (SoundSource*)  tolua_tousertype(tolua_S,1,0);
  SoundType type = *((SoundType*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetSoundType'", NULL);
#endif
  {
   self->SetSoundType(type);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetSoundType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFrequency of class  SoundSource */
#ifndef TOLUA_DISABLE_tolua_Audio_SoundSource_SetFrequency00
static int tolua_Audio_SoundSource_SetFrequency00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SoundSource",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SoundSource* self = (SoundSource*)  tolua_tousertype(tolua_S,1,0);
  float frequency = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFrequency'", NULL);
#endif
  {
   self->SetFrequency(frequency);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFrequency'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetGain of class  SoundSource */
#ifndef TOLUA_DISABLE_tolua_Audio_SoundSource_SetGain00
static int tolua_Audio_SoundSource_SetGain00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SoundSource",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SoundSource* self = (SoundSource*)  tolua_tousertype(tolua_S,1,0);
  float gain = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetGain'", NULL);
#endif
  {
   self->SetGain(gain);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetGain'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetAttenuation of class  SoundSource */
#ifndef TOLUA_DISABLE_tolua_Audio_SoundSource_SetAttenuation00
static int tolua_Audio_SoundSource_SetAttenuation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SoundSource",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SoundSource* self = (SoundSource*)  tolua_tousertype(tolua_S,1,0);
  float attenuation = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetAttenuation'", NULL);
#endif
  {
   self->SetAttenuation(attenuation);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetAttenuation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetPanning of class  SoundSource */
#ifndef TOLUA_DISABLE_tolua_Audio_SoundSource_SetPanning00
static int tolua_Audio_SoundSource_SetPanning00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SoundSource",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SoundSource* self = (SoundSource*)  tolua_tousertype(tolua_S,1,0);
  float panning = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetPanning'", NULL);
#endif
  {
   self->SetPanning(panning);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetPanning'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetAutoRemove of class  SoundSource */
#ifndef TOLUA_DISABLE_tolua_Audio_SoundSource_SetAutoRemove00
static int tolua_Audio_SoundSource_SetAutoRemove00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SoundSource",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SoundSource* self = (SoundSource*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetAutoRemove'", NULL);
#endif
  {
   self->SetAutoRemove(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetAutoRemove'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetPlayPosition of class  SoundSource */
#ifndef TOLUA_DISABLE_tolua_Audio_SoundSource_SetPlayPosition00
static int tolua_Audio_SoundSource_SetPlayPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SoundSource",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SoundSource* self = (SoundSource*)  tolua_tousertype(tolua_S,1,0);
  signed char* pos = ((signed char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetPlayPosition'", NULL);
#endif
  {
   self->SetPlayPosition(pos);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetPlayPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSound of class  SoundSource */
#ifndef TOLUA_DISABLE_tolua_Audio_SoundSource_GetSound00
static int tolua_Audio_SoundSource_GetSound00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const SoundSource",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const SoundSource* self = (const SoundSource*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSound'", NULL);
#endif
  {
   Sound* tolua_ret = (Sound*)  self->GetSound();
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

/* method: GetPlayPosition of class  SoundSource */
#ifndef TOLUA_DISABLE_tolua_Audio_SoundSource_GetPlayPosition00
static int tolua_Audio_SoundSource_GetPlayPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const SoundSource",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const SoundSource* self = (const SoundSource*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPlayPosition'", NULL);
#endif
  {
   volatile signed char* tolua_ret = (volatile signed char*)  self->GetPlayPosition();
   tolua_pushstring(tolua_S,(const char*)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPlayPosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSoundType of class  SoundSource */
#ifndef TOLUA_DISABLE_tolua_Audio_SoundSource_GetSoundType00
static int tolua_Audio_SoundSource_GetSoundType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const SoundSource",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const SoundSource* self = (const SoundSource*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSoundType'", NULL);
#endif
  {
   SoundType tolua_ret = (SoundType)  self->GetSoundType();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((SoundType)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"SoundType");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(SoundType));
     tolua_pushusertype(tolua_S,tolua_obj,"SoundType");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSoundType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTimePosition of class  SoundSource */
#ifndef TOLUA_DISABLE_tolua_Audio_SoundSource_GetTimePosition00
static int tolua_Audio_SoundSource_GetTimePosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const SoundSource",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const SoundSource* self = (const SoundSource*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTimePosition'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetTimePosition();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTimePosition'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFrequency of class  SoundSource */
#ifndef TOLUA_DISABLE_tolua_Audio_SoundSource_GetFrequency00
static int tolua_Audio_SoundSource_GetFrequency00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const SoundSource",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const SoundSource* self = (const SoundSource*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFrequency'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetFrequency();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFrequency'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetGain of class  SoundSource */
#ifndef TOLUA_DISABLE_tolua_Audio_SoundSource_GetGain00
static int tolua_Audio_SoundSource_GetGain00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const SoundSource",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const SoundSource* self = (const SoundSource*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetGain'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetGain();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetGain'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAttenuation of class  SoundSource */
#ifndef TOLUA_DISABLE_tolua_Audio_SoundSource_GetAttenuation00
static int tolua_Audio_SoundSource_GetAttenuation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const SoundSource",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const SoundSource* self = (const SoundSource*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAttenuation'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetAttenuation();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAttenuation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetPanning of class  SoundSource */
#ifndef TOLUA_DISABLE_tolua_Audio_SoundSource_GetPanning00
static int tolua_Audio_SoundSource_GetPanning00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const SoundSource",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const SoundSource* self = (const SoundSource*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPanning'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetPanning();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPanning'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAutoRemove of class  SoundSource */
#ifndef TOLUA_DISABLE_tolua_Audio_SoundSource_GetAutoRemove00
static int tolua_Audio_SoundSource_GetAutoRemove00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const SoundSource",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const SoundSource* self = (const SoundSource*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAutoRemove'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetAutoRemove();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAutoRemove'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsPlaying of class  SoundSource */
#ifndef TOLUA_DISABLE_tolua_Audio_SoundSource_IsPlaying00
static int tolua_Audio_SoundSource_IsPlaying00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const SoundSource",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const SoundSource* self = (const SoundSource*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsPlaying'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsPlaying();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsPlaying'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: PlayLockless of class  SoundSource */
#ifndef TOLUA_DISABLE_tolua_Audio_SoundSource_PlayLockless00
static int tolua_Audio_SoundSource_PlayLockless00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SoundSource",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Sound",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SoundSource* self = (SoundSource*)  tolua_tousertype(tolua_S,1,0);
  Sound* sound = ((Sound*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'PlayLockless'", NULL);
#endif
  {
   self->PlayLockless(sound);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'PlayLockless'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: StopLockless of class  SoundSource */
#ifndef TOLUA_DISABLE_tolua_Audio_SoundSource_StopLockless00
static int tolua_Audio_SoundSource_StopLockless00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SoundSource",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SoundSource* self = (SoundSource*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'StopLockless'", NULL);
#endif
  {
   self->StopLockless();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'StopLockless'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetDistanceAttenuation of class  SoundSource3D */
#ifndef TOLUA_DISABLE_tolua_Audio_SoundSource3D_SetDistanceAttenuation00
static int tolua_Audio_SoundSource3D_SetDistanceAttenuation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SoundSource3D",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SoundSource3D* self = (SoundSource3D*)  tolua_tousertype(tolua_S,1,0);
  float nearDistance = ((float)  tolua_tonumber(tolua_S,2,0));
  float farDistance = ((float)  tolua_tonumber(tolua_S,3,0));
  float rolloffFactor = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetDistanceAttenuation'", NULL);
#endif
  {
   self->SetDistanceAttenuation(nearDistance,farDistance,rolloffFactor);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetDistanceAttenuation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetNearDistance of class  SoundSource3D */
#ifndef TOLUA_DISABLE_tolua_Audio_SoundSource3D_SetNearDistance00
static int tolua_Audio_SoundSource3D_SetNearDistance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SoundSource3D",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SoundSource3D* self = (SoundSource3D*)  tolua_tousertype(tolua_S,1,0);
  float distance = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetNearDistance'", NULL);
#endif
  {
   self->SetNearDistance(distance);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetNearDistance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFarDistance of class  SoundSource3D */
#ifndef TOLUA_DISABLE_tolua_Audio_SoundSource3D_SetFarDistance00
static int tolua_Audio_SoundSource3D_SetFarDistance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SoundSource3D",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SoundSource3D* self = (SoundSource3D*)  tolua_tousertype(tolua_S,1,0);
  float distance = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFarDistance'", NULL);
#endif
  {
   self->SetFarDistance(distance);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFarDistance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetRolloffFactor of class  SoundSource3D */
#ifndef TOLUA_DISABLE_tolua_Audio_SoundSource3D_SetRolloffFactor00
static int tolua_Audio_SoundSource3D_SetRolloffFactor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SoundSource3D",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SoundSource3D* self = (SoundSource3D*)  tolua_tousertype(tolua_S,1,0);
  float factor = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetRolloffFactor'", NULL);
#endif
  {
   self->SetRolloffFactor(factor);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetRolloffFactor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: CalculateAttenuation of class  SoundSource3D */
#ifndef TOLUA_DISABLE_tolua_Audio_SoundSource3D_CalculateAttenuation00
static int tolua_Audio_SoundSource3D_CalculateAttenuation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SoundSource3D",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SoundSource3D* self = (SoundSource3D*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'CalculateAttenuation'", NULL);
#endif
  {
   self->CalculateAttenuation();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'CalculateAttenuation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNearDistance of class  SoundSource3D */
#ifndef TOLUA_DISABLE_tolua_Audio_SoundSource3D_GetNearDistance00
static int tolua_Audio_SoundSource3D_GetNearDistance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const SoundSource3D",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const SoundSource3D* self = (const SoundSource3D*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNearDistance'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetNearDistance();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNearDistance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFarDistance of class  SoundSource3D */
#ifndef TOLUA_DISABLE_tolua_Audio_SoundSource3D_GetFarDistance00
static int tolua_Audio_SoundSource3D_GetFarDistance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const SoundSource3D",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const SoundSource3D* self = (const SoundSource3D*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFarDistance'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetFarDistance();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFarDistance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RollAngleoffFactor of class  SoundSource3D */
#ifndef TOLUA_DISABLE_tolua_Audio_SoundSource3D_RollAngleoffFactor00
static int tolua_Audio_SoundSource3D_RollAngleoffFactor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const SoundSource3D",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const SoundSource3D* self = (const SoundSource3D*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RollAngleoffFactor'", NULL);
#endif
  {
   float tolua_ret = (float)  self->RollAngleoffFactor();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RollAngleoffFactor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_Audio_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_cclass(tolua_S,"Audio","Audio","Object",NULL);
  tolua_beginmodule(tolua_S,"Audio");
   tolua_function(tolua_S,"SetMode",tolua_Audio_Audio_SetMode00);
   tolua_function(tolua_S,"Update",tolua_Audio_Audio_Update00);
   tolua_function(tolua_S,"Play",tolua_Audio_Audio_Play00);
   tolua_function(tolua_S,"Stop",tolua_Audio_Audio_Stop00);
   tolua_function(tolua_S,"SetMasterGain",tolua_Audio_Audio_SetMasterGain00);
   tolua_function(tolua_S,"SetListener",tolua_Audio_Audio_SetListener00);
   tolua_function(tolua_S,"StopSound",tolua_Audio_Audio_StopSound00);
   tolua_function(tolua_S,"GetSampleSize",tolua_Audio_Audio_GetSampleSize00);
   tolua_function(tolua_S,"GetMixRate",tolua_Audio_Audio_GetMixRate00);
   tolua_function(tolua_S,"GetInterpolation",tolua_Audio_Audio_GetInterpolation00);
   tolua_function(tolua_S,"IsStereo",tolua_Audio_Audio_IsStereo00);
   tolua_function(tolua_S,"IsPlaying",tolua_Audio_Audio_IsPlaying00);
   tolua_function(tolua_S,"IsInitialized",tolua_Audio_Audio_IsInitialized00);
   tolua_function(tolua_S,"GetMasterGain",tolua_Audio_Audio_GetMasterGain00);
   tolua_function(tolua_S,"GetListener",tolua_Audio_Audio_GetListener00);
   tolua_function(tolua_S,"AddSoundSource",tolua_Audio_Audio_AddSoundSource00);
   tolua_function(tolua_S,"RemoveSoundSource",tolua_Audio_Audio_RemoveSoundSource00);
   tolua_function(tolua_S,"GetSoundSourceMasterGain",tolua_Audio_Audio_GetSoundSourceMasterGain00);
  tolua_endmodule(tolua_S);
  tolua_function(tolua_S,"GetAudio",tolua_Audio_GetAudio00);
  tolua_cclass(tolua_S,"Sound","Sound","Resource",NULL);
  tolua_beginmodule(tolua_S,"Sound");
   tolua_function(tolua_S,"SetFormat",tolua_Audio_Sound_SetFormat00);
   tolua_function(tolua_S,"SetLooped",tolua_Audio_Sound_SetLooped00);
   tolua_function(tolua_S,"SetLoop",tolua_Audio_Sound_SetLoop00);
   tolua_function(tolua_S,"FixInterpolation",tolua_Audio_Sound_FixInterpolation00);
   tolua_function(tolua_S,"GetLength",tolua_Audio_Sound_GetLength00);
   tolua_function(tolua_S,"GetDataSize",tolua_Audio_Sound_GetDataSize00);
   tolua_function(tolua_S,"GetSampleSize",tolua_Audio_Sound_GetSampleSize00);
   tolua_function(tolua_S,"GetFrequency",tolua_Audio_Sound_GetFrequency00);
   tolua_function(tolua_S,"GetIntFrequency",tolua_Audio_Sound_GetIntFrequency00);
   tolua_function(tolua_S,"IsLooped",tolua_Audio_Sound_IsLooped00);
   tolua_function(tolua_S,"IsSixteenBit",tolua_Audio_Sound_IsSixteenBit00);
   tolua_function(tolua_S,"IsStereo",tolua_Audio_Sound_IsStereo00);
   tolua_function(tolua_S,"IsCompressed",tolua_Audio_Sound_IsCompressed00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"SoundListener","SoundListener","Component",NULL);
  tolua_beginmodule(tolua_S,"SoundListener");
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"SoundSource","SoundSource","Component",NULL);
  tolua_beginmodule(tolua_S,"SoundSource");
   tolua_function(tolua_S,"Play",tolua_Audio_SoundSource_Play00);
   tolua_function(tolua_S,"Play",tolua_Audio_SoundSource_Play01);
   tolua_function(tolua_S,"Play",tolua_Audio_SoundSource_Play02);
   tolua_function(tolua_S,"Play",tolua_Audio_SoundSource_Play03);
   tolua_function(tolua_S,"Stop",tolua_Audio_SoundSource_Stop00);
   tolua_function(tolua_S,"SetSoundType",tolua_Audio_SoundSource_SetSoundType00);
   tolua_function(tolua_S,"SetFrequency",tolua_Audio_SoundSource_SetFrequency00);
   tolua_function(tolua_S,"SetGain",tolua_Audio_SoundSource_SetGain00);
   tolua_function(tolua_S,"SetAttenuation",tolua_Audio_SoundSource_SetAttenuation00);
   tolua_function(tolua_S,"SetPanning",tolua_Audio_SoundSource_SetPanning00);
   tolua_function(tolua_S,"SetAutoRemove",tolua_Audio_SoundSource_SetAutoRemove00);
   tolua_function(tolua_S,"SetPlayPosition",tolua_Audio_SoundSource_SetPlayPosition00);
   tolua_function(tolua_S,"GetSound",tolua_Audio_SoundSource_GetSound00);
   tolua_function(tolua_S,"GetPlayPosition",tolua_Audio_SoundSource_GetPlayPosition00);
   tolua_function(tolua_S,"GetSoundType",tolua_Audio_SoundSource_GetSoundType00);
   tolua_function(tolua_S,"GetTimePosition",tolua_Audio_SoundSource_GetTimePosition00);
   tolua_function(tolua_S,"GetFrequency",tolua_Audio_SoundSource_GetFrequency00);
   tolua_function(tolua_S,"GetGain",tolua_Audio_SoundSource_GetGain00);
   tolua_function(tolua_S,"GetAttenuation",tolua_Audio_SoundSource_GetAttenuation00);
   tolua_function(tolua_S,"GetPanning",tolua_Audio_SoundSource_GetPanning00);
   tolua_function(tolua_S,"GetAutoRemove",tolua_Audio_SoundSource_GetAutoRemove00);
   tolua_function(tolua_S,"IsPlaying",tolua_Audio_SoundSource_IsPlaying00);
   tolua_function(tolua_S,"PlayLockless",tolua_Audio_SoundSource_PlayLockless00);
   tolua_function(tolua_S,"StopLockless",tolua_Audio_SoundSource_StopLockless00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"SoundSource3D","SoundSource3D","SoundSource",NULL);
  tolua_beginmodule(tolua_S,"SoundSource3D");
   tolua_function(tolua_S,"SetDistanceAttenuation",tolua_Audio_SoundSource3D_SetDistanceAttenuation00);
   tolua_function(tolua_S,"SetNearDistance",tolua_Audio_SoundSource3D_SetNearDistance00);
   tolua_function(tolua_S,"SetFarDistance",tolua_Audio_SoundSource3D_SetFarDistance00);
   tolua_function(tolua_S,"SetRolloffFactor",tolua_Audio_SoundSource3D_SetRolloffFactor00);
   tolua_function(tolua_S,"CalculateAttenuation",tolua_Audio_SoundSource3D_CalculateAttenuation00);
   tolua_function(tolua_S,"GetNearDistance",tolua_Audio_SoundSource3D_GetNearDistance00);
   tolua_function(tolua_S,"GetFarDistance",tolua_Audio_SoundSource3D_GetFarDistance00);
   tolua_function(tolua_S,"RollAngleoffFactor",tolua_Audio_SoundSource3D_RollAngleoffFactor00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_Audio (lua_State* tolua_S) {
 return tolua_Audio_open(tolua_S);
};
#endif

