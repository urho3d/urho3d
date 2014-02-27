//
// Copyright (c) 2008-2014 the Urho3D project.
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
#include "APITemplates.h"
#include "Drawable2D.h"
#include "Sprite2D.h"
#include "SpriteSheet2D.h"
#include "StaticSprite2D.h"
#include "ParticleModel2D.h"
#include "ParticleEmitter2D.h"

#ifdef _MSC_VER
#pragma warning(disable:4345)
#endif

namespace Urho3D
{

static void RegisterSprite2D(asIScriptEngine* engine)
{
    RegisterResource<Sprite2D>(engine, "Sprite2D");
    engine->RegisterObjectMethod("Sprite2D", "void set_texture(Texture2D@+)", asMETHODPR(Sprite2D, SetTexture, (Texture2D*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "Texture2D@+ get_texture() const", asMETHOD(Sprite2D, GetTexture), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "void set_rectangle(const IntRect&in)", asMETHODPR(Sprite2D, SetRectangle, (const IntRect&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "const IntRect& get_rectangle() const", asMETHOD(Sprite2D, GetRectangle), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "void set_hotSpot(const Vector2&in)", asMETHODPR(Sprite2D, SetHotSpot, (const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("Sprite2D", "const Vector2& get_hotSpot() const", asMETHOD(Sprite2D, GetHotSpot), asCALL_THISCALL);
}

static void RegisterSpriteSheet2D(asIScriptEngine* engine)
{
    RegisterResource<SpriteSheet2D>(engine, "SpriteSheet2D");
    engine->RegisterObjectMethod("SpriteSheet2D", "Texture2D@+ get_texture() const", asMETHOD(SpriteSheet2D, GetTexture), asCALL_THISCALL);
    engine->RegisterObjectMethod("SpriteSheet2D", "Sprite2D@+ GetSprite(const String&)", asMETHODPR(SpriteSheet2D, GetSprite, (const String&) const, Sprite2D*), asCALL_THISCALL);
    engine->RegisterObjectMethod("SpriteSheet2D", "void DefineSprite(const String&, const IntRect&, const Vector2&)", asMETHODPR(SpriteSheet2D, DefineSprite, (const String&, const IntRect&, const Vector2&), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("SpriteSheet2D", "void UpdateSprite(const String&, const IntRect&, const Vector2&)", asMETHODPR(SpriteSheet2D, UpdateSprite, (const String&, const IntRect&, const Vector2&), void), asCALL_THISCALL);    
}

/// Template function for registering a class derived from Drawable2D.
template <class T> void RegisterDrawable2D(asIScriptEngine* engine, const char* className)
{
    RegisterDrawable<T>(engine, className);
    RegisterSubclass<Drawable2D, T>(engine, "Drawable2D", className);    
    engine->RegisterObjectMethod(className, "void set_unitPerPixel(float)", asMETHOD(T, SetUnitPerPixel), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "float get_unitPerPixel() const", asMETHOD(T, GetUnitPerPixel), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_sprite(Sprite2D@+)", asMETHODPR(T, SetSprite, (Sprite2D*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Sprite2D@+ get_sprite() const", asMETHOD(T, GetSprite), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_material(Material@+)", asMETHODPR(T, SetMaterial, (Material*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "Material@+ get_material() const", asMETHOD(T, GetMaterial), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_blendMode(BlendMode)", asMETHOD(T, SetBlendMode), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "BlendMode get_blendMode() const", asMETHOD(T, GetBlendMode), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "void set_zValue(float)", asMETHOD(T, SetZValue), asCALL_THISCALL);
    engine->RegisterObjectMethod(className, "float get_zValue() const", asMETHOD(T, GetZValue), asCALL_THISCALL);
}

static void RegisterDrawable2D(asIScriptEngine* engine)
{
    RegisterDrawable2D<Drawable2D>(engine, "Drawable2D");
}

static void RegisterStaticSprite2D(asIScriptEngine* engine)
{
    RegisterDrawable2D<StaticSprite2D>(engine, "StaticSprite2D");
    engine->RegisterObjectMethod("StaticSprite2D", "void SetFlip(bool, bool)", asMETHODPR(StaticSprite2D, SetFlip, (bool, bool), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_flipX(bool)", asMETHOD(StaticSprite2D, SetFlipX), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "bool get_flipX() const", asMETHOD(StaticSprite2D, GetFlipX), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_flipY(bool)", asMETHOD(StaticSprite2D, SetFlipY), asCALL_THISCALL);    
    engine->RegisterObjectMethod("StaticSprite2D", "bool get_flipY() const", asMETHOD(StaticSprite2D, GetFlipY), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "void set_color(const Color&in)", asMETHOD(StaticSprite2D, SetColor), asCALL_THISCALL);
    engine->RegisterObjectMethod("StaticSprite2D", "const Color& get_color() const", asMETHOD(StaticSprite2D, GetColor), asCALL_THISCALL);
}

static void RegisterParticleModel2D(asIScriptEngine* engine)
{
    engine->RegisterEnum("EmitterType2D");
    engine->RegisterEnumValue("EmitterType2D", "EMITTER_TYPE_GRAVITY", EMITTER_TYPE_GRAVITY);
    engine->RegisterEnumValue("EmitterType2D", "EMITTER_TYPE_RADIAL", EMITTER_TYPE_RADIAL);

    RegisterResource<ParticleModel2D>(engine, "ParticleModel2D");
}

static void RegisterParticleEmitter2D(asIScriptEngine* engine)
{
    RegisterDrawable2D<ParticleEmitter2D>(engine, "ParticleEmitter2D");
    engine->RegisterObjectMethod("ParticleEmitter2D", "void set_model(ParticleModel2D@+)", asMETHODPR(ParticleEmitter2D, SetModel, (ParticleModel2D*), void), asCALL_THISCALL);
    engine->RegisterObjectMethod("ParticleEmitter2D", "ParticleModel2D@+ get_model() const", asMETHOD(ParticleEmitter2D, GetModel), asCALL_THISCALL);
}

void RegisterUrho2DAPI(asIScriptEngine* engine)
{
    RegisterSprite2D(engine);
    RegisterSpriteSheet2D(engine);
    RegisterDrawable2D(engine);
    RegisterStaticSprite2D(engine);
    RegisterParticleModel2D(engine);
    RegisterParticleEmitter2D(engine);
}

}
