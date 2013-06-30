/*
** Lua binding: Graphics
** Generated automatically by tolua++-1.0.92 on 06/30/13 11:31:49.
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
TOLUA_API int  tolua_Graphics_open (lua_State* tolua_S);

#define TOLUA_RELEASE
#include "GraphicsLuaAPI.h"
#include "AnimatedModel.h"
#include "Animation.h"
#include "AnimationController.h"
#include "AnimationState.h"
#include "BillboardSet.h"
#include "Camera.h"
#include "DebugRenderer.h"
#include "DecalSet.h"
#include "Drawable.h"
#include "Graphics.h"
#include "GraphicsDefs.h"
#include "Light.h"
#include "Material.h"
#include "Model.h"
#include "Octree.h"
#include "ParticleEmitter.h"
#include "Renderer.h"
#include "RenderSurface.h"
#include "Skeleton.h"
#include "Skybox.h"
#include "StaticModel.h"
#include "Technique.h"
#include "Terrain.h"
#include "TerrainPatch.h"
#include "Texture.h"
#include "Texture2D.h"
#include "TextureCube.h"
#include "Zone.h"
using namespace Urho3D;
#pragma warning(disable:4800)

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_ColorFrame (lua_State* tolua_S)
{
 ColorFrame* self = (ColorFrame*) tolua_tousertype(tolua_S,1,0);
  Mtolua_delete(self);
  return 0;
}

static int tolua_collect_String (lua_State* tolua_S)
{
 String* self = (String*) tolua_tousertype(tolua_S,1,0);
  Mtolua_delete(self);
  return 0;
}

static int tolua_collect_Color (lua_State* tolua_S)
{
 Color* self = (Color*) tolua_tousertype(tolua_S,1,0);
  Mtolua_delete(self);
  return 0;
}

static int tolua_collect_AnimationState (lua_State* tolua_S)
{
 AnimationState* self = (AnimationState*) tolua_tousertype(tolua_S,1,0);
  Mtolua_delete(self);
  return 0;
}

static int tolua_collect_StringHash (lua_State* tolua_S)
{
 StringHash* self = (StringHash*) tolua_tousertype(tolua_S,1,0);
  Mtolua_delete(self);
  return 0;
}

static int tolua_collect_Ray (lua_State* tolua_S)
{
 Ray* self = (Ray*) tolua_tousertype(tolua_S,1,0);
  Mtolua_delete(self);
  return 0;
}

static int tolua_collect_Frustum (lua_State* tolua_S)
{
 Frustum* self = (Frustum*) tolua_tousertype(tolua_S,1,0);
  Mtolua_delete(self);
  return 0;
}

static int tolua_collect_Vector2 (lua_State* tolua_S)
{
 Vector2* self = (Vector2*) tolua_tousertype(tolua_S,1,0);
  Mtolua_delete(self);
  return 0;
}

static int tolua_collect_TextureFrame (lua_State* tolua_S)
{
 TextureFrame* self = (TextureFrame*) tolua_tousertype(tolua_S,1,0);
  Mtolua_delete(self);
  return 0;
}

static int tolua_collect_Bone (lua_State* tolua_S)
{
 Bone* self = (Bone*) tolua_tousertype(tolua_S,1,0);
  Mtolua_delete(self);
  return 0;
}

static int tolua_collect_Matrix4 (lua_State* tolua_S)
{
 Matrix4* self = (Matrix4*) tolua_tousertype(tolua_S,1,0);
  Mtolua_delete(self);
  return 0;
}

static int tolua_collect_Vector3 (lua_State* tolua_S)
{
 Vector3* self = (Vector3*) tolua_tousertype(tolua_S,1,0);
  Mtolua_delete(self);
  return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"ColorFrame");
 tolua_usertype(tolua_S,"Octant");
 tolua_usertype(tolua_S,"Component");
 tolua_usertype(tolua_S,"Node");
 tolua_usertype(tolua_S,"Light");
 tolua_usertype(tolua_S,"Pass");
 tolua_usertype(tolua_S,"Texture2D");
 tolua_usertype(tolua_S,"Graphics");
 tolua_usertype(tolua_S,"IntVector2");
 tolua_usertype(tolua_S,"AnimationController");
 tolua_usertype(tolua_S,"String");
 tolua_usertype(tolua_S,"ParticleEmitter");
 tolua_usertype(tolua_S,"Color");
 tolua_usertype(tolua_S,"Image");
 tolua_usertype(tolua_S,"FrameInfo");
 tolua_usertype(tolua_S,"Material");
 tolua_usertype(tolua_S,"TechniqueEntry");
 tolua_usertype(tolua_S,"Vector4");
 tolua_usertype(tolua_S,"DecalSet");
 tolua_usertype(tolua_S,"StaticModel");
 tolua_usertype(tolua_S,"Animation");
 tolua_usertype(tolua_S,"VertexBuffer");
 tolua_usertype(tolua_S,"Ray");
 tolua_usertype(tolua_S,"Sphere");
 tolua_usertype(tolua_S,"Frustum");
 tolua_usertype(tolua_S,"Vector2");
 tolua_usertype(tolua_S,"Matrix3x4");
 tolua_usertype(tolua_S,"CascadeParameters");
 tolua_usertype(tolua_S,"Skeleton");
 tolua_usertype(tolua_S,"Bone");
 tolua_usertype(tolua_S,"Renderer");
 tolua_usertype(tolua_S,"Vector3");
 tolua_usertype(tolua_S,"Terrain");
 tolua_usertype(tolua_S,"AnimationState");
 tolua_usertype(tolua_S,"ModelMorph");
 tolua_usertype(tolua_S,"Camera");
 tolua_usertype(tolua_S,"Object");
 tolua_usertype(tolua_S,"TextureFrame");
 tolua_usertype(tolua_S,"Geometry");
 tolua_usertype(tolua_S,"Quaternion");
 tolua_usertype(tolua_S,"Resource");
 tolua_usertype(tolua_S,"OctreeQuery");
 tolua_usertype(tolua_S,"Zone");
 tolua_usertype(tolua_S,"RenderSurface");
 tolua_usertype(tolua_S,"TextureCube");
 tolua_usertype(tolua_S,"Texture");
 tolua_usertype(tolua_S,"Drawable");
 tolua_usertype(tolua_S,"BiasParameters");
 tolua_usertype(tolua_S,"DebugRenderer");
 tolua_usertype(tolua_S,"TerrainPatch");
 tolua_usertype(tolua_S,"ShaderVariation");
 tolua_usertype(tolua_S,"BoundingBox");
 tolua_usertype(tolua_S,"Rect");
 tolua_usertype(tolua_S,"AnimationTrack");
 tolua_usertype(tolua_S,"Viewport");
 tolua_usertype(tolua_S,"Technique");
 tolua_usertype(tolua_S,"Skybox");
 tolua_usertype(tolua_S,"AnimatedModel");
 tolua_usertype(tolua_S,"BillboardSet");
 tolua_usertype(tolua_S,"Polyhedron");
 tolua_usertype(tolua_S,"RayOctreeQuery");
 tolua_usertype(tolua_S,"Octree");
 tolua_usertype(tolua_S,"StringHash");
 tolua_usertype(tolua_S,"FocusParameters");
 tolua_usertype(tolua_S,"XMLFile");
 tolua_usertype(tolua_S,"Matrix4");
 tolua_usertype(tolua_S,"RenderPath");
 tolua_usertype(tolua_S,"Model");
}

/* method: SetModel of class  AnimatedModel */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimatedModel_SetModel00
static int tolua_Graphics_AnimatedModel_SetModel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimatedModel",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Model",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimatedModel* self = (AnimatedModel*)  tolua_tousertype(tolua_S,1,0);
  Model* model = ((Model*)  tolua_tousertype(tolua_S,2,0));
  bool createBones = ((bool)  tolua_toboolean(tolua_S,3,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetModel'", NULL);
#endif
  {
   self->SetModel(model,createBones);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetModel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddAnimationState of class  AnimatedModel */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimatedModel_AddAnimationState00
static int tolua_Graphics_AnimatedModel_AddAnimationState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimatedModel",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Animation",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimatedModel* self = (AnimatedModel*)  tolua_tousertype(tolua_S,1,0);
  Animation* animation = ((Animation*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddAnimationState'", NULL);
#endif
  {
   AnimationState* tolua_ret = (AnimationState*)  self->AddAnimationState(animation);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"AnimationState");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddAnimationState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveAnimationState of class  AnimatedModel */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimatedModel_RemoveAnimationState00
static int tolua_Graphics_AnimatedModel_RemoveAnimationState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimatedModel",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Animation",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimatedModel* self = (AnimatedModel*)  tolua_tousertype(tolua_S,1,0);
  Animation* animation = ((Animation*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveAnimationState'", NULL);
#endif
  {
   self->RemoveAnimationState(animation);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemoveAnimationState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveAnimationState of class  AnimatedModel */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimatedModel_RemoveAnimationState01
static int tolua_Graphics_AnimatedModel_RemoveAnimationState01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimatedModel",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  AnimatedModel* self = (AnimatedModel*)  tolua_tousertype(tolua_S,1,0);
  const String* animationName = ((const String*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveAnimationState'", NULL);
#endif
  {
   self->RemoveAnimationState(*animationName);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Graphics_AnimatedModel_RemoveAnimationState00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveAnimationState of class  AnimatedModel */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimatedModel_RemoveAnimationState02
static int tolua_Graphics_AnimatedModel_RemoveAnimationState02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimatedModel",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"StringHash",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  AnimatedModel* self = (AnimatedModel*)  tolua_tousertype(tolua_S,1,0);
  StringHash animationNameHash = *((StringHash*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveAnimationState'", NULL);
#endif
  {
   self->RemoveAnimationState(animationNameHash);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Graphics_AnimatedModel_RemoveAnimationState01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveAnimationState of class  AnimatedModel */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimatedModel_RemoveAnimationState03
static int tolua_Graphics_AnimatedModel_RemoveAnimationState03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimatedModel",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"AnimationState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  AnimatedModel* self = (AnimatedModel*)  tolua_tousertype(tolua_S,1,0);
  AnimationState* state = ((AnimationState*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveAnimationState'", NULL);
#endif
  {
   self->RemoveAnimationState(state);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Graphics_AnimatedModel_RemoveAnimationState02(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveAnimationState of class  AnimatedModel */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimatedModel_RemoveAnimationState04
static int tolua_Graphics_AnimatedModel_RemoveAnimationState04(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimatedModel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  AnimatedModel* self = (AnimatedModel*)  tolua_tousertype(tolua_S,1,0);
  unsigned index = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveAnimationState'", NULL);
#endif
  {
   self->RemoveAnimationState(index);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Graphics_AnimatedModel_RemoveAnimationState03(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveAllAnimationStates of class  AnimatedModel */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimatedModel_RemoveAllAnimationStates00
static int tolua_Graphics_AnimatedModel_RemoveAllAnimationStates00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimatedModel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimatedModel* self = (AnimatedModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveAllAnimationStates'", NULL);
#endif
  {
   self->RemoveAllAnimationStates();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemoveAllAnimationStates'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetAnimationLodBias of class  AnimatedModel */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimatedModel_SetAnimationLodBias00
static int tolua_Graphics_AnimatedModel_SetAnimationLodBias00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimatedModel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimatedModel* self = (AnimatedModel*)  tolua_tousertype(tolua_S,1,0);
  float bias = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetAnimationLodBias'", NULL);
#endif
  {
   self->SetAnimationLodBias(bias);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetAnimationLodBias'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetInvisibleLodFactor of class  AnimatedModel */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimatedModel_SetInvisibleLodFactor00
static int tolua_Graphics_AnimatedModel_SetInvisibleLodFactor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimatedModel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimatedModel* self = (AnimatedModel*)  tolua_tousertype(tolua_S,1,0);
  float factor = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetInvisibleLodFactor'", NULL);
#endif
  {
   self->SetInvisibleLodFactor(factor);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetInvisibleLodFactor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMorphWeight of class  AnimatedModel */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimatedModel_SetMorphWeight00
static int tolua_Graphics_AnimatedModel_SetMorphWeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimatedModel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimatedModel* self = (AnimatedModel*)  tolua_tousertype(tolua_S,1,0);
  unsigned index = ((unsigned)  tolua_tonumber(tolua_S,2,0));
  float weight = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMorphWeight'", NULL);
#endif
  {
   self->SetMorphWeight(index,weight);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMorphWeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMorphWeight of class  AnimatedModel */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimatedModel_SetMorphWeight01
static int tolua_Graphics_AnimatedModel_SetMorphWeight01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimatedModel",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  AnimatedModel* self = (AnimatedModel*)  tolua_tousertype(tolua_S,1,0);
  const String* name = ((const String*)  tolua_tousertype(tolua_S,2,0));
  float weight = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMorphWeight'", NULL);
#endif
  {
   self->SetMorphWeight(*name,weight);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Graphics_AnimatedModel_SetMorphWeight00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMorphWeight of class  AnimatedModel */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimatedModel_SetMorphWeight02
static int tolua_Graphics_AnimatedModel_SetMorphWeight02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimatedModel",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"StringHash",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  AnimatedModel* self = (AnimatedModel*)  tolua_tousertype(tolua_S,1,0);
  StringHash nameHash = *((StringHash*)  tolua_tousertype(tolua_S,2,0));
  float weight = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMorphWeight'", NULL);
#endif
  {
   self->SetMorphWeight(nameHash,weight);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Graphics_AnimatedModel_SetMorphWeight01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: ResetMorphWeights of class  AnimatedModel */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimatedModel_ResetMorphWeights00
static int tolua_Graphics_AnimatedModel_ResetMorphWeights00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimatedModel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimatedModel* self = (AnimatedModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ResetMorphWeights'", NULL);
#endif
  {
   self->ResetMorphWeights();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ResetMorphWeights'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSkeleton of class  AnimatedModel */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimatedModel_GetSkeleton00
static int tolua_Graphics_AnimatedModel_GetSkeleton00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimatedModel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimatedModel* self = (AnimatedModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSkeleton'", NULL);
#endif
  {
   Skeleton& tolua_ret = (Skeleton&)  self->GetSkeleton();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"Skeleton");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSkeleton'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNumAnimationStates of class  AnimatedModel */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimatedModel_GetNumAnimationStates00
static int tolua_Graphics_AnimatedModel_GetNumAnimationStates00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const AnimatedModel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const AnimatedModel* self = (const AnimatedModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNumAnimationStates'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetNumAnimationStates();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNumAnimationStates'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAnimationState of class  AnimatedModel */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimatedModel_GetAnimationState00
static int tolua_Graphics_AnimatedModel_GetAnimationState00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const AnimatedModel",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Animation",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const AnimatedModel* self = (const AnimatedModel*)  tolua_tousertype(tolua_S,1,0);
  Animation* animation = ((Animation*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAnimationState'", NULL);
#endif
  {
   AnimationState* tolua_ret = (AnimationState*)  self->GetAnimationState(animation);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"AnimationState");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAnimationState'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAnimationState of class  AnimatedModel */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimatedModel_GetAnimationState01
static int tolua_Graphics_AnimatedModel_GetAnimationState01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const AnimatedModel",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const AnimatedModel* self = (const AnimatedModel*)  tolua_tousertype(tolua_S,1,0);
  const String* animationName = ((const String*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAnimationState'", NULL);
#endif
  {
   AnimationState* tolua_ret = (AnimationState*)  self->GetAnimationState(*animationName);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"AnimationState");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Graphics_AnimatedModel_GetAnimationState00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAnimationState of class  AnimatedModel */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimatedModel_GetAnimationState02
static int tolua_Graphics_AnimatedModel_GetAnimationState02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const AnimatedModel",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const AnimatedModel* self = (const AnimatedModel*)  tolua_tousertype(tolua_S,1,0);
  const char* animationName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAnimationState'", NULL);
#endif
  {
   AnimationState* tolua_ret = (AnimationState*)  self->GetAnimationState(animationName);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"AnimationState");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Graphics_AnimatedModel_GetAnimationState01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAnimationState of class  AnimatedModel */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimatedModel_GetAnimationState03
static int tolua_Graphics_AnimatedModel_GetAnimationState03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const AnimatedModel",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const StringHash",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const AnimatedModel* self = (const AnimatedModel*)  tolua_tousertype(tolua_S,1,0);
  const StringHash animationNameHash = *((const StringHash*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAnimationState'", NULL);
#endif
  {
   AnimationState* tolua_ret = (AnimationState*)  self->GetAnimationState(animationNameHash);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"AnimationState");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Graphics_AnimatedModel_GetAnimationState02(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAnimationState of class  AnimatedModel */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimatedModel_GetAnimationState04
static int tolua_Graphics_AnimatedModel_GetAnimationState04(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const AnimatedModel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const AnimatedModel* self = (const AnimatedModel*)  tolua_tousertype(tolua_S,1,0);
  unsigned index = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAnimationState'", NULL);
#endif
  {
   AnimationState* tolua_ret = (AnimationState*)  self->GetAnimationState(index);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"AnimationState");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Graphics_AnimatedModel_GetAnimationState03(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAnimationLodBias of class  AnimatedModel */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimatedModel_GetAnimationLodBias00
static int tolua_Graphics_AnimatedModel_GetAnimationLodBias00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const AnimatedModel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const AnimatedModel* self = (const AnimatedModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAnimationLodBias'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetAnimationLodBias();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAnimationLodBias'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetInvisibleLodFactor of class  AnimatedModel */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimatedModel_GetInvisibleLodFactor00
static int tolua_Graphics_AnimatedModel_GetInvisibleLodFactor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const AnimatedModel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const AnimatedModel* self = (const AnimatedModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetInvisibleLodFactor'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetInvisibleLodFactor();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetInvisibleLodFactor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNumMorphs of class  AnimatedModel */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimatedModel_GetNumMorphs00
static int tolua_Graphics_AnimatedModel_GetNumMorphs00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const AnimatedModel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const AnimatedModel* self = (const AnimatedModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNumMorphs'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetNumMorphs();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNumMorphs'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMorphWeight of class  AnimatedModel */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimatedModel_GetMorphWeight00
static int tolua_Graphics_AnimatedModel_GetMorphWeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const AnimatedModel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const AnimatedModel* self = (const AnimatedModel*)  tolua_tousertype(tolua_S,1,0);
  unsigned index = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMorphWeight'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetMorphWeight(index);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMorphWeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMorphWeight of class  AnimatedModel */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimatedModel_GetMorphWeight01
static int tolua_Graphics_AnimatedModel_GetMorphWeight01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const AnimatedModel",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const AnimatedModel* self = (const AnimatedModel*)  tolua_tousertype(tolua_S,1,0);
  const String* name = ((const String*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMorphWeight'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetMorphWeight(*name);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_Graphics_AnimatedModel_GetMorphWeight00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMorphWeight of class  AnimatedModel */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimatedModel_GetMorphWeight02
static int tolua_Graphics_AnimatedModel_GetMorphWeight02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const AnimatedModel",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"StringHash",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const AnimatedModel* self = (const AnimatedModel*)  tolua_tousertype(tolua_S,1,0);
  StringHash nameHash = *((StringHash*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMorphWeight'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetMorphWeight(nameHash);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_Graphics_AnimatedModel_GetMorphWeight01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsMaster of class  AnimatedModel */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimatedModel_IsMaster00
static int tolua_Graphics_AnimatedModel_IsMaster00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const AnimatedModel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const AnimatedModel* self = (const AnimatedModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsMaster'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsMaster();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsMaster'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAnimationName of class  Animation */
#ifndef TOLUA_DISABLE_tolua_Graphics_Animation_GetAnimationName00
static int tolua_Graphics_Animation_GetAnimationName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Animation",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Animation* self = (const Animation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAnimationName'", NULL);
#endif
  {
   const String& tolua_ret = (const String&)  self->GetAnimationName();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const String");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAnimationName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAnimationNameHash of class  Animation */
#ifndef TOLUA_DISABLE_tolua_Graphics_Animation_GetAnimationNameHash00
static int tolua_Graphics_Animation_GetAnimationNameHash00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Animation",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Animation* self = (const Animation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAnimationNameHash'", NULL);
#endif
  {
   StringHash tolua_ret = (StringHash)  self->GetAnimationNameHash();
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
 tolua_error(tolua_S,"#ferror in function 'GetAnimationNameHash'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLength of class  Animation */
#ifndef TOLUA_DISABLE_tolua_Graphics_Animation_GetLength00
static int tolua_Graphics_Animation_GetLength00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Animation",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Animation* self = (const Animation*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetNumTracks of class  Animation */
#ifndef TOLUA_DISABLE_tolua_Graphics_Animation_GetNumTracks00
static int tolua_Graphics_Animation_GetNumTracks00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Animation",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Animation* self = (const Animation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNumTracks'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetNumTracks();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNumTracks'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTrack of class  Animation */
#ifndef TOLUA_DISABLE_tolua_Graphics_Animation_GetTrack00
static int tolua_Graphics_Animation_GetTrack00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Animation",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Animation* self = (const Animation*)  tolua_tousertype(tolua_S,1,0);
  unsigned index = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTrack'", NULL);
#endif
  {
   const AnimationTrack* tolua_ret = (const AnimationTrack*)  self->GetTrack(index);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"const AnimationTrack");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTrack'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTrack of class  Animation */
#ifndef TOLUA_DISABLE_tolua_Graphics_Animation_GetTrack01
static int tolua_Graphics_Animation_GetTrack01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Animation",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const Animation* self = (const Animation*)  tolua_tousertype(tolua_S,1,0);
  const String* name = ((const String*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTrack'", NULL);
#endif
  {
   const AnimationTrack* tolua_ret = (const AnimationTrack*)  self->GetTrack(*name);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"const AnimationTrack");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Graphics_Animation_GetTrack00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTrack of class  Animation */
#ifndef TOLUA_DISABLE_tolua_Graphics_Animation_GetTrack02
static int tolua_Graphics_Animation_GetTrack02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Animation",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"StringHash",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const Animation* self = (const Animation*)  tolua_tousertype(tolua_S,1,0);
  StringHash nameHash = *((StringHash*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTrack'", NULL);
#endif
  {
   const AnimationTrack* tolua_ret = (const AnimationTrack*)  self->GetTrack(nameHash);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"const AnimationTrack");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Graphics_Animation_GetTrack01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNumTriggers of class  Animation */
#ifndef TOLUA_DISABLE_tolua_Graphics_Animation_GetNumTriggers00
static int tolua_Graphics_Animation_GetNumTriggers00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Animation",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Animation* self = (const Animation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNumTriggers'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetNumTriggers();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNumTriggers'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Play of class  AnimationController */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimationController_Play00
static int tolua_Graphics_AnimationController_Play00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimationController",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimationController* self = (AnimationController*)  tolua_tousertype(tolua_S,1,0);
  const String* name = ((const String*)  tolua_tousertype(tolua_S,2,0));
  unsigned char layer = ((unsigned char)  tolua_tonumber(tolua_S,3,0));
  bool looped = ((bool)  tolua_toboolean(tolua_S,4,0));
  float fadeInTime = ((float)  tolua_tonumber(tolua_S,5,0.0f));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Play'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Play(*name,layer,looped,fadeInTime);
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

/* method: PlayExclusive of class  AnimationController */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimationController_PlayExclusive00
static int tolua_Graphics_AnimationController_PlayExclusive00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimationController",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimationController* self = (AnimationController*)  tolua_tousertype(tolua_S,1,0);
  const String* name = ((const String*)  tolua_tousertype(tolua_S,2,0));
  unsigned char layer = ((unsigned char)  tolua_tonumber(tolua_S,3,0));
  bool looped = ((bool)  tolua_toboolean(tolua_S,4,0));
  float fadeTime = ((float)  tolua_tonumber(tolua_S,5,0.0f));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'PlayExclusive'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->PlayExclusive(*name,layer,looped,fadeTime);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'PlayExclusive'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Stop of class  AnimationController */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimationController_Stop00
static int tolua_Graphics_AnimationController_Stop00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimationController",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimationController* self = (AnimationController*)  tolua_tousertype(tolua_S,1,0);
  const String* name = ((const String*)  tolua_tousertype(tolua_S,2,0));
  float fadeOutTime = ((float)  tolua_tonumber(tolua_S,3,0.0f));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Stop'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Stop(*name,fadeOutTime);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Stop'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: StopLayer of class  AnimationController */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimationController_StopLayer00
static int tolua_Graphics_AnimationController_StopLayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimationController",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimationController* self = (AnimationController*)  tolua_tousertype(tolua_S,1,0);
  unsigned char layer = ((unsigned char)  tolua_tonumber(tolua_S,2,0));
  float fadeOutTime = ((float)  tolua_tonumber(tolua_S,3,0.0f));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'StopLayer'", NULL);
#endif
  {
   self->StopLayer(layer,fadeOutTime);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'StopLayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: StopAll of class  AnimationController */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimationController_StopAll00
static int tolua_Graphics_AnimationController_StopAll00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimationController",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimationController* self = (AnimationController*)  tolua_tousertype(tolua_S,1,0);
  float fadeTime = ((float)  tolua_tonumber(tolua_S,2,0.0f));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'StopAll'", NULL);
#endif
  {
   self->StopAll(fadeTime);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'StopAll'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Fade of class  AnimationController */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimationController_Fade00
static int tolua_Graphics_AnimationController_Fade00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimationController",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimationController* self = (AnimationController*)  tolua_tousertype(tolua_S,1,0);
  const String* name = ((const String*)  tolua_tousertype(tolua_S,2,0));
  float targetWeight = ((float)  tolua_tonumber(tolua_S,3,0));
  float fadeTime = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Fade'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Fade(*name,targetWeight,fadeTime);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Fade'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: FadeOthers of class  AnimationController */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimationController_FadeOthers00
static int tolua_Graphics_AnimationController_FadeOthers00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimationController",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimationController* self = (AnimationController*)  tolua_tousertype(tolua_S,1,0);
  const String* name = ((const String*)  tolua_tousertype(tolua_S,2,0));
  float targetWeight = ((float)  tolua_tonumber(tolua_S,3,0));
  float fadeTime = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'FadeOthers'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->FadeOthers(*name,targetWeight,fadeTime);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'FadeOthers'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetLayer of class  AnimationController */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimationController_SetLayer00
static int tolua_Graphics_AnimationController_SetLayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimationController",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimationController* self = (AnimationController*)  tolua_tousertype(tolua_S,1,0);
  const String* name = ((const String*)  tolua_tousertype(tolua_S,2,0));
  unsigned char layer = ((unsigned char)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLayer'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SetLayer(*name,layer);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetStartBone of class  AnimationController */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimationController_SetStartBone00
static int tolua_Graphics_AnimationController_SetStartBone00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimationController",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimationController* self = (AnimationController*)  tolua_tousertype(tolua_S,1,0);
  const String* name = ((const String*)  tolua_tousertype(tolua_S,2,0));
  const String* startBoneName = ((const String*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetStartBone'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SetStartBone(*name,*startBoneName);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetStartBone'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetTime of class  AnimationController */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimationController_SetTime00
static int tolua_Graphics_AnimationController_SetTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimationController",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimationController* self = (AnimationController*)  tolua_tousertype(tolua_S,1,0);
  const String* name = ((const String*)  tolua_tousertype(tolua_S,2,0));
  float time = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetTime'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SetTime(*name,time);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetWeight of class  AnimationController */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimationController_SetWeight00
static int tolua_Graphics_AnimationController_SetWeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimationController",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimationController* self = (AnimationController*)  tolua_tousertype(tolua_S,1,0);
  const String* name = ((const String*)  tolua_tousertype(tolua_S,2,0));
  float weight = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetWeight'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SetWeight(*name,weight);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetWeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetLooped of class  AnimationController */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimationController_SetLooped00
static int tolua_Graphics_AnimationController_SetLooped00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimationController",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isboolean(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimationController* self = (AnimationController*)  tolua_tousertype(tolua_S,1,0);
  const String* name = ((const String*)  tolua_tousertype(tolua_S,2,0));
  bool enable = ((bool)  tolua_toboolean(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLooped'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SetLooped(*name,enable);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLooped'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetSpeed of class  AnimationController */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimationController_SetSpeed00
static int tolua_Graphics_AnimationController_SetSpeed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimationController",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimationController* self = (AnimationController*)  tolua_tousertype(tolua_S,1,0);
  const String* name = ((const String*)  tolua_tousertype(tolua_S,2,0));
  float speed = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetSpeed'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SetSpeed(*name,speed);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetSpeed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetAutoFade of class  AnimationController */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimationController_SetAutoFade00
static int tolua_Graphics_AnimationController_SetAutoFade00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimationController",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimationController* self = (AnimationController*)  tolua_tousertype(tolua_S,1,0);
  const String* name = ((const String*)  tolua_tousertype(tolua_S,2,0));
  float fadeOutTime = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetAutoFade'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SetAutoFade(*name,fadeOutTime);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetAutoFade'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsPlaying of class  AnimationController */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimationController_IsPlaying00
static int tolua_Graphics_AnimationController_IsPlaying00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const AnimationController",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const AnimationController* self = (const AnimationController*)  tolua_tousertype(tolua_S,1,0);
  const String* name = ((const String*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsPlaying'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsPlaying(*name);
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

/* method: IsFadingIn of class  AnimationController */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimationController_IsFadingIn00
static int tolua_Graphics_AnimationController_IsFadingIn00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const AnimationController",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const AnimationController* self = (const AnimationController*)  tolua_tousertype(tolua_S,1,0);
  const String* name = ((const String*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsFadingIn'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsFadingIn(*name);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsFadingIn'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsFadingOut of class  AnimationController */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimationController_IsFadingOut00
static int tolua_Graphics_AnimationController_IsFadingOut00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const AnimationController",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const AnimationController* self = (const AnimationController*)  tolua_tousertype(tolua_S,1,0);
  const String* name = ((const String*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsFadingOut'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsFadingOut(*name);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsFadingOut'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLayer of class  AnimationController */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimationController_GetLayer00
static int tolua_Graphics_AnimationController_GetLayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const AnimationController",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const AnimationController* self = (const AnimationController*)  tolua_tousertype(tolua_S,1,0);
  const String* name = ((const String*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLayer'", NULL);
#endif
  {
   unsigned char tolua_ret = (unsigned char)  self->GetLayer(*name);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetStartBone of class  AnimationController */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimationController_GetStartBone00
static int tolua_Graphics_AnimationController_GetStartBone00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const AnimationController",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const AnimationController* self = (const AnimationController*)  tolua_tousertype(tolua_S,1,0);
  const String* name = ((const String*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetStartBone'", NULL);
#endif
  {
   Bone* tolua_ret = (Bone*)  self->GetStartBone(*name);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Bone");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetStartBone'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetStartBoneName of class  AnimationController */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimationController_GetStartBoneName00
static int tolua_Graphics_AnimationController_GetStartBoneName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const AnimationController",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const AnimationController* self = (const AnimationController*)  tolua_tousertype(tolua_S,1,0);
  const String* name = ((const String*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetStartBoneName'", NULL);
#endif
  {
   const String& tolua_ret = (const String&)  self->GetStartBoneName(*name);
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const String");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetStartBoneName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTime of class  AnimationController */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimationController_GetTime00
static int tolua_Graphics_AnimationController_GetTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const AnimationController",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const AnimationController* self = (const AnimationController*)  tolua_tousertype(tolua_S,1,0);
  const String* name = ((const String*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTime'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetTime(*name);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
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

/* method: GetWeight of class  AnimationController */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimationController_GetWeight00
static int tolua_Graphics_AnimationController_GetWeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const AnimationController",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const AnimationController* self = (const AnimationController*)  tolua_tousertype(tolua_S,1,0);
  const String* name = ((const String*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetWeight'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetWeight(*name);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetWeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsLooped of class  AnimationController */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimationController_IsLooped00
static int tolua_Graphics_AnimationController_IsLooped00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const AnimationController",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const AnimationController* self = (const AnimationController*)  tolua_tousertype(tolua_S,1,0);
  const String* name = ((const String*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsLooped'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsLooped(*name);
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

/* method: GetLength of class  AnimationController */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimationController_GetLength00
static int tolua_Graphics_AnimationController_GetLength00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const AnimationController",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const AnimationController* self = (const AnimationController*)  tolua_tousertype(tolua_S,1,0);
  const String* name = ((const String*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLength'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetLength(*name);
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

/* method: GetSpeed of class  AnimationController */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimationController_GetSpeed00
static int tolua_Graphics_AnimationController_GetSpeed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const AnimationController",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const AnimationController* self = (const AnimationController*)  tolua_tousertype(tolua_S,1,0);
  const String* name = ((const String*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSpeed'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetSpeed(*name);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSpeed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFadeTarget of class  AnimationController */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimationController_GetFadeTarget00
static int tolua_Graphics_AnimationController_GetFadeTarget00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const AnimationController",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const AnimationController* self = (const AnimationController*)  tolua_tousertype(tolua_S,1,0);
  const String* name = ((const String*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFadeTarget'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetFadeTarget(*name);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFadeTarget'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFadeTime of class  AnimationController */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimationController_GetFadeTime00
static int tolua_Graphics_AnimationController_GetFadeTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const AnimationController",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const AnimationController* self = (const AnimationController*)  tolua_tousertype(tolua_S,1,0);
  const String* name = ((const String*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFadeTime'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetFadeTime(*name);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFadeTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAutoFade of class  AnimationController */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimationController_GetAutoFade00
static int tolua_Graphics_AnimationController_GetAutoFade00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const AnimationController",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const AnimationController* self = (const AnimationController*)  tolua_tousertype(tolua_S,1,0);
  const String* name = ((const String*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAutoFade'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetAutoFade(*name);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAutoFade'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  AnimationState */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimationState_new00
static int tolua_Graphics_AnimationState_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"AnimationState",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"AnimatedModel",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"Animation",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimatedModel* model = ((AnimatedModel*)  tolua_tousertype(tolua_S,2,0));
  Animation* animation = ((Animation*)  tolua_tousertype(tolua_S,3,0));
  {
   AnimationState* tolua_ret = (AnimationState*)  Mtolua_new((AnimationState)(model,animation));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"AnimationState");
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

/* method: new_local of class  AnimationState */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimationState_new00_local
static int tolua_Graphics_AnimationState_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"AnimationState",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"AnimatedModel",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"Animation",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimatedModel* model = ((AnimatedModel*)  tolua_tousertype(tolua_S,2,0));
  Animation* animation = ((Animation*)  tolua_tousertype(tolua_S,3,0));
  {
   AnimationState* tolua_ret = (AnimationState*)  Mtolua_new((AnimationState)(model,animation));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"AnimationState");
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

/* method: new of class  AnimationState */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimationState_new01
static int tolua_Graphics_AnimationState_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"AnimationState",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Node",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"Animation",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Node* node = ((Node*)  tolua_tousertype(tolua_S,2,0));
  Animation* animation = ((Animation*)  tolua_tousertype(tolua_S,3,0));
  {
   AnimationState* tolua_ret = (AnimationState*)  Mtolua_new((AnimationState)(node,animation));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"AnimationState");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Graphics_AnimationState_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  AnimationState */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimationState_new01_local
static int tolua_Graphics_AnimationState_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"AnimationState",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Node",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"Animation",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Node* node = ((Node*)  tolua_tousertype(tolua_S,2,0));
  Animation* animation = ((Animation*)  tolua_tousertype(tolua_S,3,0));
  {
   AnimationState* tolua_ret = (AnimationState*)  Mtolua_new((AnimationState)(node,animation));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"AnimationState");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_Graphics_AnimationState_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: delete of class  AnimationState */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimationState_delete00
static int tolua_Graphics_AnimationState_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimationState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimationState* self = (AnimationState*)  tolua_tousertype(tolua_S,1,0);
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

/* method: SetStartBone of class  AnimationState */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimationState_SetStartBone00
static int tolua_Graphics_AnimationState_SetStartBone00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimationState",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Bone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimationState* self = (AnimationState*)  tolua_tousertype(tolua_S,1,0);
  Bone* bone = ((Bone*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetStartBone'", NULL);
#endif
  {
   self->SetStartBone(bone);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetStartBone'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetLooped of class  AnimationState */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimationState_SetLooped00
static int tolua_Graphics_AnimationState_SetLooped00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimationState",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimationState* self = (AnimationState*)  tolua_tousertype(tolua_S,1,0);
  bool looped = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLooped'", NULL);
#endif
  {
   self->SetLooped(looped);
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

/* method: SetWeight of class  AnimationState */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimationState_SetWeight00
static int tolua_Graphics_AnimationState_SetWeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimationState",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimationState* self = (AnimationState*)  tolua_tousertype(tolua_S,1,0);
  float weight = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetWeight'", NULL);
#endif
  {
   self->SetWeight(weight);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetWeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetTime of class  AnimationState */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimationState_SetTime00
static int tolua_Graphics_AnimationState_SetTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimationState",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimationState* self = (AnimationState*)  tolua_tousertype(tolua_S,1,0);
  float time = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetTime'", NULL);
#endif
  {
   self->SetTime(time);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddWeight of class  AnimationState */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimationState_AddWeight00
static int tolua_Graphics_AnimationState_AddWeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimationState",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimationState* self = (AnimationState*)  tolua_tousertype(tolua_S,1,0);
  float delta = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddWeight'", NULL);
#endif
  {
   self->AddWeight(delta);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddWeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddTime of class  AnimationState */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimationState_AddTime00
static int tolua_Graphics_AnimationState_AddTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimationState",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimationState* self = (AnimationState*)  tolua_tousertype(tolua_S,1,0);
  float delta = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddTime'", NULL);
#endif
  {
   self->AddTime(delta);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetLayer of class  AnimationState */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimationState_SetLayer00
static int tolua_Graphics_AnimationState_SetLayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimationState",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimationState* self = (AnimationState*)  tolua_tousertype(tolua_S,1,0);
  unsigned char layer = ((unsigned char)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLayer'", NULL);
#endif
  {
   self->SetLayer(layer);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAnimation of class  AnimationState */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimationState_GetAnimation00
static int tolua_Graphics_AnimationState_GetAnimation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const AnimationState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const AnimationState* self = (const AnimationState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAnimation'", NULL);
#endif
  {
   Animation* tolua_ret = (Animation*)  self->GetAnimation();
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

/* method: GetStartBone of class  AnimationState */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimationState_GetStartBone00
static int tolua_Graphics_AnimationState_GetStartBone00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const AnimationState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const AnimationState* self = (const AnimationState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetStartBone'", NULL);
#endif
  {
   Bone* tolua_ret = (Bone*)  self->GetStartBone();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Bone");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetStartBone'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsEnabled of class  AnimationState */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimationState_IsEnabled00
static int tolua_Graphics_AnimationState_IsEnabled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const AnimationState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const AnimationState* self = (const AnimationState*)  tolua_tousertype(tolua_S,1,0);
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

/* method: IsLooped of class  AnimationState */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimationState_IsLooped00
static int tolua_Graphics_AnimationState_IsLooped00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const AnimationState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const AnimationState* self = (const AnimationState*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetWeight of class  AnimationState */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimationState_GetWeight00
static int tolua_Graphics_AnimationState_GetWeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const AnimationState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const AnimationState* self = (const AnimationState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetWeight'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetWeight();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetWeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTime of class  AnimationState */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimationState_GetTime00
static int tolua_Graphics_AnimationState_GetTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const AnimationState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const AnimationState* self = (const AnimationState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTime'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetTime();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
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

/* method: GetLength of class  AnimationState */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimationState_GetLength00
static int tolua_Graphics_AnimationState_GetLength00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const AnimationState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const AnimationState* self = (const AnimationState*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetLayer of class  AnimationState */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimationState_GetLayer00
static int tolua_Graphics_AnimationState_GetLayer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const AnimationState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const AnimationState* self = (const AnimationState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLayer'", NULL);
#endif
  {
   unsigned char tolua_ret = (unsigned char)  self->GetLayer();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLayer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Apply of class  AnimationState */
#ifndef TOLUA_DISABLE_tolua_Graphics_AnimationState_Apply00
static int tolua_Graphics_AnimationState_Apply00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AnimationState",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AnimationState* self = (AnimationState*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Apply'", NULL);
#endif
  {
   self->Apply();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Apply'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMaterial of class  BillboardSet */
#ifndef TOLUA_DISABLE_tolua_Graphics_BillboardSet_SetMaterial00
static int tolua_Graphics_BillboardSet_SetMaterial00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BillboardSet",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Material",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BillboardSet* self = (BillboardSet*)  tolua_tousertype(tolua_S,1,0);
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

/* method: SetNumBillboards of class  BillboardSet */
#ifndef TOLUA_DISABLE_tolua_Graphics_BillboardSet_SetNumBillboards00
static int tolua_Graphics_BillboardSet_SetNumBillboards00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BillboardSet",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BillboardSet* self = (BillboardSet*)  tolua_tousertype(tolua_S,1,0);
  unsigned num = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetNumBillboards'", NULL);
#endif
  {
   self->SetNumBillboards(num);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetNumBillboards'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetRelative of class  BillboardSet */
#ifndef TOLUA_DISABLE_tolua_Graphics_BillboardSet_SetRelative00
static int tolua_Graphics_BillboardSet_SetRelative00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BillboardSet",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BillboardSet* self = (BillboardSet*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetRelative'", NULL);
#endif
  {
   self->SetRelative(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetRelative'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetScaled of class  BillboardSet */
#ifndef TOLUA_DISABLE_tolua_Graphics_BillboardSet_SetScaled00
static int tolua_Graphics_BillboardSet_SetScaled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BillboardSet",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BillboardSet* self = (BillboardSet*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetScaled'", NULL);
#endif
  {
   self->SetScaled(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetScaled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetSorted of class  BillboardSet */
#ifndef TOLUA_DISABLE_tolua_Graphics_BillboardSet_SetSorted00
static int tolua_Graphics_BillboardSet_SetSorted00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BillboardSet",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BillboardSet* self = (BillboardSet*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetSorted'", NULL);
#endif
  {
   self->SetSorted(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetSorted'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetAnimationLodBias of class  BillboardSet */
#ifndef TOLUA_DISABLE_tolua_Graphics_BillboardSet_SetAnimationLodBias00
static int tolua_Graphics_BillboardSet_SetAnimationLodBias00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BillboardSet",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BillboardSet* self = (BillboardSet*)  tolua_tousertype(tolua_S,1,0);
  float bias = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetAnimationLodBias'", NULL);
#endif
  {
   self->SetAnimationLodBias(bias);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetAnimationLodBias'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Commit of class  BillboardSet */
#ifndef TOLUA_DISABLE_tolua_Graphics_BillboardSet_Commit00
static int tolua_Graphics_BillboardSet_Commit00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"BillboardSet",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  BillboardSet* self = (BillboardSet*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Commit'", NULL);
#endif
  {
   self->Commit();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Commit'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMaterial of class  BillboardSet */
#ifndef TOLUA_DISABLE_tolua_Graphics_BillboardSet_GetMaterial00
static int tolua_Graphics_BillboardSet_GetMaterial00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const BillboardSet",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const BillboardSet* self = (const BillboardSet*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetNumBillboards of class  BillboardSet */
#ifndef TOLUA_DISABLE_tolua_Graphics_BillboardSet_GetNumBillboards00
static int tolua_Graphics_BillboardSet_GetNumBillboards00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const BillboardSet",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const BillboardSet* self = (const BillboardSet*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNumBillboards'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetNumBillboards();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNumBillboards'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsRelative of class  BillboardSet */
#ifndef TOLUA_DISABLE_tolua_Graphics_BillboardSet_IsRelative00
static int tolua_Graphics_BillboardSet_IsRelative00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const BillboardSet",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const BillboardSet* self = (const BillboardSet*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsRelative'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsRelative();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsRelative'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsScaled of class  BillboardSet */
#ifndef TOLUA_DISABLE_tolua_Graphics_BillboardSet_IsScaled00
static int tolua_Graphics_BillboardSet_IsScaled00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const BillboardSet",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const BillboardSet* self = (const BillboardSet*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsScaled'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsScaled();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsScaled'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsSorted of class  BillboardSet */
#ifndef TOLUA_DISABLE_tolua_Graphics_BillboardSet_IsSorted00
static int tolua_Graphics_BillboardSet_IsSorted00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const BillboardSet",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const BillboardSet* self = (const BillboardSet*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsSorted'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsSorted();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsSorted'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAnimationLodBias of class  BillboardSet */
#ifndef TOLUA_DISABLE_tolua_Graphics_BillboardSet_GetAnimationLodBias00
static int tolua_Graphics_BillboardSet_GetAnimationLodBias00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const BillboardSet",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const BillboardSet* self = (const BillboardSet*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAnimationLodBias'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetAnimationLodBias();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAnimationLodBias'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetNearClip of class  Camera */
#ifndef TOLUA_DISABLE_tolua_Graphics_Camera_SetNearClip00
static int tolua_Graphics_Camera_SetNearClip00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Camera",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Camera* self = (Camera*)  tolua_tousertype(tolua_S,1,0);
  float nearClip = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetNearClip'", NULL);
#endif
  {
   self->SetNearClip(nearClip);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetNearClip'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFarClip of class  Camera */
#ifndef TOLUA_DISABLE_tolua_Graphics_Camera_SetFarClip00
static int tolua_Graphics_Camera_SetFarClip00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Camera",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Camera* self = (Camera*)  tolua_tousertype(tolua_S,1,0);
  float farClip = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFarClip'", NULL);
#endif
  {
   self->SetFarClip(farClip);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFarClip'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFov of class  Camera */
#ifndef TOLUA_DISABLE_tolua_Graphics_Camera_SetFov00
static int tolua_Graphics_Camera_SetFov00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Camera",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Camera* self = (Camera*)  tolua_tousertype(tolua_S,1,0);
  float fov = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFov'", NULL);
#endif
  {
   self->SetFov(fov);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFov'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetOrthoSize of class  Camera */
#ifndef TOLUA_DISABLE_tolua_Graphics_Camera_SetOrthoSize00
static int tolua_Graphics_Camera_SetOrthoSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Camera",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Camera* self = (Camera*)  tolua_tousertype(tolua_S,1,0);
  float orthoSize = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetOrthoSize'", NULL);
#endif
  {
   self->SetOrthoSize(orthoSize);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetOrthoSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetOrthoSize of class  Camera */
#ifndef TOLUA_DISABLE_tolua_Graphics_Camera_SetOrthoSize01
static int tolua_Graphics_Camera_SetOrthoSize01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Camera",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Camera* self = (Camera*)  tolua_tousertype(tolua_S,1,0);
  const Vector2* orthoSize = ((const Vector2*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetOrthoSize'", NULL);
#endif
  {
   self->SetOrthoSize(*orthoSize);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Graphics_Camera_SetOrthoSize00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetAspectRatio of class  Camera */
#ifndef TOLUA_DISABLE_tolua_Graphics_Camera_SetAspectRatio00
static int tolua_Graphics_Camera_SetAspectRatio00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Camera",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Camera* self = (Camera*)  tolua_tousertype(tolua_S,1,0);
  float aspectRatio = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetAspectRatio'", NULL);
#endif
  {
   self->SetAspectRatio(aspectRatio);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetAspectRatio'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFillMode of class  Camera */
#ifndef TOLUA_DISABLE_tolua_Graphics_Camera_SetFillMode00
static int tolua_Graphics_Camera_SetFillMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Camera",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Camera* self = (Camera*)  tolua_tousertype(tolua_S,1,0);
  FillMode mode = ((FillMode) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFillMode'", NULL);
#endif
  {
   self->SetFillMode(mode);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFillMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetZoom of class  Camera */
#ifndef TOLUA_DISABLE_tolua_Graphics_Camera_SetZoom00
static int tolua_Graphics_Camera_SetZoom00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Camera",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Camera* self = (Camera*)  tolua_tousertype(tolua_S,1,0);
  float zoom = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetZoom'", NULL);
#endif
  {
   self->SetZoom(zoom);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetZoom'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetLodBias of class  Camera */
#ifndef TOLUA_DISABLE_tolua_Graphics_Camera_SetLodBias00
static int tolua_Graphics_Camera_SetLodBias00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Camera",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Camera* self = (Camera*)  tolua_tousertype(tolua_S,1,0);
  float bias = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLodBias'", NULL);
#endif
  {
   self->SetLodBias(bias);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLodBias'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetViewMask of class  Camera */
#ifndef TOLUA_DISABLE_tolua_Graphics_Camera_SetViewMask00
static int tolua_Graphics_Camera_SetViewMask00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Camera",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Camera* self = (Camera*)  tolua_tousertype(tolua_S,1,0);
  unsigned mask = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetViewMask'", NULL);
#endif
  {
   self->SetViewMask(mask);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetViewMask'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetViewOverrideFlags of class  Camera */
#ifndef TOLUA_DISABLE_tolua_Graphics_Camera_SetViewOverrideFlags00
static int tolua_Graphics_Camera_SetViewOverrideFlags00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Camera",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Camera* self = (Camera*)  tolua_tousertype(tolua_S,1,0);
  unsigned flags = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetViewOverrideFlags'", NULL);
#endif
  {
   self->SetViewOverrideFlags(flags);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetViewOverrideFlags'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetOrthographic of class  Camera */
#ifndef TOLUA_DISABLE_tolua_Graphics_Camera_SetOrthographic00
static int tolua_Graphics_Camera_SetOrthographic00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Camera",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Camera* self = (Camera*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetOrthographic'", NULL);
#endif
  {
   self->SetOrthographic(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetOrthographic'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetAutoAspectRatio of class  Camera */
#ifndef TOLUA_DISABLE_tolua_Graphics_Camera_SetAutoAspectRatio00
static int tolua_Graphics_Camera_SetAutoAspectRatio00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Camera",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Camera* self = (Camera*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetAutoAspectRatio'", NULL);
#endif
  {
   self->SetAutoAspectRatio(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetAutoAspectRatio'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetProjectionOffset of class  Camera */
#ifndef TOLUA_DISABLE_tolua_Graphics_Camera_SetProjectionOffset00
static int tolua_Graphics_Camera_SetProjectionOffset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Camera",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Camera* self = (Camera*)  tolua_tousertype(tolua_S,1,0);
  const Vector2* offset = ((const Vector2*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetProjectionOffset'", NULL);
#endif
  {
   self->SetProjectionOffset(*offset);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetProjectionOffset'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFlipVertical of class  Camera */
#ifndef TOLUA_DISABLE_tolua_Graphics_Camera_SetFlipVertical00
static int tolua_Graphics_Camera_SetFlipVertical00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Camera",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Camera* self = (Camera*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFlipVertical'", NULL);
#endif
  {
   self->SetFlipVertical(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFlipVertical'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFarClip of class  Camera */
#ifndef TOLUA_DISABLE_tolua_Graphics_Camera_GetFarClip00
static int tolua_Graphics_Camera_GetFarClip00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Camera",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Camera* self = (const Camera*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFarClip'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetFarClip();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFarClip'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNearClip of class  Camera */
#ifndef TOLUA_DISABLE_tolua_Graphics_Camera_GetNearClip00
static int tolua_Graphics_Camera_GetNearClip00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Camera",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Camera* self = (const Camera*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNearClip'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetNearClip();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNearClip'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFov of class  Camera */
#ifndef TOLUA_DISABLE_tolua_Graphics_Camera_GetFov00
static int tolua_Graphics_Camera_GetFov00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Camera",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Camera* self = (const Camera*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFov'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetFov();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFov'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetOrthoSize of class  Camera */
#ifndef TOLUA_DISABLE_tolua_Graphics_Camera_GetOrthoSize00
static int tolua_Graphics_Camera_GetOrthoSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Camera",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Camera* self = (const Camera*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetOrthoSize'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetOrthoSize();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetOrthoSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAspectRatio of class  Camera */
#ifndef TOLUA_DISABLE_tolua_Graphics_Camera_GetAspectRatio00
static int tolua_Graphics_Camera_GetAspectRatio00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Camera",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Camera* self = (const Camera*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAspectRatio'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetAspectRatio();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAspectRatio'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetZoom of class  Camera */
#ifndef TOLUA_DISABLE_tolua_Graphics_Camera_GetZoom00
static int tolua_Graphics_Camera_GetZoom00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Camera",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Camera* self = (const Camera*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetZoom'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetZoom();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetZoom'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLodBias of class  Camera */
#ifndef TOLUA_DISABLE_tolua_Graphics_Camera_GetLodBias00
static int tolua_Graphics_Camera_GetLodBias00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Camera",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Camera* self = (const Camera*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLodBias'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetLodBias();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLodBias'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetViewMask of class  Camera */
#ifndef TOLUA_DISABLE_tolua_Graphics_Camera_GetViewMask00
static int tolua_Graphics_Camera_GetViewMask00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Camera",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Camera* self = (const Camera*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetViewMask'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetViewMask();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetViewMask'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetViewOverrideFlags of class  Camera */
#ifndef TOLUA_DISABLE_tolua_Graphics_Camera_GetViewOverrideFlags00
static int tolua_Graphics_Camera_GetViewOverrideFlags00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Camera",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Camera* self = (const Camera*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetViewOverrideFlags'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetViewOverrideFlags();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetViewOverrideFlags'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFillMode of class  Camera */
#ifndef TOLUA_DISABLE_tolua_Graphics_Camera_GetFillMode00
static int tolua_Graphics_Camera_GetFillMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Camera",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Camera* self = (const Camera*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFillMode'", NULL);
#endif
  {
   FillMode tolua_ret = (FillMode)  self->GetFillMode();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFillMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsOrthographic of class  Camera */
#ifndef TOLUA_DISABLE_tolua_Graphics_Camera_IsOrthographic00
static int tolua_Graphics_Camera_IsOrthographic00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Camera",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Camera* self = (const Camera*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsOrthographic'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsOrthographic();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsOrthographic'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAutoAspectRatio of class  Camera */
#ifndef TOLUA_DISABLE_tolua_Graphics_Camera_GetAutoAspectRatio00
static int tolua_Graphics_Camera_GetAutoAspectRatio00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Camera",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Camera* self = (const Camera*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAutoAspectRatio'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetAutoAspectRatio();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAutoAspectRatio'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFrustum of class  Camera */
#ifndef TOLUA_DISABLE_tolua_Graphics_Camera_GetFrustum00
static int tolua_Graphics_Camera_GetFrustum00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Camera",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Camera* self = (const Camera*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFrustum'", NULL);
#endif
  {
   const Frustum& tolua_ret = (const Frustum&)  self->GetFrustum();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Frustum");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFrustum'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetProjection of class  Camera */
#ifndef TOLUA_DISABLE_tolua_Graphics_Camera_GetProjection00
static int tolua_Graphics_Camera_GetProjection00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Camera",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Camera* self = (const Camera*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetProjection'", NULL);
#endif
  {
   const Matrix4& tolua_ret = (const Matrix4&)  self->GetProjection();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Matrix4");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetProjection'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetProjection of class  Camera */
#ifndef TOLUA_DISABLE_tolua_Graphics_Camera_GetProjection01
static int tolua_Graphics_Camera_GetProjection01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Camera",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const Camera* self = (const Camera*)  tolua_tousertype(tolua_S,1,0);
  bool apiSpecific = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetProjection'", NULL);
#endif
  {
   Matrix4 tolua_ret = (Matrix4)  self->GetProjection(apiSpecific);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((Matrix4)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"Matrix4");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Matrix4));
     tolua_pushusertype(tolua_S,tolua_obj,"Matrix4");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
tolua_lerror:
 return tolua_Graphics_Camera_GetProjection00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetView of class  Camera */
#ifndef TOLUA_DISABLE_tolua_Graphics_Camera_GetView00
static int tolua_Graphics_Camera_GetView00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Camera",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Camera* self = (const Camera*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetView'", NULL);
#endif
  {
   const Matrix3x4& tolua_ret = (const Matrix3x4&)  self->GetView();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Matrix3x4");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetView'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFrustumSize of class  Camera */
#ifndef TOLUA_DISABLE_tolua_Graphics_Camera_GetFrustumSize00
static int tolua_Graphics_Camera_GetFrustumSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Camera",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"Vector3",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Camera* self = (const Camera*)  tolua_tousertype(tolua_S,1,0);
  Vector3* near = ((Vector3*)  tolua_tousertype(tolua_S,2,0));
  Vector3* far = ((Vector3*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFrustumSize'", NULL);
#endif
  {
   self->GetFrustumSize(*near,*far);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFrustumSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetHalfViewSize of class  Camera */
#ifndef TOLUA_DISABLE_tolua_Graphics_Camera_GetHalfViewSize00
static int tolua_Graphics_Camera_GetHalfViewSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Camera",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Camera* self = (const Camera*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetHalfViewSize'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetHalfViewSize();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetHalfViewSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSplitFrustum of class  Camera */
#ifndef TOLUA_DISABLE_tolua_Graphics_Camera_GetSplitFrustum00
static int tolua_Graphics_Camera_GetSplitFrustum00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Camera",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Camera* self = (const Camera*)  tolua_tousertype(tolua_S,1,0);
  float nearClip = ((float)  tolua_tonumber(tolua_S,2,0));
  float farClip = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSplitFrustum'", NULL);
#endif
  {
   Frustum tolua_ret = (Frustum)  self->GetSplitFrustum(nearClip,farClip);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((Frustum)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"Frustum");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Frustum));
     tolua_pushusertype(tolua_S,tolua_obj,"Frustum");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSplitFrustum'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetViewSpaceFrustum of class  Camera */
#ifndef TOLUA_DISABLE_tolua_Graphics_Camera_GetViewSpaceFrustum00
static int tolua_Graphics_Camera_GetViewSpaceFrustum00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Camera",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Camera* self = (const Camera*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetViewSpaceFrustum'", NULL);
#endif
  {
   Frustum tolua_ret = (Frustum)  self->GetViewSpaceFrustum();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((Frustum)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"Frustum");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Frustum));
     tolua_pushusertype(tolua_S,tolua_obj,"Frustum");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetViewSpaceFrustum'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetViewSpaceSplitFrustum of class  Camera */
#ifndef TOLUA_DISABLE_tolua_Graphics_Camera_GetViewSpaceSplitFrustum00
static int tolua_Graphics_Camera_GetViewSpaceSplitFrustum00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Camera",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Camera* self = (const Camera*)  tolua_tousertype(tolua_S,1,0);
  float nearClip = ((float)  tolua_tonumber(tolua_S,2,0));
  float farClip = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetViewSpaceSplitFrustum'", NULL);
#endif
  {
   Frustum tolua_ret = (Frustum)  self->GetViewSpaceSplitFrustum(nearClip,farClip);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((Frustum)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"Frustum");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Frustum));
     tolua_pushusertype(tolua_S,tolua_obj,"Frustum");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetViewSpaceSplitFrustum'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetScreenRay of class  Camera */
#ifndef TOLUA_DISABLE_tolua_Graphics_Camera_GetScreenRay00
static int tolua_Graphics_Camera_GetScreenRay00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Camera",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Camera* self = (const Camera*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetScreenRay'", NULL);
#endif
  {
   Ray tolua_ret = (Ray)  self->GetScreenRay(x,y);
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((Ray)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"Ray");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Ray));
     tolua_pushusertype(tolua_S,tolua_obj,"Ray");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetScreenRay'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: WorldToScreenPoint of class  Camera */
#ifndef TOLUA_DISABLE_tolua_Graphics_Camera_WorldToScreenPoint00
static int tolua_Graphics_Camera_WorldToScreenPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Camera",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Camera* self = (const Camera*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* worldPos = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'WorldToScreenPoint'", NULL);
#endif
  {
   Vector2 tolua_ret = (Vector2)  self->WorldToScreenPoint(*worldPos);
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
 tolua_error(tolua_S,"#ferror in function 'WorldToScreenPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ScreenToWorldPoint of class  Camera */
#ifndef TOLUA_DISABLE_tolua_Graphics_Camera_ScreenToWorldPoint00
static int tolua_Graphics_Camera_ScreenToWorldPoint00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Camera",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Camera* self = (const Camera*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* screenPos = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ScreenToWorldPoint'", NULL);
#endif
  {
   Vector3 tolua_ret = (Vector3)  self->ScreenToWorldPoint(*screenPos);
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
 tolua_error(tolua_S,"#ferror in function 'ScreenToWorldPoint'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetForwardVector of class  Camera */
#ifndef TOLUA_DISABLE_tolua_Graphics_Camera_GetForwardVector00
static int tolua_Graphics_Camera_GetForwardVector00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Camera",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Camera* self = (const Camera*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetForwardVector'", NULL);
#endif
  {
   Vector3 tolua_ret = (Vector3)  self->GetForwardVector();
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
 tolua_error(tolua_S,"#ferror in function 'GetForwardVector'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRightVector of class  Camera */
#ifndef TOLUA_DISABLE_tolua_Graphics_Camera_GetRightVector00
static int tolua_Graphics_Camera_GetRightVector00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Camera",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Camera* self = (const Camera*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRightVector'", NULL);
#endif
  {
   Vector3 tolua_ret = (Vector3)  self->GetRightVector();
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
 tolua_error(tolua_S,"#ferror in function 'GetRightVector'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetUpVector of class  Camera */
#ifndef TOLUA_DISABLE_tolua_Graphics_Camera_GetUpVector00
static int tolua_Graphics_Camera_GetUpVector00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Camera",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Camera* self = (const Camera*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetUpVector'", NULL);
#endif
  {
   Vector3 tolua_ret = (Vector3)  self->GetUpVector();
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
 tolua_error(tolua_S,"#ferror in function 'GetUpVector'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetProjectionOffset of class  Camera */
#ifndef TOLUA_DISABLE_tolua_Graphics_Camera_GetProjectionOffset00
static int tolua_Graphics_Camera_GetProjectionOffset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Camera",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Camera* self = (const Camera*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetProjectionOffset'", NULL);
#endif
  {
   const Vector2& tolua_ret = (const Vector2&)  self->GetProjectionOffset();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Vector2");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetProjectionOffset'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFlipVertical of class  Camera */
#ifndef TOLUA_DISABLE_tolua_Graphics_Camera_GetFlipVertical00
static int tolua_Graphics_Camera_GetFlipVertical00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Camera",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Camera* self = (const Camera*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFlipVertical'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetFlipVertical();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFlipVertical'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetDistance of class  Camera */
#ifndef TOLUA_DISABLE_tolua_Graphics_Camera_GetDistance00
static int tolua_Graphics_Camera_GetDistance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Camera",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Camera* self = (const Camera*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* worldPos = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetDistance'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetDistance(*worldPos);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDistance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetDistanceSquared of class  Camera */
#ifndef TOLUA_DISABLE_tolua_Graphics_Camera_GetDistanceSquared00
static int tolua_Graphics_Camera_GetDistanceSquared00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Camera",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Camera* self = (const Camera*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* worldPos = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetDistanceSquared'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetDistanceSquared(*worldPos);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDistanceSquared'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLodDistance of class  Camera */
#ifndef TOLUA_DISABLE_tolua_Graphics_Camera_GetLodDistance00
static int tolua_Graphics_Camera_GetLodDistance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Camera",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Camera* self = (const Camera*)  tolua_tousertype(tolua_S,1,0);
  float distance = ((float)  tolua_tonumber(tolua_S,2,0));
  float scale = ((float)  tolua_tonumber(tolua_S,3,0));
  float bias = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLodDistance'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetLodDistance(distance,scale,bias);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLodDistance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsProjectionValid of class  Camera */
#ifndef TOLUA_DISABLE_tolua_Graphics_Camera_IsProjectionValid00
static int tolua_Graphics_Camera_IsProjectionValid00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Camera",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Camera* self = (const Camera*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsProjectionValid'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsProjectionValid();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsProjectionValid'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddLine of class  DebugRenderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_DebugRenderer_AddLine00
static int tolua_Graphics_DebugRenderer_AddLine00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DebugRenderer",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const Vector3",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"const Color",0,&tolua_err)) ||
     !tolua_isboolean(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DebugRenderer* self = (DebugRenderer*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* start = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
  const Vector3* end = ((const Vector3*)  tolua_tousertype(tolua_S,3,0));
  const Color* color = ((const Color*)  tolua_tousertype(tolua_S,4,0));
  bool depthTest = ((bool)  tolua_toboolean(tolua_S,5,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddLine'", NULL);
#endif
  {
   self->AddLine(*start,*end,*color,depthTest);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddLine'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddLine of class  DebugRenderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_DebugRenderer_AddLine01
static int tolua_Graphics_DebugRenderer_AddLine01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DebugRenderer",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const Vector3",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  DebugRenderer* self = (DebugRenderer*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* start = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
  const Vector3* end = ((const Vector3*)  tolua_tousertype(tolua_S,3,0));
  unsigned color = ((unsigned)  tolua_tonumber(tolua_S,4,0));
  bool depthTest = ((bool)  tolua_toboolean(tolua_S,5,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddLine'", NULL);
#endif
  {
   self->AddLine(*start,*end,color,depthTest);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Graphics_DebugRenderer_AddLine00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddNode of class  DebugRenderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_DebugRenderer_AddNode00
static int tolua_Graphics_DebugRenderer_AddNode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DebugRenderer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Node",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DebugRenderer* self = (DebugRenderer*)  tolua_tousertype(tolua_S,1,0);
  Node* node = ((Node*)  tolua_tousertype(tolua_S,2,0));
  float scale = ((float)  tolua_tonumber(tolua_S,3,1.0f));
  bool depthTest = ((bool)  tolua_toboolean(tolua_S,4,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddNode'", NULL);
#endif
  {
   self->AddNode(node,scale,depthTest);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddNode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddBoundingBox of class  DebugRenderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_DebugRenderer_AddBoundingBox00
static int tolua_Graphics_DebugRenderer_AddBoundingBox00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DebugRenderer",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const BoundingBox",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const Color",0,&tolua_err)) ||
     !tolua_isboolean(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DebugRenderer* self = (DebugRenderer*)  tolua_tousertype(tolua_S,1,0);
  const BoundingBox* box = ((const BoundingBox*)  tolua_tousertype(tolua_S,2,0));
  const Color* color = ((const Color*)  tolua_tousertype(tolua_S,3,0));
  bool depthTest = ((bool)  tolua_toboolean(tolua_S,4,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddBoundingBox'", NULL);
#endif
  {
   self->AddBoundingBox(*box,*color,depthTest);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddBoundingBox'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddBoundingBox of class  DebugRenderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_DebugRenderer_AddBoundingBox01
static int tolua_Graphics_DebugRenderer_AddBoundingBox01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DebugRenderer",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const BoundingBox",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const Matrix3x4",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"const Color",0,&tolua_err)) ||
     !tolua_isboolean(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  DebugRenderer* self = (DebugRenderer*)  tolua_tousertype(tolua_S,1,0);
  const BoundingBox* box = ((const BoundingBox*)  tolua_tousertype(tolua_S,2,0));
  const Matrix3x4* transform = ((const Matrix3x4*)  tolua_tousertype(tolua_S,3,0));
  const Color* color = ((const Color*)  tolua_tousertype(tolua_S,4,0));
  bool depthTest = ((bool)  tolua_toboolean(tolua_S,5,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddBoundingBox'", NULL);
#endif
  {
   self->AddBoundingBox(*box,*transform,*color,depthTest);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Graphics_DebugRenderer_AddBoundingBox00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddFrustum of class  DebugRenderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_DebugRenderer_AddFrustum00
static int tolua_Graphics_DebugRenderer_AddFrustum00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DebugRenderer",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Frustum",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const Color",0,&tolua_err)) ||
     !tolua_isboolean(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DebugRenderer* self = (DebugRenderer*)  tolua_tousertype(tolua_S,1,0);
  const Frustum* frustum = ((const Frustum*)  tolua_tousertype(tolua_S,2,0));
  const Color* color = ((const Color*)  tolua_tousertype(tolua_S,3,0));
  bool depthTest = ((bool)  tolua_toboolean(tolua_S,4,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddFrustum'", NULL);
#endif
  {
   self->AddFrustum(*frustum,*color,depthTest);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddFrustum'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddPolyhedron of class  DebugRenderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_DebugRenderer_AddPolyhedron00
static int tolua_Graphics_DebugRenderer_AddPolyhedron00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DebugRenderer",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Polyhedron",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const Color",0,&tolua_err)) ||
     !tolua_isboolean(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DebugRenderer* self = (DebugRenderer*)  tolua_tousertype(tolua_S,1,0);
  const Polyhedron* poly = ((const Polyhedron*)  tolua_tousertype(tolua_S,2,0));
  const Color* color = ((const Color*)  tolua_tousertype(tolua_S,3,0));
  bool depthTest = ((bool)  tolua_toboolean(tolua_S,4,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddPolyhedron'", NULL);
#endif
  {
   self->AddPolyhedron(*poly,*color,depthTest);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddPolyhedron'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddSphere of class  DebugRenderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_DebugRenderer_AddSphere00
static int tolua_Graphics_DebugRenderer_AddSphere00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DebugRenderer",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Sphere",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const Color",0,&tolua_err)) ||
     !tolua_isboolean(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DebugRenderer* self = (DebugRenderer*)  tolua_tousertype(tolua_S,1,0);
  const Sphere* sphere = ((const Sphere*)  tolua_tousertype(tolua_S,2,0));
  const Color* color = ((const Color*)  tolua_tousertype(tolua_S,3,0));
  bool depthTest = ((bool)  tolua_toboolean(tolua_S,4,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddSphere'", NULL);
#endif
  {
   self->AddSphere(*sphere,*color,depthTest);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddSphere'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddSkeleton of class  DebugRenderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_DebugRenderer_AddSkeleton00
static int tolua_Graphics_DebugRenderer_AddSkeleton00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DebugRenderer",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Skeleton",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const Color",0,&tolua_err)) ||
     !tolua_isboolean(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DebugRenderer* self = (DebugRenderer*)  tolua_tousertype(tolua_S,1,0);
  const Skeleton* skeleton = ((const Skeleton*)  tolua_tousertype(tolua_S,2,0));
  const Color* color = ((const Color*)  tolua_tousertype(tolua_S,3,0));
  bool depthTest = ((bool)  tolua_toboolean(tolua_S,4,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddSkeleton'", NULL);
#endif
  {
   self->AddSkeleton(*skeleton,*color,depthTest);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddSkeleton'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GetDebugRenderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_GetDebugRenderer00
static int tolua_Graphics_GetDebugRenderer00(lua_State* tolua_S)
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
   DebugRenderer* tolua_ret = (DebugRenderer*)  GetDebugRenderer();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"DebugRenderer");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDebugRenderer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMaterial of class  DecalSet */
#ifndef TOLUA_DISABLE_tolua_Graphics_DecalSet_SetMaterial00
static int tolua_Graphics_DecalSet_SetMaterial00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DecalSet",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Material",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DecalSet* self = (DecalSet*)  tolua_tousertype(tolua_S,1,0);
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

/* method: SetMaxVertices of class  DecalSet */
#ifndef TOLUA_DISABLE_tolua_Graphics_DecalSet_SetMaxVertices00
static int tolua_Graphics_DecalSet_SetMaxVertices00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DecalSet",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DecalSet* self = (DecalSet*)  tolua_tousertype(tolua_S,1,0);
  unsigned num = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMaxVertices'", NULL);
#endif
  {
   self->SetMaxVertices(num);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMaxVertices'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMaxIndices of class  DecalSet */
#ifndef TOLUA_DISABLE_tolua_Graphics_DecalSet_SetMaxIndices00
static int tolua_Graphics_DecalSet_SetMaxIndices00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DecalSet",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DecalSet* self = (DecalSet*)  tolua_tousertype(tolua_S,1,0);
  unsigned num = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMaxIndices'", NULL);
#endif
  {
   self->SetMaxIndices(num);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMaxIndices'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddDecal of class  DecalSet */
#ifndef TOLUA_DISABLE_tolua_Graphics_DecalSet_AddDecal00
static int tolua_Graphics_DecalSet_AddDecal00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DecalSet",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Drawable",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"const Vector3",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,4,&tolua_err) || !tolua_isusertype(tolua_S,4,"const Quaternion",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,8,&tolua_err) || !tolua_isusertype(tolua_S,8,"const Vector2",0,&tolua_err)) ||
     (tolua_isvaluenil(tolua_S,9,&tolua_err) || !tolua_isusertype(tolua_S,9,"const Vector2",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,10,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,11,1,&tolua_err) ||
     !tolua_isnumber(tolua_S,12,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,13,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DecalSet* self = (DecalSet*)  tolua_tousertype(tolua_S,1,0);
  Drawable* target = ((Drawable*)  tolua_tousertype(tolua_S,2,0));
  const Vector3* worldPosition = ((const Vector3*)  tolua_tousertype(tolua_S,3,0));
  const Quaternion* worldRotation = ((const Quaternion*)  tolua_tousertype(tolua_S,4,0));
  float size = ((float)  tolua_tonumber(tolua_S,5,0));
  float aspectRatio = ((float)  tolua_tonumber(tolua_S,6,0));
  float depth = ((float)  tolua_tonumber(tolua_S,7,0));
  const Vector2* topLeftUV = ((const Vector2*)  tolua_tousertype(tolua_S,8,0));
  const Vector2* bottomRightUV = ((const Vector2*)  tolua_tousertype(tolua_S,9,0));
  float timeToLive = ((float)  tolua_tonumber(tolua_S,10,0.0f));
  float normalCutoff = ((float)  tolua_tonumber(tolua_S,11,0.1f));
  unsigned subGeometry = ((unsigned)  tolua_tonumber(tolua_S,12,M_MAX_UNSIGNED));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddDecal'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->AddDecal(target,*worldPosition,*worldRotation,size,aspectRatio,depth,*topLeftUV,*bottomRightUV,timeToLive,normalCutoff,subGeometry);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddDecal'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveDecals of class  DecalSet */
#ifndef TOLUA_DISABLE_tolua_Graphics_DecalSet_RemoveDecals00
static int tolua_Graphics_DecalSet_RemoveDecals00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DecalSet",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DecalSet* self = (DecalSet*)  tolua_tousertype(tolua_S,1,0);
  unsigned num = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveDecals'", NULL);
#endif
  {
   self->RemoveDecals(num);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemoveDecals'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveAllDecals of class  DecalSet */
#ifndef TOLUA_DISABLE_tolua_Graphics_DecalSet_RemoveAllDecals00
static int tolua_Graphics_DecalSet_RemoveAllDecals00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"DecalSet",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  DecalSet* self = (DecalSet*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveAllDecals'", NULL);
#endif
  {
   self->RemoveAllDecals();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemoveAllDecals'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMaterial of class  DecalSet */
#ifndef TOLUA_DISABLE_tolua_Graphics_DecalSet_GetMaterial00
static int tolua_Graphics_DecalSet_GetMaterial00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const DecalSet",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const DecalSet* self = (const DecalSet*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetNumDecals of class  DecalSet */
#ifndef TOLUA_DISABLE_tolua_Graphics_DecalSet_GetNumDecals00
static int tolua_Graphics_DecalSet_GetNumDecals00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const DecalSet",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const DecalSet* self = (const DecalSet*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNumDecals'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetNumDecals();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNumDecals'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNumVertices of class  DecalSet */
#ifndef TOLUA_DISABLE_tolua_Graphics_DecalSet_GetNumVertices00
static int tolua_Graphics_DecalSet_GetNumVertices00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const DecalSet",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const DecalSet* self = (const DecalSet*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNumVertices'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetNumVertices();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNumVertices'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNumIndices of class  DecalSet */
#ifndef TOLUA_DISABLE_tolua_Graphics_DecalSet_GetNumIndices00
static int tolua_Graphics_DecalSet_GetNumIndices00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const DecalSet",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const DecalSet* self = (const DecalSet*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNumIndices'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetNumIndices();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNumIndices'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMaxVertices of class  DecalSet */
#ifndef TOLUA_DISABLE_tolua_Graphics_DecalSet_GetMaxVertices00
static int tolua_Graphics_DecalSet_GetMaxVertices00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const DecalSet",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const DecalSet* self = (const DecalSet*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMaxVertices'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetMaxVertices();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMaxVertices'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMaxIndices of class  DecalSet */
#ifndef TOLUA_DISABLE_tolua_Graphics_DecalSet_GetMaxIndices00
static int tolua_Graphics_DecalSet_GetMaxIndices00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const DecalSet",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const DecalSet* self = (const DecalSet*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMaxIndices'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetMaxIndices();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMaxIndices'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetDrawDistance of class  Drawable */
#ifndef TOLUA_DISABLE_tolua_Graphics_Drawable_SetDrawDistance00
static int tolua_Graphics_Drawable_SetDrawDistance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Drawable",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Drawable* self = (Drawable*)  tolua_tousertype(tolua_S,1,0);
  float distance = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetDrawDistance'", NULL);
#endif
  {
   self->SetDrawDistance(distance);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetDrawDistance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetShadowDistance of class  Drawable */
#ifndef TOLUA_DISABLE_tolua_Graphics_Drawable_SetShadowDistance00
static int tolua_Graphics_Drawable_SetShadowDistance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Drawable",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Drawable* self = (Drawable*)  tolua_tousertype(tolua_S,1,0);
  float distance = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetShadowDistance'", NULL);
#endif
  {
   self->SetShadowDistance(distance);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetShadowDistance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetLodBias of class  Drawable */
#ifndef TOLUA_DISABLE_tolua_Graphics_Drawable_SetLodBias00
static int tolua_Graphics_Drawable_SetLodBias00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Drawable",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Drawable* self = (Drawable*)  tolua_tousertype(tolua_S,1,0);
  float bias = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLodBias'", NULL);
#endif
  {
   self->SetLodBias(bias);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLodBias'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetViewMask of class  Drawable */
#ifndef TOLUA_DISABLE_tolua_Graphics_Drawable_SetViewMask00
static int tolua_Graphics_Drawable_SetViewMask00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Drawable",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Drawable* self = (Drawable*)  tolua_tousertype(tolua_S,1,0);
  unsigned mask = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetViewMask'", NULL);
#endif
  {
   self->SetViewMask(mask);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetViewMask'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetLightMask of class  Drawable */
#ifndef TOLUA_DISABLE_tolua_Graphics_Drawable_SetLightMask00
static int tolua_Graphics_Drawable_SetLightMask00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Drawable",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Drawable* self = (Drawable*)  tolua_tousertype(tolua_S,1,0);
  unsigned mask = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLightMask'", NULL);
#endif
  {
   self->SetLightMask(mask);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLightMask'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetShadowMask of class  Drawable */
#ifndef TOLUA_DISABLE_tolua_Graphics_Drawable_SetShadowMask00
static int tolua_Graphics_Drawable_SetShadowMask00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Drawable",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Drawable* self = (Drawable*)  tolua_tousertype(tolua_S,1,0);
  unsigned mask = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetShadowMask'", NULL);
#endif
  {
   self->SetShadowMask(mask);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetShadowMask'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetZoneMask of class  Drawable */
#ifndef TOLUA_DISABLE_tolua_Graphics_Drawable_SetZoneMask00
static int tolua_Graphics_Drawable_SetZoneMask00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Drawable",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Drawable* self = (Drawable*)  tolua_tousertype(tolua_S,1,0);
  unsigned mask = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetZoneMask'", NULL);
#endif
  {
   self->SetZoneMask(mask);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetZoneMask'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMaxLights of class  Drawable */
#ifndef TOLUA_DISABLE_tolua_Graphics_Drawable_SetMaxLights00
static int tolua_Graphics_Drawable_SetMaxLights00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Drawable",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Drawable* self = (Drawable*)  tolua_tousertype(tolua_S,1,0);
  unsigned num = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMaxLights'", NULL);
#endif
  {
   self->SetMaxLights(num);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMaxLights'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetCastShadows of class  Drawable */
#ifndef TOLUA_DISABLE_tolua_Graphics_Drawable_SetCastShadows00
static int tolua_Graphics_Drawable_SetCastShadows00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Drawable",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Drawable* self = (Drawable*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetCastShadows'", NULL);
#endif
  {
   self->SetCastShadows(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetCastShadows'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetOccluder of class  Drawable */
#ifndef TOLUA_DISABLE_tolua_Graphics_Drawable_SetOccluder00
static int tolua_Graphics_Drawable_SetOccluder00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Drawable",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Drawable* self = (Drawable*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetOccluder'", NULL);
#endif
  {
   self->SetOccluder(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetOccluder'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetOccludee of class  Drawable */
#ifndef TOLUA_DISABLE_tolua_Graphics_Drawable_SetOccludee00
static int tolua_Graphics_Drawable_SetOccludee00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Drawable",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Drawable* self = (Drawable*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetOccludee'", NULL);
#endif
  {
   self->SetOccludee(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetOccludee'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: MarkForUpdate of class  Drawable */
#ifndef TOLUA_DISABLE_tolua_Graphics_Drawable_MarkForUpdate00
static int tolua_Graphics_Drawable_MarkForUpdate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Drawable",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Drawable* self = (Drawable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'MarkForUpdate'", NULL);
#endif
  {
   self->MarkForUpdate();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MarkForUpdate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetWorldBoundingBox of class  Drawable */
#ifndef TOLUA_DISABLE_tolua_Graphics_Drawable_GetWorldBoundingBox00
static int tolua_Graphics_Drawable_GetWorldBoundingBox00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Drawable",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Drawable* self = (Drawable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetWorldBoundingBox'", NULL);
#endif
  {
   const BoundingBox& tolua_ret = (const BoundingBox&)  self->GetWorldBoundingBox();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const BoundingBox");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetWorldBoundingBox'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetDrawableFlags of class  Drawable */
#ifndef TOLUA_DISABLE_tolua_Graphics_Drawable_GetDrawableFlags00
static int tolua_Graphics_Drawable_GetDrawableFlags00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Drawable",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Drawable* self = (const Drawable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetDrawableFlags'", NULL);
#endif
  {
   unsigned char tolua_ret = (unsigned char)  self->GetDrawableFlags();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDrawableFlags'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetDrawDistance of class  Drawable */
#ifndef TOLUA_DISABLE_tolua_Graphics_Drawable_GetDrawDistance00
static int tolua_Graphics_Drawable_GetDrawDistance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Drawable",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Drawable* self = (const Drawable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetDrawDistance'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetDrawDistance();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDrawDistance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetShadowDistance of class  Drawable */
#ifndef TOLUA_DISABLE_tolua_Graphics_Drawable_GetShadowDistance00
static int tolua_Graphics_Drawable_GetShadowDistance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Drawable",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Drawable* self = (const Drawable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetShadowDistance'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetShadowDistance();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetShadowDistance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLodBias of class  Drawable */
#ifndef TOLUA_DISABLE_tolua_Graphics_Drawable_GetLodBias00
static int tolua_Graphics_Drawable_GetLodBias00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Drawable",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Drawable* self = (const Drawable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLodBias'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetLodBias();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLodBias'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetViewMask of class  Drawable */
#ifndef TOLUA_DISABLE_tolua_Graphics_Drawable_GetViewMask00
static int tolua_Graphics_Drawable_GetViewMask00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Drawable",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Drawable* self = (const Drawable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetViewMask'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetViewMask();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetViewMask'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLightMask of class  Drawable */
#ifndef TOLUA_DISABLE_tolua_Graphics_Drawable_GetLightMask00
static int tolua_Graphics_Drawable_GetLightMask00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Drawable",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Drawable* self = (const Drawable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLightMask'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetLightMask();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLightMask'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetShadowMask of class  Drawable */
#ifndef TOLUA_DISABLE_tolua_Graphics_Drawable_GetShadowMask00
static int tolua_Graphics_Drawable_GetShadowMask00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Drawable",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Drawable* self = (const Drawable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetShadowMask'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetShadowMask();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetShadowMask'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetZoneMask of class  Drawable */
#ifndef TOLUA_DISABLE_tolua_Graphics_Drawable_GetZoneMask00
static int tolua_Graphics_Drawable_GetZoneMask00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Drawable",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Drawable* self = (const Drawable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetZoneMask'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetZoneMask();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetZoneMask'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMaxLights of class  Drawable */
#ifndef TOLUA_DISABLE_tolua_Graphics_Drawable_GetMaxLights00
static int tolua_Graphics_Drawable_GetMaxLights00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Drawable",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Drawable* self = (const Drawable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMaxLights'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetMaxLights();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMaxLights'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCastShadows of class  Drawable */
#ifndef TOLUA_DISABLE_tolua_Graphics_Drawable_GetCastShadows00
static int tolua_Graphics_Drawable_GetCastShadows00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Drawable",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Drawable* self = (const Drawable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCastShadows'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetCastShadows();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCastShadows'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsOccluder of class  Drawable */
#ifndef TOLUA_DISABLE_tolua_Graphics_Drawable_IsOccluder00
static int tolua_Graphics_Drawable_IsOccluder00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Drawable",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Drawable* self = (const Drawable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsOccluder'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsOccluder();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsOccluder'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsOccludee of class  Drawable */
#ifndef TOLUA_DISABLE_tolua_Graphics_Drawable_IsOccludee00
static int tolua_Graphics_Drawable_IsOccludee00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Drawable",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Drawable* self = (const Drawable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsOccludee'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsOccludee();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsOccludee'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetZone of class  Drawable */
#ifndef TOLUA_DISABLE_tolua_Graphics_Drawable_SetZone00
static int tolua_Graphics_Drawable_SetZone00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Drawable",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Zone",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Drawable* self = (Drawable*)  tolua_tousertype(tolua_S,1,0);
  Zone* zone = ((Zone*)  tolua_tousertype(tolua_S,2,0));
  bool temporary = ((bool)  tolua_toboolean(tolua_S,3,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetZone'", NULL);
#endif
  {
   self->SetZone(zone,temporary);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetZone'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetSortValue of class  Drawable */
#ifndef TOLUA_DISABLE_tolua_Graphics_Drawable_SetSortValue00
static int tolua_Graphics_Drawable_SetSortValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Drawable",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Drawable* self = (Drawable*)  tolua_tousertype(tolua_S,1,0);
  float value = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetSortValue'", NULL);
#endif
  {
   self->SetSortValue(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetSortValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMinMaxZ of class  Drawable */
#ifndef TOLUA_DISABLE_tolua_Graphics_Drawable_SetMinMaxZ00
static int tolua_Graphics_Drawable_SetMinMaxZ00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Drawable",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Drawable* self = (Drawable*)  tolua_tousertype(tolua_S,1,0);
  float minZ = ((float)  tolua_tonumber(tolua_S,2,0));
  float maxZ = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMinMaxZ'", NULL);
#endif
  {
   self->SetMinMaxZ(minZ,maxZ);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMinMaxZ'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: MarkInView of class  Drawable */
#ifndef TOLUA_DISABLE_tolua_Graphics_Drawable_MarkInView00
static int tolua_Graphics_Drawable_MarkInView00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Drawable",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const FrameInfo",0,&tolua_err)) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Drawable* self = (Drawable*)  tolua_tousertype(tolua_S,1,0);
  const FrameInfo* frame = ((const FrameInfo*)  tolua_tousertype(tolua_S,2,0));
  bool mainView = ((bool)  tolua_toboolean(tolua_S,3,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'MarkInView'", NULL);
#endif
  {
   self->MarkInView(*frame,mainView);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'MarkInView'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ClearLights of class  Drawable */
#ifndef TOLUA_DISABLE_tolua_Graphics_Drawable_ClearLights00
static int tolua_Graphics_Drawable_ClearLights00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Drawable",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Drawable* self = (Drawable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ClearLights'", NULL);
#endif
  {
   self->ClearLights();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ClearLights'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddLight of class  Drawable */
#ifndef TOLUA_DISABLE_tolua_Graphics_Drawable_AddLight00
static int tolua_Graphics_Drawable_AddLight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Drawable",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Light",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Drawable* self = (Drawable*)  tolua_tousertype(tolua_S,1,0);
  Light* light = ((Light*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddLight'", NULL);
#endif
  {
   self->AddLight(light);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddLight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: AddVertexLight of class  Drawable */
#ifndef TOLUA_DISABLE_tolua_Graphics_Drawable_AddVertexLight00
static int tolua_Graphics_Drawable_AddVertexLight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Drawable",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Light",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Drawable* self = (Drawable*)  tolua_tousertype(tolua_S,1,0);
  Light* light = ((Light*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddVertexLight'", NULL);
#endif
  {
   self->AddVertexLight(light);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddVertexLight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LimitLights of class  Drawable */
#ifndef TOLUA_DISABLE_tolua_Graphics_Drawable_LimitLights00
static int tolua_Graphics_Drawable_LimitLights00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Drawable",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Drawable* self = (Drawable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LimitLights'", NULL);
#endif
  {
   self->LimitLights();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LimitLights'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: LimitVertexLights of class  Drawable */
#ifndef TOLUA_DISABLE_tolua_Graphics_Drawable_LimitVertexLights00
static int tolua_Graphics_Drawable_LimitVertexLights00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Drawable",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Drawable* self = (Drawable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LimitVertexLights'", NULL);
#endif
  {
   self->LimitVertexLights();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LimitVertexLights'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetBasePass of class  Drawable */
#ifndef TOLUA_DISABLE_tolua_Graphics_Drawable_SetBasePass00
static int tolua_Graphics_Drawable_SetBasePass00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Drawable",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Drawable* self = (Drawable*)  tolua_tousertype(tolua_S,1,0);
  unsigned batchIndex = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetBasePass'", NULL);
#endif
  {
   self->SetBasePass(batchIndex);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetBasePass'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetOctant of class  Drawable */
#ifndef TOLUA_DISABLE_tolua_Graphics_Drawable_GetOctant00
static int tolua_Graphics_Drawable_GetOctant00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Drawable",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Drawable* self = (const Drawable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetOctant'", NULL);
#endif
  {
   Octant* tolua_ret = (Octant*)  self->GetOctant();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Octant");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetOctant'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetZone of class  Drawable */
#ifndef TOLUA_DISABLE_tolua_Graphics_Drawable_GetZone00
static int tolua_Graphics_Drawable_GetZone00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Drawable",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Drawable* self = (const Drawable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetZone'", NULL);
#endif
  {
   Zone* tolua_ret = (Zone*)  self->GetZone();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Zone");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetZone'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLastZone of class  Drawable */
#ifndef TOLUA_DISABLE_tolua_Graphics_Drawable_GetLastZone00
static int tolua_Graphics_Drawable_GetLastZone00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Drawable",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Drawable* self = (const Drawable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLastZone'", NULL);
#endif
  {
   Zone* tolua_ret = (Zone*)  self->GetLastZone();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Zone");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLastZone'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsZoneDirty of class  Drawable */
#ifndef TOLUA_DISABLE_tolua_Graphics_Drawable_IsZoneDirty00
static int tolua_Graphics_Drawable_IsZoneDirty00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Drawable",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Drawable* self = (const Drawable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsZoneDirty'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsZoneDirty();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsZoneDirty'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetDistance of class  Drawable */
#ifndef TOLUA_DISABLE_tolua_Graphics_Drawable_GetDistance00
static int tolua_Graphics_Drawable_GetDistance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Drawable",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Drawable* self = (const Drawable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetDistance'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetDistance();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDistance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLodDistance of class  Drawable */
#ifndef TOLUA_DISABLE_tolua_Graphics_Drawable_GetLodDistance00
static int tolua_Graphics_Drawable_GetLodDistance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Drawable",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Drawable* self = (const Drawable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLodDistance'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetLodDistance();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLodDistance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSortValue of class  Drawable */
#ifndef TOLUA_DISABLE_tolua_Graphics_Drawable_GetSortValue00
static int tolua_Graphics_Drawable_GetSortValue00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Drawable",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Drawable* self = (const Drawable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSortValue'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetSortValue();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSortValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsInView of class  Drawable */
#ifndef TOLUA_DISABLE_tolua_Graphics_Drawable_IsInView00
static int tolua_Graphics_Drawable_IsInView00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Drawable",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Drawable* self = (const Drawable*)  tolua_tousertype(tolua_S,1,0);
  unsigned frameNumber = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsInView'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsInView(frameNumber);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsInView'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsInView of class  Drawable */
#ifndef TOLUA_DISABLE_tolua_Graphics_Drawable_IsInView01
static int tolua_Graphics_Drawable_IsInView01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Drawable",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const FrameInfo",0,&tolua_err)) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const Drawable* self = (const Drawable*)  tolua_tousertype(tolua_S,1,0);
  const FrameInfo* frame = ((const FrameInfo*)  tolua_tousertype(tolua_S,2,0));
  bool mainView = ((bool)  tolua_toboolean(tolua_S,3,true));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsInView'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsInView(*frame,mainView);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_Graphics_Drawable_IsInView00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: HasBasePass of class  Drawable */
#ifndef TOLUA_DISABLE_tolua_Graphics_Drawable_HasBasePass00
static int tolua_Graphics_Drawable_HasBasePass00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Drawable",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Drawable* self = (const Drawable*)  tolua_tousertype(tolua_S,1,0);
  unsigned batchIndex = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'HasBasePass'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->HasBasePass(batchIndex);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'HasBasePass'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFirstLight of class  Drawable */
#ifndef TOLUA_DISABLE_tolua_Graphics_Drawable_GetFirstLight00
static int tolua_Graphics_Drawable_GetFirstLight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Drawable",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Drawable* self = (const Drawable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFirstLight'", NULL);
#endif
  {
   Light* tolua_ret = (Light*)  self->GetFirstLight();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Light");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFirstLight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMinZ of class  Drawable */
#ifndef TOLUA_DISABLE_tolua_Graphics_Drawable_GetMinZ00
static int tolua_Graphics_Drawable_GetMinZ00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Drawable",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Drawable* self = (const Drawable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMinZ'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetMinZ();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMinZ'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMaxZ of class  Drawable */
#ifndef TOLUA_DISABLE_tolua_Graphics_Drawable_GetMaxZ00
static int tolua_Graphics_Drawable_GetMaxZ00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Drawable",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Drawable* self = (const Drawable*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMaxZ'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetMaxZ();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMaxZ'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetWindowTitle of class  Graphics */
#ifndef TOLUA_DISABLE_tolua_Graphics_Graphics_SetWindowTitle00
static int tolua_Graphics_Graphics_SetWindowTitle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Graphics",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Graphics* self = (Graphics*)  tolua_tousertype(tolua_S,1,0);
  const char* windowTitle = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetWindowTitle'", NULL);
#endif
  {
   self->SetWindowTitle(windowTitle);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetWindowTitle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetSRGB of class  Graphics */
#ifndef TOLUA_DISABLE_tolua_Graphics_Graphics_SetSRGB00
static int tolua_Graphics_Graphics_SetSRGB00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Graphics",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Graphics* self = (Graphics*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetSRGB'", NULL);
#endif
  {
   self->SetSRGB(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetSRGB'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ToggleFullscreen of class  Graphics */
#ifndef TOLUA_DISABLE_tolua_Graphics_Graphics_ToggleFullscreen00
static int tolua_Graphics_Graphics_ToggleFullscreen00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Graphics",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Graphics* self = (Graphics*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ToggleFullscreen'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->ToggleFullscreen();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ToggleFullscreen'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: TakeScreenShot of class  Graphics */
#ifndef TOLUA_DISABLE_tolua_Graphics_Graphics_TakeScreenShot00
static int tolua_Graphics_Graphics_TakeScreenShot00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Graphics",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"Image",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Graphics* self = (Graphics*)  tolua_tousertype(tolua_S,1,0);
  Image* destImage = ((Image*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'TakeScreenShot'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->TakeScreenShot(*destImage);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'TakeScreenShot'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsInitialized of class  Graphics */
#ifndef TOLUA_DISABLE_tolua_Graphics_Graphics_IsInitialized00
static int tolua_Graphics_Graphics_IsInitialized00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Graphics",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Graphics* self = (const Graphics*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetWidth of class  Graphics */
#ifndef TOLUA_DISABLE_tolua_Graphics_Graphics_GetWidth00
static int tolua_Graphics_Graphics_GetWidth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Graphics",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Graphics* self = (const Graphics*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetHeight of class  Graphics */
#ifndef TOLUA_DISABLE_tolua_Graphics_Graphics_GetHeight00
static int tolua_Graphics_Graphics_GetHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Graphics",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Graphics* self = (const Graphics*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetMultiSample of class  Graphics */
#ifndef TOLUA_DISABLE_tolua_Graphics_Graphics_GetMultiSample00
static int tolua_Graphics_Graphics_GetMultiSample00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Graphics",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Graphics* self = (const Graphics*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMultiSample'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetMultiSample();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMultiSample'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFullscreen of class  Graphics */
#ifndef TOLUA_DISABLE_tolua_Graphics_Graphics_GetFullscreen00
static int tolua_Graphics_Graphics_GetFullscreen00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Graphics",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Graphics* self = (const Graphics*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFullscreen'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetFullscreen();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFullscreen'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetResizable of class  Graphics */
#ifndef TOLUA_DISABLE_tolua_Graphics_Graphics_GetResizable00
static int tolua_Graphics_Graphics_GetResizable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Graphics",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Graphics* self = (const Graphics*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetResizable'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetResizable();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetResizable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetVSync of class  Graphics */
#ifndef TOLUA_DISABLE_tolua_Graphics_Graphics_GetVSync00
static int tolua_Graphics_Graphics_GetVSync00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Graphics",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Graphics* self = (const Graphics*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetVSync'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetVSync();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetVSync'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTripleBuffer of class  Graphics */
#ifndef TOLUA_DISABLE_tolua_Graphics_Graphics_GetTripleBuffer00
static int tolua_Graphics_Graphics_GetTripleBuffer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Graphics",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Graphics* self = (const Graphics*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTripleBuffer'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetTripleBuffer();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTripleBuffer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSRGB of class  Graphics */
#ifndef TOLUA_DISABLE_tolua_Graphics_Graphics_GetSRGB00
static int tolua_Graphics_Graphics_GetSRGB00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Graphics",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Graphics* self = (const Graphics*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSRGB'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetSRGB();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSRGB'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GetGraphics */
#ifndef TOLUA_DISABLE_tolua_Graphics_GetGraphics00
static int tolua_Graphics_GetGraphics00(lua_State* tolua_S)
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
   Graphics* tolua_ret = (Graphics*)  GetGraphics();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Graphics");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetGraphics'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: QUALITY_LOW */
#ifndef TOLUA_DISABLE_tolua_get_QUALITY_LOW
static int tolua_get_QUALITY_LOW(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)QUALITY_LOW);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: QUALITY_MEDIUM */
#ifndef TOLUA_DISABLE_tolua_get_QUALITY_MEDIUM
static int tolua_get_QUALITY_MEDIUM(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)QUALITY_MEDIUM);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: QUALITY_HIGH */
#ifndef TOLUA_DISABLE_tolua_get_QUALITY_HIGH
static int tolua_get_QUALITY_HIGH(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)QUALITY_HIGH);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: QUALITY_MAX */
#ifndef TOLUA_DISABLE_tolua_get_QUALITY_MAX
static int tolua_get_QUALITY_MAX(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)QUALITY_MAX);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: SHADOWQUALITY_LOW_16BIT */
#ifndef TOLUA_DISABLE_tolua_get_SHADOWQUALITY_LOW_16BIT
static int tolua_get_SHADOWQUALITY_LOW_16BIT(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)SHADOWQUALITY_LOW_16BIT);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: SHADOWQUALITY_LOW_24BIT */
#ifndef TOLUA_DISABLE_tolua_get_SHADOWQUALITY_LOW_24BIT
static int tolua_get_SHADOWQUALITY_LOW_24BIT(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)SHADOWQUALITY_LOW_24BIT);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: SHADOWQUALITY_HIGH_16BIT */
#ifndef TOLUA_DISABLE_tolua_get_SHADOWQUALITY_HIGH_16BIT
static int tolua_get_SHADOWQUALITY_HIGH_16BIT(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)SHADOWQUALITY_HIGH_16BIT);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: SHADOWQUALITY_HIGH_24BIT */
#ifndef TOLUA_DISABLE_tolua_get_SHADOWQUALITY_HIGH_24BIT
static int tolua_get_SHADOWQUALITY_HIGH_24BIT(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)SHADOWQUALITY_HIGH_24BIT);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: CLEAR_COLOR */
#ifndef TOLUA_DISABLE_tolua_get_CLEAR_COLOR
static int tolua_get_CLEAR_COLOR(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)CLEAR_COLOR);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: CLEAR_DEPTH */
#ifndef TOLUA_DISABLE_tolua_get_CLEAR_DEPTH
static int tolua_get_CLEAR_DEPTH(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)CLEAR_DEPTH);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: CLEAR_STENCIL */
#ifndef TOLUA_DISABLE_tolua_get_CLEAR_STENCIL
static int tolua_get_CLEAR_STENCIL(lua_State* tolua_S)
{
  tolua_pushnumber(tolua_S,(lua_Number)CLEAR_STENCIL);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetLightType of class  Light */
#ifndef TOLUA_DISABLE_tolua_Graphics_Light_SetLightType00
static int tolua_Graphics_Light_SetLightType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Light",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Light* self = (Light*)  tolua_tousertype(tolua_S,1,0);
  LightType type = ((LightType) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLightType'", NULL);
#endif
  {
   self->SetLightType(type);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLightType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetPerVertex of class  Light */
#ifndef TOLUA_DISABLE_tolua_Graphics_Light_SetPerVertex00
static int tolua_Graphics_Light_SetPerVertex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Light",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Light* self = (Light*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetPerVertex'", NULL);
#endif
  {
   self->SetPerVertex(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetPerVertex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetColor of class  Light */
#ifndef TOLUA_DISABLE_tolua_Graphics_Light_SetColor00
static int tolua_Graphics_Light_SetColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Light",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Color",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Light* self = (Light*)  tolua_tousertype(tolua_S,1,0);
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

/* method: SetSpecularIntensity of class  Light */
#ifndef TOLUA_DISABLE_tolua_Graphics_Light_SetSpecularIntensity00
static int tolua_Graphics_Light_SetSpecularIntensity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Light",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Light* self = (Light*)  tolua_tousertype(tolua_S,1,0);
  float intensity = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetSpecularIntensity'", NULL);
#endif
  {
   self->SetSpecularIntensity(intensity);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetSpecularIntensity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetRange of class  Light */
#ifndef TOLUA_DISABLE_tolua_Graphics_Light_SetRange00
static int tolua_Graphics_Light_SetRange00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Light",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Light* self = (Light*)  tolua_tousertype(tolua_S,1,0);
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

/* method: SetFov of class  Light */
#ifndef TOLUA_DISABLE_tolua_Graphics_Light_SetFov00
static int tolua_Graphics_Light_SetFov00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Light",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Light* self = (Light*)  tolua_tousertype(tolua_S,1,0);
  float fov = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFov'", NULL);
#endif
  {
   self->SetFov(fov);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFov'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetAspectRatio of class  Light */
#ifndef TOLUA_DISABLE_tolua_Graphics_Light_SetAspectRatio00
static int tolua_Graphics_Light_SetAspectRatio00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Light",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Light* self = (Light*)  tolua_tousertype(tolua_S,1,0);
  float aspectRatio = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetAspectRatio'", NULL);
#endif
  {
   self->SetAspectRatio(aspectRatio);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetAspectRatio'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFadeDistance of class  Light */
#ifndef TOLUA_DISABLE_tolua_Graphics_Light_SetFadeDistance00
static int tolua_Graphics_Light_SetFadeDistance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Light",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Light* self = (Light*)  tolua_tousertype(tolua_S,1,0);
  float distance = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFadeDistance'", NULL);
#endif
  {
   self->SetFadeDistance(distance);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFadeDistance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetShadowFadeDistance of class  Light */
#ifndef TOLUA_DISABLE_tolua_Graphics_Light_SetShadowFadeDistance00
static int tolua_Graphics_Light_SetShadowFadeDistance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Light",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Light* self = (Light*)  tolua_tousertype(tolua_S,1,0);
  float distance = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetShadowFadeDistance'", NULL);
#endif
  {
   self->SetShadowFadeDistance(distance);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetShadowFadeDistance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetShadowBias of class  Light */
#ifndef TOLUA_DISABLE_tolua_Graphics_Light_SetShadowBias00
static int tolua_Graphics_Light_SetShadowBias00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Light",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const BiasParameters",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Light* self = (Light*)  tolua_tousertype(tolua_S,1,0);
  const BiasParameters* parameters = ((const BiasParameters*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetShadowBias'", NULL);
#endif
  {
   self->SetShadowBias(*parameters);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetShadowBias'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetShadowCascade of class  Light */
#ifndef TOLUA_DISABLE_tolua_Graphics_Light_SetShadowCascade00
static int tolua_Graphics_Light_SetShadowCascade00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Light",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const CascadeParameters",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Light* self = (Light*)  tolua_tousertype(tolua_S,1,0);
  const CascadeParameters* parameters = ((const CascadeParameters*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetShadowCascade'", NULL);
#endif
  {
   self->SetShadowCascade(*parameters);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetShadowCascade'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetShadowFocus of class  Light */
#ifndef TOLUA_DISABLE_tolua_Graphics_Light_SetShadowFocus00
static int tolua_Graphics_Light_SetShadowFocus00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Light",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const FocusParameters",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Light* self = (Light*)  tolua_tousertype(tolua_S,1,0);
  const FocusParameters* parameters = ((const FocusParameters*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetShadowFocus'", NULL);
#endif
  {
   self->SetShadowFocus(*parameters);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetShadowFocus'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetShadowIntensity of class  Light */
#ifndef TOLUA_DISABLE_tolua_Graphics_Light_SetShadowIntensity00
static int tolua_Graphics_Light_SetShadowIntensity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Light",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Light* self = (Light*)  tolua_tousertype(tolua_S,1,0);
  float intensity = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetShadowIntensity'", NULL);
#endif
  {
   self->SetShadowIntensity(intensity);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetShadowIntensity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetShadowResolution of class  Light */
#ifndef TOLUA_DISABLE_tolua_Graphics_Light_SetShadowResolution00
static int tolua_Graphics_Light_SetShadowResolution00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Light",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Light* self = (Light*)  tolua_tousertype(tolua_S,1,0);
  float resolution = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetShadowResolution'", NULL);
#endif
  {
   self->SetShadowResolution(resolution);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetShadowResolution'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetShadowNearFarRatio of class  Light */
#ifndef TOLUA_DISABLE_tolua_Graphics_Light_SetShadowNearFarRatio00
static int tolua_Graphics_Light_SetShadowNearFarRatio00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Light",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Light* self = (Light*)  tolua_tousertype(tolua_S,1,0);
  float nearFarRatio = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetShadowNearFarRatio'", NULL);
#endif
  {
   self->SetShadowNearFarRatio(nearFarRatio);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetShadowNearFarRatio'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetRampTexture of class  Light */
#ifndef TOLUA_DISABLE_tolua_Graphics_Light_SetRampTexture00
static int tolua_Graphics_Light_SetRampTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Light",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Texture",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Light* self = (Light*)  tolua_tousertype(tolua_S,1,0);
  Texture* texture = ((Texture*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetRampTexture'", NULL);
#endif
  {
   self->SetRampTexture(texture);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetRampTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetShapeTexture of class  Light */
#ifndef TOLUA_DISABLE_tolua_Graphics_Light_SetShapeTexture00
static int tolua_Graphics_Light_SetShapeTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Light",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Texture",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Light* self = (Light*)  tolua_tousertype(tolua_S,1,0);
  Texture* texture = ((Texture*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetShapeTexture'", NULL);
#endif
  {
   self->SetShapeTexture(texture);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetShapeTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLightType of class  Light */
#ifndef TOLUA_DISABLE_tolua_Graphics_Light_GetLightType00
static int tolua_Graphics_Light_GetLightType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Light",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Light* self = (const Light*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLightType'", NULL);
#endif
  {
   LightType tolua_ret = (LightType)  self->GetLightType();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLightType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetPerVertex of class  Light */
#ifndef TOLUA_DISABLE_tolua_Graphics_Light_GetPerVertex00
static int tolua_Graphics_Light_GetPerVertex00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Light",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Light* self = (const Light*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPerVertex'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetPerVertex();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPerVertex'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetColor of class  Light */
#ifndef TOLUA_DISABLE_tolua_Graphics_Light_GetColor00
static int tolua_Graphics_Light_GetColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Light",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Light* self = (const Light*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetSpecularIntensity of class  Light */
#ifndef TOLUA_DISABLE_tolua_Graphics_Light_GetSpecularIntensity00
static int tolua_Graphics_Light_GetSpecularIntensity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Light",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Light* self = (const Light*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSpecularIntensity'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetSpecularIntensity();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSpecularIntensity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRange of class  Light */
#ifndef TOLUA_DISABLE_tolua_Graphics_Light_GetRange00
static int tolua_Graphics_Light_GetRange00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Light",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Light* self = (const Light*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetFov of class  Light */
#ifndef TOLUA_DISABLE_tolua_Graphics_Light_GetFov00
static int tolua_Graphics_Light_GetFov00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Light",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Light* self = (const Light*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFov'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetFov();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFov'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAspectRatio of class  Light */
#ifndef TOLUA_DISABLE_tolua_Graphics_Light_GetAspectRatio00
static int tolua_Graphics_Light_GetAspectRatio00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Light",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Light* self = (const Light*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAspectRatio'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetAspectRatio();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAspectRatio'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFadeDistance of class  Light */
#ifndef TOLUA_DISABLE_tolua_Graphics_Light_GetFadeDistance00
static int tolua_Graphics_Light_GetFadeDistance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Light",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Light* self = (const Light*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFadeDistance'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetFadeDistance();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFadeDistance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetShadowFadeDistance of class  Light */
#ifndef TOLUA_DISABLE_tolua_Graphics_Light_GetShadowFadeDistance00
static int tolua_Graphics_Light_GetShadowFadeDistance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Light",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Light* self = (const Light*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetShadowFadeDistance'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetShadowFadeDistance();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetShadowFadeDistance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetShadowBias of class  Light */
#ifndef TOLUA_DISABLE_tolua_Graphics_Light_GetShadowBias00
static int tolua_Graphics_Light_GetShadowBias00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Light",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Light* self = (const Light*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetShadowBias'", NULL);
#endif
  {
   const BiasParameters& tolua_ret = (const BiasParameters&)  self->GetShadowBias();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const BiasParameters");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetShadowBias'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetShadowCascade of class  Light */
#ifndef TOLUA_DISABLE_tolua_Graphics_Light_GetShadowCascade00
static int tolua_Graphics_Light_GetShadowCascade00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Light",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Light* self = (const Light*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetShadowCascade'", NULL);
#endif
  {
   const CascadeParameters& tolua_ret = (const CascadeParameters&)  self->GetShadowCascade();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const CascadeParameters");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetShadowCascade'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetShadowFocus of class  Light */
#ifndef TOLUA_DISABLE_tolua_Graphics_Light_GetShadowFocus00
static int tolua_Graphics_Light_GetShadowFocus00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Light",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Light* self = (const Light*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetShadowFocus'", NULL);
#endif
  {
   const FocusParameters& tolua_ret = (const FocusParameters&)  self->GetShadowFocus();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const FocusParameters");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetShadowFocus'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetShadowIntensity of class  Light */
#ifndef TOLUA_DISABLE_tolua_Graphics_Light_GetShadowIntensity00
static int tolua_Graphics_Light_GetShadowIntensity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Light",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Light* self = (const Light*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetShadowIntensity'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetShadowIntensity();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetShadowIntensity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetShadowResolution of class  Light */
#ifndef TOLUA_DISABLE_tolua_Graphics_Light_GetShadowResolution00
static int tolua_Graphics_Light_GetShadowResolution00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Light",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Light* self = (const Light*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetShadowResolution'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetShadowResolution();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetShadowResolution'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetShadowNearFarRatio of class  Light */
#ifndef TOLUA_DISABLE_tolua_Graphics_Light_GetShadowNearFarRatio00
static int tolua_Graphics_Light_GetShadowNearFarRatio00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Light",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Light* self = (const Light*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetShadowNearFarRatio'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetShadowNearFarRatio();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetShadowNearFarRatio'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRampTexture of class  Light */
#ifndef TOLUA_DISABLE_tolua_Graphics_Light_GetRampTexture00
static int tolua_Graphics_Light_GetRampTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Light",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Light* self = (const Light*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRampTexture'", NULL);
#endif
  {
   Texture* tolua_ret = (Texture*)  self->GetRampTexture();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Texture");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRampTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetShapeTexture of class  Light */
#ifndef TOLUA_DISABLE_tolua_Graphics_Light_GetShapeTexture00
static int tolua_Graphics_Light_GetShapeTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Light",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Light* self = (const Light*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetShapeTexture'", NULL);
#endif
  {
   Texture* tolua_ret = (Texture*)  self->GetShapeTexture();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Texture");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetShapeTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFrustum of class  Light */
#ifndef TOLUA_DISABLE_tolua_Graphics_Light_GetFrustum00
static int tolua_Graphics_Light_GetFrustum00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Light",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Light* self = (const Light*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFrustum'", NULL);
#endif
  {
   Frustum tolua_ret = (Frustum)  self->GetFrustum();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((Frustum)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"Frustum");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(Frustum));
     tolua_pushusertype(tolua_S,tolua_obj,"Frustum");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFrustum'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNumTechniques of class  Material */
#ifndef TOLUA_DISABLE_tolua_Graphics_Material_GetNumTechniques00
static int tolua_Graphics_Material_GetNumTechniques00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Material",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Material* self = (const Material*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNumTechniques'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetNumTechniques();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNumTechniques'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTechniqueEntry of class  Material */
#ifndef TOLUA_DISABLE_tolua_Graphics_Material_GetTechniqueEntry00
static int tolua_Graphics_Material_GetTechniqueEntry00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Material",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Material* self = (const Material*)  tolua_tousertype(tolua_S,1,0);
  unsigned index = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTechniqueEntry'", NULL);
#endif
  {
   const TechniqueEntry& tolua_ret = (const TechniqueEntry&)  self->GetTechniqueEntry(index);
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const TechniqueEntry");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTechniqueEntry'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTechnique of class  Material */
#ifndef TOLUA_DISABLE_tolua_Graphics_Material_GetTechnique00
static int tolua_Graphics_Material_GetTechnique00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Material",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Material* self = (const Material*)  tolua_tousertype(tolua_S,1,0);
  unsigned index = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTechnique'", NULL);
#endif
  {
   Technique* tolua_ret = (Technique*)  self->GetTechnique(index);
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

/* method: GetPass of class  Material */
#ifndef TOLUA_DISABLE_tolua_Graphics_Material_GetPass00
static int tolua_Graphics_Material_GetPass00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Material",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"StringHash",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Material* self = (const Material*)  tolua_tousertype(tolua_S,1,0);
  unsigned index = ((unsigned)  tolua_tonumber(tolua_S,2,0));
  StringHash passType = *((StringHash*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPass'", NULL);
#endif
  {
   Pass* tolua_ret = (Pass*)  self->GetPass(index,passType);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Pass");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPass'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTexture of class  Material */
#ifndef TOLUA_DISABLE_tolua_Graphics_Material_GetTexture00
static int tolua_Graphics_Material_GetTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Material",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Material* self = (const Material*)  tolua_tousertype(tolua_S,1,0);
  TextureUnit unit = ((TextureUnit) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTexture'", NULL);
#endif
  {
   Texture* tolua_ret = (Texture*)  self->GetTexture(unit);
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

/* method: GetShaderParameter of class  Material */
#ifndef TOLUA_DISABLE_tolua_Graphics_Material_GetShaderParameter00
static int tolua_Graphics_Material_GetShaderParameter00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Material",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Material* self = (const Material*)  tolua_tousertype(tolua_S,1,0);
  const String* name = ((const String*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetShaderParameter'", NULL);
#endif
  {
   const Vector4& tolua_ret = (const Vector4&)  self->GetShaderParameter(*name);
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Vector4");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetShaderParameter'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetCullMode of class  Material */
#ifndef TOLUA_DISABLE_tolua_Graphics_Material_GetCullMode00
static int tolua_Graphics_Material_GetCullMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Material",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Material* self = (const Material*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCullMode'", NULL);
#endif
  {
   CullMode tolua_ret = (CullMode)  self->GetCullMode();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCullMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetShadowCullMode of class  Material */
#ifndef TOLUA_DISABLE_tolua_Graphics_Material_GetShadowCullMode00
static int tolua_Graphics_Material_GetShadowCullMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Material",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Material* self = (const Material*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetShadowCullMode'", NULL);
#endif
  {
   CullMode tolua_ret = (CullMode)  self->GetShadowCullMode();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetShadowCullMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetDepthBias of class  Material */
#ifndef TOLUA_DISABLE_tolua_Graphics_Material_GetDepthBias00
static int tolua_Graphics_Material_GetDepthBias00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Material",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Material* self = (const Material*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetDepthBias'", NULL);
#endif
  {
   const BiasParameters& tolua_ret = (const BiasParameters&)  self->GetDepthBias();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const BiasParameters");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDepthBias'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAuxViewFrameNumber of class  Material */
#ifndef TOLUA_DISABLE_tolua_Graphics_Material_GetAuxViewFrameNumber00
static int tolua_Graphics_Material_GetAuxViewFrameNumber00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Material",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Material* self = (const Material*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAuxViewFrameNumber'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetAuxViewFrameNumber();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAuxViewFrameNumber'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetOcclusion of class  Material */
#ifndef TOLUA_DISABLE_tolua_Graphics_Material_GetOcclusion00
static int tolua_Graphics_Material_GetOcclusion00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Material",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Material* self = (const Material*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetOcclusion'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetOcclusion();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetOcclusion'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSpecular of class  Material */
#ifndef TOLUA_DISABLE_tolua_Graphics_Material_GetSpecular00
static int tolua_Graphics_Material_GetSpecular00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Material",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Material* self = (const Material*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSpecular'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetSpecular();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSpecular'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTextureUnitName of class  Material */
#ifndef TOLUA_DISABLE_tolua_Graphics_Material_GetTextureUnitName00
static int tolua_Graphics_Material_GetTextureUnitName00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Material",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TextureUnit unit = ((TextureUnit) (int)  tolua_tonumber(tolua_S,2,0));
  {
   String tolua_ret = (String)  Material::GetTextureUnitName(unit);
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
 tolua_error(tolua_S,"#ferror in function 'GetTextureUnitName'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetBoundingBox of class  Model */
#ifndef TOLUA_DISABLE_tolua_Graphics_Model_GetBoundingBox00
static int tolua_Graphics_Model_GetBoundingBox00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Model",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Model* self = (const Model*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetBoundingBox'", NULL);
#endif
  {
   const BoundingBox& tolua_ret = (const BoundingBox&)  self->GetBoundingBox();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const BoundingBox");
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

/* method: GetSkeleton of class  Model */
#ifndef TOLUA_DISABLE_tolua_Graphics_Model_GetSkeleton00
static int tolua_Graphics_Model_GetSkeleton00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Model",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Model* self = (Model*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSkeleton'", NULL);
#endif
  {
   Skeleton& tolua_ret = (Skeleton&)  self->GetSkeleton();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"Skeleton");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSkeleton'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNumGeometries of class  Model */
#ifndef TOLUA_DISABLE_tolua_Graphics_Model_GetNumGeometries00
static int tolua_Graphics_Model_GetNumGeometries00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Model",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Model* self = (const Model*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNumGeometries'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetNumGeometries();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNumGeometries'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNumGeometryLodLevels of class  Model */
#ifndef TOLUA_DISABLE_tolua_Graphics_Model_GetNumGeometryLodLevels00
static int tolua_Graphics_Model_GetNumGeometryLodLevels00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Model",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Model* self = (const Model*)  tolua_tousertype(tolua_S,1,0);
  unsigned index = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNumGeometryLodLevels'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetNumGeometryLodLevels(index);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNumGeometryLodLevels'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetGeometry of class  Model */
#ifndef TOLUA_DISABLE_tolua_Graphics_Model_GetGeometry00
static int tolua_Graphics_Model_GetGeometry00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Model",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Model* self = (const Model*)  tolua_tousertype(tolua_S,1,0);
  unsigned index = ((unsigned)  tolua_tonumber(tolua_S,2,0));
  unsigned lodLevel = ((unsigned)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetGeometry'", NULL);
#endif
  {
   Geometry* tolua_ret = (Geometry*)  self->GetGeometry(index,lodLevel);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Geometry");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetGeometry'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNumMorphs of class  Model */
#ifndef TOLUA_DISABLE_tolua_Graphics_Model_GetNumMorphs00
static int tolua_Graphics_Model_GetNumMorphs00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Model",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Model* self = (const Model*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNumMorphs'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetNumMorphs();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNumMorphs'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMorph of class  Model */
#ifndef TOLUA_DISABLE_tolua_Graphics_Model_GetMorph00
static int tolua_Graphics_Model_GetMorph00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Model",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Model* self = (const Model*)  tolua_tousertype(tolua_S,1,0);
  unsigned index = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMorph'", NULL);
#endif
  {
   const ModelMorph* tolua_ret = (const ModelMorph*)  self->GetMorph(index);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"const ModelMorph");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMorph'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMorph of class  Model */
#ifndef TOLUA_DISABLE_tolua_Graphics_Model_GetMorph01
static int tolua_Graphics_Model_GetMorph01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Model",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const Model* self = (const Model*)  tolua_tousertype(tolua_S,1,0);
  const String* name = ((const String*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMorph'", NULL);
#endif
  {
   const ModelMorph* tolua_ret = (const ModelMorph*)  self->GetMorph(*name);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"const ModelMorph");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Graphics_Model_GetMorph00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMorph of class  Model */
#ifndef TOLUA_DISABLE_tolua_Graphics_Model_GetMorph02
static int tolua_Graphics_Model_GetMorph02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Model",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"StringHash",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const Model* self = (const Model*)  tolua_tousertype(tolua_S,1,0);
  StringHash nameHash = *((StringHash*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMorph'", NULL);
#endif
  {
   const ModelMorph* tolua_ret = (const ModelMorph*)  self->GetMorph(nameHash);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"const ModelMorph");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Graphics_Model_GetMorph01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMorphRangeStart of class  Model */
#ifndef TOLUA_DISABLE_tolua_Graphics_Model_GetMorphRangeStart00
static int tolua_Graphics_Model_GetMorphRangeStart00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Model",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Model* self = (const Model*)  tolua_tousertype(tolua_S,1,0);
  unsigned bufferIndex = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMorphRangeStart'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetMorphRangeStart(bufferIndex);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMorphRangeStart'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMorphRangeCount of class  Model */
#ifndef TOLUA_DISABLE_tolua_Graphics_Model_GetMorphRangeCount00
static int tolua_Graphics_Model_GetMorphRangeCount00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Model",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Model* self = (const Model*)  tolua_tousertype(tolua_S,1,0);
  unsigned bufferIndex = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMorphRangeCount'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetMorphRangeCount(bufferIndex);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMorphRangeCount'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Resize of class  Octree */
#ifndef TOLUA_DISABLE_tolua_Graphics_Octree_Resize00
static int tolua_Graphics_Octree_Resize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Octree",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const BoundingBox",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Octree* self = (Octree*)  tolua_tousertype(tolua_S,1,0);
  const BoundingBox* box = ((const BoundingBox*)  tolua_tousertype(tolua_S,2,0));
  unsigned numLevels = ((unsigned)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Resize'", NULL);
#endif
  {
   self->Resize(*box,numLevels);
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

/* method: Update of class  Octree */
#ifndef TOLUA_DISABLE_tolua_Graphics_Octree_Update00
static int tolua_Graphics_Octree_Update00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Octree",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const FrameInfo",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Octree* self = (Octree*)  tolua_tousertype(tolua_S,1,0);
  const FrameInfo* frame = ((const FrameInfo*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Update'", NULL);
#endif
  {
   self->Update(*frame);
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

/* method: AddManualDrawable of class  Octree */
#ifndef TOLUA_DISABLE_tolua_Graphics_Octree_AddManualDrawable00
static int tolua_Graphics_Octree_AddManualDrawable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Octree",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Drawable",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Octree* self = (Octree*)  tolua_tousertype(tolua_S,1,0);
  Drawable* drawable = ((Drawable*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddManualDrawable'", NULL);
#endif
  {
   self->AddManualDrawable(drawable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddManualDrawable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RemoveManualDrawable of class  Octree */
#ifndef TOLUA_DISABLE_tolua_Graphics_Octree_RemoveManualDrawable00
static int tolua_Graphics_Octree_RemoveManualDrawable00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Octree",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Drawable",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Octree* self = (Octree*)  tolua_tousertype(tolua_S,1,0);
  Drawable* drawable = ((Drawable*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RemoveManualDrawable'", NULL);
#endif
  {
   self->RemoveManualDrawable(drawable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RemoveManualDrawable'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetDrawables of class  Octree */
#ifndef TOLUA_DISABLE_tolua_Graphics_Octree_GetDrawables00
static int tolua_Graphics_Octree_GetDrawables00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Octree",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"OctreeQuery",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Octree* self = (const Octree*)  tolua_tousertype(tolua_S,1,0);
  OctreeQuery* query = ((OctreeQuery*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetDrawables'", NULL);
#endif
  {
   self->GetDrawables(*query);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDrawables'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Raycast of class  Octree */
#ifndef TOLUA_DISABLE_tolua_Graphics_Octree_Raycast00
static int tolua_Graphics_Octree_Raycast00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Octree",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"RayOctreeQuery",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Octree* self = (const Octree*)  tolua_tousertype(tolua_S,1,0);
  RayOctreeQuery* query = ((RayOctreeQuery*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Raycast'", NULL);
#endif
  {
   self->Raycast(*query);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Raycast'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: RaycastSingle of class  Octree */
#ifndef TOLUA_DISABLE_tolua_Graphics_Octree_RaycastSingle00
static int tolua_Graphics_Octree_RaycastSingle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Octree",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"RayOctreeQuery",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Octree* self = (const Octree*)  tolua_tousertype(tolua_S,1,0);
  RayOctreeQuery* query = ((RayOctreeQuery*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'RaycastSingle'", NULL);
#endif
  {
   self->RaycastSingle(*query);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'RaycastSingle'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNumLevels of class  Octree */
#ifndef TOLUA_DISABLE_tolua_Graphics_Octree_GetNumLevels00
static int tolua_Graphics_Octree_GetNumLevels00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Octree",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Octree* self = (const Octree*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNumLevels'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetNumLevels();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNumLevels'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: QueueUpdate of class  Octree */
#ifndef TOLUA_DISABLE_tolua_Graphics_Octree_QueueUpdate00
static int tolua_Graphics_Octree_QueueUpdate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Octree",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Drawable",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Octree* self = (Octree*)  tolua_tousertype(tolua_S,1,0);
  Drawable* drawable = ((Drawable*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'QueueUpdate'", NULL);
#endif
  {
   self->QueueUpdate(drawable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'QueueUpdate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: QueueReinsertion of class  Octree */
#ifndef TOLUA_DISABLE_tolua_Graphics_Octree_QueueReinsertion00
static int tolua_Graphics_Octree_QueueReinsertion00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Octree",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Drawable",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Octree* self = (Octree*)  tolua_tousertype(tolua_S,1,0);
  Drawable* drawable = ((Drawable*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'QueueReinsertion'", NULL);
#endif
  {
   self->QueueReinsertion(drawable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'QueueReinsertion'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: DrawDebugGeometry of class  Octree */
#ifndef TOLUA_DISABLE_tolua_Graphics_Octree_DrawDebugGeometry00
static int tolua_Graphics_Octree_DrawDebugGeometry00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Octree",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Octree* self = (Octree*)  tolua_tousertype(tolua_S,1,0);
  bool depthTest = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'DrawDebugGeometry'", NULL);
#endif
  {
   self->DrawDebugGeometry(depthTest);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'DrawDebugGeometry'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GetOctree */
#ifndef TOLUA_DISABLE_tolua_Graphics_GetOctree00
static int tolua_Graphics_GetOctree00(lua_State* tolua_S)
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
   Octree* tolua_ret = (Octree*)  GetOctree();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Octree");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetOctree'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  ColorFrame */
#ifndef TOLUA_DISABLE_tolua_Graphics_ColorFrame_new00
static int tolua_Graphics_ColorFrame_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ColorFrame",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ColorFrame* tolua_ret = (ColorFrame*)  Mtolua_new((ColorFrame)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ColorFrame");
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

/* method: new_local of class  ColorFrame */
#ifndef TOLUA_DISABLE_tolua_Graphics_ColorFrame_new00_local
static int tolua_Graphics_ColorFrame_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ColorFrame",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   ColorFrame* tolua_ret = (ColorFrame*)  Mtolua_new((ColorFrame)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ColorFrame");
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

/* method: new of class  ColorFrame */
#ifndef TOLUA_DISABLE_tolua_Graphics_ColorFrame_new01
static int tolua_Graphics_ColorFrame_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ColorFrame",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Color",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const Color* color = ((const Color*)  tolua_tousertype(tolua_S,2,0));
  {
   ColorFrame* tolua_ret = (ColorFrame*)  Mtolua_new((ColorFrame)(*color));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ColorFrame");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Graphics_ColorFrame_new00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  ColorFrame */
#ifndef TOLUA_DISABLE_tolua_Graphics_ColorFrame_new01_local
static int tolua_Graphics_ColorFrame_new01_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ColorFrame",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Color",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const Color* color = ((const Color*)  tolua_tousertype(tolua_S,2,0));
  {
   ColorFrame* tolua_ret = (ColorFrame*)  Mtolua_new((ColorFrame)(*color));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ColorFrame");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_Graphics_ColorFrame_new00_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  ColorFrame */
#ifndef TOLUA_DISABLE_tolua_Graphics_ColorFrame_new02
static int tolua_Graphics_ColorFrame_new02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ColorFrame",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Color",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const Color* color = ((const Color*)  tolua_tousertype(tolua_S,2,0));
  float time = ((float)  tolua_tonumber(tolua_S,3,0));
  {
   ColorFrame* tolua_ret = (ColorFrame*)  Mtolua_new((ColorFrame)(*color,time));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ColorFrame");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Graphics_ColorFrame_new01(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: new_local of class  ColorFrame */
#ifndef TOLUA_DISABLE_tolua_Graphics_ColorFrame_new02_local
static int tolua_Graphics_ColorFrame_new02_local(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"ColorFrame",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Color",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const Color* color = ((const Color*)  tolua_tousertype(tolua_S,2,0));
  float time = ((float)  tolua_tonumber(tolua_S,3,0));
  {
   ColorFrame* tolua_ret = (ColorFrame*)  Mtolua_new((ColorFrame)(*color,time));
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ColorFrame");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
  }
 }
 return 1;
tolua_lerror:
 return tolua_Graphics_ColorFrame_new01_local(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: Interpolate of class  ColorFrame */
#ifndef TOLUA_DISABLE_tolua_Graphics_ColorFrame_Interpolate00
static int tolua_Graphics_ColorFrame_Interpolate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ColorFrame",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const ColorFrame",0,&tolua_err)) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ColorFrame* self = (ColorFrame*)  tolua_tousertype(tolua_S,1,0);
  const ColorFrame* next = ((const ColorFrame*)  tolua_tousertype(tolua_S,2,0));
  float time = ((float)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Interpolate'", NULL);
#endif
  {
   Color tolua_ret = (Color)  self->Interpolate(*next,time);
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
 tolua_error(tolua_S,"#ferror in function 'Interpolate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: color_ of class  ColorFrame */
#ifndef TOLUA_DISABLE_tolua_get_ColorFrame_color
static int tolua_get_ColorFrame_color(lua_State* tolua_S)
{
  ColorFrame* self = (ColorFrame*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'color_'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->color_,"Color");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: color_ of class  ColorFrame */
#ifndef TOLUA_DISABLE_tolua_set_ColorFrame_color
static int tolua_set_ColorFrame_color(lua_State* tolua_S)
{
  ColorFrame* self = (ColorFrame*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'color_'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"Color",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->color_ = *((Color*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: time_ of class  ColorFrame */
#ifndef TOLUA_DISABLE_tolua_get_ColorFrame_time
static int tolua_get_ColorFrame_time(lua_State* tolua_S)
{
  ColorFrame* self = (ColorFrame*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'time_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->time_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: time_ of class  ColorFrame */
#ifndef TOLUA_DISABLE_tolua_set_ColorFrame_time
static int tolua_set_ColorFrame_time(lua_State* tolua_S)
{
  ColorFrame* self = (ColorFrame*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'time_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->time_ = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  TextureFrame */
#ifndef TOLUA_DISABLE_tolua_Graphics_TextureFrame_new00
static int tolua_Graphics_TextureFrame_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"TextureFrame",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   TextureFrame* tolua_ret = (TextureFrame*)  Mtolua_new((TextureFrame)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"TextureFrame");
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

/* method: new_local of class  TextureFrame */
#ifndef TOLUA_DISABLE_tolua_Graphics_TextureFrame_new00_local
static int tolua_Graphics_TextureFrame_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"TextureFrame",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   TextureFrame* tolua_ret = (TextureFrame*)  Mtolua_new((TextureFrame)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"TextureFrame");
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

/* get function: uv_ of class  TextureFrame */
#ifndef TOLUA_DISABLE_tolua_get_TextureFrame_uv
static int tolua_get_TextureFrame_uv(lua_State* tolua_S)
{
  TextureFrame* self = (TextureFrame*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'uv_'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->uv_,"Rect");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: uv_ of class  TextureFrame */
#ifndef TOLUA_DISABLE_tolua_set_TextureFrame_uv
static int tolua_set_TextureFrame_uv(lua_State* tolua_S)
{
  TextureFrame* self = (TextureFrame*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'uv_'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"Rect",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->uv_ = *((Rect*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: time_ of class  TextureFrame */
#ifndef TOLUA_DISABLE_tolua_get_TextureFrame_time
static int tolua_get_TextureFrame_time(lua_State* tolua_S)
{
  TextureFrame* self = (TextureFrame*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'time_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->time_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: time_ of class  TextureFrame */
#ifndef TOLUA_DISABLE_tolua_set_TextureFrame_time
static int tolua_set_TextureFrame_time(lua_State* tolua_S)
{
  TextureFrame* self = (TextureFrame*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'time_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->time_ = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: Load of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_Load00
static int tolua_Graphics_ParticleEmitter_Load00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ParticleEmitter",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"XMLFile",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ParticleEmitter* self = (ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
  XMLFile* file = ((XMLFile*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Load'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->Load(file);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Load'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetNumParticles of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_SetNumParticles00
static int tolua_Graphics_ParticleEmitter_SetNumParticles00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ParticleEmitter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ParticleEmitter* self = (ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
  unsigned num = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetNumParticles'", NULL);
#endif
  {
   self->SetNumParticles(num);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetNumParticles'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetEmissionRate of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_SetEmissionRate00
static int tolua_Graphics_ParticleEmitter_SetEmissionRate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ParticleEmitter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ParticleEmitter* self = (ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
  float rate = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetEmissionRate'", NULL);
#endif
  {
   self->SetEmissionRate(rate);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetEmissionRate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMinEmissionRate of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_SetMinEmissionRate00
static int tolua_Graphics_ParticleEmitter_SetMinEmissionRate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ParticleEmitter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ParticleEmitter* self = (ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
  float rate = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMinEmissionRate'", NULL);
#endif
  {
   self->SetMinEmissionRate(rate);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMinEmissionRate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMaxEmissionRate of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_SetMaxEmissionRate00
static int tolua_Graphics_ParticleEmitter_SetMaxEmissionRate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ParticleEmitter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ParticleEmitter* self = (ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
  float rate = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMaxEmissionRate'", NULL);
#endif
  {
   self->SetMaxEmissionRate(rate);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMaxEmissionRate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetEmitterType of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_SetEmitterType00
static int tolua_Graphics_ParticleEmitter_SetEmitterType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ParticleEmitter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ParticleEmitter* self = (ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
  EmitterType type = ((EmitterType) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetEmitterType'", NULL);
#endif
  {
   self->SetEmitterType(type);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetEmitterType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetEmitterSize of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_SetEmitterSize00
static int tolua_Graphics_ParticleEmitter_SetEmitterSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ParticleEmitter",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ParticleEmitter* self = (ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* size = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetEmitterSize'", NULL);
#endif
  {
   self->SetEmitterSize(*size);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetEmitterSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetActiveTime of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_SetActiveTime00
static int tolua_Graphics_ParticleEmitter_SetActiveTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ParticleEmitter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ParticleEmitter* self = (ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
  float time = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetActiveTime'", NULL);
#endif
  {
   self->SetActiveTime(time);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetActiveTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetInactiveTime of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_SetInactiveTime00
static int tolua_Graphics_ParticleEmitter_SetInactiveTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ParticleEmitter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ParticleEmitter* self = (ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
  float time = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetInactiveTime'", NULL);
#endif
  {
   self->SetInactiveTime(time);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetInactiveTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetEmitting of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_SetEmitting00
static int tolua_Graphics_ParticleEmitter_SetEmitting00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ParticleEmitter",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ParticleEmitter* self = (ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
  bool resetPeriod = ((bool)  tolua_toboolean(tolua_S,3,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetEmitting'", NULL);
#endif
  {
   self->SetEmitting(enable,resetPeriod);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetEmitting'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetUpdateInvisible of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_SetUpdateInvisible00
static int tolua_Graphics_ParticleEmitter_SetUpdateInvisible00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ParticleEmitter",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ParticleEmitter* self = (ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetUpdateInvisible'", NULL);
#endif
  {
   self->SetUpdateInvisible(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetUpdateInvisible'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetTimeToLive of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_SetTimeToLive00
static int tolua_Graphics_ParticleEmitter_SetTimeToLive00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ParticleEmitter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ParticleEmitter* self = (ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
  float time = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetTimeToLive'", NULL);
#endif
  {
   self->SetTimeToLive(time);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetTimeToLive'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMinTimeToLive of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_SetMinTimeToLive00
static int tolua_Graphics_ParticleEmitter_SetMinTimeToLive00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ParticleEmitter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ParticleEmitter* self = (ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
  float time = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMinTimeToLive'", NULL);
#endif
  {
   self->SetMinTimeToLive(time);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMinTimeToLive'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMaxTimeToLive of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_SetMaxTimeToLive00
static int tolua_Graphics_ParticleEmitter_SetMaxTimeToLive00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ParticleEmitter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ParticleEmitter* self = (ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
  float time = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMaxTimeToLive'", NULL);
#endif
  {
   self->SetMaxTimeToLive(time);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMaxTimeToLive'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetParticleSize of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_SetParticleSize00
static int tolua_Graphics_ParticleEmitter_SetParticleSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ParticleEmitter",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ParticleEmitter* self = (ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
  const Vector2* size = ((const Vector2*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetParticleSize'", NULL);
#endif
  {
   self->SetParticleSize(*size);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetParticleSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMinParticleSize of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_SetMinParticleSize00
static int tolua_Graphics_ParticleEmitter_SetMinParticleSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ParticleEmitter",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ParticleEmitter* self = (ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
  const Vector2* size = ((const Vector2*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMinParticleSize'", NULL);
#endif
  {
   self->SetMinParticleSize(*size);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMinParticleSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMaxParticleSize of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_SetMaxParticleSize00
static int tolua_Graphics_ParticleEmitter_SetMaxParticleSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ParticleEmitter",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ParticleEmitter* self = (ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
  const Vector2* size = ((const Vector2*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMaxParticleSize'", NULL);
#endif
  {
   self->SetMaxParticleSize(*size);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMaxParticleSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMinDirection of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_SetMinDirection00
static int tolua_Graphics_ParticleEmitter_SetMinDirection00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ParticleEmitter",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ParticleEmitter* self = (ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* direction = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMinDirection'", NULL);
#endif
  {
   self->SetMinDirection(*direction);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMinDirection'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMaxDirection of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_SetMaxDirection00
static int tolua_Graphics_ParticleEmitter_SetMaxDirection00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ParticleEmitter",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ParticleEmitter* self = (ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* direction = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMaxDirection'", NULL);
#endif
  {
   self->SetMaxDirection(*direction);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMaxDirection'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetVelocity of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_SetVelocity00
static int tolua_Graphics_ParticleEmitter_SetVelocity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ParticleEmitter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ParticleEmitter* self = (ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
  float velocity = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetVelocity'", NULL);
#endif
  {
   self->SetVelocity(velocity);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetVelocity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMinVelocity of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_SetMinVelocity00
static int tolua_Graphics_ParticleEmitter_SetMinVelocity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ParticleEmitter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ParticleEmitter* self = (ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
  float velocity = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMinVelocity'", NULL);
#endif
  {
   self->SetMinVelocity(velocity);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMinVelocity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMaxVelocity of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_SetMaxVelocity00
static int tolua_Graphics_ParticleEmitter_SetMaxVelocity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ParticleEmitter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ParticleEmitter* self = (ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
  float velocity = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMaxVelocity'", NULL);
#endif
  {
   self->SetMaxVelocity(velocity);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMaxVelocity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetRotation of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_SetRotation00
static int tolua_Graphics_ParticleEmitter_SetRotation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ParticleEmitter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ParticleEmitter* self = (ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
  float rotation = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetRotation'", NULL);
#endif
  {
   self->SetRotation(rotation);
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

/* method: SetMinRotation of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_SetMinRotation00
static int tolua_Graphics_ParticleEmitter_SetMinRotation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ParticleEmitter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ParticleEmitter* self = (ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
  float rotation = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMinRotation'", NULL);
#endif
  {
   self->SetMinRotation(rotation);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMinRotation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMaxRotation of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_SetMaxRotation00
static int tolua_Graphics_ParticleEmitter_SetMaxRotation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ParticleEmitter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ParticleEmitter* self = (ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
  float rotation = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMaxRotation'", NULL);
#endif
  {
   self->SetMaxRotation(rotation);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMaxRotation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetRotationSpeed of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_SetRotationSpeed00
static int tolua_Graphics_ParticleEmitter_SetRotationSpeed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ParticleEmitter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ParticleEmitter* self = (ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
  float speed = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetRotationSpeed'", NULL);
#endif
  {
   self->SetRotationSpeed(speed);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetRotationSpeed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMinRotationSpeed of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_SetMinRotationSpeed00
static int tolua_Graphics_ParticleEmitter_SetMinRotationSpeed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ParticleEmitter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ParticleEmitter* self = (ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
  float speed = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMinRotationSpeed'", NULL);
#endif
  {
   self->SetMinRotationSpeed(speed);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMinRotationSpeed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMaxRotationSpeed of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_SetMaxRotationSpeed00
static int tolua_Graphics_ParticleEmitter_SetMaxRotationSpeed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ParticleEmitter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ParticleEmitter* self = (ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
  float speed = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMaxRotationSpeed'", NULL);
#endif
  {
   self->SetMaxRotationSpeed(speed);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMaxRotationSpeed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetConstantForce of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_SetConstantForce00
static int tolua_Graphics_ParticleEmitter_SetConstantForce00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ParticleEmitter",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ParticleEmitter* self = (ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* force = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetConstantForce'", NULL);
#endif
  {
   self->SetConstantForce(*force);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetConstantForce'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetDampingForce of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_SetDampingForce00
static int tolua_Graphics_ParticleEmitter_SetDampingForce00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ParticleEmitter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ParticleEmitter* self = (ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
  float force = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetDampingForce'", NULL);
#endif
  {
   self->SetDampingForce(force);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetDampingForce'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetSizeAdd of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_SetSizeAdd00
static int tolua_Graphics_ParticleEmitter_SetSizeAdd00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ParticleEmitter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ParticleEmitter* self = (ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
  float sizeAdd = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetSizeAdd'", NULL);
#endif
  {
   self->SetSizeAdd(sizeAdd);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetSizeAdd'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetSizeMul of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_SetSizeMul00
static int tolua_Graphics_ParticleEmitter_SetSizeMul00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ParticleEmitter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ParticleEmitter* self = (ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
  float sizeMul = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetSizeMul'", NULL);
#endif
  {
   self->SetSizeMul(sizeMul);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetSizeMul'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetColor of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_SetColor00
static int tolua_Graphics_ParticleEmitter_SetColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ParticleEmitter",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Color",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ParticleEmitter* self = (ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
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

/* method: SetNumColors of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_SetNumColors00
static int tolua_Graphics_ParticleEmitter_SetNumColors00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ParticleEmitter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ParticleEmitter* self = (ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
  unsigned num = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetNumColors'", NULL);
#endif
  {
   self->SetNumColors(num);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetNumColors'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetNumTextureFrames of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_SetNumTextureFrames00
static int tolua_Graphics_ParticleEmitter_SetNumTextureFrames00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ParticleEmitter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ParticleEmitter* self = (ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
  unsigned num = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetNumTextureFrames'", NULL);
#endif
  {
   self->SetNumTextureFrames(num);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetNumTextureFrames'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNumParticles of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_GetNumParticles00
static int tolua_Graphics_ParticleEmitter_GetNumParticles00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ParticleEmitter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ParticleEmitter* self = (const ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNumParticles'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetNumParticles();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNumParticles'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsEmitting of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_IsEmitting00
static int tolua_Graphics_ParticleEmitter_IsEmitting00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ParticleEmitter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ParticleEmitter* self = (const ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsEmitting'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsEmitting();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsEmitting'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetUpdateInvisible of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_GetUpdateInvisible00
static int tolua_Graphics_ParticleEmitter_GetUpdateInvisible00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ParticleEmitter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ParticleEmitter* self = (const ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetUpdateInvisible'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetUpdateInvisible();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetUpdateInvisible'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMinEmissionRate of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_GetMinEmissionRate00
static int tolua_Graphics_ParticleEmitter_GetMinEmissionRate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ParticleEmitter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ParticleEmitter* self = (const ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMinEmissionRate'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetMinEmissionRate();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMinEmissionRate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMaxEmissionRate of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_GetMaxEmissionRate00
static int tolua_Graphics_ParticleEmitter_GetMaxEmissionRate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ParticleEmitter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ParticleEmitter* self = (const ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMaxEmissionRate'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetMaxEmissionRate();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMaxEmissionRate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetEmitterType of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_GetEmitterType00
static int tolua_Graphics_ParticleEmitter_GetEmitterType00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ParticleEmitter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ParticleEmitter* self = (const ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetEmitterType'", NULL);
#endif
  {
   EmitterType tolua_ret = (EmitterType)  self->GetEmitterType();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetEmitterType'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetEmitterSize of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_GetEmitterSize00
static int tolua_Graphics_ParticleEmitter_GetEmitterSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ParticleEmitter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ParticleEmitter* self = (const ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetEmitterSize'", NULL);
#endif
  {
   const Vector3& tolua_ret = (const Vector3&)  self->GetEmitterSize();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Vector3");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetEmitterSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetActiveTime of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_GetActiveTime00
static int tolua_Graphics_ParticleEmitter_GetActiveTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ParticleEmitter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ParticleEmitter* self = (const ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetActiveTime'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetActiveTime();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetActiveTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetInactiveTime of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_GetInactiveTime00
static int tolua_Graphics_ParticleEmitter_GetInactiveTime00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ParticleEmitter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ParticleEmitter* self = (const ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetInactiveTime'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetInactiveTime();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetInactiveTime'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMinTimeToLive of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_GetMinTimeToLive00
static int tolua_Graphics_ParticleEmitter_GetMinTimeToLive00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ParticleEmitter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ParticleEmitter* self = (const ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMinTimeToLive'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetMinTimeToLive();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMinTimeToLive'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMaxTimeToLive of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_GetMaxTimeToLive00
static int tolua_Graphics_ParticleEmitter_GetMaxTimeToLive00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ParticleEmitter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ParticleEmitter* self = (const ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMaxTimeToLive'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetMaxTimeToLive();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMaxTimeToLive'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMinParticleSize of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_GetMinParticleSize00
static int tolua_Graphics_ParticleEmitter_GetMinParticleSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ParticleEmitter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ParticleEmitter* self = (const ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMinParticleSize'", NULL);
#endif
  {
   const Vector2& tolua_ret = (const Vector2&)  self->GetMinParticleSize();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Vector2");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMinParticleSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMaxParticleSize of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_GetMaxParticleSize00
static int tolua_Graphics_ParticleEmitter_GetMaxParticleSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ParticleEmitter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ParticleEmitter* self = (const ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMaxParticleSize'", NULL);
#endif
  {
   const Vector2& tolua_ret = (const Vector2&)  self->GetMaxParticleSize();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Vector2");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMaxParticleSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMinDirection of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_GetMinDirection00
static int tolua_Graphics_ParticleEmitter_GetMinDirection00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ParticleEmitter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ParticleEmitter* self = (const ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMinDirection'", NULL);
#endif
  {
   const Vector3& tolua_ret = (const Vector3&)  self->GetMinDirection();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Vector3");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMinDirection'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMaxDirection of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_GetMaxDirection00
static int tolua_Graphics_ParticleEmitter_GetMaxDirection00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ParticleEmitter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ParticleEmitter* self = (const ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMaxDirection'", NULL);
#endif
  {
   const Vector3& tolua_ret = (const Vector3&)  self->GetMaxDirection();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Vector3");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMaxDirection'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMinVelocity of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_GetMinVelocity00
static int tolua_Graphics_ParticleEmitter_GetMinVelocity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ParticleEmitter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ParticleEmitter* self = (const ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMinVelocity'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetMinVelocity();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMinVelocity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMaxVelocity of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_GetMaxVelocity00
static int tolua_Graphics_ParticleEmitter_GetMaxVelocity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ParticleEmitter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ParticleEmitter* self = (const ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMaxVelocity'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetMaxVelocity();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMaxVelocity'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMinRotation of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_GetMinRotation00
static int tolua_Graphics_ParticleEmitter_GetMinRotation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ParticleEmitter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ParticleEmitter* self = (const ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMinRotation'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetMinRotation();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMinRotation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMaxRotation of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_GetMaxRotation00
static int tolua_Graphics_ParticleEmitter_GetMaxRotation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ParticleEmitter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ParticleEmitter* self = (const ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMaxRotation'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetMaxRotation();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMaxRotation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMinRotationSpeed of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_GetMinRotationSpeed00
static int tolua_Graphics_ParticleEmitter_GetMinRotationSpeed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ParticleEmitter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ParticleEmitter* self = (const ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMinRotationSpeed'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetMinRotationSpeed();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMinRotationSpeed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMaxRotationSpeed of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_GetMaxRotationSpeed00
static int tolua_Graphics_ParticleEmitter_GetMaxRotationSpeed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ParticleEmitter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ParticleEmitter* self = (const ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMaxRotationSpeed'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetMaxRotationSpeed();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMaxRotationSpeed'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetConstantForce of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_GetConstantForce00
static int tolua_Graphics_ParticleEmitter_GetConstantForce00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ParticleEmitter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ParticleEmitter* self = (const ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetConstantForce'", NULL);
#endif
  {
   const Vector3& tolua_ret = (const Vector3&)  self->GetConstantForce();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Vector3");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetConstantForce'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetDampingForce of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_GetDampingForce00
static int tolua_Graphics_ParticleEmitter_GetDampingForce00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ParticleEmitter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ParticleEmitter* self = (const ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetDampingForce'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetDampingForce();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDampingForce'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSizeAdd of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_GetSizeAdd00
static int tolua_Graphics_ParticleEmitter_GetSizeAdd00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ParticleEmitter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ParticleEmitter* self = (const ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSizeAdd'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetSizeAdd();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSizeAdd'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSizeMul of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_GetSizeMul00
static int tolua_Graphics_ParticleEmitter_GetSizeMul00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ParticleEmitter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ParticleEmitter* self = (const ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSizeMul'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetSizeMul();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSizeMul'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNumColors of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_GetNumColors00
static int tolua_Graphics_ParticleEmitter_GetNumColors00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ParticleEmitter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ParticleEmitter* self = (const ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNumColors'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetNumColors();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNumColors'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetColor of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_GetColor00
static int tolua_Graphics_ParticleEmitter_GetColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ParticleEmitter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ParticleEmitter* self = (ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
  unsigned index = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetColor'", NULL);
#endif
  {
   ColorFrame* tolua_ret = (ColorFrame*)  self->GetColor(index);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ColorFrame");
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

/* method: GetNumTextureFrames of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_GetNumTextureFrames00
static int tolua_Graphics_ParticleEmitter_GetNumTextureFrames00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const ParticleEmitter",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const ParticleEmitter* self = (const ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNumTextureFrames'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetNumTextureFrames();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNumTextureFrames'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTextureFrame of class  ParticleEmitter */
#ifndef TOLUA_DISABLE_tolua_Graphics_ParticleEmitter_GetTextureFrame00
static int tolua_Graphics_ParticleEmitter_GetTextureFrame00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ParticleEmitter",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ParticleEmitter* self = (ParticleEmitter*)  tolua_tousertype(tolua_S,1,0);
  unsigned index = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTextureFrame'", NULL);
#endif
  {
   TextureFrame* tolua_ret = (TextureFrame*)  self->GetTextureFrame(index);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"TextureFrame");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTextureFrame'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetNumViewports of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_SetNumViewports00
static int tolua_Graphics_Renderer_SetNumViewports00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Renderer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Renderer* self = (Renderer*)  tolua_tousertype(tolua_S,1,0);
  unsigned num = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetNumViewports'", NULL);
#endif
  {
   self->SetNumViewports(num);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetNumViewports'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetViewport of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_SetViewport00
static int tolua_Graphics_Renderer_SetViewport00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Renderer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"Viewport",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Renderer* self = (Renderer*)  tolua_tousertype(tolua_S,1,0);
  unsigned index = ((unsigned)  tolua_tonumber(tolua_S,2,0));
  Viewport* viewport = ((Viewport*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetViewport'", NULL);
#endif
  {
   self->SetViewport(index,viewport);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetViewport'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetDefaultRenderPath of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_SetDefaultRenderPath00
static int tolua_Graphics_Renderer_SetDefaultRenderPath00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Renderer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"RenderPath",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Renderer* self = (Renderer*)  tolua_tousertype(tolua_S,1,0);
  RenderPath* renderPath = ((RenderPath*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetDefaultRenderPath'", NULL);
#endif
  {
   self->SetDefaultRenderPath(renderPath);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetDefaultRenderPath'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetDefaultRenderPath of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_SetDefaultRenderPath01
static int tolua_Graphics_Renderer_SetDefaultRenderPath01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Renderer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"XMLFile",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  Renderer* self = (Renderer*)  tolua_tousertype(tolua_S,1,0);
  XMLFile* file = ((XMLFile*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetDefaultRenderPath'", NULL);
#endif
  {
   self->SetDefaultRenderPath(file);
  }
 }
 return 0;
tolua_lerror:
 return tolua_Graphics_Renderer_SetDefaultRenderPath00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetSpecularLighting of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_SetSpecularLighting00
static int tolua_Graphics_Renderer_SetSpecularLighting00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Renderer",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Renderer* self = (Renderer*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetSpecularLighting'", NULL);
#endif
  {
   self->SetSpecularLighting(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetSpecularLighting'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetTextureAnisotropy of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_SetTextureAnisotropy00
static int tolua_Graphics_Renderer_SetTextureAnisotropy00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Renderer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Renderer* self = (Renderer*)  tolua_tousertype(tolua_S,1,0);
  int level = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetTextureAnisotropy'", NULL);
#endif
  {
   self->SetTextureAnisotropy(level);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetTextureAnisotropy'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetTextureFilterMode of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_SetTextureFilterMode00
static int tolua_Graphics_Renderer_SetTextureFilterMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Renderer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Renderer* self = (Renderer*)  tolua_tousertype(tolua_S,1,0);
  TextureFilterMode mode = ((TextureFilterMode) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetTextureFilterMode'", NULL);
#endif
  {
   self->SetTextureFilterMode(mode);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetTextureFilterMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetTextureQuality of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_SetTextureQuality00
static int tolua_Graphics_Renderer_SetTextureQuality00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Renderer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Renderer* self = (Renderer*)  tolua_tousertype(tolua_S,1,0);
  int quality = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetTextureQuality'", NULL);
#endif
  {
   self->SetTextureQuality(quality);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetTextureQuality'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMaterialQuality of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_SetMaterialQuality00
static int tolua_Graphics_Renderer_SetMaterialQuality00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Renderer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Renderer* self = (Renderer*)  tolua_tousertype(tolua_S,1,0);
  int quality = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMaterialQuality'", NULL);
#endif
  {
   self->SetMaterialQuality(quality);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMaterialQuality'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetDrawShadows of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_SetDrawShadows00
static int tolua_Graphics_Renderer_SetDrawShadows00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Renderer",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Renderer* self = (Renderer*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetDrawShadows'", NULL);
#endif
  {
   self->SetDrawShadows(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetDrawShadows'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetShadowMapSize of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_SetShadowMapSize00
static int tolua_Graphics_Renderer_SetShadowMapSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Renderer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Renderer* self = (Renderer*)  tolua_tousertype(tolua_S,1,0);
  int size = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetShadowMapSize'", NULL);
#endif
  {
   self->SetShadowMapSize(size);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetShadowMapSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetShadowQuality of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_SetShadowQuality00
static int tolua_Graphics_Renderer_SetShadowQuality00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Renderer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Renderer* self = (Renderer*)  tolua_tousertype(tolua_S,1,0);
  int quality = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetShadowQuality'", NULL);
#endif
  {
   self->SetShadowQuality(quality);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetShadowQuality'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetReuseShadowMaps of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_SetReuseShadowMaps00
static int tolua_Graphics_Renderer_SetReuseShadowMaps00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Renderer",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Renderer* self = (Renderer*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetReuseShadowMaps'", NULL);
#endif
  {
   self->SetReuseShadowMaps(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetReuseShadowMaps'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMaxShadowMaps of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_SetMaxShadowMaps00
static int tolua_Graphics_Renderer_SetMaxShadowMaps00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Renderer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Renderer* self = (Renderer*)  tolua_tousertype(tolua_S,1,0);
  int shadowMaps = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMaxShadowMaps'", NULL);
#endif
  {
   self->SetMaxShadowMaps(shadowMaps);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMaxShadowMaps'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMaxShadowCascades of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_SetMaxShadowCascades00
static int tolua_Graphics_Renderer_SetMaxShadowCascades00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Renderer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Renderer* self = (Renderer*)  tolua_tousertype(tolua_S,1,0);
  int cascades = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMaxShadowCascades'", NULL);
#endif
  {
   self->SetMaxShadowCascades(cascades);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMaxShadowCascades'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetDynamicInstancing of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_SetDynamicInstancing00
static int tolua_Graphics_Renderer_SetDynamicInstancing00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Renderer",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Renderer* self = (Renderer*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetDynamicInstancing'", NULL);
#endif
  {
   self->SetDynamicInstancing(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetDynamicInstancing'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMinInstances of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_SetMinInstances00
static int tolua_Graphics_Renderer_SetMinInstances00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Renderer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Renderer* self = (Renderer*)  tolua_tousertype(tolua_S,1,0);
  int instances = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMinInstances'", NULL);
#endif
  {
   self->SetMinInstances(instances);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMinInstances'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMaxInstanceTriangles of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_SetMaxInstanceTriangles00
static int tolua_Graphics_Renderer_SetMaxInstanceTriangles00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Renderer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Renderer* self = (Renderer*)  tolua_tousertype(tolua_S,1,0);
  int triangles = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMaxInstanceTriangles'", NULL);
#endif
  {
   self->SetMaxInstanceTriangles(triangles);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMaxInstanceTriangles'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMaxSortedInstances of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_SetMaxSortedInstances00
static int tolua_Graphics_Renderer_SetMaxSortedInstances00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Renderer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Renderer* self = (Renderer*)  tolua_tousertype(tolua_S,1,0);
  int instances = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMaxSortedInstances'", NULL);
#endif
  {
   self->SetMaxSortedInstances(instances);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMaxSortedInstances'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMaxOccluderTriangles of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_SetMaxOccluderTriangles00
static int tolua_Graphics_Renderer_SetMaxOccluderTriangles00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Renderer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Renderer* self = (Renderer*)  tolua_tousertype(tolua_S,1,0);
  int triangles = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMaxOccluderTriangles'", NULL);
#endif
  {
   self->SetMaxOccluderTriangles(triangles);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMaxOccluderTriangles'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetOcclusionBufferSize of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_SetOcclusionBufferSize00
static int tolua_Graphics_Renderer_SetOcclusionBufferSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Renderer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Renderer* self = (Renderer*)  tolua_tousertype(tolua_S,1,0);
  int size = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetOcclusionBufferSize'", NULL);
#endif
  {
   self->SetOcclusionBufferSize(size);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetOcclusionBufferSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetOccluderSizeThreshold of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_SetOccluderSizeThreshold00
static int tolua_Graphics_Renderer_SetOccluderSizeThreshold00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Renderer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Renderer* self = (Renderer*)  tolua_tousertype(tolua_S,1,0);
  float screenSize = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetOccluderSizeThreshold'", NULL);
#endif
  {
   self->SetOccluderSizeThreshold(screenSize);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetOccluderSizeThreshold'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ReloadShaders of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_ReloadShaders00
static int tolua_Graphics_Renderer_ReloadShaders00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Renderer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Renderer* self = (Renderer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ReloadShaders'", NULL);
#endif
  {
   self->ReloadShaders();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ReloadShaders'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNumViewports of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_GetNumViewports00
static int tolua_Graphics_Renderer_GetNumViewports00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Renderer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Renderer* self = (const Renderer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNumViewports'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetNumViewports();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNumViewports'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetViewport of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_GetViewport00
static int tolua_Graphics_Renderer_GetViewport00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Renderer",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Renderer* self = (const Renderer*)  tolua_tousertype(tolua_S,1,0);
  unsigned index = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetViewport'", NULL);
#endif
  {
   Viewport* tolua_ret = (Viewport*)  self->GetViewport(index);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Viewport");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetViewport'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetDefaultRenderPath of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_GetDefaultRenderPath00
static int tolua_Graphics_Renderer_GetDefaultRenderPath00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Renderer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Renderer* self = (const Renderer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetDefaultRenderPath'", NULL);
#endif
  {
   RenderPath* tolua_ret = (RenderPath*)  self->GetDefaultRenderPath();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"RenderPath");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDefaultRenderPath'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSpecularLighting of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_GetSpecularLighting00
static int tolua_Graphics_Renderer_GetSpecularLighting00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Renderer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Renderer* self = (const Renderer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSpecularLighting'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetSpecularLighting();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSpecularLighting'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetDrawShadows of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_GetDrawShadows00
static int tolua_Graphics_Renderer_GetDrawShadows00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Renderer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Renderer* self = (const Renderer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetDrawShadows'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetDrawShadows();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDrawShadows'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTextureAnisotropy of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_GetTextureAnisotropy00
static int tolua_Graphics_Renderer_GetTextureAnisotropy00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Renderer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Renderer* self = (const Renderer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTextureAnisotropy'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetTextureAnisotropy();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTextureAnisotropy'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTextureFilterMode of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_GetTextureFilterMode00
static int tolua_Graphics_Renderer_GetTextureFilterMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Renderer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Renderer* self = (const Renderer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTextureFilterMode'", NULL);
#endif
  {
   TextureFilterMode tolua_ret = (TextureFilterMode)  self->GetTextureFilterMode();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTextureFilterMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetTextureQuality of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_GetTextureQuality00
static int tolua_Graphics_Renderer_GetTextureQuality00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Renderer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Renderer* self = (const Renderer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTextureQuality'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetTextureQuality();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTextureQuality'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMaterialQuality of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_GetMaterialQuality00
static int tolua_Graphics_Renderer_GetMaterialQuality00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Renderer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Renderer* self = (const Renderer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMaterialQuality'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetMaterialQuality();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMaterialQuality'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetShadowMapSize of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_GetShadowMapSize00
static int tolua_Graphics_Renderer_GetShadowMapSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Renderer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Renderer* self = (const Renderer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetShadowMapSize'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetShadowMapSize();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetShadowMapSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetShadowQuality of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_GetShadowQuality00
static int tolua_Graphics_Renderer_GetShadowQuality00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Renderer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Renderer* self = (const Renderer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetShadowQuality'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetShadowQuality();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetShadowQuality'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetReuseShadowMaps of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_GetReuseShadowMaps00
static int tolua_Graphics_Renderer_GetReuseShadowMaps00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Renderer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Renderer* self = (const Renderer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetReuseShadowMaps'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetReuseShadowMaps();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetReuseShadowMaps'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMaxShadowMaps of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_GetMaxShadowMaps00
static int tolua_Graphics_Renderer_GetMaxShadowMaps00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Renderer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Renderer* self = (const Renderer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMaxShadowMaps'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetMaxShadowMaps();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMaxShadowMaps'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMaxShadowCascades of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_GetMaxShadowCascades00
static int tolua_Graphics_Renderer_GetMaxShadowCascades00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Renderer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Renderer* self = (const Renderer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMaxShadowCascades'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetMaxShadowCascades();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMaxShadowCascades'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetDynamicInstancing of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_GetDynamicInstancing00
static int tolua_Graphics_Renderer_GetDynamicInstancing00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Renderer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Renderer* self = (const Renderer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetDynamicInstancing'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetDynamicInstancing();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDynamicInstancing'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMinInstances of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_GetMinInstances00
static int tolua_Graphics_Renderer_GetMinInstances00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Renderer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Renderer* self = (const Renderer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMinInstances'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetMinInstances();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMinInstances'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMaxInstanceTriangles of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_GetMaxInstanceTriangles00
static int tolua_Graphics_Renderer_GetMaxInstanceTriangles00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Renderer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Renderer* self = (const Renderer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMaxInstanceTriangles'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetMaxInstanceTriangles();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMaxInstanceTriangles'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMaxSortedInstances of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_GetMaxSortedInstances00
static int tolua_Graphics_Renderer_GetMaxSortedInstances00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Renderer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Renderer* self = (const Renderer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMaxSortedInstances'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetMaxSortedInstances();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMaxSortedInstances'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMaxOccluderTriangles of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_GetMaxOccluderTriangles00
static int tolua_Graphics_Renderer_GetMaxOccluderTriangles00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Renderer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Renderer* self = (const Renderer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMaxOccluderTriangles'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetMaxOccluderTriangles();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMaxOccluderTriangles'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetOcclusionBufferSize of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_GetOcclusionBufferSize00
static int tolua_Graphics_Renderer_GetOcclusionBufferSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Renderer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Renderer* self = (const Renderer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetOcclusionBufferSize'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetOcclusionBufferSize();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetOcclusionBufferSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetOccluderSizeThreshold of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_GetOccluderSizeThreshold00
static int tolua_Graphics_Renderer_GetOccluderSizeThreshold00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Renderer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Renderer* self = (const Renderer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetOccluderSizeThreshold'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetOccluderSizeThreshold();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetOccluderSizeThreshold'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNumViews of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_GetNumViews00
static int tolua_Graphics_Renderer_GetNumViews00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Renderer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Renderer* self = (const Renderer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNumViews'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetNumViews();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNumViews'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNumPrimitives of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_GetNumPrimitives00
static int tolua_Graphics_Renderer_GetNumPrimitives00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Renderer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Renderer* self = (const Renderer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNumPrimitives'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetNumPrimitives();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNumPrimitives'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNumBatches of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_GetNumBatches00
static int tolua_Graphics_Renderer_GetNumBatches00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Renderer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Renderer* self = (const Renderer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNumBatches'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetNumBatches();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNumBatches'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNumGeometries of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_GetNumGeometries00
static int tolua_Graphics_Renderer_GetNumGeometries00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Renderer",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Renderer* self = (const Renderer*)  tolua_tousertype(tolua_S,1,0);
  bool allViews = ((bool)  tolua_toboolean(tolua_S,2,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNumGeometries'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetNumGeometries(allViews);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNumGeometries'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNumLights of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_GetNumLights00
static int tolua_Graphics_Renderer_GetNumLights00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Renderer",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Renderer* self = (const Renderer*)  tolua_tousertype(tolua_S,1,0);
  bool allViews = ((bool)  tolua_toboolean(tolua_S,2,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNumLights'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetNumLights(allViews);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNumLights'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNumShadowMaps of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_GetNumShadowMaps00
static int tolua_Graphics_Renderer_GetNumShadowMaps00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Renderer",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Renderer* self = (const Renderer*)  tolua_tousertype(tolua_S,1,0);
  bool allViews = ((bool)  tolua_toboolean(tolua_S,2,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNumShadowMaps'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetNumShadowMaps(allViews);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNumShadowMaps'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNumOccluders of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_GetNumOccluders00
static int tolua_Graphics_Renderer_GetNumOccluders00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Renderer",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Renderer* self = (const Renderer*)  tolua_tousertype(tolua_S,1,0);
  bool allViews = ((bool)  tolua_toboolean(tolua_S,2,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNumOccluders'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetNumOccluders(allViews);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNumOccluders'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetDefaultZone of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_GetDefaultZone00
static int tolua_Graphics_Renderer_GetDefaultZone00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Renderer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Renderer* self = (const Renderer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetDefaultZone'", NULL);
#endif
  {
   Zone* tolua_ret = (Zone*)  self->GetDefaultZone();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Zone");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDefaultZone'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetQuadDirLight of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_GetQuadDirLight00
static int tolua_Graphics_Renderer_GetQuadDirLight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Renderer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Renderer* self = (const Renderer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetQuadDirLight'", NULL);
#endif
  {
   Light* tolua_ret = (Light*)  self->GetQuadDirLight();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Light");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetQuadDirLight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetDefaultMaterial of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_GetDefaultMaterial00
static int tolua_Graphics_Renderer_GetDefaultMaterial00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Renderer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Renderer* self = (const Renderer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetDefaultMaterial'", NULL);
#endif
  {
   Material* tolua_ret = (Material*)  self->GetDefaultMaterial();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Material");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDefaultMaterial'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetDefaultLightRamp of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_GetDefaultLightRamp00
static int tolua_Graphics_Renderer_GetDefaultLightRamp00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Renderer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Renderer* self = (const Renderer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetDefaultLightRamp'", NULL);
#endif
  {
   Texture2D* tolua_ret = (Texture2D*)  self->GetDefaultLightRamp();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Texture2D");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDefaultLightRamp'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetDefaultLightSpot of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_GetDefaultLightSpot00
static int tolua_Graphics_Renderer_GetDefaultLightSpot00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Renderer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Renderer* self = (const Renderer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetDefaultLightSpot'", NULL);
#endif
  {
   Texture2D* tolua_ret = (Texture2D*)  self->GetDefaultLightSpot();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Texture2D");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDefaultLightSpot'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFaceSelectCubeMap of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_GetFaceSelectCubeMap00
static int tolua_Graphics_Renderer_GetFaceSelectCubeMap00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Renderer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Renderer* self = (const Renderer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFaceSelectCubeMap'", NULL);
#endif
  {
   TextureCube* tolua_ret = (TextureCube*)  self->GetFaceSelectCubeMap();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"TextureCube");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFaceSelectCubeMap'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetIndirectionCubeMap of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_GetIndirectionCubeMap00
static int tolua_Graphics_Renderer_GetIndirectionCubeMap00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Renderer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Renderer* self = (const Renderer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetIndirectionCubeMap'", NULL);
#endif
  {
   TextureCube* tolua_ret = (TextureCube*)  self->GetIndirectionCubeMap();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"TextureCube");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetIndirectionCubeMap'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetInstancingBuffer of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_GetInstancingBuffer00
static int tolua_Graphics_Renderer_GetInstancingBuffer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Renderer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Renderer* self = (const Renderer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetInstancingBuffer'", NULL);
#endif
  {
   VertexBuffer* tolua_ret = (VertexBuffer*)  self->GetInstancingBuffer();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"VertexBuffer");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetInstancingBuffer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetVertexShader of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_GetVertexShader00
static int tolua_Graphics_Renderer_GetVertexShader00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Renderer",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Renderer* self = (const Renderer*)  tolua_tousertype(tolua_S,1,0);
  const String* name = ((const String*)  tolua_tousertype(tolua_S,2,0));
  bool checkExists = ((bool)  tolua_toboolean(tolua_S,3,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetVertexShader'", NULL);
#endif
  {
   ShaderVariation* tolua_ret = (ShaderVariation*)  self->GetVertexShader(*name,checkExists);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ShaderVariation");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetVertexShader'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetPixelShader of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_GetPixelShader00
static int tolua_Graphics_Renderer_GetPixelShader00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Renderer",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const String",0,&tolua_err)) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Renderer* self = (const Renderer*)  tolua_tousertype(tolua_S,1,0);
  const String* name = ((const String*)  tolua_tousertype(tolua_S,2,0));
  bool checkExists = ((bool)  tolua_toboolean(tolua_S,3,false));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPixelShader'", NULL);
#endif
  {
   ShaderVariation* tolua_ret = (ShaderVariation*)  self->GetPixelShader(*name,checkExists);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ShaderVariation");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPixelShader'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetStencilVS of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_GetStencilVS00
static int tolua_Graphics_Renderer_GetStencilVS00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Renderer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Renderer* self = (const Renderer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetStencilVS'", NULL);
#endif
  {
   ShaderVariation* tolua_ret = (ShaderVariation*)  self->GetStencilVS();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ShaderVariation");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetStencilVS'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetStencilPS of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_GetStencilPS00
static int tolua_Graphics_Renderer_GetStencilPS00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Renderer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Renderer* self = (const Renderer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetStencilPS'", NULL);
#endif
  {
   ShaderVariation* tolua_ret = (ShaderVariation*)  self->GetStencilPS();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"ShaderVariation");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetStencilPS'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFrameInfo of class  Renderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_Renderer_GetFrameInfo00
static int tolua_Graphics_Renderer_GetFrameInfo00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Renderer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Renderer* self = (Renderer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFrameInfo'", NULL);
#endif
  {
   const FrameInfo& tolua_ret = (const FrameInfo&)  self->GetFrameInfo();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const FrameInfo");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFrameInfo'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* function: GetRenderer */
#ifndef TOLUA_DISABLE_tolua_Graphics_GetRenderer00
static int tolua_Graphics_GetRenderer00(lua_State* tolua_S)
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
   Renderer* tolua_ret = (Renderer*)  GetRenderer();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Renderer");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRenderer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetNumViewports of class  RenderSurface */
#ifndef TOLUA_DISABLE_tolua_Graphics_RenderSurface_SetNumViewports00
static int tolua_Graphics_RenderSurface_SetNumViewports00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RenderSurface",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RenderSurface* self = (RenderSurface*)  tolua_tousertype(tolua_S,1,0);
  unsigned num = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetNumViewports'", NULL);
#endif
  {
   self->SetNumViewports(num);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetNumViewports'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetViewport of class  RenderSurface */
#ifndef TOLUA_DISABLE_tolua_Graphics_RenderSurface_SetViewport00
static int tolua_Graphics_RenderSurface_SetViewport00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RenderSurface",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"Viewport",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RenderSurface* self = (RenderSurface*)  tolua_tousertype(tolua_S,1,0);
  unsigned index = ((unsigned)  tolua_tonumber(tolua_S,2,0));
  Viewport* viewport = ((Viewport*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetViewport'", NULL);
#endif
  {
   self->SetViewport(index,viewport);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetViewport'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetUpdateMode of class  RenderSurface */
#ifndef TOLUA_DISABLE_tolua_Graphics_RenderSurface_SetUpdateMode00
static int tolua_Graphics_RenderSurface_SetUpdateMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RenderSurface",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RenderSurface* self = (RenderSurface*)  tolua_tousertype(tolua_S,1,0);
  RenderSurfaceUpdateMode mode = ((RenderSurfaceUpdateMode) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetUpdateMode'", NULL);
#endif
  {
   self->SetUpdateMode(mode);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetUpdateMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetLinkedRenderTarget of class  RenderSurface */
#ifndef TOLUA_DISABLE_tolua_Graphics_RenderSurface_SetLinkedRenderTarget00
static int tolua_Graphics_RenderSurface_SetLinkedRenderTarget00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RenderSurface",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"RenderSurface",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RenderSurface* self = (RenderSurface*)  tolua_tousertype(tolua_S,1,0);
  RenderSurface* renderTarget = ((RenderSurface*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLinkedRenderTarget'", NULL);
#endif
  {
   self->SetLinkedRenderTarget(renderTarget);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLinkedRenderTarget'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetLinkedDepthStencil of class  RenderSurface */
#ifndef TOLUA_DISABLE_tolua_Graphics_RenderSurface_SetLinkedDepthStencil00
static int tolua_Graphics_RenderSurface_SetLinkedDepthStencil00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RenderSurface",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"RenderSurface",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RenderSurface* self = (RenderSurface*)  tolua_tousertype(tolua_S,1,0);
  RenderSurface* depthStencil = ((RenderSurface*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLinkedDepthStencil'", NULL);
#endif
  {
   self->SetLinkedDepthStencil(depthStencil);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLinkedDepthStencil'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: QueueUpdate of class  RenderSurface */
#ifndef TOLUA_DISABLE_tolua_Graphics_RenderSurface_QueueUpdate00
static int tolua_Graphics_RenderSurface_QueueUpdate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RenderSurface",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RenderSurface* self = (RenderSurface*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'QueueUpdate'", NULL);
#endif
  {
   self->QueueUpdate();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'QueueUpdate'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: Release of class  RenderSurface */
#ifndef TOLUA_DISABLE_tolua_Graphics_RenderSurface_Release00
static int tolua_Graphics_RenderSurface_Release00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"RenderSurface",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  RenderSurface* self = (RenderSurface*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Release'", NULL);
#endif
  {
   self->Release();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Release'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetParentTexture of class  RenderSurface */
#ifndef TOLUA_DISABLE_tolua_Graphics_RenderSurface_GetParentTexture00
static int tolua_Graphics_RenderSurface_GetParentTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const RenderSurface",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const RenderSurface* self = (const RenderSurface*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetParentTexture'", NULL);
#endif
  {
   Texture* tolua_ret = (Texture*)  self->GetParentTexture();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Texture");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetParentTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetWidth of class  RenderSurface */
#ifndef TOLUA_DISABLE_tolua_Graphics_RenderSurface_GetWidth00
static int tolua_Graphics_RenderSurface_GetWidth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const RenderSurface",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const RenderSurface* self = (const RenderSurface*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetHeight of class  RenderSurface */
#ifndef TOLUA_DISABLE_tolua_Graphics_RenderSurface_GetHeight00
static int tolua_Graphics_RenderSurface_GetHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const RenderSurface",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const RenderSurface* self = (const RenderSurface*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetUsage of class  RenderSurface */
#ifndef TOLUA_DISABLE_tolua_Graphics_RenderSurface_GetUsage00
static int tolua_Graphics_RenderSurface_GetUsage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const RenderSurface",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const RenderSurface* self = (const RenderSurface*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetUsage'", NULL);
#endif
  {
   TextureUsage tolua_ret = (TextureUsage)  self->GetUsage();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetUsage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLinkedRenderTarget of class  RenderSurface */
#ifndef TOLUA_DISABLE_tolua_Graphics_RenderSurface_GetLinkedRenderTarget00
static int tolua_Graphics_RenderSurface_GetLinkedRenderTarget00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const RenderSurface",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const RenderSurface* self = (const RenderSurface*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLinkedRenderTarget'", NULL);
#endif
  {
   RenderSurface* tolua_ret = (RenderSurface*)  self->GetLinkedRenderTarget();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"RenderSurface");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLinkedRenderTarget'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLinkedDepthStencil of class  RenderSurface */
#ifndef TOLUA_DISABLE_tolua_Graphics_RenderSurface_GetLinkedDepthStencil00
static int tolua_Graphics_RenderSurface_GetLinkedDepthStencil00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const RenderSurface",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const RenderSurface* self = (const RenderSurface*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLinkedDepthStencil'", NULL);
#endif
  {
   RenderSurface* tolua_ret = (RenderSurface*)  self->GetLinkedDepthStencil();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"RenderSurface");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLinkedDepthStencil'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: new of class  Bone */
#ifndef TOLUA_DISABLE_tolua_Graphics_Bone_new00
static int tolua_Graphics_Bone_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Bone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Bone* tolua_ret = (Bone*)  Mtolua_new((Bone)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Bone");
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

/* method: new_local of class  Bone */
#ifndef TOLUA_DISABLE_tolua_Graphics_Bone_new00_local
static int tolua_Graphics_Bone_new00_local(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"Bone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  {
   Bone* tolua_ret = (Bone*)  Mtolua_new((Bone)());
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Bone");
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

/* get function: name_ of class  Bone */
#ifndef TOLUA_DISABLE_tolua_get_Bone_name
static int tolua_get_Bone_name(lua_State* tolua_S)
{
  Bone* self = (Bone*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'name_'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->name_,"String");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: name_ of class  Bone */
#ifndef TOLUA_DISABLE_tolua_set_Bone_name
static int tolua_set_Bone_name(lua_State* tolua_S)
{
  Bone* self = (Bone*)  tolua_tousertype(tolua_S,1,0);
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

/* get function: nameHash_ of class  Bone */
#ifndef TOLUA_DISABLE_tolua_get_Bone_nameHash
static int tolua_get_Bone_nameHash(lua_State* tolua_S)
{
  Bone* self = (Bone*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nameHash_'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->nameHash_,"StringHash");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: nameHash_ of class  Bone */
#ifndef TOLUA_DISABLE_tolua_set_Bone_nameHash
static int tolua_set_Bone_nameHash(lua_State* tolua_S)
{
  Bone* self = (Bone*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'nameHash_'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"StringHash",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->nameHash_ = *((StringHash*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: parentIndex_ of class  Bone */
#ifndef TOLUA_DISABLE_tolua_get_Bone_parentIndex
static int tolua_get_Bone_parentIndex(lua_State* tolua_S)
{
  Bone* self = (Bone*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'parentIndex_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->parentIndex_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: parentIndex_ of class  Bone */
#ifndef TOLUA_DISABLE_tolua_set_Bone_parentIndex
static int tolua_set_Bone_parentIndex(lua_State* tolua_S)
{
  Bone* self = (Bone*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'parentIndex_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->parentIndex_ = ((unsigned)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: initialPosition_ of class  Bone */
#ifndef TOLUA_DISABLE_tolua_get_Bone_initialPosition
static int tolua_get_Bone_initialPosition(lua_State* tolua_S)
{
  Bone* self = (Bone*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'initialPosition_'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->initialPosition_,"Vector3");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: initialPosition_ of class  Bone */
#ifndef TOLUA_DISABLE_tolua_set_Bone_initialPosition
static int tolua_set_Bone_initialPosition(lua_State* tolua_S)
{
  Bone* self = (Bone*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'initialPosition_'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"Vector3",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->initialPosition_ = *((Vector3*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: initialRotation_ of class  Bone */
#ifndef TOLUA_DISABLE_tolua_get_Bone_initialRotation
static int tolua_get_Bone_initialRotation(lua_State* tolua_S)
{
  Bone* self = (Bone*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'initialRotation_'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->initialRotation_,"Quaternion");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: initialRotation_ of class  Bone */
#ifndef TOLUA_DISABLE_tolua_set_Bone_initialRotation
static int tolua_set_Bone_initialRotation(lua_State* tolua_S)
{
  Bone* self = (Bone*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'initialRotation_'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"Quaternion",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->initialRotation_ = *((Quaternion*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: initialScale_ of class  Bone */
#ifndef TOLUA_DISABLE_tolua_get_Bone_initialScale
static int tolua_get_Bone_initialScale(lua_State* tolua_S)
{
  Bone* self = (Bone*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'initialScale_'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->initialScale_,"Vector3");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: initialScale_ of class  Bone */
#ifndef TOLUA_DISABLE_tolua_set_Bone_initialScale
static int tolua_set_Bone_initialScale(lua_State* tolua_S)
{
  Bone* self = (Bone*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'initialScale_'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"Vector3",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->initialScale_ = *((Vector3*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: offsetMatrix_ of class  Bone */
#ifndef TOLUA_DISABLE_tolua_get_Bone_offsetMatrix
static int tolua_get_Bone_offsetMatrix(lua_State* tolua_S)
{
  Bone* self = (Bone*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'offsetMatrix_'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->offsetMatrix_,"Matrix3x4");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: offsetMatrix_ of class  Bone */
#ifndef TOLUA_DISABLE_tolua_set_Bone_offsetMatrix
static int tolua_set_Bone_offsetMatrix(lua_State* tolua_S)
{
  Bone* self = (Bone*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'offsetMatrix_'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"Matrix3x4",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->offsetMatrix_ = *((Matrix3x4*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: animated_ of class  Bone */
#ifndef TOLUA_DISABLE_tolua_get_Bone_animated
static int tolua_get_Bone_animated(lua_State* tolua_S)
{
  Bone* self = (Bone*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'animated_'",NULL);
#endif
  tolua_pushboolean(tolua_S,(bool)self->animated_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: animated_ of class  Bone */
#ifndef TOLUA_DISABLE_tolua_set_Bone_animated
static int tolua_set_Bone_animated(lua_State* tolua_S)
{
  Bone* self = (Bone*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'animated_'",NULL);
  if (!tolua_isboolean(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->animated_ = ((bool)  tolua_toboolean(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: collisionMask_ of class  Bone */
#ifndef TOLUA_DISABLE_tolua_get_Bone_unsigned_collisionMask
static int tolua_get_Bone_unsigned_collisionMask(lua_State* tolua_S)
{
  Bone* self = (Bone*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'collisionMask_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->collisionMask_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: collisionMask_ of class  Bone */
#ifndef TOLUA_DISABLE_tolua_set_Bone_unsigned_collisionMask
static int tolua_set_Bone_unsigned_collisionMask(lua_State* tolua_S)
{
  Bone* self = (Bone*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'collisionMask_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->collisionMask_ = ((unsigned char)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: radius_ of class  Bone */
#ifndef TOLUA_DISABLE_tolua_get_Bone_radius
static int tolua_get_Bone_radius(lua_State* tolua_S)
{
  Bone* self = (Bone*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'radius_'",NULL);
#endif
  tolua_pushnumber(tolua_S,(lua_Number)self->radius_);
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: radius_ of class  Bone */
#ifndef TOLUA_DISABLE_tolua_set_Bone_radius
static int tolua_set_Bone_radius(lua_State* tolua_S)
{
  Bone* self = (Bone*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'radius_'",NULL);
  if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->radius_ = ((float)  tolua_tonumber(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: boundingBox_ of class  Bone */
#ifndef TOLUA_DISABLE_tolua_get_Bone_boundingBox
static int tolua_get_Bone_boundingBox(lua_State* tolua_S)
{
  Bone* self = (Bone*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'boundingBox_'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)&self->boundingBox_,"BoundingBox");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: boundingBox_ of class  Bone */
#ifndef TOLUA_DISABLE_tolua_set_Bone_boundingBox
static int tolua_set_Bone_boundingBox(lua_State* tolua_S)
{
  Bone* self = (Bone*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'boundingBox_'",NULL);
  if ((tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"BoundingBox",0,&tolua_err)))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->boundingBox_ = *((BoundingBox*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* get function: node_ of class  Bone */
#ifndef TOLUA_DISABLE_tolua_get_Bone_node_ptr
static int tolua_get_Bone_node_ptr(lua_State* tolua_S)
{
  Bone* self = (Bone*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'node_'",NULL);
#endif
   tolua_pushusertype(tolua_S,(void*)self->node_,"Node");
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* set function: node_ of class  Bone */
#ifndef TOLUA_DISABLE_tolua_set_Bone_node_ptr
static int tolua_set_Bone_node_ptr(lua_State* tolua_S)
{
  Bone* self = (Bone*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'node_'",NULL);
  if (!tolua_isusertype(tolua_S,2,"Node",0,&tolua_err))
   tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->node_ = ((Node*)  tolua_tousertype(tolua_S,2,0))
;
 return 0;
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNumBones of class  Skeleton */
#ifndef TOLUA_DISABLE_tolua_Graphics_Skeleton_GetNumBones00
static int tolua_Graphics_Skeleton_GetNumBones00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Skeleton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Skeleton* self = (const Skeleton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNumBones'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetNumBones();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNumBones'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRootBone of class  Skeleton */
#ifndef TOLUA_DISABLE_tolua_Graphics_Skeleton_GetRootBone00
static int tolua_Graphics_Skeleton_GetRootBone00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Skeleton",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Skeleton* self = (Skeleton*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRootBone'", NULL);
#endif
  {
   Bone* tolua_ret = (Bone*)  self->GetRootBone();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Bone");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRootBone'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetBone of class  Skeleton */
#ifndef TOLUA_DISABLE_tolua_Graphics_Skeleton_GetBone00
static int tolua_Graphics_Skeleton_GetBone00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Skeleton",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Skeleton* self = (Skeleton*)  tolua_tousertype(tolua_S,1,0);
  unsigned index = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetBone'", NULL);
#endif
  {
   Bone* tolua_ret = (Bone*)  self->GetBone(index);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Bone");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetBone'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetModel of class  StaticModel */
#ifndef TOLUA_DISABLE_tolua_Graphics_StaticModel_SetModel00
static int tolua_Graphics_StaticModel_SetModel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"StaticModel",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Model",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  StaticModel* self = (StaticModel*)  tolua_tousertype(tolua_S,1,0);
  Model* model = ((Model*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetModel'", NULL);
#endif
  {
   self->SetModel(model);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetModel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMaterial of class  StaticModel */
#ifndef TOLUA_DISABLE_tolua_Graphics_StaticModel_SetMaterial00
static int tolua_Graphics_StaticModel_SetMaterial00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"StaticModel",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Material",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  StaticModel* self = (StaticModel*)  tolua_tousertype(tolua_S,1,0);
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

/* method: SetMaterial of class  StaticModel */
#ifndef TOLUA_DISABLE_tolua_Graphics_StaticModel_SetMaterial01
static int tolua_Graphics_StaticModel_SetMaterial01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"StaticModel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"Material",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  StaticModel* self = (StaticModel*)  tolua_tousertype(tolua_S,1,0);
  unsigned index = ((unsigned)  tolua_tonumber(tolua_S,2,0));
  Material* material = ((Material*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMaterial'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SetMaterial(index,material);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
tolua_lerror:
 return tolua_Graphics_StaticModel_SetMaterial00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetOcclusionLodLevel of class  StaticModel */
#ifndef TOLUA_DISABLE_tolua_Graphics_StaticModel_SetOcclusionLodLevel00
static int tolua_Graphics_StaticModel_SetOcclusionLodLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"StaticModel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  StaticModel* self = (StaticModel*)  tolua_tousertype(tolua_S,1,0);
  unsigned level = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetOcclusionLodLevel'", NULL);
#endif
  {
   self->SetOcclusionLodLevel(level);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetOcclusionLodLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetModel of class  StaticModel */
#ifndef TOLUA_DISABLE_tolua_Graphics_StaticModel_GetModel00
static int tolua_Graphics_StaticModel_GetModel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const StaticModel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const StaticModel* self = (const StaticModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetModel'", NULL);
#endif
  {
   Model* tolua_ret = (Model*)  self->GetModel();
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

/* method: GetBoundingBox of class  StaticModel */
#ifndef TOLUA_DISABLE_tolua_Graphics_StaticModel_GetBoundingBox00
static int tolua_Graphics_StaticModel_GetBoundingBox00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const StaticModel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const StaticModel* self = (const StaticModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetBoundingBox'", NULL);
#endif
  {
   const BoundingBox& tolua_ret = (const BoundingBox&)  self->GetBoundingBox();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const BoundingBox");
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

/* method: GetNumGeometries of class  StaticModel */
#ifndef TOLUA_DISABLE_tolua_Graphics_StaticModel_GetNumGeometries00
static int tolua_Graphics_StaticModel_GetNumGeometries00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const StaticModel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const StaticModel* self = (const StaticModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNumGeometries'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetNumGeometries();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNumGeometries'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMaterial of class  StaticModel */
#ifndef TOLUA_DISABLE_tolua_Graphics_StaticModel_GetMaterial00
static int tolua_Graphics_StaticModel_GetMaterial00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const StaticModel",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const StaticModel* self = (const StaticModel*)  tolua_tousertype(tolua_S,1,0);
  unsigned index = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMaterial'", NULL);
#endif
  {
   Material* tolua_ret = (Material*)  self->GetMaterial(index);
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

/* method: GetOcclusionLodLevel of class  StaticModel */
#ifndef TOLUA_DISABLE_tolua_Graphics_StaticModel_GetOcclusionLodLevel00
static int tolua_Graphics_StaticModel_GetOcclusionLodLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const StaticModel",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const StaticModel* self = (const StaticModel*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetOcclusionLodLevel'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetOcclusionLodLevel();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetOcclusionLodLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsInside of class  StaticModel */
#ifndef TOLUA_DISABLE_tolua_Graphics_StaticModel_IsInside00
static int tolua_Graphics_StaticModel_IsInside00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const StaticModel",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const StaticModel* self = (const StaticModel*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* point = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsInside'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsInside(*point);
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

/* method: IsInsideLocal of class  StaticModel */
#ifndef TOLUA_DISABLE_tolua_Graphics_StaticModel_IsInsideLocal00
static int tolua_Graphics_StaticModel_IsInsideLocal00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const StaticModel",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const StaticModel* self = (const StaticModel*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* point = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsInsideLocal'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsInsideLocal(*point);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsInsideLocal'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetIsSM3 of class  Technique */
#ifndef TOLUA_DISABLE_tolua_Graphics_Technique_SetIsSM300
static int tolua_Graphics_Technique_SetIsSM300(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Technique",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Technique* self = (Technique*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetIsSM3'", NULL);
#endif
  {
   self->SetIsSM3(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetIsSM3'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ReleaseShaders of class  Technique */
#ifndef TOLUA_DISABLE_tolua_Graphics_Technique_ReleaseShaders00
static int tolua_Graphics_Technique_ReleaseShaders00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Technique",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Technique* self = (Technique*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ReleaseShaders'", NULL);
#endif
  {
   self->ReleaseShaders();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ReleaseShaders'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsSM3 of class  Technique */
#ifndef TOLUA_DISABLE_tolua_Graphics_Technique_IsSM300
static int tolua_Graphics_Technique_IsSM300(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Technique",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Technique* self = (const Technique*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsSM3'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsSM3();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsSM3'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetPatchSize of class  Terrain */
#ifndef TOLUA_DISABLE_tolua_Graphics_Terrain_SetPatchSize00
static int tolua_Graphics_Terrain_SetPatchSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Terrain",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Terrain* self = (Terrain*)  tolua_tousertype(tolua_S,1,0);
  int size = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetPatchSize'", NULL);
#endif
  {
   self->SetPatchSize(size);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetPatchSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetSpacing of class  Terrain */
#ifndef TOLUA_DISABLE_tolua_Graphics_Terrain_SetSpacing00
static int tolua_Graphics_Terrain_SetSpacing00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Terrain",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Terrain* self = (Terrain*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* spacing = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetSpacing'", NULL);
#endif
  {
   self->SetSpacing(*spacing);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetSpacing'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetSmoothing of class  Terrain */
#ifndef TOLUA_DISABLE_tolua_Graphics_Terrain_SetSmoothing00
static int tolua_Graphics_Terrain_SetSmoothing00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Terrain",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Terrain* self = (Terrain*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetSmoothing'", NULL);
#endif
  {
   self->SetSmoothing(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetSmoothing'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetHeightMap of class  Terrain */
#ifndef TOLUA_DISABLE_tolua_Graphics_Terrain_SetHeightMap00
static int tolua_Graphics_Terrain_SetHeightMap00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Terrain",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Image",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Terrain* self = (Terrain*)  tolua_tousertype(tolua_S,1,0);
  Image* image = ((Image*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetHeightMap'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->SetHeightMap(image);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetHeightMap'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMaterial of class  Terrain */
#ifndef TOLUA_DISABLE_tolua_Graphics_Terrain_SetMaterial00
static int tolua_Graphics_Terrain_SetMaterial00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Terrain",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Material",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Terrain* self = (Terrain*)  tolua_tousertype(tolua_S,1,0);
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

/* method: SetDrawDistance of class  Terrain */
#ifndef TOLUA_DISABLE_tolua_Graphics_Terrain_SetDrawDistance00
static int tolua_Graphics_Terrain_SetDrawDistance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Terrain",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Terrain* self = (Terrain*)  tolua_tousertype(tolua_S,1,0);
  float distance = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetDrawDistance'", NULL);
#endif
  {
   self->SetDrawDistance(distance);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetDrawDistance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetShadowDistance of class  Terrain */
#ifndef TOLUA_DISABLE_tolua_Graphics_Terrain_SetShadowDistance00
static int tolua_Graphics_Terrain_SetShadowDistance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Terrain",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Terrain* self = (Terrain*)  tolua_tousertype(tolua_S,1,0);
  float distance = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetShadowDistance'", NULL);
#endif
  {
   self->SetShadowDistance(distance);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetShadowDistance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetLodBias of class  Terrain */
#ifndef TOLUA_DISABLE_tolua_Graphics_Terrain_SetLodBias00
static int tolua_Graphics_Terrain_SetLodBias00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Terrain",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Terrain* self = (Terrain*)  tolua_tousertype(tolua_S,1,0);
  float bias = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLodBias'", NULL);
#endif
  {
   self->SetLodBias(bias);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLodBias'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetViewMask of class  Terrain */
#ifndef TOLUA_DISABLE_tolua_Graphics_Terrain_SetViewMask00
static int tolua_Graphics_Terrain_SetViewMask00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Terrain",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Terrain* self = (Terrain*)  tolua_tousertype(tolua_S,1,0);
  unsigned mask = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetViewMask'", NULL);
#endif
  {
   self->SetViewMask(mask);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetViewMask'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetLightMask of class  Terrain */
#ifndef TOLUA_DISABLE_tolua_Graphics_Terrain_SetLightMask00
static int tolua_Graphics_Terrain_SetLightMask00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Terrain",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Terrain* self = (Terrain*)  tolua_tousertype(tolua_S,1,0);
  unsigned mask = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetLightMask'", NULL);
#endif
  {
   self->SetLightMask(mask);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetLightMask'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetShadowMask of class  Terrain */
#ifndef TOLUA_DISABLE_tolua_Graphics_Terrain_SetShadowMask00
static int tolua_Graphics_Terrain_SetShadowMask00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Terrain",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Terrain* self = (Terrain*)  tolua_tousertype(tolua_S,1,0);
  unsigned mask = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetShadowMask'", NULL);
#endif
  {
   self->SetShadowMask(mask);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetShadowMask'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetZoneMask of class  Terrain */
#ifndef TOLUA_DISABLE_tolua_Graphics_Terrain_SetZoneMask00
static int tolua_Graphics_Terrain_SetZoneMask00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Terrain",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Terrain* self = (Terrain*)  tolua_tousertype(tolua_S,1,0);
  unsigned mask = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetZoneMask'", NULL);
#endif
  {
   self->SetZoneMask(mask);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetZoneMask'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMaxLights of class  Terrain */
#ifndef TOLUA_DISABLE_tolua_Graphics_Terrain_SetMaxLights00
static int tolua_Graphics_Terrain_SetMaxLights00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Terrain",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Terrain* self = (Terrain*)  tolua_tousertype(tolua_S,1,0);
  unsigned num = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetMaxLights'", NULL);
#endif
  {
   self->SetMaxLights(num);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetMaxLights'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetCastShadows of class  Terrain */
#ifndef TOLUA_DISABLE_tolua_Graphics_Terrain_SetCastShadows00
static int tolua_Graphics_Terrain_SetCastShadows00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Terrain",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Terrain* self = (Terrain*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetCastShadows'", NULL);
#endif
  {
   self->SetCastShadows(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetCastShadows'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetOccluder of class  Terrain */
#ifndef TOLUA_DISABLE_tolua_Graphics_Terrain_SetOccluder00
static int tolua_Graphics_Terrain_SetOccluder00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Terrain",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Terrain* self = (Terrain*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetOccluder'", NULL);
#endif
  {
   self->SetOccluder(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetOccluder'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetOccludee of class  Terrain */
#ifndef TOLUA_DISABLE_tolua_Graphics_Terrain_SetOccludee00
static int tolua_Graphics_Terrain_SetOccludee00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Terrain",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Terrain* self = (Terrain*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetOccludee'", NULL);
#endif
  {
   self->SetOccludee(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetOccludee'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetPatchSize of class  Terrain */
#ifndef TOLUA_DISABLE_tolua_Graphics_Terrain_GetPatchSize00
static int tolua_Graphics_Terrain_GetPatchSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Terrain",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Terrain* self = (const Terrain*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPatchSize'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetPatchSize();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPatchSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSpacing of class  Terrain */
#ifndef TOLUA_DISABLE_tolua_Graphics_Terrain_GetSpacing00
static int tolua_Graphics_Terrain_GetSpacing00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Terrain",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Terrain* self = (const Terrain*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSpacing'", NULL);
#endif
  {
   const Vector3& tolua_ret = (const Vector3&)  self->GetSpacing();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Vector3");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSpacing'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNumVertices of class  Terrain */
#ifndef TOLUA_DISABLE_tolua_Graphics_Terrain_GetNumVertices00
static int tolua_Graphics_Terrain_GetNumVertices00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Terrain",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Terrain* self = (const Terrain*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNumVertices'", NULL);
#endif
  {
   const IntVector2& tolua_ret = (const IntVector2&)  self->GetNumVertices();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const IntVector2");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNumVertices'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetNumPatches of class  Terrain */
#ifndef TOLUA_DISABLE_tolua_Graphics_Terrain_GetNumPatches00
static int tolua_Graphics_Terrain_GetNumPatches00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Terrain",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Terrain* self = (const Terrain*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNumPatches'", NULL);
#endif
  {
   const IntVector2& tolua_ret = (const IntVector2&)  self->GetNumPatches();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const IntVector2");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNumPatches'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSmoothing of class  Terrain */
#ifndef TOLUA_DISABLE_tolua_Graphics_Terrain_GetSmoothing00
static int tolua_Graphics_Terrain_GetSmoothing00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Terrain",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Terrain* self = (const Terrain*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSmoothing'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetSmoothing();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSmoothing'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetHeightMap of class  Terrain */
#ifndef TOLUA_DISABLE_tolua_Graphics_Terrain_GetHeightMap00
static int tolua_Graphics_Terrain_GetHeightMap00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Terrain",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Terrain* self = (const Terrain*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetHeightMap'", NULL);
#endif
  {
   Image* tolua_ret = (Image*)  self->GetHeightMap();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Image");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetHeightMap'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMaterial of class  Terrain */
#ifndef TOLUA_DISABLE_tolua_Graphics_Terrain_GetMaterial00
static int tolua_Graphics_Terrain_GetMaterial00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Terrain",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Terrain* self = (const Terrain*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetPatch of class  Terrain */
#ifndef TOLUA_DISABLE_tolua_Graphics_Terrain_GetPatch00
static int tolua_Graphics_Terrain_GetPatch00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Terrain",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Terrain* self = (const Terrain*)  tolua_tousertype(tolua_S,1,0);
  unsigned index = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPatch'", NULL);
#endif
  {
   TerrainPatch* tolua_ret = (TerrainPatch*)  self->GetPatch(index);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"TerrainPatch");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPatch'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetPatch of class  Terrain */
#ifndef TOLUA_DISABLE_tolua_Graphics_Terrain_GetPatch01
static int tolua_Graphics_Terrain_GetPatch01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Terrain",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const Terrain* self = (const Terrain*)  tolua_tousertype(tolua_S,1,0);
  int x = ((int)  tolua_tonumber(tolua_S,2,0));
  int z = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPatch'", NULL);
#endif
  {
   TerrainPatch* tolua_ret = (TerrainPatch*)  self->GetPatch(x,z);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"TerrainPatch");
  }
 }
 return 1;
tolua_lerror:
 return tolua_Graphics_Terrain_GetPatch00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetHeight of class  Terrain */
#ifndef TOLUA_DISABLE_tolua_Graphics_Terrain_GetHeight00
static int tolua_Graphics_Terrain_GetHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Terrain",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Terrain* self = (const Terrain*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* worldPosition = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetHeight'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetHeight(*worldPosition);
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

/* method: GetNormal of class  Terrain */
#ifndef TOLUA_DISABLE_tolua_Graphics_Terrain_GetNormal00
static int tolua_Graphics_Terrain_GetNormal00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Terrain",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Terrain* self = (const Terrain*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* worldPosition = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNormal'", NULL);
#endif
  {
   Vector3 tolua_ret = (Vector3)  self->GetNormal(*worldPosition);
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
 tolua_error(tolua_S,"#ferror in function 'GetNormal'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetDrawDistance of class  Terrain */
#ifndef TOLUA_DISABLE_tolua_Graphics_Terrain_GetDrawDistance00
static int tolua_Graphics_Terrain_GetDrawDistance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Terrain",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Terrain* self = (const Terrain*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetDrawDistance'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetDrawDistance();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetDrawDistance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetShadowDistance of class  Terrain */
#ifndef TOLUA_DISABLE_tolua_Graphics_Terrain_GetShadowDistance00
static int tolua_Graphics_Terrain_GetShadowDistance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Terrain",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Terrain* self = (const Terrain*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetShadowDistance'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetShadowDistance();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetShadowDistance'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLodBias of class  Terrain */
#ifndef TOLUA_DISABLE_tolua_Graphics_Terrain_GetLodBias00
static int tolua_Graphics_Terrain_GetLodBias00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Terrain",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Terrain* self = (const Terrain*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLodBias'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetLodBias();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLodBias'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetViewMask of class  Terrain */
#ifndef TOLUA_DISABLE_tolua_Graphics_Terrain_GetViewMask00
static int tolua_Graphics_Terrain_GetViewMask00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Terrain",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Terrain* self = (const Terrain*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetViewMask'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetViewMask();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetViewMask'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLightMask of class  Terrain */
#ifndef TOLUA_DISABLE_tolua_Graphics_Terrain_GetLightMask00
static int tolua_Graphics_Terrain_GetLightMask00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Terrain",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Terrain* self = (const Terrain*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLightMask'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetLightMask();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLightMask'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetShadowMask of class  Terrain */
#ifndef TOLUA_DISABLE_tolua_Graphics_Terrain_GetShadowMask00
static int tolua_Graphics_Terrain_GetShadowMask00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Terrain",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Terrain* self = (const Terrain*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetShadowMask'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetShadowMask();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetShadowMask'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetZoneMask of class  Terrain */
#ifndef TOLUA_DISABLE_tolua_Graphics_Terrain_GetZoneMask00
static int tolua_Graphics_Terrain_GetZoneMask00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Terrain",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Terrain* self = (const Terrain*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetZoneMask'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetZoneMask();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetZoneMask'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMaxLights of class  Terrain */
#ifndef TOLUA_DISABLE_tolua_Graphics_Terrain_GetMaxLights00
static int tolua_Graphics_Terrain_GetMaxLights00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Terrain",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Terrain* self = (const Terrain*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMaxLights'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetMaxLights();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMaxLights'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsVisible of class  Terrain */
#ifndef TOLUA_DISABLE_tolua_Graphics_Terrain_IsVisible00
static int tolua_Graphics_Terrain_IsVisible00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Terrain",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Terrain* self = (const Terrain*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetCastShadows of class  Terrain */
#ifndef TOLUA_DISABLE_tolua_Graphics_Terrain_GetCastShadows00
static int tolua_Graphics_Terrain_GetCastShadows00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Terrain",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Terrain* self = (const Terrain*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCastShadows'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetCastShadows();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCastShadows'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsOccluder of class  Terrain */
#ifndef TOLUA_DISABLE_tolua_Graphics_Terrain_IsOccluder00
static int tolua_Graphics_Terrain_IsOccluder00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Terrain",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Terrain* self = (const Terrain*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsOccluder'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsOccluder();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsOccluder'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsOccludee of class  Terrain */
#ifndef TOLUA_DISABLE_tolua_Graphics_Terrain_IsOccludee00
static int tolua_Graphics_Terrain_IsOccludee00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Terrain",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Terrain* self = (const Terrain*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsOccludee'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsOccludee();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsOccludee'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetOwner of class  TerrainPatch */
#ifndef TOLUA_DISABLE_tolua_Graphics_TerrainPatch_SetOwner00
static int tolua_Graphics_TerrainPatch_SetOwner00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TerrainPatch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Terrain",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TerrainPatch* self = (TerrainPatch*)  tolua_tousertype(tolua_S,1,0);
  Terrain* terrain = ((Terrain*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetOwner'", NULL);
#endif
  {
   self->SetOwner(terrain);
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

/* method: SetNeighbors of class  TerrainPatch */
#ifndef TOLUA_DISABLE_tolua_Graphics_TerrainPatch_SetNeighbors00
static int tolua_Graphics_TerrainPatch_SetNeighbors00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TerrainPatch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"TerrainPatch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"TerrainPatch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,4,"TerrainPatch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,5,"TerrainPatch",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TerrainPatch* self = (TerrainPatch*)  tolua_tousertype(tolua_S,1,0);
  TerrainPatch* north = ((TerrainPatch*)  tolua_tousertype(tolua_S,2,0));
  TerrainPatch* south = ((TerrainPatch*)  tolua_tousertype(tolua_S,3,0));
  TerrainPatch* west = ((TerrainPatch*)  tolua_tousertype(tolua_S,4,0));
  TerrainPatch* east = ((TerrainPatch*)  tolua_tousertype(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetNeighbors'", NULL);
#endif
  {
   self->SetNeighbors(north,south,west,east);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetNeighbors'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetMaterial of class  TerrainPatch */
#ifndef TOLUA_DISABLE_tolua_Graphics_TerrainPatch_SetMaterial00
static int tolua_Graphics_TerrainPatch_SetMaterial00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TerrainPatch",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Material",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TerrainPatch* self = (TerrainPatch*)  tolua_tousertype(tolua_S,1,0);
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

/* method: SetBoundingBox of class  TerrainPatch */
#ifndef TOLUA_DISABLE_tolua_Graphics_TerrainPatch_SetBoundingBox00
static int tolua_Graphics_TerrainPatch_SetBoundingBox00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TerrainPatch",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const BoundingBox",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TerrainPatch* self = (TerrainPatch*)  tolua_tousertype(tolua_S,1,0);
  const BoundingBox* box = ((const BoundingBox*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetBoundingBox'", NULL);
#endif
  {
   self->SetBoundingBox(*box);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetBoundingBox'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetCoordinates of class  TerrainPatch */
#ifndef TOLUA_DISABLE_tolua_Graphics_TerrainPatch_SetCoordinates00
static int tolua_Graphics_TerrainPatch_SetCoordinates00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TerrainPatch",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const IntVector2",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TerrainPatch* self = (TerrainPatch*)  tolua_tousertype(tolua_S,1,0);
  const IntVector2* coordinates = ((const IntVector2*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetCoordinates'", NULL);
#endif
  {
   self->SetCoordinates(*coordinates);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetCoordinates'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetOcclusionOffset of class  TerrainPatch */
#ifndef TOLUA_DISABLE_tolua_Graphics_TerrainPatch_SetOcclusionOffset00
static int tolua_Graphics_TerrainPatch_SetOcclusionOffset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TerrainPatch",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TerrainPatch* self = (TerrainPatch*)  tolua_tousertype(tolua_S,1,0);
  float offset = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetOcclusionOffset'", NULL);
#endif
  {
   self->SetOcclusionOffset(offset);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetOcclusionOffset'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: ResetLod of class  TerrainPatch */
#ifndef TOLUA_DISABLE_tolua_Graphics_TerrainPatch_ResetLod00
static int tolua_Graphics_TerrainPatch_ResetLod00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"TerrainPatch",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  TerrainPatch* self = (TerrainPatch*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ResetLod'", NULL);
#endif
  {
   self->ResetLod();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ResetLod'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetGeometry of class  TerrainPatch */
#ifndef TOLUA_DISABLE_tolua_Graphics_TerrainPatch_GetGeometry00
static int tolua_Graphics_TerrainPatch_GetGeometry00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const TerrainPatch",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const TerrainPatch* self = (const TerrainPatch*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetGeometry'", NULL);
#endif
  {
   Geometry* tolua_ret = (Geometry*)  self->GetGeometry();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Geometry");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetGeometry'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMaxLodGeometry of class  TerrainPatch */
#ifndef TOLUA_DISABLE_tolua_Graphics_TerrainPatch_GetMaxLodGeometry00
static int tolua_Graphics_TerrainPatch_GetMaxLodGeometry00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const TerrainPatch",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const TerrainPatch* self = (const TerrainPatch*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMaxLodGeometry'", NULL);
#endif
  {
   Geometry* tolua_ret = (Geometry*)  self->GetMaxLodGeometry();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Geometry");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMaxLodGeometry'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetMinLodGeometry of class  TerrainPatch */
#ifndef TOLUA_DISABLE_tolua_Graphics_TerrainPatch_GetMinLodGeometry00
static int tolua_Graphics_TerrainPatch_GetMinLodGeometry00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const TerrainPatch",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const TerrainPatch* self = (const TerrainPatch*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMinLodGeometry'", NULL);
#endif
  {
   Geometry* tolua_ret = (Geometry*)  self->GetMinLodGeometry();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Geometry");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMinLodGeometry'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetVertexBuffer of class  TerrainPatch */
#ifndef TOLUA_DISABLE_tolua_Graphics_TerrainPatch_GetVertexBuffer00
static int tolua_Graphics_TerrainPatch_GetVertexBuffer00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const TerrainPatch",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const TerrainPatch* self = (const TerrainPatch*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetVertexBuffer'", NULL);
#endif
  {
   VertexBuffer* tolua_ret = (VertexBuffer*)  self->GetVertexBuffer();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"VertexBuffer");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetVertexBuffer'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetOwner of class  TerrainPatch */
#ifndef TOLUA_DISABLE_tolua_Graphics_TerrainPatch_GetOwner00
static int tolua_Graphics_TerrainPatch_GetOwner00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const TerrainPatch",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const TerrainPatch* self = (const TerrainPatch*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetOwner'", NULL);
#endif
  {
   Terrain* tolua_ret = (Terrain*)  self->GetOwner();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Terrain");
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

/* method: GetNorthPatch of class  TerrainPatch */
#ifndef TOLUA_DISABLE_tolua_Graphics_TerrainPatch_GetNorthPatch00
static int tolua_Graphics_TerrainPatch_GetNorthPatch00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const TerrainPatch",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const TerrainPatch* self = (const TerrainPatch*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNorthPatch'", NULL);
#endif
  {
   TerrainPatch* tolua_ret = (TerrainPatch*)  self->GetNorthPatch();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"TerrainPatch");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNorthPatch'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSouthPatch of class  TerrainPatch */
#ifndef TOLUA_DISABLE_tolua_Graphics_TerrainPatch_GetSouthPatch00
static int tolua_Graphics_TerrainPatch_GetSouthPatch00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const TerrainPatch",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const TerrainPatch* self = (const TerrainPatch*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSouthPatch'", NULL);
#endif
  {
   TerrainPatch* tolua_ret = (TerrainPatch*)  self->GetSouthPatch();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"TerrainPatch");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSouthPatch'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetWestPatch of class  TerrainPatch */
#ifndef TOLUA_DISABLE_tolua_Graphics_TerrainPatch_GetWestPatch00
static int tolua_Graphics_TerrainPatch_GetWestPatch00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const TerrainPatch",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const TerrainPatch* self = (const TerrainPatch*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetWestPatch'", NULL);
#endif
  {
   TerrainPatch* tolua_ret = (TerrainPatch*)  self->GetWestPatch();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"TerrainPatch");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetWestPatch'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetEastPatch of class  TerrainPatch */
#ifndef TOLUA_DISABLE_tolua_Graphics_TerrainPatch_GetEastPatch00
static int tolua_Graphics_TerrainPatch_GetEastPatch00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const TerrainPatch",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const TerrainPatch* self = (const TerrainPatch*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetEastPatch'", NULL);
#endif
  {
   TerrainPatch* tolua_ret = (TerrainPatch*)  self->GetEastPatch();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"TerrainPatch");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetEastPatch'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetBoundingBox of class  TerrainPatch */
#ifndef TOLUA_DISABLE_tolua_Graphics_TerrainPatch_GetBoundingBox00
static int tolua_Graphics_TerrainPatch_GetBoundingBox00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const TerrainPatch",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const TerrainPatch* self = (const TerrainPatch*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetBoundingBox'", NULL);
#endif
  {
   const BoundingBox& tolua_ret = (const BoundingBox&)  self->GetBoundingBox();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const BoundingBox");
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

/* method: GetCoordinates of class  TerrainPatch */
#ifndef TOLUA_DISABLE_tolua_Graphics_TerrainPatch_GetCoordinates00
static int tolua_Graphics_TerrainPatch_GetCoordinates00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const TerrainPatch",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const TerrainPatch* self = (const TerrainPatch*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetCoordinates'", NULL);
#endif
  {
   const IntVector2& tolua_ret = (const IntVector2&)  self->GetCoordinates();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const IntVector2");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetCoordinates'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLodLevel of class  TerrainPatch */
#ifndef TOLUA_DISABLE_tolua_Graphics_TerrainPatch_GetLodLevel00
static int tolua_Graphics_TerrainPatch_GetLodLevel00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const TerrainPatch",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const TerrainPatch* self = (const TerrainPatch*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLodLevel'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetLodLevel();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLodLevel'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetOcclusionOffset of class  TerrainPatch */
#ifndef TOLUA_DISABLE_tolua_Graphics_TerrainPatch_GetOcclusionOffset00
static int tolua_Graphics_TerrainPatch_GetOcclusionOffset00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const TerrainPatch",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const TerrainPatch* self = (const TerrainPatch*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetOcclusionOffset'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetOcclusionOffset();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetOcclusionOffset'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetNumLevels of class  Texture */
#ifndef TOLUA_DISABLE_tolua_Graphics_Texture_SetNumLevels00
static int tolua_Graphics_Texture_SetNumLevels00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Texture",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Texture* self = (Texture*)  tolua_tousertype(tolua_S,1,0);
  unsigned levels = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetNumLevels'", NULL);
#endif
  {
   self->SetNumLevels(levels);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetNumLevels'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFilterMode of class  Texture */
#ifndef TOLUA_DISABLE_tolua_Graphics_Texture_SetFilterMode00
static int tolua_Graphics_Texture_SetFilterMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Texture",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Texture* self = (Texture*)  tolua_tousertype(tolua_S,1,0);
  TextureFilterMode filter = ((TextureFilterMode) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFilterMode'", NULL);
#endif
  {
   self->SetFilterMode(filter);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFilterMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetAddressMode of class  Texture */
#ifndef TOLUA_DISABLE_tolua_Graphics_Texture_SetAddressMode00
static int tolua_Graphics_Texture_SetAddressMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Texture",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Texture* self = (Texture*)  tolua_tousertype(tolua_S,1,0);
  TextureCoordinate coord = ((TextureCoordinate) (int)  tolua_tonumber(tolua_S,2,0));
  TextureAddressMode address = ((TextureAddressMode) (int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetAddressMode'", NULL);
#endif
  {
   self->SetAddressMode(coord,address);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetAddressMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetBorderColor of class  Texture */
#ifndef TOLUA_DISABLE_tolua_Graphics_Texture_SetBorderColor00
static int tolua_Graphics_Texture_SetBorderColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Texture",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Color",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Texture* self = (Texture*)  tolua_tousertype(tolua_S,1,0);
  const Color* color = ((const Color*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetBorderColor'", NULL);
#endif
  {
   self->SetBorderColor(*color);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetBorderColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetSRGB of class  Texture */
#ifndef TOLUA_DISABLE_tolua_Graphics_Texture_SetSRGB00
static int tolua_Graphics_Texture_SetSRGB00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Texture",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Texture* self = (Texture*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetSRGB'", NULL);
#endif
  {
   self->SetSRGB(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetSRGB'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetBackupTexture of class  Texture */
#ifndef TOLUA_DISABLE_tolua_Graphics_Texture_SetBackupTexture00
static int tolua_Graphics_Texture_SetBackupTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Texture",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"Texture",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Texture* self = (Texture*)  tolua_tousertype(tolua_S,1,0);
  Texture* texture = ((Texture*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetBackupTexture'", NULL);
#endif
  {
   self->SetBackupTexture(texture);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetBackupTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFormat of class  Texture */
#ifndef TOLUA_DISABLE_tolua_Graphics_Texture_GetFormat00
static int tolua_Graphics_Texture_GetFormat00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Texture",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Texture* self = (const Texture*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFormat'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetFormat();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFormat'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsCompressed of class  Texture */
#ifndef TOLUA_DISABLE_tolua_Graphics_Texture_IsCompressed00
static int tolua_Graphics_Texture_IsCompressed00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Texture",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Texture* self = (const Texture*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetLevels of class  Texture */
#ifndef TOLUA_DISABLE_tolua_Graphics_Texture_GetLevels00
static int tolua_Graphics_Texture_GetLevels00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Texture",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Texture* self = (const Texture*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLevels'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetLevels();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLevels'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetWidth of class  Texture */
#ifndef TOLUA_DISABLE_tolua_Graphics_Texture_GetWidth00
static int tolua_Graphics_Texture_GetWidth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Texture",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Texture* self = (const Texture*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetHeight of class  Texture */
#ifndef TOLUA_DISABLE_tolua_Graphics_Texture_GetHeight00
static int tolua_Graphics_Texture_GetHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Texture",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Texture* self = (const Texture*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetFilterMode of class  Texture */
#ifndef TOLUA_DISABLE_tolua_Graphics_Texture_GetFilterMode00
static int tolua_Graphics_Texture_GetFilterMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Texture",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Texture* self = (const Texture*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFilterMode'", NULL);
#endif
  {
   TextureFilterMode tolua_ret = (TextureFilterMode)  self->GetFilterMode();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFilterMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAddressMode of class  Texture */
#ifndef TOLUA_DISABLE_tolua_Graphics_Texture_GetAddressMode00
static int tolua_Graphics_Texture_GetAddressMode00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Texture",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Texture* self = (const Texture*)  tolua_tousertype(tolua_S,1,0);
  TextureCoordinate coord = ((TextureCoordinate) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAddressMode'", NULL);
#endif
  {
   TextureAddressMode tolua_ret = (TextureAddressMode)  self->GetAddressMode(coord);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAddressMode'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetBorderColor of class  Texture */
#ifndef TOLUA_DISABLE_tolua_Graphics_Texture_GetBorderColor00
static int tolua_Graphics_Texture_GetBorderColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Texture",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Texture* self = (const Texture*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetBorderColor'", NULL);
#endif
  {
   const Color& tolua_ret = (const Color&)  self->GetBorderColor();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Color");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetBorderColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetSRGB of class  Texture */
#ifndef TOLUA_DISABLE_tolua_Graphics_Texture_GetSRGB00
static int tolua_Graphics_Texture_GetSRGB00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Texture",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Texture* self = (const Texture*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetSRGB'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetSRGB();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetSRGB'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetBackupTexture of class  Texture */
#ifndef TOLUA_DISABLE_tolua_Graphics_Texture_GetBackupTexture00
static int tolua_Graphics_Texture_GetBackupTexture00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Texture",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Texture* self = (const Texture*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetBackupTexture'", NULL);
#endif
  {
   Texture* tolua_ret = (Texture*)  self->GetBackupTexture();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"Texture");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetBackupTexture'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLevelWidth of class  Texture */
#ifndef TOLUA_DISABLE_tolua_Graphics_Texture_GetLevelWidth00
static int tolua_Graphics_Texture_GetLevelWidth00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Texture",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Texture* self = (const Texture*)  tolua_tousertype(tolua_S,1,0);
  unsigned level = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLevelWidth'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetLevelWidth(level);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLevelWidth'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetLevelHeight of class  Texture */
#ifndef TOLUA_DISABLE_tolua_Graphics_Texture_GetLevelHeight00
static int tolua_Graphics_Texture_GetLevelHeight00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Texture",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Texture* self = (const Texture*)  tolua_tousertype(tolua_S,1,0);
  unsigned level = ((unsigned)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetLevelHeight'", NULL);
#endif
  {
   int tolua_ret = (int)  self->GetLevelHeight(level);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetLevelHeight'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetUsage of class  Texture */
#ifndef TOLUA_DISABLE_tolua_Graphics_Texture_GetUsage00
static int tolua_Graphics_Texture_GetUsage00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Texture",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Texture* self = (const Texture*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetUsage'", NULL);
#endif
  {
   TextureUsage tolua_ret = (TextureUsage)  self->GetUsage();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetUsage'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetDataSize of class  Texture */
#ifndef TOLUA_DISABLE_tolua_Graphics_Texture_GetDataSize00
static int tolua_Graphics_Texture_GetDataSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Texture",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Texture* self = (const Texture*)  tolua_tousertype(tolua_S,1,0);
  int width = ((int)  tolua_tonumber(tolua_S,2,0));
  int height = ((int)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetDataSize'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetDataSize(width,height);
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

/* method: GetRowDataSize of class  Texture */
#ifndef TOLUA_DISABLE_tolua_Graphics_Texture_GetRowDataSize00
static int tolua_Graphics_Texture_GetRowDataSize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Texture",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Texture* self = (const Texture*)  tolua_tousertype(tolua_S,1,0);
  int width = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRowDataSize'", NULL);
#endif
  {
   unsigned tolua_ret = (unsigned)  self->GetRowDataSize(width);
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRowDataSize'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRenderSurface of class  Texture2D */
#ifndef TOLUA_DISABLE_tolua_Graphics_Texture2D_GetRenderSurface00
static int tolua_Graphics_Texture2D_GetRenderSurface00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Texture2D",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Texture2D* self = (const Texture2D*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRenderSurface'", NULL);
#endif
  {
   RenderSurface* tolua_ret = (RenderSurface*)  self->GetRenderSurface();
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"RenderSurface");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRenderSurface'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetRenderSurface of class  TextureCube */
#ifndef TOLUA_DISABLE_tolua_Graphics_TextureCube_GetRenderSurface00
static int tolua_Graphics_TextureCube_GetRenderSurface00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const TextureCube",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const TextureCube* self = (const TextureCube*)  tolua_tousertype(tolua_S,1,0);
  CubeMapFace face = ((CubeMapFace) (int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetRenderSurface'", NULL);
#endif
  {
   RenderSurface* tolua_ret = (RenderSurface*)  self->GetRenderSurface(face);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"RenderSurface");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetRenderSurface'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetBoundingBox of class  Zone */
#ifndef TOLUA_DISABLE_tolua_Graphics_Zone_SetBoundingBox00
static int tolua_Graphics_Zone_SetBoundingBox00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Zone",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const BoundingBox",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Zone* self = (Zone*)  tolua_tousertype(tolua_S,1,0);
  const BoundingBox* box = ((const BoundingBox*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetBoundingBox'", NULL);
#endif
  {
   self->SetBoundingBox(*box);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetBoundingBox'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetAmbientColor of class  Zone */
#ifndef TOLUA_DISABLE_tolua_Graphics_Zone_SetAmbientColor00
static int tolua_Graphics_Zone_SetAmbientColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Zone",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Color",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Zone* self = (Zone*)  tolua_tousertype(tolua_S,1,0);
  const Color* color = ((const Color*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetAmbientColor'", NULL);
#endif
  {
   self->SetAmbientColor(*color);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetAmbientColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFogColor of class  Zone */
#ifndef TOLUA_DISABLE_tolua_Graphics_Zone_SetFogColor00
static int tolua_Graphics_Zone_SetFogColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Zone",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Color",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Zone* self = (Zone*)  tolua_tousertype(tolua_S,1,0);
  const Color* color = ((const Color*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFogColor'", NULL);
#endif
  {
   self->SetFogColor(*color);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFogColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFogStart of class  Zone */
#ifndef TOLUA_DISABLE_tolua_Graphics_Zone_SetFogStart00
static int tolua_Graphics_Zone_SetFogStart00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Zone",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Zone* self = (Zone*)  tolua_tousertype(tolua_S,1,0);
  float start = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFogStart'", NULL);
#endif
  {
   self->SetFogStart(start);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFogStart'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetFogEnd of class  Zone */
#ifndef TOLUA_DISABLE_tolua_Graphics_Zone_SetFogEnd00
static int tolua_Graphics_Zone_SetFogEnd00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Zone",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Zone* self = (Zone*)  tolua_tousertype(tolua_S,1,0);
  float end = ((float)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetFogEnd'", NULL);
#endif
  {
   self->SetFogEnd(end);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetFogEnd'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetPriority of class  Zone */
#ifndef TOLUA_DISABLE_tolua_Graphics_Zone_SetPriority00
static int tolua_Graphics_Zone_SetPriority00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Zone",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Zone* self = (Zone*)  tolua_tousertype(tolua_S,1,0);
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

/* method: SetOverride of class  Zone */
#ifndef TOLUA_DISABLE_tolua_Graphics_Zone_SetOverride00
static int tolua_Graphics_Zone_SetOverride00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Zone",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Zone* self = (Zone*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetOverride'", NULL);
#endif
  {
   self->SetOverride(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetOverride'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: SetAmbientGradient of class  Zone */
#ifndef TOLUA_DISABLE_tolua_Graphics_Zone_SetAmbientGradient00
static int tolua_Graphics_Zone_SetAmbientGradient00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Zone",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Zone* self = (Zone*)  tolua_tousertype(tolua_S,1,0);
  bool enable = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetAmbientGradient'", NULL);
#endif
  {
   self->SetAmbientGradient(enable);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetAmbientGradient'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetBoundingBox of class  Zone */
#ifndef TOLUA_DISABLE_tolua_Graphics_Zone_GetBoundingBox00
static int tolua_Graphics_Zone_GetBoundingBox00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Zone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Zone* self = (const Zone*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetBoundingBox'", NULL);
#endif
  {
   const BoundingBox& tolua_ret = (const BoundingBox&)  self->GetBoundingBox();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const BoundingBox");
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

/* method: GetInverseWorldTransform of class  Zone */
#ifndef TOLUA_DISABLE_tolua_Graphics_Zone_GetInverseWorldTransform00
static int tolua_Graphics_Zone_GetInverseWorldTransform00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Zone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Zone* self = (const Zone*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetInverseWorldTransform'", NULL);
#endif
  {
   const Matrix3x4& tolua_ret = (const Matrix3x4&)  self->GetInverseWorldTransform();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Matrix3x4");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetInverseWorldTransform'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAmbientColor of class  Zone */
#ifndef TOLUA_DISABLE_tolua_Graphics_Zone_GetAmbientColor00
static int tolua_Graphics_Zone_GetAmbientColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Zone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Zone* self = (const Zone*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAmbientColor'", NULL);
#endif
  {
   const Color& tolua_ret = (const Color&)  self->GetAmbientColor();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Color");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAmbientColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAmbientStartColor of class  Zone */
#ifndef TOLUA_DISABLE_tolua_Graphics_Zone_GetAmbientStartColor00
static int tolua_Graphics_Zone_GetAmbientStartColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Zone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Zone* self = (Zone*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAmbientStartColor'", NULL);
#endif
  {
   const Color& tolua_ret = (const Color&)  self->GetAmbientStartColor();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Color");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAmbientStartColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAmbientEndColor of class  Zone */
#ifndef TOLUA_DISABLE_tolua_Graphics_Zone_GetAmbientEndColor00
static int tolua_Graphics_Zone_GetAmbientEndColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"Zone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  Zone* self = (Zone*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAmbientEndColor'", NULL);
#endif
  {
   const Color& tolua_ret = (const Color&)  self->GetAmbientEndColor();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Color");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAmbientEndColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFogColor of class  Zone */
#ifndef TOLUA_DISABLE_tolua_Graphics_Zone_GetFogColor00
static int tolua_Graphics_Zone_GetFogColor00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Zone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Zone* self = (const Zone*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFogColor'", NULL);
#endif
  {
   const Color& tolua_ret = (const Color&)  self->GetFogColor();
    tolua_pushusertype(tolua_S,(void*)&tolua_ret,"const Color");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFogColor'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFogStart of class  Zone */
#ifndef TOLUA_DISABLE_tolua_Graphics_Zone_GetFogStart00
static int tolua_Graphics_Zone_GetFogStart00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Zone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Zone* self = (const Zone*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFogStart'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetFogStart();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFogStart'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetFogEnd of class  Zone */
#ifndef TOLUA_DISABLE_tolua_Graphics_Zone_GetFogEnd00
static int tolua_Graphics_Zone_GetFogEnd00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Zone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Zone* self = (const Zone*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetFogEnd'", NULL);
#endif
  {
   float tolua_ret = (float)  self->GetFogEnd();
   tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetFogEnd'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetPriority of class  Zone */
#ifndef TOLUA_DISABLE_tolua_Graphics_Zone_GetPriority00
static int tolua_Graphics_Zone_GetPriority00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Zone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Zone* self = (const Zone*)  tolua_tousertype(tolua_S,1,0);
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

/* method: GetOverride of class  Zone */
#ifndef TOLUA_DISABLE_tolua_Graphics_Zone_GetOverride00
static int tolua_Graphics_Zone_GetOverride00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Zone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Zone* self = (const Zone*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetOverride'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetOverride();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetOverride'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: GetAmbientGradient of class  Zone */
#ifndef TOLUA_DISABLE_tolua_Graphics_Zone_GetAmbientGradient00
static int tolua_Graphics_Zone_GetAmbientGradient00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Zone",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Zone* self = (const Zone*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAmbientGradient'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->GetAmbientGradient();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAmbientGradient'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: IsInside of class  Zone */
#ifndef TOLUA_DISABLE_tolua_Graphics_Zone_IsInside00
static int tolua_Graphics_Zone_IsInside00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"const Zone",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"const Vector3",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const Zone* self = (const Zone*)  tolua_tousertype(tolua_S,1,0);
  const Vector3* point = ((const Vector3*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsInside'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->IsInside(*point);
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

/* Open function */
TOLUA_API int tolua_Graphics_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,1);
 tolua_beginmodule(tolua_S,NULL);
  tolua_cclass(tolua_S,"AnimatedModel","AnimatedModel","StaticModel",NULL);
  tolua_beginmodule(tolua_S,"AnimatedModel");
   tolua_function(tolua_S,"SetModel",tolua_Graphics_AnimatedModel_SetModel00);
   tolua_function(tolua_S,"AddAnimationState",tolua_Graphics_AnimatedModel_AddAnimationState00);
   tolua_function(tolua_S,"RemoveAnimationState",tolua_Graphics_AnimatedModel_RemoveAnimationState00);
   tolua_function(tolua_S,"RemoveAnimationState",tolua_Graphics_AnimatedModel_RemoveAnimationState01);
   tolua_function(tolua_S,"RemoveAnimationState",tolua_Graphics_AnimatedModel_RemoveAnimationState02);
   tolua_function(tolua_S,"RemoveAnimationState",tolua_Graphics_AnimatedModel_RemoveAnimationState03);
   tolua_function(tolua_S,"RemoveAnimationState",tolua_Graphics_AnimatedModel_RemoveAnimationState04);
   tolua_function(tolua_S,"RemoveAllAnimationStates",tolua_Graphics_AnimatedModel_RemoveAllAnimationStates00);
   tolua_function(tolua_S,"SetAnimationLodBias",tolua_Graphics_AnimatedModel_SetAnimationLodBias00);
   tolua_function(tolua_S,"SetInvisibleLodFactor",tolua_Graphics_AnimatedModel_SetInvisibleLodFactor00);
   tolua_function(tolua_S,"SetMorphWeight",tolua_Graphics_AnimatedModel_SetMorphWeight00);
   tolua_function(tolua_S,"SetMorphWeight",tolua_Graphics_AnimatedModel_SetMorphWeight01);
   tolua_function(tolua_S,"SetMorphWeight",tolua_Graphics_AnimatedModel_SetMorphWeight02);
   tolua_function(tolua_S,"ResetMorphWeights",tolua_Graphics_AnimatedModel_ResetMorphWeights00);
   tolua_function(tolua_S,"GetSkeleton",tolua_Graphics_AnimatedModel_GetSkeleton00);
   tolua_function(tolua_S,"GetNumAnimationStates",tolua_Graphics_AnimatedModel_GetNumAnimationStates00);
   tolua_function(tolua_S,"GetAnimationState",tolua_Graphics_AnimatedModel_GetAnimationState00);
   tolua_function(tolua_S,"GetAnimationState",tolua_Graphics_AnimatedModel_GetAnimationState01);
   tolua_function(tolua_S,"GetAnimationState",tolua_Graphics_AnimatedModel_GetAnimationState02);
   tolua_function(tolua_S,"GetAnimationState",tolua_Graphics_AnimatedModel_GetAnimationState03);
   tolua_function(tolua_S,"GetAnimationState",tolua_Graphics_AnimatedModel_GetAnimationState04);
   tolua_function(tolua_S,"GetAnimationLodBias",tolua_Graphics_AnimatedModel_GetAnimationLodBias00);
   tolua_function(tolua_S,"GetInvisibleLodFactor",tolua_Graphics_AnimatedModel_GetInvisibleLodFactor00);
   tolua_function(tolua_S,"GetNumMorphs",tolua_Graphics_AnimatedModel_GetNumMorphs00);
   tolua_function(tolua_S,"GetMorphWeight",tolua_Graphics_AnimatedModel_GetMorphWeight00);
   tolua_function(tolua_S,"GetMorphWeight",tolua_Graphics_AnimatedModel_GetMorphWeight01);
   tolua_function(tolua_S,"GetMorphWeight",tolua_Graphics_AnimatedModel_GetMorphWeight02);
   tolua_function(tolua_S,"IsMaster",tolua_Graphics_AnimatedModel_IsMaster00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Animation","Animation","Resource",NULL);
  tolua_beginmodule(tolua_S,"Animation");
   tolua_function(tolua_S,"GetAnimationName",tolua_Graphics_Animation_GetAnimationName00);
   tolua_function(tolua_S,"GetAnimationNameHash",tolua_Graphics_Animation_GetAnimationNameHash00);
   tolua_function(tolua_S,"GetLength",tolua_Graphics_Animation_GetLength00);
   tolua_function(tolua_S,"GetNumTracks",tolua_Graphics_Animation_GetNumTracks00);
   tolua_function(tolua_S,"GetTrack",tolua_Graphics_Animation_GetTrack00);
   tolua_function(tolua_S,"GetTrack",tolua_Graphics_Animation_GetTrack01);
   tolua_function(tolua_S,"GetTrack",tolua_Graphics_Animation_GetTrack02);
   tolua_function(tolua_S,"GetNumTriggers",tolua_Graphics_Animation_GetNumTriggers00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"AnimationController","AnimationController","Component",NULL);
  tolua_beginmodule(tolua_S,"AnimationController");
   tolua_function(tolua_S,"Play",tolua_Graphics_AnimationController_Play00);
   tolua_function(tolua_S,"PlayExclusive",tolua_Graphics_AnimationController_PlayExclusive00);
   tolua_function(tolua_S,"Stop",tolua_Graphics_AnimationController_Stop00);
   tolua_function(tolua_S,"StopLayer",tolua_Graphics_AnimationController_StopLayer00);
   tolua_function(tolua_S,"StopAll",tolua_Graphics_AnimationController_StopAll00);
   tolua_function(tolua_S,"Fade",tolua_Graphics_AnimationController_Fade00);
   tolua_function(tolua_S,"FadeOthers",tolua_Graphics_AnimationController_FadeOthers00);
   tolua_function(tolua_S,"SetLayer",tolua_Graphics_AnimationController_SetLayer00);
   tolua_function(tolua_S,"SetStartBone",tolua_Graphics_AnimationController_SetStartBone00);
   tolua_function(tolua_S,"SetTime",tolua_Graphics_AnimationController_SetTime00);
   tolua_function(tolua_S,"SetWeight",tolua_Graphics_AnimationController_SetWeight00);
   tolua_function(tolua_S,"SetLooped",tolua_Graphics_AnimationController_SetLooped00);
   tolua_function(tolua_S,"SetSpeed",tolua_Graphics_AnimationController_SetSpeed00);
   tolua_function(tolua_S,"SetAutoFade",tolua_Graphics_AnimationController_SetAutoFade00);
   tolua_function(tolua_S,"IsPlaying",tolua_Graphics_AnimationController_IsPlaying00);
   tolua_function(tolua_S,"IsFadingIn",tolua_Graphics_AnimationController_IsFadingIn00);
   tolua_function(tolua_S,"IsFadingOut",tolua_Graphics_AnimationController_IsFadingOut00);
   tolua_function(tolua_S,"GetLayer",tolua_Graphics_AnimationController_GetLayer00);
   tolua_function(tolua_S,"GetStartBone",tolua_Graphics_AnimationController_GetStartBone00);
   tolua_function(tolua_S,"GetStartBoneName",tolua_Graphics_AnimationController_GetStartBoneName00);
   tolua_function(tolua_S,"GetTime",tolua_Graphics_AnimationController_GetTime00);
   tolua_function(tolua_S,"GetWeight",tolua_Graphics_AnimationController_GetWeight00);
   tolua_function(tolua_S,"IsLooped",tolua_Graphics_AnimationController_IsLooped00);
   tolua_function(tolua_S,"GetLength",tolua_Graphics_AnimationController_GetLength00);
   tolua_function(tolua_S,"GetSpeed",tolua_Graphics_AnimationController_GetSpeed00);
   tolua_function(tolua_S,"GetFadeTarget",tolua_Graphics_AnimationController_GetFadeTarget00);
   tolua_function(tolua_S,"GetFadeTime",tolua_Graphics_AnimationController_GetFadeTime00);
   tolua_function(tolua_S,"GetAutoFade",tolua_Graphics_AnimationController_GetAutoFade00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"AnimationState","AnimationState","",tolua_collect_AnimationState);
  #else
  tolua_cclass(tolua_S,"AnimationState","AnimationState","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"AnimationState");
   tolua_function(tolua_S,"new",tolua_Graphics_AnimationState_new00);
   tolua_function(tolua_S,"new_local",tolua_Graphics_AnimationState_new00_local);
   tolua_function(tolua_S,".call",tolua_Graphics_AnimationState_new00_local);
   tolua_function(tolua_S,"new",tolua_Graphics_AnimationState_new01);
   tolua_function(tolua_S,"new_local",tolua_Graphics_AnimationState_new01_local);
   tolua_function(tolua_S,".call",tolua_Graphics_AnimationState_new01_local);
   tolua_function(tolua_S,"delete",tolua_Graphics_AnimationState_delete00);
   tolua_function(tolua_S,"SetStartBone",tolua_Graphics_AnimationState_SetStartBone00);
   tolua_function(tolua_S,"SetLooped",tolua_Graphics_AnimationState_SetLooped00);
   tolua_function(tolua_S,"SetWeight",tolua_Graphics_AnimationState_SetWeight00);
   tolua_function(tolua_S,"SetTime",tolua_Graphics_AnimationState_SetTime00);
   tolua_function(tolua_S,"AddWeight",tolua_Graphics_AnimationState_AddWeight00);
   tolua_function(tolua_S,"AddTime",tolua_Graphics_AnimationState_AddTime00);
   tolua_function(tolua_S,"SetLayer",tolua_Graphics_AnimationState_SetLayer00);
   tolua_function(tolua_S,"GetAnimation",tolua_Graphics_AnimationState_GetAnimation00);
   tolua_function(tolua_S,"GetStartBone",tolua_Graphics_AnimationState_GetStartBone00);
   tolua_function(tolua_S,"IsEnabled",tolua_Graphics_AnimationState_IsEnabled00);
   tolua_function(tolua_S,"IsLooped",tolua_Graphics_AnimationState_IsLooped00);
   tolua_function(tolua_S,"GetWeight",tolua_Graphics_AnimationState_GetWeight00);
   tolua_function(tolua_S,"GetTime",tolua_Graphics_AnimationState_GetTime00);
   tolua_function(tolua_S,"GetLength",tolua_Graphics_AnimationState_GetLength00);
   tolua_function(tolua_S,"GetLayer",tolua_Graphics_AnimationState_GetLayer00);
   tolua_function(tolua_S,"Apply",tolua_Graphics_AnimationState_Apply00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"BillboardSet","BillboardSet","Drawable",NULL);
  tolua_beginmodule(tolua_S,"BillboardSet");
   tolua_function(tolua_S,"SetMaterial",tolua_Graphics_BillboardSet_SetMaterial00);
   tolua_function(tolua_S,"SetNumBillboards",tolua_Graphics_BillboardSet_SetNumBillboards00);
   tolua_function(tolua_S,"SetRelative",tolua_Graphics_BillboardSet_SetRelative00);
   tolua_function(tolua_S,"SetScaled",tolua_Graphics_BillboardSet_SetScaled00);
   tolua_function(tolua_S,"SetSorted",tolua_Graphics_BillboardSet_SetSorted00);
   tolua_function(tolua_S,"SetAnimationLodBias",tolua_Graphics_BillboardSet_SetAnimationLodBias00);
   tolua_function(tolua_S,"Commit",tolua_Graphics_BillboardSet_Commit00);
   tolua_function(tolua_S,"GetMaterial",tolua_Graphics_BillboardSet_GetMaterial00);
   tolua_function(tolua_S,"GetNumBillboards",tolua_Graphics_BillboardSet_GetNumBillboards00);
   tolua_function(tolua_S,"IsRelative",tolua_Graphics_BillboardSet_IsRelative00);
   tolua_function(tolua_S,"IsScaled",tolua_Graphics_BillboardSet_IsScaled00);
   tolua_function(tolua_S,"IsSorted",tolua_Graphics_BillboardSet_IsSorted00);
   tolua_function(tolua_S,"GetAnimationLodBias",tolua_Graphics_BillboardSet_GetAnimationLodBias00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Camera","Camera","Component",NULL);
  tolua_beginmodule(tolua_S,"Camera");
   tolua_function(tolua_S,"SetNearClip",tolua_Graphics_Camera_SetNearClip00);
   tolua_function(tolua_S,"SetFarClip",tolua_Graphics_Camera_SetFarClip00);
   tolua_function(tolua_S,"SetFov",tolua_Graphics_Camera_SetFov00);
   tolua_function(tolua_S,"SetOrthoSize",tolua_Graphics_Camera_SetOrthoSize00);
   tolua_function(tolua_S,"SetOrthoSize",tolua_Graphics_Camera_SetOrthoSize01);
   tolua_function(tolua_S,"SetAspectRatio",tolua_Graphics_Camera_SetAspectRatio00);
   tolua_function(tolua_S,"SetFillMode",tolua_Graphics_Camera_SetFillMode00);
   tolua_function(tolua_S,"SetZoom",tolua_Graphics_Camera_SetZoom00);
   tolua_function(tolua_S,"SetLodBias",tolua_Graphics_Camera_SetLodBias00);
   tolua_function(tolua_S,"SetViewMask",tolua_Graphics_Camera_SetViewMask00);
   tolua_function(tolua_S,"SetViewOverrideFlags",tolua_Graphics_Camera_SetViewOverrideFlags00);
   tolua_function(tolua_S,"SetOrthographic",tolua_Graphics_Camera_SetOrthographic00);
   tolua_function(tolua_S,"SetAutoAspectRatio",tolua_Graphics_Camera_SetAutoAspectRatio00);
   tolua_function(tolua_S,"SetProjectionOffset",tolua_Graphics_Camera_SetProjectionOffset00);
   tolua_function(tolua_S,"SetFlipVertical",tolua_Graphics_Camera_SetFlipVertical00);
   tolua_function(tolua_S,"GetFarClip",tolua_Graphics_Camera_GetFarClip00);
   tolua_function(tolua_S,"GetNearClip",tolua_Graphics_Camera_GetNearClip00);
   tolua_function(tolua_S,"GetFov",tolua_Graphics_Camera_GetFov00);
   tolua_function(tolua_S,"GetOrthoSize",tolua_Graphics_Camera_GetOrthoSize00);
   tolua_function(tolua_S,"GetAspectRatio",tolua_Graphics_Camera_GetAspectRatio00);
   tolua_function(tolua_S,"GetZoom",tolua_Graphics_Camera_GetZoom00);
   tolua_function(tolua_S,"GetLodBias",tolua_Graphics_Camera_GetLodBias00);
   tolua_function(tolua_S,"GetViewMask",tolua_Graphics_Camera_GetViewMask00);
   tolua_function(tolua_S,"GetViewOverrideFlags",tolua_Graphics_Camera_GetViewOverrideFlags00);
   tolua_function(tolua_S,"GetFillMode",tolua_Graphics_Camera_GetFillMode00);
   tolua_function(tolua_S,"IsOrthographic",tolua_Graphics_Camera_IsOrthographic00);
   tolua_function(tolua_S,"GetAutoAspectRatio",tolua_Graphics_Camera_GetAutoAspectRatio00);
   tolua_function(tolua_S,"GetFrustum",tolua_Graphics_Camera_GetFrustum00);
   tolua_function(tolua_S,"GetProjection",tolua_Graphics_Camera_GetProjection00);
   tolua_function(tolua_S,"GetProjection",tolua_Graphics_Camera_GetProjection01);
   tolua_function(tolua_S,"GetView",tolua_Graphics_Camera_GetView00);
   tolua_function(tolua_S,"GetFrustumSize",tolua_Graphics_Camera_GetFrustumSize00);
   tolua_function(tolua_S,"GetHalfViewSize",tolua_Graphics_Camera_GetHalfViewSize00);
   tolua_function(tolua_S,"GetSplitFrustum",tolua_Graphics_Camera_GetSplitFrustum00);
   tolua_function(tolua_S,"GetViewSpaceFrustum",tolua_Graphics_Camera_GetViewSpaceFrustum00);
   tolua_function(tolua_S,"GetViewSpaceSplitFrustum",tolua_Graphics_Camera_GetViewSpaceSplitFrustum00);
   tolua_function(tolua_S,"GetScreenRay",tolua_Graphics_Camera_GetScreenRay00);
   tolua_function(tolua_S,"WorldToScreenPoint",tolua_Graphics_Camera_WorldToScreenPoint00);
   tolua_function(tolua_S,"ScreenToWorldPoint",tolua_Graphics_Camera_ScreenToWorldPoint00);
   tolua_function(tolua_S,"GetForwardVector",tolua_Graphics_Camera_GetForwardVector00);
   tolua_function(tolua_S,"GetRightVector",tolua_Graphics_Camera_GetRightVector00);
   tolua_function(tolua_S,"GetUpVector",tolua_Graphics_Camera_GetUpVector00);
   tolua_function(tolua_S,"GetProjectionOffset",tolua_Graphics_Camera_GetProjectionOffset00);
   tolua_function(tolua_S,"GetFlipVertical",tolua_Graphics_Camera_GetFlipVertical00);
   tolua_function(tolua_S,"GetDistance",tolua_Graphics_Camera_GetDistance00);
   tolua_function(tolua_S,"GetDistanceSquared",tolua_Graphics_Camera_GetDistanceSquared00);
   tolua_function(tolua_S,"GetLodDistance",tolua_Graphics_Camera_GetLodDistance00);
   tolua_function(tolua_S,"IsProjectionValid",tolua_Graphics_Camera_IsProjectionValid00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"DebugRenderer","DebugRenderer","Component",NULL);
  tolua_beginmodule(tolua_S,"DebugRenderer");
   tolua_function(tolua_S,"AddLine",tolua_Graphics_DebugRenderer_AddLine00);
   tolua_function(tolua_S,"AddLine",tolua_Graphics_DebugRenderer_AddLine01);
   tolua_function(tolua_S,"AddNode",tolua_Graphics_DebugRenderer_AddNode00);
   tolua_function(tolua_S,"AddBoundingBox",tolua_Graphics_DebugRenderer_AddBoundingBox00);
   tolua_function(tolua_S,"AddBoundingBox",tolua_Graphics_DebugRenderer_AddBoundingBox01);
   tolua_function(tolua_S,"AddFrustum",tolua_Graphics_DebugRenderer_AddFrustum00);
   tolua_function(tolua_S,"AddPolyhedron",tolua_Graphics_DebugRenderer_AddPolyhedron00);
   tolua_function(tolua_S,"AddSphere",tolua_Graphics_DebugRenderer_AddSphere00);
   tolua_function(tolua_S,"AddSkeleton",tolua_Graphics_DebugRenderer_AddSkeleton00);
  tolua_endmodule(tolua_S);
  tolua_function(tolua_S,"GetDebugRenderer",tolua_Graphics_GetDebugRenderer00);
  tolua_cclass(tolua_S,"DecalSet","DecalSet","Drawable",NULL);
  tolua_beginmodule(tolua_S,"DecalSet");
   tolua_function(tolua_S,"SetMaterial",tolua_Graphics_DecalSet_SetMaterial00);
   tolua_function(tolua_S,"SetMaxVertices",tolua_Graphics_DecalSet_SetMaxVertices00);
   tolua_function(tolua_S,"SetMaxIndices",tolua_Graphics_DecalSet_SetMaxIndices00);
   tolua_function(tolua_S,"AddDecal",tolua_Graphics_DecalSet_AddDecal00);
   tolua_function(tolua_S,"RemoveDecals",tolua_Graphics_DecalSet_RemoveDecals00);
   tolua_function(tolua_S,"RemoveAllDecals",tolua_Graphics_DecalSet_RemoveAllDecals00);
   tolua_function(tolua_S,"GetMaterial",tolua_Graphics_DecalSet_GetMaterial00);
   tolua_function(tolua_S,"GetNumDecals",tolua_Graphics_DecalSet_GetNumDecals00);
   tolua_function(tolua_S,"GetNumVertices",tolua_Graphics_DecalSet_GetNumVertices00);
   tolua_function(tolua_S,"GetNumIndices",tolua_Graphics_DecalSet_GetNumIndices00);
   tolua_function(tolua_S,"GetMaxVertices",tolua_Graphics_DecalSet_GetMaxVertices00);
   tolua_function(tolua_S,"GetMaxIndices",tolua_Graphics_DecalSet_GetMaxIndices00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Drawable","Drawable","Component",NULL);
  tolua_beginmodule(tolua_S,"Drawable");
   tolua_function(tolua_S,"SetDrawDistance",tolua_Graphics_Drawable_SetDrawDistance00);
   tolua_function(tolua_S,"SetShadowDistance",tolua_Graphics_Drawable_SetShadowDistance00);
   tolua_function(tolua_S,"SetLodBias",tolua_Graphics_Drawable_SetLodBias00);
   tolua_function(tolua_S,"SetViewMask",tolua_Graphics_Drawable_SetViewMask00);
   tolua_function(tolua_S,"SetLightMask",tolua_Graphics_Drawable_SetLightMask00);
   tolua_function(tolua_S,"SetShadowMask",tolua_Graphics_Drawable_SetShadowMask00);
   tolua_function(tolua_S,"SetZoneMask",tolua_Graphics_Drawable_SetZoneMask00);
   tolua_function(tolua_S,"SetMaxLights",tolua_Graphics_Drawable_SetMaxLights00);
   tolua_function(tolua_S,"SetCastShadows",tolua_Graphics_Drawable_SetCastShadows00);
   tolua_function(tolua_S,"SetOccluder",tolua_Graphics_Drawable_SetOccluder00);
   tolua_function(tolua_S,"SetOccludee",tolua_Graphics_Drawable_SetOccludee00);
   tolua_function(tolua_S,"MarkForUpdate",tolua_Graphics_Drawable_MarkForUpdate00);
   tolua_function(tolua_S,"GetWorldBoundingBox",tolua_Graphics_Drawable_GetWorldBoundingBox00);
   tolua_function(tolua_S,"GetDrawableFlags",tolua_Graphics_Drawable_GetDrawableFlags00);
   tolua_function(tolua_S,"GetDrawDistance",tolua_Graphics_Drawable_GetDrawDistance00);
   tolua_function(tolua_S,"GetShadowDistance",tolua_Graphics_Drawable_GetShadowDistance00);
   tolua_function(tolua_S,"GetLodBias",tolua_Graphics_Drawable_GetLodBias00);
   tolua_function(tolua_S,"GetViewMask",tolua_Graphics_Drawable_GetViewMask00);
   tolua_function(tolua_S,"GetLightMask",tolua_Graphics_Drawable_GetLightMask00);
   tolua_function(tolua_S,"GetShadowMask",tolua_Graphics_Drawable_GetShadowMask00);
   tolua_function(tolua_S,"GetZoneMask",tolua_Graphics_Drawable_GetZoneMask00);
   tolua_function(tolua_S,"GetMaxLights",tolua_Graphics_Drawable_GetMaxLights00);
   tolua_function(tolua_S,"GetCastShadows",tolua_Graphics_Drawable_GetCastShadows00);
   tolua_function(tolua_S,"IsOccluder",tolua_Graphics_Drawable_IsOccluder00);
   tolua_function(tolua_S,"IsOccludee",tolua_Graphics_Drawable_IsOccludee00);
   tolua_function(tolua_S,"SetZone",tolua_Graphics_Drawable_SetZone00);
   tolua_function(tolua_S,"SetSortValue",tolua_Graphics_Drawable_SetSortValue00);
   tolua_function(tolua_S,"SetMinMaxZ",tolua_Graphics_Drawable_SetMinMaxZ00);
   tolua_function(tolua_S,"MarkInView",tolua_Graphics_Drawable_MarkInView00);
   tolua_function(tolua_S,"ClearLights",tolua_Graphics_Drawable_ClearLights00);
   tolua_function(tolua_S,"AddLight",tolua_Graphics_Drawable_AddLight00);
   tolua_function(tolua_S,"AddVertexLight",tolua_Graphics_Drawable_AddVertexLight00);
   tolua_function(tolua_S,"LimitLights",tolua_Graphics_Drawable_LimitLights00);
   tolua_function(tolua_S,"LimitVertexLights",tolua_Graphics_Drawable_LimitVertexLights00);
   tolua_function(tolua_S,"SetBasePass",tolua_Graphics_Drawable_SetBasePass00);
   tolua_function(tolua_S,"GetOctant",tolua_Graphics_Drawable_GetOctant00);
   tolua_function(tolua_S,"GetZone",tolua_Graphics_Drawable_GetZone00);
   tolua_function(tolua_S,"GetLastZone",tolua_Graphics_Drawable_GetLastZone00);
   tolua_function(tolua_S,"IsZoneDirty",tolua_Graphics_Drawable_IsZoneDirty00);
   tolua_function(tolua_S,"GetDistance",tolua_Graphics_Drawable_GetDistance00);
   tolua_function(tolua_S,"GetLodDistance",tolua_Graphics_Drawable_GetLodDistance00);
   tolua_function(tolua_S,"GetSortValue",tolua_Graphics_Drawable_GetSortValue00);
   tolua_function(tolua_S,"IsInView",tolua_Graphics_Drawable_IsInView00);
   tolua_function(tolua_S,"IsInView",tolua_Graphics_Drawable_IsInView01);
   tolua_function(tolua_S,"HasBasePass",tolua_Graphics_Drawable_HasBasePass00);
   tolua_function(tolua_S,"GetFirstLight",tolua_Graphics_Drawable_GetFirstLight00);
   tolua_function(tolua_S,"GetMinZ",tolua_Graphics_Drawable_GetMinZ00);
   tolua_function(tolua_S,"GetMaxZ",tolua_Graphics_Drawable_GetMaxZ00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Graphics","Graphics","Object",NULL);
  tolua_beginmodule(tolua_S,"Graphics");
   tolua_function(tolua_S,"SetWindowTitle",tolua_Graphics_Graphics_SetWindowTitle00);
   tolua_function(tolua_S,"SetSRGB",tolua_Graphics_Graphics_SetSRGB00);
   tolua_function(tolua_S,"ToggleFullscreen",tolua_Graphics_Graphics_ToggleFullscreen00);
   tolua_function(tolua_S,"TakeScreenShot",tolua_Graphics_Graphics_TakeScreenShot00);
   tolua_function(tolua_S,"IsInitialized",tolua_Graphics_Graphics_IsInitialized00);
   tolua_function(tolua_S,"GetWidth",tolua_Graphics_Graphics_GetWidth00);
   tolua_function(tolua_S,"GetHeight",tolua_Graphics_Graphics_GetHeight00);
   tolua_function(tolua_S,"GetMultiSample",tolua_Graphics_Graphics_GetMultiSample00);
   tolua_function(tolua_S,"GetFullscreen",tolua_Graphics_Graphics_GetFullscreen00);
   tolua_function(tolua_S,"GetResizable",tolua_Graphics_Graphics_GetResizable00);
   tolua_function(tolua_S,"GetVSync",tolua_Graphics_Graphics_GetVSync00);
   tolua_function(tolua_S,"GetTripleBuffer",tolua_Graphics_Graphics_GetTripleBuffer00);
   tolua_function(tolua_S,"GetSRGB",tolua_Graphics_Graphics_GetSRGB00);
  tolua_endmodule(tolua_S);
  tolua_function(tolua_S,"GetGraphics",tolua_Graphics_GetGraphics00);
  tolua_constant(tolua_S,"RENDER_FORWARD",RENDER_FORWARD);
  tolua_constant(tolua_S,"RENDER_PREPASS",RENDER_PREPASS);
  tolua_constant(tolua_S,"RENDER_DEFERRED",RENDER_DEFERRED);
  tolua_constant(tolua_S,"TRIANGLE_LIST",TRIANGLE_LIST);
  tolua_constant(tolua_S,"LINE_LIST",LINE_LIST);
  tolua_constant(tolua_S,"GEOM_STATIC",GEOM_STATIC);
  tolua_constant(tolua_S,"GEOM_SKINNED",GEOM_SKINNED);
  tolua_constant(tolua_S,"GEOM_INSTANCED",GEOM_INSTANCED);
  tolua_constant(tolua_S,"GEOM_BILLBOARD",GEOM_BILLBOARD);
  tolua_constant(tolua_S,"GEOM_STATIC_NOINSTANCING",GEOM_STATIC_NOINSTANCING);
  tolua_constant(tolua_S,"MAX_GEOMETRYTYPES",MAX_GEOMETRYTYPES);
  tolua_constant(tolua_S,"BLEND_REPLACE",BLEND_REPLACE);
  tolua_constant(tolua_S,"BLEND_ADD",BLEND_ADD);
  tolua_constant(tolua_S,"BLEND_MULTIPLY",BLEND_MULTIPLY);
  tolua_constant(tolua_S,"BLEND_ALPHA",BLEND_ALPHA);
  tolua_constant(tolua_S,"BLEND_ADDALPHA",BLEND_ADDALPHA);
  tolua_constant(tolua_S,"BLEND_PREMULALPHA",BLEND_PREMULALPHA);
  tolua_constant(tolua_S,"BLEND_INVDESTALPHA",BLEND_INVDESTALPHA);
  tolua_constant(tolua_S,"MAX_BLENDMODES",MAX_BLENDMODES);
  tolua_constant(tolua_S,"CMP_ALWAYS",CMP_ALWAYS);
  tolua_constant(tolua_S,"CMP_EQUAL",CMP_EQUAL);
  tolua_constant(tolua_S,"CMP_NOTEQUAL",CMP_NOTEQUAL);
  tolua_constant(tolua_S,"CMP_LESS",CMP_LESS);
  tolua_constant(tolua_S,"CMP_LESSEQUAL",CMP_LESSEQUAL);
  tolua_constant(tolua_S,"CMP_GREATER",CMP_GREATER);
  tolua_constant(tolua_S,"CMP_GREATEREQUAL",CMP_GREATEREQUAL);
  tolua_constant(tolua_S,"MAX_COMPAREMODES",MAX_COMPAREMODES);
  tolua_constant(tolua_S,"CULL_NONE",CULL_NONE);
  tolua_constant(tolua_S,"CULL_CCW",CULL_CCW);
  tolua_constant(tolua_S,"CULL_CW",CULL_CW);
  tolua_constant(tolua_S,"MAX_CULLMODES",MAX_CULLMODES);
  tolua_constant(tolua_S,"FILL_SOLID",FILL_SOLID);
  tolua_constant(tolua_S,"FILL_WIREFRAME",FILL_WIREFRAME);
  tolua_constant(tolua_S,"FILL_POINT",FILL_POINT);
  tolua_constant(tolua_S,"OP_KEEP",OP_KEEP);
  tolua_constant(tolua_S,"OP_ZERO",OP_ZERO);
  tolua_constant(tolua_S,"OP_REF",OP_REF);
  tolua_constant(tolua_S,"OP_INCR",OP_INCR);
  tolua_constant(tolua_S,"OP_DECR",OP_DECR);
  tolua_constant(tolua_S,"LOCK_NONE",LOCK_NONE);
  tolua_constant(tolua_S,"LOCK_HARDWARE",LOCK_HARDWARE);
  tolua_constant(tolua_S,"LOCK_SHADOW",LOCK_SHADOW);
  tolua_constant(tolua_S,"LOCK_SCRATCH",LOCK_SCRATCH);
  tolua_constant(tolua_S,"ELEMENT_POSITION",ELEMENT_POSITION);
  tolua_constant(tolua_S,"ELEMENT_NORMAL",ELEMENT_NORMAL);
  tolua_constant(tolua_S,"ELEMENT_COLOR",ELEMENT_COLOR);
  tolua_constant(tolua_S,"ELEMENT_TEXCOORD1",ELEMENT_TEXCOORD1);
  tolua_constant(tolua_S,"ELEMENT_TEXCOORD2",ELEMENT_TEXCOORD2);
  tolua_constant(tolua_S,"ELEMENT_CUBETEXCOORD1",ELEMENT_CUBETEXCOORD1);
  tolua_constant(tolua_S,"ELEMENT_CUBETEXCOORD2",ELEMENT_CUBETEXCOORD2);
  tolua_constant(tolua_S,"ELEMENT_TANGENT",ELEMENT_TANGENT);
  tolua_constant(tolua_S,"ELEMENT_BLENDWEIGHTS",ELEMENT_BLENDWEIGHTS);
  tolua_constant(tolua_S,"ELEMENT_BLENDINDICES",ELEMENT_BLENDINDICES);
  tolua_constant(tolua_S,"ELEMENT_INSTANCEMATRIX1",ELEMENT_INSTANCEMATRIX1);
  tolua_constant(tolua_S,"ELEMENT_INSTANCEMATRIX2",ELEMENT_INSTANCEMATRIX2);
  tolua_constant(tolua_S,"ELEMENT_INSTANCEMATRIX3",ELEMENT_INSTANCEMATRIX3);
  tolua_constant(tolua_S,"MAX_VERTEX_ELEMENTS",MAX_VERTEX_ELEMENTS);
  tolua_constant(tolua_S,"FILTER_NEAREST",FILTER_NEAREST);
  tolua_constant(tolua_S,"FILTER_BILINEAR",FILTER_BILINEAR);
  tolua_constant(tolua_S,"FILTER_TRILINEAR",FILTER_TRILINEAR);
  tolua_constant(tolua_S,"FILTER_ANISOTROPIC",FILTER_ANISOTROPIC);
  tolua_constant(tolua_S,"FILTER_DEFAULT",FILTER_DEFAULT);
  tolua_constant(tolua_S,"MAX_FILTERMODES",MAX_FILTERMODES);
  tolua_constant(tolua_S,"ADDRESS_WRAP",ADDRESS_WRAP);
  tolua_constant(tolua_S,"ADDRESS_MIRROR",ADDRESS_MIRROR);
  tolua_constant(tolua_S,"ADDRESS_CLAMP",ADDRESS_CLAMP);
  tolua_constant(tolua_S,"ADDRESS_BORDER",ADDRESS_BORDER);
  tolua_constant(tolua_S,"MAX_ADDRESSMODES",MAX_ADDRESSMODES);
  tolua_constant(tolua_S,"COORD_U",COORD_U);
  tolua_constant(tolua_S,"COORD_V",COORD_V);
  tolua_constant(tolua_S,"COORD_W",COORD_W);
  tolua_constant(tolua_S,"MAX_COORDS",MAX_COORDS);
  tolua_constant(tolua_S,"TEXTURE_STATIC",TEXTURE_STATIC);
  tolua_constant(tolua_S,"TEXTURE_DYNAMIC",TEXTURE_DYNAMIC);
  tolua_constant(tolua_S,"TEXTURE_RENDERTARGET",TEXTURE_RENDERTARGET);
  tolua_constant(tolua_S,"TEXTURE_DEPTHSTENCIL",TEXTURE_DEPTHSTENCIL);
  tolua_constant(tolua_S,"FACE_POSITIVE_X",FACE_POSITIVE_X);
  tolua_constant(tolua_S,"FACE_NEGATIVE_X",FACE_NEGATIVE_X);
  tolua_constant(tolua_S,"FACE_POSITIVE_Y",FACE_POSITIVE_Y);
  tolua_constant(tolua_S,"FACE_NEGATIVE_Y",FACE_NEGATIVE_Y);
  tolua_constant(tolua_S,"FACE_POSITIVE_Z",FACE_POSITIVE_Z);
  tolua_constant(tolua_S,"FACE_NEGATIVE_Z",FACE_NEGATIVE_Z);
  tolua_constant(tolua_S,"MAX_CUBEMAP_FACES",MAX_CUBEMAP_FACES);
  tolua_constant(tolua_S,"SURFACE_MANUALUPDATE",SURFACE_MANUALUPDATE);
  tolua_constant(tolua_S,"SURFACE_UPDATEVISIBLE",SURFACE_UPDATEVISIBLE);
  tolua_constant(tolua_S,"SURFACE_UPDATEALWAYS",SURFACE_UPDATEALWAYS);
  tolua_constant(tolua_S,"VS",VS);
  tolua_constant(tolua_S,"PS",PS);
  tolua_constant(tolua_S,"TU_DIFFUSE",TU_DIFFUSE);
  tolua_constant(tolua_S,"TU_ALBEDOBUFFER",TU_ALBEDOBUFFER);
  tolua_constant(tolua_S,"TU_NORMAL",TU_NORMAL);
  tolua_constant(tolua_S,"TU_NORMALBUFFER",TU_NORMALBUFFER);
  tolua_constant(tolua_S,"TU_SPECULAR",TU_SPECULAR);
  tolua_constant(tolua_S,"TU_EMISSIVE",TU_EMISSIVE);
  tolua_constant(tolua_S,"TU_ENVIRONMENT",TU_ENVIRONMENT);
  tolua_constant(tolua_S,"MAX_MATERIAL_TEXTURE_UNITS",MAX_MATERIAL_TEXTURE_UNITS);
  tolua_constant(tolua_S,"TU_LIGHTRAMP",TU_LIGHTRAMP);
  tolua_constant(tolua_S,"TU_LIGHTSHAPE",TU_LIGHTSHAPE);
  tolua_constant(tolua_S,"TU_SHADOWMAP",TU_SHADOWMAP);
  tolua_constant(tolua_S,"TU_FACESELECT",TU_FACESELECT);
  tolua_constant(tolua_S,"TU_INDIRECTION",TU_INDIRECTION);
  tolua_constant(tolua_S,"TU_DEPTHBUFFER",TU_DEPTHBUFFER);
  tolua_constant(tolua_S,"TU_LIGHTBUFFER",TU_LIGHTBUFFER);
  tolua_constant(tolua_S,"MAX_TEXTURE_UNITS",MAX_TEXTURE_UNITS);
  tolua_constant(tolua_S,"SP_FRAME",SP_FRAME);
  tolua_constant(tolua_S,"SP_CAMERA",SP_CAMERA);
  tolua_constant(tolua_S,"SP_VIEWPORT",SP_VIEWPORT);
  tolua_constant(tolua_S,"SP_ZONE",SP_ZONE);
  tolua_constant(tolua_S,"SP_LIGHT",SP_LIGHT);
  tolua_constant(tolua_S,"SP_VERTEXLIGHTS",SP_VERTEXLIGHTS);
  tolua_constant(tolua_S,"SP_MATERIAL",SP_MATERIAL);
  tolua_constant(tolua_S,"SP_OBJECTTRANSFORM",SP_OBJECTTRANSFORM);
  tolua_constant(tolua_S,"SP_OBJECTDATA",SP_OBJECTDATA);
  tolua_constant(tolua_S,"MAX_SHADER_PARAMETER_GROUPS",MAX_SHADER_PARAMETER_GROUPS);
  tolua_variable(tolua_S,"QUALITY_LOW",tolua_get_QUALITY_LOW,NULL);
  tolua_variable(tolua_S,"QUALITY_MEDIUM",tolua_get_QUALITY_MEDIUM,NULL);
  tolua_variable(tolua_S,"QUALITY_HIGH",tolua_get_QUALITY_HIGH,NULL);
  tolua_variable(tolua_S,"QUALITY_MAX",tolua_get_QUALITY_MAX,NULL);
  tolua_variable(tolua_S,"SHADOWQUALITY_LOW_16BIT",tolua_get_SHADOWQUALITY_LOW_16BIT,NULL);
  tolua_variable(tolua_S,"SHADOWQUALITY_LOW_24BIT",tolua_get_SHADOWQUALITY_LOW_24BIT,NULL);
  tolua_variable(tolua_S,"SHADOWQUALITY_HIGH_16BIT",tolua_get_SHADOWQUALITY_HIGH_16BIT,NULL);
  tolua_variable(tolua_S,"SHADOWQUALITY_HIGH_24BIT",tolua_get_SHADOWQUALITY_HIGH_24BIT,NULL);
  tolua_variable(tolua_S,"CLEAR_COLOR",tolua_get_CLEAR_COLOR,NULL);
  tolua_variable(tolua_S,"CLEAR_DEPTH",tolua_get_CLEAR_DEPTH,NULL);
  tolua_variable(tolua_S,"CLEAR_STENCIL",tolua_get_CLEAR_STENCIL,NULL);
  tolua_constant(tolua_S,"LIGHT_DIRECTIONAL",LIGHT_DIRECTIONAL);
  tolua_constant(tolua_S,"LIGHT_SPOT",LIGHT_SPOT);
  tolua_constant(tolua_S,"LIGHT_POINT",LIGHT_POINT);
  tolua_cclass(tolua_S,"Light","Light","Drawable",NULL);
  tolua_beginmodule(tolua_S,"Light");
   tolua_function(tolua_S,"SetLightType",tolua_Graphics_Light_SetLightType00);
   tolua_function(tolua_S,"SetPerVertex",tolua_Graphics_Light_SetPerVertex00);
   tolua_function(tolua_S,"SetColor",tolua_Graphics_Light_SetColor00);
   tolua_function(tolua_S,"SetSpecularIntensity",tolua_Graphics_Light_SetSpecularIntensity00);
   tolua_function(tolua_S,"SetRange",tolua_Graphics_Light_SetRange00);
   tolua_function(tolua_S,"SetFov",tolua_Graphics_Light_SetFov00);
   tolua_function(tolua_S,"SetAspectRatio",tolua_Graphics_Light_SetAspectRatio00);
   tolua_function(tolua_S,"SetFadeDistance",tolua_Graphics_Light_SetFadeDistance00);
   tolua_function(tolua_S,"SetShadowFadeDistance",tolua_Graphics_Light_SetShadowFadeDistance00);
   tolua_function(tolua_S,"SetShadowBias",tolua_Graphics_Light_SetShadowBias00);
   tolua_function(tolua_S,"SetShadowCascade",tolua_Graphics_Light_SetShadowCascade00);
   tolua_function(tolua_S,"SetShadowFocus",tolua_Graphics_Light_SetShadowFocus00);
   tolua_function(tolua_S,"SetShadowIntensity",tolua_Graphics_Light_SetShadowIntensity00);
   tolua_function(tolua_S,"SetShadowResolution",tolua_Graphics_Light_SetShadowResolution00);
   tolua_function(tolua_S,"SetShadowNearFarRatio",tolua_Graphics_Light_SetShadowNearFarRatio00);
   tolua_function(tolua_S,"SetRampTexture",tolua_Graphics_Light_SetRampTexture00);
   tolua_function(tolua_S,"SetShapeTexture",tolua_Graphics_Light_SetShapeTexture00);
   tolua_function(tolua_S,"GetLightType",tolua_Graphics_Light_GetLightType00);
   tolua_function(tolua_S,"GetPerVertex",tolua_Graphics_Light_GetPerVertex00);
   tolua_function(tolua_S,"GetColor",tolua_Graphics_Light_GetColor00);
   tolua_function(tolua_S,"GetSpecularIntensity",tolua_Graphics_Light_GetSpecularIntensity00);
   tolua_function(tolua_S,"GetRange",tolua_Graphics_Light_GetRange00);
   tolua_function(tolua_S,"GetFov",tolua_Graphics_Light_GetFov00);
   tolua_function(tolua_S,"GetAspectRatio",tolua_Graphics_Light_GetAspectRatio00);
   tolua_function(tolua_S,"GetFadeDistance",tolua_Graphics_Light_GetFadeDistance00);
   tolua_function(tolua_S,"GetShadowFadeDistance",tolua_Graphics_Light_GetShadowFadeDistance00);
   tolua_function(tolua_S,"GetShadowBias",tolua_Graphics_Light_GetShadowBias00);
   tolua_function(tolua_S,"GetShadowCascade",tolua_Graphics_Light_GetShadowCascade00);
   tolua_function(tolua_S,"GetShadowFocus",tolua_Graphics_Light_GetShadowFocus00);
   tolua_function(tolua_S,"GetShadowIntensity",tolua_Graphics_Light_GetShadowIntensity00);
   tolua_function(tolua_S,"GetShadowResolution",tolua_Graphics_Light_GetShadowResolution00);
   tolua_function(tolua_S,"GetShadowNearFarRatio",tolua_Graphics_Light_GetShadowNearFarRatio00);
   tolua_function(tolua_S,"GetRampTexture",tolua_Graphics_Light_GetRampTexture00);
   tolua_function(tolua_S,"GetShapeTexture",tolua_Graphics_Light_GetShapeTexture00);
   tolua_function(tolua_S,"GetFrustum",tolua_Graphics_Light_GetFrustum00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Material","Material","Resource",NULL);
  tolua_beginmodule(tolua_S,"Material");
   tolua_function(tolua_S,"GetNumTechniques",tolua_Graphics_Material_GetNumTechniques00);
   tolua_function(tolua_S,"GetTechniqueEntry",tolua_Graphics_Material_GetTechniqueEntry00);
   tolua_function(tolua_S,"GetTechnique",tolua_Graphics_Material_GetTechnique00);
   tolua_function(tolua_S,"GetPass",tolua_Graphics_Material_GetPass00);
   tolua_function(tolua_S,"GetTexture",tolua_Graphics_Material_GetTexture00);
   tolua_function(tolua_S,"GetShaderParameter",tolua_Graphics_Material_GetShaderParameter00);
   tolua_function(tolua_S,"GetCullMode",tolua_Graphics_Material_GetCullMode00);
   tolua_function(tolua_S,"GetShadowCullMode",tolua_Graphics_Material_GetShadowCullMode00);
   tolua_function(tolua_S,"GetDepthBias",tolua_Graphics_Material_GetDepthBias00);
   tolua_function(tolua_S,"GetAuxViewFrameNumber",tolua_Graphics_Material_GetAuxViewFrameNumber00);
   tolua_function(tolua_S,"GetOcclusion",tolua_Graphics_Material_GetOcclusion00);
   tolua_function(tolua_S,"GetSpecular",tolua_Graphics_Material_GetSpecular00);
   tolua_function(tolua_S,"GetTextureUnitName",tolua_Graphics_Material_GetTextureUnitName00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Model","Model","Resource",NULL);
  tolua_beginmodule(tolua_S,"Model");
   tolua_function(tolua_S,"GetBoundingBox",tolua_Graphics_Model_GetBoundingBox00);
   tolua_function(tolua_S,"GetSkeleton",tolua_Graphics_Model_GetSkeleton00);
   tolua_function(tolua_S,"GetNumGeometries",tolua_Graphics_Model_GetNumGeometries00);
   tolua_function(tolua_S,"GetNumGeometryLodLevels",tolua_Graphics_Model_GetNumGeometryLodLevels00);
   tolua_function(tolua_S,"GetGeometry",tolua_Graphics_Model_GetGeometry00);
   tolua_function(tolua_S,"GetNumMorphs",tolua_Graphics_Model_GetNumMorphs00);
   tolua_function(tolua_S,"GetMorph",tolua_Graphics_Model_GetMorph00);
   tolua_function(tolua_S,"GetMorph",tolua_Graphics_Model_GetMorph01);
   tolua_function(tolua_S,"GetMorph",tolua_Graphics_Model_GetMorph02);
   tolua_function(tolua_S,"GetMorphRangeStart",tolua_Graphics_Model_GetMorphRangeStart00);
   tolua_function(tolua_S,"GetMorphRangeCount",tolua_Graphics_Model_GetMorphRangeCount00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Octree","Octree","Component",NULL);
  tolua_beginmodule(tolua_S,"Octree");
   tolua_function(tolua_S,"Resize",tolua_Graphics_Octree_Resize00);
   tolua_function(tolua_S,"Update",tolua_Graphics_Octree_Update00);
   tolua_function(tolua_S,"AddManualDrawable",tolua_Graphics_Octree_AddManualDrawable00);
   tolua_function(tolua_S,"RemoveManualDrawable",tolua_Graphics_Octree_RemoveManualDrawable00);
   tolua_function(tolua_S,"GetDrawables",tolua_Graphics_Octree_GetDrawables00);
   tolua_function(tolua_S,"Raycast",tolua_Graphics_Octree_Raycast00);
   tolua_function(tolua_S,"RaycastSingle",tolua_Graphics_Octree_RaycastSingle00);
   tolua_function(tolua_S,"GetNumLevels",tolua_Graphics_Octree_GetNumLevels00);
   tolua_function(tolua_S,"QueueUpdate",tolua_Graphics_Octree_QueueUpdate00);
   tolua_function(tolua_S,"QueueReinsertion",tolua_Graphics_Octree_QueueReinsertion00);
   tolua_function(tolua_S,"DrawDebugGeometry",tolua_Graphics_Octree_DrawDebugGeometry00);
  tolua_endmodule(tolua_S);
  tolua_function(tolua_S,"GetOctree",tolua_Graphics_GetOctree00);
  tolua_constant(tolua_S,"EMITTER_SPHERE",EMITTER_SPHERE);
  tolua_constant(tolua_S,"EMITTER_BOX",EMITTER_BOX);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"ColorFrame","ColorFrame","",tolua_collect_ColorFrame);
  #else
  tolua_cclass(tolua_S,"ColorFrame","ColorFrame","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"ColorFrame");
   tolua_function(tolua_S,"new",tolua_Graphics_ColorFrame_new00);
   tolua_function(tolua_S,"new_local",tolua_Graphics_ColorFrame_new00_local);
   tolua_function(tolua_S,".call",tolua_Graphics_ColorFrame_new00_local);
   tolua_function(tolua_S,"new",tolua_Graphics_ColorFrame_new01);
   tolua_function(tolua_S,"new_local",tolua_Graphics_ColorFrame_new01_local);
   tolua_function(tolua_S,".call",tolua_Graphics_ColorFrame_new01_local);
   tolua_function(tolua_S,"new",tolua_Graphics_ColorFrame_new02);
   tolua_function(tolua_S,"new_local",tolua_Graphics_ColorFrame_new02_local);
   tolua_function(tolua_S,".call",tolua_Graphics_ColorFrame_new02_local);
   tolua_function(tolua_S,"Interpolate",tolua_Graphics_ColorFrame_Interpolate00);
   tolua_variable(tolua_S,"color",tolua_get_ColorFrame_color,tolua_set_ColorFrame_color);
   tolua_variable(tolua_S,"time",tolua_get_ColorFrame_time,tolua_set_ColorFrame_time);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"TextureFrame","TextureFrame","",tolua_collect_TextureFrame);
  #else
  tolua_cclass(tolua_S,"TextureFrame","TextureFrame","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"TextureFrame");
   tolua_function(tolua_S,"new",tolua_Graphics_TextureFrame_new00);
   tolua_function(tolua_S,"new_local",tolua_Graphics_TextureFrame_new00_local);
   tolua_function(tolua_S,".call",tolua_Graphics_TextureFrame_new00_local);
   tolua_variable(tolua_S,"uv",tolua_get_TextureFrame_uv,tolua_set_TextureFrame_uv);
   tolua_variable(tolua_S,"time",tolua_get_TextureFrame_time,tolua_set_TextureFrame_time);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"ParticleEmitter","ParticleEmitter","BillboardSet",NULL);
  tolua_beginmodule(tolua_S,"ParticleEmitter");
   tolua_function(tolua_S,"Load",tolua_Graphics_ParticleEmitter_Load00);
   tolua_function(tolua_S,"SetNumParticles",tolua_Graphics_ParticleEmitter_SetNumParticles00);
   tolua_function(tolua_S,"SetEmissionRate",tolua_Graphics_ParticleEmitter_SetEmissionRate00);
   tolua_function(tolua_S,"SetMinEmissionRate",tolua_Graphics_ParticleEmitter_SetMinEmissionRate00);
   tolua_function(tolua_S,"SetMaxEmissionRate",tolua_Graphics_ParticleEmitter_SetMaxEmissionRate00);
   tolua_function(tolua_S,"SetEmitterType",tolua_Graphics_ParticleEmitter_SetEmitterType00);
   tolua_function(tolua_S,"SetEmitterSize",tolua_Graphics_ParticleEmitter_SetEmitterSize00);
   tolua_function(tolua_S,"SetActiveTime",tolua_Graphics_ParticleEmitter_SetActiveTime00);
   tolua_function(tolua_S,"SetInactiveTime",tolua_Graphics_ParticleEmitter_SetInactiveTime00);
   tolua_function(tolua_S,"SetEmitting",tolua_Graphics_ParticleEmitter_SetEmitting00);
   tolua_function(tolua_S,"SetUpdateInvisible",tolua_Graphics_ParticleEmitter_SetUpdateInvisible00);
   tolua_function(tolua_S,"SetTimeToLive",tolua_Graphics_ParticleEmitter_SetTimeToLive00);
   tolua_function(tolua_S,"SetMinTimeToLive",tolua_Graphics_ParticleEmitter_SetMinTimeToLive00);
   tolua_function(tolua_S,"SetMaxTimeToLive",tolua_Graphics_ParticleEmitter_SetMaxTimeToLive00);
   tolua_function(tolua_S,"SetParticleSize",tolua_Graphics_ParticleEmitter_SetParticleSize00);
   tolua_function(tolua_S,"SetMinParticleSize",tolua_Graphics_ParticleEmitter_SetMinParticleSize00);
   tolua_function(tolua_S,"SetMaxParticleSize",tolua_Graphics_ParticleEmitter_SetMaxParticleSize00);
   tolua_function(tolua_S,"SetMinDirection",tolua_Graphics_ParticleEmitter_SetMinDirection00);
   tolua_function(tolua_S,"SetMaxDirection",tolua_Graphics_ParticleEmitter_SetMaxDirection00);
   tolua_function(tolua_S,"SetVelocity",tolua_Graphics_ParticleEmitter_SetVelocity00);
   tolua_function(tolua_S,"SetMinVelocity",tolua_Graphics_ParticleEmitter_SetMinVelocity00);
   tolua_function(tolua_S,"SetMaxVelocity",tolua_Graphics_ParticleEmitter_SetMaxVelocity00);
   tolua_function(tolua_S,"SetRotation",tolua_Graphics_ParticleEmitter_SetRotation00);
   tolua_function(tolua_S,"SetMinRotation",tolua_Graphics_ParticleEmitter_SetMinRotation00);
   tolua_function(tolua_S,"SetMaxRotation",tolua_Graphics_ParticleEmitter_SetMaxRotation00);
   tolua_function(tolua_S,"SetRotationSpeed",tolua_Graphics_ParticleEmitter_SetRotationSpeed00);
   tolua_function(tolua_S,"SetMinRotationSpeed",tolua_Graphics_ParticleEmitter_SetMinRotationSpeed00);
   tolua_function(tolua_S,"SetMaxRotationSpeed",tolua_Graphics_ParticleEmitter_SetMaxRotationSpeed00);
   tolua_function(tolua_S,"SetConstantForce",tolua_Graphics_ParticleEmitter_SetConstantForce00);
   tolua_function(tolua_S,"SetDampingForce",tolua_Graphics_ParticleEmitter_SetDampingForce00);
   tolua_function(tolua_S,"SetSizeAdd",tolua_Graphics_ParticleEmitter_SetSizeAdd00);
   tolua_function(tolua_S,"SetSizeMul",tolua_Graphics_ParticleEmitter_SetSizeMul00);
   tolua_function(tolua_S,"SetColor",tolua_Graphics_ParticleEmitter_SetColor00);
   tolua_function(tolua_S,"SetNumColors",tolua_Graphics_ParticleEmitter_SetNumColors00);
   tolua_function(tolua_S,"SetNumTextureFrames",tolua_Graphics_ParticleEmitter_SetNumTextureFrames00);
   tolua_function(tolua_S,"GetNumParticles",tolua_Graphics_ParticleEmitter_GetNumParticles00);
   tolua_function(tolua_S,"IsEmitting",tolua_Graphics_ParticleEmitter_IsEmitting00);
   tolua_function(tolua_S,"GetUpdateInvisible",tolua_Graphics_ParticleEmitter_GetUpdateInvisible00);
   tolua_function(tolua_S,"GetMinEmissionRate",tolua_Graphics_ParticleEmitter_GetMinEmissionRate00);
   tolua_function(tolua_S,"GetMaxEmissionRate",tolua_Graphics_ParticleEmitter_GetMaxEmissionRate00);
   tolua_function(tolua_S,"GetEmitterType",tolua_Graphics_ParticleEmitter_GetEmitterType00);
   tolua_function(tolua_S,"GetEmitterSize",tolua_Graphics_ParticleEmitter_GetEmitterSize00);
   tolua_function(tolua_S,"GetActiveTime",tolua_Graphics_ParticleEmitter_GetActiveTime00);
   tolua_function(tolua_S,"GetInactiveTime",tolua_Graphics_ParticleEmitter_GetInactiveTime00);
   tolua_function(tolua_S,"GetMinTimeToLive",tolua_Graphics_ParticleEmitter_GetMinTimeToLive00);
   tolua_function(tolua_S,"GetMaxTimeToLive",tolua_Graphics_ParticleEmitter_GetMaxTimeToLive00);
   tolua_function(tolua_S,"GetMinParticleSize",tolua_Graphics_ParticleEmitter_GetMinParticleSize00);
   tolua_function(tolua_S,"GetMaxParticleSize",tolua_Graphics_ParticleEmitter_GetMaxParticleSize00);
   tolua_function(tolua_S,"GetMinDirection",tolua_Graphics_ParticleEmitter_GetMinDirection00);
   tolua_function(tolua_S,"GetMaxDirection",tolua_Graphics_ParticleEmitter_GetMaxDirection00);
   tolua_function(tolua_S,"GetMinVelocity",tolua_Graphics_ParticleEmitter_GetMinVelocity00);
   tolua_function(tolua_S,"GetMaxVelocity",tolua_Graphics_ParticleEmitter_GetMaxVelocity00);
   tolua_function(tolua_S,"GetMinRotation",tolua_Graphics_ParticleEmitter_GetMinRotation00);
   tolua_function(tolua_S,"GetMaxRotation",tolua_Graphics_ParticleEmitter_GetMaxRotation00);
   tolua_function(tolua_S,"GetMinRotationSpeed",tolua_Graphics_ParticleEmitter_GetMinRotationSpeed00);
   tolua_function(tolua_S,"GetMaxRotationSpeed",tolua_Graphics_ParticleEmitter_GetMaxRotationSpeed00);
   tolua_function(tolua_S,"GetConstantForce",tolua_Graphics_ParticleEmitter_GetConstantForce00);
   tolua_function(tolua_S,"GetDampingForce",tolua_Graphics_ParticleEmitter_GetDampingForce00);
   tolua_function(tolua_S,"GetSizeAdd",tolua_Graphics_ParticleEmitter_GetSizeAdd00);
   tolua_function(tolua_S,"GetSizeMul",tolua_Graphics_ParticleEmitter_GetSizeMul00);
   tolua_function(tolua_S,"GetNumColors",tolua_Graphics_ParticleEmitter_GetNumColors00);
   tolua_function(tolua_S,"GetColor",tolua_Graphics_ParticleEmitter_GetColor00);
   tolua_function(tolua_S,"GetNumTextureFrames",tolua_Graphics_ParticleEmitter_GetNumTextureFrames00);
   tolua_function(tolua_S,"GetTextureFrame",tolua_Graphics_ParticleEmitter_GetTextureFrame00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Renderer","Renderer","",NULL);
  tolua_beginmodule(tolua_S,"Renderer");
   tolua_function(tolua_S,"SetNumViewports",tolua_Graphics_Renderer_SetNumViewports00);
   tolua_function(tolua_S,"SetViewport",tolua_Graphics_Renderer_SetViewport00);
   tolua_function(tolua_S,"SetDefaultRenderPath",tolua_Graphics_Renderer_SetDefaultRenderPath00);
   tolua_function(tolua_S,"SetDefaultRenderPath",tolua_Graphics_Renderer_SetDefaultRenderPath01);
   tolua_function(tolua_S,"SetSpecularLighting",tolua_Graphics_Renderer_SetSpecularLighting00);
   tolua_function(tolua_S,"SetTextureAnisotropy",tolua_Graphics_Renderer_SetTextureAnisotropy00);
   tolua_function(tolua_S,"SetTextureFilterMode",tolua_Graphics_Renderer_SetTextureFilterMode00);
   tolua_function(tolua_S,"SetTextureQuality",tolua_Graphics_Renderer_SetTextureQuality00);
   tolua_function(tolua_S,"SetMaterialQuality",tolua_Graphics_Renderer_SetMaterialQuality00);
   tolua_function(tolua_S,"SetDrawShadows",tolua_Graphics_Renderer_SetDrawShadows00);
   tolua_function(tolua_S,"SetShadowMapSize",tolua_Graphics_Renderer_SetShadowMapSize00);
   tolua_function(tolua_S,"SetShadowQuality",tolua_Graphics_Renderer_SetShadowQuality00);
   tolua_function(tolua_S,"SetReuseShadowMaps",tolua_Graphics_Renderer_SetReuseShadowMaps00);
   tolua_function(tolua_S,"SetMaxShadowMaps",tolua_Graphics_Renderer_SetMaxShadowMaps00);
   tolua_function(tolua_S,"SetMaxShadowCascades",tolua_Graphics_Renderer_SetMaxShadowCascades00);
   tolua_function(tolua_S,"SetDynamicInstancing",tolua_Graphics_Renderer_SetDynamicInstancing00);
   tolua_function(tolua_S,"SetMinInstances",tolua_Graphics_Renderer_SetMinInstances00);
   tolua_function(tolua_S,"SetMaxInstanceTriangles",tolua_Graphics_Renderer_SetMaxInstanceTriangles00);
   tolua_function(tolua_S,"SetMaxSortedInstances",tolua_Graphics_Renderer_SetMaxSortedInstances00);
   tolua_function(tolua_S,"SetMaxOccluderTriangles",tolua_Graphics_Renderer_SetMaxOccluderTriangles00);
   tolua_function(tolua_S,"SetOcclusionBufferSize",tolua_Graphics_Renderer_SetOcclusionBufferSize00);
   tolua_function(tolua_S,"SetOccluderSizeThreshold",tolua_Graphics_Renderer_SetOccluderSizeThreshold00);
   tolua_function(tolua_S,"ReloadShaders",tolua_Graphics_Renderer_ReloadShaders00);
   tolua_function(tolua_S,"GetNumViewports",tolua_Graphics_Renderer_GetNumViewports00);
   tolua_function(tolua_S,"GetViewport",tolua_Graphics_Renderer_GetViewport00);
   tolua_function(tolua_S,"GetDefaultRenderPath",tolua_Graphics_Renderer_GetDefaultRenderPath00);
   tolua_function(tolua_S,"GetSpecularLighting",tolua_Graphics_Renderer_GetSpecularLighting00);
   tolua_function(tolua_S,"GetDrawShadows",tolua_Graphics_Renderer_GetDrawShadows00);
   tolua_function(tolua_S,"GetTextureAnisotropy",tolua_Graphics_Renderer_GetTextureAnisotropy00);
   tolua_function(tolua_S,"GetTextureFilterMode",tolua_Graphics_Renderer_GetTextureFilterMode00);
   tolua_function(tolua_S,"GetTextureQuality",tolua_Graphics_Renderer_GetTextureQuality00);
   tolua_function(tolua_S,"GetMaterialQuality",tolua_Graphics_Renderer_GetMaterialQuality00);
   tolua_function(tolua_S,"GetShadowMapSize",tolua_Graphics_Renderer_GetShadowMapSize00);
   tolua_function(tolua_S,"GetShadowQuality",tolua_Graphics_Renderer_GetShadowQuality00);
   tolua_function(tolua_S,"GetReuseShadowMaps",tolua_Graphics_Renderer_GetReuseShadowMaps00);
   tolua_function(tolua_S,"GetMaxShadowMaps",tolua_Graphics_Renderer_GetMaxShadowMaps00);
   tolua_function(tolua_S,"GetMaxShadowCascades",tolua_Graphics_Renderer_GetMaxShadowCascades00);
   tolua_function(tolua_S,"GetDynamicInstancing",tolua_Graphics_Renderer_GetDynamicInstancing00);
   tolua_function(tolua_S,"GetMinInstances",tolua_Graphics_Renderer_GetMinInstances00);
   tolua_function(tolua_S,"GetMaxInstanceTriangles",tolua_Graphics_Renderer_GetMaxInstanceTriangles00);
   tolua_function(tolua_S,"GetMaxSortedInstances",tolua_Graphics_Renderer_GetMaxSortedInstances00);
   tolua_function(tolua_S,"GetMaxOccluderTriangles",tolua_Graphics_Renderer_GetMaxOccluderTriangles00);
   tolua_function(tolua_S,"GetOcclusionBufferSize",tolua_Graphics_Renderer_GetOcclusionBufferSize00);
   tolua_function(tolua_S,"GetOccluderSizeThreshold",tolua_Graphics_Renderer_GetOccluderSizeThreshold00);
   tolua_function(tolua_S,"GetNumViews",tolua_Graphics_Renderer_GetNumViews00);
   tolua_function(tolua_S,"GetNumPrimitives",tolua_Graphics_Renderer_GetNumPrimitives00);
   tolua_function(tolua_S,"GetNumBatches",tolua_Graphics_Renderer_GetNumBatches00);
   tolua_function(tolua_S,"GetNumGeometries",tolua_Graphics_Renderer_GetNumGeometries00);
   tolua_function(tolua_S,"GetNumLights",tolua_Graphics_Renderer_GetNumLights00);
   tolua_function(tolua_S,"GetNumShadowMaps",tolua_Graphics_Renderer_GetNumShadowMaps00);
   tolua_function(tolua_S,"GetNumOccluders",tolua_Graphics_Renderer_GetNumOccluders00);
   tolua_function(tolua_S,"GetDefaultZone",tolua_Graphics_Renderer_GetDefaultZone00);
   tolua_function(tolua_S,"GetQuadDirLight",tolua_Graphics_Renderer_GetQuadDirLight00);
   tolua_function(tolua_S,"GetDefaultMaterial",tolua_Graphics_Renderer_GetDefaultMaterial00);
   tolua_function(tolua_S,"GetDefaultLightRamp",tolua_Graphics_Renderer_GetDefaultLightRamp00);
   tolua_function(tolua_S,"GetDefaultLightSpot",tolua_Graphics_Renderer_GetDefaultLightSpot00);
   tolua_function(tolua_S,"GetFaceSelectCubeMap",tolua_Graphics_Renderer_GetFaceSelectCubeMap00);
   tolua_function(tolua_S,"GetIndirectionCubeMap",tolua_Graphics_Renderer_GetIndirectionCubeMap00);
   tolua_function(tolua_S,"GetInstancingBuffer",tolua_Graphics_Renderer_GetInstancingBuffer00);
   tolua_function(tolua_S,"GetVertexShader",tolua_Graphics_Renderer_GetVertexShader00);
   tolua_function(tolua_S,"GetPixelShader",tolua_Graphics_Renderer_GetPixelShader00);
   tolua_function(tolua_S,"GetStencilVS",tolua_Graphics_Renderer_GetStencilVS00);
   tolua_function(tolua_S,"GetStencilPS",tolua_Graphics_Renderer_GetStencilPS00);
   tolua_function(tolua_S,"GetFrameInfo",tolua_Graphics_Renderer_GetFrameInfo00);
  tolua_endmodule(tolua_S);
  tolua_function(tolua_S,"GetRenderer",tolua_Graphics_GetRenderer00);
  tolua_cclass(tolua_S,"RenderSurface","RenderSurface","",NULL);
  tolua_beginmodule(tolua_S,"RenderSurface");
   tolua_function(tolua_S,"SetNumViewports",tolua_Graphics_RenderSurface_SetNumViewports00);
   tolua_function(tolua_S,"SetViewport",tolua_Graphics_RenderSurface_SetViewport00);
   tolua_function(tolua_S,"SetUpdateMode",tolua_Graphics_RenderSurface_SetUpdateMode00);
   tolua_function(tolua_S,"SetLinkedRenderTarget",tolua_Graphics_RenderSurface_SetLinkedRenderTarget00);
   tolua_function(tolua_S,"SetLinkedDepthStencil",tolua_Graphics_RenderSurface_SetLinkedDepthStencil00);
   tolua_function(tolua_S,"QueueUpdate",tolua_Graphics_RenderSurface_QueueUpdate00);
   tolua_function(tolua_S,"Release",tolua_Graphics_RenderSurface_Release00);
   tolua_function(tolua_S,"GetParentTexture",tolua_Graphics_RenderSurface_GetParentTexture00);
   tolua_function(tolua_S,"GetWidth",tolua_Graphics_RenderSurface_GetWidth00);
   tolua_function(tolua_S,"GetHeight",tolua_Graphics_RenderSurface_GetHeight00);
   tolua_function(tolua_S,"GetUsage",tolua_Graphics_RenderSurface_GetUsage00);
   tolua_function(tolua_S,"GetLinkedRenderTarget",tolua_Graphics_RenderSurface_GetLinkedRenderTarget00);
   tolua_function(tolua_S,"GetLinkedDepthStencil",tolua_Graphics_RenderSurface_GetLinkedDepthStencil00);
  tolua_endmodule(tolua_S);
  #ifdef __cplusplus
  tolua_cclass(tolua_S,"Bone","Bone","",tolua_collect_Bone);
  #else
  tolua_cclass(tolua_S,"Bone","Bone","",NULL);
  #endif
  tolua_beginmodule(tolua_S,"Bone");
   tolua_function(tolua_S,"new",tolua_Graphics_Bone_new00);
   tolua_function(tolua_S,"new_local",tolua_Graphics_Bone_new00_local);
   tolua_function(tolua_S,".call",tolua_Graphics_Bone_new00_local);
   tolua_variable(tolua_S,"name",tolua_get_Bone_name,tolua_set_Bone_name);
   tolua_variable(tolua_S,"nameHash",tolua_get_Bone_nameHash,tolua_set_Bone_nameHash);
   tolua_variable(tolua_S,"parentIndex",tolua_get_Bone_parentIndex,tolua_set_Bone_parentIndex);
   tolua_variable(tolua_S,"initialPosition",tolua_get_Bone_initialPosition,tolua_set_Bone_initialPosition);
   tolua_variable(tolua_S,"initialRotation",tolua_get_Bone_initialRotation,tolua_set_Bone_initialRotation);
   tolua_variable(tolua_S,"initialScale",tolua_get_Bone_initialScale,tolua_set_Bone_initialScale);
   tolua_variable(tolua_S,"offsetMatrix",tolua_get_Bone_offsetMatrix,tolua_set_Bone_offsetMatrix);
   tolua_variable(tolua_S,"animated",tolua_get_Bone_animated,tolua_set_Bone_animated);
   tolua_variable(tolua_S,"collisionMask",tolua_get_Bone_unsigned_collisionMask,tolua_set_Bone_unsigned_collisionMask);
   tolua_variable(tolua_S,"radius",tolua_get_Bone_radius,tolua_set_Bone_radius);
   tolua_variable(tolua_S,"boundingBox",tolua_get_Bone_boundingBox,tolua_set_Bone_boundingBox);
   tolua_variable(tolua_S,"node",tolua_get_Bone_node_ptr,tolua_set_Bone_node_ptr);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Skeleton","Skeleton","",NULL);
  tolua_beginmodule(tolua_S,"Skeleton");
   tolua_function(tolua_S,"GetNumBones",tolua_Graphics_Skeleton_GetNumBones00);
   tolua_function(tolua_S,"GetRootBone",tolua_Graphics_Skeleton_GetRootBone00);
   tolua_function(tolua_S,"GetBone",tolua_Graphics_Skeleton_GetBone00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Skybox","Skybox","StaticModel",NULL);
  tolua_beginmodule(tolua_S,"Skybox");
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"StaticModel","StaticModel","Drawable",NULL);
  tolua_beginmodule(tolua_S,"StaticModel");
   tolua_function(tolua_S,"SetModel",tolua_Graphics_StaticModel_SetModel00);
   tolua_function(tolua_S,"SetMaterial",tolua_Graphics_StaticModel_SetMaterial00);
   tolua_function(tolua_S,"SetMaterial",tolua_Graphics_StaticModel_SetMaterial01);
   tolua_function(tolua_S,"SetOcclusionLodLevel",tolua_Graphics_StaticModel_SetOcclusionLodLevel00);
   tolua_function(tolua_S,"GetModel",tolua_Graphics_StaticModel_GetModel00);
   tolua_function(tolua_S,"GetBoundingBox",tolua_Graphics_StaticModel_GetBoundingBox00);
   tolua_function(tolua_S,"GetNumGeometries",tolua_Graphics_StaticModel_GetNumGeometries00);
   tolua_function(tolua_S,"GetMaterial",tolua_Graphics_StaticModel_GetMaterial00);
   tolua_function(tolua_S,"GetOcclusionLodLevel",tolua_Graphics_StaticModel_GetOcclusionLodLevel00);
   tolua_function(tolua_S,"IsInside",tolua_Graphics_StaticModel_IsInside00);
   tolua_function(tolua_S,"IsInsideLocal",tolua_Graphics_StaticModel_IsInsideLocal00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Technique","Technique","Resource",NULL);
  tolua_beginmodule(tolua_S,"Technique");
   tolua_function(tolua_S,"SetIsSM3",tolua_Graphics_Technique_SetIsSM300);
   tolua_function(tolua_S,"ReleaseShaders",tolua_Graphics_Technique_ReleaseShaders00);
   tolua_function(tolua_S,"IsSM3",tolua_Graphics_Technique_IsSM300);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Terrain","Terrain","Component",NULL);
  tolua_beginmodule(tolua_S,"Terrain");
   tolua_function(tolua_S,"SetPatchSize",tolua_Graphics_Terrain_SetPatchSize00);
   tolua_function(tolua_S,"SetSpacing",tolua_Graphics_Terrain_SetSpacing00);
   tolua_function(tolua_S,"SetSmoothing",tolua_Graphics_Terrain_SetSmoothing00);
   tolua_function(tolua_S,"SetHeightMap",tolua_Graphics_Terrain_SetHeightMap00);
   tolua_function(tolua_S,"SetMaterial",tolua_Graphics_Terrain_SetMaterial00);
   tolua_function(tolua_S,"SetDrawDistance",tolua_Graphics_Terrain_SetDrawDistance00);
   tolua_function(tolua_S,"SetShadowDistance",tolua_Graphics_Terrain_SetShadowDistance00);
   tolua_function(tolua_S,"SetLodBias",tolua_Graphics_Terrain_SetLodBias00);
   tolua_function(tolua_S,"SetViewMask",tolua_Graphics_Terrain_SetViewMask00);
   tolua_function(tolua_S,"SetLightMask",tolua_Graphics_Terrain_SetLightMask00);
   tolua_function(tolua_S,"SetShadowMask",tolua_Graphics_Terrain_SetShadowMask00);
   tolua_function(tolua_S,"SetZoneMask",tolua_Graphics_Terrain_SetZoneMask00);
   tolua_function(tolua_S,"SetMaxLights",tolua_Graphics_Terrain_SetMaxLights00);
   tolua_function(tolua_S,"SetCastShadows",tolua_Graphics_Terrain_SetCastShadows00);
   tolua_function(tolua_S,"SetOccluder",tolua_Graphics_Terrain_SetOccluder00);
   tolua_function(tolua_S,"SetOccludee",tolua_Graphics_Terrain_SetOccludee00);
   tolua_function(tolua_S,"GetPatchSize",tolua_Graphics_Terrain_GetPatchSize00);
   tolua_function(tolua_S,"GetSpacing",tolua_Graphics_Terrain_GetSpacing00);
   tolua_function(tolua_S,"GetNumVertices",tolua_Graphics_Terrain_GetNumVertices00);
   tolua_function(tolua_S,"GetNumPatches",tolua_Graphics_Terrain_GetNumPatches00);
   tolua_function(tolua_S,"GetSmoothing",tolua_Graphics_Terrain_GetSmoothing00);
   tolua_function(tolua_S,"GetHeightMap",tolua_Graphics_Terrain_GetHeightMap00);
   tolua_function(tolua_S,"GetMaterial",tolua_Graphics_Terrain_GetMaterial00);
   tolua_function(tolua_S,"GetPatch",tolua_Graphics_Terrain_GetPatch00);
   tolua_function(tolua_S,"GetPatch",tolua_Graphics_Terrain_GetPatch01);
   tolua_function(tolua_S,"GetHeight",tolua_Graphics_Terrain_GetHeight00);
   tolua_function(tolua_S,"GetNormal",tolua_Graphics_Terrain_GetNormal00);
   tolua_function(tolua_S,"GetDrawDistance",tolua_Graphics_Terrain_GetDrawDistance00);
   tolua_function(tolua_S,"GetShadowDistance",tolua_Graphics_Terrain_GetShadowDistance00);
   tolua_function(tolua_S,"GetLodBias",tolua_Graphics_Terrain_GetLodBias00);
   tolua_function(tolua_S,"GetViewMask",tolua_Graphics_Terrain_GetViewMask00);
   tolua_function(tolua_S,"GetLightMask",tolua_Graphics_Terrain_GetLightMask00);
   tolua_function(tolua_S,"GetShadowMask",tolua_Graphics_Terrain_GetShadowMask00);
   tolua_function(tolua_S,"GetZoneMask",tolua_Graphics_Terrain_GetZoneMask00);
   tolua_function(tolua_S,"GetMaxLights",tolua_Graphics_Terrain_GetMaxLights00);
   tolua_function(tolua_S,"IsVisible",tolua_Graphics_Terrain_IsVisible00);
   tolua_function(tolua_S,"GetCastShadows",tolua_Graphics_Terrain_GetCastShadows00);
   tolua_function(tolua_S,"IsOccluder",tolua_Graphics_Terrain_IsOccluder00);
   tolua_function(tolua_S,"IsOccludee",tolua_Graphics_Terrain_IsOccludee00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"TerrainPatch","TerrainPatch","Drawable",NULL);
  tolua_beginmodule(tolua_S,"TerrainPatch");
   tolua_function(tolua_S,"SetOwner",tolua_Graphics_TerrainPatch_SetOwner00);
   tolua_function(tolua_S,"SetNeighbors",tolua_Graphics_TerrainPatch_SetNeighbors00);
   tolua_function(tolua_S,"SetMaterial",tolua_Graphics_TerrainPatch_SetMaterial00);
   tolua_function(tolua_S,"SetBoundingBox",tolua_Graphics_TerrainPatch_SetBoundingBox00);
   tolua_function(tolua_S,"SetCoordinates",tolua_Graphics_TerrainPatch_SetCoordinates00);
   tolua_function(tolua_S,"SetOcclusionOffset",tolua_Graphics_TerrainPatch_SetOcclusionOffset00);
   tolua_function(tolua_S,"ResetLod",tolua_Graphics_TerrainPatch_ResetLod00);
   tolua_function(tolua_S,"GetGeometry",tolua_Graphics_TerrainPatch_GetGeometry00);
   tolua_function(tolua_S,"GetMaxLodGeometry",tolua_Graphics_TerrainPatch_GetMaxLodGeometry00);
   tolua_function(tolua_S,"GetMinLodGeometry",tolua_Graphics_TerrainPatch_GetMinLodGeometry00);
   tolua_function(tolua_S,"GetVertexBuffer",tolua_Graphics_TerrainPatch_GetVertexBuffer00);
   tolua_function(tolua_S,"GetOwner",tolua_Graphics_TerrainPatch_GetOwner00);
   tolua_function(tolua_S,"GetNorthPatch",tolua_Graphics_TerrainPatch_GetNorthPatch00);
   tolua_function(tolua_S,"GetSouthPatch",tolua_Graphics_TerrainPatch_GetSouthPatch00);
   tolua_function(tolua_S,"GetWestPatch",tolua_Graphics_TerrainPatch_GetWestPatch00);
   tolua_function(tolua_S,"GetEastPatch",tolua_Graphics_TerrainPatch_GetEastPatch00);
   tolua_function(tolua_S,"GetBoundingBox",tolua_Graphics_TerrainPatch_GetBoundingBox00);
   tolua_function(tolua_S,"GetCoordinates",tolua_Graphics_TerrainPatch_GetCoordinates00);
   tolua_function(tolua_S,"GetLodLevel",tolua_Graphics_TerrainPatch_GetLodLevel00);
   tolua_function(tolua_S,"GetOcclusionOffset",tolua_Graphics_TerrainPatch_GetOcclusionOffset00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Texture","Texture","Resource",NULL);
  tolua_beginmodule(tolua_S,"Texture");
   tolua_function(tolua_S,"SetNumLevels",tolua_Graphics_Texture_SetNumLevels00);
   tolua_function(tolua_S,"SetFilterMode",tolua_Graphics_Texture_SetFilterMode00);
   tolua_function(tolua_S,"SetAddressMode",tolua_Graphics_Texture_SetAddressMode00);
   tolua_function(tolua_S,"SetBorderColor",tolua_Graphics_Texture_SetBorderColor00);
   tolua_function(tolua_S,"SetSRGB",tolua_Graphics_Texture_SetSRGB00);
   tolua_function(tolua_S,"SetBackupTexture",tolua_Graphics_Texture_SetBackupTexture00);
   tolua_function(tolua_S,"GetFormat",tolua_Graphics_Texture_GetFormat00);
   tolua_function(tolua_S,"IsCompressed",tolua_Graphics_Texture_IsCompressed00);
   tolua_function(tolua_S,"GetLevels",tolua_Graphics_Texture_GetLevels00);
   tolua_function(tolua_S,"GetWidth",tolua_Graphics_Texture_GetWidth00);
   tolua_function(tolua_S,"GetHeight",tolua_Graphics_Texture_GetHeight00);
   tolua_function(tolua_S,"GetFilterMode",tolua_Graphics_Texture_GetFilterMode00);
   tolua_function(tolua_S,"GetAddressMode",tolua_Graphics_Texture_GetAddressMode00);
   tolua_function(tolua_S,"GetBorderColor",tolua_Graphics_Texture_GetBorderColor00);
   tolua_function(tolua_S,"GetSRGB",tolua_Graphics_Texture_GetSRGB00);
   tolua_function(tolua_S,"GetBackupTexture",tolua_Graphics_Texture_GetBackupTexture00);
   tolua_function(tolua_S,"GetLevelWidth",tolua_Graphics_Texture_GetLevelWidth00);
   tolua_function(tolua_S,"GetLevelHeight",tolua_Graphics_Texture_GetLevelHeight00);
   tolua_function(tolua_S,"GetUsage",tolua_Graphics_Texture_GetUsage00);
   tolua_function(tolua_S,"GetDataSize",tolua_Graphics_Texture_GetDataSize00);
   tolua_function(tolua_S,"GetRowDataSize",tolua_Graphics_Texture_GetRowDataSize00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Texture2D","Texture2D","Texture",NULL);
  tolua_beginmodule(tolua_S,"Texture2D");
   tolua_function(tolua_S,"GetRenderSurface",tolua_Graphics_Texture2D_GetRenderSurface00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"TextureCube","TextureCube","Texture",NULL);
  tolua_beginmodule(tolua_S,"TextureCube");
   tolua_function(tolua_S,"GetRenderSurface",tolua_Graphics_TextureCube_GetRenderSurface00);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"Zone","Zone","Drawable",NULL);
  tolua_beginmodule(tolua_S,"Zone");
   tolua_function(tolua_S,"SetBoundingBox",tolua_Graphics_Zone_SetBoundingBox00);
   tolua_function(tolua_S,"SetAmbientColor",tolua_Graphics_Zone_SetAmbientColor00);
   tolua_function(tolua_S,"SetFogColor",tolua_Graphics_Zone_SetFogColor00);
   tolua_function(tolua_S,"SetFogStart",tolua_Graphics_Zone_SetFogStart00);
   tolua_function(tolua_S,"SetFogEnd",tolua_Graphics_Zone_SetFogEnd00);
   tolua_function(tolua_S,"SetPriority",tolua_Graphics_Zone_SetPriority00);
   tolua_function(tolua_S,"SetOverride",tolua_Graphics_Zone_SetOverride00);
   tolua_function(tolua_S,"SetAmbientGradient",tolua_Graphics_Zone_SetAmbientGradient00);
   tolua_function(tolua_S,"GetBoundingBox",tolua_Graphics_Zone_GetBoundingBox00);
   tolua_function(tolua_S,"GetInverseWorldTransform",tolua_Graphics_Zone_GetInverseWorldTransform00);
   tolua_function(tolua_S,"GetAmbientColor",tolua_Graphics_Zone_GetAmbientColor00);
   tolua_function(tolua_S,"GetAmbientStartColor",tolua_Graphics_Zone_GetAmbientStartColor00);
   tolua_function(tolua_S,"GetAmbientEndColor",tolua_Graphics_Zone_GetAmbientEndColor00);
   tolua_function(tolua_S,"GetFogColor",tolua_Graphics_Zone_GetFogColor00);
   tolua_function(tolua_S,"GetFogStart",tolua_Graphics_Zone_GetFogStart00);
   tolua_function(tolua_S,"GetFogEnd",tolua_Graphics_Zone_GetFogEnd00);
   tolua_function(tolua_S,"GetPriority",tolua_Graphics_Zone_GetPriority00);
   tolua_function(tolua_S,"GetOverride",tolua_Graphics_Zone_GetOverride00);
   tolua_function(tolua_S,"GetAmbientGradient",tolua_Graphics_Zone_GetAmbientGradient00);
   tolua_function(tolua_S,"IsInside",tolua_Graphics_Zone_IsInside00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_Graphics (lua_State* tolua_S) {
 return tolua_Graphics_open(tolua_S);
};
#endif

