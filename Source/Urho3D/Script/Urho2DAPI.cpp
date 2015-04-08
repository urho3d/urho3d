//
// Copyright (c) 2008-2015 the Urho3D project.
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
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRNTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#ifdef URHO3D_URHO2D
#include "../Urho2D/AnimatedSprite2D.h"
#include "../Urho2D/Animation2D.h"
#include "../Urho2D/AnimationSet2D.h"
#include "../Script/APITemplates.h"
#include "../Urho2D/CollisionBox2D.h"
#include "../Urho2D/CollisionChain2D.h"
#include "../Urho2D/CollisionCircle2D.h"
#include "../Urho2D/CollisionEdge2D.h"
#include "../Urho2D/CollisionPolygon2D.h"
#include "../Urho2D/CollisionShape2D.h"
#include "../Urho2D/Constraint2D.h"
#include "../Urho2D/ConstraintDistance2D.h"
#include "../Urho2D/ConstraintFriction2D.h"
#include "../Urho2D/ConstraintGear2D.h"
#include "../Urho2D/ConstraintMotor2D.h"
#include "../Urho2D/ConstraintMouse2D.h"
#include "../Urho2D/ConstraintPrismatic2D.h"
#include "../Urho2D/ConstraintPulley2D.h"
#include "../Urho2D/ConstraintRevolute2D.h"
#include "../Urho2D/ConstraintRope2D.h"
#include "../Urho2D/ConstraintWeld2D.h"
#include "../Urho2D/ConstraintWheel2D.h"
#include "../Urho2D/Drawable2D.h"
#include "../Urho2D/ParticleEffect2D.h"
#include "../Urho2D/ParticleEmitter2D.h"
#include "../Urho2D/PhysicsWorld2D.h"
#include "../Urho2D/RigidBody2D.h"
#include "../Scene/Scene.h"
#include "../Urho2D/Sprite2D.h"
#include "../Urho2D/SpriteSheet2D.h"
#include "../Urho2D/StaticSprite2D.h"
#include "../Urho2D/TileMap2D.h"
#include "../Urho2D/TileMapDefs2D.h"
#include "../Urho2D/TileMapLayer2D.h"
#include "../Urho2D/TmxFile2D.h"

#ifdef _MSC_VER
#pragma warning(disable:4345)
#endif

namespace Urho3D
{

static void RegisterSprite2D(asIScriptEngine* engine)
{
    RegisterResource<Sprite2D>(engine, "Sprite2D");
    engine->RegisterObjectMethod("Sprite2D", "void set_texture(Texture2D@+)", asMETHOD(Sprite2D, SetTexture), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "Texture2D@+ get_texture() const", asMETHOD(Sprite2D, GetTexture), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "void set_rectangle(const IntRect&in)", asMETHOD(Sprite2D, SetRectangle), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "const IntRect& get_rectangle() const", asMETHOD(Sprite2D, GetRectangle), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "void set_hotSpot(const Vector2&in)", asMETHOD(Sprite2D, SetHotSpot), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "const Vector2& get_hotSpot() const", asMETHOD(Sprite2D, GetHotSpot), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "void set_offset(const IntVector2&in)", asMETHOD(Sprite2D, SetOffset), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "const IntVector2& get_offset() const", asMETHOD(Sprite2D, GetOffset), asCALL_THISCALL);
}

static void RegisterSpriteSheet2D(asIScriptEngine* engine)
{
    RegisterResource<SpriteSheet2D>(engine, "SpriteSheet2D");
    engine->RegisterObjectMethod("SpriteSheet2D", "Texture2D@+ get_texture() const", asMETHOD(SpriteSheet2D, GetTexture), asCALL_THISCALL);
    engine->RegisterObjectMethod("SpriteSheet2D", "Sprite2D@+ GetSprite(const String&)", asMETHOD(SpriteSheet2D, GetSprite), asCALL_THISCALL);
    engine->RegisterObjectMethod("SpriteSheet2D", "void DefineSprite(const String&, const IntRect&, const Vector2& hotSpot=Vector2(0.5f, 0.5f), const IntVector2& offset = IntVector2::ZERO)", asMETHOD(SpriteSheet2D, DefineSprite), asCALL_THISCALL);
}

// Template function for registering a class derived from Drawable2D.
template <class T> void RegisterDrawable2D(asIScriptEngine* engine, const char* className)
{
    RegisterDrawable<T>(engine, className);
    RegisterSubclass<Drawable2D, T>(engine, "Drawable2D", className);
    engine->RegisterObjectMethod(className, "void set_layer(int)", asMETHOD(T, SetLayer), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "int get_layer() const", asMETHOD(T, GetLayer), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_orderInLayer(int)", asMETHOD(T, SetOrderInLayer), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "int get_orderInLayer() const", asMETHOD(T, GetOrderInLayer), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_texture(Texture2D@+)", asMETHOD(T, SetTexture), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Texture2D@+ get_texture() const", asMETHOD(T, GetTexture), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_blendMode(BlendMode)", asMETHOD(T, SetBlendMode), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "BlendMode get_blendMode() const", asMETHOD(T, GetBlendMode), asCALL_THISCALL);
}

static void RegisterDrawable2D(asIScriptEngine* engine)
{
    engine->RegisterGlobalProperty("const float PIXEL_SIZE", (void*)&PIXEL_SIZE);

    RegisterDrawable2D<Drawable2D>(engine, "Drawable2D");
}

// Template function for registering a class derived from StaticSprite2D.
template <class T> void RegisterStaticSprite2D(asIScriptEngine* engine, const char* className)
{
    RegisterDrawable2D<T>(engine, className);
    RegisterSubclass<StaticSprite2D, T>(engine, "StaticSprite2D", className);
    engine->RegisterObjectMethod(className, "void set_sprite(Sprite2D@+)", asMETHOD(T, SetSprite), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Sprite2D@+ get_sprite() const", asMETHOD(T, GetSprite), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void SetFlip(bool, bool)", asMETHOD(T, SetFlip), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_flipX(bool)", asMETHOD(T, SetFlipX), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool get_flipX() const", asMETHOD(T, GetFlipX), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_flipY(bool)", asMETHOD(T, SetFlipY), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool get_flipY() const", asMETHOD(T, GetFlipY), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_color(const Color&in)", asMETHOD(T, SetColor), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const Color& get_color() const", asMETHOD(T, GetColor), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_alpha(float)", asMETHOD(T, SetAlpha), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "float get_alpha() const", asMETHOD(T, GetAlpha), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_useHotSpot(bool)", asMETHOD(T, SetUseHotSpot), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool get_useHotSpot() const", asMETHOD(T, GetUseHotSpot), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_hotSpot(const Vector2&in)", asMETHOD(T, SetHotSpot), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "const Vector2& get_hotSpot() const", asMETHOD(T, GetHotSpot), asCALL_THISCALL);
}

static void RegisterStaticSprite2D(asIScriptEngine* engine)
{
    RegisterStaticSprite2D<StaticSprite2D>(engine, "StaticSprite2D");
}

static void RegisterAnimation2D(asIScriptEngine* engine)
{
    RegisterRefCounted<Animation2D>(engine, "Animation2D");
    engine->RegisterObjectMethod("Animation2D", "const String& get_name() const", asMETHOD(Animation2D, GetName), asCALL_THISCALL);
    engine->RegisterObjectMethod("Animation2D", "float get_length() const", asMETHOD(Animation2D, GetLength), asCALL_THISCALL);
    engine->RegisterObjectMethod("Animation2D", "bool get_looped() const", asMETHOD(Animation2D, IsLooped), asCALL_THISCALL);
}

static void RegisterAnimationSet2D(asIScriptEngine* engine)
{
    RegisterResource<AnimationSet2D>(engine, "AnimationSet2D");
    engine->RegisterObjectMethod("AnimationSet2D", "uint get_numAnimations() const", asMETHOD(AnimationSet2D, GetNumAnimations), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationSet2D", "Animation2D@+ GetAnimation(uint) const", asMETHODPR(AnimationSet2D, GetAnimation, (unsigned) const, Animation2D*), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimationSet2D", "Animation2D@+ GetAnimation(const String&) const", asMETHODPR(AnimationSet2D, GetAnimation, (const String&) const, Animation2D*), asCALL_THISCALL);
}

static void RegisterAnimatedSprite2D(asIScriptEngine* engine)
{
    engine->RegisterEnum("LoopMode2D");
    engine->RegisterEnumValue("LoopMode2D", "LM_DEFAULT", LM_DEFAULT);
    engine->RegisterEnumValue("LoopMode2D", "LM_FORCE_LOOPED", LM_FORCE_LOOPED);
    engine->RegisterEnumValue("LoopMode2D", "LM_FORCE_CLAMPED", LM_FORCE_CLAMPED);

    RegisterStaticSprite2D<AnimatedSprite2D>(engine, "AnimatedSprite2D");
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_speed(float)", asMETHOD(AnimatedSprite2D, SetSpeed), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "float get_speed() const", asMETHOD(AnimatedSprite2D, GetSpeed), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetAnimation(AnimationSet2D@+, const String&, LoopMode2D loopMode=LM_DEFAULT)", asMETHODPR(AnimatedSprite2D, SetAnimation, (AnimationSet2D*, const String&, LoopMode2D), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void SetAnimation(const String&, LoopMode2D loopMode=LM_DEFAULT)", asMETHODPR(AnimatedSprite2D, SetAnimation, (const String&, LoopMode2D), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_animation(const String&)", asMETHODPR(AnimatedSprite2D, SetAnimationAttr, (const String&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "const String& get_animation() const", asMETHOD(AnimatedSprite2D, GetAnimation), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_animationSet(AnimationSet2D@+)", asMETHOD(AnimatedSprite2D, SetAnimationSet), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "AnimationSet2D@+ get_animationSet() const", asMETHOD(AnimatedSprite2D, GetAnimationSet), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "void set_loopMode(LoopMode2D)", asMETHOD(AnimatedSprite2D, SetLoopMode), asCALL_THISCALL);
    engine->RegisterObjectMethod("AnimatedSprite2D", "LoopMode2D get_loopMode() const", asMETHOD(AnimatedSprite2D, GetLoopMode), asCALL_THISCALL);
}

static void RegisterParticleEffect2D(asIScriptEngine* engine)
{
    engine->RegisterEnum("EmitterType2D");
    engine->RegisterEnumValue("EmitterType2D", "EMITTER_TYPE_GRAVITY", EMITTER_TYPE_GRAVITY);
    engine->RegisterEnumValue("EmitterType2D", "EMITTER_TYPE_RADIAL", EMITTER_TYPE_RADIAL);

    RegisterResource<ParticleEffect2D>(engine, "ParticleEffect2D");
}

static void RegisterParticleEmitter2D(asIScriptEngine* engine)
{
    RegisterDrawable2D<ParticleEmitter2D>(engine, "ParticleEmitter2D");
    engine->RegisterObjectMethod("ParticleEmitter2D", "void set_effect(ParticleEffect2D@+)", asMETHOD(ParticleEmitter2D, SetEffect), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "ParticleEffect2D@+ get_effect() const", asMETHOD(ParticleEmitter2D, GetEffect), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "void set_sprite(Sprite2D@+)", asMETHOD(ParticleEmitter2D, SetSprite), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "Sprite2D@+ get_sprite() const", asMETHOD(ParticleEmitter2D, GetSprite), asCALL_THISCALL);
}

static void FakeAddRef(void* ptr)
{
}

static void FakeReleaseRef(void* ptr)
{
}

static void RegisterTileMapDefs2D(asIScriptEngine* engine)
{
    engine->RegisterEnum("Orientation2D");
    engine->RegisterEnumValue("Orientation2D", "O_ORTHOGONAL", O_ORTHOGONAL);
    engine->RegisterEnumValue("Orientation2D", "O_ISOMETRIC", O_ISOMETRIC);
    engine->RegisterEnumValue("Orientation2D", "O_STAGGERED", O_STAGGERED);

    engine->RegisterObjectType("TileMapInfo2D", 0, asOBJ_REF);
    engine->RegisterObjectBehaviour("TileMapInfo2D", asBEHAVE_ADDREF, "void f()", asFUNCTION(FakeAddRef), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("TileMapInfo2D", asBEHAVE_RELEASE, "void f()", asFUNCTION(FakeReleaseRef), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectProperty("TileMapInfo2D", "Orientation2D orientation", offsetof(TileMapInfo2D, orientation_));
    engine->RegisterObjectProperty("TileMapInfo2D", "int width", offsetof(TileMapInfo2D, width_));
    engine->RegisterObjectProperty("TileMapInfo2D", "int height", offsetof(TileMapInfo2D, height_));
    engine->RegisterObjectProperty("TileMapInfo2D", "float tileWidth", offsetof(TileMapInfo2D, tileWidth_));
    engine->RegisterObjectProperty("TileMapInfo2D", "float tileHeight", offsetof(TileMapInfo2D, tileHeight_));
    engine->RegisterObjectMethod("TileMapInfo2D", "float get_mapWidth() const", asMETHOD(TileMapInfo2D, GetMapWidth), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapInfo2D", "float get_mapHeight() const", asMETHOD(TileMapInfo2D, GetMapHeight), asCALL_THISCALL);

    engine->RegisterEnum("TileMapLayerType2D");
    engine->RegisterEnumValue("TileMapLayerType2D", "LT_TILE_LAYER", LT_TILE_LAYER);
    engine->RegisterEnumValue("TileMapLayerType2D", "LT_OBJECT_GROUP", LT_OBJECT_GROUP);
    engine->RegisterEnumValue("TileMapLayerType2D", "LT_IMAGE_LAYER", LT_IMAGE_LAYER);
    engine->RegisterEnumValue("TileMapLayerType2D", "LT_INVALID", LT_INVALID);

    engine->RegisterEnum("TileObjectType2D");
    engine->RegisterEnumValue("TileObjectType2D", "OT_RECTANGLE", OT_RECTANGLE);
    engine->RegisterEnumValue("TileObjectType2D", "OT_ELLIPSE", OT_ELLIPSE);
    engine->RegisterEnumValue("TileObjectType2D", "OT_POLYGON", OT_POLYGON);
    engine->RegisterEnumValue("TileObjectType2D", "OT_POLYLINE", OT_POLYLINE);
    engine->RegisterEnumValue("TileObjectType2D", "OT_TILE", OT_TILE);
    engine->RegisterEnumValue("TileObjectType2D", "OT_INVALID", OT_INVALID);

    RegisterRefCounted<PropertySet2D>(engine, "PropertySet2D");
    engine->RegisterObjectMethod("PropertySet2D", "bool HasProperty(const String&in) const", asMETHOD(PropertySet2D, HasProperty), asCALL_THISCALL);
    engine->RegisterObjectMethod("PropertySet2D", "const String& GetProperty(const String&in) const", asMETHOD(PropertySet2D, HasProperty), asCALL_THISCALL);

    RegisterRefCounted<Tile2D>(engine, "Tile2D");
    engine->RegisterObjectMethod("Tile2D", "int get_gid() const", asMETHOD(Tile2D, GetGid), asCALL_THISCALL);
    engine->RegisterObjectMethod("Tile2D", "Sprite2D@+ get_sprite() const", asMETHOD(Tile2D, GetSprite), asCALL_THISCALL);
    engine->RegisterObjectMethod("Tile2D", "bool HasProperty(const String&in) const", asMETHOD(Tile2D, HasProperty), asCALL_THISCALL);
    engine->RegisterObjectMethod("Tile2D", "const String& GetProperty(const String&in) const", asMETHOD(Tile2D, HasProperty), asCALL_THISCALL);

    RegisterRefCounted<TileMapObject2D>(engine, "TileMapObject2D");
    engine->RegisterObjectMethod("TileMapObject2D", "TileObjectType2D get_objectType() const", asMETHOD(TileMapObject2D, GetObjectType), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapObject2D", "const String& get_name() const", asMETHOD(TileMapObject2D, GetName), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapObject2D", "const String& get_type() const", asMETHOD(TileMapObject2D, GetType), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapObject2D", "const Vector2& get_position() const", asMETHOD(TileMapObject2D, GetPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapObject2D", "const Vector2& get_size() const", asMETHOD(TileMapObject2D, GetSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapObject2D", "uint get_numPoints() const", asMETHOD(TileMapObject2D, GetNumPoints), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapObject2D", "const Vector2& GetPoint(uint) const", asMETHOD(TileMapObject2D, GetPoint), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapObject2D", "int get_tileGid() const", asMETHOD(TileMapObject2D, GetTileGid), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapObject2D", "Sprite2D@+ get_tileSprite() const", asMETHOD(TileMapObject2D, GetTileSprite), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapObject2D", "bool HasProperty(const String&in) const", asMETHOD(TileMapObject2D, HasProperty), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapObject2D", "const String& GetProperty(const String&in) const", asMETHOD(TileMapObject2D, GetProperty), asCALL_THISCALL);
}

static void RegisterTmxFile2D(asIScriptEngine* engine)
{
    RegisterResource<TmxFile2D>(engine, "TmxFile2D");
}

static void RegisterTileMapLayer2D(asIScriptEngine* engine)
{
    RegisterComponent<TileMap2D>(engine, "TileMap2D");
    RegisterComponent<TileMapLayer2D>(engine, "TileMapLayer2D");
    engine->RegisterObjectMethod("TileMapLayer2D", "void set_drawOrder(int)", asMETHOD(TileMapLayer2D, SetDrawOrder), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "int get_drawOrder() const", asMETHOD(TileMapLayer2D, GetDrawOrder), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "void set_visible(bool)", asMETHOD(TileMapLayer2D, SetVisible), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "bool get_visible() const", asMETHOD(TileMapLayer2D, IsVisible), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "bool HasProperty(const String&in) const", asMETHOD(TileMapLayer2D, HasProperty), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "const String& GetProperty(const String&in) const", asMETHOD(TileMapLayer2D, HasProperty), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "TileMapLayerType2D get_layerType() const", asMETHOD(TileMapLayer2D, GetLayerType), asCALL_THISCALL);

    // For tile layer only
    engine->RegisterObjectMethod("TileMapLayer2D", "int get_width() const", asMETHOD(TileMapLayer2D, GetWidth), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "int get_height() const", asMETHOD(TileMapLayer2D, GetHeight), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "Tile2D@+ GetTile(int, int) const", asMETHOD(TileMapLayer2D, GetTile), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "Node@+ GetTileNode(int, int) const", asMETHOD(TileMapLayer2D, GetTileNode), asCALL_THISCALL);

    // For object group only
    engine->RegisterObjectMethod("TileMapLayer2D", "uint get_numObjects() const", asMETHOD(TileMapLayer2D, GetNumObjects), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "TileMapObject2D@+ GetObject(uint) const", asMETHOD(TileMapLayer2D, GetObject), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMapLayer2D", "Node@+ GetObjectNode(uint) const", asMETHOD(TileMapLayer2D, GetObjectNode), asCALL_THISCALL);

    // For image layer only
    engine->RegisterObjectMethod("TileMapLayer2D", "Node@+ get_imageNode() const", asMETHOD(TileMapLayer2D, GetImageNode), asCALL_THISCALL);
}

static void RegisterTileMap2D(asIScriptEngine* engine)
{
    engine->RegisterObjectMethod("TileMap2D", "void set_tmxFile(TmxFile2D@+)", asMETHOD(TileMap2D, SetTmxFile), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "TmxFile2D@+ get_tmxFile() const", asMETHOD(TileMap2D, GetTmxFile), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "TileMapInfo2D@+ get_info() const", asMETHOD(TileMap2D, GetInfo), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "uint get_numLayers() const", asMETHOD(TileMap2D, GetNumLayers), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "TileMapLayer2D@+ GetLayer(uint) const", asMETHOD(TileMap2D, GetLayer), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "Vector2 TileIndexToPosition(int, int) const", asMETHOD(TileMap2D, TileIndexToPosition), asCALL_THISCALL);
    engine->RegisterObjectMethod("TileMap2D", "bool PositionToTileIndex(int&out x, int &out y, const Vector2&in) const", asMETHOD(TileMap2D, PositionToTileIndex), asCALL_THISCALL);
}

static void RegisterRigidBody2D(asIScriptEngine* engine)
{
    engine->RegisterEnum("BodyType2D");
    engine->RegisterEnumValue("BodyType2D", "BT_STATIC", BT_STATIC);
    engine->RegisterEnumValue("BodyType2D", "BT_DYNAMIC", BT_DYNAMIC);
    engine->RegisterEnumValue("BodyType2D", "BT_KINEMATIC", BT_KINEMATIC);

    RegisterComponent<RigidBody2D>(engine, "RigidBody2D");
    engine->RegisterObjectMethod("RigidBody2D", "void set_bodyType(BodyType2D)", asMETHOD(RigidBody2D, SetBodyType), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "BodyType2D get_bodyType() const", asMETHOD(RigidBody2D, GetBodyType), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void set_mass(float)", asMETHOD(RigidBody2D, SetMass), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "float get_mass() const", asMETHOD(RigidBody2D, GetMass), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void set_inertia(float)", asMETHOD(RigidBody2D, SetInertia), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "float get_inertia() const", asMETHOD(RigidBody2D, GetInertia), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void set_massCenter(const Vector2&in)", asMETHOD(RigidBody2D, SetMassCenter), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "Vector2 get_massCenter() const", asMETHOD(RigidBody2D, GetMassCenter), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void set_useFixtureMass(bool)", asMETHOD(RigidBody2D, SetUseFixtureMass), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "bool get_useFixtureMass() const", asMETHOD(RigidBody2D, GetUseFixtureMass), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void set_linearDamping(float)", asMETHOD(RigidBody2D, SetLinearDamping), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "float get_linearDamping() const", asMETHOD(RigidBody2D, GetLinearDamping), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void set_angularDamping(float)", asMETHOD(RigidBody2D, SetAngularDamping), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "float get_angularDamping() const", asMETHOD(RigidBody2D, GetAngularDamping), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void set_allowSleep(bool)", asMETHOD(RigidBody2D, SetAllowSleep), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "bool get_allowSleep() const", asMETHOD(RigidBody2D, IsAllowSleep), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void set_fixedRotation(bool)", asMETHOD(RigidBody2D, SetFixedRotation), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "bool get_fixedRotation() const", asMETHOD(RigidBody2D, IsFixedRotation), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void set_bullet(bool)", asMETHOD(RigidBody2D, SetBullet), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "bool get_bullet() const", asMETHOD(RigidBody2D, IsBullet), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void set_gravityScale(float)", asMETHOD(RigidBody2D, SetGravityScale), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "float get_gravityScale() const", asMETHOD(RigidBody2D, GetGravityScale), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void set_awake(bool)", asMETHOD(RigidBody2D, SetAwake), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "bool get_awake() const", asMETHOD(RigidBody2D, IsAwake), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void set_linearVelocity(const Vector2&in)", asMETHOD(RigidBody2D, SetLinearVelocity), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "Vector2 get_linearVelocity() const", asMETHOD(RigidBody2D, GetLinearVelocity), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void ApplyForce(const Vector2&in, const Vector2&in, bool)", asMETHOD(RigidBody2D, ApplyForce), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void ApplyForceToCenter(const Vector2&in, bool)", asMETHOD(RigidBody2D, ApplyForceToCenter), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void ApplyTorque(float torque, bool)", asMETHOD(RigidBody2D, ApplyTorque), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void ApplyLinearImpulse(const Vector2&in, const Vector2&in, bool)", asMETHOD(RigidBody2D, ApplyLinearImpulse), asCALL_THISCALL);
    engine->RegisterObjectMethod("RigidBody2D", "void ApplyAngularImpulse(float, bool)", asMETHOD(RigidBody2D, ApplyAngularImpulse), asCALL_THISCALL);
}

static void ConstructPhysicsRaycastResult2D(PhysicsRaycastResult2D* ptr)
{
    new(ptr) PhysicsRaycastResult2D();
    ptr->position_ = Vector2::ZERO;
    ptr->normal_ = Vector2::ZERO;
    ptr->distance_ = 0.0f;
}

static void DestructPhysicsRaycastResult2D(PhysicsRaycastResult2D* ptr)
{
    ptr->~PhysicsRaycastResult2D();
}

static RigidBody2D* PhysicsRaycastResultGetRigidBody2D(PhysicsRaycastResult2D* ptr)
{
    return ptr->body_;
}

static CScriptArray* PhysicsWorld2DRaycast(const Vector2& startPoint, const Vector2& endPoint, unsigned collisionMask, PhysicsWorld2D* ptr)
{
    PODVector<PhysicsRaycastResult2D> result;
    ptr->Raycast(result, startPoint, endPoint, collisionMask);
    return VectorToArray<PhysicsRaycastResult2D>(result, "Array<PhysicsRaycastResult2D>");
}

static PhysicsRaycastResult2D PhysicsWorld2DRaycastSingle(const Vector2& startPoint, const Vector2& endPoint, unsigned collisionMask, PhysicsWorld2D* ptr)
{
    PhysicsRaycastResult2D result;
    ptr->RaycastSingle(result, startPoint, endPoint, collisionMask);
    return result;
}

static CScriptArray* PhysicsWorld2DGetRigidBodies(const Rect& aabb, unsigned collisionMask, PhysicsWorld2D* ptr)
{
    PODVector<RigidBody2D*> results;
    ptr->GetRigidBodies(results, aabb, collisionMask);
    return VectorToHandleArray<RigidBody2D>(results, "Array<RigidBody2D@>");
}

static PhysicsWorld2D* SceneGetPhysicsWorld2D(Scene* ptr)
{
    return ptr->GetComponent<PhysicsWorld2D>();
}

static PhysicsWorld2D* GetPhysicsWorld2D()
{
    Scene* scene = GetScriptContextScene();
    return scene ? scene->GetComponent<PhysicsWorld2D>() : 0;
}

static void RegisterPhysicsWorld2D(asIScriptEngine* engine)
{
    engine->RegisterObjectType("PhysicsRaycastResult2D", sizeof(PhysicsRaycastResult2D), asOBJ_VALUE | asOBJ_APP_CLASS_C);
    engine->RegisterObjectBehaviour("PhysicsRaycastResult2D", asBEHAVE_CONSTRUCT, "void f()", asFUNCTION(ConstructPhysicsRaycastResult2D), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectBehaviour("PhysicsRaycastResult2D", asBEHAVE_DESTRUCT, "void f()", asFUNCTION(DestructPhysicsRaycastResult2D), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("PhysicsRaycastResult2D", "PhysicsRaycastResult2D& opAssign(const PhysicsRaycastResult2D&in)", asMETHODPR(PhysicsRaycastResult2D, operator =, (const PhysicsRaycastResult2D&), PhysicsRaycastResult2D&), asCALL_THISCALL);
    engine->RegisterObjectProperty("PhysicsRaycastResult2D", "Vector2 position", offsetof(PhysicsRaycastResult2D, position_));
    engine->RegisterObjectProperty("PhysicsRaycastResult2D", "Vector2 normal", offsetof(PhysicsRaycastResult2D, normal_));
    engine->RegisterObjectProperty("PhysicsRaycastResult2D", "float distance", offsetof(PhysicsRaycastResult2D, distance_));
    engine->RegisterObjectMethod("PhysicsRaycastResult2D", "RigidBody2D@+ get_body() const", asFUNCTION(PhysicsRaycastResultGetRigidBody2D), asCALL_CDECL_OBJLAST);

    RegisterComponent<PhysicsWorld2D>(engine, "PhysicsWorld2D");
    engine->RegisterObjectMethod("PhysicsWorld2D", "Array<PhysicsRaycastResult2D>@ Raycast(const Vector2&, const Vector2&, uint collisionMask = 0xffff)", asFUNCTION(PhysicsWorld2DRaycast), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("PhysicsWorld2D", "PhysicsRaycastResult2D RaycastSingle(const Vector2&, const Vector2&, uint collisionMask = 0xffff)", asFUNCTION(PhysicsWorld2DRaycastSingle), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("PhysicsWorld2D", "RigidBody2D@+ GetRigidBody(const Vector2&, uint collisionMask = 0xffff)", asMETHODPR(PhysicsWorld2D, GetRigidBody, (const Vector2&, unsigned), RigidBody2D*), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "RigidBody2D@+ GetRigidBody(int, int, uint collisionMask = 0xffff)", asMETHODPR(PhysicsWorld2D, GetRigidBody, (int, int, unsigned), RigidBody2D*), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "Array<RigidBody2D@>@ GetRigidBodies(const Rect&in, uint collisionMask = 0xffff)", asFUNCTION(PhysicsWorld2DGetRigidBodies), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_drawShape(bool)", asMETHOD(PhysicsWorld2D, SetDrawShape), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool get_drawShape() const", asMETHOD(PhysicsWorld2D, GetDrawShape), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_drawJoint(bool)", asMETHOD(PhysicsWorld2D, SetDrawJoint), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool get_drawJoint() const", asMETHOD(PhysicsWorld2D, GetDrawJoint), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_drawAabb(bool)", asMETHOD(PhysicsWorld2D, SetDrawAabb), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool get_drawAabb() const", asMETHOD(PhysicsWorld2D, GetDrawAabb), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_drawPair(bool)", asMETHOD(PhysicsWorld2D, SetDrawPair), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool get_drawPair() const", asMETHOD(PhysicsWorld2D, GetDrawPair), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_drawCenterOfMass(bool)", asMETHOD(PhysicsWorld2D, SetDrawCenterOfMass), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool get_drawCenterOfMass() const", asMETHOD(PhysicsWorld2D, GetDrawCenterOfMass), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_allowSleeping(bool)", asMETHOD(PhysicsWorld2D, SetAllowSleeping), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool get_allowSleeping() const", asMETHOD(PhysicsWorld2D, GetAllowSleeping), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_warmStarting(bool)", asMETHOD(PhysicsWorld2D, SetWarmStarting), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool get_warmStarting() const", asMETHOD(PhysicsWorld2D, GetWarmStarting), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_continuousPhysics(bool)", asMETHOD(PhysicsWorld2D, SetContinuousPhysics), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool get_continuousPhysics() const", asMETHOD(PhysicsWorld2D, GetContinuousPhysics), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_subStepping(bool)", asMETHOD(PhysicsWorld2D, SetSubStepping), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool get_subStepping() const", asMETHOD(PhysicsWorld2D, GetSubStepping), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_gravity(const Vector2&in)", asMETHOD(PhysicsWorld2D, SetGravity), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "const Vector2& get_gravity() const", asMETHOD(PhysicsWorld2D, GetGravity), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_autoClearForces(bool)", asMETHOD(PhysicsWorld2D, SetAutoClearForces), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "bool get_autoClearForces() const", asMETHOD(PhysicsWorld2D, GetAutoClearForces), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_velocityIterations(uint)", asMETHOD(PhysicsWorld2D, SetVelocityIterations), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "uint get_velocityIterations() const", asMETHOD(PhysicsWorld2D, GetVelocityIterations), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void set_positionIterations(uint)", asMETHOD(PhysicsWorld2D, SetPositionIterations), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "uint get_positionIterations() const", asMETHOD(PhysicsWorld2D, GetPositionIterations), asCALL_THISCALL);
    engine->RegisterObjectMethod("PhysicsWorld2D", "void DrawDebugGeometry() const", asMETHOD(PhysicsWorld2D, DrawDebugGeometry), asCALL_THISCALL);

    engine->RegisterObjectMethod("Scene", "PhysicsWorld2D@+ get_physicsWorld2D() const", asFUNCTION(SceneGetPhysicsWorld2D), asCALL_CDECL_OBJLAST);
    engine->RegisterGlobalFunction("PhysicsWorld2D@+ get_physicsWorld2D()", asFUNCTION(GetPhysicsWorld2D), asCALL_CDECL);
}

// Template function for registering a class derived from CollisionShape2D.
template <class T> void RegisterCollisionShape2D(asIScriptEngine* engine, const char* className)
{
    RegisterComponent<T>(engine, className);
    RegisterSubclass<CollisionShape2D, T>(engine, "CollisionShape2D", className);
    engine->RegisterObjectMethod(className, "void set_trigger(bool)", asMETHOD(T, SetTrigger), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool get_trigger() const", asMETHOD(T, IsTrigger), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_categoryBits(int)", asMETHOD(T, SetCategoryBits), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "int get_categoryBits() const", asMETHOD(T, GetCategoryBits), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_maskBits(int)", asMETHOD(T, SetMaskBits), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "int get_maskBits() const", asMETHOD(T, GetMaskBits), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_groupIndex(int)", asMETHOD(T, SetGroupIndex), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "int get_groupIndex() const", asMETHOD(T, GetGroupIndex), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_density(float)", asMETHOD(T, SetDensity), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "float get_density() const", asMETHOD(T, GetDensity), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_friction(float)", asMETHOD(T, SetFriction), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "float get_friction() const", asMETHOD(T, GetFriction), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_restitution(float)", asMETHOD(T, SetRestitution), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "float get_restitution() const", asMETHOD(T, GetRestitution), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "float get_mass() const", asMETHOD(T, GetMass), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "float get_inertia() const", asMETHOD(T, GetInertia), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Vector2 get_massCenter() const", asMETHOD(T, GetMassCenter), asCALL_THISCALL);
}

static void RegisterCollisionShape2D(asIScriptEngine* engine)
{
    RegisterCollisionShape2D<CollisionShape2D>(engine, "CollisionShape2D");
}

static void RegisterCollisionBox2D(asIScriptEngine* engine)
{
    RegisterCollisionShape2D<CollisionBox2D>(engine, "CollisionBox2D");
    engine->RegisterObjectMethod("CollisionBox2D", "void set_size(const Vector2&in)", asMETHODPR(CollisionBox2D, SetSize, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "void SetSize(float, float)", asMETHODPR(CollisionBox2D, SetSize, (float, float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "const Vector2& get_size() const", asMETHOD(CollisionBox2D, GetSize), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "void set_center(const Vector2&in)", asMETHODPR(CollisionBox2D, SetCenter, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "void SetCenter(float, float)", asMETHODPR(CollisionBox2D, SetCenter, (float, float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "const Vector2& get_center() const", asMETHOD(CollisionBox2D, GetCenter), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "void set_angle(float)", asMETHOD(CollisionBox2D, SetAngle), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionBox2D", "float get_angle() const", asMETHOD(CollisionBox2D, GetAngle), asCALL_THISCALL);
}

static void RegisterCollisionCircle2D(asIScriptEngine* engine)
{
    RegisterCollisionShape2D<CollisionCircle2D>(engine, "CollisionCircle2D");
    engine->RegisterObjectMethod("CollisionCircle2D", "void set_radius(float)", asMETHOD(CollisionCircle2D, SetRadius), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "float get_radius() const", asMETHOD(CollisionCircle2D, GetRadius), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "void set_center(const Vector2&in)", asMETHODPR(CollisionCircle2D, SetCenter, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "void SetCenter(float, float)", asMETHODPR(CollisionCircle2D, SetCenter, (float, float), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionCircle2D", "const Vector2& get_center() const", asMETHOD(CollisionCircle2D, GetCenter), asCALL_THISCALL);
}

static void CollisionChain2DSetVertices(CScriptArray* vertices, CollisionChain2D* ptr)
{
    ptr->SetVertices(ArrayToPODVector<Vector2>(vertices));
}

static CScriptArray* CollisionChain2DGetVertices(CollisionChain2D* ptr)
{
    return VectorToArray<Vector2>(ptr->GetVertices(), "Array<Vector2>");
}

static void RegisterCollisionChain2D(asIScriptEngine* engine)
{
    RegisterCollisionShape2D<CollisionChain2D>(engine, "CollisionChain2D");
    engine->RegisterObjectMethod("CollisionChain2D", "void set_loop(bool)", asMETHOD(CollisionChain2D, SetLoop), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "bool get_loop() const", asMETHOD(CollisionChain2D, GetLoop), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "void set_vertexCount(uint)", asMETHOD(CollisionChain2D, SetVertexCount), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "uint get_vertexCount() const", asMETHOD(CollisionChain2D, GetVertexCount), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "void SetVertex(uint, const Vector2&in)", asMETHOD(CollisionChain2D, SetVertex), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "const Vector2& GetVertex(uint) const", asMETHOD(CollisionChain2D, GetVertex), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionChain2D", "void SetVertices(Array<Vector2>@+)", asFUNCTION(CollisionChain2DSetVertices), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("CollisionChain2D", "Array<Vector2>@ GetVertices() const", asFUNCTION(CollisionChain2DGetVertices), asCALL_CDECL_OBJLAST);
}

static void RegisterCollisionEdge2D(asIScriptEngine* engine)
{
    RegisterCollisionShape2D<CollisionEdge2D>(engine, "CollisionEdge2D");
    engine->RegisterObjectMethod("CollisionEdge2D", "void set_vertex1(const Vector2&in)", asMETHOD(CollisionEdge2D, SetVertex1), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "const Vector2& get_vertex1() const", asMETHOD(CollisionEdge2D, GetVertex1), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "void set_vertex2(const Vector2&in)", asMETHOD(CollisionEdge2D, SetVertex2), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "const Vector2& get_vertex2() const", asMETHOD(CollisionEdge2D, GetVertex2), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionEdge2D", "void SetVertices(const Vector2&in, const Vector2&in)", asMETHOD(CollisionEdge2D, SetVertices), asCALL_THISCALL);
}

static void CollisionPolygon2DSetVertices(CScriptArray* vertices, CollisionPolygon2D* ptr)
{
    ptr->SetVertices(ArrayToPODVector<Vector2>(vertices));
}

static CScriptArray* CollisionPolygon2DGetVertices(CollisionPolygon2D* ptr)
{
    return VectorToArray<Vector2>(ptr->GetVertices(), "Array<Vector2>");
}

static void RegisterCollisionPolygon2D(asIScriptEngine* engine)
{
    RegisterCollisionShape2D<CollisionPolygon2D>(engine, "CollisionPolygon2D");
    engine->RegisterObjectMethod("CollisionPolygon2D", "void set_vertexCount(uint)", asMETHOD(CollisionPolygon2D, SetVertexCount), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "uint get_vertexCount() const", asMETHOD(CollisionPolygon2D, GetVertexCount), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "void SetVertex(uint, const Vector2&in)", asMETHOD(CollisionPolygon2D, SetVertex), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "const Vector2& GetVertex(uint) const", asMETHOD(CollisionPolygon2D, GetVertex), asCALL_THISCALL);
    engine->RegisterObjectMethod("CollisionPolygon2D", "void SetVertices(Array<Vector2>@+)", asFUNCTION(CollisionPolygon2DSetVertices), asCALL_CDECL_OBJLAST);
    engine->RegisterObjectMethod("CollisionPolygon2D", "Array<Vector2>@ GetVertices() const", asFUNCTION(CollisionPolygon2DGetVertices), asCALL_CDECL_OBJLAST);
}

// Template function for registering a class derived from Constraint2D.
template <class T> void RegisterConstraint2D(asIScriptEngine* engine, const char* className)
{
    RegisterComponent<T>(engine, className);
    RegisterSubclass<Constraint2D, T>(engine, "Constraint2D", className);
    engine->RegisterObjectMethod(className, "void set_otherBody(RigidBody2D@+)", asMETHOD(T, SetOtherBody), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "RigidBody2D@+ get_ownerBody() const", asMETHOD(T, GetOwnerBody), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "RigidBody2D@+ get_otherBody() const", asMETHOD(T, GetOtherBody), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_collideConnected(bool)", asMETHOD(T, SetCollideConnected), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "bool get_collideConnected() const", asMETHOD(T, GetCollideConnected), asCALL_THISCALL);
}


static void RegisterConstraint2D(asIScriptEngine* engine)
{
    RegisterConstraint2D<Constraint2D>(engine, "Constraint2D");
}

static void RegisterConstraintDistance2D(asIScriptEngine* engine)
{
    RegisterConstraint2D<ConstraintDistance2D>(engine, "ConstraintDistance2D");
    engine->RegisterObjectMethod("ConstraintDistance2D", "void set_ownerBodyAnchor(const Vector2&)", asMETHOD(ConstraintDistance2D, SetOwnerBodyAnchor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "const Vector2& get_ownerBodyAnchor() const", asMETHOD(ConstraintDistance2D, GetOwnerBodyAnchor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "void set_otherBodyAnchor(const Vector2&)", asMETHOD(ConstraintDistance2D, SetOtherBodyAnchor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "const Vector2& get_otherBodyAnchor() const", asMETHOD(ConstraintDistance2D, GetOtherBodyAnchor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "void set_frequencyHz(float)", asMETHOD(ConstraintDistance2D, SetFrequencyHz), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "float get_frequencyHz() const", asMETHOD(ConstraintDistance2D, GetFrequencyHz), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "void set_dampingRatio(float)", asMETHOD(ConstraintDistance2D, SetDampingRatio), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintDistance2D", "float get_dampingRatio() const", asMETHOD(ConstraintDistance2D, GetDampingRatio), asCALL_THISCALL);
}

static void RegisterConstraintFriction2D(asIScriptEngine* engine)
{
    RegisterConstraint2D<ConstraintFriction2D>(engine, "ConstraintFriction2D");
    engine->RegisterObjectMethod("ConstraintFriction2D", "void set_anchor(const Vector2&)", asMETHOD(ConstraintFriction2D, SetAnchor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "const Vector2& get_anchor() const", asMETHOD(ConstraintFriction2D, GetAnchor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "void set_maxForce(float)", asMETHOD(ConstraintFriction2D, SetMaxForce), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "float get_maxForce() const", asMETHOD(ConstraintFriction2D, GetMaxForce), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "void set_maxTorque(float)", asMETHOD(ConstraintFriction2D, SetMaxTorque), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintFriction2D", "float get_maxTorque() const", asMETHOD(ConstraintFriction2D, GetMaxTorque), asCALL_THISCALL);
}

static void RegisterConstraintGear2D(asIScriptEngine* engine)
{
    RegisterConstraint2D<ConstraintGear2D>(engine, "ConstraintGear2D");
    engine->RegisterObjectMethod("ConstraintGear2D", "void set_ownerConstraint(Constraint2D@+)", asMETHOD(ConstraintGear2D, SetOwnerConstraint), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "Constraint2D@+ get_ownerConstraint() const", asMETHOD(ConstraintGear2D, GetOwnerConstraint), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "void set_otherConstraint(Constraint2D@+)", asMETHOD(ConstraintGear2D, SetOtherConstraint), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "Constraint2D@+ get_otherConstraint() const", asMETHOD(ConstraintGear2D, GetOtherConstraint), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "void set_ratio(float)", asMETHOD(ConstraintGear2D, SetRatio), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintGear2D", "float get_ratio() const", asMETHOD(ConstraintGear2D, GetRatio), asCALL_THISCALL);
}

static void RegisterConstraintMotor2D(asIScriptEngine* engine)
{
    RegisterConstraint2D<ConstraintMotor2D>(engine, "ConstraintMotor2D");
    engine->RegisterObjectMethod("ConstraintMotor2D", "void set_linearOffset(const Vector2&)", asMETHOD(ConstraintMotor2D, SetLinearOffset), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "const Vector2& get_linearOffset() const", asMETHOD(ConstraintMotor2D, GetLinearOffset), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "void set_angularOffset(float)", asMETHOD(ConstraintMotor2D, SetAngularOffset), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "float get_angularOffset() const", asMETHOD(ConstraintMotor2D, GetAngularOffset), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "void set_maxForce(float)", asMETHOD(ConstraintMotor2D, SetMaxForce), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "float get_maxForce() const", asMETHOD(ConstraintMotor2D, GetMaxForce), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "void set_maxTorque(float)", asMETHOD(ConstraintMotor2D, SetMaxTorque), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "float get_maxTorque() const", asMETHOD(ConstraintMotor2D, GetMaxTorque), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "void set_correctionFactor(float)", asMETHOD(ConstraintMotor2D, SetCorrectionFactor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMotor2D", "float get_correctionFactor() const", asMETHOD(ConstraintMotor2D, GetCorrectionFactor), asCALL_THISCALL);
}

static void RegisterConstraintMouse2D(asIScriptEngine* engine)
{
    RegisterConstraint2D<ConstraintMouse2D>(engine, "ConstraintMouse2D");
    engine->RegisterObjectMethod("ConstraintMouse2D", "void set_target(const Vector2&)", asMETHOD(ConstraintMouse2D, SetTarget), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "const Vector2& get_target() const", asMETHOD(ConstraintMouse2D, GetTarget), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "void set_maxForce(float)", asMETHOD(ConstraintMouse2D, SetMaxForce), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "float get_maxForce() const", asMETHOD(ConstraintMouse2D, GetMaxForce), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "void set_frequencyHz(float)", asMETHOD(ConstraintMouse2D, SetFrequencyHz), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "float get_frequencyHz() const", asMETHOD(ConstraintMouse2D, GetFrequencyHz), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "void set_dampingRatio(float)", asMETHOD(ConstraintMouse2D, SetDampingRatio), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintMouse2D", "float get_dampingRatio() const", asMETHOD(ConstraintMouse2D, GetDampingRatio), asCALL_THISCALL);
}

static void RegisterConstraintPrismatic2D(asIScriptEngine* engine)
{
    RegisterConstraint2D<ConstraintPrismatic2D>(engine, "ConstraintPrismatic2D");
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void set_anchor(const Vector2&)", asMETHOD(ConstraintPrismatic2D, SetAnchor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "const Vector2& get_anchor() const", asMETHOD(ConstraintPrismatic2D, GetAnchor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void set_axis(const Vector2&)", asMETHOD(ConstraintPrismatic2D, SetAxis), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "const Vector2& get_axis() const", asMETHOD(ConstraintPrismatic2D, GetAxis), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void set_enableLimit(bool)", asMETHOD(ConstraintPrismatic2D, SetEnableLimit), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool get_enableLimit() const", asMETHOD(ConstraintPrismatic2D, GetEnableLimit), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void set_lowerTranslation(float)", asMETHOD(ConstraintPrismatic2D, SetLowerTranslation), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "float get_lowerTranslation() const", asMETHOD(ConstraintPrismatic2D, GetLowerTranslation), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void set_upperTranslation(float)", asMETHOD(ConstraintPrismatic2D, SetUpperTranslation), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "float get_upperTranslation() const", asMETHOD(ConstraintPrismatic2D, GetUpperTranslation), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void set_enableMotor(bool)", asMETHOD(ConstraintPrismatic2D, SetEnableMotor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "bool get_enableMotor() const", asMETHOD(ConstraintPrismatic2D, GetEnableMotor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void set_maxMotorForce(float)", asMETHOD(ConstraintPrismatic2D, SetMaxMotorForce), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "float get_maxMotorForce() const", asMETHOD(ConstraintPrismatic2D, GetMaxMotorForce), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "void set_motorSpeed(float)", asMETHOD(ConstraintPrismatic2D, SetMotorSpeed), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPrismatic2D", "float get_motorSpeed() const", asMETHOD(ConstraintPrismatic2D, GetMotorSpeed), asCALL_THISCALL);
}

static void RegisterConstraintPulley2D(asIScriptEngine* engine)
{
    RegisterConstraint2D<ConstraintPulley2D>(engine, "ConstraintPulley2D");
    engine->RegisterObjectMethod("ConstraintPulley2D", "void set_ownerBodyGroundAnchor(const Vector2&)", asMETHOD(ConstraintPulley2D, SetOwnerBodyGroundAnchor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "const Vector2& get_ownerBodyGroundAnchor() const", asMETHOD(ConstraintPulley2D, GetOwnerBodyGroundAnchor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "void set_otherBodyGroundAnchor(const Vector2&)", asMETHOD(ConstraintPulley2D, SetOtherBodyGroundAnchor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "const Vector2& get_otherBodyGroundAnchor() const", asMETHOD(ConstraintPulley2D, GetOtherBodyGroundAnchor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "void set_ownerBodyAnchor(const Vector2&)", asMETHOD(ConstraintPulley2D, SetOwnerBodyAnchor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "const Vector2& get_ownerBodyAnchor() const", asMETHOD(ConstraintPulley2D, GetOwnerBodyAnchor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "void set_otherBodyAnchor(const Vector2&)", asMETHOD(ConstraintPulley2D, SetOtherBodyAnchor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "const Vector2& get_otherBodyAnchor() const", asMETHOD(ConstraintPulley2D, GetOtherBodyAnchor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "void set_ratio(float)", asMETHOD(ConstraintPulley2D, SetRatio), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintPulley2D", "float get_ratio() const", asMETHOD(ConstraintPulley2D, GetRatio), asCALL_THISCALL);
}

static void RegisterConstraintRevolute2D(asIScriptEngine* engine)
{
    RegisterConstraint2D<ConstraintRevolute2D>(engine, "ConstraintRevolute2D");
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void set_anchor(const Vector2&)", asMETHOD(ConstraintRevolute2D, SetAnchor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "const Vector2& get_anchor() const", asMETHOD(ConstraintRevolute2D, GetAnchor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void set_enableLimit(bool)", asMETHOD(ConstraintRevolute2D, SetEnableLimit), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool get_enableLimit() const", asMETHOD(ConstraintRevolute2D, GetEnableLimit), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void set_lowerAngle(float)", asMETHOD(ConstraintRevolute2D, SetLowerAngle), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "float get_lowerAngle() const", asMETHOD(ConstraintRevolute2D, GetLowerAngle), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void set_upperAngle(float)", asMETHOD(ConstraintRevolute2D, SetUpperAngle), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "float get_upperAngle() const", asMETHOD(ConstraintRevolute2D, GetUpperAngle), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void set_enableMotor(bool)", asMETHOD(ConstraintRevolute2D, SetEnableMotor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "bool get_enableMotor() const", asMETHOD(ConstraintRevolute2D, GetEnableMotor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void set_motorSpeed(float)", asMETHOD(ConstraintRevolute2D, SetMotorSpeed), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "float get_motorSpeed() const", asMETHOD(ConstraintRevolute2D, GetMotorSpeed), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "void set_maxMotorTorque(float)", asMETHOD(ConstraintRevolute2D, SetMaxMotorTorque), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRevolute2D", "float get_maxMotorTorque() const", asMETHOD(ConstraintRevolute2D, GetMaxMotorTorque), asCALL_THISCALL);
}

static void RegisterConstraintWeld2D(asIScriptEngine* engine)
{
    RegisterConstraint2D<ConstraintWeld2D>(engine, "ConstraintWeld2D");
    engine->RegisterObjectMethod("ConstraintWeld2D", "void set_anchor(const Vector2&)", asMETHOD(ConstraintWeld2D, SetAnchor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "const Vector2& get_anchor() const", asMETHOD(ConstraintWeld2D, GetAnchor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "void set_frequencyHz(float)", asMETHOD(ConstraintWeld2D, SetFrequencyHz), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "float get_frequencyHz() const", asMETHOD(ConstraintWeld2D, GetFrequencyHz), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "void set_dampingRatio(float)", asMETHOD(ConstraintWeld2D, SetDampingRatio), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWeld2D", "float get_dampingRatio() const", asMETHOD(ConstraintWeld2D, GetDampingRatio), asCALL_THISCALL);
}

static void RegisterConstraintWheel2D(asIScriptEngine* engine)
{
    RegisterConstraint2D<ConstraintWheel2D>(engine, "ConstraintWheel2D");
    engine->RegisterObjectMethod("ConstraintWheel2D", "void set_anchor(const Vector2&)", asMETHOD(ConstraintWheel2D, SetAnchor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "const Vector2& get_anchor() const", asMETHOD(ConstraintWheel2D, GetAnchor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "void set_axis(const Vector2&)", asMETHOD(ConstraintWheel2D, SetAxis), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "const Vector2& get_axis() const", asMETHOD(ConstraintWheel2D, GetAxis), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "void set_enableMotor(bool)", asMETHOD(ConstraintWheel2D, SetEnableMotor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "bool get_enableMotor() const", asMETHOD(ConstraintWheel2D, GetEnableMotor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "void set_maxMotorTorque(float)", asMETHOD(ConstraintWheel2D, SetMaxMotorTorque), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "float get_maxMotorTorque() const", asMETHOD(ConstraintWheel2D, GetMaxMotorTorque), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "void set_motorSpeed(float)", asMETHOD(ConstraintWheel2D, SetMotorSpeed), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "float get_motorSpeed() const", asMETHOD(ConstraintWheel2D, GetMotorSpeed), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "void set_frequencyHz(float)", asMETHOD(ConstraintWheel2D, SetFrequencyHz), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "float get_frequencyHz() const", asMETHOD(ConstraintWheel2D, GetFrequencyHz), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "void set_dampingRatio(float)", asMETHOD(ConstraintWheel2D, SetDampingRatio), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintWheel2D", "float get_dampingRatio() const", asMETHOD(ConstraintWheel2D, GetDampingRatio), asCALL_THISCALL);
}

static void RegisterConstraintRope2D(asIScriptEngine* engine)
{
    RegisterConstraint2D<ConstraintRope2D>(engine, "ConstraintRope2D");
    engine->RegisterObjectMethod("ConstraintRope2D", "void set_ownerBodyAnchor(const Vector2&)", asMETHOD(ConstraintRope2D, SetOwnerBodyAnchor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "const Vector2& get_ownerBodyAnchor() const", asMETHOD(ConstraintRope2D, GetOwnerBodyAnchor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "void set_otherBodyAnchor(const Vector2&)", asMETHOD(ConstraintRope2D, SetOtherBodyAnchor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "const Vector2& get_otherBodyAnchor() const", asMETHOD(ConstraintRope2D, GetOtherBodyAnchor), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "void set_maxLength(float)", asMETHOD(ConstraintRope2D, SetMaxLength), asCALL_THISCALL);
    engine->RegisterObjectMethod("ConstraintRope2D", "float get_maxLength() const", asMETHOD(ConstraintRope2D, GetMaxLength), asCALL_THISCALL);
}

void RegisterUrho2DAPI(asIScriptEngine* engine)
{
    RegisterSprite2D(engine);
    RegisterSpriteSheet2D(engine);
    RegisterDrawable2D(engine);
    RegisterStaticSprite2D(engine);

    RegisterAnimation2D(engine);
    RegisterAnimationSet2D(engine);
    RegisterAnimatedSprite2D(engine);

    RegisterParticleEffect2D(engine);
    RegisterParticleEmitter2D(engine);

    RegisterTileMapDefs2D(engine);
    RegisterTmxFile2D(engine);
    RegisterTileMapLayer2D(engine);
    RegisterTileMap2D(engine);

    RegisterRigidBody2D(engine);
    RegisterPhysicsWorld2D(engine);

    RegisterCollisionShape2D(engine);
    RegisterCollisionBox2D(engine);
    RegisterCollisionCircle2D(engine);
    RegisterCollisionChain2D(engine);
    RegisterCollisionEdge2D(engine);
    RegisterCollisionPolygon2D(engine);

    RegisterConstraint2D(engine);
    RegisterConstraintDistance2D(engine);
    RegisterConstraintFriction2D(engine);
    RegisterConstraintGear2D(engine);
    RegisterConstraintMotor2D(engine);
    RegisterConstraintMouse2D(engine);
    RegisterConstraintPrismatic2D(engine);
    RegisterConstraintPulley2D(engine);
    RegisterConstraintRevolute2D(engine);
    RegisterConstraintWeld2D(engine);
    RegisterConstraintWheel2D(engine);
    RegisterConstraintRope2D(engine);
}

}
#endif
